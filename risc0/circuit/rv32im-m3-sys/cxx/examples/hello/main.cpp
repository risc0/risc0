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

#include "core/log.h"
#include "prove/prove.h"
#include "verify/verify.h"
#include "zkp/fp.h"
#include "zkp/rou.h"
#include <random>
// #include <fstream>

using namespace risc0;

struct Context {
  FpExt total;
  FpExt ecMix;
  FpExt curMix;

  inline void eqz(Fp val) {
    total += curMix * val;
    curMix *= ecMix;
  }

  inline void eqz(FpExt val) {
    total += curMix * val;
    curMix *= ecMix;
  }

  template<typename T>
  inline void push(T argument) {}
  template<typename T>
  inline void pull(T argument) {}
};

CircuitInfo* getCircuitInfo(IHalPtr hal, size_t po2) {
  CircuitInfo& ci = *(new CircuitInfo());

  // Set up taps
  ci.taps.addTap(0, 0, 0);
  ci.taps.addTap(1, 0, 0);
  ci.taps.addTap(2, 0, 0);
  ci.taps.done();

  // Set up accum group
  ci.groups.resize(3);
  GroupInfo& accumInfo = ci.groups[0];
  accumInfo.globalCount = 0;
  accumInfo.mixCount = 0;
  accumInfo.witgen = [hal](std::vector<GroupState>& state) {
    PinnedMatrixWO accum(hal, state[0].table);
    for (size_t row = 0; row < accum.rows(); row++) {
      accum(row, 0) = 0;
    }
  };

  // Set up code group
  GroupInfo& codeInfo = ci.groups[1];
  codeInfo.globalCount = 0;
  codeInfo.mixCount = 0;
  codeInfo.witgen = [hal](std::vector<GroupState>& state) {
    PinnedMatrixWO code(hal, state[1].table);
    for (size_t row = 0; row < code.rows(); row++) {
      code(row, 0) = 0;
    }
  };

  // Set up data group
  GroupInfo& dataInfo = ci.groups[2];
  dataInfo.globalCount = 0;
  dataInfo.mixCount = 0;
  dataInfo.witgen = [hal](std::vector<GroupState>& state) {
    PinnedMatrixWO data(hal, state[2].table);
    std::mt19937 rng(123);
    std::uniform_int_distribution<int> dist(0, 1);
    for (size_t row = 0; row < data.rows(); row++) {
      data(row, 0) = dist(rng);
    }
  };

  // Eval check
  ci.evalCheck = [hal, po2](HalMatrix<Fp> out, std::vector<GroupState>& state, FpExt ecMix) {
    size_t NUM_ROWS = 1 << (po2 + 2);
    PinnedMatrixWO pOut(hal, out);
    PinnedMatrixRO accum(hal, state[0].expTable);
    PinnedMatrixRO code(hal, state[1].expTable);
    PinnedMatrixRO data(hal, state[2].expTable);

    for (size_t row = 0; row < NUM_ROWS; row++) {
      // Collect circuit constraints
      Context ctx;
      ctx.total = FpExt(0);
      ctx.ecMix = ecMix;
      ctx.curMix = FpExt(1);
      ctx.eqz(FpExt(accum(row, 0)));
      ctx.eqz(FpExt(code(row, 0)));
      ctx.eqz(data(row, 0) * (data(row, 0) - Fp(1)));

      // Divide by 3x^n - 1 TODO: In reality this simplifies for each po2 to
      // multiplication by 4 constants, one at each row % 4, but it's annoying to
      // precompute + pass them, and impact of this code relative to the entire
      // validity polynomial is small
      auto ret = ctx.total;
      Fp rou = ROU_FWD[po2 + 2];
      Fp x = Fp(3) * pow(rou, row);
      Fp y = pow(x, 1 << po2);
      Fp quot = inv(y - 1);
      for (size_t i = 0; i < 4; i++) {
        pOut(row, i) = elem(ret, i) * quot;
      }
    }
  };

  return &ci;
}

VerifyCircuitInfo* getVerifyCircuitInfo() {
  VerifyCircuitInfo& ci = *(new VerifyCircuitInfo());

  // Set up taps
  ci.taps.addTap(0, 0, 0);
  ci.taps.addTap(1, 0, 0);
  ci.taps.addTap(2, 0, 0);
  ci.taps.done();

  // Set up groups
  ci.groups.resize(3);
  VerifyGroupInfo& accumInfo = ci.groups[0];
  accumInfo.globalCount = 0;
  accumInfo.mixCount = 0;
  VerifyGroupInfo& codeInfo = ci.groups[1];
  codeInfo.globalCount = 0;
  codeInfo.mixCount = 0;
  VerifyGroupInfo& dataInfo = ci.groups[2];
  dataInfo.globalCount = 0;
  dataInfo.mixCount = 0;

  ci.evalCheck = [](FpExt* evals, Fp* globals, FpExt* mix, FpExt ecMix, FpExt z) -> FpExt {
    FpExt* accum = const_cast<FpExt*>(evals);
    FpExt* code = const_cast<FpExt*>(evals) + 1;
    FpExt* data = const_cast<FpExt*>(evals) + 2;

    Context ctx;
    ctx.total = FpExt(0);
    ctx.ecMix = ecMix;
    LOG(0, "ecMix: " << ecMix);
    ctx.curMix = FpExt(1);
    ctx.eqz(FpExt(accum[0]));
    ctx.eqz(FpExt(code[0]));
    ctx.eqz(data[0] * (data[0] - FpExt(1)));

    return ctx.total;
  };

  return &ci;
}

int main() {
  size_t po2 = 12;

  IHalPtr hal = getCpuHal();
  CircuitInfo& ci = *getCircuitInfo(hal, po2);
  Prover prover(hal, ci, po2);

  WriteIop wiop;
  prover.prove(wiop);
  const std::vector<Fp>& transcript = wiop.getTranscript();

  LOG(0, "Finished proving, begin verifying...");

  VerifyCircuitInfo& vci = *getVerifyCircuitInfo();
  ReadIop riop(transcript.data(), transcript.size());
  verify(vci, riop, po2);
  riop.done();

  // This code can be used to write the proof to a file for consumption by the
  // Rust verifier. This artifact is checked into the risc0 repo as
  // `/risc0/zkp/src/prove/proof.bin`
  // auto myfile = std::fstream("/path/to/risc0/zkp/src/prove/proof.bin", std::ios::out | std::ios::binary);
  // myfile.write((const char*) (wiop.getTranscript().data()), 4 * wiop.getTranscript().size());
  // myfile.close();

  return 0;
}
