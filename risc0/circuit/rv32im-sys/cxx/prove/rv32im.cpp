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

#include "prove/rv32im.h"

#include "core/log.h"
#include "rv32im/emu/emu.h"
#include "rv32im/emu/povw.h"
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
    {
      // Clear initial global values
      PinnedArrayWO<Fp> globalFp(hal, state[0].global);
      for (size_t i = 0; i < globalFp.size(); i++) {
        globalFp[i] = 0;
      }
      // Copy across the one special global that is needed during 'set'
      // TODO: Remove when we get rid of v2Compat
      PinnedArrayRO<uint32_t> globalAux(hal,
                                        aux.slice(0, sizeof(GlobalsWitness) / sizeof(uint32_t)));
      const GlobalsWitness* wit = reinterpret_cast<const GlobalsWitness*>(globalAux.data());
      Globals* globals = reinterpret_cast<Globals*>(globalFp.data());
      globals->v2Compat = wit->v2Compat;
    }
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

PreflightResultsPtr preflight(size_t po2,
                              rv32im::MemoryImage& image,
                              rv32im::HostIO& io,
                              uint32_t endCycle,
                              rv32im::PovwNonce povwNonce) {
  LOG(1, "Executing");
  size_t rows = size_t(1) << po2;
  auto results = std::make_shared<PreflightResults>();
  results->rowInfo.resize(rows);
  results->aux.resize(rows * computeMaxWitPerRow());
  Trace trace(
      rows, results->rowInfo.data(), results->aux.data(), povwNonce, &results->block_counts[0]);
  results->isFinal = emulate(trace, image, io, rows, endCycle);
  results->cycles = trace.getUserCycles();
  LOG(1,
      "Finalizing, trace row count = " << trace.getRowCount()
                                       << ", aux size = " << trace.getAuxSize());
  trace.finalize();
  results->rowInfo.resize(trace.getRowCount());
  results->aux.resize(trace.getAuxSize());
  return results;
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

void Rv32imProver::prove(WriteIop& iop, const PreflightResults& preflight) {
  LOG(1, "Copying to GPU");
  rowInfo.copyFromCpu(hal, preflight.rowInfo.data(), preflight.rowInfo.size());
  aux.copyFromCpu(hal, preflight.aux.data(), preflight.aux.size());
  LOG(1, "Proving");
  prover.prove(iop);
}

size_t Rv32imProver::po2() const {
  return prover.getPo2();
}

} // namespace risc0
