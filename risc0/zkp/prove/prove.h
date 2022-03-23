// Copyright 2022 Risc0, Inc.
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

#include <string>
#include <vector>

#include "risc0/zkp/accel/accel.h"
#include "risc0/zkp/core/fp4.h"
#include "risc0/zkp/prove/step/step.h"
#include "risc0/zkp/prove/write_iop.h"
#include "risc0/zkp/verify/taps.h"

namespace risc0 {

// This class provides both virtual call which implement core cicuit specific logic
// as well as access to state data regarding execution trace, etc.

class ProveCircuit {
  virtual TapSetRef getTaps() const = 0;
  // Perform initial 'execution' setting code + data Additionally, write any
  // 'results' as needed.
  virtual void execute(WriteIOP& iop) = 0;
  // Perform 'accumlate' stage, using the iop for any RNG state.
  virtual void accumulate(WriteIOP& iop) = 0;
  // Compute check polynomial
  virtual void evalCheck(   //
      AccelSlice<Fp> check, // Output: Check polynomial
      // Evaluations of each polynomial on an extended domain
      AccelConstSlice<Fp> codeEval,  //
      AccelConstSlice<Fp> dataEval,  //
      AccelConstSlice<Fp> accumEval, //
      // Mix factor for polynomial constraints
      Fp4 polyMix) const = 0;

  // Po2 size, Code + Data are only available after execute
  virtual uint32_t getPo2() const;
  virtual std::vector<Fp>& getCode() const = 0;
  virtual std::vector<Fp>& getData() const = 0;
  // Accum is only available after accumulate
  virtual std::vector<Fp>& getAccum() const = 0;
};

BufferU32 prove(const std::string& elfFile, MemoryHandler& io);

} // namespace risc0
