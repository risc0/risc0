pub type Reg4LayoutArray = [&'static Reg; 4];
pub struct MuxLayout {
    pub body: &'static Reg4LayoutArray,
    pub ram_fini: &'static Reg4LayoutArray,
    pub ram_init: &'static Reg4LayoutArray,
    pub ram_load: &'static Reg4LayoutArray,
    pub reset: &'static Reg4LayoutArray,
}
impl risc0_zkp::layout::Component for MuxLayout {
    fn ty_name(&self) -> &'static str {
        "MuxLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("body", self.body)?;
        v.visit_component("ram_fini", self.ram_fini)?;
        v.visit_component("ram_init", self.ram_init)?;
        v.visit_component("ram_load", self.ram_load)?;
        v.visit_component("reset", self.reset)?;
        Ok(())
    }
}
pub const ACCUM_LAYOUT: &MuxLayout = &MuxLayout {
    body: &[
        &Reg { offset: 24 },
        &Reg { offset: 25 },
        &Reg { offset: 26 },
        &Reg { offset: 27 },
    ],
    ram_fini: &[
        &Reg { offset: 24 },
        &Reg { offset: 25 },
        &Reg { offset: 26 },
        &Reg { offset: 27 },
    ],
    ram_init: &[
        &Reg { offset: 24 },
        &Reg { offset: 25 },
        &Reg { offset: 26 },
        &Reg { offset: 27 },
    ],
    ram_load: &[
        &Reg { offset: 24 },
        &Reg { offset: 25 },
        &Reg { offset: 26 },
        &Reg { offset: 27 },
    ],
    reset: &[
        &Reg { offset: 24 },
        &Reg { offset: 25 },
        &Reg { offset: 26 },
        &Reg { offset: 27 },
    ],
};
pub struct RamPlonkElementLayout {
    pub addr: &'static Reg,
    pub cycle: &'static Reg,
    pub mem_op: &'static Reg,
    pub data: &'static Reg4LayoutArray,
}
impl risc0_zkp::layout::Component for RamPlonkElementLayout {
    fn ty_name(&self) -> &'static str {
        "RamPlonkElementLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("addr", self.addr)?;
        v.visit_component("cycle", self.cycle)?;
        v.visit_component("mem_op", self.mem_op)?;
        v.visit_component("data", self.data)?;
        Ok(())
    }
}
pub type Reg3LayoutArray = [&'static Reg; 3];
pub struct RamPlonkVerifierLayout {
    pub dirty: &'static Reg,
    pub extra: &'static Reg,
    pub is_new_addr: &'static Reg,
    pub diff: &'static Reg3LayoutArray,
}
impl risc0_zkp::layout::Component for RamPlonkVerifierLayout {
    fn ty_name(&self) -> &'static str {
        "RamPlonkVerifierLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("dirty", self.dirty)?;
        v.visit_component("extra", self.extra)?;
        v.visit_component("is_new_addr", self.is_new_addr)?;
        v.visit_component("diff", self.diff)?;
        Ok(())
    }
}
pub struct RamHeaderLayout {
    pub element: &'static RamPlonkElementLayout,
    pub verifier: &'static RamPlonkVerifierLayout,
}
impl risc0_zkp::layout::Component for RamHeaderLayout {
    fn ty_name(&self) -> &'static str {
        "RamHeaderLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("element", self.element)?;
        v.visit_component("verifier", self.verifier)?;
        Ok(())
    }
}
pub struct HaltCycleLayout {
    pub sys_exit_code: &'static Reg,
    pub user_exit_code: &'static Reg,
    pub write_addr: &'static Reg,
}
impl risc0_zkp::layout::Component for HaltCycleLayout {
    fn ty_name(&self) -> &'static str {
        "HaltCycleLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("sys_exit_code", self.sys_exit_code)?;
        v.visit_component("user_exit_code", self.user_exit_code)?;
        v.visit_component("write_addr", self.write_addr)?;
        Ok(())
    }
}
pub type Reg16LayoutArray = [&'static Reg; 16];
pub type Reg2LayoutArray = [&'static Reg; 2];
pub struct PcRegLayout {
    pub twits: &'static Reg2LayoutArray,
    pub bytes: &'static Reg3LayoutArray,
}
impl risc0_zkp::layout::Component for PcRegLayout {
    fn ty_name(&self) -> &'static str {
        "PcRegLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("twits", self.twits)?;
        v.visit_component("bytes", self.bytes)?;
        Ok(())
    }
}
pub struct BodyStepLayout {
    pub next_major: &'static Reg,
    pub user_mode: &'static Reg,
    pub header: &'static RamHeaderLayout,
    pub major_mux: &'static HaltCycleLayout,
    pub major_select: &'static Reg16LayoutArray,
    pub pc: &'static PcRegLayout,
}
impl risc0_zkp::layout::Component for BodyStepLayout {
    fn ty_name(&self) -> &'static str {
        "BodyStepLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("next_major", self.next_major)?;
        v.visit_component("user_mode", self.user_mode)?;
        v.visit_component("header", self.header)?;
        v.visit_component("major_mux", self.major_mux)?;
        v.visit_component("major_select", self.major_select)?;
        v.visit_component("pc", self.pc)?;
        Ok(())
    }
}
pub struct Mux0Layout {
    pub body: &'static BodyStepLayout,
    pub ram_fini: &'static RamHeaderLayout,
    pub ram_init: &'static RamHeaderLayout,
    pub ram_load: &'static RamHeaderLayout,
    pub reset: &'static RamHeaderLayout,
}
impl risc0_zkp::layout::Component for Mux0Layout {
    fn ty_name(&self) -> &'static str {
        "Mux0Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("body", self.body)?;
        v.visit_component("ram_fini", self.ram_fini)?;
        v.visit_component("ram_init", self.ram_init)?;
        v.visit_component("ram_load", self.ram_load)?;
        v.visit_component("reset", self.reset)?;
        Ok(())
    }
}
pub struct TopLayout {
    pub halted: &'static Reg,
    pub mux: &'static Mux0Layout,
}
impl risc0_zkp::layout::Component for TopLayout {
    fn ty_name(&self) -> &'static str {
        "TopLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("halted", self.halted)?;
        v.visit_component("mux", self.mux)?;
        Ok(())
    }
}
pub const DATA_LAYOUT: &TopLayout = &TopLayout {
    halted: &Reg { offset: 2 },
    mux: &Mux0Layout {
        body: &BodyStepLayout {
            next_major: &Reg { offset: 100 },
            user_mode: &Reg { offset: 99 },
            header: &RamHeaderLayout {
                element: &RamPlonkElementLayout {
                    addr: &Reg { offset: 89 },
                    cycle: &Reg { offset: 90 },
                    mem_op: &Reg { offset: 91 },
                    data: &[
                        &Reg { offset: 92 },
                        &Reg { offset: 93 },
                        &Reg { offset: 94 },
                        &Reg { offset: 95 },
                    ],
                },
                verifier: &RamPlonkVerifierLayout {
                    dirty: &Reg { offset: 97 },
                    extra: &Reg { offset: 69 },
                    is_new_addr: &Reg { offset: 96 },
                    diff: &[&Reg { offset: 3 }, &Reg { offset: 4 }, &Reg { offset: 5 }],
                },
            },
            major_mux: &HaltCycleLayout {
                sys_exit_code: &Reg { offset: 117 },
                user_exit_code: &Reg { offset: 118 },
                write_addr: &Reg { offset: 119 },
            },
            major_select: &[
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
            ],
            pc: &PcRegLayout {
                twits: &[&Reg { offset: 70 }, &Reg { offset: 71 }],
                bytes: &[&Reg { offset: 6 }, &Reg { offset: 7 }, &Reg { offset: 8 }],
            },
        },
        ram_fini: &RamHeaderLayout {
            element: &RamPlonkElementLayout {
                addr: &Reg { offset: 89 },
                cycle: &Reg { offset: 90 },
                mem_op: &Reg { offset: 91 },
                data: &[
                    &Reg { offset: 92 },
                    &Reg { offset: 93 },
                    &Reg { offset: 94 },
                    &Reg { offset: 95 },
                ],
            },
            verifier: &RamPlonkVerifierLayout {
                dirty: &Reg { offset: 97 },
                extra: &Reg { offset: 69 },
                is_new_addr: &Reg { offset: 96 },
                diff: &[&Reg { offset: 3 }, &Reg { offset: 4 }, &Reg { offset: 5 }],
            },
        },
        ram_init: &RamHeaderLayout {
            element: &RamPlonkElementLayout {
                addr: &Reg { offset: 89 },
                cycle: &Reg { offset: 90 },
                mem_op: &Reg { offset: 91 },
                data: &[
                    &Reg { offset: 92 },
                    &Reg { offset: 93 },
                    &Reg { offset: 94 },
                    &Reg { offset: 95 },
                ],
            },
            verifier: &RamPlonkVerifierLayout {
                dirty: &Reg { offset: 97 },
                extra: &Reg { offset: 69 },
                is_new_addr: &Reg { offset: 96 },
                diff: &[&Reg { offset: 3 }, &Reg { offset: 4 }, &Reg { offset: 5 }],
            },
        },
        ram_load: &RamHeaderLayout {
            element: &RamPlonkElementLayout {
                addr: &Reg { offset: 89 },
                cycle: &Reg { offset: 90 },
                mem_op: &Reg { offset: 91 },
                data: &[
                    &Reg { offset: 92 },
                    &Reg { offset: 93 },
                    &Reg { offset: 94 },
                    &Reg { offset: 95 },
                ],
            },
            verifier: &RamPlonkVerifierLayout {
                dirty: &Reg { offset: 97 },
                extra: &Reg { offset: 69 },
                is_new_addr: &Reg { offset: 96 },
                diff: &[&Reg { offset: 3 }, &Reg { offset: 4 }, &Reg { offset: 5 }],
            },
        },
        reset: &RamHeaderLayout {
            element: &RamPlonkElementLayout {
                addr: &Reg { offset: 89 },
                cycle: &Reg { offset: 90 },
                mem_op: &Reg { offset: 91 },
                data: &[
                    &Reg { offset: 92 },
                    &Reg { offset: 93 },
                    &Reg { offset: 94 },
                    &Reg { offset: 95 },
                ],
            },
            verifier: &RamPlonkVerifierLayout {
                dirty: &Reg { offset: 97 },
                extra: &Reg { offset: 69 },
                is_new_addr: &Reg { offset: 96 },
                diff: &[&Reg { offset: 3 }, &Reg { offset: 4 }, &Reg { offset: 5 }],
            },
        },
    },
};
pub type Reg4LayoutArray7LayoutArray = [&'static Reg4LayoutArray; 7];
pub struct Mux1Layout {
    pub body: &'static Reg4LayoutArray7LayoutArray,
    pub ram_fini: &'static Reg4LayoutArray7LayoutArray,
    pub ram_init: &'static Reg4LayoutArray7LayoutArray,
    pub ram_load: &'static Reg4LayoutArray7LayoutArray,
    pub reset: &'static Reg4LayoutArray7LayoutArray,
}
impl risc0_zkp::layout::Component for Mux1Layout {
    fn ty_name(&self) -> &'static str {
        "Mux1Layout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("body", self.body)?;
        v.visit_component("ram_fini", self.ram_fini)?;
        v.visit_component("ram_init", self.ram_init)?;
        v.visit_component("ram_load", self.ram_load)?;
        v.visit_component("reset", self.reset)?;
        Ok(())
    }
}
pub const MIX_LAYOUT: &Mux1Layout = &Mux1Layout {
    body: &[
        &[
            &Reg { offset: 8 },
            &Reg { offset: 9 },
            &Reg { offset: 10 },
            &Reg { offset: 11 },
        ],
        &[
            &Reg { offset: 12 },
            &Reg { offset: 13 },
            &Reg { offset: 14 },
            &Reg { offset: 15 },
        ],
        &[
            &Reg { offset: 16 },
            &Reg { offset: 17 },
            &Reg { offset: 18 },
            &Reg { offset: 19 },
        ],
        &[
            &Reg { offset: 20 },
            &Reg { offset: 21 },
            &Reg { offset: 22 },
            &Reg { offset: 23 },
        ],
        &[
            &Reg { offset: 24 },
            &Reg { offset: 25 },
            &Reg { offset: 26 },
            &Reg { offset: 27 },
        ],
        &[
            &Reg { offset: 28 },
            &Reg { offset: 29 },
            &Reg { offset: 30 },
            &Reg { offset: 31 },
        ],
        &[
            &Reg { offset: 32 },
            &Reg { offset: 33 },
            &Reg { offset: 34 },
            &Reg { offset: 35 },
        ],
    ],
    ram_fini: &[
        &[
            &Reg { offset: 8 },
            &Reg { offset: 9 },
            &Reg { offset: 10 },
            &Reg { offset: 11 },
        ],
        &[
            &Reg { offset: 12 },
            &Reg { offset: 13 },
            &Reg { offset: 14 },
            &Reg { offset: 15 },
        ],
        &[
            &Reg { offset: 16 },
            &Reg { offset: 17 },
            &Reg { offset: 18 },
            &Reg { offset: 19 },
        ],
        &[
            &Reg { offset: 20 },
            &Reg { offset: 21 },
            &Reg { offset: 22 },
            &Reg { offset: 23 },
        ],
        &[
            &Reg { offset: 24 },
            &Reg { offset: 25 },
            &Reg { offset: 26 },
            &Reg { offset: 27 },
        ],
        &[
            &Reg { offset: 28 },
            &Reg { offset: 29 },
            &Reg { offset: 30 },
            &Reg { offset: 31 },
        ],
        &[
            &Reg { offset: 32 },
            &Reg { offset: 33 },
            &Reg { offset: 34 },
            &Reg { offset: 35 },
        ],
    ],
    ram_init: &[
        &[
            &Reg { offset: 8 },
            &Reg { offset: 9 },
            &Reg { offset: 10 },
            &Reg { offset: 11 },
        ],
        &[
            &Reg { offset: 12 },
            &Reg { offset: 13 },
            &Reg { offset: 14 },
            &Reg { offset: 15 },
        ],
        &[
            &Reg { offset: 16 },
            &Reg { offset: 17 },
            &Reg { offset: 18 },
            &Reg { offset: 19 },
        ],
        &[
            &Reg { offset: 20 },
            &Reg { offset: 21 },
            &Reg { offset: 22 },
            &Reg { offset: 23 },
        ],
        &[
            &Reg { offset: 24 },
            &Reg { offset: 25 },
            &Reg { offset: 26 },
            &Reg { offset: 27 },
        ],
        &[
            &Reg { offset: 28 },
            &Reg { offset: 29 },
            &Reg { offset: 30 },
            &Reg { offset: 31 },
        ],
        &[
            &Reg { offset: 32 },
            &Reg { offset: 33 },
            &Reg { offset: 34 },
            &Reg { offset: 35 },
        ],
    ],
    ram_load: &[
        &[
            &Reg { offset: 8 },
            &Reg { offset: 9 },
            &Reg { offset: 10 },
            &Reg { offset: 11 },
        ],
        &[
            &Reg { offset: 12 },
            &Reg { offset: 13 },
            &Reg { offset: 14 },
            &Reg { offset: 15 },
        ],
        &[
            &Reg { offset: 16 },
            &Reg { offset: 17 },
            &Reg { offset: 18 },
            &Reg { offset: 19 },
        ],
        &[
            &Reg { offset: 20 },
            &Reg { offset: 21 },
            &Reg { offset: 22 },
            &Reg { offset: 23 },
        ],
        &[
            &Reg { offset: 24 },
            &Reg { offset: 25 },
            &Reg { offset: 26 },
            &Reg { offset: 27 },
        ],
        &[
            &Reg { offset: 28 },
            &Reg { offset: 29 },
            &Reg { offset: 30 },
            &Reg { offset: 31 },
        ],
        &[
            &Reg { offset: 32 },
            &Reg { offset: 33 },
            &Reg { offset: 34 },
            &Reg { offset: 35 },
        ],
    ],
    reset: &[
        &[
            &Reg { offset: 8 },
            &Reg { offset: 9 },
            &Reg { offset: 10 },
            &Reg { offset: 11 },
        ],
        &[
            &Reg { offset: 12 },
            &Reg { offset: 13 },
            &Reg { offset: 14 },
            &Reg { offset: 15 },
        ],
        &[
            &Reg { offset: 16 },
            &Reg { offset: 17 },
            &Reg { offset: 18 },
            &Reg { offset: 19 },
        ],
        &[
            &Reg { offset: 20 },
            &Reg { offset: 21 },
            &Reg { offset: 22 },
            &Reg { offset: 23 },
        ],
        &[
            &Reg { offset: 24 },
            &Reg { offset: 25 },
            &Reg { offset: 26 },
            &Reg { offset: 27 },
        ],
        &[
            &Reg { offset: 28 },
            &Reg { offset: 29 },
            &Reg { offset: 30 },
            &Reg { offset: 31 },
        ],
        &[
            &Reg { offset: 32 },
            &Reg { offset: 33 },
            &Reg { offset: 34 },
            &Reg { offset: 35 },
        ],
    ],
};
pub type Reg4LayoutArray8LayoutArray = [&'static Reg4LayoutArray; 8];
pub struct SystemStateLayout {
    pub image_id: &'static Reg4LayoutArray8LayoutArray,
    pub pc: &'static Reg4LayoutArray,
}
impl risc0_zkp::layout::Component for SystemStateLayout {
    fn ty_name(&self) -> &'static str {
        "SystemStateLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("image_id", self.image_id)?;
        v.visit_component("pc", self.pc)?;
        Ok(())
    }
}
pub struct GlobalLayout {
    pub sys_exit_code: &'static Reg,
    pub user_exit_code: &'static Reg,
    pub input: &'static Reg4LayoutArray8LayoutArray,
    pub output: &'static Reg4LayoutArray8LayoutArray,
    pub post: &'static SystemStateLayout,
    pub pre: &'static SystemStateLayout,
}
impl risc0_zkp::layout::Component for GlobalLayout {
    fn ty_name(&self) -> &'static str {
        "GlobalLayout"
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
pub const OUT_LAYOUT: &GlobalLayout = &GlobalLayout {
    sys_exit_code: &Reg { offset: 104 },
    user_exit_code: &Reg { offset: 105 },
    input: &[
        &[
            &Reg { offset: 0 },
            &Reg { offset: 1 },
            &Reg { offset: 2 },
            &Reg { offset: 3 },
        ],
        &[
            &Reg { offset: 4 },
            &Reg { offset: 5 },
            &Reg { offset: 6 },
            &Reg { offset: 7 },
        ],
        &[
            &Reg { offset: 8 },
            &Reg { offset: 9 },
            &Reg { offset: 10 },
            &Reg { offset: 11 },
        ],
        &[
            &Reg { offset: 12 },
            &Reg { offset: 13 },
            &Reg { offset: 14 },
            &Reg { offset: 15 },
        ],
        &[
            &Reg { offset: 16 },
            &Reg { offset: 17 },
            &Reg { offset: 18 },
            &Reg { offset: 19 },
        ],
        &[
            &Reg { offset: 20 },
            &Reg { offset: 21 },
            &Reg { offset: 22 },
            &Reg { offset: 23 },
        ],
        &[
            &Reg { offset: 24 },
            &Reg { offset: 25 },
            &Reg { offset: 26 },
            &Reg { offset: 27 },
        ],
        &[
            &Reg { offset: 28 },
            &Reg { offset: 29 },
            &Reg { offset: 30 },
            &Reg { offset: 31 },
        ],
    ],
    output: &[
        &[
            &Reg { offset: 106 },
            &Reg { offset: 107 },
            &Reg { offset: 108 },
            &Reg { offset: 109 },
        ],
        &[
            &Reg { offset: 110 },
            &Reg { offset: 111 },
            &Reg { offset: 112 },
            &Reg { offset: 113 },
        ],
        &[
            &Reg { offset: 114 },
            &Reg { offset: 115 },
            &Reg { offset: 116 },
            &Reg { offset: 117 },
        ],
        &[
            &Reg { offset: 118 },
            &Reg { offset: 119 },
            &Reg { offset: 120 },
            &Reg { offset: 121 },
        ],
        &[
            &Reg { offset: 122 },
            &Reg { offset: 123 },
            &Reg { offset: 124 },
            &Reg { offset: 125 },
        ],
        &[
            &Reg { offset: 126 },
            &Reg { offset: 127 },
            &Reg { offset: 128 },
            &Reg { offset: 129 },
        ],
        &[
            &Reg { offset: 130 },
            &Reg { offset: 131 },
            &Reg { offset: 132 },
            &Reg { offset: 133 },
        ],
        &[
            &Reg { offset: 134 },
            &Reg { offset: 135 },
            &Reg { offset: 136 },
            &Reg { offset: 137 },
        ],
    ],
    post: &SystemStateLayout {
        image_id: &[
            &[
                &Reg { offset: 72 },
                &Reg { offset: 73 },
                &Reg { offset: 74 },
                &Reg { offset: 75 },
            ],
            &[
                &Reg { offset: 76 },
                &Reg { offset: 77 },
                &Reg { offset: 78 },
                &Reg { offset: 79 },
            ],
            &[
                &Reg { offset: 80 },
                &Reg { offset: 81 },
                &Reg { offset: 82 },
                &Reg { offset: 83 },
            ],
            &[
                &Reg { offset: 84 },
                &Reg { offset: 85 },
                &Reg { offset: 86 },
                &Reg { offset: 87 },
            ],
            &[
                &Reg { offset: 88 },
                &Reg { offset: 89 },
                &Reg { offset: 90 },
                &Reg { offset: 91 },
            ],
            &[
                &Reg { offset: 92 },
                &Reg { offset: 93 },
                &Reg { offset: 94 },
                &Reg { offset: 95 },
            ],
            &[
                &Reg { offset: 96 },
                &Reg { offset: 97 },
                &Reg { offset: 98 },
                &Reg { offset: 99 },
            ],
            &[
                &Reg { offset: 100 },
                &Reg { offset: 101 },
                &Reg { offset: 102 },
                &Reg { offset: 103 },
            ],
        ],
        pc: &[
            &Reg { offset: 68 },
            &Reg { offset: 69 },
            &Reg { offset: 70 },
            &Reg { offset: 71 },
        ],
    },
    pre: &SystemStateLayout {
        image_id: &[
            &[
                &Reg { offset: 36 },
                &Reg { offset: 37 },
                &Reg { offset: 38 },
                &Reg { offset: 39 },
            ],
            &[
                &Reg { offset: 40 },
                &Reg { offset: 41 },
                &Reg { offset: 42 },
                &Reg { offset: 43 },
            ],
            &[
                &Reg { offset: 44 },
                &Reg { offset: 45 },
                &Reg { offset: 46 },
                &Reg { offset: 47 },
            ],
            &[
                &Reg { offset: 48 },
                &Reg { offset: 49 },
                &Reg { offset: 50 },
                &Reg { offset: 51 },
            ],
            &[
                &Reg { offset: 52 },
                &Reg { offset: 53 },
                &Reg { offset: 54 },
                &Reg { offset: 55 },
            ],
            &[
                &Reg { offset: 56 },
                &Reg { offset: 57 },
                &Reg { offset: 58 },
                &Reg { offset: 59 },
            ],
            &[
                &Reg { offset: 60 },
                &Reg { offset: 61 },
                &Reg { offset: 62 },
                &Reg { offset: 63 },
            ],
            &[
                &Reg { offset: 64 },
                &Reg { offset: 65 },
                &Reg { offset: 66 },
                &Reg { offset: 67 },
            ],
        ],
        pc: &[
            &Reg { offset: 32 },
            &Reg { offset: 33 },
            &Reg { offset: 34 },
            &Reg { offset: 35 },
        ],
    },
};
