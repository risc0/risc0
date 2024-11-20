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

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/SMLoc.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/Support/raw_ostream.h"

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace zirgen {
namespace dsl {
namespace ast {

using llvm::SMLoc;
using llvm::StringRef;

// Base for all nodes, using curiously-recurring template pattern
template <class T> class Node {
  SMLoc location;

protected:
  Node(SMLoc loc) : location(std::move(loc)) {}

public:
  virtual ~Node() = default;
  const SMLoc& loc() { return location; }
  virtual void print(llvm::raw_ostream&) const = 0;
  void dump() const { print(llvm::errs()); }
  using Ptr = std::shared_ptr<T>;
  using Opt = std::optional<Ptr>;
  using Vec = std::vector<Ptr>;
  using ArrayRef = llvm::ArrayRef<Ptr>;

  // Allow gtest to print the AST tree upon match failures.
  friend void PrintTo(const T& node, std::ostream* os) {
    llvm::raw_os_ostream s{*os};
    node.print(s);
  }

  // Allow MLIR to print the AST tree
  friend llvm::raw_ostream& operator<<(llvm::raw_ostream& os, const Ptr& node) {
    node->print(os);
    return os;
  }
};

// Abstract base for expression nodes
class Expression : public Node<Expression> {
public:
  enum class Kind {
    Literal,
    StringLiteral,
    Ident,
    Lookup,
    Subscript,
    Specialize,
    Construct,
    Block,
    Map,
    Reduce,
    Switch,
    Range,
    Back,
    ArrayLiteral,
  };
  Kind getKind() const { return kind; }

protected:
  Expression(Kind kind, SMLoc loc);
  const Kind kind;
};

bool operator==(const Expression& left, const Expression& right);

// Abstract base for statement nodes
class Statement : public Node<Statement> {
public:
  enum class Kind {
    Definition,
    Declaration,
    Constraint,
    Void,
    Directive,
  };
  Kind getKind() const { return kind; }

protected:
  Statement(Kind kind, SMLoc loc);
  const Kind kind;
};

bool operator==(const Statement& left, const Statement& right);

class Parameter : public Node<Parameter> {
  std::string name;
  Expression::Ptr type;
  bool isVariadic;

public:
  Parameter(SMLoc loc, StringRef name, Expression::Ptr type, bool isVariadic);
  StringRef getName() const { return name; }
  Expression* getType() const { return type.get(); }
  bool getIsVariadic() const { return isVariadic; }
  void print(llvm::raw_ostream&) const override;
};

bool operator==(const Parameter& left, const Parameter& right);

class Component : public Node<Component> {
public:
  enum class Kind {
    Object,
    Function,
    Extern,
    Argument,
    Major,
  };

private:
  const Kind kind;
  std::string name;
  Parameter::Vec type_params;
  Parameter::Vec params;
  Expression::Ptr body;

public:
  Component(SMLoc loc,
            Kind kind,
            StringRef name,
            Parameter::Vec type_params,
            Parameter::Vec params,
            Expression::Ptr body);
  Kind getKind() const { return kind; }
  StringRef getName() const { return name; }
  Parameter::ArrayRef getTypeParams() const { return type_params; }
  Parameter::ArrayRef getParams() const { return params; }
  Expression* getBody() const { return body.get(); }
  void print(llvm::raw_ostream&) const override;
};

bool operator==(const Component& left, const Component& right);

class Module : public Node<Module> {
  Component::Vec body;

public:
  Module(SMLoc loc, Component::Vec body);
  Component::ArrayRef getBody() const { return body; }
  void print(llvm::raw_ostream&) const override;
};

bool operator==(const Module& left, const Module& right);

// Concrete expression nodes
class Literal : public Expression {
  const uint64_t value;

public:
  Literal(SMLoc loc, uint64_t value);
  uint64_t getValue() const { return value; }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Literal& left, const Literal& right);

class StringLiteral : public Expression {
  const std::string value;

public:
  StringLiteral(SMLoc loc, std::string value);
  StringRef getValue() const { return value; }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const StringLiteral& left, const StringLiteral& right);

class Ident : public Expression {
  const std::string name;

public:
  Ident(SMLoc loc, StringRef name);
  StringRef getName() const { return name; }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Ident& left, const Ident& right);

class Lookup : public Expression {
  Expression::Ptr component;
  std::string member;

public:
  Lookup(SMLoc loc, Expression::Ptr component, StringRef member);
  Expression* getComponent() const { return component.get(); }
  StringRef getMember() const { return member; }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Lookup& left, const Lookup& right);

class Subscript : public Expression {
  Expression::Ptr array;
  Expression::Ptr element;

public:
  Subscript(SMLoc loc, Expression::Ptr array, Expression::Ptr element);
  Expression* getArray() const { return array.get(); }
  Expression* getElement() const { return element.get(); }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Subscript& left, const Subscript& right);

class Specialize : public Expression {
  Expression::Ptr type;
  Expression::Vec args;

public:
  Specialize(SMLoc loc, Expression::Ptr type, Expression::Vec args);
  Expression* getType() const { return type.get(); }
  Expression::ArrayRef getArgs() const { return args; }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Specialize& left, const Specialize& right);

class Construct : public Expression {
  Expression::Ptr type;
  Expression::Vec args;

public:
  Construct(SMLoc loc, Expression::Ptr type, Expression::Vec args);
  Expression* getType() const { return type.get(); }
  Expression::ArrayRef getArgs() const { return args; }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Construct& left, const Construct& right);

class Block : public Expression {
  Statement::Vec body;
  Expression::Ptr value;

public:
  Block(SMLoc loc, Statement::Vec body, Expression::Ptr value);
  Statement::ArrayRef getBody() const { return body; }
  Expression* getValue() const { return value.get(); }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Block& left, const Block& right);

class Map : public Expression {
  Expression::Ptr array;
  std::string element;
  Expression::Ptr function;

public:
  Map(SMLoc loc, Expression::Ptr array, StringRef element, Expression::Ptr function);
  Expression* getArray() const { return array.get(); }
  StringRef getElement() const { return element; }
  Expression* getFunction() const { return function.get(); }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Map& left, const Map& right);

class Reduce : public Expression {
  Expression::Ptr array;
  Expression::Ptr init;
  Expression::Ptr type;

public:
  Reduce(SMLoc loc, Expression::Ptr array, Expression::Ptr init, Expression::Ptr type);
  Expression* getArray() const { return array.get(); }
  Expression* getInit() const { return init.get(); }
  Expression* getType() const { return type.get(); }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Reduce& left, const Reduce& right);

class Switch : public Expression {
  Expression::Ptr selector;
  Expression::Vec cases;
  bool isMajor;

public:
  Switch(SMLoc loc, Expression::Ptr selector, Expression::Vec cases, bool isMajor);
  Expression* getSelector() const { return selector.get(); }
  Expression::ArrayRef getCases() const { return cases; }
  bool getIsMajor() { return isMajor; }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Switch& left, const Switch& right);

class Range : public Expression {
  Expression::Ptr start;
  Expression::Ptr end;

public:
  Range(SMLoc loc, Expression::Ptr start, Expression::Ptr end);
  Expression* getStart() const { return start.get(); }
  Expression* getEnd() const { return end.get(); }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Range& left, const Range& right);

class Back : public Expression {
  Expression::Ptr expression;
  Expression::Ptr distance;

public:
  Back(SMLoc loc, Expression::Ptr expression, Expression::Ptr distance);
  Expression* getExpression() const { return expression.get(); }
  Expression* getDistance() const { return distance.get(); }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const Back& left, const Back& right);

class ArrayLiteral : public Expression {
  Expression::Vec elements;

public:
  ArrayLiteral(SMLoc loc, Expression::Vec elements);
  Expression::ArrayRef getElements() const { return elements; }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Expression* e);
};

bool operator==(const ArrayLiteral& left, const ArrayLiteral& right);

// Concrete statement nodes
class Definition : public Statement {
  std::string name;
  Expression::Ptr value;
  bool isGlobal;

public:
  Definition(SMLoc loc, StringRef name, Expression::Ptr value, bool isGlobal);
  StringRef getName() const { return name; }
  Expression* getValue() const { return value.get(); }
  bool getIsGlobal() const { return isGlobal; }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Statement* s);
};

bool operator==(const Definition& left, const Definition& right);

class Declaration : public Statement {
  std::string name;
  Expression::Ptr type;
  bool isGlobal;

public:
  Declaration(SMLoc loc, StringRef name, Expression::Ptr type, bool isGlobal);
  StringRef getName() const { return name; }
  Expression* getType() const { return type.get(); }
  bool getIsGlobal() const { return isGlobal; }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Statement* s);
};

bool operator==(const Declaration& left, const Declaration& right);

class Constraint : public Statement {
  Expression::Ptr left;
  Expression::Ptr right;

public:
  Constraint(SMLoc loc, Expression::Ptr left, Expression::Ptr right);
  Expression* getLeft() const { return left.get(); }
  Expression* getRight() const { return right.get(); }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Statement* s);
};

bool operator==(const Constraint& left, const Constraint& right);

class Void : public Statement {
  Expression::Ptr value;

public:
  Void(SMLoc loc, Expression::Ptr value);
  Expression* getValue() const { return value.get(); }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Statement* s);
};

bool operator==(const Void& left, const Void& right);

class Directive : public Statement {
public:
  Directive(SMLoc loc, std::string name, Expression::Vec params);
  std::string getName() const { return name; }
  Expression::ArrayRef getArgs() const { return args; }
  void print(llvm::raw_ostream&) const override;
  static bool classof(const Statement* s);

private:
  std::string name;
  Expression::Vec args;
};

bool operator==(const Directive& left, const Directive& right);

} // namespace ast
} // namespace dsl
} // namespace zirgen
