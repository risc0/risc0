// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include "boost/multiprecision/cpp_int.hpp"

#include "rv32im/base/constants.h"
#include "rv32im/emu/bigint.h"

namespace risc0::rv32im {

namespace {

constexpr size_t BIGINT_WIDTH_BYTES = 16;

using BigInt = boost::multiprecision::cpp_int;

BigInt bigIntFromWords(const std::vector<uint32_t>& words) {
  BigInt result;
  import_bits(result, words.begin(), words.end(), 32, false);
  return result;
}

BigInt bigIntFromWords(const std::vector<uint64_t>& words) {
  BigInt result;
  import_bits(result, words.begin(), words.end(), 64, false);
  return result;
}

uint32_t getBigIntWord(const BigInt& val, size_t index) {
  std::uint32_t word = 0;
  word = static_cast<uint32_t>((val >> (32 * index)) & 0xffffffff);
  return word;
}

struct BigIntIO {
  uint32_t mm;
  PeekFunc peek;
  std::map<uint32_t, uint32_t>& polyWitness;

  BigIntIO(uint32_t mm, PeekFunc peek, std::map<uint32_t, uint32_t>& polyWitness)
      : mm(mm), peek(peek), polyWitness(polyWitness) {}

  BigInt load(uint32_t arena, uint32_t offset, uint32_t count);
  void store(uint32_t arena, uint32_t offset, uint32_t count, BigInt val);
};

template <typename int_t> int_t read(void** stream) {
  auto* casted = (int_t*)*stream;
  int_t value = *(casted++);
  *stream = (void*)casted;
  return value;
}

struct Type {
  uint64_t coeffs;
  uint64_t maxPos;
  uint64_t maxNeg;
  uint64_t minBits;

  static Type decode(void*& stream) {
    uint64_t coeffs = read<uint64_t>(&stream);
    uint64_t maxPos = read<uint64_t>(&stream);
    uint64_t maxNeg = read<uint64_t>(&stream);
    uint64_t minBits = read<uint64_t>(&stream);
    return Type{coeffs, maxPos, maxNeg, minBits};
  }
};

struct Input {
  uint64_t label;
  uint32_t bitWidth;
  uint16_t minBits;
  bool isPublic;

  static Input decode(void*& stream) {
    uint64_t label = read<uint64_t>(&stream);
    uint32_t bitWidth = read<uint32_t>(&stream);
    uint16_t minBits = read<uint16_t>(&stream);
    bool isPublic = read<uint16_t>(&stream) != 0;
    return Input{label, bitWidth, minBits, isPublic};
  }
};

enum class OpCode {
  Const = 0x2, // unary: constant index
  Load = 0x3,  // unary: constant index
  Store = 0x4, // unary: constant index
  Add = 0x8,   // binary
  Sub = 0x9,   // binary
  Mul = 0xA,   // binary
  Rem = 0xB,   // binary
  Quo = 0xC,   // binary
  Inv = 0xE,   // binary
};

struct Op {
  OpCode code;
  size_t resultType;
  size_t a;
  size_t b;

  uint32_t arena() const { return (uint32_t)(a >> 16); }

  uint32_t offset() const { return (uint32_t)(a & 0xffff); }

  static Op decode(void*& stream) {
    uint64_t bits = read<uint64_t>(&stream);
    return Op{
        .code = static_cast<OpCode>(bits & 0x0F),
        .resultType = (bits >> 4) & 0x0FFF,
        .a = (bits >> 16) & 0x00FFFFFF,
        .b = (bits >> 40) & 0x00FFFFFF,
    };
  }
};

struct Program {
  std::vector<Input> inputs;
  std::vector<Type> types;
  std::vector<uint64_t> constants;
  std::vector<Op> ops;

  static Program decode(void*& stream) {
    uint32_t magic = read<uint32_t>(&stream);
    if (magic != 0x63626962) {
      throw std::runtime_error("Bad magic");
    }

    uint32_t version = read<uint32_t>(&stream);
    if (version != 1) {
      throw std::runtime_error("Bad version");
    }

    uint32_t numInputs = read<uint32_t>(&stream);
    uint32_t numTypes = read<uint32_t>(&stream);
    uint32_t numConstants = read<uint32_t>(&stream);
    uint32_t numOps = read<uint32_t>(&stream);

    // Allocate storage for the program sections, then read each one.
    Program result;
    for (size_t i = 0; i < numInputs; i++) {
      result.inputs.push_back(Input::decode(stream));
    }
    for (size_t i = 0; i < numTypes; i++) {
      result.types.push_back(Type::decode(stream));
    }
    for (size_t i = 0; i < numConstants; i++) {
      result.constants.push_back(read<uint64_t>(&stream));
    }
    for (size_t i = 0; i < numOps; i++) {
      result.ops.push_back(Op::decode(stream));
    }
    return result;
  }

  void eval(BigIntIO& io) {
    std::vector<BigInt> regs;
    regs.resize(ops.size());
    for (size_t opIndex = 0; opIndex < ops.size(); opIndex++) {
      auto& op = ops[opIndex];
      switch (op.code) {
      case OpCode::Const: {
        uint32_t offset = op.a;
        uint32_t words = op.b;
        std::vector<uint64_t> bigWords;
        for (size_t i = 0; i < words; i++) {
          uint64_t word = constants[offset + i];
          bigWords.push_back(word);
        }
        regs[opIndex] = bigIntFromWords(bigWords);
        LOG(2, "[" << opIndex << "] CONST " << regs[opIndex]);
      } break;
      case OpCode::Load: {
        auto& typ = types[op.resultType];
        uint32_t count = (typ.coeffs + 15) / 16;
        auto value = io.load(op.arena(), op.offset(), count);
        LOG(2,
            "[" << opIndex << "] LOAD " << count << " FpExts from arena " << op.arena()
                << ", offset " << op.offset());
        regs[opIndex] = value;
      } break;
      case OpCode::Store: {
        LOG(2, "[" << opIndex << "] STORE " << op.a << ", " << op.b);
        auto& typ = types[op.resultType];
        uint32_t count = (typ.coeffs + 15) / 16;
        auto& value = regs[op.b];
        io.store(op.arena(), op.offset(), count, value);
      } break;
      case OpCode::Add: {
        auto& lhs = regs[op.a];
        auto& rhs = regs[op.b];
        auto& dst = regs[opIndex];
        LOG(2, "[" << opIndex << "] ADD " << op.a << ", " << op.b);
        dst = lhs + rhs;
      } break;
      case OpCode::Sub: {
        LOG(2, "[" << opIndex << "] SUB " << op.a << ", " << op.b);
        auto& lhs = regs[op.a];
        auto& rhs = regs[op.b];
        auto& dst = regs[opIndex];
        dst = lhs - rhs;
      } break;
      case OpCode::Mul: {
        LOG(2, "[" << opIndex << "] MUL " << op.a << ", " << op.b);
        auto& lhs = regs[op.a];
        auto& rhs = regs[op.b];
        auto& dst = regs[opIndex];
        dst = lhs * rhs;
      } break;
      case OpCode::Rem: {
        LOG(2, "[" << opIndex << "] REM " << op.a << ", " << op.b);
        auto& lhs = regs[op.a];
        auto& rhs = regs[op.b];
        auto& dst = regs[opIndex];
        dst = lhs % rhs;
      } break;
      case OpCode::Quo: {
        LOG(2, "[" << opIndex << "] QUO " << op.a << ", " << op.b);
        auto& lhs = regs[op.a];
        auto& rhs = regs[op.b];
        auto& dst = regs[opIndex];
        dst = lhs / rhs;
      } break;
      case OpCode::Inv: {
        LOG(2, "[" << opIndex << "] INV " << op.a << ", " << op.b);
        auto& lhs = regs[op.a];
        auto& rhs = regs[op.b];
        auto& dst = regs[opIndex];
        dst = powm(lhs, rhs - 2, rhs);
      } break;
      }
    }
  }
};

BigInt BigIntIO::load(uint32_t arena, uint32_t offset, uint32_t count) {
  uint32_t regVal = peek((mm ? MACHINE_REGS_WORD : USER_REGS_WORD) + arena);
  uint32_t addr = regVal + offset * 16;
  uint32_t baseWord = addr / 4;
  std::vector<uint32_t> words;
  for (size_t i = 0; i < count; i++) {
    for (size_t j = 0; j < 4; j++) {
      words.push_back(peek(baseWord + i * 4 + j));
      LOG(3, "host peek [" << (baseWord + i * 4 + j) << "] = " << words.back());
    }
  }
  BigInt val = bigIntFromWords(words);
  LOG(2, "Load, arena=" << arena << ", offset=" << offset);
  LOG(2, "  Addr = " << addr);
  LOG(2, "  Val = " << val);
  return val;
}

void BigIntIO::store(uint32_t arena, uint32_t offset, uint32_t count, BigInt val) {
  uint32_t regVal = peek((mm ? MACHINE_REGS_WORD : USER_REGS_WORD) + arena);
  uint32_t addr = regVal + offset * 16;
  uint32_t baseWord = addr / 4;
  LOG(2, "Store, arena=" << arena << ", offset=" << offset);
  LOG(2, "  Addr = " << addr);
  LOG(2, "  Val = " << val);
  for (size_t i = 0; i < count * 4; i++) {
    LOG(2, "  Polywitness[" << baseWord + i << "] = " << getBigIntWord(val, i));
    polyWitness[baseWord + i] = getBigIntWord(val, i);
  }
}

} // namespace

size_t witgenBigInt(std::map<uint32_t, uint32_t>& polyWitness, PeekFunc peek) {
  // TODO: Proper error handling
  uint32_t blobWordAddr = peek(MACHINE_REGS_WORD + REG_A0) / WORD_SIZE;
  uint32_t bibcWordAddr = peek(MACHINE_REGS_WORD + REG_T1) / WORD_SIZE;
  uint32_t bibcSize = peek(blobWordAddr);
  uint32_t verifySize = peek(blobWordAddr + 1);

  std::vector<uint32_t> code;
  for (size_t i = 0; i < bibcSize; i++) {
    code.push_back(peek(bibcWordAddr + i));
  }

  void* stream = (void*)code.data();
  Program prog = Program::decode(stream);
  uint32_t mm = peek(MACHINE_REGS_WORD + REG_T0);
  BigIntIO io(mm, peek, polyWitness);
  prog.eval(io);

  return verifySize;
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

// Do carry propagation
BytePolynomial BytePolynomial::propagateCarry() const {
  BytePolynomial ret;
  ret.coeffs = coeffs;

  int32_t carry = 0;
  for (size_t i = 0; i < ret.coeffs.size(); i++) {
    ret.coeffs[i] += carry;
    if (ret.coeffs[i] % 256 != 0) {
      LOG(0, "totCarry[" << i << "]=" << ret.coeffs[i]);
      throw std::runtime_error("Bad carry");
    }
    ret.coeffs[i] /= 256;
    carry = ret.coeffs[i];
  }

  return ret;
}

BytePolynomial BytePolynomial::fromData(uint32_t* data) {
  BytePolynomial ret;
  ret.coeffs.resize(16);
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      ret.coeffs[i * 4 + j] = (data[i] >> (8 * j)) & 0xff;
    }
  }
  return ret;
}

BytePolynomial BytePolynomial::negPoly() {
  BytePolynomial ret;
  ret.coeffs.resize(16, -128);
  return ret;
}

BytePolynomial BytePolynomial::basisPoint() {
  BytePolynomial ret;
  ret.coeffs.push_back(-256);
  ret.coeffs.push_back(1);
  return ret;
}

BigIntPreflight::BigIntPreflight() : inCarry(false) {
  poly = BytePolynomial::zero();
  term = BytePolynomial::one();
  total = BytePolynomial::zero();
}

void BigIntPreflight::step(const BigIntInstruction& inst, uint32_t* data) {
  if (inst.polyOp != static_cast<uint32_t>(PolyOp::NOP) &&
      inst.memOp == static_cast<uint32_t>(MemoryOp::CHECK)) {
    LOG(2, "MemoryOp::CHECK && !PolyOp::NOP");
    // Handle carry computation
    if (!inCarry) {
      // Transition to carry output, compute carry
      totCarry = total.propagateCarry();
      inCarry = true;
    }

    // Output carry to ret
    uint8_t ret[BIGINT_WIDTH_BYTES];
    int32_t basePoint = 128 * 256 * 64;
    LOG(2, "totCarry: " << totCarry.size());
    for (size_t i = 0; i < BIGINT_WIDTH_BYTES; i++) {
      uint32_t val = totCarry[inst.offset * BIGINT_WIDTH_BYTES + i] + basePoint;
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
        throw std::runtime_error("Invalid polyOp with MemoryOp_Check");
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
  BytePolynomial local = BytePolynomial::fromData(data);

  // Precompute some values
  BytePolynomial newPoly = poly + local;
  int32_t coeff = int32_t(inst.coeff) - 4;

  // Apply the poly-op
  switch (PolyOp(inst.polyOp)) {
  case PolyOp::NOP:
    LOG(2, "NOP");
    poly = BytePolynomial::zero();
    term = BytePolynomial::one();
    total = BytePolynomial::zero();
    inCarry = false;
    break;
  case PolyOp::SHIFT:
    LOG(2, "SHIFT");
    poly = newPoly.shift();
    break;
  case PolyOp::SET_TERM:
    LOG(2, "SET_TERM");
    poly = BytePolynomial::zero();
    term = newPoly;
    break;
  case PolyOp::ADD_TOTAL:
    LOG(2, "ADD_TOTAL");
    total = total + newPoly * term * coeff;
    term = BytePolynomial::one();
    poly = BytePolynomial::zero();
    break;
  case PolyOp::CARRY_1:
    LOG(2, "CARRY_1");
    poly = poly + (local + BytePolynomial::negPoly()) * 64 * 256;
    break;
  case PolyOp::CARRY_2:
    LOG(2, "CARRY_1");
    poly = poly + local * 256;
    break;
  case PolyOp::EQZ:
    LOG(2, "EQZ");
    total = total + BytePolynomial::basisPoint() * newPoly;
    for (size_t i = 0; i < total.size(); i++) {
      if (total[i] != 0) {
        LOG(0, "Coeffs[" << i << "]=" << total[i]);
        throw std::runtime_error("INVALID EQZ");
      }
    }
    poly = BytePolynomial::zero();
    term = BytePolynomial::one();
    total = BytePolynomial::zero();
    inCarry = false;
    break;
  }
  LOG(3, "PolyOp = " << inst.polyOp);
  LOG(3, "  local = " << local);
  LOG(3, "  newPoly = " << newPoly);
  LOG(3, "  poly = " << poly);
  LOG(3, "  term = " << term);
  LOG(3, "  total = " << total);
}

} // namespace risc0::rv32im
