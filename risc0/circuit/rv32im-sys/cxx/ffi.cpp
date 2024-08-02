// Copyright 2024 RISC Zero, Inc.
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

#include <array>
#include <cstdint>

using namespace risc0;
using namespace risc0::circuit::rv32im;

constexpr size_t kStepModeSeqParallel = 0;
constexpr size_t kStepModeSeqForward = 1;
constexpr size_t kStepModeSeqReverse = 2;

// constexpr size_t kVerifyMemBodyKind = 1;
constexpr size_t kVerifyMemHaltKind = 2;

namespace {

using CodeReg = size_t;
using OutReg = size_t;
using DataReg = size_t;
using MixReg = size_t;
using AccumReg = size_t;

#include "layout.cpp.inc"

} // namespace

void par_step_exec(MachineContext* ctx,
                   uint32_t steps,
                   uint32_t cycle,
                   uint32_t count,
                   Fp* ctrl,
                   Fp* io,
                   Fp* data) {
  std::array<Fp*, 3> args{ctrl, io, data};
  if (cycle == 0 || ctx->isParSafeExec(cycle)) {
    // printf("step_exec(%u)\n", cycle);
    step_exec(ctx, steps, cycle++, args.data());
    while (cycle < count && !ctx->isParSafeExec(cycle)) {
      // printf("step_exec(%u)\n", cycle);
      step_exec(ctx, steps, cycle++, args.data());
    }
  }
}

void par_step_verify_mem(MachineContext* ctx,
                         uint32_t steps,
                         uint32_t cycle,
                         uint32_t count,
                         Fp* ctrl,
                         Fp* io,
                         Fp* data) {
  std::array<Fp*, 3> args{ctrl, io, data};
  if (cycle == 0 || ctx->isParSafeVerifyMem(cycle)) {
    // printf("step_verify_mem(%u)\n", cycle);
    step_verify_mem(ctx, steps, cycle++, args.data());
    while (cycle < count && !ctx->isParSafeVerifyMem(cycle)) {
      step_verify_mem(ctx, steps, cycle++, args.data());
    }
  }
}

void MachineContext::sortRam() {
  // printf("sortRam\n");
  nvtx3::scoped_range range("sortRam");
  {
    nvtx3::scoped_range range("sort");
    std::sort(poolstl::par, ramRows.begin(), ramRows.end());
  }

  {
    nvtx3::scoped_range range("dirty");
    uint32_t prevDirty = 0;
    for (size_t i = 0; i < ramRows.size(); i++) {
      RamArgumentRow& row = ramRows[i];
      switch (row.getMemOp()) {
      case 0: // pageIo
        row.dirty = 0;
        break;
      case 1: // read
        row.dirty = prevDirty;
        break;
      case 2: // write
        row.dirty = 1;
        break;
      }
      prevDirty = row.dirty;
    }
  }

  {
    nvtx3::scoped_range range("scan");
    std::exclusive_scan(poolstl::par, ramIndex.begin(), ramIndex.end(), ramIndex.begin(), 0);
  }
}

void inject_backs_ram(MachineContext* ctx, size_t steps, size_t cycle, Fp* data) {
  uint8_t kind = ctx->isParSafeVerifyMem(cycle);
  if (cycle > 2 && kind) {
    size_t idx = ctx->ramIndex[cycle];
    if (idx == 0) {
      throw std::runtime_error("inject_backs_ram: idx == 0");
    }

    const RamArgumentRow& back1 = ctx->ramRows[idx - 1];
    constexpr auto header = kLayout.mux.body.header;
    constexpr auto a = header.element;
    constexpr auto v = header.verifier;
    data[a.addr * steps + cycle - 1] = back1.addr;                 // a->addr
    data[a.cycle * steps + cycle - 1] = back1.getMemCycle();       // a->cycle
    data[a.memOp * steps + cycle - 1] = back1.getMemOp();          // a->memOp
    data[a.data[0] * steps + cycle - 1] = back1.word & 0xff;       // a->data[0]
    data[a.data[1] * steps + cycle - 1] = back1.word >> 8 & 0xff;  // a->data[1]
    data[a.data[2] * steps + cycle - 1] = back1.word >> 16 & 0xff; // a->data[2]
    data[a.data[3] * steps + cycle - 1] = back1.word >> 24 & 0xff; // a->data[3]
    data[v.dirty * steps + cycle - 1] = back1.dirty;               // prevVerifier->dirty
    if (kind == kVerifyMemHaltKind) {
      const RamArgumentRow& back2 = ctx->ramRows[idx - 2];
      uint32_t isNewAddr = back2.addr != back1.addr;
      uint32_t cmp;
      if (isNewAddr) {
        cmp = back1.addr - back2.addr - 1;
      } else {
        cmp =
            back1.getMemCycle() * 3 + back1.getMemOp() - back2.getMemCycle() * 3 + back2.getMemOp();
      }
      uint32_t diff[3];
      for (size_t i = 0; i < 3; i++) {
        diff[i] = cmp & 0xff;
        cmp = cmp >> 8;
      }
      uint32_t extra = cmp;
      data[v.isNewAddr * steps + cycle - 1] = isNewAddr; // isNewAddr
      data[v.diff[0] * steps + cycle - 1] = diff[0];     // diff[0]
      data[v.diff[1] * steps + cycle - 1] = diff[1];     // diff[1]
      data[v.diff[2] * steps + cycle - 1] = diff[2];     // diff[2]
      data[v.extra * steps + cycle - 1] = extra;         // extra
    }
  }
}

void MachineContext::sortBytes() {
  // printf("sortBytes\n");
  nvtx3::scoped_range range("sortBytes");

  {
    nvtx3::scoped_range range("sort");
    std::sort(poolstl::par, pairs.begin(), pairs.end());
  }

  {
    nvtx3::scoped_range range("scan");
    std::exclusive_scan(poolstl::par, pairsIndex.begin(), pairsIndex.end(), pairsIndex.begin(), 0);
  }
}

void inject_backs_bytes(MachineContext* ctx, size_t steps, size_t cycle, Fp* data) {
  if (cycle == 0) {
    return;
  }

  uint32_t idx = ctx->pairsIndex[cycle];
  uint32_t writeCount = idx - ctx->pairsIndex[cycle - 1];
  // printf("inject> cycle: %u, writeCount: %lu\n", cycle, writeCount);
  if (writeCount) {
    uint32_t pair = ctx->pairs[idx - 1];
    // printf("inject> pair: %x\n", pair);
    data[0 * steps + cycle - 1] = pair >> 8 & 0xff;
    data[1 * steps + cycle - 1] = pair & 0xff;
  }
}

namespace risc0::circuit::rv32im {

MachineContext::MachineContext(PreflightTrace* trace, uint32_t steps)
    : trace(trace)
    , steps(steps)
    , ramRows(steps * kMaxRamRowsPerCycle,
              RamArgumentRow{kInvalidPattern, kInvalidPattern, kInvalidPattern, kInvalidPattern})
    , ramIndex(steps)
    , pairs(steps * kMaxBytePairsPerCycle, kInvalidPattern)
    , pairsIndex(steps) {}

AccumCell operator*(const AccumCell& lhs, const AccumCell& rhs) {
  return AccumCell{lhs.ram * rhs.ram, lhs.bytes * rhs.bytes};
}

void AccumContext::calcPrefixProducts() {
  // printf("calcPrefixProducts\n");
  std::inclusive_scan(cells.begin(),
                      cells.end(),
                      cells.begin(),
                      std::multiplies<AccumCell>{},
                      AccumCell{FpExt(1), FpExt(1)});
}

} // namespace risc0::circuit::rv32im

void do_step_exec(
    MachineContext* ctx, uint32_t mode, uint32_t last_cycle, Fp* ctrl, Fp* io, Fp* data) {
  // printf("step_exec\n");
  nvtx3::scoped_range range("step_exec");
  std::array<Fp*, 3> args{ctrl, io, data};
  switch (mode) {
  case kStepModeSeqParallel: {
    auto begin = poolstl::iota_iter<uint32_t>(0);
    auto end = poolstl::iota_iter<uint32_t>(last_cycle);
    std::for_each(poolstl::par, begin, end, [&](uint32_t cycle) {
      par_step_exec(ctx, ctx->steps, cycle, last_cycle, ctrl, io, data);
    });
  } break;
  case kStepModeSeqForward: {
    for (size_t i = 0; i < last_cycle; i++) {
      step_exec(ctx, ctx->steps, i, args.data());
    }
  } break;
  case kStepModeSeqReverse: {
    for (size_t i = 0; i < last_cycle; i++) {
      size_t cycle = last_cycle - i - 1;
      par_step_exec(ctx, ctx->steps, cycle, last_cycle, ctrl, io, data);
    }
  } break;
  }
}

extern "C" {

const char* risc0_circuit_rv32im_cpu_witgen(uint32_t mode,
                                            PreflightTrace* trace,
                                            uint32_t steps,
                                            uint32_t last_cycle,
                                            Fp* ctrl,
                                            Fp* io,
                                            Fp* data) {
  try {
    // printf("risc0_circuit_rv32im_cpu_witgen\n");
    MachineContext ctx(trace, steps);

    auto begin = []() { return poolstl::iota_iter<uint32_t>(0); };
    auto end = poolstl::iota_iter<uint32_t>(last_cycle);
    std::array<Fp*, 3> args{ctrl, io, data};

    do_step_exec(&ctx, mode, last_cycle, ctrl, io, data);

    {
      nvtx3::scoped_range range("verify_ram");
      ctx.sortRam();

      {
        // printf("inject_backs_ram\n");
        nvtx3::scoped_range range("inject_backs_ram");
        std::for_each(poolstl::par, begin(), end, [&](uint32_t cycle) {
          inject_backs_ram(&ctx, steps, cycle, data);
        });
      }

      {
        // printf("step_verify_mem\n");
        nvtx3::scoped_range range("step_verify_mem");
        std::for_each(poolstl::par, begin(), end, [&](uint32_t cycle) {
          par_step_verify_mem(&ctx, steps, cycle, last_cycle, ctrl, io, data);
        });
      }
    }

    {
      nvtx3::scoped_range range("verify_bytes");
      ctx.sortBytes();

      {
        // printf("inject_backs_bytes\n");
        nvtx3::scoped_range range("inject_backs_bytes");
        std::for_each(poolstl::par, begin(), end, [&](uint32_t cycle) {
          inject_backs_bytes(&ctx, steps, cycle, data);
        });
      }

      {

        // printf("step_verify_bytes\n");
        nvtx3::scoped_range range("step_verify_bytes");
        std::for_each(poolstl::par, begin(), end, [&](uint32_t cycle) {
          step_verify_bytes(&ctx, steps, cycle++, args.data());
        });
      }
    }
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

void risc0_circuit_rv32im_step_compute_accum(
    risc0_error* err, void* ctx, size_t steps, size_t cycle, Fp** args) {
  ffi_wrap<uint32_t>(err, 0, [&] {
    // printf("step_compute_accum(%p, %lu, %lu, %p)\n", ctx, steps, cycle, args);
    circuit::rv32im::step_compute_accum(ctx, steps, cycle, args);
    return 0;
  });
}

void risc0_circuit_rv32im_step_verify_accum(
    risc0_error* err, void* ctx, size_t steps, size_t cycle, Fp** args) {
  ffi_wrap<uint32_t>(err, 0, [&] {
    // printf("step_verify_accum(%p, %lu, %lu, %p)\n", ctx, steps, cycle, args);
    circuit::rv32im::step_verify_accum(ctx, steps, cycle, args);
    return 0;
  });
}

AccumContext* risc0_circuit_rv32im_accum_context_alloc(size_t steps) {
  AccumContext* ctx = new AccumContext;
  ctx->steps = steps;
  ctx->cells.resize(steps, AccumCell{FpExt(1), FpExt(1)});
  return ctx;
}

void risc0_circuit_rv32im_accum_context_free(AccumContext* ctx) {
  delete ctx;
}

void risc0_circuit_rv32im_calc_prefix_products(risc0_error* err, AccumContext* ctx) {
  ffi_wrap<uint32_t>(err, 0, [&] {
    ctx->calcPrefixProducts();
    return 0;
  });
}

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
#endif

FpExt risc0_circuit_rv32im_poly_fp(size_t cycle, size_t steps, FpExt* poly_mix, Fp** args) {
  return circuit::rv32im::poly_fp(cycle, steps, poly_mix, args);
}

const char* risc0_circuit_string_ptr(risc0_string* str) {
  return str->str.c_str();
}

void risc0_circuit_string_free(risc0_string* str) {
  delete str;
}

} // extern "C"
