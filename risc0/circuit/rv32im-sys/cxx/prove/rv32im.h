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

#pragma once

#include "prove/prove.h"
#include "rv32im/emu/emu.h"

namespace risc0 {

struct Rv32CircuitInfo {
  Rv32CircuitInfo(IHalPtr hal,
                  HalArray<RowInfo> rowInfo,
                  HalArray<uint32_t> aux,
                  HalArray<uint32_t> tables,
                  bool doValidate);
  CircuitInfo ci;
};

struct PreflightResults {
  bool isFinal;    // Did this preflight result in termination
  uint32_t cycles; // How many cycles did this preflight do
  std::vector<RowInfo> rowInfo;
  std::vector<uint32_t> aux;
};

using PreflightResultsPtr = std::shared_ptr<PreflightResults>;

PreflightResultsPtr preflight(size_t po2,
                              rv32im::MemoryImage& image,
                              rv32im::HostIO& io,
                              uint32_t endCycle = UINT32_MAX);

class Rv32imProver {
public:
  Rv32imProver(IHalPtr hal, size_t po2, bool doValidate = false);
  void prove(WriteIop& iop,
             const RowInfo* rowInfo,
             size_t rowInfoSize,
             const uint32_t* aux,
             size_t aux_size);

  size_t po2() const;

private:
  IHalPtr hal;
  size_t rows;
  HalArray<RowInfo> rowInfo;
  HalArray<uint32_t> aux;
  HalArray<uint32_t> tables;
  Rv32CircuitInfo ci;
  Prover prover;
};

} // namespace risc0
