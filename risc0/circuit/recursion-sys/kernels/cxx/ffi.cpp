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

#include "ffi.h"
#include "context.h"
#include "fp.h"
#include "fpext.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-braces"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"
#endif

#include "vendor/nvtx3/nvtx3.hpp"
#include "vendor/poolstl.hpp"

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#include <algorithm>
#include <exception>
#include <numeric>
#include <stdio.h>
#include <string.h>

using namespace risc0;
using namespace risc0::circuit::recursion;

constexpr size_t kStepModeParallel = 0;
constexpr size_t kStepModeSeqForward = 1;
constexpr size_t kStepModeSeqReverse = 2;

namespace risc0::circuit::recursion {

MachineContext::MachineContext(ExecBuffers* buffers, PreflightTrace* trace, uint32_t steps)
    : buffers(buffers)
    , trace(trace)
    , steps(steps)
    , womRows(trace->numCycles * kMaxWomRowsPerCycle,
              WomArgumentRow{kInvalidPattern, FpExt::invalid()})
    , womIndex(trace->numCycles) {}

void MachineContext::parStepExec(uint32_t cycle) {
  if (cycle == 0 || isParSafeExec(cycle)) {
    // printf("step_exec(%u)\n", cycle);
    step_exec(this, steps, cycle++, args().data());
    while (cycle < trace->numCycles && !isParSafeExec(cycle)) {
      // printf("step_exec(%u)\n", cycle);
      step_exec(this, steps, cycle++, args().data());
    }
  }
}

void MachineContext::doStepExec(uint32_t mode) {
  nvtx3::scoped_range range("stepExec");
  switch (mode) {
  case kStepModeParallel: {
    auto begin = poolstl::iota_iter<uint32_t>(0);
    auto end = poolstl::iota_iter<uint32_t>(trace->numCycles);
    std::for_each(poolstl::par, begin, end, [&](uint32_t cycle) { parStepExec(cycle); });
  } break;
  case kStepModeSeqForward: {
    for (size_t i = 0; i < trace->numCycles; i++) {
      // printf("step_exec(%zu)\n", i);
      step_exec(this, steps, i, args().data());
    }
  } break;
  case kStepModeSeqReverse: {
    for (size_t i = 0; i < trace->numCycles; i++) {
      parStepExec(trace->numCycles - i - 1);
    }
  } break;
  }
}

void MachineContext::doStepVerifyWom(uint32_t mode) {
  nvtx3::scoped_range range("stepVerifyWom");
  switch (mode) {
  case kStepModeParallel: {
    auto begin = poolstl::iota_iter<uint32_t>(0);
    auto end = poolstl::iota_iter<uint32_t>(trace->numCycles);
    std::for_each(poolstl::par, begin, end, [&](uint32_t cycle) {
      step_verify_mem(this, steps, cycle, args().data());
    });
  } break;
  case kStepModeSeqForward: {
    for (size_t i = 0; i < trace->numCycles; i++) {
      // printf("step_verify_mem(%zu)\n", i);
      step_verify_mem(this, steps, i, args().data());
    }
  } break;
  case kStepModeSeqReverse: {
    for (size_t i = 0; i < trace->numCycles; i++) {
      size_t cycle = trace->numCycles - i - 1;
      // printf("step_verify_mem(%zu)\n", cycle);
      step_verify_mem(this, steps, cycle, args().data());
    }
  } break;
  }
}

void MachineContext::verifyWom(uint32_t mode) {
  nvtx3::scoped_range range("verifyWom");

  {
    nvtx3::scoped_range range("sortWom");
    std::sort(poolstl::par, womRows.begin(), womRows.end());
  }

  {
    nvtx3::scoped_range range("scan");
    std::exclusive_scan(poolstl::par, womIndex.begin(), womIndex.end(), womIndex.begin(), 0);
  }

  injectWomBacks();
  doStepVerifyWom(mode);
}

void MachineContext::injectWomBacks() {
  nvtx3::scoped_range range("injectWomBacks");
  auto begin = poolstl::iota_iter<uint32_t>(1);
  auto end = poolstl::iota_iter<uint32_t>(trace->numCycles);
  Fp* data = buffers->data;
  std::for_each(poolstl::par, begin, end, [&](uint32_t cycle) {
    uint32_t idx = womIndex[cycle];
    if (idx) {
      const WomArgumentRow& prev = womRows[idx - 1];
      data[0 * steps + cycle - 1] = prev.addr;
      data[1 * steps + cycle - 1] = prev.value.elems[0];
      data[2 * steps + cycle - 1] = prev.value.elems[1];
      data[3 * steps + cycle - 1] = prev.value.elems[2];
      data[4 * steps + cycle - 1] = prev.value.elems[3];
    } else {
      data[0 * steps + cycle - 1] = 0;
      data[1 * steps + cycle - 1] = 0;
      data[2 * steps + cycle - 1] = 0;
      data[3 * steps + cycle - 1] = 0;
      data[4 * steps + cycle - 1] = 0;
    }
  });
}

AccumContext::AccumContext(AccumBuffers* buffers, uint32_t steps, uint32_t cycles)
    : buffers(buffers), steps(steps), cycles(cycles), accum(steps, FpExt(1)) {}

void AccumContext::computeAccum() {
  nvtx3::scoped_range range("computeAccum");
  auto begin = poolstl::iota_iter<uint32_t>(0);
  auto end = poolstl::iota_iter<uint32_t>(steps);
  std::for_each(poolstl::par, begin, end, [&](uint32_t cycle) {
    // printf("step_compute_accum(%zu)\n", cycle);
    step_compute_accum(this, cycles, cycle, args().data());
  });
}

void AccumContext::calcPrefixProducts() {
  nvtx3::scoped_range range("calcPrefixProducts");
  std::inclusive_scan(
      accum.begin(), accum.end(), accum.begin(), std::multiplies<FpExt>{}, FpExt(1));
}

void AccumContext::verifyAccum() {
  nvtx3::scoped_range range("verifyAccum");
  auto begin = poolstl::iota_iter<uint32_t>(0);
  auto end = poolstl::iota_iter<uint32_t>(steps);
  std::for_each(poolstl::par, begin, end, [&](uint32_t cycle) {
    // printf("step_verify_accum(%zu)\n", cycle);
    step_verify_accum(this, cycles, cycle, args().data());
  });
}

} // namespace risc0::circuit::recursion

extern "C" {

const char* risc0_circuit_recursion_cpu_witgen(uint32_t mode,
                                               ExecBuffers* buffers,
                                               PreflightTrace* trace,
                                               uint32_t steps) {
  try {
    MachineContext ctx(buffers, trace, steps);
    ctx.doStepExec(mode);
    ctx.verifyWom(mode);
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

const char*
risc0_circuit_recursion_cpu_accum(AccumBuffers* buffers, uint32_t steps, uint32_t cycles) {
  try {
    AccumContext ctx(buffers, steps, cycles);
    ctx.computeAccum();
    ctx.calcPrefixProducts();
    ctx.verifyAccum();
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

const char* risc0_circuit_recursion_cpu_eval_check(
    AccumBuffers* buffers, FpExt* poly_mix, Fp* check, Fp rou, uint32_t po2, uint32_t steps) {
  try {
    nvtx3::scoped_range range("evalCheck");
    std::array<Fp*, 5> args{
        buffers->ctrl,
        buffers->global,
        buffers->data,
        buffers->mix,
        buffers->accum,
    };
    auto begin = poolstl::iota_iter<uint32_t>(0);
    auto end = poolstl::iota_iter<uint32_t>(steps);
    std::for_each(poolstl::par, begin, end, [&](uint32_t cycle) {
      FpExt tot = poly_fp(cycle, steps, poly_mix, args.data());
      Fp x = pow(rou, cycle);
      Fp y = pow(Fp(3) * x, 1 << po2);
      FpExt ret = tot * inv(y - Fp(1));
      check[steps * 0 + cycle] = ret.elems[0];
      check[steps * 1 + cycle] = ret.elems[1];
      check[steps * 2 + cycle] = ret.elems[2];
      check[steps * 3 + cycle] = ret.elems[3];
    });
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

} // extern "C"
