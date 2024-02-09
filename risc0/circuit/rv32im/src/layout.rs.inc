pub type OutReg4LayoutArray = [&'static OutReg; 4];
pub struct U32Reg {
    pub byte: &'static OutReg4LayoutArray,
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
pub type U32Reg8LayoutArray = [&'static U32Reg; 8];
pub struct GlobalDigest {
    pub word: &'static U32Reg8LayoutArray,
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
pub const LAYOUT: &Top = &Top {
    halted: &DataReg { offset: 2 },
    mux: &Mux {
        body: &BodyStep {
            global: &Global {
                sys_exit_code: &OutReg { offset: 104 },
                user_exit_code: &OutReg { offset: 105 },
                input: &GlobalDigest {
                    word: &[
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 0 },
                                &OutReg { offset: 1 },
                                &OutReg { offset: 2 },
                                &OutReg { offset: 3 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 4 },
                                &OutReg { offset: 5 },
                                &OutReg { offset: 6 },
                                &OutReg { offset: 7 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 8 },
                                &OutReg { offset: 9 },
                                &OutReg { offset: 10 },
                                &OutReg { offset: 11 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 12 },
                                &OutReg { offset: 13 },
                                &OutReg { offset: 14 },
                                &OutReg { offset: 15 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 16 },
                                &OutReg { offset: 17 },
                                &OutReg { offset: 18 },
                                &OutReg { offset: 19 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 20 },
                                &OutReg { offset: 21 },
                                &OutReg { offset: 22 },
                                &OutReg { offset: 23 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 24 },
                                &OutReg { offset: 25 },
                                &OutReg { offset: 26 },
                                &OutReg { offset: 27 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 28 },
                                &OutReg { offset: 29 },
                                &OutReg { offset: 30 },
                                &OutReg { offset: 31 },
                            ],
                        },
                    ],
                },
                output: &GlobalDigest {
                    word: &[
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 106 },
                                &OutReg { offset: 107 },
                                &OutReg { offset: 108 },
                                &OutReg { offset: 109 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 110 },
                                &OutReg { offset: 111 },
                                &OutReg { offset: 112 },
                                &OutReg { offset: 113 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 114 },
                                &OutReg { offset: 115 },
                                &OutReg { offset: 116 },
                                &OutReg { offset: 117 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 118 },
                                &OutReg { offset: 119 },
                                &OutReg { offset: 120 },
                                &OutReg { offset: 121 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 122 },
                                &OutReg { offset: 123 },
                                &OutReg { offset: 124 },
                                &OutReg { offset: 125 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 126 },
                                &OutReg { offset: 127 },
                                &OutReg { offset: 128 },
                                &OutReg { offset: 129 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 130 },
                                &OutReg { offset: 131 },
                                &OutReg { offset: 132 },
                                &OutReg { offset: 133 },
                            ],
                        },
                        &U32Reg {
                            byte: &[
                                &OutReg { offset: 134 },
                                &OutReg { offset: 135 },
                                &OutReg { offset: 136 },
                                &OutReg { offset: 137 },
                            ],
                        },
                    ],
                },
                post: &SystemState {
                    image_id: &GlobalDigest {
                        word: &[
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 72 },
                                    &OutReg { offset: 73 },
                                    &OutReg { offset: 74 },
                                    &OutReg { offset: 75 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 76 },
                                    &OutReg { offset: 77 },
                                    &OutReg { offset: 78 },
                                    &OutReg { offset: 79 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 80 },
                                    &OutReg { offset: 81 },
                                    &OutReg { offset: 82 },
                                    &OutReg { offset: 83 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 84 },
                                    &OutReg { offset: 85 },
                                    &OutReg { offset: 86 },
                                    &OutReg { offset: 87 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 88 },
                                    &OutReg { offset: 89 },
                                    &OutReg { offset: 90 },
                                    &OutReg { offset: 91 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 92 },
                                    &OutReg { offset: 93 },
                                    &OutReg { offset: 94 },
                                    &OutReg { offset: 95 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 96 },
                                    &OutReg { offset: 97 },
                                    &OutReg { offset: 98 },
                                    &OutReg { offset: 99 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 100 },
                                    &OutReg { offset: 101 },
                                    &OutReg { offset: 102 },
                                    &OutReg { offset: 103 },
                                ],
                            },
                        ],
                    },
                    pc: &U32Reg {
                        byte: &[
                            &OutReg { offset: 68 },
                            &OutReg { offset: 69 },
                            &OutReg { offset: 70 },
                            &OutReg { offset: 71 },
                        ],
                    },
                },
                pre: &SystemState {
                    image_id: &GlobalDigest {
                        word: &[
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 36 },
                                    &OutReg { offset: 37 },
                                    &OutReg { offset: 38 },
                                    &OutReg { offset: 39 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 40 },
                                    &OutReg { offset: 41 },
                                    &OutReg { offset: 42 },
                                    &OutReg { offset: 43 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 44 },
                                    &OutReg { offset: 45 },
                                    &OutReg { offset: 46 },
                                    &OutReg { offset: 47 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 48 },
                                    &OutReg { offset: 49 },
                                    &OutReg { offset: 50 },
                                    &OutReg { offset: 51 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 52 },
                                    &OutReg { offset: 53 },
                                    &OutReg { offset: 54 },
                                    &OutReg { offset: 55 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 56 },
                                    &OutReg { offset: 57 },
                                    &OutReg { offset: 58 },
                                    &OutReg { offset: 59 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 60 },
                                    &OutReg { offset: 61 },
                                    &OutReg { offset: 62 },
                                    &OutReg { offset: 63 },
                                ],
                            },
                            &U32Reg {
                                byte: &[
                                    &OutReg { offset: 64 },
                                    &OutReg { offset: 65 },
                                    &OutReg { offset: 66 },
                                    &OutReg { offset: 67 },
                                ],
                            },
                        ],
                    },
                    pc: &U32Reg {
                        byte: &[
                            &OutReg { offset: 32 },
                            &OutReg { offset: 33 },
                            &OutReg { offset: 34 },
                            &OutReg { offset: 35 },
                        ],
                    },
                },
            },
        },
        bytes_fini: &BytesFiniStep {},
        bytes_init: &BytesFiniStep {},
        bytes_setup: &BytesFiniStep {},
        ram_fini: &BytesFiniStep {},
        ram_init: &BytesFiniStep {},
        ram_load: &BytesFiniStep {},
        reset: &BytesFiniStep {},
    },
};
