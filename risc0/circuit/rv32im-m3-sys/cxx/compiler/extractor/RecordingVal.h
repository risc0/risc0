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

struct RecordingContext;

struct RecordingVal {
    mlir::Value value;

    RecordingVal();
    RecordingVal(mlir::Value v) : value(v) {}
    RecordingVal(uint32_t c);
    RecordingVal(risc0::Fp c);

    RecordingVal operator+(const RecordingVal& other) const;
    RecordingVal operator+=(const RecordingVal& other) {
      return *this = *this + other;
    }
    RecordingVal operator-(const RecordingVal& other) const;
    RecordingVal operator-=(const RecordingVal& other) {
      return *this = *this - other;
    }
    RecordingVal operator-() const;
    RecordingVal operator*(const RecordingVal& other) const;
    RecordingVal operator*=(const RecordingVal& other) {
      return *this = *this * other;
    }
    bool operator==(const RecordingVal& other) const;

    static void setContext(RecordingContext* ctx) {
        context = ctx;
    }

    static RecordingContext* getContext() {
        return context;
    }

    operator risc0::Fp() const {
      return risc0::Fp();
    }
    
    uint32_t asUInt32() const {
      // This should only happen in witgen
      throw std::runtime_error("Call to asUInt32() in RecordingVal");
    }

protected:
    static RecordingContext* context;
};

// TODO
struct RecordingValExt {
  RecordingValExt() {}
  explicit RecordingValExt(risc0::FpExt v) {}
  explicit RecordingValExt(RecordingVal v) {}
  explicit RecordingValExt(RecordingVal v0, RecordingVal v1, RecordingVal v2, RecordingVal v3) {}

  // Never called in constraint code, only witgen
  RecordingVal elem(size_t i) { throw std::runtime_error("Not implemented"); }

  RecordingValExt operator+(RecordingValExt rhs) const {
    return RecordingValExt();
  }
  RecordingValExt operator-(RecordingValExt rhs) const {
    return RecordingValExt();
  }
  RecordingValExt operator*(RecordingValExt rhs) const {
    return RecordingValExt();
  }
  RecordingValExt operator*(RecordingVal rhs) const {
    return RecordingValExt();
  }
  RecordingValExt& operator+=(RecordingValExt rhs) {
    return *this;
  }
  RecordingValExt& operator*=(RecordingValExt rhs) {
    return *this;
  }
};

