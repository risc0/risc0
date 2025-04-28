#include "poseidon254_constants.cuh"

template <int N, typename fr_t>
__device__
void add_bb31_digit(fr_t& val, uint32_t digit)
{
  static_assert(N < (sizeof(fr_t) / sizeof(uint32_t)));

  if (N == 0) {
    val[0] = digit;
    return;
  }

  union { uint32_t u[2]; uint64_t ul; } temp[N ? N : 1];
  const uint64_t mod = 0x78000001;

  for (int i = 0; i < N; i++)
    temp[i].ul = val[i] * mod;

  asm("add.cc.u32      %0, %1, %2;" : "=r"(val[0]) : "r"(temp[0].u[0]), "r"(digit));
  for (int i = 1; i < N; i++)
    asm("addc.cc.u32 %0, %1, %2;" : "=r"(val[i]) : "r"(temp[i].u[0]), "r"(temp[i-1].u[1]));
  asm("addc.u32        %0, %1, 0;"  : "=r"(val[N]) : "r"(temp[N-1].u[1]));
}

template<typename fr_t>
__device__ __noinline__
fr_t bb31_to_mont_t(fr_t in)
{
  static_assert(sizeof(fr_t) == 32);
  fr_t out;

  add_bb31_digit<0>(out, in[7]);
  add_bb31_digit<1>(out, in[6]);
  add_bb31_digit<2>(out, in[5]);
  add_bb31_digit<3>(out, in[4]);
  add_bb31_digit<4>(out, in[3]);
  add_bb31_digit<5>(out, in[2]);
  add_bb31_digit<6>(out, in[1]);
  add_bb31_digit<7>(out, in[0]);

  out.to();
  return out;
}

template<typename fr_t>
__device__ __noinline__
fr_t to_montgomery(fr_t fr)
{ fr.to(); return fr; }

template<typename fr_t>
__device__ __noinline__
static fr_t sbox(fr_t fr)
{ fr ^= 8; return fr; }

template<typename fr_t>
__device__ __forceinline__
static void add_round_constants_state(fr_t state[CELLS_254],
                                      const fr_t round_constants[CELLS_254])
{
  #pragma unroll
  for (uint32_t i = 0; i < CELLS_254; i++) {
    fr_t rc = round_constants[i];
    state[i] += rc;
  }
}

template<typename fr_t>
__device__ __forceinline__
static void full_round(fr_t state[CELLS_254], const fr_t round_constants[CELLS_254],
                       const fr_t matrix[CELLS_254][CELLS_254],
                       uint32_t iters)
{
  #pragma unroll
  for (uint32_t i = 0; i < CELLS_254; i++) {
    fr_t rc = round_constants[i];
    state[i] = sbox(state[i] + rc);
  }

  fr_t out_state[CELLS_254];

  #pragma unroll 1
  for (uint32_t i = 0; i < iters; i++) {
    out_state[CELLS_254 - 1] = fr_t::dot_product(state, matrix[i], CELLS_254);

    #pragma unroll
    for (uint32_t j = 0; j < (CELLS_254 - 1); j++)
      out_state[j] = fr_t::csel(out_state[CELLS_254 - 1], out_state[j], i == j);
  }

  #pragma unroll
  for (uint32_t i = 0; i < CELLS_254; i++)
    state[i] = fr_t::csel(out_state[i], state[i], i < iters);
}

template<typename fr_t>
__device__ __forceinline__
static void partial_round(fr_t state[CELLS_254], fr_t round_constant,
                          const fr_t sparse_matrix[2 * (CELLS_254 - 1)],
                          fr_t m_0_0)
{
  state[0] = sbox(state[0]);

  fr_t p0 = state[0] + round_constant;
  state[0] = p0 * m_0_0;

  state[0] += fr_t::dot_product(state + 1, sparse_matrix, CELLS_254 - 1);

  #pragma unroll
  for (uint32_t j = 1; j < CELLS_254; j++) {
    fr_t sm_val = sparse_matrix[(CELLS_254 - 1) + (j - 1)];
    state[j] += p0 * sm_val;
  }
}

template<typename fr_t>
__device__ __forceinline__
static void poseidon_mix(fr_t state[CELLS_254], const poseidon254_blob& s_const)
{
  const fr_t* s_round_constants = s_const.round_constants;

  #pragma unroll 1
  for (uint32_t fround = 0; fround < ROUNDS_FULL_254; fround++)
  {
    const auto matrix = (fround == ROUNDS_HALF_FULL_254 - 1) ? s_const.pre_sparse_matrix : s_const.mds;

    uint32_t iters = fround < (ROUNDS_FULL_254 - 1) ? CELLS_254 : CELLS_OUT_254;

    full_round(state, s_round_constants, matrix, iters);
    s_round_constants += CELLS_254;

    if (fround == ROUNDS_HALF_FULL_254 - 1) {
      add_round_constants_state(state, s_round_constants);
      s_round_constants += CELLS_254;

      #pragma unroll 1
      for (uint32_t pround = 0; pround < ROUNDS_PARTIAL_254; pround++)
      {
        bool last_partial = (pround == ROUNDS_PARTIAL_254 - 1);
        fr_t rc = czero(s_round_constants[0], last_partial);
        s_round_constants += !last_partial;
        partial_round(state, rc, s_const.sparse_matrices[pround], s_const.m_0_0[0]);
      }
    }
  }
}

template<typename bn254_t>
__global__ __launch_bounds__(512)
void _poseidon254_rows(bn254_t out[/*row_size*/], const fr_t matrix[/*row_size * col_size*/],
                       size_t row_size, uint32_t col_size)
{
  size_t tid0 = (size_t)blockDim.x * blockIdx.x + threadIdx.x;

  static __shared__ uint4 s_const[sizeof(poseidon254_blob) / sizeof(uint4)];

  for (uint32_t i = threadIdx.x; i < sizeof(poseidon254_blob) / sizeof(uint4); i += blockDim.x) {
    auto val = poseidon254_constants.reserved[i];
    s_const[i] = val;
  }

  __syncthreads();

  const poseidon254_blob& s_const_blob = *reinterpret_cast<const poseidon254_blob*>(s_const);

  for (size_t tid = tid0; tid < row_size; tid += (size_t)gridDim.x * blockDim.x) {
    bn254_t state[CELLS_254]; state[0].zero();

    uint32_t i = 0;

    do {
      #pragma unroll
      for (uint32_t j = CELLS_OUT_254; j < CELLS_254; j++) {
        #pragma unroll
        for (uint32_t z = 0; z < state[j].len(); z++, i++) {
          fr_t val = (i < col_size) ? matrix[i * row_size + tid] : fr_t{0};
          state[j][z] = val;
        }
      }

      #pragma unroll
      for (uint32_t j = CELLS_OUT_254; j < CELLS_254; j++) {
        state[j] = bb31_to_mont_t(state[j]);
      }

      poseidon_mix(state, s_const_blob);

    } while (i < col_size);

    state[0].from();
    out[tid] = state[0];
  }
}

template<typename bn254_t>
__global__ __launch_bounds__(512)
void _poseidon254_fold(bn254_t out[/*out_size*/], const bn254_t in[/*2 * out_size*/],
                       size_t out_size)
{
  size_t tid = (size_t)blockDim.x * blockIdx.x + threadIdx.x;

  static __shared__ uint4 s_const[sizeof(poseidon254_blob) / sizeof(uint4)];

  for (uint32_t i = threadIdx.x; i < sizeof(poseidon254_blob) / sizeof(uint4); i += blockDim.x) {
    auto val = poseidon254_constants.reserved[i];
    s_const[i] = val;
  }

  __syncthreads();

  const poseidon254_blob& s_const_blob = *reinterpret_cast<const poseidon254_blob*>(s_const);

  for (size_t i = tid; i < out_size; i += (size_t)gridDim.x * blockDim.x) {
    bn254_t state[CELLS_254]; state[0].zero();

    #pragma unroll
    for (uint32_t j = CELLS_OUT_254; j < CELLS_254; j++) {
      state[j] = in[(j - CELLS_OUT_254) + (i * CELLS_RATE_254)];
    }

    #pragma unroll
    for (uint32_t j = CELLS_OUT_254; j < CELLS_254; j++) {
      state[j] = to_montgomery(state[j]);
    }

    poseidon_mix(state, s_const_blob);

    state[0].from();
    out[i] = state[0];
  }
}
