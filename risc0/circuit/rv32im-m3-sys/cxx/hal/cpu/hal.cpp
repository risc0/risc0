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
#include "zkp/poseidon2.h"
#include "zkp/ntt.h"
#include "zkp/params.h"
#include "zkp/poly.h"
#include "core/log.h"
#include "core/util.h"

#include <iostream>
#include <map>

using namespace risc0;

namespace risc0 {

void computeDataWitnessCpu(Fp* data, Fp* globals, const RowInfo* info, const uint32_t* aux, uint32_t* tables, size_t numRows);
void computeAccumWitnessCpu(Fp* accum, const Fp* data, const Fp* globals, const FpExt* accMix, size_t numRows);
void evalCheckCpu(Fp* check, const Fp* data, const Fp* accum, const Fp* globals, const FpExt* accMix, FpExt ecMix, size_t numRows);

}

namespace {

class CpuBuffer : public IBuffer {
  friend class CpuHal;
public:
  CpuBuffer(size_t size) : buffer(new char[size]), _size(size) {
    memset(buffer, 0, size);
  }
  ~CpuBuffer() override {
    delete[] reinterpret_cast<char*>(buffer);
  }
  size_t size() override {
    return _size;
  }
private:
  void* buffer;
  size_t _size;
};


class CpuHal : public IHal {
public:
  CpuHal() {}
  ~CpuHal() override {}

  void copy(IBufferPtr dst, size_t dstOffset, IBufferPtr src, size_t srcOffset, size_t count) override {
    memcpy(
        reinterpret_cast<uint8_t*>(static_cast<CpuBuffer*>(dst.get())->buffer) + dstOffset,
        reinterpret_cast<uint8_t*>(static_cast<CpuBuffer*>(src.get())->buffer) + srcOffset,
        count);
  }

  void zero(IBufferPtr buf, size_t offset, size_t size) override {
    memset(reinterpret_cast<uint8_t*>(static_cast<CpuBuffer*>(buf.get())->buffer) + offset, 0, size);
  }

  void hashRows(HalArray<Digest> out, HalMatrix<Fp> in) override {
    PinnedArrayWO<Digest> pOut(shared_from_this(), out);
    PinnedMatrixRO<Fp> pIn(shared_from_this(), in);
    if (in.rows() != out.size()) {
      throw std::runtime_error("Mismatched sizes in hashRows");
    }
    // TODO: Parallel
    for (size_t i = 0; i < out.size(); i++) {
      pOut[i] = poseidon2Hash(pIn.data() + i, in.cols(), in.rows());
    }
  }
  void hashFold(HalArray<Digest> out, HalArray<Digest> in) override {
    PinnedArrayWO<Digest> pOut(shared_from_this(), out);
    PinnedArrayRO<Digest> pIn(shared_from_this(), in);
    if (in.size() != 2*out.size()) {
      throw std::runtime_error("Mismatched sizes in hashRows");
    }
    // TODO: Parallel
    for (size_t i = 0; i < out.size(); i++) {
      pOut[i] = poseidon2HashPair(pIn[2*i], pIn[2*i + 1]);
    }
  }
  void query(HalArray<Fp> out, HalMatrix<Fp> data, HalArray<Digest> tree, size_t topSize, size_t idx) override {
    size_t steps = log2Ceil(data.rows()) - log2Ceil(topSize);
    size_t querySize = steps * p2impl::CELLS_DIGEST + data.cols();
    if (querySize != out.size() || tree.size() != 2 * data.rows() || idx >= data.rows()) {
      throw std::runtime_error("Inconsistent sizes in query");
    }
    PinnedArrayWO<Fp> pOut(shared_from_this(), out);
    PinnedMatrixRO<Fp> pData(shared_from_this(), data);
    PinnedArrayRO<Digest> pTree(shared_from_this(), tree);
    for (size_t i = 0; i < pOut.size(); i++) {
      if (i < pData.cols()) {
        pOut[i] = pData(idx, i);
      } else {
        size_t i2 = i - pData.cols();
        size_t up = i2 / 8;
        size_t elem = i2 % 8;
        size_t cidx = (idx + data.rows())  >> up;
        size_t other = (cidx % 2) ? cidx - 1 : cidx + 1;
        pOut[i] = Fp::fromRaw(pTree[other].words[elem]);
      }
    }
  }

  void batchBitReverse(HalMatrix<Fp> io) override {
    PinnedMatrixRW<Fp> pIo(shared_from_this(), io);
    multiBitReverse(pIo.data(), io.rows(), io.cols());
  }

  void batchExpandAndEvaluate(HalMatrix<Fp> out, HalMatrix<Fp> in) override {
    PinnedMatrixWO<Fp> pOut(shared_from_this(), out);
    PinnedMatrixRO<Fp> pIn(shared_from_this(), in);
    uint32_t inPo2 = log2Ceil(in.rows());
    uint32_t expPo2 = log2Ceil(out.rows() / in.rows());
    if (
      in.rows() != (size_t(1) << inPo2) ||
      (size_t(1) << expPo2) * in.rows() != out.rows() ||
      in.cols() != out.cols())
    {
      LOG(0, "in.rows() = " << in.rows() << ", in.cols = " << in.cols());
      LOG(0, "out.rows() = " << out.rows() << ", out.cols = " << out.cols());
      LOG(0, "inPo2 = " << inPo2 << ", expPo2 = " << expPo2);
      throw std::runtime_error("Mismatched sizes batchExpandNtt");
    }
    // Expand input into output
    memset((void*) pOut.data(), 0, sizeof(Fp) * out.rows() * out.cols());
    for (size_t r = 0; r < in.rows(); r++) {
      for (size_t c = 0; c < in.cols(); c++) {
        pOut(r * (1 << expPo2), c) = pIn(r, c);
      }
    }
    multiEvaluate(pOut.data(), out.rows(), out.cols());
  }

  void batchInterpolate(HalMatrix<Fp> io) override {
    uint32_t inPo2 = log2Ceil(io.rows());
    if (io.rows() != (size_t(1) << inPo2)) {
      throw std::runtime_error("invalid size in batchInterpolateNtt");
    }
    PinnedMatrixRW<Fp> pIo(shared_from_this(), io);
    multiInterpolate(pIo.data(), io.rows(), io.cols());
  }

  void batchShift(HalMatrix<Fp> io) override {
    PinnedMatrixRW<Fp> pIo(shared_from_this(), io);
    multiShift(pIo.data(), io.rows(), io.cols());
  }

  void batchPolyEval(HalArray<FpExt> out, HalMatrix<Fp> coeffs, HalArray<uint32_t> cols, HalArray<FpExt> xs) override {
    PinnedArrayWO<FpExt> pOut(shared_from_this(), out);
    PinnedMatrixRO<Fp> pCoeffs(shared_from_this(), coeffs);
    PinnedArrayRO<uint32_t> pCols(shared_from_this(), cols);
    PinnedArrayRO<FpExt> pXs(shared_from_this(), xs);
    if (out.size() != cols.size() || cols.size() != xs.size()) {
      throw std::runtime_error("Invalid batchPolyEval");
    }
    size_t size = out.size();
    for (size_t i = 0; i < size; i++) {
      uint32_t which = pCols[i];
      if (which >= coeffs.cols()) {
        throw std::runtime_error("Invalid column in batchPolyEval");
      }
      FpExt tot;
      FpExt x = pXs[i];
      FpExt mul = FpExt(Fp(1));
      for (size_t j = 0; j < coeffs.rows(); j++) {
        tot += mul * pCoeffs(j, which);
        mul *= x;
      }
      pOut[i] = tot;
    }
  }

  void combosMix(HalMatrix<FpExt> combos, HalMatrix<Fp> coeffs, HalArray<uint32_t> whichCombo, FpExt cur, FpExt mix) override {
    if (combos.rows() != coeffs.rows() || coeffs.cols() != whichCombo.size()) {
      throw std::runtime_error("Invalid combosMix");
    }
    PinnedMatrixRW<FpExt> pCombos(shared_from_this(), combos);
    PinnedMatrixRO<Fp> pCoeffs(shared_from_this(), coeffs);
    PinnedArrayRO<uint32_t> pWhichCombo(shared_from_this(), whichCombo);
    for (size_t i = 0; i < coeffs.cols(); i++) {
      size_t which = pWhichCombo[i];
      for (size_t j = 0; j < combos.rows(); j++) {
        pCombos(j, which) += cur * pCoeffs(j, i);
      }
      cur *= mix;
    }
  }

  void combosPrep(HalMatrix<FpExt> combos, HalArray<FpExt> eval, HalArray<EvalInfo> info, FpExt mix) override {
    if (eval.size() != info.size()) {
      throw std::runtime_error("Invalid combosMix");
    }
    PinnedMatrixRW<FpExt> pCombos(shared_from_this(), combos);
    PinnedArrayRO<FpExt> pEval(shared_from_this(), eval);
    PinnedArrayRO<EvalInfo> pInfo(shared_from_this(), info);
    FpExt cur(1);
    for (size_t i = 0; i < eval.size(); i++) {
      pCombos(pInfo[i].coeffIndex, pInfo[i].comboId) -= cur * pEval[i];
      if (i + 1 < eval.size() && (pInfo[i + 1].group != pInfo[i].group || pInfo[i + 1].column != pInfo[i].column)) {
        cur *= mix;
      }
    }
  }

  void combosDivide(HalMatrix<FpExt> combos, HalArray<DivideInfo> info) override {
    PinnedMatrixRW<FpExt> pCombos(shared_from_this(), combos);
    PinnedArrayRO<DivideInfo> pInfo(shared_from_this(), info);
    for (size_t i = 0; i < info.size(); i++) {
      FpExt rem = polyDivide(pCombos.data() + combos.rows() * pInfo[i].comboId, combos.rows(), pInfo[i].z);
      if (rem != FpExt(0)) {
        LOG(0, "invalid remainder: " << i << " " << rem);
        throw std::runtime_error("Invalid remainder");
      }
    }
  }

  void combosFinalize(HalMatrix<Fp> out, HalMatrix<FpExt> combos) override {
    if (out.rows() != combos.rows() || out.cols() != kExtSize) {
      throw std::runtime_error("Invalid combosFinalize");
    }
    PinnedMatrixRO<FpExt> pCombos(shared_from_this(), combos);
    PinnedMatrixWO<Fp> pOut(shared_from_this(), out);
    for (size_t i = 0; i < out.rows(); i++) {
      FpExt tot;
      for (size_t j = 0; j < combos.cols(); j++) {
        tot += pCombos(i, j);
      }
      for (size_t j = 0; j < kExtSize; j++) {
        pOut(i, j) = elem(tot, j);
      }
    }
  }

  void friFold(HalMatrix<Fp> out, HalMatrix<Fp> in, FpExt mix) override {
    PinnedMatrixWO<Fp> pOut(shared_from_this(), out);
    PinnedMatrixRO<Fp> pIn(shared_from_this(), in);
    if (out.rows() * kFriFold != in.rows() || out.cols() != kExtSize || in.cols() != kExtSize) {
      throw std::runtime_error("Invalid size in friFold");
    }
    size_t count = out.rows();
    for (size_t gid = 0; gid < count; gid++) {
      FpExt tot;
      FpExt curMix(1);
      for (uint32_t i = 0; i < kFriFold; i++) {
        size_t rev_i = bitReverse(i) >> (32 - log2Ceil(kFriFold));
        size_t rev_idx = rev_i * count + gid;
        FpExt factor(pIn(rev_idx, 0), pIn(rev_idx, 1), pIn(rev_idx, 2), pIn(rev_idx, 3));
        tot += curMix * factor;
        curMix *= mix;
      }
      for (size_t i = 0; i < kExtSize; i++) {
        pOut(gid, i) = tot.elems[i];
      }
    }
  }

  void computeDataWitness(HalMatrix<Fp> data, HalArray<Fp> globals, HalArray<RowInfo> rows, HalArray<uint32_t> aux, HalArray<uint32_t> tables) override {
    PinnedMatrixWO<Fp> pData(shared_from_this(), data);
    PinnedArrayRW<Fp> pGlobals(shared_from_this(), globals);
    PinnedArrayRO<RowInfo> pRows(shared_from_this(), rows);
    PinnedArrayRO<uint32_t> pAux(shared_from_this(), aux);
    PinnedArrayRW<uint32_t> pTables(shared_from_this(), tables);
    if (data.rows() != rows.size()) {
      throw std::runtime_error("Mismatched sizes in computeDataWitness");
    }
    computeDataWitnessCpu(pData.data(), pGlobals.data(), pRows.data(), pAux.data(), pTables.data(), rows.size());
  }

  void computeAccumWitness(HalMatrix<Fp> accum, HalMatrix<Fp> data, HalArray<Fp> globals, HalArray<FpExt> accMix) override {
    PinnedMatrixWO<Fp> pAccum(shared_from_this(), accum);
    PinnedMatrixRO<Fp> pData(shared_from_this(), data);
    PinnedArrayRO<Fp> pGlobals(shared_from_this(), globals);
    PinnedArrayRO<FpExt> pAccMix(shared_from_this(), accMix);
    if (accum.rows() != data.rows()) {
      throw std::runtime_error("Mismatched sizes in computeAccumWitness");
    }
    computeAccumWitnessCpu(pAccum.data(), pData.data(), pGlobals.data(), pAccMix.data(), accum.rows());
    LOG(0, "Doing prefix sum");
    FpExt tot;
    for (size_t i = 0; i < pAccum.rows(); i++) {
      tot += FpExt(pAccum(i, 0), pAccum(i, 1), pAccum(i, 2), pAccum(i, 3));
      pAccum(i, 0) = tot.elem(0);
      pAccum(i, 1) = tot.elem(1);
      pAccum(i, 2) = tot.elem(2);
      pAccum(i, 3) = tot.elem(3);
    }
    LOG(0, "Accum tot = " << tot);
  }

  void evalCheck(HalMatrix<Fp> check, HalMatrix<Fp> data, HalMatrix<Fp> accum, HalArray<Fp> globals, HalArray<FpExt> accMix, FpExt ecMix) override {
    PinnedMatrixWO<Fp> pCheck(shared_from_this(), check);
    PinnedMatrixRO<Fp> pData(shared_from_this(), data);
    PinnedMatrixRO<Fp> pAccum(shared_from_this(), accum);
    PinnedArrayRO<Fp> pGlobals(shared_from_this(), globals);
    PinnedArrayRO<FpExt> pAccMix(shared_from_this(), accMix);
    if (check.rows() != accum.rows() || accum.rows() != data.rows()) {
      throw std::runtime_error("Mismatched sizes in evalCheck");
    }
    evalCheckCpu(pCheck.data(), pData.data(), pAccum.data(), pGlobals.data(), pAccMix.data(), ecMix, check.rows());
  }

  void sync() override {
    // NOP
  }

private:
  IBufferPtr allocate(size_t size) override {
    return std::make_shared<CpuBuffer>(size);
  }

  void* pin(IBufferPtr buf, size_t offset, size_t size, bool sync) override {
    return reinterpret_cast<uint8_t*>(getBuffer(buf)) + offset;
  }
  void unpin(IBufferPtr buf, void* pinned, size_t offset, size_t size, bool modified) override {}

  void* getBuffer(IBufferPtr buf) {
    auto cpuBuf = dynamic_cast<CpuBuffer*>(buf.get());
    if (!cpuBuf) {
      throw std::runtime_error("null or invalid buffer type");
    }
    return cpuBuf->buffer;
  }
};

} // namespace

namespace risc0 {

IHalPtr getCpuHal() { return std::make_shared<CpuHal>(); }

}  // namespace risc0

