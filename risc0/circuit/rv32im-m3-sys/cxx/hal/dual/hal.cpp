// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include "hal/hal.h"
#include "core/log.h"
#include "core/util.h"

#include <iostream>
#include <map>

namespace risc0 {

#define REQUIRE(x)                                                                                 \
  do {                                                                                             \
    if (!(x)) {                                                                                    \
      LOG(0, "Assertion: " #x " failed in Dual Hal");                                              \
      throw std::runtime_error("Dual Hal failure");                                                \
    }                                                                                              \
  } while (0)

class DualBuffer : public IBuffer {
  friend class DualHal;

public:
  DualBuffer(IBufferPtr a, IBufferPtr b) : a(a), b(b) {}

  ~DualBuffer() override {}
  size_t size() override {
    REQUIRE(a->size() == b->size());
    return a->size();
  }

private:
  IBufferPtr a;
  IBufferPtr b;
};

class DualHal : public IHal {
  IBufferPtr getA(IBufferPtr dual) { return static_cast<DualBuffer*>(dual.get())->a; }
  template <typename T> HalArray<T> getA(HalArray<T> dual) {
    HalArray<T> out = dual;
    out.inner = getA(out.inner);
    return out;
  }
  template <typename T> HalMatrix<T> getA(HalMatrix<T> dual) {
    HalMatrix<T> out = dual;
    out.inner = getA(out.inner);
    return out;
  }

  IBufferPtr getB(IBufferPtr dual) { return static_cast<DualBuffer*>(dual.get())->b; }
  template <typename T> HalArray<T> getB(HalArray<T> dual) {
    HalArray<T> out = dual;
    out.inner = getB(out.inner);
    return out;
  }
  template <typename T> HalMatrix<T> getB(HalMatrix<T> dual) {
    HalMatrix<T> out = dual;
    out.inner = getB(out.inner);
    return out;
  }

  void verify(IBufferPtr buf) {
    uint8_t* aPin = reinterpret_cast<uint8_t*>(a->pin(getA(buf), 0, buf->size(), true));
    uint8_t* bPin = reinterpret_cast<uint8_t*>(b->pin(getB(buf), 0, buf->size(), true));
    for (size_t i = 0; i < buf->size(); i++) {
      if (aPin[i] != bPin[i]) {
        LOG(0,
            "DualHal buffer verify mismatch at byte " << i << ", " << aPin[i] << " vs " << bPin[i]);
        throw std::runtime_error("DualHal mismatch");
      }
    }
    a->unpin(getA(buf), aPin, 0, buf->size(), false);
    b->unpin(getB(buf), bPin, 0, buf->size(), false);
  }
  template <typename T> void verify(HalArray<T> buf) {
    PinnedArrayRO<T> aBuf(a, getA(buf));
    PinnedArrayRO<T> bBuf(b, getB(buf));
    for (size_t i = 0; i < buf.size(); i++) {
      if (aBuf[i] != bBuf[i]) {
        LOG(0, "DualHal array verify mismatch at " << i << ", " << aBuf[i] << " vs " << bBuf[i]);
        throw std::runtime_error("DualHal mismatch");
      }
    }
  }
  template <typename T> void verify(HalMatrix<T> buf) {
    PinnedMatrixRO<T> aBuf(a, getA(buf));
    PinnedMatrixRO<T> bBuf(b, getB(buf));
    for (size_t i = 0; i < buf.size(); i++) {
      size_t row = i % buf.rows();
      size_t col = i / buf.rows();
      if (aBuf[i] != bBuf[i]) {
        LOG(0,
            "DualHal matrix verify mismatch at row " << row << "col " << col << ", " << aBuf[i]
                                                     << " vs " << bBuf[i]);
        throw std::runtime_error("DualHal mismatch");
      }
    }
  }

  IHalPtr a;
  IHalPtr b;

public:
  DualHal(IHalPtr a, IHalPtr b) : a(a), b(b) {}
  ~DualHal() override {}

  void
  copy(IBufferPtr dst, size_t dstOffset, IBufferPtr src, size_t srcOffset, size_t count) override {
    a->copy(getA(dst), dstOffset, getA(src), srcOffset, count);
    b->copy(getB(dst), dstOffset, getB(src), srcOffset, count);
    verify(dst);
  }

  void zero(IBufferPtr buf, size_t offset, size_t size) override {
    a->zero(getA(buf), offset, size);
    b->zero(getB(buf), offset, size);
    verify(buf);
  }

  void hashRows(HalArray<Digest> out, HalMatrix<Fp> in) override {
    a->hashRows(getA(out), getA(in));
    b->hashRows(getB(out), getB(in));
    verify(out);
  }

  void hashFold(HalArray<Digest> out, HalArray<Digest> in) override {
    a->hashFold(getA(out), getA(in));
    b->hashFold(getB(out), getB(in));
    verify(out);
  }

  void query(HalArray<Fp> out,
             HalMatrix<Fp> data,
             HalArray<Digest> tree,
             size_t topSize,
             size_t idx) override {
    a->query(getA(out), getA(data), getA(tree), topSize, idx);
    b->query(getB(out), getB(data), getB(tree), topSize, idx);
    verify(out);
  }

  void batchBitReverse(HalMatrix<Fp> io) override {
    a->batchBitReverse(getA(io));
    b->batchBitReverse(getB(io));
    verify(io);
  }

  void batchExpandAndEvaluate(HalMatrix<Fp> out, HalMatrix<Fp> in) override {
    a->batchExpandAndEvaluate(getA(out), getA(in));
    b->batchExpandAndEvaluate(getB(out), getB(in));
    verify(out);
  }

  void batchInterpolate(HalMatrix<Fp> io) override {
    a->batchInterpolate(getA(io));
    b->batchInterpolate(getB(io));
    verify(io);
  }

  void batchShift(HalMatrix<Fp> io) override {
    a->batchShift(getA(io));
    b->batchShift(getB(io));
    verify(io);
  }

  void batchPolyEval(HalArray<FpExt> out,
                     HalMatrix<Fp> coeffs,
                     HalArray<uint32_t> cols,
                     HalArray<FpExt> xs) override {
    a->batchPolyEval(getA(out), getA(coeffs), getA(cols), getA(xs));
    b->batchPolyEval(getB(out), getB(coeffs), getB(cols), getB(xs));
    verify(out);
  }

  void combosMix(HalMatrix<FpExt> combos,
                 HalMatrix<Fp> coeffs,
                 HalArray<uint32_t> whichCombo,
                 FpExt cur,
                 FpExt mix) override {
    a->combosMix(getA(combos), getA(coeffs), getA(whichCombo), cur, mix);
    b->combosMix(getB(combos), getB(coeffs), getB(whichCombo), cur, mix);
    verify(combos);
  }

  void combosPrep(HalMatrix<FpExt> combos,
                  HalArray<FpExt> eval,
                  HalArray<EvalInfo> info,
                  FpExt mix) override {
    a->combosPrep(getA(combos), getA(eval), getA(info), mix);
    b->combosPrep(getB(combos), getB(eval), getB(info), mix);
    verify(combos);
  }

  void combosDivide(HalMatrix<FpExt> combos, HalArray<DivideInfo> info) override {
    a->combosDivide(getA(combos), getA(info));
    b->combosDivide(getB(combos), getB(info));
    verify(combos);
  }

  void combosFinalize(HalMatrix<Fp> out, HalMatrix<FpExt> combos) override {
    a->combosFinalize(getA(out), getA(combos));
    b->combosFinalize(getB(out), getB(combos));
    verify(out);
  }

  void friFold(HalMatrix<Fp> out, HalMatrix<Fp> in, FpExt mix) override {
    a->friFold(getA(out), getA(in), mix);
    b->friFold(getB(out), getB(in), mix);
    verify(out);
  }

  void computeDataWitness(HalMatrix<Fp> data,
                          HalArray<Fp> globals,
                          HalArray<RowInfo> rows,
                          HalArray<uint32_t> aux,
                          HalArray<uint32_t> tables) override {
    a->computeDataWitness(getA(data), getA(globals), getA(rows), getA(aux), getA(tables));
    b->computeDataWitness(getB(data), getB(globals), getB(rows), getB(aux), getB(tables));
    verify(data);
    verify(globals);
    verify(tables);
  }

  void computeAccumWitness(HalMatrix<Fp> accum,
                           HalMatrix<Fp> data,
                           HalArray<Fp> globals,
                           HalArray<FpExt> accMix) override {
    a->computeAccumWitness(getA(accum), getA(data), getA(globals), getA(accMix));
    b->computeAccumWitness(getB(accum), getB(data), getB(globals), getB(accMix));
    verify(accum);
  }

  void evalCheck(HalMatrix<Fp> check,
                 HalMatrix<Fp> data,
                 HalMatrix<Fp> accum,
                 HalArray<Fp> globals,
                 HalArray<FpExt> accMix,
                 FpExt ecMix) override {
    a->evalCheck(getA(check), getA(data), getA(accum), getA(globals), getA(accMix), ecMix);
    b->evalCheck(getB(check), getB(data), getB(accum), getB(globals), getB(accMix), ecMix);
    verify(check);
  }

  void sync() override {
    a->sync();
    b->sync();
  }

private:
  IBufferPtr allocate(size_t size) override {
    return std::make_shared<DualBuffer>(a->allocate(size), b->allocate(size));
  }

  void* pin(IBufferPtr buf, size_t offset, size_t size, bool sync) override {
    void* aPin = a->pin(getA(buf), offset, size, sync);
    if (sync) {
      void* bPin = b->pin(getB(buf), offset, size, sync);
      if (memcmp(aPin, bPin, size) != 0) {
        LOG(0, "Mismatch on synced pin: offset = " << offset << ", size = " << size);
        throw std::runtime_error("Mismatched pin in DualHal");
      }
      b->unpin(getB(buf), bPin, offset, size, false);
    }
    return aPin;
  }

  void unpin(IBufferPtr buf, void* pinned, size_t offset, size_t size, bool modified) override {
    if (modified) {
      void* bPin = b->pin(getB(buf), offset, size, false);
      memcpy(bPin, pinned, size);
      b->unpin(getB(buf), bPin, offset, size, true);
    }
    a->unpin(getA(buf), pinned, offset, size, modified);
  }
};

IHalPtr getDualHal(IHalPtr a, IHalPtr b) {
  return std::make_shared<DualHal>(a, b);
}

} // namespace risc0
