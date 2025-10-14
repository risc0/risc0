// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#if defined(__HIPCC__) && !defined(__SPPARK_FF_MONT_T_HIP__)
# define __SPPARK_FF_MONT_T_HIP__

# include <cstddef>
# include <cstdint>
# include "pow.hpp"

//
// This is a trimmed-down version tailored for use in NTT only.
//

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

# define __MONT_T_STR(x) #x
# define __MONT_T_XSTR(x) __MONT_T_STR(x)
# define S_OP(op) "s_" #op "_b" __MONT_T_XSTR(__AMDGCN_WAVEFRONT_SIZE) " "

# define inline __device__ __forceinline__

//
// To instantiate declare modulus as __device__ __constant___ const and
// complement it with its factual bit-length and the corresponding 32-bit
// Motgomery factor. Bit-length has to be such that (N+31)/32 is even
// and not less than 4.
//
template<const size_t N, const uint32_t MOD[(N+31)/32], const uint32_t& M0,
         const uint32_t RR[(N+31)/32], const uint32_t ONE[(N+31)/32],
         const uint32_t MODx[(N+31)/32] = MOD>
class __align__(((N+63)/64)&1 ? 8 : 16) mont_t {
public:
    static const size_t nbits = N;
    static constexpr size_t __device__ bit_length() { return N; }
    static const uint32_t degree = 1;
    using mem_t = mont_t;
protected:
    static const size_t n = (N+31)/32;
    static_assert((n%2) == 0 && n >= 4, "unsupported bit length");
private:
    uint32_t val[n];

# if __AMDGCN_WAVEFRONT_SIZE == 64
    using cond_t = uint64_t;
# else
    using cond_t = uint32_t;
# endif

    static __device__ __noinline__ void noop()          { asm("");       }

    inline operator const uint32_t*() const             { return val;    }
    inline operator uint32_t*()                         { return val;    }

public:
    inline uint32_t& operator[](size_t i)               { return val[i]; }
    inline const uint32_t& operator[](size_t i) const   { return val[i]; }
    inline constexpr size_t len() const                 { return n;      }

    inline mont_t() {}
    inline mont_t(const uint32_t p[n])
    {
        for (size_t i=0; i<n; i++)
            val[i] = p[i];
    }

    template<typename... Ts>
    constexpr mont_t(uint32_t a0, Ts... arr) : val{a0, arr...} {}

    __host__ mont_t(const uint64_t p[n/2])
    {
        for (size_t i=0; i<n/2; i++) {
            val[2*i]     = (uint32_t)(p[i]);
            val[2*i + 1] = (uint32_t)(p[i] >> 32);
        }
    }

    inline void store(uint32_t p[n]) const
    {
        for (size_t i=0; i<n; i++)
            p[i] = val[i];
    }

    inline mont_t& operator+=(const mont_t& b)
    {
        cond_t carry;

        asm("v_add_co_u32   %0, %1, %0, %2"         : "+v"(val[0]), "=s"(carry)
                                                    : "v"(b[0]));
        for (size_t i=1; i<n; i++)
            asm( v_addc_co_u32 "%0, %1, %0, %2, %1" : "+v"(val[i]), "+s"(carry)
                                                    : "v"(b[i]));
        final_sub(carry);

        return *this;
    }
    friend inline mont_t operator+(mont_t a, const mont_t& b)
    {   return a += b;   }

    inline mont_t& operator-=(const mont_t& b)
    {
        cond_t borrow, carry;
        uint32_t tmp[n];

        asm("v_sub_co_u32   %0, %1, %0, %2"         : "+v"(val[0]), "=s"(borrow)
                                                    : "v"(b[0]));
        for (size_t i=1; i<n; i++)
            asm( v_subb_co_u32 "%0, %1, %0, %2, %1" : "+v"(val[i]), "+s"(borrow)
                                                    : "v"(b[i]));

        asm("v_add_co_u32   %0, %1, %2, %3"         : "=v"(tmp[0]), "=s"(carry)
                                                    : "v"(val[0]), "v"(MOD[0]));
        for (size_t i=1; i<n; i++) {
            asm( v_addc_co_u32 "%0, %1, %2, %3, %1" : "=v"(tmp[i]), "+s"(carry)
                                                    : "v"(val[i]), "v"(MOD[i]));
            asm("v_cndmask_b32  %0, %0, %1, %2"     : "+v"(val[i-1])
                                                    : "v"(tmp[i-1]), "s"(borrow));
        }
        asm("v_cndmask_b32  %0, %0, %1, %2"         : "+v"(val[n-1])
                                                    : "v"(tmp[n-1]), "s"(borrow));
        noop();

        return *this;
    }
    friend inline mont_t operator-(mont_t a, const mont_t& b)
    {   return a -= b;   }

    friend inline mont_t operator*(const mont_t& a, const mont_t& b)
    {
        union { uint64_t ul; uint32_t u[2]; };
        cond_t carry = 0;
        mont_t ret;
        size_t i;

        uint64_t mx = b[0];
        ul = mx * a[0];
        ret[0] = u[0];
        for (i=1; i<n; i++) {
            ul = mx * a[i] + u[1];
            ret[i] = u[0];
        }
        auto top = u[1];

        for (size_t j=0; ; ) {
            mx = M0 * ret[0];
            ul = mx * MOD[0] + ret[0];
            for (i=1; i<n; i++) {
                ul = (mx * MOD[i] + u[1]) + ret[i];
                ret[i-1] = u[0];
            }
            if (N%32 != 0) {
                ret[n-1] = u[1] + top;
            } else {
                asm( v_addc_co_u32 "%0, %1, %2, %3, %1" : "=v"(ret[n-1]), "+s"(carry)
                                                        : "v"(u[1]), "v"(top));
            }

            if (++j == n)
                break;

            mx = b[j];
            ul = mx * a[0] + ret[0];
            ret[0] = u[0];
            for (i=1; i<n; i++) {
                ul = (mx * a[i] + u[1]) + ret[i];
                ret[i] = u[0];
            }
            if (N%32 != 0) {
                top = u[1];
            } else {
                asm( v_addc_co_u32 "%0, %1, %2, 0, %1"  : "=v"(top), "+s"(carry)
                                                        : "v"(u[1]));
            }
        }

        ret.final_sub(carry);

        return ret;
    }
    inline mont_t& operator*=(const mont_t& a)
    {   return *this = *this * a;   }

    inline mont_t& sqr()
    {   return *this = *this * *this;   }

    // raise to a variable power, variable in respect to threadIdx,
    // but mind the ^ operator's precedence!
    inline mont_t& operator^=(uint32_t p)
    {   return pow_byref(*this, p);   }
    friend inline mont_t operator^(mont_t a, uint32_t p)
    {   return a ^= p;   }
    inline mont_t operator()(uint32_t p)
    {   return *this^p;   }

    // raise to a constant power, e.g. x^7, to be unrolled at compile time
    inline mont_t& operator^=(int p)
    {   return pow_byref(*this, p);   }
    friend inline mont_t operator^(mont_t a, int p)
    {   return p == 2 ? a *= a : a ^= p;   }
    inline mont_t operator()(int p)
    {   return *this^p;   }
    friend inline mont_t sqr(const mont_t& a)
    {   return a^2;   }

    inline void to()    { mont_t t = RR * *this; *this = t; }
    inline void from()  { mul_by_1(); }

    static inline const mont_t& one()
    {   return *reinterpret_cast<const mont_t*>(ONE);   }

    inline void zero()
    {
        if (n%4 == 0) {
            uint4* p = reinterpret_cast<uint4*>(val);
            for (size_t i=0; i<sizeof(val)/(sizeof(uint4)); i++)
                p[i] = uint4{0, 0, 0, 0};
        } else {
            uint64_t* p = reinterpret_cast<uint64_t*>(val);
            for (size_t i=0; i<sizeof(val)/(sizeof(uint64_t)); i++)
                p[i] = 0;
        }
    }

    friend inline mont_t czero(const mont_t& a, int set_z)
    {
        mont_t ret;
        cond_t cond;

        asm("v_cmp_ne_u32  %0, %1, 0"           : "=s"(cond)
                                                : "v"(set_z));
        for (size_t i=0; i<n; i++)
            asm("v_cndmask_b32 %0, %1, 0, %2"   : "=v"(ret[i])
                                                : "v"(a[i]), "s"(cond));
        return ret;
    }

    static inline mont_t csel(const mont_t& a, const mont_t& b, int sel_a)
    {
        mont_t ret;
        cond_t cond;

        asm("v_cmp_ne_u32  %0, %1, 0"           : "=s"(cond)
                                                : "v"(sel_a));
        for (size_t i=0; i<n; i++)
            asm("v_cndmask_b32 %0, %1, %2, %3"  : "=v"(ret[i])
                                                : "v"(b[i]), "v"(a[i]), "s"(cond));
        return ret;
    }

    inline void shfl_bfly(uint32_t laneMask)
    {
        uint32_t idx = (threadIdx.x ^ laneMask) << 2;

        for (size_t i=0; i<n; i++)
            val[i] = __builtin_amdgcn_ds_bpermute(idx, val[i]);
    }

private:
    inline void final_sub(cond_t carry)
    {
        cond_t borrow;
        uint32_t tmp[n];

        asm("v_sub_co_u32   %0, %1, %2, %3"         : "=v"(tmp[0]), "=s"(borrow)
                                                    : "v"(val[0]), "v"(MOD[0]));
        for (size_t i=1; i<n; i++)
            asm( v_subb_co_u32 "%0, %1, %2, %3, %1" : "=v"(tmp[i]), "+s"(borrow)
                                                    : "v"(val[i]), "v"(MOD[i]));
        asm(S_OP(orn2)     "%0, %0, %1"             : "+s"(carry)
                                                    : "s"(borrow));
        for (size_t i=0; i<n; i++)
            asm("v_cndmask_b32  %0, %0, %1, %2"     : "+v"(val[i])
                                                    : "v"(tmp[i]), "s"(carry));
        noop();
    }

    inline void mul_by_1()
    {
        union { uint64_t ul; uint32_t u[2]; };

        for (size_t j=0; j<n; j++) {
            uint64_t mx = M0 * val[0];
            ul = mx * MOD[0] + val[0];
            for (size_t i=1; i<n; i++) {
                ul = (mx * MOD[i] + u[1]) + val[i];
                val[i-1] = u[0];
            }
            val[n-1] = u[1];
        }
    }
};

# undef inline
# undef v_subb_co_u32
# undef v_addc_co_u32
# undef S_OP
# undef __MONT_T_XSTR
# undef __MONT_T_STR
#endif
