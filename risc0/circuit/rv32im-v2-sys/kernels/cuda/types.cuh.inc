struct NondetRegLayout {
  Reg _super;
};
using NondetRegLayout8LayoutArray = ::cuda::std::array<NondetRegLayout,8>;
struct OneHot_8_Layout {
  NondetRegLayout8LayoutArray _super;
};
struct InstInputLayout {
  OneHot_8_Layout minorOnehot;
};
using NondetRegLayout11LayoutArray = ::cuda::std::array<NondetRegLayout,11>;
struct OneHot_11_Layout {
  NondetRegLayout11LayoutArray _super;
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
struct U16RegLayout {
  NondetU16RegLayout ret;
};
struct AddrDecomposeLayout {
  NondetRegLayout low2;
  U16RegLayout upperDiff;
  IsZeroLayout _0;
  NondetU16RegLayout med14;
};
struct MemoryReadLayout {
  MemoryIOLayout io;
  IsForwardLayout _0;
};
struct DecodeInstLayout {
  DecoderLayout _super;
  CycleArgLayout arg;
  AddrDecomposeLayout pcAddr;
  MemoryReadLayout loadInst;
};
struct ReadRegLayout {
  MemoryReadLayout _super;
  NondetRegLayout addr;
};
struct MiscInputLayout {
  DecodeInstLayout decoded;
  ReadRegLayout rs1;
  ReadRegLayout rs2;
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
  MiscInputLayout input;
  _Arguments_Misc2MiscOutputLayout _arguments_Misc2MiscOutput;
  Misc2MiscOutputLayout miscOutput;
};
struct MulInputLayout {
  DecodeInstLayout decoded;
  ReadRegLayout rs1;
  ReadRegLayout rs2;
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
  MulInputLayout input;
  _Arguments_Mul0MulOutputLayout _arguments_Mul0MulOutput;
  Mul0MulOutputLayout mulOutput;
  WriteRdLayout _0;
  NormalizeU32Layout pcAdd;
};
struct DivInputLayout {
  DecodeInstLayout decoded;
  ReadRegLayout rs1;
  ReadRegLayout rs2;
};
using ArgU16Layout9LayoutArray = ::cuda::std::array<ArgU16Layout,9>;
struct _Arguments_Div0MulOutputLayout {
  ArgU16Layout9LayoutArray argU16;
  ArgU8Layout13LayoutArray argU8;
};
struct DoDivLayout {
  NondetRegLayout quotLow;
  NondetRegLayout quotHigh;
  NondetU16RegLayout remLow;
  NondetU16RegLayout remHigh;
  MultiplyAccumulateLayout mul;
  NondetRegLayout topBitType;
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
  DivInputLayout input;
  _Arguments_Div0MulOutputLayout _arguments_Div0MulOutput;
  Div0MulOutputLayout mulOutput;
  WriteRdLayout _0;
  NormalizeU32Layout pcAdd;
};
struct AddrDecomposeBitsLayout {
  NondetRegLayout low0;
  NondetRegLayout low1;
  U16RegLayout upperDiff;
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
  MemLoadInputLayout input;
  _Arguments_Mem0OutputLayout _arguments_Mem0Output;
  Mem0OutputLayout output;
  WriteRdLayout _0;
  NormalizeU32Layout pcAdd;
};
struct MemStoreInputLayout {
  DecodeInstLayout decoded;
  ReadRegLayout rs1;
  ReadRegLayout rs2;
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
  MemStoreInputLayout input;
  _Arguments_Mem1OutputLayout _arguments_Mem1Output;
  Mem1OutputLayout output;
  MemStoreFinalizeLayout _0;
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
  MemoryReadLayout dispatchIdx;
  U16RegLayout _0;
  MemoryReadLayout newPcAddr;
  MemoryWriteLayout _1;
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
  ArgU8Layout _extra40;
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
using ArgU16Layout16LayoutArray = ::cuda::std::array<ArgU16Layout,16>;
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
struct Control0_SuperArm7Layout {
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
  ArgU8Layout _extra55;
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
  CycleArgLayout arg;
  _Arguments_Control0_SuperLayout _arguments_Control0_Super;
};
using MemoryArgLayout8LayoutArray = ::cuda::std::array<MemoryArgLayout,8>;
using CycleArgLayout4LayoutArray = ::cuda::std::array<CycleArgLayout,4>;
using ArgU16Layout2LayoutArray = ::cuda::std::array<ArgU16Layout,2>;
struct _Arguments_ECall0OutputLayout {
  MemoryArgLayout8LayoutArray memoryArg;
  CycleArgLayout4LayoutArray cycleArg;
  ArgU16Layout2LayoutArray argU16;
};
using NondetRegLayout4LayoutArray = ::cuda::std::array<NondetRegLayout,4>;
struct OneHot_4_Layout {
  NondetRegLayout4LayoutArray _super;
};
struct MachineECallLayout {
  MemoryReadLayout loadInst;
  MemoryReadLayout dispatchIdx;
  OneHot_4_Layout dispatch;
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
};
struct DecomposeLow2Layout {
  NondetRegLayout high;
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
  U16RegLayout diff;
  MemoryWriteLayout _0;
  DecomposeLow2Layout ptrDecomp;
  DecomposeLow2Layout lenDecomp;
  NondetRegLayout len123;
  NondetRegLayout uneven;
};
struct ECallHostWriteLayout {
  MemoryReadLayout fd;
  MemoryReadLayout ptr;
  MemoryReadLayout len;
  NondetU16RegLayout newLen;
  U16RegLayout diff;
  MemoryWriteLayout _0;
};
struct ECall0OutputArm4Layout {
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
};
struct MemoryWriteUnconstrainedLayout {
  MemoryIOLayout io;
  IsForwardLayout _0;
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
  IsZeroLayout lenZero;
};
struct ECall0OutputArm5Layout {
  ECallHostReadWordsLayout _super;
  ArgU16Layout _extra0;
  ArgU16Layout _extra1;
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
};
struct ECall0OutputLayout {
  ECall0OutputArm0Layout arm0;
  ECall0OutputArm1Layout arm1;
  ECallHostReadSetupLayout arm2;
  ECallHostWriteLayout arm3;
  ECall0OutputArm4Layout arm4;
  ECall0OutputArm5Layout arm5;
  ECall0OutputArm6Layout arm6;
  ECall0OutputArm7Layout arm7;
};
struct ECall0Layout {
  NondetRegLayout s0;
  NondetRegLayout s1;
  NondetRegLayout s2;
  AddrDecomposeBitsLayout pcAddr;
  _Arguments_ECall0OutputLayout _arguments_ECall0Output;
  ECall0OutputLayout output;
  IsZeroLayout isDecode;
  IsZeroLayout isP2Entry;
  NormalizeU32Layout addPC;
  CycleArgLayout arg;
};
using NondetRegLayout24LayoutArray = ::cuda::std::array<NondetRegLayout,24>;
struct NondetExtRegLayout {
  Reg _super;
};
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
using ArgU8Layout2LayoutArray = ::cuda::std::array<ArgU8Layout,2>;
struct _Arguments_Poseidon0StateLayout {
  MemoryArgLayout16LayoutArray memoryArg;
  CycleArgLayout8LayoutArray cycleArg;
  ArgU16Layout16LayoutArray argU16;
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
  ArgU8Layout _extra28;
  ArgU8Layout _extra29;
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
  ArgU8Layout _extra16;
  ArgU8Layout _extra17;
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
using CycleArgLayout1LayoutArray = ::cuda::std::array<CycleArgLayout,1>;
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
  ArgU8Layout _extra16;
  ArgU8Layout _extra17;
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
  ArgU8Layout _extra40;
  ArgU8Layout _extra41;
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
  ArgU8Layout _extra40;
  ArgU8Layout _extra41;
};
struct PoseidonCheckOut__0_SuperLayout {
  ReadElemLayout goal;
};
using PoseidonCheckOut__0_SuperLayout8LayoutArray = ::cuda::std::array<PoseidonCheckOut__0_SuperLayout,8>;
struct PoseidonCheckOutLayout {
  PoseidonStateLayout _super;
  PoseidonCheckOut__0_SuperLayout8LayoutArray _1;
  IsZeroLayout isNormal;
  NondetExtRegLayout extInv;
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
};
struct PoseidonStoreOut__0_SuperLayout {
  NondetU16RegLayout low;
  U16RegLayout high;
  MemoryWriteLayout _0;
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
  ArgU16Layout16LayoutArray argU16;
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
using NondetRegLayout6LayoutArray = ::cuda::std::array<NondetRegLayout,6>;
struct OneHot_6_Layout {
  NondetRegLayout6LayoutArray _super;
};
struct U8RegLayout {
  NondetU8RegLayout ret;
};
struct IsU24Layout {
  NondetU16RegLayout low16;
  U8RegLayout _0;
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
};
struct PoseidonStoreState__0_SuperLayout {
  NondetU16RegLayout low;
  U16RegLayout high;
  MemoryWriteLayout _0;
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
  PoseidonStateLayout state;
  _Arguments_Poseidon0StateLayout _arguments_Poseidon0State;
  Poseidon0StateLayout stateRedef;
  CycleArgLayout arg;
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
  PoseidonStateLayout state;
  Poseidon1StateLayout stateRedef;
  CycleArgLayout arg;
};
struct TopInstResultLayout {
  NondetRegLayout11LayoutArray _selector;
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
};
struct TopLayout {
  NondetRegLayout nextPcLow;
  NondetRegLayout nextPcHigh;
  NondetRegLayout nextState_0;
  NondetRegLayout nextMachineMode;
  NondetRegLayout isFirstCycle;
  NondetRegLayout cycleND;
  NondetRegLayout cycle;
  NondetRegLayout major;
  NondetRegLayout minor;
  InstInputLayout instInput;
  OneHot_11_Layout majorOnehot;
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
struct _accumLayout {
  Arg_ArgU8Layout argU8;
  Arg_ArgU16Layout argU16;
  Arg_MemoryArgLayout memoryArg;
  Arg_CycleArgLayout cycleArg;
  Reg _offset;
};
using Reg19LayoutArray = ::cuda::std::array<Reg,19>;
struct LayoutAccumLayout {
  Reg19LayoutArray columns;
};
struct TestSuccRunLayout {
  TopLayout _0;
};
struct _globalLayout {
  DigestRegLayout input;
  NondetRegLayout isTerminate;
  DigestRegLayout output;
  NondetExtRegLayout rng;
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
struct RegStruct {
  NondetRegStruct _super;
};
struct BitRegStruct {
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
struct U16RegStruct {
  Val _super;
};
using Val5Array = ::cuda::std::array<Val,5>;
using Val16Array = ::cuda::std::array<Val,16>;
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
  NondetRegStruct carry;
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
  Val addr;
};
struct CmpEqualStruct {
  RegStruct isEqual;
};
struct CmpLessThanUnsignedStruct {
  Val isLessThan;
};
struct CmpLessThanStruct {
  RegStruct isLessThan;
};
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
  NondetRegStruct8Array bits;
};
struct InstInputStruct {
  ValU32Struct pcU32;
  Val state;
  Val mode;
  OneHot_8_Struct minorOnehot;
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
  NondetRegStruct out;
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
};
struct DivInputStruct {
  InstInputStruct _super;
  InstInputStruct ii;
  DecoderStruct decoded;
  GetDataStruct rs1;
  GetDataStruct rs2;
};
struct DivideReturnStruct {
  ValU32Struct quot;
  ValU32Struct rem;
};
struct InstOutputStruct {
  ValU32Struct newPc;
  Val newState;
  Val newMode;
};
struct MiscInputStruct {
  InstInputStruct _super;
  InstInputStruct ii;
  DecoderStruct decoded;
  GetDataStruct rs1;
  GetDataStruct rs2;
};
struct MiscOutputStruct {
  Val doWrite;
  DenormedValU32Struct toWrite;
  DenormedValU32Struct newPc;
};
struct MulInputStruct {
  InstInputStruct _super;
  InstInputStruct ii;
  DecoderStruct decoded;
  GetDataStruct rs1;
  GetDataStruct rs2;
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
  GetDataStruct rs2;
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
  RegStruct low;
  RegStruct high;
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
struct ComponentStruct {
};
using GetDataStruct8Array = ::cuda::std::array<GetDataStruct,8>;
struct ControlTable_SuperArm0_Super__0Struct {
};
struct ControlTable_SuperArm1_Super__0Struct {
};
using ControlTable_SuperArm0_Super__0Struct16Array = ::cuda::std::array<ControlTable_SuperArm0_Super__0Struct,16>;
using ControlTable_SuperArm1_Super__0Struct16Array = ::cuda::std::array<ControlTable_SuperArm1_Super__0Struct,16>;
using Val4Array = ::cuda::std::array<Val,4>;
using NondetRegStruct4Array = ::cuda::std::array<NondetRegStruct,4>;
struct OneHot_4_Struct {
  NondetRegStruct4Array _super;
};
struct ECallOutputStruct {
  Val state;
  Val s0;
  Val s1;
  Val s2;
};
struct DecomposeLow2Struct {
  NondetRegStruct high;
  NondetRegStruct low2;
  OneHot_4_Struct low2Hot;
  NondetRegStruct highZero;
  RegStruct isZero;
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
using RegStruct24Array = ::cuda::std::array<RegStruct,24>;
struct MultiplyByMExt_Super_SuperStruct {
  Val _super;
};
using MultiplyByMExt_Super_SuperStruct24Array = ::cuda::std::array<MultiplyByMExt_Super_SuperStruct,24>;
struct MultiplyByMExtStruct {
  MultiplyByMExt_Super_SuperStruct24Array _super;
};
struct PoseidonStateStruct {
  RegStruct hasState;
  RegStruct stateAddr;
  RegStruct bufOutAddr;
  RegStruct isElem;
  RegStruct checkOut;
  RegStruct loadTxType;
  RegStruct nextState;
  RegStruct subState;
  RegStruct bufInAddr;
  RegStruct count;
  RegStruct mode;
  RegStruct24Array inner;
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
struct PoseidonStoreOut__0Struct {
};
using PoseidonStoreOut__0Struct8Array = ::cuda::std::array<PoseidonStoreOut__0Struct,8>;
struct PoseidonStoreState__0Struct {
};
using PoseidonStoreState__0Struct8Array = ::cuda::std::array<PoseidonStoreState__0Struct,8>;
struct IsU24Struct {
};
using Val6Array = ::cuda::std::array<Val,6>;
using NondetRegStruct6Array = ::cuda::std::array<NondetRegStruct,6>;
struct OneHot_6_Struct {
  NondetRegStruct6Array _super;
  NondetRegStruct6Array bits;
};
using Val11Array = ::cuda::std::array<Val,11>;
using NondetRegStruct11Array = ::cuda::std::array<NondetRegStruct,11>;
struct OneHot_11_Struct {
  NondetRegStruct11Array _super;
};
struct TopStruct {
};
