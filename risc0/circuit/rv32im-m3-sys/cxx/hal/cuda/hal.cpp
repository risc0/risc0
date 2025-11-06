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
#include "hal/po2s.h"

#include <iostream>
#include <map>

#include "core/log.h"
#include "core/util.h"
#include "zkp/params.h"
#include "zkp/rou.h"

using risc0::EvalInfo;
using risc0::Fp;
using risc0::FpExt;
using risc0::RowInfo;

struct SparkError {
  int code;
  char* message;
};

// sys.cu
extern "C" void* cuda_malloc(size_t size);
extern "C" void cuda_free(void* buf);
extern "C" bool cuda_sync();
extern "C" bool cuda_copy_to_host_sync(void* host, const void* dev, size_t size);
extern "C" bool cuda_copy_to_dev_sync(void* dev, const void* host, size_t size);
extern "C" bool cuda_copy_dev(void* dst, void* src, size_t size);
extern "C" bool cuda_zero_dev(void* buf, size_t size);

// api.cu
extern "C" SparkError sppark_poseidon2_fold(void* d_out, const void* d_in, size_t num_hashes);
extern "C" SparkError
sppark_poseidon2_rows(void* d_out, const void* d_in, uint32_t count, uint32_t col_size);
extern "C" void prefix_sum(Fp* d_inout, uint32_t count);
extern "C" SparkError
rv32im_m3_poly_divide(FpExt* d_inout, size_t len, FpExt* remainder, FpExt pow);

// query.cu
extern "C" bool cuda_query(
    void* out, void* data, void* tree, size_t querySize, size_t rows, size_t cols, size_t idx);

// ntt.cu
extern "C" SparkError sppark_init();
extern "C" SparkError
sppark_batch_expand(void* out, void* in, uint32_t inPo2, uint32_t expPo2, uint32_t cols);
extern "C" SparkError sppark_batch_NTT(void* d_inout, uint32_t lg_domain_size, uint32_t poly_count);
extern "C" SparkError
sppark_batch_iNTT(void* d_inout, uint32_t lg_domain_size, uint32_t poly_count);
extern "C" SparkError
sppark_batch_zk_shift(void* d_inout, uint32_t lg_domain_size, uint32_t poly_count);

// kernels.cu
extern "C" bool cuda_batch_bit_reverse(Fp* io, uint32_t po2, uint32_t cols);
extern "C" bool cuda_batch_evaluate_any(FpExt* out,
                                        const Fp* coeffs,
                                        const uint32_t* which,
                                        const FpExt* xs,
                                        uint32_t outSize,
                                        uint32_t deg);
extern "C" bool cuda_fri_fold(Fp* out, const Fp* in, FpExt mix, uint32_t count);
extern "C" bool cuda_mix_poly_coeffs(FpExt* out,
                                     const Fp* in,
                                     const uint32_t* combos,
                                     FpExt mixStart,
                                     FpExt mix,
                                     uint32_t inputSize,
                                     uint32_t count);
extern "C" bool cuda_combos_prepare(FpExt* combos,
                                    const FpExt* eval,
                                    const EvalInfo* info,
                                    FpExt mix,
                                    uint32_t rows,
                                    uint32_t evalSize);
extern "C" bool
cuda_combos_finalize(Fp* out, const FpExt* combos, uint32_t numCombos, uint32_t count);

// data_witgen.cu
extern "C" void data_witgen_cuda(Fp* data,
                                 Fp* globals,
                                 const RowInfo* info,
                                 const uint32_t* aux,
                                 uint32_t* tables,
                                 Fp rou,
                                 uint32_t numRows);

// accum_witgen.cu
extern "C" void accum_witgen_cuda(
    Fp* accum, const Fp* data, const Fp* globals, const FpExt* accMix, Fp rou, uint32_t numRows);

// eval_check.cu
extern "C" void eval_check_cuda(Fp* check,
                                const Fp* data,
                                const Fp* accum,
                                const Fp* globals,
                                const FpExt* accMix,
                                FpExt ecMix,
                                Fp rou,
                                uint32_t numRows);

using namespace risc0;

class CudaHal;

size_t checkPo2(size_t in) {
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

class CudaBuffer : public IBuffer {
  friend class CudaHal;

public:
  CudaBuffer(void* devPtr, size_t size) : devPtr(devPtr), bufSize(size) {}
  ~CudaBuffer() override { cuda_free(devPtr); }
  size_t size() override { return bufSize; }
  void copyFromCpu(size_t offset, const void* data, size_t size) override {
    cuda_copy_to_dev_sync(reinterpret_cast<uint8_t*>(devPtr) + offset, data, size);
  }

private:
  void* devPtr;
  size_t bufSize;
};

using CudaBufferPtr = std::shared_ptr<CudaBuffer>;

class CudaHal : public IHal {
private:
  template <typename T> T* toDevPtr(HalArray<T>& in) {
    IBufferPtr iBuf = extract(in);
    size_t offset = getOffset(in);
    CudaBuffer* cudaBuf = static_cast<CudaBuffer*>(iBuf.get());
    return reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(cudaBuf->devPtr) + offset);
  }
  template <typename T> T* toDevPtr(HalMatrix<T>& in) {
    IBufferPtr iBuf = extract(in);
    CudaBuffer* cudaBuf = static_cast<CudaBuffer*>(iBuf.get());
    return reinterpret_cast<T*>(cudaBuf->devPtr);
  }

public:
  CudaHal() {}
  ~CudaHal() override {}

  void hashRows(HalArray<Digest> out, HalMatrix<Fp> in) override {
    if (in.rows() != out.size()) {
      throw std::runtime_error("Mismatched sizes in hashRows");
    }
    auto err = sppark_poseidon2_rows(toDevPtr(out), toDevPtr(in), out.size(), in.cols());
    if (err.code != 0) {
      throw std::runtime_error(std::string("Error during hash fold: ") + err.message);
    }
  }

  void hashFold(HalArray<Digest> out, HalArray<Digest> in) override {
    if (in.size() != 2 * out.size()) {
      throw std::runtime_error("Mismatched sizes in hashFold");
    }
    auto err = sppark_poseidon2_fold(toDevPtr(out), toDevPtr(in), out.size());
    if (err.code != 0) {
      throw std::runtime_error(std::string("Error during hash fold:") + err.message);
    }
  }

  void query(HalArray<Fp> out,
             HalMatrix<Fp> data,
             HalArray<Digest> tree,
             size_t topSize,
             size_t idx) override {
    size_t steps = log2Ceil(data.rows()) - log2Ceil(topSize);
    size_t querySize = steps * 8 + data.cols();
    if (querySize != out.size() || tree.size() != 2 * data.rows() || idx >= data.rows()) {
      throw std::runtime_error("Inconsistent sizes in query");
    }
    bool ok = cuda_query(
        toDevPtr(out), toDevPtr(data), toDevPtr(tree), querySize, data.rows(), data.cols(), idx);
    if (!ok) {
      throw std::runtime_error("Error during query");
    }
  }

  void batchBitReverse(HalMatrix<Fp> io) override {
    size_t po2 = log2Ceil(io.rows());
    if (size_t(1) << po2 != io.rows()) {
      throw std::runtime_error("Batch bit reverse must be a po2");
    }
    bool ok = cuda_batch_bit_reverse(toDevPtr(io), po2, io.cols());
    if (!ok) {
      throw std::runtime_error("Error during batch bit reverse");
    }
  }

  void batchExpandAndEvaluate(HalMatrix<Fp> out, HalMatrix<Fp> in) override {
    uint32_t inPo2 = log2Ceil(in.rows());
    uint32_t expPo2 = log2Ceil(out.rows() / in.rows());
    if (in.rows() != (size_t(1) << inPo2) || (size_t(1) << expPo2) * in.rows() != out.rows() ||
        in.cols() != out.cols()) {
      LOG(0, "in.rows() = " << in.rows() << ", in.cols = " << in.cols());
      LOG(0, "out.rows() = " << out.rows() << ", out.cols = " << out.cols());
      LOG(0, "inPo2 = " << inPo2 << ", expPo2 = " << expPo2);
      throw std::runtime_error("Mismatched sizes batchExpandNtt");
    }
    auto err = sppark_batch_expand(toDevPtr(out), toDevPtr(in), inPo2, expPo2, in.cols());
    if (err.code != 0) {
      throw std::runtime_error(std::string("Error during batch expand:") + err.message);
    }
    err = sppark_batch_NTT(toDevPtr(out), inPo2 + expPo2, out.cols());
    if (err.code != 0) {
      throw std::runtime_error(std::string("Error during batch interpolate:") + err.message);
    }
  }

  void batchInterpolate(HalMatrix<Fp> io) override {
    uint32_t inPo2 = log2Ceil(io.rows());
    if (io.rows() != (size_t(1) << inPo2)) {
      throw std::runtime_error("invlaid size in batchInterpolateNtt");
    }
    auto err = sppark_batch_iNTT(toDevPtr(io), inPo2, io.cols());
    if (err.code != 0) {
      throw std::runtime_error(std::string("Error during batch interpolate:") + err.message);
    }
  }

  void batchShift(HalMatrix<Fp> io) override {
    uint32_t inPo2 = log2Ceil(io.rows());
    if (io.rows() != (size_t(1) << inPo2)) {
      throw std::runtime_error("invlaid size in batchInterpolateNtt");
    }
    auto err = sppark_batch_zk_shift(toDevPtr(io), inPo2, io.cols());
    if (err.code != 0) {
      throw std::runtime_error(std::string("Error during batch interpolate:") + err.message);
    }
  }

  void batchPolyEval(HalArray<FpExt> out,
                     HalMatrix<Fp> coeffs,
                     HalArray<uint32_t> cols,
                     HalArray<FpExt> xs) override {
    bool ok = cuda_batch_evaluate_any(
        toDevPtr(out), toDevPtr(coeffs), toDevPtr(cols), toDevPtr(xs), out.size(), coeffs.rows());
    if (!ok) {
      throw std::runtime_error("Error during batchPolyEval");
    }
  }

  void combosMix(HalMatrix<FpExt> combos,
                 HalMatrix<Fp> coeffs,
                 HalArray<uint32_t> whichCombo,
                 FpExt cur,
                 FpExt mix) override {
    if (combos.rows() != coeffs.rows() || coeffs.cols() != whichCombo.size()) {
      throw std::runtime_error("Invalid combosMix");
    }
    bool ok = cuda_mix_poly_coeffs(toDevPtr(combos),
                                   toDevPtr(coeffs),
                                   toDevPtr(whichCombo),
                                   cur,
                                   mix,
                                   coeffs.cols(),
                                   combos.rows());
    if (!ok) {
      throw std::runtime_error("Error during combosMix");
    }
  }

  void combosPrep(HalMatrix<FpExt> combos,
                  HalArray<FpExt> eval,
                  HalArray<EvalInfo> info,
                  FpExt mix) override {
    if (eval.size() != info.size()) {
      throw std::runtime_error("Invalid combosMix");
    }
    bool ok = cuda_combos_prepare(
        toDevPtr(combos), toDevPtr(eval), toDevPtr(info), mix, combos.rows(), eval.size());
    if (!ok) {
      throw std::runtime_error("Error during combosPrep");
    }
  }

  void combosDivide(HalMatrix<FpExt> combos, HalArray<DivideInfo> info) override {
    PinnedArrayRO<DivideInfo> pInfo(shared_from_this(), info);
    FpExt rem;
    for (size_t i = 0; i < info.size(); i++) {
      FpExt* poly = reinterpret_cast<FpExt*>(toDevPtr(combos)) + pInfo[i].comboId * combos.rows();
      auto err = rv32im_m3_poly_divide(poly, combos.rows(), &rem, pInfo[i].z);
      if (err.code != 0) {
        throw std::runtime_error(std::string("Error during combosDivide:") + err.message);
      }
    }
  }

  void combosFinalize(HalMatrix<Fp> out, HalMatrix<FpExt> combos) override {
    if (out.rows() != combos.rows() || out.cols() != kExtSize) {
      throw std::runtime_error("Invalid combosFinalize");
    }
    bool ok = cuda_combos_finalize(toDevPtr(out), toDevPtr(combos), combos.cols(), out.rows());
    if (!ok) {
      throw std::runtime_error("Error during combosFinalize");
    }
  }

  void friFold(HalMatrix<Fp> out, HalMatrix<Fp> in, FpExt mix) override {
    bool ok = cuda_fri_fold(toDevPtr(out), toDevPtr(in), mix, out.rows());
    if (!ok) {
      throw std::runtime_error("Error during friFold");
    }
  }

  void computeDataWitness(HalMatrix<Fp> data,
                          HalArray<Fp> globals,
                          HalArray<RowInfo> rows,
                          HalArray<uint32_t> aux,
                          HalArray<uint32_t> tables) override {
    if (data.rows() != rows.size()) {
      throw std::runtime_error("Mismatched sizes in computeDataWitness");
    }
    size_t po2 = checkPo2(data.rows());
    data_witgen_cuda(toDevPtr(data),
                     toDevPtr(globals),
                     toDevPtr(rows),
                     toDevPtr(aux),
                     toDevPtr(tables),
                     risc0::ROU_FWD[po2],
                     data.rows());
  }

  void computeAccumWitness(HalMatrix<Fp> accum,
                           HalMatrix<Fp> data,
                           HalArray<Fp> globals,
                           HalArray<FpExt> accMix) override {
    if (accum.rows() != data.rows()) {
      throw std::runtime_error("Mismatched sizes in computeDataWitness");
    }
    size_t po2 = checkPo2(accum.rows());
    accum_witgen_cuda(toDevPtr(accum),
                      toDevPtr(data),
                      toDevPtr(globals),
                      toDevPtr(accMix),
                      risc0::ROU_FWD[po2],
                      accum.rows());
    for (size_t i = 0; i < 4; i++) {
      prefix_sum(toDevPtr(accum) + accum.rows() * i, accum.rows());
    }
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
    size_t po2 = checkPo2(check.rows() >> 2);
    eval_check_cuda(toDevPtr(check),
                    toDevPtr(data),
                    toDevPtr(accum),
                    toDevPtr(globals),
                    toDevPtr(accMix),
                    ecMix,
                    risc0::ROU_FWD[po2 + 2],
                    check.rows());
  }

  void sync() override {
    if (!cuda_sync()) {
      throw std::runtime_error("CUDA sync failed");
    }
  }

private:
  IBufferPtr allocate(size_t size) override {
    void* devPtr = cuda_malloc(size);
    return std::make_shared<CudaBuffer>(devPtr, size);
  }

  void
  copy(IBufferPtr dst, size_t dstOffset, IBufferPtr src, size_t srcOffset, size_t count) override {
    uint8_t* dstPtr =
        reinterpret_cast<uint8_t*>(static_cast<CudaBuffer*>(dst.get())->devPtr) + dstOffset;
    uint8_t* srcPtr =
        reinterpret_cast<uint8_t*>(static_cast<CudaBuffer*>(src.get())->devPtr) + srcOffset;
    if (!cuda_copy_dev(dstPtr, srcPtr, count)) {
      throw std::runtime_error("Failed to copy");
    }
  }

  void zero(IBufferPtr buf, size_t offset, size_t size) override {
    uint8_t* bufPtr =
        reinterpret_cast<uint8_t*>(static_cast<CudaBuffer*>(buf.get())->devPtr) + offset;
    if (!cuda_zero_dev(bufPtr, size)) {
      throw std::runtime_error("Failed to zero");
    }
  }

  void* pin(IBufferPtr buf, size_t offset, size_t size, bool _sync) override {
    void* host = malloc(size);
    if (_sync) {
      CudaBuffer* cudaBuf = static_cast<CudaBuffer*>(buf.get());
      uint8_t* dev = reinterpret_cast<uint8_t*>(cudaBuf->devPtr) + offset;
      if (!cuda_copy_to_host_sync(host, dev, size)) {
        throw std::runtime_error("CUDA copy + sync failed");
      }
    }
    return host;
  }

  void unpin(IBufferPtr buf, void* pinned, size_t offset, size_t size, bool modified) override {
    if (modified) {
      CudaBuffer* cudaBuf = static_cast<CudaBuffer*>(buf.get());
      uint8_t* dev = reinterpret_cast<uint8_t*>(cudaBuf->devPtr) + offset;
      cuda_copy_to_dev_sync(dev, pinned, size);
    }
    free(pinned);
  }
};

namespace risc0 {

IHalPtr getGpuHal() {
  return std::make_shared<CudaHal>();
}

} // namespace risc0
