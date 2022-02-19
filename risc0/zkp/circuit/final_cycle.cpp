#include "risc0/zkp/circuit/final_cycle.h"

#include "risc0/zkp/circuit/step_state.h"

namespace risc0 {

void FinalCycle::set(StepState& state) {
  Value cycle = state.code.cycle.get();
  auto prevFinal = state.getPrev(3).asFinal();
  auto decode = state.getPrev(2).asDecode();
  auto compute = state.getPrev(1).asCompute();
  auto& resultInfo = compute.resultInfo;
  ValueU32 result = resultInfo.result.get();
  BYZ_IF(resultInfo.doStore.get()) {
    Value isWOM = compute.x1.get(kMemBits + 1);
    Value memAddr = compute.x1.getPart(2, kMemBits);
    state.data.memIO.doWrite(cycle, memAddr, result, isWOM);
  }
  BYZ_IF(1 - resultInfo.doStore.get()) { state.data.memIO.doRead(cycle); }
  // Set the registers
  rdLow.set(resultInfo.setReg.get() * decode.inst.getPart(7, 3));
  rdHigh.set(resultInfo.setReg.get() * decode.inst.getPart(10, 2));
  for (int i = 1; i < 32; i++) {
    Value sel = rdLow.is(i % 8) * rdHigh.is(i / 8);
    regs[i].set((1 - sel) * prevFinal.regs[i].get() + sel * result);
  }
  // Set the new PC
  carryLow.set(pc.setPart(resultInfo.pcRaw.low(), 0, 16));
  carryHigh.set(pc.setPart(resultInfo.pcRaw.high() + carryLow.get(), 16, 16));
  risc0Log("C%u: Final: 0x%04x%04x -> r%u, pc = 0x%08x",
           {cycle,
            resultInfo.result.high(),
            resultInfo.result.low(),
            decode.inst.getPart(7, 5),
            pc.getPart(2, kMemBits) * 4});
}

} // namespace risc0
