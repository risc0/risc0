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

#include "risc0/zkvm/circuit/data_regs.h"

#include "risc0/zkvm/circuit/mem_check.h"
#include "risc0/zkvm/circuit/step_state.h"

namespace risc0 {

void DataRegs::setExec(StepState& state) {
  Value cycle = state.code.cycle.get();
  auto& codeType = state.code.codeCycleType;
  BYZ_IF(codeType[CodeCycleType::INIT]) {
    risc0Log("C%u: Init", {cycle});
    memIO.doRead(cycle);
    getCycleType().set(DataCycleType::HALT);
  }
  BYZ_IF(codeType[CodeCycleType::MEM_WRITE]) {
    risc0Log("C%u: MemWrite: M[0x%x] = 0x%04x%04x",
             {cycle, state.code.p1.get() * 4, state.code.data.high(), state.code.data.low()});
    memIO.doWrite(
        state.code.cycle.get(), state.code.p1.get(), state.code.data.get(), state.code.p2.get());
    getCycleType().set(DataCycleType::HALT);
  }
  BYZ_IF(codeType[CodeCycleType::RESET]) {
    auto alloc = finalAlloc();
    FinalCycle final(alloc);
    risc0Log("C%u: Reset: %u", {cycle, state.code.p1.get()});
    memIO.doRead(cycle);
    getCycleType().set(DataCycleType::FINAL);
    final.rdLow.set(0);
    final.rdHigh.set(0);
    final.pc.setPartExact(state.code.p1.get(), 0, kMemBits + 2);
    for (size_t i = 0; i < 32; i++) {
      final.regs[i].setLow(0);
      final.regs[i].setHigh(0);
    }
  }
  BYZ_IF(codeType[CodeCycleType::FINI]) {
    auto prevCycleType = state.getPrev(1).getCycleType();
    risc0Log("C%u: Fini", {cycle});
    memIO.doRead(cycle);
    getCycleType().set(DataCycleType::HALT);
    equate(prevCycleType.is(DataCycleType::HALT), 1);
  }
  Value isShaInit0 = state.code.shaCycleType[ShaCycleType::CONTROL] * state.code.p2.get();
  BYZ_IF(codeType[CodeCycleType::NORMAL]) {
    auto alloc = normalAlloc();
    auto prevCycleType = state.getPrev(1).getCycleType();
    auto cycleType = getCycleType();

    // Set cycle type
    BYZ_IF(prevCycleType.is(DataCycleType::FINAL)) { cycleType.set(DataCycleType::DECODE); }
    BYZ_IF(prevCycleType.is(DataCycleType::DECODE)) {
      cycleType.set(state.getPrev(1).asDecode().nextCycleType.get());
      BYZ_IF(cycleType.is(DataCycleType::SHA_SYNC)) {
        auto final = state.getPrev(2).asFinal();
        for (size_t i = 0; i < kOutputRegs; i++) {
          setGlobal(kRegistersGlobalOffset + 2 * i, final.regs[1 + i].low());
          setGlobal(kRegistersGlobalOffset + 2 * i + 1, final.regs[1 + i].high());
        }
      }
    }
    BYZ_IF(prevCycleType.is(DataCycleType::SHA_SYNC)) {
      BYZ_IF(isShaInit0) { cycleType.set(DataCycleType::SHA_CONTROL); }
      BYZ_IF(1 - isShaInit0) { cycleType.set(DataCycleType::SHA_SYNC); }
    }
    BYZ_IF(prevCycleType.is(DataCycleType::SHA_CONTROL) +
           prevCycleType.is(DataCycleType::SHA_DATA)) {
      cycleType.set(state.getPrev(1).asSha().nextCycleType.get());
    }
    BYZ_IF(prevCycleType.is(DataCycleType::HALT)) { cycleType.set(DataCycleType::HALT); }

    // Apply cycle type
    BYZ_IF(cycleType.is(DataCycleType::DECODE)) {
      BufAlloc allocCopy = alloc;
      DecodeCycle decode(allocCopy);
      decode.set(state);
    }
    BYZ_IF(cycleType.is(DataCycleType::COMPUTE_0)) {
      BufAlloc allocCopy = alloc;
      ComputeCycle compute(allocCopy);
      compute.set(state, 0);
    }
    BYZ_IF(cycleType.is(DataCycleType::COMPUTE_1)) {
      BufAlloc allocCopy = alloc;
      ComputeCycle compute(allocCopy);
      compute.set(state, 1);
    }
    BYZ_IF(cycleType.is(DataCycleType::COMPUTE_2)) {
      BufAlloc allocCopy = alloc;
      ComputeCycle compute(allocCopy);
      compute.set(state, 2);
    }
    BYZ_IF(cycleType.is(DataCycleType::COMPUTE_3)) {
      BufAlloc allocCopy = alloc;
      ComputeCycle compute(allocCopy);
      compute.set(state, 3);
    }
    BYZ_IF(cycleType.is(DataCycleType::MULTIPLY)) {
      BufAlloc allocCopy = alloc;
      MultiplyCycle multiply(allocCopy);
      multiply.set(state);
    }
    BYZ_IF(cycleType.is(DataCycleType::DIVIDE)) {
      BufAlloc allocCopy = alloc;
      DivideCycle divide(allocCopy);
      divide.set(state);
    }
    BYZ_IF(cycleType.is(DataCycleType::SHA_SYNC)) {
      BufAlloc alloc = shaAlloc();
      ShaCycle sha(alloc);
      sha.sync(state);
    }
    BYZ_IF(cycleType.is(DataCycleType::SHA_CONTROL)) {
      BufAlloc alloc = shaAlloc();
      ShaCycle sha(alloc);
      sha.setControl(state);
    }
    BYZ_IF(cycleType.is(DataCycleType::SHA_DATA)) {
      BufAlloc alloc = shaAlloc();
      ShaCycle sha(alloc);
      sha.setData(state);
    }
    BYZ_IF(cycleType.is(DataCycleType::HALT)) { memIO.doRead(state.code.cycle.get()); }
  }
  BYZ_IF(codeType[CodeCycleType::FINAL]) {
    auto alloc = finalAlloc();
    auto prevCycleType = state.getPrev(1).getCycleType();
    auto cycleType = getCycleType();
    // Set cycle type
    BYZ_IF(1 - prevCycleType.is(DataCycleType::HALT) - prevCycleType.is(DataCycleType::SHA_SYNC) -
           prevCycleType.is(DataCycleType::SHA_CONTROL) -
           prevCycleType.is(DataCycleType::SHA_DATA)) {
      cycleType.set(DataCycleType::FINAL);
    }
    BYZ_IF(prevCycleType.is(DataCycleType::SHA_SYNC)) {
      BYZ_IF(isShaInit0) { cycleType.set(DataCycleType::SHA_CONTROL); }
      BYZ_IF(1 - isShaInit0) { cycleType.set(DataCycleType::SHA_SYNC); }
    }
    BYZ_IF(prevCycleType.is(DataCycleType::SHA_CONTROL) +
           prevCycleType.is(DataCycleType::SHA_DATA)) {
      cycleType.set(state.getPrev(1).asSha().nextCycleType.get());
    }
    BYZ_IF(prevCycleType.is(DataCycleType::HALT)) { cycleType.set(DataCycleType::HALT); }

    // Apply cycle type
    BYZ_IF(cycleType.is(DataCycleType::FINAL)) {
      BufAlloc allocCopy = alloc;
      FinalCycle final(allocCopy);
      final.set(state);
    }
    BYZ_IF(cycleType.is(DataCycleType::SHA_SYNC)) {
      BufAlloc alloc = shaAlloc();
      ShaCycle sha(alloc);
      sha.sync(state);
    }
    BYZ_IF(cycleType.is(DataCycleType::SHA_CONTROL)) {
      BufAlloc alloc = shaAlloc();
      ShaCycle sha(alloc);
      sha.setControl(state);
    }
    BYZ_IF(cycleType.is(DataCycleType::SHA_DATA)) {
      BufAlloc alloc = shaAlloc();
      ShaCycle sha(alloc);
      sha.setData(state);
    }
    BYZ_IF(cycleType.is(DataCycleType::HALT)) { memIO.doRead(state.code.cycle.get()); }
  }
}

void DataRegs::setMemCheck(StepState& state) { // NOLINT
  auto& codeType = state.code.codeCycleType;
  Value isActive = 0;
  for (size_t i = 0; i < CodeCycleType::NUM_TYPES; i++) {
    isActive = isActive + codeType[i];
  }
  BYZ_IF(isActive) {
    BufAlloc alloc(memCheckBuf.slice(0, 0), memCheckBuf);
    MemCheck check(alloc);
    check.set(state);
  }
}

} // namespace risc0
