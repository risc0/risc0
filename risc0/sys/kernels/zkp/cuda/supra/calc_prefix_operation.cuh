typedef bb31_4_t Fp4;

#include <cooperative_groups.h>

#ifndef WARP_SZ
#define WARP_SZ 32
#endif

template <typename fr_t> class Add {
public:
  __device__ __forceinline__ fr_t operator()(const fr_t& a, const fr_t& b) const { return a + b; }

  __device__ __forceinline__ fr_t identity() const { return 0; }
};

template <typename fr_t> class Multiply {
public:
  __device__ __forceinline__ fr_t operator()(const fr_t& a, const fr_t& b) const { return a * b; }

  __device__ __forceinline__ fr_t identity() const { return 1; }
};

template <typename fr_t> __device__ __forceinline__ fr_t shfl_up(const fr_t& src, uint32_t offset) {
  const auto len = sizeof(fr_t) / sizeof(uint32_t);
  union {
    fr_t val;
    uint32_t vec[len];
  } ret{src};

  for (auto i = 0; i < len; i++)
    ret.vec[i] = __shfl_up_sync(0xffffffff, ret.vec[i], offset);

  return ret.val;
}

template <typename fr_t> __device__ __forceinline__ fr_t shfl(const fr_t& src, uint32_t idx) {
  const auto len = sizeof(fr_t) / sizeof(uint32_t);
  union {
    fr_t val;
    uint32_t vec[len];
  } ret{src};

  for (auto i = 0; i < len; i++)
    ret.vec[i] = __shfl_sync(0xffffffff, ret.vec[i], idx);

  return ret.val;
}

template <typename fr_t, typename Operation>
__device__ __forceinline__ fr_t warp_prefix_op(fr_t val, Operation op, uint32_t limit = WARP_SZ) {
  uint32_t laneid = threadIdx.x % WARP_SZ;
  for (uint32_t offset = 1; offset < limit; offset *= 2) {
    fr_t other_val = shfl_up(val, offset);
    if (laneid >= offset)
      val = op(val, other_val);
  }
  return val;
}

template <typename Operation, typename fr_t, uint32_t CHUNK>
__global__ void calc_prefix_op_kernel(fr_t* src, size_t count) {
  assert(blockDim.x >= gridDim.x);

  uint32_t t_idx = blockDim.x * blockIdx.x + threadIdx.x;
  uint32_t warpid = threadIdx.x / WARP_SZ;
  uint32_t warp_count = blockDim.x / WARP_SZ;
  uint32_t laneid = threadIdx.x % WARP_SZ;
  uint32_t block_size = blockDim.x * CHUNK;
  uint32_t blob_size = block_size * gridDim.x;
  uint32_t num_warps_needed = (gridDim.x + WARP_SZ - 1) / WARP_SZ;
  fr_t chunk_reg[CHUNK];

  extern __shared__ fr_t partial_result[];

  Operation op;
  fr_t accumulator, grid_carry_over = op.identity();

#pragma unroll 1
  for (size_t blob_start = 0; blob_start < count; blob_start += blob_size) {
    size_t base = (t_idx / WARP_SZ) * WARP_SZ * CHUNK + blob_start;

    accumulator = grid_carry_over;

#pragma unroll
    for (uint32_t i = 0; i < CHUNK; i++) {
      size_t src_idx = base + WARP_SZ * i + laneid;
      if (src_idx < count)
        chunk_reg[i] = src[src_idx];
      else
        chunk_reg[i] = op.identity();
    }

#pragma unroll
    for (uint32_t i = 0; i < CHUNK; i++) {
      chunk_reg[i] = warp_prefix_op(chunk_reg[i], op);

      if (i > 0)
        chunk_reg[i] = op(chunk_reg[i], shfl(chunk_reg[i - 1], WARP_SZ - 1));
    }

    if (laneid == WARP_SZ - 1)
      partial_result[warpid] = chunk_reg[CHUNK - 1];

    __syncthreads();

    fr_t warp_carry_over = op.identity();

    if (laneid < warp_count && laneid > 0)
      warp_carry_over = partial_result[laneid - 1];

    warp_carry_over = warp_prefix_op(warp_carry_over, op, warp_count);
    warp_carry_over = shfl(warp_carry_over, warpid);

    chunk_reg[CHUNK - 1] = op(chunk_reg[CHUNK - 1], warp_carry_over);

    size_t global_offset = block_size * blockIdx.x + blob_start;
    if (threadIdx.x == blockDim.x - 1 && global_offset < count)
      src[global_offset] = chunk_reg[CHUNK - 1];

    cooperative_groups::this_grid().sync();
    __syncthreads();

    fr_t partial_sm = op.identity();

    if (gridDim.x <= WARP_SZ) {
      size_t warp_offset = block_size * laneid + blob_start;
      if (laneid < gridDim.x && warp_offset < count)
        partial_sm = src[warp_offset];

      partial_sm = warp_prefix_op(partial_sm, op, gridDim.x);
      grid_carry_over = op(grid_carry_over, shfl(partial_sm, gridDim.x - 1));

      if (blockIdx.x > 0)
        partial_sm = shfl(partial_sm, blockIdx.x - 1);
      else
        partial_sm = op.identity();

    } else {
      size_t local_offset = block_size * threadIdx.x + blob_start;
      if (threadIdx.x < gridDim.x && local_offset < count)
        partial_sm = src[local_offset];

      partial_sm = warp_prefix_op(partial_sm, op);

      // The last warp saves a value only when gridDim.x is divisible by WARP_SZ.
      // However, note that this value is later disregarded, which is why there is no need
      // to handle all divisibility cases. Therefore, we compare threadIdx.x to gridDim.x.
      if (laneid == WARP_SZ - 1 && threadIdx.x < gridDim.x)
        partial_result[warpid] = partial_sm;

      __syncthreads();

      fr_t partial_sm_carry_over = op.identity();
      if (laneid < num_warps_needed && laneid > 0)
        partial_sm_carry_over = partial_result[laneid - 1];

      partial_sm_carry_over = warp_prefix_op(partial_sm_carry_over, op, num_warps_needed);
      partial_sm_carry_over = shfl(partial_sm_carry_over, warpid);

      __syncthreads();

      if (threadIdx.x == blockIdx.x - 1 || threadIdx.x == gridDim.x - 1) {
        partial_sm = op(partial_sm, partial_sm_carry_over);
        partial_result[threadIdx.x == gridDim.x - 1] = partial_sm;
      }

      __syncthreads();

      partial_sm = op.identity();
      if (blockIdx.x > 0)
        partial_sm = partial_result[0];

      grid_carry_over = op(grid_carry_over, partial_result[1]);
    }

    cooperative_groups::this_grid().sync();
    __syncthreads();

    fr_t last_chunk_combined = op(partial_sm, accumulator);
    fr_t combined_op = op(warp_carry_over, last_chunk_combined);

#pragma unroll
    for (uint32_t i = 0; i < CHUNK; i++) {
      size_t dest_idx = base + WARP_SZ * i + laneid;
      if (i == CHUNK - 1)
        chunk_reg[i] = op(chunk_reg[i], last_chunk_combined);
      else
        chunk_reg[i] = op(chunk_reg[i], combined_op);
      if (dest_idx < count)
        src[dest_idx] = chunk_reg[i];
    }
  }
}
