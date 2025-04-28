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
pub type NondetRegLayout12LayoutArray = [&'static NondetRegLayout; 12];
pub struct WrapOneHotLayout {
    pub _super: &'static NondetRegLayout12LayoutArray,
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
    pub block: &'static NondetRegLayout,
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
        v.visit_component("block", self.block)?;
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
pub struct ShaNextRound_SuperLayout {
    pub _super: &'static ControlStateLayout,
    pub arm0: &'static ControlStateLayout,
    pub arm1: &'static ControlStateLayout,
}
impl risc0_zkp::layout::Component for ShaNextRound_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ShaNextRound_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ShaNextRoundLayout {
    pub _super: &'static ShaNextRound_SuperLayout,
    pub is_last: &'static IsZeroLayout,
}
impl risc0_zkp::layout::Component for ShaNextRoundLayout {
    fn ty_name(&self) -> &'static str {
        "ShaNextRoundLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("is_last", self.is_last)?;
        Ok(())
    }
}
pub struct ShaNextBlock_SuperArm2_Super_SuperLayout {
    pub _super: &'static ControlStateLayout,
    pub arm0: &'static ControlStateLayout,
    pub arm1: &'static ControlStateLayout,
}
impl risc0_zkp::layout::Component for ShaNextBlock_SuperArm2_Super_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ShaNextBlock_SuperArm2_Super_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct ShaNextBlock_SuperArm2_SuperLayout {
    pub _super: &'static ShaNextBlock_SuperArm2_Super_SuperLayout,
    pub more: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ShaNextBlock_SuperArm2_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ShaNextBlock_SuperArm2_SuperLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("more", self.more)?;
        Ok(())
    }
}
pub struct ShaNextBlock_SuperLayout {
    pub _super: &'static ControlStateLayout,
    pub arm0: &'static ControlStateLayout,
    pub arm1: &'static ControlStateLayout,
    pub arm2: &'static ShaNextBlock_SuperArm2_SuperLayout,
}
impl risc0_zkp::layout::Component for ShaNextBlock_SuperLayout {
    fn ty_name(&self) -> &'static str {
        "ShaNextBlock_SuperLayout"
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
pub struct ShaNextBlockLayout {
    pub _super: &'static ShaNextBlock_SuperLayout,
    pub is_last: &'static IsZeroLayout,
    pub is_sub0: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for ShaNextBlockLayout {
    fn ty_name(&self) -> &'static str {
        "ShaNextBlockLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("is_last", self.is_last)?;
        v.visit_component("is_sub0", self.is_sub0)?;
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
    pub arm9: &'static ShaNextRoundLayout,
    pub arm10: &'static ShaNextBlockLayout,
    pub arm11: &'static ControlStateLayout,
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
        v.visit_component("arm11", self.arm11)?;
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
pub struct OneHot_12_Layout {
    pub _super: &'static NondetRegLayout12LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_12_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_12_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub type NondetRegLayout800LayoutArray = [&'static NondetRegLayout; 800];
pub type NondetRegLayout100LayoutArray = [&'static NondetRegLayout; 100];
pub type NondetRegLayout16LayoutArray = [&'static NondetRegLayout; 16];
pub struct TopStateLayout {
    pub bits: &'static NondetRegLayout800LayoutArray,
    pub kflat: &'static NondetRegLayout100LayoutArray,
    pub sflat: &'static NondetRegLayout16LayoutArray,
}
impl risc0_zkp::layout::Component for TopStateLayout {
    fn ty_name(&self) -> &'static str {
        "TopStateLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("bits", self.bits)?;
        v.visit_component("kflat", self.kflat)?;
        v.visit_component("sflat", self.sflat)?;
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
pub struct ReadCycleLayout {
    pub _super: &'static TopStateLayout,
    pub load: &'static NondetRegLayout100LayoutArray,
    pub bits: &'static UnpackReg_800__16_Layout,
}
impl risc0_zkp::layout::Component for ReadCycleLayout {
    fn ty_name(&self) -> &'static str {
        "ReadCycleLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("load", self.load)?;
        v.visit_component("bits", self.bits)?;
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
pub struct WriteCycleLayout {
    pub _super: &'static TopStateLayout,
    pub bits: &'static UnpackReg_800__16_Layout,
}
impl risc0_zkp::layout::Component for WriteCycleLayout {
    fn ty_name(&self) -> &'static str {
        "WriteCycleLayout"
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
pub type NondetRegLayout24LayoutArray = [&'static NondetRegLayout; 24];
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
pub type NondetRegLayout4LayoutArray = [&'static NondetRegLayout; 4];
pub struct OneHot_4_Layout {
    pub _super: &'static NondetRegLayout4LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot_4_Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot_4_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct LoadWinLayout {
    pub block_select: &'static OneHot_4_Layout,
}
impl risc0_zkp::layout::Component for LoadWinLayout {
    fn ty_name(&self) -> &'static str {
        "LoadWinLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("block_select", self.block_select)?;
        Ok(())
    }
}
pub type NondetRegLayout32LayoutArray = [&'static NondetRegLayout; 32];
pub struct ExpandBELayout {
    pub _super: &'static NondetRegLayout32LayoutArray,
}
impl risc0_zkp::layout::Component for ExpandBELayout {
    fn ty_name(&self) -> &'static str {
        "ExpandBELayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct UnpackReg_32__16_Layout {
    pub _super: &'static NondetRegLayout32LayoutArray,
}
impl risc0_zkp::layout::Component for UnpackReg_32__16_Layout {
    fn ty_name(&self) -> &'static str {
        "UnpackReg_32__16_Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct CarryExtractLayout {
    pub bit0: &'static NondetRegLayout,
    pub bit1: &'static NondetRegLayout,
    pub bit2: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for CarryExtractLayout {
    fn ty_name(&self) -> &'static str {
        "CarryExtractLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("bit0", self.bit0)?;
        v.visit_component("bit1", self.bit1)?;
        v.visit_component("bit2", self.bit2)?;
        Ok(())
    }
}
pub struct CarryAndExpandLayout {
    pub _super: &'static UnpackReg_32__16_Layout,
    pub low_carry: &'static CarryExtractLayout,
    pub high_carry: &'static CarryExtractLayout,
}
impl risc0_zkp::layout::Component for CarryAndExpandLayout {
    fn ty_name(&self) -> &'static str {
        "CarryAndExpandLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("low_carry", self.low_carry)?;
        v.visit_component("high_carry", self.high_carry)?;
        Ok(())
    }
}
pub struct DoShaStepWLayout {
    pub _super: &'static NondetRegLayout32LayoutArray,
    pub arm0: &'static ExpandBELayout,
    pub arm1: &'static CarryAndExpandLayout,
}
impl risc0_zkp::layout::Component for DoShaStepWLayout {
    fn ty_name(&self) -> &'static str {
        "DoShaStepWLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("arm0", self.arm0)?;
        v.visit_component("arm1", self.arm1)?;
        Ok(())
    }
}
pub struct DoShaStepLayout {
    pub w: &'static DoShaStepWLayout,
    pub a: &'static CarryAndExpandLayout,
    pub e: &'static CarryAndExpandLayout,
}
impl risc0_zkp::layout::Component for DoShaStepLayout {
    fn ty_name(&self) -> &'static str {
        "DoShaStepLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("w", self.w)?;
        v.visit_component("a", self.a)?;
        v.visit_component("e", self.e)?;
        Ok(())
    }
}
pub type DoShaStepLayout8LayoutArray = [&'static DoShaStepLayout; 8];
pub struct ShaCycleLayout {
    pub _super: &'static TopStateLayout,
    pub one_hot: &'static OneHot_8_Layout,
    pub is_load: &'static NondetRegLayout,
    pub win: &'static LoadWinLayout,
    pub step0: &'static DoShaStepLayout,
    pub step1: &'static DoShaStepLayout,
    pub step2: &'static DoShaStepLayout,
    pub step3: &'static DoShaStepLayout,
    pub step4: &'static DoShaStepLayout,
    pub step5: &'static DoShaStepLayout,
    pub step6: &'static DoShaStepLayout,
    pub step7: &'static DoShaStepLayout,
    pub steps: &'static DoShaStepLayout8LayoutArray,
}
impl risc0_zkp::layout::Component for ShaCycleLayout {
    fn ty_name(&self) -> &'static str {
        "ShaCycleLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("one_hot", self.one_hot)?;
        v.visit_component("is_load", self.is_load)?;
        v.visit_component("win", self.win)?;
        v.visit_component("step0", self.step0)?;
        v.visit_component("step1", self.step1)?;
        v.visit_component("step2", self.step2)?;
        v.visit_component("step3", self.step3)?;
        v.visit_component("step4", self.step4)?;
        v.visit_component("step5", self.step5)?;
        v.visit_component("step6", self.step6)?;
        v.visit_component("step7", self.step7)?;
        v.visit_component("steps", self.steps)?;
        Ok(())
    }
}
pub type CarryAndExpandLayout4LayoutArray = [&'static CarryAndExpandLayout; 4];
pub struct ShaNextBlockCycleLayout {
    pub _super: &'static TopStateLayout,
    pub tot_a: &'static CarryAndExpandLayout4LayoutArray,
    pub tot_e: &'static CarryAndExpandLayout4LayoutArray,
}
impl risc0_zkp::layout::Component for ShaNextBlockCycleLayout {
    fn ty_name(&self) -> &'static str {
        "ShaNextBlockCycleLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("tot_a", self.tot_a)?;
        v.visit_component("tot_e", self.tot_e)?;
        Ok(())
    }
}
pub struct TopCurStateLayout {
    pub _super: &'static TopStateLayout,
    pub arm0: &'static TopStateLayout,
    pub arm1: &'static ReadCycleLayout,
    pub arm2: &'static ExpandCycleLayout,
    pub arm3: &'static WriteCycleLayout,
    pub arm4: &'static KeccakRound0Layout,
    pub arm5: &'static TopStateLayout,
    pub arm6: &'static TopStateLayout,
    pub arm7: &'static KeccakRound34_0_Layout,
    pub arm8: &'static KeccakRound34_1_Layout,
    pub arm9: &'static ShaCycleLayout,
    pub arm10: &'static ShaNextBlockCycleLayout,
    pub arm11: &'static TopStateLayout,
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
        v.visit_component("arm11", self.arm11)?;
        Ok(())
    }
}
pub struct DigestRegLayout {
    pub values: &'static NondetRegLayout16LayoutArray,
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
    pub one_hot: &'static OneHot_12_Layout,
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
pub struct NondetBitRegStruct {
    pub _super: NondetRegStruct,
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
    pub _super: NondetBitRegStruct,
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
pub type NondetBitRegStruct24Array = [NondetBitRegStruct; 24];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_24_Struct {
    pub _super: NondetBitRegStruct24Array,
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
pub struct CarryExtractStruct {
    pub carry: Val,
    pub out: Val,
}
pub type Val2Array = [Val; 2];
#[derive(Copy, Clone, Debug)]
pub struct DivStruct {
    pub _super: Val,
}
pub type DivStruct32Array = [DivStruct; 32];
pub type Val32Array = [Val; 32];
#[derive(Copy, Clone, Debug)]
pub struct UnpackReg_32__16__SuperStruct {
    pub _super: NondetBitRegStruct,
}
pub type UnpackReg_32__16__SuperStruct32Array = [UnpackReg_32__16__SuperStruct; 32];
#[derive(Copy, Clone, Debug)]
pub struct UnpackReg_32__16_Struct {
    pub _super: UnpackReg_32__16__SuperStruct32Array,
}
pub type NondetBitRegStruct32Array = [NondetBitRegStruct; 32];
#[derive(Copy, Clone, Debug)]
pub struct ExpandBEStruct {
    pub _super: NondetBitRegStruct32Array,
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
pub type Val16Array = [Val; 16];
pub type NondetRegStruct16Array = [NondetRegStruct; 16];
#[derive(Copy, Clone, Debug)]
pub struct TopStateStruct {
    pub bits: TopStateBitsStruct800Array,
    pub kflat: TopStateKflatStruct100Array,
    pub sflat: NondetRegStruct16Array,
}
pub type Val8Array = [Val; 8];
pub type NondetBitRegStruct8Array = [NondetBitRegStruct; 8];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_8_Struct {
    pub _super: NondetBitRegStruct8Array,
}
pub type Val32Array4Array = [Val32Array; 4];
pub type Val32Array16Array = [Val32Array; 16];
#[derive(Copy, Clone, Debug)]
pub struct ShaStateStruct {
    pub a: Val32Array4Array,
    pub e: Val32Array4Array,
    pub w: Val32Array16Array,
}
pub type ComponentStruct32Array = [ComponentStruct; 32];
#[derive(Copy, Clone, Debug)]
pub struct DoShaStepStruct {
    pub w: NondetBitRegStruct32Array,
    pub a: UnpackReg_32__16_Struct,
    pub e: UnpackReg_32__16_Struct,
    pub new_state: ShaStateStruct,
}
pub type Val4Array = [Val; 4];
pub type NondetBitRegStruct4Array = [NondetBitRegStruct; 4];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_4_Struct {
    pub _super: NondetBitRegStruct4Array,
}
pub type Val2Array8Array = [Val2Array; 8];
#[derive(Copy, Clone, Debug)]
pub struct LoadWinStruct {
    pub _super: Val2Array8Array,
}
#[derive(Copy, Clone, Debug)]
pub struct Pack_32__16__Super_SuperStruct {
    pub _super: Val,
}
pub type Pack_32__16__Super_SuperStruct2Array = [Pack_32__16__Super_SuperStruct; 2];
#[derive(Copy, Clone, Debug)]
pub struct Pack_32__16_Struct {
    pub _super: Pack_32__16__Super_SuperStruct2Array,
}
pub type Pack_32__16_Struct4Array = [Pack_32__16_Struct; 4];
pub type NondetRegStruct2Array = [NondetRegStruct; 2];
#[derive(Copy, Clone, Debug)]
pub struct ShaNextBlockCyclePrevA_SuperStruct {
    pub _super: NondetRegStruct2Array,
}
pub type ShaNextBlockCyclePrevA_SuperStruct4Array = [ShaNextBlockCyclePrevA_SuperStruct; 4];
#[derive(Copy, Clone, Debug)]
pub struct ShaNextBlockCyclePrevE_SuperStruct {
    pub _super: NondetRegStruct2Array,
}
pub type ShaNextBlockCyclePrevE_SuperStruct4Array = [ShaNextBlockCyclePrevE_SuperStruct; 4];
pub type UnpackReg_32__16_Struct4Array = [UnpackReg_32__16_Struct; 4];
pub type Val50Array = [Val; 50];
pub type DivStruct800Array = [DivStruct; 800];
#[derive(Copy, Clone, Debug)]
pub struct UnpackReg_800__16__SuperStruct {
    pub _super: NondetBitRegStruct,
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
pub type DigestRegValuesStruct16Array = [DigestRegValuesStruct; 16];
#[derive(Copy, Clone, Debug)]
pub struct DigestRegStruct {}
#[derive(Copy, Clone, Debug)]
pub struct ControlStateStruct {
    pub cycle_type: NondetRegStruct,
    pub sub_type: NondetRegStruct,
    pub block: NondetRegStruct,
    pub round: NondetRegStruct,
}
pub type Val12Array = [Val; 12];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_12__SuperStruct {
    pub _super: NondetBitRegStruct,
}
pub type OneHot_12__SuperStruct12Array = [OneHot_12__SuperStruct; 12];
#[derive(Copy, Clone, Debug)]
pub struct OneHot_12_Struct {
    pub bits: OneHot_12__SuperStruct12Array,
}
#[derive(Copy, Clone, Debug)]
pub struct WrapOneHot_SuperStruct {
    pub _super: NondetRegStruct,
}
pub type WrapOneHot_SuperStruct12Array = [WrapOneHot_SuperStruct; 12];
#[derive(Copy, Clone, Debug)]
pub struct WrapOneHotStruct {
    pub _super: WrapOneHot_SuperStruct12Array,
}
#[derive(Copy, Clone, Debug)]
pub struct TopStruct {}
