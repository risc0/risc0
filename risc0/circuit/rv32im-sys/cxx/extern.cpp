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

#include <cstring>
#include <iostream>
#include <stdexcept>

namespace risc0::circuit::rv32im {

constexpr size_t kBabyBearExtSize = 4;

struct MemoryTransaction {
  size_t cycle;
  uint32_t addr;
  uint32_t data;
};

struct PreflightCycle {
  uint32_t major;
  uint32_t minor;
  size_t memIdx;
  size_t extraIdx;
};

struct Preflight {
  PreflightCycle* cycles;
  MemoryTransaction* txns;
  uint32_t* extras;
  uint32_t isTrace;
};

void extern_halt(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  // no-op
}

void extern_trace(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args) {
  // no-op
}

Fp extern_getMajor(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  Preflight* preflight = static_cast<Preflight*>(ctx);
  return Fp(preflight->cycles[cycle].major);
}

Fp extern_getMinor(void* ctx, size_t cycle, const char* extra, std::array<Fp, 4> args) {
  Preflight* preflight = static_cast<Preflight*>(ctx);
  return Fp(preflight->cycles[cycle].minor);
}

std::array<Fp, 3>
extern_pageInfo(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args) {
  Preflight* preflight = static_cast<Preflight*>(ctx);
  if (preflight->isTrace) {
    printf("pageInfo\n");
  }
  size_t idx = preflight->cycles[cycle].extraIdx;
  uint32_t isRead = preflight->extras[idx + 0];
  uint32_t pageIdx = preflight->extras[idx + 1];
  uint32_t isDone = preflight->extras[idx + 2];
  return {Fp(isRead), Fp(pageIdx), Fp(isDone)};
}

void extern_ramWrite(void* ctx, size_t cycle, const char* extra, std::array<Fp, 6> args) {
  // no-op
}

std::array<Fp, 4>
extern_ramRead(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  Preflight* preflight = static_cast<Preflight*>(ctx);
  uint32_t addr = args[0].asUInt32();
  size_t memIdx = preflight->cycles[cycle].memIdx++;
  MemoryTransaction& txn = preflight->txns[memIdx];
  if (preflight->isTrace) {
    printf("ramRead(%lu, 0x%x): txn(%lu, 0x%x)\n", cycle, addr, txn.cycle, txn.addr);
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
  Preflight* preflight = static_cast<Preflight*>(ctx);
  size_t extraIdx = preflight->cycles[cycle].extraIdx++;
  uint32_t word = preflight->extras[extraIdx];
  return {
      Fp(word & 0xff),
      Fp(word >> 8 & 0xff),
      Fp(word >> 16 & 0xff),
      Fp(word >> 24 & 0xff),
  };
}

std::array<Fp, 8>
extern_syscallFini(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  Preflight* preflight = static_cast<Preflight*>(ctx);
  size_t extraIdx = preflight->cycles[cycle].extraIdx++;
  uint32_t a0 = preflight->extras[extraIdx + 0];
  uint32_t a1 = preflight->extras[extraIdx + 1];
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
  // Throws if the quotient overflows BigInt::kByteWidth. Overflows will not happen if the
  // numberator, a, is the result of a multiplication of two numbers less than the denomintor.
  // The BigInt arithmatic circuit does not accept larger quotients.
  // Returns only the quotient value q as the BigInt circuit does not use the r value.
  // std::vector<uint64_t> a = llvm::ArrayRef(fpArgs).slice(0, BigInt::kByteWidth * 2).vec();
  // std::vector<uint64_t> b =
  //     llvm::ArrayRef(fpArgs).slice(BigInt::kByteWidth * 2, BigInt::kByteWidth).vec();
  std::array<Fp, 32> q;

  // This is a variant of school-book multiplication.
  // Reference the Handbook of Elliptic and Hyper-elliptic Cryptography alg. 10.5.1

  // Determine n, the width of the denominator, and check for a denominator of zero.
  // size_t n = BigInt::kByteWidth;
  // while (n > 0 && b.at(n - 1) == 0) {
  //   n--;
  // }
  // if (n == 0) {
  //   // Divide by zero is strictly undefined, but the BigInt multiplier circuit uses a modulus of
  //   // zero as a special case to support "checked multiply" of up to 256-bits.
  //   // Return zero here to facilitate this.
  //   return q;
  // }
  // if (n < 2) {
  //   // TODO(victor): Not an important case. But we should likely handle it anyway.
  //   throw std::runtime_error("bigint quotient: denominator must be at least 9 bits");
  // }
  // Pad the denominator with a zero to avoid edge cases later.
  // if (n == BigInt::kByteWidth) {
  //   b.emplace_back(0);
  // }
  // size_t m = a.size() - n;

  // Shift (i.e. multiply by two) the inputs a and b until the leading bit of b is 1.
  // Note that shifting both numerator and denominator has no effect on the quotient.
  // uint64_t dBits = 0;
  // while ((b.at(n - 1) & (0x80 >> dBits)) == 0) {
  //   dBits++;
  // }
  // uint64_t carry = 0;
  // for (size_t i = 0; i < n; i++) {
  //   uint64_t tmp = (b.at(i) << dBits) + carry;
  //   b.at(i) = tmp & 0xFF;
  //   carry = tmp >> 8;
  // }
  // if (carry != 0) {
  //   throw std::runtime_error("implementation error: final carry in input shift");
  // }
  // for (size_t i = 0; i < a.size() - 1; i++) {
  //   uint64_t tmp = (a.at(i) << dBits) + carry;
  //   a.at(i) = tmp & 0xFF;
  //   carry = tmp >> 8;
  // }
  // a.emplace_back(carry);

  // for (size_t i = m;; i--) {
  //   // Approximate how many multiples of b can be subtracted. May overestimate by up to one.
  //   uint64_t qApprox =
  //       std::min<uint64_t>(((a.at(i + n) << 8) + a.at(i + n - 1)) / b.at(n - 1), 255);
  //   while ((qApprox * ((b.at(n - 1) << 8) + b.at(n - 2))) >
  //          ((a.at(i + n) << 16) + (a.at(i + n - 1) << 8) + a.at(i + n - 2))) {
  //     qApprox--;
  //   }

  //   // Subtract multiples of the denominator from a.
  //   uint64_t borrow = 0;
  //   for (size_t j = 0; j <= n; j++) {
  //     uint64_t sub = qApprox * b.at(j) + borrow;
  //     if (a.at(i + j) < (sub & 0xFF)) {
  //       a.at(i + j) += 0x100 - (sub & 0xFF);
  //       borrow = (sub >> 8) + 1;
  //     } else {
  //       a.at(i + j) -= sub & 0xFF;
  //       borrow = sub >> 8;
  //     }
  //   }
  //   if (borrow > 0) {
  //     // Oops, went negative. Add back one multiple of b.
  //     qApprox--;
  //     uint64_t carry = 0;
  //     for (size_t j = 0; j <= n; j++) {
  //       uint64_t tmp = a.at(i + j) + b.at(j) + carry;
  //       a.at(i + j) = tmp & 0xFF;
  //       carry = tmp >> 8;
  //     }
  //     // Adding back one multiple of b should go from negative back to positive.
  //     if (borrow - carry != 0) {
  //       throw std::runtime_error("implementation error: underflow in bigint division");
  //     }
  //   }

  //   if (i < q.size()) {
  //     q.at(i) = qApprox;
  //   } else if (qApprox != 0) {
  //     throw std::runtime_error("bigint quotient: quotient exceeds allowed size");
  //   }

  //   if (i == 0) {
  //     break;
  //   }
  // }
  return q;
}

void extern_plonkWrite_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 7> args) {
  // TODO
}

void extern_plonkWrite_bytes(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  // TODO
}

std::array<Fp, 7>
extern_plonkRead_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  throw std::runtime_error("plonkRead ram not implemented");
}

std::array<Fp, 2>
extern_plonkRead_bytes(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  throw std::runtime_error("plonkRead bytes implemented");
}

void extern_log(void* ctx, size_t cycle, const char* extra, std::vector<Fp> args) {
  Preflight* preflight = static_cast<Preflight*>(ctx);
  if (!preflight->isTrace) {
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

} // namespace risc0::circuit::rv32im
