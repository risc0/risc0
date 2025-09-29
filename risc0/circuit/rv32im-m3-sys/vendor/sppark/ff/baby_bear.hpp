// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#if (defined(__CUDACC__) || defined(__HIPCC__)) && \
    !defined(__SPPARK_FF_BABY_BEAR_HPP__)
#define __SPPARK_FF_BABY_BEAR_HPP__

# include "pow.hpp"
# include <cassert>

# ifdef __CUDACC__  // CUDA device-side field types
#  include "mont32_t.cuh"
# else
#  include "mont32_t.hip"
# endif
# define inline __device__ __forceinline__

using bb31_base = mont32_t<31, 0x78000001, 0x77ffffff, 0x45dddde3, 0x0ffffffe>;

struct bb31_t : public bb31_base {
    using mem_t = bb31_t;

    inline bb31_t() {}
    inline bb31_t(const bb31_base& a) : bb31_base(a) {}
    inline bb31_t(const uint32_t *p)  : bb31_base(p) {}
    // this is used in constant declaration, e.g. as bb31_t{11}
    __host__ __device__ constexpr bb31_t(int a)      : bb31_base(a) {}
    __host__ __device__ constexpr bb31_t(uint32_t a) : bb31_base(a) {}

    inline bb31_t reciprocal() const
    {
        bb31_t x11, xff, ret = *this;

        x11 = sqr_n_mul(ret, 4, ret);   // 0b10001
        ret = sqr_n_mul(x11, 1, x11);   // 0b110011
        ret = sqr_n_mul(ret, 1, x11);   // 0b1110111
        xff = sqr_n_mul(ret, 1, x11);   // 0b11111111
        ret = sqr_n_mul(ret, 8, xff);   // 0b111011111111111
        ret = sqr_n_mul(ret, 8, xff);   // 0b11101111111111111111111
        ret = sqr_n_mul(ret, 8, xff);   // 0b1110111111111111111111111111111

        return ret;
    }
    friend inline bb31_t operator/(int one, bb31_t a)
    {   assert(one == 1); return a.reciprocal();   }
    friend inline bb31_t operator/(bb31_t a, bb31_t b)
    {   return a * b.reciprocal();   }
    inline bb31_t& operator/=(const bb31_t a)
    {   *this *= a.reciprocal(); return *this;   }

    inline bb31_t heptaroot() const
    {
        bb31_t x03, x18, x1b, ret = *this;

        x03 = sqr_n_mul(ret, 1, ret);   // 0b11
        x18 = sqr_n(x03, 3);            // 0b11000
        x1b = x18*x03;                  // 0b11011
        ret = x18*x1b;                  // 0b110011
        ret = sqr_n_mul(ret, 6, x1b);   // 0b110011011011
        ret = sqr_n_mul(ret, 6, x1b);   // 0b110011011011011011
        ret = sqr_n_mul(ret, 6, x1b);   // 0b110011011011011011011011
        ret = sqr_n_mul(ret, 6, x1b);   // 0b110011011011011011011011011011
        ret = sqr_n_mul(ret, 1, *this); // 0b1100110110110110110110110110111

        return ret;
    }
};

class __align__(16) bb31_4_t {
    union { bb31_t c[4]; uint32_t u[4]; };

    static const uint32_t MOD   = 0x78000001;
    static const uint32_t M     = 0x77ffffff;
#ifdef BABY_BEAR_CANONICAL
    static const uint32_t BETA  = 0x37ffffe9;   // (11<<32)%MOD
#else                                           // such as RISC Zero
    static const uint32_t BETA  = 0x40000018;   // (-11<<32)%MOD
#endif

public:
    static const uint32_t degree = 4;
    using mem_t = bb31_4_t;

    inline bb31_t& operator[](size_t i)             { return c[i]; }
    inline const bb31_t& operator[](size_t i) const { return c[i]; }
    inline size_t len() const                       { return 4; }

    __host__ inline bb31_4_t()          {}
    __host__ inline bb31_4_t(bb31_t a)  { c[0] = a; u[1] = u[2] = u[3] = 0; }
    // this is used in constant declaration, e.g. as bb31_4_t{1, 2, 3, 4}
    __host__ inline bb31_4_t(int a)
    {   c[0] = bb31_t{a}; u[1] = u[2] = u[3] = 0;   }
    __host__ inline bb31_4_t(int d, int f, int g, int h)
    {   c[0] = bb31_t{d}; c[1] = bb31_t{f}; c[2] = bb31_t{g}; c[3] = bb31_t{h};   }

    static inline bb31_4_t csel(const bb31_4_t& a, const bb31_4_t& b, int sel_a)
    {
        bb31_4_t ret;
        for (size_t i = 0; i < 4; i++)
            ret[i] = bb31_t::csel(a[i], b[i], sel_a);
        return ret;
    }

    // Polynomial multiplication/squaring modulo x^4 - BETA
    inline bb31_4_t& sqr()
    {
        bb31_4_t ret;

# ifdef __CUDA_ARCH__
#  ifdef __GNUC__
#   define asm __asm__ __volatile__
#  else
#   define asm asm volatile
#  endif
        // +25% in comparison to multiplication by itself
        uint32_t u3x2 = u[3]<<1;
        uint32_t u1x2 = u[1]<<1;

        // ret[0] = a[0]*a[0] + BETA*(2*a[1]*a[3] + a[2]*a[2]);
        asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
            "mul.lo.u32     %lo, %4, %2;      mul.hi.u32  %hi, %4, %2;\n\t"
            "mad.lo.cc.u32  %lo, %3, %3, %lo; madc.hi.u32 %hi, %3, %3, %hi;\n\t"
            "setp.ge.u32    %p, %hi, %5;\n\t"
            "@%p sub.u32    %hi, %hi, %5;\n\t"

            "mul.lo.u32     %m, %lo, %6;\n\t"
            "mad.lo.cc.u32  %lo, %m, %5, %lo; madc.hi.u32 %hi, %m, %5, %hi;\n\t"
            //"setp.ge.u32  %p, %hi, %5;\n\t"
            //"@%p sub.u32  %hi, %hi, %5;\n\t"

            "mul.lo.u32     %lo, %hi, %7;     mul.hi.u32  %hi, %hi, %7;\n\t"
            "mad.lo.cc.u32  %lo, %1, %1, %lo; madc.hi.u32 %hi, %1, %1, %hi;\n\t"

            "mul.lo.u32     %m, %lo, %6;\n\t"
            "mad.lo.cc.u32  %lo, %m, %5, %lo; madc.hi.u32 %0, %m, %5, %hi;\n\t"
            "setp.ge.u32    %p, %0, %5;\n\t"
            "@%p sub.u32    %0, %0, %5;\n\t"
            "}" : "=r"(ret.u[0])
                : "r"(u[0]), "r"(u[1]), "r"(u[2]), "r"(u3x2),
                  "r"(MOD), "r"(M), "r"(BETA));

        // ret[1] = 2*(a[0]*a[1] + BETA*(a[2]*a[3]));
        asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
            "mul.lo.u32     %lo, %4, %3;      mul.hi.u32  %hi, %4, %3;\n\t"

            "mul.lo.u32     %m, %lo, %6;\n\t"
            "mad.lo.cc.u32  %lo, %m, %5, %lo; madc.hi.u32 %hi, %m, %5, %hi;\n\t"
            //"setp.ge.u32  %p, %hi, %5;\n\t"
            //"@%p sub.u32  %hi, %hi, %5;\n\t"

            "mul.lo.u32     %lo, %hi, %7;     mul.hi.u32  %hi, %hi, %7;\n\t"
            "mad.lo.cc.u32  %lo, %2, %1, %lo; madc.hi.u32 %hi, %2, %1, %hi;\n\t"
            "setp.ge.u32    %p, %hi, %5;\n\t"
            "@%p sub.u32    %hi, %hi, %5;\n\t"

            "mul.lo.u32     %m, %lo, %6;\n\t"
            "mad.lo.cc.u32  %lo, %m, %5, %lo; madc.hi.u32 %0, %m, %5, %hi;\n\t"
            "setp.ge.u32    %p, %0, %5;\n\t"
            "@%p sub.u32    %0, %0, %5;\n\t"
            "}" : "=r"(ret.u[1])
                : "r"(u[0]), "r"(u1x2), "r"(u[2]), "r"(u3x2),
                  "r"(MOD), "r"(M), "r"(BETA));

        // ret[2] = 2*a[0]*a[2] + a[1]*a[1] + BETA*(a[3]*a[3]);
        asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
            "mul.lo.u32     %lo, %4, %4;      mul.hi.u32  %hi, %4, %4;\n\t"

            "mul.lo.u32     %m, %lo, %6;\n\t"
            "mad.lo.cc.u32  %lo, %m, %5, %lo; madc.hi.u32 %m, %m, %5, %hi;\n\t"
            //"setp.ge.u32  %p, %m, %5;\n\t"
            //"@%p sub.u32  %m, %m, %5;\n\t"

            "mul.lo.u32     %lo, %3, %1;      mul.hi.u32  %hi, %3, %1;\n\t"
            "mad.lo.cc.u32  %lo, %2, %2, %lo; madc.hi.u32 %hi, %2, %2, %hi;\n\t"
            "mad.lo.cc.u32  %lo, %m, %7, %lo; madc.hi.u32 %hi, %m, %7, %hi;\n\t"
            "setp.ge.u32    %p, %hi, %5;\n\t"
            "@%p sub.u32    %hi, %hi, %5;\n\t"

            "mul.lo.u32     %m, %lo, %6;\n\t"
            "mad.lo.cc.u32  %lo, %m, %5, %lo; madc.hi.u32 %0, %m, %5, %hi;\n\t"
            "setp.ge.u32    %p, %0, %5;\n\t"
            "@%p sub.u32    %0, %0, %5;\n\t"
            "}" : "=r"(ret.u[2])
                : "r"(u[0]<<1), "r"(u[1]), "r"(u[2]), "r"(u[3]),
                  "r"(MOD), "r"(M), "r"(BETA));

        // ret[3] = 2*(a[0]*a[3] + a[1]*a[2]);
        asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
            "mul.lo.u32     %lo, %4, %1;      mul.hi.u32  %hi, %4, %1;\n\t"
            "mad.lo.cc.u32  %lo, %3, %2, %lo; madc.hi.u32 %hi, %3, %2, %hi;\n\t"
            "setp.ge.u32    %p, %hi, %5;\n\t"
            "@%p sub.u32    %hi, %hi, %5;\n\t"

            "mul.lo.u32     %m, %lo, %6;\n\t"
            "mad.lo.cc.u32  %lo, %m, %5, %lo; madc.hi.u32 %0, %m, %5, %hi;\n\t"
            "setp.ge.u32    %p, %0, %5;\n\t"
            "@%p sub.u32    %0, %0, %5;\n\t"
            "}" : "=r"(ret.u[3])
                : "r"(u[0]), "r"(u1x2), "r"(u[2]), "r"(u3x2),
                  "r"(MOD), "r"(M), "r"(BETA));
#  undef asm
# else
        union { uint64_t wl; uint32_t w[2]; };
        uint32_t u3x2 = u[3]<<1;
        uint32_t u1x2 = u[1]<<1;

        // ret[0] = a[0]*a[0] + BETA*(2*a[1]*a[3] + a[2]*a[2]);
        wl  = u[1] * (uint64_t)u3x2;
        wl += u[2] * (uint64_t)u[2];        final_sub(w[1]);
        wl += (w[0] * M) * (uint64_t)MOD;   //final_sub(w[1]);
        wl  = w[1] * (uint64_t)BETA;
        wl += u[0] * (uint64_t)u[0];
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[0] = final_sub(w[1]);

        // ret[1] = 2*(a[0]*a[1] + BETA*(a[2]*a[3]));
        wl  = u[2] * (uint64_t)u3x2;
        wl += (w[0] * M) * (uint64_t)MOD;   //final_sub(w[1]);
        wl  = w[1] * (uint64_t)BETA;
        wl += u[0] * (uint64_t)u1x2;        final_sub(w[1]);
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[1] = final_sub(w[1]);

        // ret[2] = 2*a[0]*a[2] + a[1]*a[1] + BETA*(a[3]*a[3]);
        wl  = u[3] * (uint64_t)u[3];
        wl += (w[0] * M) * (uint64_t)MOD;   //final_sub(w[1]);
        auto hi  = w[1];
        wl  = u[2] * (uint64_t)(u[0]<<1);
        wl += u[1] * (uint64_t)u[1];
        wl += hi * (uint64_t)BETA;          final_sub(w[1]);
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[2] = final_sub(w[1]);

        // ret[3] = 2*(a[0]*a[3] + a[1]*a[2]);
        wl  = u[0] * (uint64_t)u3x2;
        wl += u[2] * (uint64_t)u1x2;        final_sub(w[1]);
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[3] = final_sub(w[1]);
# endif

        return *this = ret;
    }

private:
    static inline uint32_t final_sub(uint32_t& u)
    {   if (u >= MOD) u -= MOD; return u;   }

    inline bb31_4_t& mul(const bb31_4_t& b)
    {
        bb31_4_t ret;

# ifdef __CUDA_ARCH__
#  ifdef __GNUC__
#   define asm __asm__ __volatile__
#  else
#   define asm asm volatile
#  endif
        // ret[0] = a[0]*b[0] + BETA*(a[1]*b[3] + a[2]*b[2] + a[3]*b[1]);
        asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
            "mul.lo.u32    %lo, %4, %6;      mul.hi.u32  %hi, %4, %6;\n\t"
            "mad.lo.cc.u32 %lo, %3, %7, %lo; madc.hi.u32 %hi, %3, %7, %hi;\n\t"
            "mad.lo.cc.u32 %lo, %2, %8, %lo; madc.hi.u32 %hi, %2, %8, %hi;\n\t"
            "setp.ge.u32 %p, %hi, %9;\n\t"
            "@%p sub.u32 %hi, %hi, %9;\n\t"

            "mul.lo.u32    %m, %lo, %10;\n\t"
            "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %hi, %m, %9, %hi;\n\t"
            //"setp.ge.u32 %p, %hi, %9;\n\t"
            //"@%p sub.u32 %hi, %hi, %9;\n\t"

            "mul.lo.u32    %lo, %hi, %11;    mul.hi.u32  %hi, %hi, %11;\n\t"
            "mad.lo.cc.u32 %lo, %1, %5, %lo; madc.hi.u32 %hi, %1, %5, %hi;\n\t"

            "mul.lo.u32    %m, %lo, %10;\n\t"
            "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %0, %m, %9, %hi;\n\t"
            "setp.ge.u32 %p, %0, %9;\n\t"
            "@%p sub.u32 %0, %0, %9;\n\t"
            "}" : "=r"(ret.u[0])
                : "r"(u[0]), "r"(u[1]), "r"(u[2]), "r"(u[3]),
                  "r"(b.u[0]), "r"(b.u[1]), "r"(b.u[2]), "r"(b.u[3]),
                  "r"(MOD), "r"(M), "r"(BETA));

        // ret[1] = a[0]*b[1] + a[1]*b[0] + BETA*(a[2]*b[3] + a[3]*b[2]);
        asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
            "mul.lo.u32    %lo, %4, %7;      mul.hi.u32  %hi, %4, %7;\n\t"
            "mad.lo.cc.u32 %lo, %3, %8, %lo; madc.hi.u32 %hi, %3, %8, %hi;\n\t"

            "mul.lo.u32    %m, %lo, %10;\n\t"
            "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %hi, %m, %9, %hi;\n\t"
            //"setp.ge.u32 %p, %hi, %9;\n\t"
            //"@%p sub.u32 %hi, %hi, %9;\n\t"

            "mul.lo.u32    %lo, %hi, %11;    mul.hi.u32  %hi, %hi, %11;\n\t"
            "mad.lo.cc.u32 %lo, %2, %5, %lo; madc.hi.u32 %hi, %2, %5, %hi;\n\t"
            "mad.lo.cc.u32 %lo, %1, %6, %lo; madc.hi.u32 %hi, %1, %6, %hi;\n\t"
            "setp.ge.u32 %p, %hi, %9;\n\t"
            "@%p sub.u32 %hi, %hi, %9;\n\t"

            "mul.lo.u32    %m, %lo, %10;\n\t"
            "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %0, %m, %9, %hi;\n\t"
            "setp.ge.u32 %p, %0, %9;\n\t"
            "@%p sub.u32 %0, %0, %9;\n\t"
            "}" : "=r"(ret.u[1])
                : "r"(u[0]), "r"(u[1]), "r"(u[2]), "r"(u[3]),
                  "r"(b.u[0]), "r"(b.u[1]), "r"(b.u[2]), "r"(b.u[3]),
                  "r"(MOD), "r"(M), "r"(BETA));

        // ret[2] = a[0]*b[2] + a[1]*b[1] + a[2]*b[0] + BETA*(a[3]*b[3]);
        asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
            "mul.lo.u32    %lo, %4, %8;      mul.hi.u32  %hi, %4, %8;\n\t"

            "mul.lo.u32    %m, %lo, %10;\n\t"
            "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %hi, %m, %9, %hi;\n\t"
            //"setp.ge.u32 %p, %hi, %9;\n\t"
            //"@%p sub.u32 %hi, %hi, %9;\n\t"

            "mul.lo.u32    %lo, %hi, %11;    mul.hi.u32  %hi, %hi, %11;\n\t"
            "mad.lo.cc.u32 %lo, %3, %5, %lo; madc.hi.u32 %hi, %3, %5, %hi;\n\t"
            "mad.lo.cc.u32 %lo, %2, %6, %lo; madc.hi.u32 %hi, %2, %6, %hi;\n\t"
            "mad.lo.cc.u32 %lo, %1, %7, %lo; madc.hi.u32 %hi, %1, %7, %hi;\n\t"
            "setp.ge.u32 %p, %hi, %9;\n\t"
            "@%p sub.u32 %hi, %hi, %9;\n\t"

            "mul.lo.u32    %m, %lo, %10;\n\t"
            "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %0, %m, %9, %hi;\n\t"
            "setp.ge.u32 %p, %0, %9;\n\t"
            "@%p sub.u32 %0, %0, %9;\n\t"
            "}" : "=r"(ret.u[2])
                : "r"(u[0]), "r"(u[1]), "r"(u[2]), "r"(u[3]),
                  "r"(b.u[0]), "r"(b.u[1]), "r"(b.u[2]), "r"(b.u[3]),
                  "r"(MOD), "r"(M), "r"(BETA));

        // ret[3] = a[0]*b[3] + a[1]*b[2] + a[2]*b[1] + a[3]*b[0];
        asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
            "mul.lo.u32    %lo, %4, %5;      mul.hi.u32  %hi, %4, %5;\n\t"
            "mad.lo.cc.u32 %lo, %3, %6, %lo; madc.hi.u32 %hi, %3, %6, %hi;\n\t"
            "mad.lo.cc.u32 %lo, %2, %7, %lo; madc.hi.u32 %hi, %2, %7, %hi;\n\t"
            "mad.lo.cc.u32 %lo, %1, %8, %lo; madc.hi.u32 %hi, %1, %8, %hi;\n\t"
            "setp.ge.u32 %p, %hi, %9;\n\t"
            "@%p sub.u32 %hi, %hi, %9;\n\t"

            "mul.lo.u32    %m, %lo, %10;\n\t"
            "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %0, %m, %9, %hi;\n\t"
            "setp.ge.u32 %p, %0, %9;\n\t"
            "@%p sub.u32 %0, %0, %9;\n\t"
            "}" : "=r"(ret.u[3])
                : "r"(u[0]), "r"(u[1]), "r"(u[2]), "r"(u[3]),
                  "r"(b.u[0]), "r"(b.u[1]), "r"(b.u[2]), "r"(b.u[3]),
                  "r"(MOD), "r"(M), "r"(BETA));
#  undef asm
# else
        union { uint64_t wl; uint32_t w[2]; };

        // ret[0] = a[0]*b[0] + BETA*(a[1]*b[3] + a[2]*b[2] + a[3]*b[1]);
        wl  = u[1] * (uint64_t)b.u[3];
        wl += u[2] * (uint64_t)b.u[2];
        wl += u[3] * (uint64_t)b.u[1];      final_sub(w[1]);
        wl += (w[0] * M) * (uint64_t)MOD;   //final_sub(w[1]);
        wl  = w[1] * (uint64_t)BETA;
        wl += u[0] * (uint64_t)b.u[0];
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[0] = final_sub(w[1]);

        // ret[1] = a[0]*b[1] + a[1]*b[0] + BETA*(a[2]*b[3] + a[3]*b[2]);
        wl  = u[2] * (uint64_t)b.u[3];
        wl += u[3] * (uint64_t)b.u[2];
        wl += (w[0] * M) * (uint64_t)MOD;   //final_sub(w[1]);
        wl  = w[1] * (uint64_t)BETA;
        wl += u[0] * (uint64_t)b.u[1];
        wl += u[1] * (uint64_t)b.u[0];      final_sub(w[1]);
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[1] = final_sub(w[1]);

        // ret[2] = a[0]*b[2] + a[1]*b[1] + a[2]*b[0] + BETA*(a[3]*b[3]);
        wl  = u[3] * (uint64_t)b.u[3];
        wl += (w[0] * M) * (uint64_t)MOD;   //final_sub(w[1]);
        wl  = w[1] * (uint64_t)BETA;
        wl += u[0] * (uint64_t)b.u[2];
        wl += u[1] * (uint64_t)b.u[1];
        wl += u[2] * (uint64_t)b.u[0];      final_sub(w[1]);
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[2] = final_sub(w[1]);

        // ret[3] = a[0]*b[3] + a[1]*b[2] + a[2]*b[1] + a[3]*b[0];
        wl  = u[0] * (uint64_t)b.u[3];
        wl += u[1] * (uint64_t)b.u[2];
        wl += u[2] * (uint64_t)b.u[1];
        wl += u[3] * (uint64_t)b.u[0];      final_sub(w[1]);
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[3] = final_sub(w[1]);
# endif

        return *this = ret;
    }

public:
# ifdef __CUDACC_RDC__
    friend __device__ __noinline__ bb31_4_t operator*(bb31_4_t a, bb31_4_t b)
    {   return a.mul(b);   }
    inline bb31_4_t& operator*=(const bb31_4_t& b)
    {   return *this = *this * b;   }

    friend __device__ __noinline__ bb31_4_t operator*(bb31_4_t a, bb31_t b)
    {
        bb31_4_t ret;

        for (size_t i = 0; i < 4; i++)
            ret[i] = a[i] * b;

        return ret;
    }
    friend inline bb31_4_t operator*(bb31_t b, const bb31_4_t& a)
    {   return a * b;   }
    inline bb31_4_t& operator*=(bb31_t b)
    {   return *this = *this * b;   }
# else
    friend inline bb31_4_t operator*(bb31_4_t a, const bb31_4_t& b)
    {   return a.mul(b);   }
    inline bb31_4_t& operator*=(const bb31_4_t& b)
    {   return mul(b);   }

    inline bb31_4_t& operator*=(bb31_t b)
    {
        for (size_t i = 0; i < 4; i++)
            c[i] *= b;

        return *this;
    }
    friend inline bb31_4_t operator*(bb31_4_t a, bb31_t b)
    {   return a *= b;   }
    friend inline bb31_4_t operator*(bb31_t b, bb31_4_t a)
    {   return a *= b;   }
# endif

    friend inline bb31_4_t operator+(const bb31_4_t& a, const bb31_4_t& b)
    {
        bb31_4_t ret;

        for (size_t i = 0; i < 4; i++)
            ret[i] = a[i] + b[i];

        return ret;
    }
    inline bb31_4_t& operator+=(const bb31_4_t& b)
    {   return *this = *this + b;   }

    friend inline bb31_4_t operator+(const bb31_4_t& a, bb31_t b)
    {
        bb31_4_t ret;

        ret[0] = a[0] + b;
        ret[1] = a[1];
        ret[2] = a[2];
        ret[3] = a[3];

        return ret;
    }
    friend inline bb31_4_t operator+(bb31_t b, const bb31_4_t& a)
    {   return a + b;   }
    inline bb31_4_t& operator+=(bb31_t b)
    {   c[0] += b; return *this;   }

    friend inline bb31_4_t operator-(const bb31_4_t& a, const bb31_4_t& b)
    {
        bb31_4_t ret;

        for (size_t i = 0; i < 4; i++)
            ret[i] = a[i] - b[i];

        return ret;
    }
    inline bb31_4_t& operator-=(const bb31_4_t& b)
    {   return *this = *this - b;   }

    friend inline bb31_4_t operator-(const bb31_4_t& a, bb31_t b)
    {
        bb31_4_t ret;

        ret[0] = a[0] - b;
        ret[1] = a[1];
        ret[2] = a[2];
        ret[3] = a[3];

        return ret;
    }
    friend inline bb31_4_t operator-(bb31_t b, const bb31_4_t& a)
    {
        bb31_4_t ret;

        ret[0] = b - a[0];
        ret[1] = -a[1];
        ret[2] = -a[2];
        ret[3] = -a[3];

        return ret;
    }
    inline bb31_4_t& operator-=(bb31_t b)
    {   c[0] -= b; return *this;   }

private:
    inline bb31_t recip_b0() const
    {
        union { uint64_t wl; uint32_t w[2]; };

        // c[0]*c[0] - beta*(c[1]*bb31_t{u[3]<<1} - c[2]*c[2]);
        wl  = u[1] * (uint64_t)(u[3]<<1);
        wl += u[2] * (uint64_t)(MOD-u[2]);
        wl += (w[0] * M) * (uint64_t)MOD;   final_sub(w[1]);
        wl  = w[1] * (uint64_t)(MOD-BETA);
        wl += u[0] * (uint64_t)u[0];
        wl += (w[0] * M) * (uint64_t)MOD;

        return bb31_t{final_sub(w[1])};
    }

    inline bb31_t recip_b2() const
    {
        union { uint64_t wl; uint32_t w[2]; };

        // c[0]*bb31_t{u[2]<<1} - c[1]*c[1] - beta*(c[3]*c[3]);
        wl  = u[3] * (uint64_t)u[3];
        wl += (w[0] * M) * (uint64_t)MOD;   final_sub(w[1]);
        wl  = w[1] * (uint64_t)(MOD-BETA);
        wl += u[1] * (uint64_t)(MOD-u[1]);
        wl += u[0] * (uint64_t)(u[2]<<1);   final_sub(w[1]);
        wl += (w[0] * M) * (uint64_t)MOD;

        return bb31_t{final_sub(w[1])};
    }

    inline bb31_4_t recip_ret(bb31_t b0, bb31_t b2) const
    {
        bb31_4_t ret;
        union { uint64_t wl; uint32_t w[2]; };

        wl  = b2[0] * (uint64_t)BETA;
        wl += (w[0] * M) * (uint64_t)MOD;   //final_sub(w[1]);

        uint32_t beta_b2 = w[1];

        // ret[0] = c[0]*b0 - c[2]*beta_b2;
        wl  = u[0] * (uint64_t)b0[0];
        wl += (MOD-u[2]) * (uint64_t)beta_b2;
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[0] = final_sub(w[1]);

        // ret[1] = c[3]*beta_b2 - c[1]b0;
        wl  = u[3] * (uint64_t)beta_b2;
        wl += (MOD-u[1]) * (uint64_t)b0[0];
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[1] = final_sub(w[1]);

        // ret[2] = c[2]*b0 - c[0]*b2;
        wl  = u[2] * (uint64_t)b0[0];
        wl += (MOD-u[0]) * (uint64_t)b2[0];
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[2] = final_sub(w[1]);

        // ret[3] = c[1]*b2 - c[3]*b0;
        wl  = u[1] * (uint64_t)b2[0];
        wl += (MOD-u[3]) * (uint64_t)b0[0];
        wl += (w[0] * M) * (uint64_t)MOD;
        ret.u[3] = final_sub(w[1]);

        return ret;
    }

public:
    inline bb31_4_t reciprocal() const
    {
        const bb31_t beta{BETA};

        bb31_t b0 = recip_b0();
        bb31_t b2 = recip_b2();

# if 0  // inefficient code generated by at least 12.5?
        bb31_t inv = 1/(b0*b0 - beta*b2*b2);
# else
        bb31_t inv = b0*b0 - beta*b2*b2;
        inv = 1/inv;
# endif

        b0 *= inv;
        b2 *= inv;

        return recip_ret(b0, b2);
    }
    friend inline bb31_4_t operator/(int one, const bb31_4_t& a)
    {   assert(one == 1); return a.reciprocal();   }
    friend inline bb31_4_t operator/(const bb31_4_t& a, const bb31_4_t& b)
    {   return a * b.reciprocal();   }
    friend inline bb31_4_t operator/(bb31_t a, const bb31_4_t& b)
    {   return b.reciprocal() * a;   }
    friend inline bb31_4_t operator/(const bb31_4_t& a, bb31_t b)
    {   return a * b.reciprocal();   }
    inline bb31_4_t& operator/=(const bb31_4_t& a)
    {   return *this *= a.reciprocal();   }
    inline bb31_4_t& operator/=(bb31_t a)
    {   return *this *= a.reciprocal();   }

# ifdef __SPPARK_FF_BATCH_INVERSION_HPP__
    template<size_t N, typename S = bb31_4_t[N]>
    friend inline void batch_inversion(bb31_4_t out[N], const S inp)
    {
        const bb31_t beta{BETA};
        bb31_t b0[N], b2[N], bx[N];

        for (size_t i = 0; i < N; i++) {
            bb31_4_t tmp = inp[i];
            b0[i] = tmp.recip_b0();
            b2[i] = tmp.recip_b2();
            bx[i] = b0[i]*b0[i] - beta*b2[i]*b2[i];
        }

        bb31_t inv[N];

        batch_inversion<bb31_t, N>(inv, bx);

        for (size_t i = N; i--;) {
            b0[i] *= inv[i];
            b2[i] *= inv[i];
            bb31_4_t tmp = inp[i];
            out[i] = tmp.recip_ret(b0[i], b2[i]);
        }
    }

    // Unlike the generic batch_inversion<T, N> bb31_4_t procedure
    // can perform the inversion in-place.
    template<size_t N>
    friend inline void batch_inversion(bb31_4_t inout[N])
    {   batch_inversion<N>(inout, inout);   }
# endif

    inline void zero()
    {   u[0] = u[1] = u[2] = u[3] = 0;   }
    static inline const bb31_4_t one()
    {   return bb31_4_t{1};   }
    inline bool is_one() const
    {   return c[0].is_one() & ((u[1] | u[2] | u[3]) == 0);   }
    inline bool is_zero() const
    {   return (u[0] | u[1] | u[2] | u[3]) == 0;   }

    friend inline bb31_4_t czero(const bb31_4_t& a, int set_z)
    {
        bb31_4_t ret;
        for (size_t i = 0; i < 4; i++)
            ret[i] = czero(a[i], set_z);
        return ret;
    }

    // raise to a variable power, variable in respect to threadIdx,
    // but mind the ^ operator's precedence!
    inline bb31_4_t& operator^=(uint32_t p)
    {   return pow_byref(*this, p);   }
    friend inline bb31_4_t operator^(bb31_4_t a, uint32_t p)
    {   return a ^= p;   }
    inline bb31_4_t operator()(uint32_t p)
    {   return *this^p;   }

    // raise to a constant power, e.g. x^7, to be unrolled at compile time
    inline bb31_4_t& operator^=(int p)
    {   return pow_byref(*this, p);   }
    friend inline bb31_4_t operator^(bb31_4_t a, int p)
    {   return a ^= p;   }
    inline bb31_4_t operator()(int p)
    {   return *this^p;   }
# undef inline

public:
    friend inline bool operator==(const bb31_4_t& a, const bb31_4_t& b)
    {   return (a.u[0]==b.u[0]) & (a.u[1]==b.u[1]) & (a.u[2]==b.u[2]) & (a.u[3]==b.u[3]);   }
    friend inline bool operator!=(const bb31_4_t& a, const bb31_4_t& b)
    {   return (a.u[0]!=b.u[0]) | (a.u[1]!=b.u[1]) | (a.u[2]!=b.u[2]) | (a.u[3]!=b.u[3]);   }

# if defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_) // non-standard
    friend std::ostream& operator<<(std::ostream& os, const bb31_4_t& a)
    {
        os << "[" << a.c[0] << ", " << a.c[1] << ", " << a.c[2] << ", " << a.c[3] << "]";
        return os;
    }
# endif
};

namespace baby_bear {
typedef bb31_t fr_t;
typedef bb31_4_t fr4_t;
}

#ifdef FEATURE_BABY_BEAR
using namespace baby_bear;
#endif

#endif
