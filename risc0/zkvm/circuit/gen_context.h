// Copyright 2022 Risc0, Inc.
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

#include <sstream>

#include "risc0/zkvm/circuit/context.h"

namespace risc0 {

class GenContext : public Context {
public:
  GenContext(const char* name);
  ~GenContext() override {}

  BufPtr addParam(const std::string& name, size_t size, bool isConst);
  void paramsDone();
  std::string funcDone();

  ValPtr constant(Fp val, SourceLoc loc) override;
  ValPtr getVal(BufPtr buf, size_t index, SourceLoc loc) override;
  void setVal(BufPtr buf, size_t index, ValPtr val, SourceLoc loc) override;
  ValPtr getGlobal(size_t index, SourceLoc loc) override;
  void setGlobal(size_t index, ValPtr val, SourceLoc loc) override;

  bool beginNondet(SourceLoc loc) override;
  void endNondet() override;
  void beginGroup(SourceLoc loc) override {}
  void endGroup() override {}
  void beginIf(ValPtr a, SourceLoc loc) override;
  void endIf() override;

  BufPtr slice(BufPtr buf, size_t offset, size_t size, SourceLoc loc) override;
  BufPtr back(BufPtr buf, size_t size, SourceLoc loc) override;
  BufPtr requireDigits(BufPtr buf, size_t bits, SourceLoc loc) override;
  BufPtr requireMux(BufPtr buf, SourceLoc loc) override;
  ValPtr getDigits(BufPtr buf, size_t bits, SourceLoc loc) override;
  ValPtr setDigits(BufPtr buf, size_t bits, ValPtr input, SourceLoc loc) override;
  ValPtr getMux(BufPtr buf, SourceLoc loc) override;
  void setMux(BufPtr buf, ValPtr input, SourceLoc loc) override;

  ValPtr add(ValPtr a, ValPtr b, SourceLoc loc) override;
  ValPtr sub(ValPtr a, ValPtr b, SourceLoc loc) override;
  ValPtr mul(ValPtr a, ValPtr b, SourceLoc loc) override;
  ValPtr bitAnd(ValPtr a, ValPtr b, SourceLoc loc) override;

  ValPtr inv(ValPtr a, SourceLoc loc) override;
  ValPtr nonzero(ValPtr a, SourceLoc loc) override;

  void assertZero(ValPtr a, SourceLoc loc) override;

  void log(const char* str, std::vector<ValPtr> vals) override;
  std::array<ValPtr, 4> divide32(
      ValPtr numerLow, ValPtr numerHigh, ValPtr denomLow, ValPtr denomHigh, SourceLoc loc) override;
  void memWrite(ValPtr cycle, ValPtr addr, ValPtr low, ValPtr high, SourceLoc loc) override;
  std::array<ValPtr, 2> memRead(ValPtr cycle, ValPtr addr, SourceLoc loc) override;
  std::array<ValPtr, 5> memCheck(SourceLoc loc) override;

private:
  size_t nextId = 0;
  size_t indent = 0;
  std::stringstream outs;
  std::vector<std::stringstream> verifyStack;
  std::ostream& begl();
  std::ostream& vegl();
  std::ostream& defl();
  std::string loc(SourceLoc loc);
  std::string endl(SourceLoc loc);
  ValPtr newDef();
};

} // namespace risc0
