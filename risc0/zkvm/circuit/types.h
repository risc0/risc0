// Copyright 2022 Risc0, Inc.
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

#include "risc0/zkvm/circuit/edsl.h"

namespace risc0 {

class BufAlloc {
public:
  BufAlloc(Buffer digits, Buffer generic)
      : digits(digits), generic(generic), digitsOffset(0), genericOffset(0) {}
  Buffer allocDigits(size_t size) {
    if (digits.size() - digitsOffset >= size) {
      return alloc(digits, digitsOffset, size);
    }
    return allocGeneric(size);
  }
  Buffer allocGeneric(size_t size) {
    if (generic.size() - genericOffset >= size) {
      return alloc(generic, genericOffset, size);
    }
    throw std::runtime_error("Unable to alloc");
  }

private:
  Buffer alloc(Buffer base, size_t& offset, size_t size) {
    Buffer ret = base.slice(offset, size);
    offset += size;
    return ret;
  }

  Buffer digits;
  Buffer generic;
  size_t digitsOffset;
  size_t genericOffset;
};

struct ValueU32 {
  Value low;
  Value high;
  static ValueU32 fromConst(uint32_t val) { return {val & 0xffff, val >> 16}; }
};

inline ValueU32 operator*(Value a, ValueU32 b) {
  return {a * b.low, a * b.high};
}

inline ValueU32 operator+(ValueU32 a, ValueU32 b) {
  return {a.low + b.low, a.high + b.high};
}

inline ValueU32 operator-(ValueU32 a, ValueU32 b) {
  return {0x10000 + a.low - b.low, 0xffff + a.high - b.high};
}

inline ValueU32 operator+(ValueU32 a, int b) {
  return {a.low + b, a.high};
}

class Reg {
public:
  Reg(BufAlloc& alloc) : buf(alloc.allocGeneric(1)) {}
  Value get(SourceLoc loc = SourceLoc::current()) { return buf.at(0, loc); }
  void set(Value val, SourceLoc loc = SourceLoc::current()) { buf.at(0, loc) = val; }

private:
  Buffer buf;
};

class RegBin {
public:
  RegBin(BufAlloc& alloc, SourceLoc loc = SourceLoc::current())
      : buf(alloc.allocDigits(1).requireDigits(1, loc)) {}
  Value get(SourceLoc loc = SourceLoc::current()) const { return buf.at(0, loc); }
  void set(Value val, SourceLoc loc = SourceLoc::current()) { buf.at(0, loc) = val; }

private:
  Buffer buf;
};

template <size_t Bits, size_t Size> class RegDigits {
public:
  static_assert(Bits <= 2);
  static_assert(Size % Bits == 0);
  RegDigits(BufAlloc& alloc, SourceLoc loc = SourceLoc::current())
      : buf(alloc.allocDigits(Size / Bits).requireDigits(Bits, loc)) {}
  Value getPart(size_t off, size_t size, SourceLoc loc = SourceLoc::current()) const {
    return buf.slice(off / Bits, size / Bits, loc).getDigits(Bits, loc);
  }
  Value setPart(Value num, size_t off, size_t size, SourceLoc loc = SourceLoc::current()) {
    return buf.slice(off / Bits, size / Bits, loc).setDigits(Bits, num, loc);
  }
  void setPartExact(Value num, size_t off, size_t size, SourceLoc loc = SourceLoc::current()) {
    equate(setPart(num, off, size, loc), 0, loc);
  }
  Value get(size_t i, SourceLoc loc = SourceLoc::current()) const { return buf.at(i, loc); }
  ValueU32 get(SourceLoc loc = SourceLoc::current()) const {
    static_assert(Size == 32);
    return {getPart(0, 16, loc), getPart(16, 16, loc)};
  }
  void set(ValueU32 val, SourceLoc loc = SourceLoc::current()) {
    static_assert(Size == 32);
    setPartExact(val.low, 0, 16, loc);
    setPartExact(val.high, 16, 16, loc);
  }
  void setBE(ValueU32 val, SourceLoc loc = SourceLoc::current()) {
    static_assert(Size == 32);
    Value x0 = setPart(val.high, 8, 8, loc);
    equate(setPart(x0, 0, 8, loc), 0, loc);
    Value x1 = setPart(val.low, 24, 8, loc);
    equate(setPart(x1, 16, 8, loc), 0, loc);
  }
  void setCarry(ValueU32 val,
                RegBin& carryLow,
                RegBin& carryHigh,
                SourceLoc loc = SourceLoc::current()) {
    static_assert(Size == 32);
    carryLow.set(setPart(val.low, 0, 16));
    carryHigh.set(setPart(val.high + carryLow.get(), 16, 16));
  }
  template <size_t CarryBits>
  void setCarry(ValueU32 val,
                RegDigits<1, CarryBits>& carryLow,
                RegDigits<1, CarryBits>& carryHigh,
                SourceLoc loc = SourceLoc::current()) {
    static_assert(Size == 32);
    carryLow.setPartExact(setPart(val.low, 0, 16), 0, CarryBits);
    carryHigh.setPartExact(
        setPart(val.high + carryLow.getPart(0, CarryBits), 16, 16), 0, CarryBits);
  }

  operator ValueU32() const { return get(); }
  template <typename T> ValueU32 bitOp(const RegDigits& rhs, T func) const {
    static_assert(Bits == 1);
    static_assert(Size == 32);
    ValueU32 ret = {0, 0};
    for (int i = 0; i < 32; i++) {
      if (i >= 16) {
        ret.high = ret.high + (1 << (i - 16)) * func(get(i), rhs.get(i));
      } else {
        ret.low = ret.low + (1 << i) * func(get(i), rhs.get(i));
      }
    }
    return ret;
  }
  ValueU32 operator^(const RegDigits& rhs) const {
    return bitOp(rhs, [](Value a, Value b) { return a + b - 2 * a * b; });
  }
  ValueU32 operator|(const RegDigits& rhs) const {
    return bitOp(rhs, [](Value a, Value b) { return a + b - a * b; });
  }
  ValueU32 operator&(const RegDigits& rhs) const {
    return bitOp(rhs, [](Value a, Value b) { return a * b; });
  }

private:
  Buffer buf;
};

template <size_t Size> class RegMux {
public:
  RegMux(BufAlloc& alloc, SourceLoc loc = SourceLoc::current())
      : buf(alloc.allocDigits(Size).requireMux(loc)) {}
  Value get(SourceLoc loc = SourceLoc::current()) { return buf.getMux(loc); }
  void set(Value val, SourceLoc loc = SourceLoc::current()) { buf.setMux(val, loc); }
  Value is(size_t idx, SourceLoc loc = SourceLoc::current()) { return buf.at(idx, loc); }
  ValueU32 asU32() {
    static_assert(Size == 32);
    return {buf.slice(0, 16).getDigits(1), buf.slice(16, 16).getDigits(1)};
  }

private:
  Buffer buf;
};

class RegU32 {
public:
  RegU32(BufAlloc& alloc) : buf(alloc.allocGeneric(2)) {}
  Value low(SourceLoc loc = SourceLoc::current()) { return buf.at(0, loc); }
  Value high(SourceLoc loc = SourceLoc::current()) { return buf.at(1, loc); }
  ValueU32 get(SourceLoc loc = SourceLoc::current()) { return {low(loc), high(loc)}; }
  void setLow(Value val, SourceLoc loc = SourceLoc::current()) { buf.at(0, loc) = val; }
  void setHigh(Value val, SourceLoc loc = SourceLoc::current()) { buf.at(1, loc) = val; }
  void set(ValueU32 val, SourceLoc loc = SourceLoc::current()) {
    setLow(val.low, loc);
    setHigh(val.high, loc);
  }

private:
  Buffer buf;
};

/// A widgit that converts some value into a boolean.
struct MakeBoolRegs {
  RegBin isNonzero;
  Reg maybeInv;

  MakeBoolRegs(BufAlloc& alloc) : isNonzero(alloc), maybeInv(alloc) {}

  Value get() const { return isNonzero.get(); }
  void set(Value num) {
    BYZ_NONDET {
      isNonzero.set(nonzero(num));
      maybeInv.set(inv(num));
    }
    equate(num * maybeInv.get(), isNonzero.get());
    equate((1 - isNonzero.get()) * num, 0);
  }
};

/// A widgit that negates a U32 number which is almost just subtraction, except for the case of zero
/// that needs to be handled specially.
struct NegU32Regs {
  MakeBoolRegs lowSafe;
  MakeBoolRegs highSafe;
  RegU32 store;

  NegU32Regs(BufAlloc& alloc) : lowSafe(alloc), highSafe(alloc), store(alloc) {}

  // Set the input number, gets the output.
  ValueU32 set(ValueU32 val) {
    // Pick the values for the two 'carry' registers via nondet
    ValueU32 out;
    Value lowSub = 0x10000 - val.low;
    lowSafe.set(lowSub - 0x10000);
    out.low = lowSafe.isNonzero.get() * lowSub;
    Value highSub = 0x10000 - lowSafe.isNonzero.get() - val.high;
    highSafe.set(highSub - 0x10000);
    out.high = highSafe.isNonzero.get() * highSub;
    store.set(out);
    return store.get();
  }
};

struct StepState;

} // namespace risc0
