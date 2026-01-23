// Copyright 2026 RISC Zero, Inc.
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
#include "hal/po2s.h"

#include <iostream>
#include <map>

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Metal/Metal.hpp>

#include "core/log.h"
#include "core/util.h"
#include "zkp/params.h"
#include "zkp/poly.h"
#include "zkp/poseidon2_consts.h"
#include "zkp/rou.h"

#include METAL_KERNEL_H

using namespace risc0;

class MetalHal;

class MetalBuffer : public IBuffer {
  friend class MetalHal;

public:
  MetalBuffer(MTL::Buffer* buffer) : buffer(buffer) {}
  ~MetalBuffer() override { buffer->release(); }
  size_t size() override { return buffer->length(); }
  void copyFromCpu(size_t offset, const void* data, size_t size) override {
    memcpy(reinterpret_cast<uint8_t*>(buffer->contents()) + offset, data, size);
  }

private:
  MTL::Buffer* buffer;
};

using MetalBufferPtr = std::shared_ptr<MetalBuffer>;

size_t getPo2(size_t in) {
  size_t po2 = log2Ceil(in);
  if (po2 < MIN_PO2 || po2 > MAX_PO2) {
    LOG(0, "PO2 = " << po2);
    throw std::runtime_error("Invalid po2");
  }
  if (in != (size_t(1) << po2)) {
    throw std::runtime_error("input is not a power of 2");
  }
  return po2;
}

class MetalHal : public IHal {
public:
  MetalHal() : device(nullptr) {
    // Get all metal devices and pick the first
    NS::Array* all = MTLCopyAllDevices();
    if (all->count() == 0) {
      throw std::runtime_error("No devices");
    }
    device = all->object<MTL::Device>(0);
    device->retain();
    all->release();
    LOG(1, "Opening metal device: " << device->name()->utf8String());

    // Create the command queue
    commandQueue = device->newCommandQueue();
    if (!commandQueue) {
      throw std::runtime_error("Unable to make command queue");
    }

    // Load the library and get the functions
    NS::Error* error;

    auto data = dispatch_data_create(
      metal_kernel, metal_kernel_len, dispatch_get_main_queue(), DISPATCH_DATA_DESTRUCTOR_DEFAULT);
    MTL::Library* library = device->newLibrary(data, &error);
    dispatch_release(data);

    if (!library) {
      LOG(0, "Unable to load library: " << error->localizedDescription()->utf8String());
      throw std::runtime_error("Unable to load library");
    }

    auto allNames = library->functionNames();
    for (size_t i = 0; i < allNames->count(); i++) {
      NS::String* name = allNames->object<NS::String>(i);
      std::string cppName = name->utf8String();
      MTL::Function* func = library->newFunction(name);
      MTL::ComputePipelineState* pls = device->newComputePipelineState(func, &error);
      func->release();
      if (!pls) {
        LOG(0,
            "Unable to load kernel `" << cppName
                                      << "`: " << error->localizedDescription()->utf8String());
        throw std::runtime_error("Unable to load kernel");
      }
      kernels[cppName] = pls;
    }
    library->release();

    // Prepare some constants
    roundConstants = copyData(risc0::p2impl::ROUND_CONSTANTS, sizeof(Fp) * 696);
    mIntDiag = copyData(risc0::p2impl::M_INT_DIAG_HZN, sizeof(Fp) * 24);

    // Prepare ROU constants
    rouFwd = copyData(ROU_FWD.data(), sizeof(Fp) * (MAX_ROU_PO2 + 1));
    rouRev = copyData(ROU_REV.data(), sizeof(Fp) * (MAX_ROU_PO2 + 1));

    // Prepare inverse constants
    std::vector<Fp> invTableBuild;
    for (size_t i = 0; i < MAX_ROU_PO2 + 1; i++) {
      invTableBuild.push_back(inv(Fp(uint32_t(1) << i)));
    }
    invTable = copyData(invTableBuild.data(), sizeof(Fp) * (MAX_ROU_PO2 + 1));
  }

  ~MetalHal() override {
    if (commandBuffer) {
      commandBuffer->release();
    }
    for (auto& [_, value] : kernels) {
      value->release();
    }
    if (commandQueue) {
      commandQueue->release();
    }
    if (device) {
      device->release();
    }
  }

  void
  copy(IBufferPtr dst, size_t dstOffset, IBufferPtr src, size_t srcOffset, size_t count) override {
    prepBuffer();
    auto* blitEncoder = commandBuffer->blitCommandEncoder();
    blitEncoder->copyFromBuffer(getBuffer(src), srcOffset, getBuffer(dst), dstOffset, count);
    blitEncoder->endEncoding();
  }

  void zero(IBufferPtr buf, size_t offset, size_t size) override {
    prepBuffer();
    auto* blitEncoder = commandBuffer->blitCommandEncoder();
    blitEncoder->fillBuffer(getBuffer(buf), NS::Range(offset, size), 0);
    blitEncoder->endEncoding();
  }

  void hashRows(HalArray<Digest> out, HalMatrix<Fp> in) override {
    if (in.rows() != out.size()) {
      throw std::runtime_error("Mismatched sizes in hashRows");
    }
    size_t groupSize;
    auto encoder = getEncoder("poseidon2_rows", groupSize);
    setBufArg(encoder, 0, roundConstants);
    setBufArg(encoder, 1, mIntDiag);
    setBufArg(encoder, 2, extract(out), getOffset(out));
    setBufArg(encoder, 3, extract(in));
    setIntArg(encoder, 4, in.rows());
    setIntArg(encoder, 5, in.cols());
    dispatchEasy(encoder, in.rows(), groupSize);
  }

  void hashFold(HalArray<Digest> out, HalArray<Digest> in) override {
    if (in.size() != 2 * out.size()) {
      throw std::runtime_error("Mismatched sizes in hashFold");
    }
    size_t groupSize;
    auto encoder = getEncoder("poseidon2_fold", groupSize);
    setBufArg(encoder, 0, roundConstants);
    setBufArg(encoder, 1, mIntDiag);
    setBufArg(encoder, 2, extract(out), getOffset(out));
    setBufArg(encoder, 3, extract(in), getOffset(in));
    setIntArg(encoder, 4, out.size());
    dispatchEasy(encoder, out.size(), groupSize);
  }

  void query(HalArray<Fp> out,
             HalMatrix<Fp> data,
             HalArray<Digest> tree,
             size_t topSize,
             size_t idx) override {
    size_t steps = log2Ceil(data.rows()) - log2Ceil(topSize);
    size_t querySize = steps * p2impl::CELLS_DIGEST + data.cols();
    if (querySize != out.size() || tree.size() != 2 * data.rows() || idx >= data.rows()) {
      throw std::runtime_error("Inconsistent sizes in query");
    }
    size_t groupSize;
    auto encoder = getEncoder("query", groupSize);
    setBufArg(encoder, 0, extract(out), getOffset(out));
    setBufArg(encoder, 1, extract(data));
    setBufArg(encoder, 2, extract(tree), getOffset(tree));
    setIntArg(encoder, 3, data.rows());
    setIntArg(encoder, 4, data.cols());
    setIntArg(encoder, 5, idx);
    dispatchEasy(encoder, out.size(), groupSize);
  }

  void batchBitReverse(HalMatrix<Fp> io) override {
    uint32_t bits = log2Ceil(io.rows());
    if ((1 << bits) != io.rows()) {
      throw std::runtime_error("Invalid # of rows in batchBitReverse");
    }
    size_t groupSize;
    auto encoder = getEncoder("multi_bit_reverse", groupSize);
    setBufArg(encoder, 0, extract(io));
    setIntArg(encoder, 1, bits);
    dispatchEasy(encoder, io.rows() * io.cols(), groupSize);
  }

  void batchExpandAndEvaluate(HalMatrix<Fp> out, HalMatrix<Fp> in) override {
    uint32_t inPo2 = log2Ceil(in.rows());
    uint32_t expPo2 = log2Ceil(out.rows() / in.rows());
    if (in.rows() != (size_t(1) << inPo2) || (size_t(1) << expPo2) * in.rows() != out.rows() ||
        in.cols() != out.cols()) {
      throw std::runtime_error("Mismatched sizes batchExpandNtt");
    }
    size_t groupSize;
    auto encoder = getEncoder("batch_expand", groupSize);
    setBufArg(encoder, 0, extract(out));
    setBufArg(encoder, 1, extract(in));
    setIntArg(encoder, 2, out.cols());
    setIntArg(encoder, 3, out.rows());
    setIntArg(encoder, 4, in.rows());
    setIntArg(encoder, 5, expPo2);
    dispatchEasy(encoder, out.rows(), groupSize);
    size_t nBits = inPo2 + expPo2;
    for (size_t sBits = 1 + expPo2; sBits <= nBits; sBits++) {
      auto encoder = getEncoder("multi_ntt_fwd_step", groupSize);
      setBufArg(encoder, 0, extract(out));
      setBufArg(encoder, 1, rouFwd);
      setIntArg(encoder, 2, nBits);
      setIntArg(encoder, 3, sBits);
      setIntArg(encoder, 4, out.cols());
      dispatchNTT(encoder, nBits, sBits, out.cols());
    }
  }

  void batchInterpolate(HalMatrix<Fp> io) override {
    uint32_t nBits = log2Ceil(io.rows());
    if (io.rows() != (size_t(1) << nBits)) {
      throw std::runtime_error("invalid size in batchInterpolateNtt");
    }
    size_t groupSize;
    for (size_t sBits = nBits; sBits > 0; sBits--) {
      auto encoder = getEncoder("multi_ntt_rev_step", groupSize);
      setBufArg(encoder, 0, extract(io));
      setBufArg(encoder, 1, rouRev);
      setIntArg(encoder, 2, nBits);
      setIntArg(encoder, 3, sBits);
      setIntArg(encoder, 4, io.cols());
      dispatchNTT(encoder, nBits, sBits, io.cols());
    }
    auto encoder = getEncoder("eltwise_mul_factor_fp", groupSize);
    setBufArg(encoder, 0, extract(io));
    setBufArg(encoder, 1, invTable, nBits * sizeof(Fp));
    dispatchEasy(encoder, io.size(), groupSize);
  }

  void batchShift(HalMatrix<Fp> io) override {
    uint32_t bits = log2Ceil(io.rows());
    if ((1 << bits) != io.rows()) {
      throw std::runtime_error("Invalid # of rows in batchShift");
    }
    size_t groupSize;
    auto encoder = getEncoder("zk_shift", groupSize);
    setBufArg(encoder, 0, extract(io));
    setIntArg(encoder, 1, bits);
    dispatchEasy(encoder, io.rows() * io.cols(), groupSize);
  }

  void batchPolyEval(HalArray<FpExt> out,
                     HalMatrix<Fp> coeffs,
                     HalArray<uint32_t> cols,
                     HalArray<FpExt> xs) override {
    if (out.size() != cols.size() || cols.size() != xs.size()) {
      throw std::runtime_error("Invalid batchPolyEval");
    }
    size_t groupSize;
    auto encoder = getEncoder("multi_poly_eval", groupSize);
    setBufArg(encoder, 0, extract(out), getOffset(out));
    setBufArg(encoder, 1, extract(coeffs));
    setBufArg(encoder, 2, extract(cols), getOffset(cols));
    setBufArg(encoder, 3, extract(xs), getOffset(xs));
    setIntArg(encoder, 4, coeffs.rows());
    dispatchEasy(encoder, out.size() * groupSize, groupSize);
  }

  void combosMix(HalMatrix<FpExt> combos,
                 HalMatrix<Fp> coeffs,
                 HalArray<uint32_t> whichCombo,
                 FpExt cur,
                 FpExt mix) override {
    if (combos.rows() != coeffs.rows() || coeffs.cols() != whichCombo.size()) {
      throw std::runtime_error("Invalid combosMix");
    }
    size_t groupSize;
    auto encoder = getEncoder("mix_poly_coeffs", groupSize);
    setBufArg(encoder, 0, extract(combos));
    setBufArg(encoder, 1, extract(coeffs));
    setBufArg(encoder, 2, extract(whichCombo));
    setFpExtArg(encoder, 3, cur);
    setFpExtArg(encoder, 4, mix);
    setIntArg(encoder, 5, coeffs.cols());
    setIntArg(encoder, 6, coeffs.rows());
    dispatchEasy(encoder, coeffs.rows(), groupSize);
  }

  void combosPrep(HalMatrix<FpExt> combos,
                  HalArray<FpExt> eval,
                  HalArray<EvalInfo> info,
                  FpExt mix) override {
    // TODO: Maybe do this on the GPU?  Not really that relevant though since we current do poly
    // division on CPU also
    if (eval.size() != info.size()) {
      throw std::runtime_error("Invalid combosMix");
    }
    PinnedMatrixRW<FpExt> pCombos(shared_from_this(), combos);
    PinnedArrayRO<FpExt> pEval(shared_from_this(), eval);
    PinnedArrayRO<EvalInfo> pInfo(shared_from_this(), info);
    FpExt cur(1);
    for (size_t i = 0; i < eval.size(); i++) {
      pCombos(pInfo[i].coeffIndex, pInfo[i].comboId) -= cur * pEval[i];
      if (i + 1 < eval.size() &&
          (pInfo[i + 1].group != pInfo[i].group || pInfo[i + 1].column != pInfo[i].column)) {
        cur *= mix;
      }
    }
  }

  void combosDivide(HalMatrix<FpExt> combos, HalArray<DivideInfo> info) override {
    PinnedMatrixRW<FpExt> pCombos(shared_from_this(), combos);
    PinnedArrayRO<DivideInfo> pInfo(shared_from_this(), info);
    for (size_t i = 0; i < info.size(); i++) {
      FpExt rem =
          polyDivide(pCombos.data() + combos.rows() * pInfo[i].comboId, combos.rows(), pInfo[i].z);
      if (rem != FpExt(0)) {
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
    size_t groupSize;
    if (out.rows() * kFriFold != in.rows() || out.cols() != kExtSize || in.cols() != kExtSize) {
      throw std::runtime_error("Invalid size in friFold");
    }
    auto encoder = getEncoder("fri_fold", groupSize);
    setBufArg(encoder, 0, extract(out));
    setBufArg(encoder, 1, extract(in));
    setFpExtArg(encoder, 2, mix);
    setIntArg(encoder, 3, out.rows());
    dispatchEasy(encoder, out.rows(), groupSize);
  }

  void computeDataWitness(HalMatrix<Fp> data,
                          HalArray<Fp> globals,
                          HalArray<RowInfo> rows,
                          HalArray<uint32_t> aux,
                          HalArray<uint32_t> tables) override {
    if (data.rows() != rows.size()) {
      throw std::runtime_error("Mismatched sizes in computeDataWitness");
    }
    size_t po2 = getPo2(rows.size());
    size_t groupSize;
    auto encoder = getEncoder("data_witgen_metal_" + std::to_string(po2) + "_set", groupSize);
    setBufArg(encoder, 0, extract(data));
    setBufArg(encoder, 1, extract(globals), getOffset(globals));
    setBufArg(encoder, 2, extract(rows), getOffset(rows));
    setBufArg(encoder, 3, extract(aux), getOffset(aux));
    setBufArg(encoder, 4, extract(tables), getOffset(tables));
    setFpArg(encoder, 5, ROU_FWD[po2]);
    dispatchEasy(encoder, rows.size(), groupSize);
    encoder = getEncoder("data_witgen_metal_" + std::to_string(po2) + "_finalize", groupSize);
    setBufArg(encoder, 0, extract(data));
    setBufArg(encoder, 1, extract(globals), getOffset(globals));
    setBufArg(encoder, 2, extract(rows), getOffset(rows));
    setBufArg(encoder, 3, extract(aux), getOffset(aux));
    setBufArg(encoder, 4, extract(tables), getOffset(tables));
    setFpArg(encoder, 5, ROU_FWD[po2]);
    dispatchEasy(encoder, rows.size(), groupSize);
  }

  void computeAccumWitness(HalMatrix<Fp> accum,
                           HalMatrix<Fp> data,
                           HalArray<Fp> globals,
                           HalArray<FpExt> accMix) override {
    if (accum.rows() != data.rows()) {
      throw std::runtime_error("Mismatched sizes in computeDataWitness");
    }
    size_t po2 = getPo2(accum.rows());
    size_t groupSize;
    auto encoder = getEncoder("accum_witgen_metal_" + std::to_string(po2) + "_phase1", groupSize);
    setBufArg(encoder, 0, extract(accum));
    setBufArg(encoder, 1, extract(data));
    setBufArg(encoder, 2, extract(globals), getOffset(globals));
    setBufArg(encoder, 3, extract(accMix), getOffset(accMix));
    dispatchEasy(encoder, accum.rows(), groupSize);
    encoder = getEncoder("accum_witgen_metal_" + std::to_string(po2) + "_phase2", groupSize);
    setBufArg(encoder, 0, extract(accum));
    setBufArg(encoder, 1, extract(data));
    setBufArg(encoder, 2, extract(globals), getOffset(globals));
    setBufArg(encoder, 3, extract(accMix), getOffset(accMix));
    dispatchEasy(encoder, accum.rows(), groupSize);
    PinnedMatrixRW<Fp> pAccum(shared_from_this(), accum);
    FpExt tot;
    for (size_t i = 0; i < pAccum.rows(); i++) {
      tot += FpExt(pAccum(i, 0), pAccum(i, 1), pAccum(i, 2), pAccum(i, 3));
      pAccum(i, 0) = tot.elem(0);
      pAccum(i, 1) = tot.elem(1);
      pAccum(i, 2) = tot.elem(2);
      pAccum(i, 3) = tot.elem(3);
    }
    LOG(1, "Accum tot = " << tot);
  }

  void evalCheck(HalMatrix<Fp> check,
                 HalMatrix<Fp> data,
                 HalMatrix<Fp> accum,
                 HalArray<Fp> globals,
                 HalArray<FpExt> accMix,
                 FpExt ecMix) override {
    if (check.rows() != accum.rows() || accum.rows() != data.rows()) {
      throw std::runtime_error("Mismatched sizes in evalCheck");
    }
    // -2 to undo to expansion factor
    size_t po2 = getPo2(check.rows()) - 2;
    size_t groupSize;
    auto encoder = getEncoder("eval_check_metal_" + std::to_string(po2), groupSize);
    setBufArg(encoder, 0, extract(check));
    setBufArg(encoder, 1, extract(data));
    setBufArg(encoder, 2, extract(accum));
    setBufArg(encoder, 3, extract(globals), getOffset(globals));
    setBufArg(encoder, 4, extract(accMix), getOffset(accMix));
    setFpExtArg(encoder, 5, ecMix);
    setFpArg(encoder, 6, ROU_FWD[po2 + 2]);
    dispatchEasy(encoder, check.rows(), groupSize);
  }

  void sync() override {
    if (!commandBuffer) {
      return;
    }
    commandBuffer->commit();
    commandBuffer->waitUntilCompleted();
    auto status = commandBuffer->status();
    if (status != MTL::CommandBufferStatusCompleted) {
      LOG(0, "Invalid status after sync: ");
      NS::Error* error = commandBuffer->error();
      if (error) {
        std::cerr << "Error: " << error->localizedDescription()->utf8String() << "\n";
      }
      throw std::runtime_error("Failed during sync");
    }
    commandBuffer->release();
    commandBuffer = nullptr;
  }

private:
  MTL::Device* device = nullptr;
  MTL::CommandQueue* commandQueue = nullptr;
  MTL::CommandBuffer* commandBuffer = nullptr;
  std::map<std::string, MTL::ComputePipelineState*> kernels;
  IBufferPtr roundConstants;
  IBufferPtr mIntDiag;
  IBufferPtr rouFwd;
  IBufferPtr rouRev;
  IBufferPtr invTable;

  IBufferPtr allocate(size_t size) override {
    MTL::Buffer* buffer = device->newBuffer(size, MTL::ResourceStorageModeShared);
    if (buffer == nullptr) {
      throw std::runtime_error("Unable to allocate buffer");
    }
    memset(buffer->contents(), 0, size);
    return std::make_shared<MetalBuffer>(buffer);
  }

  IBufferPtr copyData(const void* data, size_t size) {
    MTL::Buffer* buffer = device->newBuffer(size, MTL::ResourceStorageModeShared);
    if (buffer == nullptr) {
      throw std::runtime_error("Unable to allocate buffer");
    }
    memcpy(buffer->contents(), data, size);
    return std::make_shared<MetalBuffer>(buffer);
  }

  void* pin(IBufferPtr buf, size_t offset, size_t size, bool _sync) override {
    sync();
    return reinterpret_cast<uint8_t*>(getBuffer(buf)->contents()) + offset;
  }

  void unpin(IBufferPtr buf, void* pinned, size_t offset, size_t size, bool modified) override {}

  MTL::Buffer* getBuffer(IBufferPtr buf) {
    auto metalBuf = dynamic_cast<MetalBuffer*>(buf.get());
    if (!metalBuf) {
      throw std::runtime_error("null or invalid buffer type");
    }
    return metalBuf->buffer;
  }

  void prepBuffer() {
    if (!commandBuffer) {
      commandBuffer = commandQueue->commandBuffer();
      commandBuffer->retain();
    } else {
      return;
    }
    if (!commandBuffer) {
      throw std::runtime_error("Unable to get command buffer");
    }
  }

  MTL::ComputeCommandEncoder* getEncoder(const std::string& name, size_t& groupSize) {
    auto it = kernels.find(name);
    if (it == kernels.end()) {
      LOG(0, "Invalid kernel name in call to `" << name);
      throw std::runtime_error("Invalid kernel name");
    }
    groupSize = it->second->maxTotalThreadsPerThreadgroup();
    prepBuffer();
    auto* encode = commandBuffer->computeCommandEncoder();
    encode->retain();
    encode->setComputePipelineState(it->second);
    return encode;
  }

  void
  setBufArg(MTL::ComputeCommandEncoder* encode, size_t arg, IBufferPtr buf, size_t offset = 0) {
    encode->setBuffer(getBuffer(buf), offset, arg);
  }

  void setIntArg(MTL::ComputeCommandEncoder* encode, size_t arg, uint64_t data) {
    uint32_t ret = uint32_t(data);
    encode->setBytes(&ret, sizeof(uint32_t), arg);
  }

  void setFpArg(MTL::ComputeCommandEncoder* encode, size_t arg, Fp data) {
    encode->setBytes(&data, sizeof(Fp), arg);
  }

  void setFpExtArg(MTL::ComputeCommandEncoder* encode, size_t arg, FpExt data) {
    encode->setBytes(&data, sizeof(FpExt), arg);
  }

  void dispatchEasy(MTL::ComputeCommandEncoder* encode, size_t count, size_t groupSize) {
    if (groupSize > count) {
      groupSize = count;
    }
    encode->dispatchThreads(MTL::Size(count, 1, 1), MTL::Size(groupSize, 1, 1));
    encode->endEncoding();
    encode->release();
  }

  void dispatchNTT(MTL::ComputeCommandEncoder* encode, size_t nBits, size_t sBits, size_t cSize) {
    size_t sSize = 1 << (sBits - 1);
    size_t gSize = 1 << (nBits - sBits);

    auto grid = MTL::Size(1, 1, 1);
    auto block = MTL::Size(1, 1, 1);

    size_t threads = 128;
    // First thread over S
    block.width = std::min(threads, sSize);
    threads /= block.width;
    // Next thread over G
    block.height = std::min(threads, gSize);
    // Don't bother threading over C
    size_t grids = 32;
    // First grid over S
    grid.width = std::min(grids, sSize / block.width);
    grids /= grid.width;
    // Next grid over G
    grid.height = std::min(grids, gSize / block.height);
    grids /= grid.height;
    // Next grid over C
    grid.depth = std::min(grids, cSize);
    // Kick it off
    encode->dispatchThreadgroups(grid, block);
    encode->endEncoding();
    encode->release();
  }
};

namespace risc0 {

IHalPtr getGpuHal() {
  return std::make_shared<MetalHal>();
}

} // namespace risc0
