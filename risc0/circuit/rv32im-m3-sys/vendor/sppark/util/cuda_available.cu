// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

// #include <util/cuda_available.cu> or compile separately...

#if defined(__NVCC__) && !defined(__CUDA_ARCH__)
#include <atomic>

extern "C"
bool cuda_available()
{
    static std::atomic<int> available(-1);
    int ret = available;
    if (ret < 0) {
        cudaDeviceProp prop;
        ret = cudaGetDeviceProperties(&prop, 0) == cudaSuccess &&
              prop.major >= 7;
        available = ret;
    }
    return (bool)ret;
}
#endif
