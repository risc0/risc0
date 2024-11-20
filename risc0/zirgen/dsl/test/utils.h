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

#pragma once

#include "zirgen/dsl/ast.h"
#include <string>

namespace zirgen {
namespace dsl {
namespace utils {
// Helper functions for more concise test-case implementations

// using namespace zirgen::dsl;
using Expr = ast::Expression::Ptr;
using ExprVec = ast::Expression::Vec;
using Stmt = ast::Statement::Ptr;
using StmtVec = ast::Statement::Vec;
using Param = ast::Parameter::Ptr;
using ParamVec = ast::Parameter::Vec;
using Comp = ast::Component::Ptr;
using CompVec = ast::Component::Vec;
using Mod = ast::Module::Ptr;
using std::make_unique;
using std::string;

template <typename T> string print(T&& node) {
  string result;
  llvm::raw_string_ostream output(result);
  node->print(output);
  return result;
}

/*
 * Utility for building and moving vectors of unique_ptrs inline. In some cases
 * this dramatically improves readability of AST declarations. For example, to
 * build the AST for Foo<1>(2) one could write:
 *
 * ExprVec typeArgs;
 * typeArgs.push_back(Literal(1));
 * ExprVec args;
 * args.push_back(Literal(2));
 * auto expected = Construct(
 *   Specialize(
 *     Ident("Foo"),
 *     std::move(typeArgs)
 *   ),
 *   std::move(args)
 * );
 *
 * Which can now be expressed like this:
 *
 * auto expected = Construct(
 *   Specialize(
 *     Ident("Foo"),
 *     arr(Literal(1))
 *   ),
 *   arr(Literal(2))
 * );
 */

template <typename T> void push_all(std::vector<T>& vec, T first) {
  vec.push_back(std::move(first));
}

template <typename T, typename... Elems>
void push_all(std::vector<T>& vec, T first, Elems... rest) {
  vec.push_back(std::move(first));
  push_all(vec, std::forward<Elems>(rest)...);
}

template <typename T, typename... Elems> std::vector<T> arr(T&& first, Elems... elems) {
  std::vector<T> array;
  push_all(array, std::move(first), std::forward<Elems>(elems)...);
  return array;
}

// AST Builders
Param Parameter(string name, Expr&& type, bool isVariadic = false);
Expr Literal(uint64_t value);
Expr StringLiteral(string value);
Expr Ident(string name);
Expr Lookup(Expr&& component, string member);
Expr Subscript(Expr&& array, Expr&& element);
Expr Specialize(Expr&& type, ExprVec&& args);
Stmt Definition(string name, Expr&& value, bool isGlobal = false);
Stmt Declaration(string name, Expr&& type, bool isGlobal = false);
Stmt Constraint(Expr&& lhs, Expr&& rhs);
Stmt Void(Expr&& expression);
Expr Block(StmtVec&& body, Expr value);
Expr Construct(Expr&& type, ExprVec&& args);
Expr Construct(string ident, ExprVec&& args);
Expr Map(Expr&& array, string element, Expr&& function);
Expr Reduce(Expr&& array, Expr&& init, Expr&& type);
Expr Switch(Expr&& selector, ExprVec&& cases, bool isMajor = false);
Expr Range(Expr&& start, Expr&& end);
Expr ArrayLiteral(ExprVec&& elements);
Comp Component(string name, ParamVec&& tp, ParamVec&& p, Expr&& body);
Comp Function(string name, ParamVec&& tp, ParamVec&& p, Expr&& body);
Comp Extern(string name, ParamVec&& p, Expr&& resultType);
Mod Module(CompVec&& components);
Expr Back(Expr&& body, Expr&& distance);
Expr Isz(Expr&& value);

inline Expr component() {
  return Construct(Ident("Component"), {});
}

} // namespace utils
} // namespace dsl
} // namespace zirgen
