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

namespace zirgen {
namespace dsl {

using namespace ast;
using std::make_shared;

BinaryOpPrecedence getPrecedence(Token token) {
  switch (token) {
  case tok_range:
    return 1;
  case tok_bit_and:
    return 2;
  case tok_plus:
    return 3;
  case tok_minus:
    return 3;
  case tok_times:
    return 4;
  case tok_div:
    return 4;
  case tok_dot:
    return 5;
  default:
    // If we see something that isn't a binary operation, we've reached the end
    // of the expression and should stop parsing. Assigning this a precedence
    // below all other binary operations means nothing to the left of the
    // current position has an operand to the right of the current position,
    // and assigning it below 0 finishes the parse once this is done.
    return -1;
  }
}

Expression::Ptr
Parser::buildBinaryOp(Token token, Expression::Ptr&& lhs, Expression::Ptr&& rhs, SMLoc location) {
  std::string desugaredName;
  switch (token) {
  case tok_range:
    return make_shared<Range>(location, std::move(lhs), std::move(rhs));
  case tok_bit_and:
    desugaredName = "BitAnd";
    break;
  case tok_plus:
    desugaredName = "Add";
    break;
  case tok_minus:
    desugaredName = "Sub";
    break;
  case tok_times:
    desugaredName = "Mul";
    break;
  case tok_div:
    desugaredName = "Div";
    break;
  default:
    error("Undefined binary operator");
    desugaredName = "Undefined";
    break;
  }

  Ident::Ptr component = make_shared<Ident>(location, desugaredName);
  Expression::Vec args;
  args.push_back(std::move(lhs));
  args.push_back(std::move(rhs));
  return make_shared<Construct>(location, std::move(component), std::move(args));
}

Module::Ptr Parser::parseModule() {
  Component::Vec components;

  for (bool done = false; !done;) {
    switch (lexer.peekToken()) {
    case tok_argument:
    case tok_component:
    case tok_function:
    case tok_extern:
      components.push_back(parseComponent());
      break;
    case tok_import:
      parseImport();
      break;
    case tok_test:
    case tok_test_fails: {
      Component::Ptr testMain = parseTest();
      if (lexer.inMain()) {
        components.push_back(testMain);
      }
    } break;
    default:
      done = true;
      break;
    }
  }

  Token lastToken = lexer.takeToken();
  if (lastToken != tok_eof) {
    error("unexpected input at end of file");
  }

  if (errors.empty()) {
    return make_shared<Module>(lexer.getLastLocation(), std::move(components));
  } else {
    return nullptr;
  }
}

Component::Ptr Parser::parseComponent() {
  ast::Component::Kind kind;
  switch (lexer.takeToken()) {
  case tok_argument:
    kind = ast::Component::Kind::Argument;
    break;
  case tok_component:
    kind = ast::Component::Kind::Object;
    break;
  case tok_function:
    kind = ast::Component::Kind::Function;
    break;
  case tok_extern:
    return parseExtern();
  default:
    error("A component declaration must start with the `component` keyword");
    return nullptr;
  }
  SMLoc location = lexer.getLastLocation();

  if (lexer.takeToken() != tok_ident) {
    error("Expected an identifier name, got \"" + lexer.getIdentifier() + "\" instead");
    return nullptr;
  }
  std::string name = lexer.getIdentifier();

  Parameter::Vec typeParams = parseOptionalTypeParameters();
  Parameter::Vec params = parseParameters();
  Expression::Ptr body = parseBlock();

  return make_shared<Component>(
      location, kind, name, std::move(typeParams), std::move(params), std::move(body));
}

Component::Ptr Parser::parseExtern() {
  SMLoc location = lexer.getLastLocation();

  if (!lexer.takeTokenIf(tok_ident)) {
    error("Expected an identifier name, got \"" + lexer.getIdentifier() + "\" instead");
    return nullptr;
  }
  std::string name = lexer.getIdentifier();

  Parameter::Vec typeParams;
  Parameter::Vec params = parseParameters();

  Expression::Ptr returnType;
  switch (lexer.takeToken()) {
  case tok_semicolon: {
    // Default blank type Component()
    returnType = make_shared<Ident>(location, "Component");
    break;
  }
  case tok_colon:
    returnType = matchExpression("Expecting return type");
    if (!lexer.takeTokenIf(tok_semicolon)) {
      error("Expecting extern definition to be followed by a semicolon");
      return nullptr;
    }
    break;
  default:
    error("Expecting extern definition to end with either ';' or ': type;'");
    return nullptr;
  }

  return make_shared<Component>(location,
                                Component::Kind::Extern,
                                name,
                                std::move(typeParams),
                                std::move(params),
                                std::move(returnType));
}

Component::Ptr Parser::parseTest() {
  SMLoc location = lexer.getLastLocation();
  bool isFail = (lexer.takeToken() == tok_test_fails);

  std::string name;
  if (lexer.takeTokenIf(tok_ident)) {
    name = lexer.getIdentifier();
  } else {
    name = std::to_string(testNum++);
  }

  Expression::Ptr body = parseBlock();
  name = std::string(isFail ? "test$fail$" : "test$succ$") + name;

  return make_shared<Component>(
      location, ast::Component::Kind::Object, name, Parameter::Vec(), Parameter::Vec(), body);
}

Block::Ptr Parser::parseBlock() {
  if (lexer.takeToken() != tok_curly_l) {
    error("A block must start with '{'");
    return nullptr;
  }
  Statement::Vec body;
  Expression::Ptr lastExpression;
  SMLoc blockLoc = lexer.getLastLocation();

  bool done = false;
  while (!done) {
    Token token = lexer.peekToken();
    SMLoc location = lexer.getLastLocation();
    bool globalTokenPending = false;
    switch (token) {
    case tok_curly_r:
      done = true;
      break;
    case tok_global:
      lexer.takeToken();
      globalTokenPending = true;
      // Fallthrough
    default:
      // definition, declaration, constraint, void, or value
      lastExpression = matchExpression("expected expression at beginning of statement");

      if (lexer.peekToken() == tok_semicolon) {
        // void
        lexer.takeToken();
        body.push_back(make_shared<Void>(location, std::move(lastExpression)));
        lastExpression = nullptr;
      } else if (lexer.peekToken() == tok_bang) {
        // directive
        location = lexer.getLastLocation();
        std::string name = lexer.getIdentifier();
        lexer.takeToken();
        if (!lexer.takeTokenIf(tok_paren_l)) {
          error("expected '(' after '!' in compiler directive");
        }
        Expression::Vec arguments;
        if (lexer.peekToken() != tok_paren_r) {
          arguments = parseExpressions();
        }
        lexer.takeToken();
        if (lexer.takeToken() != tok_semicolon) {
          error("expected semicolon after compiler directive");
          return nullptr;
        }

        body.push_back(make_shared<Directive>(location, name, std::move(arguments)));
        lastExpression = nullptr;
      } else if (lexer.peekToken() == tok_define) {
        // definition
        if (!lastExpression || !Ident::classof(lastExpression.get())) {
          error("expected an identifier on left side of member definition");
          return nullptr;
        }
        auto identifier = dynamic_cast<Ident*>(lastExpression.get())->getName();

        lexer.takeToken();
        location = lexer.getLastLocation();
        Expression::Ptr defBody =
            matchExpression("expected an expression on right side of member definition");
        if (lexer.takeToken() != tok_semicolon) {
          error("expected semicolon after member definition");
          return nullptr;
        }
        body.push_back(
            make_shared<Definition>(location, identifier, std::move(defBody), globalTokenPending));
        globalTokenPending = false;
        lastExpression = nullptr;
      } else if (lexer.peekToken() == tok_eq) {
        // constraint
        lexer.takeToken();
        location = lexer.getLastLocation();
        Expression::Ptr rhs = matchExpression("expected an expression on right side of constraint");
        if (lexer.takeToken() != tok_semicolon) {
          error("expected semicolon after constraint statement");
          return nullptr;
        }
        body.push_back(
            make_shared<Constraint>(location, std::move(lastExpression), std::move(rhs)));
        lastExpression = nullptr;
      } else if (lexer.peekToken() == tok_colon) {
        // declaration
        if (!lastExpression || !Ident::classof(lastExpression.get())) {
          error("expected an identifier on left side of member declaration");
          return nullptr;
        }
        auto identifier = dynamic_cast<Ident*>(lastExpression.get())->getName();

        lexer.takeToken();
        location = lexer.getLastLocation();
        Expression::Ptr declType = matchExpression("expected type expression");
        if (lexer.takeToken() != tok_semicolon) {
          error("expected semicolon after member declaration");
          return nullptr;
        }
        body.push_back(make_shared<Declaration>(
            location, identifier, std::move(declType), globalTokenPending));
        globalTokenPending = false;
        lastExpression = nullptr;
      } else if (lexer.peekToken() != tok_curly_r) {
        error("invalid statement");
        return nullptr;
      }
      if (globalTokenPending) {
        error("Expected declaration or definition after `global'");
        return nullptr;
      }
      break;
    }
  }

  if (lexer.takeToken() != tok_curly_r) {
    error("A block must end with '}'");
    return nullptr;
  }

  if (!lastExpression) {
    Ident::Ptr component = make_shared<Ident>(blockLoc, "Component");
    Expression::Vec args;
    lastExpression = make_shared<Construct>(blockLoc, std::move(component), std::move(args));
  }

  if (errors.empty()) {
    return make_shared<Block>(blockLoc, std::move(body), std::move(lastExpression));
  } else {
    return nullptr;
  }
}

void Parser::parseImport() {
  // Imports must be of the form 'import <ident>;'
  lexer.takeToken(); // Consume 'import'
  if (!lexer.takeTokenIf(tok_ident)) {
    error("Expected identifier in import statement");
    return;
  }
  std::string name = lexer.getIdentifier();
  if (!lexer.takeTokenIf(tok_semicolon)) {
    error("Expected semicolon after import statement");
    return;
  }
  lexer.doImport(name);
}

Parameter::Vec Parser::parseOptionalTypeParameters() {
  if (!lexer.takeTokenIf(tok_angle_l)) {
    // There are no type parameters, which is not an error
    return {};
  }

  Parameter::Vec typeParams;
  Token token;
  do {
    Parameter::Ptr param = parseParameter();
    token = lexer.takeToken();
    if (param) {
      typeParams.push_back(std::move(param));
    } else {
      break;
    }
  } while (token == tok_comma && errors.empty());

  if (token != tok_angle_r) {
    error("Missing final '>' at the end of a type parameter list");
    return {};
  }

  return typeParams;
}

Parameter::Vec Parser::parseParameters() {
  if (!lexer.takeTokenIf(tok_paren_l)) {
    error("Expected '(' at the beginning of a parameter list");
    return {};
  }

  // Handle the case where there are no parameters
  if (lexer.takeTokenIf(tok_paren_r)) {
    return {};
  }

  Parameter::Vec params;
  Token token;
  do {
    Parameter::Ptr param = parseParameter();
    token = lexer.takeToken();
    if (param) {
      params.push_back(std::move(param));
    } else {
      break;
    }
  } while (token == tok_comma && errors.empty());

  if (token != tok_paren_r) {
    error("Expected ')' at the end of a parameter list");
    return {};
  }

  return params;
}

Parameter::Ptr Parser::parseParameter() {
  Token token = lexer.takeToken();
  if (token != tok_ident) {
    error("A parameter must start with its name");
    return nullptr;
  }
  std::string name = lexer.getIdentifier();
  SMLoc location = lexer.getLastLocation();
  if (lexer.takeToken() != tok_colon) {
    error("Expected type annotation ': type' after parameter name");
    return nullptr;
  }
  Expression::Ptr type =
      matchExpression("Expected type annotation expression after parameter name");
  if (!type) {
    return nullptr;
  }
  token = lexer.peekToken();
  bool isVariadic = (token == tok_variadic);
  if (isVariadic) {
    lexer.takeToken();
  }

  return make_shared<Parameter>(location, name, std::move(type), isVariadic);
}

Expression::Ptr Parser::parseExpression(BinaryOpPrecedence precedence) {
  // The expression grammar is left recursive, so we use bottom up parsing for
  // the expression subgrammar. At any point in time, leftExpr holds the
  // "largest" leftmost subexpression that has been constructed yet.
  Expression::Ptr leftExpr;

  bool done = false;
  while (!done) {
    Token token = lexer.peekToken();
    switch (token) {
    case tok_curly_l:
      // A '{' denotes the start of a block; a block is a kind of expression,
      // but it can also follow another expression that it is not part of, for
      // example after the array subexpression of a map. This guard prevents
      // parsing the block as "part of" the array subexpression.
      if (leftExpr) {
        done = true;
        break;
      }
      [[fallthrough]];
    case tok_literal:
    case tok_string_literal:
    case tok_ident:
    case tok_for:
    case tok_reduce:
    case tok_if:
    case tok_square_l:
    case tok_angle_l:
    case tok_paren_l:
    case tok_mux:
    case tok_dot:
    case tok_back:
      if (leftExpr) {
        error("unexpected expression");
      }
      leftExpr = parsePrimaryExpression();
      break;

    // infix operators
    case tok_range:
    case tok_bit_and:
    case tok_plus:
    case tok_times:
    case tok_div:
      if (!leftExpr) {
        error("missing left operand for binary operator");
      }
      leftExpr = parseBinaryOp(std::move(leftExpr), precedence);
      break;

    // either prefix or infix
    case tok_minus:
      if (leftExpr) {
        leftExpr = parseBinaryOp(leftExpr, precedence);
      } else {
        leftExpr = parseNegate();
      }
      break;

    default:
      // Reached something that isn't part of the expression, so we're done
      done = true;
    };
  }

  return leftExpr;
}

Expression::Ptr Parser::matchExpression(std::string message) {
  auto expr = parseExpression();
  if (!expr)
    error(message);
  return expr;
}

Expression::Ptr Parser::parsePrimaryExpression() {
  // Parse expressions which do not directly contain infix operators.
  // This subgrammar is left recursive, so we use bottom up parsing. At any
  // point in time, leftExpr holds the "largest" leftmost subexpression that
  // has been constructed yet.
  Expression::Ptr leftExpr;

  bool done = false;
  while (!done) {
    switch (lexer.peekToken()) {
    // non-left-recursive expressions
    case tok_literal:
    case tok_string_literal:
      if (!leftExpr) {
        leftExpr = parseLiteral();
      } else {
        done = true;
      }
      break;
    case tok_ident:
      if (!leftExpr) {
        leftExpr = parseIdentifier();
      } else {
        done = true;
      }
      break;
    case tok_for:
      if (!leftExpr) {
        leftExpr = parseMap();
      } else {
        done = true;
      }
      break;
    case tok_reduce:
      if (!leftExpr) {
        leftExpr = parseReduce();
      } else {
        done = true;
      }
      break;
    case tok_if:
      if (!leftExpr) {
        leftExpr = parseConditional();
      } else {
        done = true;
      }
      break;
    case tok_curly_l:
      // Sometimes a block may directly follow another primary expression that
      // it is not part of, for example in a map:
      //   for i : arr { ... }
      if (!leftExpr) {
        leftExpr = parseBlock();
      }
      done = true;
      break;
    case tok_minus:
      if (leftExpr) {
        done = true;
      } else {
        leftExpr = parseNegate();
      }
      break;

    // left-recursive expressions
    case tok_square_l:
      if (leftExpr) {
        leftExpr = parseSubscript(std::move(leftExpr));
      } else {
        leftExpr = parseArrayLiteral();
      }
      break;
    case tok_angle_l:
      if (!leftExpr) {
        error("missing base expression for specialization");
      }
      leftExpr = parseSpecialize(std::move(leftExpr));
      break;
    case tok_paren_l:
      if (leftExpr) {
        leftExpr = parseConstruct(std::move(leftExpr));
      } else {
        leftExpr = parseParenthesizedExpression();
      }
      break;
    case tok_mux:
      if (!leftExpr) {
        error("missing base expression for switch operation");
      }
      leftExpr = parseSwitch(std::move(leftExpr));
      break;
    case tok_dot:
      if (!leftExpr) {
        error("missing base expression for member lookup");
      }
      leftExpr = parseLookup(std::move(leftExpr));
      break;
    case tok_back:
      if (!leftExpr) {
        error("missing base expression for back operation");
      }
      leftExpr = parseBack(std::move(leftExpr));
      break;
    default:
      // Reached something that isn't part of the expression, so we're done
      done = true;
      if (!leftExpr) {
        error("expected a primary expression here");
      }
    }
  }

  return leftExpr;
}

Literal::Ptr Parser::parseLiteral() {
  Token token = lexer.takeToken();
  if (token == tok_literal) {
    return make_shared<Literal>(lexer.getLastLocation(), lexer.getLiteral());
  } else if (token == tok_string_literal) {
    return make_shared<StringLiteral>(lexer.getLastLocation(), lexer.getIdentifier());
  } else {
    return nullptr;
  }
}

Ident::Ptr Parser::parseIdentifier() {
  if (lexer.takeToken() == tok_ident) {
    return make_shared<Ident>(lexer.getLastLocation(), lexer.getIdentifier());
  } else {
    error("An identifier must start with a letter");
    return nullptr;
  }
}

Map::Ptr Parser::parseMap() {
  if (lexer.takeToken() != tok_for) {
    error("A map construct must start with the keyword 'for'");
    return nullptr;
  }
  SMLoc location = lexer.getLastLocation();

  if (lexer.takeToken() != tok_ident) {
    error("Expected an identifier after 'for'");
    return nullptr;
  }
  std::string inductionVar = lexer.getIdentifier();

  if (lexer.takeToken() != tok_colon) {
    error("Expected ':' after induction variable in map construct");
    return nullptr;
  }

  Expression::Ptr array = matchExpression("Expected array expression");
  Expression::Ptr function = parseBlock();

  return make_shared<Map>(location, std::move(array), inductionVar, std::move(function));
}

Reduce::Ptr Parser::parseReduce() {
  if (lexer.takeToken() != tok_reduce) {
    error("A reduce construct must start with the keyword 'reduce'");
    return nullptr;
  }
  SMLoc location = lexer.getLastLocation();

  Expression::Ptr array = matchExpression("Expected array expression");

  if (lexer.takeToken() != tok_init) {
    error("Expected initial value in reduce construct");
    return nullptr;
  }

  Expression::Ptr init = matchExpression("Expected init expression");

  if (lexer.takeToken() != tok_with) {
    error("Expected a reducer component in reduce construct");
    return nullptr;
  }

  Expression::Ptr reducer = matchExpression("Expected reducer expression");

  return make_shared<Reduce>(location, std::move(array), std::move(init), std::move(reducer));
}

Switch::Ptr Parser::parseConditional() {
  if (!lexer.takeTokenIf(tok_if)) {
    error("A conditional expression must start with the 'if' keyword");
    return nullptr;
  }
  SMLoc location = lexer.getLastLocation();

  if (!lexer.takeTokenIf(tok_paren_l)) {
    error("Expected parentheses around condition, missing '('");
    return nullptr;
  }

  Expression::Ptr condition = matchExpression("Expected a condition expression");

  if (!lexer.takeTokenIf(tok_paren_r)) {
    error("Missing ')' after condition");
    return nullptr;
  }

  Expression::Vec cases;
  Expression::Vec selectors;

  cases.push_back(parseBlock());
  selectors.push_back(condition);
  if (lexer.takeTokenIf(tok_else)) {
    cases.push_back(parseBlock());
    Expression::Vec subArgs;
    subArgs.push_back(make_shared<Literal>(location, 1));
    subArgs.push_back(condition);
    selectors.push_back(
        make_shared<Construct>(location, make_shared<Ident>(location, "Sub"), subArgs));
  }
  Expression::Ptr selector = make_shared<ArrayLiteral>(location, std::move(selectors));
  return make_shared<Switch>(location, std::move(selector), std::move(cases), false);
}

Expression::Ptr Parser::parseParenthesizedExpression() {
  if (!lexer.takeTokenIf(tok_paren_l)) {
    error("Expected a '(' at the start of a parenthesized expression");
    return nullptr;
  }

  Expression::Ptr expression = parseExpression();

  if (!lexer.takeTokenIf(tok_paren_r)) {
    error("Expected a ')' at the end of a parenthesized expression");
    return nullptr;
  }

  return expression;
}

ArrayLiteral::Ptr Parser::parseArrayLiteral() {
  if (!lexer.takeTokenIf(tok_square_l)) {
    error("Expected a '[' at the start of an array literal");
    return nullptr;
  }
  SMLoc location = lexer.getLastLocation();

  Expression::Vec elements;
  if (lexer.peekToken() != tok_square_r) {
    elements = parseExpressions();
  }

  if (!lexer.takeTokenIf(tok_square_r)) {
    error("Expected a ']' at the end of an array literal");
    return nullptr;
  }

  return make_shared<ArrayLiteral>(location, std::move(elements));
}

Back::Ptr Parser::parseBack(Expression::Ptr&& baseExpr) {
  if (lexer.takeToken() != tok_back) {
    error("Expected a '@' after base component in back expression");
    return nullptr;
  }
  SMLoc location = lexer.getLastLocation();
  Expression::Ptr rhs;

  switch (lexer.peekToken()) {
  case tok_paren_l:
    rhs = parseParenthesizedExpression();
    break;
  case tok_literal:
    rhs = parseLiteral();
    break;
  case tok_ident:
    rhs = parseIdentifier();
    break;
  default:
    rhs = nullptr;
    break;
  }

  if (!rhs) {
    error("Unable to parse back distance");
    return nullptr;
  }
  return make_shared<Back>(location, std::move(baseExpr), std::move(rhs));
}

Lookup::Ptr Parser::parseLookup(Expression::Ptr&& baseExpr) {
  if (lexer.takeToken() != tok_dot) {
    error("Expected a '.' after base component in member lookup expression");
    return nullptr;
  }
  SMLoc location = lexer.getLastLocation();

  if (lexer.takeToken() != tok_ident) {
    error("Expected an identifier");
    return nullptr;
  }
  std::string member = lexer.getIdentifier();

  return make_shared<Lookup>(location, std::move(baseExpr), member);
}

Subscript::Ptr Parser::parseSubscript(Expression::Ptr&& primaryExpr) {
  if (!lexer.takeTokenIf(tok_square_l)) {
    error("Expected a '[' after array component in subscript expression");
    return nullptr;
  }
  SMLoc location = lexer.getLastLocation();

  Expression::Ptr element = matchExpression("Expected index expression");

  if (!lexer.takeTokenIf(tok_square_r)) {
    error("Expected a ']' after element of subscript expression");
    return nullptr;
  }

  return make_shared<Subscript>(location, std::move(primaryExpr), std::move(element));
}

Specialize::Ptr Parser::parseSpecialize(Expression::Ptr&& generic) {
  if (!lexer.takeTokenIf(tok_angle_l)) {
    error("Expected a '<' after the type in a \"specialize\" expression");
    return nullptr;
  }
  SMLoc location = lexer.getLastLocation();

  Expression::Vec typeArguments = parseExpressions();

  if (!lexer.takeTokenIf(tok_angle_r)) {
    error("Expected a '>' after type arguments in a \"specialize\" expression");
    return nullptr;
  }

  return make_shared<Specialize>(location, std::move(generic), std::move(typeArguments));
}

Construct::Ptr Parser::parseConstruct(Expression::Ptr&& component) {
  if (!lexer.takeTokenIf(tok_paren_l)) {
    error("Expected a '(' after component type in constructor expression");
    return nullptr;
  }
  SMLoc location = lexer.getLastLocation();

  Expression::Vec arguments;
  if (lexer.peekToken() != tok_paren_r) {
    arguments = parseExpressions();
  }

  if (!lexer.takeTokenIf(tok_paren_r)) {
    error("Expected a ')' after arguments in constructor expression");
    return nullptr;
  }

  return make_shared<Construct>(location, std::move(component), std::move(arguments));
}

Switch::Ptr Parser::parseSwitch(Expression::Ptr&& selector) {
  // The selector has already been parsed
  if (!lexer.takeTokenIf(tok_mux)) {
    error("Expected '->' after selector in mux");
    return nullptr;
  }
  SMLoc location = lexer.getLastLocation();

  // If there is a bang, it's the major mux
  bool isMajor = lexer.takeTokenIf(tok_bang);

  if (!lexer.takeTokenIf(tok_paren_l)) {
    error("A mux's arms should be enclosed in parentheses, missing '('");
    return nullptr;
  }

  if (lexer.peekToken() == tok_paren_r) {
    error("A mux must have at least one arm");
    return nullptr;
  }

  Expression::Vec cases = parseExpressions();

  if (!lexer.takeTokenIf(tok_paren_r)) {
    error("Expected ')' after all of the mux's arms");
    return nullptr;
  }

  return make_shared<Switch>(location, std::move(selector), std::move(cases), isMajor);
}

Expression::Ptr Parser::parseBinaryOp(Expression::Ptr lhs, BinaryOpPrecedence precedence) {
  while (true) {
    Token opToken = lexer.peekToken();
    SMLoc location = lexer.getLastLocation();
    BinaryOpPrecedence opPrecedence = getPrecedence(opToken);

    if (opPrecedence < precedence) {
      // The next operation binds less tightly than the "unresolved" one, so
      // now we can resolve it. For example, if we see "a * b + ...", then the
      // rhs of the multiply is b and doesn't involve the "+ ..." because + has
      // lower precedence than *.
      return lhs;
    }

    lexer.takeToken();
    Expression::Ptr rhs = parsePrimaryExpression();

    Token nextOpToken = lexer.peekToken();
    BinaryOpPrecedence nextOpPrecedence = getPrecedence(nextOpToken);
    if (opPrecedence < nextOpPrecedence) {
      // If the operation after the rhs has higher precedence than the one
      // between lhs and rhs, then it is also part of the rhs. For example, if
      // we see "a + b * c" then the rhs of the add is "b * c" and not just "b"
      // because + has lower precedence than *.
      rhs = parseBinaryOp(std::move(rhs), opPrecedence + 1);
    }

    lhs = buildBinaryOp(opToken, std::move(lhs), std::move(rhs), location);
  }
}

Expression::Vec Parser::parseExpressions() {
  // Comma-separated list of one or more expressions
  Expression::Vec expressions;

  do {
    Expression::Ptr expression = parseExpression();
    if (expression) {
      expressions.push_back(std::move(expression));
    } else {
      error("Expected an expression");
      break;
    }
  } while (lexer.takeTokenIf(tok_comma));

  return expressions;
}

Expression::Ptr Parser::parseNegate() {
  if (!lexer.takeTokenIf(tok_minus)) {
    error("expected minus sign at start of negation expression");
    return nullptr;
  }

  SMLoc location = lexer.getLastLocation();
  Expression::Ptr val = parsePrimaryExpression();
  if (!val) {
    error("expected expression after minus sign");
  }

  Ident::Ptr id = make_shared<Ident>(location, "Neg");
  Expression::Vec args;
  args.push_back(std::move(val));
  return make_shared<Construct>(location, std::move(id), std::move(args));
}

} // namespace dsl
} // namespace zirgen
