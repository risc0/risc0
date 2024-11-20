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

#include "zirgen/dsl/lower.h"
#include "zirgen/Dialect/ZHL/IR/ZHL.h"
#include "zirgen/dsl/ast.h"
#include "zirgen/dsl/test/utils.h"

#include "mlir/IR/MLIRContext.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include <gtest/gtest.h>
#include <memory>

using namespace zirgen::dsl;
using namespace zirgen::dsl::utils;

namespace {

std::string lowerAndPrint(Mod& mod) {
  mlir::MLIRContext ctx;
  llvm::SourceMgr mgr;
  ctx.getOrLoadDialect<zirgen::Zhl::ZhlDialect>();
  std::string errors;
  mlir::ScopedDiagnosticHandler handler(&ctx, [&](mlir::Diagnostic& diag) {
    if (!errors.empty()) {
      errors += "\n";
    }
    errors += diag.str();
  });
  auto result = lower(ctx, mgr, mod.get());
  return errors.empty() ? print(result) : errors;
}

std::string lowerAndPrint(Comp&& comp) {
  auto m = Module(arr(std::move(comp)));
  return lowerAndPrint(m);
}

} // namespace

TEST(lower, Bit) {
#if 0
  component Bit(x : Val) {
    r := Reg(x);
    IsBit(r);
    r;
  }
#endif
  auto makeBit = []() -> ast::Component::Ptr {
    ExprVec args;
    args.push_back(Ident("x"));
    Stmt def = Definition("r", Construct(Ident("Reg"), std::move(args)));
    Stmt cst = Void(Construct(Ident("IsBit"), arr(Ident("r"))));
    Expr res = Ident("r");
    StmtVec stmts;
    stmts.push_back(std::move(def));
    stmts.push_back(std::move(cst));
    Expr body = Block(std::move(stmts), std::move(res));
    ParamVec type_params;
    ParamVec params;
    params.push_back(Parameter("x", Ident("Val")));
    return Component("Bit", std::move(type_params), std::move(params), std::move(body));
  };

  string expect =
      R"(module {
  zhl.component @Bit {
    %0 = zhl.global "Val"
    %1 = zhl.parameter "x"(0) : %0
    %2 = zhl.global "Reg"
    %3 = zhl.construct %2(%1)
    %4 = zhl.declare "r"
    zhl.define %4 = %3
    %5 = zhl.global "IsBit"
    %6 = zhl.construct %5(%3)
    zhl.super %3
  }
}
)";
  EXPECT_EQ(expect, lowerAndPrint(makeBit()));
}

TEST(lower, Function) {
#if 0
  function Bit(x : Val) {
    r := Reg(x);
    IsBit(r);
    r;
  }
#endif
  auto makeBit = []() -> ast::Component::Ptr {
    ExprVec args;
    args.push_back(Ident("x"));
    Stmt def = Definition("r", Construct(Ident("Reg"), std::move(args)));
    Stmt cst = Void(Construct(Ident("IsBit"), arr(Ident("r"))));
    Expr res = Ident("r");
    StmtVec stmts;
    stmts.push_back(std::move(def));
    stmts.push_back(std::move(cst));
    Expr body = Block(std::move(stmts), std::move(res));
    ParamVec type_params;
    ParamVec params;
    params.push_back(Parameter("x", Ident("Val")));
    return Function("Bit", std::move(type_params), std::move(params), std::move(body));
  };

  string expect =
      R"(module {
  zhl.component @Bit attributes {function} {
    %0 = zhl.global "Val"
    %1 = zhl.parameter "x"(0) : %0
    %2 = zhl.global "Reg"
    %3 = zhl.construct %2(%1)
    %4 = zhl.declare "r"
    zhl.define %4 = %3
    %5 = zhl.global "IsBit"
    %6 = zhl.construct %5(%3)
    zhl.super %3
  }
}
)";
  EXPECT_EQ(expect, lowerAndPrint(makeBit()));
}

TEST(lower, Extern) {
#if 0
  extern Extern(x : XType, y : YType) : RetType;
#endif
  auto makeExtern = []() -> ast::Component::Ptr {
    return Extern("MyExtern",
                  arr(Parameter("x", Ident("XType")), Parameter("y", Ident("YType"))),
                  Ident("RetType"));
  };

  string expect =
      R"(module {
  zhl.component @MyExtern {
    %0 = zhl.global "XType"
    %1 = zhl.parameter "x"(0) : %0
    %2 = zhl.global "YType"
    %3 = zhl.parameter "y"(1) : %2
    %4 = zhl.global "RetType"
    %5 = zhl.extern "MyExtern"(%1, %3) : %4
    zhl.super %5
  }
}
)";
  EXPECT_EQ(expect, lowerAndPrint(makeExtern()));
}

TEST(lower, Loops) {
#if 0
  component ForExpr() {
    for i: [1, 2, 3] {
      i + 1
    }
  }
  component ReduceExpr() {
    reduce 0..10 init 0 with Add
  }
#endif
  auto makeMap = []() -> ast::Component::Ptr {
    StmtVec stmts;
    Expr range = ArrayLiteral(arr(Literal(1), Literal(2), Literal(3)));
    Expr add = Construct(Ident("Add"), arr(Ident("i"), Literal(1)));
    Expr res = Map(std::move(range), "i", std::move(add));
    Expr body = Block(std::move(stmts), std::move(res));
    ParamVec type_params;
    ParamVec params;
    return Component("ForExpr", std::move(type_params), std::move(params), std::move(body));
  };

  auto makeReduce = []() -> ast::Component::Ptr {
    StmtVec stmts;
    Expr range = Range(Literal(0), Literal(10));
    Expr init = Literal(0);
    Expr type = Ident("Add");
    Expr res = Reduce(std::move(range), std::move(init), std::move(type));
    Expr body = Block(std::move(stmts), std::move(res));
    ParamVec type_params;
    ParamVec params;
    return Component("ReduceExpr", std::move(type_params), std::move(params), std::move(body));
  };

  string expect =
      R"(module {
  zhl.component @ForExpr {
    %0 = zhl.literal 1
    %1 = zhl.literal 2
    %2 = zhl.literal 3
    %3 = zhl.array[%0, %1, %2]
    %4 = zhl.map %3 {
    ^bb0(%arg0: !zhl.expr):
      %5 = zhl.global "Add"
      %6 = zhl.literal 1
      %7 = zhl.construct %5(%arg0, %6)
      zhl.super %7
    }
    zhl.super %4
  }
  zhl.component @ReduceExpr {
    %0 = zhl.literal 0
    %1 = zhl.literal 10
    %2 = zhl.range %0, %1
    %3 = zhl.literal 0
    %4 = zhl.global "Add"
    %5 = zhl.reduce %2, %3, %4
    zhl.super %5
  }
}
)";

  auto mod = Module(arr(makeMap(), makeReduce()));
  EXPECT_EQ(expect, lowerAndPrint(mod));
}

TEST(lower, miniBack) {
#if 0
component Foo() {
  a := Reg(1);
  a@1
}
#endif
  auto makeFoo = []() -> ast::Component::Ptr {
    StmtVec stmts;
    Stmt def = Definition("a", Construct(Ident("Reg"), {Literal(1)}));
    stmts.push_back(std::move(def));
    Expr res = Back(Ident("a"), Literal(1));
    Expr body = Block(std::move(stmts), std::move(res));
    ParamVec type_params;
    ParamVec params;
    return Component("Foo", std::move(type_params), std::move(params), std::move(body));
  };

  string expect =
      R"(module {
  zhl.component @Foo {
    %0 = zhl.global "Reg"
    %1 = zhl.literal 1
    %2 = zhl.construct %0(%1)
    %3 = zhl.declare "a"
    zhl.define %3 = %2
    %4 = zhl.literal 1
    %5 = zhl.back %4, %2
    zhl.super %5
  }
}
)";
  EXPECT_EQ(expect, lowerAndPrint(makeFoo()));
}

TEST(lower, dupdefs) {
#if 0
component Foo(bar : Val) {
  bar : Reg; // legal to shadow a parameter
  bar := Reg(1); // legal to provide definition for declaration
  bar := 1; // error to define same name twice
  bar
}
#endif
  auto makeFoo = []() -> ast::Component::Ptr {
    StmtVec stmts;
    stmts.push_back(Declaration("bar", Ident("Reg")));
    stmts.push_back(Definition("bar", Construct(Ident("Reg"), arr(Literal(1)))));
    stmts.push_back(Definition("bar", Literal(1)));

    Expr body = Block(std::move(stmts), Ident("bar"));
    ParamVec type_params;
    ParamVec params;
    params.push_back(Parameter("bar", Ident("Val")));
    return Component("Foo", std::move(type_params), std::move(params), std::move(body));
  };

  string expect = "Only constructor parameters may be shadowed.\nConflicting definition of `bar`";
  auto mod = Module(arr(makeFoo()));
  EXPECT_EQ(expect, lowerAndPrint(mod));
}

TEST(lower, useUndefinedDecl) {
#if 0
component X() {
  a : b;
  a
}
#endif

  auto makeX = []() -> ast::Component::Ptr {
    StmtVec stmts;
    stmts.push_back(Declaration("a", Ident("b")));
    Expr body = Block(std::move(stmts), Ident("a"));
    ParamVec type_params, params;
    return Component("X", std::move(type_params), std::move(params), std::move(body));
  };

  string expect = "Cannot use undefined value of symbol `a`";
  EXPECT_EQ(expect, lowerAndPrint(makeX()));
}

TEST(lower, dupComponentNameError) {
#if 0
component X() {
  1
}
component X() {
  2
}
#endif
  auto makeX = [](unsigned i) -> ast::Component::Ptr {
    StmtVec stmts;
    Expr body = Literal(i);
    ParamVec type_params, func_params;
    return Component("X", std::move(type_params), std::move(func_params), std::move(body));
  };
  string expect = "Conflicting definition of `X`";
  auto mod = Module(arr(makeX(1), makeX(2)));
  EXPECT_EQ(expect, lowerAndPrint(mod));
}

TEST(lower, redefineBuiltin) {
// This little program will not actually work, but the lowering should be able
// to handle it without choking.
#if 0
component Foo() { Array<Val, 1>() }
component Array(a: Val) { a }
component Bar() { Array(1) }
#endif
  auto makeFoo = []() -> ast::Component::Ptr {
    StmtVec stmts;
    Expr arraytype = Specialize(Ident("Array"), arr(Ident("Val"), Literal(1)));
    ExprVec args;
    Expr body = Construct(std::move(arraytype), std::move(args));
    ParamVec type_params, func_params;
    return Component("Foo", std::move(type_params), std::move(func_params), std::move(body));
  };
  auto makeArray = []() -> ast::Component::Ptr {
    StmtVec stmts;
    Expr body = Ident("a");
    ParamVec type_params, func_params;
    func_params.push_back(Parameter("a", Ident("Val")));
    return Component("Array", std::move(type_params), std::move(func_params), std::move(body));
  };
  auto makeBar = []() -> ast::Component::Ptr {
    StmtVec stmts;
    Expr body = Construct(Ident("Array"), arr(Literal(1)));
    ParamVec type_params, func_params;
    return Component("Bar", std::move(type_params), std::move(func_params), std::move(body));
  };
  string expect =
      R"(module {
  zhl.component @Foo {
    %0 = zhl.global "Array"
    %1 = zhl.global "Val"
    %2 = zhl.literal 1
    %3 = zhl.specialize %0<%1, %2>
    %4 = zhl.construct %3()
    zhl.super %4
  }
  zhl.component @Array {
    %0 = zhl.global "Val"
    %1 = zhl.parameter "a"(0) : %0
    zhl.super %1
  }
  zhl.component @Bar {
    %0 = zhl.global "Array"
    %1 = zhl.literal 1
    %2 = zhl.construct %0(%1)
    zhl.super %2
  }
}
)";
  auto mod = Module(arr(makeFoo(), makeArray(), makeBar()));
  EXPECT_EQ(expect, lowerAndPrint(mod));
}

TEST(lower, invokeSelf) {
#if 0
component X() {
  X()
}
#endif
  auto makeX = []() -> ast::Component::Ptr {
    ExprVec args;
    StmtVec stmts;
    Expr body = Construct(Ident("X"), std::move(args));
    ParamVec type_params, func_params;
    return Component("X", std::move(type_params), std::move(func_params), std::move(body));
  };
  string expect =
      R"(module {
  zhl.component @X {
    %0 = zhl.global "X"
    %1 = zhl.construct %0()
    zhl.super %1
  }
}
)";
  auto mod = Module(arr(makeX()));
  EXPECT_EQ(expect, lowerAndPrint(mod));
}
