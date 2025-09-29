// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#if defined(__HIPCC__) && !defined(__SPPARK_FF_GL64_T_HIP__)
#define __SPPARK_FF_GL64_T_HIP__

# include <cstddef>
# include <cstdint>
# include "pow.hpp"

# if defined(__GFX10__) || defined(__GFX11__) || defined(__GFX12__)
#  define v_addc_co_u32 "v_add_co_ci_u32 "
#  define v_subb_co_u32 "v_sub_co_ci_u32 "
# elif defined(__GFX9__)
#  define v_addc_co_u32 "v_addc_co_u32 "
#  define v_subb_co_u32 "v_subb_co_u32 "
# elif !defined(__HIP_DEVICE_COMPILE__)
#  define v_addc_co_u32 "v_dummy "
#  define v_subb_co_u32 "v_dummy "
# else
#  error "unsupported GFX architecture"
# endif

# define __GL64_T_STR(x) #x
# define __GL64_T_XSTR(x) __GL64_T_STR(x)
# define S_OP(op) "s_" #op "_b" __GL64_T_XSTR(__AMDGCN_WAVEFRONT_SIZE) " "

# define inline __device__ __forceinline__

class gl64_t {
private:
    union {
        uint64_t ul;
        uint32_t u[2];
    };
#if __AMDGCN_WAVEFRONT_SIZE == 64
    using cond_t = uint64_t;
#else
    using cond_t = uint32_t;
#endif

public:
    using mem_t = gl64_t;
    static const uint32_t degree = 1;
    static const unsigned nbits = 64;
    static const uint64_t MOD = 0xffffffff00000001U;
    static constexpr size_t __device__ bit_length()     { return 64; }

    inline uint32_t& operator[](size_t i)               { return u[i]; }
    inline const uint32_t& operator[](size_t i) const   { return u[i]; }
    inline size_t len() const                           { return 2;    }

    inline gl64_t()                                     {}
    inline gl64_t(int a)                    : ul(a)     {}
#ifdef __HIP_DEVICE_COMPILE__
    inline gl64_t(uint64_t a)               : ul(a)     { to(); }
#else
    __host__ constexpr gl64_t(uint64_t a)   : ul(a)     {}
#endif
    inline gl64_t(const uint64_t *p)        : ul(*p)    { to(); }

    inline operator uint64_t() const
    {   auto ret = *this; ret.from(); return ret.ul;   }
    inline void store(uint64_t *p) const
    {   *p = *this;   }

    inline gl64_t& operator+=(const gl64_t& b)
    {
        cond_t carry, borrow;
        uint32_t lo, hi;

        asm("v_add_co_u32   %0, %1, %0, %2"     : "+v"(u[0]), "=s"(carry)
                                                : "v"(b[0]));
        asm( v_addc_co_u32 "%0, %1, %0, %2, %1" : "+v"(u[1]), "+s"(carry)
                                                : "v"(b[1]));
        asm("v_sub_co_u32   %0, %1, %2, 1"      : "=v"(lo), "=s"(borrow)
                                                : "v"(u[0]));
        asm( v_subb_co_u32 "%0, %1, %2, -1, %1" : "=v"(hi), "+s"(borrow)
                                                : "v"(u[1]));
#if defined(__GFX11__)
        asm(S_OP(or_not1)  "%0, %0, %1"         : "+s"(carry)
                                                : "s"(borrow));
#else
        asm(S_OP(orn2)     "%0, %0, %1"         : "+s"(carry)
                                                : "s"(borrow));
#endif
        asm("v_cndmask_b32  %0, %0, %1, %2"     : "+v"(u[0])
                                                : "v"(lo), "s"(carry));
        asm("v_cndmask_b32  %0, %0, %1, %2"     : "+v"(u[1])
                                                : "v"(hi), "s"(carry));
        return *this;
    }
    friend inline gl64_t operator+(gl64_t a, const gl64_t& b)
    {   return a += b;   }

    inline gl64_t& operator-=(const gl64_t& b)
    {
        cond_t borrow, carry;
        uint32_t lo, hi;

        asm("v_sub_co_u32   %0, %1, %0, %2"     : "+v"(u[0]), "=s"(borrow)
                                                : "v"(b[0]));
        asm( v_subb_co_u32 "%0, %1, %0, %2, %1" : "+v"(u[1]), "+s"(borrow)
                                                : "v"(b[1]));
        asm("v_add_co_u32   %0, %1, %2, 1"      : "=v"(lo), "=s"(carry)
                                                : "v"(u[0]));
        asm( v_addc_co_u32 "%0, %1, %2, -1, %1" : "=v"(hi), "+s"(carry)
                                                : "v"(u[1]));
        asm("v_cndmask_b32  %0, %0, %1, %2"     : "+v"(u[0])
                                                : "v"(lo), "s"(borrow));
        asm("v_cndmask_b32  %0, %0, %1, %2"     : "+v"(u[1])
                                                : "v"(hi), "s"(borrow));
        return *this;
    }
    friend inline gl64_t operator-(gl64_t a, const gl64_t& b)
    {   return a -= b;   }

    inline gl64_t& operator<<=(int l)
    {
        uint32_t carry;
        cond_t borrow;

        while (l--) {
            carry = (int)u[1] >> 31;
            asm("v_lshlrev_b64  %0, 1, %0"          : "+v"(ul));
            asm("v_add_co_u32   %0, %1, %0, %2"     : "+v"(u[0]), "=s"(borrow)
                                                    : "v"(carry));
            asm( v_addc_co_u32 "%0, %1, %0, 0, %1"  : "+v"(u[1]), "+s"(borrow));
        }

        return *this;
    }
    friend inline gl64_t operator<<(gl64_t a, int l)
    {   return a <<= l;   }

    inline gl64_t& operator>>=(int r)
    {
        uint32_t odd;
        cond_t carry;

        while (r--) {
            odd = u[0]&1;
            asm("v_add_co_u32   %0, %1, %0, %2"     : "+v"(u[0]), "=s"(carry)
                                                    : "v"(odd));
            asm( v_addc_co_u32 "%0, %1, %0, %2, %1" : "+v"(u[1]), "+s"(carry)
                                                    : "v"(-odd));
            asm( v_addc_co_u32 "%0, %1, 0, 0, %1"   : "=v"(odd), "+s"(carry));
            asm("v_lshrrev_b64  %0, 1, %0"          : "+v"(ul));
            u[1] |= odd<<31;
        }

        return *this;
    }
    friend inline gl64_t operator>>(gl64_t a, int r)
    {   return a >>= r;   }

private:
    inline gl64_t& cneg(cond_t cond)
    {
        cond_t borrow, nzero;
        uint32_t lo, hi;

        asm("v_cmp_ne_u64   %0, %1, 0"          : "=s"(nzero)
                                                : "v"(ul));
        asm("v_sub_co_u32   %0, %1, 1, %2"      : "=v"(lo), "=s"(borrow)
                                                : "v"(u[0]));
        asm(S_OP(and)      "%0, %0, %1"         : "+s"(cond)
                                                : "s"(nzero));
        asm( v_subb_co_u32 "%0, %1, -1, %2, %1" : "=v"(hi), "+s"(borrow)
                                                : "v"(u[1]));
        asm("v_cndmask_b32  %0, %0, %1, %2"     : "+v"(u[0])
                                                : "v"(lo), "s"(cond));
        asm("v_cndmask_b32  %0, %0, %1, %2"     : "+v"(u[1])
                                                : "v"(hi), "s"(cond));
        return *this;
    }

public:
    inline gl64_t& cneg(int flag)
    {
        cond_t cond;
        asm("v_cmp_ne_u32 %0, %1, 0" : "=s"(cond) : "v"(flag));
        return cneg(cond);
    }
    static inline gl64_t cneg(gl64_t a, int flag)
    {   return a.cneg(flag);   }
    inline gl64_t operator-() const
    {   gl64_t ret = *this; return ret.cneg((cond_t)0-1);   }

    static inline const gl64_t one()
    {   gl64_t ret; ret.ul = 1; return ret;   }

    inline bool is_zero() const { return ul == 0;   }
    inline bool is_one()  const { return ul == 1;   }

    inline void zero()
    {   ul = 0;   }

    friend inline gl64_t czero(const gl64_t& a, int set_z)
    {
        gl64_t ret;
        cond_t cond;

        asm("v_cmp_ne_u32  %0, %1, 0"       : "=s"(cond)
                                            : "v"(set_z));
        asm("v_cndmask_b32 %0, %1, 0, %2"   : "=v"(ret[0])
                                            : "v"(a[0]), "s"(cond));
        asm("v_cndmask_b32 %0, %1, 0, %2"   : "=v"(ret[1])
                                            : "v"(a[1]), "s"(cond));
        return ret;
    }

    static inline gl64_t csel(const gl64_t& a, const gl64_t& b, int sel_a)
    {
        gl64_t ret;
        cond_t cond;

        asm("v_cmp_ne_u32  %0, %1, 0"       : "=s"(cond)
                                            : "v"(sel_a));
        asm("v_cndmask_b32 %0, %1, %2, %3"  : "=v"(ret[0])
                                            : "v"(b[0]), "v"(a[0]), "s"(cond));
        asm("v_cndmask_b32 %0, %1, %2, %3"  : "=v"(ret[1])
                                            : "v"(b[1]), "v"(a[1]), "s"(cond));
        return ret;
    }

private:
    inline void mul(uint32_t b)
    {
        cond_t carry;
        uint32_t hi;
        union { unsigned __int128 ull; uint64_t ul; uint32_t u[3]; } temp;

        temp.ull = ul * (unsigned __int128)b;

        asm("v_mad_u64_u32  %0, %1, %2, -1, %3" : "=v"(ul), "=s"(carry)
                                                : "v"(temp.u[2]), "v"(temp.ul));
        asm( v_addc_co_u32 "%0, %1, 0, 0, %1"   : "=v"(hi), "+s"(carry));

        asm("v_sub_co_u32   %0, %1, %0, %2"     : "+v"(u[0]), "=s"(carry)
                                                : "v"(hi));
        asm( v_subb_co_u32 "%0, %1, %0, %2, %1" : "+v"(u[1]), "+s"(carry)
                                                : "v"(-hi));
    }

public:
    friend inline gl64_t operator*(gl64_t a, uint32_t b)
    {   a.mul(b); a.to(); return a;   }
    inline gl64_t& operator*=(uint32_t a)
    {   mul(a);   to();   return *this;   }

private:
    using wide_t = union { unsigned __int128 ull; uint64_t ul[2]; uint32_t u[4]; };

    inline void mul(const gl64_t& b)
    {
        wide_t temp;
        temp.ull = (unsigned __int128)ul * b.ul;
        reduce(temp);
    }

    inline void reduce(wide_t &w)
    {
        cond_t carry, borrow;

        asm("v_mad_u64_u32  %0, %1, %2, -1, %0" : "+v"(w.ul[0]), "=s"(carry)
                                                : "v"(w.u[2]));
        asm( v_addc_co_u32 "%0, %1, 0, 0, %1"   : "=v"(w.u[2]), "+s"(carry));

        asm("v_sub_co_u32   %0, %1, %0, %2"     : "+v"(w.u[0]), "=s"(borrow)
                                                : "v"(w.u[3]));
        asm( v_subb_co_u32 "%0, %1, %0, 0, %1"  : "+v"(w.u[1]), "+s"(borrow));
        asm( v_subb_co_u32 "%0, %1, %0, 0, %1"  : "+v"(w.u[2]), "+s"(borrow));

        asm("v_sub_co_u32   %0, %1, %2, %3"     : "=v"(u[0]), "=s"(carry)
                                                : "v"(w.u[0]), "v"(w.u[2]));
        asm( v_subb_co_u32 "%0, %1, %2, %3, %1" : "=v"(u[1]), "+s"(carry)
                                                : "v"(w.u[1]), "v"(-(int)w.u[2]>>1));
    }

public:
    friend inline gl64_t operator*(gl64_t a, const gl64_t& b)
    {   a.mul(b); a.to(); return a;   }
    inline gl64_t& operator*=(const gl64_t& a)
    {   mul(a);   to();   return *this;   }

    // raise to a variable power, variable in respect to threadIdx,
    // but mind the ^ operator's precedence!
    inline gl64_t& operator^=(uint32_t p)
    {   return pow_byref(*this, p);   }
    friend inline gl64_t operator^(gl64_t a, uint32_t p)
    {   return a ^= p;   }
    inline gl64_t operator()(uint32_t p)
    {   return *this^p;   }

    // raise to a constant power, e.g. x^7, to be unrolled at compile time
    inline gl64_t& operator^=(int p)
    {   return pow_byref(*this, p);   }
    friend inline gl64_t operator^(gl64_t a, int p)
    {   return a ^= p;   }
    inline gl64_t operator()(int p)
    {   return *this^p;   }
    friend inline gl64_t sqr(gl64_t a)
    {   return a.sqr();   }
    inline gl64_t& sqr()
    {   mul(*this); to(); return *this;   }

private:
    inline void final_sub()
    {
        uint32_t lo, hi;
        cond_t borrow;

        asm("v_sub_co_u32   %0, %1, %2, 1"      : "=v"(lo), "=s"(borrow)
                                                : "v"(u[0]));
        asm( v_subb_co_u32 "%0, %1, %2, -1, %1" : "=v"(hi), "+s"(borrow)
                                                : "v"(u[1]));
        asm("v_cndmask_b32  %0, %1, %0, %2"     : "+v"(u[0])
                                                : "v"(lo), "s"(borrow));
        asm("v_cndmask_b32  %0, %1, %0, %2"     : "+v"(u[1])
                                                : "v"(hi), "s"(borrow));
    }

public:
    inline void to()    { final_sub(); }
    inline void from()  {}

    template<size_t T>
    static inline gl64_t dot_product(const gl64_t a[T], const uint8_t b[T])
    {
        uint64_t lo_acc, hi_acc;
        cond_t lo_c, hi_c;

        uint32_t bi = b[0];
        asm("v_mad_u64_u32 %0, %1, %2, %3, 0"   : "=v"(lo_acc), "=s"(lo_c)
                                                : "v"(a[0][0]), "v"(bi));
        asm("v_mad_u64_u32 %0, %1, %2, %3, 0"   : "=v"(hi_acc), "=s"(hi_c)
                                                : "v"(a[0][1]), "v"(bi));

        for (uint32_t i = 1; i < T; i++) {
            bi = b[i];
            asm("v_mad_u64_u32 %0, %1, %2, %3, %0"  : "+v"(lo_acc), "=s"(lo_c)
                                                    : "v"(a[i][0]), "v"(bi));
            asm("v_mad_u64_u32 %0, %1, %2, %3, %0"  : "+v"(hi_acc), "=s"(hi_c)
                                                    : "v"(a[i][1]), "v"(bi));
        }

        gl64_t ret;
        uint32_t carry;

        ret.ul = lo_acc;
        asm("v_add_co_u32   %0, %1, %0, %2"     : "+v"(ret[1]), "=s"(lo_c)
                                                : "v"((uint32_t)hi_acc));
        asm( v_addc_co_u32 "%0, %1, %2, 0, %1"  : "=v"(carry),  "+s"(lo_c)
                                                : "v"((uint32_t)(hi_acc>>32)));

        asm("v_mad_u64_u32  %0, %1, %2, -1, %0" : "+v"(ret.ul), "=s"(hi_c)
                                                : "v"(carry));
        asm( v_addc_co_u32 "%0, %1, 0, 0, %1"   : "=v"(carry), "+s"(hi_c));

        asm("v_sub_co_u32   %0, %1, %0, %2"     : "+v"(ret[0]), "=s"(lo_c)
                                                : "v"(carry));
        asm( v_subb_co_u32 "%0, %1, %0, %2, %1" : "+v"(ret[1]), "+s"(lo_c)
                                                : "v"(-carry));
        ret.to();
        return ret;
    }

    template<size_t T>
    static inline gl64_t dot_product(const gl64_t a[T], const gl64_t b[T])
    {
        uint64_t lo_acc, mi_acc, hi_acc;
        uint32_t lo_top, mi_top, hi_top;
        cond_t lo_c, hi_c;

        uint32_t a_lo = a[0][0], b_lo = b[0][0];
        uint32_t a_hi = a[0][1], b_hi = b[0][1];

        asm("v_mad_u64_u32  %0, %1, %2, %3, 0"  : "=v"(lo_acc), "=s"(lo_c)
                                                : "v"(a_lo), "v"(b_lo));
        lo_top = 0;

        asm("v_mad_u64_u32  %0, %1, %2, %3, 0"  : "=v"(mi_acc), "=s"(hi_c)
                                                : "v"(a_lo), "v"(b_hi));
        asm("v_mad_u64_u32  %0, %1, %2, %3, %0" : "+v"(mi_acc), "=s"(lo_c)
                                                : "v"(a_hi), "v"(b_lo));
        asm( v_addc_co_u32 "%0, %1, 0, 0, %1"   : "=v"(mi_top), "+s"(lo_c));

        asm("v_mad_u64_u32  %0, %1, %2, %3, 0"  : "=v"(hi_acc), "=s"(hi_c)
                                                : "v"(a_hi), "v"(b_hi));
        hi_top = 0;

        for (uint32_t i = 1; i < T; i++) {
            a_lo = a[i][0], b_lo = b[i][0];
            a_hi = a[i][1], b_hi = b[i][1];

            asm("v_mad_u64_u32  %0, %1, %2, %3, %0" : "+v"(lo_acc), "=s"(lo_c)
                                                    : "v"(a_lo), "v"(b_lo));
            asm("v_mad_u64_u32  %0, %1, %2, %3, %0" : "+v"(mi_acc), "=s"(hi_c)
                                                    : "v"(a_lo), "v"(b_hi));
            asm( v_addc_co_u32 "%0, %1, %0, 0, %1"  : "+v"(lo_top), "+s"(lo_c));
            asm("v_mad_u64_u32  %0, %1, %2, %3, %0" : "+v"(mi_acc), "=s"(lo_c)
                                                    : "v"(a_hi), "v"(b_lo));
            asm( v_addc_co_u32 "%0, %1, %0, 0, %1"  : "+v"(mi_top), "+s"(hi_c));
            asm("v_mad_u64_u32  %0, %1, %2, %3, %0" : "+v"(hi_acc), "=s"(hi_c)
                                                    : "v"(a_hi), "v"(b_hi));
            asm( v_addc_co_u32 "%0, %1, %0, 0, %1"  : "+v"(mi_top), "+s"(lo_c));
            asm( v_addc_co_u32 "%0, %1, %0, 0, %1"  : "+v"(hi_top), "+s"(hi_c));
        }

        wide_t w;
        w.u[0] = (uint32_t)lo_acc;

        asm("v_add_co_u32   %0, %1, %2, %3"     : "=v"(w.u[1]), "=s"(lo_c)
                                                : "v"((uint32_t)(lo_acc>>32)), "v"((uint32_t)mi_acc));
        asm( v_addc_co_u32 "%0, %1, %2, %3, %1" : "=v"(w.u[2]), "+s"(lo_c)
                                                : "v"((uint32_t)(mi_acc>>32)), "v"(lo_top));
        asm( v_addc_co_u32 "%0, %1, %2, %3, %1" : "=v"(w.u[3]), "+s"(lo_c)
                                                : "v"((uint32_t)(hi_acc>>32)), "v"(mi_top));
        asm( v_addc_co_u32 "%0, %1, %0, 0, %1"  : "+v"(hi_top),  "+s"(lo_c));

        asm("v_add_co_u32   %0, %1, %0, %2"     : "+v"(w.u[2]), "=s"(hi_c)
                                                : "v"((uint32_t)hi_acc));
        asm( v_addc_co_u32 "%0, %1, %0, 0, %1"  : "+v"(w.u[3]), "+s"(hi_c));
        asm( v_addc_co_u32 "%0, %1, %0, 0, %1"  : "+v"(hi_top),  "+s"(hi_c));

        // reduce modulo |(mod << 64) + (mod <<32)|
        asm("v_sub_co_u32    %0, %1, %0, %2"    : "+v"(w.u[1]), "=s"(lo_c)
                                                : "v"(hi_top));
        asm( v_subb_co_u32 "%0, %1, %0, 0, %1"  : "+v"(w.u[2]), "+s"(lo_c));
        asm( v_subb_co_u32 "%0, %1, %0, 0, %1"  : "+v"(w.u[3]), "+s"(lo_c));
        asm( v_subb_co_u32 "%0, %1, %0, %0, %1" : "+v"(hi_top),  "+s"(lo_c));

        // "add" |mod<<64| if reduction borrowed
        w.u[2] -= hi_top;

        gl64_t ret;
        ret.reduce(w);
        ret.to();
        return ret;
    }

private:
    template<int unroll> // 1, 2 or 3
    static __device__ __noinline__ gl64_t sqr_n_mul(gl64_t s, uint32_t n, gl64_t m)
    {
        if (unroll&1) {
            s.mul(s);
            n--;
        }
        if (unroll > 1) {
            #pragma unroll 1
            do {
                s.mul(s);
                s.mul(s);
            } while (n -= 2);
        }
        s.mul(m);

        return s;
    }

public:
    inline gl64_t reciprocal() const
    {
        gl64_t t0, t1;

        t1 = sqr_n_mul<1>(*this, 1, *this); // 0b11
        t0 = sqr_n_mul<2>(t1, 2,  t1);      // 0b1111
        t0 = sqr_n_mul<2>(t0, 2,  t1);      // 0b111111
        t1 = sqr_n_mul<2>(t0, 6,  t0);      // 0b111111111111
        t1 = sqr_n_mul<2>(t1, 12, t1);      // 0b111111111111111111111111
        t1 = sqr_n_mul<2>(t1, 6,  t0);      // 0b111111111111111111111111111111
        t1 = sqr_n_mul<1>(t1, 1,  *this);   // 0b1111111111111111111111111111111
        t1 = sqr_n_mul<2>(t1, 32, t1);      // 0b111111111111111111111111111111101111111111111111111111111111111
        t1 = sqr_n_mul<1>(t1, 1,  *this);   // 0b1111111111111111111111111111111011111111111111111111111111111111
        t1.to();

        return t1;
    }
    friend inline gl64_t operator/(int one, const gl64_t& a)
    {   assert(one == 1); return a.reciprocal();   }
    friend inline gl64_t operator/(const gl64_t& a, const gl64_t& b)
    {   return a * b.reciprocal();   }
    inline gl64_t& operator/=(const gl64_t& a)
    {   return *this *= a.reciprocal();   }

    inline gl64_t heptaroot() const
    {
        gl64_t t0, t1;

        t1 = sqr_n_mul<3>(*this, 3, *this); // 0b1001
        t0 = sqr_n_mul<2>(t1, 6,  t1);      // 0b1001001001
        t0 = sqr_n_mul<2>(t0, 12, t0);      // 0b1001001001001001001001
        t0 = sqr_n_mul<2>(t0, 6,  t1);      // 0b1001001001001001001001001001
        t1 = sqr_n_mul<2>(t0, 4,  *this);   // 0b10010010010010010010010010010001
        t1 = sqr_n_mul<2>(t1, 28, t0);      // 0b100100100100100100100100100100011001001001001001001001001001
        t1 = sqr_n_mul<2>(t1, 2,  t0);      // 0b10010010010010010010010010010001101101101101101101101101101101
        t1 = sqr_n_mul<1>(t1, 1,  *this);   // 0b100100100100100100100100100100011011011011011011011011011011011
        t1 = sqr_n_mul<1>(t1, 1,  *this);   // 0b1001001001001001001001001001000110110110110110110110110110110111
        t1.to();

        return t1;
    }

    inline void shfl_bfly(uint32_t laneMask)
    {
        uint32_t idx = (threadIdx.x ^ laneMask) << 2;

        u[0] = __builtin_amdgcn_ds_bpermute(idx, u[0]);
        u[1] = __builtin_amdgcn_ds_bpermute(idx, u[1]);
    }

# undef inline

public:
    friend inline bool operator==(gl64_t a, gl64_t b)
    {   return a.ul == b.ul;   }
    friend inline bool operator!=(gl64_t a, gl64_t b)
    {   return a.ul != b.ul;   }
# if defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_) // non-standard
    friend std::ostream& operator<<(std::ostream& os, const gl64_t& obj)
    {
        auto f = os.flags();
        os << "0x" << std::hex << obj.val;
        os.flags(f);
        return os;
    }
# endif
};

# undef v_subb_co_u32
# undef v_addc_co_u32
# undef S_OP
# undef __GL64_T_XSTR
# undef __GL64_T_STR
#endif /* __SPPARK_FF_GL64_T_HIP__ */
