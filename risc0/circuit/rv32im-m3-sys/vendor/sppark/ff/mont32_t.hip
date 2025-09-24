// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#if defined(__HIPCC__) && !defined(__SPPARK_FF_MONT32_T_HIP__)
#define __SPPARK_FF_MONT32_T_HIP__

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

# define __MONT32_T_STR(x) #x
# define __MONT32_T_XSTR(x) __MONT32_T_STR(x)
# define S_OP(op) "s_" #op "_b" __MONT32_T_XSTR(__AMDGCN_WAVEFRONT_SIZE) " "

# define inline __device__ __forceinline__

template<const size_t N, const uint32_t MOD, const uint32_t M0,
         const uint32_t RR, const uint32_t ONE>
class mont32_t {
private:
    uint32_t val;

# if __AMDGCN_WAVEFRONT_SIZE == 64
    using cond_t = uint64_t;
# else
    using cond_t = uint32_t;
# endif

public:
    using mem_t = mont32_t;
    static const uint32_t degree = 1;
    static constexpr size_t __device__ bit_length()     { return N;  }

    inline uint32_t& operator[](size_t i)               { return val; (void)i; }
    inline uint32_t& operator*()                        { return val; }
    inline const uint32_t& operator[](size_t i) const   { return val; (void)i; }
    inline uint32_t operator*() const                   { return val; }
    inline size_t len() const                           { return 1;   }

    inline mont32_t() {}
    inline mont32_t(const uint32_t *p)                  { val = *p; }
    // this is used in constant declaration, e.g. as mont32_t{11}
    __host__ __device__ constexpr mont32_t(int a)       : val(((uint64_t)a << 32) % MOD) {}
    __host__ __device__ constexpr mont32_t(uint32_t a)  : val(a) {}

    inline operator uint32_t() const        { return mul_by_1(); }
    inline void store(uint32_t *p) const    { *p = mul_by_1();   }
    inline mont32_t& operator=(uint32_t b)  { val = b; to(); return *this; }

    inline mont32_t& operator+=(const mont32_t b)
    {
        val += b.val;
        if (N == 32) {
            if (val < b.val || val >= MOD)  val -= MOD;
        } else {
            if (val >= MOD)                 val -= MOD;
        }

        return *this;
    }
    friend inline mont32_t operator+(mont32_t a, const mont32_t b)
    {   return a += b;   }

    inline mont32_t& operator<<=(uint32_t l)
    {
        if (N == 32) {
            while (l--) {
                bool carry = val >> 31;
                val <<= 1;
                if (carry || val >= MOD)    val -= MOD;
            }
        } else {
            while (l--) {
                val <<= 1;
                if (val >= MOD)             val -= MOD;
            }
        }

        return *this;
    }
    friend inline mont32_t operator<<(mont32_t a, uint32_t l)
    {   return a <<= l;   }

    inline mont32_t& operator>>=(uint32_t r)
    {
        while (r >= 32) {
            val = mul_by_1();
            r -= 32;
        }

        if (r > 2) {
            uint32_t red = (val * M0) & ((1<<r) - 1);
            uint64_t tmp = (uint64_t)MOD * red + val;

            val = (uint32_t)(tmp >> r);
        } else if (N == 32) {
            while (r--) {
                uint64_t tmp = val&1 ? MOD : 0;

                tmp += val;
                val = (uint32_t)(tmp >> 1);
            }
        } else {
            while (r--) {
                if (val&1)  val += MOD;
                val >>= 1;
            }
        }

        return *this;
    }
    friend inline mont32_t operator>>(mont32_t a, uint32_t r)
    {   return a >>= r;   }

    inline mont32_t& operator-=(const mont32_t b)
    {
        bool borrow = val < b.val;

        val -= b.val;
        if (borrow)
            val += MOD;

        return *this;
    }
    friend inline mont32_t operator-(mont32_t a, const mont32_t b)
    {   return a -= b;   }

    inline mont32_t& cneg(bool flag)
    {
        if (flag && val != 0)
            val = MOD - val;

        return *this;
    }
    static inline mont32_t cneg(mont32_t a, bool flag)
    {   return a.cneg(flag);   }
    inline mont32_t operator-() const
    {   return cneg(*this, true);   }

    static inline const mont32_t one()  { return mont32_t{ONE}; }
    inline bool is_one() const          { return val == ONE;    }
    inline bool is_zero() const         { return val == 0;      }
    inline void zero()                  { val = 0;              }

    friend inline mont32_t czero(const mont32_t a, int set_z)
    {   return set_z ? mont32_t{0u} : a;   }

    static inline mont32_t csel(const mont32_t a, const mont32_t b, int sel_a)
    {   return sel_a ? a : b;   }

private:
    static inline uint32_t final_sub(uint32_t val, cond_t carry)
    {
        if (N == 32) {
            cond_t borrow;
            uint32_t tmp;

            asm("v_sub_co_u32  %0, %1, %2, %3" : "=v"(tmp), "=s"(borrow)
                                               : "v"(val), "v"(MOD));
#if defined(__GFX11__)
            asm(S_OP(or_not1) "%0, %0, %1"     : "+s"(carry) : "s"(borrow));
#else
            asm(S_OP(orn2)    "%0, %0, %1"     : "+s"(carry) : "s"(borrow));
#endif
            asm("v_cndmask_b32 %0, %0, %1, %2" : "+v"(val)
                                               : "v"(tmp), "s"(carry));
        } else {
            if (val >= MOD)
                val -= MOD;
        }

        return val;
    }

    inline mont32_t& mul(const mont32_t b)
    {
        uint64_t tmp = (uint64_t)val * b.val;
        uint32_t red = (uint32_t)tmp * M0;
        cond_t carry;

        asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(tmp), "=s"(carry)
                                               : "v"(red), "v"(MOD));
        val = final_sub(tmp >> 32, carry);

        return *this;
    }

    inline uint32_t mul_by_1() const
    {
        uint32_t red = val * M0;
        uint64_t tmp;
        cond_t carry;

        asm("v_mad_u64_u32 %0, %1, %2, %3, %4" : "=v"(tmp), "=s"(carry)
                                               : "v"(red), "v"(MOD), "v"((uint64_t)val));
        return tmp >> 32;
    }

public:
    friend inline mont32_t operator*(mont32_t a, const mont32_t b)
    {   return a.mul(b);   }
    inline mont32_t& operator*=(const mont32_t a)
    {   return mul(a);   }

    // raise to a variable power, variable in respect to threadIdx,
    // but mind the ^ operator's precedence!
    inline mont32_t& operator^=(uint32_t p)
    {   return pow_byref(*this, p);   }
    friend inline mont32_t operator^(mont32_t a, uint32_t p)
    {   return a ^= p;   }
    inline mont32_t operator()(uint32_t p)
    {   return *this^p;   }

    // raise to a constant power, e.g. x^7, to be unrolled at compile time
    inline mont32_t& operator^=(int p)
    {   return pow_byref(*this, p);   }
    friend inline mont32_t operator^(mont32_t a, int p)
    {   return a ^= p;   }
    inline mont32_t operator()(int p)
    {   return *this^p;   }
    friend inline mont32_t sqr(mont32_t a)
    {   return a.sqr();   }
    inline mont32_t& sqr()
    {   return mul(*this);   }

    inline void to()   { mul(RR); }
    inline void from() { val = mul_by_1(); }

    template<size_t T>
    static inline mont32_t dot_product(const mont32_t a[T], const mont32_t b[T])
    {
        union { uint64_t acc; uint32_t ul[2]; };
        cond_t carry;

        acc = *a[0] * (uint64_t)*b[0];

        if (N == 32) {
            for (size_t i = 1; i < T; i++) {
                asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                                       : "v"(*a[i]), "v"(*b[i]));
                ul[1] = final_sub(ul[1], carry);
            }
        } else {
            size_t i = 1;

            if ((T&1) == 0) {
                asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                                       : "v"(*a[i]), "v"(*b[i]));
                i++;
            }
            for (; i < T; i += 2) {
                asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                                       : "v"(*a[i]), "v"(*b[i]));
                asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                                       : "v"(*a[i+1]), "v"(*b[i+1]));
                ul[1] = final_sub(ul[1], carry);
            }
        }

        uint32_t red = ul[0] * M0;
        asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                               : "v"(red), "v"(MOD));
        return final_sub(ul[1], carry);
    }

    template<size_t T>
    static inline mont32_t dot_product(mont32_t a0, mont32_t b0,
                                       const mont32_t a[T-1], const mont32_t *b,
                                       size_t stride_b = 1)
    {
        union { uint64_t acc; uint32_t ul[2]; };
        cond_t carry;

        acc = *a0 * (uint64_t)*b0;

        if (N == 32) {
            for (size_t i = 0; i < T-1; i++, b += stride_b) {
                asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                                       : "v"(*a[i]), "v"(*b[0]));
                ul[1] = final_sub(ul[1], carry);
            }
        } else {
            size_t i = 0;

            if ((T&1) == 0) {
                asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                                       : "v"(*a[i]), "v"(*b[0]));
                i++, b += stride_b;
            }
            for (; i < T-1; i += 2) {
                asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                                       : "v"(*a[i]), "v"(*b[0]));
                b += stride_b;
                asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                                       : "v"(*a[i+1]), "v"(*b[0]));
                b += stride_b;
                ul[1] = final_sub(ul[1], carry);
            }
        }

        uint32_t red = ul[0] * M0;
        asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                               : "v"(red), "v"(MOD));
        return final_sub(ul[1], carry);
    }

    static inline mont32_t dot_product(mont32_t a, mont32_t b,
                                       mont32_t c, mont32_t d)
    {
        union { uint64_t acc; uint32_t ul[2]; };
        cond_t carry;

        acc = *a * (uint64_t)*b;

        asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                               : "v"(*c), "v"(*d));
        if (N == 32)
            ul[1] = final_sub(ul[1], carry);

        uint32_t red = ul[0] * M0;
        asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(acc), "=s"(carry)
                                               : "v"(red), "v"(MOD));
        return final_sub(ul[1], carry);
    }

    inline mont32_t reciprocal() const
    {   return *this ^ (MOD-2);   }
    friend inline mont32_t operator/(int one, mont32_t a)
    {   assert(one == 1); return a.reciprocal();   }
    friend inline mont32_t operator/(mont32_t a, mont32_t b)
    {   return a * b.reciprocal();   }
    inline mont32_t& operator/=(const mont32_t a)
    {   return *this *= a.reciprocal();   }

    inline void shfl_bfly(uint32_t laneMask)
    {
        uint32_t idx = (threadIdx.x ^ laneMask) << 2;

        val = __builtin_amdgcn_ds_bpermute(idx, val);
    }

protected:
    static inline mont32_t sqr_n(mont32_t s, uint32_t n)
    {
        if (N == 32 || M0 > MOD) {
            #pragma unroll 2
            while (n--)
                s.sqr();
        } else {
            #pragma unroll 2
            while (n--) {
                uint64_t tmp = (uint64_t)s.val * s.val;
                uint32_t red = (uint32_t)tmp * M0;
                cond_t carry;

                asm("v_mad_u64_u32 %0, %1, %2, %3, %0" : "+v"(tmp), "=s"(carry)
                                                       : "v"(red), "v"(MOD));
                s.val = tmp >> 32;

                if (n&1)
                    s.val = final_sub(s.val, carry);
            }
        }

        return s;
    }

    static inline mont32_t sqr_n_mul(mont32_t s, uint32_t n, mont32_t m)
    {
        s = sqr_n(s, n);
        s.mul(m);

        return s;
    }

# undef inline

public:
    friend inline bool operator==(mont32_t a, mont32_t b)
    {   return a.val == b.val;   }
    friend inline bool operator!=(mont32_t a, mont32_t b)
    {   return a.val != b.val;   }

# if defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_) // non-standard
    friend std::ostream& operator<<(std::ostream& os, const mont32_t& obj)
    {
        auto f = os.flags();
        uint32_t red = obj.val * M0;
        uint64_t v = obj.val + red * (uint64_t)MOD;
        os << "0x" << std::hex << (uint32_t)(v >> 32);
        os.flags(f);
        return os;
    }
# endif
};

# undef v_subb_co_u32
# undef v_addc_co_u32
# undef S_OP
# undef __MONT32_T_XSTR
# undef __MONT32_T_STR
#endif /* __SPPARK_FF_MONT32_T_HIP__ */
