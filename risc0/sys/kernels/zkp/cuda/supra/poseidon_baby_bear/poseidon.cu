#include "poseidon_constants.cuh"

#define CELLS 24
#define FULL_ROUNDS 8
#define HALF_FULL_ROUNDS 4
#define PARTIAL_ROUNDS 21
#define RATE 16
#define OUT 8

extern __shared__ fr_t _scratchpad[];

class scratchpad {
public:
  __device__ __forceinline__ fr_t& operator[](uint32_t i) const {
    return _scratchpad[32 * CELLS * (threadIdx.x / 32) + i * 32 + threadIdx.x % 32];
  }
};

__device__ __forceinline__ void add_round_constants_cells(fr_t cells[CELLS],
                                                          const fr_t round_constants[CELLS]) {
#pragma unroll
  for (uint32_t i = 0; i < CELLS; i++) {
    cells[i] += round_constants[i];
  }
}

__device__ __forceinline__ void pow7_cells(fr_t cells[CELLS]) {
#pragma unroll
  for (uint32_t i = 0; i < CELLS; i++) {
#ifdef __CUDA_ARCH__
    cells[i] ^= 7;
#endif
  }
}

__device__ __forceinline__ void matrix_mul(fr_t cells[CELLS],
                                           const fr_t matrix[CELLS][CELLS],
                                           uint32_t iters = CELLS,
                                           uint32_t iter_start = 0) {
  scratchpad sc;

#pragma unroll 1
  for (uint32_t i = iter_start; i < iter_start + iters; i++) {
#ifdef __CUDA_ARCH__
    fr_t sum = fr_t::dot_product<CELLS>(matrix[i], cells);

    sc[i] = sum;
#endif
  }

#pragma unroll
  for (uint32_t i = 0; i < CELLS; i++) {
    cells[i] = sc[i];
  }
}

__device__ __forceinline__ void full_round(fr_t cells[CELLS],
                                           const fr_t round_constants[CELLS],
                                           const fr_t matrix[CELLS][CELLS],
                                           uint32_t matrix_mul_iters = CELLS,
                                           uint32_t matrix_mul_iter_start = 0) {
  add_round_constants_cells(cells, round_constants);
  pow7_cells(cells);
  matrix_mul(cells, matrix, matrix_mul_iters, matrix_mul_iter_start);
}

__device__ __forceinline__ void
partial_round(fr_t cells[CELLS], fr_t round_constant, const fr_t* sparse_matrix) {
#ifdef __CUDA_ARCH__
  cells[0] ^= 7;
#endif
  fr_t p0 = cells[0] + round_constant;
  fr_t s0;
#ifdef __CUDA_ARCH__
  s0 = fr_t::dot_product<CELLS>(p0, fr_t(m00), &sparse_matrix[0], cells + 1);
#endif

#pragma unroll
  for (uint32_t j = 1; j < CELLS; j++) {
    cells[j] += p0 * sparse_matrix[CELLS - 1 + j - 1];
  }
  cells[0] = s0;
}

__device__ __forceinline__ void poseidon_hash(fr_t cells[CELLS],
                                              uint32_t final_matrix_mul_iters,
                                              uint32_t final_matrix_mul_iter_start) {
  const fr_t(*round_constants) = (decltype(round_constants))poseidon_rc_dev;
  const fr_t(*mds_matrix)[CELLS] = (decltype(mds_matrix))poseidon_mds_dev;
  const fr_t(*pre_sparse_matrix)[CELLS] = (decltype(pre_sparse_matrix))poseidon_ps_dev;
  const fr_t(*sparse_matrices)[2 * (CELLS - 1)] = (decltype(sparse_matrices))poseidon_sm_dev;

  uint32_t rc_counter = 0;

#pragma unroll 1
  for (uint32_t r = 0; r < HALF_FULL_ROUNDS; r++) {
    full_round(cells, &round_constants[rc_counter], r == 3 ? pre_sparse_matrix : mds_matrix);
    rc_counter += CELLS;
  }

  {
    add_round_constants_cells(cells, &round_constants[rc_counter]);
    rc_counter += CELLS;
  }

#pragma unroll 1
  for (uint32_t r = 0; r < PARTIAL_ROUNDS; r++) {
    partial_round(cells, round_constants[rc_counter], sparse_matrices[r]);
    rc_counter += 1;
  }

#pragma unroll 1
  for (uint32_t r = 0; r < HALF_FULL_ROUNDS; r++) {
    if (r == 3)
      full_round(cells,
                 &round_constants[rc_counter],
                 mds_matrix,
                 final_matrix_mul_iters,
                 final_matrix_mul_iter_start);
    else
      full_round(cells, &round_constants[rc_counter], mds_matrix);
    rc_counter += CELLS;
  }
}

__device__ __forceinline__ void poseidon_hash(uint32_t final_matrix_mul_iters,
                                              uint32_t final_matrix_mul_iter_start) {
  scratchpad sc;

  fr_t cells[CELLS];

  for (uint32_t i = 0; i < CELLS; i++) {
    cells[i] = sc[i];
  }

  poseidon_hash(cells, final_matrix_mul_iters, final_matrix_mul_iter_start);

  for (uint32_t i = 0; i < CELLS; i++) {
    sc[i] = cells[i];
  }
}

__launch_bounds__(256, 3) __global__ void _poseidon_fold(fr_t* out, const fr_t* in) {
  uint32_t tid = blockDim.x * blockIdx.x + threadIdx.x;

  fr_t cells[CELLS];

// set last OUT elements of CELLS to 0
#pragma unroll
  for (uint32_t i = RATE; i < CELLS; i++) {
    cells[i] = fr_t(0);
  }

  // load RATE elements into the start of CELLS
  const fr_t* in_off = in + tid * RATE;
#pragma unroll
  for (uint32_t i = 0; i < RATE; i++) {
    cells[i] = in_off[i];
  }

  poseidon_hash(cells, OUT, 0);

  // return first OUT elements of CELLS as output
  fr_t* inout_off = out + tid * OUT;
#pragma unroll
  for (uint32_t i = 0; i < OUT; i++) {
    inout_off[i] = cells[i];
  }
}

__launch_bounds__(256, 3) __global__
    void _poseidon_rows(fr_t* out, const fr_t* matrix, uint32_t count, uint32_t col_size) {
  uint32_t tid = blockDim.x * blockIdx.x + threadIdx.x;

  scratchpad sc;

// set CELLS to 0 initially
#pragma unroll
  for (uint32_t i = 0; i < CELLS; i++) {
    sc[i] = fr_t(0);
  }

  uint32_t body_iterations = (col_size / RATE) * RATE;
  uint32_t leftovers = col_size - body_iterations;
  if (leftovers == 0) {
    body_iterations -= RATE;
    leftovers = RATE;
  }
  for (uint32_t i = 0; i < body_iterations; i += RATE) {
    for (uint32_t j = 0; j < RATE; j++) {
      sc[j] += matrix[(i + j) * count + tid];
    }
    poseidon_hash(CELLS, 0);
  }
  if (leftovers > 0 || count == 0) {
    for (uint32_t i = 0; i < leftovers; i++) {
      sc[i] += matrix[(body_iterations + i) * count + tid];
    }
    poseidon_hash(OUT, 0);
  }

  // return first OUT elements of CELLS as output
  fr_t* inout_off = out + tid * OUT;
#pragma unroll
  for (uint32_t i = 0; i < OUT; i++) {
    inout_off[i] = sc[i];
  }
}
