// Copyright 2026 RISC Zero, Inc.
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

#pragma once

#include <ff/baby_bear.hpp>

class Fp {
private:
  bb31_base val;

public:
  __device__ constexpr inline Fp() : val(0) {}
  __device__ constexpr inline Fp(bb31_base val) : val(val) {}
  __device__ constexpr inline Fp(uint32_t a) : val(int(a)) {}

  __device__ inline bb31_t innerVal() const { return bb31_t(val); }
  __device__ inline uint32_t asUInt32() const { return uint32_t(val); }

  __device__ inline Fp operator+(Fp rhs) const { return val + rhs.val; }
  __device__ inline Fp operator-() const { return -val; }
  __device__ inline Fp operator-(Fp rhs) const { return val - rhs.val; }
  __device__ inline Fp operator*(Fp rhs) const { return val * rhs.val; }

  __device__ inline Fp& operator+=(Fp rhs) {
    val += rhs.val;
    return *this;
  }
  __device__ inline Fp& operator-=(Fp rhs) {
    val -= rhs.val;
    return *this;
  }
  __device__ inline Fp& operator*=(Fp rhs) {
    val *= rhs.val;
    return *this;
  }

  __device__ inline Fp inv() { return val.reciprocal(); }
  __device__ inline Fp pow(uint32_t i) { return val ^ i; }

  __device__ inline bool operator==(Fp rhs) const { return asUInt32() == rhs.asUInt32(); }
  __device__ inline bool operator!=(Fp rhs) const { return asUInt32() != rhs.asUInt32(); }
};

__device__ inline Fp inv(Fp val) {
  return val.inv();
}

__device__ inline Fp pow(Fp val, uint32_t i) {
  return val.pow(i);
}

__device__ inline uint32_t asUInt32(Fp val) {
  return val.asUInt32();
}

class FpExt {
private:
  bb31_4_t val;

public:
  __device__ inline FpExt() { val.zero(); }
  __device__ inline FpExt(int val) : val(val) {}
  __device__ inline FpExt(Fp val) : val(bb31_t(val.innerVal())) {}
  __device__ inline FpExt(bb31_4_t val) : val(val) {}
  __device__ inline FpExt(int a, int b, int c, int d) : val(a, b, c, d) {}
  __device__ inline FpExt(Fp a, Fp b, Fp c, Fp d)
      : val(a.asUInt32(), b.asUInt32(), c.asUInt32(), d.asUInt32()) {}

  __device__ inline Fp elem(size_t i) { return val[i]; }

  __device__ inline FpExt operator+(FpExt rhs) const { return val + rhs.val; }
  __device__ inline FpExt operator-(FpExt rhs) const { return val - rhs.val; }
  __device__ inline FpExt operator*(FpExt rhs) const { return val * rhs.val; }

  __device__ inline FpExt operator+(Fp rhs) const { return val + rhs.innerVal(); }
  __device__ inline FpExt operator-(Fp rhs) const { return val - rhs.innerVal(); }
  __device__ inline FpExt operator*(Fp rhs) const { return val * rhs.innerVal(); }

  __device__ inline FpExt& operator+=(FpExt rhs) {
    val = val + rhs.val;
    return *this;
  }
  __device__ inline FpExt& operator-=(FpExt rhs) {
    val = val - rhs.val;
    return *this;
  }
  __device__ inline FpExt& operator*=(FpExt rhs) {
    val = val * rhs.val;
    return *this;
  }

  __device__ inline FpExt pow(uint32_t i) const { return val ^ i; }
  __device__ inline FpExt inv() const { return val.reciprocal(); }
};

__device__ inline Fp elem(FpExt a, size_t i) {
  return a.elem(i);
}

__device__ inline FpExt pow(FpExt val, uint32_t i) {
  return val.pow(i);
}

__device__ inline FpExt inv(FpExt val) {
  return val.inv();
}
