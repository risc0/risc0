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

#include "buffers.h"
#include "fp.h"
#include "fpext.h"
#include "witgen.h"

namespace risc0::circuit::rv32im_v2::cpu {

extern NondetRegStruct back_NondetReg(ExecContext& ctx,Index distance0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetRegStruct exec_NondetReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetExtRegStruct back_NondetExtReg(ExecContext& ctx,Index distance0, BoundLayout<NondetExtRegLayout> layout1)  ;
extern NondetExtRegStruct exec_NondetExtReg(ExecContext& ctx,ExtVal arg0, BoundLayout<NondetExtRegLayout> layout1)  ;
extern NondetRegStruct back_Reg(ExecContext& ctx,Index distance0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetRegStruct exec_Reg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetExtRegStruct back_ExtReg(ExecContext& ctx,Index distance0, BoundLayout<NondetExtRegLayout> layout1)  ;
extern NondetExtRegStruct exec_ExtReg(ExecContext& ctx,ExtVal arg0, BoundLayout<NondetExtRegLayout> layout1)  ;
extern NondetRegStruct back_NondetBitReg(ExecContext& ctx,Index distance0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetRegStruct exec_NondetBitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetRegStruct back_BitReg(ExecContext& ctx,Index distance0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetRegStruct exec_BitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetRegStruct exec_NondetTwitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)  ;
extern NondetFakeTwitRegStruct exec_NondetFakeTwitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetFakeTwitRegLayout> layout1)  ;
extern FakeTwitRegStruct exec_FakeTwitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetFakeTwitRegLayout> layout1)  ;
extern NondetRegStruct exec_IsZero(ExecContext& ctx,Val arg0, BoundLayout<IsZeroLayout> layout1)  ;
extern ArgU8Struct exec_ArgU8(ExecContext& ctx,Val arg0, Val arg1_0, BoundLayout<ArgU8Layout> layout2)  ;
extern NondetRegStruct exec_NondetU8Reg(ExecContext& ctx,Val arg0, BoundLayout<NondetU8RegLayout> layout1)  ;
extern U8RegStruct exec_U8Reg(ExecContext& ctx,Val arg0, BoundLayout<NondetU8RegLayout> layout1)  ;
extern ArgU16Struct exec_ArgU16(ExecContext& ctx,Val arg0, Val arg1_0, BoundLayout<ArgU16Layout> layout2)  ;
extern NondetU16RegStruct exec_NondetU16Reg(ExecContext& ctx,Val arg0, BoundLayout<NondetU16RegLayout> layout1)  ;
extern NondetU16RegStruct exec_U16Reg(ExecContext& ctx,Val arg0, BoundLayout<NondetU16RegLayout> layout1)  ;
extern ToBits_5_Struct exec_ToBits_5_(ExecContext& ctx,Val arg0, BoundLayout<ToBits_5_Layout> layout1)  ;
extern ValU32Struct exec_DynPo2(ExecContext& ctx,Val arg0, BoundLayout<DynPo2Layout> layout1)  ;
extern NormalizeU32Struct exec_NormalizeU32(ExecContext& ctx,DenormedValU32Struct arg0, BoundLayout<NormalizeU32Layout> layout1)  ;
extern AddrDecomposeStruct exec_AddrDecompose(ExecContext& ctx,ValU32Struct arg0, Val arg1_0, BoundLayout<AddrDecomposeLayout> layout2)  ;
extern AddrDecomposeBitsStruct exec_AddrDecomposeBits(ExecContext& ctx,ValU32Struct arg0, Val arg1_0, BoundLayout<AddrDecomposeBitsLayout> layout2)  ;
extern CmpEqualStruct exec_CmpEqual(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<CmpEqualLayout> layout2)  ;
extern CmpLessThanUnsignedStruct exec_CmpLessThanUnsigned(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<CmpLessThanUnsignedLayout> layout2)  ;
extern NondetRegStruct exec_GetSignU32(ExecContext& ctx,ValU32Struct arg0, BoundLayout<GetSignU32Layout> layout1)  ;
extern CmpLessThanStruct exec_CmpLessThan(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<CmpLessThanLayout> layout2)  ;
extern ToBits_16_Struct exec_ToBits_16_(ExecContext& ctx,Val arg0, BoundLayout<ToBits_16_Layout> layout1)  ;
extern FromBits_16_Struct exec_BitwiseAndU16(ExecContext& ctx,Val arg0, Val arg1_0, BoundLayout<BitwiseAndU16Layout> layout2)  ;
extern ValU32Struct exec_BitwiseAnd(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<BitwiseAndLayout> layout2)  ;
extern ValU32Struct exec_BitwiseOr(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<BitwiseOrLayout> layout2)  ;
extern ValU32Struct exec_BitwiseXor(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<BitwiseXorLayout> layout2)  ;
extern DecoderStruct exec_Decoder(ExecContext& ctx,ValU32Struct arg0, BoundLayout<DecoderLayout> layout1)  ;
extern MemoryArgStruct exec_MemoryArg(ExecContext& ctx,Val arg0, Val arg1_0, Val arg2_0, ValU32Struct arg3, BoundLayout<MemoryArgLayout> layout4)  ;
extern CycleArgStruct exec_CycleArg(ExecContext& ctx,Val arg0, Val arg1_0, BoundLayout<CycleArgLayout> layout2)  ;
extern IsCycleStruct exec_IsCycle(ExecContext& ctx,Val arg0, BoundLayout<IsCycleLayout> layout1)  ;
extern MemoryIOStruct exec_MemoryIO(ExecContext& ctx,Val arg0, Val arg1_0, BoundLayout<MemoryIOLayout> layout2)  ;
extern IsForwardStruct exec_IsForward(ExecContext& ctx,MemoryIOStruct arg0, BoundLayout<IsForwardLayout> layout1)  ;
extern GetDataStruct exec_MemoryRead(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<MemoryReadLayout> layout2)  ;
extern MemoryWriteStruct exec_MemoryWrite(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, ValU32Struct arg2_0, BoundLayout<MemoryWriteLayout> layout3)  ;
extern MemoryWriteUnconstrainedStruct exec_MemoryWriteUnconstrained(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<MemoryWriteUnconstrainedLayout> layout2)  ;
extern GetDataStruct exec_MemoryPageIn(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<MemoryPageInLayout> layout2)  ;
extern GetDataStruct exec_MemoryPageOut(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<MemoryPageOutLayout> layout2)  ;
extern OneHot_3_Struct exec_OneHot_3_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_3_Layout> layout1)  ;
extern GetDataStruct exec_MemoryGet(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, OneHot_3_Struct arg2_0, BoundLayout<MemoryGetLayout> layout3)  ;
extern OneHot_8_Struct exec_OneHot_8_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_8_Layout> layout1)  ;
extern InstInputStruct exec_InstInput(ExecContext& ctx,Val arg0, Val arg1_0, ValU32Struct arg2_0, Val arg3, Val arg4, BoundLayout<InstInputLayout> layout5)  ;
extern DoCycleTableStruct exec_DoCycleTable(ExecContext& ctx,NondetRegStruct arg0, BoundLayout<DoCycleTableLayout> layout1)  ;
extern DecoderStruct exec_DecodeInst(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<DecodeInstLayout> layout2)  ;
extern GetDataStruct exec_ReadReg(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, Val arg2_0, BoundLayout<ReadRegLayout> layout3)  ;
extern ReadSourceRegsStruct exec_ReadSourceRegs(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, DecoderStruct arg2_0, BoundLayout<ReadSourceRegsLayout> layout3)  ;
extern WriteRdStruct exec_WriteRd(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, DecoderStruct arg2_0, Val arg3, ValU32Struct arg4, BoundLayout<WriteRdLayout> layout5)  ;
extern ExpandU32Struct exec_ExpandU32(ExecContext& ctx,ValU32Struct arg0, Val arg1_0, BoundLayout<ExpandU32Layout> layout2)  ;
extern SplitTotalStruct exec_SplitTotal(ExecContext& ctx,Val arg0, BoundLayout<SplitTotalLayout> layout1)  ;
extern MultiplyAccumulateStruct exec_MultiplyAccumulate(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, ValU32Struct arg2_0, MultiplySettingsStruct arg3, BoundLayout<MultiplyAccumulateLayout> layout4)  ;
extern DivInputStruct exec_DivInput(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<DivInputLayout> layout2)  ;
extern DivideReturnStruct exec_DoDiv(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, Val arg2_0, Val arg3, BoundLayout<DoDivLayout> layout4)  ;
extern ValU32Struct exec_OpSRL(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpSRLLayout> layout1)  ;
extern NondetRegStruct exec_TopBit(ExecContext& ctx,ValU32Struct arg0, BoundLayout<TopBitLayout> layout1)  ;
extern ValU32Struct exec_OpSRA(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpSRALayout> layout1)  ;
extern ValU32Struct exec_OpSRLI(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpSRLILayout> layout1)  ;
extern ValU32Struct exec_OpSRAI(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpSRAILayout> layout1)  ;
extern ValU32Struct exec_OpDIV(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpDIVLayout> layout1)  ;
extern ValU32Struct exec_OpDIVU(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpDIVULayout> layout1)  ;
extern ValU32Struct exec_OpREM(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpREMLayout> layout1)  ;
extern ValU32Struct exec_OpREMU(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpREMULayout> layout1)  ;
extern InstOutputBaseStruct exec_Div0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Div0Layout> layout2)  ;
extern MiscInputStruct exec_MiscInput(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<MiscInputLayout> layout2)  ;
extern InstOutputBaseStruct exec_FinalizeMisc(ExecContext& ctx,NondetRegStruct arg0, MiscInputStruct arg1_0, MiscOutputStruct arg2_0, BoundLayout<FinalizeMiscLayout> layout3)  ;
extern MiscOutputStruct exec_OpXOR(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpXORLayout> layout1)  ;
extern MiscOutputStruct exec_OpOR(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpORLayout> layout1)  ;
extern MiscOutputStruct exec_OpAND(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpANDLayout> layout1)  ;
extern MiscOutputStruct exec_OpSLT(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpSLTLayout> layout1)  ;
extern MiscOutputStruct exec_OpSLTU(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpSLTULayout> layout1)  ;
extern InstOutputBaseStruct exec_Misc0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Misc0Layout> layout2)  ;
extern MiscOutputStruct exec_OpXORI(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpXORILayout> layout1)  ;
extern MiscOutputStruct exec_OpORI(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpORILayout> layout1)  ;
extern MiscOutputStruct exec_OpANDI(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpANDILayout> layout1)  ;
extern MiscOutputStruct exec_OpSLTI(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpSLTILayout> layout1)  ;
extern MiscOutputStruct exec_OpSLTIU(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpSLTIULayout> layout1)  ;
extern MiscOutputStruct exec_OpBEQ(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBEQLayout> layout1)  ;
extern MiscOutputStruct exec_OpBNE(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBNELayout> layout1)  ;
extern MiscOutputStruct exec_OpBLT(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBLTLayout> layout1)  ;
extern InstOutputBaseStruct exec_Misc1(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Misc1Layout> layout2)  ;
extern MiscOutputStruct exec_OpBGE(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBGELayout> layout1)  ;
extern MiscOutputStruct exec_OpBLTU(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBLTULayout> layout1)  ;
extern MiscOutputStruct exec_OpBGEU(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBGEULayout> layout1)  ;
extern MiscOutputStruct exec_OpJALR(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpJALRLayout> layout1)  ;
extern InstOutputBaseStruct exec_Misc2(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Misc2Layout> layout2)  ;
extern MulInputStruct exec_MulInput(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<MulInputLayout> layout2)  ;
extern DoMulStruct exec_DoMul(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, Val arg2_0, Val arg3, BoundLayout<DoMulLayout> layout4)  ;
extern ValU32Struct exec_OpSLL(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpSLLLayout> layout1)  ;
extern ValU32Struct exec_OpSLLI(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpSLLILayout> layout1)  ;
extern ValU32Struct exec_OpMUL(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpMULLayout> layout1)  ;
extern ValU32Struct exec_OpMULH(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpMULHLayout> layout1)  ;
extern ValU32Struct exec_OpMULHSU(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpMULHSULayout> layout1)  ;
extern ValU32Struct exec_OpMULHU(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpMULHULayout> layout1)  ;
extern InstOutputBaseStruct exec_Mul0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Mul0Layout> layout2)  ;
extern MemLoadInputStruct exec_MemLoadInput(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<MemLoadInputLayout> layout2)  ;
extern MemStoreInputStruct exec_MemStoreInput(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<MemStoreInputLayout> layout2)  ;
extern MemStoreFinalizeStruct exec_MemStoreFinalize(ExecContext& ctx,NondetRegStruct arg0, MemStoreInputStruct arg1_0, ValU32Struct arg2_0, BoundLayout<MemStoreFinalizeLayout> layout3)  ;
extern SplitWordStruct exec_SplitWord(ExecContext& ctx,Val arg0, BoundLayout<SplitWordLayout> layout1)  ;
extern ValU32Struct exec_OpLB(ExecContext& ctx,MemLoadInputStruct arg0, BoundLayout<OpLBLayout> layout1)  ;
extern ValU32Struct exec_OpLH(ExecContext& ctx,MemLoadInputStruct arg0, BoundLayout<OpLHLayout> layout1)  ;
extern ValU32Struct exec_OpLBU(ExecContext& ctx,MemLoadInputStruct arg0, BoundLayout<OpLBULayout> layout1)  ;
extern InstOutputBaseStruct exec_Mem0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Mem0Layout> layout2)  ;
extern ValU32Struct exec_OpSB(ExecContext& ctx,MemStoreInputStruct arg0, BoundLayout<OpSBLayout> layout1)  ;
extern InstOutputBaseStruct exec_Mem1(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Mem1Layout> layout2)  ;
extern DigestRegStruct back_DigestReg(ExecContext& ctx,Index distance0, BoundLayout<DigestRegLayout> layout1)  ;
extern DigestRegStruct exec_DigestReg(ExecContext& ctx,ValU32Struct8Array arg0, BoundLayout<DigestRegLayout> layout1)  ;
extern InstOutputBaseStruct exec_ControlLoadRootAndNonce(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlLoadRootAndNonceLayout> layout2, GlobalBuf global3)  ;
extern InstOutputBaseStruct exec_ControlResume(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlResumeLayout> layout2, GlobalBuf global3)  ;
extern InstOutputBaseStruct exec_ControlMRET(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlMRETLayout> layout2)  ;
extern InstOutputBaseStruct exec_ControlSuspend(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlSuspendLayout> layout2, GlobalBuf global3)  ;
extern InstOutputBaseStruct exec_ControlStoreRoot(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlStoreRootLayout> layout2, GlobalBuf global3)  ;
extern InstOutputBaseStruct exec_ControlTable(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlTableLayout> layout2)  ;
extern InstOutputBaseStruct exec_ControlDone(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlDoneLayout> layout2, GlobalBuf global3)  ;
extern InstOutputBaseStruct exec_ControlUserEcallOrFence(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlUserEcallOrFenceLayout> layout2)  ;
extern InstOutputBaseStruct exec_Control0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Control0Layout> layout2, GlobalBuf global3)  ;
extern OneHot_6_Struct exec_OneHot_6_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_6_Layout> layout1)  ;
extern ECallOutputStruct exec_MachineECall(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, Val arg2_0, BoundLayout<MachineECallLayout> layout3)  ;
extern ECallOutputStruct exec_ECallTerminate(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ECallTerminateLayout> layout2, GlobalBuf global3)  ;
extern OneHot_4_Struct exec_OneHot_4_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_4_Layout> layout1)  ;
extern DecomposeLow2Struct exec_DecomposeLow2(ExecContext& ctx,Val arg0, BoundLayout<DecomposeLow2Layout> layout1)  ;
extern ECallOutputStruct exec_ECallHostReadSetup(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ECallHostReadSetupLayout> layout2)  ;
extern ECallOutputStruct exec_ECallHostWrite(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ECallHostWriteLayout> layout2)  ;
extern ECallOutputStruct exec_ECallHostReadBytes(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, Val arg2_0, Val arg3, Val arg4, BoundLayout<ECallHostReadBytesLayout> layout5)  ;
extern ECallOutputStruct exec_ECallHostReadWords(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, Val arg2_0, Val arg3, BoundLayout<ECallHostReadWordsLayout> layout4)  ;
extern InstOutputBaseStruct exec_ECall0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ECall0Layout> layout2, GlobalBuf global3)  ;
extern NondetRegStruct exec_SBox(ExecContext& ctx,Val arg0, BoundLayout<SBoxLayout> layout1)  ;
extern MultiplyByMIntStruct exec_DoIntRound(ExecContext& ctx,Val24Array arg0, Val arg1_0, BoundLayout<DoIntRoundLayout> layout2)  ;
extern DoIntRoundsStruct exec_DoIntRounds(ExecContext& ctx,Val24Array arg0, BoundLayout<DoIntRoundsLayout> layout1)  ;
extern MultiplyByMExtStruct exec_DoExtRound(ExecContext& ctx,Val24Array arg0, Val24Array arg1_0, BoundLayout<DoExtRoundLayout> layout2)  ;
extern MultiplyByMExtStruct exec_DoExtRoundByIdx(ExecContext& ctx,Val24Array arg0, Val arg1_0, BoundLayout<DoExtRoundByIdxLayout> layout2)  ;
extern PoseidonStateStruct back_PoseidonState(ExecContext& ctx,Index distance0, BoundLayout<PoseidonStateLayout> layout1)  ;
extern PoseidonStateStruct exec_PoseidonState(ExecContext& ctx,PoseidonOpDefStruct arg0, Val arg1_0, Val arg2_0, Val arg3, Val arg4, Val arg5, Val24Array arg6, ExtVal arg7, BoundLayout<PoseidonStateLayout> layout8)  ;
extern PoseidonStateStruct exec_PoseidonInvalid(ExecContext& ctx,BoundLayout<PoseidonStateLayout> layout0)  ;
extern ReadAddrStruct exec_ReadAddr(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<ReadAddrLayout> layout2)  ;
extern PoseidonStateStruct exec_PoseidonEcall(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonEcallLayout> layout2)  ;
extern PoseidonStateStruct exec_PoseidonPagingEntry(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonStateLayout> layout2)  ;
extern PoseidonStateStruct exec_PoseidonEntry(ExecContext& ctx,NondetRegStruct arg0, ValU32Struct arg1_0, Val arg2_0, BoundLayout<PoseidonEntryLayout> layout3)  ;
extern ReadElemStruct exec_ReadElem(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<ReadElemLayout> layout2)  ;
extern PoseidonStateStruct exec_PoseidonLoadState(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonLoadStateLayout> layout2)  ;
extern PoseidonStateStruct exec_PoseidonLoadInShort(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonLoadInShortLayout> layout2, GlobalBuf global3)  ;
extern PoseidonStateStruct exec_PoseidonLoadInLow(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonLoadInLowLayout> layout2, GlobalBuf global3)  ;
extern PoseidonStateStruct exec_PoseidonLoadInHigh(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonLoadInHighLayout> layout2, GlobalBuf global3)  ;
extern PoseidonStateStruct exec_PoseidonLoadIn(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonLoadInLayout> layout2, GlobalBuf global3)  ;
extern PoseidonStateStruct exec_PoseidonExtRound(ExecContext& ctx,PoseidonStateStruct arg0, BoundLayout<PoseidonExtRoundLayout> layout1)  ;
extern PoseidonStateStruct exec_PoseidonIntRounds(ExecContext& ctx,PoseidonStateStruct arg0, BoundLayout<PoseidonIntRoundsLayout> layout1)  ;
extern PoseidonStateStruct exec_PoseidonCheckOut(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonCheckOutLayout> layout2)  ;
extern FieldToWordStruct exec_FieldToWord(ExecContext& ctx,Val arg0, BoundLayout<FieldToWordLayout> layout1)  ;
extern PoseidonStateStruct exec_PoseidonStoreOut(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonStoreOutLayout> layout2)  ;
extern PoseidonStateStruct exec_PoseidonDoOut(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonDoOutLayout> layout2)  ;
extern PoseidonStateStruct exec_PoseidonStoreState(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonStoreStateLayout> layout2)  ;
extern IsU24Struct exec_IsU24(ExecContext& ctx,Val arg0, BoundLayout<IsU24Layout> layout1)  ;
extern PoseidonStateStruct exec_PoseidonPagingLoadNode(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonStateLayout> layout2)  ;
extern PoseidonStateStruct exec_PoseidonPagingLoadPage(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonStateLayout> layout2)  ;
extern PoseidonStateStruct exec_PoseidonPagingLoadDone(ExecContext& ctx,BoundLayout<PoseidonStateLayout> layout0)  ;
extern PoseidonStateStruct exec_PoseidonPagingStoreNode(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonStateLayout> layout2)  ;
extern PoseidonStateStruct exec_PoseidonPagingStorePage(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonStateLayout> layout2)  ;
extern PoseidonStateStruct exec_PoseidonPagingStoreDone(ExecContext& ctx,BoundLayout<PoseidonStateLayout> layout0)  ;
extern PoseidonStateStruct exec_PoseidonPaging(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, PoseidonStateStruct arg2_0, BoundLayout<PoseidonPagingLayout> layout3)  ;
extern InstOutputBaseStruct exec_Poseidon0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Poseidon0Layout> layout2, GlobalBuf global3)  ;
extern InstOutputBaseStruct exec_Poseidon1(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Poseidon1Layout> layout2)  ;
extern CarryExtractStruct exec_CarryExtract(ExecContext& ctx,Val arg0, BoundLayout<CarryExtractLayout> layout1)  ;
extern UnpackReg_32__16_Struct exec_UnpackReg_32__16_(ExecContext& ctx,Val2Array arg0, BoundLayout<UnpackReg_32__16_Layout> layout1)  ;
extern UnpackReg_32__16_Struct exec_CarryAndExpand(ExecContext& ctx,Val2Array arg0, BoundLayout<CarryAndExpandLayout> layout1)  ;
extern ShaStateStruct back_ShaState(ExecContext& ctx,Index distance0, BoundLayout<ShaStateLayout> layout1)  ;
extern ShaStateStruct exec_ShaState(ExecContext& ctx,Val32Array arg0, Val32Array arg1_0, Val32Array arg2_0, Val arg3, Val arg4, Val arg5, Val arg6, Val arg7, Val arg8, Val arg9, BoundLayout<ShaStateLayout> layout10)  ;
extern ShaStateStruct exec_ShaInvalid(ExecContext& ctx,BoundLayout<ShaStateLayout> layout0)  ;
extern ShaStateStruct exec_ShaEcall(ExecContext& ctx,NondetRegStruct arg0, BoundLayout<ShaEcallLayout> layout1)  ;
extern ShaStateStruct exec_ShaLoadState(ExecContext& ctx,NondetRegStruct arg0, ShaStateStruct arg1_0, BoundLayout<ShaLoadStateLayout> layout2)  ;
extern ShaStateStruct exec_ShaLoadData(ExecContext& ctx,NondetRegStruct arg0, ShaStateStruct arg1_0, ShaStateStruct arg2_0, ShaStateStruct arg3, ShaStateStruct arg4, BoundLayout<ShaLoadDataLayout> layout5)  ;
extern ShaStateStruct exec_ShaMix(ExecContext& ctx,NondetRegStruct arg0, ShaStateStruct arg1_0, ShaStateStruct arg2_0, ShaStateStruct arg3, ShaStateStruct arg4, ShaStateStruct arg5, ShaStateStruct arg6, ShaStateStruct arg7, BoundLayout<ShaMixLayout> layout8)  ;
extern ShaStateStruct exec_ShaStoreState(ExecContext& ctx,NondetRegStruct arg0, ShaStateStruct arg1_0, ShaStateStruct arg2_0, ShaStateStruct arg3, BoundLayout<ShaStoreStateLayout> layout4)  ;
extern InstOutputBaseStruct exec_Sha0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Sha0Layout> layout2)  ;
extern BigIntStateStruct back_BigIntState(ExecContext& ctx,Index distance0, BoundLayout<BigIntStateLayout> layout1)  ;
extern BigIntStateStruct exec_BigIntState(ExecContext& ctx,Val arg0, Val arg1_0, Val arg2_0, Val arg3, Val arg4, Val16Array arg5, Val arg6, BoundLayout<BigIntStateLayout> layout7)  ;
extern BigIntStateStruct exec_BigIntInvalid(ExecContext& ctx,BoundLayout<BigIntStateLayout> layout0)  ;
extern BigIntStateStruct exec_BigIntEcall(ExecContext& ctx,NondetRegStruct arg0, BoundLayout<BigIntEcallLayout> layout1)  ;
extern SplitU32Struct exec_SplitU32(ExecContext& ctx,ValU32Struct arg0, BoundLayout<SplitU32Layout> layout1)  ;
extern AddrDecomposeBitsStruct exec_BigIntAddr(ExecContext& ctx,ValU32Struct arg0, Val arg1_0, BoundLayout<BigIntAddrLayout> layout2)  ;
extern BigIntReadStruct exec_BigIntRead(ExecContext& ctx,NondetRegStruct arg0, ValU32Struct arg1_0, Val arg2_0, BoundLayout<BigIntReadLayout> layout3)  ;
extern BigIntWitnessStruct exec_BigIntWitness(ExecContext& ctx,Val16Array arg0, BoundLayout<BigIntWitnessLayout> layout1)  ;
extern BigIntWitnessStruct exec_BigIntWrite(ExecContext& ctx,NondetRegStruct arg0, ValU32Struct arg1_0, Val arg2_0, BoundLayout<BigIntWriteLayout> layout3)  ;
extern BigIntWitnessStruct exec_BigIntCheck(ExecContext& ctx,BoundLayout<BigIntWitnessLayout> layout0)  ;
extern BigIntStateStruct exec_BigIntStep(ExecContext& ctx,NondetRegStruct arg0, BigIntStateStruct arg1_0, BoundLayout<BigIntStepLayout> layout2)  ;
extern InstOutputBaseStruct exec_BigInt0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<BigInt0Layout> layout2)  ;
extern BigIntAccumStateStruct back_BigIntAccumState(ExecContext& ctx,Index distance0, BoundLayout<BigIntAccumStateLayout> layout1)  ;
extern BigIntAccumStateStruct exec_BigIntAccumState(ExecContext& ctx,ExtVal arg0, ExtVal arg1_0, ExtVal arg2_0, BoundLayout<BigIntAccumStateLayout> layout3)  ;
extern OneHot_7_Struct exec_OneHot_7_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_7_Layout> layout1)  ;
extern BigIntAccumStateStruct exec_BigIntPolyOpNop(ExecContext& ctx,BoundLayout<BigIntAccumStateLayout> layout0)  ;
extern BigIntAccumStateStruct exec_BigIntPolyOpShift(ExecContext& ctx,BigIntTopStateStruct arg0, BigIntAccumStateStruct arg1_0, ExtVal arg2_0, BoundLayout<BigIntAccumStateLayout> layout3)  ;
extern BigIntAccumStateStruct exec_BigIntPolyOpSetTerm(ExecContext& ctx,BigIntTopStateStruct arg0, BigIntAccumStateStruct arg1_0, ExtVal arg2_0, BoundLayout<BigIntAccumStateLayout> layout3)  ;
extern BigIntAccumStateStruct exec_BigIntPolyOpAddTotal(ExecContext& ctx,BigIntTopStateStruct arg0, BigIntAccumStateStruct arg1_0, ExtVal arg2_0, BoundLayout<BigIntPolyOpAddTotalLayout> layout3)  ;
extern BigIntAccumStateStruct exec_BigIntPolyOpCarry1(ExecContext& ctx,BigIntTopStateStruct arg0, BigIntAccumStateStruct arg1_0, ExtVal arg2_0, BoundLayout<BigIntAccumStateLayout> layout3)  ;
extern BigIntAccumStateStruct exec_BigIntPolyOpCarry2(ExecContext& ctx,BigIntTopStateStruct arg0, BigIntAccumStateStruct arg1_0, ExtVal arg2_0, BoundLayout<BigIntAccumStateLayout> layout3)  ;
extern BigIntAccumStateStruct exec_BigIntPolyOpEqz(ExecContext& ctx,BigIntTopStateStruct arg0, BigIntAccumStateStruct arg1_0, ExtVal arg2_0, BoundLayout<BigIntAccumStateLayout> layout3)  ;
extern BigIntAccumStruct exec_BigIntAccum(ExecContext& ctx,BigIntTopStateStruct arg0, ExtVal1Array arg1_0, BoundLayout<BigIntAccumLayout> layout2)  ;
extern OneHot_13_Struct exec_OneHot_13_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_13_Layout> layout1)  ;
extern TopStruct exec_Top(ExecContext& ctx,BoundLayout<TopLayout> layout0, GlobalBuf global1)  ;
extern void step_Top(ExecContext& ctx,MutableBuf data0, GlobalBuf global1)  ;
extern AccumStruct exec_Accum(ExecContext& ctx,BigIntTopStateStruct arg0, ExtVal1Array arg1_0, BoundLayout<AccumLayout> layout2)  ;
extern BigIntTopStateStruct exec_TopExtract(ExecContext& ctx,BoundLayout<TopLayout> layout0, GlobalBuf global1)  ;
extern AccumStruct execUser_Accum(ExecContext& ctx,BoundLayout<TopLayout> arg0, ExtVal1Array arg1_0, BoundLayout<AccumLayout> layout2, GlobalBuf global3)  ;
extern ComponentStruct exec_TopAccum(ExecContext& ctx,BoundLayout<TopLayout> arg0, BoundLayout<LayoutAccumLayout> layout1, GlobalBuf global2, GlobalBuf mix3)  ;
extern void step_TopAccum(ExecContext& ctx,MutableBuf accum0, MutableBuf data1, GlobalBuf global2, GlobalBuf mix3)  ;

} // namespace risc0::circuit::rv32im_v2::cpu
