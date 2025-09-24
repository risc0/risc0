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

#include "rv32im/emu/bigint.h"

#include "rv32im/base/constants.h"

#if defined(RV32IM_BIGINT)

#include "zirgen/Dialect/BigInt/Bytecode/decode.h"
#include "zirgen/Dialect/BigInt/Bytecode/file.h"
#include "zirgen/Dialect/BigInt/IR/BigInt.h"
#include "zirgen/Dialect/BigInt/IR/Eval.h"

#endif

namespace risc0::rv32im {

#if defined(RV32IM_BIGINT)

namespace {

struct BigIntIO : public zirgen::BigInt::BigIntIO {
  uint32_t mm;
  PeekFunc peek;
  std::map<uint32_t, uint32_t>& polyWitness;

  BigIntIO(uint32_t mm, PeekFunc peek, std::map<uint32_t, uint32_t>& polyWitness)
      : mm(mm), peek(peek), polyWitness(polyWitness) {}

  llvm::APInt load(uint32_t arena, uint32_t offset, uint32_t count) override;
  void store(uint32_t arena, uint32_t offset, uint32_t count, llvm::APInt val) override;
};

std::string toString(llvm::APInt val) {
  llvm::SmallVector<char, 128> out;
  val.toStringUnsigned(out, /*Radix=*/16);
  return std::string(out.data(), out.size());
}

llvm::APInt BigIntIO::load(uint32_t arena, uint32_t offset, uint32_t count) {
  uint32_t regVal = peek((mm ? MACHINE_REGS_WORD : USER_REGS_WORD) + arena);
  uint32_t addr = regVal + offset * 16;
  uint32_t baseWord = addr / 4;
  std::vector<uint64_t> limbs64;
  for (size_t i = 0; i < count; i++) {
    std::array<uint32_t, 4> words;
    for (size_t j = 0; j < 4; j++) {
      words[j] = peek(baseWord + i * 4 + j);
    }
    limbs64.push_back(uint64_t(words[0]) | ((uint64_t(words[1])) << 32));
    limbs64.push_back(uint64_t(words[2]) | ((uint64_t(words[3])) << 32));
  }
  llvm::APInt val(count * 128, limbs64);
  LOG(2, "Load, arena=" << arena << ", offset=" << offset);
  LOG(2, "  Addr = " << addr);
  LOG(2, "  Val = " << toString(val));
  return val;
}

void BigIntIO::store(uint32_t arena, uint32_t offset, uint32_t count, llvm::APInt val) {
  uint32_t regVal = peek((mm ? MACHINE_REGS_WORD : USER_REGS_WORD) + arena);
  uint32_t addr = regVal + offset * 16;
  uint32_t baseWord = addr / 4;
  LOG(2, "Store, arena=" << arena << ", offset=" << offset);
  LOG(2, "  Addr = " << addr);
  LOG(2, "  Val = " << toString(val));
  val = val.zext(count * 128);
  for (size_t i = 0; i < count * 4; i++) {
    LOG(2, "  Polywitness[" << baseWord + i << "] = " << val.extractBitsAsZExtValue(32, i * 32));
    polyWitness[baseWord + i] = val.extractBitsAsZExtValue(32, i * 32);
  }
}

} // namespace

#endif

size_t witgenBigInt(std::map<uint32_t, uint32_t>& polyWitness, PeekFunc peek) {
  // TODO: Proper error handling
  uint32_t blobWordAddr = peek(MACHINE_REGS_WORD + REG_A0) / 4;
  uint32_t bibcWordAddr = peek(MACHINE_REGS_WORD + REG_T1) / 4;
  uint32_t bibcSize = peek(blobWordAddr);

  std::vector<uint32_t> code;
  for (size_t i = 0; i < bibcSize; i++) {
    code.push_back(peek(bibcWordAddr + i));
  }

#if defined(RV32IM_BIGINT)

  // Deserialize
  zirgen::BigInt::Bytecode::Program prog;
  zirgen::BigInt::Bytecode::read(prog, code.data(), code.size() * 4);

  // Build a module + func
  mlir::DialectRegistry registry;
  registry.insert<mlir::func::FuncDialect>();
  registry.insert<zirgen::BigInt::BigIntDialect>();
  mlir::MLIRContext mlirContext(registry);
  mlirContext.loadAllAvailableDialects();
  auto loc = mlir::UnknownLoc::get(&mlirContext);
  auto module = mlir::ModuleOp::create(loc);
  auto func = zirgen::BigInt::Bytecode::decode(module, prog);

  // evaluate the program to compute the polyWitness
  uint32_t mm = peek(MACHINE_REGS_WORD + REG_T0);
  BigIntIO io(mm, peek, polyWitness);
  zirgen::BigInt::eval(func, io, false);

#endif

  // Count # of steps
  // TODO, should be have a max size, error handling?
  size_t size = 0;
  uint32_t progStart = peek(MACHINE_REGS_WORD + REG_T2) / 4;
  while (true) {
    auto decoded = BigIntInstruction::decode(peek(progStart + size));
    // LOG(0, "Reading program @ " << progStart + size);
    // LOG(0, "  polyOp = " << decoded.polyOp);
    // LOG(0, "  memOp = " << decoded.memOp);
    // LOG(0, "  coeff = " << decoded.coeff);
    // LOG(0, "  reg = " << decoded.reg);
    // LOG(0, "  offset = " << decoded.offset);
    size++;
    if (decoded.polyOp == 0) {
      break;
    }
  }
  return size;
}

BytePolynomial::BytePolynomial() {}

BytePolynomial BytePolynomial::zero() {
  BytePolynomial r;
  r.coeffs.push_back(0);
  return r;
}

BytePolynomial BytePolynomial::one() {
  BytePolynomial r;
  r.coeffs.push_back(1);
  return r;
}

BytePolynomial BytePolynomial::shift() const {
  BytePolynomial r;
  std::vector<int32_t> zeros(16);
  r.coeffs = coeffs;
  r.coeffs.insert(r.coeffs.begin(), zeros.begin(), zeros.end());
  return r;
}

BytePolynomial BytePolynomial::operator*(int x) const {
  BytePolynomial r;
  r.coeffs = coeffs;
  for (size_t i = 0; i < coeffs.size(); i++) {
    r.coeffs[i] = coeffs[i] * x;
  }
  return r;
}

BytePolynomial BytePolynomial::operator+(const BytePolynomial& rhs) const {
  BytePolynomial r;
  r.coeffs.resize(std::max(coeffs.size(), rhs.coeffs.size()));
  for (size_t i = 0; i < r.coeffs.size(); i++) {
    if (i < coeffs.size()) {
      r.coeffs[i] += coeffs[i];
    }
    if (i < rhs.coeffs.size()) {
      r.coeffs[i] += rhs.coeffs[i];
    }
  }
  return r;
}

BytePolynomial BytePolynomial::operator*(const BytePolynomial& rhs) const {
  BytePolynomial r;
  r.coeffs.resize(coeffs.size() + rhs.coeffs.size() - 1);
  for (size_t i = 0; i < coeffs.size(); i++) {
    for (size_t j = 0; j < rhs.coeffs.size(); j++) {
      r.coeffs[i + j] += coeffs[i] * rhs.coeffs[j];
    }
  }
  return r;
}

std::ostream& operator<<(std::ostream& os, const BytePolynomial& x) {
  os << "[";
  for (size_t i = 0; i < std::min(x.coeffs.size(), size_t(20)); i++) {
    os << x.coeffs[i];
    if (i != x.coeffs.size() - 1) {
      os << " ";
    }
  }
  if (x.coeffs.size() > 20) {
    os << " ... ";
  }
  os << "]";
  return os;
}

BigIntPreflight::BigIntPreflight() : inCarry(false) {
  poly = BytePolynomial::zero();
  term = BytePolynomial::one();
  total = BytePolynomial::zero();
}

void BigIntPreflight::step(const BigIntInstruction& inst, uint32_t* data) {
  if (inst.polyOp != 0 && inst.memOp == 2) {
    // Handle carry computation
    if (!inCarry) {
      // Transition to carry output, compute carry
      totCarry = total;
      int32_t carry = 0;
      // Do carry propagation
      for (size_t i = 0; i < totCarry.coeffs.size(); i++) {
        totCarry.coeffs[i] += carry;
        if (totCarry.coeffs[i] % 256 != 0) {
          LOG(0, "totCarry.coeffs[" << i << "]=" << totCarry.coeffs[i]);
          throw std::runtime_error("Bad carry");
        }
        totCarry.coeffs[i] /= 256;
        carry = totCarry.coeffs[i];
      }
      inCarry = true;
    }
    // Output carry to ret
    uint8_t ret[16];
    int32_t basePoint = 128 * 256 * 64;
    for (size_t i = 0; i < 16; i++) {
      uint32_t val = totCarry.coeffs[inst.offset * 16 + i] + basePoint;
      switch (PolyOp(inst.polyOp)) {
      case PolyOp::CARRY_1:
        ret[i] = (val >> 14) & 0xff;
        break;
      case PolyOp::CARRY_2:
        ret[i] = (val >> 8) & 0x3f;
        break;
      case PolyOp::SHIFT:
      case PolyOp::EQZ:
        ret[i] = val & 0xff;
        break;
      default:
        throw std::runtime_error("Invalid memOp=2 operation");
      }
    }
    // Write to data
    for (size_t i = 0; i < 4; i++) {
      uint32_t val = 0;
      for (size_t j = 0; j < 4; j++) {
        val |= ret[i * 4 + j] << (8 * j);
      }
      data[i] = val;
    }
  }
  // Expand data into a byte poly
  BytePolynomial local;
  local.coeffs.resize(16);
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      local.coeffs[i * 4 + j] = (data[i] >> (8 * j)) & 0xff;
    }
  }
  // Precompute some values
  BytePolynomial negPoly;
  negPoly.coeffs.resize(16, -128);
  BytePolynomial newPoly = poly + local;
  BytePolynomial bp;
  bp.coeffs.push_back(-256);
  bp.coeffs.push_back(1);
  int32_t coeff = int32_t(inst.coeff) - 4;
  // Apply the poly-op
  switch (PolyOp(inst.polyOp)) {
  case PolyOp::NOP:
    poly = BytePolynomial::zero();
    term = BytePolynomial::one();
    total = BytePolynomial::zero();
    inCarry = false;
    break;
  case PolyOp::SHIFT:
    poly = newPoly.shift();
    break;
  case PolyOp::SET_TERM:
    poly = BytePolynomial::zero();
    term = newPoly;
    break;
  case PolyOp::ADD_TOTAL:
    total = total + newPoly * term * coeff;
    term = BytePolynomial::one();
    poly = BytePolynomial::zero();
    break;
  case PolyOp::CARRY_1:
    poly = poly + (local + negPoly) * 64 * 256;
    break;
  case PolyOp::CARRY_2:
    poly = poly + local * 256;
    break;
  case PolyOp::EQZ:
    total = total + bp * newPoly;
    for (size_t i = 0; i < total.coeffs.size(); i++) {
      if (total.coeffs[i] != 0) {
        LOG(0, "Coeffs[" << i << "]=" << total.coeffs[i]);
        throw std::runtime_error("INVALID EQZ");
      }
    }
    poly = BytePolynomial::zero();
    term = BytePolynomial::one();
    total = BytePolynomial::zero();
    inCarry = false;
    break;
  }
  // LOG(0, "PolyOp = " << inst.polyOp);
  // LOG(0, "  local = " << local);
  // LOG(0, "  newPoly = " << newPoly);
  // LOG(0, "  poly = " << poly);
  // LOG(0, "  term = " << term);
  // LOG(0, "  total = " << total);
}

} // namespace risc0::rv32im
