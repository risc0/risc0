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

#include "risc0/zkvm/circuit/context.h"

namespace risc0 {

class Value {
public:
  // Just for aggregates...
  Value() = default;

  // Construct from an existing impl
  Value(std::shared_ptr<ValueImplBase> impl) : impl(impl) {}

  // Construct a new expression with a constant value
  Value(int value, SourceLoc loc = SourceLoc::current())
      : Value(getGlobalContext()->constant(Fp(value), loc)) {}
  Value(Fp value, SourceLoc loc = SourceLoc::current())
      : Value(getGlobalContext()->constant(value, loc)) {}

  // Get the details
  std::shared_ptr<ValueImplBase> getImpl() const { return impl; }

private:
  std::shared_ptr<ValueImplBase> impl;
};

class Buffer {
public:
  Buffer(std::shared_ptr<BufferImplBase> impl) : impl(impl) {}
  size_t size() { return impl->size; }
  size_t back() { return impl->back; }
  Buffer slice(size_t start, size_t size, SourceLoc loc = SourceLoc::current()) const {
    return getGlobalContext()->slice(impl, start, size, loc);
  }
  Buffer back(size_t back, SourceLoc loc = SourceLoc::current()) {
    return getGlobalContext()->back(impl, back, loc);
  }
  Buffer requireDigits(size_t bits, SourceLoc loc = SourceLoc::current()) {
    return getGlobalContext()->requireDigits(impl, bits, loc);
  }
  Buffer requireMux(SourceLoc loc = SourceLoc::current()) {
    return getGlobalContext()->requireMux(impl, loc);
  }
  struct BufAccess {
  public:
    BufAccess(std::shared_ptr<BufferImplBase> impl, size_t idx, SourceLoc loc)
        : impl(impl), idx(idx), loc(loc) {}
    BufAccess(const BufAccess& rhs) = delete;
    BufAccess(BufAccess&& rhs) = default;
    void operator=(const BufAccess& rhs) {
      auto rawVal = getGlobalContext()->getVal(impl, idx, loc);
      getGlobalContext()->setVal(impl, idx, rawVal, loc);
    }
    void operator=(Value val) { getGlobalContext()->setVal(impl, idx, val.getImpl(), loc); }
    operator Value() const { return getGlobalContext()->getVal(impl, idx, loc); }

  private:
    std::shared_ptr<BufferImplBase> impl;
    size_t idx;
    SourceLoc loc;
  };
  struct CaptureIdxLoc {
    CaptureIdxLoc(size_t idx, SourceLoc loc = SourceLoc::current()) : idx(idx), loc(loc) {}
    size_t idx;
    SourceLoc loc;
  };

  const BufAccess operator[](CaptureIdxLoc idxLoc) const {
    return BufAccess(impl, idxLoc.idx, idxLoc.loc);
  }
  BufAccess operator[](CaptureIdxLoc idxLoc) { return BufAccess(impl, idxLoc.idx, idxLoc.loc); }
  const BufAccess at(size_t idx, SourceLoc loc = SourceLoc::current()) const {
    return BufAccess(impl, idx, loc);
  }
  BufAccess at(size_t idx, SourceLoc loc = SourceLoc::current()) {
    return BufAccess(impl, idx, loc);
  }
  Value getDigits(size_t bits, SourceLoc loc = SourceLoc::current()) {
    return getGlobalContext()->getDigits(impl, bits, loc);
  }
  Value setDigits(size_t bits, Value val, SourceLoc loc = SourceLoc::current()) {
    return getGlobalContext()->setDigits(impl, bits, val.getImpl(), loc);
  }
  Value getMux(SourceLoc loc = SourceLoc::current()) {
    return getGlobalContext()->getMux(impl, loc);
  }
  void setMux(Value val, SourceLoc loc = SourceLoc::current()) {
    getGlobalContext()->setMux(impl, val.getImpl(), loc);
  }

private:
  std::shared_ptr<BufferImplBase> impl;
};

inline Value getGlobal(size_t offset, SourceLoc loc = SourceLoc::current()) {
  return getGlobalContext()->getGlobal(offset, loc);
}

inline void setGlobal(size_t offset, Value val, SourceLoc loc = SourceLoc::current()) {
  return getGlobalContext()->setGlobal(offset, val.getImpl(), loc);
}

struct CaptureValLoc {
  CaptureValLoc(Value val, SourceLoc loc = SourceLoc::current()) : val(val), loc(loc) {}
  CaptureValLoc(Buffer::BufAccess access, SourceLoc loc = SourceLoc::current())
      : val(access), loc(loc) {}
  CaptureValLoc(Fp fp, SourceLoc loc = SourceLoc::current()) : val(fp), loc(loc) {}
  CaptureValLoc(int num, SourceLoc loc = SourceLoc::current()) : val(Fp(num)), loc(loc) {}
  Value val;
  SourceLoc loc;
};

inline Value operator+(CaptureValLoc a, CaptureValLoc b) {
  return getGlobalContext()->add(a.val.getImpl(), b.val.getImpl(), b.loc);
}

inline Value operator-(CaptureValLoc a, CaptureValLoc b) {
  return getGlobalContext()->sub(a.val.getImpl(), b.val.getImpl(), b.loc);
}

inline Value operator*(CaptureValLoc a, CaptureValLoc b) {
  return getGlobalContext()->mul(a.val.getImpl(), b.val.getImpl(), b.loc);
}

inline Value operator/(CaptureValLoc a, CaptureValLoc b) {
  auto invB = getGlobalContext()->inv(b.val.getImpl(), b.loc);
  return getGlobalContext()->mul(a.val.getImpl(), invB, b.loc);
}

inline Value operator&(CaptureValLoc a, CaptureValLoc b) {
  return getGlobalContext()->bitAnd(a.val.getImpl(), b.val.getImpl(), b.loc);
}

inline Value inv(Value a, SourceLoc loc = SourceLoc::current()) {
  return getGlobalContext()->inv(a.getImpl(), loc);
}

inline Value nonzero(Value a, SourceLoc loc = SourceLoc::current()) {
  return getGlobalContext()->nonzero(a.getImpl(), loc);
}

inline void equate(Value a, Value b, SourceLoc loc = SourceLoc::current()) {
  auto diff = getGlobalContext()->sub(a.getImpl(), b.getImpl(), loc);
  return getGlobalContext()->assertZero(diff, loc);
}

inline void risc0Log(const char* str, std::vector<Value> vals) {
  std::vector<std::shared_ptr<ValueImplBase>> impls;
  for (auto& val : vals) {
    impls.push_back(val.getImpl());
  }
  getGlobalContext()->log(str, impls);
}

inline std::array<Value, 4> divide(Value numerLow,
                                   Value numerHigh,
                                   Value denomLow,
                                   Value denomHigh,
                                   SourceLoc loc = SourceLoc::current()) {
  auto [v1, v2, v3, v4] = getGlobalContext()->divide32(
      numerLow.getImpl(), numerHigh.getImpl(), denomLow.getImpl(), denomHigh.getImpl(), loc);
  return {v1, v2, v3, v4};
}

inline void
memWrite(Value cycle, Value addr, Value low, Value high, SourceLoc loc = SourceLoc::current()) {
  getGlobalContext()->memWrite(cycle.getImpl(), addr.getImpl(), low.getImpl(), high.getImpl(), loc);
}

inline std::array<Value, 2> memRead(Value cycle, Value addr, SourceLoc loc = SourceLoc::current()) {
  auto [v1, v2] = getGlobalContext()->memRead(cycle.getImpl(), addr.getImpl(), loc);
  return {v1, v2};
}

inline std::array<Value, 5> memCheck(SourceLoc loc = SourceLoc::current()) {
  auto [v1, v2, v3, v4, v5] = getGlobalContext()->memCheck(loc);
  return {v1, v2, v3, v4, v5};
}

// RIAA style nondet region
class NondetGuard {
public:
  bool doNondet;
  NondetGuard(SourceLoc loc = SourceLoc::current())
      : doNondet(getGlobalContext()->beginNondet(loc)) {}
  ~NondetGuard() { getGlobalContext()->endNondet(); }
  operator bool() { return doNondet; }
};

// RIAA style group region
class GroupGuard {
public:
  GroupGuard(SourceLoc loc = SourceLoc::current()) { getGlobalContext()->beginGroup(loc); }
  ~GroupGuard() { getGlobalContext()->endGroup(); }
  operator bool() { return true; }
};

// RIAA style guard for if.
class IfGuard {
public:
  IfGuard(Value cond, SourceLoc loc = SourceLoc::current()) {
    getGlobalContext()->beginIf(cond.getImpl(), loc);
  }
  ~IfGuard() { getGlobalContext()->endIf(); }
  operator bool() { return true; }
};

// Macros for syntax
#define BYZ_NONDET if (auto nondetGuard = NondetGuard())
#define BYZ_GROUP if (auto groupGuard = GroupGuard())
#define BYZ_IF(cond) if (auto ifGuard = IfGuard(cond))

} // namespace risc0
