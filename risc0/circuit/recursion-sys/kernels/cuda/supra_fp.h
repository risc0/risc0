#pragma once

#include <ff/baby_bear.hpp>

static __device__ bb31_t pow(bb31_t b, int e) { return b^(unsigned int)e; }
static __device__ bb31_t inv(bb31_t a)        { return a.reciprocal(); }

typedef bb31_t Fp;
typedef bb31_4_t Fp4;
typedef bb31_4_t FpExt;
