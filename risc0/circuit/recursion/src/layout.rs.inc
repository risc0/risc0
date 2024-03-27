pub struct OneHot {
    pub bit_and_elem: &'static CodeReg,
    pub bit_op_shorts: &'static CodeReg,
    pub nop: &'static CodeReg,
    pub set_global: &'static CodeReg,
    pub sha_fini: &'static CodeReg,
    pub sha_init: &'static CodeReg,
    pub sha_load: &'static CodeReg,
    pub sha_mix: &'static CodeReg,
    pub wom_fini: &'static CodeReg,
    pub wom_init: &'static CodeReg,
}
impl risc0_zkp::layout::Component for OneHot {
    fn ty_name(&self) -> &'static str {
        "OneHot"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("bit_and_elem", self.bit_and_elem)?;
        v.visit_component("bit_op_shorts", self.bit_op_shorts)?;
        v.visit_component("nop", self.nop)?;
        v.visit_component("set_global", self.set_global)?;
        v.visit_component("sha_fini", self.sha_fini)?;
        v.visit_component("sha_init", self.sha_init)?;
        v.visit_component("sha_load", self.sha_load)?;
        v.visit_component("sha_mix", self.sha_mix)?;
        v.visit_component("wom_fini", self.wom_fini)?;
        v.visit_component("wom_init", self.wom_init)?;
        Ok(())
    }
}
pub type CodeReg3LayoutArray = [&'static CodeReg; 3];
pub struct RecursionMacroInst {
    pub opcode: &'static OneHot,
    pub operand: &'static CodeReg3LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionMacroInst {
    fn ty_name(&self) -> &'static str {
        "RecursionMacroInst"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("opcode", self.opcode)?;
        v.visit_component("operand", self.operand)?;
        Ok(())
    }
}
pub struct RecursionMicroInst {
    pub opcode: &'static CodeReg,
    pub operand: &'static CodeReg3LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionMicroInst {
    fn ty_name(&self) -> &'static str {
        "RecursionMicroInst"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("opcode", self.opcode)?;
        v.visit_component("operand", self.operand)?;
        Ok(())
    }
}
pub type RecursionMicroInst3LayoutArray = [&'static RecursionMicroInst; 3];
pub struct RecursionMicroInsts {
    pub inst: &'static RecursionMicroInst3LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionMicroInsts {
    fn ty_name(&self) -> &'static str {
        "RecursionMicroInsts"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("inst", self.inst)?;
        Ok(())
    }
}
pub struct OneHot0 {
    pub c0: &'static CodeReg,
    pub c1: &'static CodeReg,
    pub c2: &'static CodeReg,
    pub c3: &'static CodeReg,
}
impl risc0_zkp::layout::Component for OneHot0 {
    fn ty_name(&self) -> &'static str {
        "OneHot0"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("c0", self.c0)?;
        v.visit_component("c1", self.c1)?;
        v.visit_component("c2", self.c2)?;
        v.visit_component("c3", self.c3)?;
        Ok(())
    }
}
pub struct RecursionPoseidon2FullInst {
    pub cycle: &'static OneHot0,
}
impl risc0_zkp::layout::Component for RecursionPoseidon2FullInst {
    fn ty_name(&self) -> &'static str {
        "RecursionPoseidon2FullInst"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("cycle", self.cycle)?;
        Ok(())
    }
}
pub struct OneHot1 {
    pub g0: &'static CodeReg,
    pub g1: &'static CodeReg,
    pub g2: &'static CodeReg,
}
impl risc0_zkp::layout::Component for OneHot1 {
    fn ty_name(&self) -> &'static str {
        "OneHot1"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("g0", self.g0)?;
        v.visit_component("g1", self.g1)?;
        v.visit_component("g2", self.g2)?;
        Ok(())
    }
}
pub type CodeReg8LayoutArray = [&'static CodeReg; 8];
pub struct RecursionPoseidon2MemInst {
    pub do_mont: &'static CodeReg,
    pub keep_state: &'static CodeReg,
    pub prep_full: &'static CodeReg,
    pub group: &'static OneHot1,
    pub inputs: &'static CodeReg8LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionPoseidon2MemInst {
    fn ty_name(&self) -> &'static str {
        "RecursionPoseidon2MemInst"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("do_mont", self.do_mont)?;
        v.visit_component("keep_state", self.keep_state)?;
        v.visit_component("prep_full", self.prep_full)?;
        v.visit_component("group", self.group)?;
        v.visit_component("inputs", self.inputs)?;
        Ok(())
    }
}
pub struct RecursionPoseidon2Inst {}
impl risc0_zkp::layout::Component for RecursionPoseidon2Inst {
    fn ty_name(&self) -> &'static str {
        "RecursionPoseidon2Inst"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        Ok(())
    }
}
pub struct Mux {
    pub macro_ops: &'static RecursionMacroInst,
    pub micro_ops: &'static RecursionMicroInsts,
    pub poseidon2_full: &'static RecursionPoseidon2FullInst,
    pub poseidon2_load: &'static RecursionPoseidon2MemInst,
    pub poseidon2_partial: &'static RecursionPoseidon2Inst,
    pub poseidon2_store: &'static RecursionPoseidon2MemInst,
}
impl risc0_zkp::layout::Component for Mux {
    fn ty_name(&self) -> &'static str {
        "Mux"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("macro_ops", self.macro_ops)?;
        v.visit_component("micro_ops", self.micro_ops)?;
        v.visit_component("poseidon2_full", self.poseidon2_full)?;
        v.visit_component("poseidon2_load", self.poseidon2_load)?;
        v.visit_component("poseidon2_partial", self.poseidon2_partial)?;
        v.visit_component("poseidon2_store", self.poseidon2_store)?;
        Ok(())
    }
}
pub struct OneHot2 {
    pub macro_ops: &'static CodeReg,
    pub micro_ops: &'static CodeReg,
    pub poseidon2_full: &'static CodeReg,
    pub poseidon2_load: &'static CodeReg,
    pub poseidon2_partial: &'static CodeReg,
    pub poseidon2_store: &'static CodeReg,
}
impl risc0_zkp::layout::Component for OneHot2 {
    fn ty_name(&self) -> &'static str {
        "OneHot2"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("macro_ops", self.macro_ops)?;
        v.visit_component("micro_ops", self.micro_ops)?;
        v.visit_component("poseidon2_full", self.poseidon2_full)?;
        v.visit_component("poseidon2_load", self.poseidon2_load)?;
        v.visit_component("poseidon2_partial", self.poseidon2_partial)?;
        v.visit_component("poseidon2_store", self.poseidon2_store)?;
        Ok(())
    }
}
pub struct RecursionCode {
    pub write_addr: &'static CodeReg,
    pub inst: &'static Mux,
    pub select: &'static OneHot2,
}
impl risc0_zkp::layout::Component for RecursionCode {
    fn ty_name(&self) -> &'static str {
        "RecursionCode"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("write_addr", self.write_addr)?;
        v.visit_component("inst", self.inst)?;
        v.visit_component("select", self.select)?;
        Ok(())
    }
}
pub type DataReg4LayoutArray = [&'static DataReg; 4];
pub struct RecursionImplWomPlonkElement {
    pub addr: &'static DataReg,
    pub data: &'static DataReg4LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionImplWomPlonkElement {
    fn ty_name(&self) -> &'static str {
        "RecursionImplWomPlonkElement"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("addr", self.addr)?;
        v.visit_component("data", self.data)?;
        Ok(())
    }
}
pub struct RecursionWomReg {
    pub wom: &'static RecursionImplWomPlonkElement,
}
impl risc0_zkp::layout::Component for RecursionWomReg {
    fn ty_name(&self) -> &'static str {
        "RecursionWomReg"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("wom", self.wom)?;
        Ok(())
    }
}
pub struct RecursionWomBody {
    pub plonk_body: &'static RecursionPoseidon2Inst,
}
impl risc0_zkp::layout::Component for RecursionWomBody {
    fn ty_name(&self) -> &'static str {
        "RecursionWomBody"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("plonk_body", self.plonk_body)?;
        Ok(())
    }
}
pub type DataReg31LayoutArray = [&'static DataReg; 31];
pub struct RecursionBitAndElem {
    pub in_a: &'static RecursionWomReg,
    pub in_b: &'static RecursionWomReg,
    pub out: &'static RecursionWomReg,
    pub wom_body: &'static RecursionWomBody,
    pub bits_a: &'static DataReg31LayoutArray,
    pub bits_b: &'static DataReg31LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionBitAndElem {
    fn ty_name(&self) -> &'static str {
        "RecursionBitAndElem"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("in_a", self.in_a)?;
        v.visit_component("in_b", self.in_b)?;
        v.visit_component("out", self.out)?;
        v.visit_component("wom_body", self.wom_body)?;
        v.visit_component("bits_a", self.bits_a)?;
        v.visit_component("bits_b", self.bits_b)?;
        Ok(())
    }
}
pub type DataReg32LayoutArray = [&'static DataReg; 32];
pub struct RecursionBitOpShorts {
    pub in_a: &'static RecursionWomReg,
    pub in_b: &'static RecursionWomReg,
    pub out: &'static RecursionWomReg,
    pub wom_body: &'static RecursionWomBody,
    pub bits_a: &'static DataReg32LayoutArray,
    pub bits_b: &'static DataReg32LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionBitOpShorts {
    fn ty_name(&self) -> &'static str {
        "RecursionBitOpShorts"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("in_a", self.in_a)?;
        v.visit_component("in_b", self.in_b)?;
        v.visit_component("out", self.out)?;
        v.visit_component("wom_body", self.wom_body)?;
        v.visit_component("bits_a", self.bits_a)?;
        v.visit_component("bits_b", self.bits_b)?;
        Ok(())
    }
}
pub struct OneHot3 {
    pub hot: &'static DataReg4LayoutArray,
}
impl risc0_zkp::layout::Component for OneHot3 {
    fn ty_name(&self) -> &'static str {
        "OneHot3"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("hot", self.hot)?;
        Ok(())
    }
}
pub type OutReg32LayoutArray = [&'static OutReg; 32];
pub type RecursionWomReg4LayoutArray = [&'static RecursionWomReg; 4];
pub struct RecursionSetGlobal {
    pub select: &'static OneHot3,
    pub wom_body: &'static RecursionWomBody,
    pub out: &'static OutReg32LayoutArray,
    pub regs: &'static RecursionWomReg4LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionSetGlobal {
    fn ty_name(&self) -> &'static str {
        "RecursionSetGlobal"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("select", self.select)?;
        v.visit_component("wom_body", self.wom_body)?;
        v.visit_component("out", self.out)?;
        v.visit_component("regs", self.regs)?;
        Ok(())
    }
}
pub type DataReg2LayoutArray = [&'static DataReg; 2];
pub struct RecursionShaCycle {
    pub a_carry_hi: &'static RecursionPoseidon2Inst,
    pub a_carry_low: &'static RecursionPoseidon2Inst,
    pub e_carry_high: &'static RecursionPoseidon2Inst,
    pub e_carry_low: &'static RecursionPoseidon2Inst,
    pub io0: &'static RecursionWomReg,
    pub io1: &'static RecursionWomReg,
    pub w_carry_high: &'static RecursionPoseidon2Inst,
    pub w_carry_low: &'static RecursionPoseidon2Inst,
    pub a: &'static DataReg32LayoutArray,
    pub a_raw: &'static DataReg2LayoutArray,
    pub e: &'static DataReg32LayoutArray,
    pub e_raw: &'static DataReg2LayoutArray,
    pub w: &'static DataReg32LayoutArray,
    pub w_raw: &'static DataReg2LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionShaCycle {
    fn ty_name(&self) -> &'static str {
        "RecursionShaCycle"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("a_carry_hi", self.a_carry_hi)?;
        v.visit_component("a_carry_low", self.a_carry_low)?;
        v.visit_component("e_carry_high", self.e_carry_high)?;
        v.visit_component("e_carry_low", self.e_carry_low)?;
        v.visit_component("io0", self.io0)?;
        v.visit_component("io1", self.io1)?;
        v.visit_component("w_carry_high", self.w_carry_high)?;
        v.visit_component("w_carry_low", self.w_carry_low)?;
        v.visit_component("a", self.a)?;
        v.visit_component("a_raw", self.a_raw)?;
        v.visit_component("e", self.e)?;
        v.visit_component("e_raw", self.e_raw)?;
        v.visit_component("w", self.w)?;
        v.visit_component("w_raw", self.w_raw)?;
        Ok(())
    }
}
pub struct RecursionShaWrap {
    pub sha_cycle: &'static RecursionShaCycle,
}
impl risc0_zkp::layout::Component for RecursionShaWrap {
    fn ty_name(&self) -> &'static str {
        "RecursionShaWrap"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("sha_cycle", self.sha_cycle)?;
        Ok(())
    }
}
pub struct Mux4 {
    pub bit_and_elem: &'static RecursionBitAndElem,
    pub bit_op_shorts: &'static RecursionBitOpShorts,
    pub nop: &'static RecursionPoseidon2Inst,
    pub set_global: &'static RecursionSetGlobal,
    pub sha_fini: &'static RecursionShaWrap,
    pub sha_init: &'static RecursionShaWrap,
    pub sha_load: &'static RecursionShaWrap,
    pub sha_mix: &'static RecursionShaWrap,
    pub wom_fini: &'static RecursionPoseidon2Inst,
    pub wom_init: &'static RecursionPoseidon2Inst,
}
impl risc0_zkp::layout::Component for Mux4 {
    fn ty_name(&self) -> &'static str {
        "Mux4"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("bit_and_elem", self.bit_and_elem)?;
        v.visit_component("bit_op_shorts", self.bit_op_shorts)?;
        v.visit_component("nop", self.nop)?;
        v.visit_component("set_global", self.set_global)?;
        v.visit_component("sha_fini", self.sha_fini)?;
        v.visit_component("sha_init", self.sha_init)?;
        v.visit_component("sha_load", self.sha_load)?;
        v.visit_component("sha_mix", self.sha_mix)?;
        v.visit_component("wom_fini", self.wom_fini)?;
        v.visit_component("wom_init", self.wom_init)?;
        Ok(())
    }
}
pub struct RecursionMacroOp {
    pub mux: &'static Mux4,
}
impl risc0_zkp::layout::Component for RecursionMacroOp {
    fn ty_name(&self) -> &'static str {
        "RecursionMacroOp"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("mux", self.mux)?;
        Ok(())
    }
}
pub struct OneHot5 {
    pub add: &'static DataReg,
    pub constop: &'static DataReg,
    pub eq: &'static DataReg,
    pub extract: &'static DataReg,
    pub inv: &'static DataReg,
    pub mix_rng: &'static DataReg,
    pub mul: &'static DataReg,
    pub read_iop_body: &'static DataReg,
    pub read_iop_header: &'static DataReg,
    pub select: &'static DataReg,
    pub sub: &'static DataReg,
}
impl risc0_zkp::layout::Component for OneHot5 {
    fn ty_name(&self) -> &'static str {
        "OneHot5"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("add", self.add)?;
        v.visit_component("constop", self.constop)?;
        v.visit_component("eq", self.eq)?;
        v.visit_component("extract", self.extract)?;
        v.visit_component("inv", self.inv)?;
        v.visit_component("mix_rng", self.mix_rng)?;
        v.visit_component("mul", self.mul)?;
        v.visit_component("read_iop_body", self.read_iop_body)?;
        v.visit_component("read_iop_header", self.read_iop_header)?;
        v.visit_component("select", self.select)?;
        v.visit_component("sub", self.sub)?;
        Ok(())
    }
}
pub struct RecursionMicroOp {
    pub extra: &'static DataReg,
    pub decode: &'static OneHot5,
    pub in0: &'static RecursionWomReg,
    pub in1: &'static RecursionWomReg,
    pub inst: &'static RecursionMicroInst,
    pub out: &'static RecursionWomReg,
}
impl risc0_zkp::layout::Component for RecursionMicroOp {
    fn ty_name(&self) -> &'static str {
        "RecursionMicroOp"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("extra", self.extra)?;
        v.visit_component("decode", self.decode)?;
        v.visit_component("in0", self.in0)?;
        v.visit_component("in1", self.in1)?;
        v.visit_component("inst", self.inst)?;
        v.visit_component("out", self.out)?;
        Ok(())
    }
}
pub type RecursionMicroOp3LayoutArray = [&'static RecursionMicroOp; 3];
pub struct RecursionMicroOps {
    pub wom_body: &'static RecursionWomBody,
    pub op: &'static RecursionMicroOp3LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionMicroOps {
    fn ty_name(&self) -> &'static str {
        "RecursionMicroOps"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("wom_body", self.wom_body)?;
        v.visit_component("op", self.op)?;
        Ok(())
    }
}
pub struct RecursionPoseidon2Load {
    pub wom_body: &'static RecursionWomBody,
}
impl risc0_zkp::layout::Component for RecursionPoseidon2Load {
    fn ty_name(&self) -> &'static str {
        "RecursionPoseidon2Load"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("wom_body", self.wom_body)?;
        Ok(())
    }
}
pub struct Mux6 {
    pub macro_ops: &'static RecursionMacroOp,
    pub micro_ops: &'static RecursionMicroOps,
    pub poseidon2_full: &'static RecursionPoseidon2Inst,
    pub poseidon2_load: &'static RecursionPoseidon2Load,
    pub poseidon2_partial: &'static RecursionPoseidon2Inst,
    pub poseidon2_store: &'static RecursionPoseidon2Load,
}
impl risc0_zkp::layout::Component for Mux6 {
    fn ty_name(&self) -> &'static str {
        "Mux6"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("macro_ops", self.macro_ops)?;
        v.visit_component("micro_ops", self.micro_ops)?;
        v.visit_component("poseidon2_full", self.poseidon2_full)?;
        v.visit_component("poseidon2_load", self.poseidon2_load)?;
        v.visit_component("poseidon2_partial", self.poseidon2_partial)?;
        v.visit_component("poseidon2_store", self.poseidon2_store)?;
        Ok(())
    }
}
pub struct RecursionTop {
    pub code: &'static RecursionCode,
    pub mux: &'static Mux6,
}
impl risc0_zkp::layout::Component for RecursionTop {
    fn ty_name(&self) -> &'static str {
        "RecursionTop"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("code", self.code)?;
        v.visit_component("mux", self.mux)?;
        Ok(())
    }
}
pub const LAYOUT: &RecursionTop = &RecursionTop {
    code: &RecursionCode {
        write_addr: &CodeReg { offset: 0 },
        inst: &Mux {
            macro_ops: &RecursionMacroInst {
                opcode: &OneHot {
                    bit_and_elem: &CodeReg { offset: 10 },
                    bit_op_shorts: &CodeReg { offset: 11 },
                    nop: &CodeReg { offset: 7 },
                    set_global: &CodeReg { offset: 16 },
                    sha_fini: &CodeReg { offset: 13 },
                    sha_init: &CodeReg { offset: 12 },
                    sha_load: &CodeReg { offset: 14 },
                    sha_mix: &CodeReg { offset: 15 },
                    wom_fini: &CodeReg { offset: 9 },
                    wom_init: &CodeReg { offset: 8 },
                },
                operand: &[
                    &CodeReg { offset: 17 },
                    &CodeReg { offset: 18 },
                    &CodeReg { offset: 19 },
                ],
            },
            micro_ops: &RecursionMicroInsts {
                inst: &[
                    &RecursionMicroInst {
                        opcode: &CodeReg { offset: 7 },
                        operand: &[
                            &CodeReg { offset: 8 },
                            &CodeReg { offset: 9 },
                            &CodeReg { offset: 10 },
                        ],
                    },
                    &RecursionMicroInst {
                        opcode: &CodeReg { offset: 11 },
                        operand: &[
                            &CodeReg { offset: 12 },
                            &CodeReg { offset: 13 },
                            &CodeReg { offset: 14 },
                        ],
                    },
                    &RecursionMicroInst {
                        opcode: &CodeReg { offset: 15 },
                        operand: &[
                            &CodeReg { offset: 16 },
                            &CodeReg { offset: 17 },
                            &CodeReg { offset: 18 },
                        ],
                    },
                ],
            },
            poseidon2_full: &RecursionPoseidon2FullInst {
                cycle: &OneHot0 {
                    c0: &CodeReg { offset: 7 },
                    c1: &CodeReg { offset: 8 },
                    c2: &CodeReg { offset: 9 },
                    c3: &CodeReg { offset: 10 },
                },
            },
            poseidon2_load: &RecursionPoseidon2MemInst {
                do_mont: &CodeReg { offset: 7 },
                keep_state: &CodeReg { offset: 8 },
                prep_full: &CodeReg { offset: 9 },
                group: &OneHot1 {
                    g0: &CodeReg { offset: 10 },
                    g1: &CodeReg { offset: 11 },
                    g2: &CodeReg { offset: 12 },
                },
                inputs: &[
                    &CodeReg { offset: 13 },
                    &CodeReg { offset: 14 },
                    &CodeReg { offset: 15 },
                    &CodeReg { offset: 16 },
                    &CodeReg { offset: 17 },
                    &CodeReg { offset: 18 },
                    &CodeReg { offset: 19 },
                    &CodeReg { offset: 20 },
                ],
            },
            poseidon2_partial: &RecursionPoseidon2Inst {},
            poseidon2_store: &RecursionPoseidon2MemInst {
                do_mont: &CodeReg { offset: 7 },
                keep_state: &CodeReg { offset: 8 },
                prep_full: &CodeReg { offset: 9 },
                group: &OneHot1 {
                    g0: &CodeReg { offset: 10 },
                    g1: &CodeReg { offset: 11 },
                    g2: &CodeReg { offset: 12 },
                },
                inputs: &[
                    &CodeReg { offset: 13 },
                    &CodeReg { offset: 14 },
                    &CodeReg { offset: 15 },
                    &CodeReg { offset: 16 },
                    &CodeReg { offset: 17 },
                    &CodeReg { offset: 18 },
                    &CodeReg { offset: 19 },
                    &CodeReg { offset: 20 },
                ],
            },
        },
        select: &OneHot2 {
            macro_ops: &CodeReg { offset: 2 },
            micro_ops: &CodeReg { offset: 1 },
            poseidon2_full: &CodeReg { offset: 4 },
            poseidon2_load: &CodeReg { offset: 3 },
            poseidon2_partial: &CodeReg { offset: 5 },
            poseidon2_store: &CodeReg { offset: 6 },
        },
    },
    mux: &Mux6 {
        macro_ops: &RecursionMacroOp {
            mux: &Mux4 {
                bit_and_elem: &RecursionBitAndElem {
                    in_a: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 11 },
                            data: &[
                                &DataReg { offset: 12 },
                                &DataReg { offset: 13 },
                                &DataReg { offset: 14 },
                                &DataReg { offset: 15 },
                            ],
                        },
                    },
                    in_b: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 16 },
                            data: &[
                                &DataReg { offset: 17 },
                                &DataReg { offset: 18 },
                                &DataReg { offset: 19 },
                                &DataReg { offset: 20 },
                            ],
                        },
                    },
                    out: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 21 },
                            data: &[
                                &DataReg { offset: 22 },
                                &DataReg { offset: 23 },
                                &DataReg { offset: 24 },
                                &DataReg { offset: 25 },
                            ],
                        },
                    },
                    wom_body: &RecursionWomBody {
                        plonk_body: &RecursionPoseidon2Inst {},
                    },
                    bits_a: &[
                        &DataReg { offset: 36 },
                        &DataReg { offset: 38 },
                        &DataReg { offset: 40 },
                        &DataReg { offset: 42 },
                        &DataReg { offset: 44 },
                        &DataReg { offset: 46 },
                        &DataReg { offset: 48 },
                        &DataReg { offset: 50 },
                        &DataReg { offset: 52 },
                        &DataReg { offset: 54 },
                        &DataReg { offset: 56 },
                        &DataReg { offset: 58 },
                        &DataReg { offset: 60 },
                        &DataReg { offset: 62 },
                        &DataReg { offset: 64 },
                        &DataReg { offset: 66 },
                        &DataReg { offset: 68 },
                        &DataReg { offset: 70 },
                        &DataReg { offset: 72 },
                        &DataReg { offset: 74 },
                        &DataReg { offset: 76 },
                        &DataReg { offset: 78 },
                        &DataReg { offset: 80 },
                        &DataReg { offset: 82 },
                        &DataReg { offset: 84 },
                        &DataReg { offset: 86 },
                        &DataReg { offset: 88 },
                        &DataReg { offset: 90 },
                        &DataReg { offset: 92 },
                        &DataReg { offset: 94 },
                        &DataReg { offset: 96 },
                    ],
                    bits_b: &[
                        &DataReg { offset: 37 },
                        &DataReg { offset: 39 },
                        &DataReg { offset: 41 },
                        &DataReg { offset: 43 },
                        &DataReg { offset: 45 },
                        &DataReg { offset: 47 },
                        &DataReg { offset: 49 },
                        &DataReg { offset: 51 },
                        &DataReg { offset: 53 },
                        &DataReg { offset: 55 },
                        &DataReg { offset: 57 },
                        &DataReg { offset: 59 },
                        &DataReg { offset: 61 },
                        &DataReg { offset: 63 },
                        &DataReg { offset: 65 },
                        &DataReg { offset: 67 },
                        &DataReg { offset: 69 },
                        &DataReg { offset: 71 },
                        &DataReg { offset: 73 },
                        &DataReg { offset: 75 },
                        &DataReg { offset: 77 },
                        &DataReg { offset: 79 },
                        &DataReg { offset: 81 },
                        &DataReg { offset: 83 },
                        &DataReg { offset: 85 },
                        &DataReg { offset: 87 },
                        &DataReg { offset: 89 },
                        &DataReg { offset: 91 },
                        &DataReg { offset: 93 },
                        &DataReg { offset: 95 },
                        &DataReg { offset: 97 },
                    ],
                },
                bit_op_shorts: &RecursionBitOpShorts {
                    in_a: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 11 },
                            data: &[
                                &DataReg { offset: 12 },
                                &DataReg { offset: 13 },
                                &DataReg { offset: 14 },
                                &DataReg { offset: 15 },
                            ],
                        },
                    },
                    in_b: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 16 },
                            data: &[
                                &DataReg { offset: 17 },
                                &DataReg { offset: 18 },
                                &DataReg { offset: 19 },
                                &DataReg { offset: 20 },
                            ],
                        },
                    },
                    out: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 21 },
                            data: &[
                                &DataReg { offset: 22 },
                                &DataReg { offset: 23 },
                                &DataReg { offset: 24 },
                                &DataReg { offset: 25 },
                            ],
                        },
                    },
                    wom_body: &RecursionWomBody {
                        plonk_body: &RecursionPoseidon2Inst {},
                    },
                    bits_a: &[
                        &DataReg { offset: 36 },
                        &DataReg { offset: 37 },
                        &DataReg { offset: 38 },
                        &DataReg { offset: 39 },
                        &DataReg { offset: 40 },
                        &DataReg { offset: 41 },
                        &DataReg { offset: 42 },
                        &DataReg { offset: 43 },
                        &DataReg { offset: 44 },
                        &DataReg { offset: 45 },
                        &DataReg { offset: 46 },
                        &DataReg { offset: 47 },
                        &DataReg { offset: 48 },
                        &DataReg { offset: 49 },
                        &DataReg { offset: 50 },
                        &DataReg { offset: 51 },
                        &DataReg { offset: 52 },
                        &DataReg { offset: 53 },
                        &DataReg { offset: 54 },
                        &DataReg { offset: 55 },
                        &DataReg { offset: 56 },
                        &DataReg { offset: 57 },
                        &DataReg { offset: 58 },
                        &DataReg { offset: 59 },
                        &DataReg { offset: 60 },
                        &DataReg { offset: 61 },
                        &DataReg { offset: 62 },
                        &DataReg { offset: 63 },
                        &DataReg { offset: 64 },
                        &DataReg { offset: 65 },
                        &DataReg { offset: 66 },
                        &DataReg { offset: 67 },
                    ],
                    bits_b: &[
                        &DataReg { offset: 68 },
                        &DataReg { offset: 69 },
                        &DataReg { offset: 70 },
                        &DataReg { offset: 71 },
                        &DataReg { offset: 72 },
                        &DataReg { offset: 73 },
                        &DataReg { offset: 74 },
                        &DataReg { offset: 75 },
                        &DataReg { offset: 76 },
                        &DataReg { offset: 77 },
                        &DataReg { offset: 78 },
                        &DataReg { offset: 79 },
                        &DataReg { offset: 80 },
                        &DataReg { offset: 81 },
                        &DataReg { offset: 82 },
                        &DataReg { offset: 83 },
                        &DataReg { offset: 84 },
                        &DataReg { offset: 85 },
                        &DataReg { offset: 86 },
                        &DataReg { offset: 87 },
                        &DataReg { offset: 88 },
                        &DataReg { offset: 89 },
                        &DataReg { offset: 90 },
                        &DataReg { offset: 91 },
                        &DataReg { offset: 92 },
                        &DataReg { offset: 93 },
                        &DataReg { offset: 94 },
                        &DataReg { offset: 95 },
                        &DataReg { offset: 96 },
                        &DataReg { offset: 97 },
                        &DataReg { offset: 98 },
                        &DataReg { offset: 99 },
                    ],
                },
                nop: &RecursionPoseidon2Inst {},
                set_global: &RecursionSetGlobal {
                    select: &OneHot3 {
                        hot: &[
                            &DataReg { offset: 11 },
                            &DataReg { offset: 12 },
                            &DataReg { offset: 13 },
                            &DataReg { offset: 14 },
                        ],
                    },
                    wom_body: &RecursionWomBody {
                        plonk_body: &RecursionPoseidon2Inst {},
                    },
                    out: &[
                        &OutReg { offset: 0 },
                        &OutReg { offset: 1 },
                        &OutReg { offset: 2 },
                        &OutReg { offset: 3 },
                        &OutReg { offset: 4 },
                        &OutReg { offset: 5 },
                        &OutReg { offset: 6 },
                        &OutReg { offset: 7 },
                        &OutReg { offset: 8 },
                        &OutReg { offset: 9 },
                        &OutReg { offset: 10 },
                        &OutReg { offset: 11 },
                        &OutReg { offset: 12 },
                        &OutReg { offset: 13 },
                        &OutReg { offset: 14 },
                        &OutReg { offset: 15 },
                        &OutReg { offset: 16 },
                        &OutReg { offset: 17 },
                        &OutReg { offset: 18 },
                        &OutReg { offset: 19 },
                        &OutReg { offset: 20 },
                        &OutReg { offset: 21 },
                        &OutReg { offset: 22 },
                        &OutReg { offset: 23 },
                        &OutReg { offset: 24 },
                        &OutReg { offset: 25 },
                        &OutReg { offset: 26 },
                        &OutReg { offset: 27 },
                        &OutReg { offset: 28 },
                        &OutReg { offset: 29 },
                        &OutReg { offset: 30 },
                        &OutReg { offset: 31 },
                    ],
                    regs: &[
                        &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 15 },
                                data: &[
                                    &DataReg { offset: 16 },
                                    &DataReg { offset: 17 },
                                    &DataReg { offset: 18 },
                                    &DataReg { offset: 19 },
                                ],
                            },
                        },
                        &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 20 },
                                data: &[
                                    &DataReg { offset: 21 },
                                    &DataReg { offset: 22 },
                                    &DataReg { offset: 23 },
                                    &DataReg { offset: 24 },
                                ],
                            },
                        },
                        &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 25 },
                                data: &[
                                    &DataReg { offset: 26 },
                                    &DataReg { offset: 27 },
                                    &DataReg { offset: 28 },
                                    &DataReg { offset: 29 },
                                ],
                            },
                        },
                        &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 30 },
                                data: &[
                                    &DataReg { offset: 31 },
                                    &DataReg { offset: 32 },
                                    &DataReg { offset: 33 },
                                    &DataReg { offset: 34 },
                                ],
                            },
                        },
                    ],
                },
                sha_fini: &RecursionShaWrap {
                    sha_cycle: &RecursionShaCycle {
                        a_carry_hi: &RecursionPoseidon2Inst {},
                        a_carry_low: &RecursionPoseidon2Inst {},
                        e_carry_high: &RecursionPoseidon2Inst {},
                        e_carry_low: &RecursionPoseidon2Inst {},
                        io0: &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 11 },
                                data: &[
                                    &DataReg { offset: 12 },
                                    &DataReg { offset: 13 },
                                    &DataReg { offset: 14 },
                                    &DataReg { offset: 15 },
                                ],
                            },
                        },
                        io1: &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 16 },
                                data: &[
                                    &DataReg { offset: 17 },
                                    &DataReg { offset: 18 },
                                    &DataReg { offset: 19 },
                                    &DataReg { offset: 20 },
                                ],
                            },
                        },
                        w_carry_high: &RecursionPoseidon2Inst {},
                        w_carry_low: &RecursionPoseidon2Inst {},
                        a: &[
                            &DataReg { offset: 26 },
                            &DataReg { offset: 27 },
                            &DataReg { offset: 28 },
                            &DataReg { offset: 29 },
                            &DataReg { offset: 30 },
                            &DataReg { offset: 31 },
                            &DataReg { offset: 32 },
                            &DataReg { offset: 33 },
                            &DataReg { offset: 34 },
                            &DataReg { offset: 35 },
                            &DataReg { offset: 36 },
                            &DataReg { offset: 37 },
                            &DataReg { offset: 38 },
                            &DataReg { offset: 39 },
                            &DataReg { offset: 40 },
                            &DataReg { offset: 41 },
                            &DataReg { offset: 42 },
                            &DataReg { offset: 43 },
                            &DataReg { offset: 44 },
                            &DataReg { offset: 45 },
                            &DataReg { offset: 46 },
                            &DataReg { offset: 47 },
                            &DataReg { offset: 48 },
                            &DataReg { offset: 49 },
                            &DataReg { offset: 50 },
                            &DataReg { offset: 51 },
                            &DataReg { offset: 52 },
                            &DataReg { offset: 53 },
                            &DataReg { offset: 54 },
                            &DataReg { offset: 55 },
                            &DataReg { offset: 56 },
                            &DataReg { offset: 57 },
                        ],
                        a_raw: &[&DataReg { offset: 58 }, &DataReg { offset: 59 }],
                        e: &[
                            &DataReg { offset: 60 },
                            &DataReg { offset: 61 },
                            &DataReg { offset: 62 },
                            &DataReg { offset: 63 },
                            &DataReg { offset: 64 },
                            &DataReg { offset: 65 },
                            &DataReg { offset: 66 },
                            &DataReg { offset: 67 },
                            &DataReg { offset: 68 },
                            &DataReg { offset: 69 },
                            &DataReg { offset: 70 },
                            &DataReg { offset: 71 },
                            &DataReg { offset: 72 },
                            &DataReg { offset: 73 },
                            &DataReg { offset: 74 },
                            &DataReg { offset: 75 },
                            &DataReg { offset: 76 },
                            &DataReg { offset: 77 },
                            &DataReg { offset: 78 },
                            &DataReg { offset: 79 },
                            &DataReg { offset: 80 },
                            &DataReg { offset: 81 },
                            &DataReg { offset: 82 },
                            &DataReg { offset: 83 },
                            &DataReg { offset: 84 },
                            &DataReg { offset: 85 },
                            &DataReg { offset: 86 },
                            &DataReg { offset: 87 },
                            &DataReg { offset: 88 },
                            &DataReg { offset: 89 },
                            &DataReg { offset: 90 },
                            &DataReg { offset: 91 },
                        ],
                        e_raw: &[&DataReg { offset: 92 }, &DataReg { offset: 93 }],
                        w: &[
                            &DataReg { offset: 94 },
                            &DataReg { offset: 95 },
                            &DataReg { offset: 96 },
                            &DataReg { offset: 97 },
                            &DataReg { offset: 98 },
                            &DataReg { offset: 99 },
                            &DataReg { offset: 100 },
                            &DataReg { offset: 101 },
                            &DataReg { offset: 102 },
                            &DataReg { offset: 103 },
                            &DataReg { offset: 104 },
                            &DataReg { offset: 105 },
                            &DataReg { offset: 106 },
                            &DataReg { offset: 107 },
                            &DataReg { offset: 108 },
                            &DataReg { offset: 109 },
                            &DataReg { offset: 110 },
                            &DataReg { offset: 111 },
                            &DataReg { offset: 112 },
                            &DataReg { offset: 113 },
                            &DataReg { offset: 114 },
                            &DataReg { offset: 115 },
                            &DataReg { offset: 116 },
                            &DataReg { offset: 117 },
                            &DataReg { offset: 118 },
                            &DataReg { offset: 119 },
                            &DataReg { offset: 120 },
                            &DataReg { offset: 121 },
                            &DataReg { offset: 122 },
                            &DataReg { offset: 123 },
                            &DataReg { offset: 124 },
                            &DataReg { offset: 125 },
                        ],
                        w_raw: &[&DataReg { offset: 126 }, &DataReg { offset: 127 }],
                    },
                },
                sha_init: &RecursionShaWrap {
                    sha_cycle: &RecursionShaCycle {
                        a_carry_hi: &RecursionPoseidon2Inst {},
                        a_carry_low: &RecursionPoseidon2Inst {},
                        e_carry_high: &RecursionPoseidon2Inst {},
                        e_carry_low: &RecursionPoseidon2Inst {},
                        io0: &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 11 },
                                data: &[
                                    &DataReg { offset: 12 },
                                    &DataReg { offset: 13 },
                                    &DataReg { offset: 14 },
                                    &DataReg { offset: 15 },
                                ],
                            },
                        },
                        io1: &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 16 },
                                data: &[
                                    &DataReg { offset: 17 },
                                    &DataReg { offset: 18 },
                                    &DataReg { offset: 19 },
                                    &DataReg { offset: 20 },
                                ],
                            },
                        },
                        w_carry_high: &RecursionPoseidon2Inst {},
                        w_carry_low: &RecursionPoseidon2Inst {},
                        a: &[
                            &DataReg { offset: 26 },
                            &DataReg { offset: 27 },
                            &DataReg { offset: 28 },
                            &DataReg { offset: 29 },
                            &DataReg { offset: 30 },
                            &DataReg { offset: 31 },
                            &DataReg { offset: 32 },
                            &DataReg { offset: 33 },
                            &DataReg { offset: 34 },
                            &DataReg { offset: 35 },
                            &DataReg { offset: 36 },
                            &DataReg { offset: 37 },
                            &DataReg { offset: 38 },
                            &DataReg { offset: 39 },
                            &DataReg { offset: 40 },
                            &DataReg { offset: 41 },
                            &DataReg { offset: 42 },
                            &DataReg { offset: 43 },
                            &DataReg { offset: 44 },
                            &DataReg { offset: 45 },
                            &DataReg { offset: 46 },
                            &DataReg { offset: 47 },
                            &DataReg { offset: 48 },
                            &DataReg { offset: 49 },
                            &DataReg { offset: 50 },
                            &DataReg { offset: 51 },
                            &DataReg { offset: 52 },
                            &DataReg { offset: 53 },
                            &DataReg { offset: 54 },
                            &DataReg { offset: 55 },
                            &DataReg { offset: 56 },
                            &DataReg { offset: 57 },
                        ],
                        a_raw: &[&DataReg { offset: 58 }, &DataReg { offset: 59 }],
                        e: &[
                            &DataReg { offset: 60 },
                            &DataReg { offset: 61 },
                            &DataReg { offset: 62 },
                            &DataReg { offset: 63 },
                            &DataReg { offset: 64 },
                            &DataReg { offset: 65 },
                            &DataReg { offset: 66 },
                            &DataReg { offset: 67 },
                            &DataReg { offset: 68 },
                            &DataReg { offset: 69 },
                            &DataReg { offset: 70 },
                            &DataReg { offset: 71 },
                            &DataReg { offset: 72 },
                            &DataReg { offset: 73 },
                            &DataReg { offset: 74 },
                            &DataReg { offset: 75 },
                            &DataReg { offset: 76 },
                            &DataReg { offset: 77 },
                            &DataReg { offset: 78 },
                            &DataReg { offset: 79 },
                            &DataReg { offset: 80 },
                            &DataReg { offset: 81 },
                            &DataReg { offset: 82 },
                            &DataReg { offset: 83 },
                            &DataReg { offset: 84 },
                            &DataReg { offset: 85 },
                            &DataReg { offset: 86 },
                            &DataReg { offset: 87 },
                            &DataReg { offset: 88 },
                            &DataReg { offset: 89 },
                            &DataReg { offset: 90 },
                            &DataReg { offset: 91 },
                        ],
                        e_raw: &[&DataReg { offset: 92 }, &DataReg { offset: 93 }],
                        w: &[
                            &DataReg { offset: 94 },
                            &DataReg { offset: 95 },
                            &DataReg { offset: 96 },
                            &DataReg { offset: 97 },
                            &DataReg { offset: 98 },
                            &DataReg { offset: 99 },
                            &DataReg { offset: 100 },
                            &DataReg { offset: 101 },
                            &DataReg { offset: 102 },
                            &DataReg { offset: 103 },
                            &DataReg { offset: 104 },
                            &DataReg { offset: 105 },
                            &DataReg { offset: 106 },
                            &DataReg { offset: 107 },
                            &DataReg { offset: 108 },
                            &DataReg { offset: 109 },
                            &DataReg { offset: 110 },
                            &DataReg { offset: 111 },
                            &DataReg { offset: 112 },
                            &DataReg { offset: 113 },
                            &DataReg { offset: 114 },
                            &DataReg { offset: 115 },
                            &DataReg { offset: 116 },
                            &DataReg { offset: 117 },
                            &DataReg { offset: 118 },
                            &DataReg { offset: 119 },
                            &DataReg { offset: 120 },
                            &DataReg { offset: 121 },
                            &DataReg { offset: 122 },
                            &DataReg { offset: 123 },
                            &DataReg { offset: 124 },
                            &DataReg { offset: 125 },
                        ],
                        w_raw: &[&DataReg { offset: 126 }, &DataReg { offset: 127 }],
                    },
                },
                sha_load: &RecursionShaWrap {
                    sha_cycle: &RecursionShaCycle {
                        a_carry_hi: &RecursionPoseidon2Inst {},
                        a_carry_low: &RecursionPoseidon2Inst {},
                        e_carry_high: &RecursionPoseidon2Inst {},
                        e_carry_low: &RecursionPoseidon2Inst {},
                        io0: &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 11 },
                                data: &[
                                    &DataReg { offset: 12 },
                                    &DataReg { offset: 13 },
                                    &DataReg { offset: 14 },
                                    &DataReg { offset: 15 },
                                ],
                            },
                        },
                        io1: &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 16 },
                                data: &[
                                    &DataReg { offset: 17 },
                                    &DataReg { offset: 18 },
                                    &DataReg { offset: 19 },
                                    &DataReg { offset: 20 },
                                ],
                            },
                        },
                        w_carry_high: &RecursionPoseidon2Inst {},
                        w_carry_low: &RecursionPoseidon2Inst {},
                        a: &[
                            &DataReg { offset: 26 },
                            &DataReg { offset: 27 },
                            &DataReg { offset: 28 },
                            &DataReg { offset: 29 },
                            &DataReg { offset: 30 },
                            &DataReg { offset: 31 },
                            &DataReg { offset: 32 },
                            &DataReg { offset: 33 },
                            &DataReg { offset: 34 },
                            &DataReg { offset: 35 },
                            &DataReg { offset: 36 },
                            &DataReg { offset: 37 },
                            &DataReg { offset: 38 },
                            &DataReg { offset: 39 },
                            &DataReg { offset: 40 },
                            &DataReg { offset: 41 },
                            &DataReg { offset: 42 },
                            &DataReg { offset: 43 },
                            &DataReg { offset: 44 },
                            &DataReg { offset: 45 },
                            &DataReg { offset: 46 },
                            &DataReg { offset: 47 },
                            &DataReg { offset: 48 },
                            &DataReg { offset: 49 },
                            &DataReg { offset: 50 },
                            &DataReg { offset: 51 },
                            &DataReg { offset: 52 },
                            &DataReg { offset: 53 },
                            &DataReg { offset: 54 },
                            &DataReg { offset: 55 },
                            &DataReg { offset: 56 },
                            &DataReg { offset: 57 },
                        ],
                        a_raw: &[&DataReg { offset: 58 }, &DataReg { offset: 59 }],
                        e: &[
                            &DataReg { offset: 60 },
                            &DataReg { offset: 61 },
                            &DataReg { offset: 62 },
                            &DataReg { offset: 63 },
                            &DataReg { offset: 64 },
                            &DataReg { offset: 65 },
                            &DataReg { offset: 66 },
                            &DataReg { offset: 67 },
                            &DataReg { offset: 68 },
                            &DataReg { offset: 69 },
                            &DataReg { offset: 70 },
                            &DataReg { offset: 71 },
                            &DataReg { offset: 72 },
                            &DataReg { offset: 73 },
                            &DataReg { offset: 74 },
                            &DataReg { offset: 75 },
                            &DataReg { offset: 76 },
                            &DataReg { offset: 77 },
                            &DataReg { offset: 78 },
                            &DataReg { offset: 79 },
                            &DataReg { offset: 80 },
                            &DataReg { offset: 81 },
                            &DataReg { offset: 82 },
                            &DataReg { offset: 83 },
                            &DataReg { offset: 84 },
                            &DataReg { offset: 85 },
                            &DataReg { offset: 86 },
                            &DataReg { offset: 87 },
                            &DataReg { offset: 88 },
                            &DataReg { offset: 89 },
                            &DataReg { offset: 90 },
                            &DataReg { offset: 91 },
                        ],
                        e_raw: &[&DataReg { offset: 92 }, &DataReg { offset: 93 }],
                        w: &[
                            &DataReg { offset: 94 },
                            &DataReg { offset: 95 },
                            &DataReg { offset: 96 },
                            &DataReg { offset: 97 },
                            &DataReg { offset: 98 },
                            &DataReg { offset: 99 },
                            &DataReg { offset: 100 },
                            &DataReg { offset: 101 },
                            &DataReg { offset: 102 },
                            &DataReg { offset: 103 },
                            &DataReg { offset: 104 },
                            &DataReg { offset: 105 },
                            &DataReg { offset: 106 },
                            &DataReg { offset: 107 },
                            &DataReg { offset: 108 },
                            &DataReg { offset: 109 },
                            &DataReg { offset: 110 },
                            &DataReg { offset: 111 },
                            &DataReg { offset: 112 },
                            &DataReg { offset: 113 },
                            &DataReg { offset: 114 },
                            &DataReg { offset: 115 },
                            &DataReg { offset: 116 },
                            &DataReg { offset: 117 },
                            &DataReg { offset: 118 },
                            &DataReg { offset: 119 },
                            &DataReg { offset: 120 },
                            &DataReg { offset: 121 },
                            &DataReg { offset: 122 },
                            &DataReg { offset: 123 },
                            &DataReg { offset: 124 },
                            &DataReg { offset: 125 },
                        ],
                        w_raw: &[&DataReg { offset: 126 }, &DataReg { offset: 127 }],
                    },
                },
                sha_mix: &RecursionShaWrap {
                    sha_cycle: &RecursionShaCycle {
                        a_carry_hi: &RecursionPoseidon2Inst {},
                        a_carry_low: &RecursionPoseidon2Inst {},
                        e_carry_high: &RecursionPoseidon2Inst {},
                        e_carry_low: &RecursionPoseidon2Inst {},
                        io0: &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 11 },
                                data: &[
                                    &DataReg { offset: 12 },
                                    &DataReg { offset: 13 },
                                    &DataReg { offset: 14 },
                                    &DataReg { offset: 15 },
                                ],
                            },
                        },
                        io1: &RecursionWomReg {
                            wom: &RecursionImplWomPlonkElement {
                                addr: &DataReg { offset: 16 },
                                data: &[
                                    &DataReg { offset: 17 },
                                    &DataReg { offset: 18 },
                                    &DataReg { offset: 19 },
                                    &DataReg { offset: 20 },
                                ],
                            },
                        },
                        w_carry_high: &RecursionPoseidon2Inst {},
                        w_carry_low: &RecursionPoseidon2Inst {},
                        a: &[
                            &DataReg { offset: 26 },
                            &DataReg { offset: 27 },
                            &DataReg { offset: 28 },
                            &DataReg { offset: 29 },
                            &DataReg { offset: 30 },
                            &DataReg { offset: 31 },
                            &DataReg { offset: 32 },
                            &DataReg { offset: 33 },
                            &DataReg { offset: 34 },
                            &DataReg { offset: 35 },
                            &DataReg { offset: 36 },
                            &DataReg { offset: 37 },
                            &DataReg { offset: 38 },
                            &DataReg { offset: 39 },
                            &DataReg { offset: 40 },
                            &DataReg { offset: 41 },
                            &DataReg { offset: 42 },
                            &DataReg { offset: 43 },
                            &DataReg { offset: 44 },
                            &DataReg { offset: 45 },
                            &DataReg { offset: 46 },
                            &DataReg { offset: 47 },
                            &DataReg { offset: 48 },
                            &DataReg { offset: 49 },
                            &DataReg { offset: 50 },
                            &DataReg { offset: 51 },
                            &DataReg { offset: 52 },
                            &DataReg { offset: 53 },
                            &DataReg { offset: 54 },
                            &DataReg { offset: 55 },
                            &DataReg { offset: 56 },
                            &DataReg { offset: 57 },
                        ],
                        a_raw: &[&DataReg { offset: 58 }, &DataReg { offset: 59 }],
                        e: &[
                            &DataReg { offset: 60 },
                            &DataReg { offset: 61 },
                            &DataReg { offset: 62 },
                            &DataReg { offset: 63 },
                            &DataReg { offset: 64 },
                            &DataReg { offset: 65 },
                            &DataReg { offset: 66 },
                            &DataReg { offset: 67 },
                            &DataReg { offset: 68 },
                            &DataReg { offset: 69 },
                            &DataReg { offset: 70 },
                            &DataReg { offset: 71 },
                            &DataReg { offset: 72 },
                            &DataReg { offset: 73 },
                            &DataReg { offset: 74 },
                            &DataReg { offset: 75 },
                            &DataReg { offset: 76 },
                            &DataReg { offset: 77 },
                            &DataReg { offset: 78 },
                            &DataReg { offset: 79 },
                            &DataReg { offset: 80 },
                            &DataReg { offset: 81 },
                            &DataReg { offset: 82 },
                            &DataReg { offset: 83 },
                            &DataReg { offset: 84 },
                            &DataReg { offset: 85 },
                            &DataReg { offset: 86 },
                            &DataReg { offset: 87 },
                            &DataReg { offset: 88 },
                            &DataReg { offset: 89 },
                            &DataReg { offset: 90 },
                            &DataReg { offset: 91 },
                        ],
                        e_raw: &[&DataReg { offset: 92 }, &DataReg { offset: 93 }],
                        w: &[
                            &DataReg { offset: 94 },
                            &DataReg { offset: 95 },
                            &DataReg { offset: 96 },
                            &DataReg { offset: 97 },
                            &DataReg { offset: 98 },
                            &DataReg { offset: 99 },
                            &DataReg { offset: 100 },
                            &DataReg { offset: 101 },
                            &DataReg { offset: 102 },
                            &DataReg { offset: 103 },
                            &DataReg { offset: 104 },
                            &DataReg { offset: 105 },
                            &DataReg { offset: 106 },
                            &DataReg { offset: 107 },
                            &DataReg { offset: 108 },
                            &DataReg { offset: 109 },
                            &DataReg { offset: 110 },
                            &DataReg { offset: 111 },
                            &DataReg { offset: 112 },
                            &DataReg { offset: 113 },
                            &DataReg { offset: 114 },
                            &DataReg { offset: 115 },
                            &DataReg { offset: 116 },
                            &DataReg { offset: 117 },
                            &DataReg { offset: 118 },
                            &DataReg { offset: 119 },
                            &DataReg { offset: 120 },
                            &DataReg { offset: 121 },
                            &DataReg { offset: 122 },
                            &DataReg { offset: 123 },
                            &DataReg { offset: 124 },
                            &DataReg { offset: 125 },
                        ],
                        w_raw: &[&DataReg { offset: 126 }, &DataReg { offset: 127 }],
                    },
                },
                wom_fini: &RecursionPoseidon2Inst {},
                wom_init: &RecursionPoseidon2Inst {},
            },
        },
        micro_ops: &RecursionMicroOps {
            wom_body: &RecursionWomBody {
                plonk_body: &RecursionPoseidon2Inst {},
            },
            op: &[
                &RecursionMicroOp {
                    extra: &DataReg { offset: 101 },
                    decode: &OneHot5 {
                        add: &DataReg { offset: 91 },
                        constop: &DataReg { offset: 90 },
                        eq: &DataReg { offset: 95 },
                        extract: &DataReg { offset: 100 },
                        inv: &DataReg { offset: 94 },
                        mix_rng: &DataReg { offset: 98 },
                        mul: &DataReg { offset: 93 },
                        read_iop_body: &DataReg { offset: 97 },
                        read_iop_header: &DataReg { offset: 96 },
                        select: &DataReg { offset: 99 },
                        sub: &DataReg { offset: 92 },
                    },
                    in0: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 5 },
                            data: &[
                                &DataReg { offset: 6 },
                                &DataReg { offset: 7 },
                                &DataReg { offset: 8 },
                                &DataReg { offset: 9 },
                            ],
                        },
                    },
                    in1: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 10 },
                            data: &[
                                &DataReg { offset: 11 },
                                &DataReg { offset: 12 },
                                &DataReg { offset: 13 },
                                &DataReg { offset: 14 },
                            ],
                        },
                    },
                    inst: &RecursionMicroInst {
                        opcode: &CodeReg { offset: 7 },
                        operand: &[
                            &CodeReg { offset: 8 },
                            &CodeReg { offset: 9 },
                            &CodeReg { offset: 10 },
                        ],
                    },
                    out: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 15 },
                            data: &[
                                &DataReg { offset: 16 },
                                &DataReg { offset: 17 },
                                &DataReg { offset: 18 },
                                &DataReg { offset: 19 },
                            ],
                        },
                    },
                },
                &RecursionMicroOp {
                    extra: &DataReg { offset: 113 },
                    decode: &OneHot5 {
                        add: &DataReg { offset: 103 },
                        constop: &DataReg { offset: 102 },
                        eq: &DataReg { offset: 107 },
                        extract: &DataReg { offset: 112 },
                        inv: &DataReg { offset: 106 },
                        mix_rng: &DataReg { offset: 110 },
                        mul: &DataReg { offset: 105 },
                        read_iop_body: &DataReg { offset: 109 },
                        read_iop_header: &DataReg { offset: 108 },
                        select: &DataReg { offset: 111 },
                        sub: &DataReg { offset: 104 },
                    },
                    in0: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 20 },
                            data: &[
                                &DataReg { offset: 21 },
                                &DataReg { offset: 22 },
                                &DataReg { offset: 23 },
                                &DataReg { offset: 24 },
                            ],
                        },
                    },
                    in1: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 25 },
                            data: &[
                                &DataReg { offset: 26 },
                                &DataReg { offset: 27 },
                                &DataReg { offset: 28 },
                                &DataReg { offset: 29 },
                            ],
                        },
                    },
                    inst: &RecursionMicroInst {
                        opcode: &CodeReg { offset: 11 },
                        operand: &[
                            &CodeReg { offset: 12 },
                            &CodeReg { offset: 13 },
                            &CodeReg { offset: 14 },
                        ],
                    },
                    out: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 30 },
                            data: &[
                                &DataReg { offset: 31 },
                                &DataReg { offset: 32 },
                                &DataReg { offset: 33 },
                                &DataReg { offset: 34 },
                            ],
                        },
                    },
                },
                &RecursionMicroOp {
                    extra: &DataReg { offset: 125 },
                    decode: &OneHot5 {
                        add: &DataReg { offset: 115 },
                        constop: &DataReg { offset: 114 },
                        eq: &DataReg { offset: 119 },
                        extract: &DataReg { offset: 124 },
                        inv: &DataReg { offset: 118 },
                        mix_rng: &DataReg { offset: 122 },
                        mul: &DataReg { offset: 117 },
                        read_iop_body: &DataReg { offset: 121 },
                        read_iop_header: &DataReg { offset: 120 },
                        select: &DataReg { offset: 123 },
                        sub: &DataReg { offset: 116 },
                    },
                    in0: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 35 },
                            data: &[
                                &DataReg { offset: 36 },
                                &DataReg { offset: 37 },
                                &DataReg { offset: 38 },
                                &DataReg { offset: 39 },
                            ],
                        },
                    },
                    in1: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 40 },
                            data: &[
                                &DataReg { offset: 41 },
                                &DataReg { offset: 42 },
                                &DataReg { offset: 43 },
                                &DataReg { offset: 44 },
                            ],
                        },
                    },
                    inst: &RecursionMicroInst {
                        opcode: &CodeReg { offset: 15 },
                        operand: &[
                            &CodeReg { offset: 16 },
                            &CodeReg { offset: 17 },
                            &CodeReg { offset: 18 },
                        ],
                    },
                    out: &RecursionWomReg {
                        wom: &RecursionImplWomPlonkElement {
                            addr: &DataReg { offset: 45 },
                            data: &[
                                &DataReg { offset: 46 },
                                &DataReg { offset: 47 },
                                &DataReg { offset: 48 },
                                &DataReg { offset: 49 },
                            ],
                        },
                    },
                },
            ],
        },
        poseidon2_full: &RecursionPoseidon2Inst {},
        poseidon2_load: &RecursionPoseidon2Load {
            wom_body: &RecursionWomBody {
                plonk_body: &RecursionPoseidon2Inst {},
            },
        },
        poseidon2_partial: &RecursionPoseidon2Inst {},
        poseidon2_store: &RecursionPoseidon2Load {
            wom_body: &RecursionWomBody {
                plonk_body: &RecursionPoseidon2Inst {},
            },
        },
    },
};
