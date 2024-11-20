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

#include "zirgen/dsl/ast.h"
#include "zirgen/dsl/test/utils.h"

#include "llvm/Support/raw_ostream.h"

#include <gtest/gtest.h>
#include <memory>

using namespace zirgen::dsl;
using namespace utils;
using Expr = ast::Expression::Ptr;
using ExprVec = ast::Expression::Vec;
using Stmt = ast::Statement::Ptr;
using StmtVec = ast::Statement::Vec;
using std::string;

TEST(ast, Simple_Literal) {
  auto v = Literal(42);

  string expect = R"({"class":"Literal","value":42})";
  EXPECT_EQ(print(v), expect);
}

TEST(ast, Simple_Ident) {
  auto v = Ident("Hello");

  string expect = R"({"class":"Ident","name":"Hello"})";
  EXPECT_EQ(print(v), expect);
}

TEST(ast, Simple_Parameter) {
  auto v = Parameter("Foo", Ident("Bar"));

  string expect = R"({"name":"Foo","type":{"class":"Ident","name":"Bar"},"isVariadic":false})";
  EXPECT_EQ(print(v), expect);
}

TEST(ast, Array_Parameter) {
  ExprVec args;
  args.push_back(Ident("Frob"));
  args.push_back(Literal(23));
  Expr type = Specialize(Ident("Array"), std::move(args));
  auto v = Parameter("Widget", std::move(type));

  string expect = R"({"name":"Widget","type":{"class":"Specialize","type":)"
                  R"({"class":"Ident","name":"Array"},"args":)"
                  R"([{"class":"Ident","name":"Frob"},{"class":"Literal","value":23}]},)"
                  R"("isVariadic":false})";
  EXPECT_EQ(print(v), expect);
}

TEST(ast, Variadic_Parameter) {
  auto v = Parameter("foo", Ident("Val"), true);

  string expect = R"({"name":"foo","type":{"class":"Ident","name":"Val"},"isVariadic":true})";
}

TEST(ast, Lookup) {
  auto v = Lookup(Ident("some_object"), "some_member");

  string expect = R"({"class":"Lookup","component":)"
                  R"({"class":"Ident","name":"some_object"},"member":"some_member"})";
  EXPECT_EQ(print(v), expect);
}

TEST(ast, DefineAndResolve) {
  StmtVec stmts;
  stmts.push_back(Definition("plef", Literal(101)));
  auto v = Block(std::move(stmts), Ident("plef"));

  string expect = R"({"class":"Block","body":)"
                  R"([{"class":"Definition","name":"plef","value":)"
                  R"({"class":"Literal","value":101},"isGlobal":false}],)"
                  R"("value":{"class":"Ident","name":"plef"}})";
  EXPECT_EQ(print(v), expect);
}

TEST(ast, Construct) {
  ExprVec args;
  args.push_back(Ident("silver"));
  args.push_back(Ident("gold"));
  auto v = Construct(Ident("make"), std::move(args));

  string expect = R"({"class":"Construct","type":)"
                  R"({"class":"Ident","name":"make"},"args":)"
                  R"([{"class":"Ident","name":"silver"},)"
                  R"({"class":"Ident","name":"gold"}]})";
  EXPECT_EQ(print(v), expect);
}

TEST(ast, Back) {
  auto v = Back(Ident("x"), Literal(1));

  string expect = R"({"class":"Back",)"
                  R"("expression":{"class":"Ident","name":"x"},)"
                  R"("distance":{"class":"Literal","value":1}})";
  EXPECT_EQ(print(v), expect);
}
