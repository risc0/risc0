// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#if defined(__CUDA_ARCH__) && !defined(__SPPARK_FF_MONT_T_CUH__)
# define __SPPARK_FF_MONT_T_CUH__

# include <cstddef>
# include <cstdint>
# include "pow.hpp"

# define inline __device__ __forceinline__
# ifdef __GNUC__
#  define asm __asm__ __volatile__
# else
#  define asm asm volatile
# endif

//
// To instantiate declare modulus as __device__ __constant___ const and
// complement it with its factual bit-length and the corresponding 32-bit
// Motgomery factor. Bit-length has to be such that (N+31)/32 is even
// and not less than 4.
//
// Special note about M0 being declared as uint32_t& [as opposed to just
// uint32_t]. It was noted that if M0 is 0xffffffff, CUDA compiler
// generates suboptimal code for Montgomery reduction. The way to work
// around the problem is to prevent compiler from viewing it as constant.
// For this reason it's suggested to declare the parameter as following:
//
//    __device__ __constant__ /*const*/ my_M0 = <literal>;
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
    uint32_t even[n];

    static inline void mul_n(uint32_t* acc, const uint32_t* a, uint32_t bi,
                             size_t n=n)
    {
        for (size_t j = 0; j < n; j += 2)
            asm("mul.lo.u32 %0, %2, %3; mul.hi.u32 %1, %2, %3;"
                : "=r"(acc[j]), "=r"(acc[j+1])
                : "r"(a[j]), "r"(bi));
    }

    static inline void cmad_n(uint32_t* acc, const uint32_t* a, uint32_t bi,
                              size_t n=n)
    {
        asm("mad.lo.cc.u32 %0, %2, %3, %0; madc.hi.cc.u32 %1, %2, %3, %1;"
            : "+r"(acc[0]), "+r"(acc[1])
            : "r"(a[0]), "r"(bi));
        for (size_t j = 2; j < n; j += 2)
            asm("madc.lo.cc.u32 %0, %2, %3, %0; madc.hi.cc.u32 %1, %2, %3, %1;"
                : "+r"(acc[j]), "+r"(acc[j+1])
                : "r"(a[j]), "r"(bi));
        // return carry flag
    }

    static inline void cadd_n(uint32_t* acc, const uint32_t* a, size_t n=n)
    {
        asm("add.cc.u32 %0, %0, %1;" : "+r"(acc[0]) : "r"(a[0]));
        for (size_t i = 1; i < n; i++)
            asm("addc.cc.u32 %0, %0, %1;" : "+r"(acc[i]) : "r"(a[i]));
        // return carry flag
    }

    class wide_t {
    private:
        union {
            uint32_t even[2*n];
            mont_t s[2];
        };

    public:
        inline uint32_t& operator[](size_t i)               { return even[i]; }
        inline const uint32_t& operator[](size_t i) const   { return even[i]; }
        inline operator mont_t()
        {
            s[0].mul_by_1();
            return s[0] + s[1];
        }
        inline void final_sub(uint32_t carry, uint32_t* tmp)
        {   s[1].final_sub(carry, tmp);   }

        inline wide_t() {}

    private:
        static inline void mad_row(uint32_t* odd, uint32_t* even,
                                   const uint32_t* a, uint32_t bi, size_t n=n)
        {
            cmad_n(odd, a+1, bi, n-2);
            asm("madc.lo.cc.u32 %0, %2, %3, 0; madc.hi.u32 %1, %2, %3, 0;"
                : "=r"(odd[n-2]), "=r"(odd[n-1])
                : "r"(a[n-1]), "r"(bi));

            cmad_n(even, a, bi, n);
            asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));
        }

    public:
        inline wide_t(const mont_t& a, const mont_t& b)     //// |a|*|b|
        {
            size_t i = 0;
            uint32_t odd[2*n-2];

            mul_n(even, &a[0], b[0]);
            mul_n(odd,  &a[1], b[0]);
            ++i; mad_row(&even[i+1], &odd[i-1], &a[0], b[i]);

            #pragma unroll
            while (i < n-2) {
                ++i; mad_row(&odd[i],    &even[i],  &a[0], b[i]);
                ++i; mad_row(&even[i+1], &odd[i-1], &a[0], b[i]);
            }

            // merge |even| and |odd|
            cadd_n(&even[1], &odd[0], 2*n-2);
            asm("addc.u32 %0, %0, 0;" : "+r"(even[2*n-1]));
        }

    private:
        static inline void qad_row(uint32_t* odd, uint32_t* even,
                                   const uint32_t* a, uint32_t bi, size_t n)
        {
            cmad_n(odd, a, bi, n-2);
            asm("madc.lo.cc.u32 %0, %2, %3, 0; madc.hi.u32 %1, %2, %3, 0;"
                : "=r"(odd[n-2]), "=r"(odd[n-1])
                : "r"(a[n-2]), "r"(bi));

            cmad_n(even, a+1, bi, n-2);
            asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));
        }

    public:
        inline wide_t(const mont_t& a)                      //// |a|**2
        {
            size_t i = 0, j;
            uint32_t odd[2*n-2];

            // perform |a[i]|*|a[j]| for all j>i
            mul_n(even+2, &a[2], a[0], n-2);
            mul_n(odd,    &a[1], a[0], n);

            #pragma unroll
            while (i < n-4) {
                ++i; mad_row(&even[2*i+2], &odd[2*i], &a[i+1], a[i], n-i-1);
                ++i; qad_row(&odd[2*i], &even[2*i+2], &a[i+1], a[i], n-i);
            }

            asm("mul.lo.u32 %0, %2, %3; mul.hi.u32 %1, %2, %3;"
                : "=r"(even[2*n-4]), "=r"(even[2*n-3])
                : "r"(a[n-1]), "r"(a[n-3]));
            asm("mad.lo.cc.u32 %0, %2, %3, %0; madc.hi.cc.u32 %1, %2, %3, %1;"
                : "+r"(odd[2*n-6]), "+r"(odd[2*n-5])
                : "r"(a[n-2]), "r"(a[n-3]));
            asm("addc.u32 %0, %0, 0;" : "+r"(even[2*n-3]));

            asm("mul.lo.u32 %0, %2, %3; mul.hi.u32 %1, %2, %3;"
                : "=r"(odd[2*n-4]), "=r"(odd[2*n-3])
                : "r"(a[n-1]), "r"(a[n-2]));

            // merge |even[2:]| and |odd[1:]|
            cadd_n(&even[2], &odd[1], 2*n-4);
            asm("addc.u32 %0, %1, 0;" : "=r"(even[2*n-2]) : "r"(odd[2*n-3]));

            // double |even|
            even[0] = 0;
            asm("add.cc.u32 %0, %1, %1;" : "=r"(even[1]) : "r"(odd[0]));
            for (j = 2; j < 2*n-1; j++)
                asm("addc.cc.u32 %0, %0, %0;" : "+r"(even[j]));
            asm("addc.u32 %0, 0, 0;" : "=r"(even[j]));

            // accumulate "diagonal" |a[i]|*|a[i]| product
            i = 0;
            asm("mad.lo.cc.u32 %0, %2, %2, %0; madc.hi.cc.u32 %1, %2, %2, %1;"
                : "+r"(even[2*i]), "+r"(even[2*i+1])
                : "r"(a[i]));
            for (++i; i < n; i++)
                asm("madc.lo.cc.u32 %0, %2, %2, %0; madc.hi.cc.u32 %1, %2, %2, %1;"
                    : "+r"(even[2*i]), "+r"(even[2*i+1])
                    : "r"(a[i]));
        }
    };

private:
    inline operator const uint32_t*() const             { return even;    }
    inline operator uint32_t*()                         { return even;    }

public:
    inline uint32_t& operator[](size_t i)               { return even[i]; }
    inline const uint32_t& operator[](size_t i) const   { return even[i]; }
    inline constexpr size_t len() const                 { return n;       }

    inline mont_t() {}
    inline mont_t(const uint32_t *p)
    {
        for (size_t i = 0; i < n; i++)
            even[i] = p[i];
    }

    template<typename... Ts>
    constexpr mont_t(uint32_t a0, Ts... arr) : even{a0, arr...} {}

    inline void store(uint32_t *p) const
    {
        for (size_t i = 0; i < n; i++)
            p[i] = even[i];
    }

    inline mont_t& operator+=(const mont_t& b)
    {
        cadd_n(&even[0], &b[0]);
        final_subc();
        return *this;
    }
    friend inline mont_t operator+(mont_t a, const mont_t& b)
    {   return a += b;   }

    inline mont_t& operator<<=(unsigned l)
    {
        while (l--) {
            asm("add.cc.u32 %0, %0, %0;" : "+r"(even[0]));
            for (size_t i = 1; i < n; i++)
                asm("addc.cc.u32 %0, %0, %0;" : "+r"(even[i]));
            final_subc();
        }

        return *this;
    }
    friend inline mont_t operator<<(mont_t a, unsigned l)
    {   return a <<= l;   }

    inline mont_t& operator>>=(unsigned r)
    {
        size_t i;
        uint32_t tmp[n+1];

        while (r--) {
            tmp[n] = 0 - (even[0]&1);
            for (i = 0; i < n; i++)
                tmp[i] = MOD[i] & tmp[n];

            cadd_n(&tmp[0], &even[0]);
            if (N%32 == 0)
                asm("addc.u32 %0, 0, 0;" : "=r"(tmp[n]));

            for (i = 0; i < n-1; i++)
                asm("shf.r.wrap.b32 %0, %1, %2, 1;"
                    : "=r"(even[i]) : "r"(tmp[i]), "r"(tmp[i+1]));
            if (N%32 == 0)
                asm("shf.r.wrap.b32 %0, %1, %2, 1;"
                    : "=r"(even[i]) : "r"(tmp[i]), "r"(tmp[i+1]));
            else
                even[i] = tmp[i] >> 1;
        }

        return *this;
    }
    friend inline mont_t operator>>(mont_t a, unsigned r)
    {   return a >>= r;   }

    inline mont_t& operator-=(const mont_t& b)
    {
        size_t i;
        uint32_t tmp[n], borrow;

        asm("sub.cc.u32 %0, %0, %1;" : "+r"(even[0]) : "r"(b[0]));
        for (i = 1; i < n; i++)
            asm("subc.cc.u32 %0, %0, %1;" : "+r"(even[i]) : "r"(b[i]));
        asm("subc.u32 %0, 0, 0;" : "=r"(borrow));

        asm("add.cc.u32 %0, %1, %2;" : "=r"(tmp[0]) : "r"(even[0]), "r"(MOD[0]));
        for (i = 1; i < n-1; i++)
            asm("addc.cc.u32 %0, %1, %2;" : "=r"(tmp[i]) : "r"(even[i]), "r"(MOD[i]));
        asm("addc.u32 %0, %1, %2;" : "=r"(tmp[i]) : "r"(even[i]), "r"(MOD[i]));

        asm("{ .reg.pred %top; setp.ne.u32 %top, %0, 0;" :: "r"(borrow));
        for (i = 0; i < n; i++)
            asm("@%top mov.b32 %0, %1;" : "+r"(even[i]) : "r"(tmp[i]));
        asm("}");

        return *this;
    }
    friend inline mont_t operator-(mont_t a, const mont_t& b)
    {   return a -= b;   }

#if 1
    inline mont_t& cneg(bool flag)
    {
        size_t i;
        uint32_t tmp[n], is_zero = even[0];
        asm("{ .reg.pred %flag; setp.ne.u32 %flag, %0, 0;" :: "r"((int)flag));

        asm("sub.cc.u32 %0, %1, %2;" : "=r"(tmp[0]) : "r"(MOD[0]), "r"(even[0]));
        for (i = 1; i < n; i++) {
            asm("subc.cc.u32 %0, %1, %2;" : "=r"(tmp[i]) : "r"(MOD[i]), "r"(even[i]));
            asm("or.b32 %0, %0, %1;" : "+r"(is_zero) : "r"(even[i]));
        }

        asm("@%flag setp.ne.u32 %flag, %0, 0;" :: "r"(is_zero));

        for (i = 0; i < n; i++)
            asm("@%flag mov.b32 %0, %1;" : "+r"(even[i]) : "r"(tmp[i]));

        asm("}");
        return *this;
    }
    static inline mont_t cneg(mont_t a, bool flag)
    {   return a.cneg(flag);   }
#else
    static inline mont_t cneg(const mont_t& a, bool flag)
    {
        size_t i;
        uint32_t tmp[n], is_zero = a[0];
        asm("{ .reg.pred %flag; setp.ne.u32 %flag, %0, 0;" :: "r"((int)flag));

        asm("sub.cc.u32 %0, %1, %2;" : "=r"(tmp[0]) : "r"(MOD[0]), "r"(a[0]));
        for (i = 1; i < n; i++) {
            asm("subc.cc.u32 %0, %1, %2;" : "=r"(tmp[i]) : "r"(MOD[i]), "r"(a[i]));
            asm("or.b32 %0, %0, %1;" : "+r"(is_zero) : "r"(a[i]));
        }

        asm("@%flag setp.ne.u32 %flag, %0, 0;" :: "r"(is_zero));

        mont_t ret = a;
        for (i = 0; i < n; i++)
            asm("@%flag mov.b32 %0, %1;" : "+r"(ret[i]) : "r"(tmp[i]));

        asm("}");
        return ret;
    }
    inline mont_t& cneg(bool flag)
    {   return *this = cneg(*this, flag);   }
#endif
    inline mont_t operator-() const
    {   return cneg(*this, true);   }

    // make the value "positive" and return the original "sign"
    inline bool abs()
    {
        size_t i;
        uint32_t tmp[n], sign;

        asm("sub.cc.u32 %0, %1, %2;" : "=r"(tmp[0]) : "r"(MOD[0]), "r"(even[0]));
        for (i = 1; i < n; i++)
            asm("subc.cc.u32 %0, %1, %2;" : "=r"(tmp[i]) : "r"(MOD[i]), "r"(even[i]));

        sign = tmp[n-1] < even[n-1];

        asm("{ .reg.pred %flag; setp.ne.u32 %flag, %0, 0;" :: "r"(sign));
        for (i = 0; i < n; i++)
            asm("@%flag mov.b32 %0, %1;" : "+r"(even[i]) : "r"(tmp[i]));
        asm("}");

        return sign;
    }

private:
    static inline void madc_n_rshift(uint32_t* odd, const uint32_t *a, uint32_t bi)
    {
        for (size_t j = 0; j < n-2; j += 2)
            asm("madc.lo.cc.u32 %0, %2, %3, %4; madc.hi.cc.u32 %1, %2, %3, %5;"
                : "=r"(odd[j]), "=r"(odd[j+1])
                : "r"(a[j]), "r"(bi), "r"(odd[j+2]), "r"(odd[j+3]));
        asm("madc.lo.cc.u32 %0, %2, %3, 0; madc.hi.u32 %1, %2, %3, 0;"
            : "=r"(odd[n-2]), "=r"(odd[n-1])
            : "r"(a[n-2]), "r"(bi));
    }

    static inline void mad_n_redc(uint32_t *even, uint32_t* odd,
                                  const uint32_t *a, uint32_t bi, bool first=false)
    {
        if (first) {
            mul_n(odd, a+1, bi);
            mul_n(even, a,  bi);
        } else {
            asm("add.cc.u32 %0, %0, %1;" : "+r"(even[0]) : "r"(odd[1]));
            madc_n_rshift(odd, a+1, bi);
            cmad_n(even, a, bi);
            asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));
        }

        uint32_t mi = even[0] * M0;

        cmad_n(odd, MOD+1, mi);
        cmad_n(even, MOD,  mi);
        asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));
    }

public:
    friend inline mont_t operator*(const mont_t& a, const mont_t& b)
    {
        if (N%32 == 0) {
            return wide_t{a, b};
        } else {
            mont_t even, odd;

            #pragma unroll
            for (size_t i = 0; i < n; i += 2) {
                mad_n_redc(&even[0], &odd[0], &a[0], b[i], i==0);
                mad_n_redc(&odd[0], &even[0], &a[0], b[i+1]);
            }

            // merge |even| and |odd|
            cadd_n(&even[0], &odd[1], n-1);
            asm("addc.u32 %0, %0, 0;" : "+r"(even[n-1]));

            even.final_sub(0, &odd[0]);

            return even;
        }
    }
    inline mont_t& operator*=(const mont_t& a)
    {   return *this = *this * a;   }

    inline mont_t& sqr()
    {   return *this = wide_t{*this};   }

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
    {   return p == 2 ? (mont_t)wide_t{a} : a ^= p;   }
    inline mont_t operator()(int p)
    {   return *this^p;   }
    friend inline mont_t sqr(const mont_t& a)
    {   return a^2;   }

    inline void to()    { mont_t t = RR * *this; *this = t; }
    inline void to(const uint32_t a[2*n], bool host_order = true)
    {
        size_t i;

        // load the most significant half
        if (host_order) {
            for (i = 0; i < n; i++)
                even[i] = a[n + i];
        } else {
            for (i = 0; i < n; i++)
                asm("prmt.b32 %0, %1, %1, 0x0123;" : "=r"(even[i]) : "r"(a[n - 1 - i]));
        }
        to();

        mont_t lo;

        // load the least significant half
        if (host_order) {
            for (i = 0; i < n; i++)
                lo[i] = a[i];
        } else {
            for (i = 0; i < n; i++)
                asm("prmt.b32 %0, %1, %1, 0x0123;" : "=r"(lo[i]) : "r"(a[2*n - 1 - i]));
        }

        cadd_n(&even[0], &lo[0]);
        final_subc();
        to();
    }
    inline void from()  { mont_t t = *this; t.mul_by_1(); *this = t; }
    inline void from(const uint32_t a[2*n], bool host_order = true)
    {
        size_t i;

        // load the least significant half
        if (host_order) {
            for (i = 0; i < n; i++)
                even[i] = a[i];
        } else {
            for (i = 0; i < n; i++)
                asm("prmt.b32 %0, %1, 0, 0x0123;" : "=r"(even[i]) : "r"(a[2*n - 1 -i]));
        }
        mul_by_1();

        mont_t hi;

        // load the most significant half
        if (host_order) {
            for (i = 0; i < n; i++)
                hi[i] = a[n + i];
        } else {
            for (i = 0; i < n; i++)
                asm("prmt.b32 %0, %1, 0, 0x0123;" : "=r"(hi[i]) : "r"(a[n - 1 - i]));
        }

        cadd_n(&even[0], &hi[0]);
        final_subc();
        to();
    }

    static inline const mont_t& one()
    {   return *reinterpret_cast<const mont_t*>(ONE);   }

    static inline mont_t one(int or_zero)
    {
        mont_t ret;
        asm("{ .reg.pred %or_zero;");
        asm("setp.ne.s32 %or_zero, %0, 0;" : : "r"(or_zero));
        for (size_t i = 0; i < n; i++)
            asm("selp.u32 %0, 0, %1, %or_zero;" : "=r"(ret[i]) : "r"(ONE[i]));
        asm("}");
        return ret;
    }

    inline bool is_one() const
    {
#if __CUDACC_VER_MAJOR__ == 12 && __CUDACC_VER_MINOR__ > 3
        uint32_t is_zero = 0;

        for (size_t i = 0; i < n; i++)
            is_zero |= even[i] ^ ONE[i];
#else
        uint32_t is_zero = even[0] ^ ONE[0];

        for (size_t i = 1; i < n; i++)
            is_zero |= even[i] ^ ONE[i];
#endif

        return is_zero == 0;
    }

    inline bool is_zero() const
    {
        uint32_t is_zero = even[0] | even[1];

        for (size_t i = 2; i < n; i += 2)
            is_zero |= even[i] | even[i+1];

        return is_zero == 0;
    }

    inline bool is_zero(const mont_t& a) const
    {
        uint32_t is_zero = even[0] | a[0];

        for (size_t i = 1; i < n; i++)
            is_zero |= even[i] | a[i];

        return is_zero == 0;
    }

    inline void zero()
    {
        if (n%4 == 0) {
            uint4* p = (uint4*)even;
            for (size_t i=0; i<sizeof(even)/sizeof(*p); i++)
                p[i] = uint4{0, 0, 0, 0};
        } else {
            uint64_t* p = (uint64_t*)even;
            for (size_t i=0; i<sizeof(even)/sizeof(uint64_t); i++)
                p[i] = 0;
        }
    }

    friend inline mont_t czero(const mont_t& a, int set_z)
    {
        mont_t ret;
        asm("{ .reg.pred %set_z;");
        asm("setp.ne.s32 %set_z, %0, 0;" : : "r"(set_z));
        for (size_t i = 0; i < n; i++)
            asm("selp.u32 %0, 0, %1, %set_z;" : "=r"(ret[i]) : "r"(a[i]));
        asm("}");
        return ret;
    }

    static inline mont_t csel(const mont_t& a, const mont_t& b, int sel_a)
    {
        mont_t ret;
        asm("{ .reg.pred %sel_a;");
        asm("setp.ne.s32 %sel_a, %0, 0;" : : "r"(sel_a));
        for (size_t i = 0; i < n; i++)
            asm("selp.u32 %0, %1, %2, %sel_a;" : "=r"(ret[i]) : "r"(a[i]), "r"(b[i]));
        asm("}");
        return ret;
    }

private:
    static inline void mul_by_1_row(uint32_t* even, uint32_t* odd, bool first=false)
    {
        uint32_t mi;

        if (first) {
            mi = even[0] * M0;
            mul_n(odd, MOD+1, mi);
            cmad_n(even, MOD,  mi);
            asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));
        } else {
            asm("add.cc.u32 %0, %0, %1;" : "+r"(even[0]) : "r"(odd[1]));
# if 1      // do we trust the compiler to *not* touch the carry flag here?
            mi = even[0] * M0;
# else
            asm("mul.lo.u32 %0, %1, %2;" : "=r"(mi) : "r"(even[0]), "r"(M0));
# endif
            madc_n_rshift(odd, MOD+1, mi);
            cmad_n(even, MOD, mi);
            asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));
        }
    }
    inline void mul_by_1()
    {
        mont_t odd;

        #pragma unroll
        for (size_t i = 0; i < n; i += 2) {
            mul_by_1_row(&even[0], &odd[0], i==0);
            mul_by_1_row(&odd[0], &even[0]);
        }

        cadd_n(&even[0], &odd[1], n-1);
        asm("addc.u32 %0, %0, 0;" : "+r"(even[n-1]));
    }

    inline void final_sub(uint32_t carry, uint32_t* tmp)
    {
        size_t i;
        asm("{ .reg.pred %top;");

        asm("sub.cc.u32 %0, %1, %2;" : "=r"(tmp[0]) : "r"(even[0]), "r"(MOD[0]));
        for (i = 1; i < n; i++)
            asm("subc.cc.u32 %0, %1, %2;" : "=r"(tmp[i]) : "r"(even[i]), "r"(MOD[i]));
        if (N%32 == 0)
            asm("subc.u32 %0, %0, 0; setp.eq.u32 %top, %0, 0;" : "+r"(carry));
        else
            asm("subc.u32 %0, 0, 0; setp.eq.u32 %top, %0, 0;" : "=r"(carry));

        for (i = 0; i < n; i++)
            asm("@%top mov.b32 %0, %1;" : "+r"(even[i]) : "r"(tmp[i]));

        asm("}");
    }

    inline void final_subc()
    {
        uint32_t carry, tmp[n];

        asm("addc.u32 %0, 0, 0;" : "=r"(carry));

        asm("sub.cc.u32 %0, %1, %2;" : "=r"(tmp[0]) : "r"(even[0]), "r"(MOD[0]));
        for (size_t i = 1; i < n; i++)
            asm("subc.cc.u32 %0, %1, %2;" : "=r"(tmp[i]) : "r"(even[i]), "r"(MOD[i]));
        asm("subc.u32 %0, %0, 0;" : "+r"(carry));

        asm("{ .reg.pred %top;");
        asm("setp.eq.u32 %top, %0, 0;" :: "r"(carry));
        for (size_t i = 0; i < n; i++)
            asm("@%top mov.b32 %0, %1;" : "+r"(even[i]) : "r"(tmp[i]));
        asm("}");
    }

    static inline void dot_n_redc(uint32_t *even, uint32_t *odd,
                                  const uint32_t *a, uint32_t bi,
                                  const uint32_t *c, uint32_t di, bool first = false)
    {
        if (first) {
            mul_n(odd, a+1, bi);
            cmad_n(odd, c+1, di);
            mul_n(even, a, bi);
            cmad_n(even, c, di);
            asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));
        } else {
            asm("add.cc.u32 %0, %0, %1;" : "+r"(even[0]) : "r"(odd[1]));
            madc_n_rshift(odd, a+1, bi);
            cmad_n(odd, c+1, di);
            cmad_n(even, a, bi);
            asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));
            cmad_n(even, c, di);
            asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));
        }

        uint32_t mi = even[0] * M0;

        cmad_n(odd, MOD+1, mi);
        cmad_n(even, MOD, mi);
        asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));
    }

public:
    static inline mont_t dot_product(const mont_t& a, const mont_t& b,
                                     const mont_t& c, const mont_t& d)
    {
        if (N%32 == 0 || N%32 > 30) {
            return a*b + c*d;   // can be improved too...
        } else {
            mont_t even, odd;

            #pragma unroll
            for (size_t i = 0; i < n; i += 2) {
                dot_n_redc(&even[0], &odd[0], &a[0], b[i], &c[0], d[i], i==0);
                dot_n_redc(&odd[0], &even[0], &a[0], b[i+1], &c[0], d[i+1]);
            }

            // merge |even| and |odd|
            cadd_n(&even[0], &odd[1], n-1);
            asm("addc.u32 %0, %0, 0;" : "+r"(even[n-1]));

            even.final_sub(0, &odd[0]);

            return even;
        }
    }

    static inline mont_t dot_product(const mont_t a[], const mont_t* b_ptr,
                                     size_t len, size_t stride_b = 1)
    {
        size_t i;
        mont_t tmp;
        wide_t even;
        uint32_t odd[2*n-2], carry;

        for (i = 0; i < 2*n-2; i++)
            even[i] = odd[i] = 0;
        even[i] = even[i+1] = 0;

        #pragma unroll
        for (size_t j = 0; j < len; j++, b_ptr += stride_b) {
            mont_t b = *b_ptr;
            tmp = a[j];
            carry = 0;

            #pragma unroll
            for (i = 0; i < n; i += 2) {
                uint32_t bi;

                cmad_n(&even[i], &tmp[0], bi = b[i]);
                asm("addc.u32 %0, %0, 0;" : "+r"(carry));
                asm("add.cc.u32 %0, %0, %1; addc.u32 %1, 0, 0;"
                    : "+r"(odd[n+i-1]), "+r"(carry));
                cmad_n(&odd[i], &tmp[1], bi);
                asm("addc.u32 %0, %0, 0;" : "+r"(carry));

                cmad_n(&odd[i], &tmp[0], bi = b[i+1]);
                asm("addc.u32 %0, %0, 0;" : "+r"(carry));
                asm("add.cc.u32 %0, %0, %1; addc.u32 %1, 0, 0;"
                    : "+r"(even[n+i+1]), "+r"(carry));
                cmad_n(&even[i+2], &tmp[1], bi);
                asm("addc.u32 %0, %0, 0;" : "+r"(carry));
            }

            // reduce |even| modulo |MOD<<(n*32)|
            even.final_sub(carry, &tmp[0]);
        }

        // merge |even| and |odd|
        cadd_n(&even[1], &odd[0], 2*n-2);
        asm("addc.cc.u32 %0, %0, 0; addc.u32 %1, 0, 0;"
            : "+r"(even[2*n-1]), "=r"(carry));

        // reduce |even| modulo |MOD<<(n*32)|
        even.final_sub(carry, &tmp[0]);

        return even; // implicit cast to mont_t performs the reduction
    }

    inline mont_t shfl(uint32_t idx, uint32_t mask = 0xffffffff) const
    {
        mont_t ret;

        for (size_t i = 0; i < n; i++)
            ret[i] = __shfl_sync(mask, even[i], idx);

        return ret;
    }

protected:
    template<typename vec_t>
    static inline vec_t shfl_xor(const vec_t& a, uint32_t idx = 1)
    {
        vec_t ret;
        for (size_t i = 0; i < sizeof(vec_t)/sizeof(uint32_t); i++)
            ret[i] = __shfl_xor_sync(0xffffffff, a[i], idx);
        return ret;
    }

private:
    // Euclidean inversion based on https://eprint.iacr.org/2020/972
    // and <blst>/src/no_asm.h.

    struct approx_t  { uint32_t lo, hi; };
    struct factorx_t { uint32_t f0, g0; };

    static inline uint32_t lshift_2(uint32_t hi, uint32_t lo, uint32_t i)
    {
        uint32_t ret;
        asm("shf.l.clamp.b32 %0, %1, %2, %3;" : "=r"(ret) : "r"(lo), "r"(hi), "r"(i));
        return ret;
    }

    static inline void ab_approximation_n(approx_t& a_, const mont_t& a,
                                          approx_t& b_, const mont_t& b)
    {
        size_t i = n-1;

        uint32_t a_hi = a[i], a_lo = a[i-1];
        uint32_t b_hi = b[i], b_lo = b[i-1];

        #pragma unroll
        for (i--; --i;) {
            asm("{ .reg.pred %flag;");
            asm("setp.eq.u32 %flag, %0, 0;" : : "r"(a_hi | b_hi));
            asm("@%flag mov.b32 %0, %1;" : "+r"(a_hi) : "r"(a_lo));
            asm("@%flag mov.b32 %0, %1;" : "+r"(b_hi) : "r"(b_lo));
            asm("@%flag mov.b32 %0, %1;" : "+r"(a_lo) : "r"(a[i]));
            asm("@%flag mov.b32 %0, %1;" : "+r"(b_lo) : "r"(b[i]));
            asm("}");
        }
        uint32_t off = __clz(a_hi | b_hi);
        /* |off| can be LIMB_T_BITS if all a[2..]|b[2..] were zeros */
        off -= off==32 ? (a_lo | b_lo)>>31 : 1;

        a_ = approx_t{a[0], off<=32 ? lshift_2(a_hi, a_lo, off) : a_hi>>1 };
        b_ = approx_t{b[0], off<=32 ? lshift_2(b_hi, b_lo, off) : b_hi>>1 };
    }

    static inline void cswap(uint32_t& a, uint32_t& b, uint32_t mask)
    {
        uint32_t xorm = (a ^ b) & mask;
        a ^= xorm;
        b ^= xorm;
    }

    static inline factorx_t inner_loop_x(approx_t a, approx_t b)
    {
        const uint32_t tid = threadIdx.x&1;
        const uint32_t odd = 0 - tid;

        // even thread calculates |f0|,|f1|, odd - |g0|,|g1|
        uint32_t fg0 = tid^1, fg1 = tid;

        // in the odd thread |a| and |b| are in reverse order, compensate...
        cswap(a.lo, b.lo, odd);
        cswap(a.hi, b.hi, odd);

        #pragma unroll 2
        for (uint32_t n = 32-2; n--;) {
            asm("{ .reg.pred %odd, %brw;");
            approx_t a_b;

            asm("setp.ne.u32 %odd, %0, 0;" :: "r"(a.lo&1));

            /* a_ -= b_ if a_ is odd */
            asm("selp.b32          %0, %1, 0, !%odd;"
                "@%odd sub.cc.u32  %0, %1, %2;" : "=r"(a_b.lo) : "r"(a.lo), "r"(b.lo));
            asm("selp.b32          %0, %1, 0, !%odd;"
                "@%odd subc.cc.u32 %0, %1, %2;" : "=r"(a_b.hi) : "r"(a.hi), "r"(b.hi));
            asm("setp.gt.and.u32   %brw, %0, %1, %odd;" :: "r"(a_b.hi), "r"(a.hi));

            /* negate a_-b_ if it borrowed */
            asm("@%brw sub.cc.u32  %0, %1, %2;" : "+r"(a_b.lo) : "r"(b.lo), "r"(a.lo));
            asm("@%brw subc.cc.u32 %0, %1, %2;" : "+r"(a_b.hi) : "r"(b.hi), "r"(a.hi));

            /* b_=a_ if a_-b_ borrowed */
            asm("@%brw mov.b32 %0, %1;" : "+r"(b.lo) : "r"(a.lo));
            asm("@%brw mov.b32 %0, %1;" : "+r"(b.hi) : "r"(a.hi));

            /* exchange f0 and f1 if a_-b_ borrowed */
            uint32_t fgx;
            asm("selp.u32 %0, %1, %2, %brw;" : "=r"(fgx) : "r"(fg0), "r"(fg1));
            asm("selp.u32 %0, %1, %0, %brw;" : "+r"(fg0) : "r"(fg1));

            /* subtract if a_ was odd */
            asm("@%odd sub.u32 %0, %0, %1;" : "+r"(fg0) : "r"(fgx));

            fg1 = fgx << 1;
            asm("shf.r.wrap.b32 %0, %1, %2, 1;" : "=r"(a.lo) : "r"(a_b.lo), "r"(a_b.hi));
            a.hi = a_b.hi >> 1;

            asm("}");
        }

        // even thread needs |f0|,|g0|, odd - |g1|,|f1|, in this order
        cswap(fg0, fg1, odd);

        fg1 = __shfl_xor_sync(0xffffffff, fg1, 1);

        return factorx_t{fg0, fg1};
    }

    static inline factorx_t inner_loop_x(uint32_t a, uint32_t b, uint32_t n)
    {
        const uint32_t tid = threadIdx.x&1;
        const uint32_t odd = 0 - tid;

        // even thread calculates |f0|,|f1|, odd - |g0|,|g1|
        uint32_t fg0 = tid^1, fg1 = tid;

        // in the odd thread |a| and |b| are in reverse order, compensate...
        cswap(a, b, odd);

        #pragma unroll 1
        while (n--) {
            asm("{ .reg.pred %odd, %brw;");
            uint32_t a_b = a;

            asm("setp.ne.u32 %odd, %0, 0;" :: "r"(a&1));

            /* a_ -= b_ if a_ is odd */
            asm("setp.lt.and.u32  %brw, %0, %1, %odd;" :: "r"(a), "r"(b));
            asm("@%odd sub.u32 %0, %1, %2;" : "+r"(a_b) : "r"(a), "r"(b));

            /* negate a_-b_ if it borrowed */
            asm("@%brw sub.u32 %0, %1, %2;" : "+r"(a_b) : "r"(b), "r"(a));

            /* b_=a_ if a_-b_ borrowed */
            asm("@%brw mov.b32 %0, %1;" : "+r"(b) : "r"(a));

            /* exchange f0 and f1 if a_-b_ borrowed */
            uint32_t fgx;
            asm("selp.u32 %0, %1, %2, %brw;" : "=r"(fgx) : "r"(fg0), "r"(fg1));
            asm("selp.u32 %0, %1, %0, %brw;" : "+r"(fg0) : "r"(fg1));

            /* subtract if a_ was odd */
            asm("@%odd sub.u32 %0, %0, %1;" : "+r"(fg0) : "r"(fgx));

            fg1 = fgx << 1;
            a = a_b >> 1;

            asm("}");
        }

        // we care only about |f1| and |g1| in this subroutine
        fg0 = __shfl_xor_sync(0xffffffff, fg1, 1);

        return factorx_t{fg1, fg0};
    }

    template<typename vec_t>
    static inline uint32_t cneg_v(vec_t& ret, const vec_t& a, uint32_t neg)
    {
        const size_t n = sizeof(vec_t)/sizeof(uint32_t);

        asm("xor.b32 %0, %1, %2;"    : "=r"(ret[0]) : "r"(a[0]), "r"(neg));
        asm("add.cc.u32 %0, %0, %1;" : "+r"(ret[0]) : "r"(neg&1));
        for (size_t i=1; i<n; i++)
            asm("xor.b32 %0, %1, %2; addc.cc.u32 %0, %0, 0;"
                : "=r"(ret[i]) : "r"(a[i]), "r"(neg));

        uint32_t sign;
        asm("shr.s32 %0, %1, 31;" : "=r"(sign) : "r"(ret[n-1]));
        return sign;
    }

    static inline void smul_n_shift_x(mont_t& a, uint32_t& f_,
                                      mont_t& b, uint32_t& g_)
    {
        mont_t even, odd;
        uint32_t neg;
        size_t i;

        /* |a|*|f_| */
        asm("shr.s32 %0, %1, 31;" : "=r"(neg) : "r"(f_));
        auto f = (f_ ^ neg) - neg;  /* ensure |f| is positive */
        (void)cneg_v(a, a, neg);
        mul_n(&even[0], &a[0], f);
        mul_n(&odd[0],  &a[1], f);
        odd[n-1] -= f & neg;

        /* |b|*|g_| */
        asm("shr.s32 %0, %1, 31;" : "=r"(neg) : "r"(g_));
        auto g = (g_ ^ neg) - neg;  /* ensure |g| is positive */
        (void)cneg_v(b, b, neg);
        cmad_n(&even[0], &b[0], g);
        asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));
        cmad_n(&odd[0],  &b[1], g);
        odd[n-1] -= g & neg;

        /* (|a|*|f_| + |b|*|g_|) >> k */
        cadd_n(&even[1], &odd[0], n-1);
        asm("addc.u32 %0, %0, 0;" : "+r"(odd[n-1]));

        for (i=0; i<n-1; i++)
            asm("shf.r.wrap.b32 %0, %0, %1, 32-2;" : "+r"(even[i]) : "r"(even[i+1]));
        asm("shf.r.wrap.b32 %0, %0, %1, 32-2;" : "+r"(even[i]) : "r"(odd[i]));

        /* ensure result is non-negative, fix up |f_| and |g_| accordingly */
        asm("shr.s32 %0, %1, 31;" : "=r"(neg) : "r"(odd[i]));
        f_ = (f_ ^ neg) - neg;
        g_ = (g_ ^ neg) - neg;
        (void)cneg_v(a, even, neg);
    }

    static inline uint32_t smul_2x(wide_t& u, uint32_t f,
                                   wide_t& v, uint32_t g)
    {
        wide_t even, odd;
        uint32_t neg;

        /* |u|*|f_| */
        asm("shr.s32 %0, %1, 31;" : "=r"(neg) : "r"(f));
        f = (f ^ neg) - neg;        /* ensure |f| is positive */
        neg = cneg_v(u, u, neg);
        mul_n(&even[0], &u[0], f, 2*n);
        mul_n(&odd[0],  &u[1], f, 2*n);
        odd[2*n-1] -= f & neg;

        /* |v|*|g_| */
        asm("shr.s32 %0, %1, 31;" : "=r"(neg) : "r"(g));
        g = (g ^ neg) - neg;        /* ensure |g| is positive */
        neg = cneg_v(v, v, neg);
        cmad_n(&even[0], &v[0], g, 2*n);
        asm("addc.u32 %0, %0, 0;" : "+r"(odd[2*n-1]));
        cmad_n(&odd[0],  &v[1], g, 2*n);
        odd[2*n-1] -= g & neg;

        /* |u|*|f_| + |v|*|g_| */
        u[0] = even[0];
        asm("add.cc.u32 %0, %1, %2;" : "=r"(u[1]) : "r"(even[1]), "r"(odd[0]));
        for (size_t i=2; i<2*n; i++)
            asm("addc.cc.u32 %0, %1, %2;" : "=r"(u[i]) : "r"(even[i]), "r"(odd[i-1]));
        asm("addc.u32 %0, %0, 0;" : "+r"(odd[2*n-1]));

        return odd[2*n-1];
    }

protected:
    /*
     * Even thread holds |a| and |u|, while odd one - |b| and |v|. They need
     * to exchange the values, but then perform the multiplications in
     * parallel. The improvement [for 38x-bit moduli] is >20% and ~5.5KB
     * code size reduction in comparison to a single-threaded version.
     */
    static inline mont_t ct_inverse_mod_x(const mont_t& inp)
    {
        if (N%32 != 0 && MOD == MODx) asm("trap;");

        const uint32_t tid = threadIdx.x&1;
        const uint32_t nbits = 2*n*32;

        mont_t a_b = csel(MOD, inp, tid);
        wide_t u_v, v_u;

        u_v[0] = tid^1;
        v_u[0] = tid;
        for (size_t i=1; i<2*n; i++)
            u_v[i] = v_u[i] = 0;

        #pragma unroll 1
        for (uint32_t i=0; i<nbits/(32-2); i++) {
            mont_t b_a = shfl_xor(a_b);
            approx_t a_, b_;
            ab_approximation_n(a_, a_b, b_, b_a);
            auto fg = inner_loop_x(a_, b_);
            smul_n_shift_x(a_b, fg.f0, b_a, fg.g0);
            (void)smul_2x(u_v, fg.f0, v_u, fg.g0);
            v_u = shfl_xor(u_v);
        }

        // now both even and odd threads compute the same |ret| value
        uint32_t b_a = __shfl_xor_sync(0xffffffff, a_b[0], 1);
        auto fg = inner_loop_x(a_b[0], b_a, nbits%(32-2));
        auto top = smul_2x(u_v, fg.f0, v_u, fg.g0);

        asm("{ .reg.pred %flag;");  /* top is 1, 0 or -1 */
        asm("setp.lt.s32 %flag, %0, 0;" :: "r"(top));
        asm("@%flag add.cc.u32 %0, %0, %1;" : "+r"(u_v[n]) : "r"(MODx[0]));
        for (size_t i=1; i<n; i++)
            asm("@%flag addc.cc.u32 %0, %0, %1;" : "+r"(u_v[n+i]) : "r"(MODx[i]));
        asm("@%flag addc.cc.u32 %0, %0, 0;" : "+r"(top));
        asm("}");

        auto sign = 0 - top;        /* top is 1, 0 or -1 */
        top |= sign;
        for (size_t i=0; i<n; i++)
            a_b[i] = MODx[i] & top;
        asm("shr.s32 %0, %0, 31;" : "+r"(sign));
        (void)cneg_v(a_b, a_b, sign);
        cadd_n(&u_v[n], &a_b[0]);

        mont_t ret = u_v;
        ret.to();
        return ret;
    }

public:
    inline mont_t reciprocal() const
    {
        bool a_zero = is_zero();
        mont_t a = csel(ONE, even, a_zero);
        mont_t b = shfl_xor(a);
        a *= b;                     // a*b
        a = ct_inverse_mod_x(a);    // 1/(a*b)
        a *= b;                     // b/(a*b) == 1/a
        return czero(a, a_zero);
    }
    friend inline mont_t operator/(int one, const mont_t& a)
    {   if (one != 1) asm("trap;"); return a.reciprocal();   }
    friend inline mont_t operator/(const mont_t& a, const mont_t& b)
    {   return a * b.reciprocal();   }
    inline mont_t& operator/=(const mont_t& a)
    {   return *this *= a.reciprocal();   }

    inline void shfl_bfly(uint32_t laneMask)
    {
        #pragma unroll
        for (size_t i=0; i<n; i++)
            even[i] = __shfl_xor_sync(0xFFFFFFFF, even[i], laneMask);
    }
};

# undef inline
# undef asm
#endif
