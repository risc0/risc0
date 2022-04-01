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

#include "risc0/zkvm/circuit/gen_context.h"

namespace risc0 {

namespace {

struct GenValue : public ValueImplBase {
  std::string name;
};

struct GenBuffer : public BufferImplBase {
  std::string param;
  bool isConst;
};

} // namespace

std::ostream& operator<<(std::ostream& out, Context::ValPtr val) {
  auto gval = std::static_pointer_cast<GenValue>(val);
  out << gval->name;
  return out;
}

GenContext::GenContext(const char* name) {
  outs << "void " << name << "(StepContext& ctx";
}

Context::BufPtr GenContext::addParam(const std::string& name, size_t size, bool isConst) {
  auto out = std::make_shared<GenBuffer>();
  out->size = size;
  out->param = name;
  out->isConst = isConst;
  outs << ", ";
  if (isConst) {
    outs << "const ";
  }
  outs << "Fp* " << name;
  return out;
}

void GenContext::paramsDone() {
  outs << ") {\n";
  verifyStack.emplace_back();
  indent++;
}

std::string GenContext::funcDone() {
  outs << verifyStack.back().str();
  verifyStack.clear();
  outs << "}\n";
  return outs.str();
}

Context::ValPtr GenContext::constant(Fp val, SourceLoc loc) {
  defl() << val << endl(loc);
  return newDef();
}

Context::ValPtr GenContext::getVal(BufPtr buf, size_t index, SourceLoc loc) {
  auto gbuf = std::static_pointer_cast<GenBuffer>(buf);
  defl() << "ctx.get(" << gbuf->param << ", " << gbuf->offset + index << ", " << gbuf->back << ")"
         << endl(loc);
  return newDef();
}

void GenContext::setVal(BufPtr buf, size_t index, ValPtr val, SourceLoc loc) {
  auto gbuf = std::static_pointer_cast<GenBuffer>(buf);
  if (gbuf->back) {
    throw std::runtime_error("Invalid set of element in prior time step");
  }
  begl() << "ctx.set(" << gbuf->param << ", " << gbuf->offset + index << ", " << val << ")"
         << endl(loc);
}

Context::ValPtr GenContext::getGlobal(size_t index, SourceLoc loc) {
  defl() << "ctx.globals[" << index << "]" << endl(loc);
  return newDef();
}

void GenContext::setGlobal(size_t index, ValPtr val, SourceLoc loc) {
  begl() << "ctx.globals[" << index << "] = " << val << endl(loc);
}

bool GenContext::beginNondet(SourceLoc loc) {
  return true;
}

void GenContext::endNondet() {
  // NO-OP
}

void GenContext::beginIf(ValPtr a, SourceLoc loc) {
  begl() << "if (" << a << " != 0) {\n";
  verifyStack.emplace_back();
  indent++;
}

void GenContext::endIf() {
  indent--;
  outs << verifyStack.back().str();
  verifyStack.pop_back();
  begl() << "}\n";
}

Context::BufPtr GenContext::slice(BufPtr buf, size_t offset, size_t size, SourceLoc loc) {
  auto gbuf = std::static_pointer_cast<GenBuffer>(buf);
  auto nbuf = std::make_shared<GenBuffer>(*gbuf);
  if (offset + size > gbuf->size) {
    throw std::runtime_error("Slice out of bounds");
  }
  nbuf->offset += offset;
  nbuf->size = size;
  return nbuf;
}

Context::BufPtr GenContext::back(BufPtr buf, size_t size, SourceLoc loc) {
  auto gbuf = std::static_pointer_cast<GenBuffer>(buf);
  auto nbuf = std::make_shared<GenBuffer>(*gbuf);
  nbuf->back += size;
  return nbuf;
}

Context::BufPtr GenContext::requireDigits(BufPtr buf, size_t bits, SourceLoc loc) {
  auto gbuf = std::static_pointer_cast<GenBuffer>(buf);
  auto nbuf = std::make_shared<GenBuffer>(*gbuf);
  nbuf->digits = bits;
  if (gbuf->back == 0) {
    vegl() << "ctx.requireDigits(" << gbuf->param << ", " << bits << ", " << gbuf->offset << ", "
           << gbuf->size << ")" << endl(loc);
  }
  return nbuf;
}

Context::BufPtr GenContext::requireMux(BufPtr buf, SourceLoc loc) {
  auto gbuf = std::static_pointer_cast<GenBuffer>(buf);
  auto nbuf = std::make_shared<GenBuffer>(*gbuf);
  nbuf->digits = 1;
  nbuf->isMux = true;
  if (gbuf->back == 0) {
    vegl() << "ctx.requireMux(" << gbuf->param << ", " << gbuf->offset << ", " << gbuf->size
           << ", \"" << this->loc(loc) << "\")" << endl(loc);
  }
  return nbuf;
}

Context::ValPtr GenContext::getDigits(BufPtr buf, size_t bits, SourceLoc loc) {
  auto gbuf = std::static_pointer_cast<GenBuffer>(buf);
  if (gbuf->digits != bits) {
    throw std::runtime_error("Get digits called on non-digits");
  }
  defl() << "ctx.getDigits(" << gbuf->param << ", " << bits << ", " << gbuf->offset << ", "
         << gbuf->back << ", " << gbuf->size << ")" << endl(loc);
  return newDef();
}

Context::ValPtr GenContext::setDigits(BufPtr buf, size_t bits, ValPtr input, SourceLoc loc) {
  auto gbuf = std::static_pointer_cast<GenBuffer>(buf);
  if (gbuf->digits != bits) {
    throw std::runtime_error("Set digits called on non-digits");
  }
  if (gbuf->back) {
    throw std::runtime_error("Invalid set of element in prior time step");
  }
  defl() << "ctx.setDigits(" << gbuf->param << ", " << bits << ", " << gbuf->offset << ", "
         << gbuf->size << ", " << input << ")" << endl(loc);
  return newDef();
}

Context::ValPtr GenContext::getMux(BufPtr buf, SourceLoc loc) {
  auto gbuf = std::static_pointer_cast<GenBuffer>(buf);
  if (!gbuf->isMux) {
    throw std::runtime_error("Get mux called on non-mux");
  }
  defl() << "ctx.getMux(" << gbuf->param << ", " << gbuf->offset << ", " << gbuf->back << ", "
         << gbuf->size << ")" << endl(loc);
  return newDef();
}

void GenContext::setMux(BufPtr buf, ValPtr input, SourceLoc loc) {
  auto gbuf = std::static_pointer_cast<GenBuffer>(buf);
  if (!gbuf->isMux) {
    throw std::runtime_error("Set mux called on non-mux");
  }
  if (gbuf->back) {
    throw std::runtime_error("Invalid set of element in prior time step");
  }
  begl() << "ctx.setMux(" << gbuf->param << ", " << gbuf->offset << ", " << gbuf->size << ", "
         << input << ")" << endl(loc);
}

Context::ValPtr GenContext::add(ValPtr a, ValPtr b, SourceLoc loc) {
  defl() << a << " + " << b << endl(loc);
  return newDef();
}

Context::ValPtr GenContext::sub(ValPtr a, ValPtr b, SourceLoc loc) {
  defl() << a << " - " << b << endl(loc);
  return newDef();
}

Context::ValPtr GenContext::mul(ValPtr a, ValPtr b, SourceLoc loc) {
  defl() << a << " * " << b << endl(loc);
  return newDef();
}

Context::ValPtr GenContext::bitAnd(ValPtr a, ValPtr b, SourceLoc loc) {
  defl() << a << ".asUInt32() & " << b << ".asUInt32()" << endl(loc);
  return newDef();
}

Context::ValPtr GenContext::inv(ValPtr a, SourceLoc loc) {
  defl() << "inv(" << a << ")" << endl(loc);
  return newDef();
}

Context::ValPtr GenContext::nonzero(ValPtr a, SourceLoc loc) {
  defl() << "(" << a << " != Fp(0))" << endl(loc);
  return newDef();
}

void GenContext::assertZero(ValPtr a, SourceLoc loc) {
  vegl() << "ctx.requireZero(" << a << ", \"" << this->loc(loc) << "\")" << endl(loc);
}

void GenContext::log(const char* str, std::vector<ValPtr> vals) {
  begl() << "DO_LOG(\"" << str << "\"";
  for (auto val : vals) {
    outs << ", " << val << ".asUInt32()";
  }
  outs << ");\n";
}

std::array<Context::ValPtr, 4> GenContext::divide32(
    ValPtr numerLow, ValPtr numerHigh, ValPtr denomLow, ValPtr denomHigh, SourceLoc loc) {
  ValPtr o1 = newDef();
  ValPtr o2 = newDef();
  ValPtr o3 = newDef();
  ValPtr o4 = newDef();
  begl() << "auto [" << o1 << ", " << o2 << ", " << o3 << ", " << o4 << "] = ";
  outs << "ctx.divide(" << numerLow << ", " << numerHigh << ", " << denomLow << ", " << denomHigh
       << ")" << endl(loc);
  return {o1, o2, o3, o4};
}

void GenContext::memWrite(ValPtr cycle, ValPtr addr, ValPtr low, ValPtr high, SourceLoc loc) {
  begl() << "ctx.memWrite(" << cycle << ", " << addr << ", " << low << ", " << high << ")"
         << endl(loc);
}

std::array<Context::ValPtr, 2> GenContext::memRead(ValPtr cycle, ValPtr addr, SourceLoc loc) {
  ValPtr o1 = newDef();
  ValPtr o2 = newDef();
  begl() << "auto [" << o1 << ", " << o2 << "] = ";
  outs << "ctx.memRead(" << cycle << ", " << addr << ")" << endl(loc);
  return {o1, o2};
}

std::array<Context::ValPtr, 5> GenContext::memCheck(SourceLoc loc) {
  ValPtr o1 = newDef();
  ValPtr o2 = newDef();
  ValPtr o3 = newDef();
  ValPtr o4 = newDef();
  ValPtr o5 = newDef();
  begl() << "auto [" << o1 << ", " << o2 << ", " << o3 << ", " << o4 << ", " << o5 << "] = ";
  outs << "ctx.memCheck()" << endl(loc);
  return {o1, o2, o3, o4, o5};
}

std::ostream& GenContext::begl() {
  for (size_t i = 0; i < indent; i++) {
    outs << "  ";
  }
  return outs;
}

std::ostream& GenContext::vegl() {
  for (size_t i = 0; i < indent; i++) {
    verifyStack.back() << "  ";
  }
  return verifyStack.back();
}

std::ostream& GenContext::defl() {
  begl() << "Fp val" << nextId << " = ";
  return outs;
}

std::string GenContext::loc(SourceLoc loc) {
  return std::string(loc.filename) + ":" + std::to_string(loc.line);
}

std::string GenContext::endl(SourceLoc loc) {
  return std::string("; // ") + this->loc(loc) + "\n";
}

Context::ValPtr GenContext::newDef() {
  auto ret = std::make_shared<GenValue>();
  ret->name = "val" + std::to_string(nextId++);
  return ret;
}

} // namespace risc0
