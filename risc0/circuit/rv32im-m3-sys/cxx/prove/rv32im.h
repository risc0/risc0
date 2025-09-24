// Copyright 2025 RISC Zero, Inc.
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

#pragma once

#include "rv32im/emu/emu.h"
#include "prove/prove.h"

namespace risc0 {

struct Rv32CircuitInfo {
  Rv32CircuitInfo(IHalPtr hal, HalArray<RowInfo> rowInfo, HalArray<uint32_t> aux, HalArray<uint32_t> tables, bool doValidate);
  CircuitInfo ci;
};

class Rv32imProver {
public:
  Rv32imProver(IHalPtr hal, size_t po2, bool doValidate = false);

  bool preflight(rv32im::MemoryImage& image, rv32im::HostIO& io);
  void prove(WriteIop& iop);

private:
  IHalPtr hal;
  size_t rows;
  HalArray<RowInfo> rowInfo;
  HalArray<uint32_t> aux;
  HalArray<uint32_t> tables;
  Rv32CircuitInfo ci;
  Prover prover;
};

}  // namespace risc0
