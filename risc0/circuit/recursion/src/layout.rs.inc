// zirgen/circuit/recursion/code.cpp:22
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

// :0
pub struct RecursionMacroInst {
    pub opcode: &'static OneHot,
    pub operand: &'static [&'static CodeReg; 3],
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

// zirgen/circuit/recursion/code.cpp:17
pub struct RecursionMicroInst {
    pub opcode: &'static CodeReg,
    pub operand: &'static [&'static CodeReg; 3],
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

// :0
pub struct RecursionMicroInsts {
    pub inst: &'static [&'static RecursionMicroInst; 3],
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

// zirgen/circuit/recursion/code.cpp:51
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

// :0
pub struct RecursionPoseidonFullInst {
    pub cycle: &'static OneHot0,
}
impl risc0_zkp::layout::Component for RecursionPoseidonFullInst {
    fn ty_name(&self) -> &'static str {
        "RecursionPoseidonFullInst"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("cycle", self.cycle)?;
        Ok(())
    }
}

// zirgen/circuit/recursion/code.cpp:44
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

// :0
pub struct RecursionPoseidonMemInst {
    pub add_consts: &'static CodeReg,
    pub do_mont: &'static CodeReg,
    pub keep_state: &'static CodeReg,
    pub group: &'static OneHot1,
    pub inputs: &'static [&'static CodeReg; 8],
}
impl risc0_zkp::layout::Component for RecursionPoseidonMemInst {
    fn ty_name(&self) -> &'static str {
        "RecursionPoseidonMemInst"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("add_consts", self.add_consts)?;
        v.visit_component("do_mont", self.do_mont)?;
        v.visit_component("keep_state", self.keep_state)?;
        v.visit_component("group", self.group)?;
        v.visit_component("inputs", self.inputs)?;
        Ok(())
    }
}

// :0
pub struct RecursionPoseidonInst {}
impl risc0_zkp::layout::Component for RecursionPoseidonInst {
    fn ty_name(&self) -> &'static str {
        "RecursionPoseidonInst"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        Ok(())
    }
}

// zirgen/circuit/recursion/code.cpp:64
pub struct Mux {
    pub macro_ops: &'static RecursionMacroInst,
    pub micro_ops: &'static RecursionMicroInsts,
    pub poseidon_full: &'static RecursionPoseidonFullInst,
    pub poseidon_load: &'static RecursionPoseidonMemInst,
    pub poseidon_partial: &'static RecursionPoseidonInst,
    pub poseidon_store: &'static RecursionPoseidonMemInst,
}
impl risc0_zkp::layout::Component for Mux {
    fn ty_name(&self) -> &'static str {
        "Mux"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("macro_ops", self.macro_ops)?;
        v.visit_component("micro_ops", self.micro_ops)?;
        v.visit_component("poseidon_full", self.poseidon_full)?;
        v.visit_component("poseidon_load", self.poseidon_load)?;
        v.visit_component("poseidon_partial", self.poseidon_partial)?;
        v.visit_component("poseidon_store", self.poseidon_store)?;
        Ok(())
    }
}

// zirgen/circuit/recursion/code.cpp:55
pub struct OneHot2 {
    pub macro_ops: &'static CodeReg,
    pub micro_ops: &'static CodeReg,
    pub poseidon_full: &'static CodeReg,
    pub poseidon_load: &'static CodeReg,
    pub poseidon_partial: &'static CodeReg,
    pub poseidon_store: &'static CodeReg,
}
impl risc0_zkp::layout::Component for OneHot2 {
    fn ty_name(&self) -> &'static str {
        "OneHot2"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("macro_ops", self.macro_ops)?;
        v.visit_component("micro_ops", self.micro_ops)?;
        v.visit_component("poseidon_full", self.poseidon_full)?;
        v.visit_component("poseidon_load", self.poseidon_load)?;
        v.visit_component("poseidon_partial", self.poseidon_partial)?;
        v.visit_component("poseidon_store", self.poseidon_store)?;
        Ok(())
    }
}

// zirgen/circuit/recursion/top.cpp:9
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

// compiler/edsl/component.h:142
pub struct RecursionImplWomPlonkElement {
    pub addr: &'static DataReg,
    pub data: &'static [&'static DataReg; 4],
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

// zirgen/circuit/recursion/bits.cpp:58
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

// zirgen/circuit/recursion/bits.cpp:58
pub struct RecursionWomBody {
    pub plonk_body: &'static RecursionPoseidonInst,
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

// :0
pub struct RecursionBitAndElem {
    pub in_a: &'static RecursionWomReg,
    pub in_b: &'static RecursionWomReg,
    pub out: &'static RecursionWomReg,
    pub wom_body: &'static RecursionWomBody,
    pub bits_a: &'static [&'static DataReg; 31],
    pub bits_b: &'static [&'static DataReg; 31],
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

// :0
pub struct RecursionBitOpShorts {
    pub in_a: &'static RecursionWomReg,
    pub in_b: &'static RecursionWomReg,
    pub out: &'static RecursionWomReg,
    pub wom_body: &'static RecursionWomBody,
    pub bits_a: &'static [&'static DataReg; 32],
    pub bits_b: &'static [&'static DataReg; 32],
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

// zirgen/circuit/recursion/macro.cpp:22
pub struct OneHot3 {
    pub hot: &'static [&'static DataReg; 4],
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

// :0
pub struct RecursionSetGlobal {
    pub select: &'static OneHot3,
    pub wom_body: &'static RecursionWomBody,
    pub regs: &'static [&'static RecursionWomReg; 4],
    pub out: &'static [&'static OutReg; 32],
}
impl risc0_zkp::layout::Component for RecursionSetGlobal {
    fn ty_name(&self) -> &'static str {
        "RecursionSetGlobal"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("select", self.select)?;
        v.visit_component("wom_body", self.wom_body)?;
        v.visit_component("regs", self.regs)?;
        v.visit_component("out", self.out)?;
        Ok(())
    }
}

// circuit/recursion/sha.h:51
pub struct RecursionShaCycle {
    pub a_carry_hi: &'static RecursionPoseidonInst,
    pub a_carry_low: &'static RecursionPoseidonInst,
    pub e_carry_high: &'static RecursionPoseidonInst,
    pub e_carry_low: &'static RecursionPoseidonInst,
    pub io0: &'static RecursionWomReg,
    pub io1: &'static RecursionWomReg,
    pub w_carry_high: &'static RecursionPoseidonInst,
    pub w_carry_low: &'static RecursionPoseidonInst,
    pub e_raw: &'static [&'static DataReg; 2],
    pub w: &'static [&'static DataReg; 32],
    pub e: &'static [&'static DataReg; 32],
    pub w_raw: &'static [&'static DataReg; 2],
    pub a_raw: &'static [&'static DataReg; 2],
    pub a: &'static [&'static DataReg; 32],
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
        v.visit_component("e_raw", self.e_raw)?;
        v.visit_component("w", self.w)?;
        v.visit_component("e", self.e)?;
        v.visit_component("w_raw", self.w_raw)?;
        v.visit_component("a_raw", self.a_raw)?;
        v.visit_component("a", self.a)?;
        Ok(())
    }
}

// :0
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

// zirgen/circuit/recursion/macro.cpp:48
pub struct Mux4 {
    pub bit_and_elem: &'static RecursionBitAndElem,
    pub bit_op_shorts: &'static RecursionBitOpShorts,
    pub nop: &'static RecursionPoseidonInst,
    pub set_global: &'static RecursionSetGlobal,
    pub sha_fini: &'static RecursionShaWrap,
    pub sha_init: &'static RecursionShaWrap,
    pub sha_load: &'static RecursionShaWrap,
    pub sha_mix: &'static RecursionShaWrap,
    pub wom_fini: &'static RecursionPoseidonInst,
    pub wom_init: &'static RecursionPoseidonInst,
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

// :0
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

// circuit/recursion/micro.h:12
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

// zirgen/circuit/recursion/micro.cpp:142
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

// :0
pub struct RecursionMicroOps {
    pub wom_body: &'static RecursionWomBody,
    pub op: &'static [&'static RecursionMicroOp; 3],
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

// :0
pub struct RecursionPoseidonLoad {
    pub wom_body: &'static RecursionWomBody,
}
impl risc0_zkp::layout::Component for RecursionPoseidonLoad {
    fn ty_name(&self) -> &'static str {
        "RecursionPoseidonLoad"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("wom_body", self.wom_body)?;
        Ok(())
    }
}

// zirgen/circuit/recursion/top.cpp:10
pub struct Mux6 {
    pub macro_ops: &'static RecursionMacroOp,
    pub micro_ops: &'static RecursionMicroOps,
    pub poseidon_full: &'static RecursionPoseidonInst,
    pub poseidon_load: &'static RecursionPoseidonLoad,
    pub poseidon_partial: &'static RecursionPoseidonInst,
    pub poseidon_store: &'static RecursionPoseidonLoad,
}
impl risc0_zkp::layout::Component for Mux6 {
    fn ty_name(&self) -> &'static str {
        "Mux6"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("macro_ops", self.macro_ops)?;
        v.visit_component("micro_ops", self.micro_ops)?;
        v.visit_component("poseidon_full", self.poseidon_full)?;
        v.visit_component("poseidon_load", self.poseidon_load)?;
        v.visit_component("poseidon_partial", self.poseidon_partial)?;
        v.visit_component("poseidon_store", self.poseidon_store)?;
        Ok(())
    }
}

// zirgen/circuit/recursion/recursion.cpp:34
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

// zirgen/circuit/recursion/top.cpp:9
pub const LAYOUT_CODE_WRITE_ADDR: CodeReg = CodeReg { offset: 0 };

// zirgen/circuit/recursion/code.cpp:22
pub const LAYOUT_CODE_INST_MACRO_OPS_OPCODE_BIT_AND_ELEM: CodeReg = CodeReg { offset: 10 };

// zirgen/circuit/recursion/code.cpp:22
pub const LAYOUT_CODE_INST_MACRO_OPS_OPCODE_BIT_OP_SHORTS: CodeReg = CodeReg { offset: 11 };

// zirgen/circuit/recursion/code.cpp:22
pub const LAYOUT_CODE_INST_MACRO_OPS_OPCODE_NOP: CodeReg = CodeReg { offset: 7 };

// zirgen/circuit/recursion/code.cpp:22
pub const LAYOUT_CODE_INST_MACRO_OPS_OPCODE_SET_GLOBAL: CodeReg = CodeReg { offset: 16 };

// zirgen/circuit/recursion/code.cpp:22
pub const LAYOUT_CODE_INST_MACRO_OPS_OPCODE_SHA_FINI: CodeReg = CodeReg { offset: 13 };

// zirgen/circuit/recursion/code.cpp:22
pub const LAYOUT_CODE_INST_MACRO_OPS_OPCODE_SHA_INIT: CodeReg = CodeReg { offset: 12 };

// zirgen/circuit/recursion/code.cpp:22
pub const LAYOUT_CODE_INST_MACRO_OPS_OPCODE_SHA_LOAD: CodeReg = CodeReg { offset: 14 };

// zirgen/circuit/recursion/code.cpp:22
pub const LAYOUT_CODE_INST_MACRO_OPS_OPCODE_SHA_MIX: CodeReg = CodeReg { offset: 15 };

// zirgen/circuit/recursion/code.cpp:22
pub const LAYOUT_CODE_INST_MACRO_OPS_OPCODE_WOM_FINI: CodeReg = CodeReg { offset: 9 };

// zirgen/circuit/recursion/code.cpp:22
pub const LAYOUT_CODE_INST_MACRO_OPS_OPCODE_WOM_INIT: CodeReg = CodeReg { offset: 8 };

// zirgen/circuit/recursion/code.cpp:22
pub const LAYOUT_CODE_INST_MACRO_OPS_OPCODE: OneHot = OneHot {
    bit_and_elem: &LAYOUT_CODE_INST_MACRO_OPS_OPCODE_BIT_AND_ELEM,
    bit_op_shorts: &LAYOUT_CODE_INST_MACRO_OPS_OPCODE_BIT_OP_SHORTS,
    nop: &LAYOUT_CODE_INST_MACRO_OPS_OPCODE_NOP,
    set_global: &LAYOUT_CODE_INST_MACRO_OPS_OPCODE_SET_GLOBAL,
    sha_fini: &LAYOUT_CODE_INST_MACRO_OPS_OPCODE_SHA_FINI,
    sha_init: &LAYOUT_CODE_INST_MACRO_OPS_OPCODE_SHA_INIT,
    sha_load: &LAYOUT_CODE_INST_MACRO_OPS_OPCODE_SHA_LOAD,
    sha_mix: &LAYOUT_CODE_INST_MACRO_OPS_OPCODE_SHA_MIX,
    wom_fini: &LAYOUT_CODE_INST_MACRO_OPS_OPCODE_WOM_FINI,
    wom_init: &LAYOUT_CODE_INST_MACRO_OPS_OPCODE_WOM_INIT,
};

// :0
pub const LAYOUT_CODE_INST_MACRO_OPS_OPERAND_0_: CodeReg = CodeReg { offset: 17 };

// :0
pub const LAYOUT_CODE_INST_MACRO_OPS_OPERAND_1_: CodeReg = CodeReg { offset: 18 };

// :0
pub const LAYOUT_CODE_INST_MACRO_OPS_OPERAND_2_: CodeReg = CodeReg { offset: 19 };

// :0
pub const LAYOUT_CODE_INST_MACRO_OPS: RecursionMacroInst = RecursionMacroInst {
    opcode: &LAYOUT_CODE_INST_MACRO_OPS_OPCODE,
    operand: &[
        &LAYOUT_CODE_INST_MACRO_OPS_OPERAND_0_,
        &LAYOUT_CODE_INST_MACRO_OPS_OPERAND_1_,
        &LAYOUT_CODE_INST_MACRO_OPS_OPERAND_2_,
    ],
};

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_0_OPCODE: CodeReg = CodeReg { offset: 7 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_0_OPERAND_0_: CodeReg = CodeReg { offset: 8 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_0_OPERAND_1_: CodeReg = CodeReg { offset: 9 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_0_OPERAND_2_: CodeReg = CodeReg { offset: 10 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_0_: RecursionMicroInst = RecursionMicroInst {
    opcode: &LAYOUT_CODE_INST_MICRO_OPS_INST_0_OPCODE,
    operand: &[
        &LAYOUT_CODE_INST_MICRO_OPS_INST_0_OPERAND_0_,
        &LAYOUT_CODE_INST_MICRO_OPS_INST_0_OPERAND_1_,
        &LAYOUT_CODE_INST_MICRO_OPS_INST_0_OPERAND_2_,
    ],
};

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_1_OPCODE: CodeReg = CodeReg { offset: 11 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_1_OPERAND_0_: CodeReg = CodeReg { offset: 12 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_1_OPERAND_1_: CodeReg = CodeReg { offset: 13 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_1_OPERAND_2_: CodeReg = CodeReg { offset: 14 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_1_: RecursionMicroInst = RecursionMicroInst {
    opcode: &LAYOUT_CODE_INST_MICRO_OPS_INST_1_OPCODE,
    operand: &[
        &LAYOUT_CODE_INST_MICRO_OPS_INST_1_OPERAND_0_,
        &LAYOUT_CODE_INST_MICRO_OPS_INST_1_OPERAND_1_,
        &LAYOUT_CODE_INST_MICRO_OPS_INST_1_OPERAND_2_,
    ],
};

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_2_OPCODE: CodeReg = CodeReg { offset: 15 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_2_OPERAND_0_: CodeReg = CodeReg { offset: 16 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_2_OPERAND_1_: CodeReg = CodeReg { offset: 17 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_2_OPERAND_2_: CodeReg = CodeReg { offset: 18 };

// zirgen/circuit/recursion/code.cpp:17
pub const LAYOUT_CODE_INST_MICRO_OPS_INST_2_: RecursionMicroInst = RecursionMicroInst {
    opcode: &LAYOUT_CODE_INST_MICRO_OPS_INST_2_OPCODE,
    operand: &[
        &LAYOUT_CODE_INST_MICRO_OPS_INST_2_OPERAND_0_,
        &LAYOUT_CODE_INST_MICRO_OPS_INST_2_OPERAND_1_,
        &LAYOUT_CODE_INST_MICRO_OPS_INST_2_OPERAND_2_,
    ],
};

// :0
pub const LAYOUT_CODE_INST_MICRO_OPS: RecursionMicroInsts = RecursionMicroInsts {
    inst: &[
        &LAYOUT_CODE_INST_MICRO_OPS_INST_0_,
        &LAYOUT_CODE_INST_MICRO_OPS_INST_1_,
        &LAYOUT_CODE_INST_MICRO_OPS_INST_2_,
    ],
};

// zirgen/circuit/recursion/code.cpp:51
pub const LAYOUT_CODE_INST_POSEIDON_FULL_CYCLE_C0: CodeReg = CodeReg { offset: 7 };

// zirgen/circuit/recursion/code.cpp:51
pub const LAYOUT_CODE_INST_POSEIDON_FULL_CYCLE_C1: CodeReg = CodeReg { offset: 8 };

// zirgen/circuit/recursion/code.cpp:51
pub const LAYOUT_CODE_INST_POSEIDON_FULL_CYCLE_C2: CodeReg = CodeReg { offset: 9 };

// zirgen/circuit/recursion/code.cpp:51
pub const LAYOUT_CODE_INST_POSEIDON_FULL_CYCLE_C3: CodeReg = CodeReg { offset: 10 };

// zirgen/circuit/recursion/code.cpp:51
pub const LAYOUT_CODE_INST_POSEIDON_FULL_CYCLE: OneHot0 = OneHot0 {
    c0: &LAYOUT_CODE_INST_POSEIDON_FULL_CYCLE_C0,
    c1: &LAYOUT_CODE_INST_POSEIDON_FULL_CYCLE_C1,
    c2: &LAYOUT_CODE_INST_POSEIDON_FULL_CYCLE_C2,
    c3: &LAYOUT_CODE_INST_POSEIDON_FULL_CYCLE_C3,
};

// :0
pub const LAYOUT_CODE_INST_POSEIDON_FULL: RecursionPoseidonFullInst = RecursionPoseidonFullInst {
    cycle: &LAYOUT_CODE_INST_POSEIDON_FULL_CYCLE,
};

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_ADD_CONSTS: CodeReg = CodeReg { offset: 9 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_DO_MONT: CodeReg = CodeReg { offset: 7 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_KEEP_STATE: CodeReg = CodeReg { offset: 8 };

// zirgen/circuit/recursion/code.cpp:44
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_GROUP_G0: CodeReg = CodeReg { offset: 10 };

// zirgen/circuit/recursion/code.cpp:44
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_GROUP_G1: CodeReg = CodeReg { offset: 11 };

// zirgen/circuit/recursion/code.cpp:44
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_GROUP_G2: CodeReg = CodeReg { offset: 12 };

// zirgen/circuit/recursion/code.cpp:44
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_GROUP: OneHot1 = OneHot1 {
    g0: &LAYOUT_CODE_INST_POSEIDON_LOAD_GROUP_G0,
    g1: &LAYOUT_CODE_INST_POSEIDON_LOAD_GROUP_G1,
    g2: &LAYOUT_CODE_INST_POSEIDON_LOAD_GROUP_G2,
};

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_0_: CodeReg = CodeReg { offset: 13 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_1_: CodeReg = CodeReg { offset: 14 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_2_: CodeReg = CodeReg { offset: 15 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_3_: CodeReg = CodeReg { offset: 16 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_4_: CodeReg = CodeReg { offset: 17 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_5_: CodeReg = CodeReg { offset: 18 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_6_: CodeReg = CodeReg { offset: 19 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_7_: CodeReg = CodeReg { offset: 20 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_LOAD: RecursionPoseidonMemInst = RecursionPoseidonMemInst {
    add_consts: &LAYOUT_CODE_INST_POSEIDON_LOAD_ADD_CONSTS,
    do_mont: &LAYOUT_CODE_INST_POSEIDON_LOAD_DO_MONT,
    keep_state: &LAYOUT_CODE_INST_POSEIDON_LOAD_KEEP_STATE,
    group: &LAYOUT_CODE_INST_POSEIDON_LOAD_GROUP,
    inputs: &[
        &LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_0_,
        &LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_1_,
        &LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_2_,
        &LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_3_,
        &LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_4_,
        &LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_5_,
        &LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_6_,
        &LAYOUT_CODE_INST_POSEIDON_LOAD_INPUTS_7_,
    ],
};

// :0
pub const LAYOUT_CODE_INST_POSEIDON_PARTIAL: RecursionPoseidonInst = RecursionPoseidonInst {};

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE_ADD_CONSTS: CodeReg = CodeReg { offset: 9 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE_DO_MONT: CodeReg = CodeReg { offset: 7 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE_KEEP_STATE: CodeReg = CodeReg { offset: 8 };

// zirgen/circuit/recursion/code.cpp:44
pub const LAYOUT_CODE_INST_POSEIDON_STORE_GROUP_G0: CodeReg = CodeReg { offset: 10 };

// zirgen/circuit/recursion/code.cpp:44
pub const LAYOUT_CODE_INST_POSEIDON_STORE_GROUP_G1: CodeReg = CodeReg { offset: 11 };

// zirgen/circuit/recursion/code.cpp:44
pub const LAYOUT_CODE_INST_POSEIDON_STORE_GROUP_G2: CodeReg = CodeReg { offset: 12 };

// zirgen/circuit/recursion/code.cpp:44
pub const LAYOUT_CODE_INST_POSEIDON_STORE_GROUP: OneHot1 = OneHot1 {
    g0: &LAYOUT_CODE_INST_POSEIDON_STORE_GROUP_G0,
    g1: &LAYOUT_CODE_INST_POSEIDON_STORE_GROUP_G1,
    g2: &LAYOUT_CODE_INST_POSEIDON_STORE_GROUP_G2,
};

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_0_: CodeReg = CodeReg { offset: 13 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_1_: CodeReg = CodeReg { offset: 14 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_2_: CodeReg = CodeReg { offset: 15 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_3_: CodeReg = CodeReg { offset: 16 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_4_: CodeReg = CodeReg { offset: 17 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_5_: CodeReg = CodeReg { offset: 18 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_6_: CodeReg = CodeReg { offset: 19 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_7_: CodeReg = CodeReg { offset: 20 };

// :0
pub const LAYOUT_CODE_INST_POSEIDON_STORE: RecursionPoseidonMemInst = RecursionPoseidonMemInst {
    add_consts: &LAYOUT_CODE_INST_POSEIDON_STORE_ADD_CONSTS,
    do_mont: &LAYOUT_CODE_INST_POSEIDON_STORE_DO_MONT,
    keep_state: &LAYOUT_CODE_INST_POSEIDON_STORE_KEEP_STATE,
    group: &LAYOUT_CODE_INST_POSEIDON_STORE_GROUP,
    inputs: &[
        &LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_0_,
        &LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_1_,
        &LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_2_,
        &LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_3_,
        &LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_4_,
        &LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_5_,
        &LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_6_,
        &LAYOUT_CODE_INST_POSEIDON_STORE_INPUTS_7_,
    ],
};

// zirgen/circuit/recursion/code.cpp:64
pub const LAYOUT_CODE_INST: Mux = Mux {
    macro_ops: &LAYOUT_CODE_INST_MACRO_OPS,
    micro_ops: &LAYOUT_CODE_INST_MICRO_OPS,
    poseidon_full: &LAYOUT_CODE_INST_POSEIDON_FULL,
    poseidon_load: &LAYOUT_CODE_INST_POSEIDON_LOAD,
    poseidon_partial: &LAYOUT_CODE_INST_POSEIDON_PARTIAL,
    poseidon_store: &LAYOUT_CODE_INST_POSEIDON_STORE,
};

// zirgen/circuit/recursion/code.cpp:55
pub const LAYOUT_CODE_SELECT_MACRO_OPS: CodeReg = CodeReg { offset: 2 };

// zirgen/circuit/recursion/code.cpp:55
pub const LAYOUT_CODE_SELECT_MICRO_OPS: CodeReg = CodeReg { offset: 1 };

// zirgen/circuit/recursion/code.cpp:55
pub const LAYOUT_CODE_SELECT_POSEIDON_FULL: CodeReg = CodeReg { offset: 4 };

// zirgen/circuit/recursion/code.cpp:55
pub const LAYOUT_CODE_SELECT_POSEIDON_LOAD: CodeReg = CodeReg { offset: 3 };

// zirgen/circuit/recursion/code.cpp:55
pub const LAYOUT_CODE_SELECT_POSEIDON_PARTIAL: CodeReg = CodeReg { offset: 5 };

// zirgen/circuit/recursion/code.cpp:55
pub const LAYOUT_CODE_SELECT_POSEIDON_STORE: CodeReg = CodeReg { offset: 6 };

// zirgen/circuit/recursion/code.cpp:55
pub const LAYOUT_CODE_SELECT: OneHot2 = OneHot2 {
    macro_ops: &LAYOUT_CODE_SELECT_MACRO_OPS,
    micro_ops: &LAYOUT_CODE_SELECT_MICRO_OPS,
    poseidon_full: &LAYOUT_CODE_SELECT_POSEIDON_FULL,
    poseidon_load: &LAYOUT_CODE_SELECT_POSEIDON_LOAD,
    poseidon_partial: &LAYOUT_CODE_SELECT_POSEIDON_PARTIAL,
    poseidon_store: &LAYOUT_CODE_SELECT_POSEIDON_STORE,
};

// zirgen/circuit/recursion/top.cpp:9
pub const LAYOUT_CODE: RecursionCode = RecursionCode {
    write_addr: &LAYOUT_CODE_WRITE_ADDR,
    inst: &LAYOUT_CODE_INST,
    select: &LAYOUT_CODE_SELECT,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM_ADDR: DataReg = DataReg { offset: 11 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM_DATA_0_: DataReg = DataReg { offset: 12 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM_DATA_1_: DataReg = DataReg { offset: 13 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM_DATA_2_: DataReg = DataReg { offset: 14 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM_DATA_3_: DataReg = DataReg { offset: 15 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/bits.cpp:58
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM_ADDR: DataReg = DataReg { offset: 16 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM_DATA_0_: DataReg = DataReg { offset: 17 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM_DATA_1_: DataReg = DataReg { offset: 18 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM_DATA_2_: DataReg = DataReg { offset: 19 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM_DATA_3_: DataReg = DataReg { offset: 20 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/bits.cpp:58
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM_ADDR: DataReg = DataReg { offset: 21 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM_DATA_0_: DataReg = DataReg { offset: 22 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM_DATA_1_: DataReg = DataReg { offset: 23 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM_DATA_2_: DataReg = DataReg { offset: 24 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM_DATA_3_: DataReg = DataReg { offset: 25 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/bits.cpp:58
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT_WOM,
};

// zirgen/circuit/recursion/wom.cpp:102
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_WOM_BODY_PLONK_BODY: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/bits.cpp:58
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_WOM_BODY: RecursionWomBody = RecursionWomBody {
    plonk_body: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_WOM_BODY_PLONK_BODY,
};

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_0_: DataReg = DataReg { offset: 36 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_1_: DataReg = DataReg { offset: 38 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_2_: DataReg = DataReg { offset: 40 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_3_: DataReg = DataReg { offset: 42 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_4_: DataReg = DataReg { offset: 44 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_5_: DataReg = DataReg { offset: 46 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_6_: DataReg = DataReg { offset: 48 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_7_: DataReg = DataReg { offset: 50 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_8_: DataReg = DataReg { offset: 52 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_9_: DataReg = DataReg { offset: 54 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_10_: DataReg = DataReg { offset: 56 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_11_: DataReg = DataReg { offset: 58 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_12_: DataReg = DataReg { offset: 60 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_13_: DataReg = DataReg { offset: 62 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_14_: DataReg = DataReg { offset: 64 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_15_: DataReg = DataReg { offset: 66 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_16_: DataReg = DataReg { offset: 68 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_17_: DataReg = DataReg { offset: 70 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_18_: DataReg = DataReg { offset: 72 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_19_: DataReg = DataReg { offset: 74 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_20_: DataReg = DataReg { offset: 76 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_21_: DataReg = DataReg { offset: 78 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_22_: DataReg = DataReg { offset: 80 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_23_: DataReg = DataReg { offset: 82 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_24_: DataReg = DataReg { offset: 84 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_25_: DataReg = DataReg { offset: 86 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_26_: DataReg = DataReg { offset: 88 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_27_: DataReg = DataReg { offset: 90 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_28_: DataReg = DataReg { offset: 92 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_29_: DataReg = DataReg { offset: 94 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_30_: DataReg = DataReg { offset: 96 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_0_: DataReg = DataReg { offset: 37 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_1_: DataReg = DataReg { offset: 39 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_2_: DataReg = DataReg { offset: 41 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_3_: DataReg = DataReg { offset: 43 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_4_: DataReg = DataReg { offset: 45 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_5_: DataReg = DataReg { offset: 47 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_6_: DataReg = DataReg { offset: 49 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_7_: DataReg = DataReg { offset: 51 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_8_: DataReg = DataReg { offset: 53 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_9_: DataReg = DataReg { offset: 55 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_10_: DataReg = DataReg { offset: 57 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_11_: DataReg = DataReg { offset: 59 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_12_: DataReg = DataReg { offset: 61 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_13_: DataReg = DataReg { offset: 63 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_14_: DataReg = DataReg { offset: 65 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_15_: DataReg = DataReg { offset: 67 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_16_: DataReg = DataReg { offset: 69 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_17_: DataReg = DataReg { offset: 71 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_18_: DataReg = DataReg { offset: 73 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_19_: DataReg = DataReg { offset: 75 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_20_: DataReg = DataReg { offset: 77 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_21_: DataReg = DataReg { offset: 79 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_22_: DataReg = DataReg { offset: 81 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_23_: DataReg = DataReg { offset: 83 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_24_: DataReg = DataReg { offset: 85 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_25_: DataReg = DataReg { offset: 87 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_26_: DataReg = DataReg { offset: 89 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_27_: DataReg = DataReg { offset: 91 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_28_: DataReg = DataReg { offset: 93 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_29_: DataReg = DataReg { offset: 95 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_30_: DataReg = DataReg { offset: 97 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM: RecursionBitAndElem = RecursionBitAndElem {
    in_a: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_A,
    in_b: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_IN_B,
    out: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_OUT,
    wom_body: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_WOM_BODY,
    bits_a: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_A_30_,
    ],
    bits_b: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM_BITS_B_30_,
    ],
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM_ADDR: DataReg = DataReg { offset: 11 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM_DATA_0_: DataReg = DataReg { offset: 12 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM_DATA_1_: DataReg = DataReg { offset: 13 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM_DATA_2_: DataReg = DataReg { offset: 14 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM_DATA_3_: DataReg = DataReg { offset: 15 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/bits.cpp:9
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM_ADDR: DataReg = DataReg { offset: 16 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM_DATA_0_: DataReg = DataReg { offset: 17 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM_DATA_1_: DataReg = DataReg { offset: 18 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM_DATA_2_: DataReg = DataReg { offset: 19 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM_DATA_3_: DataReg = DataReg { offset: 20 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/bits.cpp:9
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM_ADDR: DataReg = DataReg { offset: 21 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM_DATA_0_: DataReg = DataReg { offset: 22 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM_DATA_1_: DataReg = DataReg { offset: 23 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM_DATA_2_: DataReg = DataReg { offset: 24 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM_DATA_3_: DataReg = DataReg { offset: 25 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/bits.cpp:9
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT_WOM,
};

// zirgen/circuit/recursion/wom.cpp:102
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_WOM_BODY_PLONK_BODY: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/bits.cpp:9
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_WOM_BODY: RecursionWomBody = RecursionWomBody {
    plonk_body: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_WOM_BODY_PLONK_BODY,
};

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_0_: DataReg = DataReg { offset: 36 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_1_: DataReg = DataReg { offset: 37 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_2_: DataReg = DataReg { offset: 38 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_3_: DataReg = DataReg { offset: 39 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_4_: DataReg = DataReg { offset: 40 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_5_: DataReg = DataReg { offset: 41 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_6_: DataReg = DataReg { offset: 42 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_7_: DataReg = DataReg { offset: 43 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_8_: DataReg = DataReg { offset: 44 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_9_: DataReg = DataReg { offset: 45 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_10_: DataReg = DataReg { offset: 46 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_11_: DataReg = DataReg { offset: 47 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_12_: DataReg = DataReg { offset: 48 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_13_: DataReg = DataReg { offset: 49 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_14_: DataReg = DataReg { offset: 50 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_15_: DataReg = DataReg { offset: 51 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_16_: DataReg = DataReg { offset: 52 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_17_: DataReg = DataReg { offset: 53 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_18_: DataReg = DataReg { offset: 54 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_19_: DataReg = DataReg { offset: 55 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_20_: DataReg = DataReg { offset: 56 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_21_: DataReg = DataReg { offset: 57 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_22_: DataReg = DataReg { offset: 58 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_23_: DataReg = DataReg { offset: 59 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_24_: DataReg = DataReg { offset: 60 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_25_: DataReg = DataReg { offset: 61 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_26_: DataReg = DataReg { offset: 62 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_27_: DataReg = DataReg { offset: 63 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_28_: DataReg = DataReg { offset: 64 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_29_: DataReg = DataReg { offset: 65 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_30_: DataReg = DataReg { offset: 66 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_31_: DataReg = DataReg { offset: 67 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_0_: DataReg = DataReg { offset: 68 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_1_: DataReg = DataReg { offset: 69 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_2_: DataReg = DataReg { offset: 70 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_3_: DataReg = DataReg { offset: 71 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_4_: DataReg = DataReg { offset: 72 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_5_: DataReg = DataReg { offset: 73 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_6_: DataReg = DataReg { offset: 74 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_7_: DataReg = DataReg { offset: 75 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_8_: DataReg = DataReg { offset: 76 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_9_: DataReg = DataReg { offset: 77 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_10_: DataReg = DataReg { offset: 78 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_11_: DataReg = DataReg { offset: 79 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_12_: DataReg = DataReg { offset: 80 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_13_: DataReg = DataReg { offset: 81 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_14_: DataReg = DataReg { offset: 82 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_15_: DataReg = DataReg { offset: 83 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_16_: DataReg = DataReg { offset: 84 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_17_: DataReg = DataReg { offset: 85 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_18_: DataReg = DataReg { offset: 86 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_19_: DataReg = DataReg { offset: 87 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_20_: DataReg = DataReg { offset: 88 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_21_: DataReg = DataReg { offset: 89 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_22_: DataReg = DataReg { offset: 90 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_23_: DataReg = DataReg { offset: 91 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_24_: DataReg = DataReg { offset: 92 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_25_: DataReg = DataReg { offset: 93 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_26_: DataReg = DataReg { offset: 94 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_27_: DataReg = DataReg { offset: 95 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_28_: DataReg = DataReg { offset: 96 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_29_: DataReg = DataReg { offset: 97 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_30_: DataReg = DataReg { offset: 98 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_31_: DataReg = DataReg { offset: 99 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS: RecursionBitOpShorts = RecursionBitOpShorts {
    in_a: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_A,
    in_b: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_IN_B,
    out: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_OUT,
    wom_body: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_WOM_BODY,
    bits_a: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_A_31_,
    ],
    bits_b: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS_BITS_B_31_,
    ],
};

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_NOP: RecursionPoseidonInst = RecursionPoseidonInst {};

// zirgen/circuit/recursion/macro.cpp:22
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_SELECT_HOT_0_: DataReg = DataReg { offset: 11 };

// zirgen/circuit/recursion/macro.cpp:22
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_SELECT_HOT_1_: DataReg = DataReg { offset: 12 };

// zirgen/circuit/recursion/macro.cpp:22
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_SELECT_HOT_2_: DataReg = DataReg { offset: 13 };

// zirgen/circuit/recursion/macro.cpp:22
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_SELECT_HOT_3_: DataReg = DataReg { offset: 14 };

// zirgen/circuit/recursion/macro.cpp:22
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_SELECT: OneHot3 = OneHot3 {
    hot: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_SELECT_HOT_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_SELECT_HOT_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_SELECT_HOT_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_SELECT_HOT_3_,
    ],
};

// zirgen/circuit/recursion/wom.cpp:102
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_WOM_BODY_PLONK_BODY: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/macro.cpp:22
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_WOM_BODY: RecursionWomBody = RecursionWomBody {
    plonk_body: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_WOM_BODY_PLONK_BODY,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM_ADDR: DataReg = DataReg { offset: 15 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM_DATA_0_: DataReg = DataReg { offset: 16 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM_DATA_1_: DataReg = DataReg { offset: 17 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM_DATA_2_: DataReg = DataReg { offset: 18 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM_DATA_3_: DataReg = DataReg { offset: 19 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM_DATA_3_,
        ],
    };

// compiler/edsl/component.h:107
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM_ADDR: DataReg = DataReg { offset: 20 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM_DATA_0_: DataReg = DataReg { offset: 21 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM_DATA_1_: DataReg = DataReg { offset: 22 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM_DATA_2_: DataReg = DataReg { offset: 23 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM_DATA_3_: DataReg = DataReg { offset: 24 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM_DATA_3_,
        ],
    };

// compiler/edsl/component.h:107
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM_ADDR: DataReg = DataReg { offset: 25 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM_DATA_0_: DataReg = DataReg { offset: 26 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM_DATA_1_: DataReg = DataReg { offset: 27 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM_DATA_2_: DataReg = DataReg { offset: 28 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM_DATA_3_: DataReg = DataReg { offset: 29 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM_DATA_3_,
        ],
    };

// compiler/edsl/component.h:107
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM_ADDR: DataReg = DataReg { offset: 30 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM_DATA_0_: DataReg = DataReg { offset: 31 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM_DATA_1_: DataReg = DataReg { offset: 32 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM_DATA_2_: DataReg = DataReg { offset: 33 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM_DATA_3_: DataReg = DataReg { offset: 34 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM_DATA_3_,
        ],
    };

// compiler/edsl/component.h:107
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_WOM,
};

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_0_: OutReg = OutReg { offset: 0 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_1_: OutReg = OutReg { offset: 1 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_2_: OutReg = OutReg { offset: 2 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_3_: OutReg = OutReg { offset: 3 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_4_: OutReg = OutReg { offset: 4 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_5_: OutReg = OutReg { offset: 5 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_6_: OutReg = OutReg { offset: 6 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_7_: OutReg = OutReg { offset: 7 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_8_: OutReg = OutReg { offset: 8 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_9_: OutReg = OutReg { offset: 9 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_10_: OutReg = OutReg { offset: 10 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_11_: OutReg = OutReg { offset: 11 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_12_: OutReg = OutReg { offset: 12 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_13_: OutReg = OutReg { offset: 13 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_14_: OutReg = OutReg { offset: 14 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_15_: OutReg = OutReg { offset: 15 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_16_: OutReg = OutReg { offset: 16 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_17_: OutReg = OutReg { offset: 17 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_18_: OutReg = OutReg { offset: 18 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_19_: OutReg = OutReg { offset: 19 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_20_: OutReg = OutReg { offset: 20 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_21_: OutReg = OutReg { offset: 21 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_22_: OutReg = OutReg { offset: 22 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_23_: OutReg = OutReg { offset: 23 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_24_: OutReg = OutReg { offset: 24 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_25_: OutReg = OutReg { offset: 25 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_26_: OutReg = OutReg { offset: 26 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_27_: OutReg = OutReg { offset: 27 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_28_: OutReg = OutReg { offset: 28 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_29_: OutReg = OutReg { offset: 29 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_30_: OutReg = OutReg { offset: 30 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_31_: OutReg = OutReg { offset: 31 };

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL: RecursionSetGlobal = RecursionSetGlobal {
    select: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_SELECT,
    wom_body: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_WOM_BODY,
    regs: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_REGS_3_,
    ],
    out: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL_OUT_31_,
    ],
};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_CARRY_HI: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_CARRY_HIGH: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM_ADDR: DataReg =
    DataReg { offset: 11 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM_DATA_0_: DataReg =
    DataReg { offset: 12 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM_DATA_1_: DataReg =
    DataReg { offset: 13 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM_DATA_2_: DataReg =
    DataReg { offset: 14 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM_DATA_3_: DataReg =
    DataReg { offset: 15 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM_ADDR: DataReg =
    DataReg { offset: 16 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM_DATA_0_: DataReg =
    DataReg { offset: 17 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM_DATA_1_: DataReg =
    DataReg { offset: 18 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM_DATA_2_: DataReg =
    DataReg { offset: 19 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM_DATA_3_: DataReg =
    DataReg { offset: 20 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1_WOM,
};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_CARRY_HIGH: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_RAW_0_: DataReg = DataReg { offset: 92 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_RAW_1_: DataReg = DataReg { offset: 93 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_0_: DataReg = DataReg { offset: 94 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_1_: DataReg = DataReg { offset: 95 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_2_: DataReg = DataReg { offset: 96 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_3_: DataReg = DataReg { offset: 97 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_4_: DataReg = DataReg { offset: 98 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_5_: DataReg = DataReg { offset: 99 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_6_: DataReg = DataReg { offset: 100 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_7_: DataReg = DataReg { offset: 101 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_8_: DataReg = DataReg { offset: 102 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_9_: DataReg = DataReg { offset: 103 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_10_: DataReg = DataReg { offset: 104 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_11_: DataReg = DataReg { offset: 105 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_12_: DataReg = DataReg { offset: 106 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_13_: DataReg = DataReg { offset: 107 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_14_: DataReg = DataReg { offset: 108 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_15_: DataReg = DataReg { offset: 109 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_16_: DataReg = DataReg { offset: 110 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_17_: DataReg = DataReg { offset: 111 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_18_: DataReg = DataReg { offset: 112 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_19_: DataReg = DataReg { offset: 113 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_20_: DataReg = DataReg { offset: 114 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_21_: DataReg = DataReg { offset: 115 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_22_: DataReg = DataReg { offset: 116 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_23_: DataReg = DataReg { offset: 117 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_24_: DataReg = DataReg { offset: 118 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_25_: DataReg = DataReg { offset: 119 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_26_: DataReg = DataReg { offset: 120 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_27_: DataReg = DataReg { offset: 121 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_28_: DataReg = DataReg { offset: 122 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_29_: DataReg = DataReg { offset: 123 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_30_: DataReg = DataReg { offset: 124 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_31_: DataReg = DataReg { offset: 125 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_0_: DataReg = DataReg { offset: 60 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_1_: DataReg = DataReg { offset: 61 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_2_: DataReg = DataReg { offset: 62 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_3_: DataReg = DataReg { offset: 63 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_4_: DataReg = DataReg { offset: 64 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_5_: DataReg = DataReg { offset: 65 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_6_: DataReg = DataReg { offset: 66 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_7_: DataReg = DataReg { offset: 67 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_8_: DataReg = DataReg { offset: 68 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_9_: DataReg = DataReg { offset: 69 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_10_: DataReg = DataReg { offset: 70 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_11_: DataReg = DataReg { offset: 71 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_12_: DataReg = DataReg { offset: 72 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_13_: DataReg = DataReg { offset: 73 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_14_: DataReg = DataReg { offset: 74 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_15_: DataReg = DataReg { offset: 75 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_16_: DataReg = DataReg { offset: 76 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_17_: DataReg = DataReg { offset: 77 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_18_: DataReg = DataReg { offset: 78 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_19_: DataReg = DataReg { offset: 79 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_20_: DataReg = DataReg { offset: 80 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_21_: DataReg = DataReg { offset: 81 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_22_: DataReg = DataReg { offset: 82 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_23_: DataReg = DataReg { offset: 83 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_24_: DataReg = DataReg { offset: 84 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_25_: DataReg = DataReg { offset: 85 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_26_: DataReg = DataReg { offset: 86 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_27_: DataReg = DataReg { offset: 87 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_28_: DataReg = DataReg { offset: 88 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_29_: DataReg = DataReg { offset: 89 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_30_: DataReg = DataReg { offset: 90 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_31_: DataReg = DataReg { offset: 91 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_RAW_0_: DataReg = DataReg { offset: 126 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_RAW_1_: DataReg = DataReg { offset: 127 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_RAW_0_: DataReg = DataReg { offset: 58 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_RAW_1_: DataReg = DataReg { offset: 59 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_0_: DataReg = DataReg { offset: 26 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_1_: DataReg = DataReg { offset: 27 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_2_: DataReg = DataReg { offset: 28 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_3_: DataReg = DataReg { offset: 29 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_4_: DataReg = DataReg { offset: 30 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_5_: DataReg = DataReg { offset: 31 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_6_: DataReg = DataReg { offset: 32 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_7_: DataReg = DataReg { offset: 33 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_8_: DataReg = DataReg { offset: 34 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_9_: DataReg = DataReg { offset: 35 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_10_: DataReg = DataReg { offset: 36 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_11_: DataReg = DataReg { offset: 37 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_12_: DataReg = DataReg { offset: 38 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_13_: DataReg = DataReg { offset: 39 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_14_: DataReg = DataReg { offset: 40 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_15_: DataReg = DataReg { offset: 41 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_16_: DataReg = DataReg { offset: 42 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_17_: DataReg = DataReg { offset: 43 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_18_: DataReg = DataReg { offset: 44 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_19_: DataReg = DataReg { offset: 45 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_20_: DataReg = DataReg { offset: 46 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_21_: DataReg = DataReg { offset: 47 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_22_: DataReg = DataReg { offset: 48 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_23_: DataReg = DataReg { offset: 49 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_24_: DataReg = DataReg { offset: 50 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_25_: DataReg = DataReg { offset: 51 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_26_: DataReg = DataReg { offset: 52 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_27_: DataReg = DataReg { offset: 53 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_28_: DataReg = DataReg { offset: 54 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_29_: DataReg = DataReg { offset: 55 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_30_: DataReg = DataReg { offset: 56 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_31_: DataReg = DataReg { offset: 57 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE: RecursionShaCycle = RecursionShaCycle {
    a_carry_hi: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_CARRY_HI,
    a_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_CARRY_LOW,
    e_carry_high: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_CARRY_HIGH,
    e_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_CARRY_LOW,
    io0: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO0,
    io1: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_IO1,
    w_carry_high: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_CARRY_HIGH,
    w_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_CARRY_LOW,
    e_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_RAW_1_,
    ],
    w: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_31_,
    ],
    e: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_E_31_,
    ],
    w_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_W_RAW_1_,
    ],
    a_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_RAW_1_,
    ],
    a: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE_A_31_,
    ],
};

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI: RecursionShaWrap = RecursionShaWrap {
    sha_cycle: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI_SHA_CYCLE,
};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_CARRY_HI: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_CARRY_HIGH: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM_ADDR: DataReg =
    DataReg { offset: 11 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM_DATA_0_: DataReg =
    DataReg { offset: 12 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM_DATA_1_: DataReg =
    DataReg { offset: 13 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM_DATA_2_: DataReg =
    DataReg { offset: 14 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM_DATA_3_: DataReg =
    DataReg { offset: 15 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM_ADDR: DataReg =
    DataReg { offset: 16 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM_DATA_0_: DataReg =
    DataReg { offset: 17 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM_DATA_1_: DataReg =
    DataReg { offset: 18 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM_DATA_2_: DataReg =
    DataReg { offset: 19 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM_DATA_3_: DataReg =
    DataReg { offset: 20 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1_WOM,
};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_CARRY_HIGH: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_RAW_0_: DataReg = DataReg { offset: 92 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_RAW_1_: DataReg = DataReg { offset: 93 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_0_: DataReg = DataReg { offset: 94 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_1_: DataReg = DataReg { offset: 95 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_2_: DataReg = DataReg { offset: 96 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_3_: DataReg = DataReg { offset: 97 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_4_: DataReg = DataReg { offset: 98 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_5_: DataReg = DataReg { offset: 99 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_6_: DataReg = DataReg { offset: 100 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_7_: DataReg = DataReg { offset: 101 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_8_: DataReg = DataReg { offset: 102 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_9_: DataReg = DataReg { offset: 103 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_10_: DataReg = DataReg { offset: 104 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_11_: DataReg = DataReg { offset: 105 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_12_: DataReg = DataReg { offset: 106 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_13_: DataReg = DataReg { offset: 107 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_14_: DataReg = DataReg { offset: 108 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_15_: DataReg = DataReg { offset: 109 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_16_: DataReg = DataReg { offset: 110 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_17_: DataReg = DataReg { offset: 111 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_18_: DataReg = DataReg { offset: 112 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_19_: DataReg = DataReg { offset: 113 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_20_: DataReg = DataReg { offset: 114 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_21_: DataReg = DataReg { offset: 115 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_22_: DataReg = DataReg { offset: 116 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_23_: DataReg = DataReg { offset: 117 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_24_: DataReg = DataReg { offset: 118 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_25_: DataReg = DataReg { offset: 119 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_26_: DataReg = DataReg { offset: 120 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_27_: DataReg = DataReg { offset: 121 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_28_: DataReg = DataReg { offset: 122 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_29_: DataReg = DataReg { offset: 123 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_30_: DataReg = DataReg { offset: 124 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_31_: DataReg = DataReg { offset: 125 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_0_: DataReg = DataReg { offset: 60 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_1_: DataReg = DataReg { offset: 61 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_2_: DataReg = DataReg { offset: 62 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_3_: DataReg = DataReg { offset: 63 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_4_: DataReg = DataReg { offset: 64 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_5_: DataReg = DataReg { offset: 65 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_6_: DataReg = DataReg { offset: 66 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_7_: DataReg = DataReg { offset: 67 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_8_: DataReg = DataReg { offset: 68 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_9_: DataReg = DataReg { offset: 69 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_10_: DataReg = DataReg { offset: 70 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_11_: DataReg = DataReg { offset: 71 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_12_: DataReg = DataReg { offset: 72 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_13_: DataReg = DataReg { offset: 73 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_14_: DataReg = DataReg { offset: 74 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_15_: DataReg = DataReg { offset: 75 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_16_: DataReg = DataReg { offset: 76 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_17_: DataReg = DataReg { offset: 77 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_18_: DataReg = DataReg { offset: 78 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_19_: DataReg = DataReg { offset: 79 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_20_: DataReg = DataReg { offset: 80 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_21_: DataReg = DataReg { offset: 81 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_22_: DataReg = DataReg { offset: 82 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_23_: DataReg = DataReg { offset: 83 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_24_: DataReg = DataReg { offset: 84 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_25_: DataReg = DataReg { offset: 85 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_26_: DataReg = DataReg { offset: 86 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_27_: DataReg = DataReg { offset: 87 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_28_: DataReg = DataReg { offset: 88 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_29_: DataReg = DataReg { offset: 89 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_30_: DataReg = DataReg { offset: 90 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_31_: DataReg = DataReg { offset: 91 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_RAW_0_: DataReg = DataReg { offset: 126 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_RAW_1_: DataReg = DataReg { offset: 127 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_RAW_0_: DataReg = DataReg { offset: 58 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_RAW_1_: DataReg = DataReg { offset: 59 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_0_: DataReg = DataReg { offset: 26 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_1_: DataReg = DataReg { offset: 27 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_2_: DataReg = DataReg { offset: 28 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_3_: DataReg = DataReg { offset: 29 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_4_: DataReg = DataReg { offset: 30 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_5_: DataReg = DataReg { offset: 31 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_6_: DataReg = DataReg { offset: 32 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_7_: DataReg = DataReg { offset: 33 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_8_: DataReg = DataReg { offset: 34 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_9_: DataReg = DataReg { offset: 35 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_10_: DataReg = DataReg { offset: 36 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_11_: DataReg = DataReg { offset: 37 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_12_: DataReg = DataReg { offset: 38 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_13_: DataReg = DataReg { offset: 39 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_14_: DataReg = DataReg { offset: 40 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_15_: DataReg = DataReg { offset: 41 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_16_: DataReg = DataReg { offset: 42 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_17_: DataReg = DataReg { offset: 43 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_18_: DataReg = DataReg { offset: 44 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_19_: DataReg = DataReg { offset: 45 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_20_: DataReg = DataReg { offset: 46 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_21_: DataReg = DataReg { offset: 47 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_22_: DataReg = DataReg { offset: 48 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_23_: DataReg = DataReg { offset: 49 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_24_: DataReg = DataReg { offset: 50 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_25_: DataReg = DataReg { offset: 51 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_26_: DataReg = DataReg { offset: 52 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_27_: DataReg = DataReg { offset: 53 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_28_: DataReg = DataReg { offset: 54 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_29_: DataReg = DataReg { offset: 55 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_30_: DataReg = DataReg { offset: 56 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_31_: DataReg = DataReg { offset: 57 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE: RecursionShaCycle = RecursionShaCycle {
    a_carry_hi: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_CARRY_HI,
    a_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_CARRY_LOW,
    e_carry_high: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_CARRY_HIGH,
    e_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_CARRY_LOW,
    io0: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO0,
    io1: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_IO1,
    w_carry_high: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_CARRY_HIGH,
    w_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_CARRY_LOW,
    e_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_RAW_1_,
    ],
    w: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_31_,
    ],
    e: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_E_31_,
    ],
    w_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_W_RAW_1_,
    ],
    a_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_RAW_1_,
    ],
    a: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE_A_31_,
    ],
};

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT: RecursionShaWrap = RecursionShaWrap {
    sha_cycle: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT_SHA_CYCLE,
};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_CARRY_HI: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_CARRY_HIGH: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM_ADDR: DataReg =
    DataReg { offset: 11 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM_DATA_0_: DataReg =
    DataReg { offset: 12 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM_DATA_1_: DataReg =
    DataReg { offset: 13 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM_DATA_2_: DataReg =
    DataReg { offset: 14 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM_DATA_3_: DataReg =
    DataReg { offset: 15 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM_ADDR: DataReg =
    DataReg { offset: 16 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM_DATA_0_: DataReg =
    DataReg { offset: 17 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM_DATA_1_: DataReg =
    DataReg { offset: 18 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM_DATA_2_: DataReg =
    DataReg { offset: 19 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM_DATA_3_: DataReg =
    DataReg { offset: 20 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1_WOM,
};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_CARRY_HIGH: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_RAW_0_: DataReg = DataReg { offset: 92 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_RAW_1_: DataReg = DataReg { offset: 93 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_0_: DataReg = DataReg { offset: 94 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_1_: DataReg = DataReg { offset: 95 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_2_: DataReg = DataReg { offset: 96 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_3_: DataReg = DataReg { offset: 97 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_4_: DataReg = DataReg { offset: 98 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_5_: DataReg = DataReg { offset: 99 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_6_: DataReg = DataReg { offset: 100 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_7_: DataReg = DataReg { offset: 101 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_8_: DataReg = DataReg { offset: 102 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_9_: DataReg = DataReg { offset: 103 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_10_: DataReg = DataReg { offset: 104 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_11_: DataReg = DataReg { offset: 105 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_12_: DataReg = DataReg { offset: 106 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_13_: DataReg = DataReg { offset: 107 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_14_: DataReg = DataReg { offset: 108 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_15_: DataReg = DataReg { offset: 109 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_16_: DataReg = DataReg { offset: 110 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_17_: DataReg = DataReg { offset: 111 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_18_: DataReg = DataReg { offset: 112 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_19_: DataReg = DataReg { offset: 113 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_20_: DataReg = DataReg { offset: 114 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_21_: DataReg = DataReg { offset: 115 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_22_: DataReg = DataReg { offset: 116 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_23_: DataReg = DataReg { offset: 117 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_24_: DataReg = DataReg { offset: 118 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_25_: DataReg = DataReg { offset: 119 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_26_: DataReg = DataReg { offset: 120 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_27_: DataReg = DataReg { offset: 121 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_28_: DataReg = DataReg { offset: 122 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_29_: DataReg = DataReg { offset: 123 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_30_: DataReg = DataReg { offset: 124 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_31_: DataReg = DataReg { offset: 125 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_0_: DataReg = DataReg { offset: 60 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_1_: DataReg = DataReg { offset: 61 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_2_: DataReg = DataReg { offset: 62 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_3_: DataReg = DataReg { offset: 63 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_4_: DataReg = DataReg { offset: 64 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_5_: DataReg = DataReg { offset: 65 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_6_: DataReg = DataReg { offset: 66 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_7_: DataReg = DataReg { offset: 67 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_8_: DataReg = DataReg { offset: 68 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_9_: DataReg = DataReg { offset: 69 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_10_: DataReg = DataReg { offset: 70 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_11_: DataReg = DataReg { offset: 71 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_12_: DataReg = DataReg { offset: 72 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_13_: DataReg = DataReg { offset: 73 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_14_: DataReg = DataReg { offset: 74 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_15_: DataReg = DataReg { offset: 75 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_16_: DataReg = DataReg { offset: 76 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_17_: DataReg = DataReg { offset: 77 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_18_: DataReg = DataReg { offset: 78 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_19_: DataReg = DataReg { offset: 79 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_20_: DataReg = DataReg { offset: 80 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_21_: DataReg = DataReg { offset: 81 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_22_: DataReg = DataReg { offset: 82 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_23_: DataReg = DataReg { offset: 83 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_24_: DataReg = DataReg { offset: 84 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_25_: DataReg = DataReg { offset: 85 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_26_: DataReg = DataReg { offset: 86 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_27_: DataReg = DataReg { offset: 87 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_28_: DataReg = DataReg { offset: 88 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_29_: DataReg = DataReg { offset: 89 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_30_: DataReg = DataReg { offset: 90 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_31_: DataReg = DataReg { offset: 91 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_RAW_0_: DataReg = DataReg { offset: 126 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_RAW_1_: DataReg = DataReg { offset: 127 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_RAW_0_: DataReg = DataReg { offset: 58 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_RAW_1_: DataReg = DataReg { offset: 59 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_0_: DataReg = DataReg { offset: 26 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_1_: DataReg = DataReg { offset: 27 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_2_: DataReg = DataReg { offset: 28 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_3_: DataReg = DataReg { offset: 29 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_4_: DataReg = DataReg { offset: 30 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_5_: DataReg = DataReg { offset: 31 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_6_: DataReg = DataReg { offset: 32 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_7_: DataReg = DataReg { offset: 33 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_8_: DataReg = DataReg { offset: 34 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_9_: DataReg = DataReg { offset: 35 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_10_: DataReg = DataReg { offset: 36 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_11_: DataReg = DataReg { offset: 37 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_12_: DataReg = DataReg { offset: 38 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_13_: DataReg = DataReg { offset: 39 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_14_: DataReg = DataReg { offset: 40 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_15_: DataReg = DataReg { offset: 41 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_16_: DataReg = DataReg { offset: 42 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_17_: DataReg = DataReg { offset: 43 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_18_: DataReg = DataReg { offset: 44 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_19_: DataReg = DataReg { offset: 45 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_20_: DataReg = DataReg { offset: 46 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_21_: DataReg = DataReg { offset: 47 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_22_: DataReg = DataReg { offset: 48 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_23_: DataReg = DataReg { offset: 49 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_24_: DataReg = DataReg { offset: 50 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_25_: DataReg = DataReg { offset: 51 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_26_: DataReg = DataReg { offset: 52 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_27_: DataReg = DataReg { offset: 53 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_28_: DataReg = DataReg { offset: 54 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_29_: DataReg = DataReg { offset: 55 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_30_: DataReg = DataReg { offset: 56 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_31_: DataReg = DataReg { offset: 57 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE: RecursionShaCycle = RecursionShaCycle {
    a_carry_hi: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_CARRY_HI,
    a_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_CARRY_LOW,
    e_carry_high: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_CARRY_HIGH,
    e_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_CARRY_LOW,
    io0: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO0,
    io1: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_IO1,
    w_carry_high: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_CARRY_HIGH,
    w_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_CARRY_LOW,
    e_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_RAW_1_,
    ],
    w: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_31_,
    ],
    e: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_E_31_,
    ],
    w_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_W_RAW_1_,
    ],
    a_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_RAW_1_,
    ],
    a: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE_A_31_,
    ],
};

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD: RecursionShaWrap = RecursionShaWrap {
    sha_cycle: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD_SHA_CYCLE,
};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_CARRY_HI: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_CARRY_HIGH: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM_ADDR: DataReg = DataReg { offset: 11 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM_DATA_0_: DataReg =
    DataReg { offset: 12 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM_DATA_1_: DataReg =
    DataReg { offset: 13 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM_DATA_2_: DataReg =
    DataReg { offset: 14 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM_DATA_3_: DataReg =
    DataReg { offset: 15 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM_ADDR: DataReg = DataReg { offset: 16 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM_DATA_0_: DataReg =
    DataReg { offset: 17 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM_DATA_1_: DataReg =
    DataReg { offset: 18 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM_DATA_2_: DataReg =
    DataReg { offset: 19 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM_DATA_3_: DataReg =
    DataReg { offset: 20 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM_DATA_0_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM_DATA_1_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM_DATA_2_,
            &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM_DATA_3_,
        ],
    };

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1_WOM,
};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_CARRY_HIGH: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/sha.cpp:138
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_CARRY_LOW: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_RAW_0_: DataReg = DataReg { offset: 92 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_RAW_1_: DataReg = DataReg { offset: 93 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_0_: DataReg = DataReg { offset: 94 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_1_: DataReg = DataReg { offset: 95 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_2_: DataReg = DataReg { offset: 96 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_3_: DataReg = DataReg { offset: 97 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_4_: DataReg = DataReg { offset: 98 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_5_: DataReg = DataReg { offset: 99 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_6_: DataReg = DataReg { offset: 100 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_7_: DataReg = DataReg { offset: 101 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_8_: DataReg = DataReg { offset: 102 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_9_: DataReg = DataReg { offset: 103 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_10_: DataReg = DataReg { offset: 104 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_11_: DataReg = DataReg { offset: 105 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_12_: DataReg = DataReg { offset: 106 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_13_: DataReg = DataReg { offset: 107 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_14_: DataReg = DataReg { offset: 108 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_15_: DataReg = DataReg { offset: 109 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_16_: DataReg = DataReg { offset: 110 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_17_: DataReg = DataReg { offset: 111 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_18_: DataReg = DataReg { offset: 112 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_19_: DataReg = DataReg { offset: 113 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_20_: DataReg = DataReg { offset: 114 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_21_: DataReg = DataReg { offset: 115 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_22_: DataReg = DataReg { offset: 116 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_23_: DataReg = DataReg { offset: 117 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_24_: DataReg = DataReg { offset: 118 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_25_: DataReg = DataReg { offset: 119 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_26_: DataReg = DataReg { offset: 120 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_27_: DataReg = DataReg { offset: 121 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_28_: DataReg = DataReg { offset: 122 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_29_: DataReg = DataReg { offset: 123 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_30_: DataReg = DataReg { offset: 124 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_31_: DataReg = DataReg { offset: 125 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_0_: DataReg = DataReg { offset: 60 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_1_: DataReg = DataReg { offset: 61 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_2_: DataReg = DataReg { offset: 62 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_3_: DataReg = DataReg { offset: 63 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_4_: DataReg = DataReg { offset: 64 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_5_: DataReg = DataReg { offset: 65 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_6_: DataReg = DataReg { offset: 66 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_7_: DataReg = DataReg { offset: 67 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_8_: DataReg = DataReg { offset: 68 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_9_: DataReg = DataReg { offset: 69 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_10_: DataReg = DataReg { offset: 70 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_11_: DataReg = DataReg { offset: 71 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_12_: DataReg = DataReg { offset: 72 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_13_: DataReg = DataReg { offset: 73 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_14_: DataReg = DataReg { offset: 74 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_15_: DataReg = DataReg { offset: 75 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_16_: DataReg = DataReg { offset: 76 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_17_: DataReg = DataReg { offset: 77 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_18_: DataReg = DataReg { offset: 78 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_19_: DataReg = DataReg { offset: 79 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_20_: DataReg = DataReg { offset: 80 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_21_: DataReg = DataReg { offset: 81 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_22_: DataReg = DataReg { offset: 82 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_23_: DataReg = DataReg { offset: 83 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_24_: DataReg = DataReg { offset: 84 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_25_: DataReg = DataReg { offset: 85 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_26_: DataReg = DataReg { offset: 86 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_27_: DataReg = DataReg { offset: 87 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_28_: DataReg = DataReg { offset: 88 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_29_: DataReg = DataReg { offset: 89 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_30_: DataReg = DataReg { offset: 90 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_31_: DataReg = DataReg { offset: 91 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_RAW_0_: DataReg = DataReg { offset: 126 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_RAW_1_: DataReg = DataReg { offset: 127 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_RAW_0_: DataReg = DataReg { offset: 58 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_RAW_1_: DataReg = DataReg { offset: 59 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_0_: DataReg = DataReg { offset: 26 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_1_: DataReg = DataReg { offset: 27 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_2_: DataReg = DataReg { offset: 28 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_3_: DataReg = DataReg { offset: 29 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_4_: DataReg = DataReg { offset: 30 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_5_: DataReg = DataReg { offset: 31 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_6_: DataReg = DataReg { offset: 32 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_7_: DataReg = DataReg { offset: 33 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_8_: DataReg = DataReg { offset: 34 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_9_: DataReg = DataReg { offset: 35 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_10_: DataReg = DataReg { offset: 36 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_11_: DataReg = DataReg { offset: 37 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_12_: DataReg = DataReg { offset: 38 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_13_: DataReg = DataReg { offset: 39 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_14_: DataReg = DataReg { offset: 40 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_15_: DataReg = DataReg { offset: 41 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_16_: DataReg = DataReg { offset: 42 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_17_: DataReg = DataReg { offset: 43 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_18_: DataReg = DataReg { offset: 44 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_19_: DataReg = DataReg { offset: 45 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_20_: DataReg = DataReg { offset: 46 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_21_: DataReg = DataReg { offset: 47 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_22_: DataReg = DataReg { offset: 48 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_23_: DataReg = DataReg { offset: 49 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_24_: DataReg = DataReg { offset: 50 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_25_: DataReg = DataReg { offset: 51 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_26_: DataReg = DataReg { offset: 52 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_27_: DataReg = DataReg { offset: 53 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_28_: DataReg = DataReg { offset: 54 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_29_: DataReg = DataReg { offset: 55 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_30_: DataReg = DataReg { offset: 56 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_31_: DataReg = DataReg { offset: 57 };

// circuit/recursion/sha.h:51
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE: RecursionShaCycle = RecursionShaCycle {
    a_carry_hi: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_CARRY_HI,
    a_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_CARRY_LOW,
    e_carry_high: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_CARRY_HIGH,
    e_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_CARRY_LOW,
    io0: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO0,
    io1: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_IO1,
    w_carry_high: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_CARRY_HIGH,
    w_carry_low: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_CARRY_LOW,
    e_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_RAW_1_,
    ],
    w: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_31_,
    ],
    e: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_E_31_,
    ],
    w_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_W_RAW_1_,
    ],
    a_raw: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_RAW_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_RAW_1_,
    ],
    a: &[
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_0_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_1_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_2_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_3_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_4_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_5_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_6_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_7_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_8_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_9_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_10_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_11_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_12_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_13_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_14_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_15_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_16_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_17_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_18_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_19_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_20_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_21_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_22_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_23_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_24_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_25_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_26_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_27_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_28_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_29_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_30_,
        &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE_A_31_,
    ],
};

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX: RecursionShaWrap = RecursionShaWrap {
    sha_cycle: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX_SHA_CYCLE,
};

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_WOM_FINI: RecursionPoseidonInst = RecursionPoseidonInst {};

// :0
pub const LAYOUT_MUX_MACRO_OPS_MUX_WOM_INIT: RecursionPoseidonInst = RecursionPoseidonInst {};

// zirgen/circuit/recursion/macro.cpp:48
pub const LAYOUT_MUX_MACRO_OPS_MUX: Mux4 = Mux4 {
    bit_and_elem: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_AND_ELEM,
    bit_op_shorts: &LAYOUT_MUX_MACRO_OPS_MUX_BIT_OP_SHORTS,
    nop: &LAYOUT_MUX_MACRO_OPS_MUX_NOP,
    set_global: &LAYOUT_MUX_MACRO_OPS_MUX_SET_GLOBAL,
    sha_fini: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_FINI,
    sha_init: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_INIT,
    sha_load: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_LOAD,
    sha_mix: &LAYOUT_MUX_MACRO_OPS_MUX_SHA_MIX,
    wom_fini: &LAYOUT_MUX_MACRO_OPS_MUX_WOM_FINI,
    wom_init: &LAYOUT_MUX_MACRO_OPS_MUX_WOM_INIT,
};

// :0
pub const LAYOUT_MUX_MACRO_OPS: RecursionMacroOp = RecursionMacroOp {
    mux: &LAYOUT_MUX_MACRO_OPS_MUX,
};

// zirgen/circuit/recursion/wom.cpp:102
pub const LAYOUT_MUX_MICRO_OPS_WOM_BODY_PLONK_BODY: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/micro.cpp:140
pub const LAYOUT_MUX_MICRO_OPS_WOM_BODY: RecursionWomBody = RecursionWomBody {
    plonk_body: &LAYOUT_MUX_MICRO_OPS_WOM_BODY_PLONK_BODY,
};

// zirgen/circuit/recursion/micro.cpp:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_EXTRA: DataReg = DataReg { offset: 101 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_ADD: DataReg = DataReg { offset: 91 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_CONSTOP: DataReg = DataReg { offset: 90 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_EQ: DataReg = DataReg { offset: 95 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_EXTRACT: DataReg = DataReg { offset: 100 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_INV: DataReg = DataReg { offset: 94 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_MIX_RNG: DataReg = DataReg { offset: 98 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_MUL: DataReg = DataReg { offset: 93 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_READ_IOP_BODY: DataReg = DataReg { offset: 97 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_READ_IOP_HEADER: DataReg = DataReg { offset: 96 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_SELECT: DataReg = DataReg { offset: 99 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_SUB: DataReg = DataReg { offset: 92 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_DECODE: OneHot5 = OneHot5 {
    add: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_ADD,
    constop: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_CONSTOP,
    eq: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_EQ,
    extract: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_EXTRACT,
    inv: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_INV,
    mix_rng: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_MIX_RNG,
    mul: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_MUL,
    read_iop_body: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_READ_IOP_BODY,
    read_iop_header: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_READ_IOP_HEADER,
    select: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_SELECT,
    sub: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE_SUB,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM_ADDR: DataReg = DataReg { offset: 5 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM_DATA_0_: DataReg = DataReg { offset: 6 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM_DATA_1_: DataReg = DataReg { offset: 7 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM_DATA_2_: DataReg = DataReg { offset: 8 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM_DATA_3_: DataReg = DataReg { offset: 9 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM_DATA_0_,
            &LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM_DATA_1_,
            &LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM_DATA_2_,
            &LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM_DATA_3_,
        ],
    };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN0: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MICRO_OPS_OP_0_IN0_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM_ADDR: DataReg = DataReg { offset: 10 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM_DATA_0_: DataReg = DataReg { offset: 11 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM_DATA_1_: DataReg = DataReg { offset: 12 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM_DATA_2_: DataReg = DataReg { offset: 13 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM_DATA_3_: DataReg = DataReg { offset: 14 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM_DATA_0_,
            &LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM_DATA_1_,
            &LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM_DATA_2_,
            &LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM_DATA_3_,
        ],
    };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_IN1: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MICRO_OPS_OP_0_IN1_WOM,
};

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_INST_OPCODE: CodeReg = CodeReg { offset: 7 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_INST_OPERAND_0_: CodeReg = CodeReg { offset: 8 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_INST_OPERAND_1_: CodeReg = CodeReg { offset: 9 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_INST_OPERAND_2_: CodeReg = CodeReg { offset: 10 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_INST: RecursionMicroInst = RecursionMicroInst {
    opcode: &LAYOUT_MUX_MICRO_OPS_OP_0_INST_OPCODE,
    operand: &[
        &LAYOUT_MUX_MICRO_OPS_OP_0_INST_OPERAND_0_,
        &LAYOUT_MUX_MICRO_OPS_OP_0_INST_OPERAND_1_,
        &LAYOUT_MUX_MICRO_OPS_OP_0_INST_OPERAND_2_,
    ],
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM_ADDR: DataReg = DataReg { offset: 15 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM_DATA_0_: DataReg = DataReg { offset: 16 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM_DATA_1_: DataReg = DataReg { offset: 17 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM_DATA_2_: DataReg = DataReg { offset: 18 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM_DATA_3_: DataReg = DataReg { offset: 19 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM_DATA_0_,
            &LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM_DATA_1_,
            &LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM_DATA_2_,
            &LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM_DATA_3_,
        ],
    };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_0_OUT: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MICRO_OPS_OP_0_OUT_WOM,
};

// zirgen/circuit/recursion/micro.cpp:142
pub const LAYOUT_MUX_MICRO_OPS_OP_0_: RecursionMicroOp = RecursionMicroOp {
    extra: &LAYOUT_MUX_MICRO_OPS_OP_0_EXTRA,
    decode: &LAYOUT_MUX_MICRO_OPS_OP_0_DECODE,
    in0: &LAYOUT_MUX_MICRO_OPS_OP_0_IN0,
    in1: &LAYOUT_MUX_MICRO_OPS_OP_0_IN1,
    inst: &LAYOUT_MUX_MICRO_OPS_OP_0_INST,
    out: &LAYOUT_MUX_MICRO_OPS_OP_0_OUT,
};

// zirgen/circuit/recursion/micro.cpp:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_EXTRA: DataReg = DataReg { offset: 113 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_ADD: DataReg = DataReg { offset: 103 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_CONSTOP: DataReg = DataReg { offset: 102 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_EQ: DataReg = DataReg { offset: 107 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_EXTRACT: DataReg = DataReg { offset: 112 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_INV: DataReg = DataReg { offset: 106 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_MIX_RNG: DataReg = DataReg { offset: 110 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_MUL: DataReg = DataReg { offset: 105 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_READ_IOP_BODY: DataReg = DataReg { offset: 109 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_READ_IOP_HEADER: DataReg = DataReg { offset: 108 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_SELECT: DataReg = DataReg { offset: 111 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_SUB: DataReg = DataReg { offset: 104 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_DECODE: OneHot5 = OneHot5 {
    add: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_ADD,
    constop: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_CONSTOP,
    eq: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_EQ,
    extract: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_EXTRACT,
    inv: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_INV,
    mix_rng: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_MIX_RNG,
    mul: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_MUL,
    read_iop_body: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_READ_IOP_BODY,
    read_iop_header: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_READ_IOP_HEADER,
    select: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_SELECT,
    sub: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE_SUB,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM_ADDR: DataReg = DataReg { offset: 20 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM_DATA_0_: DataReg = DataReg { offset: 21 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM_DATA_1_: DataReg = DataReg { offset: 22 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM_DATA_2_: DataReg = DataReg { offset: 23 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM_DATA_3_: DataReg = DataReg { offset: 24 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM_DATA_0_,
            &LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM_DATA_1_,
            &LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM_DATA_2_,
            &LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM_DATA_3_,
        ],
    };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN0: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MICRO_OPS_OP_1_IN0_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM_ADDR: DataReg = DataReg { offset: 25 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM_DATA_0_: DataReg = DataReg { offset: 26 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM_DATA_1_: DataReg = DataReg { offset: 27 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM_DATA_2_: DataReg = DataReg { offset: 28 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM_DATA_3_: DataReg = DataReg { offset: 29 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM_DATA_0_,
            &LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM_DATA_1_,
            &LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM_DATA_2_,
            &LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM_DATA_3_,
        ],
    };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_IN1: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MICRO_OPS_OP_1_IN1_WOM,
};

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_INST_OPCODE: CodeReg = CodeReg { offset: 11 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_INST_OPERAND_0_: CodeReg = CodeReg { offset: 12 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_INST_OPERAND_1_: CodeReg = CodeReg { offset: 13 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_INST_OPERAND_2_: CodeReg = CodeReg { offset: 14 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_INST: RecursionMicroInst = RecursionMicroInst {
    opcode: &LAYOUT_MUX_MICRO_OPS_OP_1_INST_OPCODE,
    operand: &[
        &LAYOUT_MUX_MICRO_OPS_OP_1_INST_OPERAND_0_,
        &LAYOUT_MUX_MICRO_OPS_OP_1_INST_OPERAND_1_,
        &LAYOUT_MUX_MICRO_OPS_OP_1_INST_OPERAND_2_,
    ],
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM_ADDR: DataReg = DataReg { offset: 30 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM_DATA_0_: DataReg = DataReg { offset: 31 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM_DATA_1_: DataReg = DataReg { offset: 32 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM_DATA_2_: DataReg = DataReg { offset: 33 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM_DATA_3_: DataReg = DataReg { offset: 34 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM_DATA_0_,
            &LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM_DATA_1_,
            &LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM_DATA_2_,
            &LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM_DATA_3_,
        ],
    };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_1_OUT: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MICRO_OPS_OP_1_OUT_WOM,
};

// zirgen/circuit/recursion/micro.cpp:142
pub const LAYOUT_MUX_MICRO_OPS_OP_1_: RecursionMicroOp = RecursionMicroOp {
    extra: &LAYOUT_MUX_MICRO_OPS_OP_1_EXTRA,
    decode: &LAYOUT_MUX_MICRO_OPS_OP_1_DECODE,
    in0: &LAYOUT_MUX_MICRO_OPS_OP_1_IN0,
    in1: &LAYOUT_MUX_MICRO_OPS_OP_1_IN1,
    inst: &LAYOUT_MUX_MICRO_OPS_OP_1_INST,
    out: &LAYOUT_MUX_MICRO_OPS_OP_1_OUT,
};

// zirgen/circuit/recursion/micro.cpp:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_EXTRA: DataReg = DataReg { offset: 125 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_ADD: DataReg = DataReg { offset: 115 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_CONSTOP: DataReg = DataReg { offset: 114 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_EQ: DataReg = DataReg { offset: 119 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_EXTRACT: DataReg = DataReg { offset: 124 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_INV: DataReg = DataReg { offset: 118 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_MIX_RNG: DataReg = DataReg { offset: 122 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_MUL: DataReg = DataReg { offset: 117 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_READ_IOP_BODY: DataReg = DataReg { offset: 121 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_READ_IOP_HEADER: DataReg = DataReg { offset: 120 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_SELECT: DataReg = DataReg { offset: 123 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_SUB: DataReg = DataReg { offset: 116 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_DECODE: OneHot5 = OneHot5 {
    add: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_ADD,
    constop: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_CONSTOP,
    eq: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_EQ,
    extract: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_EXTRACT,
    inv: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_INV,
    mix_rng: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_MIX_RNG,
    mul: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_MUL,
    read_iop_body: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_READ_IOP_BODY,
    read_iop_header: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_READ_IOP_HEADER,
    select: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_SELECT,
    sub: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE_SUB,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM_ADDR: DataReg = DataReg { offset: 35 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM_DATA_0_: DataReg = DataReg { offset: 36 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM_DATA_1_: DataReg = DataReg { offset: 37 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM_DATA_2_: DataReg = DataReg { offset: 38 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM_DATA_3_: DataReg = DataReg { offset: 39 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM_DATA_0_,
            &LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM_DATA_1_,
            &LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM_DATA_2_,
            &LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM_DATA_3_,
        ],
    };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN0: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MICRO_OPS_OP_2_IN0_WOM,
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM_ADDR: DataReg = DataReg { offset: 40 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM_DATA_0_: DataReg = DataReg { offset: 41 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM_DATA_1_: DataReg = DataReg { offset: 42 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM_DATA_2_: DataReg = DataReg { offset: 43 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM_DATA_3_: DataReg = DataReg { offset: 44 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM_DATA_0_,
            &LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM_DATA_1_,
            &LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM_DATA_2_,
            &LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM_DATA_3_,
        ],
    };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_IN1: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MICRO_OPS_OP_2_IN1_WOM,
};

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_INST_OPCODE: CodeReg = CodeReg { offset: 15 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_INST_OPERAND_0_: CodeReg = CodeReg { offset: 16 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_INST_OPERAND_1_: CodeReg = CodeReg { offset: 17 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_INST_OPERAND_2_: CodeReg = CodeReg { offset: 18 };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_INST: RecursionMicroInst = RecursionMicroInst {
    opcode: &LAYOUT_MUX_MICRO_OPS_OP_2_INST_OPCODE,
    operand: &[
        &LAYOUT_MUX_MICRO_OPS_OP_2_INST_OPERAND_0_,
        &LAYOUT_MUX_MICRO_OPS_OP_2_INST_OPERAND_1_,
        &LAYOUT_MUX_MICRO_OPS_OP_2_INST_OPERAND_2_,
    ],
};

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM_ADDR: DataReg = DataReg { offset: 45 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM_DATA_0_: DataReg = DataReg { offset: 46 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM_DATA_1_: DataReg = DataReg { offset: 47 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM_DATA_2_: DataReg = DataReg { offset: 48 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM_DATA_3_: DataReg = DataReg { offset: 49 };

// compiler/edsl/component.h:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM: RecursionImplWomPlonkElement =
    RecursionImplWomPlonkElement {
        addr: &LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM_ADDR,
        data: &[
            &LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM_DATA_0_,
            &LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM_DATA_1_,
            &LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM_DATA_2_,
            &LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM_DATA_3_,
        ],
    };

// circuit/recursion/micro.h:12
pub const LAYOUT_MUX_MICRO_OPS_OP_2_OUT: RecursionWomReg = RecursionWomReg {
    wom: &LAYOUT_MUX_MICRO_OPS_OP_2_OUT_WOM,
};

// zirgen/circuit/recursion/micro.cpp:142
pub const LAYOUT_MUX_MICRO_OPS_OP_2_: RecursionMicroOp = RecursionMicroOp {
    extra: &LAYOUT_MUX_MICRO_OPS_OP_2_EXTRA,
    decode: &LAYOUT_MUX_MICRO_OPS_OP_2_DECODE,
    in0: &LAYOUT_MUX_MICRO_OPS_OP_2_IN0,
    in1: &LAYOUT_MUX_MICRO_OPS_OP_2_IN1,
    inst: &LAYOUT_MUX_MICRO_OPS_OP_2_INST,
    out: &LAYOUT_MUX_MICRO_OPS_OP_2_OUT,
};

// :0
pub const LAYOUT_MUX_MICRO_OPS: RecursionMicroOps = RecursionMicroOps {
    wom_body: &LAYOUT_MUX_MICRO_OPS_WOM_BODY,
    op: &[
        &LAYOUT_MUX_MICRO_OPS_OP_0_,
        &LAYOUT_MUX_MICRO_OPS_OP_1_,
        &LAYOUT_MUX_MICRO_OPS_OP_2_,
    ],
};

// :0
pub const LAYOUT_MUX_POSEIDON_FULL: RecursionPoseidonInst = RecursionPoseidonInst {};

// zirgen/circuit/recursion/wom.cpp:102
pub const LAYOUT_MUX_POSEIDON_LOAD_WOM_BODY_PLONK_BODY: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/poseidon.cpp:13
pub const LAYOUT_MUX_POSEIDON_LOAD_WOM_BODY: RecursionWomBody = RecursionWomBody {
    plonk_body: &LAYOUT_MUX_POSEIDON_LOAD_WOM_BODY_PLONK_BODY,
};

// :0
pub const LAYOUT_MUX_POSEIDON_LOAD: RecursionPoseidonLoad = RecursionPoseidonLoad {
    wom_body: &LAYOUT_MUX_POSEIDON_LOAD_WOM_BODY,
};

// :0
pub const LAYOUT_MUX_POSEIDON_PARTIAL: RecursionPoseidonInst = RecursionPoseidonInst {};

// zirgen/circuit/recursion/wom.cpp:102
pub const LAYOUT_MUX_POSEIDON_STORE_WOM_BODY_PLONK_BODY: RecursionPoseidonInst =
    RecursionPoseidonInst {};

// zirgen/circuit/recursion/poseidon.cpp:152
pub const LAYOUT_MUX_POSEIDON_STORE_WOM_BODY: RecursionWomBody = RecursionWomBody {
    plonk_body: &LAYOUT_MUX_POSEIDON_STORE_WOM_BODY_PLONK_BODY,
};

// :0
pub const LAYOUT_MUX_POSEIDON_STORE: RecursionPoseidonLoad = RecursionPoseidonLoad {
    wom_body: &LAYOUT_MUX_POSEIDON_STORE_WOM_BODY,
};

// zirgen/circuit/recursion/top.cpp:10
pub const LAYOUT_MUX: Mux6 = Mux6 {
    macro_ops: &LAYOUT_MUX_MACRO_OPS,
    micro_ops: &LAYOUT_MUX_MICRO_OPS,
    poseidon_full: &LAYOUT_MUX_POSEIDON_FULL,
    poseidon_load: &LAYOUT_MUX_POSEIDON_LOAD,
    poseidon_partial: &LAYOUT_MUX_POSEIDON_PARTIAL,
    poseidon_store: &LAYOUT_MUX_POSEIDON_STORE,
};

// zirgen/circuit/recursion/recursion.cpp:34
pub const LAYOUT: RecursionTop = RecursionTop {
    code: &LAYOUT_CODE,
    mux: &LAYOUT_MUX,
};
