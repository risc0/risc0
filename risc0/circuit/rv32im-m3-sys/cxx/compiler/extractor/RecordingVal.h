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

#pragma once

#include "zirgen/Dialect/Zll/IR/IR.h"
#include "zkp/fp.h"
#include "zkp/fpext.h"

struct BuilderSingleton {
  static void set(mlir::OpBuilder* value) { builder = value; }
  static mlir::OpBuilder* get() { return builder; }
    
protected:
  static mlir::OpBuilder* builder;
};


struct RecordingVal {
  mlir::Value value;

  RecordingVal();
  RecordingVal(mlir::Value v) : value(v) {} 
  RecordingVal(uint32_t c);
  RecordingVal(risc0::Fp c);

  RecordingVal operator+(const RecordingVal& rhs) const;
  RecordingVal operator+=(const RecordingVal& rhs) {
    return *this = *this + rhs;
  }
  RecordingVal operator-(const RecordingVal& rhs) const;
  RecordingVal operator-=(const RecordingVal& rhs) {
    return *this = *this - rhs;
  }
  RecordingVal operator-() const;
  RecordingVal operator*(const RecordingVal& rhs) const;
  RecordingVal operator*=(const RecordingVal& rhs) {
    return *this = *this * rhs;
  }

  operator risc0::Fp() const {
    return risc0::Fp();
  }
};

struct RecordingValExt {
  mlir::Value value;

  RecordingValExt();
  RecordingValExt(uint32_t x);
  RecordingValExt(mlir::Value v) : value(v) {}
  explicit RecordingValExt(risc0::FpExt v);
  explicit RecordingValExt(RecordingVal v);
  explicit RecordingValExt(RecordingVal v0, RecordingVal v1, RecordingVal v2, RecordingVal v3);

  RecordingValExt operator+(RecordingValExt rhs) const;
  RecordingValExt operator-(RecordingValExt rhs) const;
  RecordingValExt operator*(RecordingValExt rhs) const;
  RecordingValExt operator*(RecordingVal rhs) const;
  RecordingValExt& operator+=(RecordingValExt rhs) {
    return *this = *this + rhs;
  }
  RecordingValExt& operator*=(RecordingValExt rhs) {
    return *this = *this * rhs;
  }
  RecordingValExt& operator*=(RecordingVal rhs) {
    return *this = *this * rhs;
  }
};
