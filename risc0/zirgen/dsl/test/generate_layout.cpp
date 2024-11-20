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

#include "zirgen/Dialect/ZStruct/IR/TypeUtils.h"
#include "zirgen/dsl/Analysis/LayoutDAGAnalysis.h"
#include <gtest/gtest.h>

using namespace mlir;
using namespace zirgen::dsl;
using namespace zirgen::ZStruct;

class LayoutDAGTest : public testing::Test {
protected:
  LayoutDAGTest() {
    ctx.getOrLoadDialect<ZStructDialect>();
    ref = getRefType(&ctx);
  }

  LayoutDAG::Ptr makeReg() { return std::make_shared<LayoutDAG>(AbstractRegister{ref}); }

  LayoutDAG::Ptr makeArray(std::initializer_list<LayoutDAG::Ptr> elements) {
    Type elemType = (*elements.begin())->getType();
    auto type = LayoutArrayType::get(&ctx, elemType, elements.size());
    return std::make_shared<LayoutDAG>(AbstractArray{type, elements});
  }

  LayoutDAG::Ptr makeStr(LayoutType type,
                         SmallVector<std::pair<StringAttr, LayoutDAG::Ptr>> fields) {
    return std::make_shared<LayoutDAG>(AbstractStructure{type, fields});
  }

  MLIRContext ctx;
  RefType ref;
};

TEST_F(LayoutDAGTest, unify_reg_simple) {
  LayoutDAG::Ptr r1 = makeReg();
  LayoutDAG::Ptr r2 = makeReg();
  ASSERT_NE(r1, r2);

  // Unification should succeed, and r1 and r2 should subsequently resolve to
  // the same layout object
  EXPECT_TRUE(succeeded(LayoutDAG::unify(r1, r2)));
  EXPECT_EQ(&r1->resolve(), &r2->resolve());
}

TEST_F(LayoutDAGTest, unify_reg_self) {
  auto r1 = makeReg();

  // r1 should trivially unify with itself; in particular, r1 must not become
  // a pointer to itself as this makes r1->resolve() loop infinitely
  EXPECT_TRUE(succeeded(LayoutDAG::unify(r1, r1)));
  EXPECT_TRUE(std::holds_alternative<AbstractRegister>(*r1));
}

TEST_F(LayoutDAGTest, unify_reg_triple_1) {
  LayoutDAG::Ptr r1 = makeReg();
  LayoutDAG::Ptr r2 = makeReg();
  LayoutDAG::Ptr r3 = makeReg();

  EXPECT_TRUE(succeeded(LayoutDAG::unify(r1, r2)));
  EXPECT_TRUE(succeeded(LayoutDAG::unify(r2, r3)));
  EXPECT_EQ(&r1->resolve(), &r2->resolve());
  EXPECT_EQ(&r2->resolve(), &r3->resolve());
}

TEST_F(LayoutDAGTest, unify_reg_triple_2) {
  LayoutDAG::Ptr r1 = makeReg();
  LayoutDAG::Ptr r2 = makeReg();
  LayoutDAG::Ptr r3 = makeReg();

  EXPECT_TRUE(succeeded(LayoutDAG::unify(r1, r2)));
  EXPECT_TRUE(succeeded(LayoutDAG::unify(r3, r2)));
  EXPECT_EQ(&r1->resolve(), &r2->resolve());
  EXPECT_EQ(&r2->resolve(), &r3->resolve());
}

TEST_F(LayoutDAGTest, unify_array_basic) {
  LayoutDAG::Ptr r1 = makeReg();
  LayoutDAG::Ptr r2 = makeReg();
  LayoutDAG::Ptr r3 = makeReg();
  LayoutDAG::Ptr r4 = makeReg();
  LayoutDAG::Ptr r5 = makeReg();
  LayoutDAG::Ptr r6 = makeReg();
  LayoutDAG::Ptr arr1 = makeArray({r1, r2, r3});
  LayoutDAG::Ptr arr2 = makeArray({r4, r5, r6});

  // Corresponding array elements are unified
  EXPECT_TRUE(succeeded(LayoutDAG::unify(arr1, arr2)));
  EXPECT_EQ(&r1->resolve(), &r4->resolve());
  EXPECT_EQ(&r2->resolve(), &r5->resolve());
  EXPECT_EQ(&r3->resolve(), &r6->resolve());
}

TEST_F(LayoutDAGTest, unify_array_complex) {
  LayoutDAG::Ptr r1 = makeReg();
  LayoutDAG::Ptr r2 = makeReg();
  LayoutDAG::Ptr r3 = makeReg();
  LayoutDAG::Ptr r4 = makeReg();
  LayoutDAG::Ptr r5 = makeReg();
  LayoutDAG::Ptr r6 = makeReg();
  LayoutDAG::Ptr arr1 = makeArray({r1, r2, r3});
  LayoutDAG::Ptr arr2 = makeArray({r4, r5, r6});

  // By transitivity, all registers should be unified!
  EXPECT_TRUE(succeeded(LayoutDAG::unify(r1, r3)));
  EXPECT_TRUE(succeeded(LayoutDAG::unify(r1, r5)));
  EXPECT_TRUE(succeeded(LayoutDAG::unify(arr1, arr2)));
  EXPECT_EQ(&r1->resolve(), &r2->resolve());
  EXPECT_EQ(&r1->resolve(), &r3->resolve());
  EXPECT_EQ(&r1->resolve(), &r4->resolve());
  EXPECT_EQ(&r1->resolve(), &r5->resolve());
  EXPECT_EQ(&r1->resolve(), &r6->resolve());
}

TEST_F(LayoutDAGTest, unify_struct_basic) {
  auto a = StringAttr::get(&ctx, "a");
  auto b = StringAttr::get(&ctx, "b");
  SmallVector<FieldInfo> members;
  members.push_back({a, ref});
  members.push_back({b, ref});
  auto type = LayoutType::get(&ctx, "Foo", members);

  LayoutDAG::Ptr r1 = makeReg();
  LayoutDAG::Ptr r2 = makeReg();
  LayoutDAG::Ptr r3 = makeReg();
  LayoutDAG::Ptr r4 = makeReg();
  LayoutDAG::Ptr str1 = makeStr(type, {{a, r1}, {b, r2}});
  LayoutDAG::Ptr str2 = makeStr(type, {{a, r3}, {b, r4}});

  ASSERT_NE(str1, str2);
  EXPECT_TRUE(succeeded(LayoutDAG::unify(str1, str2)));
  EXPECT_EQ(&r1->resolve(), &r3->resolve());
  EXPECT_EQ(&r2->resolve(), &r4->resolve());
}

TEST_F(LayoutDAGTest, clone_basic) {
  LayoutDAG::Ptr r1 = makeReg();
  LayoutDAG::Ptr r2 = makeReg();
  LayoutDAG::Ptr arr = makeArray({r1, r2});
  LayoutDAG::Ptr r3 = makeReg();

  auto a = StringAttr::get(&ctx, "a");
  auto b = StringAttr::get(&ctx, "b");
  SmallVector<FieldInfo> members;
  members.push_back({a, arr->getType()});
  members.push_back({b, r3->getType()});
  auto type = LayoutType::get(&ctx, "Foo", members);

  LayoutDAG::Ptr str = makeStr(type, {{a, arr}, {b, r3}});

  // Cloning a LayoutDAG should produce a distinct but structurally equal DAG.
  // This means all pointers should be different after cloning, but it should
  // successfully unify with the original. Furthermore, after unification, all
  // corresponding registers in the DAGs should resolve to the same layout
  // columns.
  LayoutDAG::Ptr str2 = LayoutDAG::clone(str);
  EXPECT_NE(str, str2);
  EXPECT_NE(str->lookup(a), str2->lookup(a));
  EXPECT_NE(str->lookup(a)->subscript(0), str2->lookup(a)->subscript(0));
  EXPECT_NE(str->lookup(a)->subscript(1), str2->lookup(a)->subscript(1));
  EXPECT_NE(str->lookup(b), str2->lookup(b));

  EXPECT_TRUE(succeeded(LayoutDAG::unify(str, str2)));
  EXPECT_EQ(&str->lookup(a)->subscript(0)->resolve(), &str2->lookup(a)->subscript(0)->resolve());
  EXPECT_EQ(&str->lookup(a)->subscript(1)->resolve(), &str2->lookup(a)->subscript(1)->resolve());
  EXPECT_EQ(&str->lookup(b)->resolve(), &str2->lookup(b)->resolve());
}

TEST_F(LayoutDAGTest, clone_ref) {
  LayoutDAG::Ptr r1 = makeReg();
  LayoutDAG::Ptr r2 = std::make_shared<LayoutDAG>(r1);
  LayoutDAG::Ptr arr = makeArray({r1, r2});

  // LayoutDAGs with multiple pointers to the same sublayout should only clone
  // it once. The structure of the DAG should be preserved.
  ASSERT_EQ(&arr->subscript(0)->resolve(), &arr->subscript(1)->resolve());
  LayoutDAG::Ptr arr2 = LayoutDAG::clone(arr);

  // The clone should use entirely different objects from the original
  EXPECT_NE(arr, arr2);
  EXPECT_NE(&arr->subscript(0)->resolve(), &arr2->subscript(0)->resolve());
  EXPECT_NE(&arr->subscript(1)->resolve(), &arr2->subscript(1)->resolve());

  // The clone should have the same structure as the original
  EXPECT_EQ(&arr2->subscript(0)->resolve(), &arr2->subscript(1)->resolve());
}
