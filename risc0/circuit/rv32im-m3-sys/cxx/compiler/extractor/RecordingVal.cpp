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

#include "RecordingVal.h"
#include "compiler/extractor/RecordingContext.h"
#include "compiler/extractor/RecordingVal.h"
#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"

using namespace mlir;

mlir::OpBuilder* BuilderSingleton::builder = nullptr;

RecordingVal::RecordingVal() {
  OpBuilder& builder = *BuilderSingleton::get();
  this->value = builder.create<zirgen::Zll::ConstOp>(builder.getUnknownLoc(), 0);
}

RecordingVal::RecordingVal(uint32_t c) {
  OpBuilder& builder = *BuilderSingleton::get();
  this->value = builder.create<zirgen::Zll::ConstOp>(builder.getUnknownLoc(), c);
}

RecordingVal::RecordingVal(risc0::Fp c) : RecordingVal(c.asUInt32()) {}

RecordingVal RecordingVal::operator+(const RecordingVal& rhs) const {
  OpBuilder& builder = *BuilderSingleton::get();
  return RecordingVal(
      builder.create<zirgen::Zll::AddOp>(builder.getUnknownLoc(), this->value, rhs.value));
}

RecordingVal RecordingVal::operator-(const RecordingVal& rhs) const {
  OpBuilder& builder = *BuilderSingleton::get();
  return RecordingVal(
      builder.create<zirgen::Zll::SubOp>(builder.getUnknownLoc(), this->value, rhs.value));
}

RecordingVal RecordingVal::operator-() const {
  OpBuilder& builder = *BuilderSingleton::get();
  return RecordingVal(builder.create<zirgen::Zll::NegOp>(builder.getUnknownLoc(), this->value));
}

RecordingVal RecordingVal::operator*(const RecordingVal& rhs) const {
  OpBuilder& builder = *BuilderSingleton::get();
  return RecordingVal(
      builder.create<zirgen::Zll::MulOp>(builder.getUnknownLoc(), this->value, rhs.value));
}

RecordingValExt::RecordingValExt() {
  OpBuilder& builder = *BuilderSingleton::get();
  mlir::PolynomialAttr attr = mlir::PolynomialAttr::get(builder.getContext(), {0, 0, 0, 0});
  this->value = builder.create<zirgen::Zll::ConstOp>(builder.getUnknownLoc(), attr);
}

RecordingValExt::RecordingValExt(uint32_t x) {
  OpBuilder& builder = *BuilderSingleton::get();
  mlir::PolynomialAttr attr = mlir::PolynomialAttr::get(builder.getContext(), {x, 0, 0, 0});
  this->value = builder.create<zirgen::Zll::ConstOp>(builder.getUnknownLoc(), attr);
}

RecordingValExt::RecordingValExt(risc0::FpExt v) {
  OpBuilder& builder = *BuilderSingleton::get();
  mlir::PolynomialAttr attr = mlir::PolynomialAttr::get(
      builder.getContext(),
      {v.elem(0).asUInt32(), v.elem(1).asUInt32(), v.elem(2).asUInt32(), v.elem(3).asUInt32()});
  this->value = builder.create<zirgen::Zll::ConstOp>(builder.getUnknownLoc(), attr);
}

RecordingValExt::RecordingValExt(RecordingVal v) {
  // Technically, we don't need to do anything here since arithemetic ops in zll
  // are autocasting
  this->value = v.value;
}

RecordingValExt::RecordingValExt(RecordingVal v0,
                                 RecordingVal v1,
                                 RecordingVal v2,
                                 RecordingVal v3) {
  // TODO: Cache the constants somewhere
  RecordingValExt m1 = RecordingValExt(risc0::FpExt(0, 1, 0, 0));
  RecordingValExt m2 = RecordingValExt(risc0::FpExt(0, 0, 1, 0));
  RecordingValExt m3 = RecordingValExt(risc0::FpExt(0, 0, 0, 1));
  auto tot = RecordingValExt(v0) + m1 * v1 + m2 * v2 + m3 * v3;
  this->value = tot.value;
}

RecordingValExt RecordingValExt::operator+(RecordingValExt rhs) const {
  OpBuilder& builder = *BuilderSingleton::get();
  return RecordingValExt(
      builder.create<zirgen::Zll::AddOp>(builder.getUnknownLoc(), this->value, rhs.value));
}

RecordingValExt RecordingValExt::operator-(RecordingValExt rhs) const {
  OpBuilder& builder = *BuilderSingleton::get();
  return RecordingValExt(
      builder.create<zirgen::Zll::SubOp>(builder.getUnknownLoc(), this->value, rhs.value));
}

RecordingValExt RecordingValExt::operator*(RecordingValExt rhs) const {
  OpBuilder& builder = *BuilderSingleton::get();
  return RecordingValExt(
      builder.create<zirgen::Zll::MulOp>(builder.getUnknownLoc(), this->value, rhs.value));
}

RecordingValExt RecordingValExt::operator*(RecordingVal rhs) const {
  OpBuilder& builder = *BuilderSingleton::get();
  return RecordingValExt(
      builder.create<zirgen::Zll::MulOp>(builder.getUnknownLoc(), this->value, rhs.value));
}
