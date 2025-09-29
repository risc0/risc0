// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_EC_XYZZ_T_HPP__
#define __SPPARK_EC_XYZZ_T_HPP__

#ifndef __CUDACC__
# undef  __host__
# define __host__
# undef  __device__
# define __device__
# undef  __noinline__
# define __noinline__
#else
# pragma nv_diag_suppress 284   // NULL reference is not allowed
#endif

template<class field_t, class field_h = typename field_t::mem_t,
         const field_h* a4 = nullptr>
class xyzz_t {
    field_t X, Y, ZZZ, ZZ;

public:
    static const unsigned int degree = field_t::degree;

#ifdef __CUDACC__
    class mem_t { friend class xyzz_t;
        field_h X, Y, ZZZ, ZZ;

    public:
        inline __device__ operator xyzz_t() const
        {
            xyzz_t p;
            p.X   = X;
            p.Y   = Y;
            p.ZZZ = ZZZ;
            p.ZZ  = ZZ;
            return p;
        }
        inline __device__ mem_t& operator=(const xyzz_t& p)
        {
            X   = p.X;
            Y   = p.Y;
            ZZZ = p.ZZZ;
            ZZ  = p.ZZ;
            return *this;
        }
        inline __device__ void inf() { ZZZ.zero(); ZZ.zero(); }
    };

    inline __device__ xyzz_t& operator=(const mem_t& p)
    {
        X   = p.X;
        Y   = p.Y;
        ZZZ = p.ZZZ;
        ZZ  = p.ZZ;
        return *this;
    }
#else
    using mem_t = xyzz_t;
#endif

    class affine_t { friend class xyzz_t;
        field_t X, Y;

    public:
        affine_t(const field_t& x, const field_t& y) : X(x), Y(y) {}
        inline __host__ __device__ affine_t() {}

#ifdef __CUDA_ARCH__
        inline __device__ bool is_inf() const
        {   return (bool)(X.is_zero(Y));   }
#else
        inline __host__   bool is_inf() const
        {   return (bool)((int)X.is_zero() & (int)Y.is_zero());   }
#endif

        inline __host__ affine_t& operator=(const xyzz_t& a)
        {
            Y = 1/a.ZZZ;
            X = Y * a.ZZ;   // 1/Z
            X = X^2;        // 1/Z^2
            X *= a.X;       // X/Z^2
            Y *= a.Y;       // Y/Z^3
            return *this;
        }
        inline __host__ affine_t(const xyzz_t& a)  { *this = a; }

#ifdef __SPPARK_EC_JACOBIAN_T_HPP__
        inline operator jacobian_t<field_t>() const
        {   return jacobian_t<field_t>{ X, Y, field_t::one(is_inf()) };   }
#endif

        inline __host__ __device__ operator xyzz_t() const
        {
            xyzz_t p;
            p.X = X;
            p.Y = Y;
            p.ZZZ = p.ZZ = field_t::one(is_inf());
            return p;
        }

#ifdef __CUDACC__
        class mem_t {
            field_h X, Y;

        public:
            inline __device__ operator affine_t() const
            {
                affine_t p;
                p.X = X;
                p.Y = Y;
                return p;
            }
        };
#else
        using mem_t = affine_t;
#endif
    };

    class affine_inf_t {
        field_t X, Y;
        bool inf;

        inline __host__ __device__ bool is_inf() const
        {   return inf;   }

    public:
        inline __host__ __device__ operator affine_t() const
        {
            bool inf = is_inf();
            affine_t p;
            p.X = czero(X, inf);
            p.Y = czero(Y, inf);
            return p;
        }

#ifdef __CUDACC__
        class mem_t {
            field_h X, Y;
            int inf[sizeof(field_t)%16 ? 2 : 4];

            inline __device__ bool is_inf() const
            {   return inf[0]&1 != 0;   }

        public:
            inline __device__ operator affine_t() const
            {
                bool inf = is_inf();
                affine_t p;
                p.X = czero((field_t)X, inf);
                p.Y = czero((field_t)Y, inf);
                return p;
            }

            inline __device__ operator affine_inf_t() const
            {
                bool inf = is_inf();
                affine_inf_t p;
                p.X = czero((field_t)X, inf);
                p.Y = czero((field_t)Y, inf);
                p.inf = inf;
                return p;
            }
        };
#else
        using mem_t = affine_inf_t;
#endif
    };

    template<class affine_t>
    inline __host__ __device__ xyzz_t& operator=(const affine_t& a)
    {
        X = a.X;
        Y = a.Y;
        ZZZ = ZZ = field_t::one(a.is_inf());
        return *this;
    }

    inline __host__ operator affine_t() const      { return affine_t(*this); }

#ifdef __SPPARK_EC_JACOBIAN_T_HPP__
    inline operator jacobian_t<field_t>() const
    {   return jacobian_t<field_t>{ X*ZZ, Y*ZZZ, ZZ };   }
#endif

#ifdef __CUDA_ARCH__
    inline __device__ bool is_inf() const
    {   return (bool)(ZZZ.is_zero(ZZ));   }
#else
    inline __host__   bool is_inf() const
    {   return (bool)((int)ZZZ.is_zero() & (int)ZZ.is_zero());   }
#endif
    inline __host__ __device__ void inf()          { ZZZ.zero(); ZZ.zero(); }
    inline __host__ __device__ void cneg(bool neg) { ZZZ.cneg(neg); }

#ifdef __CUDA_ARCH__
    static inline __device__ void prefetch(const xyzz_t* p_)
    {
        const unsigned char* p = (const unsigned char*)p_;
        for (size_t i = 0; i < sizeof(*p_); i += 128)
            asm("prefetch.global.L2 [%0];" :: "l"(p+i));
    }
#endif

    /*
     * http://hyperelliptic.org/EFD/g1p/auto-shortw-xyzz.html#addition-add-2008-s
     * http://hyperelliptic.org/EFD/g1p/auto-shortw-xyzz.html#doubling-dbl-2008-s-1
     * with twist to handle either input at infinity. Addition costs 12M+2S,
     * while conditional doubling - 4M+6M+3S.
     */
    __host__ __device__ void add(const xyzz_t& p2)
    {
        if (p2.is_inf()) {
            return;
        } else if (is_inf()) {
            *this = p2;
            return;
        }

#ifdef __CUDA_ARCH__
        xyzz_t p31 = *this;
#else
        xyzz_t& p31 = *this;
#endif
        field_t U, S, P, R;

        U = p31.X * p2.ZZ;          /* U1 = X1*ZZ2 */
        S = p31.Y * p2.ZZZ;         /* S1 = Y1*ZZZ2 */
        P = p2.X * p31.ZZ;          /* U2 = X2*ZZ1 */
        R = p2.Y * p31.ZZZ;         /* S2 = Y2*ZZZ1 */
        P -= U;                     /* P = U2-U1 */
        R -= S;                     /* R = S2-S1 */

        if (!P.is_zero()) {         /* X1!=X2 */
            field_t PP;             /* add |p1| and |p2| */

            PP = P^2;               /* PP = P^2 */
#define PPP P
            PPP = P * PP;           /* PPP = P*PP */
            p31.ZZ *= PP;           /* ZZ3 = ZZ1*ZZ2*PP */
            p31.ZZZ *= PPP;         /* ZZZ3 = ZZZ1*ZZZ2*PPP */
#define Q PP
            Q = U * PP;             /* Q = U1*PP */
            p31.X = R^2;            /* R^2 */
            p31.X -= PPP;           /* R^2-PPP */
            p31.X -= Q;
            p31.X -= Q;             /* X3 = R^2-PPP-2*Q */
            Q -= p31.X;
            Q *= R;                 /* R*(Q-X3) */
            p31.Y = S * PPP;        /* S1*PPP */
            p31.Y = Q - p31.Y;      /* Y3 = R*(Q-X3)-S1*PPP */
            p31.ZZ *= p2.ZZ;        /* ZZ1*ZZ2 */
            p31.ZZZ *= p2.ZZZ;      /* ZZZ1*ZZZ2 */
#undef PPP
#undef Q
        } else if (R.is_zero()) {   /* X1==X2 && Y1==Y2 */
            field_t M;              /* double |p1| */

            U = p31.Y + p31.Y;      /* U = 2*Y1 */
#define V P
#define W R
            V = U^2;                /* V = U^2 */
            W = U * V;              /* W = U*V */
            S = p31.X * V;          /* S = X1*V */
            M = p31.X^2;
            M = M + M + M;          /* M = 3*X1^2[+a*ZZ1^2] */
            if (a4 != nullptr) {
#ifdef __CUDA_ARCH__
                U = *a4;
                U *= p31.ZZ^2;
#else
                U = p31.ZZ^2;
                U *= *a4;
#endif
                M += U;
            }
            p31.X = M^2;
            p31.X -= S;
            p31.X -= S;             /* X3 = M^2-2*S */
            p31.Y *= W;             /* W*Y1 */
            S -= p31.X;
            S *= M;                 /* M*(S-X3) */
            p31.Y = S - p31.Y;      /* Y3 = M*(S-X3)-W*Y1 */
            p31.ZZ *= V;            /* ZZ3 = V*ZZ1 */
            p31.ZZZ *= W;           /* ZZZ3 = W*ZZZ1 */
#undef V
#undef W
        } else {                    /* X1==X2 && Y1==-Y2 */\
            p31.inf();              /* set |p3| to infinity */\
        }
#ifdef __CUDA_ARCH__
        *this = p31;
#endif
    }

#ifdef __CUDA_ARCH__
    __device__ void uadd(const xyzz_t& p2)
    {
        xyzz_t p31 = *this;

        if (p2.is_inf()) {
            return;
        } else if (p31.is_inf()) {
            *this = p2;
            return;
        }

        field_t A, B, U, S, P, R, PP;
        int pc = -1;
        bool done = false, dbl = false, inf = false;

        A = p31.Y;
        B = p2.ZZZ;
        #pragma unroll 1
        do {
            A = A * B;
            switch (++pc) {
            case 0:
                S = A;                  /* S1 = Y1*ZZZ2 */
                A = p2.Y;
                B = p31.ZZZ;
                break;
            case 1:                     /* S2 = Y2*ZZZ1 */
                R = A - S;              /* R = S2-S1 */
                A = p31.X;
                B = p2.ZZ;
                break;
            case 2:
                U = A;                  /* U1 = X1*ZZ2 */
                A = p2.X;
                B = p31.ZZ;
                break;
            case 3:                     /* U2 = X2*ZZ1 */
                A = A - U;              /* P = U2-U1 */
                inf = A.is_zero();      /* X1==X2, not add |p1| and |p2| */
                dbl = R.is_zero() & inf;
                if (dbl) {              /* X1==X2 && Y1==Y2, double |p2| */
                    if (a4 != nullptr) {
                        A = p2.ZZ;
                        pc = 16;
                    } else {
                        A = p2.Y<<1;    /* U = 2*Y1 */
                    }
                    inf = false;        /* don't set |p3| to infinity */
                }
                B = A;
                break;
            case 4:
                PP = A;                 /* PP = P^2 */
                break;
            case 5:
#define PPP P
                PPP = A;                /* PPP = P*PP */
                B = field_t::csel(field_t::one(), p31.ZZZ, dbl);
                break;
            case 6:                     /* ZZZ1*PPP */
                B = czero(p2.ZZZ, inf);
                break;
            case 7:
                p31.ZZZ = A;            /* ZZZ3 = ZZZ1*ZZZ2*PPP */
                A = field_t::csel(field_t::one(), p31.ZZ, dbl);
                B = czero(p2.ZZ, inf);
                break;
            case 8:                     /* ZZ1*ZZ2 */
                B = PP;
                break;
            case 9:
                p31.ZZ = A;             /* ZZ3 = ZZ1*ZZ2*PP */
                A = field_t::csel(p2.X, U, dbl);
                break;
            case 10:
#define Q PP
                Q = A;                  /* Q = U1*PP */
                A = field_t::csel(p2.Y, S, dbl);
                B = PPP;
                break;
            case 11:
                p31.Y = A;              /* S1*PPP */
                A = R;
                B = R;
                break;
            case 12:                    /* R^2 */
                p31.X = A - PPP;        /* R^2-PPP */
                p31.X -= Q;
                p31.X -= Q;             /* X3 = R^2-PPP-2*Q */
                A = Q - p31.X;
                break;
            case 13:                    /* R*(Q-X3) */
                //p31.Y = A - p31.Y;    /* Y3 = R*(Q-X3)-S1*PPP */
                if (dbl) {
                    A = p2.X;
                    B = p2.X;
                } else {
                    done = true;
                }
                break;
#undef PPP
#undef Q
            /*** double |p2|, V*X1, W*Y1, ZZZ3 and ZZ3 are already calculated ***/
#define S PP
            case 14:
                A = A + A + A;          /* M = 3*X1^2[+a*ZZ1^2] */
                if (a4 != nullptr)
                    A += U;
                B = A;
                break;
            case 15:
                p31.X = A - S - S;      /* X3 = M^2-2*S */
                A = S - p31.X;
                break;
            case 16:                    /* M*(S-X3) */
                //p31.Y = A - p31.Y;    /* Y3 = M*(S-X3)-W*Y1 */
                done = true;
                break;
#undef S
            /*** account for a4 != nullptr when doubling ***/
            case 17:                    /* ZZ1^2 */
                if (a4 != nullptr)
                    B = *a4;
                break;
            case 18:                    /* ZZ1^2*a4 */
                if (a4 != nullptr) {
                    U = A;
                    A = p2.Y<<1;        /* U = 2*Y1 */
                    B = A;
                }
                pc = 3;
                break;
            }
        } while (!done);
        p31.Y = A - p31.Y;              /* Y3 = R*(Q-X3)-S1*PPP */

        *this = p31;
    }
#else
    inline void uadd(const xyzz_t& p2) { add(p2); }
#endif

    /*
     * http://hyperelliptic.org/EFD/g1p/auto-shortw-xyzz.html#addition-madd-2008-s
     * http://hyperelliptic.org/EFD/g1p/auto-shortw-xyzz.html#doubling-mdbl-2008-s-1
     * with twists to handle even subtractions and either input at infinity.
     * Addition costs 8M+2S, while conditional doubling - 2M+4M+3S.
     */
    template<class affine_t>
    __host__ __device__ void add(const affine_t& p2, bool subtract = false)
    {
#ifdef __CUDA_ARCH__
        xyzz_t p31 = *this;
#else
        xyzz_t& p31 = *this;
#endif

        if (p2.is_inf()) {
            return;
        } else if (p31.is_inf()) {
            p31 = p2;
            p31.ZZZ.cneg(subtract);
        } else {
            field_t P, R;

            R = p2.Y * p31.ZZZ;         /* S2 = Y2*ZZZ1 */
            R.cneg(subtract);
            R -= p31.Y;                 /* R = S2-Y1 */
            P = p2.X * p31.ZZ;          /* U2 = X2*ZZ1 */
            P -= p31.X;                 /* P = U2-X1 */

            if (!P.is_zero()) {         /* X1!=X2 */
                field_t PP;             /* add |p2| to |p1| */

                PP = P^2;               /* PP = P^2 */
#define PPP P
                PPP = P * PP;           /* PPP = P*PP */
                p31.ZZ *= PP;           /* ZZ3 = ZZ1*PP */
                p31.ZZZ *= PPP;         /* ZZZ3 = ZZZ1*PPP */
#define Q PP
                Q = PP * p31.X;         /* Q = X1*PP */
                p31.X = R^2;            /* R^2 */
                p31.X -= PPP;           /* R^2-PPP */
                p31.X -= Q;
                p31.X -= Q;             /* X3 = R^2-PPP-2*Q */
                Q -= p31.X;
                Q *= R;                 /* R*(Q-X3) */
                p31.Y *= PPP;           /* Y1*PPP */
                p31.Y = Q - p31.Y;      /* Y3 = R*(Q-X3)-Y1*PPP */
#undef Q
#undef PPP
            } else if (R.is_zero()) {   /* X1==X2 && Y1==Y2 */
                field_t M;              /* double |p2| */

#define U P
                U = p2.Y + p2.Y;        /* U = 2*Y1 */
                p31.ZZ = U^2;           /* [ZZ3 =] V = U^2 */
                p31.ZZZ = p31.ZZ * U;   /* [ZZZ3 =] W = U*V */
#define S R
                S = p2.X * p31.ZZ;      /* S = X1*V */
                M = p2.X^2;
                M = M + M + M;          /* M = 3*X1^2[+a] */
                if (a4 != nullptr) {
#ifdef __CUDA_ARCH__
                    M += (U = *a4);
#else
                    M += *a4;
#endif
                }
                p31.X = M^2;
                p31.X -= S;
                p31.X -= S;             /* X3 = M^2-2*S */
                p31.Y = p31.ZZZ * p2.Y; /* W*Y1 */
                S -= p31.X;
                S *= M;                 /* M*(S-X3) */
                p31.Y = S - p31.Y;      /* Y3 = M*(S-X3)-W*Y1 */
#undef S
#undef U
                p31.ZZZ.cneg(subtract);
            } else {                    /* X1==X2 && Y1==-Y2 */
                p31.inf();              /* set |p3| to infinity */
            }
        }
#ifdef __CUDA_ARCH__
        *this = p31;
#endif
    }

#ifdef __CUDA_ARCH__
    template<class affine_t>
    __device__ void uadd(const affine_t& p2, bool subtract = false)
    {

        if (p2.is_inf()) {
            return;
        } else if (is_inf()) {
            X = p2.X;
            Y = p2.Y;
            ZZ = ZZZ = field_t::one();
            ZZZ.cneg(subtract);
            return;
        }

        xyzz_t p31 = *this;

        field_t A, B, R, PP, PPP;
        int pc = -1;
        bool done = false, dbl = false, inf = false;

        A = p2.Y;
        B = p31.ZZZ;
        #pragma unroll 1
        do {
            A = A * B;
            switch (++pc) {
            case 0:                     /* S2 = Y2*ZZZ1 */
                A.cneg(subtract);
                R = A - p31.Y;          /* R = S2-Y1 */
                A = p2.X;
                B = p31.ZZ;
                break;
            case 1:                     /* U2 = X2*ZZ1 */
                A -= p31.X;             /* P = U2-X1 */
                inf = A.is_zero();      /* X1==X2, not add |p2| to |p1| */
                dbl = R.is_zero() & inf;
                if (dbl) {              /* X1==X2 && Y1==Y2, double |p2| */
                    A = p2.Y<<1;        /* U = 2*Y1 */
                    inf = false;        /* don't set |p3| to infinity */
                }
                B = A;
                break;
            case 2:
                PP = A;                 /* PP = P^2 */
                break;
            case 3:
                PPP = A;                /* PPP = P*PP */
                B = czero(p31.ZZZ, inf);
                break;
            case 4:
                p31.ZZZ = field_t::csel(PPP, A, dbl);   /* ZZZ3 = ZZZ1*PPP */
                A = field_t::csel(p2.Y, p31.Y, dbl);
                B = PPP;
                break;
            case 5:
                p31.Y = A;              /* Y1*PPP */
                A = czero(p31.ZZ, inf);
                B = PP;
                break;
            case 6:
                p31.ZZ = field_t::csel(PP, A, dbl);     /* ZZ3 = ZZ1*PP */
                A = field_t::csel(p2.X, p31.X, dbl);
                break;
            case 7:
                B = R;
#define Q R
                Q = A;                  /* Q = X1*PP */
                A = B;
                break;
            case 8:                     /* R^2 */
                p31.X = A - PPP;        /* R^2-PPP */
                p31.X -= Q;
                p31.X -= Q;             /* X3 = R^2-PPP-2*Q */
                A = Q - p31.X;
                break;
            case 9:                     /* R*(Q-X3) */
                //p31.Y = A - p31.Y;    /* Y3 = R*(Q-X3)-Y1*PPP */
                if (dbl) {
                    //p31.ZZ = PP;      /* [ZZ3 =] V = U^2 */
                    //p31.ZZZ = PPP;    /* [ZZZ3 =] W = U*V */
                    A = p2.X;
                    B = p2.X;
                } else {
                    done = true;
                }
                break;
#undef Q
            /*** double |p2|, V*X1, W*Y1, ZZ3 and ZZZ3 are already calculated ***/
#define S R
            case 10:                    /* X1^2 */
                A += A<<1;              /* M = 3*X1^2[+a] */
                if (a4 != nullptr)
                    A += (B = *a4);
                B = A;
                break;
            case 11:                    /* M^2 */
                p31.X = A - S - S;      /* X3 = M^2-2*S */
                A = S - p31.X;
                break;
            case 12:                    /* M*(S-X3) */
                //p31.Y = A - p31.Y;    /* Y3 = M*(S-X3)-W*Y1 */
                p31.ZZZ.cneg(subtract);
                done = true;
                break;
#undef S
            }
        } while (!done);
        p31.Y = A - p31.Y;              /* Y3 = R*(Q-X3)-Y1*PPP */

        *this = p31;
    }
#else
    template<class affine_t>
    inline void uadd(const affine_t& p2, bool subtract = false)
    {   add(p2, subtract);   }
#endif

#ifdef __CUDA_ARCH__
    inline __device__ xyzz_t shfl_down(uint32_t off) const
    {
        xyzz_t ret;

        ret.X   = X.shfl_down(off);
        ret.Y   = Y.shfl_down(off);
        ret.ZZZ = ZZZ.shfl_down(off);
        ret.ZZ  = ZZ.shfl_down(off);

        return ret;
    }
#endif
};

#ifdef __CUDACC__
# pragma nv_diag_default 284
#endif
#endif
