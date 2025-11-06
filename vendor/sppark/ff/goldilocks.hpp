// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#if !defined(__SPPARK_FF_BABY_GOLDILOCKS_HPP__)
#define __SPPARK_FF_BABY_GOLDILOCKS_HPP__

#ifdef __CUDACC__
# include "gl64_t.cuh"  // CUDA device-side field types
#elif defined(__HIPCC__)
# include "gl64_t.hip"
#endif

namespace goldilocks {
typedef gl64_t fr_t;
}

#ifdef FEATURE_GOLDILOCKS
using namespace goldilocks;
#endif

#endif
