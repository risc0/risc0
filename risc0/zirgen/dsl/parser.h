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
#include "zirgen/dsl/lexer.h"

#include "llvm/Support/SourceMgr.h"

namespace zirgen {
namespace dsl {

using namespace ast;

using BinaryOpPrecedence = int;

BinaryOpPrecedence getPrecedence(Token token);

class Parser {
public:
  Parser(llvm::SourceMgr& mgr) : sourceManager(mgr), lexer(mgr, errors), testNum(0) {}

  // Parses the file, and returns its AST if it is well formed. If it is not
  // well formed, it returns nullptr and the syntax errors that occurred can be
  // queried with the getErrors method. This method should only be called once
  // per Parser instance.
  ast::Module::Ptr parseModule();

  // Returns a list of syntax errors that occurred during parsing.
  const std::vector<llvm::SMDiagnostic>& getErrors() const { return errors; }

  // Adds the given preamble ZIR code to the lexer.
  void addPreamble(llvm::StringRef preambleText) { lexer.addPreamble(preambleText); }

protected:
  Component::Ptr parseComponent();
  Component::Ptr parseExtern();
  Component::Ptr parseTest();
  Block::Ptr parseBlock();

  // Parse a possible expression, returning nullptr if no expression found.
  Expression::Ptr parseExpression(BinaryOpPrecedence precedence = 0);
  // Parse an expected expression, reporting an error message if not found.
  Expression::Ptr matchExpression(std::string message);

private:
  Expression::Ptr
  buildBinaryOp(Token token, Expression::Ptr&& lhs, Expression::Ptr&& rhs, llvm::SMLoc location);
  void parseImport();
  Parameter::Vec parseOptionalTypeParameters();
  Parameter::Vec parseParameters();
  Parameter::Ptr parseParameter();

  Expression::Ptr parsePrimaryExpression();
  Literal::Ptr parseLiteral();
  Ident::Ptr parseIdentifier();
  Map::Ptr parseMap();
  Reduce::Ptr parseReduce();
  Switch::Ptr parseConditional();
  Expression::Ptr parseParenthesizedExpression();
  ArrayLiteral::Ptr parseArrayLiteral();
  Back::Ptr parseBack(Expression::Ptr&&);
  Lookup::Ptr parseLookup(Expression::Ptr&&);
  Subscript::Ptr parseSubscript(Expression::Ptr&&);
  Specialize::Ptr parseSpecialize(Expression::Ptr&&);
  Construct::Ptr parseConstruct(Expression::Ptr&&);
  Switch::Ptr parseSwitch(Expression::Ptr&&);
  Expression::Ptr parseBinaryOp(Expression::Ptr, BinaryOpPrecedence = 0);
  Expression::Vec parseExpressions();
  Expression::Ptr parseNegate();

  void error(std::string message) {
    auto diagnostic = sourceManager.GetMessage(
        lexer.getLastLocation(), llvm::SourceMgr::DiagKind::DK_Error, message);
    errors.push_back(diagnostic);
  }

  llvm::SourceMgr& sourceManager;
  std::vector<llvm::SMDiagnostic> errors;
  Lexer lexer;
  size_t testNum;
};

} // namespace dsl
} // namespace zirgen
