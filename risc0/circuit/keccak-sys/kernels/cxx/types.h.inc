struct NondetRegLayout {
  Reg _super;
};
struct IsZeroLayout {
  NondetRegLayout _super;
  NondetRegLayout inv;
};
struct CycleCounterLayout {
  NondetRegLayout _super;
  IsZeroLayout isFirstCycle;
};
using NondetRegLayout11LayoutArray = std::array<NondetRegLayout, 11>;
struct WrapOneHotLayout {
  NondetRegLayout11LayoutArray _super;
};
struct ControlStateLayout {
  NondetRegLayout cycleType;
  NondetRegLayout subType;
  NondetRegLayout round;
};
struct ComputeCurrentStep_SuperArm2_SuperLayout {
  ControlStateLayout _super;
  ControlStateLayout arm0;
  ControlStateLayout arm1;
};
struct KeccackNextRound_SuperLayout {
  ControlStateLayout _super;
  ControlStateLayout arm0;
  ControlStateLayout arm1;
};
struct KeccackNextRoundLayout {
  KeccackNextRound_SuperLayout _super;
  IsZeroLayout isLast;
};
struct CheckNextPreimage_SuperLayout {
  ControlStateLayout _super;
  ControlStateLayout arm0;
  ControlStateLayout arm1;
};
struct CheckNextPreimageLayout {
  CheckNextPreimage_SuperLayout _super;
  NondetRegLayout more;
};
struct Poseidon2NextRound_SuperLayout {
  ControlStateLayout _super;
  ControlStateLayout arm0;
  ControlStateLayout arm1;
  CheckNextPreimageLayout arm2;
};
struct Poseidon2NextRoundLayout {
  Poseidon2NextRound_SuperLayout _super;
  IsZeroLayout isLast;
  NondetRegLayout isLastRead;
  NondetRegLayout isLastWrite;
};
struct ComputeCurrentStep_SuperLayout {
  ControlStateLayout _super;
  ControlStateLayout arm0;
  ControlStateLayout arm1;
  ComputeCurrentStep_SuperArm2_SuperLayout arm2;
  ControlStateLayout arm3;
  ControlStateLayout arm4;
  ControlStateLayout arm5;
  ControlStateLayout arm6;
  ControlStateLayout arm7;
  KeccackNextRoundLayout arm8;
  Poseidon2NextRoundLayout arm9;
  ControlStateLayout arm10;
};
struct TopControlStateLayout {
  ControlStateLayout _super;
  ControlStateLayout arm0;
  ComputeCurrentStep_SuperLayout arm1;
};
struct OneHot_11_Layout {
  NondetRegLayout11LayoutArray _super;
};
using NondetRegLayout800LayoutArray = std::array<NondetRegLayout, 800>;
using NondetRegLayout100LayoutArray = std::array<NondetRegLayout, 100>;
using NondetRegLayout24LayoutArray = std::array<NondetRegLayout, 24>;
struct TopStateLayout {
  NondetRegLayout800LayoutArray bits;
  NondetRegLayout100LayoutArray kflat;
  NondetRegLayout24LayoutArray pflat;
};
struct ReadCycleLayout {
  TopStateLayout _super;
  NondetRegLayout100LayoutArray load;
};
struct UnpackReg_800__16_Layout {
  NondetRegLayout800LayoutArray _super;
};
struct ExpandCycleLayout {
  TopStateLayout _super;
  UnpackReg_800__16_Layout bits;
};
using NondetRegLayout64LayoutArray = std::array<NondetRegLayout, 64>;
struct ThetaP1_Super_SuperLayout {
  NondetRegLayout64LayoutArray _super;
};
using ThetaP1_Super_SuperLayout5LayoutArray = std::array<ThetaP1_Super_SuperLayout, 5>;
struct ThetaP1Layout {
  ThetaP1_Super_SuperLayout5LayoutArray _super;
};
struct KeccakRound0Layout {
  TopStateLayout _super;
  ThetaP1Layout b;
};
struct OneHot_24_Layout {
  NondetRegLayout24LayoutArray _super;
};
struct RoundToArrayLayout {
  OneHot_24_Layout split;
};
struct IotaLayout {
  RoundToArrayLayout iotaArray;
};
struct KeccakRound34_0_Layout {
  TopStateLayout _super;
  IotaLayout _0;
};
struct KeccakRound34_1_Layout {
  TopStateLayout _super;
  IotaLayout _0;
};
using NondetRegLayout7LayoutArray = std::array<NondetRegLayout, 7>;
struct OneHot_7_Layout {
  NondetRegLayout7LayoutArray _super;
};
struct SBoxLayout {
  NondetRegLayout _super;
  NondetRegLayout cubed;
};
using SBoxLayout24LayoutArray = std::array<SBoxLayout, 24>;
struct DoExtRoundLayout {
  SBoxLayout24LayoutArray _1;
};
using NondetRegLayout8LayoutArray = std::array<NondetRegLayout, 8>;
struct OneHot_8_Layout {
  NondetRegLayout8LayoutArray _super;
};
struct DoExtRoundByIdxLayout {
  DoExtRoundLayout _super;
  OneHot_8_Layout idxHot;
};
struct DoIntRoundLayout {
  SBoxLayout sbox;
};
using DoIntRoundLayout21LayoutArray = std::array<DoIntRoundLayout, 21>;
struct DoIntRoundsLayout {
  DoIntRoundLayout21LayoutArray _super;
};
struct DoSpongeLayout {
  DoExtRoundByIdxLayout _super;
  NondetRegLayout24LayoutArray stage0x;
  DoExtRoundByIdxLayout stage1;
  DoExtRoundByIdxLayout stage2;
  DoExtRoundByIdxLayout stage3;
  DoExtRoundByIdxLayout stage4;
  DoIntRoundsLayout stage5;
  DoExtRoundByIdxLayout stage6;
  DoExtRoundByIdxLayout stage7;
  DoExtRoundByIdxLayout stage8;
};
struct Poseidon2CycleLayout {
  TopStateLayout _super;
  OneHot_7_Layout roundOH;
  DoSpongeLayout stateOut;
};
struct TopCurStateLayout {
  TopStateLayout _super;
  TopStateLayout arm0;
  ReadCycleLayout arm1;
  ExpandCycleLayout arm2;
  TopStateLayout arm3;
  KeccakRound0Layout arm4;
  TopStateLayout arm5;
  TopStateLayout arm6;
  KeccakRound34_0_Layout arm7;
  KeccakRound34_1_Layout arm8;
  Poseidon2CycleLayout arm9;
  TopStateLayout arm10;
};
struct DigestRegLayout {
  NondetRegLayout8LayoutArray values;
};
struct TopLayout {
  CycleCounterLayout cycle;
  WrapOneHotLayout cycleMux;
  ControlStateLayout controlState;
  TopControlStateLayout controlStateRedef;
  OneHot_11_Layout oneHot;
  TopStateLayout curState;
  TopCurStateLayout curStateRedef;
};
struct _globalLayout {
  DigestRegLayout finalDigest;
  NondetRegLayout totalCycles;
};
struct NondetRegStruct {
  Val _super;
};
struct ComponentStruct {
};
struct CycleCounterStruct {
  NondetRegStruct isFirstCycle;
};
using Val5Array = std::array<Val, 5>;
using Val64Array = std::array<Val, 64>;
using Val64Array5Array = std::array<Val64Array, 5>;
using Val64Array5Array5Array = std::array<Val64Array5Array, 5>;
struct ThetaP1_Super_Super_SuperStruct {
  NondetRegStruct _super;
};
using ThetaP1_Super_Super_SuperStruct64Array = std::array<ThetaP1_Super_Super_SuperStruct, 64>;
struct ThetaP1_Super_SuperStruct {
  ThetaP1_Super_Super_SuperStruct64Array _super;
};
using ThetaP1_Super_SuperStruct5Array = std::array<ThetaP1_Super_SuperStruct, 5>;
struct ThetaP1Struct {
  ThetaP1_Super_SuperStruct5Array _super;
};
using Val24Array = std::array<Val, 24>;
using NondetRegStruct24Array = std::array<NondetRegStruct, 24>;
struct OneHot_24_Struct {
  NondetRegStruct24Array _super;
};
struct RoundToArray_Super_SuperStruct {
  Val _super;
};
using RoundToArray_Super_SuperStruct64Array = std::array<RoundToArray_Super_SuperStruct, 64>;
struct RoundToArrayStruct {
  RoundToArray_Super_SuperStruct64Array _super;
};
struct Iota_Super_Super_Super_SuperStruct {
  Val64Array _super;
};
using Iota_Super_Super_Super_SuperStruct5Array = std::array<Iota_Super_Super_Super_SuperStruct, 5>;
struct Iota_Super_SuperStruct {
  Iota_Super_Super_Super_SuperStruct5Array _super;
};
using Iota_Super_SuperStruct5Array = std::array<Iota_Super_SuperStruct, 5>;
struct IotaStruct {
  Iota_Super_SuperStruct5Array _super;
};
struct MultiplyByMInt_Super_SuperStruct {
  Val _super;
};
using MultiplyByMInt_Super_SuperStruct24Array = std::array<MultiplyByMInt_Super_SuperStruct, 24>;
struct MultiplyByMIntStruct {
  MultiplyByMInt_Super_SuperStruct24Array _super;
};
struct DoIntRounds__0_SuperStruct {
  Val _super;
};
using DoIntRounds__0_SuperStruct21Array = std::array<DoIntRounds__0_SuperStruct, 21>;
struct DoIntRoundsStruct {
  Val24Array _super;
};
struct MultiplyByMExt_Super_SuperStruct {
  Val _super;
};
using MultiplyByMExt_Super_SuperStruct24Array = std::array<MultiplyByMExt_Super_SuperStruct, 24>;
struct MultiplyByMExtStruct {
  MultiplyByMExt_Super_SuperStruct24Array _super;
};
using Val8Array = std::array<Val, 8>;
using NondetRegStruct8Array = std::array<NondetRegStruct, 8>;
struct OneHot_8_Struct {
  NondetRegStruct8Array _super;
};
using Val800Array = std::array<Val, 800>;
struct TopStateBitsStruct {
  NondetRegStruct _super;
};
using TopStateBitsStruct800Array = std::array<TopStateBitsStruct, 800>;
using Val100Array = std::array<Val, 100>;
struct TopStateKflatStruct {
  NondetRegStruct _super;
};
using TopStateKflatStruct100Array = std::array<TopStateKflatStruct, 100>;
struct TopStateStruct {
  TopStateBitsStruct800Array bits;
  TopStateKflatStruct100Array kflat;
  NondetRegStruct24Array pflat;
};
using Val7Array = std::array<Val, 7>;
using NondetRegStruct7Array = std::array<NondetRegStruct, 7>;
struct OneHot_7_Struct {
  NondetRegStruct7Array _super;
};
using Val16Array = std::array<Val, 16>;
using Val50Array = std::array<Val, 50>;
struct DivStruct {
  Val _super;
};
using DivStruct800Array = std::array<DivStruct, 800>;
struct UnpackReg_800__16__SuperStruct {
  NondetRegStruct _super;
};
using UnpackReg_800__16__SuperStruct800Array = std::array<UnpackReg_800__16__SuperStruct, 800>;
struct UnpackReg_800__16_Struct {
  UnpackReg_800__16__SuperStruct800Array _super;
};
struct ReadCycleLoadStruct {
  NondetRegStruct _super;
};
using ReadCycleLoadStruct100Array = std::array<ReadCycleLoadStruct, 100>;
using TopStateKflatStruct50Array = std::array<TopStateKflatStruct, 50>;
struct DigestRegValuesStruct {
};
using DigestRegValuesStruct8Array = std::array<DigestRegValuesStruct, 8>;
struct DigestRegStruct {
};
struct ControlStateStruct {
  NondetRegStruct cycleType;
  NondetRegStruct subType;
  NondetRegStruct round;
};
using Val11Array = std::array<Val, 11>;
struct OneHot_11__SuperStruct {
  NondetRegStruct _super;
};
using OneHot_11__SuperStruct11Array = std::array<OneHot_11__SuperStruct, 11>;
struct OneHot_11_Struct {
  OneHot_11__SuperStruct11Array _super;
};
struct WrapOneHot_SuperStruct {
  NondetRegStruct _super;
};
using WrapOneHot_SuperStruct11Array = std::array<WrapOneHot_SuperStruct, 11>;
struct WrapOneHotStruct {
  WrapOneHot_SuperStruct11Array _super;
};
struct TopStruct {
};
