struct NondetRegLayout {
  Reg _super;
};
using NondetRegLayout7LayoutArray = ::cuda::std::array<NondetRegLayout,7>;
struct OneHot_7_Layout {
  NondetRegLayout7LayoutArray _super;
};
struct NondetExtRegLayout {
  Reg _super;
};
struct BigIntAccumStateLayout {
  NondetExtRegLayout poly;
  NondetExtRegLayout term;
  NondetExtRegLayout total;
};
struct BigIntPolyOpAddTotalLayout {
  BigIntAccumStateLayout _super;
  NondetExtRegLayout tmp;
};
struct BigIntAccumStateLayout_0 {
  BigIntAccumStateLayout _super;
  BigIntAccumStateLayout arm0;
  BigIntAccumStateLayout arm1;
  BigIntAccumStateLayout arm2;
  BigIntPolyOpAddTotalLayout arm3;
  BigIntAccumStateLayout arm4;
  BigIntAccumStateLayout arm5;
  BigIntAccumStateLayout arm6;
};
struct BigIntAccumLayout {
  OneHot_7_Layout polyOp;
  BigIntAccumStateLayout state;
  BigIntAccumStateLayout_0 stateRedef;
};
struct AccumLayout {
  BigIntAccumLayout _0;
};
using NondetRegLayout8LayoutArray = ::cuda::std::array<NondetRegLayout,8>;
struct OneHot_8_Layout {
  NondetRegLayout8LayoutArray _super;
};
struct InstInputLayout {
  OneHot_8_Layout minorOnehot;
};
using NondetRegLayout13LayoutArray = ::cuda::std::array<NondetRegLayout,13>;
struct OneHot_13_Layout {
  NondetRegLayout13LayoutArray _super;
};
struct ArgU16Layout {
  NondetRegLayout count;
  NondetRegLayout val;
};
struct NondetU16RegLayout {
  ArgU16Layout arg;
};
struct NormalizeU32Layout {
  NondetU16RegLayout low16;
  NondetRegLayout lowCarry;
  NondetU16RegLayout high16;
  NondetRegLayout highCarry;
};
struct MemoryArgLayout {
  NondetRegLayout count;
  NondetRegLayout addr;
  NondetRegLayout cycle;
  NondetRegLayout dataLow;
  NondetRegLayout dataHigh;
};
struct MemoryIOLayout {
  MemoryArgLayout oldTxn;
  MemoryArgLayout newTxn;
};
struct CycleArgLayout {
  NondetRegLayout count;
  NondetRegLayout cycle;
};
struct IsCycleLayout {
  CycleArgLayout arg;
};
struct IsForwardLayout {
  IsCycleLayout _0;
};
struct MemoryWriteLayout {
  MemoryIOLayout io;
  IsForwardLayout _0;
};
struct IsZeroLayout {
  NondetRegLayout _super;
  NondetRegLayout inv;
};
struct WriteRdLayout {
  IsZeroLayout isRd0;
  NondetRegLayout writeAddr;
  MemoryWriteLayout _0;
};
struct FinalizeMiscLayout {
  NormalizeU32Layout writeData;
  NormalizeU32Layout pcNorm;
  WriteRdLayout _0;
};
struct DoCycleTableLayout {
  CycleArgLayout arg1;
  CycleArgLayout arg2;
};
struct DecoderLayout {
  NondetRegLayout _f7_6;
  NondetRegLayout _f7_45;
  NondetRegLayout _f7_23;
  NondetRegLayout _f7_01;
  NondetRegLayout _rs2_34;
  NondetRegLayout _rs2_12;
  NondetRegLayout _rs2_0;
  NondetRegLayout _rs1_34;
  NondetRegLayout _rs1_12;
  NondetRegLayout _rs1_0;
  NondetRegLayout _f3_2;
  NondetRegLayout _f3_01;
  NondetRegLayout _rd_34;
  NondetRegLayout _rd_12;
  NondetRegLayout _rd_0;
  NondetRegLayout opcode;
};
struct AddrDecomposeLayout {
  NondetRegLayout low2;
  NondetU16RegLayout upperDiff;
  IsZeroLayout _0;
  NondetU16RegLayout med14;
};
struct MemoryReadLayout {
  MemoryIOLayout io;
  IsForwardLayout _0;
};
struct DecodeInstLayout {
  DecoderLayout _super;
  AddrDecomposeLayout pcAddr;
  MemoryReadLayout loadInst;
};
using MemoryArgLayout4LayoutArray = ::cuda::std::array<MemoryArgLayout,4>;
using CycleArgLayout2LayoutArray = ::cuda::std::array<CycleArgLayout,2>;
struct _Arguments_ReadSourceRegsSourceRegsLayout {
  MemoryArgLayout4LayoutArray memoryArg;
  CycleArgLayout2LayoutArray cycleArg;
};
struct ReadRegLayout {
  MemoryReadLayout _super;
  NondetRegLayout addr;
};
struct ReadSourceRegsSourceRegsArm0_SuperLayout {
  ReadRegLayout rboth;
};
struct ReadSourceRegsSourceRegsArm0Layout {
  ReadSourceRegsSourceRegsArm0_SuperLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  CycleArgLayout _extra2;
};
struct ReadSourceRegsSourceRegsArm1_SuperLayout {
  ReadRegLayout _0;
  ReadRegLayout _1;
};
struct ReadSourceRegsSourceRegsLayout {
  ReadSourceRegsSourceRegsArm0Layout arm0;
  ReadSourceRegsSourceRegsArm1_SuperLayout arm1;
};
struct ReadSourceRegsLayout {
  NondetRegLayout isSameReg;
  _Arguments_ReadSourceRegsSourceRegsLayout _arguments_ReadSourceRegsSourceRegs;
  ReadSourceRegsSourceRegsLayout sourceRegs;
  NondetRegLayout rs1Low;
  NondetRegLayout rs1High;
  NondetRegLayout rs2Low;
  NondetRegLayout rs2High;
};
struct MiscInputLayout {
  DecodeInstLayout decoded;
  ReadSourceRegsLayout sourceRegs;
};
using ArgU16Layout5LayoutArray = ::cuda::std::array<ArgU16Layout,5>;
struct _Arguments_Misc0MiscOutputLayout {
  ArgU16Layout5LayoutArray argU16;
};
struct Misc0MiscOutputArm0Layout {
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct Misc0MiscOutputArm1Layout {
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
using NondetRegLayout16LayoutArray = ::cuda::std::array<NondetRegLayout,16>;
struct ToBits_16_Layout {
  NondetRegLayout16LayoutArray _super;
};
struct BitwiseAndU16Layout {
  ToBits_16_Layout bitsX;
  ToBits_16_Layout bitsY;
};
struct BitwiseAndLayout {
  BitwiseAndU16Layout _0;
  BitwiseAndU16Layout _1;
};
struct BitwiseXorLayout {
  BitwiseAndLayout andXy;
};
struct OpXORLayout {
  BitwiseXorLayout _0;
};
struct Misc0MiscOutputArm2Layout {
  OpXORLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct BitwiseOrLayout {
  BitwiseAndLayout andXy;
};
struct OpORLayout {
  BitwiseOrLayout _0;
};
struct Misc0MiscOutputArm3Layout {
  OpORLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct OpANDLayout {
  BitwiseAndLayout _0;
};
struct Misc0MiscOutputArm4Layout {
  OpANDLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct GetSignU32Layout {
  NondetRegLayout _super;
  NondetU16RegLayout restTimesTwo;
};
struct CmpLessThanLayout {
  NormalizeU32Layout diff;
  GetSignU32Layout s1;
  GetSignU32Layout s2;
  GetSignU32Layout s3;
  NondetRegLayout overflow;
  NondetRegLayout isLessThan;
};
struct OpSLTLayout {
  CmpLessThanLayout cmp;
};
struct CmpLessThanUnsignedLayout {
  NormalizeU32Layout diff;
};
struct OpSLTULayout {
  CmpLessThanUnsignedLayout cmp;
};
struct Misc0MiscOutputArm6Layout {
  OpSLTULayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
};
struct Misc0MiscOutputArm7Layout {
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct Misc0MiscOutputLayout {
  Misc0MiscOutputArm0Layout arm0;
  Misc0MiscOutputArm1Layout arm1;
  Misc0MiscOutputArm2Layout arm2;
  Misc0MiscOutputArm3Layout arm3;
  Misc0MiscOutputArm4Layout arm4;
  OpSLTLayout arm5;
  Misc0MiscOutputArm6Layout arm6;
  Misc0MiscOutputArm7Layout arm7;
};
struct Misc0Layout {
  FinalizeMiscLayout _super;
  DoCycleTableLayout _0;
  MiscInputLayout input;
  _Arguments_Misc0MiscOutputLayout _arguments_Misc0MiscOutput;
  Misc0MiscOutputLayout miscOutput;
};
struct _Arguments_Misc1MiscOutputLayout {
  ArgU16Layout5LayoutArray argU16;
};
struct OpXORILayout {
  BitwiseXorLayout _0;
};
struct Misc1MiscOutputArm0Layout {
  OpXORILayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct OpORILayout {
  BitwiseOrLayout _0;
};
struct Misc1MiscOutputArm1Layout {
  OpORILayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct OpANDILayout {
  BitwiseAndLayout _0;
};
struct Misc1MiscOutputArm2Layout {
  OpANDILayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct OpSLTILayout {
  CmpLessThanLayout cmp;
};
struct OpSLTIULayout {
  CmpLessThanUnsignedLayout cmp;
};
struct Misc1MiscOutputArm4Layout {
  OpSLTIULayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
};
struct CmpEqualLayout {
  IsZeroLayout lowSame;
  IsZeroLayout highSame;
  NondetRegLayout isEqual;
};
struct OpBEQLayout {
  CmpEqualLayout cmp;
};
struct Misc1MiscOutputArm5Layout {
  OpBEQLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct OpBNELayout {
  CmpEqualLayout cmp;
};
struct Misc1MiscOutputArm6Layout {
  OpBNELayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct OpBLTLayout {
  CmpLessThanLayout cmp;
};
struct Misc1MiscOutputLayout {
  Misc1MiscOutputArm0Layout arm0;
  Misc1MiscOutputArm1Layout arm1;
  Misc1MiscOutputArm2Layout arm2;
  OpSLTILayout arm3;
  Misc1MiscOutputArm4Layout arm4;
  Misc1MiscOutputArm5Layout arm5;
  Misc1MiscOutputArm6Layout arm6;
  OpBLTLayout arm7;
};
struct Misc1Layout {
  FinalizeMiscLayout _super;
  DoCycleTableLayout _0;
  MiscInputLayout input;
  _Arguments_Misc1MiscOutputLayout _arguments_Misc1MiscOutput;
  Misc1MiscOutputLayout miscOutput;
};
struct _Arguments_Misc2MiscOutputLayout {
  ArgU16Layout5LayoutArray argU16;
};
struct OpBGELayout {
  CmpLessThanLayout cmp;
};
struct OpBLTULayout {
  CmpLessThanUnsignedLayout cmp;
};
struct Misc2MiscOutputArm1Layout {
  OpBLTULayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
};
struct OpBGEULayout {
  CmpLessThanUnsignedLayout cmp;
};
struct Misc2MiscOutputArm2Layout {
  OpBGEULayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
};
struct Misc2MiscOutputArm3Layout {
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct Misc2MiscOutputArm4Layout {
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct Misc2MiscOutputArm5Layout {
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct Misc2MiscOutputArm6Layout {
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct Misc2MiscOutputArm7Layout {
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
};
struct Misc2MiscOutputLayout {
  OpBGELayout arm0;
  Misc2MiscOutputArm1Layout arm1;
  Misc2MiscOutputArm2Layout arm2;
  Misc2MiscOutputArm3Layout arm3;
  Misc2MiscOutputArm4Layout arm4;
  Misc2MiscOutputArm5Layout arm5;
  Misc2MiscOutputArm6Layout arm6;
  Misc2MiscOutputArm7Layout arm7;
};
struct Misc2Layout {
  FinalizeMiscLayout _super;
  DoCycleTableLayout _0;
  MiscInputLayout input;
  _Arguments_Misc2MiscOutputLayout _arguments_Misc2MiscOutput;
  Misc2MiscOutputLayout miscOutput;
};
struct MulInputLayout {
  DecodeInstLayout decoded;
  ReadSourceRegsLayout sourceRegs;
};
using ArgU16Layout6LayoutArray = ::cuda::std::array<ArgU16Layout,6>;
struct ArgU8Layout {
  NondetRegLayout count;
  NondetRegLayout val;
};
using ArgU8Layout13LayoutArray = ::cuda::std::array<ArgU8Layout,13>;
struct _Arguments_Mul0MulOutputLayout {
  ArgU16Layout6LayoutArray argU16;
  ArgU8Layout13LayoutArray argU8;
};
using NondetRegLayout5LayoutArray = ::cuda::std::array<NondetRegLayout,5>;
struct ToBits_5_Layout {
  NondetRegLayout5LayoutArray _super;
};
struct DynPo2Layout {
  ToBits_5_Layout low5;
  NondetU16RegLayout checkU16;
  NondetRegLayout b3;
  NondetRegLayout low;
  NondetRegLayout high;
};
struct NondetU8RegLayout {
  ArgU8Layout arg;
};
struct ExpandU32Layout {
  NondetU8RegLayout b0;
  NondetU8RegLayout b1;
  NondetU8RegLayout b2;
  NondetU8RegLayout b3;
  NondetU8RegLayout b3Top7times2;
  NondetRegLayout topBit;
};
struct NondetFakeTwitRegLayout {
  NondetRegLayout reg0;
  NondetRegLayout reg1;
};
struct SplitTotalLayout {
  NondetU16RegLayout out;
  NondetU8RegLayout carryByte;
  NondetFakeTwitRegLayout carryExtra;
};
struct MultiplyAccumulateLayout {
  ExpandU32Layout ax;
  ExpandU32Layout bx;
  NondetRegLayout cSign;
  NondetU16RegLayout cRestTimes2;
  SplitTotalLayout s0;
  SplitTotalLayout s1;
  SplitTotalLayout s2;
  NondetU16RegLayout s3Out;
  NondetFakeTwitRegLayout s3Carry;
};
struct DoMulLayout {
  MultiplyAccumulateLayout mul;
};
struct OpSLLLayout {
  DynPo2Layout shiftMul;
  DoMulLayout _0;
};
struct OpSLLILayout {
  DynPo2Layout shiftMul;
  DoMulLayout _0;
};
struct OpMULLayout {
  DoMulLayout _0;
};
struct Mul0MulOutputArm2Layout {
  OpMULLayout _super;
  ArgU16Layout _extra0;
};
struct OpMULHLayout {
  DoMulLayout _0;
};
struct Mul0MulOutputArm3Layout {
  OpMULHLayout _super;
  ArgU16Layout _extra0;
};
struct OpMULHSULayout {
  DoMulLayout _0;
};
struct Mul0MulOutputArm4Layout {
  OpMULHSULayout _super;
  ArgU16Layout _extra0;
};
struct OpMULHULayout {
  DoMulLayout _0;
};
struct Mul0MulOutputArm5Layout {
  OpMULHULayout _super;
  ArgU16Layout _extra0;
};
struct Mul0MulOutputArm6Layout {
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
  ArgU16Layout _extra5;
  ArgU8Layout _extra6;
  ArgU8Layout _extra7;
  ArgU8Layout _extra8;
  ArgU8Layout _extra9;
  ArgU8Layout _extra10;
  ArgU8Layout _extra11;
  ArgU8Layout _extra12;
  ArgU8Layout _extra13;
  ArgU8Layout _extra14;
  ArgU8Layout _extra15;
  ArgU8Layout _extra16;
  ArgU8Layout _extra17;
  ArgU8Layout _extra18;
};
struct Mul0MulOutputArm7Layout {
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
  ArgU16Layout _extra5;
  ArgU8Layout _extra6;
  ArgU8Layout _extra7;
  ArgU8Layout _extra8;
  ArgU8Layout _extra9;
  ArgU8Layout _extra10;
  ArgU8Layout _extra11;
  ArgU8Layout _extra12;
  ArgU8Layout _extra13;
  ArgU8Layout _extra14;
  ArgU8Layout _extra15;
  ArgU8Layout _extra16;
  ArgU8Layout _extra17;
  ArgU8Layout _extra18;
};
struct Mul0MulOutputLayout {
  OpSLLLayout arm0;
  OpSLLILayout arm1;
  Mul0MulOutputArm2Layout arm2;
  Mul0MulOutputArm3Layout arm3;
  Mul0MulOutputArm4Layout arm4;
  Mul0MulOutputArm5Layout arm5;
  Mul0MulOutputArm6Layout arm6;
  Mul0MulOutputArm7Layout arm7;
};
struct Mul0Layout {
  DoCycleTableLayout _0;
  MulInputLayout input;
  _Arguments_Mul0MulOutputLayout _arguments_Mul0MulOutput;
  Mul0MulOutputLayout mulOutput;
  WriteRdLayout _1;
  NormalizeU32Layout pcAdd;
};
struct DivInputLayout {
  DecodeInstLayout decoded;
  ReadSourceRegsLayout sourceRegs;
};
using ArgU16Layout16LayoutArray = ::cuda::std::array<ArgU16Layout,16>;
struct _Arguments_Div0MulOutputLayout {
  ArgU16Layout16LayoutArray argU16;
  ArgU8Layout13LayoutArray argU8;
};
struct DoDivLayout {
  NondetRegLayout quotLow;
  NondetRegLayout quotHigh;
  NondetU16RegLayout remLow;
  NondetU16RegLayout remHigh;
  MultiplyAccumulateLayout mul;
  NondetRegLayout topBitType;
  NondetRegLayout topNum;
  NondetU16RegLayout _0;
  NormalizeU32Layout denomAbs;
  NormalizeU32Layout remNormal;
  NondetRegLayout isZero;
  NondetRegLayout signedOverflowCase;
  CmpLessThanUnsignedLayout lt;
};
struct OpSRLLayout {
  DynPo2Layout shiftMul;
  DoDivLayout _0;
};
struct Div0MulOutputArm0Layout {
  OpSRLLayout _super;
  ArgU16Layout _extra0;
};
struct TopBitLayout {
  NondetRegLayout _super;
  NondetU16RegLayout rest;
};
struct OpSRALayout {
  DynPo2Layout shiftMul;
  TopBitLayout flip;
  DoDivLayout _0;
};
struct OpSRLILayout {
  DynPo2Layout shiftMul;
  DoDivLayout _0;
};
struct Div0MulOutputArm2Layout {
  OpSRLILayout _super;
  ArgU16Layout _extra0;
};
struct OpSRAILayout {
  DynPo2Layout shiftMul;
  TopBitLayout flip;
  DoDivLayout _0;
};
struct OpDIVLayout {
  DoDivLayout _0;
};
struct Div0MulOutputArm4Layout {
  OpDIVLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
};
struct OpDIVULayout {
  DoDivLayout _0;
};
struct Div0MulOutputArm5Layout {
  OpDIVULayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
};
struct OpREMLayout {
  DoDivLayout _0;
};
struct Div0MulOutputArm6Layout {
  OpREMLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
};
struct OpREMULayout {
  DoDivLayout _0;
};
struct Div0MulOutputArm7Layout {
  OpREMULayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
};
struct Div0MulOutputLayout {
  Div0MulOutputArm0Layout arm0;
  OpSRALayout arm1;
  Div0MulOutputArm2Layout arm2;
  OpSRAILayout arm3;
  Div0MulOutputArm4Layout arm4;
  Div0MulOutputArm5Layout arm5;
  Div0MulOutputArm6Layout arm6;
  Div0MulOutputArm7Layout arm7;
};
struct Div0Layout {
  DoCycleTableLayout _0;
  DivInputLayout input;
  _Arguments_Div0MulOutputLayout _arguments_Div0MulOutput;
  Div0MulOutputLayout mulOutput;
  WriteRdLayout _1;
  NormalizeU32Layout pcAdd;
};
struct AddrDecomposeBitsLayout {
  NondetRegLayout low0;
  NondetRegLayout low1;
  NondetU16RegLayout upperDiff;
  IsZeroLayout _0;
  NondetU16RegLayout med14;
};
struct MemLoadInputLayout {
  DecodeInstLayout decoded;
  ReadRegLayout rs1;
  NormalizeU32Layout addrU32;
  AddrDecomposeBitsLayout addr;
  MemoryReadLayout data;
};
using ArgU8Layout3LayoutArray = ::cuda::std::array<ArgU8Layout,3>;
using ArgU16Layout1LayoutArray = ::cuda::std::array<ArgU16Layout,1>;
struct _Arguments_Mem0OutputLayout {
  ArgU8Layout3LayoutArray argU8;
  ArgU16Layout1LayoutArray argU16;
};
struct SplitWordLayout {
  NondetU8RegLayout byte0;
  NondetU8RegLayout byte1;
};
struct OpLBLayout {
  SplitWordLayout bytes;
  NondetRegLayout highBit;
  NondetU8RegLayout low7x2;
};
struct Mem0OutputArm0Layout {
  OpLBLayout _super;
  ArgU16Layout _extra0;
};
struct OpLHLayout {
  NondetRegLayout highBit;
  NondetU16RegLayout low15x2;
};
struct Mem0OutputArm1Layout {
  OpLHLayout _super;
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
};
struct Mem0OutputArm2Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU16Layout _extra3;
};
struct OpLBULayout {
  SplitWordLayout bytes;
};
struct Mem0OutputArm3Layout {
  OpLBULayout _super;
  ArgU8Layout _extra0;
  ArgU16Layout _extra1;
};
struct Mem0OutputArm4Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU16Layout _extra3;
};
struct Mem0OutputArm5Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU16Layout _extra3;
};
struct Mem0OutputArm6Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU16Layout _extra3;
};
struct Mem0OutputArm7Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU16Layout _extra3;
};
struct Mem0OutputLayout {
  Mem0OutputArm0Layout arm0;
  Mem0OutputArm1Layout arm1;
  Mem0OutputArm2Layout arm2;
  Mem0OutputArm3Layout arm3;
  Mem0OutputArm4Layout arm4;
  Mem0OutputArm5Layout arm5;
  Mem0OutputArm6Layout arm6;
  Mem0OutputArm7Layout arm7;
};
struct Mem0Layout {
  DoCycleTableLayout _0;
  MemLoadInputLayout input;
  _Arguments_Mem0OutputLayout _arguments_Mem0Output;
  Mem0OutputLayout output;
  WriteRdLayout _1;
  NormalizeU32Layout pcAdd;
};
struct MemStoreInputLayout {
  DecodeInstLayout decoded;
  ReadSourceRegsLayout sourceRegs;
  NormalizeU32Layout addrU32;
  AddrDecomposeBitsLayout addr;
  MemoryReadLayout data;
};
using ArgU8Layout4LayoutArray = ::cuda::std::array<ArgU8Layout,4>;
struct _Arguments_Mem1OutputLayout {
  ArgU8Layout4LayoutArray argU8;
};
struct OpSBLayout {
  SplitWordLayout origBytes;
  SplitWordLayout newBytes;
};
struct Mem1OutputArm1Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU8Layout _extra3;
};
struct Mem1OutputArm2Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU8Layout _extra3;
};
struct Mem1OutputArm3Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU8Layout _extra3;
};
struct Mem1OutputArm4Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU8Layout _extra3;
};
struct Mem1OutputArm5Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU8Layout _extra3;
};
struct Mem1OutputArm6Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU8Layout _extra3;
};
struct Mem1OutputArm7Layout {
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU8Layout _extra3;
};
struct Mem1OutputLayout {
  OpSBLayout arm0;
  Mem1OutputArm1Layout arm1;
  Mem1OutputArm2Layout arm2;
  Mem1OutputArm3Layout arm3;
  Mem1OutputArm4Layout arm4;
  Mem1OutputArm5Layout arm5;
  Mem1OutputArm6Layout arm6;
  Mem1OutputArm7Layout arm7;
};
struct MemStoreFinalizeLayout {
  MemoryWriteLayout _0;
};
struct Mem1Layout {
  DoCycleTableLayout _0;
  MemStoreInputLayout input;
  _Arguments_Mem1OutputLayout _arguments_Mem1Output;
  Mem1OutputLayout output;
  MemStoreFinalizeLayout _1;
  NormalizeU32Layout pcAdd;
};
struct MemoryPageInLayout {
  MemoryIOLayout io;
};
struct ControlLoadRoot__0_SuperLayout {
  MemoryPageInLayout mem;
};
using ControlLoadRoot__0_SuperLayout8LayoutArray = ::cuda::std::array<ControlLoadRoot__0_SuperLayout,8>;
struct ControlLoadRootLayout {
  ControlLoadRoot__0_SuperLayout8LayoutArray _1;
};
struct Control0_SuperArm0Layout {
  ControlLoadRootLayout _super;
  CycleArgLayout _extra0;
  CycleArgLayout _extra1;
  CycleArgLayout _extra2;
  CycleArgLayout _extra3;
  CycleArgLayout _extra4;
  CycleArgLayout _extra5;
  CycleArgLayout _extra6;
  CycleArgLayout _extra7;
  ArgU16Layout _extra8;
  ArgU16Layout _extra9;
  ArgU16Layout _extra10;
  ArgU16Layout _extra11;
  ArgU16Layout _extra12;
  ArgU16Layout _extra13;
  ArgU16Layout _extra14;
  ArgU16Layout _extra15;
  ArgU16Layout _extra16;
  ArgU16Layout _extra17;
  ArgU16Layout _extra18;
  ArgU16Layout _extra19;
  ArgU16Layout _extra20;
  ArgU16Layout _extra21;
  ArgU16Layout _extra22;
  ArgU16Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
  ArgU8Layout _extra26;
  ArgU8Layout _extra27;
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
  ArgU8Layout _extra32;
  ArgU8Layout _extra33;
  ArgU8Layout _extra34;
  ArgU8Layout _extra35;
  ArgU8Layout _extra36;
  ArgU8Layout _extra37;
  ArgU8Layout _extra38;
  ArgU8Layout _extra39;
};
struct ControlResume_SuperArm0_SuperLayout {
  MemoryReadLayout pc;
  MemoryReadLayout mode;
};
struct ControlResume_SuperArm0Layout {
  ControlResume_SuperArm0_SuperLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
  CycleArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
};
struct ControlResume_SuperArm1_Super__0_SuperLayout {
  MemoryWriteLayout _0;
};
using ControlResume_SuperArm1_Super__0_SuperLayout8LayoutArray = ::cuda::std::array<ControlResume_SuperArm1_Super__0_SuperLayout,8>;
struct ControlResume_SuperArm1_SuperLayout {
  ControlResume_SuperArm1_Super__0_SuperLayout8LayoutArray _1;
};
struct ControlResume_SuperLayout {
  ControlResume_SuperArm0Layout arm0;
  ControlResume_SuperArm1_SuperLayout arm1;
};
using MemoryArgLayout16LayoutArray = ::cuda::std::array<MemoryArgLayout,16>;
using CycleArgLayout8LayoutArray = ::cuda::std::array<CycleArgLayout,8>;
struct _Arguments_ControlResume_SuperLayout {
  MemoryArgLayout16LayoutArray memoryArg;
  CycleArgLayout8LayoutArray cycleArg;
};
struct ControlResumeLayout {
  ControlResume_SuperLayout _super;
  IsZeroLayout pcZero;
  _Arguments_ControlResume_SuperLayout _arguments_ControlResume_Super;
};
struct Control0_SuperArm1Layout {
  ControlResumeLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
  ArgU16Layout _extra5;
  ArgU16Layout _extra6;
  ArgU16Layout _extra7;
  ArgU16Layout _extra8;
  ArgU16Layout _extra9;
  ArgU16Layout _extra10;
  ArgU16Layout _extra11;
  ArgU16Layout _extra12;
  ArgU16Layout _extra13;
  ArgU16Layout _extra14;
  ArgU16Layout _extra15;
  ArgU8Layout _extra16;
  ArgU8Layout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
  ArgU8Layout _extra20;
  ArgU8Layout _extra21;
  ArgU8Layout _extra22;
  ArgU8Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
  ArgU8Layout _extra26;
  ArgU8Layout _extra27;
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
};
struct ControlUserECALLLayout {
  NondetRegLayout safeMode;
  AddrDecomposeBitsLayout pcAddr;
  MemoryReadLayout loadInst;
  MemoryReadLayout newPcAddr;
  MemoryWriteLayout _0;
};
struct Control0_SuperArm2Layout {
  ControlUserECALLLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  CycleArgLayout _extra10;
  CycleArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
  ArgU16Layout _extra15;
  ArgU16Layout _extra16;
  ArgU16Layout _extra17;
  ArgU16Layout _extra18;
  ArgU16Layout _extra19;
  ArgU16Layout _extra20;
  ArgU16Layout _extra21;
  ArgU16Layout _extra22;
  ArgU16Layout _extra23;
  ArgU16Layout _extra24;
  ArgU16Layout _extra25;
  ArgU16Layout _extra26;
  ArgU16Layout _extra27;
  ArgU16Layout _extra28;
  ArgU8Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
  ArgU8Layout _extra32;
  ArgU8Layout _extra33;
  ArgU8Layout _extra34;
  ArgU8Layout _extra35;
  ArgU8Layout _extra36;
  ArgU8Layout _extra37;
  ArgU8Layout _extra38;
  ArgU8Layout _extra39;
  ArgU8Layout _extra40;
  ArgU8Layout _extra41;
  ArgU8Layout _extra42;
  ArgU8Layout _extra43;
  ArgU8Layout _extra44;
};
struct ControlMRETLayout {
  NondetRegLayout safeMode;
  AddrDecomposeBitsLayout pcAddr;
  MemoryReadLayout loadInst;
  MemoryReadLayout pc;
  NormalizeU32Layout pcAdd;
};
struct Control0_SuperArm3Layout {
  ControlMRETLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
  CycleArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  ArgU16Layout _extra18;
  ArgU16Layout _extra19;
  ArgU16Layout _extra20;
  ArgU16Layout _extra21;
  ArgU16Layout _extra22;
  ArgU16Layout _extra23;
  ArgU16Layout _extra24;
  ArgU16Layout _extra25;
  ArgU16Layout _extra26;
  ArgU16Layout _extra27;
  ArgU16Layout _extra28;
  ArgU16Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
  ArgU8Layout _extra32;
  ArgU8Layout _extra33;
  ArgU8Layout _extra34;
  ArgU8Layout _extra35;
  ArgU8Layout _extra36;
  ArgU8Layout _extra37;
  ArgU8Layout _extra38;
  ArgU8Layout _extra39;
  ArgU8Layout _extra40;
  ArgU8Layout _extra41;
  ArgU8Layout _extra42;
  ArgU8Layout _extra43;
  ArgU8Layout _extra44;
  ArgU8Layout _extra45;
};
using MemoryReadLayout8LayoutArray = ::cuda::std::array<MemoryReadLayout,8>;
struct ControlSuspend_SuperArm0_SuperLayout {
  MemoryReadLayout8LayoutArray _1;
};
struct ControlSuspend_SuperArm1_SuperLayout {
  NondetRegLayout state;
  MemoryWriteLayout _0;
  MemoryWriteLayout _1;
};
struct ControlSuspend_SuperArm1Layout {
  ControlSuspend_SuperArm1_SuperLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
  CycleArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
};
struct ControlSuspend_SuperLayout {
  ControlSuspend_SuperArm0_SuperLayout arm0;
  ControlSuspend_SuperArm1Layout arm1;
};
struct _Arguments_ControlSuspend_SuperLayout {
  MemoryArgLayout16LayoutArray memoryArg;
  CycleArgLayout8LayoutArray cycleArg;
};
struct ControlSuspendLayout {
  ControlSuspend_SuperLayout _super;
  IsZeroLayout pcZero;
  _Arguments_ControlSuspend_SuperLayout _arguments_ControlSuspend_Super;
};
struct Control0_SuperArm4Layout {
  ControlSuspendLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
  ArgU16Layout _extra5;
  ArgU16Layout _extra6;
  ArgU16Layout _extra7;
  ArgU16Layout _extra8;
  ArgU16Layout _extra9;
  ArgU16Layout _extra10;
  ArgU16Layout _extra11;
  ArgU16Layout _extra12;
  ArgU16Layout _extra13;
  ArgU16Layout _extra14;
  ArgU16Layout _extra15;
  ArgU8Layout _extra16;
  ArgU8Layout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
  ArgU8Layout _extra20;
  ArgU8Layout _extra21;
  ArgU8Layout _extra22;
  ArgU8Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
  ArgU8Layout _extra26;
  ArgU8Layout _extra27;
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
};
struct MemoryPageOutLayout {
  MemoryIOLayout io;
  IsForwardLayout _0;
};
using MemoryPageOutLayout8LayoutArray = ::cuda::std::array<MemoryPageOutLayout,8>;
struct ControlStoreRootLayout {
  MemoryPageOutLayout8LayoutArray _1;
};
struct Control0_SuperArm5Layout {
  ControlStoreRootLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
  ArgU16Layout _extra5;
  ArgU16Layout _extra6;
  ArgU16Layout _extra7;
  ArgU16Layout _extra8;
  ArgU16Layout _extra9;
  ArgU16Layout _extra10;
  ArgU16Layout _extra11;
  ArgU16Layout _extra12;
  ArgU16Layout _extra13;
  ArgU16Layout _extra14;
  ArgU16Layout _extra15;
  ArgU8Layout _extra16;
  ArgU8Layout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
  ArgU8Layout _extra20;
  ArgU8Layout _extra21;
  ArgU8Layout _extra22;
  ArgU8Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
  ArgU8Layout _extra26;
  ArgU8Layout _extra27;
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
};
struct ControlTable_SuperArm0_Super__0_SuperLayout {
  ArgU16Layout arg;
};
using ControlTable_SuperArm0_Super__0_SuperLayout16LayoutArray = ::cuda::std::array<ControlTable_SuperArm0_Super__0_SuperLayout,16>;
struct ControlTable_SuperArm0_SuperLayout {
  ControlTable_SuperArm0_Super__0_SuperLayout16LayoutArray _1;
  IsZeroLayout done;
};
struct ControlTable_SuperArm0Layout {
  ControlTable_SuperArm0_SuperLayout _super;
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU8Layout _extra3;
  ArgU8Layout _extra4;
  ArgU8Layout _extra5;
  ArgU8Layout _extra6;
  ArgU8Layout _extra7;
  ArgU8Layout _extra8;
  ArgU8Layout _extra9;
  ArgU8Layout _extra10;
  ArgU8Layout _extra11;
  ArgU8Layout _extra12;
  ArgU8Layout _extra13;
  ArgU8Layout _extra14;
  ArgU8Layout _extra15;
};
struct ControlTable_SuperArm1_Super__0_SuperLayout {
  ArgU8Layout arg;
};
using ControlTable_SuperArm1_Super__0_SuperLayout16LayoutArray = ::cuda::std::array<ControlTable_SuperArm1_Super__0_SuperLayout,16>;
struct ControlTable_SuperArm1_SuperLayout {
  ControlTable_SuperArm1_Super__0_SuperLayout16LayoutArray _1;
  IsZeroLayout done;
};
struct ControlTable_SuperArm1Layout {
  ControlTable_SuperArm1_SuperLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
  ArgU16Layout _extra5;
  ArgU16Layout _extra6;
  ArgU16Layout _extra7;
  ArgU16Layout _extra8;
  ArgU16Layout _extra9;
  ArgU16Layout _extra10;
  ArgU16Layout _extra11;
  ArgU16Layout _extra12;
  ArgU16Layout _extra13;
  ArgU16Layout _extra14;
  ArgU16Layout _extra15;
};
struct ControlTable_SuperLayout {
  ControlTable_SuperArm0Layout arm0;
  ControlTable_SuperArm1Layout arm1;
};
using ArgU8Layout16LayoutArray = ::cuda::std::array<ArgU8Layout,16>;
struct _Arguments_ControlTable_SuperLayout {
  ArgU16Layout16LayoutArray argU16;
  ArgU8Layout16LayoutArray argU8;
};
struct ControlTableLayout {
  ControlTable_SuperLayout _super;
  NondetRegLayout entry;
  NondetRegLayout mode;
  _Arguments_ControlTable_SuperLayout _arguments_ControlTable_Super;
};
struct Control0_SuperArm6Layout {
  ControlTableLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  MemoryArgLayout _extra12;
  MemoryArgLayout _extra13;
  MemoryArgLayout _extra14;
  MemoryArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  CycleArgLayout _extra18;
  CycleArgLayout _extra19;
  CycleArgLayout _extra20;
  CycleArgLayout _extra21;
  CycleArgLayout _extra22;
  CycleArgLayout _extra23;
};
using CycleArgLayout1LayoutArray = ::cuda::std::array<CycleArgLayout,1>;
struct _Arguments_ControlDone__0Layout {
  CycleArgLayout1LayoutArray cycleArg;
};
struct ControlDone__0Arm0_SuperLayout {
  IsCycleLayout _0;
};
struct ControlDone__0Arm1Layout {
  CycleArgLayout _extra0;
};
struct ControlDone__0Layout {
  ControlDone__0Arm0_SuperLayout arm0;
  ControlDone__0Arm1Layout arm1;
};
struct ControlDoneLayout {
  _Arguments_ControlDone__0Layout _arguments_ControlDone__0;
  ControlDone__0Layout _2;
};
struct Control0_SuperArm7Layout {
  ControlDoneLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  MemoryArgLayout _extra12;
  MemoryArgLayout _extra13;
  MemoryArgLayout _extra14;
  MemoryArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  CycleArgLayout _extra18;
  CycleArgLayout _extra19;
  CycleArgLayout _extra20;
  CycleArgLayout _extra21;
  CycleArgLayout _extra22;
  ArgU16Layout _extra23;
  ArgU16Layout _extra24;
  ArgU16Layout _extra25;
  ArgU16Layout _extra26;
  ArgU16Layout _extra27;
  ArgU16Layout _extra28;
  ArgU16Layout _extra29;
  ArgU16Layout _extra30;
  ArgU16Layout _extra31;
  ArgU16Layout _extra32;
  ArgU16Layout _extra33;
  ArgU16Layout _extra34;
  ArgU16Layout _extra35;
  ArgU16Layout _extra36;
  ArgU16Layout _extra37;
  ArgU16Layout _extra38;
  ArgU8Layout _extra39;
  ArgU8Layout _extra40;
  ArgU8Layout _extra41;
  ArgU8Layout _extra42;
  ArgU8Layout _extra43;
  ArgU8Layout _extra44;
  ArgU8Layout _extra45;
  ArgU8Layout _extra46;
  ArgU8Layout _extra47;
  ArgU8Layout _extra48;
  ArgU8Layout _extra49;
  ArgU8Layout _extra50;
  ArgU8Layout _extra51;
  ArgU8Layout _extra52;
  ArgU8Layout _extra53;
  ArgU8Layout _extra54;
};
struct Control0_SuperLayout {
  Control0_SuperArm0Layout arm0;
  Control0_SuperArm1Layout arm1;
  Control0_SuperArm2Layout arm2;
  Control0_SuperArm3Layout arm3;
  Control0_SuperArm4Layout arm4;
  Control0_SuperArm5Layout arm5;
  Control0_SuperArm6Layout arm6;
  Control0_SuperArm7Layout arm7;
};
struct _Arguments_Control0_SuperLayout {
  MemoryArgLayout16LayoutArray memoryArg;
  CycleArgLayout8LayoutArray cycleArg;
  ArgU16Layout16LayoutArray argU16;
  ArgU8Layout16LayoutArray argU8;
};
struct Control0Layout {
  Control0_SuperLayout _super;
  DoCycleTableLayout _0;
  _Arguments_Control0_SuperLayout _arguments_Control0_Super;
};
using MemoryArgLayout8LayoutArray = ::cuda::std::array<MemoryArgLayout,8>;
using CycleArgLayout4LayoutArray = ::cuda::std::array<CycleArgLayout,4>;
using ArgU16Layout4LayoutArray = ::cuda::std::array<ArgU16Layout,4>;
struct _Arguments_ECall0OutputLayout {
  MemoryArgLayout8LayoutArray memoryArg;
  CycleArgLayout4LayoutArray cycleArg;
  ArgU16Layout4LayoutArray argU16;
  ArgU8Layout4LayoutArray argU8;
};
using NondetRegLayout6LayoutArray = ::cuda::std::array<NondetRegLayout,6>;
struct OneHot_6_Layout {
  NondetRegLayout6LayoutArray _super;
};
struct MachineECallLayout {
  MemoryReadLayout loadInst;
  MemoryReadLayout dispatchIdx;
  OneHot_6_Layout dispatch;
};
struct ECall0OutputArm0Layout {
  MachineECallLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  CycleArgLayout _extra4;
  CycleArgLayout _extra5;
  ArgU16Layout _extra6;
  ArgU16Layout _extra7;
  ArgU16Layout _extra8;
  ArgU16Layout _extra9;
  ArgU8Layout _extra10;
  ArgU8Layout _extra11;
  ArgU8Layout _extra12;
  ArgU8Layout _extra13;
};
struct ECallTerminateLayout {
  MemoryReadLayout a0;
  MemoryReadLayout a1;
};
struct ECall0OutputArm1Layout {
  ECallTerminateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  CycleArgLayout _extra4;
  CycleArgLayout _extra5;
  ArgU16Layout _extra6;
  ArgU16Layout _extra7;
  ArgU16Layout _extra8;
  ArgU16Layout _extra9;
  ArgU8Layout _extra10;
  ArgU8Layout _extra11;
  ArgU8Layout _extra12;
  ArgU8Layout _extra13;
};
using NondetRegLayout4LayoutArray = ::cuda::std::array<NondetRegLayout,4>;
struct OneHot_4_Layout {
  NondetRegLayout4LayoutArray _super;
};
struct DecomposeLow2Layout {
  NondetU16RegLayout high;
  NondetRegLayout low2;
  OneHot_4_Layout low2Hot;
  IsZeroLayout highZero;
  NondetRegLayout isZero;
};
struct ECallHostReadSetupLayout {
  MemoryReadLayout fd;
  MemoryReadLayout ptr;
  MemoryReadLayout len;
  NondetU16RegLayout newLen;
  NondetU16RegLayout diff;
  MemoryWriteLayout _0;
  DecomposeLow2Layout ptrDecomp;
  DecomposeLow2Layout lenDecomp;
  NondetRegLayout len123;
  NondetRegLayout uneven;
};
struct ECall0OutputArm2Layout {
  ECallHostReadSetupLayout _super;
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
  ArgU8Layout _extra2;
  ArgU8Layout _extra3;
};
struct ECallHostWriteLayout {
  MemoryReadLayout fd;
  MemoryReadLayout ptr;
  MemoryReadLayout len;
  NondetU16RegLayout newLen;
  NondetU16RegLayout diff;
  MemoryWriteLayout _0;
};
struct ECall0OutputArm3Layout {
  ECallHostWriteLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU8Layout _extra2;
  ArgU8Layout _extra3;
  ArgU8Layout _extra4;
  ArgU8Layout _extra5;
};
struct MemoryWriteUnconstrainedLayout {
  MemoryIOLayout io;
  IsForwardLayout _0;
};
struct ECallHostReadBytesLayout {
  DecomposeLow2Layout lenDecomp;
  NondetRegLayout len123;
  IsZeroLayout nextPtrEven;
  NondetRegLayout uneven;
  IsZeroLayout lenZero;
  NondetRegLayout low0;
  NondetRegLayout low1;
  MemoryReadLayout origWord;
  MemoryWriteUnconstrainedLayout _0;
  SplitWordLayout oldBytes;
  SplitWordLayout newBytes_0;
};
struct ECall0OutputArm4Layout {
  ECallHostReadBytesLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  CycleArgLayout _extra4;
  CycleArgLayout _extra5;
  ArgU16Layout _extra6;
  ArgU16Layout _extra7;
  ArgU16Layout _extra8;
};
struct ECallHostReadWords__0_SuperLayout {
  NondetRegLayout addr;
  MemoryWriteUnconstrainedLayout _0;
};
using ECallHostReadWords__0_SuperLayout4LayoutArray = ::cuda::std::array<ECallHostReadWords__0_SuperLayout,4>;
struct ECallHostReadWordsLayout {
  DecomposeLow2Layout lenDecomp;
  DecomposeLow2Layout wordsDecomp;
  ECallHostReadWords__0_SuperLayout4LayoutArray _1;
  IsZeroLayout newLenHighZero;
  NondetRegLayout lenZero;
};
struct ECall0OutputArm5Layout {
  ECallHostReadWordsLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU8Layout _extra2;
  ArgU8Layout _extra3;
  ArgU8Layout _extra4;
  ArgU8Layout _extra5;
};
struct ECall0OutputArm6Layout {
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  CycleArgLayout _extra8;
  CycleArgLayout _extra9;
  CycleArgLayout _extra10;
  CycleArgLayout _extra11;
  ArgU16Layout _extra12;
  ArgU16Layout _extra13;
  ArgU16Layout _extra14;
  ArgU16Layout _extra15;
  ArgU8Layout _extra16;
  ArgU8Layout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
};
struct ECall0OutputArm7Layout {
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  CycleArgLayout _extra8;
  CycleArgLayout _extra9;
  CycleArgLayout _extra10;
  CycleArgLayout _extra11;
  ArgU16Layout _extra12;
  ArgU16Layout _extra13;
  ArgU16Layout _extra14;
  ArgU16Layout _extra15;
  ArgU8Layout _extra16;
  ArgU8Layout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
};
struct ECall0OutputLayout {
  ECall0OutputArm0Layout arm0;
  ECall0OutputArm1Layout arm1;
  ECall0OutputArm2Layout arm2;
  ECall0OutputArm3Layout arm3;
  ECall0OutputArm4Layout arm4;
  ECall0OutputArm5Layout arm5;
  ECall0OutputArm6Layout arm6;
  ECall0OutputArm7Layout arm7;
};
struct ECall0Layout {
  NondetRegLayout s0;
  NondetRegLayout s1;
  NondetRegLayout s2;
  DoCycleTableLayout _0;
  AddrDecomposeBitsLayout pcAddr;
  _Arguments_ECall0OutputLayout _arguments_ECall0Output;
  ECall0OutputLayout output;
  IsZeroLayout isSuspend;
  IsZeroLayout isDecode;
  IsZeroLayout isP2Entry;
  IsZeroLayout isShaEcall;
  IsZeroLayout isBigIntEcall;
  NormalizeU32Layout addPC;
};
using NondetRegLayout24LayoutArray = ::cuda::std::array<NondetRegLayout,24>;
struct PoseidonStateLayout {
  NondetRegLayout hasState;
  NondetRegLayout stateAddr;
  NondetRegLayout bufOutAddr;
  NondetRegLayout isElem;
  NondetRegLayout checkOut;
  NondetRegLayout loadTxType;
  NondetRegLayout nextState;
  NondetRegLayout subState;
  NondetRegLayout bufInAddr;
  NondetRegLayout count;
  NondetRegLayout mode;
  NondetRegLayout24LayoutArray inner;
  NondetExtRegLayout zcheck;
};
using ArgU16Layout24LayoutArray = ::cuda::std::array<ArgU16Layout,24>;
using ArgU8Layout2LayoutArray = ::cuda::std::array<ArgU8Layout,2>;
struct _Arguments_Poseidon0StateLayout {
  MemoryArgLayout16LayoutArray memoryArg;
  CycleArgLayout8LayoutArray cycleArg;
  ArgU16Layout24LayoutArray argU16;
  ArgU8Layout2LayoutArray argU8;
};
struct PoseidonEntry_SuperArm0Layout {
  PoseidonStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  CycleArgLayout _extra8;
  CycleArgLayout _extra9;
  CycleArgLayout _extra10;
  CycleArgLayout _extra11;
};
struct ReadAddrLayout {
  MemoryReadLayout addr32;
};
struct PoseidonEcallLayout {
  PoseidonStateLayout _super;
  ReadAddrLayout stateAddr;
  ReadAddrLayout bufInAddr;
  ReadAddrLayout bufOutAddr;
  MemoryReadLayout bitsAndCount;
  IsZeroLayout _0;
  NondetRegLayout isElem;
  NondetRegLayout checkOut;
  IsZeroLayout countZero;
};
struct PoseidonEntry_SuperLayout {
  PoseidonStateLayout _super;
  PoseidonEntry_SuperArm0Layout arm0;
  PoseidonEcallLayout arm1;
};
struct _Arguments_PoseidonEntry_SuperLayout {
  MemoryArgLayout8LayoutArray memoryArg;
  CycleArgLayout4LayoutArray cycleArg;
};
struct PoseidonEntryLayout {
  PoseidonEntry_SuperLayout _super;
  IsZeroLayout pcZero;
  _Arguments_PoseidonEntry_SuperLayout _arguments_PoseidonEntry_Super;
};
struct Poseidon0StateArm0Layout {
  PoseidonEntryLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  CycleArgLayout _extra8;
  CycleArgLayout _extra9;
  CycleArgLayout _extra10;
  CycleArgLayout _extra11;
  ArgU16Layout _extra12;
  ArgU16Layout _extra13;
  ArgU16Layout _extra14;
  ArgU16Layout _extra15;
  ArgU16Layout _extra16;
  ArgU16Layout _extra17;
  ArgU16Layout _extra18;
  ArgU16Layout _extra19;
  ArgU16Layout _extra20;
  ArgU16Layout _extra21;
  ArgU16Layout _extra22;
  ArgU16Layout _extra23;
  ArgU16Layout _extra24;
  ArgU16Layout _extra25;
  ArgU16Layout _extra26;
  ArgU16Layout _extra27;
  ArgU16Layout _extra28;
  ArgU16Layout _extra29;
  ArgU16Layout _extra30;
  ArgU16Layout _extra31;
  ArgU16Layout _extra32;
  ArgU16Layout _extra33;
  ArgU16Layout _extra34;
  ArgU16Layout _extra35;
  ArgU8Layout _extra36;
  ArgU8Layout _extra37;
};
struct ReadElemLayout {
  MemoryReadLayout elem32;
};
using ReadElemLayout8LayoutArray = ::cuda::std::array<ReadElemLayout,8>;
struct PoseidonLoadStateLayout {
  PoseidonStateLayout _super;
  ReadElemLayout8LayoutArray loadList;
};
struct Poseidon0StateArm1Layout {
  PoseidonLoadStateLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
  ArgU16Layout _extra5;
  ArgU16Layout _extra6;
  ArgU16Layout _extra7;
  ArgU16Layout _extra8;
  ArgU16Layout _extra9;
  ArgU16Layout _extra10;
  ArgU16Layout _extra11;
  ArgU16Layout _extra12;
  ArgU16Layout _extra13;
  ArgU16Layout _extra14;
  ArgU16Layout _extra15;
  ArgU16Layout _extra16;
  ArgU16Layout _extra17;
  ArgU16Layout _extra18;
  ArgU16Layout _extra19;
  ArgU16Layout _extra20;
  ArgU16Layout _extra21;
  ArgU16Layout _extra22;
  ArgU16Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
};
using NondetRegLayout3LayoutArray = ::cuda::std::array<NondetRegLayout,3>;
struct OneHot_3_Layout {
  NondetRegLayout3LayoutArray _super;
};
struct MemoryGet_SuperArm1Layout {
  MemoryPageInLayout _super;
  CycleArgLayout _extra0;
};
struct MemoryGet_SuperLayout {
  MemoryReadLayout arm0;
  MemoryGet_SuperArm1Layout arm1;
  MemoryPageOutLayout arm2;
};
using MemoryArgLayout2LayoutArray = ::cuda::std::array<MemoryArgLayout,2>;
struct _Arguments_MemoryGet_SuperLayout {
  MemoryArgLayout2LayoutArray memoryArg;
  CycleArgLayout1LayoutArray cycleArg;
};
struct MemoryGetLayout {
  MemoryGet_SuperLayout _super;
  _Arguments_MemoryGet_SuperLayout _arguments_MemoryGet_Super;
};
using MemoryGetLayout8LayoutArray = ::cuda::std::array<MemoryGetLayout,8>;
struct PoseidonLoadInShortLayout {
  PoseidonStateLayout _super;
  OneHot_3_Layout txType;
  MemoryGetLayout8LayoutArray loadList;
};
struct PoseidonLoadInLowLayout {
  PoseidonStateLayout _super;
  OneHot_3_Layout txType;
  MemoryGetLayout8LayoutArray loadList;
};
struct PoseidonLoadInHighLayout {
  PoseidonStateLayout _super;
  OneHot_3_Layout txType;
  MemoryGetLayout8LayoutArray loadList;
};
struct PoseidonLoadIn_SuperLayout {
  PoseidonStateLayout _super;
  PoseidonLoadInShortLayout arm0;
  PoseidonLoadInLowLayout arm1;
  PoseidonLoadInHighLayout arm2;
};
struct _Arguments_PoseidonLoadIn_SuperLayout {
  MemoryArgLayout16LayoutArray memoryArg;
  CycleArgLayout8LayoutArray cycleArg;
};
struct PoseidonLoadInLayout {
  PoseidonLoadIn_SuperLayout _super;
  OneHot_3_Layout _0;
  _Arguments_PoseidonLoadIn_SuperLayout _arguments_PoseidonLoadIn_Super;
};
struct Poseidon0StateArm2Layout {
  PoseidonLoadInLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
  ArgU16Layout _extra5;
  ArgU16Layout _extra6;
  ArgU16Layout _extra7;
  ArgU16Layout _extra8;
  ArgU16Layout _extra9;
  ArgU16Layout _extra10;
  ArgU16Layout _extra11;
  ArgU16Layout _extra12;
  ArgU16Layout _extra13;
  ArgU16Layout _extra14;
  ArgU16Layout _extra15;
  ArgU16Layout _extra16;
  ArgU16Layout _extra17;
  ArgU16Layout _extra18;
  ArgU16Layout _extra19;
  ArgU16Layout _extra20;
  ArgU16Layout _extra21;
  ArgU16Layout _extra22;
  ArgU16Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
};
struct Poseidon0StateArm3Layout {
  PoseidonStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  MemoryArgLayout _extra12;
  MemoryArgLayout _extra13;
  MemoryArgLayout _extra14;
  MemoryArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  CycleArgLayout _extra18;
  CycleArgLayout _extra19;
  CycleArgLayout _extra20;
  CycleArgLayout _extra21;
  CycleArgLayout _extra22;
  CycleArgLayout _extra23;
  ArgU16Layout _extra24;
  ArgU16Layout _extra25;
  ArgU16Layout _extra26;
  ArgU16Layout _extra27;
  ArgU16Layout _extra28;
  ArgU16Layout _extra29;
  ArgU16Layout _extra30;
  ArgU16Layout _extra31;
  ArgU16Layout _extra32;
  ArgU16Layout _extra33;
  ArgU16Layout _extra34;
  ArgU16Layout _extra35;
  ArgU16Layout _extra36;
  ArgU16Layout _extra37;
  ArgU16Layout _extra38;
  ArgU16Layout _extra39;
  ArgU16Layout _extra40;
  ArgU16Layout _extra41;
  ArgU16Layout _extra42;
  ArgU16Layout _extra43;
  ArgU16Layout _extra44;
  ArgU16Layout _extra45;
  ArgU16Layout _extra46;
  ArgU16Layout _extra47;
  ArgU8Layout _extra48;
  ArgU8Layout _extra49;
};
struct Poseidon0StateArm4Layout {
  PoseidonStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  MemoryArgLayout _extra12;
  MemoryArgLayout _extra13;
  MemoryArgLayout _extra14;
  MemoryArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  CycleArgLayout _extra18;
  CycleArgLayout _extra19;
  CycleArgLayout _extra20;
  CycleArgLayout _extra21;
  CycleArgLayout _extra22;
  CycleArgLayout _extra23;
  ArgU16Layout _extra24;
  ArgU16Layout _extra25;
  ArgU16Layout _extra26;
  ArgU16Layout _extra27;
  ArgU16Layout _extra28;
  ArgU16Layout _extra29;
  ArgU16Layout _extra30;
  ArgU16Layout _extra31;
  ArgU16Layout _extra32;
  ArgU16Layout _extra33;
  ArgU16Layout _extra34;
  ArgU16Layout _extra35;
  ArgU16Layout _extra36;
  ArgU16Layout _extra37;
  ArgU16Layout _extra38;
  ArgU16Layout _extra39;
  ArgU16Layout _extra40;
  ArgU16Layout _extra41;
  ArgU16Layout _extra42;
  ArgU16Layout _extra43;
  ArgU16Layout _extra44;
  ArgU16Layout _extra45;
  ArgU16Layout _extra46;
  ArgU16Layout _extra47;
  ArgU8Layout _extra48;
  ArgU8Layout _extra49;
};
struct PoseidonCheckOut__0_SuperLayout {
  ReadElemLayout goal;
};
using PoseidonCheckOut__0_SuperLayout8LayoutArray = ::cuda::std::array<PoseidonCheckOut__0_SuperLayout,8>;
struct PoseidonCheckOutLayout {
  PoseidonStateLayout _super;
  PoseidonCheckOut__0_SuperLayout8LayoutArray _1;
  IsZeroLayout isNormal;
};
struct PoseidonDoOut_SuperArm0Layout {
  PoseidonCheckOutLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  ArgU16Layout _extra2;
  ArgU16Layout _extra3;
  ArgU16Layout _extra4;
  ArgU16Layout _extra5;
  ArgU16Layout _extra6;
  ArgU16Layout _extra7;
  ArgU16Layout _extra8;
  ArgU16Layout _extra9;
  ArgU16Layout _extra10;
  ArgU16Layout _extra11;
  ArgU16Layout _extra12;
  ArgU16Layout _extra13;
  ArgU16Layout _extra14;
  ArgU16Layout _extra15;
  ArgU16Layout _extra16;
  ArgU16Layout _extra17;
  ArgU16Layout _extra18;
  ArgU16Layout _extra19;
  ArgU16Layout _extra20;
  ArgU16Layout _extra21;
  ArgU16Layout _extra22;
  ArgU16Layout _extra23;
};
struct _Arguments_FieldToWord__0Layout {
  ArgU16Layout1LayoutArray argU16;
};
struct FieldToWord__0Arm0_SuperLayout {
  NondetU16RegLayout _0;
};
struct FieldToWord__0Arm1_SuperLayout {
  NondetU16RegLayout _0;
};
struct FieldToWord__0Layout {
  FieldToWord__0Arm0_SuperLayout arm0;
  FieldToWord__0Arm1_SuperLayout arm1;
};
struct FieldToWordLayout {
  NondetU16RegLayout low;
  NondetU16RegLayout high;
  NondetRegLayout lowIsZero;
  _Arguments_FieldToWord__0Layout _arguments_FieldToWord__0;
  FieldToWord__0Layout _2;
};
struct PoseidonStoreOut__0_SuperLayout {
  FieldToWordLayout ftw;
  MemoryWriteLayout mw;
};
using PoseidonStoreOut__0_SuperLayout8LayoutArray = ::cuda::std::array<PoseidonStoreOut__0_SuperLayout,8>;
struct PoseidonStoreOutLayout {
  PoseidonStateLayout _super;
  PoseidonStoreOut__0_SuperLayout8LayoutArray _1;
  IsZeroLayout isNormal;
  NondetExtRegLayout extInv;
};
struct PoseidonDoOut_SuperLayout {
  PoseidonStateLayout _super;
  PoseidonDoOut_SuperArm0Layout arm0;
  PoseidonStoreOutLayout arm1;
};
struct _Arguments_PoseidonDoOut_SuperLayout {
  MemoryArgLayout16LayoutArray memoryArg;
  CycleArgLayout8LayoutArray cycleArg;
  ArgU16Layout24LayoutArray argU16;
};
struct PoseidonDoOutLayout {
  PoseidonDoOut_SuperLayout _super;
  _Arguments_PoseidonDoOut_SuperLayout _arguments_PoseidonDoOut_Super;
};
struct Poseidon0StateArm5Layout {
  PoseidonDoOutLayout _super;
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
};
struct PoseidonPaging_SuperLayout {
  PoseidonStateLayout _super;
  PoseidonStateLayout arm0;
  PoseidonStateLayout arm1;
  PoseidonStateLayout arm2;
  PoseidonStateLayout arm3;
  PoseidonStateLayout arm4;
  PoseidonStateLayout arm5;
};
struct IsU24Layout {
  NondetU16RegLayout low16;
  NondetU8RegLayout _0;
};
using ArgU8Layout1LayoutArray = ::cuda::std::array<ArgU8Layout,1>;
struct _Arguments_PoseidonPaging__1Layout {
  ArgU16Layout1LayoutArray argU16;
  ArgU8Layout1LayoutArray argU8;
};
struct PoseidonPaging__1Arm0_SuperLayout {
  IsU24Layout _0;
};
struct PoseidonPaging__1Arm1_SuperLayout {
  IsU24Layout _0;
};
struct PoseidonPaging__1Layout {
  PoseidonPaging__1Arm0_SuperLayout arm0;
  PoseidonPaging__1Arm1_SuperLayout arm1;
};
struct PoseidonPagingLayout {
  PoseidonPaging_SuperLayout _super;
  NondetRegLayout curIdx;
  NondetRegLayout curMode;
  OneHot_6_Layout modeSplit;
  IsU24Layout _0;
  _Arguments_PoseidonPaging__1Layout _arguments_PoseidonPaging__1;
  PoseidonPaging__1Layout _3;
  NondetRegLayout _4;
};
struct Poseidon0StateArm6Layout {
  PoseidonPagingLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  MemoryArgLayout _extra12;
  MemoryArgLayout _extra13;
  MemoryArgLayout _extra14;
  MemoryArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  CycleArgLayout _extra18;
  CycleArgLayout _extra19;
  CycleArgLayout _extra20;
  CycleArgLayout _extra21;
  CycleArgLayout _extra22;
  CycleArgLayout _extra23;
  ArgU16Layout _extra24;
  ArgU16Layout _extra25;
  ArgU16Layout _extra26;
  ArgU16Layout _extra27;
  ArgU16Layout _extra28;
  ArgU16Layout _extra29;
  ArgU16Layout _extra30;
  ArgU16Layout _extra31;
  ArgU16Layout _extra32;
  ArgU16Layout _extra33;
  ArgU16Layout _extra34;
  ArgU16Layout _extra35;
  ArgU16Layout _extra36;
  ArgU16Layout _extra37;
  ArgU16Layout _extra38;
  ArgU16Layout _extra39;
  ArgU16Layout _extra40;
  ArgU16Layout _extra41;
  ArgU16Layout _extra42;
  ArgU16Layout _extra43;
  ArgU16Layout _extra44;
  ArgU16Layout _extra45;
};
struct PoseidonStoreState__0_SuperLayout {
  FieldToWordLayout ftw;
  MemoryWriteLayout mw;
};
using PoseidonStoreState__0_SuperLayout8LayoutArray = ::cuda::std::array<PoseidonStoreState__0_SuperLayout,8>;
struct PoseidonStoreStateLayout {
  PoseidonStateLayout _super;
  PoseidonStoreState__0_SuperLayout8LayoutArray _1;
};
struct Poseidon0StateArm7Layout {
  PoseidonStoreStateLayout _super;
  ArgU8Layout _extra0;
  ArgU8Layout _extra1;
};
struct Poseidon0StateLayout {
  PoseidonStateLayout _super;
  Poseidon0StateArm0Layout arm0;
  Poseidon0StateArm1Layout arm1;
  Poseidon0StateArm2Layout arm2;
  Poseidon0StateArm3Layout arm3;
  Poseidon0StateArm4Layout arm4;
  Poseidon0StateArm5Layout arm5;
  Poseidon0StateArm6Layout arm6;
  Poseidon0StateArm7Layout arm7;
};
struct Poseidon0Layout {
  DoCycleTableLayout _0;
  PoseidonStateLayout state;
  _Arguments_Poseidon0StateLayout _arguments_Poseidon0State;
  Poseidon0StateLayout stateRedef;
};
struct SBoxLayout {
  NondetRegLayout _super;
  NondetRegLayout cubed;
};
using SBoxLayout24LayoutArray = ::cuda::std::array<SBoxLayout,24>;
struct DoExtRoundLayout {
  SBoxLayout24LayoutArray _1;
};
struct DoExtRoundByIdxLayout {
  DoExtRoundLayout _super;
  OneHot_8_Layout idxHot;
};
struct PoseidonExtRoundLayout {
  PoseidonStateLayout _super;
  IsZeroLayout isRound3;
  IsZeroLayout isRound7;
  IsZeroLayout lastBlock;
  DoExtRoundByIdxLayout nextInner;
};
struct DoIntRoundLayout {
  SBoxLayout sbox;
};
using DoIntRoundLayout21LayoutArray = ::cuda::std::array<DoIntRoundLayout,21>;
struct DoIntRoundsLayout {
  DoIntRoundLayout21LayoutArray _super;
};
struct PoseidonIntRoundsLayout {
  PoseidonStateLayout _super;
  DoIntRoundsLayout nextInner;
};
struct Poseidon1StateLayout {
  PoseidonStateLayout _super;
  PoseidonExtRoundLayout arm0;
  PoseidonIntRoundsLayout arm1;
  PoseidonStateLayout arm2;
  PoseidonStateLayout arm3;
  PoseidonStateLayout arm4;
  PoseidonStateLayout arm5;
  PoseidonStateLayout arm6;
  PoseidonStateLayout arm7;
};
struct Poseidon1Layout {
  DoCycleTableLayout _0;
  PoseidonStateLayout state;
  Poseidon1StateLayout stateRedef;
};
using NondetRegLayout32LayoutArray = ::cuda::std::array<NondetRegLayout,32>;
struct ShaStateLayout {
  NondetRegLayout stateInAddr;
  NondetRegLayout stateOutAddr;
  NondetRegLayout dataAddr;
  NondetRegLayout count;
  NondetRegLayout kAddr;
  NondetRegLayout round;
  NondetRegLayout nextState;
  NondetRegLayout32LayoutArray a;
  NondetRegLayout32LayoutArray e;
  NondetRegLayout32LayoutArray w;
};
using MemoryArgLayout10LayoutArray = ::cuda::std::array<MemoryArgLayout,10>;
using CycleArgLayout5LayoutArray = ::cuda::std::array<CycleArgLayout,5>;
struct _Arguments_Sha0StateLayout {
  MemoryArgLayout10LayoutArray memoryArg;
  CycleArgLayout5LayoutArray cycleArg;
};
struct ShaEcallLayout {
  ShaStateLayout _super;
  ReadAddrLayout stateInAddr;
  ReadAddrLayout stateOutAddr;
  ReadAddrLayout dataAddr;
  MemoryReadLayout _0;
  ReadAddrLayout kAddr;
};
struct ShaLoadStateLayout {
  ShaStateLayout _super;
  IsZeroLayout lastRound;
  IsZeroLayout countZero;
  MemoryReadLayout a32;
  MemoryReadLayout e32;
  MemoryWriteLayout _0;
  MemoryWriteLayout _1;
};
struct Sha0StateArm1Layout {
  ShaLoadStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  CycleArgLayout _extra2;
};
struct UnpackReg_32__16_Layout {
  NondetRegLayout32LayoutArray _super;
};
struct CarryExtractLayout {
  NondetRegLayout bit0;
  NondetRegLayout bit1;
  NondetRegLayout bit2;
};
struct CarryAndExpandLayout {
  UnpackReg_32__16_Layout _super;
  CarryExtractLayout lowCarry;
  CarryExtractLayout highCarry;
};
struct ShaLoadDataLayout {
  ShaStateLayout _super;
  IsZeroLayout lastRound;
  MemoryReadLayout k;
  MemoryReadLayout wMem;
  NondetRegLayout32LayoutArray wBits;
  CarryAndExpandLayout a;
  CarryAndExpandLayout e;
};
struct Sha0StateArm2Layout {
  ShaLoadDataLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  CycleArgLayout _extra6;
  CycleArgLayout _extra7;
  CycleArgLayout _extra8;
};
struct ShaMixLayout {
  ShaStateLayout _super;
  IsZeroLayout lastRound;
  MemoryReadLayout k;
  CarryAndExpandLayout wBits;
  CarryAndExpandLayout a;
  CarryAndExpandLayout e;
};
struct Sha0StateArm3Layout {
  ShaMixLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  CycleArgLayout _extra8;
  CycleArgLayout _extra9;
  CycleArgLayout _extra10;
  CycleArgLayout _extra11;
};
struct ShaStoreStateLayout {
  ShaStateLayout _super;
  IsZeroLayout lastRound;
  IsZeroLayout countZero;
  CarryAndExpandLayout a;
  CarryAndExpandLayout e;
  MemoryWriteLayout _1;
  MemoryWriteLayout _2;
};
struct Sha0StateArm4Layout {
  ShaStoreStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  CycleArgLayout _extra6;
  CycleArgLayout _extra7;
  CycleArgLayout _extra8;
};
struct Sha0StateArm5Layout {
  ShaStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  CycleArgLayout _extra10;
  CycleArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
};
struct Sha0StateArm6Layout {
  ShaStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  CycleArgLayout _extra10;
  CycleArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
};
struct Sha0StateArm7Layout {
  ShaStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  CycleArgLayout _extra10;
  CycleArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
};
struct Sha0StateLayout {
  ShaStateLayout _super;
  ShaEcallLayout arm0;
  Sha0StateArm1Layout arm1;
  Sha0StateArm2Layout arm2;
  Sha0StateArm3Layout arm3;
  Sha0StateArm4Layout arm4;
  Sha0StateArm5Layout arm5;
  Sha0StateArm6Layout arm6;
  Sha0StateArm7Layout arm7;
};
struct Sha0Layout {
  DoCycleTableLayout _0;
  ShaStateLayout state;
  _Arguments_Sha0StateLayout _arguments_Sha0State;
  Sha0StateLayout stateRedef;
};
struct BigIntStateLayout {
  NondetRegLayout isEcall;
  NondetRegLayout mode;
  NondetRegLayout pc;
  NondetRegLayout polyOp;
  NondetRegLayout coeff;
  NondetRegLayout16LayoutArray bytes;
  NondetRegLayout nextState;
};
using MemoryArgLayout12LayoutArray = ::cuda::std::array<MemoryArgLayout,12>;
using CycleArgLayout6LayoutArray = ::cuda::std::array<CycleArgLayout,6>;
using ArgU8Layout18LayoutArray = ::cuda::std::array<ArgU8Layout,18>;
struct _Arguments_BigInt0StateLayout {
  MemoryArgLayout12LayoutArray memoryArg;
  CycleArgLayout6LayoutArray cycleArg;
  ArgU8Layout18LayoutArray argU8;
  ArgU16Layout4LayoutArray argU16;
};
struct BigIntEcallLayout {
  BigIntStateLayout _super;
  MemoryReadLayout mode;
  ReadAddrLayout pc;
};
struct BigInt0StateArm0Layout {
  BigIntEcallLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  CycleArgLayout _extra8;
  CycleArgLayout _extra9;
  CycleArgLayout _extra10;
  CycleArgLayout _extra11;
  ArgU8Layout _extra12;
  ArgU8Layout _extra13;
  ArgU8Layout _extra14;
  ArgU8Layout _extra15;
  ArgU8Layout _extra16;
  ArgU8Layout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
  ArgU8Layout _extra20;
  ArgU8Layout _extra21;
  ArgU8Layout _extra22;
  ArgU8Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
  ArgU8Layout _extra26;
  ArgU8Layout _extra27;
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
  ArgU16Layout _extra30;
  ArgU16Layout _extra31;
  ArgU16Layout _extra32;
  ArgU16Layout _extra33;
};
using ArgU16Layout2LayoutArray = ::cuda::std::array<ArgU16Layout,2>;
struct _Arguments_BigIntStepBytesLayout {
  ArgU16Layout2LayoutArray argU16;
  ArgU8Layout16LayoutArray argU8;
  MemoryArgLayout8LayoutArray memoryArg;
  CycleArgLayout4LayoutArray cycleArg;
};
struct BigIntAddrLayout {
  AddrDecomposeBitsLayout _super;
  IsZeroLayout _0;
};
struct SplitU32Layout {
  SplitWordLayout low;
  SplitWordLayout high;
};
struct BigIntReadWords_SuperLayout {
  SplitU32Layout _super;
  MemoryReadLayout _0;
};
using BigIntReadWords_SuperLayout4LayoutArray = ::cuda::std::array<BigIntReadWords_SuperLayout,4>;
struct BigIntReadLayout {
  BigIntAddrLayout addr;
  BigIntReadWords_SuperLayout4LayoutArray words;
};
using NondetU8RegLayout16LayoutArray = ::cuda::std::array<NondetU8RegLayout,16>;
struct BigIntWitnessLayout {
  NondetU8RegLayout16LayoutArray _super;
};
struct BigIntWrite__0_SuperLayout {
  MemoryWriteLayout _0;
};
using BigIntWrite__0_SuperLayout4LayoutArray = ::cuda::std::array<BigIntWrite__0_SuperLayout,4>;
struct BigIntWriteLayout {
  BigIntWitnessLayout _super;
  BigIntAddrLayout addr;
  BigIntWrite__0_SuperLayout4LayoutArray _1;
};
struct BigIntStepBytesArm2Layout {
  BigIntWitnessLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  CycleArgLayout _extra10;
  CycleArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
};
struct BigIntStepBytesLayout {
  BigIntReadLayout arm0;
  BigIntWriteLayout arm1;
  BigIntStepBytesArm2Layout arm2;
};
struct BigIntStepLayout {
  BigIntStateLayout _super;
  MemoryReadLayout loadInst_0;
  SplitWordLayout instHigh;
  NondetRegLayout polyOp;
  NondetRegLayout memOp;
  NondetRegLayout5LayoutArray regBits;
  NondetRegLayout3LayoutArray coeffBits;
  MemoryReadLayout baseAddrU32;
  NormalizeU32Layout dataAddrU32;
  OneHot_3_Layout memOpOneHot;
  _Arguments_BigIntStepBytesLayout _arguments_BigIntStepBytes;
  BigIntStepBytesLayout bytes;
  IsZeroLayout _2;
};
struct BigInt0StateArm2Layout {
  BigIntStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
  CycleArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
  ArgU8Layout _extra20;
  ArgU8Layout _extra21;
  ArgU8Layout _extra22;
  ArgU8Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
  ArgU8Layout _extra26;
  ArgU8Layout _extra27;
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
  ArgU8Layout _extra32;
  ArgU8Layout _extra33;
  ArgU8Layout _extra34;
  ArgU8Layout _extra35;
  ArgU16Layout _extra36;
  ArgU16Layout _extra37;
  ArgU16Layout _extra38;
  ArgU16Layout _extra39;
};
struct BigInt0StateArm3Layout {
  BigIntStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
  CycleArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
  ArgU8Layout _extra20;
  ArgU8Layout _extra21;
  ArgU8Layout _extra22;
  ArgU8Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
  ArgU8Layout _extra26;
  ArgU8Layout _extra27;
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
  ArgU8Layout _extra32;
  ArgU8Layout _extra33;
  ArgU8Layout _extra34;
  ArgU8Layout _extra35;
  ArgU16Layout _extra36;
  ArgU16Layout _extra37;
  ArgU16Layout _extra38;
  ArgU16Layout _extra39;
};
struct BigInt0StateArm4Layout {
  BigIntStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
  CycleArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
  ArgU8Layout _extra20;
  ArgU8Layout _extra21;
  ArgU8Layout _extra22;
  ArgU8Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
  ArgU8Layout _extra26;
  ArgU8Layout _extra27;
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
  ArgU8Layout _extra32;
  ArgU8Layout _extra33;
  ArgU8Layout _extra34;
  ArgU8Layout _extra35;
  ArgU16Layout _extra36;
  ArgU16Layout _extra37;
  ArgU16Layout _extra38;
  ArgU16Layout _extra39;
};
struct BigInt0StateArm5Layout {
  BigIntStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
  CycleArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
  ArgU8Layout _extra20;
  ArgU8Layout _extra21;
  ArgU8Layout _extra22;
  ArgU8Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
  ArgU8Layout _extra26;
  ArgU8Layout _extra27;
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
  ArgU8Layout _extra32;
  ArgU8Layout _extra33;
  ArgU8Layout _extra34;
  ArgU8Layout _extra35;
  ArgU16Layout _extra36;
  ArgU16Layout _extra37;
  ArgU16Layout _extra38;
  ArgU16Layout _extra39;
};
struct BigInt0StateArm6Layout {
  BigIntStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
  CycleArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
  ArgU8Layout _extra20;
  ArgU8Layout _extra21;
  ArgU8Layout _extra22;
  ArgU8Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
  ArgU8Layout _extra26;
  ArgU8Layout _extra27;
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
  ArgU8Layout _extra32;
  ArgU8Layout _extra33;
  ArgU8Layout _extra34;
  ArgU8Layout _extra35;
  ArgU16Layout _extra36;
  ArgU16Layout _extra37;
  ArgU16Layout _extra38;
  ArgU16Layout _extra39;
};
struct BigInt0StateArm7Layout {
  BigIntStateLayout _super;
  MemoryArgLayout _extra0;
  MemoryArgLayout _extra1;
  MemoryArgLayout _extra2;
  MemoryArgLayout _extra3;
  MemoryArgLayout _extra4;
  MemoryArgLayout _extra5;
  MemoryArgLayout _extra6;
  MemoryArgLayout _extra7;
  MemoryArgLayout _extra8;
  MemoryArgLayout _extra9;
  MemoryArgLayout _extra10;
  MemoryArgLayout _extra11;
  CycleArgLayout _extra12;
  CycleArgLayout _extra13;
  CycleArgLayout _extra14;
  CycleArgLayout _extra15;
  CycleArgLayout _extra16;
  CycleArgLayout _extra17;
  ArgU8Layout _extra18;
  ArgU8Layout _extra19;
  ArgU8Layout _extra20;
  ArgU8Layout _extra21;
  ArgU8Layout _extra22;
  ArgU8Layout _extra23;
  ArgU8Layout _extra24;
  ArgU8Layout _extra25;
  ArgU8Layout _extra26;
  ArgU8Layout _extra27;
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
  ArgU8Layout _extra30;
  ArgU8Layout _extra31;
  ArgU8Layout _extra32;
  ArgU8Layout _extra33;
  ArgU8Layout _extra34;
  ArgU8Layout _extra35;
  ArgU16Layout _extra36;
  ArgU16Layout _extra37;
  ArgU16Layout _extra38;
  ArgU16Layout _extra39;
};
struct BigInt0StateLayout {
  BigIntStateLayout _super;
  BigInt0StateArm0Layout arm0;
  BigIntStepLayout arm1;
  BigInt0StateArm2Layout arm2;
  BigInt0StateArm3Layout arm3;
  BigInt0StateArm4Layout arm4;
  BigInt0StateArm5Layout arm5;
  BigInt0StateArm6Layout arm6;
  BigInt0StateArm7Layout arm7;
};
struct BigInt0Layout {
  DoCycleTableLayout _0;
  BigIntStateLayout state;
  _Arguments_BigInt0StateLayout _arguments_BigInt0State;
  BigInt0StateLayout stateRedef;
};
struct TopInstResultLayout {
  NondetRegLayout13LayoutArray _selector;
  Misc0Layout arm0;
  Misc1Layout arm1;
  Misc2Layout arm2;
  Mul0Layout arm3;
  Div0Layout arm4;
  Mem0Layout arm5;
  Mem1Layout arm6;
  Control0Layout arm7;
  ECall0Layout arm8;
  Poseidon0Layout arm9;
  Poseidon1Layout arm10;
  Sha0Layout arm11;
  BigInt0Layout arm12;
};
struct TopCycleLayout {
  NondetRegLayout _super;
  NondetRegLayout arm0;
  NondetRegLayout arm1;
};
struct TopLayout {
  NondetRegLayout cycle;
  NondetRegLayout nextPcLow;
  NondetRegLayout nextPcHigh;
  NondetRegLayout nextState_0;
  NondetRegLayout nextMachineMode;
  NondetRegLayout isFirstCycle;
  TopCycleLayout cycleRedef;
  NondetRegLayout major;
  NondetRegLayout minor;
  InstInputLayout instInput;
  OneHot_13_Layout majorOnehot;
  TopInstResultLayout instResult;
};
struct DigestRegValues_SuperLayout {
  NondetRegLayout low;
  NondetRegLayout high;
};
using DigestRegValues_SuperLayout8LayoutArray = ::cuda::std::array<DigestRegValues_SuperLayout,8>;
struct DigestRegLayout {
  DigestRegValues_SuperLayout8LayoutArray values;
};
struct Arg_ArgU8Layout {
  Reg val;
};
struct Arg_ArgU16Layout {
  Reg val;
};
struct Arg_MemoryArgLayout {
  Reg addr;
  Reg cycle;
  Reg dataLow;
  Reg dataHigh;
};
struct Arg_CycleArgLayout {
  Reg cycle;
};
using Reg1LayoutArray = ::cuda::std::array<Reg,1>;
struct _accumLayout {
  Arg_ArgU8Layout argU8;
  Arg_ArgU16Layout argU16;
  Arg_MemoryArgLayout memoryArg;
  Arg_CycleArgLayout cycleArg;
  Reg _offset;
  Reg1LayoutArray _user;
};
using Reg20LayoutArray = ::cuda::std::array<Reg,20>;
struct LayoutAccumLayout {
  AccumLayout user;
  Reg20LayoutArray columns;
};
struct TestSuccRunLayout {
  TopLayout _0;
};
struct _globalLayout {
  DigestRegLayout input;
  NondetRegLayout isTerminate;
  DigestRegLayout output;
  NondetExtRegLayout rng;
  NondetRegLayout shutdownCycle;
  DigestRegLayout stateIn;
  DigestRegLayout stateOut;
  NondetRegLayout termA0high;
  NondetRegLayout termA0low;
  NondetRegLayout termA1high;
  NondetRegLayout termA1low;
};
struct _mixLayout {
  _accumLayout randomness;
};
struct NondetRegStruct {
  Val _super;
};
struct NondetExtRegStruct {
  ExtVal _super;
};
struct NondetFakeTwitRegStruct {
  Val _super;
};
struct FakeTwitRegStruct {
};
struct ArgU8Struct {
  NondetRegStruct count;
  NondetRegStruct val;
};
struct U8RegStruct {
};
struct ArgU16Struct {
  NondetRegStruct count;
  NondetRegStruct val;
};
struct NondetU16RegStruct {
  NondetRegStruct _super;
};
using Val5Array = ::cuda::std::array<Val,5>;
using Val30Array = ::cuda::std::array<Val,30>;
using NondetRegStruct5Array = ::cuda::std::array<NondetRegStruct,5>;
struct ToBits_5_Struct {
  NondetRegStruct5Array _super;
};
struct ValU32Struct {
  Val low;
  Val high;
};
struct DenormedValU32Struct {
  Val low;
  Val high;
};
struct NormalizeU32Struct {
  ValU32Struct _super;
  NondetRegStruct highCarry;
};
struct AddrDecomposeStruct {
  Val _super;
  NondetRegStruct low2;
};
struct AddrDecomposeBitsStruct {
  Val _super;
  NondetRegStruct low0;
  NondetRegStruct low1;
  Val low2;
};
struct CmpEqualStruct {
  NondetRegStruct isEqual;
};
struct CmpLessThanUnsignedStruct {
  Val isLessThan;
};
struct CmpLessThanStruct {
  NondetRegStruct isLessThan;
};
using Val16Array = ::cuda::std::array<Val,16>;
using NondetRegStruct16Array = ::cuda::std::array<NondetRegStruct,16>;
struct ToBits_16_Struct {
  NondetRegStruct16Array _super;
};
struct FromBits_16_Struct {
  Val _super;
};
struct DecoderStruct {
  NondetRegStruct opcode;
  Val rs1;
  Val rs2;
  Val rd;
  Val func7;
  Val func3;
  ValU32Struct immI;
  ValU32Struct immS;
  ValU32Struct immB;
  ValU32Struct immU;
  ValU32Struct immJ;
};
struct MemoryArgStruct {
  NondetRegStruct count;
  NondetRegStruct addr;
  NondetRegStruct cycle;
  NondetRegStruct dataLow;
  NondetRegStruct dataHigh;
};
struct CycleArgStruct {
  NondetRegStruct count;
  NondetRegStruct cycle;
};
struct IsCycleStruct {
};
struct MemoryIOStruct {
  MemoryArgStruct oldTxn;
  MemoryArgStruct newTxn;
};
struct IsForwardStruct {
};
struct GetDataStruct {
  ValU32Struct _super;
  Val diffLow;
  Val diffHigh;
};
struct MemoryWriteStruct {
};
struct MemoryWriteUnconstrainedStruct {
  MemoryIOStruct io;
};
using Val3Array = ::cuda::std::array<Val,3>;
using NondetRegStruct3Array = ::cuda::std::array<NondetRegStruct,3>;
struct OneHot_3_Struct {
  NondetRegStruct3Array _super;
};
using Val8Array = ::cuda::std::array<Val,8>;
using NondetRegStruct8Array = ::cuda::std::array<NondetRegStruct,8>;
struct OneHot_8_Struct {
  NondetRegStruct8Array _super;
};
struct InstInputStruct {
  Val minor;
  ValU32Struct pcU32;
  Val state;
  Val mode;
  OneHot_8_Struct minorOnehot;
};
struct DoCycleTableStruct {
};
struct SourceRegsStruct {
  ValU32Struct rs1;
  ValU32Struct rs2;
};
struct ReadSourceRegsStruct {
  ValU32Struct rs1;
  ValU32Struct rs2;
};
struct WriteRdStruct {
};
struct ExpandU32Struct {
  NondetRegStruct b0;
  NondetRegStruct b1;
  NondetRegStruct b2;
  NondetRegStruct b3;
  Val neg;
};
struct SplitTotalStruct {
  NondetU16RegStruct out;
  Val carry;
};
struct MultiplySettingsStruct {
  Val aSigned;
  Val bSigned;
  Val cSigned;
};
struct MultiplyAccumulateStruct {
  ValU32Struct outLow;
  ValU32Struct outHigh;
  Val bNeg;
};
struct DivInputStruct {
  InstInputStruct _super;
  DecoderStruct decoded;
  ValU32Struct rs1;
  ValU32Struct rs2;
};
struct ComponentStruct {
};
struct DivideReturnStruct {
  ValU32Struct quot;
  ValU32Struct rem;
};
struct BigIntTopStateStruct {
  Val polyOp;
  Val coeff;
  Val16Array witness;
};
struct InstOutputBaseStruct {
  ValU32Struct newPc;
  Val newState;
  Val newMode;
  BigIntTopStateStruct topState;
};
struct MiscInputStruct {
  InstInputStruct _super;
  DecoderStruct decoded;
  ValU32Struct rs1;
  ValU32Struct rs2;
};
struct MiscOutputStruct {
  Val doWrite;
  DenormedValU32Struct toWrite;
  DenormedValU32Struct newPc;
};
struct MulInputStruct {
  InstInputStruct _super;
  DecoderStruct decoded;
  ValU32Struct rs1;
  ValU32Struct rs2;
};
struct DoMulStruct {
  ValU32Struct low;
  ValU32Struct high;
};
struct MemLoadInputStruct {
  InstInputStruct ii;
  DecoderStruct decoded;
  AddrDecomposeBitsStruct addr;
  GetDataStruct data;
};
struct MemStoreInputStruct {
  DecoderStruct decoded;
  ValU32Struct rs2;
  AddrDecomposeBitsStruct addr;
  GetDataStruct data;
};
struct MemStoreFinalizeStruct {
};
struct SplitWordStruct {
  NondetRegStruct byte0;
  NondetRegStruct byte1;
};
struct DigestRegValues_SuperStruct {
  NondetRegStruct low;
  NondetRegStruct high;
};
using DigestRegValues_SuperStruct8Array = ::cuda::std::array<DigestRegValues_SuperStruct,8>;
struct DigestRegStruct {
  DigestRegValues_SuperStruct8Array values;
};
using ValU32Struct8Array = ::cuda::std::array<ValU32Struct,8>;
struct ControlLoadRoot__0Struct {
};
using ControlLoadRoot__0Struct8Array = ::cuda::std::array<ControlLoadRoot__0Struct,8>;
struct ControlResume_SuperArm1_Super__0Struct {
};
using ControlResume_SuperArm1_Super__0Struct8Array = ::cuda::std::array<ControlResume_SuperArm1_Super__0Struct,8>;
using GetDataStruct8Array = ::cuda::std::array<GetDataStruct,8>;
struct ControlTable_SuperArm0_Super__0Struct {
};
struct ControlTable_SuperArm1_Super__0Struct {
};
using ControlTable_SuperArm0_Super__0Struct16Array = ::cuda::std::array<ControlTable_SuperArm0_Super__0Struct,16>;
using ControlTable_SuperArm1_Super__0Struct16Array = ::cuda::std::array<ControlTable_SuperArm1_Super__0Struct,16>;
using Val6Array = ::cuda::std::array<Val,6>;
using NondetRegStruct6Array = ::cuda::std::array<NondetRegStruct,6>;
struct OneHot_6_Struct {
  NondetRegStruct6Array _super;
};
struct ECallOutputStruct {
  Val state;
  Val s0;
  Val s1;
  Val s2;
};
using Val4Array = ::cuda::std::array<Val,4>;
using NondetRegStruct4Array = ::cuda::std::array<NondetRegStruct,4>;
struct OneHot_4_Struct {
  NondetRegStruct4Array _super;
};
struct DecomposeLow2Struct {
  NondetU16RegStruct high;
  NondetRegStruct low2;
  OneHot_4_Struct low2Hot;
  NondetRegStruct highZero;
  NondetRegStruct isZero;
  Val low2Nonzero;
};
struct ECallHostReadWords__0Struct {
};
using ECallHostReadWords__0Struct4Array = ::cuda::std::array<ECallHostReadWords__0Struct,4>;
using Val24Array = ::cuda::std::array<Val,24>;
struct MultiplyByMInt_Super_SuperStruct {
  Val _super;
};
using MultiplyByMInt_Super_SuperStruct24Array = ::cuda::std::array<MultiplyByMInt_Super_SuperStruct,24>;
struct MultiplyByMIntStruct {
  MultiplyByMInt_Super_SuperStruct24Array _super;
};
struct DoIntRounds__0_SuperStruct {
  Val _super;
};
using DoIntRounds__0_SuperStruct21Array = ::cuda::std::array<DoIntRounds__0_SuperStruct,21>;
struct DoIntRoundsStruct {
  Val24Array _super;
};
using NondetRegStruct24Array = ::cuda::std::array<NondetRegStruct,24>;
struct MultiplyByMExt_Super_SuperStruct {
  Val _super;
};
using MultiplyByMExt_Super_SuperStruct24Array = ::cuda::std::array<MultiplyByMExt_Super_SuperStruct,24>;
struct MultiplyByMExtStruct {
  MultiplyByMExt_Super_SuperStruct24Array _super;
};
struct PoseidonStateStruct {
  NondetRegStruct hasState;
  NondetRegStruct stateAddr;
  NondetRegStruct bufOutAddr;
  NondetRegStruct isElem;
  NondetRegStruct checkOut;
  NondetRegStruct loadTxType;
  NondetRegStruct nextState;
  NondetRegStruct subState;
  NondetRegStruct bufInAddr;
  NondetRegStruct count;
  NondetRegStruct mode;
  NondetRegStruct24Array inner;
  NondetExtRegStruct zcheck;
};
struct PoseidonOpDefStruct {
  Val hasState;
  Val stateAddr;
  Val bufOutAddr;
  Val isElem;
  Val checkOut;
  Val loadTxType;
};
struct ReadAddrStruct {
  Val _super;
};
struct ReadElemStruct {
  Val _super;
};
using ReadElemStruct8Array = ::cuda::std::array<ReadElemStruct,8>;
struct PoseidonCheckOut__0Struct {
};
using PoseidonCheckOut__0Struct8Array = ::cuda::std::array<PoseidonCheckOut__0Struct,8>;
struct FieldToWordStruct {
  ValU32Struct ret;
};
struct PoseidonStoreOut__0Struct {
};
using PoseidonStoreOut__0Struct8Array = ::cuda::std::array<PoseidonStoreOut__0Struct,8>;
struct PoseidonStoreState__0Struct {
};
using PoseidonStoreState__0Struct8Array = ::cuda::std::array<PoseidonStoreState__0Struct,8>;
struct IsU24Struct {
};
struct CarryExtractStruct {
  Val carry;
  Val out;
};
using Val2Array = ::cuda::std::array<Val,2>;
struct DivStruct {
  Val _super;
};
using DivStruct32Array = ::cuda::std::array<DivStruct,32>;
using Val32Array = ::cuda::std::array<Val,32>;
using NondetRegStruct32Array = ::cuda::std::array<NondetRegStruct,32>;
struct UnpackReg_32__16_Struct {
  NondetRegStruct32Array _super;
};
struct ShaStateAStruct {
  NondetRegStruct _super;
};
using ShaStateAStruct32Array = ::cuda::std::array<ShaStateAStruct,32>;
struct ShaStateEStruct {
  NondetRegStruct _super;
};
using ShaStateEStruct32Array = ::cuda::std::array<ShaStateEStruct,32>;
struct ShaStateWStruct {
  NondetRegStruct _super;
};
using ShaStateWStruct32Array = ::cuda::std::array<ShaStateWStruct,32>;
struct ShaStateStruct {
  NondetRegStruct stateInAddr;
  NondetRegStruct stateOutAddr;
  NondetRegStruct dataAddr;
  NondetRegStruct count;
  NondetRegStruct kAddr;
  NondetRegStruct round;
  NondetRegStruct nextState;
  ShaStateAStruct32Array a;
  ShaStateEStruct32Array e;
  ShaStateWStruct32Array w;
};
struct BigIntStateStruct {
  NondetRegStruct isEcall;
  NondetRegStruct mode;
  NondetRegStruct pc;
  NondetRegStruct polyOp;
  NondetRegStruct coeff;
  NondetRegStruct16Array bytes;
  NondetRegStruct nextState;
};
struct SplitU32Struct {
  NondetRegStruct4Array bytes;
};
using SplitU32Struct4Array = ::cuda::std::array<SplitU32Struct,4>;
struct BigIntReadStruct {
  NondetRegStruct16Array _super;
};
struct BigIntWitnessStruct {
  NondetRegStruct16Array _super;
};
struct BigIntWrite__0Struct {
};
using BigIntWrite__0Struct4Array = ::cuda::std::array<BigIntWrite__0Struct,4>;
struct BigIntAccumStateStruct {
  NondetExtRegStruct poly;
  NondetExtRegStruct term;
  NondetExtRegStruct total;
};
using Val7Array = ::cuda::std::array<Val,7>;
using NondetRegStruct7Array = ::cuda::std::array<NondetRegStruct,7>;
struct OneHot_7_Struct {
  NondetRegStruct7Array _super;
};
using ExtVal1Array = ::cuda::std::array<ExtVal,1>;
struct BigIntAccumStruct {
};
using Val13Array = ::cuda::std::array<Val,13>;
using NondetRegStruct13Array = ::cuda::std::array<NondetRegStruct,13>;
struct OneHot_13_Struct {
  NondetRegStruct13Array _super;
};
struct TopStruct {
};
struct AccumStruct {
};
