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

#include <unordered_map>

#include "zirgen/dsl/lexer.h"

namespace zirgen {
namespace dsl {

Reader::Reader(const llvm::MemoryBuffer* buf)
    : position(buf->getBufferStart()), end(buf->getBufferEnd()) {}

Lexer::Lexer(llvm::SourceMgr& sourceMgr, std::vector<llvm::SMDiagnostic>& errors)
    : sourceMgr(sourceMgr)
    , errors(errors)
    , source(sourceMgr.getMemoryBuffer(sourceMgr.getMainFileID()))
    , lastLocation(source.location()) {}

Token Lexer::peekToken() {
  skipToNextToken();
  Reader start = this->source;
  llvm::SMLoc last = this->lastLocation;
  auto oldStack = this->stack;
  Token token = takeToken();
  this->source = start;
  this->lastLocation = last;
  this->stack = oldStack;
  return token;
}

Token Lexer::takeToken() {
  // Get the next character
  skipToNextToken();
  char c = takeNextChar();

  // End any imports
  while (c == 0) {
    if (stack.empty()) {
      return tok_eof;
    }
    this->source = stack.back();
    stack.pop_back();
    skipToNextToken();
    c = takeNextChar();
  }

  // Set the "last location" to the start of the token we are about to lex
  this->lastLocation = source.location();

  // Tokens that start with [a-zA-Z] are identifiers or keywords
  if (isalpha(c) || c == '_') {
    identifier.clear();
    do {
      identifier.push_back((char)c);
      c = takeNextChar();
    } while (isalnum(c) || c == '_');
    unget();

    static const std::unordered_map<std::string, Token> keywords{
        {"argument", tok_argument},
        {"component", tok_component},
        {"function", tok_function},
        {"else", tok_else},
        {"extern", tok_extern},
        {"for", tok_for},
        {"if", tok_if},
        {"import", tok_import},
        {"init", tok_init},
        {"order", tok_order},
        {"reduce", tok_reduce},
        {"test", tok_test},
        {"test_fails", tok_test_fails},
        {"with", tok_with},
        {"global", tok_global},
    };
    auto found = keywords.find(identifier);
    return found != keywords.end() ? found->second : tok_ident;
  }

  // Literals are one of the following:
  // [0-9]+ are decimal literals
  // 0x[0-9a-fA-F]+ are hexadecimal literals
  // 0b[0-1]+ are binary literals
  if (isdigit(c)) {
    std::string digitString;
    int base;

    if (c == '0' && peek() == 'x') {
      // hexadecimal literal - skip past the "0x"
      takeNextChar();
      c = takeNextChar();
      base = 16;
    } else if (c == '0' && peek() == 'b') {
      // binary literal - skip past the "0b"
      takeNextChar();
      c = takeNextChar();
      base = 2;

    } else {
      // decimal literal
      base = 10;
    }

    auto isLiteralDigit = [base](int c) {
      if (base == 2) {
        return (int)(c == '0' || c == '1');
      } else if (base == 10) {
        return isdigit(c);
      } else if (base == 16) {
        return isxdigit(c);
      } else {
        throw std::runtime_error("Unknown literal base");
      }
    };

    while (isLiteralDigit(c)) {
      digitString.push_back((char)c);
      c = takeNextChar();
    }
    unget();

    if (digitString.empty()) {
      error("Literal base prefix not followed by one or more digits");
      digitString = "0";
    }

    try {
      this->literal = std::stol(digitString, nullptr, base);
    } catch (std::out_of_range const& ex) {
      error("Literal value exceeds legal range");
    }
    return tok_literal;
  }

  // String literals
  if (c == '"') {
    identifier.clear();
    // skip past the opening quote
    c = takeNextChar();
    while (c != '"' && c != '\n') {
      identifier.push_back((char)c);
      c = takeNextChar();
    }

    if (c == '\n') {
      error("String literals must be closed before the end of the line");
    }

    return tok_string_literal;
  }

  // Multi-character operators
  if (c == ':') {
    if (takeNextChar() == '=') {
      return tok_define;
    } else {
      unget();
    }
  }

  if (c == '-') {
    if (takeNextChar() == '>') {
      return tok_mux;
    } else {
      unget();
    }
  }

  if (c == '.') {
    if (takeNextChar() == '.') {
      if (takeNextChar() == '.') {
        return tok_variadic;
      }
      unget();
      return tok_range;
    } else {
      unget();
    }
  }

  // All of the other tokens are single characters that coincide with their
  // ascii codes, interpreted as an unsigned integer in order not to conflict
  // with our grammar's token codes (which are all negative).
  return Token(static_cast<unsigned char>(c));
}

bool Lexer::takeTokenIf(Token token) {
  skipToNextToken();
  Reader start = this->source;
  llvm::SMLoc last = this->lastLocation;

  if (takeToken() == token) {
    return true;
  } else {
    this->source = start;
    this->lastLocation = last;
    return false;
  }
}

void Lexer::doImport(llvm::StringRef name) {
  if (imported.count(name.str())) {
    // Ignore any file already imported once
    return;
  }
  // Whether we succeed or fail, never try again
  imported.insert(name.str());
  // Add .zir suffix
  std::string filename = (name + ".zir").str();
  // Try to include it
  std::string full_path;
  unsigned id = sourceMgr.AddIncludeFile(filename, source.location(), full_path);
  if (id == 0) {
    error("Unable to find file '" + filename + "'");
    return;
  }
  // Move position to begining of included file
  stack.push_back(source);
  source = Reader(sourceMgr.getMemoryBuffer(id));
}

void Lexer::addPreamble(llvm::StringRef preambleText) {
  auto preamble = llvm::MemoryBuffer::getMemBuffer(preambleText, "<preamble>");
  auto id = sourceMgr.AddNewSourceBuffer(std::move(preamble), llvm::SMLoc());
  stack.push_back(source);
  source = Reader(sourceMgr.getMemoryBuffer(id));
}

void Lexer::error(llvm::StringRef error) {
  errors.push_back(
      sourceMgr.GetMessage(source.location(), llvm::SourceMgr::DiagKind::DK_Error, error));
}

void Lexer::skipWhitespace() {
  int c;
  do {
    c = takeNextChar();
  } while (isspace(c));
  unget();
}

void Lexer::skipToEndOfLine() {
  int c;
  do {
    c = takeNextChar();
  } while (c != '\n' && c != 0);
  if (c == 0) {
    unget();
  }
}

void Lexer::skipToEndOfBlockComment() {
  int c;
  do {
    do {
      c = takeNextChar();
      if (c == 0) {
        unget();
        error("EOF when reading block comment");
        return;
      }
    } while (c != '*');
  } while (peek() != '/');
  takeNextChar();
}

void Lexer::skipToNextToken() {
  skipWhitespace();

  while (peek() == '/') {
    Reader startPos = source;
    takeNextChar();
    int c2 = takeNextChar();

    if (c2 == '/') {
      // The leading '/' is the start of a line comment
      skipToEndOfLine();
      skipWhitespace();
    } else if (c2 == '*') {
      // The leading '/' is the start of a block comment
      skipToEndOfBlockComment();
      skipWhitespace();
    } else {
      // The leading '/' is the start of the next token
      source = startPos;
      break;
    }
  }
}

} // namespace dsl
} // namespace zirgen
