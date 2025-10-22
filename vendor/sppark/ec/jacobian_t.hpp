// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_EC_JACOBIAN_T_HPP__
#define __SPPARK_EC_JACOBIAN_T_HPP__

#include "affine_t.hpp"

template<class field_t, class field_h = typename field_t::mem_t,
         const field_h* a4 = nullptr>
class jacobian_t {
    field_t X, Y, Z;

    inline operator const void*() const { return this; }
    inline operator void*()             { return this; }

public:
    jacobian_t() = default;
    jacobian_t(const field_t& x, const field_t& y, const field_t& z) :
                            X(x),             Y(y),             Z(z) {}
    jacobian_t(const field_t& x, const field_t& y, bool is_inf) :
                            X(x),             Y(y),
                            Z(field_t::one(is_inf)) {}

    using affine_t = Affine_t<field_t, field_h, a4>;

    inline operator affine_t() const
    {
        field_t ya = 1/Z;
        field_t xa = ya^2;  // 1/Z^2
        ya *= xa;           // 1/Z^3
        xa *= X;            // X/Z^2
        ya *= Y;            // Y/Z^3
        return affine_t{xa, ya};
    }

#ifdef __CUDACC__ // mask a warning
    inline jacobian_t& operator=(const affine_t& a)
    {
        X = a.X;
        Y = a.Y;
        Z = field_t::one(a.is_inf());
        return *this;
    }
#endif

    template<class point_t>
    inline jacobian_t& operator=(const point_t& a)
    {   return *this = static_cast<jacobian_t>(a);   }

    inline bool is_inf() const { return (bool)(Z.is_zero()); }
    inline void inf()          { Z.zero(); }
    inline void cneg(bool neg) { Y.cneg(neg); }

    /*
     * Addition that can handle doubling [as well as points at infinity,
     * which are encoded as Z==0] in constant time. It naturally comes at
     * cost, but this subroutine should be called only when independent
     * points are processed, which is considered reasonable compromise.
     * For example, ptype##s_mult_w5 calls it, but since *major* gain is
     * result of pure doublings being effectively divided by amount of
     * points, slightly slower addition can be tolerated. But what is the
     * additional cost more specifically? Best addition result is 11M+5S,
     * while this routine takes 13M+5S (+1M+1S if a4!=0), as per
     *
     * -------------+-------------
     * addition     | doubling
     * -------------+-------------
     * U1 = X1*Z2^2 | U1 = X1
     * U2 = X2*Z1^2 |
     * S1 = Y1*Z2^3 | S1 = Y1
     * S2 = Y2*Z1^3 |
     * zz = Z1*Z2   | zz = Z1
     * H = U2-U1    | H' = 2*Y1
     * R = S2-S1    | R' = 3*X1^2[+a*Z1^4]
     * sx = U1+U2   | sx = X1+X1
     * -------------+-------------
     * H!=0 || R!=0 | H==0 && R==0
     *
     *      X3 = R^2-H^2*sx
     *      Y3 = R*(H^2*U1-X3)-H^3*S1
     *      Z3 = H*zz
     *
     * As for R!=0 condition in context of H==0, a.k.a. P-P. The result is
     * infinity by virtue of Z3 = (U2-U1)*zz = H*zz = 0*zz == 0.
     */
    static void dadd(jacobian_t& out, const jacobian_t& p1,
                                      const jacobian_t& p2)
    {
        jacobian_t p3;          /* starts as (U1, S1, zz) from addition side */
        struct { field_t H, R, sx; } add, dbl;
        bool p1inf, p2inf, is_dbl;

        dbl.sx = p1.X + p1.X;   /* sx = X1+X1 */
        dbl.R = p1.X^2;         /* X1^2 */
        dbl.R += dbl.R + dbl.R; /* R = 3*X1^2 */
        dbl.H = p1.Y + p1.Y;    /* H = 2*Y1 */

        p2inf = p2.is_inf();
        p3.X = p2.Z^2;          /* Z2^2 */
        p3.Z = p1.Z * p2.Z;     /* Z1*Z2 */
        p1inf = p1.is_inf();
        add.H = p1.Z^2;         /* Z1^2 */

        if (a4 != nullptr) {
            p3.Y = add.H^2;     /* Z1^4, [borrow p3.Y] */
            p3.Y *= *a4;
            dbl.R += p3.Y;      /* R = 3*X1^2+a*Z1^4 */
        }

        p3.Y = p1.Y * p2.Z;
        p3.Y *= p3.X;           /* S1 = Y1*Z2^3 */
        add.R = p2.Y * p1.Z;
        add.R *= add.H;         /* S2 = Y2*Z1^3 */
        add.R -= p3.Y;          /* R = S2-S1 */

        p3.X *= p1.X;           /* U1 = X1*Z2^2 */
        add.H *= p2.X;          /* U2 = X2*Z1^2 */

        add.sx = add.H + p3.X;  /* sx = U1+U2 */
        add.H -= p3.X;          /* H = U2-U1 */

        is_dbl = add.H.is_zero() & add.R.is_zero();
        vec_select(&p3, &p1, &p3, sizeof(p3), is_dbl);
        vec_select(&add, &dbl, &add, sizeof(add), is_dbl);
        /* |p3| and |add| hold all inputs now, |p3| will hold output */

        p3.Z *= add.H;          /* Z3 = H*Z1*Z2 */

        dbl.H = add.H^2;        /* H^2 */
        dbl.R = dbl.H * add.H;  /* H^3 */
        dbl.R *= p3.Y;          /* H^3*S1 */
        p3.Y = dbl.H * p3.X;    /* H^2*U1 */

        dbl.H *= add.sx;        /* H^2*sx */
        p3.X = add.R^2;         /* R^2 */
        p3.X -= dbl.H;          /* X3 = R^2-H^2*sx */

        p3.Y -= p3.X;           /* H^2*U1-X3 */
        p3.Y *= add.R;          /* R*(H^2*U1-X3) */
        p3.Y -= dbl.R;          /* Y3 = R*(H^2*U1-X3)-H^3*S1 */

        vec_select(&p3, &p1, &p3, sizeof(p3), p2inf);
        vec_select(out, &p2, &p3, sizeof(p3), p1inf);
    }
    inline void dadd(const jacobian_t& p2)
    {   dadd(*this, *this, p2);   }

    /*
     * Addition with affine point that can handle doubling [as well as
     * points at infinity, with |p1| being encoded as Z==0 and |p2| as
     * X,Y==0] in constant time. But at what additional cost? Best
     * addition result is 7M+4S, while this routine takes 8M+5S, as per
     *
     * -------------+-------------
     * addition     | doubling
     * -------------+-------------
     * U1 = X1      | U1 = X2
     * U2 = X2*Z1^2 |
     * S1 = Y1      | S1 = Y2
     * S2 = Y2*Z1^3 |
     * H = U2-X1    | H' = 2*Y2
     * R = S2-Y1    | R' = 3*X2^2[+a]
     * sx = X1+U2   | sx = X2+X2
     * zz = H*Z1    | zz = H'
     * -------------+-------------
     * H!=0 || R!=0 | H==0 && R==0
     *
     *      X3 = R^2-H^2*sx
     *      Y3 = R*(H^2*U1-X3)-H^3*S1
     *      Z3 = zz
     *
     * As for R!=0 condition in context of H==0, a.k.a. P-P. The result is
     * infinity by virtue of Z3 = (U2-U1)*zz = H*zz = 0*zz == 0.
     */
    static void dadd(jacobian_t& out, const jacobian_t& p1, const affine_t& p2)
    {
        jacobian_t p3;          /* starts as (,, H*Z1) from addition side */
        struct { field_t H, R, sx; } add, dbl;
        bool p1inf, p2inf, is_dbl;

        p2inf = p2.is_inf();
        dbl.sx = p2.X + p2.X;   /* sx = X2+X2 */
        dbl.R = p2.X^2;         /* X2^2 */
        dbl.R += dbl.R + dbl.R; /* R = 3*X2^2 */
        if (a4 != nullptr)
            dbl.R += *a4;
        dbl.H = p2.Y + p2.Y;    /* H = 2*Y2 */

        p1inf = p1.is_inf();
        add.H = p1.Z^2;         /* Z1^2 */
        add.R = add.H * p1.Z;   /* Z1^3 */
        add.R *= p2.Y;          /* S2 = Y2*Z1^3 */
        add.R -= p1.Y;          /* R = S2-Y1 */

        add.H *= p2.X;          /* U2 = X2*Z1^2 */

        add.sx = add.H + p1.X;  /* sx = X1+U2 */
        add.H -= p1.X;          /* H = U2-X1 */

        p3.Z = add.H * p1.Z;    /* Z3 = H*Z1 */

        /* make the choice between addition and doubling */
        is_dbl = add.H.is_zero() & add.R.is_zero();
        vec_select(p3.X, p2.X, p1.X, 2*sizeof(p3.X), is_dbl);
        vec_select(p3.Z, dbl.H, p3.Z, sizeof(p3.Z), is_dbl);
        vec_select(&add, &dbl, &add, sizeof(add), is_dbl);
        /* |p3| and |add| hold all inputs now, |p3| will hold output */

        dbl.H = add.H^2;        /* H^2 */
        dbl.R = dbl.H * add.H;  /* H^3 */
        dbl.R *= p3.Y;          /* H^3*S1 */
        p3.Y = dbl.H * p3.X;    /* H^2*U1 */

        dbl.H *= add.sx;        /* H^2*sx */
        p3.X = add.R^2;         /* R^2 */
        p3.X -= dbl.H;          /* X3 = R^2-H^2*sx */

        p3.Y -= p3.X;           /* H^2*U1-X3 */
        p3.Y *= add.R;          /* R*(H^2*U1-X3) */
        p3.Y -= dbl.R;          /* Y3 = R*(H^2*U1-X3)-H^3*S1 */

        vec_select(p3.X, p2.X, p3.X, 2*sizeof(p3.X), p1inf);
        vec_select(p3.Z, field_t::one(), p3.Z, sizeof(p3.Z), p1inf);
        vec_select(&out, &p1, &p3, sizeof(p3), p2inf);
    }
    inline void dadd(const affine_t& p2)
    {   dadd(*this, *this, p2);   }

    /*
     * https://www.hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-0.html#addition-add-2007-bl
     * with twist to handle either input at infinity, which are encoded as Z==0.
     */
    static void add(jacobian_t& out, const jacobian_t& p1, const jacobian_t& p2)
    {
        jacobian_t p3;
        field_t Z1Z1, Z2Z2, U1, S1, H, I, J;
        bool p1inf, p2inf;

        p1inf = p1.is_inf();
        Z1Z1 = p1.Z^2;          /* Z1Z1 = Z1^2 */
        p3.Z = Z1Z1 * p1.Z;     /* Z1*Z1Z1 */
        p3.Z *= p2.Y;           /* S2 = Y2*Z1*Z1Z1 */

        p2inf = p2.is_inf();
        Z2Z2 = p2.Z^2;          /* Z2Z2 = Z2^2 */

        S1 = Z2Z2 * p2.Z;       /* Z2*Z2Z2 */
        S1 *= p1.Y;             /* S1 = Y1*Z2*Z2Z2 */

        p3.Z -= S1;             /* S2-S1 */
        p3.Z += p3.Z;           /* r = 2*(S2-S1) */

        U1 = p1.X * Z2Z2;       /* U1 = X1*Z2Z2 */
        H = p2.X * Z1Z1;        /* U2 = X2*Z1Z1 */

        H -= U1;                /* H = U2-U1 */

        I = H + H;              /* 2*H */
        I ^= 2;                 /* I = (2*H)^2 */

        J = H * I;              /* J = H*I */
        S1 *= J;                /* S1*J */

        p3.Y = U1 * I;          /* V = U1*I */

        p3.X = p3.Z^2;          /* r^2 */
        p3.X -= J;              /* r^2-J */
        p3.X -= p3.Y;
        p3.X -= p3.Y;           /* X3 = r^2-J-2*V */

        p3.Y -= p3.X;           /* V-X3 */
        p3.Y *= p3.Z;           /* r*(V-X3) */
        p3.Y -= S1;
        p3.Y -= S1;             /* Y3 = r*(V-X3)-2*S1*J */

        p3.Z = p1.Z + p2.Z;     /* Z1+Z2 */
        p3.Z ^= 2;              /* (Z1+Z2)^2 */
        p3.Z -= Z1Z1;           /* (Z1+Z2)^2-Z1Z1 */
        p3.Z -= Z2Z2;           /* (Z1+Z2)^2-Z1Z1-Z2Z2 */
        p3.Z *= H;              /* Z3 = ((Z1+Z2)^2-Z1Z1-Z2Z2)*H */

        vec_select(&p3, &p1, &p3, sizeof(p3), p2inf);
        vec_select(&out, &p2, &p3, sizeof(p3), p1inf);
    }

    /*
     * https://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-0.html#addition-madd-2007-bl
     * with twist to handle either input at infinity, with |p1| encoded as Z==0,
     * and |p2| as X==Y==0.
     */
    static void add(jacobian_t& out, const jacobian_t& p1, const affine_t& p2)
    {
        jacobian_t p3;
        field_t Z1Z1, H, HH, I, J;
        bool p1inf, p2inf;

        p1inf = p1.is_inf();

        Z1Z1 = p1.Z^2;          /* Z1Z1 = Z1^2 */

        p3.Z = Z1Z1 * p1.Z;     /* Z1*Z1Z1 */
        p3.Z *= p2.Y;           /* S2 = Y2*Z1*Z1Z1 */

        p2inf = p2.is_inf();

        H = p2.X * Z1Z1;        /* U2 = X2*Z1Z1 */
        H -= p1.X;              /* H = U2-X1 */

        HH = H^2;               /* HH = H^2 */
        I = HH + HH;
        I += I;                 /* I = 4*HH */

        p3.Y = p1.X * I;        /* V = X1*I */
        J = H * I;              /* J = H*I */
        I = J * p1.Y;           /* Y1*J */

        p3.Z -= p1.Y;           /* S2-Y1 */
        p3.Z += p3.Z;           /* r = 2*(S2-Y1) */

        p3.X = p3.Z^2;          /* r^2 */
        p3.X -= J;              /* r^2-J */
        p3.X -= p3.Y;
        p3.X -= p3.Y;           /* X3 = r^2-J-2*V */

        p3.Y -= p3.X;           /* V-X3 */
        p3.Y *= p3.Z;           /* r*(V-X3) */
        p3.Y -= I;
        p3.Y -= I;              /* Y3 = r*(V-X3)-2*Y1*J */

        p3.Z = p1.Z + H;        /* Z1+H */
        p3.Z ^= 2;              /* (Z1+H)^2 */
        p3.Z -= Z1Z1;           /* (Z1+H)^2-Z1Z1 */
        p3.Z -= HH;             /* Z3 = (Z1+H)^2-Z1Z1-HH */

        vec_select(p3.Z, field_t::one(), p3.Z, sizeof(p3.Z), p1inf);
        vec_select(p3.X, p2.X,  p3.X, 2*sizeof(p3.X), p1inf);
        vec_select(&out, &p1, &p3, sizeof(p3), p2inf);
    }

    /*
     * https://www.hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-0.html#doubling-dbl-2009-l
     */
    static void dbl(jacobian_t& p3, const jacobian_t& p1)
    {
        field_t A, B, C;

        A = p1.X^2;             /* A = X1^2 */
        B = p1.Y^2;             /* B = Y1^2 */
        C = B^2;                /* C = B^2 */

        B += p1.X;              /* X1+B */
        B *= B;                 /* (X1+B)^2 */
        B -= A;                 /* (X1+B)^2-A */
        B -= C;                 /* (X1+B)^2-A-C */
        B += B;                 /* D = 2*((X1+B)^2-A-C) */

        A += A<<1;              /* E = 3*A */

        p3.X = A^2;             /* F = E^2 */
        p3.X -= B;
        p3.X -= B;              /* X3 = F-2*D */

        p3.Z = p1.Z * p1.Y;     /* Z1*Y1 */
        p3.Z <<= 1;             /* Z3 = 2*Z1*Y1 */

        C <<= 3;                /* 8*C */
        p3.Y = B - p3.X;        /* D-X3 */
        p3.Y *= A;              /* E*(D-X3) */
        p3.Y -= C;              /* Y3 = E*(D-X3)-8*C */
    }
    inline void dbl() { dbl(*this, *this); }

    /*
     * Non-constant-time add-or-double.
     */
    void add(const jacobian_t& p2)
    {
#ifdef __CUDA_ARCH__
        jacobian_t p1 = *this;
#else
        jacobian_t &p1 = *this;
#endif
        jacobian_t p3;

        if (p2.is_inf()) {
            return;
        } else if (p1.is_inf()) {
            p3 = p2;
        } else {
            field_t Z1Z1, Z2Z2, U1, S1, H;

            Z1Z1 = p1.Z^2;          /* Z1Z1 = Z1^2 */
            p3.Z = Z1Z1 * p1.Z;     /* Z1*Z1Z1 */
            p3.Z *= p2.Y;           /* S2 = Y2*Z1*Z1Z1 */

            Z2Z2 = p2.Z^2;          /* Z2Z2 = Z2^2 */
            S1 = Z2Z2 * p2.Z;       /* Z2*Z2Z2 */
            S1 *= p1.Y;             /* S1 = Y1*Z2*Z2Z2 */
            p3.Z -= S1;             /* S2-S1 */

            U1 = p1.X * Z2Z2;       /* U1 = X1*Z2Z2 */
            H = p2.X * Z1Z1;        /* U2 = X2*Z1Z1 */
            H -= U1;                /* H = U2-U1 */

            if ((int)H.is_zero() & (int)p3.Z.is_zero()) {
                field_t A, B, C;    /* double |p1| */

                A = p1.X^2;         /* A = X1^2 */
                B = p1.Y^2;         /* B = Y1^2 */
                C = B^2;            /* C = B^2 */

                B += p1.X;          /* X1+B */
                B *= B;             /* (X1+B)^2 */
                B -= A;             /* (X1+B)^2-A */
                B -= C;             /* (X1+B)^2-A-C */
                B += B;             /* D = 2*((X1+B)^2-A-C) */

                A += A<<1;          /* E = 3*A */

                p3.X = A^2;         /* F = E^2 */
                p3.X -= B;
                p3.X -= B;          /* X3 = F-2*D */

                p3.Z = p1.Z * p1.Y; /* Z1*Y1 */
                p3.Z <<= 1;         /* Z3 = 2*Z1*Y1 */

                C <<= 3;            /* 8*C */
                p3.Y = B - p3.X;    /* D-X3 */
                p3.Y *= A;          /* E*(D-X3) */
                p3.Y -= C;          /* Y3 = E*(D-X3)-8*C */
            } else {
                field_t I, J;       /* add |p1| and |p2| */

                I = H + H;          /* 2*H */
                I ^= 2;             /* I = (2*H)^2 */

                J = H * I;          /* J = H*I */
                S1 *= J;            /* S1*J */

                p3.Y = U1 * I;      /* V = U1*I */

                p3.Z += p3.Z;       /* r = 2*(S2-S1) */
                p3.X = p3.Z^2;      /* r^2 */
                p3.X -= J;          /* r^2-J */
                p3.X -= p3.Y;
                p3.X -= p3.Y;       /* X3 = r^2-J-2*V */

                p3.Y -= p3.X;       /* V-X3 */
                p3.Y *= p3.Z;       /* r*(V-X3) */
                p3.Y -= S1;
                p3.Y -= S1;         /* Y3 = r*(V-X3)-2*S1*J */

                p3.Z = p1.Z + p2.Z; /* Z1+Z2 */
                p3.Z ^= 2;          /* (Z1+Z2)^2 */
                p3.Z -= Z1Z1;       /* (Z1+Z2)^2-Z1Z1 */
                p3.Z -= Z2Z2;       /* (Z1+Z2)^2-Z1Z1-Z2Z2 */
                p3.Z *= H;          /* Z3 = ((Z1+Z2)^2-Z1Z1-Z2Z2)*H */
            }
        }
        *this = p3;
    }

    void add(const affine_t& p2)
    {
#ifdef __CUDA_ARCH__
        jacobian_t p1 = *this;
#else
        jacobian_t &p1 = *this;
#endif
        jacobian_t p3;

        if (p2.is_inf()) {
            return;
        } else if (p1.is_inf()) {
            p3 = p2;
        } else {
            field_t Z1Z1, H;

            Z1Z1 = p1.Z^2;          /* Z1Z1 = Z1^2 */
            p3.Z = Z1Z1 * p1.Z;     /* Z1*Z1Z1 */
            p3.Z *= p2.Y;           /* S2 = Y2*Z1*Z1Z1 */
            p3.Z -= p1.Y;           /* S2-Y1 */

            H = p2.X * Z1Z1;        /* U2 = X2*Z1Z1 */
            H -= p1.X;              /* H = U2-X1 */

            if (H.is_zero() & p3.Z.is_zero()) {
                field_t A, B, C;    /* double |p2| */

                A = p2.X^2;         /* A = X1^2 */
                B = p2.Y^2;         /* B = Y1^2 */
                C = B^2;            /* C = B^2 */

                B += p2.X;          /* X1+B */
                B *= B;             /* (X1+B)^2 */
                B -= A;             /* (X1+B)^2-A */
                B -= C;             /* (X1+B)^2-A-C */
                B += B;             /* D = 2*((X1+B)^2-A-C) */

                A += A<<1;          /* E = 3*A */

                p3.X = A^2;         /* F = E^2 */
                p3.X -= B;
                p3.X -= B;          /* X3 = F-2*D */

                p3.Z = p2.Y + p2.Y; /* Z3 = 2*[Z1==1]*Y1 */

                C <<= 3;            /* 8*C */
                p3.Y = B - p3.X;    /* D-X3 */
                p3.Y *= A;          /* E*(D-X3) */
                p3.Y -= C;          /* Y3 = E*(D-X3)-8*C */
            } else {
                field_t HH, I, J;   /* add |p1| and |p2| */

                HH = H^2;           /* HH = H^2 */
                I = HH + HH;
                I += I;             /* I = 4*HH */

                p3.Y = p1.X * I;    /* V = X1*I */
                J = H * I;          /* J = H*I */
                I = J * p1.Y;       /* Y1*J */

                p3.Z += p3.Z;       /* r = 2*(S2-Y1) */
                p3.X = p3.Z^2;      /* r^2 */
                p3.X -= J;          /* r^2-J */
                p3.X -= p3.Y;
                p3.X -= p3.Y;       /* X3 = r^2-J-2*V */

                p3.Y -= p3.X;       /* V-X3 */
                p3.Y *= p3.Z;       /* r*(V-X3) */
                p3.Y -= I;
                p3.Y -= I;          /* Y3 = r*(V-X3)-2*Y1*J */

                p3.Z = p1.Z + H;    /* Z1+H */
                p3.Z ^= 2;          /* (Z1+H)^2 */
                p3.Z -= Z1Z1;       /* (Z1+H)^2-Z1Z1 */
                p3.Z -= HH;         /* Z3 = (Z1+H)^2-Z1Z1-HH */
            }
        }
        *this = p3;
    }

    friend inline bool operator==(const jacobian_t& p1, const jacobian_t& p2)
    {
        field_t Z1Z1 = p1.Z^2;
        field_t Z2Z2 = p2.Z^2;
        struct { field_t X, Y; } a1{p1.X * Z2Z2, p1.Y * (Z2Z2 *= p2.Z)};
        struct { field_t X, Y; } a2{p2.X * Z1Z1, p2.Y * (Z1Z1 *= p1.Z)};
        return (a1.X == a2.X) & (a1.Y == a2.Y) & (p1.is_inf() ^ p2.is_inf() ^ 1);
    }
    friend inline bool operator!=(const jacobian_t& p1, const jacobian_t& p2)
    {   return !(p1 == p2);   }

private:
    inline bool eq(const affine_t& p2) const
    {
        field_t Z1Z1 = Z^2;
        struct { field_t X, Y; } a2{p2.X * Z1Z1, p2.Y * (Z1Z1 *= Z)};
        return (X == a2.X) & (Y == a2.Y) & (is_inf() ^ p2.is_inf() ^ 1);
    }

public:
    friend inline bool operator==(const jacobian_t& p1, const affine_t& p2)
    {   return p1.eq(p2);   }
    friend inline bool operator!=(const jacobian_t& p1, const affine_t& p2)
    {   return !p1.eq(p2);   }
};
#endif
