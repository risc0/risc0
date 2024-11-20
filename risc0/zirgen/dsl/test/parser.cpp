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

#include "zirgen/dsl/parser.h"
#include "zirgen/dsl/test/utils.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace zirgen::dsl::utils;
using std::string;

namespace {

llvm::SourceMgr streamManager(const std::string& str) {
  llvm::SourceMgr mgr;
  auto buffer = llvm::MemoryBuffer::getMemBuffer(str, "test.zir");
  mgr.AddNewSourceBuffer(std::move(buffer), llvm::SMLoc());
  return mgr;
}

// A wrapper around parser to expose some of its protected methods for testing
class WrappedParser : public zirgen::dsl::Parser {
public:
  WrappedParser(llvm::SourceMgr& mgr) : Parser(mgr) {}

  zirgen::dsl::ast::Component::Ptr parseComponent() { return Parser::parseComponent(); }
  zirgen::dsl::ast::Block::Ptr parseBlock() { return Parser::parseBlock(); }
  zirgen::dsl::ast::Expression::Ptr parseExpression() { return Parser::parseExpression(0); }
};

// A wrapper around a WrappedParser which owns the buffer being parsed and
// encapsulates the SourceMgr
class TestParser {
public:
  TestParser(std::string src) : source(std::move(src)), mgr(streamManager(source)), parser(mgr) {}

  zirgen::dsl::ast::Component::Ptr parseComponent() { return parser.parseComponent(); }
  zirgen::dsl::ast::Block::Ptr parseBlock() { return parser.parseBlock(); }
  zirgen::dsl::ast::Expression::Ptr parseExpression() { return parser.parseExpression(); }

  ~TestParser() { checkErrors(); }

private:
  void checkErrors() {
    if (!parser.getErrors().empty()) {
      for (auto error : parser.getErrors()) {
        llvm::errs() << error.getMessage() << "\n";
      }
    }
    EXPECT_EQ(parser.getErrors().size(), 0);
  }

  std::string source;
  llvm::SourceMgr mgr;
  WrappedParser parser;
};

} // namespace

//
// Expression parsing
//

TEST(parser, decimal_literal) {
  TestParser parser("2013265919");
  auto expected = Literal(2013265919);
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, hex_literal) {
  TestParser parser("0xffffffff");
  auto expected = Literal(0xffffffff);
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, binary_literal) {
  TestParser parser("0b0101");
  auto expected = Literal(0b0101);
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, empty_string) {
  TestParser parser("\"\"");
  auto expected = StringLiteral("");
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, nonempty_string) {
  TestParser parser("\"Hello, world!\"");
  auto expected = StringLiteral("Hello, world!");
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, lower_camel_case_identifier) {
  TestParser parser("lowerCamelCase");
  auto expected = Ident("lowerCamelCase");
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, upper_camel_case_identifier) {
  TestParser parser("UpperCamelCase");
  auto expected = Ident("UpperCamelCase");
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, snake_case_identifier) {
  TestParser parser("_snake_case");
  auto expected = Ident("_snake_case");
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, map) {
  TestParser parser("for i : arr { i }");
  auto expected = Map(Ident("arr"), "i", Block({}, Ident("i")));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, reduce) {
  TestParser parser("reduce arr init 0 with Add");
  auto expected = Reduce(Ident("arr"), Literal(0), Ident("Add"));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, conditional_if_else) {
  TestParser parser("if (x) { y } else { z }");

  // desuggars to [x, (1 - x)] -> ({ y }, { z })"
  auto expected =
      Switch(ArrayLiteral(arr(Ident("x"), Construct(Ident("Sub"), arr(Literal(1), Ident("x"))))),
             arr(Block({}, Ident("y")), Block({}, Ident("z"))));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, conditional_if) {
  TestParser parser("if (x) { y }");

  // desuggars to [x] -> ({ y })"
  auto expected = Switch(ArrayLiteral(arr(Ident("x"))), arr(Block({}, Ident("y"))));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, back) {
  TestParser parser("x@1");

  auto expected = Back(Ident("x"), Literal(1));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, array_literal) {
  TestParser parser("[1, 2, 3]");
  auto expected = ArrayLiteral(arr(Literal(1), Literal(2), Literal(3)));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, empty_array_literal) {
  TestParser parser("[]");
  auto expected = ArrayLiteral({});
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, lookup) {
  TestParser parser("foo.member");
  auto expected = Lookup(Ident("foo"), "member");
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, subscript) {
  TestParser parser("arr[2]");
  auto expected = Subscript(Ident("arr"), Literal(2));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, specialize) {
  TestParser parser("Custom<Bar, 2>");
  auto expected = Specialize(Ident("Custom"), arr(Ident("Bar"), Literal(2)));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, construct_simple) {
  TestParser parser("Foo()");
  auto expected = Construct(Ident("Foo"), {});
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, construct_with_one_arg) {
  TestParser parser("Foo(0x10)");
  auto expected = Construct(Ident("Foo"), arr(Literal(0x10)));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, construct_with_multiple_args) {
  TestParser parser("Foo(0b111, baz, baz.subcomponent)");
  auto expected = Construct(
      Ident("Foo"), arr(Literal(0b111), Ident("baz"), Lookup(Ident("baz"), "subcomponent")));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, construct_with_type_args) {
  TestParser parser("Foo<Bar>(baz)");
  auto expected = Construct(Specialize(Ident("Foo"), arr(Ident("Bar"))), arr(Ident("baz")));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, switch) {
  TestParser parser("sel -> (1, 2)");
  auto expected = Switch(Ident("sel"), arr(Literal(1), Literal(2)));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, infix_add) {
  TestParser parser("1 + x");
  auto expected = Construct(Ident("Add"), arr(Literal(1), Ident("x")));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, infix_sub) {
  TestParser parser("1 - x");
  auto expected = Construct(Ident("Sub"), arr(Literal(1), Ident("x")));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, infix_mul) {
  TestParser parser("1 * x");
  auto expected = Construct(Ident("Mul"), arr(Literal(1), Ident("x")));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, infix_div) {
  TestParser parser("1 / x");
  auto expected = Construct(Ident("Div"), arr(Literal(1), Ident("x")));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, infix_add_mul_prec) {
  TestParser parser("1 + x * 2");
  auto expected = Construct(Ident("Add"),
                            arr(Literal(1), Construct(Ident("Mul"), arr(Ident("x"), Literal(2)))));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, infix_add_mul_prec_2) {
  TestParser parser("1 + 5 * 10 * x");
  auto expected = Construct(
      Ident("Add"),
      arr(Literal(1),
          Construct(Ident("Mul"),
                    arr(Construct(Ident("Mul"), arr(Literal(5), Literal(10))), Ident("x")))));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, infix_sub_div_prec) {
  TestParser parser("1 - x / 2");
  auto expected = Construct(Ident("Sub"),
                            arr(Literal(1), Construct(Ident("Div"), arr(Ident("x"), Literal(2)))));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, infix_complex_prec) {
  TestParser parser("x * (1 - x) + x * x");
  auto expected = Construct(
      Ident("Add"),
      arr(Construct(Ident("Mul"),
                    arr(Ident("x"), Construct(Ident("Sub"), arr(Literal(1), Ident("x"))))),
          Construct(Ident("Mul"), arr(Ident("x"), Ident("x")))));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, simple_neg) {
  TestParser parser("-2");
  auto expected = Construct("Neg", arr(Literal(2)));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, neg_and_mul) {
  TestParser parser("-1 * x");
  auto expected = Construct("Mul", arr(Construct("Neg", arr(Literal(1))), Ident("x")));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

TEST(parser, complex_neg) {
  TestParser parser("-(x + 1) - -(4 * -y) / 3");
  auto expected = Construct(
      "Sub",
      arr(Construct("Neg", arr(Construct("Add", arr(Ident("x"), Literal(1))))),
          Construct("Div",
                    arr(Construct("Neg",
                                  arr(Construct(
                                      "Mul", arr(Literal(4), Construct("Neg", arr(Ident("y"))))))),
                        Literal(3)))));
  EXPECT_EQ(*parser.parseExpression(), *expected);
}

//
// Block parsing
//

TEST(parser, trivial_block) {
  TestParser parser("{}");
  auto expected = Block({}, component());
  EXPECT_EQ(*parser.parseBlock(), *expected);
}

TEST(parser, member_definition) {
  TestParser parser("{ x := 7; }");
  auto expected = Block(arr(Definition("x", Literal(7))), component());
  EXPECT_EQ(*parser.parseBlock(), *expected);
}

TEST(parser, member_declaration) {
  TestParser parser("{ x : Val; }");
  auto expected = Block(arr(Declaration("x", Ident("Val"))), component());
  EXPECT_EQ(*parser.parseBlock(), *expected);
}

TEST(parser, constraint) {
  TestParser parser("{ x * (1 - x) = 0; }");
  auto expected =
      Block(arr(Constraint(
                Construct(Ident("Mul"),
                          arr(Ident("x"), Construct(Ident("Sub"), arr(Literal(1), Ident("x"))))),
                Literal(0))),
            component());
  EXPECT_EQ(*parser.parseBlock(), *expected);
}

TEST(parser, void) {
  TestParser parser("{ IsBit(x); }");
  auto expected = Block(arr(Void(Construct(Ident("IsBit"), arr(Ident("x"))))), component());
  EXPECT_EQ(*parser.parseBlock(), *expected);
}

TEST(parser, component) {
  TestParser parser("component Bit(x: Val) {\n"
                    "  r := Reg(x);\n"
                    "  IsBit(r);\n"
                    "  r\n"
                    "}\n");

  auto expected = Component("Bit",
                            {},
                            arr(Parameter("x", Ident("Val"))),
                            Block(arr(Definition("r", Construct(Ident("Reg"), arr(Ident("x")))),
                                      Void(Construct(Ident("IsBit"), arr(Ident("r"))))),
                                  Ident("r")));
  EXPECT_EQ(*parser.parseComponent(), *expected);
}

TEST(parser, block_with_block_super) {
  TestParser parser("{{}}");
  auto expected = Block({}, Block({}, component()));
  EXPECT_EQ(*parser.parseBlock(), *expected);
}

TEST(parser, block_with_block_member) {
  TestParser parser("{member := {};}");
  auto expected = Block(arr(Definition("member", Block({}, component()))), component());
  EXPECT_EQ(*parser.parseBlock(), *expected);
}

TEST(parser, block_with_void_block) {
  TestParser parser("{{};}");
  auto expected = Block(arr(Void(Block({}, component()))), component());
  EXPECT_EQ(*parser.parseBlock(), *expected);
}

TEST(parser, block_with_blocks) {
  TestParser parser("{member := {}; {}; {}}");
  auto expected =
      Block(arr(Definition("member", Block({}, component())), Void(Block({}, component()))),
            Block({}, component()));
  EXPECT_EQ(*parser.parseBlock(), *expected);
}

TEST(parser, function) {
  TestParser parser("function Bit(x: Val) {\n"
                    "  r := Reg(x);\n"
                    "  IsBit(r);\n"
                    "  r\n"
                    "}\n");

  auto expected = Function("Bit",
                           {},
                           arr(Parameter("x", Ident("Val"))),
                           Block(arr(Definition("r", Construct(Ident("Reg"), arr(Ident("x")))),
                                     Void(Construct(Ident("IsBit"), arr(Ident("r"))))),
                                 Ident("r")));
  EXPECT_EQ(*parser.parseComponent(), *expected);
}

TEST(parser, extern_no_return) {
  TestParser parser("extern MyExtern(x: Val);\n");

  auto expected = Extern("MyExtern", arr(Parameter("x", Ident("Val"))), Ident("Component"));
  auto c = parser.parseComponent();
  EXPECT_EQ(*c, *expected);
}

TEST(parser, extern_no_args) {
  TestParser parser("extern MyExtern();\n");

  auto expected = Extern("MyExtern", {}, Ident("Component"));
  auto c = parser.parseComponent();
  EXPECT_EQ(*c, *expected);
}

TEST(parser, extern_multi_args_returns_val) {
  TestParser parser("extern MyExtern(x: Val, y: Val) : Val;\n");

  auto expected = Extern(
      "MyExtern", arr(Parameter("x", Ident("Val")), Parameter("y", Ident("Val"))), Ident("Val"));
  EXPECT_EQ(*parser.parseComponent(), *expected);
}
