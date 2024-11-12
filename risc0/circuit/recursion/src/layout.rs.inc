pub struct RecursionCheckedBytesInstLayout {
    pub eval_point: &'static Reg,
    pub keep_coeffs: &'static Reg,
    pub keep_upper_state: &'static Reg,
    pub prep_full: &'static Reg,
}
impl risc0_zkp::layout::Component for RecursionCheckedBytesInstLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionCheckedBytesInstLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("eval_point", self.eval_point)?;
        v.visit_component("keep_coeffs", self.keep_coeffs)?;
        v.visit_component("keep_upper_state", self.keep_upper_state)?;
        v.visit_component("prep_full", self.prep_full)?;
        Ok(())
    }
}
pub struct OneHotLayout {
    pub bit_and_elem: &'static Reg,
    pub bit_op_shorts: &'static Reg,
    pub nop: &'static Reg,
    pub set_global: &'static Reg,
    pub sha_fini: &'static Reg,
    pub sha_init: &'static Reg,
    pub sha_load: &'static Reg,
    pub sha_mix: &'static Reg,
    pub wom_fini: &'static Reg,
    pub wom_init: &'static Reg,
}
impl risc0_zkp::layout::Component for OneHotLayout {
    fn ty_name(&self) -> &'static str {
        "OneHotLayout"
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
pub type Reg3LayoutArray = [&'static Reg; 3];
pub struct RecursionMacroInstLayout {
    pub opcode: &'static OneHotLayout,
    pub operand: &'static Reg3LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionMacroInstLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionMacroInstLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("opcode", self.opcode)?;
        v.visit_component("operand", self.operand)?;
        Ok(())
    }
}
pub struct RecursionMicroInstLayout {
    pub opcode: &'static Reg,
    pub operand: &'static Reg3LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionMicroInstLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionMicroInstLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("opcode", self.opcode)?;
        v.visit_component("operand", self.operand)?;
        Ok(())
    }
}
pub type RecursionMicroInstLayout3LayoutArray = [&'static RecursionMicroInstLayout; 3];
pub struct OneHot0Layout {
    pub c0: &'static Reg,
    pub c1: &'static Reg,
    pub c2: &'static Reg,
    pub c3: &'static Reg,
}
impl risc0_zkp::layout::Component for OneHot0Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot0Layout"
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
pub struct OneHot1Layout {
    pub g0: &'static Reg,
    pub g1: &'static Reg,
    pub g2: &'static Reg,
}
impl risc0_zkp::layout::Component for OneHot1Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("g0", self.g0)?;
        v.visit_component("g1", self.g1)?;
        v.visit_component("g2", self.g2)?;
        Ok(())
    }
}
pub type Reg8LayoutArray = [&'static Reg; 8];
pub struct RecursionPoseidon2MemInstLayout {
    pub do_mont: &'static Reg,
    pub keep_state: &'static Reg,
    pub keep_upper_state: &'static Reg,
    pub prep_full: &'static Reg,
    pub group: &'static OneHot1Layout,
    pub inputs: &'static Reg8LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionPoseidon2MemInstLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionPoseidon2MemInstLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("do_mont", self.do_mont)?;
        v.visit_component("keep_state", self.keep_state)?;
        v.visit_component("keep_upper_state", self.keep_upper_state)?;
        v.visit_component("prep_full", self.prep_full)?;
        v.visit_component("group", self.group)?;
        v.visit_component("inputs", self.inputs)?;
        Ok(())
    }
}
pub struct MuxLayout {
    pub checked_bytes: &'static RecursionCheckedBytesInstLayout,
    pub macro_ops: &'static RecursionMacroInstLayout,
    pub micro_ops: &'static RecursionMicroInstLayout3LayoutArray,
    pub poseidon2_full: &'static OneHot0Layout,
    pub poseidon2_load: &'static RecursionPoseidon2MemInstLayout,
    pub poseidon2_store: &'static RecursionPoseidon2MemInstLayout,
}
impl risc0_zkp::layout::Component for MuxLayout {
    fn ty_name(&self) -> &'static str {
        "MuxLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("checked_bytes", self.checked_bytes)?;
        v.visit_component("macro_ops", self.macro_ops)?;
        v.visit_component("micro_ops", self.micro_ops)?;
        v.visit_component("poseidon2_full", self.poseidon2_full)?;
        v.visit_component("poseidon2_load", self.poseidon2_load)?;
        v.visit_component("poseidon2_store", self.poseidon2_store)?;
        Ok(())
    }
}
pub struct OneHot2Layout {
    pub checked_bytes: &'static Reg,
    pub macro_ops: &'static Reg,
    pub micro_ops: &'static Reg,
    pub poseidon2_full: &'static Reg,
    pub poseidon2_load: &'static Reg,
    pub poseidon2_partial: &'static Reg,
    pub poseidon2_store: &'static Reg,
}
impl risc0_zkp::layout::Component for OneHot2Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot2Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("checked_bytes", self.checked_bytes)?;
        v.visit_component("macro_ops", self.macro_ops)?;
        v.visit_component("micro_ops", self.micro_ops)?;
        v.visit_component("poseidon2_full", self.poseidon2_full)?;
        v.visit_component("poseidon2_load", self.poseidon2_load)?;
        v.visit_component("poseidon2_partial", self.poseidon2_partial)?;
        v.visit_component("poseidon2_store", self.poseidon2_store)?;
        Ok(())
    }
}
pub struct RecursionCodeLayout {
    pub write_addr: &'static Reg,
    pub inst: &'static MuxLayout,
    pub select: &'static OneHot2Layout,
}
impl risc0_zkp::layout::Component for RecursionCodeLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionCodeLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("write_addr", self.write_addr)?;
        v.visit_component("inst", self.inst)?;
        v.visit_component("select", self.select)?;
        Ok(())
    }
}
pub struct RecursionTopLayout {
    pub code: &'static RecursionCodeLayout,
    pub mux: &'static RecursionMicroInstLayout3LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionTopLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionTopLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("code", self.code)?;
        v.visit_component("mux", self.mux)?;
        Ok(())
    }
}
pub const CODE_LAYOUT: &RecursionTopLayout = &RecursionTopLayout {
    code: &RecursionCodeLayout {
        write_addr: &Reg { offset: 0 },
        inst: &MuxLayout {
            checked_bytes: &RecursionCheckedBytesInstLayout {
                eval_point: &Reg { offset: 8 },
                keep_coeffs: &Reg { offset: 9 },
                keep_upper_state: &Reg { offset: 10 },
                prep_full: &Reg { offset: 11 },
            },
            macro_ops: &RecursionMacroInstLayout {
                opcode: &OneHotLayout {
                    bit_and_elem: &Reg { offset: 11 },
                    bit_op_shorts: &Reg { offset: 12 },
                    nop: &Reg { offset: 8 },
                    set_global: &Reg { offset: 17 },
                    sha_fini: &Reg { offset: 14 },
                    sha_init: &Reg { offset: 13 },
                    sha_load: &Reg { offset: 15 },
                    sha_mix: &Reg { offset: 16 },
                    wom_fini: &Reg { offset: 10 },
                    wom_init: &Reg { offset: 9 },
                },
                operand: &[
                    &Reg { offset: 18 },
                    &Reg { offset: 19 },
                    &Reg { offset: 20 },
                ],
            },
            micro_ops: &[
                &RecursionMicroInstLayout {
                    opcode: &Reg { offset: 8 },
                    operand: &[&Reg { offset: 9 }, &Reg { offset: 10 }, &Reg { offset: 11 }],
                },
                &RecursionMicroInstLayout {
                    opcode: &Reg { offset: 12 },
                    operand: &[
                        &Reg { offset: 13 },
                        &Reg { offset: 14 },
                        &Reg { offset: 15 },
                    ],
                },
                &RecursionMicroInstLayout {
                    opcode: &Reg { offset: 16 },
                    operand: &[
                        &Reg { offset: 17 },
                        &Reg { offset: 18 },
                        &Reg { offset: 19 },
                    ],
                },
            ],
            poseidon2_full: &OneHot0Layout {
                c0: &Reg { offset: 8 },
                c1: &Reg { offset: 9 },
                c2: &Reg { offset: 10 },
                c3: &Reg { offset: 11 },
            },
            poseidon2_load: &RecursionPoseidon2MemInstLayout {
                do_mont: &Reg { offset: 8 },
                keep_state: &Reg { offset: 9 },
                keep_upper_state: &Reg { offset: 10 },
                prep_full: &Reg { offset: 11 },
                group: &OneHot1Layout {
                    g0: &Reg { offset: 12 },
                    g1: &Reg { offset: 13 },
                    g2: &Reg { offset: 14 },
                },
                inputs: &[
                    &Reg { offset: 15 },
                    &Reg { offset: 16 },
                    &Reg { offset: 17 },
                    &Reg { offset: 18 },
                    &Reg { offset: 19 },
                    &Reg { offset: 20 },
                    &Reg { offset: 21 },
                    &Reg { offset: 22 },
                ],
            },
            poseidon2_store: &RecursionPoseidon2MemInstLayout {
                do_mont: &Reg { offset: 8 },
                keep_state: &Reg { offset: 9 },
                keep_upper_state: &Reg { offset: 10 },
                prep_full: &Reg { offset: 11 },
                group: &OneHot1Layout {
                    g0: &Reg { offset: 12 },
                    g1: &Reg { offset: 13 },
                    g2: &Reg { offset: 14 },
                },
                inputs: &[
                    &Reg { offset: 15 },
                    &Reg { offset: 16 },
                    &Reg { offset: 17 },
                    &Reg { offset: 18 },
                    &Reg { offset: 19 },
                    &Reg { offset: 20 },
                    &Reg { offset: 21 },
                    &Reg { offset: 22 },
                ],
            },
        },
        select: &OneHot2Layout {
            checked_bytes: &Reg { offset: 7 },
            macro_ops: &Reg { offset: 2 },
            micro_ops: &Reg { offset: 1 },
            poseidon2_full: &Reg { offset: 4 },
            poseidon2_load: &Reg { offset: 3 },
            poseidon2_partial: &Reg { offset: 5 },
            poseidon2_store: &Reg { offset: 6 },
        },
    },
    mux: &[
        &RecursionMicroInstLayout {
            opcode: &Reg { offset: 8 },
            operand: &[&Reg { offset: 9 }, &Reg { offset: 10 }, &Reg { offset: 11 }],
        },
        &RecursionMicroInstLayout {
            opcode: &Reg { offset: 12 },
            operand: &[
                &Reg { offset: 13 },
                &Reg { offset: 14 },
                &Reg { offset: 15 },
            ],
        },
        &RecursionMicroInstLayout {
            opcode: &Reg { offset: 16 },
            operand: &[
                &Reg { offset: 17 },
                &Reg { offset: 18 },
                &Reg { offset: 19 },
            ],
        },
    ],
};
pub type Reg4LayoutArray = [&'static Reg; 4];
pub struct RecursionImplWomPlonkElementLayout {
    pub addr: &'static Reg,
    pub data: &'static Reg4LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionImplWomPlonkElementLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionImplWomPlonkElementLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("addr", self.addr)?;
        v.visit_component("data", self.data)?;
        Ok(())
    }
}
pub type Reg31LayoutArray = [&'static Reg; 31];
pub struct RecursionBitAndElemLayout {
    pub in_a: &'static RecursionImplWomPlonkElementLayout,
    pub in_b: &'static RecursionImplWomPlonkElementLayout,
    pub out: &'static RecursionImplWomPlonkElementLayout,
    pub bits_a: &'static Reg31LayoutArray,
    pub bits_b: &'static Reg31LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionBitAndElemLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionBitAndElemLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("in_a", self.in_a)?;
        v.visit_component("in_b", self.in_b)?;
        v.visit_component("out", self.out)?;
        v.visit_component("bits_a", self.bits_a)?;
        v.visit_component("bits_b", self.bits_b)?;
        Ok(())
    }
}
pub type Reg32LayoutArray = [&'static Reg; 32];
pub struct RecursionBitOpShortsLayout {
    pub in_a: &'static RecursionImplWomPlonkElementLayout,
    pub in_b: &'static RecursionImplWomPlonkElementLayout,
    pub out: &'static RecursionImplWomPlonkElementLayout,
    pub bits_a: &'static Reg32LayoutArray,
    pub bits_b: &'static Reg32LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionBitOpShortsLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionBitOpShortsLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("in_a", self.in_a)?;
        v.visit_component("in_b", self.in_b)?;
        v.visit_component("out", self.out)?;
        v.visit_component("bits_a", self.bits_a)?;
        v.visit_component("bits_b", self.bits_b)?;
        Ok(())
    }
}
pub type RecursionImplWomPlonkElementLayout4LayoutArray =
    [&'static RecursionImplWomPlonkElementLayout; 4];
pub struct RecursionSetGlobalLayout {
    pub select: &'static Reg4LayoutArray,
    pub regs: &'static RecursionImplWomPlonkElementLayout4LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionSetGlobalLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionSetGlobalLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("select", self.select)?;
        v.visit_component("regs", self.regs)?;
        Ok(())
    }
}
pub type Reg2LayoutArray = [&'static Reg; 2];
pub struct RecursionShaCycleLayout {
    pub a_carry_hi: &'static Reg,
    pub a_carry_low: &'static Reg,
    pub e_carry_high: &'static Reg,
    pub e_carry_low: &'static Reg,
    pub w_carry_high: &'static Reg,
    pub w_carry_low: &'static Reg,
    pub io0: &'static RecursionImplWomPlonkElementLayout,
    pub io1: &'static RecursionImplWomPlonkElementLayout,
    pub a: &'static Reg32LayoutArray,
    pub a_raw: &'static Reg2LayoutArray,
    pub e: &'static Reg32LayoutArray,
    pub e_raw: &'static Reg2LayoutArray,
    pub w: &'static Reg32LayoutArray,
    pub w_raw: &'static Reg2LayoutArray,
}
impl risc0_zkp::layout::Component for RecursionShaCycleLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionShaCycleLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("a_carry_hi", self.a_carry_hi)?;
        v.visit_component("a_carry_low", self.a_carry_low)?;
        v.visit_component("e_carry_high", self.e_carry_high)?;
        v.visit_component("e_carry_low", self.e_carry_low)?;
        v.visit_component("w_carry_high", self.w_carry_high)?;
        v.visit_component("w_carry_low", self.w_carry_low)?;
        v.visit_component("io0", self.io0)?;
        v.visit_component("io1", self.io1)?;
        v.visit_component("a", self.a)?;
        v.visit_component("a_raw", self.a_raw)?;
        v.visit_component("e", self.e)?;
        v.visit_component("e_raw", self.e_raw)?;
        v.visit_component("w", self.w)?;
        v.visit_component("w_raw", self.w_raw)?;
        Ok(())
    }
}
pub struct Mux3Layout {
    pub bit_and_elem: &'static RecursionBitAndElemLayout,
    pub bit_op_shorts: &'static RecursionBitOpShortsLayout,
    pub set_global: &'static RecursionSetGlobalLayout,
    pub sha_fini: &'static RecursionShaCycleLayout,
    pub sha_init: &'static RecursionShaCycleLayout,
    pub sha_load: &'static RecursionShaCycleLayout,
    pub sha_mix: &'static RecursionShaCycleLayout,
}
impl risc0_zkp::layout::Component for Mux3Layout {
    fn ty_name(&self) -> &'static str {
        "Mux3Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("bit_and_elem", self.bit_and_elem)?;
        v.visit_component("bit_op_shorts", self.bit_op_shorts)?;
        v.visit_component("set_global", self.set_global)?;
        v.visit_component("sha_fini", self.sha_fini)?;
        v.visit_component("sha_init", self.sha_init)?;
        v.visit_component("sha_load", self.sha_load)?;
        v.visit_component("sha_mix", self.sha_mix)?;
        Ok(())
    }
}
pub struct OneHot4Layout {
    pub add: &'static Reg,
    pub constop: &'static Reg,
    pub eq: &'static Reg,
    pub extract: &'static Reg,
    pub inv: &'static Reg,
    pub mix_rng: &'static Reg,
    pub mul: &'static Reg,
    pub read_iop_body: &'static Reg,
    pub read_iop_header: &'static Reg,
    pub select: &'static Reg,
    pub sub: &'static Reg,
}
impl risc0_zkp::layout::Component for OneHot4Layout {
    fn ty_name(&self) -> &'static str {
        "OneHot4Layout"
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
pub struct RecursionMicroOpLayout {
    pub extra: &'static Reg,
    pub decode: &'static OneHot4Layout,
    pub in0: &'static RecursionImplWomPlonkElementLayout,
    pub in1: &'static RecursionImplWomPlonkElementLayout,
    pub out: &'static RecursionImplWomPlonkElementLayout,
}
impl risc0_zkp::layout::Component for RecursionMicroOpLayout {
    fn ty_name(&self) -> &'static str {
        "RecursionMicroOpLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("extra", self.extra)?;
        v.visit_component("decode", self.decode)?;
        v.visit_component("in0", self.in0)?;
        v.visit_component("in1", self.in1)?;
        v.visit_component("out", self.out)?;
        Ok(())
    }
}
pub type RecursionMicroOpLayout3LayoutArray = [&'static RecursionMicroOpLayout; 3];
pub struct Mux5Layout {
    pub checked_bytes: &'static RecursionImplWomPlonkElementLayout,
    pub macro_ops: &'static Mux3Layout,
    pub micro_ops: &'static RecursionMicroOpLayout3LayoutArray,
}
impl risc0_zkp::layout::Component for Mux5Layout {
    fn ty_name(&self) -> &'static str {
        "Mux5Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("checked_bytes", self.checked_bytes)?;
        v.visit_component("macro_ops", self.macro_ops)?;
        v.visit_component("micro_ops", self.micro_ops)?;
        Ok(())
    }
}
pub const DATA_LAYOUT: &Mux5Layout = &Mux5Layout {
    checked_bytes: &RecursionImplWomPlonkElementLayout {
        addr: &Reg { offset: 5 },
        data: &[
            &Reg { offset: 6 },
            &Reg { offset: 7 },
            &Reg { offset: 8 },
            &Reg { offset: 9 },
        ],
    },
    macro_ops: &Mux3Layout {
        bit_and_elem: &RecursionBitAndElemLayout {
            in_a: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 11 },
                data: &[
                    &Reg { offset: 12 },
                    &Reg { offset: 13 },
                    &Reg { offset: 14 },
                    &Reg { offset: 15 },
                ],
            },
            in_b: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 16 },
                data: &[
                    &Reg { offset: 17 },
                    &Reg { offset: 18 },
                    &Reg { offset: 19 },
                    &Reg { offset: 20 },
                ],
            },
            out: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 21 },
                data: &[
                    &Reg { offset: 22 },
                    &Reg { offset: 23 },
                    &Reg { offset: 24 },
                    &Reg { offset: 25 },
                ],
            },
            bits_a: &[
                &Reg { offset: 36 },
                &Reg { offset: 38 },
                &Reg { offset: 40 },
                &Reg { offset: 42 },
                &Reg { offset: 44 },
                &Reg { offset: 46 },
                &Reg { offset: 48 },
                &Reg { offset: 50 },
                &Reg { offset: 52 },
                &Reg { offset: 54 },
                &Reg { offset: 56 },
                &Reg { offset: 58 },
                &Reg { offset: 60 },
                &Reg { offset: 62 },
                &Reg { offset: 64 },
                &Reg { offset: 66 },
                &Reg { offset: 68 },
                &Reg { offset: 70 },
                &Reg { offset: 72 },
                &Reg { offset: 74 },
                &Reg { offset: 76 },
                &Reg { offset: 78 },
                &Reg { offset: 80 },
                &Reg { offset: 82 },
                &Reg { offset: 84 },
                &Reg { offset: 86 },
                &Reg { offset: 88 },
                &Reg { offset: 90 },
                &Reg { offset: 92 },
                &Reg { offset: 94 },
                &Reg { offset: 96 },
            ],
            bits_b: &[
                &Reg { offset: 37 },
                &Reg { offset: 39 },
                &Reg { offset: 41 },
                &Reg { offset: 43 },
                &Reg { offset: 45 },
                &Reg { offset: 47 },
                &Reg { offset: 49 },
                &Reg { offset: 51 },
                &Reg { offset: 53 },
                &Reg { offset: 55 },
                &Reg { offset: 57 },
                &Reg { offset: 59 },
                &Reg { offset: 61 },
                &Reg { offset: 63 },
                &Reg { offset: 65 },
                &Reg { offset: 67 },
                &Reg { offset: 69 },
                &Reg { offset: 71 },
                &Reg { offset: 73 },
                &Reg { offset: 75 },
                &Reg { offset: 77 },
                &Reg { offset: 79 },
                &Reg { offset: 81 },
                &Reg { offset: 83 },
                &Reg { offset: 85 },
                &Reg { offset: 87 },
                &Reg { offset: 89 },
                &Reg { offset: 91 },
                &Reg { offset: 93 },
                &Reg { offset: 95 },
                &Reg { offset: 97 },
            ],
        },
        bit_op_shorts: &RecursionBitOpShortsLayout {
            in_a: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 11 },
                data: &[
                    &Reg { offset: 12 },
                    &Reg { offset: 13 },
                    &Reg { offset: 14 },
                    &Reg { offset: 15 },
                ],
            },
            in_b: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 16 },
                data: &[
                    &Reg { offset: 17 },
                    &Reg { offset: 18 },
                    &Reg { offset: 19 },
                    &Reg { offset: 20 },
                ],
            },
            out: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 21 },
                data: &[
                    &Reg { offset: 22 },
                    &Reg { offset: 23 },
                    &Reg { offset: 24 },
                    &Reg { offset: 25 },
                ],
            },
            bits_a: &[
                &Reg { offset: 36 },
                &Reg { offset: 37 },
                &Reg { offset: 38 },
                &Reg { offset: 39 },
                &Reg { offset: 40 },
                &Reg { offset: 41 },
                &Reg { offset: 42 },
                &Reg { offset: 43 },
                &Reg { offset: 44 },
                &Reg { offset: 45 },
                &Reg { offset: 46 },
                &Reg { offset: 47 },
                &Reg { offset: 48 },
                &Reg { offset: 49 },
                &Reg { offset: 50 },
                &Reg { offset: 51 },
                &Reg { offset: 52 },
                &Reg { offset: 53 },
                &Reg { offset: 54 },
                &Reg { offset: 55 },
                &Reg { offset: 56 },
                &Reg { offset: 57 },
                &Reg { offset: 58 },
                &Reg { offset: 59 },
                &Reg { offset: 60 },
                &Reg { offset: 61 },
                &Reg { offset: 62 },
                &Reg { offset: 63 },
                &Reg { offset: 64 },
                &Reg { offset: 65 },
                &Reg { offset: 66 },
                &Reg { offset: 67 },
            ],
            bits_b: &[
                &Reg { offset: 68 },
                &Reg { offset: 69 },
                &Reg { offset: 70 },
                &Reg { offset: 71 },
                &Reg { offset: 72 },
                &Reg { offset: 73 },
                &Reg { offset: 74 },
                &Reg { offset: 75 },
                &Reg { offset: 76 },
                &Reg { offset: 77 },
                &Reg { offset: 78 },
                &Reg { offset: 79 },
                &Reg { offset: 80 },
                &Reg { offset: 81 },
                &Reg { offset: 82 },
                &Reg { offset: 83 },
                &Reg { offset: 84 },
                &Reg { offset: 85 },
                &Reg { offset: 86 },
                &Reg { offset: 87 },
                &Reg { offset: 88 },
                &Reg { offset: 89 },
                &Reg { offset: 90 },
                &Reg { offset: 91 },
                &Reg { offset: 92 },
                &Reg { offset: 93 },
                &Reg { offset: 94 },
                &Reg { offset: 95 },
                &Reg { offset: 96 },
                &Reg { offset: 97 },
                &Reg { offset: 98 },
                &Reg { offset: 99 },
            ],
        },
        set_global: &RecursionSetGlobalLayout {
            select: &[
                &Reg { offset: 11 },
                &Reg { offset: 12 },
                &Reg { offset: 13 },
                &Reg { offset: 14 },
            ],
            regs: &[
                &RecursionImplWomPlonkElementLayout {
                    addr: &Reg { offset: 15 },
                    data: &[
                        &Reg { offset: 16 },
                        &Reg { offset: 17 },
                        &Reg { offset: 18 },
                        &Reg { offset: 19 },
                    ],
                },
                &RecursionImplWomPlonkElementLayout {
                    addr: &Reg { offset: 20 },
                    data: &[
                        &Reg { offset: 21 },
                        &Reg { offset: 22 },
                        &Reg { offset: 23 },
                        &Reg { offset: 24 },
                    ],
                },
                &RecursionImplWomPlonkElementLayout {
                    addr: &Reg { offset: 25 },
                    data: &[
                        &Reg { offset: 26 },
                        &Reg { offset: 27 },
                        &Reg { offset: 28 },
                        &Reg { offset: 29 },
                    ],
                },
                &RecursionImplWomPlonkElementLayout {
                    addr: &Reg { offset: 30 },
                    data: &[
                        &Reg { offset: 31 },
                        &Reg { offset: 32 },
                        &Reg { offset: 33 },
                        &Reg { offset: 34 },
                    ],
                },
            ],
        },
        sha_fini: &RecursionShaCycleLayout {
            a_carry_hi: &Reg { offset: 6 },
            a_carry_low: &Reg { offset: 5 },
            e_carry_high: &Reg { offset: 8 },
            e_carry_low: &Reg { offset: 7 },
            w_carry_high: &Reg { offset: 10 },
            w_carry_low: &Reg { offset: 9 },
            io0: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 11 },
                data: &[
                    &Reg { offset: 12 },
                    &Reg { offset: 13 },
                    &Reg { offset: 14 },
                    &Reg { offset: 15 },
                ],
            },
            io1: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 16 },
                data: &[
                    &Reg { offset: 17 },
                    &Reg { offset: 18 },
                    &Reg { offset: 19 },
                    &Reg { offset: 20 },
                ],
            },
            a: &[
                &Reg { offset: 26 },
                &Reg { offset: 27 },
                &Reg { offset: 28 },
                &Reg { offset: 29 },
                &Reg { offset: 30 },
                &Reg { offset: 31 },
                &Reg { offset: 32 },
                &Reg { offset: 33 },
                &Reg { offset: 34 },
                &Reg { offset: 35 },
                &Reg { offset: 36 },
                &Reg { offset: 37 },
                &Reg { offset: 38 },
                &Reg { offset: 39 },
                &Reg { offset: 40 },
                &Reg { offset: 41 },
                &Reg { offset: 42 },
                &Reg { offset: 43 },
                &Reg { offset: 44 },
                &Reg { offset: 45 },
                &Reg { offset: 46 },
                &Reg { offset: 47 },
                &Reg { offset: 48 },
                &Reg { offset: 49 },
                &Reg { offset: 50 },
                &Reg { offset: 51 },
                &Reg { offset: 52 },
                &Reg { offset: 53 },
                &Reg { offset: 54 },
                &Reg { offset: 55 },
                &Reg { offset: 56 },
                &Reg { offset: 57 },
            ],
            a_raw: &[&Reg { offset: 58 }, &Reg { offset: 59 }],
            e: &[
                &Reg { offset: 60 },
                &Reg { offset: 61 },
                &Reg { offset: 62 },
                &Reg { offset: 63 },
                &Reg { offset: 64 },
                &Reg { offset: 65 },
                &Reg { offset: 66 },
                &Reg { offset: 67 },
                &Reg { offset: 68 },
                &Reg { offset: 69 },
                &Reg { offset: 70 },
                &Reg { offset: 71 },
                &Reg { offset: 72 },
                &Reg { offset: 73 },
                &Reg { offset: 74 },
                &Reg { offset: 75 },
                &Reg { offset: 76 },
                &Reg { offset: 77 },
                &Reg { offset: 78 },
                &Reg { offset: 79 },
                &Reg { offset: 80 },
                &Reg { offset: 81 },
                &Reg { offset: 82 },
                &Reg { offset: 83 },
                &Reg { offset: 84 },
                &Reg { offset: 85 },
                &Reg { offset: 86 },
                &Reg { offset: 87 },
                &Reg { offset: 88 },
                &Reg { offset: 89 },
                &Reg { offset: 90 },
                &Reg { offset: 91 },
            ],
            e_raw: &[&Reg { offset: 92 }, &Reg { offset: 93 }],
            w: &[
                &Reg { offset: 94 },
                &Reg { offset: 95 },
                &Reg { offset: 96 },
                &Reg { offset: 97 },
                &Reg { offset: 98 },
                &Reg { offset: 99 },
                &Reg { offset: 100 },
                &Reg { offset: 101 },
                &Reg { offset: 102 },
                &Reg { offset: 103 },
                &Reg { offset: 104 },
                &Reg { offset: 105 },
                &Reg { offset: 106 },
                &Reg { offset: 107 },
                &Reg { offset: 108 },
                &Reg { offset: 109 },
                &Reg { offset: 110 },
                &Reg { offset: 111 },
                &Reg { offset: 112 },
                &Reg { offset: 113 },
                &Reg { offset: 114 },
                &Reg { offset: 115 },
                &Reg { offset: 116 },
                &Reg { offset: 117 },
                &Reg { offset: 118 },
                &Reg { offset: 119 },
                &Reg { offset: 120 },
                &Reg { offset: 121 },
                &Reg { offset: 122 },
                &Reg { offset: 123 },
                &Reg { offset: 124 },
                &Reg { offset: 125 },
            ],
            w_raw: &[&Reg { offset: 126 }, &Reg { offset: 127 }],
        },
        sha_init: &RecursionShaCycleLayout {
            a_carry_hi: &Reg { offset: 6 },
            a_carry_low: &Reg { offset: 5 },
            e_carry_high: &Reg { offset: 8 },
            e_carry_low: &Reg { offset: 7 },
            w_carry_high: &Reg { offset: 10 },
            w_carry_low: &Reg { offset: 9 },
            io0: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 11 },
                data: &[
                    &Reg { offset: 12 },
                    &Reg { offset: 13 },
                    &Reg { offset: 14 },
                    &Reg { offset: 15 },
                ],
            },
            io1: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 16 },
                data: &[
                    &Reg { offset: 17 },
                    &Reg { offset: 18 },
                    &Reg { offset: 19 },
                    &Reg { offset: 20 },
                ],
            },
            a: &[
                &Reg { offset: 26 },
                &Reg { offset: 27 },
                &Reg { offset: 28 },
                &Reg { offset: 29 },
                &Reg { offset: 30 },
                &Reg { offset: 31 },
                &Reg { offset: 32 },
                &Reg { offset: 33 },
                &Reg { offset: 34 },
                &Reg { offset: 35 },
                &Reg { offset: 36 },
                &Reg { offset: 37 },
                &Reg { offset: 38 },
                &Reg { offset: 39 },
                &Reg { offset: 40 },
                &Reg { offset: 41 },
                &Reg { offset: 42 },
                &Reg { offset: 43 },
                &Reg { offset: 44 },
                &Reg { offset: 45 },
                &Reg { offset: 46 },
                &Reg { offset: 47 },
                &Reg { offset: 48 },
                &Reg { offset: 49 },
                &Reg { offset: 50 },
                &Reg { offset: 51 },
                &Reg { offset: 52 },
                &Reg { offset: 53 },
                &Reg { offset: 54 },
                &Reg { offset: 55 },
                &Reg { offset: 56 },
                &Reg { offset: 57 },
            ],
            a_raw: &[&Reg { offset: 58 }, &Reg { offset: 59 }],
            e: &[
                &Reg { offset: 60 },
                &Reg { offset: 61 },
                &Reg { offset: 62 },
                &Reg { offset: 63 },
                &Reg { offset: 64 },
                &Reg { offset: 65 },
                &Reg { offset: 66 },
                &Reg { offset: 67 },
                &Reg { offset: 68 },
                &Reg { offset: 69 },
                &Reg { offset: 70 },
                &Reg { offset: 71 },
                &Reg { offset: 72 },
                &Reg { offset: 73 },
                &Reg { offset: 74 },
                &Reg { offset: 75 },
                &Reg { offset: 76 },
                &Reg { offset: 77 },
                &Reg { offset: 78 },
                &Reg { offset: 79 },
                &Reg { offset: 80 },
                &Reg { offset: 81 },
                &Reg { offset: 82 },
                &Reg { offset: 83 },
                &Reg { offset: 84 },
                &Reg { offset: 85 },
                &Reg { offset: 86 },
                &Reg { offset: 87 },
                &Reg { offset: 88 },
                &Reg { offset: 89 },
                &Reg { offset: 90 },
                &Reg { offset: 91 },
            ],
            e_raw: &[&Reg { offset: 92 }, &Reg { offset: 93 }],
            w: &[
                &Reg { offset: 94 },
                &Reg { offset: 95 },
                &Reg { offset: 96 },
                &Reg { offset: 97 },
                &Reg { offset: 98 },
                &Reg { offset: 99 },
                &Reg { offset: 100 },
                &Reg { offset: 101 },
                &Reg { offset: 102 },
                &Reg { offset: 103 },
                &Reg { offset: 104 },
                &Reg { offset: 105 },
                &Reg { offset: 106 },
                &Reg { offset: 107 },
                &Reg { offset: 108 },
                &Reg { offset: 109 },
                &Reg { offset: 110 },
                &Reg { offset: 111 },
                &Reg { offset: 112 },
                &Reg { offset: 113 },
                &Reg { offset: 114 },
                &Reg { offset: 115 },
                &Reg { offset: 116 },
                &Reg { offset: 117 },
                &Reg { offset: 118 },
                &Reg { offset: 119 },
                &Reg { offset: 120 },
                &Reg { offset: 121 },
                &Reg { offset: 122 },
                &Reg { offset: 123 },
                &Reg { offset: 124 },
                &Reg { offset: 125 },
            ],
            w_raw: &[&Reg { offset: 126 }, &Reg { offset: 127 }],
        },
        sha_load: &RecursionShaCycleLayout {
            a_carry_hi: &Reg { offset: 6 },
            a_carry_low: &Reg { offset: 5 },
            e_carry_high: &Reg { offset: 8 },
            e_carry_low: &Reg { offset: 7 },
            w_carry_high: &Reg { offset: 10 },
            w_carry_low: &Reg { offset: 9 },
            io0: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 11 },
                data: &[
                    &Reg { offset: 12 },
                    &Reg { offset: 13 },
                    &Reg { offset: 14 },
                    &Reg { offset: 15 },
                ],
            },
            io1: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 16 },
                data: &[
                    &Reg { offset: 17 },
                    &Reg { offset: 18 },
                    &Reg { offset: 19 },
                    &Reg { offset: 20 },
                ],
            },
            a: &[
                &Reg { offset: 26 },
                &Reg { offset: 27 },
                &Reg { offset: 28 },
                &Reg { offset: 29 },
                &Reg { offset: 30 },
                &Reg { offset: 31 },
                &Reg { offset: 32 },
                &Reg { offset: 33 },
                &Reg { offset: 34 },
                &Reg { offset: 35 },
                &Reg { offset: 36 },
                &Reg { offset: 37 },
                &Reg { offset: 38 },
                &Reg { offset: 39 },
                &Reg { offset: 40 },
                &Reg { offset: 41 },
                &Reg { offset: 42 },
                &Reg { offset: 43 },
                &Reg { offset: 44 },
                &Reg { offset: 45 },
                &Reg { offset: 46 },
                &Reg { offset: 47 },
                &Reg { offset: 48 },
                &Reg { offset: 49 },
                &Reg { offset: 50 },
                &Reg { offset: 51 },
                &Reg { offset: 52 },
                &Reg { offset: 53 },
                &Reg { offset: 54 },
                &Reg { offset: 55 },
                &Reg { offset: 56 },
                &Reg { offset: 57 },
            ],
            a_raw: &[&Reg { offset: 58 }, &Reg { offset: 59 }],
            e: &[
                &Reg { offset: 60 },
                &Reg { offset: 61 },
                &Reg { offset: 62 },
                &Reg { offset: 63 },
                &Reg { offset: 64 },
                &Reg { offset: 65 },
                &Reg { offset: 66 },
                &Reg { offset: 67 },
                &Reg { offset: 68 },
                &Reg { offset: 69 },
                &Reg { offset: 70 },
                &Reg { offset: 71 },
                &Reg { offset: 72 },
                &Reg { offset: 73 },
                &Reg { offset: 74 },
                &Reg { offset: 75 },
                &Reg { offset: 76 },
                &Reg { offset: 77 },
                &Reg { offset: 78 },
                &Reg { offset: 79 },
                &Reg { offset: 80 },
                &Reg { offset: 81 },
                &Reg { offset: 82 },
                &Reg { offset: 83 },
                &Reg { offset: 84 },
                &Reg { offset: 85 },
                &Reg { offset: 86 },
                &Reg { offset: 87 },
                &Reg { offset: 88 },
                &Reg { offset: 89 },
                &Reg { offset: 90 },
                &Reg { offset: 91 },
            ],
            e_raw: &[&Reg { offset: 92 }, &Reg { offset: 93 }],
            w: &[
                &Reg { offset: 94 },
                &Reg { offset: 95 },
                &Reg { offset: 96 },
                &Reg { offset: 97 },
                &Reg { offset: 98 },
                &Reg { offset: 99 },
                &Reg { offset: 100 },
                &Reg { offset: 101 },
                &Reg { offset: 102 },
                &Reg { offset: 103 },
                &Reg { offset: 104 },
                &Reg { offset: 105 },
                &Reg { offset: 106 },
                &Reg { offset: 107 },
                &Reg { offset: 108 },
                &Reg { offset: 109 },
                &Reg { offset: 110 },
                &Reg { offset: 111 },
                &Reg { offset: 112 },
                &Reg { offset: 113 },
                &Reg { offset: 114 },
                &Reg { offset: 115 },
                &Reg { offset: 116 },
                &Reg { offset: 117 },
                &Reg { offset: 118 },
                &Reg { offset: 119 },
                &Reg { offset: 120 },
                &Reg { offset: 121 },
                &Reg { offset: 122 },
                &Reg { offset: 123 },
                &Reg { offset: 124 },
                &Reg { offset: 125 },
            ],
            w_raw: &[&Reg { offset: 126 }, &Reg { offset: 127 }],
        },
        sha_mix: &RecursionShaCycleLayout {
            a_carry_hi: &Reg { offset: 6 },
            a_carry_low: &Reg { offset: 5 },
            e_carry_high: &Reg { offset: 8 },
            e_carry_low: &Reg { offset: 7 },
            w_carry_high: &Reg { offset: 10 },
            w_carry_low: &Reg { offset: 9 },
            io0: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 11 },
                data: &[
                    &Reg { offset: 12 },
                    &Reg { offset: 13 },
                    &Reg { offset: 14 },
                    &Reg { offset: 15 },
                ],
            },
            io1: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 16 },
                data: &[
                    &Reg { offset: 17 },
                    &Reg { offset: 18 },
                    &Reg { offset: 19 },
                    &Reg { offset: 20 },
                ],
            },
            a: &[
                &Reg { offset: 26 },
                &Reg { offset: 27 },
                &Reg { offset: 28 },
                &Reg { offset: 29 },
                &Reg { offset: 30 },
                &Reg { offset: 31 },
                &Reg { offset: 32 },
                &Reg { offset: 33 },
                &Reg { offset: 34 },
                &Reg { offset: 35 },
                &Reg { offset: 36 },
                &Reg { offset: 37 },
                &Reg { offset: 38 },
                &Reg { offset: 39 },
                &Reg { offset: 40 },
                &Reg { offset: 41 },
                &Reg { offset: 42 },
                &Reg { offset: 43 },
                &Reg { offset: 44 },
                &Reg { offset: 45 },
                &Reg { offset: 46 },
                &Reg { offset: 47 },
                &Reg { offset: 48 },
                &Reg { offset: 49 },
                &Reg { offset: 50 },
                &Reg { offset: 51 },
                &Reg { offset: 52 },
                &Reg { offset: 53 },
                &Reg { offset: 54 },
                &Reg { offset: 55 },
                &Reg { offset: 56 },
                &Reg { offset: 57 },
            ],
            a_raw: &[&Reg { offset: 58 }, &Reg { offset: 59 }],
            e: &[
                &Reg { offset: 60 },
                &Reg { offset: 61 },
                &Reg { offset: 62 },
                &Reg { offset: 63 },
                &Reg { offset: 64 },
                &Reg { offset: 65 },
                &Reg { offset: 66 },
                &Reg { offset: 67 },
                &Reg { offset: 68 },
                &Reg { offset: 69 },
                &Reg { offset: 70 },
                &Reg { offset: 71 },
                &Reg { offset: 72 },
                &Reg { offset: 73 },
                &Reg { offset: 74 },
                &Reg { offset: 75 },
                &Reg { offset: 76 },
                &Reg { offset: 77 },
                &Reg { offset: 78 },
                &Reg { offset: 79 },
                &Reg { offset: 80 },
                &Reg { offset: 81 },
                &Reg { offset: 82 },
                &Reg { offset: 83 },
                &Reg { offset: 84 },
                &Reg { offset: 85 },
                &Reg { offset: 86 },
                &Reg { offset: 87 },
                &Reg { offset: 88 },
                &Reg { offset: 89 },
                &Reg { offset: 90 },
                &Reg { offset: 91 },
            ],
            e_raw: &[&Reg { offset: 92 }, &Reg { offset: 93 }],
            w: &[
                &Reg { offset: 94 },
                &Reg { offset: 95 },
                &Reg { offset: 96 },
                &Reg { offset: 97 },
                &Reg { offset: 98 },
                &Reg { offset: 99 },
                &Reg { offset: 100 },
                &Reg { offset: 101 },
                &Reg { offset: 102 },
                &Reg { offset: 103 },
                &Reg { offset: 104 },
                &Reg { offset: 105 },
                &Reg { offset: 106 },
                &Reg { offset: 107 },
                &Reg { offset: 108 },
                &Reg { offset: 109 },
                &Reg { offset: 110 },
                &Reg { offset: 111 },
                &Reg { offset: 112 },
                &Reg { offset: 113 },
                &Reg { offset: 114 },
                &Reg { offset: 115 },
                &Reg { offset: 116 },
                &Reg { offset: 117 },
                &Reg { offset: 118 },
                &Reg { offset: 119 },
                &Reg { offset: 120 },
                &Reg { offset: 121 },
                &Reg { offset: 122 },
                &Reg { offset: 123 },
                &Reg { offset: 124 },
                &Reg { offset: 125 },
            ],
            w_raw: &[&Reg { offset: 126 }, &Reg { offset: 127 }],
        },
    },
    micro_ops: &[
        &RecursionMicroOpLayout {
            extra: &Reg { offset: 101 },
            decode: &OneHot4Layout {
                add: &Reg { offset: 91 },
                constop: &Reg { offset: 90 },
                eq: &Reg { offset: 95 },
                extract: &Reg { offset: 100 },
                inv: &Reg { offset: 94 },
                mix_rng: &Reg { offset: 98 },
                mul: &Reg { offset: 93 },
                read_iop_body: &Reg { offset: 97 },
                read_iop_header: &Reg { offset: 96 },
                select: &Reg { offset: 99 },
                sub: &Reg { offset: 92 },
            },
            in0: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 5 },
                data: &[
                    &Reg { offset: 6 },
                    &Reg { offset: 7 },
                    &Reg { offset: 8 },
                    &Reg { offset: 9 },
                ],
            },
            in1: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 10 },
                data: &[
                    &Reg { offset: 11 },
                    &Reg { offset: 12 },
                    &Reg { offset: 13 },
                    &Reg { offset: 14 },
                ],
            },
            out: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 15 },
                data: &[
                    &Reg { offset: 16 },
                    &Reg { offset: 17 },
                    &Reg { offset: 18 },
                    &Reg { offset: 19 },
                ],
            },
        },
        &RecursionMicroOpLayout {
            extra: &Reg { offset: 113 },
            decode: &OneHot4Layout {
                add: &Reg { offset: 103 },
                constop: &Reg { offset: 102 },
                eq: &Reg { offset: 107 },
                extract: &Reg { offset: 112 },
                inv: &Reg { offset: 106 },
                mix_rng: &Reg { offset: 110 },
                mul: &Reg { offset: 105 },
                read_iop_body: &Reg { offset: 109 },
                read_iop_header: &Reg { offset: 108 },
                select: &Reg { offset: 111 },
                sub: &Reg { offset: 104 },
            },
            in0: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 20 },
                data: &[
                    &Reg { offset: 21 },
                    &Reg { offset: 22 },
                    &Reg { offset: 23 },
                    &Reg { offset: 24 },
                ],
            },
            in1: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 25 },
                data: &[
                    &Reg { offset: 26 },
                    &Reg { offset: 27 },
                    &Reg { offset: 28 },
                    &Reg { offset: 29 },
                ],
            },
            out: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 30 },
                data: &[
                    &Reg { offset: 31 },
                    &Reg { offset: 32 },
                    &Reg { offset: 33 },
                    &Reg { offset: 34 },
                ],
            },
        },
        &RecursionMicroOpLayout {
            extra: &Reg { offset: 125 },
            decode: &OneHot4Layout {
                add: &Reg { offset: 115 },
                constop: &Reg { offset: 114 },
                eq: &Reg { offset: 119 },
                extract: &Reg { offset: 124 },
                inv: &Reg { offset: 118 },
                mix_rng: &Reg { offset: 122 },
                mul: &Reg { offset: 117 },
                read_iop_body: &Reg { offset: 121 },
                read_iop_header: &Reg { offset: 120 },
                select: &Reg { offset: 123 },
                sub: &Reg { offset: 116 },
            },
            in0: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 35 },
                data: &[
                    &Reg { offset: 36 },
                    &Reg { offset: 37 },
                    &Reg { offset: 38 },
                    &Reg { offset: 39 },
                ],
            },
            in1: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 40 },
                data: &[
                    &Reg { offset: 41 },
                    &Reg { offset: 42 },
                    &Reg { offset: 43 },
                    &Reg { offset: 44 },
                ],
            },
            out: &RecursionImplWomPlonkElementLayout {
                addr: &Reg { offset: 45 },
                data: &[
                    &Reg { offset: 46 },
                    &Reg { offset: 47 },
                    &Reg { offset: 48 },
                    &Reg { offset: 49 },
                ],
            },
        },
    ],
};
pub const OUT_LAYOUT: &Reg32LayoutArray = &[
    &Reg { offset: 0 },
    &Reg { offset: 1 },
    &Reg { offset: 2 },
    &Reg { offset: 3 },
    &Reg { offset: 4 },
    &Reg { offset: 5 },
    &Reg { offset: 6 },
    &Reg { offset: 7 },
    &Reg { offset: 8 },
    &Reg { offset: 9 },
    &Reg { offset: 10 },
    &Reg { offset: 11 },
    &Reg { offset: 12 },
    &Reg { offset: 13 },
    &Reg { offset: 14 },
    &Reg { offset: 15 },
    &Reg { offset: 16 },
    &Reg { offset: 17 },
    &Reg { offset: 18 },
    &Reg { offset: 19 },
    &Reg { offset: 20 },
    &Reg { offset: 21 },
    &Reg { offset: 22 },
    &Reg { offset: 23 },
    &Reg { offset: 24 },
    &Reg { offset: 25 },
    &Reg { offset: 26 },
    &Reg { offset: 27 },
    &Reg { offset: 28 },
    &Reg { offset: 29 },
    &Reg { offset: 30 },
    &Reg { offset: 31 },
];
