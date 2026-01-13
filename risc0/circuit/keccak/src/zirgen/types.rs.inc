pub struct NondetRegLayout {
    pub _super: &'static Reg,
}
impl risc0_zkp::layout::Component for NondetRegLayout {
    fn ty_name(&self) -> &'static str {
        "NondetRegLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct IsZeroLayout {
    pub _super: &'static NondetRegLayout,
    pub inv: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for IsZeroLayout {
    fn ty_name(&self) -> &'static str {
        "IsZeroLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("inv", self.inv)?;
        Ok(())
    }
}
pub struct CycleCounterLayout {
    pub _super: &'static NondetRegLayout,
    pub is_first_cycle: &'static IsZeroLayout,
}
impl risc0_zkp::layout::Component for CycleCounterLayout {
    fn ty_name(&self) -> &'static str {
        "CycleCounterLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("is_first_cycle", self.is_first_cycle)?;
        Ok(())
    }
}
pub type NondetRegLayout11LayoutArray = [&'static NondetRegLayout; 11];
pub struct WrapOneHotLayout {
    pub _super: &'static NondetRegLayout11LayoutArray,
}
impl risc0_zkp::layout::Component for WrapOneHotLayout {
    fn ty_name(&self) -> &'static str {
        "WrapOneHotLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct ControlStateLayout {
    pub cycle_type: &'static NondetRegLayout,
    pub sub_type: &'static NondetRegLayout,
    pub round: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ControlStateLayout {
    fn ty_name(&self) -> &'static str {
        "ControlStateLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("cycle_type", self.cycle_type)?;
        v.visit_component("sub_type", self.sub_type)?;
        v.visit_component("round", self.round)?;
        Ok(())
    }
}
pub struct ComputeCurrentStep_SuperArm2_SuperLayout {
    pub _super: &'static ControlStateLayout,
    pub arm0: &'static ControlStateLayout,
    pub arm1: &'static ControlStateLayout,
}
impl risc0_zkp::layout::Component for ComputeCurrentStep_SuperArm2_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ComputeCurrentStep_SuperArm2_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct KeccackNextRound_SuperLayout {
    pub _super: &'static ControlStateLayout,
    pub arm0: &'static ControlStateLayout,
    pub arm1: &'static ControlStateLayout,
}
impl risc0_zkp::layout::Component for KeccackNextRound_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "KeccackNextRound_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct KeccackNextRoundLayout {
    pub _super: &'static KeccackNextRound_SuperLayout,
    pub is_last: &'static IsZeroLayout,
}
impl risc0_zkp::layout::Component for KeccackNextRoundLayout {
    fn ty_name(&self) -> &'static str {
        "KeccackNextRoundLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("is_last", self.is_last)?;
        Ok(())
    }
}
pub struct CheckNextPreimage_SuperLayout {
    pub _super: &'static ControlStateLayout,
    pub arm0: &'static ControlStateLayout,
    pub arm1: &'static ControlStateLayout,
}
impl risc0_zkp::layout::Component for CheckNextPreimage_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "CheckNextPreimage_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct CheckNextPreimageLayout {
    pub _super: &'static CheckNextPreimage_SuperLayout,
    pub more: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for CheckNextPreimageLayout {
    fn ty_name(&self) -> &'static str {
        "CheckNextPreimageLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("more", self.more)?;
        Ok(())
    }
}
pub struct Poseidon2NextRound_SuperLayout {
    pub _super: &'static ControlStateLayout,
    pub arm0: &'static ControlStateLayout,
    pub arm1: &'static ControlStateLayout,
    pub arm2: &'static CheckNextPreimageLayout,
}
impl risc0_zkp::layout::Component for Poseidon2NextRound_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "Poseidon2NextRound_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        Ok(())
    }
}
pub struct Poseidon2NextRoundLayout {
    pub _super: &'static Poseidon2NextRound_SuperLayout,
    pub is_last: &'static IsZeroLayout,
    pub is_last_read: &'static NondetRegLayout,
    pub is_last_write: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for Poseidon2NextRoundLayout {
    fn ty_name(&self) -> &'static str {
        "Poseidon2NextRoundLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("is_last", self.is_last)?;
        v.visit_component("is_last_read", self.is_last_read)?;
        v.visit_component("is_last_write", self.is_last_write)?;
        Ok(())
    }
}
pub struct ComputeCurrentStep_SuperLayout {
    pub _super: &'static ControlStateLayout,
    pub arm0: &'static ControlStateLayout,
    pub arm1: &'static ControlStateLayout,
    pub arm2: &'static ComputeCurrentStep_SuperArm2_SuperLayout,
    pub arm3: &'static ControlStateLayout,
    pub arm4: &'static ControlStateLayout,
    pub arm5: &'static ControlStateLayout,
    pub arm6: &'static ControlStateLayout,
    pub arm7: &'static ControlStateLayout,
    pub arm8: &'static KeccackNextRoundLayout,
    pub arm9: &'static Poseidon2NextRoundLayout,
    pub arm10: &'static ControlStateLayout,
}
impl risc0_zkp::layout::Component for ComputeCurrentStep_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ComputeCurrentStep_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        v.visit_component("arm10", self.arm10)?;
        Ok(())
    }
}
pub struct TopControlStateLayout {
    pub _super: &'static ControlStateLayout,
    pub arm0: &'static ControlStateLayout,
    pub arm1: &'static ComputeCurrentStep_SuperLayout,
}
impl risc0_zkp::layout::Component for TopControlStateLayout {
    fn ty_name(&self) -> &'static str {
        "TopControlStateLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct OneHot_11_Layout {
    pub _super: &'static NondetRegLayout11LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_11_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_11_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub type NondetRegLayout800LayoutArray = [&'static NondetRegLayout; 800];
pub type NondetRegLayout100LayoutArray = [&'static NondetRegLayout; 100];
pub type NondetRegLayout24LayoutArray = [&'static NondetRegLayout; 24];
pub struct TopStateLayout {
    pub bits: &'static NondetRegLayout800LayoutArray,
    pub kflat: &'static NondetRegLayout100LayoutArray,
    pub pflat: &'static NondetRegLayout24LayoutArray,
}
impl risc0_zkp::layout::Component for TopStateLayout {
    fn ty_name(&self) -> &'static str {
        "TopStateLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("bits", self.bits)?;
        v.visit_component("kflat", self.kflat)?;
        v.visit_component("pflat", self.pflat)?;
        Ok(())
    }
}
pub struct ReadCycleLayout {
    pub _super: &'static TopStateLayout,
    pub load: &'static NondetRegLayout100LayoutArray,
}
impl risc0_zkp::layout::Component for ReadCycleLayout {
    fn ty_name(&self) -> &'static str {
        "ReadCycleLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("load", self.load)?;
        Ok(())
    }
}
pub struct UnpackReg_800__16_Layout {
    pub _super: &'static NondetRegLayout800LayoutArray,
}
impl risc0_zkp::layout::Component for UnpackReg_800__16_Layout {
    fn ty_name(&self) -> &'static str {
        "UnpackReg_800__16_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct ExpandCycleLayout {
    pub _super: &'static TopStateLayout,
    pub bits: &'static UnpackReg_800__16_Layout,
}
impl risc0_zkp::layout::Component for ExpandCycleLayout {
    fn ty_name(&self) -> &'static str {
        "ExpandCycleLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("bits", self.bits)?;
        Ok(())
    }
}
pub type NondetRegLayout64LayoutArray = [&'static NondetRegLayout; 64];
pub struct ThetaP1_Super_SuperLayout {
    pub _super: &'static NondetRegLayout64LayoutArray,
}
impl risc0_zkp::layout::Component for ThetaP1_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ThetaP1_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub type ThetaP1_Super_SuperLayout5LayoutArray = [&'static ThetaP1_Super_SuperLayout; 5];
pub struct ThetaP1Layout {
    pub _super: &'static ThetaP1_Super_SuperLayout5LayoutArray,
}
impl risc0_zkp::layout::Component for ThetaP1Layout {
    fn ty_name(&self) -> &'static str {
        "ThetaP1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct KeccakRound0Layout {
    pub _super: &'static TopStateLayout,
    pub b: &'static ThetaP1Layout,
}
impl risc0_zkp::layout::Component for KeccakRound0Layout {
    fn ty_name(&self) -> &'static str {
        "KeccakRound0Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("b", self.b)?;
        Ok(())
    }
}
pub struct OneHot_24_Layout {
    pub _super: &'static NondetRegLayout24LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_24_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_24_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct RoundToArrayLayout {
    pub split: &'static OneHot_24_Layout,
}
impl risc0_zkp::layout::Component for RoundToArrayLayout {
    fn ty_name(&self) -> &'static str {
        "RoundToArrayLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("split", self.split)?;
        Ok(())
    }
}
pub struct IotaLayout {
    pub iota_array: &'static RoundToArrayLayout,
}
impl risc0_zkp::layout::Component for IotaLayout {
    fn ty_name(&self) -> &'static str {
        "IotaLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("iota_array", self.iota_array)?;
        Ok(())
    }
}
pub struct KeccakRound34_0_Layout {
    pub _super: &'static TopStateLayout,
    pub _0: &'static IotaLayout,
}
impl risc0_zkp::layout::Component for KeccakRound34_0_Layout {
    fn ty_name(&self) -> &'static str {
        "KeccakRound34_0_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub struct KeccakRound34_1_Layout {
    pub _super: &'static TopStateLayout,
    pub _0: &'static IotaLayout,
}
impl risc0_zkp::layout::Component for KeccakRound34_1_Layout {
    fn ty_name(&self) -> &'static str {
        "KeccakRound34_1_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("_0", self._0)?;
        Ok(())
    }
}
pub type NondetRegLayout7LayoutArray = [&'static NondetRegLayout; 7];
pub struct OneHot_7_Layout {
    pub _super: &'static NondetRegLayout7LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_7_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_7_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct SBoxLayout {
    pub _super: &'static NondetRegLayout,
    pub cubed: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for SBoxLayout {
    fn ty_name(&self) -> &'static str {
        "SBoxLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("cubed", self.cubed)?;
        Ok(())
    }
}
pub type SBoxLayout24LayoutArray = [&'static SBoxLayout; 24];
pub struct DoExtRoundLayout {
    pub _1: &'static SBoxLayout24LayoutArray,
}
impl risc0_zkp::layout::Component for DoExtRoundLayout {
    fn ty_name(&self) -> &'static str {
        "DoExtRoundLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_1", self._1)?;
        Ok(())
    }
}
pub type NondetRegLayout8LayoutArray = [&'static NondetRegLayout; 8];
pub struct OneHot_8_Layout {
    pub _super: &'static NondetRegLayout8LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_8_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_8_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct DoExtRoundByIdxLayout {
    pub _super: &'static DoExtRoundLayout,
    pub idx_hot: &'static OneHot_8_Layout,
}
impl risc0_zkp::layout::Component for DoExtRoundByIdxLayout {
    fn ty_name(&self) -> &'static str {
        "DoExtRoundByIdxLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("idx_hot", self.idx_hot)?;
        Ok(())
    }
}
pub struct DoIntRoundLayout {
    pub sbox: &'static SBoxLayout,
}
impl risc0_zkp::layout::Component for DoIntRoundLayout {
    fn ty_name(&self) -> &'static str {
        "DoIntRoundLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("sbox", self.sbox)?;
        Ok(())
    }
}
pub type DoIntRoundLayout21LayoutArray = [&'static DoIntRoundLayout; 21];
pub struct DoIntRoundsLayout {
    pub _super: &'static DoIntRoundLayout21LayoutArray,
}
impl risc0_zkp::layout::Component for DoIntRoundsLayout {
    fn ty_name(&self) -> &'static str {
        "DoIntRoundsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct DoSpongeLayout {
    pub _super: &'static DoExtRoundByIdxLayout,
    pub stage0x: &'static NondetRegLayout24LayoutArray,
    pub stage1: &'static DoExtRoundByIdxLayout,
    pub stage2: &'static DoExtRoundByIdxLayout,
    pub stage3: &'static DoExtRoundByIdxLayout,
    pub stage4: &'static DoExtRoundByIdxLayout,
    pub stage5: &'static DoIntRoundsLayout,
    pub stage6: &'static DoExtRoundByIdxLayout,
    pub stage7: &'static DoExtRoundByIdxLayout,
    pub stage8: &'static DoExtRoundByIdxLayout,
}
impl risc0_zkp::layout::Component for DoSpongeLayout {
    fn ty_name(&self) -> &'static str {
        "DoSpongeLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("stage0x", self.stage0x)?;
        v.visit_component("stage1", self.stage1)?;
        v.visit_component("stage2", self.stage2)?;
        v.visit_component("stage3", self.stage3)?;
        v.visit_component("stage4", self.stage4)?;
        v.visit_component("stage5", self.stage5)?;
        v.visit_component("stage6", self.stage6)?;
        v.visit_component("stage7", self.stage7)?;
        v.visit_component("stage8", self.stage8)?;
        Ok(())
    }
}
pub struct Poseidon2CycleLayout {
    pub _super: &'static TopStateLayout,
    pub round_oh: &'static OneHot_7_Layout,
    pub state_out: &'static DoSpongeLayout,
}
impl risc0_zkp::layout::Component for Poseidon2CycleLayout {
    fn ty_name(&self) -> &'static str {
        "Poseidon2CycleLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("round_oh", self.round_oh)?;
        v.visit_component("state_out", self.state_out)?;
        Ok(())
    }
}
pub struct TopCurStateLayout {
    pub _super: &'static TopStateLayout,
    pub arm0: &'static TopStateLayout,
    pub arm1: &'static ReadCycleLayout,
    pub arm2: &'static ExpandCycleLayout,
    pub arm3: &'static TopStateLayout,
    pub arm4: &'static KeccakRound0Layout,
    pub arm5: &'static TopStateLayout,
    pub arm6: &'static TopStateLayout,
    pub arm7: &'static KeccakRound34_0_Layout,
    pub arm8: &'static KeccakRound34_1_Layout,
    pub arm9: &'static Poseidon2CycleLayout,
    pub arm10: &'static TopStateLayout,
}
impl risc0_zkp::layout::Component for TopCurStateLayout {
    fn ty_name(&self) -> &'static str {
        "TopCurStateLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        v.visit_component("arm2", self.arm2)?;
        v.visit_component("arm3", self.arm3)?;
        v.visit_component("arm4", self.arm4)?;
        v.visit_component("arm5", self.arm5)?;
        v.visit_component("arm6", self.arm6)?;
        v.visit_component("arm7", self.arm7)?;
        v.visit_component("arm8", self.arm8)?;
        v.visit_component("arm9", self.arm9)?;
        v.visit_component("arm10", self.arm10)?;
        Ok(())
    }
}
pub struct DigestRegLayout {
    pub values: &'static NondetRegLayout8LayoutArray,
}
impl risc0_zkp::layout::Component for DigestRegLayout {
    fn ty_name(&self) -> &'static str {
        "DigestRegLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("values", self.values)?;
        Ok(())
    }
}
pub struct TopLayout {
    pub cycle: &'static CycleCounterLayout,
    pub cycle_mux: &'static WrapOneHotLayout,
    pub control_state: &'static ControlStateLayout,
    pub control_state_redef: &'static TopControlStateLayout,
    pub one_hot: &'static OneHot_11_Layout,
    pub cur_state: &'static TopStateLayout,
    pub cur_state_redef: &'static TopCurStateLayout,
}
impl risc0_zkp::layout::Component for TopLayout {
    fn ty_name(&self) -> &'static str {
        "TopLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("cycle", self.cycle)?;
        v.visit_component("cycle_mux", self.cycle_mux)?;
        v.visit_component("control_state", self.control_state)?;
        v.visit_component("control_state_redef", self.control_state_redef)?;
        v.visit_component("one_hot", self.one_hot)?;
        v.visit_component("cur_state", self.cur_state)?;
        v.visit_component("cur_state_redef", self.cur_state_redef)?;
        Ok(())
    }
}
pub struct _globalLayout {
    pub final_digest: &'static DigestRegLayout,
    pub total_cycles: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for _globalLayout {
    fn ty_name(&self) -> &'static str {
        "_globalLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("final_digest", self.final_digest)?;
        v.visit_component("total_cycles", self.total_cycles)?;
        Ok(())
    }
}
#[derive(Copy, Clone, Debug)]
pub struct NondetRegStruct {
    pub _super: Val,
}
#[derive(Copy, Clone, Debug)]
pub struct ComponentStruct {}
#[derive(Copy, Clone, Debug)]
pub struct CycleCounterStruct {
    pub is_first_cycle: NondetRegStruct,
}
pub type Val5Array = [Val; 5];
pub type Val64Array = [Val; 64];
pub type Val64Array5Array = [Val64Array; 5];
pub type Val64Array5Array5Array = [Val64Array5Array; 5];
#[derive(Copy, Clone, Debug)]
pub struct ThetaP1_Super_Super_SuperStruct {
    pub _super: NondetRegStruct,
}
pub type ThetaP1_Super_Super_SuperStruct64Array = [ThetaP1_Super_Super_SuperStruct; 64];
#[derive(Copy, Clone, Debug)]
pub struct ThetaP1_Super_SuperStruct {
    pub _super: ThetaP1_Super_Super_SuperStruct64Array,
}
pub type ThetaP1_Super_SuperStruct5Array = [ThetaP1_Super_SuperStruct; 5];
#[derive(Copy, Clone, Debug)]
pub struct ThetaP1Struct {
    pub _super: ThetaP1_Super_SuperStruct5Array,
}
pub type Val24Array = [Val; 24];
pub type NondetRegStruct24Array = [NondetRegStruct; 24];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_24_Struct {
    pub _super: NondetRegStruct24Array,
}
#[derive(Copy, Clone, Debug)]
pub struct RoundToArray_Super_SuperStruct {
    pub _super: Val,
}
pub type RoundToArray_Super_SuperStruct64Array = [RoundToArray_Super_SuperStruct; 64];
#[derive(Copy, Clone, Debug)]
pub struct RoundToArrayStruct {
    pub _super: RoundToArray_Super_SuperStruct64Array,
}
#[derive(Copy, Clone, Debug)]
pub struct Iota_Super_Super_Super_SuperStruct {
    pub _super: Val64Array,
}
pub type Iota_Super_Super_Super_SuperStruct5Array = [Iota_Super_Super_Super_SuperStruct; 5];
#[derive(Copy, Clone, Debug)]
pub struct Iota_Super_SuperStruct {
    pub _super: Iota_Super_Super_Super_SuperStruct5Array,
}
pub type Iota_Super_SuperStruct5Array = [Iota_Super_SuperStruct; 5];
#[derive(Copy, Clone, Debug)]
pub struct IotaStruct {
    pub _super: Iota_Super_SuperStruct5Array,
}
#[derive(Copy, Clone, Debug)]
pub struct MultiplyByMInt_Super_SuperStruct {
    pub _super: Val,
}
pub type MultiplyByMInt_Super_SuperStruct24Array = [MultiplyByMInt_Super_SuperStruct; 24];
#[derive(Copy, Clone, Debug)]
pub struct MultiplyByMIntStruct {
    pub _super: MultiplyByMInt_Super_SuperStruct24Array,
}
pub type Val21Array = [Val; 21];
#[derive(Copy, Clone, Debug)]
pub struct DoIntRoundsStruct {
    pub _super: Val24Array,
}
#[derive(Copy, Clone, Debug)]
pub struct MultiplyByMExt_Super_SuperStruct {
    pub _super: Val,
}
pub type MultiplyByMExt_Super_SuperStruct24Array = [MultiplyByMExt_Super_SuperStruct; 24];
#[derive(Copy, Clone, Debug)]
pub struct MultiplyByMExtStruct {
    pub _super: MultiplyByMExt_Super_SuperStruct24Array,
}
pub type Val8Array = [Val; 8];
pub type NondetRegStruct8Array = [NondetRegStruct; 8];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_8_Struct {
    pub _super: NondetRegStruct8Array,
}
pub type Val800Array = [Val; 800];
#[derive(Copy, Clone, Debug)]
pub struct TopStateBitsStruct {
    pub _super: NondetRegStruct,
}
pub type TopStateBitsStruct800Array = [TopStateBitsStruct; 800];
pub type Val100Array = [Val; 100];
#[derive(Copy, Clone, Debug)]
pub struct TopStateKflatStruct {
    pub _super: NondetRegStruct,
}
pub type TopStateKflatStruct100Array = [TopStateKflatStruct; 100];
#[derive(Copy, Clone, Debug)]
pub struct TopStateStruct {
    pub bits: TopStateBitsStruct800Array,
    pub kflat: TopStateKflatStruct100Array,
    pub pflat: NondetRegStruct24Array,
}
pub type Val7Array = [Val; 7];
pub type NondetRegStruct7Array = [NondetRegStruct; 7];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_7_Struct {
    pub _super: NondetRegStruct7Array,
}
pub type Val16Array = [Val; 16];
pub type Val50Array = [Val; 50];
#[derive(Copy, Clone, Debug)]
pub struct DivStruct {
    pub _super: Val,
}
pub type DivStruct800Array = [DivStruct; 800];
#[derive(Copy, Clone, Debug)]
pub struct UnpackReg_800__16__SuperStruct {
    pub _super: NondetRegStruct,
}
pub type UnpackReg_800__16__SuperStruct800Array = [UnpackReg_800__16__SuperStruct; 800];
#[derive(Copy, Clone, Debug)]
pub struct UnpackReg_800__16_Struct {
    pub _super: UnpackReg_800__16__SuperStruct800Array,
}
#[derive(Copy, Clone, Debug)]
pub struct ReadCycleLoadStruct {
    pub _super: NondetRegStruct,
}
pub type ReadCycleLoadStruct100Array = [ReadCycleLoadStruct; 100];
pub type TopStateKflatStruct50Array = [TopStateKflatStruct; 50];
#[derive(Copy, Clone, Debug)]
pub struct DigestRegValuesStruct {}
pub type DigestRegValuesStruct8Array = [DigestRegValuesStruct; 8];
#[derive(Copy, Clone, Debug)]
pub struct DigestRegStruct {}
#[derive(Copy, Clone, Debug)]
pub struct ControlStateStruct {
    pub cycle_type: NondetRegStruct,
    pub sub_type: NondetRegStruct,
    pub round: NondetRegStruct,
}
pub type Val11Array = [Val; 11];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_11__SuperStruct {
    pub _super: NondetRegStruct,
}
pub type OneHot_11__SuperStruct11Array = [OneHot_11__SuperStruct; 11];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_11_Struct {
    pub _super: OneHot_11__SuperStruct11Array,
}
#[derive(Copy, Clone, Debug)]
pub struct WrapOneHot_SuperStruct {
    pub _super: NondetRegStruct,
}
pub type WrapOneHot_SuperStruct11Array = [WrapOneHot_SuperStruct; 11];
#[derive(Copy, Clone, Debug)]
pub struct WrapOneHotStruct {
    pub _super: WrapOneHot_SuperStruct11Array,
}
#[derive(Copy, Clone, Debug)]
pub struct TopStruct {}
