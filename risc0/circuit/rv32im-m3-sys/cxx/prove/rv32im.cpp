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

#include "prove/rv32im.h"

#include "core/log.h"
#include "rv32im/emu/emu.h"
#include "rv32im/emu/verify.h"

namespace risc0 {

using namespace rv32im;

Rv32CircuitInfo::Rv32CircuitInfo(IHalPtr hal,
                                 HalArray<RowInfo> rowInfo,
                                 HalArray<uint32_t> aux,
                                 HalArray<uint32_t> tables,
                                 bool doValidate) {
  ci.groups.resize(2);
  size_t dataCols = computeMaxDataPerRow();
  GroupInfo& dataInfo = ci.groups[0];
  dataInfo.globalCount = NUM_GLOBALS;
  dataInfo.mixCount = 0;
  for (size_t i = 0; i < dataCols; i++) {
    ci.taps.addTap(0, i, 0);
  }
  dataInfo.witgen = [hal, rowInfo, aux, tables, doValidate](std::vector<GroupState>& state) {
    LOG(1, "Computing data witness");
    hal->zero(tables);
    hal->computeDataWitness(state[0].table, state[0].global, rowInfo, aux, tables);
    if (doValidate) {
      LOG(1, "Do verify");
      PinnedMatrixRO<Fp> pData(hal, state[0].table);
      PinnedArrayRO<Fp> pGlobals(hal, state[0].global);
      verify(pData.data(), pGlobals.data(), pData.rows());
    }
  };
  size_t accumCols = computeTotalAccum();
  size_t accumNormalCols = computeMaxAccumPerRow();
  GroupInfo& accumInfo = ci.groups[1];
  accumInfo.globalCount = 0;
  accumInfo.mixCount = ACCUM_MIX_SIZE;
  for (size_t i = 0; i < accumCols; i++) {
    ci.taps.addTap(1, i, 0);
    if (i < 4 || i >= accumNormalCols) {
      ci.taps.addTap(1, i, 1);
    }
  }
  accumInfo.witgen = [hal](std::vector<GroupState>& state) {
    LOG(1, "Computing accum witness");
    hal->computeAccumWitness(state[1].table, state[0].table, state[0].global, state[1].mix);
  };
  ci.evalCheck = [hal](HalMatrix<Fp> out, std::vector<GroupState>& state, FpExt ecMix) {
    LOG(1, "Do eval check");
    hal->evalCheck(out, state[0].expTable, state[1].expTable, state[0].global, state[1].mix, ecMix);
  };
  ci.taps.done();
}

Rv32imProver::Rv32imProver(IHalPtr hal, size_t po2, bool doValidate)
    : hal(hal)
    , rows(size_t(1) << po2)
    , rowInfo(hal->allocateArray<RowInfo>(rows))
    , aux(hal->allocateArray<uint32_t>(rows * computeMaxWitPerRow()))
    // TODO: table size needs to handle max cycles * 2, this presumes no more
    // than 10 cycles per row
    , tables(hal->allocateArray<uint32_t>(256 + 65536 + 20 * rows))
    , ci(hal, rowInfo, aux, tables, doValidate)
    , prover(hal, ci.ci, po2) {}

bool Rv32imProver::preflight(rv32im::MemoryImage& image, HostIO& io) {
  LOG(1, "Pinning");
  PinnedArrayWO cpuRI(hal, rowInfo);
  PinnedArrayWO cpuAux(hal, aux);
  LOG(1, "Executing");
  Trace trace(rows, cpuRI.data(), cpuAux.data());
  bool ret = emulate(trace, image, io, rows);
  LOG(1, "Finalizing, trace row count = " << trace.getRowCount());
  trace.finalize();
  LOG(1, "Copying to GPU");
  return ret;
}

void Rv32imProver::prove(WriteIop& iop) {
  prover.prove(iop);
}

size_t Rv32imProver::po2() const {
  return prover.getPo2();
}

} // namespace risc0
