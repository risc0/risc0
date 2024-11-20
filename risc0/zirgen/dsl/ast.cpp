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

#include "ast.h"

namespace zirgen {
namespace dsl {
namespace ast {

using ostream = llvm::raw_ostream;

namespace JSON {
struct Printer {
  Printer(ostream& out) : out(out) {}
  void emit_string(StringRef s);
  void emit_uint(uint64_t n);
  void emit_bool(bool b);
  void join_comma();

protected:
  bool empty_list = true;
  ostream& out;
};
struct Array : Printer {
  Array(llvm::raw_ostream& out) : Printer(out) { out << "["; }
  ~Array() { out << "]"; }
  template <typename T> void emit_dict(T&& v);
};
struct Dict : Printer {
  Dict(llvm::raw_ostream& out) : Printer(out) { out << "{"; }
  ~Dict() { out << "}"; }
  void attr_string(StringRef k, StringRef v);
  void attr_uint(StringRef k, uint64_t v);
  void attr_bool(StringRef k, bool v);
  template <typename T> void attr_dict(StringRef k, T&& v);
  template <typename T> void attr_array(StringRef k, T& v);

private:
  void emit_key(StringRef k);
};

} // namespace JSON

template <typename T, typename U> static bool subtype_compare(const U& left, const U& right) {
  return *dynamic_cast<const T*>(&left) == *dynamic_cast<const T*>(&right);
}

template <typename T> static bool vec_compare(const T& left, const T& right) {
  if (left.size() != right.size())
    return false;

  for (size_t i = 0; i < left.size(); i++) {
    if (!(*left[i] == *right[i]))
      return false;
  }

  return true;
}

Expression::Expression(Kind kind, SMLoc loc) : Node(std::move(loc)), kind(kind) {}

bool operator==(const Expression& left, const Expression& right) {
  if (left.getKind() != right.getKind())
    return false;

  switch (left.getKind()) {
  case Expression::Kind::Literal:
    return subtype_compare<Literal>(left, right);
  case Expression::Kind::StringLiteral:
    return subtype_compare<StringLiteral>(left, right);
  case Expression::Kind::Ident:
    return subtype_compare<Ident>(left, right);
  case Expression::Kind::Lookup:
    return subtype_compare<Lookup>(left, right);
  case Expression::Kind::Subscript:
    return subtype_compare<Subscript>(left, right);
  case Expression::Kind::Specialize:
    return subtype_compare<Specialize>(left, right);
  case Expression::Kind::Construct:
    return subtype_compare<Construct>(left, right);
  case Expression::Kind::Block:
    return subtype_compare<Block>(left, right);
  case Expression::Kind::Map:
    return subtype_compare<Map>(left, right);
  case Expression::Kind::Reduce:
    return subtype_compare<Reduce>(left, right);
  case Expression::Kind::Switch:
    return subtype_compare<Switch>(left, right);
  case Expression::Kind::Range:
    return subtype_compare<Range>(left, right);
  case Expression::Kind::Back:
    return subtype_compare<Back>(left, right);
  case Expression::Kind::ArrayLiteral:
    return subtype_compare<ArrayLiteral>(left, right);
  }
  throw std::runtime_error("unreachable: missing case");
}

Statement::Statement(Kind kind, SMLoc loc) : Node(std::move(loc)), kind(kind) {}

bool operator==(const Statement& left, const Statement& right) {
  if (left.getKind() != right.getKind())
    return false;

  switch (left.getKind()) {
  case Statement::Kind::Definition:
    return subtype_compare<Definition>(left, right);
  case Statement::Kind::Declaration:
    return subtype_compare<Declaration>(left, right);
  case Statement::Kind::Constraint:
    return subtype_compare<Constraint>(left, right);
  case Statement::Kind::Void:
    return subtype_compare<Void>(left, right);
  case Statement::Kind::Directive:
    return subtype_compare<Directive>(left, right);
  }
  throw std::runtime_error("unreachable: missing case");
}

Parameter::Parameter(SMLoc loc, StringRef name, Expression::Ptr type, bool isVariadic)
    : Node(std::move(loc)), name(name), type(std::move(type)), isVariadic(isVariadic) {}

void Parameter::print(llvm::raw_ostream& out) const {
  JSON::Dict dict(out);
  dict.attr_string("name", name);
  dict.attr_dict("type", type);
  dict.attr_bool("isVariadic", isVariadic);
}

bool operator==(const Parameter& left, const Parameter& right) {
  return left.getName() == right.getName() && *left.getType() == *right.getType() &&
         left.getIsVariadic() == right.getIsVariadic();
}

Component::Component(SMLoc loc,
                     Kind kind,
                     StringRef name,
                     Parameter::Vec type_params,
                     Parameter::Vec params,
                     Expression::Ptr body)
    : Node(std::move(loc))
    , kind(kind)
    , name(name)
    , type_params(std::move(type_params))
    , params(std::move(params))
    , body(std::move(body)) {}

void Component::print(ostream& os) const {
  JSON::Dict dict(os);
  switch (kind) {
  case Kind::Object:
    dict.attr_string("kind", "object");
    break;
  case Kind::Function:
    dict.attr_string("kind", "function");
    break;
  case Kind::Extern:
    dict.attr_string("kind", "extern");
    break;
  case Kind::Argument:
    dict.attr_string("kind", "argument");
    break;
  case Kind::Major:
    dict.attr_string("kind", "major");
    break;
  }
  dict.attr_string("name", name);
  dict.attr_array("type_params", type_params);
  dict.attr_array("params", params);
  dict.attr_dict("body", body);
}

bool operator==(const Component& left, const Component& right) {
  return left.getKind() == right.getKind() && left.getName() == right.getName() &&
         vec_compare(left.getTypeParams(), right.getTypeParams()) &&
         vec_compare(left.getParams(), right.getParams()) && *left.getBody() == *right.getBody();
}

Module::Module(SMLoc loc, Component::Vec body) : Node(std::move(loc)), body(std::move(body)) {}

void Module::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_array("body", body);
}

bool operator==(const Module& left, const Module& right) {
  return vec_compare(left.getBody(), right.getBody());
}

Literal::Literal(SMLoc loc, uint64_t value)
    : Expression(Kind::Literal, std::move(loc)), value(value) {}

void Literal::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Literal");
  dict.attr_uint("value", value);
}

bool Literal::classof(const Expression* e) {
  return Kind::Literal == e->getKind();
}

bool operator==(const Literal& left, const Literal& right) {
  return left.getValue() == right.getValue();
}

StringLiteral::StringLiteral(SMLoc loc, std::string value)
    : Expression(Kind::StringLiteral, std::move(loc)), value(value) {}

void StringLiteral::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "StringLiteral");
  dict.attr_string("value", value);
}

bool StringLiteral::classof(const Expression* e) {
  return Kind::StringLiteral == e->getKind();
}

bool operator==(const StringLiteral& left, const StringLiteral& right) {
  return left.getValue() == right.getValue();
}

Ident::Ident(SMLoc loc, StringRef name) : Expression(Kind::Ident, std::move(loc)), name(name) {}

void Ident::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Ident");
  dict.attr_string("name", name);
}

bool Ident::classof(const Expression* e) {
  return Kind::Ident == e->getKind();
}

bool operator==(const Ident& left, const Ident& right) {
  return left.getName() == right.getName();
}

Lookup::Lookup(SMLoc loc, Expression::Ptr component, StringRef member)
    : Expression(Kind::Lookup, std::move(loc)), component(std::move(component)), member(member) {}

void Lookup::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Lookup");
  dict.attr_dict("component", component);
  dict.attr_string("member", member);
}

bool Lookup::classof(const Expression* e) {
  return Kind::Lookup == e->getKind();
}

bool operator==(const Lookup& left, const Lookup& right) {
  return *left.getComponent() == *right.getComponent() && left.getMember() == right.getMember();
}

Subscript::Subscript(SMLoc loc, Expression::Ptr array, Expression::Ptr element)
    : Expression(Kind::Subscript, std::move(loc))
    , array(std::move(array))
    , element(std::move(element)) {}

void Subscript::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Subscript");
  dict.attr_dict("array", array);
  dict.attr_dict("element", element);
}

bool Subscript::classof(const Expression* e) {
  return Kind::Subscript == e->getKind();
}

bool operator==(const Subscript& left, const Subscript& right) {
  return *left.getArray() == *right.getArray() && *left.getElement() == *right.getElement();
}

Specialize::Specialize(SMLoc loc, Expression::Ptr type, Expression::Vec args)
    : Expression(Kind::Specialize, std::move(loc)), type(std::move(type)), args(std::move(args)) {}

void Specialize::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Specialize");
  dict.attr_dict("type", type);
  dict.attr_array("args", args);
}

bool Specialize::classof(const Expression* e) {
  return Kind::Specialize == e->getKind();
}

bool operator==(const Specialize& left, const Specialize& right) {
  return *left.getType() == *right.getType() && vec_compare(left.getArgs(), right.getArgs());
}

Construct::Construct(SMLoc loc, Expression::Ptr type, Expression::Vec args)
    : Expression(Kind::Construct, std::move(loc)), type(std::move(type)), args(std::move(args)) {}

void Construct::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Construct");
  dict.attr_dict("type", type);
  dict.attr_array("args", args);
}

bool Construct::classof(const Expression* e) {
  return Kind::Construct == e->getKind();
}

bool operator==(const Construct& left, const Construct& right) {
  assert(*left.getType() == *right.getType());
  assert(vec_compare(left.getArgs(), right.getArgs()));
  return *left.getType() == *right.getType() && vec_compare(left.getArgs(), right.getArgs());
}

Block::Block(SMLoc loc, Statement::Vec body, Expression::Ptr value)
    : Expression(Kind::Block, std::move(loc)), body(std::move(body)), value(std::move(value)) {}

void Block::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Block");
  dict.attr_array("body", body);
  if (value) {
    dict.attr_dict("value", value);
  }
}

bool Block::classof(const Expression* e) {
  return Kind::Block == e->getKind();
}

bool operator==(const Block& left, const Block& right) {
  return vec_compare(left.getBody(), right.getBody()) && *left.getValue() == *right.getValue();
}

Map::Map(SMLoc loc, Expression::Ptr array, StringRef element, Expression::Ptr function)
    : Expression(Kind::Map, std::move(loc))
    , array(std::move(array))
    , element(std::move(element))
    , function(std::move(function)) {}

void Map::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Map");
  dict.attr_dict("array", array);
  dict.attr_string("element", element);
  dict.attr_dict("function", function);
}

bool Map::classof(const Expression* e) {
  return Kind::Map == e->getKind();
}

bool operator==(const Map& left, const Map& right) {
  assert(*left.getArray() == *right.getArray());
  assert(left.getElement() == right.getElement());
  assert(*left.getFunction() == *right.getFunction());
  return *left.getArray() == *right.getArray() && left.getElement() == right.getElement() &&
         *left.getFunction() == *right.getFunction();
}

Reduce::Reduce(SMLoc loc, Expression::Ptr array, Expression::Ptr init, Expression::Ptr type)
    : Expression(Kind::Reduce, std::move(loc))
    , array(std::move(array))
    , init(std::move(init))
    , type(std::move(type)) {}

void Reduce::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Reduce");
  dict.attr_dict("array", array);
  dict.attr_dict("init", init);
  dict.attr_dict("type", type);
}

bool Reduce::classof(const Expression* e) {
  return Kind::Reduce == e->getKind();
}

bool operator==(const Reduce& left, const Reduce& right) {
  return *left.getArray() == *right.getArray() && *left.getInit() == *right.getInit() &&
         *left.getType() == *right.getType();
}

Switch::Switch(SMLoc loc, Expression::Ptr selector, Expression::Vec cases, bool isMajor)
    : Expression(Kind::Switch, std::move(loc))
    , selector(std::move(selector))
    , cases(std::move(cases))
    , isMajor(isMajor) {}

void Switch::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Switch");
  dict.attr_dict("selector", selector);
  dict.attr_array("cases", cases);
  dict.attr_bool("isMajor", isMajor);
}

bool Switch::classof(const Expression* e) {
  return Kind::Switch == e->getKind();
}

bool operator==(const Switch& left, const Switch& right) {
  return *left.getSelector() == *right.getSelector() &&
         vec_compare(left.getCases(), right.getCases());
}

Range::Range(SMLoc loc, Expression::Ptr start, Expression::Ptr end)
    : Expression(Kind::Range, std::move(loc)), start(std::move(start)), end(std::move(end)) {}

void Range::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Range");
  dict.attr_dict("start", start);
  dict.attr_dict("end", end);
}

bool Range::classof(const Expression* e) {
  return Kind::Range == e->getKind();
}

bool operator==(const Range& left, const Range& right) {
  return *left.getStart() == *right.getStart() && *left.getEnd() == *right.getEnd();
}

Back::Back(SMLoc loc, Expression::Ptr expression, Expression::Ptr distance)
    : Expression(Kind::Back, std::move(loc))
    , expression(std::move(expression))
    , distance(std::move(distance)) {}

void Back::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Back");
  dict.attr_dict("expression", expression);
  dict.attr_dict("distance", distance);
}

bool Back::classof(const Expression* e) {
  return Kind::Back == e->getKind();
}

bool operator==(const Back& left, const Back& right) {
  return *left.getExpression() == *right.getExpression() &&
         *left.getDistance() == *right.getDistance();
}

ArrayLiteral::ArrayLiteral(SMLoc loc, Expression::Vec elements)
    : Expression(Kind::ArrayLiteral, std::move(loc)), elements(std::move(elements)) {}

void ArrayLiteral::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "ArrayLiteral");
  dict.attr_array("elements", elements);
}

bool ArrayLiteral::classof(const Expression* e) {
  return Kind::ArrayLiteral == e->getKind();
}

bool operator==(const ArrayLiteral& left, const ArrayLiteral& right) {
  return vec_compare(left.getElements(), right.getElements());
}

Definition::Definition(SMLoc loc, StringRef name, Expression::Ptr value, bool isGlobal)
    : Statement(Kind::Definition, std::move(loc))
    , name(std::move(name))
    , value(std::move(value))
    , isGlobal(isGlobal) {}

void Definition::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Definition");
  dict.attr_string("name", name);
  dict.attr_dict("value", value);
  dict.attr_bool("isGlobal", isGlobal);
}

bool Definition::classof(const Statement* s) {
  return Kind::Definition == s->getKind();
}

bool operator==(const Definition& left, const Definition& right) {
  return left.getName() == right.getName() && *left.getValue() == *right.getValue() &&
         left.getIsGlobal() == right.getIsGlobal();
}

Declaration::Declaration(SMLoc loc, StringRef name, Expression::Ptr type, bool isGlobal)
    : Statement(Kind::Declaration, std::move(loc))
    , name(std::move(name))
    , type(std::move(type))
    , isGlobal(isGlobal) {}

void Declaration::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Declaration");
  dict.attr_string("name", name);
  dict.attr_dict("type", type);
  dict.attr_bool("isGlobal", isGlobal);
}

bool Declaration::classof(const Statement* s) {
  return Kind::Declaration == s->getKind();
}

bool operator==(const Declaration& left, const Declaration& right) {
  return left.getName() == right.getName() && *left.getType() == *right.getType() &&
         left.getIsGlobal() == right.getIsGlobal();
}

Constraint::Constraint(SMLoc loc, Expression::Ptr left, Expression::Ptr right)
    : Statement(Kind::Constraint, std::move(loc)), left(std::move(left)), right(std::move(right)) {}

void Constraint::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Constraint");
  dict.attr_dict("left", left);
  dict.attr_dict("right", right);
}

bool Constraint::classof(const Statement* s) {
  return Kind::Constraint == s->getKind();
}

bool operator==(const Constraint& left, const Constraint& right) {
  return *left.getLeft() == *right.getLeft() && *left.getRight() == *right.getRight();
}

Void::Void(SMLoc loc, Expression::Ptr value)
    : Statement(Kind::Void, std::move(loc)), value(std::move(value)) {}

void Void::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Void");
  dict.attr_dict("value", value);
}

bool Void::classof(const Statement* s) {
  return Kind::Void == s->getKind();
}

bool operator==(const Void& left, const Void& right) {
  return *left.getValue() == *right.getValue();
}

Directive::Directive(SMLoc loc, std::string name, Expression::Vec args)
    : Statement(Kind::Directive, std::move(loc)), name(std::move(name)), args(std::move(args)) {}

void Directive::print(ostream& os) const {
  JSON::Dict dict(os);
  dict.attr_string("class", "Directive");
  dict.attr_string("name", name);
  dict.attr_array("args", args);
}

bool Directive::classof(const Statement* s) {
  return Kind::Directive == s->getKind();
}

bool operator==(const Directive& left, const Directive& right) {
  return left.getName() == right.getName() && vec_compare(left.getArgs(), right.getArgs());
}

namespace JSON {

void Printer::emit_string(StringRef s) {
  out << '\"';
  for (char c : s) {
    switch (c) {
    case '\\':
    case '\"':
      out << '\\';
    default:
      out << c;
    }
  }
  out << '\"';
}

void Printer::emit_uint(uint64_t n) {
  out << n;
}

void Printer::emit_bool(bool b) {
  if (b) {
    out << "true";
  } else {
    out << "false";
  }
}

void Printer::join_comma() {
  if (empty_list) {
    empty_list = false;
  } else {
    out << ",";
  }
}

template <typename T> void Array::emit_dict(T&& v) {
  join_comma();
  if (v) {
    v->print(out);
  } else {
    out << "null";
  }
}

void Dict::attr_string(StringRef k, StringRef v) {
  emit_key(k);
  emit_string(v);
}

void Dict::attr_uint(StringRef k, uint64_t v) {
  emit_key(k);
  emit_uint(v);
}

void Dict::attr_bool(StringRef k, bool v) {
  emit_key(k);
  emit_bool(v);
}

template <typename T> void Dict::attr_dict(StringRef k, T&& v) {
  emit_key(k);
  if (v) {
    v->print(out);
  } else {
    out << "null";
  }
}

template <typename T> void Dict::attr_array(StringRef k, T& v) {
  emit_key(k);
  Array a(out);
  for (auto& e : v) {
    a.emit_dict(e);
  }
}

void Dict::emit_key(StringRef k) {
  join_comma();
  emit_string(k);
  out << ':';
}

} // namespace JSON

} // namespace ast
} // namespace dsl
} // namespace zirgen
