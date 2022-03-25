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

#include "risc0/core/source_loc.h"
#include "risc0/zkp/core/fp.h"

#include <array>
#include <memory>
#include <vector>

namespace risc0 {

struct ValueImplBase {
  virtual ~ValueImplBase() {}
};

struct BufferImplBase {
  virtual ~BufferImplBase() {}
  size_t size;
  size_t offset;
  size_t back = 0;
  size_t digits = 0;
  bool isMux = false;
};

class Context {
public:
  using ValPtr = std::shared_ptr<ValueImplBase>;
  using BufPtr = std::shared_ptr<BufferImplBase>;

  virtual ~Context() {}

  virtual ValPtr constant(Fp val, SourceLoc loc) = 0;
  virtual ValPtr getVal(BufPtr buf, size_t index, SourceLoc loc) = 0;
  virtual void setVal(BufPtr buf, size_t index, ValPtr val, SourceLoc loc) = 0;
  virtual ValPtr getGlobal(size_t index, SourceLoc loc) = 0;
  virtual void setGlobal(size_t index, ValPtr val, SourceLoc loc) = 0;

  virtual bool beginNondet(SourceLoc loc) = 0;
  virtual void endNondet() = 0;
  virtual void beginGroup(SourceLoc loc) = 0;
  virtual void endGroup() = 0;
  virtual void beginIf(ValPtr a, SourceLoc loc) = 0;
  virtual void endIf() = 0;

  virtual BufPtr slice(BufPtr buf, size_t offset, size_t size, SourceLoc loc) = 0;
  virtual BufPtr back(BufPtr buf, size_t size, SourceLoc loc) = 0;
  virtual BufPtr requireDigits(BufPtr buf, size_t bits, SourceLoc loc) = 0;
  virtual BufPtr requireMux(BufPtr buf, SourceLoc loc) = 0;
  virtual ValPtr getDigits(BufPtr buf, size_t bits, SourceLoc loc) = 0;
  virtual ValPtr setDigits(BufPtr buf, size_t bits, ValPtr input, SourceLoc loc) = 0;
  virtual ValPtr getMux(BufPtr buf, SourceLoc loc) = 0;
  virtual void setMux(BufPtr buf, ValPtr input, SourceLoc loc) = 0;

  virtual ValPtr add(ValPtr a, ValPtr b, SourceLoc loc) = 0;
  virtual ValPtr sub(ValPtr a, ValPtr b, SourceLoc loc) = 0;
  virtual ValPtr mul(ValPtr a, ValPtr b, SourceLoc loc) = 0;
  virtual ValPtr bitAnd(ValPtr a, ValPtr b, SourceLoc loc) = 0;

  virtual ValPtr inv(ValPtr a, SourceLoc loc) = 0;
  virtual ValPtr nonzero(ValPtr a, SourceLoc loc) = 0;

  virtual void assertZero(ValPtr a, SourceLoc loc) = 0;

  virtual void log(const char* str, std::vector<ValPtr> vals) = 0;
  virtual std::array<ValPtr, 4>
  divide32(ValPtr numerLow, ValPtr numerHigh, ValPtr denomLow, ValPtr denomHigh, SourceLoc loc) = 0;
  virtual void memWrite(ValPtr cycle, ValPtr addr, ValPtr low, ValPtr high, SourceLoc loc) = 0;
  virtual std::array<ValPtr, 2> memRead(ValPtr cycle, ValPtr addr, SourceLoc loc) = 0;
  virtual std::array<ValPtr, 5> memCheck(SourceLoc loc) = 0;
};

void setGlobalContext(Context* context);
Context* getGlobalContext();

} // namespace risc0
