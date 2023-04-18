// :0
pub struct BytesSetupStep {}
impl risc0_zkp::layout::Component for BytesSetupStep {
    fn ty_name(&self) -> &'static str {
        "BytesSetupStep"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        Ok(())
    }
}

// circuit/rv32im/global.h:15
pub struct U32Reg {
    pub byte: &'static [&'static OutReg; 4],
}
impl risc0_zkp::layout::Component for U32Reg {
    fn ty_name(&self) -> &'static str {
        "U32Reg"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("byte", self.byte)?;
        Ok(())
    }
}

// circuit/rv32im/global.h:26
pub struct SystemState {
    pub pc: &'static U32Reg,
    pub image_id: &'static [&'static U32Reg; 8],
}
impl risc0_zkp::layout::Component for SystemState {
    fn ty_name(&self) -> &'static str {
        "SystemState"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("pc", self.pc)?;
        v.visit_component("image_id", self.image_id)?;
        Ok(())
    }
}

// :0
pub struct RamLoadStep {
    pub check_dirty: &'static OutReg,
    pub post: &'static SystemState,
    pub pre: &'static SystemState,
    pub output: &'static [&'static U32Reg; 8],
}
impl risc0_zkp::layout::Component for RamLoadStep {
    fn ty_name(&self) -> &'static str {
        "RamLoadStep"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("check_dirty", self.check_dirty)?;
        v.visit_component("post", self.post)?;
        v.visit_component("pre", self.pre)?;
        v.visit_component("output", self.output)?;
        Ok(())
    }
}

// cirgen/circuit/rv32im/top.cpp:60
pub struct Mux {
    pub body: &'static RamLoadStep,
    pub bytes_fini: &'static BytesSetupStep,
    pub bytes_init: &'static BytesSetupStep,
    pub bytes_setup: &'static BytesSetupStep,
    pub ram_fini: &'static RamLoadStep,
    pub ram_init: &'static RamLoadStep,
    pub ram_load: &'static RamLoadStep,
    pub reset: &'static RamLoadStep,
}
impl risc0_zkp::layout::Component for Mux {
    fn ty_name(&self) -> &'static str {
        "Mux"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("body", self.body)?;
        v.visit_component("bytes_fini", self.bytes_fini)?;
        v.visit_component("bytes_init", self.bytes_init)?;
        v.visit_component("bytes_setup", self.bytes_setup)?;
        v.visit_component("ram_fini", self.ram_fini)?;
        v.visit_component("ram_init", self.ram_init)?;
        v.visit_component("ram_load", self.ram_load)?;
        v.visit_component("reset", self.reset)?;
        Ok(())
    }
}

// compiler/edsl/component.h:142
pub struct Top {
    pub halted: &'static DataReg,
    pub mux: &'static Mux,
}
impl risc0_zkp::layout::Component for Top {
    fn ty_name(&self) -> &'static str {
        "Top"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("halted", self.halted)?;
        v.visit_component("mux", self.mux)?;
        Ok(())
    }
}

// compiler/edsl/component.h:142
pub const LAYOUT_HALTED: DataReg = DataReg { offset: 2 };

// :0
pub const LAYOUT_MUX_BODY_CHECK_DIRTY: OutReg = OutReg { offset: 72 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_BODY_POST_PC_BYTE_0_: OutReg = OutReg { offset: 36 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_BODY_POST_PC_BYTE_1_: OutReg = OutReg { offset: 37 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_BODY_POST_PC_BYTE_2_: OutReg = OutReg { offset: 38 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_BODY_POST_PC_BYTE_3_: OutReg = OutReg { offset: 39 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_BODY_POST_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_POST_PC_BYTE_0_,
        &LAYOUT_MUX_BODY_POST_PC_BYTE_1_,
        &LAYOUT_MUX_BODY_POST_PC_BYTE_2_,
        &LAYOUT_MUX_BODY_POST_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_0_BYTE_0_: OutReg = OutReg { offset: 40 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_0_BYTE_1_: OutReg = OutReg { offset: 41 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_0_BYTE_2_: OutReg = OutReg { offset: 42 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_0_BYTE_3_: OutReg = OutReg { offset: 43 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_0_BYTE_0_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_0_BYTE_1_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_0_BYTE_2_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_1_BYTE_0_: OutReg = OutReg { offset: 44 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_1_BYTE_1_: OutReg = OutReg { offset: 45 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_1_BYTE_2_: OutReg = OutReg { offset: 46 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_1_BYTE_3_: OutReg = OutReg { offset: 47 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_1_BYTE_0_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_1_BYTE_1_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_1_BYTE_2_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_2_BYTE_0_: OutReg = OutReg { offset: 48 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_2_BYTE_1_: OutReg = OutReg { offset: 49 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_2_BYTE_2_: OutReg = OutReg { offset: 50 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_2_BYTE_3_: OutReg = OutReg { offset: 51 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_2_BYTE_0_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_2_BYTE_1_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_2_BYTE_2_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_3_BYTE_0_: OutReg = OutReg { offset: 52 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_3_BYTE_1_: OutReg = OutReg { offset: 53 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_3_BYTE_2_: OutReg = OutReg { offset: 54 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_3_BYTE_3_: OutReg = OutReg { offset: 55 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_3_BYTE_0_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_3_BYTE_1_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_3_BYTE_2_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_4_BYTE_0_: OutReg = OutReg { offset: 56 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_4_BYTE_1_: OutReg = OutReg { offset: 57 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_4_BYTE_2_: OutReg = OutReg { offset: 58 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_4_BYTE_3_: OutReg = OutReg { offset: 59 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_4_BYTE_0_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_4_BYTE_1_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_4_BYTE_2_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_5_BYTE_0_: OutReg = OutReg { offset: 60 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_5_BYTE_1_: OutReg = OutReg { offset: 61 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_5_BYTE_2_: OutReg = OutReg { offset: 62 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_5_BYTE_3_: OutReg = OutReg { offset: 63 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_5_BYTE_0_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_5_BYTE_1_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_5_BYTE_2_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_6_BYTE_0_: OutReg = OutReg { offset: 64 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_6_BYTE_1_: OutReg = OutReg { offset: 65 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_6_BYTE_2_: OutReg = OutReg { offset: 66 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_6_BYTE_3_: OutReg = OutReg { offset: 67 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_6_BYTE_0_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_6_BYTE_1_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_6_BYTE_2_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_7_BYTE_0_: OutReg = OutReg { offset: 68 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_7_BYTE_1_: OutReg = OutReg { offset: 69 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_7_BYTE_2_: OutReg = OutReg { offset: 70 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_7_BYTE_3_: OutReg = OutReg { offset: 71 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_POST_IMAGE_ID_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_7_BYTE_0_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_7_BYTE_1_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_7_BYTE_2_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:26
pub const LAYOUT_MUX_BODY_POST: SystemState = SystemState {
    pc: &LAYOUT_MUX_BODY_POST_PC,
    image_id: &[
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_0_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_1_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_2_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_3_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_4_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_5_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_6_,
        &LAYOUT_MUX_BODY_POST_IMAGE_ID_7_,
    ],
};

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_BODY_PRE_PC_BYTE_0_: OutReg = OutReg { offset: 0 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_BODY_PRE_PC_BYTE_1_: OutReg = OutReg { offset: 1 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_BODY_PRE_PC_BYTE_2_: OutReg = OutReg { offset: 2 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_BODY_PRE_PC_BYTE_3_: OutReg = OutReg { offset: 3 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_BODY_PRE_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_PRE_PC_BYTE_0_,
        &LAYOUT_MUX_BODY_PRE_PC_BYTE_1_,
        &LAYOUT_MUX_BODY_PRE_PC_BYTE_2_,
        &LAYOUT_MUX_BODY_PRE_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_0_BYTE_0_: OutReg = OutReg { offset: 4 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_0_BYTE_1_: OutReg = OutReg { offset: 5 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_0_BYTE_2_: OutReg = OutReg { offset: 6 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_0_BYTE_3_: OutReg = OutReg { offset: 7 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_0_BYTE_0_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_0_BYTE_1_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_0_BYTE_2_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_1_BYTE_0_: OutReg = OutReg { offset: 8 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_1_BYTE_1_: OutReg = OutReg { offset: 9 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_1_BYTE_2_: OutReg = OutReg { offset: 10 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_1_BYTE_3_: OutReg = OutReg { offset: 11 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_1_BYTE_0_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_1_BYTE_1_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_1_BYTE_2_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_2_BYTE_0_: OutReg = OutReg { offset: 12 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_2_BYTE_1_: OutReg = OutReg { offset: 13 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_2_BYTE_2_: OutReg = OutReg { offset: 14 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_2_BYTE_3_: OutReg = OutReg { offset: 15 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_2_BYTE_0_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_2_BYTE_1_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_2_BYTE_2_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_3_BYTE_0_: OutReg = OutReg { offset: 16 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_3_BYTE_1_: OutReg = OutReg { offset: 17 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_3_BYTE_2_: OutReg = OutReg { offset: 18 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_3_BYTE_3_: OutReg = OutReg { offset: 19 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_3_BYTE_0_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_3_BYTE_1_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_3_BYTE_2_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_4_BYTE_0_: OutReg = OutReg { offset: 20 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_4_BYTE_1_: OutReg = OutReg { offset: 21 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_4_BYTE_2_: OutReg = OutReg { offset: 22 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_4_BYTE_3_: OutReg = OutReg { offset: 23 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_4_BYTE_0_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_4_BYTE_1_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_4_BYTE_2_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_5_BYTE_0_: OutReg = OutReg { offset: 24 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_5_BYTE_1_: OutReg = OutReg { offset: 25 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_5_BYTE_2_: OutReg = OutReg { offset: 26 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_5_BYTE_3_: OutReg = OutReg { offset: 27 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_5_BYTE_0_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_5_BYTE_1_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_5_BYTE_2_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_6_BYTE_0_: OutReg = OutReg { offset: 28 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_6_BYTE_1_: OutReg = OutReg { offset: 29 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_6_BYTE_2_: OutReg = OutReg { offset: 30 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_6_BYTE_3_: OutReg = OutReg { offset: 31 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_6_BYTE_0_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_6_BYTE_1_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_6_BYTE_2_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_7_BYTE_0_: OutReg = OutReg { offset: 32 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_7_BYTE_1_: OutReg = OutReg { offset: 33 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_7_BYTE_2_: OutReg = OutReg { offset: 34 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_7_BYTE_3_: OutReg = OutReg { offset: 35 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_PRE_IMAGE_ID_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_7_BYTE_0_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_7_BYTE_1_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_7_BYTE_2_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:26
pub const LAYOUT_MUX_BODY_PRE: SystemState = SystemState {
    pc: &LAYOUT_MUX_BODY_PRE_PC,
    image_id: &[
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_0_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_1_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_2_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_3_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_4_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_5_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_6_,
        &LAYOUT_MUX_BODY_PRE_IMAGE_ID_7_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_0_BYTE_0_: OutReg = OutReg { offset: 73 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_0_BYTE_1_: OutReg = OutReg { offset: 74 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_0_BYTE_2_: OutReg = OutReg { offset: 75 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_0_BYTE_3_: OutReg = OutReg { offset: 76 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_OUTPUT_0_BYTE_0_,
        &LAYOUT_MUX_BODY_OUTPUT_0_BYTE_1_,
        &LAYOUT_MUX_BODY_OUTPUT_0_BYTE_2_,
        &LAYOUT_MUX_BODY_OUTPUT_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_1_BYTE_0_: OutReg = OutReg { offset: 77 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_1_BYTE_1_: OutReg = OutReg { offset: 78 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_1_BYTE_2_: OutReg = OutReg { offset: 79 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_1_BYTE_3_: OutReg = OutReg { offset: 80 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_OUTPUT_1_BYTE_0_,
        &LAYOUT_MUX_BODY_OUTPUT_1_BYTE_1_,
        &LAYOUT_MUX_BODY_OUTPUT_1_BYTE_2_,
        &LAYOUT_MUX_BODY_OUTPUT_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_2_BYTE_0_: OutReg = OutReg { offset: 81 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_2_BYTE_1_: OutReg = OutReg { offset: 82 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_2_BYTE_2_: OutReg = OutReg { offset: 83 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_2_BYTE_3_: OutReg = OutReg { offset: 84 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_OUTPUT_2_BYTE_0_,
        &LAYOUT_MUX_BODY_OUTPUT_2_BYTE_1_,
        &LAYOUT_MUX_BODY_OUTPUT_2_BYTE_2_,
        &LAYOUT_MUX_BODY_OUTPUT_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_3_BYTE_0_: OutReg = OutReg { offset: 85 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_3_BYTE_1_: OutReg = OutReg { offset: 86 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_3_BYTE_2_: OutReg = OutReg { offset: 87 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_3_BYTE_3_: OutReg = OutReg { offset: 88 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_OUTPUT_3_BYTE_0_,
        &LAYOUT_MUX_BODY_OUTPUT_3_BYTE_1_,
        &LAYOUT_MUX_BODY_OUTPUT_3_BYTE_2_,
        &LAYOUT_MUX_BODY_OUTPUT_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_4_BYTE_0_: OutReg = OutReg { offset: 89 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_4_BYTE_1_: OutReg = OutReg { offset: 90 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_4_BYTE_2_: OutReg = OutReg { offset: 91 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_4_BYTE_3_: OutReg = OutReg { offset: 92 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_OUTPUT_4_BYTE_0_,
        &LAYOUT_MUX_BODY_OUTPUT_4_BYTE_1_,
        &LAYOUT_MUX_BODY_OUTPUT_4_BYTE_2_,
        &LAYOUT_MUX_BODY_OUTPUT_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_5_BYTE_0_: OutReg = OutReg { offset: 93 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_5_BYTE_1_: OutReg = OutReg { offset: 94 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_5_BYTE_2_: OutReg = OutReg { offset: 95 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_5_BYTE_3_: OutReg = OutReg { offset: 96 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_OUTPUT_5_BYTE_0_,
        &LAYOUT_MUX_BODY_OUTPUT_5_BYTE_1_,
        &LAYOUT_MUX_BODY_OUTPUT_5_BYTE_2_,
        &LAYOUT_MUX_BODY_OUTPUT_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_6_BYTE_0_: OutReg = OutReg { offset: 97 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_6_BYTE_1_: OutReg = OutReg { offset: 98 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_6_BYTE_2_: OutReg = OutReg { offset: 99 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_6_BYTE_3_: OutReg = OutReg { offset: 100 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_OUTPUT_6_BYTE_0_,
        &LAYOUT_MUX_BODY_OUTPUT_6_BYTE_1_,
        &LAYOUT_MUX_BODY_OUTPUT_6_BYTE_2_,
        &LAYOUT_MUX_BODY_OUTPUT_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_7_BYTE_0_: OutReg = OutReg { offset: 101 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_7_BYTE_1_: OutReg = OutReg { offset: 102 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_7_BYTE_2_: OutReg = OutReg { offset: 103 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_7_BYTE_3_: OutReg = OutReg { offset: 104 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_BODY_OUTPUT_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_OUTPUT_7_BYTE_0_,
        &LAYOUT_MUX_BODY_OUTPUT_7_BYTE_1_,
        &LAYOUT_MUX_BODY_OUTPUT_7_BYTE_2_,
        &LAYOUT_MUX_BODY_OUTPUT_7_BYTE_3_,
    ],
};

// :0
pub const LAYOUT_MUX_BODY: RamLoadStep = RamLoadStep {
    check_dirty: &LAYOUT_MUX_BODY_CHECK_DIRTY,
    post: &LAYOUT_MUX_BODY_POST,
    pre: &LAYOUT_MUX_BODY_PRE,
    output: &[
        &LAYOUT_MUX_BODY_OUTPUT_0_,
        &LAYOUT_MUX_BODY_OUTPUT_1_,
        &LAYOUT_MUX_BODY_OUTPUT_2_,
        &LAYOUT_MUX_BODY_OUTPUT_3_,
        &LAYOUT_MUX_BODY_OUTPUT_4_,
        &LAYOUT_MUX_BODY_OUTPUT_5_,
        &LAYOUT_MUX_BODY_OUTPUT_6_,
        &LAYOUT_MUX_BODY_OUTPUT_7_,
    ],
};

// :0
pub const LAYOUT_MUX_BYTES_FINI: BytesSetupStep = BytesSetupStep {};

// :0
pub const LAYOUT_MUX_BYTES_INIT: BytesSetupStep = BytesSetupStep {};

// :0
pub const LAYOUT_MUX_BYTES_SETUP: BytesSetupStep = BytesSetupStep {};

// :0
pub const LAYOUT_MUX_RAM_FINI_CHECK_DIRTY: OutReg = OutReg { offset: 72 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_FINI_POST_PC_BYTE_0_: OutReg = OutReg { offset: 36 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_FINI_POST_PC_BYTE_1_: OutReg = OutReg { offset: 37 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_FINI_POST_PC_BYTE_2_: OutReg = OutReg { offset: 38 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_FINI_POST_PC_BYTE_3_: OutReg = OutReg { offset: 39 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_FINI_POST_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_POST_PC_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_POST_PC_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_POST_PC_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_POST_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_0_BYTE_0_: OutReg = OutReg { offset: 40 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_0_BYTE_1_: OutReg = OutReg { offset: 41 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_0_BYTE_2_: OutReg = OutReg { offset: 42 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_0_BYTE_3_: OutReg = OutReg { offset: 43 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_0_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_0_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_0_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_1_BYTE_0_: OutReg = OutReg { offset: 44 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_1_BYTE_1_: OutReg = OutReg { offset: 45 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_1_BYTE_2_: OutReg = OutReg { offset: 46 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_1_BYTE_3_: OutReg = OutReg { offset: 47 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_1_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_1_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_1_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_2_BYTE_0_: OutReg = OutReg { offset: 48 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_2_BYTE_1_: OutReg = OutReg { offset: 49 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_2_BYTE_2_: OutReg = OutReg { offset: 50 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_2_BYTE_3_: OutReg = OutReg { offset: 51 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_2_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_2_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_2_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_3_BYTE_0_: OutReg = OutReg { offset: 52 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_3_BYTE_1_: OutReg = OutReg { offset: 53 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_3_BYTE_2_: OutReg = OutReg { offset: 54 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_3_BYTE_3_: OutReg = OutReg { offset: 55 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_3_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_3_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_3_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_4_BYTE_0_: OutReg = OutReg { offset: 56 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_4_BYTE_1_: OutReg = OutReg { offset: 57 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_4_BYTE_2_: OutReg = OutReg { offset: 58 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_4_BYTE_3_: OutReg = OutReg { offset: 59 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_4_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_4_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_4_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_5_BYTE_0_: OutReg = OutReg { offset: 60 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_5_BYTE_1_: OutReg = OutReg { offset: 61 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_5_BYTE_2_: OutReg = OutReg { offset: 62 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_5_BYTE_3_: OutReg = OutReg { offset: 63 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_5_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_5_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_5_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_6_BYTE_0_: OutReg = OutReg { offset: 64 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_6_BYTE_1_: OutReg = OutReg { offset: 65 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_6_BYTE_2_: OutReg = OutReg { offset: 66 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_6_BYTE_3_: OutReg = OutReg { offset: 67 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_6_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_6_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_6_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_7_BYTE_0_: OutReg = OutReg { offset: 68 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_7_BYTE_1_: OutReg = OutReg { offset: 69 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_7_BYTE_2_: OutReg = OutReg { offset: 70 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_7_BYTE_3_: OutReg = OutReg { offset: 71 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_7_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_7_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_7_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:26
pub const LAYOUT_MUX_RAM_FINI_POST: SystemState = SystemState {
    pc: &LAYOUT_MUX_RAM_FINI_POST_PC,
    image_id: &[
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_0_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_1_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_2_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_3_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_4_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_5_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_6_,
        &LAYOUT_MUX_RAM_FINI_POST_IMAGE_ID_7_,
    ],
};

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_FINI_PRE_PC_BYTE_0_: OutReg = OutReg { offset: 0 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_FINI_PRE_PC_BYTE_1_: OutReg = OutReg { offset: 1 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_FINI_PRE_PC_BYTE_2_: OutReg = OutReg { offset: 2 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_FINI_PRE_PC_BYTE_3_: OutReg = OutReg { offset: 3 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_FINI_PRE_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_PRE_PC_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_PRE_PC_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_PRE_PC_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_PRE_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_0_BYTE_0_: OutReg = OutReg { offset: 4 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_0_BYTE_1_: OutReg = OutReg { offset: 5 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_0_BYTE_2_: OutReg = OutReg { offset: 6 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_0_BYTE_3_: OutReg = OutReg { offset: 7 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_0_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_0_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_0_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_1_BYTE_0_: OutReg = OutReg { offset: 8 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_1_BYTE_1_: OutReg = OutReg { offset: 9 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_1_BYTE_2_: OutReg = OutReg { offset: 10 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_1_BYTE_3_: OutReg = OutReg { offset: 11 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_1_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_1_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_1_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_2_BYTE_0_: OutReg = OutReg { offset: 12 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_2_BYTE_1_: OutReg = OutReg { offset: 13 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_2_BYTE_2_: OutReg = OutReg { offset: 14 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_2_BYTE_3_: OutReg = OutReg { offset: 15 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_2_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_2_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_2_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_3_BYTE_0_: OutReg = OutReg { offset: 16 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_3_BYTE_1_: OutReg = OutReg { offset: 17 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_3_BYTE_2_: OutReg = OutReg { offset: 18 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_3_BYTE_3_: OutReg = OutReg { offset: 19 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_3_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_3_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_3_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_4_BYTE_0_: OutReg = OutReg { offset: 20 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_4_BYTE_1_: OutReg = OutReg { offset: 21 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_4_BYTE_2_: OutReg = OutReg { offset: 22 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_4_BYTE_3_: OutReg = OutReg { offset: 23 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_4_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_4_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_4_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_5_BYTE_0_: OutReg = OutReg { offset: 24 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_5_BYTE_1_: OutReg = OutReg { offset: 25 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_5_BYTE_2_: OutReg = OutReg { offset: 26 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_5_BYTE_3_: OutReg = OutReg { offset: 27 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_5_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_5_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_5_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_6_BYTE_0_: OutReg = OutReg { offset: 28 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_6_BYTE_1_: OutReg = OutReg { offset: 29 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_6_BYTE_2_: OutReg = OutReg { offset: 30 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_6_BYTE_3_: OutReg = OutReg { offset: 31 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_6_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_6_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_6_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_7_BYTE_0_: OutReg = OutReg { offset: 32 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_7_BYTE_1_: OutReg = OutReg { offset: 33 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_7_BYTE_2_: OutReg = OutReg { offset: 34 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_7_BYTE_3_: OutReg = OutReg { offset: 35 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_7_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_7_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_7_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:26
pub const LAYOUT_MUX_RAM_FINI_PRE: SystemState = SystemState {
    pc: &LAYOUT_MUX_RAM_FINI_PRE_PC,
    image_id: &[
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_0_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_1_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_2_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_3_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_4_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_5_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_6_,
        &LAYOUT_MUX_RAM_FINI_PRE_IMAGE_ID_7_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_0_BYTE_0_: OutReg = OutReg { offset: 73 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_0_BYTE_1_: OutReg = OutReg { offset: 74 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_0_BYTE_2_: OutReg = OutReg { offset: 75 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_0_BYTE_3_: OutReg = OutReg { offset: 76 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_OUTPUT_0_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_0_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_0_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_1_BYTE_0_: OutReg = OutReg { offset: 77 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_1_BYTE_1_: OutReg = OutReg { offset: 78 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_1_BYTE_2_: OutReg = OutReg { offset: 79 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_1_BYTE_3_: OutReg = OutReg { offset: 80 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_OUTPUT_1_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_1_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_1_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_2_BYTE_0_: OutReg = OutReg { offset: 81 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_2_BYTE_1_: OutReg = OutReg { offset: 82 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_2_BYTE_2_: OutReg = OutReg { offset: 83 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_2_BYTE_3_: OutReg = OutReg { offset: 84 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_OUTPUT_2_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_2_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_2_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_3_BYTE_0_: OutReg = OutReg { offset: 85 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_3_BYTE_1_: OutReg = OutReg { offset: 86 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_3_BYTE_2_: OutReg = OutReg { offset: 87 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_3_BYTE_3_: OutReg = OutReg { offset: 88 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_OUTPUT_3_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_3_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_3_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_4_BYTE_0_: OutReg = OutReg { offset: 89 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_4_BYTE_1_: OutReg = OutReg { offset: 90 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_4_BYTE_2_: OutReg = OutReg { offset: 91 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_4_BYTE_3_: OutReg = OutReg { offset: 92 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_OUTPUT_4_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_4_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_4_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_5_BYTE_0_: OutReg = OutReg { offset: 93 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_5_BYTE_1_: OutReg = OutReg { offset: 94 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_5_BYTE_2_: OutReg = OutReg { offset: 95 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_5_BYTE_3_: OutReg = OutReg { offset: 96 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_OUTPUT_5_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_5_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_5_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_6_BYTE_0_: OutReg = OutReg { offset: 97 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_6_BYTE_1_: OutReg = OutReg { offset: 98 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_6_BYTE_2_: OutReg = OutReg { offset: 99 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_6_BYTE_3_: OutReg = OutReg { offset: 100 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_OUTPUT_6_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_6_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_6_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_7_BYTE_0_: OutReg = OutReg { offset: 101 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_7_BYTE_1_: OutReg = OutReg { offset: 102 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_7_BYTE_2_: OutReg = OutReg { offset: 103 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_7_BYTE_3_: OutReg = OutReg { offset: 104 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_FINI_OUTPUT_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_FINI_OUTPUT_7_BYTE_0_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_7_BYTE_1_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_7_BYTE_2_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_7_BYTE_3_,
    ],
};

// :0
pub const LAYOUT_MUX_RAM_FINI: RamLoadStep = RamLoadStep {
    check_dirty: &LAYOUT_MUX_RAM_FINI_CHECK_DIRTY,
    post: &LAYOUT_MUX_RAM_FINI_POST,
    pre: &LAYOUT_MUX_RAM_FINI_PRE,
    output: &[
        &LAYOUT_MUX_RAM_FINI_OUTPUT_0_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_1_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_2_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_3_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_4_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_5_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_6_,
        &LAYOUT_MUX_RAM_FINI_OUTPUT_7_,
    ],
};

// :0
pub const LAYOUT_MUX_RAM_INIT_CHECK_DIRTY: OutReg = OutReg { offset: 72 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_INIT_POST_PC_BYTE_0_: OutReg = OutReg { offset: 36 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_INIT_POST_PC_BYTE_1_: OutReg = OutReg { offset: 37 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_INIT_POST_PC_BYTE_2_: OutReg = OutReg { offset: 38 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_INIT_POST_PC_BYTE_3_: OutReg = OutReg { offset: 39 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_INIT_POST_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_POST_PC_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_POST_PC_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_POST_PC_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_POST_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_0_BYTE_0_: OutReg = OutReg { offset: 40 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_0_BYTE_1_: OutReg = OutReg { offset: 41 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_0_BYTE_2_: OutReg = OutReg { offset: 42 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_0_BYTE_3_: OutReg = OutReg { offset: 43 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_0_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_0_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_0_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_1_BYTE_0_: OutReg = OutReg { offset: 44 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_1_BYTE_1_: OutReg = OutReg { offset: 45 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_1_BYTE_2_: OutReg = OutReg { offset: 46 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_1_BYTE_3_: OutReg = OutReg { offset: 47 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_1_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_1_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_1_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_2_BYTE_0_: OutReg = OutReg { offset: 48 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_2_BYTE_1_: OutReg = OutReg { offset: 49 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_2_BYTE_2_: OutReg = OutReg { offset: 50 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_2_BYTE_3_: OutReg = OutReg { offset: 51 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_2_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_2_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_2_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_3_BYTE_0_: OutReg = OutReg { offset: 52 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_3_BYTE_1_: OutReg = OutReg { offset: 53 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_3_BYTE_2_: OutReg = OutReg { offset: 54 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_3_BYTE_3_: OutReg = OutReg { offset: 55 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_3_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_3_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_3_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_4_BYTE_0_: OutReg = OutReg { offset: 56 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_4_BYTE_1_: OutReg = OutReg { offset: 57 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_4_BYTE_2_: OutReg = OutReg { offset: 58 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_4_BYTE_3_: OutReg = OutReg { offset: 59 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_4_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_4_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_4_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_5_BYTE_0_: OutReg = OutReg { offset: 60 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_5_BYTE_1_: OutReg = OutReg { offset: 61 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_5_BYTE_2_: OutReg = OutReg { offset: 62 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_5_BYTE_3_: OutReg = OutReg { offset: 63 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_5_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_5_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_5_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_6_BYTE_0_: OutReg = OutReg { offset: 64 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_6_BYTE_1_: OutReg = OutReg { offset: 65 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_6_BYTE_2_: OutReg = OutReg { offset: 66 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_6_BYTE_3_: OutReg = OutReg { offset: 67 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_6_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_6_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_6_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_7_BYTE_0_: OutReg = OutReg { offset: 68 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_7_BYTE_1_: OutReg = OutReg { offset: 69 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_7_BYTE_2_: OutReg = OutReg { offset: 70 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_7_BYTE_3_: OutReg = OutReg { offset: 71 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_7_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_7_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_7_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:26
pub const LAYOUT_MUX_RAM_INIT_POST: SystemState = SystemState {
    pc: &LAYOUT_MUX_RAM_INIT_POST_PC,
    image_id: &[
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_0_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_1_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_2_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_3_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_4_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_5_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_6_,
        &LAYOUT_MUX_RAM_INIT_POST_IMAGE_ID_7_,
    ],
};

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_INIT_PRE_PC_BYTE_0_: OutReg = OutReg { offset: 0 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_INIT_PRE_PC_BYTE_1_: OutReg = OutReg { offset: 1 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_INIT_PRE_PC_BYTE_2_: OutReg = OutReg { offset: 2 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_INIT_PRE_PC_BYTE_3_: OutReg = OutReg { offset: 3 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_INIT_PRE_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_PRE_PC_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_PRE_PC_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_PRE_PC_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_PRE_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_0_BYTE_0_: OutReg = OutReg { offset: 4 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_0_BYTE_1_: OutReg = OutReg { offset: 5 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_0_BYTE_2_: OutReg = OutReg { offset: 6 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_0_BYTE_3_: OutReg = OutReg { offset: 7 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_0_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_0_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_0_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_1_BYTE_0_: OutReg = OutReg { offset: 8 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_1_BYTE_1_: OutReg = OutReg { offset: 9 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_1_BYTE_2_: OutReg = OutReg { offset: 10 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_1_BYTE_3_: OutReg = OutReg { offset: 11 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_1_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_1_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_1_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_2_BYTE_0_: OutReg = OutReg { offset: 12 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_2_BYTE_1_: OutReg = OutReg { offset: 13 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_2_BYTE_2_: OutReg = OutReg { offset: 14 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_2_BYTE_3_: OutReg = OutReg { offset: 15 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_2_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_2_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_2_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_3_BYTE_0_: OutReg = OutReg { offset: 16 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_3_BYTE_1_: OutReg = OutReg { offset: 17 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_3_BYTE_2_: OutReg = OutReg { offset: 18 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_3_BYTE_3_: OutReg = OutReg { offset: 19 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_3_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_3_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_3_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_4_BYTE_0_: OutReg = OutReg { offset: 20 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_4_BYTE_1_: OutReg = OutReg { offset: 21 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_4_BYTE_2_: OutReg = OutReg { offset: 22 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_4_BYTE_3_: OutReg = OutReg { offset: 23 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_4_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_4_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_4_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_5_BYTE_0_: OutReg = OutReg { offset: 24 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_5_BYTE_1_: OutReg = OutReg { offset: 25 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_5_BYTE_2_: OutReg = OutReg { offset: 26 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_5_BYTE_3_: OutReg = OutReg { offset: 27 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_5_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_5_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_5_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_6_BYTE_0_: OutReg = OutReg { offset: 28 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_6_BYTE_1_: OutReg = OutReg { offset: 29 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_6_BYTE_2_: OutReg = OutReg { offset: 30 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_6_BYTE_3_: OutReg = OutReg { offset: 31 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_6_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_6_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_6_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_7_BYTE_0_: OutReg = OutReg { offset: 32 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_7_BYTE_1_: OutReg = OutReg { offset: 33 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_7_BYTE_2_: OutReg = OutReg { offset: 34 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_7_BYTE_3_: OutReg = OutReg { offset: 35 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_7_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_7_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_7_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:26
pub const LAYOUT_MUX_RAM_INIT_PRE: SystemState = SystemState {
    pc: &LAYOUT_MUX_RAM_INIT_PRE_PC,
    image_id: &[
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_0_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_1_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_2_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_3_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_4_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_5_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_6_,
        &LAYOUT_MUX_RAM_INIT_PRE_IMAGE_ID_7_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_0_BYTE_0_: OutReg = OutReg { offset: 73 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_0_BYTE_1_: OutReg = OutReg { offset: 74 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_0_BYTE_2_: OutReg = OutReg { offset: 75 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_0_BYTE_3_: OutReg = OutReg { offset: 76 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_OUTPUT_0_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_0_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_0_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_1_BYTE_0_: OutReg = OutReg { offset: 77 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_1_BYTE_1_: OutReg = OutReg { offset: 78 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_1_BYTE_2_: OutReg = OutReg { offset: 79 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_1_BYTE_3_: OutReg = OutReg { offset: 80 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_OUTPUT_1_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_1_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_1_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_2_BYTE_0_: OutReg = OutReg { offset: 81 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_2_BYTE_1_: OutReg = OutReg { offset: 82 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_2_BYTE_2_: OutReg = OutReg { offset: 83 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_2_BYTE_3_: OutReg = OutReg { offset: 84 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_OUTPUT_2_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_2_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_2_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_3_BYTE_0_: OutReg = OutReg { offset: 85 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_3_BYTE_1_: OutReg = OutReg { offset: 86 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_3_BYTE_2_: OutReg = OutReg { offset: 87 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_3_BYTE_3_: OutReg = OutReg { offset: 88 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_OUTPUT_3_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_3_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_3_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_4_BYTE_0_: OutReg = OutReg { offset: 89 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_4_BYTE_1_: OutReg = OutReg { offset: 90 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_4_BYTE_2_: OutReg = OutReg { offset: 91 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_4_BYTE_3_: OutReg = OutReg { offset: 92 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_OUTPUT_4_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_4_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_4_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_5_BYTE_0_: OutReg = OutReg { offset: 93 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_5_BYTE_1_: OutReg = OutReg { offset: 94 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_5_BYTE_2_: OutReg = OutReg { offset: 95 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_5_BYTE_3_: OutReg = OutReg { offset: 96 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_OUTPUT_5_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_5_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_5_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_6_BYTE_0_: OutReg = OutReg { offset: 97 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_6_BYTE_1_: OutReg = OutReg { offset: 98 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_6_BYTE_2_: OutReg = OutReg { offset: 99 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_6_BYTE_3_: OutReg = OutReg { offset: 100 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_OUTPUT_6_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_6_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_6_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_7_BYTE_0_: OutReg = OutReg { offset: 101 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_7_BYTE_1_: OutReg = OutReg { offset: 102 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_7_BYTE_2_: OutReg = OutReg { offset: 103 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_7_BYTE_3_: OutReg = OutReg { offset: 104 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_INIT_OUTPUT_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_INIT_OUTPUT_7_BYTE_0_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_7_BYTE_1_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_7_BYTE_2_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_7_BYTE_3_,
    ],
};

// :0
pub const LAYOUT_MUX_RAM_INIT: RamLoadStep = RamLoadStep {
    check_dirty: &LAYOUT_MUX_RAM_INIT_CHECK_DIRTY,
    post: &LAYOUT_MUX_RAM_INIT_POST,
    pre: &LAYOUT_MUX_RAM_INIT_PRE,
    output: &[
        &LAYOUT_MUX_RAM_INIT_OUTPUT_0_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_1_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_2_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_3_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_4_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_5_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_6_,
        &LAYOUT_MUX_RAM_INIT_OUTPUT_7_,
    ],
};

// :0
pub const LAYOUT_MUX_RAM_LOAD_CHECK_DIRTY: OutReg = OutReg { offset: 72 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_LOAD_POST_PC_BYTE_0_: OutReg = OutReg { offset: 36 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_LOAD_POST_PC_BYTE_1_: OutReg = OutReg { offset: 37 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_LOAD_POST_PC_BYTE_2_: OutReg = OutReg { offset: 38 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_LOAD_POST_PC_BYTE_3_: OutReg = OutReg { offset: 39 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_LOAD_POST_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_POST_PC_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_POST_PC_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_POST_PC_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_POST_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_0_BYTE_0_: OutReg = OutReg { offset: 40 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_0_BYTE_1_: OutReg = OutReg { offset: 41 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_0_BYTE_2_: OutReg = OutReg { offset: 42 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_0_BYTE_3_: OutReg = OutReg { offset: 43 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_0_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_0_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_0_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_1_BYTE_0_: OutReg = OutReg { offset: 44 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_1_BYTE_1_: OutReg = OutReg { offset: 45 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_1_BYTE_2_: OutReg = OutReg { offset: 46 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_1_BYTE_3_: OutReg = OutReg { offset: 47 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_1_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_1_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_1_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_2_BYTE_0_: OutReg = OutReg { offset: 48 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_2_BYTE_1_: OutReg = OutReg { offset: 49 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_2_BYTE_2_: OutReg = OutReg { offset: 50 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_2_BYTE_3_: OutReg = OutReg { offset: 51 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_2_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_2_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_2_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_3_BYTE_0_: OutReg = OutReg { offset: 52 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_3_BYTE_1_: OutReg = OutReg { offset: 53 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_3_BYTE_2_: OutReg = OutReg { offset: 54 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_3_BYTE_3_: OutReg = OutReg { offset: 55 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_3_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_3_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_3_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_4_BYTE_0_: OutReg = OutReg { offset: 56 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_4_BYTE_1_: OutReg = OutReg { offset: 57 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_4_BYTE_2_: OutReg = OutReg { offset: 58 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_4_BYTE_3_: OutReg = OutReg { offset: 59 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_4_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_4_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_4_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_5_BYTE_0_: OutReg = OutReg { offset: 60 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_5_BYTE_1_: OutReg = OutReg { offset: 61 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_5_BYTE_2_: OutReg = OutReg { offset: 62 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_5_BYTE_3_: OutReg = OutReg { offset: 63 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_5_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_5_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_5_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_6_BYTE_0_: OutReg = OutReg { offset: 64 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_6_BYTE_1_: OutReg = OutReg { offset: 65 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_6_BYTE_2_: OutReg = OutReg { offset: 66 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_6_BYTE_3_: OutReg = OutReg { offset: 67 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_6_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_6_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_6_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_7_BYTE_0_: OutReg = OutReg { offset: 68 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_7_BYTE_1_: OutReg = OutReg { offset: 69 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_7_BYTE_2_: OutReg = OutReg { offset: 70 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_7_BYTE_3_: OutReg = OutReg { offset: 71 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_7_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_7_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_7_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:26
pub const LAYOUT_MUX_RAM_LOAD_POST: SystemState = SystemState {
    pc: &LAYOUT_MUX_RAM_LOAD_POST_PC,
    image_id: &[
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_0_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_1_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_2_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_3_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_4_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_5_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_6_,
        &LAYOUT_MUX_RAM_LOAD_POST_IMAGE_ID_7_,
    ],
};

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_LOAD_PRE_PC_BYTE_0_: OutReg = OutReg { offset: 0 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_LOAD_PRE_PC_BYTE_1_: OutReg = OutReg { offset: 1 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_LOAD_PRE_PC_BYTE_2_: OutReg = OutReg { offset: 2 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_LOAD_PRE_PC_BYTE_3_: OutReg = OutReg { offset: 3 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RAM_LOAD_PRE_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_PRE_PC_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_PRE_PC_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_PRE_PC_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_PRE_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_0_BYTE_0_: OutReg = OutReg { offset: 4 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_0_BYTE_1_: OutReg = OutReg { offset: 5 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_0_BYTE_2_: OutReg = OutReg { offset: 6 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_0_BYTE_3_: OutReg = OutReg { offset: 7 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_0_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_0_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_0_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_1_BYTE_0_: OutReg = OutReg { offset: 8 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_1_BYTE_1_: OutReg = OutReg { offset: 9 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_1_BYTE_2_: OutReg = OutReg { offset: 10 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_1_BYTE_3_: OutReg = OutReg { offset: 11 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_1_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_1_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_1_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_2_BYTE_0_: OutReg = OutReg { offset: 12 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_2_BYTE_1_: OutReg = OutReg { offset: 13 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_2_BYTE_2_: OutReg = OutReg { offset: 14 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_2_BYTE_3_: OutReg = OutReg { offset: 15 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_2_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_2_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_2_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_3_BYTE_0_: OutReg = OutReg { offset: 16 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_3_BYTE_1_: OutReg = OutReg { offset: 17 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_3_BYTE_2_: OutReg = OutReg { offset: 18 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_3_BYTE_3_: OutReg = OutReg { offset: 19 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_3_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_3_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_3_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_4_BYTE_0_: OutReg = OutReg { offset: 20 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_4_BYTE_1_: OutReg = OutReg { offset: 21 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_4_BYTE_2_: OutReg = OutReg { offset: 22 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_4_BYTE_3_: OutReg = OutReg { offset: 23 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_4_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_4_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_4_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_5_BYTE_0_: OutReg = OutReg { offset: 24 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_5_BYTE_1_: OutReg = OutReg { offset: 25 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_5_BYTE_2_: OutReg = OutReg { offset: 26 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_5_BYTE_3_: OutReg = OutReg { offset: 27 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_5_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_5_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_5_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_6_BYTE_0_: OutReg = OutReg { offset: 28 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_6_BYTE_1_: OutReg = OutReg { offset: 29 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_6_BYTE_2_: OutReg = OutReg { offset: 30 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_6_BYTE_3_: OutReg = OutReg { offset: 31 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_6_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_6_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_6_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_7_BYTE_0_: OutReg = OutReg { offset: 32 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_7_BYTE_1_: OutReg = OutReg { offset: 33 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_7_BYTE_2_: OutReg = OutReg { offset: 34 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_7_BYTE_3_: OutReg = OutReg { offset: 35 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_7_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_7_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_7_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:26
pub const LAYOUT_MUX_RAM_LOAD_PRE: SystemState = SystemState {
    pc: &LAYOUT_MUX_RAM_LOAD_PRE_PC,
    image_id: &[
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_0_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_1_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_2_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_3_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_4_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_5_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_6_,
        &LAYOUT_MUX_RAM_LOAD_PRE_IMAGE_ID_7_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_0_BYTE_0_: OutReg = OutReg { offset: 73 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_0_BYTE_1_: OutReg = OutReg { offset: 74 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_0_BYTE_2_: OutReg = OutReg { offset: 75 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_0_BYTE_3_: OutReg = OutReg { offset: 76 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_0_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_0_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_0_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_1_BYTE_0_: OutReg = OutReg { offset: 77 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_1_BYTE_1_: OutReg = OutReg { offset: 78 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_1_BYTE_2_: OutReg = OutReg { offset: 79 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_1_BYTE_3_: OutReg = OutReg { offset: 80 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_1_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_1_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_1_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_2_BYTE_0_: OutReg = OutReg { offset: 81 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_2_BYTE_1_: OutReg = OutReg { offset: 82 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_2_BYTE_2_: OutReg = OutReg { offset: 83 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_2_BYTE_3_: OutReg = OutReg { offset: 84 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_2_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_2_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_2_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_3_BYTE_0_: OutReg = OutReg { offset: 85 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_3_BYTE_1_: OutReg = OutReg { offset: 86 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_3_BYTE_2_: OutReg = OutReg { offset: 87 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_3_BYTE_3_: OutReg = OutReg { offset: 88 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_3_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_3_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_3_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_4_BYTE_0_: OutReg = OutReg { offset: 89 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_4_BYTE_1_: OutReg = OutReg { offset: 90 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_4_BYTE_2_: OutReg = OutReg { offset: 91 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_4_BYTE_3_: OutReg = OutReg { offset: 92 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_4_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_4_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_4_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_5_BYTE_0_: OutReg = OutReg { offset: 93 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_5_BYTE_1_: OutReg = OutReg { offset: 94 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_5_BYTE_2_: OutReg = OutReg { offset: 95 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_5_BYTE_3_: OutReg = OutReg { offset: 96 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_5_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_5_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_5_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_6_BYTE_0_: OutReg = OutReg { offset: 97 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_6_BYTE_1_: OutReg = OutReg { offset: 98 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_6_BYTE_2_: OutReg = OutReg { offset: 99 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_6_BYTE_3_: OutReg = OutReg { offset: 100 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_6_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_6_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_6_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_7_BYTE_0_: OutReg = OutReg { offset: 101 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_7_BYTE_1_: OutReg = OutReg { offset: 102 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_7_BYTE_2_: OutReg = OutReg { offset: 103 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_7_BYTE_3_: OutReg = OutReg { offset: 104 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RAM_LOAD_OUTPUT_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_7_BYTE_0_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_7_BYTE_1_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_7_BYTE_2_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_7_BYTE_3_,
    ],
};

// :0
pub const LAYOUT_MUX_RAM_LOAD: RamLoadStep = RamLoadStep {
    check_dirty: &LAYOUT_MUX_RAM_LOAD_CHECK_DIRTY,
    post: &LAYOUT_MUX_RAM_LOAD_POST,
    pre: &LAYOUT_MUX_RAM_LOAD_PRE,
    output: &[
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_0_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_1_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_2_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_3_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_4_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_5_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_6_,
        &LAYOUT_MUX_RAM_LOAD_OUTPUT_7_,
    ],
};

// :0
pub const LAYOUT_MUX_RESET_CHECK_DIRTY: OutReg = OutReg { offset: 72 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RESET_POST_PC_BYTE_0_: OutReg = OutReg { offset: 36 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RESET_POST_PC_BYTE_1_: OutReg = OutReg { offset: 37 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RESET_POST_PC_BYTE_2_: OutReg = OutReg { offset: 38 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RESET_POST_PC_BYTE_3_: OutReg = OutReg { offset: 39 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RESET_POST_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_POST_PC_BYTE_0_,
        &LAYOUT_MUX_RESET_POST_PC_BYTE_1_,
        &LAYOUT_MUX_RESET_POST_PC_BYTE_2_,
        &LAYOUT_MUX_RESET_POST_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_0_BYTE_0_: OutReg = OutReg { offset: 40 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_0_BYTE_1_: OutReg = OutReg { offset: 41 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_0_BYTE_2_: OutReg = OutReg { offset: 42 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_0_BYTE_3_: OutReg = OutReg { offset: 43 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_0_BYTE_0_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_0_BYTE_1_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_0_BYTE_2_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_1_BYTE_0_: OutReg = OutReg { offset: 44 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_1_BYTE_1_: OutReg = OutReg { offset: 45 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_1_BYTE_2_: OutReg = OutReg { offset: 46 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_1_BYTE_3_: OutReg = OutReg { offset: 47 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_1_BYTE_0_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_1_BYTE_1_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_1_BYTE_2_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_2_BYTE_0_: OutReg = OutReg { offset: 48 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_2_BYTE_1_: OutReg = OutReg { offset: 49 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_2_BYTE_2_: OutReg = OutReg { offset: 50 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_2_BYTE_3_: OutReg = OutReg { offset: 51 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_2_BYTE_0_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_2_BYTE_1_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_2_BYTE_2_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_3_BYTE_0_: OutReg = OutReg { offset: 52 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_3_BYTE_1_: OutReg = OutReg { offset: 53 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_3_BYTE_2_: OutReg = OutReg { offset: 54 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_3_BYTE_3_: OutReg = OutReg { offset: 55 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_3_BYTE_0_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_3_BYTE_1_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_3_BYTE_2_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_4_BYTE_0_: OutReg = OutReg { offset: 56 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_4_BYTE_1_: OutReg = OutReg { offset: 57 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_4_BYTE_2_: OutReg = OutReg { offset: 58 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_4_BYTE_3_: OutReg = OutReg { offset: 59 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_4_BYTE_0_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_4_BYTE_1_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_4_BYTE_2_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_5_BYTE_0_: OutReg = OutReg { offset: 60 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_5_BYTE_1_: OutReg = OutReg { offset: 61 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_5_BYTE_2_: OutReg = OutReg { offset: 62 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_5_BYTE_3_: OutReg = OutReg { offset: 63 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_5_BYTE_0_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_5_BYTE_1_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_5_BYTE_2_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_6_BYTE_0_: OutReg = OutReg { offset: 64 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_6_BYTE_1_: OutReg = OutReg { offset: 65 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_6_BYTE_2_: OutReg = OutReg { offset: 66 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_6_BYTE_3_: OutReg = OutReg { offset: 67 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_6_BYTE_0_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_6_BYTE_1_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_6_BYTE_2_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_7_BYTE_0_: OutReg = OutReg { offset: 68 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_7_BYTE_1_: OutReg = OutReg { offset: 69 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_7_BYTE_2_: OutReg = OutReg { offset: 70 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_7_BYTE_3_: OutReg = OutReg { offset: 71 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_POST_IMAGE_ID_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_7_BYTE_0_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_7_BYTE_1_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_7_BYTE_2_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:26
pub const LAYOUT_MUX_RESET_POST: SystemState = SystemState {
    pc: &LAYOUT_MUX_RESET_POST_PC,
    image_id: &[
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_0_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_1_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_2_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_3_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_4_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_5_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_6_,
        &LAYOUT_MUX_RESET_POST_IMAGE_ID_7_,
    ],
};

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RESET_PRE_PC_BYTE_0_: OutReg = OutReg { offset: 0 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RESET_PRE_PC_BYTE_1_: OutReg = OutReg { offset: 1 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RESET_PRE_PC_BYTE_2_: OutReg = OutReg { offset: 2 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RESET_PRE_PC_BYTE_3_: OutReg = OutReg { offset: 3 };

// circuit/rv32im/global.h:13
pub const LAYOUT_MUX_RESET_PRE_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_PRE_PC_BYTE_0_,
        &LAYOUT_MUX_RESET_PRE_PC_BYTE_1_,
        &LAYOUT_MUX_RESET_PRE_PC_BYTE_2_,
        &LAYOUT_MUX_RESET_PRE_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_0_BYTE_0_: OutReg = OutReg { offset: 4 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_0_BYTE_1_: OutReg = OutReg { offset: 5 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_0_BYTE_2_: OutReg = OutReg { offset: 6 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_0_BYTE_3_: OutReg = OutReg { offset: 7 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_0_BYTE_0_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_0_BYTE_1_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_0_BYTE_2_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_1_BYTE_0_: OutReg = OutReg { offset: 8 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_1_BYTE_1_: OutReg = OutReg { offset: 9 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_1_BYTE_2_: OutReg = OutReg { offset: 10 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_1_BYTE_3_: OutReg = OutReg { offset: 11 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_1_BYTE_0_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_1_BYTE_1_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_1_BYTE_2_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_2_BYTE_0_: OutReg = OutReg { offset: 12 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_2_BYTE_1_: OutReg = OutReg { offset: 13 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_2_BYTE_2_: OutReg = OutReg { offset: 14 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_2_BYTE_3_: OutReg = OutReg { offset: 15 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_2_BYTE_0_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_2_BYTE_1_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_2_BYTE_2_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_3_BYTE_0_: OutReg = OutReg { offset: 16 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_3_BYTE_1_: OutReg = OutReg { offset: 17 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_3_BYTE_2_: OutReg = OutReg { offset: 18 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_3_BYTE_3_: OutReg = OutReg { offset: 19 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_3_BYTE_0_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_3_BYTE_1_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_3_BYTE_2_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_4_BYTE_0_: OutReg = OutReg { offset: 20 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_4_BYTE_1_: OutReg = OutReg { offset: 21 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_4_BYTE_2_: OutReg = OutReg { offset: 22 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_4_BYTE_3_: OutReg = OutReg { offset: 23 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_4_BYTE_0_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_4_BYTE_1_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_4_BYTE_2_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_5_BYTE_0_: OutReg = OutReg { offset: 24 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_5_BYTE_1_: OutReg = OutReg { offset: 25 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_5_BYTE_2_: OutReg = OutReg { offset: 26 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_5_BYTE_3_: OutReg = OutReg { offset: 27 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_5_BYTE_0_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_5_BYTE_1_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_5_BYTE_2_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_6_BYTE_0_: OutReg = OutReg { offset: 28 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_6_BYTE_1_: OutReg = OutReg { offset: 29 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_6_BYTE_2_: OutReg = OutReg { offset: 30 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_6_BYTE_3_: OutReg = OutReg { offset: 31 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_6_BYTE_0_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_6_BYTE_1_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_6_BYTE_2_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_7_BYTE_0_: OutReg = OutReg { offset: 32 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_7_BYTE_1_: OutReg = OutReg { offset: 33 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_7_BYTE_2_: OutReg = OutReg { offset: 34 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_7_BYTE_3_: OutReg = OutReg { offset: 35 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_RESET_PRE_IMAGE_ID_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_7_BYTE_0_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_7_BYTE_1_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_7_BYTE_2_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:26
pub const LAYOUT_MUX_RESET_PRE: SystemState = SystemState {
    pc: &LAYOUT_MUX_RESET_PRE_PC,
    image_id: &[
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_0_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_1_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_2_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_3_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_4_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_5_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_6_,
        &LAYOUT_MUX_RESET_PRE_IMAGE_ID_7_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_0_BYTE_0_: OutReg = OutReg { offset: 73 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_0_BYTE_1_: OutReg = OutReg { offset: 74 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_0_BYTE_2_: OutReg = OutReg { offset: 75 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_0_BYTE_3_: OutReg = OutReg { offset: 76 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_OUTPUT_0_BYTE_0_,
        &LAYOUT_MUX_RESET_OUTPUT_0_BYTE_1_,
        &LAYOUT_MUX_RESET_OUTPUT_0_BYTE_2_,
        &LAYOUT_MUX_RESET_OUTPUT_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_1_BYTE_0_: OutReg = OutReg { offset: 77 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_1_BYTE_1_: OutReg = OutReg { offset: 78 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_1_BYTE_2_: OutReg = OutReg { offset: 79 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_1_BYTE_3_: OutReg = OutReg { offset: 80 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_OUTPUT_1_BYTE_0_,
        &LAYOUT_MUX_RESET_OUTPUT_1_BYTE_1_,
        &LAYOUT_MUX_RESET_OUTPUT_1_BYTE_2_,
        &LAYOUT_MUX_RESET_OUTPUT_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_2_BYTE_0_: OutReg = OutReg { offset: 81 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_2_BYTE_1_: OutReg = OutReg { offset: 82 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_2_BYTE_2_: OutReg = OutReg { offset: 83 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_2_BYTE_3_: OutReg = OutReg { offset: 84 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_OUTPUT_2_BYTE_0_,
        &LAYOUT_MUX_RESET_OUTPUT_2_BYTE_1_,
        &LAYOUT_MUX_RESET_OUTPUT_2_BYTE_2_,
        &LAYOUT_MUX_RESET_OUTPUT_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_3_BYTE_0_: OutReg = OutReg { offset: 85 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_3_BYTE_1_: OutReg = OutReg { offset: 86 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_3_BYTE_2_: OutReg = OutReg { offset: 87 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_3_BYTE_3_: OutReg = OutReg { offset: 88 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_OUTPUT_3_BYTE_0_,
        &LAYOUT_MUX_RESET_OUTPUT_3_BYTE_1_,
        &LAYOUT_MUX_RESET_OUTPUT_3_BYTE_2_,
        &LAYOUT_MUX_RESET_OUTPUT_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_4_BYTE_0_: OutReg = OutReg { offset: 89 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_4_BYTE_1_: OutReg = OutReg { offset: 90 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_4_BYTE_2_: OutReg = OutReg { offset: 91 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_4_BYTE_3_: OutReg = OutReg { offset: 92 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_OUTPUT_4_BYTE_0_,
        &LAYOUT_MUX_RESET_OUTPUT_4_BYTE_1_,
        &LAYOUT_MUX_RESET_OUTPUT_4_BYTE_2_,
        &LAYOUT_MUX_RESET_OUTPUT_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_5_BYTE_0_: OutReg = OutReg { offset: 93 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_5_BYTE_1_: OutReg = OutReg { offset: 94 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_5_BYTE_2_: OutReg = OutReg { offset: 95 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_5_BYTE_3_: OutReg = OutReg { offset: 96 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_OUTPUT_5_BYTE_0_,
        &LAYOUT_MUX_RESET_OUTPUT_5_BYTE_1_,
        &LAYOUT_MUX_RESET_OUTPUT_5_BYTE_2_,
        &LAYOUT_MUX_RESET_OUTPUT_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_6_BYTE_0_: OutReg = OutReg { offset: 97 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_6_BYTE_1_: OutReg = OutReg { offset: 98 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_6_BYTE_2_: OutReg = OutReg { offset: 99 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_6_BYTE_3_: OutReg = OutReg { offset: 100 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_OUTPUT_6_BYTE_0_,
        &LAYOUT_MUX_RESET_OUTPUT_6_BYTE_1_,
        &LAYOUT_MUX_RESET_OUTPUT_6_BYTE_2_,
        &LAYOUT_MUX_RESET_OUTPUT_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_7_BYTE_0_: OutReg = OutReg { offset: 101 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_7_BYTE_1_: OutReg = OutReg { offset: 102 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_7_BYTE_2_: OutReg = OutReg { offset: 103 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_7_BYTE_3_: OutReg = OutReg { offset: 104 };

// circuit/rv32im/global.h:28
pub const LAYOUT_MUX_RESET_OUTPUT_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_RESET_OUTPUT_7_BYTE_0_,
        &LAYOUT_MUX_RESET_OUTPUT_7_BYTE_1_,
        &LAYOUT_MUX_RESET_OUTPUT_7_BYTE_2_,
        &LAYOUT_MUX_RESET_OUTPUT_7_BYTE_3_,
    ],
};

// :0
pub const LAYOUT_MUX_RESET: RamLoadStep = RamLoadStep {
    check_dirty: &LAYOUT_MUX_RESET_CHECK_DIRTY,
    post: &LAYOUT_MUX_RESET_POST,
    pre: &LAYOUT_MUX_RESET_PRE,
    output: &[
        &LAYOUT_MUX_RESET_OUTPUT_0_,
        &LAYOUT_MUX_RESET_OUTPUT_1_,
        &LAYOUT_MUX_RESET_OUTPUT_2_,
        &LAYOUT_MUX_RESET_OUTPUT_3_,
        &LAYOUT_MUX_RESET_OUTPUT_4_,
        &LAYOUT_MUX_RESET_OUTPUT_5_,
        &LAYOUT_MUX_RESET_OUTPUT_6_,
        &LAYOUT_MUX_RESET_OUTPUT_7_,
    ],
};

// cirgen/circuit/rv32im/top.cpp:60
pub const LAYOUT_MUX: Mux = Mux {
    body: &LAYOUT_MUX_BODY,
    bytes_fini: &LAYOUT_MUX_BYTES_FINI,
    bytes_init: &LAYOUT_MUX_BYTES_INIT,
    bytes_setup: &LAYOUT_MUX_BYTES_SETUP,
    ram_fini: &LAYOUT_MUX_RAM_FINI,
    ram_init: &LAYOUT_MUX_RAM_INIT,
    ram_load: &LAYOUT_MUX_RAM_LOAD,
    reset: &LAYOUT_MUX_RESET,
};

// compiler/edsl/component.h:142
pub const LAYOUT: Top = Top {
    halted: &LAYOUT_HALTED,
    mux: &LAYOUT_MUX,
};
