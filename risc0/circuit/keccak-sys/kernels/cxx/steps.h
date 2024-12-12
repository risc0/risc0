// Copyright 2024 RISC Zero, Inc.
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

#include "buffers.h"
#include "fp.h"
#include "fpext.h"
#include "witgen.h"

namespace risc0::circuit::keccak::cpu {

<<<<<<< HEAD
=======
extern NondetRegStruct back_NondetReg(ExecContext& ctx,Index distance0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetRegStruct exec_NondetReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetRegStruct back_Reg(ExecContext& ctx,Index distance0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetRegStruct exec_Reg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetBitRegStruct back_NondetBitReg(ExecContext& ctx,Index distance0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetBitRegStruct exec_NondetBitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetRegStruct exec_IsZero(ExecContext& ctx,Val arg0, BoundLayout<IsZeroLayout> layout1)  ;
extern NondetBitRegStruct exec_Xor5(ExecContext& ctx,Val5Array arg0, BoundLayout<NondetRegLayout> layout1)  ;
extern ThetaP1Struct exec_ThetaP1(ExecContext& ctx,Val64Array5Array5Array arg0, BoundLayout<ThetaP1Layout> layout1)  ;
extern OneHot_24_Struct exec_OneHot_24_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_24_Layout> layout1)  ;
extern RoundToArrayStruct exec_RoundToArray(ExecContext& ctx,Val arg0, BoundLayout<RoundToArrayLayout> layout1)  ;
extern IotaStruct exec_Iota(ExecContext& ctx,Val64Array5Array5Array arg0, Val arg1, BoundLayout<IotaLayout> layout2)  ;
extern CarryExtractStruct exec_CarryExtract(ExecContext& ctx,Val arg0, BoundLayout<CarryExtractLayout> layout1)  ;
extern UnpackReg_32__16_Struct exec_UnpackReg_32__16_(ExecContext& ctx,Val2Array arg0, BoundLayout<UnpackReg_32__16_Layout> layout1)  ;
extern UnpackReg_32__16_Struct exec_CarryAndExpand(ExecContext& ctx,Val2Array arg0, BoundLayout<CarryAndExpandLayout> layout1)  ;
extern ExpandBEStruct exec_ExpandBE(ExecContext& ctx,Val2Array arg0, BoundLayout<ExpandBELayout> layout1)  ;
extern TopStateStruct back_TopState(ExecContext& ctx,Index distance0, BoundLayout<TopStateLayout> layout1)  ;
extern TopStateStruct exec_TopState(ExecContext& ctx,Val800Array arg0, Val100Array arg1, Val16Array arg2, BoundLayout<TopStateLayout> layout3)  ;
extern TopStateStruct exec_KeccakRound0(ExecContext& ctx,TopStateStruct arg0, TopStateStruct arg1, BoundLayout<KeccakRound0Layout> layout2)  ;
extern OneHot_8_Struct exec_OneHot_8_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_8_Layout> layout1)  ;
extern DoShaStepStruct exec_DoShaStep(ExecContext& ctx,ShaStateStruct arg0, Val2Array arg1, Val arg2, Val2Array arg3, BoundLayout<DoShaStepLayout> layout4)  ;
extern OneHot_4_Struct exec_OneHot_4_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_4_Layout> layout1)  ;
extern LoadWinStruct exec_LoadWin(ExecContext& ctx,Val100Array arg0, OneHot_8_Struct arg1, Val arg2, BoundLayout<LoadWinLayout> layout3)  ;
extern TopStateStruct exec_ShaCycle(ExecContext& ctx,TopStateStruct arg0, TopStateStruct arg1, Val arg2, Val arg3, BoundLayout<ShaCycleLayout> layout4)  ;
extern TopStateStruct exec_ShaNextBlockCycle(ExecContext& ctx,TopStateStruct arg0, BoundLayout<ShaNextBlockCycleLayout> layout1)  ;
extern TopStateStruct exec_InitCycle(ExecContext& ctx,BoundLayout<TopStateLayout> layout0)  ;
extern UnpackReg_800__16_Struct exec_UnpackReg_800__16_(ExecContext& ctx,Val50Array arg0, BoundLayout<UnpackReg_800__16_Layout> layout1)  ;
extern UnpackReg_800__16_Struct exec_SFlatToBits(ExecContext& ctx,Val16Array arg0, BoundLayout<UnpackReg_800__16_Layout> layout1)  ;
extern TopStateStruct exec_ReadCycle(ExecContext& ctx,TopStateStruct arg0, BoundLayout<ReadCycleLayout> layout1)  ;
extern TopStateStruct exec_ExpandCycle(ExecContext& ctx,TopStateStruct arg0, Val arg1, BoundLayout<ExpandCycleLayout> layout2)  ;
extern TopStateStruct exec_WriteCycle(ExecContext& ctx,TopStateStruct arg0, TopStateStruct arg1, BoundLayout<WriteCycleLayout> layout2)  ;
extern DigestRegStruct exec_DigestReg(ExecContext& ctx,Val16Array arg0, BoundLayout<DigestRegLayout> layout1)  ;
extern TopStateStruct exec_ShutdownCycle(ExecContext& ctx,TopStateStruct arg0, BoundLayout<TopStateLayout> layout1, GlobalBuf global2)  ;
extern ControlStateStruct back_ControlState(ExecContext& ctx,Index distance0, BoundLayout<ControlStateLayout> layout1)  ;
extern ControlStateStruct exec_ControlState(ExecContext& ctx,Val arg0, Val arg1, Val arg2, Val arg3, BoundLayout<ControlStateLayout> layout4)  ;
extern ControlStateStruct exec_KeccackNextRound(ExecContext& ctx,ControlStateStruct arg0, BoundLayout<KeccackNextRoundLayout> layout1)  ;
extern ControlStateStruct exec_ShaNextRound(ExecContext& ctx,ControlStateStruct arg0, BoundLayout<ShaNextRoundLayout> layout1)  ;
extern ControlStateStruct exec_ShaNextBlock(ExecContext& ctx,ControlStateStruct arg0, BoundLayout<ShaNextBlockLayout> layout1)  ;
extern ControlStateStruct exec_ComputeCurrentStep(ExecContext& ctx,Val12Array arg0, ControlStateStruct arg1, BoundLayout<ComputeCurrentStep_SuperLayout> layout2)  ;
extern OneHot_12_Struct exec_OneHot_12_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_12_Layout> layout1)  ;
extern WrapOneHotStruct back_WrapOneHot(ExecContext& ctx,Index distance0, BoundLayout<WrapOneHotLayout> layout1)  ;
extern WrapOneHotStruct exec_WrapOneHot(ExecContext& ctx,OneHot_12_Struct arg0, BoundLayout<WrapOneHotLayout> layout1)  ;
extern TopStateStruct exec_KeccakRound12_0_(ExecContext& ctx,TopStateStruct arg0, TopStateStruct arg1, TopStateStruct arg2, TopStateStruct arg3, BoundLayout<TopStateLayout> layout4)  ;
extern TopStateStruct exec_KeccakRound12_1_(ExecContext& ctx,TopStateStruct arg0, TopStateStruct arg1, TopStateStruct arg2, TopStateStruct arg3, BoundLayout<TopStateLayout> layout4)  ;
extern TopStateStruct exec_KeccakRound34_0_(ExecContext& ctx,TopStateStruct arg0, TopStateStruct arg1, TopStateStruct arg2, Val arg3, BoundLayout<KeccakRound34_0_Layout> layout4)  ;
extern TopStateStruct exec_KeccakRound34_1_(ExecContext& ctx,TopStateStruct arg0, TopStateStruct arg1, TopStateStruct arg2, Val arg3, BoundLayout<KeccakRound34_1_Layout> layout4)  ;
extern TopStruct exec_Top(ExecContext& ctx,BoundLayout<TopLayout> layout0, GlobalBuf global1)  ;
>>>>>>> origin/main
extern void step_Top(ExecContext& ctx,MutableBuf data0, GlobalBuf global1)  ;
extern void step_Top_0(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_1(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_2(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_3(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_4(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_5(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_6(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_7(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_8(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_9(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_10(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_11(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_12(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_13(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_14(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_15(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_16(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_17(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_18(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_19(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_20(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_21(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_22(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_23(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_24(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_25(ExecContext& ctx,MutableBuf arg0, GlobalBuf arg1)  ;
extern void step_Top_26(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_27(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_28(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_29(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_30(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_31(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_32(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_33(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_34(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_35(ExecContext& ctx,MutableBuf arg0)  ;
extern void step_Top_36(ExecContext& ctx,MutableBuf arg0)  ;

} // namespace risc0::circuit::keccak::cpu
