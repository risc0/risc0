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

// circuit/rv32im/global.h:33
pub struct GlobalDigest {
    pub word: &'static [&'static U32Reg; 8],
}
impl risc0_zkp::layout::Component for GlobalDigest {
    fn ty_name(&self) -> &'static str {
        "GlobalDigest"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("word", self.word)?;
        Ok(())
    }
}

// circuit/rv32im/global.h:35
pub struct SystemState {
    pub image_id: &'static GlobalDigest,
    pub pc: &'static U32Reg,
}
impl risc0_zkp::layout::Component for SystemState {
    fn ty_name(&self) -> &'static str {
        "SystemState"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("image_id", self.image_id)?;
        v.visit_component("pc", self.pc)?;
        Ok(())
    }
}

// zirgen/circuit/rv32im/body.cpp:163
pub struct Global {
    pub sys_exit_code: &'static OutReg,
    pub user_exit_code: &'static OutReg,
    pub input: &'static GlobalDigest,
    pub output: &'static GlobalDigest,
    pub post: &'static SystemState,
    pub pre: &'static SystemState,
}
impl risc0_zkp::layout::Component for Global {
    fn ty_name(&self) -> &'static str {
        "Global"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("sys_exit_code", self.sys_exit_code)?;
        v.visit_component("user_exit_code", self.user_exit_code)?;
        v.visit_component("input", self.input)?;
        v.visit_component("output", self.output)?;
        v.visit_component("post", self.post)?;
        v.visit_component("pre", self.pre)?;
        Ok(())
    }
}

// :0
pub struct BodyStep {
    pub global: &'static Global,
}
impl risc0_zkp::layout::Component for BodyStep {
    fn ty_name(&self) -> &'static str {
        "BodyStep"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("global", self.global)?;
        Ok(())
    }
}

// :0
pub struct BytesFiniStep {}
impl risc0_zkp::layout::Component for BytesFiniStep {
    fn ty_name(&self) -> &'static str {
        "BytesFiniStep"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        Ok(())
    }
}

// zirgen/circuit/rv32im/top.cpp:60
pub struct Mux {
    pub body: &'static BodyStep,
    pub bytes_fini: &'static BytesFiniStep,
    pub bytes_init: &'static BytesFiniStep,
    pub bytes_setup: &'static BytesFiniStep,
    pub ram_fini: &'static BytesFiniStep,
    pub ram_init: &'static BytesFiniStep,
    pub ram_load: &'static BytesFiniStep,
    pub reset: &'static BytesFiniStep,
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

// zirgen/circuit/rv32im/body.cpp:163
pub const LAYOUT_MUX_BODY_GLOBAL_SYS_EXIT_CODE: OutReg = OutReg { offset: 104 };

// zirgen/circuit/rv32im/body.cpp:163
pub const LAYOUT_MUX_BODY_GLOBAL_USER_EXIT_CODE: OutReg = OutReg { offset: 105 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_0_BYTE_0_: OutReg = OutReg { offset: 0 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_0_BYTE_1_: OutReg = OutReg { offset: 1 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_0_BYTE_2_: OutReg = OutReg { offset: 2 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_0_BYTE_3_: OutReg = OutReg { offset: 3 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_0_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_0_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_0_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_1_BYTE_0_: OutReg = OutReg { offset: 4 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_1_BYTE_1_: OutReg = OutReg { offset: 5 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_1_BYTE_2_: OutReg = OutReg { offset: 6 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_1_BYTE_3_: OutReg = OutReg { offset: 7 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_1_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_1_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_1_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_2_BYTE_0_: OutReg = OutReg { offset: 8 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_2_BYTE_1_: OutReg = OutReg { offset: 9 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_2_BYTE_2_: OutReg = OutReg { offset: 10 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_2_BYTE_3_: OutReg = OutReg { offset: 11 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_2_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_2_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_2_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_3_BYTE_0_: OutReg = OutReg { offset: 12 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_3_BYTE_1_: OutReg = OutReg { offset: 13 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_3_BYTE_2_: OutReg = OutReg { offset: 14 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_3_BYTE_3_: OutReg = OutReg { offset: 15 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_3_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_3_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_3_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_4_BYTE_0_: OutReg = OutReg { offset: 16 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_4_BYTE_1_: OutReg = OutReg { offset: 17 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_4_BYTE_2_: OutReg = OutReg { offset: 18 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_4_BYTE_3_: OutReg = OutReg { offset: 19 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_4_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_4_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_4_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_5_BYTE_0_: OutReg = OutReg { offset: 20 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_5_BYTE_1_: OutReg = OutReg { offset: 21 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_5_BYTE_2_: OutReg = OutReg { offset: 22 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_5_BYTE_3_: OutReg = OutReg { offset: 23 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_5_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_5_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_5_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_6_BYTE_0_: OutReg = OutReg { offset: 24 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_6_BYTE_1_: OutReg = OutReg { offset: 25 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_6_BYTE_2_: OutReg = OutReg { offset: 26 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_6_BYTE_3_: OutReg = OutReg { offset: 27 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_6_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_6_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_6_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_7_BYTE_0_: OutReg = OutReg { offset: 28 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_7_BYTE_1_: OutReg = OutReg { offset: 29 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_7_BYTE_2_: OutReg = OutReg { offset: 30 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_7_BYTE_3_: OutReg = OutReg { offset: 31 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_7_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_7_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_7_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:33
pub const LAYOUT_MUX_BODY_GLOBAL_INPUT: GlobalDigest = GlobalDigest {
    word: &[
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_0_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_1_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_2_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_3_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_4_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_5_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_6_,
        &LAYOUT_MUX_BODY_GLOBAL_INPUT_WORD_7_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_0_BYTE_0_: OutReg = OutReg { offset: 106 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_0_BYTE_1_: OutReg = OutReg { offset: 107 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_0_BYTE_2_: OutReg = OutReg { offset: 108 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_0_BYTE_3_: OutReg = OutReg { offset: 109 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_0_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_0_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_0_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_1_BYTE_0_: OutReg = OutReg { offset: 110 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_1_BYTE_1_: OutReg = OutReg { offset: 111 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_1_BYTE_2_: OutReg = OutReg { offset: 112 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_1_BYTE_3_: OutReg = OutReg { offset: 113 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_1_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_1_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_1_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_2_BYTE_0_: OutReg = OutReg { offset: 114 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_2_BYTE_1_: OutReg = OutReg { offset: 115 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_2_BYTE_2_: OutReg = OutReg { offset: 116 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_2_BYTE_3_: OutReg = OutReg { offset: 117 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_2_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_2_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_2_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_3_BYTE_0_: OutReg = OutReg { offset: 118 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_3_BYTE_1_: OutReg = OutReg { offset: 119 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_3_BYTE_2_: OutReg = OutReg { offset: 120 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_3_BYTE_3_: OutReg = OutReg { offset: 121 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_3_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_3_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_3_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_4_BYTE_0_: OutReg = OutReg { offset: 122 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_4_BYTE_1_: OutReg = OutReg { offset: 123 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_4_BYTE_2_: OutReg = OutReg { offset: 124 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_4_BYTE_3_: OutReg = OutReg { offset: 125 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_4_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_4_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_4_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_5_BYTE_0_: OutReg = OutReg { offset: 126 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_5_BYTE_1_: OutReg = OutReg { offset: 127 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_5_BYTE_2_: OutReg = OutReg { offset: 128 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_5_BYTE_3_: OutReg = OutReg { offset: 129 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_5_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_5_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_5_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_6_BYTE_0_: OutReg = OutReg { offset: 130 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_6_BYTE_1_: OutReg = OutReg { offset: 131 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_6_BYTE_2_: OutReg = OutReg { offset: 132 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_6_BYTE_3_: OutReg = OutReg { offset: 133 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_6_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_6_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_6_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_7_BYTE_0_: OutReg = OutReg { offset: 134 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_7_BYTE_1_: OutReg = OutReg { offset: 135 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_7_BYTE_2_: OutReg = OutReg { offset: 136 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_7_BYTE_3_: OutReg = OutReg { offset: 137 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_7_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_7_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_7_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:38
pub const LAYOUT_MUX_BODY_GLOBAL_OUTPUT: GlobalDigest = GlobalDigest {
    word: &[
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_0_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_1_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_2_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_3_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_4_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_5_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_6_,
        &LAYOUT_MUX_BODY_GLOBAL_OUTPUT_WORD_7_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_0_BYTE_0_: OutReg = OutReg { offset: 72 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_0_BYTE_1_: OutReg = OutReg { offset: 73 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_0_BYTE_2_: OutReg = OutReg { offset: 74 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_0_BYTE_3_: OutReg = OutReg { offset: 75 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_0_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_0_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_0_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_1_BYTE_0_: OutReg = OutReg { offset: 76 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_1_BYTE_1_: OutReg = OutReg { offset: 77 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_1_BYTE_2_: OutReg = OutReg { offset: 78 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_1_BYTE_3_: OutReg = OutReg { offset: 79 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_1_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_1_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_1_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_2_BYTE_0_: OutReg = OutReg { offset: 80 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_2_BYTE_1_: OutReg = OutReg { offset: 81 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_2_BYTE_2_: OutReg = OutReg { offset: 82 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_2_BYTE_3_: OutReg = OutReg { offset: 83 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_2_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_2_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_2_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_3_BYTE_0_: OutReg = OutReg { offset: 84 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_3_BYTE_1_: OutReg = OutReg { offset: 85 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_3_BYTE_2_: OutReg = OutReg { offset: 86 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_3_BYTE_3_: OutReg = OutReg { offset: 87 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_3_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_3_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_3_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_4_BYTE_0_: OutReg = OutReg { offset: 88 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_4_BYTE_1_: OutReg = OutReg { offset: 89 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_4_BYTE_2_: OutReg = OutReg { offset: 90 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_4_BYTE_3_: OutReg = OutReg { offset: 91 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_4_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_4_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_4_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_5_BYTE_0_: OutReg = OutReg { offset: 92 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_5_BYTE_1_: OutReg = OutReg { offset: 93 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_5_BYTE_2_: OutReg = OutReg { offset: 94 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_5_BYTE_3_: OutReg = OutReg { offset: 95 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_5_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_5_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_5_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_6_BYTE_0_: OutReg = OutReg { offset: 96 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_6_BYTE_1_: OutReg = OutReg { offset: 97 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_6_BYTE_2_: OutReg = OutReg { offset: 98 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_6_BYTE_3_: OutReg = OutReg { offset: 99 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_6_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_6_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_6_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_7_BYTE_0_: OutReg = OutReg { offset: 100 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_7_BYTE_1_: OutReg = OutReg { offset: 101 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_7_BYTE_2_: OutReg = OutReg { offset: 102 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_7_BYTE_3_: OutReg = OutReg { offset: 103 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_7_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_7_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_7_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID: GlobalDigest = GlobalDigest {
    word: &[
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_0_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_1_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_2_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_3_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_4_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_5_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_6_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID_WORD_7_,
    ],
};

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_POST_PC_BYTE_0_: OutReg = OutReg { offset: 68 };

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_POST_PC_BYTE_1_: OutReg = OutReg { offset: 69 };

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_POST_PC_BYTE_2_: OutReg = OutReg { offset: 70 };

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_POST_PC_BYTE_3_: OutReg = OutReg { offset: 71 };

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_POST_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_POST_PC_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_PC_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_PC_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_POST_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:35
pub const LAYOUT_MUX_BODY_GLOBAL_POST: SystemState = SystemState {
    image_id: &LAYOUT_MUX_BODY_GLOBAL_POST_IMAGE_ID,
    pc: &LAYOUT_MUX_BODY_GLOBAL_POST_PC,
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_0_BYTE_0_: OutReg = OutReg { offset: 36 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_0_BYTE_1_: OutReg = OutReg { offset: 37 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_0_BYTE_2_: OutReg = OutReg { offset: 38 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_0_BYTE_3_: OutReg = OutReg { offset: 39 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_0_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_0_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_0_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_0_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_0_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_1_BYTE_0_: OutReg = OutReg { offset: 40 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_1_BYTE_1_: OutReg = OutReg { offset: 41 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_1_BYTE_2_: OutReg = OutReg { offset: 42 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_1_BYTE_3_: OutReg = OutReg { offset: 43 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_1_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_1_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_1_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_1_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_1_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_2_BYTE_0_: OutReg = OutReg { offset: 44 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_2_BYTE_1_: OutReg = OutReg { offset: 45 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_2_BYTE_2_: OutReg = OutReg { offset: 46 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_2_BYTE_3_: OutReg = OutReg { offset: 47 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_2_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_2_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_2_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_2_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_2_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_3_BYTE_0_: OutReg = OutReg { offset: 48 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_3_BYTE_1_: OutReg = OutReg { offset: 49 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_3_BYTE_2_: OutReg = OutReg { offset: 50 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_3_BYTE_3_: OutReg = OutReg { offset: 51 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_3_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_3_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_3_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_3_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_3_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_4_BYTE_0_: OutReg = OutReg { offset: 52 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_4_BYTE_1_: OutReg = OutReg { offset: 53 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_4_BYTE_2_: OutReg = OutReg { offset: 54 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_4_BYTE_3_: OutReg = OutReg { offset: 55 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_4_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_4_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_4_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_4_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_4_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_5_BYTE_0_: OutReg = OutReg { offset: 56 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_5_BYTE_1_: OutReg = OutReg { offset: 57 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_5_BYTE_2_: OutReg = OutReg { offset: 58 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_5_BYTE_3_: OutReg = OutReg { offset: 59 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_5_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_5_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_5_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_5_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_5_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_6_BYTE_0_: OutReg = OutReg { offset: 60 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_6_BYTE_1_: OutReg = OutReg { offset: 61 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_6_BYTE_2_: OutReg = OutReg { offset: 62 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_6_BYTE_3_: OutReg = OutReg { offset: 63 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_6_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_6_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_6_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_6_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_6_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_7_BYTE_0_: OutReg = OutReg { offset: 64 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_7_BYTE_1_: OutReg = OutReg { offset: 65 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_7_BYTE_2_: OutReg = OutReg { offset: 66 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_7_BYTE_3_: OutReg = OutReg { offset: 67 };

// circuit/rv32im/global.h:15
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_7_: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_7_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_7_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_7_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_7_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID: GlobalDigest = GlobalDigest {
    word: &[
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_0_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_1_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_2_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_3_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_4_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_5_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_6_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID_WORD_7_,
    ],
};

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_PC_BYTE_0_: OutReg = OutReg { offset: 32 };

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_PC_BYTE_1_: OutReg = OutReg { offset: 33 };

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_PC_BYTE_2_: OutReg = OutReg { offset: 34 };

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_PC_BYTE_3_: OutReg = OutReg { offset: 35 };

// circuit/rv32im/global.h:24
pub const LAYOUT_MUX_BODY_GLOBAL_PRE_PC: U32Reg = U32Reg {
    byte: &[
        &LAYOUT_MUX_BODY_GLOBAL_PRE_PC_BYTE_0_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_PC_BYTE_1_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_PC_BYTE_2_,
        &LAYOUT_MUX_BODY_GLOBAL_PRE_PC_BYTE_3_,
    ],
};

// circuit/rv32im/global.h:34
pub const LAYOUT_MUX_BODY_GLOBAL_PRE: SystemState = SystemState {
    image_id: &LAYOUT_MUX_BODY_GLOBAL_PRE_IMAGE_ID,
    pc: &LAYOUT_MUX_BODY_GLOBAL_PRE_PC,
};

// zirgen/circuit/rv32im/body.cpp:163
pub const LAYOUT_MUX_BODY_GLOBAL: Global = Global {
    sys_exit_code: &LAYOUT_MUX_BODY_GLOBAL_SYS_EXIT_CODE,
    user_exit_code: &LAYOUT_MUX_BODY_GLOBAL_USER_EXIT_CODE,
    input: &LAYOUT_MUX_BODY_GLOBAL_INPUT,
    output: &LAYOUT_MUX_BODY_GLOBAL_OUTPUT,
    post: &LAYOUT_MUX_BODY_GLOBAL_POST,
    pre: &LAYOUT_MUX_BODY_GLOBAL_PRE,
};

// :0
pub const LAYOUT_MUX_BODY: BodyStep = BodyStep {
    global: &LAYOUT_MUX_BODY_GLOBAL,
};

// :0
pub const LAYOUT_MUX_BYTES_FINI: BytesFiniStep = BytesFiniStep {};

// :0
pub const LAYOUT_MUX_BYTES_INIT: BytesFiniStep = BytesFiniStep {};

// :0
pub const LAYOUT_MUX_BYTES_SETUP: BytesFiniStep = BytesFiniStep {};

// :0
pub const LAYOUT_MUX_RAM_FINI: BytesFiniStep = BytesFiniStep {};

// :0
pub const LAYOUT_MUX_RAM_INIT: BytesFiniStep = BytesFiniStep {};

// :0
pub const LAYOUT_MUX_RAM_LOAD: BytesFiniStep = BytesFiniStep {};

// :0
pub const LAYOUT_MUX_RESET: BytesFiniStep = BytesFiniStep {};

// zirgen/circuit/rv32im/top.cpp:60
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
