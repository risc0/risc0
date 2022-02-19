#pragma once

#include <sstream>

#include "risc0/zkp/circuit/context.h"

namespace risc0 {

class PolyContext : public Context {
public:
  PolyContext();
  ~PolyContext();

  BufPtr addParam(const std::string& name, size_t size);
  std::string done();

  ValPtr constant(Fp val, SourceLoc loc) override;
  ValPtr getVal(BufPtr buf, size_t index, SourceLoc loc) override;
  void setVal(BufPtr buf, size_t index, ValPtr val, SourceLoc loc) override;
  ValPtr getGlobal(size_t index, SourceLoc loc) override;
  void setGlobal(size_t index, ValPtr val, SourceLoc loc) override;

  bool beginNondet(SourceLoc loc) override;
  void endNondet() override;
  void beginGroup(SourceLoc loc) override;
  void endGroup() override;
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

  struct Impl;

private:
  std::unique_ptr<Impl> impl;
};

} // namespace risc0
