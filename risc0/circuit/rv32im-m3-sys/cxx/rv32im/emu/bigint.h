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

#pragma once

#include <array>
#include <cstdint>
#include <map>
#include <functional>

#include "rv32im/emu/trace.h"

namespace risc0::rv32im {

using PeekFunc = std::function<uint32_t(uint32_t)>;

struct BigIntInstruction {
  uint32_t polyOp;
  uint32_t memOp;
  uint32_t coeff;
  uint32_t reg;
  uint32_t offset;

  static BigIntInstruction decode(uint32_t insn) {
    return BigIntInstruction{
        .polyOp = insn >> 24 & 0x0f,
        .memOp = insn >> 28 & 0x0f,
        .coeff = insn >> 21 & 0x07,
        .reg = insn >> 16 & 0x1f,
        .offset = insn & 0xffff,
    };
  }
};

// Given access to system memory via peek, preflight a BigInt function, return of validate
size_t witgenBigInt(std::map<uint32_t, uint32_t>& polyWitness, PeekFunc peek);

struct BytePolynomial {
  BytePolynomial();
  static BytePolynomial zero();
  static BytePolynomial one();
  BytePolynomial shift() const;
  BytePolynomial operator*(int x) const;
  BytePolynomial operator+(const BytePolynomial& rhs) const;
  BytePolynomial operator*(const BytePolynomial& rhs) const;

  std::vector<int32_t> coeffs;
};

std::ostream& operator<<(std::ostream& os, const BytePolynomial& x);

struct BigIntPreflight {
  BigIntPreflight();
  void step(const BigIntInstruction& inst, uint32_t* data);

  BytePolynomial poly;
  BytePolynomial term;
  BytePolynomial total;
  bool inCarry;
  BytePolynomial totCarry;
};


} // namespace risc0::rv32im
