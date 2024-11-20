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

#include <iostream>
#include <set>
#include <string>

#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

namespace zirgen {
namespace dsl {

enum Token : int {
  tok_angle_l = '<',
  tok_angle_r = '>',
  tok_bang = '!',
  tok_bit_and = '&',
  tok_colon = ':',
  tok_comma = ',',
  tok_curly_l = '{',
  tok_curly_r = '}',
  tok_div = '/',
  tok_dot = '.',
  tok_eq = '=',
  tok_minus = '-',
  tok_paren_l = '(',
  tok_paren_r = ')',
  tok_plus = '+',
  tok_semicolon = ';',
  tok_square_l = '[',
  tok_square_r = ']',
  tok_times = '*',
  tok_back = '@',
  tok_component = -1,
  tok_define = -2,
  tok_else = -3,
  tok_for = -4,
  tok_ident = -5,
  tok_if = -6,
  tok_init = -7,
  tok_import = -8,
  tok_literal = -9,
  tok_mux = -10,
  tok_order = -11,
  tok_range = -12,
  tok_reduce = -13,
  tok_with = -14,
  tok_function = -15,
  tok_extern = -16,
  tok_test = -17,
  tok_test_fails = -18,
  tok_argument = -19,
  tok_string_literal = -20,
  tok_variadic = -21,
  tok_global = -22,
  tok_eof = 0,
};

inline llvm::raw_ostream& operator<<(llvm::raw_ostream& os, const Token& tok) {
  if (isprint(tok)) {
    os << "'" << static_cast<char>(tok) << "'";
  } else {
    os << static_cast<int>(tok);
  }
  return os;
}

class Reader {
public:
  Reader(const llvm::MemoryBuffer* buf);
  char peek() const { return eof() ? 0 : *position; }
  char take() { return eof() ? extra++, 0 : *position++; }
  void unget() {
    if (extra)
      extra--;
    else
      position--;
  }
  bool eof() const { return position == end; }
  llvm::SMLoc location() { return llvm::SMLoc::getFromPointer(position); }

private:
  const char* position;
  const char* end;
  unsigned extra = 0;
};

class Lexer {
public:
  // Construct a lexer with a SourceMgr, presume main file has been opened already
  Lexer(llvm::SourceMgr& file, std::vector<llvm::SMDiagnostic>& errors);

  // Lexes and returns the next token, without advancing the lexer
  Token peekToken();

  // Lexes and returns the next token, advancing the lexer
  Token takeToken();

  // Lexes the next token, advancing the lexer and returning true only if it matches the given token
  bool takeTokenIf(Token token);

  // Returns the location of the most recently lexed token
  llvm::SMLoc getLastLocation() const { return lastLocation; }

  // If the current token is an identifier, this member contains its text.
  // Otherwise, its value is undefined.
  const std::string& getIdentifier() const { return identifier; }

  // If the current token is a literal, this member contains its value.
  // Otherwise, its value is undefined.
  uint64_t getLiteral() const { return literal; }

  // Attempt to import the given file
  void doImport(llvm::StringRef name);

  bool inMain() { return stack.empty(); }

  // Adds the given preamble ZIR code to the lexer.
  void addPreamble(llvm::StringRef preambleText);

private:
  // Add an error message at the current position
  void error(llvm::StringRef error);

  // Advances the lexer until the next non-whitespace character
  void skipWhitespace();

  // Advances the lexer until the end of the line, to consume a single-line comment
  void skipToEndOfLine();

  // Advances the lexer until the next occurence of "*/"
  void skipToEndOfBlockComment();

  // Advances the lexer until the start of the next token, skipping over
  // whitespace and comments
  void skipToNextToken();

  char peek() { return source.peek(); }
  char takeNextChar() { return source.take(); }
  void unget() { source.unget(); }

  // The source manager
  llvm::SourceMgr& sourceMgr;
  // Where to put errors
  std::vector<llvm::SMDiagnostic>& errors;

  // The stack of things to return to at EOF (for import handling)
  std::vector<Reader> stack;
  // The list of files already imported
  std::set<std::string> imported;

  // Iterator over the current input buffer
  Reader source;

  // The location of the most recently lexed token
  llvm::SMLoc lastLocation;

  std::string identifier;
  uint64_t literal;
};

} // namespace dsl
} // namespace zirgen
