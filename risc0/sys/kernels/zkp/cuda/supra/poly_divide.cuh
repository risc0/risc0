#include <cooperative_groups.h>
#include <ff/baby_bear.hpp>

#define LG_DIV_BLOCK_SZ 10
#define DIV_BLOCK_SZ (1 << LG_DIV_BLOCK_SZ)
#define DIVISOR_DEGREE 1

__device__ __forceinline__ fr4_t shfl(const fr4_t& src, uint32_t idx, uint32_t width = 32) {
  const size_t len = sizeof(fr4_t) / sizeof(uint32_t);
  union {
    fr4_t val;
    uint32_t vec[len];
  } ret{src};

  for (size_t i = 0; i < len; i++)
    ret.vec[i] = __shfl_sync(0xffffffff, ret.vec[i], idx, width);

  return ret.val;
}

__device__ __forceinline__ void
warp_sum_and_reduce(fr4_t& val, uint32_t upper_bound, const fr4_t* powers) {
  uint32_t lane = threadIdx.x % WARP_SZ;

  fr4_t sval, rval;

#pragma unroll 1
  for (uint32_t i = 1; i <= upper_bound; i *= 2) {
    uint32_t width = i * 2;
    uint32_t lanew = lane & (width - 1);
    uint32_t exp = i - lanew;

    sval = shfl(val, i, width);

    rval = 0;
    if (lanew < i)
      rval = powers[exp - 1];

    sval *= rval;
    val += sval;
  }
}

__device__ __forceinline__ fr4_t get_windowed_power(const fr4_t (*windowed_powers)[DIV_BLOCK_SZ],
                                                    uint32_t pow) {
  unsigned int off = 0;

  fr4_t t, res;

  if (pow % DIV_BLOCK_SZ == 0) {
    pow >>= LG_DIV_BLOCK_SZ;
    off++;
  }

  res = windowed_powers[off][pow % DIV_BLOCK_SZ];

#pragma unroll 1
  while (pow >>= LG_DIV_BLOCK_SZ)
    res *= (t = windowed_powers[++off][pow % DIV_BLOCK_SZ]);

  return res;
}

template <typename T> __host__ __device__ __forceinline__ T round_to_next_power_of_2(T r) {
  if (sizeof(T) == 8) {
#ifdef __CUDA_ARCH__
    return (T)1 << (64 - __clzll(r - 1));
#else
    return (T)1 << (64 - __builtin_clzll(r - 1));
#endif
  } else { // 32 bits
#ifdef __CUDA_ARCH__
    return (T)1 << (32 - __clz(r - 1));
#else
    return (T)1 << (32 - __builtin_clz(r - 1));
#endif
  }
}

__launch_bounds__(DIV_BLOCK_SZ) __global__
    void generate_z_powers(fr4_t (*z_powers)[DIV_BLOCK_SZ], const fr4_t z, uint32_t sm_count) {
  uint32_t sm_ceil = round_to_next_power_of_2(sm_count);

  uint32_t tid = threadIdx.x;
  z_powers[0][tid] = z ^ tid;
  if (tid <= sm_ceil)
    z_powers[1][tid] = z ^ (DIV_BLOCK_SZ * tid);
}

__launch_bounds__(DIV_BLOCK_SZ) __global__
    void div_by_x_minus_z(fr4_t* polynomial,
                          fr4_t* acc,
                          fr4_t* prev_acc,
                          size_t polynomial_size,
                          size_t nloops,
                          const fr4_t (*z_powers)[DIV_BLOCK_SZ]) {
  const uint32_t WARP_SZ_1_HALF = 3 * WARP_SZ / 2;

  extern __shared__ fr4_t shared_memory[];
  fr4_t* exchange = &shared_memory[0];
  fr4_t* shared_z_powers = &shared_memory[DIV_BLOCK_SZ / WARP_SZ];

  uint32_t nthreads = gridDim.x * blockDim.x;
  uint32_t tid = threadIdx.x + blockIdx.x * blockDim.x;

  uint32_t wid = threadIdx.x / WARP_SZ;
  uint32_t lane = threadIdx.x % WARP_SZ;

  uint32_t sm_ceil = round_to_next_power_of_2(gridDim.x);
  uint32_t nwarps_red = sm_ceil < WARP_SZ ? sm_ceil : WARP_SZ;
  uint32_t nwarps_sm = sm_ceil < WARP_SZ ? 1 : sm_ceil / WARP_SZ;

  uint32_t shared_powers_size = WARP_SZ_1_HALF + nwarps_red + nwarps_sm / 2;

  fr4_t val, sval, tval, rval;

  size_t off = polynomial_size + tid;

  bool participate = off >= nthreads;

  if (threadIdx.x < shared_powers_size) {
    uint32_t idx;
    if (threadIdx.x < WARP_SZ)
      idx = threadIdx.x + 1;
    else if (threadIdx.x < WARP_SZ_1_HALF)
      idx = (threadIdx.x - WARP_SZ + 1) * WARP_SZ;
    else if (threadIdx.x < WARP_SZ_1_HALF + nwarps_red)
      idx = threadIdx.x - WARP_SZ - WARP_SZ / 2 + 1;
    else
      idx = (threadIdx.x - WARP_SZ - WARP_SZ / 2 - nwarps_red + 1) * nwarps_red;
    shared_z_powers[threadIdx.x] = z_powers[threadIdx.x >= WARP_SZ_1_HALF][idx];
  }

  __syncthreads();

  for (size_t loop = 0; loop < nloops; loop++) {
    off -= nthreads;

    if (participate)
      val = polynomial[off];

    warp_sum_and_reduce(val, WARP_SZ / 2, shared_z_powers);

    if (lane == 0)
      exchange[wid] = val;

    __syncthreads();

    sval = 0;
    if (threadIdx.x < WARP_SZ - 1)
      sval = exchange[(threadIdx.x + 1) % WARP_SZ];

    warp_sum_and_reduce(sval, WARP_SZ / 2, shared_z_powers + WARP_SZ);

    if (threadIdx.x < WARP_SZ)
      exchange[threadIdx.x] = sval;

    __syncthreads();

    sval = exchange[wid];
    rval = shared_z_powers[WARP_SZ - lane - 1];
    sval *= rval;
    val += sval;

    if (threadIdx.x == 0)
      acc[blockIdx.x] = val;

    cooperative_groups::this_grid().sync();

    sval = 0;
    if (tid < gridDim.x - 1)
      sval = acc[tid + 1];

    warp_sum_and_reduce(sval, nwarps_red / 2, shared_z_powers + WARP_SZ_1_HALF);

    if ((tid < sm_ceil) && (lane == 0))
      exchange[wid] = sval;

    __syncthreads();

    tval = 0;
    if (tid < nwarps_sm - 1)
      tval = exchange[(threadIdx.x + 1) % nwarps_sm];

    warp_sum_and_reduce(tval, nwarps_sm / 2, shared_z_powers + WARP_SZ_1_HALF + nwarps_red);

    if (tid < nwarps_sm)
      exchange[threadIdx.x] = tval;

    __syncthreads();

    tval = 0;
    if (tid < sm_ceil)
      tval = exchange[wid];
    rval = shared_z_powers[3 * WARP_SZ / 2 + nwarps_red - lane - 1];
    tval *= rval;
    sval += tval;

    __syncthreads();

    if (tid < gridDim.x)
      acc[tid] = sval;

    cooperative_groups::this_grid().sync();

    sval = acc[blockIdx.x];
    sval *= get_windowed_power(z_powers, blockDim.x - threadIdx.x);
    val += sval;
    sval = prev_acc[(loop - 1) & 1];
    sval *= get_windowed_power(z_powers, nthreads - tid);
    val += sval;

    if (blockIdx.x == 0 && threadIdx.x == 0)
      prev_acc[loop & 1] = val;

    if (participate)
      polynomial[off] = val;

    participate = off >= nthreads;
  }
}
