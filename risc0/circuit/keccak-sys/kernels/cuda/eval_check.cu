// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "eval_check.cuh"

#include "cuda.h"
#include "supra/fp.h"
#include <exception>
#include <iostream>

namespace risc0::circuit::keccak::cuda {

using MutableBuf = const Fp*;
using GlobalBuf = const Fp*;
using GlobalExtBuf = const FpExt*;
using ExtVal = FpExt;
using Val = Fp;
using Index = size_t;
using MixState = FpExt;

constexpr bool kDebug = false;
__constant__ FpExt poly_mix[kNumPolyMixPows];

constexpr size_t kInvRate = 4;

struct EncodedProg {
  const uint32_t* __restrict__ curPos = nullptr;

  __device__ __inline__ uint32_t decode() { return *curPos++; }
};

template <typename T> T tempLoad(Fp* buf, size_t offset);

template <> __device__ __inline__ Fp tempLoad<Fp>(Fp* buf, size_t offset) {
  return buf[offset];
}

template <> __device__ __inline__ FpExt tempLoad<FpExt>(Fp* buf, size_t offset) {
  return FpExt(buf[offset], buf[offset + 1], buf[offset + 2], buf[offset + 3]);
}

template <typename T> __device__ __inline__ void tempStore(Fp* buf, size_t offset, T val);

template <> __device__ __inline__ void tempStore<Fp>(Fp* buf, size_t offset, Fp val) {
  buf[offset] = val;
}
template <> __device__ __inline__ void tempStore<FpExt>(Fp* buf, size_t offset, FpExt val) {
  buf[offset] = val[0];
  buf[offset + 1] = val[1];
  buf[offset + 2] = val[2];
  buf[offset + 3] = val[3];
}

template <typename ConcreteType> struct EncodedProgBase : public EncodedProg {};

__device__ __inline__ constexpr size_t getBackOrZero() { return 0; }
__device__ __inline__ constexpr size_t getBackOrZero(size_t back) { return back; }

#define zllGet(BUF, OFFSET, BACK...) ((BUF)[(OFFSET) * steps + ((cycle - kInvRate * (getBackOrZero(BACK))) & mask)]);
#define zllGetGlobal(BUF, OFFSET) ((BUF)[(OFFSET)])
#define debugIn(X) (X)
#define debugOut(X)                                                                                \
  do {                                                                                             \
  } while (0)

__device__ __inline__ Fp zllConst(int a) {
  return Fp(a);
}

__device__ __inline__ FpExt zllConst(int a, int b, int c, int d) {
  return FpExt(a, b, c, d);
}

__device__ __inline__ FpExt trivialConstraint() {
  return FpExt(0, 0, 0, 0);
}

__device__ __inline__ FpExt zllAndEqz(FpExt inMix, Fp val, size_t mixPowIndex) {
  return inMix + val * poly_mix[mixPowIndex];
}

__device__ __inline__ FpExt zllAndEqz(FpExt inMix, FpExt val, size_t mixPowIndex) {
  return inMix + val * poly_mix[mixPowIndex];
}

__device__ __inline__ FpExt zllAndCond(FpExt inMix, Fp cond, FpExt innerMix, size_t mixPowIndex) {
  return inMix + cond * innerMix * poly_mix[mixPowIndex];
}

__device__ __inline__ FpExt
zllAndCond(FpExt inMix, FpExt cond, FpExt innerMix, size_t mixPowIndex) {
  return inMix + cond * innerMix * poly_mix[mixPowIndex];
}

#include "eval_check_bc.cu.inc"


__global__ void
__launch_bounds__(256, 6)
eval_check(Fp* check,
                           const Fp* ctrl,
                           const Fp* data,
                           const Fp* accum,
                           const Fp* mix,
                           const Fp* out,
                           const Fp rou,
                           uint32_t po2,
                           uint32_t domain) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= domain)
    return;
  FpExt tot = execByteCode<Keccak>(cycle, domain, data, out, poly_mix);
  Fp x = pow(rou, cycle);
  Fp y = pow(Fp(3) * x, 1 << po2);
  FpExt ret = tot * inv(y - Fp(1));
  check[domain * 0 + cycle] = ret[0];
  check[domain * 1 + cycle] = ret[1];
  check[domain * 2 + cycle] = ret[2];
  check[domain * 3 + cycle] = ret[3];
}

} // namespace risc0::circuit::keccak::cuda

extern "C" {

using namespace risc0::circuit::keccak::cuda;

const char* risc0_circuit_keccak_cuda_eval_check(Fp* check,
                                                 const Fp* ctrl,
                                                 const Fp* data,
                                                 const Fp* accum,
                                                 const Fp* mix,
                                                 const Fp* out,
                                                 const Fp& rou,
                                                 uint32_t po2,
                                                 uint32_t domain,
                                                 const FpExt* poly_mix_pows) {
  try {
    CUDA_OK(cudaDeviceSynchronize());
    CudaStream stream;
    auto cfg = getSimpleConfig(domain);
    cudaMemcpyToSymbol(poly_mix, poly_mix_pows, sizeof(poly_mix));
    eval_check<<<cfg.grid, cfg.block, 0, stream>>>(
        check, ctrl, data, accum, mix, out, rou, po2, domain);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

} // extern "C"
