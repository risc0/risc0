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

#include "core/log.h"
#include "core/util.h"

#include <algorithm>
#include <array>

#include "rv32im/circuit/verify.h"

namespace {

// Track degree
class DegVal {
private:
  uint32_t degree;
public:
  // Constants are degree 0
  DegVal() : degree(0) {}
  DegVal(uint32_t val) : degree(0) {}
  DegVal(Fp val) : degree(0) {}

  uint32_t getDegree() const { return degree; }
  static DegVal makeDegree(uint32_t degree) {
    DegVal val(0);
    val.degree = degree;
    return val;
  }

  DegVal operator+(const DegVal& rhs) const {
    return makeDegree(std::max(degree, rhs.degree));
  }
  DegVal operator-(const DegVal& rhs) const {
    return makeDegree(std::max(degree, rhs.degree));
  }
  DegVal operator*(const DegVal& rhs) const {
    return makeDegree(degree + rhs.degree);
  }
  DegVal operator-() const {
    return *this;
  }
  DegVal& operator+=(const DegVal& rhs) {
    degree = std::max(degree, rhs.degree);
    return *this;
  }
  DegVal& operator*=(const DegVal& rhs) {
    degree += rhs.degree;
    return *this;
  }
};

class DegValExt {
private:
  uint32_t degree;
public:
  DegValExt() : degree(0) {}
  explicit DegValExt(FpExt x) : degree(0) {}
  explicit DegValExt(DegVal e0) : degree(e0.getDegree()) {}
  explicit DegValExt(DegVal e0, DegVal e1, DegVal e2, DegVal e3) 
    : degree(std::max({e0.getDegree(), e1.getDegree(), e2.getDegree(), e3.getDegree()})) {}
  explicit DegValExt(uint32_t x) : degree(0) {}

  uint32_t getDegree() const { return degree; }
  static DegValExt makeDegree(uint32_t degree) {
    DegValExt val(0);
    val.degree = degree;
    return val;
  }

  DegValExt operator+(const DegValExt& rhs) const { 
    return DegValExt::makeDegree(std::max(degree, rhs.degree)); 
  }
  DegValExt operator-(const DegValExt& rhs) const {
    return DegValExt::makeDegree(std::max(degree, rhs.degree)); 
  }

  DegValExt operator*(const DegVal& rhs) const {
    return DegValExt::makeDegree(degree + rhs.getDegree()); 
  }
  DegValExt operator*(const DegValExt& rhs) const {
    return DegValExt::makeDegree(degree + rhs.degree); 
  }
  DegValExt& operator+=(const DegValExt& rhs) {
    degree = std::max(degree, rhs.degree);
    return *this; 
  }
  DegValExt& operator*=(const DegValExt& rhs) {
    degree += rhs.degree;
    return *this; 
  }
  DegValExt& operator*=(const DegVal& rhs) { 
    degree += rhs.getDegree();
    return *this; 
  }
};

struct DegReg {
  DegVal get() { return DegVal::makeDegree(1); }
  template<typename T, typename C> void applyInner(C& ctx) {}
  template<typename C> void verify(C& ctx) {}
  template<typename C> void addArguments(C& ctx) {}
};

} // namespace 

namespace risc0::rv32im {

size_t computeMaxDegree(bool tune) {
  // TODO: proper sizes
  std::vector<DegReg> fakeRegs(1000);
  std::vector<DegVal> globals(1000);
  std::vector<DegValExt> fakeMixing(1000, DegValExt());
  DegReg* fakePtr = fakeRegs.data();
  DegValExt r = verifyCircuit(fakePtr, fakePtr, fakePtr, globals.data(), fakeMixing.data(), DegValExt(), DegVal::makeDegree(1));
  return r.getDegree();
}

} // namespace risc0::rv32im
