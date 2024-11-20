// Copyright 2024 RISC Zero, Inc.
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

#include "mlir/IR/MLIRContext.h"
#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"

#include <gtest/gtest.h>

using namespace testing;
using namespace zirgen;
using namespace zirgen::Zhlt;
using namespace zirgen::ZStruct;

struct TypeTest : public Test {
  std::unique_ptr<mlir::MLIRContext> context;
  mlir::MLIRContext* ctx;

  TypeTest() {
    mlir::DialectRegistry registry;
    registry.insert<zirgen::Zll::ZllDialect>();
    registry.insert<zirgen::ZStruct::ZStructDialect>();
    registry.insert<zirgen::Zhlt::ZhltDialect>();

    context = std::make_unique<mlir::MLIRContext>(registry);
    context->loadAllAvailableDialects();
    ctx = context.get();
  }
};

// LCS(NonReg, Val) = Val
TEST_F(TypeTest, LCSRegVal) {
  EXPECT_EQ(getLeastCommonSuper({getNondetRegType(ctx), getValType(ctx)}), getValType(ctx));
}

// LCS(Val, Array<Val, 3>) = Component
TEST_F(TypeTest, LCSValArray) {
  EXPECT_EQ(getLeastCommonSuper({getValType(ctx), ArrayType::get(ctx, getValType(ctx), 3)}),
            getComponentType(ctx));
}

// Is NondetReg coercible to Component?
TEST_F(TypeTest, CoerceRegComponent) {
  EXPECT_TRUE(isCoercibleTo(getNondetRegType(ctx), getComponentType(ctx)));
}

// Is NondetReg coercible to Val?
TEST_F(TypeTest, CoerceNondetRegVal) {
  EXPECT_TRUE(isCoercibleTo(getNondetRegType(ctx), getValType(ctx)));
}
