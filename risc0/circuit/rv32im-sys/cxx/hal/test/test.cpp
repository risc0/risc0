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

#include <iostream>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "core/log.h"
#include "rv32im/emu/trace.h"

using namespace risc0;

class TestIO {
public:
  TestIO(IHalPtr hal) : hal(hal), rng(42), dist(0, Fp::P - 1) {}
  IHalPtr getHal() { return hal; }
  HalArray<Fp> makeArray(size_t size) {
    auto out = hal->allocateArray<Fp>(size);
    PinnedArrayWO<Fp> pOut(hal, out);
    for (size_t i = 0; i < size; i++) {
      pOut[i] = dist(rng);
    }
    return out;
  }
  HalMatrix<Fp> makeMatrix(size_t rows, size_t cols) {
    auto out = hal->allocateMatrix<Fp>(rows, cols);
    PinnedMatrixWO<Fp> pOut(hal, out);
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        pOut(i, j) = dist(rng);
      }
    }
    return out;
  }
  template <typename T> void addOutput(HalArray<T> out) {
    PinnedArrayRO<T> pOut(hal, out);
    size_t start = data.size();
    data.resize(start + out.size() * sizeof(T));
    memcpy(data.data() + start, pOut.data(), out.size() * sizeof(T));
  }
  template <typename T> void addOutput(HalMatrix<T> out) {
    PinnedMatrixRO<T> pOut(hal, out);
    size_t start = data.size();
    data.resize(start + out.size() * sizeof(T));
    memcpy(data.data() + start, pOut.data(), out.size() * sizeof(T));
  }
  size_t outSize() { return data.size(); }
  uint8_t* outData() { return data.data(); }
  Fp rngFp() { return dist(rng); }
  FpExt rngFpExt() { return FpExt(rngFp(), rngFp(), rngFp(), rngFp()); }
  uint32_t rngU32(size_t size) {
    std::uniform_int_distribution<uint32_t> distX(0, size - 1);
    return distX(rng);
  }

private:
  IHalPtr hal;
  std::default_random_engine rng;
  std::uniform_int_distribution<uint32_t> dist;
  std::vector<uint8_t> data;
};

template <typename F> void compareHals(IHalPtr h1, IHalPtr h2, F func) {
  TestIO t1(h1);
  TestIO t2(h2);
  LOG(1, "Running H1");
  func(h1, t1);
  LOG(1, "Running H2");
  func(h2, t2);
  LOG(1, "Verifying");
  if (t1.outSize() != t2.outSize()) {
    throw std::runtime_error("Size mismatch");
  }
  uint8_t* out1 = t1.outData();
  uint8_t* out2 = t2.outData();
  for (size_t i = 0; i < t1.outSize(); i++) {
    if (out1[i] != out2[i]) {
      LOG(0,
          "Mismatch: byte " << i << ", h1 = " << uint32_t(out1[i])
                            << ", h2 = " << uint32_t(out2[i]));
      throw std::runtime_error("Mismatch");
    }
  }
}

void testArrayRoundtrip(IHalPtr hal, TestIO& io) {
  auto data = io.makeArray(107);
  io.addOutput(data.slice(17, 53));
}

void testMatrixRoundtrip(IHalPtr hal, TestIO& io) {
  auto data = io.makeMatrix(23, 75);
  io.addOutput(data);
}

void testHashRows(IHalPtr hal, TestIO& io) {
  auto in = io.makeMatrix(5000, 600);
  auto out = hal->allocateArray<Digest>(5000);
  hal->hashRows(out, in);
  io.addOutput(out);
}

void testMerkle(IHalPtr hal, TestIO& io) {
  size_t levels = 10;
  size_t cols = 200;
  size_t maxPo2 = (1 << levels);
  auto in = io.makeMatrix(maxPo2, cols);
  auto out = hal->allocateArray<Digest>(2 * maxPo2);
  hal->hashRows(out.slice(maxPo2, maxPo2), in);
  for (size_t i = levels; i-- > 0;) {
    uint32_t po2 = 1 << i;
    hal->hashFold(out.slice(po2, po2), out.slice(2 * po2, 2 * po2));
  }
  io.addOutput(out.slice(maxPo2, maxPo2));
}

void testExpand(IHalPtr hal, TestIO& io) {
  auto in = io.makeMatrix(1024, 101);
  auto out = hal->allocateMatrix<Fp>(4096, 101);
  hal->batchExpandAndEvaluate(out, in);
  io.addOutput(out);
}

void testInterpolate(IHalPtr hal, TestIO& io) {
  auto in = io.makeMatrix(1024, 101);
  hal->batchInterpolate(in);
  io.addOutput(in);
}

void testBatchPolyEval(IHalPtr hal, TestIO& io) {
  size_t rows = 1024;
  size_t cols = 150;
  size_t spots = 17;
  auto input = hal->allocateMatrix<Fp>(rows, cols);
  auto out = hal->allocateArray<FpExt>(spots);
  auto which = hal->allocateArray<uint32_t>(spots);
  auto xs = hal->allocateArray<FpExt>(spots);
  {
    PinnedMatrixWO<Fp> cInput(hal, input);
    PinnedArrayWO<uint32_t> cWhich(hal, which);
    PinnedArrayWO<FpExt> cXs(hal, xs);
    for (size_t i = 0; i < cols; i++) {
      for (size_t j = 0; j < rows; j++) {
        cInput(j, i) = io.rngFp();
      }
    }
    for (size_t i = 0; i < spots; i++) {
      cWhich[i] = io.rngU32(cols);
      cXs[i] = io.rngFpExt();
    }
  }
  hal->batchPolyEval(out, input, which, xs);
  {
    PinnedArrayRO<FpExt> pOut(hal, out);
    for (size_t i = 0; i < 10; i++) {
      LOG(0, i << ":" << pOut[i]);
    }
  }
  io.addOutput(out);
}

TEST(hal, compareArrayRoundtrip) {
  IHalPtr cpuHal = getCpuHal();
  IHalPtr gpuHal = getGpuHal();
  compareHals(cpuHal, gpuHal, testArrayRoundtrip);
}

TEST(hal, compareMatrixRoundtrip) {
  IHalPtr cpuHal = getCpuHal();
  IHalPtr gpuHal = getGpuHal();
  compareHals(cpuHal, gpuHal, testMatrixRoundtrip);
}

TEST(hal, compareHashRow) {
  IHalPtr cpuHal = getCpuHal();
  IHalPtr gpuHal = getGpuHal();
  compareHals(cpuHal, gpuHal, testHashRows);
}

TEST(hal, compareMerkle) {
  IHalPtr cpuHal = getCpuHal();
  IHalPtr gpuHal = getGpuHal();
  compareHals(cpuHal, gpuHal, testMerkle);
}

TEST(hal, compareExpand) {
  IHalPtr cpuHal = getCpuHal();
  IHalPtr gpuHal = getGpuHal();
  compareHals(cpuHal, gpuHal, testExpand);
}

TEST(hal, compareInterpolate) {
  IHalPtr cpuHal = getCpuHal();
  IHalPtr gpuHal = getGpuHal();
  compareHals(cpuHal, gpuHal, testInterpolate);
}

TEST(hal, compareBatchPolyEval) {
  IHalPtr cpuHal = getCpuHal();
  IHalPtr gpuHal = getGpuHal();
  compareHals(cpuHal, gpuHal, testBatchPolyEval);
}
