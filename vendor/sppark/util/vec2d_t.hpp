// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_UTIL_VEC2D_T_HPP__
#define __SPPARK_UTIL_VEC2D_T_HPP__

#include <cstddef>

#if !defined(__CUDACC__) && !defined(__HIPCC__)
# define __host__
# define __device__
#endif

template<typename T, typename dim_t = unsigned int>
class vec2d_t {
    dim_t dim_x, dim_y_owned;
    T* ptr;

public:
    __host__ __device__
    vec2d_t(T* data, dim_t x) : dim_x(x), dim_y_owned(0), ptr(data) {}
    __host__ __device__
    vec2d_t(T* data, dim_t x, dim_t y) : dim_x(x), dim_y_owned(y<<1), ptr(data) {}
    vec2d_t(void* data, dim_t x) : dim_x(x), dim_y_owned(0), ptr((T*)data) {}
    vec2d_t(dim_t x, size_t y) : dim_x(x), dim_y_owned(((dim_t)y<<1) | 1), ptr(new T[x*y]) {}
    vec2d_t() : dim_x(0), dim_y_owned(0), ptr(nullptr) {}
#if !defined(__CUDA_ARCH__) && !defined(__HIP_DEVICE_COMPILE__)
    vec2d_t(const vec2d_t& other) { *this = other; dim_y_owned &= ((dim_t)0-1) << 1; }
    ~vec2d_t() { if (dim_y_owned&1) delete[] ptr; }

    inline vec2d_t& operator=(const vec2d_t& other)
    {
        if (this == &other)
            return *this;

        dim_x = other.dim_x;
        dim_y_owned = other.dim_y_owned & ((dim_t)0 - 1) << 1;
        ptr = other.ptr;

        return *this;
    }
#endif
    inline operator void*() const { return ptr; }
    __host__ __device__
    inline T* operator[](size_t y) const { return ptr + dim_x*y; }
    __host__ __device__
    inline dim_t y() const { return dim_y_owned >> 1; }
    __host__ __device__
    inline dim_t x() const { return dim_x; }
};

#if !defined(__CUDACC__) && !defined(__HIPCC__)
# undef __device__
# undef __host__
#endif

#endif
