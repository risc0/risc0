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

#include "extern.h"

#include "ffi.h"
#include "fp.h"
#include "fpext.h"
#include "vendor/nvtx3/nvtx3.hpp"
#include "vendor/poolstl.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

using namespace risc0;
using namespace risc0::circuit::rv32im;

namespace risc0::circuit::rv32im {

constexpr size_t kBabyBearExtSize = 4;
constexpr size_t kMaxRamRowsPerCycle = 5;
constexpr size_t kMaxBytePairsPerCycle = 21;

constexpr size_t kWordSize = sizeof(uint32_t);
constexpr size_t kBitWidth = 256;
constexpr size_t kByteWidth = kBitWidth / 8;

struct MemoryTransaction {
  uint32_t cycle;
  uint32_t addr;
  uint32_t data;
};

struct PreflightCycle {
  uint8_t major;
  uint8_t minor;
  uint8_t isSafeExec;
  uint8_t isSafeVerifyMem;
  uint32_t memIdx;
  uint32_t extraIdx;
};

struct PreflightTrace {
  PreflightCycle* cycles;
  MemoryTransaction* txns;
  uint32_t* extras;
  uint32_t numCycles;
  uint32_t numTxns;
  uint32_t numExtras;
  uint32_t isTrace;
};

struct RamArgumentRow {
  uint32_t addr;
  uint32_t cyclop;
  uint32_t word;
  uint32_t dirty;

  void setCyclop(uint32_t memCycle, uint32_t memOp) { cyclop = (memCycle << 2) | memOp; }
  uint32_t getMemCycle() const { return cyclop >> 2; }
  uint32_t getMemOp() const { return cyclop & 0b11; }
};

struct MachineContext {
  PreflightTrace* trace;
  uint32_t steps;

  std::vector<RamArgumentRow> ramRows;
  std::vector<RamArgumentRow> ramSorted;
  std::vector<uint32_t> ramIndex;

  std::array<std::atomic<uint32_t>, 256 * 256> bytePairs{0};
  std::vector<uint32_t> byteSorted;
  std::vector<uint32_t> byteWrites;
  std::vector<uint32_t> byteReads;

  void sortRam();
  void sortBytes();

  bool isParSafeExec(uint32_t cycle) { return trace->cycles[cycle].isSafeExec; }
  bool isParSafeVerifyMem(uint32_t cycle) { return trace->cycles[cycle].isSafeVerifyMem; }
};

struct AccumCell {
  FpExt ram;
  FpExt bytes;
};

struct AccumContext {
  size_t steps;
  std::vector<AccumCell> cells;

  void calcPrefixProducts();
};

void extern_halt(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  // no-op
}

void extern_trace(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args) {
  // no-op
}

Fp extern_getMajor(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  uint32_t major = trace->cycles[cycle].major;
  // printf("[%lu] getMajor: %u\n", cycle, major);
  return major;
}

Fp extern_getMinor(void* ctx, size_t cycle, const char* extra, std::array<Fp, 4> args) {
  // printf("getMinor\n");
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  return trace->cycles[cycle].minor;
}

std::array<Fp, 3>
extern_pageInfo(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  if (trace->isTrace) {
    printf("pageInfo\n");
  }
  size_t idx = trace->cycles[cycle].extraIdx;
  uint32_t isRead = trace->extras[idx + 0];
  uint32_t pageIdx = trace->extras[idx + 1];
  uint32_t isDone = trace->extras[idx + 2];
  return {Fp(isRead), Fp(pageIdx), Fp(isDone)};
}

void extern_ramWrite(void* ctx, size_t cycle, const char* extra, std::array<Fp, 6> args) {
  // no-op
}

std::array<Fp, 4>
extern_ramRead(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  uint32_t addr = args[0].asUInt32();
  size_t memIdx = trace->cycles[cycle].memIdx++;
  MemoryTransaction& txn = trace->txns[memIdx];
  if (trace->isTrace) {
    printf("ramRead(%lu, 0x%x): txn(%u, 0x%x)\n", cycle, addr, txn.cycle, txn.addr);
  }
  if (cycle != txn.cycle) {
    throw std::runtime_error("Mismatched memory txn cycle");
  }
  if (addr != txn.addr) {
    throw std::runtime_error("Mismatched memory txn addr");
  }
  return {
      Fp(txn.data & 0xff),
      Fp(txn.data >> 8 & 0xff),
      Fp(txn.data >> 16 & 0xff),
      Fp(txn.data >> 24 & 0xff),
  };
}

std::array<Fp, 4>
extern_syscallBody(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  size_t extraIdx = trace->cycles[cycle].extraIdx++;
  uint32_t word = trace->extras[extraIdx];
  return {
      Fp(word & 0xff),
      Fp(word >> 8 & 0xff),
      Fp(word >> 16 & 0xff),
      Fp(word >> 24 & 0xff),
  };
}

std::array<Fp, 8>
extern_syscallFini(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  size_t extraIdx = trace->cycles[cycle].extraIdx++;
  uint32_t a0 = trace->extras[extraIdx + 0];
  uint32_t a1 = trace->extras[extraIdx + 1];
  return {
      Fp(a0 & 0xff),
      Fp(a0 >> 8 & 0xff),
      Fp(a0 >> 16 & 0xff),
      Fp(a0 >> 24 & 0xff),
      Fp(a1 & 0xff),
      Fp(a1 >> 8 & 0xff),
      Fp(a1 >> 16 & 0xff),
      Fp(a1 >> 24 & 0xff),
  };
}

std::array<Fp, 8>
extern_divide(void* ctx, size_t cycle, const char* extra, std::array<Fp, 9> args) {
  uint32_t numer = args[0].asUInt32() |       //
                   args[1].asUInt32() << 8 |  //
                   args[2].asUInt32() << 16 | //
                   args[3].asUInt32() << 24;
  uint32_t denom = args[4].asUInt32() |       //
                   args[5].asUInt32() << 8 |  //
                   args[6].asUInt32() << 16 | //
                   args[7].asUInt32() << 24;
  uint32_t sign = args[8].asUInt32();
  uint32_t onesComp = (sign == 2);
  bool negNumer = sign && int32_t(numer) < 0;
  bool negDenom = sign == 1 && int32_t(denom) < 0;
  if (negNumer) {
    numer = -numer - onesComp;
  }
  if (negDenom) {
    denom = -denom - onesComp;
  }
  uint32_t quot;
  uint32_t rem;
  if (denom == 0) {
    quot = 0xffffffff;
    rem = numer;
  } else {
    quot = numer / denom;
    rem = numer % denom;
  }
  uint32_t quotNegOut = (negNumer ^ negDenom) - ((denom == 0) * negNumer);
  uint32_t remNegOut = negNumer;
  if (quotNegOut) {
    quot = -quot - onesComp;
  }
  if (remNegOut) {
    rem = -rem - onesComp;
  }
  return {
      Fp(quot & 0xff),
      Fp(quot >> 8 & 0xff),
      Fp(quot >> 16 & 0xff),
      Fp(quot >> 24 & 0xff),
      Fp(rem & 0xff),
      Fp(rem >> 8 & 0xff),
      Fp(rem >> 16 & 0xff),
      Fp(rem >> 24 & 0xff),
  };
}

std::array<Fp, 32>
extern_bigintQuotient(void* ctx, size_t cycle, const char* extra, std::array<Fp, 96> args) {
  // Division of two little-endian positive byte-limbed bigints. a = q * b + r.
  // Assumes a and b are both normalized with limbs in range [0, 255].
  // Throws if the quotient overflows kByteWidth. Overflows will not happen if the
  // numberator, a, is the result of a multiplication of two numbers less than the denomintor.
  // The BigInt arithmetic circuit does not accept larger quotients.
  // Returns only the quotient value q as the BigInt circuit does not use the r value.

  std::vector<uint64_t> a;
  std::transform(args.cbegin(), args.cbegin() + kByteWidth * 2, std::back_inserter(a), [](Fp x) {
    return x.asUInt32();
  });
  a.emplace_back(0);

  std::vector<uint64_t> b;
  std::transform(args.cbegin() + kByteWidth * 2, args.cend(), std::back_inserter(b), [](Fp x) {
    return x.asUInt32();
  });
  b.emplace_back(0);

  std::array<Fp, 32> q;

  // This is a variant of school-book multiplication.
  // Reference the Handbook of Elliptic and Hyper-elliptic Cryptography alg. 10.5.1

  // Determine n, the width of the denominator, and check for a denominator of zero.
  size_t n = kByteWidth;
  while (n > 0 && b.at(n - 1) == 0) {
    n--;
  }
  if (n == 0) {
    // Divide by zero is strictly undefined, but the BigInt multiplier circuit uses a modulus of
    // zero as a special case to support "checked multiply" of up to 256-bits.
    // Return zero here to facilitate this.
    return q;
  }
  if (n < 2) {
    // TODO(victor): Not an important case. But we should likely handle it anyway.
    throw std::runtime_error("bigint quotient: denominator must be at least 9 bits");
  }
  size_t m = a.size() - n - 1;

  // Shift (i.e. multiply by two) the inputs a and b until the leading bit of b is 1.
  // Note that shifting both numerator and denominator has no effect on the quotient.
  uint64_t dBits = 0;
  while ((b.at(n - 1) & (0x80 >> dBits)) == 0) {
    dBits++;
  }
  uint64_t carry = 0;
  for (size_t i = 0; i < n; i++) {
    uint64_t tmp = (b.at(i) << dBits) + carry;
    b.at(i) = tmp & 0xFF;
    carry = tmp >> 8;
  }
  if (carry != 0) {
    throw std::runtime_error("implementation error: final carry in input shift");
  }
  for (size_t i = 0; i < a.size() - 1; i++) {
    uint64_t tmp = (a.at(i) << dBits) + carry;
    a.at(i) = tmp & 0xFF;
    carry = tmp >> 8;
  }
  a.at(a.size() - 1) = carry;

  for (size_t i = m;; i--) {
    // Approximate how many multiples of b can be subtracted. May overestimate by up to one.
    uint64_t qApprox =
        std::min<uint64_t>(((a.at(i + n) << 8) + a.at(i + n - 1)) / b.at(n - 1), 255);
    while ((qApprox * ((b.at(n - 1) << 8) + b.at(n - 2))) >
           ((a.at(i + n) << 16) + (a.at(i + n - 1) << 8) + a.at(i + n - 2))) {
      qApprox--;
    }

    // Subtract multiples of the denominator from a.
    uint64_t borrow = 0;
    for (size_t j = 0; j <= n; j++) {
      uint64_t sub = qApprox * b.at(j) + borrow;
      if (a.at(i + j) < (sub & 0xFF)) {
        a.at(i + j) += 0x100 - (sub & 0xFF);
        borrow = (sub >> 8) + 1;
      } else {
        a.at(i + j) -= sub & 0xFF;
        borrow = sub >> 8;
      }
    }
    if (borrow > 0) {
      // Oops, went negative. Add back one multiple of b.
      qApprox--;
      uint64_t carry = 0;
      for (size_t j = 0; j <= n; j++) {
        uint64_t tmp = a.at(i + j) + b.at(j) + carry;
        a.at(i + j) = tmp & 0xFF;
        carry = tmp >> 8;
      }
      // Adding back one multiple of b should go from negative back to positive.
      if (borrow - carry != 0) {
        throw std::runtime_error("implementation error: underflow in bigint division");
      }
    }

    if (i < q.size()) {
      q.at(i) = qApprox;
    } else if (qApprox != 0) {
      throw std::runtime_error("bigint quotient: quotient exceeds allowed size");
    }

    if (i == 0) {
      break;
    }
  }
  return q;
}

void extern_log(void* ctx, size_t cycle, const char* extra, std::vector<Fp> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  if (!trace->isTrace) {
    return;
  }

  size_t argNum = 0;
  auto nextArg = [&]() {
    if (argNum >= args.size()) {
      return Fp(0);
    }
    return args[argNum++];
  };
  const char* p = extra;
  while (*p) {
    if (*p == '%') {
      p++;
      int len = 0;
      while (*p >= '0' && *p <= '9') {
        len *= 10;
        len += *p - '0';
        p++;
      }
      if (*p == '%') {
        std::cout << "%";
        p++;
      } else if (*p == 'x') {
        std::cout << std::hex << nextArg().asUInt32() << std::dec;
        p++;
      } else if (*p == 'u') {
        std::cout << nextArg().asUInt32();
        p++;
      } else if (*p == 'w') {
        uint64_t vals[sizeof(uint32_t)];
        uint32_t u32val = 0;
        for (auto& val : vals) {
          val = nextArg().asUInt32();
          u32val >>= 8;
          u32val |= val << 24;
        }
        std::cout << u32val; // hex
        p++;
      } else if (*p == 'e') {
        uint64_t vals[kBabyBearExtSize];
        for (auto& val : vals) {
          val = nextArg().asUInt32();
        }
        std::cout << "[";
        for (size_t i = 0; i < kBabyBearExtSize; ++i) {
          if (i) {
            std::cout << ", ";
          }
          std::cout << vals[i];
        }
        std::cout << "]";
        p++;
      }
    } else {
      std::cout << *p;
      p++;
    }
  }
  std::cout << "\n";
}

void extern_syscallInit(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args) {
  // no-op
}

void extern_plonkWrite_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 7> args) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t addr = args[0].asUInt32();
  uint32_t memCycle = args[1].asUInt32();
  uint32_t memOp = args[2].asUInt32();
  uint32_t word = args[3].asUInt32() |       //
                  args[4].asUInt32() << 8 |  //
                  args[5].asUInt32() << 16 | //
                  args[6].asUInt32() << 24;
  if (mctx->trace->isTrace) {
    printf("plonkWriteRam(0x%x, %u, %u, 0x%x)\n", addr, memCycle, memOp, word);
  }
  uint32_t idx = mctx->ramIndex[cycle]++;
  assert(idx < kMaxRamRowsPerCycle);
  RamArgumentRow& row = mctx->ramRows[cycle * kMaxRamRowsPerCycle + idx];
  row.addr = addr;
  row.setCyclop(memCycle, memOp);
  row.word = word;
  row.dirty = 0;
}

void MachineContext::sortRam() {
  printf("sortRam\n");
  {
    nvtx3::scoped_range range("prepare");
    for (size_t i = 0; i < steps; i++) {
      size_t count = ramIndex[i];
      for (size_t j = 0; j < count; j++) {
        ramSorted.push_back(ramRows[i * kMaxRamRowsPerCycle + j]);
      }
    }
  }

  {
    nvtx3::scoped_range range("sort");
    std::sort(poolstl::par, ramSorted.begin(), ramSorted.end(), [](const auto& a, const auto& b) {
      return std::tie(a.addr, a.cyclop, a.word, a.dirty) <
             std::tie(b.addr, b.cyclop, b.word, b.dirty);
    });
  }

  {
    nvtx3::scoped_range range("dirty");
    uint32_t prevDirty = 0;
    for (size_t i = 0; i < ramSorted.size(); i++) {
      RamArgumentRow& row = ramSorted[i];
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
    nvtx3::scoped_range range("update");
    std::exclusive_scan(ramIndex.begin(), ramIndex.end(), ramIndex.begin(), 0);
  }
}

void inject_backs_ram(void* ctx, size_t steps, size_t cycle, Fp* data) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  assert(cycle != 0);

  size_t idx = mctx->ramIndex[cycle];
  assert(idx != 0);

  const RamArgumentRow& row = mctx->ramSorted[idx - 1];
  data[89 * steps + cycle - 1] = Fp(row.addr);
  data[90 * steps + cycle - 1] = Fp(row.getMemCycle());     // a->cycle
  data[91 * steps + cycle - 1] = Fp(row.getMemOp());        // a->memOp
  data[92 * steps + cycle - 1] = Fp(row.word & 0xff);       // a->data[0]
  data[93 * steps + cycle - 1] = Fp(row.word >> 8 & 0xff);  // a->data[1]
  data[94 * steps + cycle - 1] = Fp(row.word >> 16 & 0xff); // a->data[2]
  data[95 * steps + cycle - 1] = Fp(row.word >> 24 & 0xff); // a->data[3]
  data[97 * steps + cycle - 1] = Fp(row.dirty);             // prevVerifier->dirty

  // RamPass
  // data.set(96 * steps + cycle - 1, 0u32.into()); // isNewAddr
  // data.set(97 * steps + cycle - 1, 0u32.into()); // dirty
  // data.set(3 * steps + cycle - 1, 0u32.into()); // diff[0]
  // data.set(4 * steps + cycle - 1, 0u32.into()); // diff[1]
  // data.set(5 * steps + cycle - 1, 0u32.into()); // diff[2]
  // data.set(69 * steps + cycle - 1, 0u32.into()); // extra
}

std::array<Fp, 7>
extern_plonkRead_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t idx = mctx->ramIndex[cycle]++;
  const RamArgumentRow& row = mctx->ramSorted[idx];
  return {
      Fp(row.addr),
      Fp(row.getMemCycle()),
      Fp(row.getMemOp()),
      Fp(row.word & 0xff),
      Fp(row.word >> 8 & 0xff),
      Fp(row.word >> 16 & 0xff),
      Fp(row.word >> 24 & 0xff),
  };
}

void extern_plonkWrite_bytes(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t pair = args[0].asUInt32() << 8 | args[1].asUInt32();
  mctx->bytePairs[pair]++;
  mctx->byteWrites[cycle]++;
}

void MachineContext::sortBytes() {
  printf("sortBytes\n");
  size_t pos = 0;
  auto next = [&]() {
    while (!bytePairs[pos]) {
      pos++;
    }
    bytePairs[pos]--;
    return pos;
  };

  for (size_t cycle = 0; cycle < steps; cycle++) {
    uint32_t count = byteWrites[cycle];
    assert(count <= kMaxBytePairsPerCycle);
    for (size_t i = 0; i < count; i++) {
      byteSorted[cycle * kMaxBytePairsPerCycle + i] = next();
    }
  }
}

void inject_backs_bytes(void* ctx, size_t steps, size_t cycle, Fp* data) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  assert(cycle != 0);

  uint32_t writeCount = mctx->byteWrites[cycle - 1];
  // printf("inject> cycle: %lu, writeCount: %u\n", cycle, writeCount);
  if (writeCount) {
    uint32_t pair = mctx->byteSorted[(cycle - 1) * kMaxBytePairsPerCycle + writeCount - 1];
    // printf("inject> pair: %x\n", pair);
    data[0 * steps + cycle - 1] = Fp(pair >> 8 & 0xff);
    data[1 * steps + cycle - 1] = Fp(pair & 0xff);
  }
}

std::array<Fp, 2>
extern_plonkRead_bytes(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t idx = mctx->byteReads[cycle]++;
  uint32_t pair = mctx->byteSorted[cycle * kMaxBytePairsPerCycle + idx];
  // printf("plonkReadBytes> cycle: %lu, idx: %u, pair: %x\n", cycle, idx, pair);
  return {Fp(pair >> 8 & 0xff), Fp(pair & 0xff)};
}

void extern_plonkWriteAccum_ram(void* ctx,
                                size_t cycle,
                                const char* extra,
                                std::array<Fp, 4> args) {
  // printf("plonkWriteAccumRam\n");
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  actx->cells[cycle].ram = FpExt(args[0], args[1], args[2], args[3]);
}

void extern_plonkWriteAccum_bytes(void* ctx,
                                  size_t cycle,
                                  const char* extra,
                                  std::array<Fp, 4> args) {
  // printf("plonkWriteAccumBytes\n");
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  actx->cells[cycle].bytes = FpExt(args[0], args[1], args[2], args[3]);
}

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

std::array<Fp, 4>
extern_plonkReadAccum_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  // printf("plonkReadAccumRam\n");
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  const FpExt& item = actx->cells[cycle].ram;
  return {item.elems[0], item.elems[1], item.elems[2], item.elems[3]};
}

std::array<Fp, 4>
extern_plonkReadAccum_bytes(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  const FpExt& item = actx->cells[cycle].bytes;
  return {item.elems[0], item.elems[1], item.elems[2], item.elems[3]};
}

} // namespace risc0::circuit::rv32im

extern "C" {

extern "C" const char* risc0_circuit_rv32im_cpu_witgen(
    PreflightTrace* trace, uint32_t steps, uint32_t last_cycle, Fp* ctrl, Fp* io, Fp* data) {
  try {
    printf("risc0_circuit_rv32im_cpu_witgen\n");

    MachineContext ctx;
    ctx.trace = trace;
    ctx.steps = steps;
    ctx.ramRows.resize(steps * kMaxRamRowsPerCycle);
    ctx.ramIndex.resize(steps);
    ctx.byteSorted.resize(steps * kMaxBytePairsPerCycle);
    ctx.byteWrites.resize(steps);
    ctx.byteReads.resize(steps);

    auto begin = poolstl::iota_iter<uint32_t>(0);
    auto end = poolstl::iota_iter<uint32_t>(last_cycle);
    std::array<Fp*, 3> args{ctrl, io, data};

    printf("step_exec\n");
    std::for_each(poolstl::seq, begin, end, [&](uint32_t cycle) {
      if (cycle == 0 || ctx.isParSafeExec(cycle)) {
        // printf("step_exec(%u)\n", cycle);
        step_exec(&ctx, steps, cycle++, args.data());
        while (cycle < last_cycle && !ctx.isParSafeExec(cycle)) {
          // printf("next, step_exec(%u)\n", cycle);
          step_exec(&ctx, steps, cycle++, args.data());
        }
      }
    });

    // ctx.ctx->sortRam();
    printf("inject_backs_ram\n");
    // inject_backs_ram<<<cfg.grid, cfg.block, 0, stream>>>(ctx.ctx, steps, last_cycle, data);

    printf("step_verify_mem\n");
    // par_step_verify_mem<<<cfg.grid, cfg.block, 0, stream>>>(
    //     ctx.ctx, steps, last_cycle, ctrl, io, data);

    // ctx.ctx->sortBytes();
    printf("inject_backs_bytes\n");
    // inject_backs_bytes<<<cfg.grid, cfg.block, 0, stream>>>(ctx.ctx, steps, last_cycle, data);

    printf("step_verify_bytes\n");
    // step_verify_bytes<<<cfg.grid, cfg.block, 0, stream>>>(
    //     ctx.ctx, steps, last_cycle, ctrl, io, data, nullptr, nullptr);

    // zeroize<<<cfg.grid, cfg.block, 0, stream>>>(data);
    // std::for_each(poolstl::seq, begin, end, [&](uint32_t cycle) {
    //   Fp val = data[cycle];
    //   elems[idx] = val.zeroize();
    // });

  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

void risc0_circuit_rv32im_sort_ram(risc0_error* err, MachineContext* ctx) {
  ffi_wrap<uint32_t>(err, 0, [&] {
    ctx->sortRam();
    return 0;
  });
}

void risc0_circuit_rv32im_sort_bytes(risc0_error* err, MachineContext* ctx) {
  ffi_wrap<uint32_t>(err, 0, [&] {
    ctx->sortBytes();
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

} // extern "C"
