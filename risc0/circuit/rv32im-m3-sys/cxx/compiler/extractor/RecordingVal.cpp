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

#include "RecordingVal.h"
#include "compiler/extractor/RecordingContext.h"
#include "compiler/extractor/RecordingVal.h"
#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"

using namespace mlir;

RecordingContext* RecordingVal::context;

RecordingVal::RecordingVal() {
    OpBuilder& builder = context->builder;
    this->value = builder.create<zirgen::Zll::ConstOp>(builder.getUnknownLoc(), 0);
}

RecordingVal::RecordingVal(uint32_t c) {
    OpBuilder& builder = context->builder;
    this->value = builder.create<zirgen::Zll::ConstOp>(builder.getUnknownLoc(), c);
}

RecordingVal::RecordingVal(risc0::Fp c) : RecordingVal(c.asUInt32()) {}

RecordingVal RecordingVal::operator+(const RecordingVal& other) const {
    OpBuilder& builder = context->builder;
    return RecordingVal(builder.create<zirgen::Zll::AddOp>(builder.getUnknownLoc(), this->value, other.value));
}

RecordingVal RecordingVal::operator-(const RecordingVal& other) const {
    OpBuilder& builder = context->builder;
    return RecordingVal(builder.create<zirgen::Zll::SubOp>(builder.getUnknownLoc(), this->value, other.value));
}

RecordingVal RecordingVal::operator-() const {
    OpBuilder& builder = context->builder;
    return RecordingVal(builder.create<zirgen::Zll::NegOp>(builder.getUnknownLoc(), this->value));
}

RecordingVal RecordingVal::operator*(const RecordingVal& other) const {
    OpBuilder& builder = context->builder;
    return RecordingVal(builder.create<zirgen::Zll::MulOp>(builder.getUnknownLoc(), this->value, other.value));
}

bool RecordingVal::operator==(const RecordingVal& other) const {
    assert(false && "Equality check not implemented in RecordingVal");
    return false;
}

