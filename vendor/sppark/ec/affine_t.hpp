// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_EC_AFFINE_T_HPP__
#define __SPPARK_EC_AFFINE_T_HPP__

#ifndef __CUDACC__
# undef  __host__
# define __host__
# undef  __device__
# define __device__
# undef  __noinline__
# define __noinline__
#endif

template<class field_t, class field_h = typename field_t::mem_t,
         const field_h* a4 = nullptr>
class Affine_t {
template<class, class H, const H*> friend class jacobian_t;
template<class, class H, const H*> friend class xyzz_t;

    field_t X, Y;

public:
    inline __host__ __device__ Affine_t() {}
    inline __host__ __device__ Affine_t(const field_t& x, const field_t& y) :
                                                     X(x),             Y(y) {}

#ifdef __CUDA_ARCH__
    inline __device__ bool is_inf() const
    {   return (bool)(X.is_zero(Y));   }
#else
    inline __host__   bool is_inf() const
    {   return (bool)((int)X.is_zero() & (int)Y.is_zero());   }
#endif
    inline __host__ __device__ void cneg(bool neg) { Y.cneg(neg); }

    template<class point_t>
    inline __host__ __device__ operator point_t() const
    {   return point_t{ X, Y, is_inf() };   }

    friend inline bool operator==(const Affine_t& p1, const Affine_t& p2)
    {   return (p1.X == p2.X) & (p1.Y == p2.Y);   }
    friend inline bool operator!=(const Affine_t& p1, const Affine_t& p2)
    {   return !(p1 == p2);   }

    template<class point_t>
    friend inline bool operator==(const Affine_t& p1, const point_t& p2)
    {   return p2 == p1;   }
    template<class point_t>
    friend inline bool operator!=(const Affine_t& p1, const point_t& p2)
    {   return p2 != p1;   }

#ifdef __CUDACC__
    class mem_t {
        field_h X, Y;

    public:
        inline __device__ operator Affine_t() const
        {
            Affine_t p;
            p.X = X;
            p.Y = Y;
            return p;
        }
    };
#else
    using mem_t = Affine_t;
#endif
};

template<class field_t, class field_h = typename field_t::mem_t,
         const field_h* a4 = nullptr>
class Affine_inf_t {
template<class, class H, const H*> friend class jacobian_t;
template<class, class H, const H*> friend class xyzz_t;

    field_t X, Y;
    bool inf;

    inline __host__ __device__ bool is_inf() const
    {   return inf;   }

    using affine_t = Affine_t<field_t, field_h, a4>;

public:
    inline __host__ __device__ operator affine_t() const
    {
        bool inf = is_inf();
        return affine_t{czero(X, inf), czero(Y, inf)};
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
            return affine_t{czero((field_t)X, inf), czero((field_t)Y, inf)};
        }

        inline __device__ operator Affine_inf_t() const
        {
            bool inf = is_inf();
            Affine_inf_t p;
            p.X = czero((field_t)X, inf);
            p.Y = czero((field_t)Y, inf);
            p.inf = inf;
            return p;
        }
    };
#else
    using mem_t = Affine_inf_t;
#endif
};

#endif
