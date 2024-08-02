pub type OutReg4LayoutArray = [&'static OutReg; 4];
pub type OutReg4LayoutArray8LayoutArray = [&'static OutReg4LayoutArray; 8];
pub struct SystemState {
    pub image_id: &'static OutReg4LayoutArray8LayoutArray,
    pub pc: &'static OutReg4LayoutArray,
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
    pub input: &'static OutReg4LayoutArray8LayoutArray,
    pub output: &'static OutReg4LayoutArray8LayoutArray,
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
pub type AccumReg4LayoutArray = [&'static AccumReg; 4];
pub type DataReg4LayoutArray = [&'static DataReg; 4];
pub struct RamPlonkElement {
    pub addr: &'static DataReg,
    pub cycle: &'static DataReg,
    pub mem_op: &'static DataReg,
    pub data: &'static DataReg4LayoutArray,
}
impl risc0_zkp::layout::Component for RamPlonkElement {
    fn ty_name(&self) -> &'static str {
        "RamPlonkElement"
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
pub type DataReg3LayoutArray = [&'static DataReg; 3];
pub struct RamPlonkVerifier {
    pub dirty: &'static DataReg,
    pub extra: &'static DataReg,
    pub is_new_addr: &'static DataReg,
    pub diff: &'static DataReg3LayoutArray,
}
impl risc0_zkp::layout::Component for RamPlonkVerifier {
    fn ty_name(&self) -> &'static str {
        "RamPlonkVerifier"
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
pub type MixReg4LayoutArray = [&'static MixReg; 4];
pub type MixReg4LayoutArray7LayoutArray = [&'static MixReg4LayoutArray; 7];
pub struct RamHeader {
    pub accum: &'static AccumReg4LayoutArray,
    pub element: &'static RamPlonkElement,
    pub verifier: &'static RamPlonkVerifier,
    pub mix: &'static MixReg4LayoutArray7LayoutArray,
}
impl risc0_zkp::layout::Component for RamHeader {
    fn ty_name(&self) -> &'static str {
        "RamHeader"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("accum", self.accum)?;
        v.visit_component("element", self.element)?;
        v.visit_component("verifier", self.verifier)?;
        v.visit_component("mix", self.mix)?;
        Ok(())
    }
}
pub struct HaltCycle {
    pub sys_exit_code: &'static DataReg,
    pub user_exit_code: &'static DataReg,
    pub write_addr: &'static DataReg,
}
impl risc0_zkp::layout::Component for HaltCycle {
    fn ty_name(&self) -> &'static str {
        "HaltCycle"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("sys_exit_code", self.sys_exit_code)?;
        v.visit_component("user_exit_code", self.user_exit_code)?;
        v.visit_component("write_addr", self.write_addr)?;
        Ok(())
    }
}
pub type DataReg16LayoutArray = [&'static DataReg; 16];
pub type DataReg2LayoutArray = [&'static DataReg; 2];
pub struct PcReg {
    pub twits: &'static DataReg2LayoutArray,
    pub bytes: &'static DataReg3LayoutArray,
}
impl risc0_zkp::layout::Component for PcReg {
    fn ty_name(&self) -> &'static str {
        "PcReg"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("twits", self.twits)?;
        v.visit_component("bytes", self.bytes)?;
        Ok(())
    }
}
pub struct BodyStep {
    pub next_major: &'static DataReg,
    pub user_mode: &'static DataReg,
    pub global: &'static Global,
    pub header: &'static RamHeader,
    pub major_mux: &'static HaltCycle,
    pub major_select: &'static DataReg16LayoutArray,
    pub pc: &'static PcReg,
}
impl risc0_zkp::layout::Component for BodyStep {
    fn ty_name(&self) -> &'static str {
        "BodyStep"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("next_major", self.next_major)?;
        v.visit_component("user_mode", self.user_mode)?;
        v.visit_component("global", self.global)?;
        v.visit_component("header", self.header)?;
        v.visit_component("major_mux", self.major_mux)?;
        v.visit_component("major_select", self.major_select)?;
        v.visit_component("pc", self.pc)?;
        Ok(())
    }
}
pub struct Mux {
    pub body: &'static BodyStep,
    pub ram_fini: &'static RamHeader,
    pub ram_init: &'static RamHeader,
    pub ram_load: &'static RamHeader,
    pub reset: &'static RamHeader,
}
impl risc0_zkp::layout::Component for Mux {
    fn ty_name(&self) -> &'static str {
        "Mux"
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
            next_major: &DataReg { offset: 100 },
            user_mode: &DataReg { offset: 99 },
            global: &Global {
                sys_exit_code: &OutReg { offset: 104 },
                user_exit_code: &OutReg { offset: 105 },
                input: &[
                    &[
                        &OutReg { offset: 0 },
                        &OutReg { offset: 1 },
                        &OutReg { offset: 2 },
                        &OutReg { offset: 3 },
                    ],
                    &[
                        &OutReg { offset: 4 },
                        &OutReg { offset: 5 },
                        &OutReg { offset: 6 },
                        &OutReg { offset: 7 },
                    ],
                    &[
                        &OutReg { offset: 8 },
                        &OutReg { offset: 9 },
                        &OutReg { offset: 10 },
                        &OutReg { offset: 11 },
                    ],
                    &[
                        &OutReg { offset: 12 },
                        &OutReg { offset: 13 },
                        &OutReg { offset: 14 },
                        &OutReg { offset: 15 },
                    ],
                    &[
                        &OutReg { offset: 16 },
                        &OutReg { offset: 17 },
                        &OutReg { offset: 18 },
                        &OutReg { offset: 19 },
                    ],
                    &[
                        &OutReg { offset: 20 },
                        &OutReg { offset: 21 },
                        &OutReg { offset: 22 },
                        &OutReg { offset: 23 },
                    ],
                    &[
                        &OutReg { offset: 24 },
                        &OutReg { offset: 25 },
                        &OutReg { offset: 26 },
                        &OutReg { offset: 27 },
                    ],
                    &[
                        &OutReg { offset: 28 },
                        &OutReg { offset: 29 },
                        &OutReg { offset: 30 },
                        &OutReg { offset: 31 },
                    ],
                ],
                output: &[
                    &[
                        &OutReg { offset: 106 },
                        &OutReg { offset: 107 },
                        &OutReg { offset: 108 },
                        &OutReg { offset: 109 },
                    ],
                    &[
                        &OutReg { offset: 110 },
                        &OutReg { offset: 111 },
                        &OutReg { offset: 112 },
                        &OutReg { offset: 113 },
                    ],
                    &[
                        &OutReg { offset: 114 },
                        &OutReg { offset: 115 },
                        &OutReg { offset: 116 },
                        &OutReg { offset: 117 },
                    ],
                    &[
                        &OutReg { offset: 118 },
                        &OutReg { offset: 119 },
                        &OutReg { offset: 120 },
                        &OutReg { offset: 121 },
                    ],
                    &[
                        &OutReg { offset: 122 },
                        &OutReg { offset: 123 },
                        &OutReg { offset: 124 },
                        &OutReg { offset: 125 },
                    ],
                    &[
                        &OutReg { offset: 126 },
                        &OutReg { offset: 127 },
                        &OutReg { offset: 128 },
                        &OutReg { offset: 129 },
                    ],
                    &[
                        &OutReg { offset: 130 },
                        &OutReg { offset: 131 },
                        &OutReg { offset: 132 },
                        &OutReg { offset: 133 },
                    ],
                    &[
                        &OutReg { offset: 134 },
                        &OutReg { offset: 135 },
                        &OutReg { offset: 136 },
                        &OutReg { offset: 137 },
                    ],
                ],
                post: &SystemState {
                    image_id: &[
                        &[
                            &OutReg { offset: 72 },
                            &OutReg { offset: 73 },
                            &OutReg { offset: 74 },
                            &OutReg { offset: 75 },
                        ],
                        &[
                            &OutReg { offset: 76 },
                            &OutReg { offset: 77 },
                            &OutReg { offset: 78 },
                            &OutReg { offset: 79 },
                        ],
                        &[
                            &OutReg { offset: 80 },
                            &OutReg { offset: 81 },
                            &OutReg { offset: 82 },
                            &OutReg { offset: 83 },
                        ],
                        &[
                            &OutReg { offset: 84 },
                            &OutReg { offset: 85 },
                            &OutReg { offset: 86 },
                            &OutReg { offset: 87 },
                        ],
                        &[
                            &OutReg { offset: 88 },
                            &OutReg { offset: 89 },
                            &OutReg { offset: 90 },
                            &OutReg { offset: 91 },
                        ],
                        &[
                            &OutReg { offset: 92 },
                            &OutReg { offset: 93 },
                            &OutReg { offset: 94 },
                            &OutReg { offset: 95 },
                        ],
                        &[
                            &OutReg { offset: 96 },
                            &OutReg { offset: 97 },
                            &OutReg { offset: 98 },
                            &OutReg { offset: 99 },
                        ],
                        &[
                            &OutReg { offset: 100 },
                            &OutReg { offset: 101 },
                            &OutReg { offset: 102 },
                            &OutReg { offset: 103 },
                        ],
                    ],
                    pc: &[
                        &OutReg { offset: 68 },
                        &OutReg { offset: 69 },
                        &OutReg { offset: 70 },
                        &OutReg { offset: 71 },
                    ],
                },
                pre: &SystemState {
                    image_id: &[
                        &[
                            &OutReg { offset: 36 },
                            &OutReg { offset: 37 },
                            &OutReg { offset: 38 },
                            &OutReg { offset: 39 },
                        ],
                        &[
                            &OutReg { offset: 40 },
                            &OutReg { offset: 41 },
                            &OutReg { offset: 42 },
                            &OutReg { offset: 43 },
                        ],
                        &[
                            &OutReg { offset: 44 },
                            &OutReg { offset: 45 },
                            &OutReg { offset: 46 },
                            &OutReg { offset: 47 },
                        ],
                        &[
                            &OutReg { offset: 48 },
                            &OutReg { offset: 49 },
                            &OutReg { offset: 50 },
                            &OutReg { offset: 51 },
                        ],
                        &[
                            &OutReg { offset: 52 },
                            &OutReg { offset: 53 },
                            &OutReg { offset: 54 },
                            &OutReg { offset: 55 },
                        ],
                        &[
                            &OutReg { offset: 56 },
                            &OutReg { offset: 57 },
                            &OutReg { offset: 58 },
                            &OutReg { offset: 59 },
                        ],
                        &[
                            &OutReg { offset: 60 },
                            &OutReg { offset: 61 },
                            &OutReg { offset: 62 },
                            &OutReg { offset: 63 },
                        ],
                        &[
                            &OutReg { offset: 64 },
                            &OutReg { offset: 65 },
                            &OutReg { offset: 66 },
                            &OutReg { offset: 67 },
                        ],
                    ],
                    pc: &[
                        &OutReg { offset: 32 },
                        &OutReg { offset: 33 },
                        &OutReg { offset: 34 },
                        &OutReg { offset: 35 },
                    ],
                },
            },
            header: &RamHeader {
                accum: &[
                    &AccumReg { offset: 24 },
                    &AccumReg { offset: 25 },
                    &AccumReg { offset: 26 },
                    &AccumReg { offset: 27 },
                ],
                element: &RamPlonkElement {
                    addr: &DataReg { offset: 89 },
                    cycle: &DataReg { offset: 90 },
                    mem_op: &DataReg { offset: 91 },
                    data: &[
                        &DataReg { offset: 92 },
                        &DataReg { offset: 93 },
                        &DataReg { offset: 94 },
                        &DataReg { offset: 95 },
                    ],
                },
                verifier: &RamPlonkVerifier {
                    dirty: &DataReg { offset: 97 },
                    extra: &DataReg { offset: 69 },
                    is_new_addr: &DataReg { offset: 96 },
                    diff: &[
                        &DataReg { offset: 3 },
                        &DataReg { offset: 4 },
                        &DataReg { offset: 5 },
                    ],
                },
                mix: &[
                    &[
                        &MixReg { offset: 8 },
                        &MixReg { offset: 9 },
                        &MixReg { offset: 10 },
                        &MixReg { offset: 11 },
                    ],
                    &[
                        &MixReg { offset: 12 },
                        &MixReg { offset: 13 },
                        &MixReg { offset: 14 },
                        &MixReg { offset: 15 },
                    ],
                    &[
                        &MixReg { offset: 16 },
                        &MixReg { offset: 17 },
                        &MixReg { offset: 18 },
                        &MixReg { offset: 19 },
                    ],
                    &[
                        &MixReg { offset: 20 },
                        &MixReg { offset: 21 },
                        &MixReg { offset: 22 },
                        &MixReg { offset: 23 },
                    ],
                    &[
                        &MixReg { offset: 24 },
                        &MixReg { offset: 25 },
                        &MixReg { offset: 26 },
                        &MixReg { offset: 27 },
                    ],
                    &[
                        &MixReg { offset: 28 },
                        &MixReg { offset: 29 },
                        &MixReg { offset: 30 },
                        &MixReg { offset: 31 },
                    ],
                    &[
                        &MixReg { offset: 32 },
                        &MixReg { offset: 33 },
                        &MixReg { offset: 34 },
                        &MixReg { offset: 35 },
                    ],
                ],
            },
            major_mux: &HaltCycle {
                sys_exit_code: &DataReg { offset: 117 },
                user_exit_code: &DataReg { offset: 118 },
                write_addr: &DataReg { offset: 119 },
            },
            major_select: &[
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
            ],
            pc: &PcReg {
                twits: &[&DataReg { offset: 70 }, &DataReg { offset: 71 }],
                bytes: &[
                    &DataReg { offset: 6 },
                    &DataReg { offset: 7 },
                    &DataReg { offset: 8 },
                ],
            },
        },
        ram_fini: &RamHeader {
            accum: &[
                &AccumReg { offset: 24 },
                &AccumReg { offset: 25 },
                &AccumReg { offset: 26 },
                &AccumReg { offset: 27 },
            ],
            element: &RamPlonkElement {
                addr: &DataReg { offset: 89 },
                cycle: &DataReg { offset: 90 },
                mem_op: &DataReg { offset: 91 },
                data: &[
                    &DataReg { offset: 92 },
                    &DataReg { offset: 93 },
                    &DataReg { offset: 94 },
                    &DataReg { offset: 95 },
                ],
            },
            verifier: &RamPlonkVerifier {
                dirty: &DataReg { offset: 97 },
                extra: &DataReg { offset: 69 },
                is_new_addr: &DataReg { offset: 96 },
                diff: &[
                    &DataReg { offset: 3 },
                    &DataReg { offset: 4 },
                    &DataReg { offset: 5 },
                ],
            },
            mix: &[
                &[
                    &MixReg { offset: 8 },
                    &MixReg { offset: 9 },
                    &MixReg { offset: 10 },
                    &MixReg { offset: 11 },
                ],
                &[
                    &MixReg { offset: 12 },
                    &MixReg { offset: 13 },
                    &MixReg { offset: 14 },
                    &MixReg { offset: 15 },
                ],
                &[
                    &MixReg { offset: 16 },
                    &MixReg { offset: 17 },
                    &MixReg { offset: 18 },
                    &MixReg { offset: 19 },
                ],
                &[
                    &MixReg { offset: 20 },
                    &MixReg { offset: 21 },
                    &MixReg { offset: 22 },
                    &MixReg { offset: 23 },
                ],
                &[
                    &MixReg { offset: 24 },
                    &MixReg { offset: 25 },
                    &MixReg { offset: 26 },
                    &MixReg { offset: 27 },
                ],
                &[
                    &MixReg { offset: 28 },
                    &MixReg { offset: 29 },
                    &MixReg { offset: 30 },
                    &MixReg { offset: 31 },
                ],
                &[
                    &MixReg { offset: 32 },
                    &MixReg { offset: 33 },
                    &MixReg { offset: 34 },
                    &MixReg { offset: 35 },
                ],
            ],
        },
        ram_init: &RamHeader {
            accum: &[
                &AccumReg { offset: 24 },
                &AccumReg { offset: 25 },
                &AccumReg { offset: 26 },
                &AccumReg { offset: 27 },
            ],
            element: &RamPlonkElement {
                addr: &DataReg { offset: 89 },
                cycle: &DataReg { offset: 90 },
                mem_op: &DataReg { offset: 91 },
                data: &[
                    &DataReg { offset: 92 },
                    &DataReg { offset: 93 },
                    &DataReg { offset: 94 },
                    &DataReg { offset: 95 },
                ],
            },
            verifier: &RamPlonkVerifier {
                dirty: &DataReg { offset: 97 },
                extra: &DataReg { offset: 69 },
                is_new_addr: &DataReg { offset: 96 },
                diff: &[
                    &DataReg { offset: 3 },
                    &DataReg { offset: 4 },
                    &DataReg { offset: 5 },
                ],
            },
            mix: &[
                &[
                    &MixReg { offset: 8 },
                    &MixReg { offset: 9 },
                    &MixReg { offset: 10 },
                    &MixReg { offset: 11 },
                ],
                &[
                    &MixReg { offset: 12 },
                    &MixReg { offset: 13 },
                    &MixReg { offset: 14 },
                    &MixReg { offset: 15 },
                ],
                &[
                    &MixReg { offset: 16 },
                    &MixReg { offset: 17 },
                    &MixReg { offset: 18 },
                    &MixReg { offset: 19 },
                ],
                &[
                    &MixReg { offset: 20 },
                    &MixReg { offset: 21 },
                    &MixReg { offset: 22 },
                    &MixReg { offset: 23 },
                ],
                &[
                    &MixReg { offset: 24 },
                    &MixReg { offset: 25 },
                    &MixReg { offset: 26 },
                    &MixReg { offset: 27 },
                ],
                &[
                    &MixReg { offset: 28 },
                    &MixReg { offset: 29 },
                    &MixReg { offset: 30 },
                    &MixReg { offset: 31 },
                ],
                &[
                    &MixReg { offset: 32 },
                    &MixReg { offset: 33 },
                    &MixReg { offset: 34 },
                    &MixReg { offset: 35 },
                ],
            ],
        },
        ram_load: &RamHeader {
            accum: &[
                &AccumReg { offset: 24 },
                &AccumReg { offset: 25 },
                &AccumReg { offset: 26 },
                &AccumReg { offset: 27 },
            ],
            element: &RamPlonkElement {
                addr: &DataReg { offset: 89 },
                cycle: &DataReg { offset: 90 },
                mem_op: &DataReg { offset: 91 },
                data: &[
                    &DataReg { offset: 92 },
                    &DataReg { offset: 93 },
                    &DataReg { offset: 94 },
                    &DataReg { offset: 95 },
                ],
            },
            verifier: &RamPlonkVerifier {
                dirty: &DataReg { offset: 97 },
                extra: &DataReg { offset: 69 },
                is_new_addr: &DataReg { offset: 96 },
                diff: &[
                    &DataReg { offset: 3 },
                    &DataReg { offset: 4 },
                    &DataReg { offset: 5 },
                ],
            },
            mix: &[
                &[
                    &MixReg { offset: 8 },
                    &MixReg { offset: 9 },
                    &MixReg { offset: 10 },
                    &MixReg { offset: 11 },
                ],
                &[
                    &MixReg { offset: 12 },
                    &MixReg { offset: 13 },
                    &MixReg { offset: 14 },
                    &MixReg { offset: 15 },
                ],
                &[
                    &MixReg { offset: 16 },
                    &MixReg { offset: 17 },
                    &MixReg { offset: 18 },
                    &MixReg { offset: 19 },
                ],
                &[
                    &MixReg { offset: 20 },
                    &MixReg { offset: 21 },
                    &MixReg { offset: 22 },
                    &MixReg { offset: 23 },
                ],
                &[
                    &MixReg { offset: 24 },
                    &MixReg { offset: 25 },
                    &MixReg { offset: 26 },
                    &MixReg { offset: 27 },
                ],
                &[
                    &MixReg { offset: 28 },
                    &MixReg { offset: 29 },
                    &MixReg { offset: 30 },
                    &MixReg { offset: 31 },
                ],
                &[
                    &MixReg { offset: 32 },
                    &MixReg { offset: 33 },
                    &MixReg { offset: 34 },
                    &MixReg { offset: 35 },
                ],
            ],
        },
        reset: &RamHeader {
            accum: &[
                &AccumReg { offset: 24 },
                &AccumReg { offset: 25 },
                &AccumReg { offset: 26 },
                &AccumReg { offset: 27 },
            ],
            element: &RamPlonkElement {
                addr: &DataReg { offset: 89 },
                cycle: &DataReg { offset: 90 },
                mem_op: &DataReg { offset: 91 },
                data: &[
                    &DataReg { offset: 92 },
                    &DataReg { offset: 93 },
                    &DataReg { offset: 94 },
                    &DataReg { offset: 95 },
                ],
            },
            verifier: &RamPlonkVerifier {
                dirty: &DataReg { offset: 97 },
                extra: &DataReg { offset: 69 },
                is_new_addr: &DataReg { offset: 96 },
                diff: &[
                    &DataReg { offset: 3 },
                    &DataReg { offset: 4 },
                    &DataReg { offset: 5 },
                ],
            },
            mix: &[
                &[
                    &MixReg { offset: 8 },
                    &MixReg { offset: 9 },
                    &MixReg { offset: 10 },
                    &MixReg { offset: 11 },
                ],
                &[
                    &MixReg { offset: 12 },
                    &MixReg { offset: 13 },
                    &MixReg { offset: 14 },
                    &MixReg { offset: 15 },
                ],
                &[
                    &MixReg { offset: 16 },
                    &MixReg { offset: 17 },
                    &MixReg { offset: 18 },
                    &MixReg { offset: 19 },
                ],
                &[
                    &MixReg { offset: 20 },
                    &MixReg { offset: 21 },
                    &MixReg { offset: 22 },
                    &MixReg { offset: 23 },
                ],
                &[
                    &MixReg { offset: 24 },
                    &MixReg { offset: 25 },
                    &MixReg { offset: 26 },
                    &MixReg { offset: 27 },
                ],
                &[
                    &MixReg { offset: 28 },
                    &MixReg { offset: 29 },
                    &MixReg { offset: 30 },
                    &MixReg { offset: 31 },
                ],
                &[
                    &MixReg { offset: 32 },
                    &MixReg { offset: 33 },
                    &MixReg { offset: 34 },
                    &MixReg { offset: 35 },
                ],
            ],
        },
    },
};
