// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_FF_MERSENNE31_HPP__
#define __SPPARK_FF_MERSENNE31_HPP__

#include "pow.hpp"

#ifdef __CUDACC__   // CUDA device-side field types
# include "mont32_t.cuh"
# define inline __device__ __forceinline__

using mrs31_base = mont32_t<31, 0x7fffffff, 0x80000001, 4, 2>;

struct mrs31_t : public mrs31_base {
    // mem_t bridges the host-side non-Montgomery representation
    class mem_t { friend mrs31_t;
        uint32_t val;

    public:
        inline operator mrs31_t() const
        {   return mrs31_t{val} << 1;   }
        inline mem_t& operator=(const mrs31_t& a)
        {   val = *(a >> 1); return *this;   }
    };

    inline mrs31_t() {}
    inline mrs31_t(const mrs31_base& a) : mrs31_base(a) {}
    inline mrs31_t(const uint32_t *p)   : mrs31_base(p) {}
    inline mrs31_t(const mem_t* p)                      { *this = *p; }
    // this is used in constant declaration, e.g. as mrs31_t{11}
    __host__ __device__ constexpr mrs31_t(int a)        : mrs31_base(a) {}
    __host__ __device__ constexpr mrs31_t(uint32_t a)   : mrs31_base(a) {}

    inline operator uint32_t() const    { return *(*this >> 1); }
    inline void to()                    { *this <<= 1; }
    inline void from()                  { *this >>= 1; }
    inline void store(mem_t* p) const   { *p = *this;  }

    inline mrs31_t& operator<<=(int l);
    friend inline mrs31_t operator<<(mrs31_t a, int l)
    {   return a <<= l;   }

    inline mrs31_t& operator>>=(int r);
    friend inline mrs31_t operator>>(mrs31_t a, int r)
    {   return a >>= r;   }

    inline mrs31_t reciprocal() const;
    friend inline mrs31_t operator/(int one, mrs31_t a)
    {   if (one != 1) asm("trap;"); return a.reciprocal();   }
    friend inline mrs31_t operator/(mrs31_t a, mrs31_t b)
    {   return a * b.reciprocal();   }
    inline mrs31_t& operator/=(const mrs31_t a)
    {   *this *= a.reciprocal(); return *this;   }

    inline mrs31_t recip_sqrt() const;
    inline mrs31_t sqrt() const;
    friend inline mrs31_t sqrt(mrs31_t a)
    {   return a.sqrt();   }

    inline mrs31_t pentaroot() const;
};
# undef inline
#else
# include <cstddef>
# include <cstdint>
# include <cassert>
# if defined(__CUDACC__) || defined(__HIPCC__)
#  define inline __host__ __device__ __forceinline__
# endif
# if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable: 4068)
# elif defined(__GNUC__) && !defined(__clang__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunknown-pragmas"
# endif

class mrs31_t {
private:
    uint32_t val;

    const static uint32_t MOD = 0x7fffffff;

public:
    // mem_t is a pass-through to mirror the corresponding CUDA bridge
    class mem_t { friend mrs31_t;
        uint32_t val;

    public:
        inline operator mrs31_t() const
        {   return mrs31_t{val};   }
        inline mem_t& operator=(const mrs31_t& a)
        {   val = a; return *this;   }
    };

    static const uint32_t degree = 1;
    static constexpr size_t bit_length()                { return 31;  }

    inline uint32_t& operator[](size_t i)               { return val; (void)i; }
    inline const uint32_t& operator[](size_t i) const   { return val; (void)i; }
    inline uint32_t& operator*()                        { return val; }
    inline uint32_t operator*() const                   { return val; }
    inline size_t len() const                           { return 1;   }

    inline mrs31_t() {}
    inline constexpr mrs31_t(int a)         : val(a)    {}
    inline constexpr mrs31_t(uint32_t a)    : val(a)    {}
    inline mrs31_t(const uint32_t* p)       : val(*p)   {}
    inline mrs31_t(const mem_t* p)                      { *this = *p; }

    inline operator uint32_t() const                    { return val; }
    inline void store(uint32_t* p) const                { *p = val;   }
    inline void store(mem_t* p) const                   { *p = *this; }
    inline mrs31_t& operator=(uint32_t b)               { val = b; return *this; }

    inline mrs31_t& operator+=(const mrs31_t b)
    {
        val += b.val;
        if (val >= MOD)
            val -= MOD;

        return *this;
    }
    friend inline mrs31_t operator+(mrs31_t a, const mrs31_t b)
    {   return a += b;   }

    inline mrs31_t& operator<<=(int l);
    friend inline mrs31_t operator<<(mrs31_t a, int l)
    {   return a <<= l;   }

    inline mrs31_t& operator>>=(int r);
    friend inline mrs31_t operator>>(mrs31_t a, int r)
    {   return a >>= r;   }

    inline mrs31_t& operator-=(const mrs31_t b)
    {
        bool borrow = val < b.val;

        val -= b.val;
        if (borrow)
            val += MOD;

        return *this;
    }
    friend inline mrs31_t operator-(mrs31_t a, const mrs31_t b)
    {   return a -= b;   }

    inline mrs31_t& cneg(bool flag)
    {
        if (flag && val != 0)
            val = MOD - val;

        return *this;
    }
    static inline mrs31_t cneg(mrs31_t a, bool flag)
    {   return a.cneg(flag);   }
    inline mrs31_t operator-() const
    {   return cneg(*this, true);   }

    static inline const mrs31_t one()   { return mrs31_t{1}; }
    inline bool is_one() const          { return val == 1;   }
    inline bool is_zero() const         { return val == 0;   }
    inline void zero()                  { val = 0;           }

    friend inline mrs31_t czero(const mrs31_t a, int set_z)
    {   return set_z ? mrs31_t{0} : a;   }

    static inline mrs31_t csel(const mrs31_t a, const mrs31_t b, int sel_a)
    {   return sel_a ? a : b;   }

private:
    inline mrs31_t& mul(const mrs31_t b)
    {
        uint64_t tmp = val * (uint64_t)b.val;

        val = ((uint32_t)tmp & MOD) + (uint32_t)(tmp >> 31);
        if (val >= MOD)
            val -= MOD;

        return *this;
    }

public:
    friend inline mrs31_t operator*(mrs31_t a, const mrs31_t b)
    {   return a.mul(b);   }
    inline mrs31_t& operator*=(const mrs31_t a)
    {   return mul(a);   }

    // raise to a variable power, variable in respect to threadIdx,
    // but mind the ^ operator's precedence!
    inline mrs31_t& operator^=(uint32_t p)
    {   return pow_byref(*this, p);   }
    friend inline mrs31_t operator^(mrs31_t a, uint32_t p)
    {   return a ^= p;   }
    inline mrs31_t operator()(uint32_t p)
    {   return *this^p;   }

    // raise to a constant power, e.g. x^7, to be unrolled at compile time
    inline mrs31_t& operator^=(int p)
    {   return pow_byref(*this, p);   }
    friend inline mrs31_t operator^(mrs31_t a, int p)
    {   return a ^= p;   }
    inline mrs31_t operator()(int p)
    {   return *this^p;   }
    friend inline mrs31_t sqr(mrs31_t a)
    {   return a.sqr();   }
    inline mrs31_t& sqr()
    {   return mul(*this);   }

    template<size_t T>
    static inline mrs31_t dot_product(const mrs31_t a[T], const mrs31_t b[T])
    {
        union { uint64_t acc; uint32_t u[2]; };
        size_t i = 1;

	acc = *a[0] * (uint64_t)*b[0];

        if ((T&1) == 0) {
            acc += *a[i] * (uint64_t)*b[i];
            i++;
        }
        for (; i < T; i += 2) {
            acc += *a[i] * (uint64_t)*b[i];
            acc += *a[i+1] * (uint64_t)*b[i+1];
            if (u[1] >= MOD)
                u[1] -= MOD;
        }

        uint32_t ret = u[0] + (u[1] << 1);

        if (ret < u[0])
            ret += 2;
        if (ret >= MOD)
            ret -= MOD;

        return mrs31_t{ret};
    }

    template<size_t T>
    static inline mrs31_t dot_product(mrs31_t a0, mrs31_t b0,
                                      const mrs31_t a[T-1], const mrs31_t* b,
                                      size_t stride_b = 1)
    {
        union { uint64_t acc; uint32_t u[2]; };
        size_t i = 0;

	acc = *a0 * (uint64_t)*b0;

        if ((T&1) == 0) {
            acc += *a[i] * (uint64_t)*b[0];
            i++, b += stride_b;
        }
        for (; i < T-1; i += 2) {
            acc += *a[i] * (uint64_t)*b[0];
            b += stride_b;
            acc += *a[i+1] * (uint64_t)*b[0];
            b += stride_b;
            if (u[1] >= MOD)
                u[1] -= MOD;
        }

        uint32_t ret = u[0] + (u[1] << 1);

        if (ret < u[0])
            ret += 2;
        if (ret >= MOD)
            ret -= MOD;

        return mrs31_t{ret};
    }

    static inline mrs31_t dot_product(mrs31_t a, mrs31_t b,
                                      mrs31_t c, mrs31_t d)
    {
        uint64_t tmp = a.val*(uint64_t)b.val + c.val*(uint64_t)d.val;
        uint32_t ret = (uint32_t)(tmp >> 31);
        if (ret >= MOD)
            ret -= MOD;
        ret += (uint32_t)tmp & MOD;
        if (ret >= MOD)
            ret -= MOD;

        return mrs31_t{ret};
    }

private:
    static inline mrs31_t sqr_n(mrs31_t s, uint32_t n)
    {
        #pragma unroll 4
        while (n--) {
            uint64_t tmp = s.val * (uint64_t)s.val;

            s.val = ((uint32_t)tmp & MOD) + (uint32_t)(tmp >> 31);

            if (s.val >= MOD)
                s.val -= MOD;
        }

        return s;
    }

    static inline mrs31_t sqr_n_mul(mrs31_t s, uint32_t n, mrs31_t m)
    {
        s = sqr_n(s, n);
        s.mul(m);

        return s;
    }

public:
    inline mrs31_t recip_sqrt() const;
    inline mrs31_t sqrt() const;
    friend inline mrs31_t sqrt(mrs31_t a)
    {   return a.sqrt();   }

    inline mrs31_t reciprocal() const;
    friend inline mrs31_t operator/(int one, mrs31_t a)
    {   assert(one == 1); return a.reciprocal();   }
    friend inline mrs31_t operator/(mrs31_t a, mrs31_t b)
    {   return a * b.reciprocal();   }
    inline mrs31_t& operator/=(const mrs31_t a)
    {   *this *= a.reciprocal(); return *this;   }

    inline mrs31_t pentaroot() const;

# if defined(__CUDACC__)
#  undef inline
    __device__ __forceinline__ void shfl_bfly(uint32_t laneMask)
    {   val = __shfl_xor_sync(0xFFFFFFFF, val, laneMask);   }
# elif defined(__HIPCC__)
#  undef inline
    __device__ __forceinline__ void shfl_bfly(uint32_t laneMask)
    {
        uint32_t idx = (threadIdx.x ^ laneMask) << 2;

        val = __builtin_amdgcn_ds_bpermute(idx, val);
    }
# endif

public:
    friend inline bool operator==(mrs31_t a, mrs31_t b)
    {   return a.val == b.val;   }
    friend inline bool operator!=(mrs31_t a, mrs31_t b)
    {   return a.val != b.val;   }

# if defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_) // non-standard
    friend std::ostream& operator<<(std::ostream& os, const mrs31_t& obj)
    {
        auto f = os.flags();
        os << "0x" << std::hex << obj.val;
        os.flags(f);
        return os;
    }
# endif
};
# if defined(_MSC_VER)
#  pragma warning(pop)
# elif defined(__GNUC__) && !defined(__clang__)
#  pragma GCC diagnostic pop
# endif
#endif

#if defined(__CUDACC__) && defined(__SPPARK_FF_MONT32_T_CUH__)
# define inline __device__ __forceinline__
#elif defined(__CUDACC__) || defined(__HIPCC__)
# define inline __host__ __device__ __forceinline__
#endif
inline mrs31_t& mrs31_t::operator<<=(int l)
{
    l = (l&31) + (l>>5);    // l %= 31 for l<1055 [with below correction]
    if (l >= 31)
        l -= 31;
    val = ((val << l) & 0x7fffffff) | (val >> (31-l));
    return *this;
}

inline mrs31_t& mrs31_t::operator>>=(int r)
{
    r = (r&31) + (r>>5);    // r %= 31 for r<1055 [with below correction]
    if (r >= 31)
        r -= 31;
    val = ((val << (31-r)) & 0x7fffffff) | (val >> r);
    return *this;
}

inline mrs31_t mrs31_t::reciprocal() const
{
    mrs31_t x05, x0f, x7d, xff, ret = *this;

    x05 = sqr_n_mul(ret, 2, ret);   // 0b101
    x0f = sqr_n_mul(x05, 1, x05);   // 0b1111
    x7d = sqr_n_mul(x0f, 3, x05);   // 0b1111101
    xff = sqr_n_mul(x7d, 1, x05);   // 0b11111111
    ret = sqr_n_mul(xff, 8, xff);   // 0b1111111111111111
    ret = sqr_n_mul(ret, 8, xff);   // 0b111111111111111111111111
    ret = sqr_n_mul(ret, 7, x7d);   // 0b1111111111111111111111111111101

    return ret;
}

/*
 * is-square check is on caller. Note that if the result is invalid for
 * a specific value, it's correct for its negative.
 */
inline mrs31_t mrs31_t::sqrt() const
{   return sqr_n(*this, 29);   }

inline mrs31_t mrs31_t::recip_sqrt() const
{
    mrs31_t x03, x0f, xff, ret = *this;

    x03 = sqr_n_mul(ret, 1, ret);   // 0b11
    x0f = sqr_n_mul(x03, 2, x03);   // 0b1111
    xff = sqr_n_mul(x0f, 4, x0f);   // 0b11111111
    ret = sqr_n_mul(xff, 8, xff);   // 0b1111111111111111
    ret = sqr_n_mul(ret, 8, xff);   // 0b111111111111111111111111
    ret = sqr_n_mul(ret, 4, x0f);   // 0b1111111111111111111111111111
    ret = sqr_n_mul(ret, 1, *this); // 0b11111111111111111111111111111

    return ret;
}

inline mrs31_t mrs31_t::pentaroot() const
{
    mrs31_t x05, x06, x66, ret = *this;

    x05 = sqr_n_mul(ret, 2, ret);   // 0b101
    x06 = x05 * ret;                // 0b110
    x66 = sqr_n_mul(x06, 4, x06);   // 0b1100110
    ret = sqr_n_mul(x66, 8, x66);   // 0b110011001100110
    ret = sqr_n_mul(ret, 8, x66);   // 0b11001100110011001100110
    ret = sqr_n_mul(ret, 4, x06);   // 0b110011001100110011001100110
    ret = sqr_n_mul(ret, 4, x05);   // 0b1100110011001100110011001100101

    return ret;
}
#if defined(__CUDACC__) || defined(__HIPCC__)
# undef inline
#endif

namespace mersenne31 {
typedef mrs31_t fr_t;
}

#ifdef FEATURE_MERSENNE_31
using namespace mersenne31;
#endif

#endif /* __SPPARK_FF_MERSENNE31_HPP__ */
