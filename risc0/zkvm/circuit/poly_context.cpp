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

#include "risc0/zkvm/circuit/poly_context.h"

#include "risc0/core/log.h"
#include "risc0/core/util.h"
#include "risc0/zkvm/circuit/constants.h"

#include <map>
#include <set>
#include <sstream>

namespace risc0 {

namespace {

struct PolyOpInterface : public ValueImplBase,
                         public std::enable_shared_from_this<PolyOpInterface> {
  virtual int getTypeID() const = 0;
  virtual bool lessThan(const PolyOpInterface& rhs) const = 0;
  virtual int degree() const = 0;
  virtual void computeTaps(PolyContext::Impl& impl) = 0;
  virtual std::string output(PolyContext::Impl& impl) = 0;
  virtual void findCriticalPath(PolyContext::Impl& impl) = 0;
};

template <typename Derived, int TypeID> struct PolyOpBase : PolyOpInterface {
  mutable int cachedDegree = -1;
  int getTypeID() const override { return TypeID; }
  bool lessThan(const PolyOpInterface& rhs) const override {
    if (rhs.getTypeID() != TypeID) {
      return TypeID < rhs.getTypeID();
    }
    return static_cast<const Derived*>(this)->key() < static_cast<const Derived&>(rhs).key();
  }
  int degree() const override {
    if (cachedDegree < 0) {
      cachedDegree = static_cast<const Derived*>(this)->getDegree();
    }
    return cachedDegree;
  }
};

using PolyOp = std::shared_ptr<PolyOpInterface>;

struct OpConstant : public PolyOpBase<OpConstant, 0> {
  Fp value;
  OpConstant(Fp value) : value(value) {}
  int getDegree() const { return 0; }
  Fp key() const { return value; }
  void computeTaps(PolyContext::Impl& impl) override {}
  std::string output(PolyContext::Impl& impl) override;
  void findCriticalPath(PolyContext::Impl& impl) override;
};

struct OpGet : public PolyOpBase<OpGet, 1> {
  std::string base;
  size_t offset;
  size_t back;
  OpGet(const std::string& base, size_t offset, size_t back)
      : base(base), offset(offset), back(back) {}
  int getDegree() const { return 1; }
  std::tuple<std::string, size_t, size_t> key() const {
    return std::make_tuple(base, offset, back);
  }
  void computeTaps(PolyContext::Impl& impl) override;
  std::string output(PolyContext::Impl& impl) override;
  void findCriticalPath(PolyContext::Impl& impl) override;
};

struct OpAdd : public PolyOpBase<OpAdd, 2> {
  PolyOp lhs;
  PolyOp rhs;
  OpAdd(PolyOp lhs, PolyOp rhs) : lhs(lhs), rhs(rhs) {}
  int getDegree() const { return std::max(lhs->degree(), rhs->degree()); }
  std::pair<PolyOp, PolyOp> key() const { return std::make_pair(lhs, rhs); }
  void computeTaps(PolyContext::Impl& impl) override {
    lhs->computeTaps(impl);
    rhs->computeTaps(impl);
  }
  std::string output(PolyContext::Impl& impl) override;
  void findCriticalPath(PolyContext::Impl& impl) override;
};

struct OpSub : public PolyOpBase<OpSub, 3> {
  PolyOp lhs;
  PolyOp rhs;
  OpSub(PolyOp lhs, PolyOp rhs) : lhs(lhs), rhs(rhs) {}
  int getDegree() const { return std::max(lhs->degree(), rhs->degree()); }
  std::pair<PolyOp, PolyOp> key() const { return std::make_pair(lhs, rhs); }
  void computeTaps(PolyContext::Impl& impl) override {
    lhs->computeTaps(impl);
    rhs->computeTaps(impl);
  }
  std::string output(PolyContext::Impl& impl) override;
  void findCriticalPath(PolyContext::Impl& impl) override;
};

struct OpMul : public PolyOpBase<OpMul, 4> {
  PolyOp lhs;
  PolyOp rhs;
  OpMul(PolyOp lhs, PolyOp rhs) : lhs(lhs), rhs(rhs) {}
  int getDegree() const { return lhs->degree() + rhs->degree(); }
  std::pair<PolyOp, PolyOp> key() const { return std::make_pair(lhs, rhs); }
  void computeTaps(PolyContext::Impl& impl) override {
    lhs->computeTaps(impl);
    rhs->computeTaps(impl);
  }
  std::string output(PolyContext::Impl& impl) override;
  void findCriticalPath(PolyContext::Impl& impl) override;
};

struct OpBegin : public PolyOpBase<OpBegin, 5> {
  int getDegree() const { return 0; }
  int key() const { return 0; }
  void computeTaps(PolyContext::Impl& impl) override {}
  std::string output(PolyContext::Impl& impl) override;
  void findCriticalPath(PolyContext::Impl& impl) override;
};

struct OpAssertZero : public PolyOpBase<OpAssertZero, 6> {
  PolyOp prev;
  PolyOp zero;
  OpAssertZero(PolyOp prev, PolyOp zero) : prev(prev), zero(zero) {}
  int getDegree() const { return std::max(prev->degree(), zero->degree()); }
  std::pair<PolyOp, PolyOp> key() const { return std::make_pair(prev, zero); }
  void computeTaps(PolyContext::Impl& impl) override {
    prev->computeTaps(impl);
    zero->computeTaps(impl);
  }
  std::string output(PolyContext::Impl& impl) override;
  void findCriticalPath(PolyContext::Impl& impl) override;
};

struct OpCombine : public PolyOpBase<OpCombine, 7> {
  PolyOp prev;
  PolyOp mul;
  PolyOp inner;
  OpCombine(PolyOp prev, PolyOp mul, PolyOp inner) : prev(prev), mul(mul), inner(inner) {}
  int getDegree() const { return std::max(prev->degree(), mul->degree() + inner->degree()); }
  std::tuple<PolyOp, PolyOp, PolyOp> key() const { return std::make_tuple(prev, mul, inner); }
  void computeTaps(PolyContext::Impl& impl) override {
    prev->computeTaps(impl);
    mul->computeTaps(impl);
    inner->computeTaps(impl);
  }
  std::string output(PolyContext::Impl& impl) override;
  void findCriticalPath(PolyContext::Impl& impl) override;
};

struct OpGetGlobal : public PolyOpBase<OpGetGlobal, 8> {
  size_t offset;
  OpGetGlobal(size_t offset) : offset(offset) {}
  int getDegree() const { return 0; }
  size_t key() const { return offset; }
  void computeTaps(PolyContext::Impl& impl) override {}
  std::string output(PolyContext::Impl& impl) override;
  void findCriticalPath(PolyContext::Impl& impl) override;
};

struct PolyBuffer : public BufferImplBase {
  std::string param;
};

PolyOp asPoly(Context::ValPtr ptr) {
  return std::static_pointer_cast<PolyOpInterface>(ptr);
}

struct InternLessThan {
  bool operator()(PolyOp a, PolyOp b) const { return a->lessThan(*b); }
};

} // namespace

struct PolyContext::Impl {
  std::set<PolyOp, InternLessThan> interned;
  std::vector<PolyOp> condStack;
  std::vector<SourceLoc> locStack;
  std::vector<PolyOp> resultStack;
  std::map<PolyOp, SourceLoc> opToLoc;
  std::map<PolyOp, std::string> opToName;
  std::stringstream outs;
  struct Tap {
    std::string base;
    size_t offset;
    size_t back;
    Tap(const std::string& base, size_t offset, size_t back)
        : base(base), offset(offset), back(back) {}
    bool operator<(const Tap& rhs) const {
      return std::make_tuple(base, offset, back) < std::make_tuple(rhs.base, rhs.offset, rhs.back);
    }
  };
  std::set<Tap> taps;
  std::map<Tap, size_t> tapToID;

  template <typename OpClass, typename... Args> PolyOp intern(SourceLoc loc, Args... args) {
    PolyOp newOp = std::make_shared<OpClass>(args...);
    auto it = interned.find(newOp);
    if (it != interned.end()) {
      return *it;
    }
    interned.emplace(newOp);
    opToLoc[newOp] = loc;
    return newOp;
  }
  Impl() { resultStack.push_back(intern<OpBegin>(SourceLoc::current())); }
  bool isConst(PolyOp a) { return static_cast<bool>(std::dynamic_pointer_cast<OpConstant>(a)); }
  Fp getConst(PolyOp a) { return std::dynamic_pointer_cast<OpConstant>(a)->value; }
  PolyOp constant(Fp val, SourceLoc loc) { return intern<OpConstant>(loc, val); }
  PolyOp get(const std::string& name, size_t offset, size_t back, SourceLoc loc) {
    return intern<OpGet>(loc, name, offset, back);
  }
  PolyOp getGlobal(size_t offset, SourceLoc loc) { return intern<OpGetGlobal>(loc, offset); }
  PolyOp add(PolyOp a, PolyOp b, SourceLoc loc) {
    if (isConst(a) && !isConst(b)) {
      std::swap(a, b);
    }
    if (isConst(b) && getConst(b) == 0) {
      return a;
    }
    if (isConst(a) && isConst(b)) {
      return constant(getConst(a) + getConst(b), loc);
    }
    return intern<OpAdd>(loc, a, b);
  }
  PolyOp sub(PolyOp a, PolyOp b, SourceLoc loc) {
    if (isConst(b) && getConst(b) == 0) {
      return a;
    }
    if (isConst(a) && isConst(b)) {
      return constant(getConst(a) - getConst(b), loc);
    }
    if (a == b) {
      return constant(0, loc);
    }
    return intern<OpSub>(loc, a, b);
  }
  PolyOp mul(PolyOp a, PolyOp b, SourceLoc loc) {
    if (isConst(a) && !isConst(b)) {
      std::swap(a, b);
    }
    if (isConst(b) && getConst(b) == 0) {
      return constant(0, loc);
    }
    if (isConst(b) && getConst(b) == 1) {
      return a;
    }
    if (isConst(a) && isConst(b)) {
      return constant(getConst(a) * getConst(b), loc);
    }
    return intern<OpMul>(loc, a, b);
  }
  void assertZero(PolyOp a, SourceLoc loc) {
    resultStack.back() = intern<OpAssertZero>(loc, resultStack.back(), a);
  }
  void beginGroup(SourceLoc loc) {
    locStack.push_back(loc);
    resultStack.push_back(intern<OpBegin>(loc));
  }
  void endGroup() {
    PolyOp inner = resultStack.back();
    auto cond = constant(1, locStack.back());
    resultStack.pop_back();
    resultStack.back() = intern<OpCombine>(locStack.back(), resultStack.back(), cond, inner);
    locStack.pop_back();
  }
  void beginIf(PolyOp a, SourceLoc loc) {
    condStack.push_back(a);
    locStack.push_back(loc);
    resultStack.push_back(intern<OpBegin>(loc));
  }
  void endIf() {
    PolyOp cond = condStack.back();
    condStack.pop_back();
    PolyOp inner = resultStack.back();
    resultStack.pop_back();
    resultStack.back() = intern<OpCombine>(locStack.back(), resultStack.back(), cond, inner);
    locStack.pop_back();
  }
  std::string eval(PolyOp op) {
    auto it = opToName.find(op);
    if (it != opToName.end()) {
      return it->second;
    }
    std::string opName = "val" + std::to_string(opToName.size());
    opToName[op] = opName;
    std::string expr = op->output(*this);
    outs << "  auto " << opName << " = " << expr << "; // deg=" << op->degree() << ", "
         << opToLoc[op].filename << ":" << opToLoc[op].line << "\n";
    return opName;
  }
  void onCriticalPath(PolyOp op) {
    LOG(0,
        "  name=" << opToName[op] << ", deg=" << op->degree() << " " << opToLoc[op].filename << ":"
                  << opToLoc[op].line);
  }
};

std::string OpConstant::output(PolyContext::Impl& impl) {
  return "Fp(" + value.str() + ")";
}

void OpConstant::findCriticalPath(PolyContext::Impl& impl) {}

void OpGet::computeTaps(PolyContext::Impl& impl) {
  impl.taps.emplace(base, offset, back);
}

std::string OpGet::output(PolyContext::Impl& impl) {
  using Tap = PolyContext::Impl::Tap;
  Tap myTap = {base, offset, back};
  size_t myID = impl.tapToID[myTap];
  return std::string("do_get(") + base + ", " + std::to_string(offset) + ", " +
         std::to_string(back) + ", " + std::to_string(myID) + ")";
}

void OpGet::findCriticalPath(PolyContext::Impl& impl) {
  impl.onCriticalPath(shared_from_this());
}

std::string OpGetGlobal::output(PolyContext::Impl& impl) {
  return std::string("do_get_global(") + std::to_string(offset) + ")";
}

void OpGetGlobal::findCriticalPath(PolyContext::Impl& impl) {}

std::string OpAdd::output(PolyContext::Impl& impl) {
  return std::string("do_add(") + impl.eval(lhs) + ", " + impl.eval(rhs) + ")";
}

void OpAdd::findCriticalPath(PolyContext::Impl& impl) {
  if (lhs->degree() < rhs->degree()) {
    rhs->findCriticalPath(impl);
  } else {
    lhs->findCriticalPath(impl);
  }
}

std::string OpSub::output(PolyContext::Impl& impl) {
  return std::string("do_sub(") + impl.eval(lhs) + ", " + impl.eval(rhs) + ")";
}

void OpSub::findCriticalPath(PolyContext::Impl& impl) {
  if (lhs->degree() < rhs->degree()) {
    rhs->findCriticalPath(impl);
  } else {
    lhs->findCriticalPath(impl);
  }
}

std::string OpMul::output(PolyContext::Impl& impl) {
  return std::string("do_mul(") + impl.eval(lhs) + ", " + impl.eval(rhs) + ")";
}

void OpMul::findCriticalPath(PolyContext::Impl& impl) {
  impl.onCriticalPath(shared_from_this());
  rhs->findCriticalPath(impl);
  lhs->findCriticalPath(impl);
}

std::string OpBegin::output(PolyContext::Impl& impl) {
  return std::string("do_begin()");
}

void OpBegin::findCriticalPath(PolyContext::Impl& impl) {}

std::string OpAssertZero::output(PolyContext::Impl& impl) {
  auto opLoc = impl.opToLoc[shared_from_this()];
  return std::string("do_assert_zero(") + impl.eval(prev) + ", " + impl.eval(zero) + ", \"" +
         opLoc.filename + ":" + std::to_string(opLoc.line) + "\")";
}

void OpAssertZero::findCriticalPath(PolyContext::Impl& impl) {
  if (prev->degree() == degree()) {
    prev->findCriticalPath(impl);
    return;
  }
  impl.onCriticalPath(shared_from_this());
  zero->findCriticalPath(impl);
}

std::string OpCombine::output(PolyContext::Impl& impl) {
  auto opLoc = impl.opToLoc[shared_from_this()];
  return std::string("do_combine(") + impl.eval(prev) + ", " + impl.eval(mul) + "," +
         impl.eval(inner) + ", \"" + opLoc.filename + ":" + std::to_string(opLoc.line) + "\")";
}

void OpCombine::findCriticalPath(PolyContext::Impl& impl) {
  if (prev->degree() == degree()) {
    prev->findCriticalPath(impl);
    return;
  }
  impl.onCriticalPath(shared_from_this());
  mul->findCriticalPath(impl);
  inner->findCriticalPath(impl);
}

PolyContext::PolyContext() : impl(std::make_unique<Impl>()) {}

PolyContext::~PolyContext() {}

Context::BufPtr PolyContext::addParam(const std::string& name, size_t size) {
  auto out = std::make_shared<PolyBuffer>();
  out->size = size;
  out->param = name;
  return out;
}

std::string PolyContext::done() {
  impl->outs << "#ifdef CHECK_EVAL\n";
  PolyOp result = impl->resultStack.back();
  impl->resultStack.pop_back();
  REQUIRE(impl->condStack.empty());
  REQUIRE(impl->resultStack.empty());
  result->computeTaps(*impl);
  size_t nextID = 0;
  for (const auto& tap : impl->taps) {
    impl->tapToID[tap] = nextID++;
  }
  std::string finalName = impl->eval(result);
  if (result->degree() > kMaxDegree) {
    result->findCriticalPath(*impl);
    throw std::runtime_error("Degree too large!");
  }
  std::map<std::set<size_t>, size_t> uniqCombos;
  std::vector<std::set<size_t>> comboById;
  std::set<size_t> simpleCombo = {0};
  comboById.push_back(simpleCombo);
  uniqCombos[simpleCombo] = 0;
  impl->outs << "  auto result = " << finalName << ";\n";
  impl->outs << "#endif  // CHECK_EVAL\n";
  impl->outs << "#ifdef TAPS\n";
  impl->outs << R"**(
#ifndef base_begin
#define base_begin(base) /**/
#endif
#ifndef base_end
#define base_end(base) /**/
#endif
#ifndef offset_begin
#define offset_begin(base, offset) /**/
#endif
#ifndef offset_end
#define offset_end(base, offset, combo) /**/
#endif
#ifndef tap
#define tap(base, offset, back) /**/
#endif
)**";
  Impl::Tap prev("", 0, 0);
  bool first = true;
  std::set<size_t> curCombo;
  auto comboFinal = [&]() {
    size_t id;
    auto it = uniqCombos.find(curCombo);
    if (it != uniqCombos.end()) {
      id = it->second;
    } else {
      id = comboById.size();
      uniqCombos[curCombo] = id;
      comboById.push_back(curCombo);
    }
    curCombo.clear();
    return id;
  };
  for (const auto& tap : impl->taps) {
    if (first) {
      impl->outs << "base_begin(" << tap.base << ")\n";
      impl->outs << "  offset_begin(" << tap.base << ", " << tap.offset << ")\n";
    }
    if (!first && prev.base != tap.base) {
      size_t id = comboFinal();
      impl->outs << "  offset_end(" << prev.base << ", " << prev.offset << ", " << id << ")\n";
      impl->outs << "base_end(" << prev.base << ")\n";
      impl->outs << "base_begin(" << tap.base << ")\n";
      impl->outs << "  offset_begin(" << tap.base << ", " << tap.offset << ")\n";
    } else if (!first && prev.offset != tap.offset) {
      size_t id = comboFinal();
      impl->outs << "  offset_end(" << prev.base << ", " << prev.offset << ", " << id << ")\n";
      impl->outs << "  offset_begin(" << tap.base << ", " << tap.offset << ")\n";
    }
    impl->outs << "    tap(" << tap.base << ", " << tap.offset << ", " << tap.back << ")\n";
    curCombo.emplace(tap.back);
    first = false;
    prev = tap;
  }
  size_t id = comboFinal();
  impl->outs << "  offset_end(" << prev.base << ", " << prev.offset << ", " << id << ")\n";
  impl->outs << "base_end(" << prev.base << ")\n";
  impl->outs << R"**(
#undef base_begin
#undef base_end
#undef offset_begin
#undef offset_end
#undef tap
)**";
  impl->outs << "#endif  // TAPS\n";
  if (kComboCount != comboById.size()) {
    LOG(0, "Required " << comboById.size() << " combos");
  }
  REQUIRE(kComboCount == comboById.size());

  return impl->outs.str();
}

Context::ValPtr PolyContext::constant(Fp val, SourceLoc loc) {
  return impl->constant(val, loc);
}

Context::ValPtr PolyContext::getVal(BufPtr buf, size_t index, SourceLoc loc) {
  auto pbuf = std::static_pointer_cast<PolyBuffer>(buf);
  return impl->get(pbuf->param, pbuf->offset + index, pbuf->back, loc);
}

void PolyContext::setVal(BufPtr buf, size_t index, ValPtr val, SourceLoc loc) {
  auto pbuf = std::static_pointer_cast<PolyBuffer>(buf);
  auto lhs = impl->get(pbuf->param, pbuf->offset + index, pbuf->back, loc);
  impl->assertZero(impl->sub(lhs, asPoly(val), loc), loc);
}

Context::ValPtr PolyContext::getGlobal(size_t index, SourceLoc loc) {
  return impl->getGlobal(index, loc);
}

void PolyContext::setGlobal(size_t index, ValPtr val, SourceLoc loc) {
  auto lhs = impl->getGlobal(index, loc);
  impl->assertZero(impl->sub(lhs, asPoly(val), loc), loc);
}

bool PolyContext::beginNondet(SourceLoc loc) {
  return false;
}
void PolyContext::endNondet() {}

void PolyContext::beginGroup(SourceLoc loc) {
  impl->beginGroup(loc);
}

void PolyContext::endGroup() {
  impl->endGroup();
}

void PolyContext::beginIf(ValPtr a, SourceLoc loc) {
  impl->beginIf(asPoly(a), loc);
}

void PolyContext::endIf() {
  impl->endIf();
}

Context::BufPtr PolyContext::slice(BufPtr buf, size_t offset, size_t size, SourceLoc loc) {
  auto pbuf = std::static_pointer_cast<PolyBuffer>(buf);
  auto nbuf = std::make_shared<PolyBuffer>(*pbuf);
  if (offset + size > pbuf->size) {
    throw std::runtime_error("Slice out of bounds");
  }
  nbuf->offset += offset;
  nbuf->size = size;
  return nbuf;
}

Context::BufPtr PolyContext::back(BufPtr buf, size_t size, SourceLoc loc) {
  auto pbuf = std::static_pointer_cast<PolyBuffer>(buf);
  auto nbuf = std::make_shared<PolyBuffer>(*pbuf);
  nbuf->back += size;
  return nbuf;
}

Context::BufPtr PolyContext::requireDigits(BufPtr buf, size_t bits, SourceLoc loc) {
  auto pbuf = std::static_pointer_cast<PolyBuffer>(buf);
  if (pbuf->digits != 0 && pbuf->digits <= bits) {
    return pbuf;
  }
  auto nbuf = std::make_shared<PolyBuffer>(*pbuf);
  nbuf->digits = bits;
  if (pbuf->back == 0) {
    for (size_t i = 0; i < pbuf->size; i++) {
      PolyOp val = impl->get(pbuf->param, pbuf->offset + i, 0, loc);
      PolyOp cur = impl->constant(1, loc);
      for (int j = 0; j < (1 << bits); j++) {
        cur = impl->mul(cur, impl->sub(val, impl->constant(j, loc), loc), loc);
      }
      impl->assertZero(cur, loc);
    }
  }
  return nbuf;
}

Context::BufPtr PolyContext::requireMux(BufPtr buf, SourceLoc loc) {
  auto pbuf = std::static_pointer_cast<PolyBuffer>(buf);
  auto nbuf = std::make_shared<PolyBuffer>(*pbuf);
  nbuf->digits = 1;
  nbuf->isMux = true;
  if (pbuf->back == 0) {
    (void)requireDigits(buf, 1, loc);
    PolyOp tot = impl->constant(0, loc);
    for (size_t i = 0; i < pbuf->size; i++) {
      PolyOp val = impl->get(pbuf->param, pbuf->offset + i, 0, loc);
      tot = impl->add(tot, val, loc);
    }
    impl->assertZero(impl->sub(tot, impl->constant(1, loc), loc), loc);
  }
  return nbuf;
}

Context::ValPtr PolyContext::getDigits(BufPtr buf, size_t bits, SourceLoc loc) {
  auto pbuf = std::static_pointer_cast<PolyBuffer>(buf);
  PolyOp tot = impl->constant(0, loc);
  for (size_t i = 0; i < pbuf->size; i++) {
    PolyOp val = impl->get(pbuf->param, pbuf->offset + i, pbuf->back, loc);
    PolyOp bitMul = impl->constant(1 << (i * bits), loc);
    tot = impl->add(tot, impl->mul(bitMul, val, loc), loc);
  }
  return tot;
}

Context::ValPtr PolyContext::setDigits(BufPtr buf, size_t bits, ValPtr input, SourceLoc loc) {
  auto pbuf = std::static_pointer_cast<PolyBuffer>(buf);
  PolyOp getVal = asPoly(getDigits(buf, bits, loc));
  PolyOp subDigits = impl->sub(asPoly(input), getVal, loc);
  Fp shiftDiv = ::risc0::inv(Fp(1 << (pbuf->size * bits)));
  return impl->mul(subDigits, impl->constant(shiftDiv, loc), loc);
}

Context::ValPtr PolyContext::getMux(BufPtr buf, SourceLoc loc) {
  PolyOp tot = impl->constant(0, loc);
  auto pbuf = std::static_pointer_cast<PolyBuffer>(buf);
  for (size_t i = 0; i < pbuf->size; i++) {
    PolyOp val = impl->get(pbuf->param, pbuf->offset + i, pbuf->back, loc);
    tot = impl->add(tot, impl->mul(impl->constant(i, loc), val, loc), loc);
  }
  return tot;
}

void PolyContext::setMux(BufPtr buf, ValPtr input, SourceLoc loc) {
  PolyOp muxVal = asPoly(getMux(buf, loc));
  return impl->assertZero(impl->sub(muxVal, asPoly(input), loc), loc);
}

Context::ValPtr PolyContext::add(ValPtr a, ValPtr b, SourceLoc loc) {
  return impl->add(asPoly(a), asPoly(b), loc);
}

Context::ValPtr PolyContext::sub(ValPtr a, ValPtr b, SourceLoc loc) {
  return impl->sub(asPoly(a), asPoly(b), loc);
}

Context::ValPtr PolyContext::mul(ValPtr a, ValPtr b, SourceLoc loc) {
  return impl->mul(asPoly(a), asPoly(b), loc);
}

Context::ValPtr PolyContext::bitAnd(ValPtr a, ValPtr b, SourceLoc loc) {
  throw std::runtime_error("Unimplemented");
}

Context::ValPtr PolyContext::inv(ValPtr a, SourceLoc loc) {
  throw std::runtime_error("Unimplemented");
}

Context::ValPtr PolyContext::nonzero(ValPtr a, SourceLoc loc) {
  throw std::runtime_error("Unimplemented");
}

void PolyContext::assertZero(ValPtr a, SourceLoc loc) {
  impl->assertZero(asPoly(a), loc);
}

void PolyContext::log(const char* str, std::vector<ValPtr> vals) {
  // NO-OP
}

std::array<Context::ValPtr, 4> PolyContext::divide32(
    ValPtr numerLow, ValPtr numerHigh, ValPtr denomLow, ValPtr denomHigh, SourceLoc loc) {
  throw std::runtime_error("Unimplemented");
}

void PolyContext::memWrite(ValPtr cycle, ValPtr addr, ValPtr low, ValPtr high, SourceLoc loc) {
  throw std::runtime_error("Unimplemented");
}

std::array<Context::ValPtr, 2> PolyContext::memRead(ValPtr cycle, ValPtr addr, SourceLoc loc) {
  throw std::runtime_error("Unimplemented");
}

std::array<Context::ValPtr, 5> PolyContext::memCheck(SourceLoc loc) {
  throw std::runtime_error("Unimplemented");
}

} // namespace risc0
