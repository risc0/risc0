pub const LAYOUT__3: &NondetRegLayout7LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 12 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 13 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 14 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 15 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 17 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 18 },
    },
];
pub const LAYOUT__2: &OneHot_7_Layout = &OneHot_7_Layout { _super: LAYOUT__3 };
pub const LAYOUT__4: &BigIntAccumStateLayout = &BigIntAccumStateLayout {
    poly: &NondetExtRegLayout {
        _super: &Reg { offset: 0 },
    },
    term: &NondetExtRegLayout {
        _super: &Reg { offset: 4 },
    },
    total: &NondetExtRegLayout {
        _super: &Reg { offset: 8 },
    },
};
pub const LAYOUT__6: &BigIntPolyOpAddTotalLayout = &BigIntPolyOpAddTotalLayout {
    _super: LAYOUT__4,
    tmp: &NondetExtRegLayout {
        _super: &Reg { offset: 19 },
    },
};
pub const LAYOUT__5: &BigIntAccumStateLayout_0 = &BigIntAccumStateLayout_0 {
    _super: LAYOUT__4,
    arm0: LAYOUT__4,
    arm1: LAYOUT__4,
    arm2: LAYOUT__4,
    arm3: LAYOUT__6,
    arm4: LAYOUT__4,
    arm5: LAYOUT__4,
    arm6: LAYOUT__4,
};
pub const LAYOUT__1: &BigIntAccumLayout = &BigIntAccumLayout {
    poly_op: LAYOUT__2,
    state: LAYOUT__4,
    state_redef: LAYOUT__5,
};
pub const LAYOUT__0: &AccumLayout = &AccumLayout { _0: LAYOUT__1 };
pub const LAYOUT__10: &NondetRegLayout8LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 21 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 22 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 23 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 24 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 25 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 26 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 27 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 28 },
    },
];
pub const LAYOUT__9: &OneHot_8_Layout = &OneHot_8_Layout { _super: LAYOUT__10 };
pub const LAYOUT__8: &InstInputLayout = &InstInputLayout {
    minor_onehot: LAYOUT__9,
};
pub const LAYOUT__12: &NondetRegLayout13LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 1 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 2 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 3 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 4 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 5 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 6 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 7 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 8 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 9 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 10 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 11 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 12 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 13 },
    },
];
pub const LAYOUT__11: &OneHot_13_Layout = &OneHot_13_Layout { _super: LAYOUT__12 };
pub const LAYOUT__17: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__18: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
    },
};
pub const LAYOUT__16: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__17,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    high16: LAYOUT__18,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
};
pub const LAYOUT__20: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
};
pub const LAYOUT__21: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
    },
};
pub const LAYOUT__19: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__20,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    high16: LAYOUT__21,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
};
pub const LAYOUT__25: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 55 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 56 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 58 },
    },
};
pub const LAYOUT__26: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 59 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 60 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 61 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 62 },
    },
};
pub const LAYOUT__24: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__25,
    new_txn: LAYOUT__26,
};
pub const LAYOUT__28: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
};
pub const LAYOUT__27: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__28 };
pub const LAYOUT__23: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__24,
    _0: LAYOUT__27,
};
pub const LAYOUT__22: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    _0: LAYOUT__23,
};
pub const LAYOUT__15: &FinalizeMiscLayout = &FinalizeMiscLayout {
    write_data: LAYOUT__16,
    pc_norm: LAYOUT__19,
    _0: LAYOUT__22,
};
pub const LAYOUT__29: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__32: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
};
pub const LAYOUT__34: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
};
pub const LAYOUT__35: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
};
pub const LAYOUT__33: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    upper_diff: LAYOUT__34,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
    med14: LAYOUT__35,
};
pub const LAYOUT__38: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
};
pub const LAYOUT__39: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
};
pub const LAYOUT__37: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__38,
    new_txn: LAYOUT__39,
};
pub const LAYOUT__41: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__40: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__41 };
pub const LAYOUT__36: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__37,
    _0: LAYOUT__40,
};
pub const LAYOUT__31: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__32,
    pc_addr: LAYOUT__33,
    load_inst: LAYOUT__36,
};
pub const LAYOUT__45: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
};
pub const LAYOUT__46: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
};
pub const LAYOUT__47: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
};
pub const LAYOUT__48: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 117 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
};
pub const LAYOUT__44: &MemoryArgLayout4LayoutArray =
    &[LAYOUT__45, LAYOUT__46, LAYOUT__47, LAYOUT__48];
pub const LAYOUT__49: &CycleArgLayout2LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
];
pub const LAYOUT__43: &_Arguments_ReadSourceRegsSourceRegsLayout =
    &_Arguments_ReadSourceRegsSourceRegsLayout {
        memory_arg: LAYOUT__44,
        cycle_arg: LAYOUT__49,
    };
pub const LAYOUT__55: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__45,
    new_txn: LAYOUT__46,
};
pub const LAYOUT__57: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
};
pub const LAYOUT__56: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__57 };
pub const LAYOUT__54: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__55,
    _0: LAYOUT__56,
};
pub const LAYOUT__53: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__54,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
};
pub const LAYOUT__52: &ReadSourceRegsSourceRegsArm0_SuperLayout =
    &ReadSourceRegsSourceRegsArm0_SuperLayout { rboth: LAYOUT__53 };
pub const LAYOUT__51: &ReadSourceRegsSourceRegsArm0Layout = &ReadSourceRegsSourceRegsArm0Layout {
    _super: LAYOUT__52,
    _extra0: LAYOUT__47,
    _extra1: LAYOUT__48,
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__61: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__47,
    new_txn: LAYOUT__48,
};
pub const LAYOUT__63: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__62: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__63 };
pub const LAYOUT__60: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__61,
    _0: LAYOUT__62,
};
pub const LAYOUT__59: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__60,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
};
pub const LAYOUT__58: &ReadSourceRegsSourceRegsArm1_SuperLayout =
    &ReadSourceRegsSourceRegsArm1_SuperLayout {
        _0: LAYOUT__53,
        _1: LAYOUT__59,
    };
pub const LAYOUT__50: &ReadSourceRegsSourceRegsLayout = &ReadSourceRegsSourceRegsLayout {
    arm0: LAYOUT__51,
    arm1: LAYOUT__58,
};
pub const LAYOUT__42: &ReadSourceRegsLayout = &ReadSourceRegsLayout {
    is_same_reg: &NondetRegLayout {
        _super: &Reg { offset: 125 },
    },
    _arguments_read_source_regs_source_regs: LAYOUT__43,
    source_regs: LAYOUT__50,
    rs1_low: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
    rs1_high: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    rs2_low: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    rs2_high: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
};
pub const LAYOUT__30: &MiscInputLayout = &MiscInputLayout {
    decoded: LAYOUT__31,
    source_regs: LAYOUT__42,
};
pub const LAYOUT__65: &ArgU16Layout5LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
];
pub const LAYOUT__64: &_Arguments_Misc0MiscOutputLayout = &_Arguments_Misc0MiscOutputLayout {
    arg_u16: LAYOUT__65,
};
pub const LAYOUT__67: &Misc0MiscOutputArm0Layout = &Misc0MiscOutputArm0Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__68: &Misc0MiscOutputArm1Layout = &Misc0MiscOutputArm1Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__75: &NondetRegLayout16LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 140 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 141 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 143 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 144 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 145 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 146 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 147 },
    },
];
pub const LAYOUT__74: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__75 };
pub const LAYOUT__77: &NondetRegLayout16LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 148 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 149 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 150 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 151 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 152 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 153 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 161 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 162 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 163 },
    },
];
pub const LAYOUT__76: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__77 };
pub const LAYOUT__73: &BitwiseAndU16Layout = &BitwiseAndU16Layout {
    bits_x: LAYOUT__74,
    bits_y: LAYOUT__76,
};
pub const LAYOUT__80: &NondetRegLayout16LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 167 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 168 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 170 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 172 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 173 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 174 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 177 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 178 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 179 },
    },
];
pub const LAYOUT__79: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__80 };
pub const LAYOUT__82: &NondetRegLayout16LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 185 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 186 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 187 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 188 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 189 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 190 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 191 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 192 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 193 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 194 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 195 },
    },
];
pub const LAYOUT__81: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__82 };
pub const LAYOUT__78: &BitwiseAndU16Layout = &BitwiseAndU16Layout {
    bits_x: LAYOUT__79,
    bits_y: LAYOUT__81,
};
pub const LAYOUT__72: &BitwiseAndLayout = &BitwiseAndLayout {
    _0: LAYOUT__73,
    _1: LAYOUT__78,
};
pub const LAYOUT__71: &BitwiseXorLayout = &BitwiseXorLayout { and_xy: LAYOUT__72 };
pub const LAYOUT__70: &OpXORLayout = &OpXORLayout { _0: LAYOUT__71 };
pub const LAYOUT__69: &Misc0MiscOutputArm2Layout = &Misc0MiscOutputArm2Layout {
    _super: LAYOUT__70,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__85: &BitwiseOrLayout = &BitwiseOrLayout { and_xy: LAYOUT__72 };
pub const LAYOUT__84: &OpORLayout = &OpORLayout { _0: LAYOUT__85 };
pub const LAYOUT__83: &Misc0MiscOutputArm3Layout = &Misc0MiscOutputArm3Layout {
    _super: LAYOUT__84,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__87: &OpANDLayout = &OpANDLayout { _0: LAYOUT__72 };
pub const LAYOUT__86: &Misc0MiscOutputArm4Layout = &Misc0MiscOutputArm4Layout {
    _super: LAYOUT__87,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__91: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
};
pub const LAYOUT__92: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__90: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__91,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    high16: LAYOUT__92,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
};
pub const LAYOUT__94: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__93: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
    rest_times_two: LAYOUT__94,
};
pub const LAYOUT__96: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__95: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    rest_times_two: LAYOUT__96,
};
pub const LAYOUT__98: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__97: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    rest_times_two: LAYOUT__98,
};
pub const LAYOUT__89: &CmpLessThanLayout = &CmpLessThanLayout {
    diff: LAYOUT__90,
    s1: LAYOUT__93,
    s2: LAYOUT__95,
    s3: LAYOUT__97,
    overflow: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    is_less_than: &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
};
pub const LAYOUT__88: &OpSLTLayout = &OpSLTLayout { cmp: LAYOUT__89 };
pub const LAYOUT__101: &CmpLessThanUnsignedLayout = &CmpLessThanUnsignedLayout { diff: LAYOUT__90 };
pub const LAYOUT__100: &OpSLTULayout = &OpSLTULayout { cmp: LAYOUT__101 };
pub const LAYOUT__99: &Misc0MiscOutputArm6Layout = &Misc0MiscOutputArm6Layout {
    _super: LAYOUT__100,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__102: &Misc0MiscOutputArm7Layout = &Misc0MiscOutputArm7Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__66: &Misc0MiscOutputLayout = &Misc0MiscOutputLayout {
    arm0: LAYOUT__67,
    arm1: LAYOUT__68,
    arm2: LAYOUT__69,
    arm3: LAYOUT__83,
    arm4: LAYOUT__86,
    arm5: LAYOUT__88,
    arm6: LAYOUT__99,
    arm7: LAYOUT__102,
};
pub const LAYOUT__14: &Misc0Layout = &Misc0Layout {
    _super: LAYOUT__15,
    _0: LAYOUT__29,
    input: LAYOUT__30,
    _arguments_misc0_misc_output: LAYOUT__64,
    misc_output: LAYOUT__66,
};
pub const LAYOUT__104: &_Arguments_Misc1MiscOutputLayout = &_Arguments_Misc1MiscOutputLayout {
    arg_u16: LAYOUT__65,
};
pub const LAYOUT__107: &OpXORILayout = &OpXORILayout { _0: LAYOUT__71 };
pub const LAYOUT__106: &Misc1MiscOutputArm0Layout = &Misc1MiscOutputArm0Layout {
    _super: LAYOUT__107,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__109: &OpORILayout = &OpORILayout { _0: LAYOUT__85 };
pub const LAYOUT__108: &Misc1MiscOutputArm1Layout = &Misc1MiscOutputArm1Layout {
    _super: LAYOUT__109,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__111: &OpANDILayout = &OpANDILayout { _0: LAYOUT__72 };
pub const LAYOUT__110: &Misc1MiscOutputArm2Layout = &Misc1MiscOutputArm2Layout {
    _super: LAYOUT__111,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__112: &OpSLTILayout = &OpSLTILayout { cmp: LAYOUT__89 };
pub const LAYOUT__114: &OpSLTIULayout = &OpSLTIULayout { cmp: LAYOUT__101 };
pub const LAYOUT__113: &Misc1MiscOutputArm4Layout = &Misc1MiscOutputArm4Layout {
    _super: LAYOUT__114,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__117: &CmpEqualLayout = &CmpEqualLayout {
    low_same: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    high_same: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    is_equal: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
};
pub const LAYOUT__116: &OpBEQLayout = &OpBEQLayout { cmp: LAYOUT__117 };
pub const LAYOUT__115: &Misc1MiscOutputArm5Layout = &Misc1MiscOutputArm5Layout {
    _super: LAYOUT__116,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__119: &OpBNELayout = &OpBNELayout { cmp: LAYOUT__117 };
pub const LAYOUT__118: &Misc1MiscOutputArm6Layout = &Misc1MiscOutputArm6Layout {
    _super: LAYOUT__119,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__120: &OpBLTLayout = &OpBLTLayout { cmp: LAYOUT__89 };
pub const LAYOUT__105: &Misc1MiscOutputLayout = &Misc1MiscOutputLayout {
    arm0: LAYOUT__106,
    arm1: LAYOUT__108,
    arm2: LAYOUT__110,
    arm3: LAYOUT__112,
    arm4: LAYOUT__113,
    arm5: LAYOUT__115,
    arm6: LAYOUT__118,
    arm7: LAYOUT__120,
};
pub const LAYOUT__103: &Misc1Layout = &Misc1Layout {
    _super: LAYOUT__15,
    _0: LAYOUT__29,
    input: LAYOUT__30,
    _arguments_misc1_misc_output: LAYOUT__104,
    misc_output: LAYOUT__105,
};
pub const LAYOUT__122: &_Arguments_Misc2MiscOutputLayout = &_Arguments_Misc2MiscOutputLayout {
    arg_u16: LAYOUT__65,
};
pub const LAYOUT__124: &OpBGELayout = &OpBGELayout { cmp: LAYOUT__89 };
pub const LAYOUT__126: &OpBLTULayout = &OpBLTULayout { cmp: LAYOUT__101 };
pub const LAYOUT__125: &Misc2MiscOutputArm1Layout = &Misc2MiscOutputArm1Layout {
    _super: LAYOUT__126,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__128: &OpBGEULayout = &OpBGEULayout { cmp: LAYOUT__101 };
pub const LAYOUT__127: &Misc2MiscOutputArm2Layout = &Misc2MiscOutputArm2Layout {
    _super: LAYOUT__128,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__129: &Misc2MiscOutputArm3Layout = &Misc2MiscOutputArm3Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__131: &OpJALRLayout = &OpJALRLayout {
    lsb: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    half: LAYOUT__91,
};
pub const LAYOUT__130: &Misc2MiscOutputArm4Layout = &Misc2MiscOutputArm4Layout {
    _super: LAYOUT__131,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__132: &Misc2MiscOutputArm5Layout = &Misc2MiscOutputArm5Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__133: &Misc2MiscOutputArm6Layout = &Misc2MiscOutputArm6Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__134: &Misc2MiscOutputArm7Layout = &Misc2MiscOutputArm7Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__123: &Misc2MiscOutputLayout = &Misc2MiscOutputLayout {
    arm0: LAYOUT__124,
    arm1: LAYOUT__125,
    arm2: LAYOUT__127,
    arm3: LAYOUT__129,
    arm4: LAYOUT__130,
    arm5: LAYOUT__132,
    arm6: LAYOUT__133,
    arm7: LAYOUT__134,
};
pub const LAYOUT__121: &Misc2Layout = &Misc2Layout {
    _super: LAYOUT__15,
    _0: LAYOUT__29,
    input: LAYOUT__30,
    _arguments_misc2_misc_output: LAYOUT__122,
    misc_output: LAYOUT__123,
};
pub const LAYOUT__136: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__139: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
};
pub const LAYOUT__141: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__142: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__140: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    upper_diff: LAYOUT__141,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
    med14: LAYOUT__142,
};
pub const LAYOUT__145: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
};
pub const LAYOUT__146: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
};
pub const LAYOUT__144: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__145,
    new_txn: LAYOUT__146,
};
pub const LAYOUT__148: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
};
pub const LAYOUT__147: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__148 };
pub const LAYOUT__143: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__144,
    _0: LAYOUT__147,
};
pub const LAYOUT__138: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__139,
    pc_addr: LAYOUT__140,
    load_inst: LAYOUT__143,
};
pub const LAYOUT__152: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
};
pub const LAYOUT__153: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
};
pub const LAYOUT__154: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 117 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
};
pub const LAYOUT__155: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
};
pub const LAYOUT__151: &MemoryArgLayout4LayoutArray =
    &[LAYOUT__152, LAYOUT__153, LAYOUT__154, LAYOUT__155];
pub const LAYOUT__156: &CycleArgLayout2LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
];
pub const LAYOUT__150: &_Arguments_ReadSourceRegsSourceRegsLayout =
    &_Arguments_ReadSourceRegsSourceRegsLayout {
        memory_arg: LAYOUT__151,
        cycle_arg: LAYOUT__156,
    };
pub const LAYOUT__162: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__152,
    new_txn: LAYOUT__153,
};
pub const LAYOUT__161: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__162,
    _0: LAYOUT__62,
};
pub const LAYOUT__160: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__161,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
};
pub const LAYOUT__159: &ReadSourceRegsSourceRegsArm0_SuperLayout =
    &ReadSourceRegsSourceRegsArm0_SuperLayout { rboth: LAYOUT__160 };
pub const LAYOUT__158: &ReadSourceRegsSourceRegsArm0Layout = &ReadSourceRegsSourceRegsArm0Layout {
    _super: LAYOUT__159,
    _extra0: LAYOUT__154,
    _extra1: LAYOUT__155,
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
};
pub const LAYOUT__166: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__154,
    new_txn: LAYOUT__155,
};
pub const LAYOUT__168: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
};
pub const LAYOUT__167: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__168 };
pub const LAYOUT__165: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__166,
    _0: LAYOUT__167,
};
pub const LAYOUT__164: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__165,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
};
pub const LAYOUT__163: &ReadSourceRegsSourceRegsArm1_SuperLayout =
    &ReadSourceRegsSourceRegsArm1_SuperLayout {
        _0: LAYOUT__160,
        _1: LAYOUT__164,
    };
pub const LAYOUT__157: &ReadSourceRegsSourceRegsLayout = &ReadSourceRegsSourceRegsLayout {
    arm0: LAYOUT__158,
    arm1: LAYOUT__163,
};
pub const LAYOUT__149: &ReadSourceRegsLayout = &ReadSourceRegsLayout {
    is_same_reg: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    _arguments_read_source_regs_source_regs: LAYOUT__150,
    source_regs: LAYOUT__157,
    rs1_low: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    rs1_high: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    rs2_low: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    rs2_high: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
};
pub const LAYOUT__137: &MulInputLayout = &MulInputLayout {
    decoded: LAYOUT__138,
    source_regs: LAYOUT__149,
};
pub const LAYOUT__170: &ArgU16Layout6LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
];
pub const LAYOUT__171: &ArgU8Layout13LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
];
pub const LAYOUT__169: &_Arguments_Mul0MulOutputLayout = &_Arguments_Mul0MulOutputLayout {
    arg_u16: LAYOUT__170,
    arg_u8: LAYOUT__171,
};
pub const LAYOUT__176: &NondetRegLayout5LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
];
pub const LAYOUT__175: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__176,
};
pub const LAYOUT__174: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__175,
    check_u16: LAYOUT__91,
    b3: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
    low: &NondetRegLayout {
        _super: &Reg { offset: 140 },
    },
    high: &NondetRegLayout {
        _super: &Reg { offset: 141 },
    },
};
pub const LAYOUT__180: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
};
pub const LAYOUT__181: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__182: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
};
pub const LAYOUT__183: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
};
pub const LAYOUT__184: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
};
pub const LAYOUT__179: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__180,
    b1: LAYOUT__181,
    b2: LAYOUT__182,
    b3: LAYOUT__183,
    b3_top7times2: LAYOUT__184,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
};
pub const LAYOUT__186: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
};
pub const LAYOUT__187: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
};
pub const LAYOUT__188: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
};
pub const LAYOUT__189: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
};
pub const LAYOUT__190: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__185: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__186,
    b1: LAYOUT__187,
    b2: LAYOUT__188,
    b3: LAYOUT__189,
    b3_top7times2: LAYOUT__190,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 143 },
    },
};
pub const LAYOUT__192: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
};
pub const LAYOUT__191: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__94,
    carry_byte: LAYOUT__192,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__194: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
};
pub const LAYOUT__193: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__96,
    carry_byte: LAYOUT__194,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
};
pub const LAYOUT__196: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__195: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__98,
    carry_byte: LAYOUT__196,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
};
pub const LAYOUT__178: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__179,
    bx: LAYOUT__185,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 144 },
    },
    c_rest_times2: LAYOUT__92,
    s0: LAYOUT__191,
    s1: LAYOUT__193,
    s2: LAYOUT__195,
    s3_out: LAYOUT__17,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
};
pub const LAYOUT__177: &DoMulLayout = &DoMulLayout { mul: LAYOUT__178 };
pub const LAYOUT__173: &OpSLLLayout = &OpSLLLayout {
    shift_mul: LAYOUT__174,
    _0: LAYOUT__177,
};
pub const LAYOUT__197: &OpSLLILayout = &OpSLLILayout {
    shift_mul: LAYOUT__174,
    _0: LAYOUT__177,
};
pub const LAYOUT__202: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__180,
    b1: LAYOUT__181,
    b2: LAYOUT__182,
    b3: LAYOUT__183,
    b3_top7times2: LAYOUT__184,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
};
pub const LAYOUT__203: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__186,
    b1: LAYOUT__187,
    b2: LAYOUT__188,
    b3: LAYOUT__189,
    b3_top7times2: LAYOUT__190,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
};
pub const LAYOUT__204: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__92,
    carry_byte: LAYOUT__192,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__205: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__94,
    carry_byte: LAYOUT__194,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
};
pub const LAYOUT__206: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__96,
    carry_byte: LAYOUT__196,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
};
pub const LAYOUT__201: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__202,
    bx: LAYOUT__203,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    c_rest_times2: LAYOUT__91,
    s0: LAYOUT__204,
    s1: LAYOUT__205,
    s2: LAYOUT__206,
    s3_out: LAYOUT__98,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__200: &DoMulLayout = &DoMulLayout { mul: LAYOUT__201 };
pub const LAYOUT__199: &OpMULLayout = &OpMULLayout { _0: LAYOUT__200 };
pub const LAYOUT__198: &Mul0MulOutputArm2Layout = &Mul0MulOutputArm2Layout {
    _super: LAYOUT__199,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__208: &OpMULHLayout = &OpMULHLayout { _0: LAYOUT__200 };
pub const LAYOUT__207: &Mul0MulOutputArm3Layout = &Mul0MulOutputArm3Layout {
    _super: LAYOUT__208,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__210: &OpMULHSULayout = &OpMULHSULayout { _0: LAYOUT__200 };
pub const LAYOUT__209: &Mul0MulOutputArm4Layout = &Mul0MulOutputArm4Layout {
    _super: LAYOUT__210,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__212: &OpMULHULayout = &OpMULHULayout { _0: LAYOUT__200 };
pub const LAYOUT__211: &Mul0MulOutputArm5Layout = &Mul0MulOutputArm5Layout {
    _super: LAYOUT__212,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__213: &Mul0MulOutputArm6Layout = &Mul0MulOutputArm6Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
    _extra6: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
    _extra7: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
    _extra8: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
    _extra9: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
    _extra14: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
    _extra15: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__214: &Mul0MulOutputArm7Layout = &Mul0MulOutputArm7Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
    _extra6: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
    _extra7: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
    _extra8: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
    _extra9: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
    _extra14: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
    _extra15: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__172: &Mul0MulOutputLayout = &Mul0MulOutputLayout {
    arm0: LAYOUT__173,
    arm1: LAYOUT__197,
    arm2: LAYOUT__198,
    arm3: LAYOUT__207,
    arm4: LAYOUT__209,
    arm5: LAYOUT__211,
    arm6: LAYOUT__213,
    arm7: LAYOUT__214,
};
pub const LAYOUT__218: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
};
pub const LAYOUT__219: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 161 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 162 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 163 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
};
pub const LAYOUT__217: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__218,
    new_txn: LAYOUT__219,
};
pub const LAYOUT__221: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
};
pub const LAYOUT__220: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__221 };
pub const LAYOUT__216: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__217,
    _0: LAYOUT__220,
};
pub const LAYOUT__215: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
    _0: LAYOUT__216,
};
pub const LAYOUT__223: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
};
pub const LAYOUT__224: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
};
pub const LAYOUT__222: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__223,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
    high16: LAYOUT__224,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 172 },
    },
};
pub const LAYOUT__135: &Mul0Layout = &Mul0Layout {
    _0: LAYOUT__136,
    input: LAYOUT__137,
    _arguments_mul0_mul_output: LAYOUT__169,
    mul_output: LAYOUT__172,
    _1: LAYOUT__215,
    pc_add: LAYOUT__222,
};
pub const LAYOUT__226: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
    },
};
pub const LAYOUT__229: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
};
pub const LAYOUT__231: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
};
pub const LAYOUT__232: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
};
pub const LAYOUT__230: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    upper_diff: LAYOUT__231,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    med14: LAYOUT__232,
};
pub const LAYOUT__235: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 117 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
};
pub const LAYOUT__236: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
};
pub const LAYOUT__234: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__235,
    new_txn: LAYOUT__236,
};
pub const LAYOUT__233: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__234,
    _0: LAYOUT__62,
};
pub const LAYOUT__228: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__229,
    pc_addr: LAYOUT__230,
    load_inst: LAYOUT__233,
};
pub const LAYOUT__240: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 125 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
};
pub const LAYOUT__241: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
};
pub const LAYOUT__242: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
};
pub const LAYOUT__243: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 140 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 141 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
};
pub const LAYOUT__239: &MemoryArgLayout4LayoutArray =
    &[LAYOUT__240, LAYOUT__241, LAYOUT__242, LAYOUT__243];
pub const LAYOUT__244: &CycleArgLayout2LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
];
pub const LAYOUT__238: &_Arguments_ReadSourceRegsSourceRegsLayout =
    &_Arguments_ReadSourceRegsSourceRegsLayout {
        memory_arg: LAYOUT__239,
        cycle_arg: LAYOUT__244,
    };
pub const LAYOUT__250: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__240,
    new_txn: LAYOUT__241,
};
pub const LAYOUT__252: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__251: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__252 };
pub const LAYOUT__249: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__250,
    _0: LAYOUT__251,
};
pub const LAYOUT__248: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__249,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 148 },
    },
};
pub const LAYOUT__247: &ReadSourceRegsSourceRegsArm0_SuperLayout =
    &ReadSourceRegsSourceRegsArm0_SuperLayout { rboth: LAYOUT__248 };
pub const LAYOUT__246: &ReadSourceRegsSourceRegsArm0Layout = &ReadSourceRegsSourceRegsArm0Layout {
    _super: LAYOUT__247,
    _extra0: LAYOUT__242,
    _extra1: LAYOUT__243,
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__256: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__242,
    new_txn: LAYOUT__243,
};
pub const LAYOUT__258: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__257: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__258 };
pub const LAYOUT__255: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__256,
    _0: LAYOUT__257,
};
pub const LAYOUT__254: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__255,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 149 },
    },
};
pub const LAYOUT__253: &ReadSourceRegsSourceRegsArm1_SuperLayout =
    &ReadSourceRegsSourceRegsArm1_SuperLayout {
        _0: LAYOUT__248,
        _1: LAYOUT__254,
    };
pub const LAYOUT__245: &ReadSourceRegsSourceRegsLayout = &ReadSourceRegsSourceRegsLayout {
    arm0: LAYOUT__246,
    arm1: LAYOUT__253,
};
pub const LAYOUT__237: &ReadSourceRegsLayout = &ReadSourceRegsLayout {
    is_same_reg: &NondetRegLayout {
        _super: &Reg { offset: 147 },
    },
    _arguments_read_source_regs_source_regs: LAYOUT__238,
    source_regs: LAYOUT__245,
    rs1_low: &NondetRegLayout {
        _super: &Reg { offset: 150 },
    },
    rs1_high: &NondetRegLayout {
        _super: &Reg { offset: 151 },
    },
    rs2_low: &NondetRegLayout {
        _super: &Reg { offset: 152 },
    },
    rs2_high: &NondetRegLayout {
        _super: &Reg { offset: 153 },
    },
};
pub const LAYOUT__227: &DivInputLayout = &DivInputLayout {
    decoded: LAYOUT__228,
    source_regs: LAYOUT__237,
};
pub const LAYOUT__260: &ArgU16Layout16LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
];
pub const LAYOUT__261: &ArgU8Layout13LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
];
pub const LAYOUT__259: &_Arguments_Div0MulOutputLayout = &_Arguments_Div0MulOutputLayout {
    arg_u16: LAYOUT__260,
    arg_u8: LAYOUT__261,
};
pub const LAYOUT__267: &NondetRegLayout5LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
];
pub const LAYOUT__266: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__267,
};
pub const LAYOUT__265: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__266,
    check_u16: LAYOUT__91,
    b3: &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
    low: &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
    high: &NondetRegLayout {
        _super: &Reg { offset: 161 },
    },
};
pub const LAYOUT__271: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__272: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__270: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__192,
    b1: LAYOUT__194,
    b2: LAYOUT__196,
    b3: LAYOUT__271,
    b3_top7times2: LAYOUT__272,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
};
pub const LAYOUT__274: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
};
pub const LAYOUT__275: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__276: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
};
pub const LAYOUT__277: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
};
pub const LAYOUT__278: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
};
pub const LAYOUT__273: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__274,
    b1: LAYOUT__275,
    b2: LAYOUT__276,
    b3: LAYOUT__277,
    b3_top7times2: LAYOUT__278,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
};
pub const LAYOUT__280: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
};
pub const LAYOUT__279: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__98,
    carry_byte: LAYOUT__280,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
};
pub const LAYOUT__282: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
};
pub const LAYOUT__281: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__17,
    carry_byte: LAYOUT__282,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
};
pub const LAYOUT__284: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
};
pub const LAYOUT__285: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
};
pub const LAYOUT__283: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__284,
    carry_byte: LAYOUT__285,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
};
pub const LAYOUT__286: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__269: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__270,
    bx: LAYOUT__273,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
    c_rest_times2: LAYOUT__96,
    s0: LAYOUT__279,
    s1: LAYOUT__281,
    s2: LAYOUT__283,
    s3_out: LAYOUT__286,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
};
pub const LAYOUT__288: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
};
pub const LAYOUT__289: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
};
pub const LAYOUT__287: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__288,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 177 },
    },
    high16: LAYOUT__289,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 178 },
    },
};
pub const LAYOUT__291: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
};
pub const LAYOUT__292: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
};
pub const LAYOUT__290: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__291,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 179 },
    },
    high16: LAYOUT__292,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
};
pub const LAYOUT__295: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
};
pub const LAYOUT__296: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
};
pub const LAYOUT__294: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__295,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    high16: LAYOUT__296,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
};
pub const LAYOUT__293: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__294 };
pub const LAYOUT__268: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 162 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 163 },
    },
    rem_low: LAYOUT__92,
    rem_high: LAYOUT__94,
    mul: LAYOUT__269,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
    top_num: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
    _0: LAYOUT__20,
    denom_abs: LAYOUT__287,
    rem_normal: LAYOUT__290,
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    signed_overflow_case: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    lt: LAYOUT__293,
};
pub const LAYOUT__264: &OpSRLLayout = &OpSRLLayout {
    shift_mul: LAYOUT__265,
    _0: LAYOUT__268,
};
pub const LAYOUT__263: &Div0MulOutputArm0Layout = &Div0MulOutputArm0Layout {
    _super: LAYOUT__264,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__298: &TopBitLayout = &TopBitLayout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 162 },
    },
    rest: LAYOUT__92,
};
pub const LAYOUT__301: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__192,
    b1: LAYOUT__194,
    b2: LAYOUT__196,
    b3: LAYOUT__271,
    b3_top7times2: LAYOUT__272,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
};
pub const LAYOUT__302: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__274,
    b1: LAYOUT__275,
    b2: LAYOUT__276,
    b3: LAYOUT__277,
    b3_top7times2: LAYOUT__278,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
};
pub const LAYOUT__303: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__17,
    carry_byte: LAYOUT__280,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
};
pub const LAYOUT__304: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__284,
    carry_byte: LAYOUT__282,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
};
pub const LAYOUT__305: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__286,
    carry_byte: LAYOUT__285,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
};
pub const LAYOUT__300: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__301,
    bx: LAYOUT__302,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 167 },
    },
    c_rest_times2: LAYOUT__98,
    s0: LAYOUT__303,
    s1: LAYOUT__304,
    s2: LAYOUT__305,
    s3_out: LAYOUT__20,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
};
pub const LAYOUT__306: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__289,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 178 },
    },
    high16: LAYOUT__291,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 179 },
    },
};
pub const LAYOUT__307: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__292,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
    high16: LAYOUT__295,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
};
pub const LAYOUT__310: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__309: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__296,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    high16: LAYOUT__310,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 185 },
    },
};
pub const LAYOUT__308: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__309 };
pub const LAYOUT__299: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 163 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
    rem_low: LAYOUT__94,
    rem_high: LAYOUT__96,
    mul: LAYOUT__300,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
    top_num: &NondetRegLayout {
        _super: &Reg { offset: 177 },
    },
    _0: LAYOUT__288,
    denom_abs: LAYOUT__306,
    rem_normal: LAYOUT__307,
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    signed_overflow_case: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    lt: LAYOUT__308,
};
pub const LAYOUT__297: &OpSRALayout = &OpSRALayout {
    shift_mul: LAYOUT__265,
    flip: LAYOUT__298,
    _0: LAYOUT__299,
};
pub const LAYOUT__312: &OpSRLILayout = &OpSRLILayout {
    shift_mul: LAYOUT__265,
    _0: LAYOUT__268,
};
pub const LAYOUT__311: &Div0MulOutputArm2Layout = &Div0MulOutputArm2Layout {
    _super: LAYOUT__312,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__313: &OpSRAILayout = &OpSRAILayout {
    shift_mul: LAYOUT__265,
    flip: LAYOUT__298,
    _0: LAYOUT__299,
};
pub const LAYOUT__318: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__192,
    b1: LAYOUT__194,
    b2: LAYOUT__196,
    b3: LAYOUT__271,
    b3_top7times2: LAYOUT__272,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
};
pub const LAYOUT__319: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__274,
    b1: LAYOUT__275,
    b2: LAYOUT__276,
    b3: LAYOUT__277,
    b3_top7times2: LAYOUT__278,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
};
pub const LAYOUT__320: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__96,
    carry_byte: LAYOUT__280,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__321: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__98,
    carry_byte: LAYOUT__282,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
};
pub const LAYOUT__322: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__17,
    carry_byte: LAYOUT__285,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
};
pub const LAYOUT__317: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__318,
    bx: LAYOUT__319,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
    c_rest_times2: LAYOUT__94,
    s0: LAYOUT__320,
    s1: LAYOUT__321,
    s2: LAYOUT__322,
    s3_out: LAYOUT__284,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
};
pub const LAYOUT__323: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__20,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
    high16: LAYOUT__288,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 170 },
    },
};
pub const LAYOUT__324: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__289,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
    high16: LAYOUT__291,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 172 },
    },
};
pub const LAYOUT__326: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__292,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
    high16: LAYOUT__295,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
};
pub const LAYOUT__325: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__326 };
pub const LAYOUT__316: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
    rem_low: LAYOUT__91,
    rem_high: LAYOUT__92,
    mul: LAYOUT__317,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 167 },
    },
    top_num: &NondetRegLayout {
        _super: &Reg { offset: 168 },
    },
    _0: LAYOUT__286,
    denom_abs: LAYOUT__323,
    rem_normal: LAYOUT__324,
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 173 },
    },
    signed_overflow_case: &NondetRegLayout {
        _super: &Reg { offset: 174 },
    },
    lt: LAYOUT__325,
};
pub const LAYOUT__315: &OpDIVLayout = &OpDIVLayout { _0: LAYOUT__316 };
pub const LAYOUT__314: &Div0MulOutputArm4Layout = &Div0MulOutputArm4Layout {
    _super: LAYOUT__315,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__328: &OpDIVULayout = &OpDIVULayout { _0: LAYOUT__316 };
pub const LAYOUT__327: &Div0MulOutputArm5Layout = &Div0MulOutputArm5Layout {
    _super: LAYOUT__328,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__330: &OpREMLayout = &OpREMLayout { _0: LAYOUT__316 };
pub const LAYOUT__329: &Div0MulOutputArm6Layout = &Div0MulOutputArm6Layout {
    _super: LAYOUT__330,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__332: &OpREMULayout = &OpREMULayout { _0: LAYOUT__316 };
pub const LAYOUT__331: &Div0MulOutputArm7Layout = &Div0MulOutputArm7Layout {
    _super: LAYOUT__332,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__262: &Div0MulOutputLayout = &Div0MulOutputLayout {
    arm0: LAYOUT__263,
    arm1: LAYOUT__297,
    arm2: LAYOUT__311,
    arm3: LAYOUT__313,
    arm4: LAYOUT__314,
    arm5: LAYOUT__327,
    arm6: LAYOUT__329,
    arm7: LAYOUT__331,
};
pub const LAYOUT__336: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 190 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 189 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 191 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 192 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 193 },
    },
};
pub const LAYOUT__337: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 194 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 189 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 195 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
};
pub const LAYOUT__335: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__336,
    new_txn: LAYOUT__337,
};
pub const LAYOUT__339: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 198 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 199 },
        },
    },
};
pub const LAYOUT__338: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__339 };
pub const LAYOUT__334: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__335,
    _0: LAYOUT__338,
};
pub const LAYOUT__333: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 188 },
    },
    _0: LAYOUT__334,
};
pub const LAYOUT__341: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 200 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 201 },
        },
    },
};
pub const LAYOUT__342: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 203 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 204 },
        },
    },
};
pub const LAYOUT__340: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__341,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 202 },
    },
    high16: LAYOUT__342,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 205 },
    },
};
pub const LAYOUT__225: &Div0Layout = &Div0Layout {
    _0: LAYOUT__226,
    input: LAYOUT__227,
    _arguments_div0_mul_output: LAYOUT__259,
    mul_output: LAYOUT__262,
    _1: LAYOUT__333,
    pc_add: LAYOUT__340,
};
pub const LAYOUT__344: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__347: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 51 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 55 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 56 },
    },
};
pub const LAYOUT__349: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__350: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
    },
};
pub const LAYOUT__348: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    upper_diff: LAYOUT__349,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
    },
    med14: LAYOUT__350,
};
pub const LAYOUT__353: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 65 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 66 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
};
pub const LAYOUT__354: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
};
pub const LAYOUT__352: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__353,
    new_txn: LAYOUT__354,
};
pub const LAYOUT__356: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__355: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__356 };
pub const LAYOUT__351: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__352,
    _0: LAYOUT__355,
};
pub const LAYOUT__346: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__347,
    pc_addr: LAYOUT__348,
    load_inst: LAYOUT__351,
};
pub const LAYOUT__360: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
};
pub const LAYOUT__361: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
};
pub const LAYOUT__359: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__360,
    new_txn: LAYOUT__361,
};
pub const LAYOUT__363: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__362: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__363 };
pub const LAYOUT__358: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__359,
    _0: LAYOUT__362,
};
pub const LAYOUT__357: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__358,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
};
pub const LAYOUT__365: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__364: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__365,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    high16: LAYOUT__35,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
};
pub const LAYOUT__367: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
};
pub const LAYOUT__368: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
};
pub const LAYOUT__366: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    upper_diff: LAYOUT__367,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
    med14: LAYOUT__368,
};
pub const LAYOUT__371: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
};
pub const LAYOUT__372: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
};
pub const LAYOUT__370: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__371,
    new_txn: LAYOUT__372,
};
pub const LAYOUT__374: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__373: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__374 };
pub const LAYOUT__369: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__370,
    _0: LAYOUT__373,
};
pub const LAYOUT__345: &MemLoadInputLayout = &MemLoadInputLayout {
    decoded: LAYOUT__346,
    rs1: LAYOUT__357,
    addr_u32: LAYOUT__364,
    addr: LAYOUT__366,
    data_0: LAYOUT__369,
};
pub const LAYOUT__376: &ArgU8Layout3LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
];
pub const LAYOUT__375: &_Arguments_Mem0OutputLayout = &_Arguments_Mem0OutputLayout {
    arg_u8: LAYOUT__376,
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    }],
};
pub const LAYOUT__381: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
};
pub const LAYOUT__382: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__380: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__381,
    byte1: LAYOUT__382,
};
pub const LAYOUT__383: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__379: &OpLBLayout = &OpLBLayout {
    bytes: LAYOUT__380,
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low7x2: LAYOUT__383,
};
pub const LAYOUT__378: &Mem0OutputArm0Layout = &Mem0OutputArm0Layout {
    _super: LAYOUT__379,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__385: &OpLHLayout = &OpLHLayout {
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low15x2: LAYOUT__96,
};
pub const LAYOUT__384: &Mem0OutputArm1Layout = &Mem0OutputArm1Layout {
    _super: LAYOUT__385,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__386: &Mem0OutputArm2Layout = &Mem0OutputArm2Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__388: &OpLBULayout = &OpLBULayout { bytes: LAYOUT__380 };
pub const LAYOUT__387: &Mem0OutputArm3Layout = &Mem0OutputArm3Layout {
    _super: LAYOUT__388,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__389: &Mem0OutputArm4Layout = &Mem0OutputArm4Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__390: &Mem0OutputArm5Layout = &Mem0OutputArm5Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__391: &Mem0OutputArm6Layout = &Mem0OutputArm6Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__392: &Mem0OutputArm7Layout = &Mem0OutputArm7Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__377: &Mem0OutputLayout = &Mem0OutputLayout {
    arm0: LAYOUT__378,
    arm1: LAYOUT__384,
    arm2: LAYOUT__386,
    arm3: LAYOUT__387,
    arm4: LAYOUT__389,
    arm5: LAYOUT__390,
    arm6: LAYOUT__391,
    arm7: LAYOUT__392,
};
pub const LAYOUT__396: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 117 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
};
pub const LAYOUT__397: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 124 },
    },
};
pub const LAYOUT__395: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__396,
    new_txn: LAYOUT__397,
};
pub const LAYOUT__394: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__395,
    _0: LAYOUT__167,
};
pub const LAYOUT__393: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    _0: LAYOUT__394,
};
pub const LAYOUT__399: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
};
pub const LAYOUT__400: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
};
pub const LAYOUT__398: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__399,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    high16: LAYOUT__400,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
};
pub const LAYOUT__343: &Mem0Layout = &Mem0Layout {
    _0: LAYOUT__344,
    input: LAYOUT__345,
    _arguments_mem0_output: LAYOUT__375,
    output: LAYOUT__377,
    _1: LAYOUT__393,
    pc_add: LAYOUT__398,
};
pub const LAYOUT__406: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
};
pub const LAYOUT__407: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
};
pub const LAYOUT__408: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
};
pub const LAYOUT__409: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
};
pub const LAYOUT__405: &MemoryArgLayout4LayoutArray =
    &[LAYOUT__406, LAYOUT__407, LAYOUT__408, LAYOUT__409];
pub const LAYOUT__410: &CycleArgLayout2LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
];
pub const LAYOUT__404: &_Arguments_ReadSourceRegsSourceRegsLayout =
    &_Arguments_ReadSourceRegsSourceRegsLayout {
        memory_arg: LAYOUT__405,
        cycle_arg: LAYOUT__410,
    };
pub const LAYOUT__416: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__406,
    new_txn: LAYOUT__407,
};
pub const LAYOUT__418: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
};
pub const LAYOUT__417: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__418 };
pub const LAYOUT__415: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__416,
    _0: LAYOUT__417,
};
pub const LAYOUT__414: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__415,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
};
pub const LAYOUT__413: &ReadSourceRegsSourceRegsArm0_SuperLayout =
    &ReadSourceRegsSourceRegsArm0_SuperLayout { rboth: LAYOUT__414 };
pub const LAYOUT__412: &ReadSourceRegsSourceRegsArm0Layout = &ReadSourceRegsSourceRegsArm0Layout {
    _super: LAYOUT__413,
    _extra0: LAYOUT__408,
    _extra1: LAYOUT__409,
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
};
pub const LAYOUT__422: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__408,
    new_txn: LAYOUT__409,
};
pub const LAYOUT__424: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
};
pub const LAYOUT__423: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__424 };
pub const LAYOUT__421: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__422,
    _0: LAYOUT__423,
};
pub const LAYOUT__420: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__421,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
};
pub const LAYOUT__419: &ReadSourceRegsSourceRegsArm1_SuperLayout =
    &ReadSourceRegsSourceRegsArm1_SuperLayout {
        _0: LAYOUT__414,
        _1: LAYOUT__420,
    };
pub const LAYOUT__411: &ReadSourceRegsSourceRegsLayout = &ReadSourceRegsSourceRegsLayout {
    arm0: LAYOUT__412,
    arm1: LAYOUT__419,
};
pub const LAYOUT__403: &ReadSourceRegsLayout = &ReadSourceRegsLayout {
    is_same_reg: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    _arguments_read_source_regs_source_regs: LAYOUT__404,
    source_regs: LAYOUT__411,
    rs1_low: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    rs1_high: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    rs2_low: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    rs2_high: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
};
pub const LAYOUT__426: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
};
pub const LAYOUT__427: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
};
pub const LAYOUT__425: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__426,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    high16: LAYOUT__427,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
};
pub const LAYOUT__429: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
};
pub const LAYOUT__428: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    upper_diff: LAYOUT__232,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
    med14: LAYOUT__429,
};
pub const LAYOUT__432: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
};
pub const LAYOUT__433: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 124 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 125 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
};
pub const LAYOUT__431: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__432,
    new_txn: LAYOUT__433,
};
pub const LAYOUT__435: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
};
pub const LAYOUT__434: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__435 };
pub const LAYOUT__430: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__431,
    _0: LAYOUT__434,
};
pub const LAYOUT__402: &MemStoreInputLayout = &MemStoreInputLayout {
    decoded: LAYOUT__346,
    source_regs: LAYOUT__403,
    addr_u32: LAYOUT__425,
    addr: LAYOUT__428,
    data_0: LAYOUT__430,
};
pub const LAYOUT__437: &ArgU8Layout4LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
];
pub const LAYOUT__436: &_Arguments_Mem1OutputLayout = &_Arguments_Mem1OutputLayout {
    arg_u8: LAYOUT__437,
};
pub const LAYOUT__441: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__440: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__383,
    byte1: LAYOUT__441,
};
pub const LAYOUT__439: &OpSBLayout = &OpSBLayout {
    orig_bytes: LAYOUT__380,
    new_bytes: LAYOUT__440,
};
pub const LAYOUT__442: &Mem1OutputArm1Layout = &Mem1OutputArm1Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__443: &Mem1OutputArm2Layout = &Mem1OutputArm2Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__444: &Mem1OutputArm3Layout = &Mem1OutputArm3Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__445: &Mem1OutputArm4Layout = &Mem1OutputArm4Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__446: &Mem1OutputArm5Layout = &Mem1OutputArm5Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__447: &Mem1OutputArm6Layout = &Mem1OutputArm6Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__448: &Mem1OutputArm7Layout = &Mem1OutputArm7Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__438: &Mem1OutputLayout = &Mem1OutputLayout {
    arm0: LAYOUT__439,
    arm1: LAYOUT__442,
    arm2: LAYOUT__443,
    arm3: LAYOUT__444,
    arm4: LAYOUT__445,
    arm5: LAYOUT__446,
    arm6: LAYOUT__447,
    arm7: LAYOUT__448,
};
pub const LAYOUT__452: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
};
pub const LAYOUT__453: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
};
pub const LAYOUT__451: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__452,
    new_txn: LAYOUT__453,
};
pub const LAYOUT__455: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__454: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__455 };
pub const LAYOUT__450: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__451,
    _0: LAYOUT__454,
};
pub const LAYOUT__449: &MemStoreFinalizeLayout = &MemStoreFinalizeLayout { _0: LAYOUT__450 };
pub const LAYOUT__457: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__458: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__456: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__457,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
    high16: LAYOUT__458,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 145 },
    },
};
pub const LAYOUT__401: &Mem1Layout = &Mem1Layout {
    _0: LAYOUT__344,
    input: LAYOUT__402,
    _arguments_mem1_output: LAYOUT__436,
    output: LAYOUT__438,
    _1: LAYOUT__449,
    pc_add: LAYOUT__456,
};
pub const LAYOUT__466: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 29 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 30 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 31 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 32 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 33 },
    },
};
pub const LAYOUT__467: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 34 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 30 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 35 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
};
pub const LAYOUT__465: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__466,
    new_txn: LAYOUT__467,
};
pub const LAYOUT__464: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__465 };
pub const LAYOUT__470: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 38 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
};
pub const LAYOUT__471: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
};
pub const LAYOUT__469: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__470,
    new_txn: LAYOUT__471,
};
pub const LAYOUT__468: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__469 };
pub const LAYOUT__474: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 51 },
    },
};
pub const LAYOUT__475: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 55 },
    },
};
pub const LAYOUT__473: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__474,
    new_txn: LAYOUT__475,
};
pub const LAYOUT__472: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__473 };
pub const LAYOUT__478: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 56 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 58 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 59 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 60 },
    },
};
pub const LAYOUT__479: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 61 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 62 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 63 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
};
pub const LAYOUT__477: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__478,
    new_txn: LAYOUT__479,
};
pub const LAYOUT__476: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__477 };
pub const LAYOUT__482: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 65 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 66 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
};
pub const LAYOUT__483: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 66 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
};
pub const LAYOUT__481: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__482,
    new_txn: LAYOUT__483,
};
pub const LAYOUT__480: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__481 };
pub const LAYOUT__486: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
};
pub const LAYOUT__487: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
};
pub const LAYOUT__485: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__486,
    new_txn: LAYOUT__487,
};
pub const LAYOUT__484: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__485 };
pub const LAYOUT__490: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
};
pub const LAYOUT__491: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
};
pub const LAYOUT__489: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__490,
    new_txn: LAYOUT__491,
};
pub const LAYOUT__488: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__489 };
pub const LAYOUT__494: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
};
pub const LAYOUT__495: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
};
pub const LAYOUT__493: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__494,
    new_txn: LAYOUT__495,
};
pub const LAYOUT__492: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__493 };
pub const LAYOUT__463: &MemoryPageInLayout8LayoutArray = &[
    LAYOUT__464,
    LAYOUT__468,
    LAYOUT__472,
    LAYOUT__476,
    LAYOUT__480,
    LAYOUT__484,
    LAYOUT__488,
    LAYOUT__492,
];
pub const LAYOUT__462: &ControlLoadRootAndNonceLayout =
    &ControlLoadRootAndNonceLayout { mem: LAYOUT__463 };
pub const LAYOUT__461: &Control0_SuperArm0Layout = &Control0_SuperArm0Layout {
    _super: LAYOUT__462,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra3: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra6: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra7: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra38: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__501: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__465,
    _0: LAYOUT__40,
};
pub const LAYOUT__502: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__469,
    _0: LAYOUT__147,
};
pub const LAYOUT__500: &ControlResume_SuperArm0_SuperLayout =
    &ControlResume_SuperArm0_SuperLayout {
        pc: LAYOUT__501,
        mode: LAYOUT__502,
    };
pub const LAYOUT__499: &ControlResume_SuperArm0Layout = &ControlResume_SuperArm0Layout {
    _super: LAYOUT__500,
    _extra0: LAYOUT__474,
    _extra1: LAYOUT__475,
    _extra2: LAYOUT__478,
    _extra3: LAYOUT__479,
    _extra4: LAYOUT__482,
    _extra5: LAYOUT__483,
    _extra6: LAYOUT__486,
    _extra7: LAYOUT__487,
    _extra8: LAYOUT__490,
    _extra9: LAYOUT__491,
    _extra10: LAYOUT__494,
    _extra11: LAYOUT__495,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
};
pub const LAYOUT__506: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__465,
    _0: LAYOUT__40,
};
pub const LAYOUT__505: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__506 };
pub const LAYOUT__508: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__469,
    _0: LAYOUT__147,
};
pub const LAYOUT__507: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__508 };
pub const LAYOUT__512: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
};
pub const LAYOUT__511: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__512 };
pub const LAYOUT__510: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__473,
    _0: LAYOUT__511,
};
pub const LAYOUT__509: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__510 };
pub const LAYOUT__516: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
};
pub const LAYOUT__515: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__516 };
pub const LAYOUT__514: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__477,
    _0: LAYOUT__515,
};
pub const LAYOUT__513: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__514 };
pub const LAYOUT__520: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
};
pub const LAYOUT__519: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__520 };
pub const LAYOUT__518: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__481,
    _0: LAYOUT__519,
};
pub const LAYOUT__517: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__518 };
pub const LAYOUT__524: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__523: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__524 };
pub const LAYOUT__522: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__485,
    _0: LAYOUT__523,
};
pub const LAYOUT__521: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__522 };
pub const LAYOUT__528: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
};
pub const LAYOUT__527: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__528 };
pub const LAYOUT__526: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__489,
    _0: LAYOUT__527,
};
pub const LAYOUT__525: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__526 };
pub const LAYOUT__532: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
};
pub const LAYOUT__531: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__532 };
pub const LAYOUT__530: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__493,
    _0: LAYOUT__531,
};
pub const LAYOUT__529: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__530 };
pub const LAYOUT__504: &ControlResume_SuperArm1_Super__0_SuperLayout8LayoutArray = &[
    LAYOUT__505,
    LAYOUT__507,
    LAYOUT__509,
    LAYOUT__513,
    LAYOUT__517,
    LAYOUT__521,
    LAYOUT__525,
    LAYOUT__529,
];
pub const LAYOUT__503: &ControlResume_SuperArm1_SuperLayout =
    &ControlResume_SuperArm1_SuperLayout { _1: LAYOUT__504 };
pub const LAYOUT__498: &ControlResume_SuperLayout = &ControlResume_SuperLayout {
    arm0: LAYOUT__499,
    arm1: LAYOUT__503,
};
pub const LAYOUT__534: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__466,
    LAYOUT__467,
    LAYOUT__470,
    LAYOUT__471,
    LAYOUT__474,
    LAYOUT__475,
    LAYOUT__478,
    LAYOUT__479,
    LAYOUT__482,
    LAYOUT__483,
    LAYOUT__486,
    LAYOUT__487,
    LAYOUT__490,
    LAYOUT__491,
    LAYOUT__494,
    LAYOUT__495,
];
pub const LAYOUT__535: &CycleArgLayout8LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
];
pub const LAYOUT__533: &_Arguments_ControlResume_SuperLayout =
    &_Arguments_ControlResume_SuperLayout {
        memory_arg: LAYOUT__534,
        cycle_arg: LAYOUT__535,
    };
pub const LAYOUT__497: &ControlResumeLayout = &ControlResumeLayout {
    _super: LAYOUT__498,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _arguments_control_resume__super: LAYOUT__533,
};
pub const LAYOUT__496: &Control0_SuperArm1Layout = &Control0_SuperArm1Layout {
    _super: LAYOUT__497,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__542: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
};
pub const LAYOUT__543: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__541: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__542,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    high16: LAYOUT__543,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
};
pub const LAYOUT__540: &ControlUserEcallOrFence_SuperArm0_SuperLayout =
    &ControlUserEcallOrFence_SuperArm0_SuperLayout {
        new_pc: LAYOUT__541,
    };
pub const LAYOUT__539: &ControlUserEcallOrFence_SuperArm0Layout =
    &ControlUserEcallOrFence_SuperArm0Layout {
        _super: LAYOUT__540,
        _extra0: LAYOUT__470,
        _extra1: LAYOUT__471,
        _extra2: LAYOUT__474,
        _extra3: LAYOUT__475,
        _extra4: &CycleArgLayout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 103 },
            },
            cycle: &NondetRegLayout {
                _super: &Reg { offset: 104 },
            },
        },
        _extra5: &CycleArgLayout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 105 },
            },
            cycle: &NondetRegLayout {
                _super: &Reg { offset: 106 },
            },
        },
    };
pub const LAYOUT__545: &ControlUserEcallOrFence_SuperArm1_SuperLayout =
    &ControlUserEcallOrFence_SuperArm1_SuperLayout {
        new_pc_addr: LAYOUT__502,
        _0: LAYOUT__510,
    };
pub const LAYOUT__544: &ControlUserEcallOrFence_SuperArm1Layout =
    &ControlUserEcallOrFence_SuperArm1Layout {
        _super: LAYOUT__545,
        _extra0: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 121 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 122 },
            },
        },
        _extra1: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 123 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 124 },
            },
        },
    };
pub const LAYOUT__538: &ControlUserEcallOrFence_SuperLayout =
    &ControlUserEcallOrFence_SuperLayout {
        arm0: LAYOUT__539,
        arm1: LAYOUT__544,
    };
pub const LAYOUT__547: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
};
pub const LAYOUT__548: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__546: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 185 },
    },
    upper_diff: LAYOUT__547,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    med14: LAYOUT__548,
};
pub const LAYOUT__550: &ArgU16Layout2LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
];
pub const LAYOUT__551: &MemoryArgLayout4LayoutArray =
    &[LAYOUT__470, LAYOUT__471, LAYOUT__474, LAYOUT__475];
pub const LAYOUT__552: &CycleArgLayout2LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
];
pub const LAYOUT__549: &_Arguments_ControlUserEcallOrFence_SuperLayout =
    &_Arguments_ControlUserEcallOrFence_SuperLayout {
        arg_u16: LAYOUT__550,
        memory_arg: LAYOUT__551,
        cycle_arg: LAYOUT__552,
    };
pub const LAYOUT__537: &ControlUserEcallOrFenceLayout = &ControlUserEcallOrFenceLayout {
    _super: LAYOUT__538,
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    pc_addr: LAYOUT__546,
    load_inst: LAYOUT__501,
    is_fence: &NondetRegLayout {
        _super: &Reg { offset: 188 },
    },
    _arguments_control_user_ecall_or_fence__super: LAYOUT__549,
};
pub const LAYOUT__536: &Control0_SuperArm2Layout = &Control0_SuperArm2Layout {
    _super: LAYOUT__537,
    _extra0: LAYOUT__478,
    _extra1: LAYOUT__479,
    _extra2: LAYOUT__482,
    _extra3: LAYOUT__483,
    _extra4: LAYOUT__486,
    _extra5: LAYOUT__487,
    _extra6: LAYOUT__490,
    _extra7: LAYOUT__491,
    _extra8: LAYOUT__494,
    _extra9: LAYOUT__495,
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra38: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra42: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__555: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    upper_diff: LAYOUT__547,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
    med14: LAYOUT__548,
};
pub const LAYOUT__556: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__542,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 186 },
    },
    high16: LAYOUT__543,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 187 },
    },
};
pub const LAYOUT__554: &ControlMRETLayout = &ControlMRETLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    pc_addr: LAYOUT__555,
    load_inst: LAYOUT__501,
    pc: LAYOUT__502,
    pc_add: LAYOUT__556,
};
pub const LAYOUT__553: &Control0_SuperArm3Layout = &Control0_SuperArm3Layout {
    _super: LAYOUT__554,
    _extra0: LAYOUT__474,
    _extra1: LAYOUT__475,
    _extra2: LAYOUT__478,
    _extra3: LAYOUT__479,
    _extra4: LAYOUT__482,
    _extra5: LAYOUT__483,
    _extra6: LAYOUT__486,
    _extra7: LAYOUT__487,
    _extra8: LAYOUT__490,
    _extra9: LAYOUT__491,
    _extra10: LAYOUT__494,
    _extra11: LAYOUT__495,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra38: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra42: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra43: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra44: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra45: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__562: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__473,
    _0: LAYOUT__511,
};
pub const LAYOUT__563: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__477,
    _0: LAYOUT__515,
};
pub const LAYOUT__564: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__481,
    _0: LAYOUT__519,
};
pub const LAYOUT__565: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__485,
    _0: LAYOUT__523,
};
pub const LAYOUT__566: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__489,
    _0: LAYOUT__527,
};
pub const LAYOUT__567: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__493,
    _0: LAYOUT__531,
};
pub const LAYOUT__561: &MemoryReadLayout8LayoutArray = &[
    LAYOUT__501,
    LAYOUT__502,
    LAYOUT__562,
    LAYOUT__563,
    LAYOUT__564,
    LAYOUT__565,
    LAYOUT__566,
    LAYOUT__567,
];
pub const LAYOUT__560: &ControlSuspend_SuperArm0_SuperLayout =
    &ControlSuspend_SuperArm0_SuperLayout { _1: LAYOUT__561 };
pub const LAYOUT__569: &ControlSuspend_SuperArm1_SuperLayout =
    &ControlSuspend_SuperArm1_SuperLayout {
        state: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        _0: LAYOUT__506,
        _1: LAYOUT__508,
    };
pub const LAYOUT__568: &ControlSuspend_SuperArm1Layout = &ControlSuspend_SuperArm1Layout {
    _super: LAYOUT__569,
    _extra0: LAYOUT__474,
    _extra1: LAYOUT__475,
    _extra2: LAYOUT__478,
    _extra3: LAYOUT__479,
    _extra4: LAYOUT__482,
    _extra5: LAYOUT__483,
    _extra6: LAYOUT__486,
    _extra7: LAYOUT__487,
    _extra8: LAYOUT__490,
    _extra9: LAYOUT__491,
    _extra10: LAYOUT__494,
    _extra11: LAYOUT__495,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
};
pub const LAYOUT__559: &ControlSuspend_SuperLayout = &ControlSuspend_SuperLayout {
    arm0: LAYOUT__560,
    arm1: LAYOUT__568,
};
pub const LAYOUT__570: &_Arguments_ControlSuspend_SuperLayout =
    &_Arguments_ControlSuspend_SuperLayout {
        memory_arg: LAYOUT__534,
        cycle_arg: LAYOUT__535,
    };
pub const LAYOUT__558: &ControlSuspendLayout = &ControlSuspendLayout {
    _super: LAYOUT__559,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _arguments_control_suspend__super: LAYOUT__570,
};
pub const LAYOUT__557: &Control0_SuperArm4Layout = &Control0_SuperArm4Layout {
    _super: LAYOUT__558,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__574: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__465,
    _0: LAYOUT__40,
};
pub const LAYOUT__575: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__469,
    _0: LAYOUT__147,
};
pub const LAYOUT__576: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__473,
    _0: LAYOUT__511,
};
pub const LAYOUT__577: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__477,
    _0: LAYOUT__515,
};
pub const LAYOUT__578: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__481,
    _0: LAYOUT__519,
};
pub const LAYOUT__579: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__485,
    _0: LAYOUT__523,
};
pub const LAYOUT__580: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__489,
    _0: LAYOUT__527,
};
pub const LAYOUT__581: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__493,
    _0: LAYOUT__531,
};
pub const LAYOUT__573: &MemoryPageOutLayout8LayoutArray = &[
    LAYOUT__574,
    LAYOUT__575,
    LAYOUT__576,
    LAYOUT__577,
    LAYOUT__578,
    LAYOUT__579,
    LAYOUT__580,
    LAYOUT__581,
];
pub const LAYOUT__572: &ControlStoreRootLayout = &ControlStoreRootLayout { _1: LAYOUT__573 };
pub const LAYOUT__571: &Control0_SuperArm5Layout = &Control0_SuperArm5Layout {
    _super: LAYOUT__572,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__588: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 117 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 118 },
            },
        },
    };
pub const LAYOUT__589: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 119 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 120 },
            },
        },
    };
pub const LAYOUT__590: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 121 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 122 },
            },
        },
    };
pub const LAYOUT__591: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 123 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 124 },
            },
        },
    };
pub const LAYOUT__592: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 125 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 126 },
            },
        },
    };
pub const LAYOUT__593: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 127 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 128 },
            },
        },
    };
pub const LAYOUT__594: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 129 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 130 },
            },
        },
    };
pub const LAYOUT__595: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 131 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 132 },
            },
        },
    };
pub const LAYOUT__596: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 133 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 134 },
            },
        },
    };
pub const LAYOUT__597: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 135 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 136 },
            },
        },
    };
pub const LAYOUT__598: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 137 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 138 },
            },
        },
    };
pub const LAYOUT__599: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 139 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 140 },
            },
        },
    };
pub const LAYOUT__600: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 141 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 142 },
            },
        },
    };
pub const LAYOUT__601: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 143 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 144 },
            },
        },
    };
pub const LAYOUT__602: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 145 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 146 },
            },
        },
    };
pub const LAYOUT__603: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 147 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 148 },
            },
        },
    };
pub const LAYOUT__587: &ControlTable_SuperArm0_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__588,
    LAYOUT__589,
    LAYOUT__590,
    LAYOUT__591,
    LAYOUT__592,
    LAYOUT__593,
    LAYOUT__594,
    LAYOUT__595,
    LAYOUT__596,
    LAYOUT__597,
    LAYOUT__598,
    LAYOUT__599,
    LAYOUT__600,
    LAYOUT__601,
    LAYOUT__602,
    LAYOUT__603,
];
pub const LAYOUT__586: &ControlTable_SuperArm0_SuperLayout = &ControlTable_SuperArm0_SuperLayout {
    _1: LAYOUT__587,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
};
pub const LAYOUT__585: &ControlTable_SuperArm0Layout = &ControlTable_SuperArm0Layout {
    _super: LAYOUT__586,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra4: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra5: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra6: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra7: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra8: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra9: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra14: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra15: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__607: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 149 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 150 },
            },
        },
    };
pub const LAYOUT__608: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 151 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 152 },
            },
        },
    };
pub const LAYOUT__609: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 153 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 154 },
            },
        },
    };
pub const LAYOUT__610: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 155 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 156 },
            },
        },
    };
pub const LAYOUT__611: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 157 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 158 },
            },
        },
    };
pub const LAYOUT__612: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 159 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 160 },
            },
        },
    };
pub const LAYOUT__613: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 161 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 162 },
            },
        },
    };
pub const LAYOUT__614: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 163 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 164 },
            },
        },
    };
pub const LAYOUT__615: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 165 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 166 },
            },
        },
    };
pub const LAYOUT__616: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 167 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 168 },
            },
        },
    };
pub const LAYOUT__617: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 169 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 170 },
            },
        },
    };
pub const LAYOUT__618: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 171 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 172 },
            },
        },
    };
pub const LAYOUT__619: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 173 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 174 },
            },
        },
    };
pub const LAYOUT__620: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 175 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 176 },
            },
        },
    };
pub const LAYOUT__621: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 177 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 178 },
            },
        },
    };
pub const LAYOUT__622: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 179 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 180 },
            },
        },
    };
pub const LAYOUT__606: &ControlTable_SuperArm1_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__607,
    LAYOUT__608,
    LAYOUT__609,
    LAYOUT__610,
    LAYOUT__611,
    LAYOUT__612,
    LAYOUT__613,
    LAYOUT__614,
    LAYOUT__615,
    LAYOUT__616,
    LAYOUT__617,
    LAYOUT__618,
    LAYOUT__619,
    LAYOUT__620,
    LAYOUT__621,
    LAYOUT__622,
];
pub const LAYOUT__605: &ControlTable_SuperArm1_SuperLayout = &ControlTable_SuperArm1_SuperLayout {
    _1: LAYOUT__606,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
};
pub const LAYOUT__604: &ControlTable_SuperArm1Layout = &ControlTable_SuperArm1Layout {
    _super: LAYOUT__605,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
};
pub const LAYOUT__584: &ControlTable_SuperLayout = &ControlTable_SuperLayout {
    arm0: LAYOUT__585,
    arm1: LAYOUT__604,
};
pub const LAYOUT__624: &ArgU16Layout16LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
];
pub const LAYOUT__625: &ArgU8Layout16LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
];
pub const LAYOUT__623: &_Arguments_ControlTable_SuperLayout =
    &_Arguments_ControlTable_SuperLayout {
        arg_u16: LAYOUT__624,
        arg_u8: LAYOUT__625,
    };
pub const LAYOUT__583: &ControlTableLayout = &ControlTableLayout {
    _super: LAYOUT__584,
    entry: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    mode: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    _arguments_control_table__super: LAYOUT__623,
};
pub const LAYOUT__582: &Control0_SuperArm6Layout = &Control0_SuperArm6Layout {
    _super: LAYOUT__583,
    _extra0: LAYOUT__466,
    _extra1: LAYOUT__467,
    _extra2: LAYOUT__470,
    _extra3: LAYOUT__471,
    _extra4: LAYOUT__474,
    _extra5: LAYOUT__475,
    _extra6: LAYOUT__478,
    _extra7: LAYOUT__479,
    _extra8: LAYOUT__482,
    _extra9: LAYOUT__483,
    _extra10: LAYOUT__486,
    _extra11: LAYOUT__487,
    _extra12: LAYOUT__490,
    _extra13: LAYOUT__491,
    _extra14: LAYOUT__494,
    _extra15: LAYOUT__495,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
};
pub const LAYOUT__628: &_Arguments_ControlDone__0Layout = &_Arguments_ControlDone__0Layout {
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    }],
};
pub const LAYOUT__630: &ControlDone__0Arm0_SuperLayout =
    &ControlDone__0Arm0_SuperLayout { _0: LAYOUT__41 };
pub const LAYOUT__631: &ControlDone__0Arm1Layout = &ControlDone__0Arm1Layout {
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__629: &ControlDone__0Layout = &ControlDone__0Layout {
    arm0: LAYOUT__630,
    arm1: LAYOUT__631,
};
pub const LAYOUT__627: &ControlDoneLayout = &ControlDoneLayout {
    _arguments_control_done__0: LAYOUT__628,
    _2: LAYOUT__629,
};
pub const LAYOUT__626: &Control0_SuperArm7Layout = &Control0_SuperArm7Layout {
    _super: LAYOUT__627,
    _extra0: LAYOUT__466,
    _extra1: LAYOUT__467,
    _extra2: LAYOUT__470,
    _extra3: LAYOUT__471,
    _extra4: LAYOUT__474,
    _extra5: LAYOUT__475,
    _extra6: LAYOUT__478,
    _extra7: LAYOUT__479,
    _extra8: LAYOUT__482,
    _extra9: LAYOUT__483,
    _extra10: LAYOUT__486,
    _extra11: LAYOUT__487,
    _extra12: LAYOUT__490,
    _extra13: LAYOUT__491,
    _extra14: LAYOUT__494,
    _extra15: LAYOUT__495,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra42: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra43: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra44: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra45: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra46: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra47: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra48: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra49: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra50: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra51: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra52: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra53: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra54: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__460: &Control0_SuperLayout = &Control0_SuperLayout {
    arm0: LAYOUT__461,
    arm1: LAYOUT__496,
    arm2: LAYOUT__536,
    arm3: LAYOUT__553,
    arm4: LAYOUT__557,
    arm5: LAYOUT__571,
    arm6: LAYOUT__582,
    arm7: LAYOUT__626,
};
pub const LAYOUT__632: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
    },
};
pub const LAYOUT__633: &_Arguments_Control0_SuperLayout = &_Arguments_Control0_SuperLayout {
    memory_arg: LAYOUT__534,
    cycle_arg: LAYOUT__535,
    arg_u16: LAYOUT__624,
    arg_u8: LAYOUT__625,
};
pub const LAYOUT__459: &Control0Layout = &Control0Layout {
    _super: LAYOUT__460,
    _0: LAYOUT__632,
    _arguments_control0__super: LAYOUT__633,
};
pub const LAYOUT__635: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
};
pub const LAYOUT__637: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
    },
};
pub const LAYOUT__638: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__636: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    upper_diff: LAYOUT__637,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    med14: LAYOUT__638,
};
pub const LAYOUT__640: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__466,
    LAYOUT__467,
    LAYOUT__470,
    LAYOUT__471,
    LAYOUT__474,
    LAYOUT__475,
    LAYOUT__478,
    LAYOUT__479,
];
pub const LAYOUT__641: &CycleArgLayout4LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
];
pub const LAYOUT__642: &ArgU16Layout4LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
];
pub const LAYOUT__643: &ArgU8Layout4LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
];
pub const LAYOUT__639: &_Arguments_ECall0OutputLayout = &_Arguments_ECall0OutputLayout {
    memory_arg: LAYOUT__640,
    cycle_arg: LAYOUT__641,
    arg_u16: LAYOUT__642,
    arg_u8: LAYOUT__643,
};
pub const LAYOUT__649: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__648: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__649 };
pub const LAYOUT__647: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__465,
    _0: LAYOUT__648,
};
pub const LAYOUT__652: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__651: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__652 };
pub const LAYOUT__650: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__469,
    _0: LAYOUT__651,
};
pub const LAYOUT__654: &NondetRegLayout6LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
];
pub const LAYOUT__653: &OneHot_6_Layout = &OneHot_6_Layout {
    _super: LAYOUT__654,
};
pub const LAYOUT__646: &MachineECallLayout = &MachineECallLayout {
    load_inst: LAYOUT__647,
    dispatch_idx: LAYOUT__650,
    dispatch: LAYOUT__653,
};
pub const LAYOUT__645: &ECall0OutputArm0Layout = &ECall0OutputArm0Layout {
    _super: LAYOUT__646,
    _extra0: LAYOUT__474,
    _extra1: LAYOUT__475,
    _extra2: LAYOUT__478,
    _extra3: LAYOUT__479,
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__656: &ECallTerminateLayout = &ECallTerminateLayout {
    a0: LAYOUT__647,
    a1: LAYOUT__650,
};
pub const LAYOUT__655: &ECall0OutputArm1Layout = &ECall0OutputArm1Layout {
    _super: LAYOUT__656,
    _extra0: LAYOUT__474,
    _extra1: LAYOUT__475,
    _extra2: LAYOUT__478,
    _extra3: LAYOUT__479,
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__661: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__660: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__661 };
pub const LAYOUT__659: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__473,
    _0: LAYOUT__660,
};
pub const LAYOUT__662: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__663: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
};
pub const LAYOUT__666: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
};
pub const LAYOUT__665: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__666 };
pub const LAYOUT__664: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__477,
    _0: LAYOUT__665,
};
pub const LAYOUT__668: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
};
pub const LAYOUT__670: &NondetRegLayout4LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
];
pub const LAYOUT__669: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__670,
};
pub const LAYOUT__667: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__668,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    low2_hot: LAYOUT__669,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
};
pub const LAYOUT__672: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
};
pub const LAYOUT__674: &NondetRegLayout4LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
];
pub const LAYOUT__673: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__674,
};
pub const LAYOUT__671: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__672,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low2_hot: LAYOUT__673,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
};
pub const LAYOUT__658: &ECallHostReadSetupLayout = &ECallHostReadSetupLayout {
    fd: LAYOUT__647,
    ptr: LAYOUT__650,
    len: LAYOUT__659,
    new_len: LAYOUT__662,
    diff: LAYOUT__663,
    _0: LAYOUT__664,
    ptr_decomp: LAYOUT__667,
    len_decomp: LAYOUT__671,
    len123: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    uneven: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
};
pub const LAYOUT__657: &ECall0OutputArm2Layout = &ECall0OutputArm2Layout {
    _super: LAYOUT__658,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__676: &ECallHostWriteLayout = &ECallHostWriteLayout {
    fd: LAYOUT__647,
    ptr: LAYOUT__650,
    len: LAYOUT__659,
    new_len: LAYOUT__662,
    diff: LAYOUT__663,
    _0: LAYOUT__664,
};
pub const LAYOUT__675: &ECall0OutputArm3Layout = &ECall0OutputArm3Layout {
    _super: LAYOUT__676,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra4: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
    _extra5: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__679: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__662,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    low2_hot: LAYOUT__669,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
};
pub const LAYOUT__680: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__469,
    _0: LAYOUT__651,
};
pub const LAYOUT__681: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__280,
    byte1: LAYOUT__282,
};
pub const LAYOUT__683: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__682: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__285,
    byte1: LAYOUT__683,
};
pub const LAYOUT__678: &ECallHostReadBytesLayout = &ECallHostReadBytesLayout {
    len_decomp: LAYOUT__679,
    len123: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    next_ptr_even: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    uneven: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    len_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
    low0: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
    orig_word: LAYOUT__647,
    _0: LAYOUT__680,
    old_bytes: LAYOUT__681,
    new_bytes_0: LAYOUT__682,
};
pub const LAYOUT__677: &ECall0OutputArm4Layout = &ECall0OutputArm4Layout {
    _super: LAYOUT__678,
    _extra0: LAYOUT__474,
    _extra1: LAYOUT__475,
    _extra2: LAYOUT__478,
    _extra3: LAYOUT__479,
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
};
pub const LAYOUT__686: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__663,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low2_hot: LAYOUT__673,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
};
pub const LAYOUT__689: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__465,
    _0: LAYOUT__648,
};
pub const LAYOUT__688: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    _0: LAYOUT__689,
};
pub const LAYOUT__690: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    _0: LAYOUT__680,
};
pub const LAYOUT__692: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__473,
    _0: LAYOUT__660,
};
pub const LAYOUT__691: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
    _0: LAYOUT__692,
};
pub const LAYOUT__694: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__477,
    _0: LAYOUT__665,
};
pub const LAYOUT__693: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    _0: LAYOUT__694,
};
pub const LAYOUT__687: &ECallHostReadWords__0_SuperLayout4LayoutArray =
    &[LAYOUT__688, LAYOUT__690, LAYOUT__691, LAYOUT__693];
pub const LAYOUT__685: &ECallHostReadWordsLayout = &ECallHostReadWordsLayout {
    len_decomp: LAYOUT__679,
    words_decomp: LAYOUT__686,
    _1: LAYOUT__687,
    new_len_high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
    len_zero: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
};
pub const LAYOUT__684: &ECall0OutputArm5Layout = &ECall0OutputArm5Layout {
    _super: LAYOUT__685,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra4: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
    _extra5: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__695: &ECall0OutputArm6Layout = &ECall0OutputArm6Layout {
    _extra0: LAYOUT__466,
    _extra1: LAYOUT__467,
    _extra2: LAYOUT__470,
    _extra3: LAYOUT__471,
    _extra4: LAYOUT__474,
    _extra5: LAYOUT__475,
    _extra6: LAYOUT__478,
    _extra7: LAYOUT__479,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__696: &ECall0OutputArm7Layout = &ECall0OutputArm7Layout {
    _extra0: LAYOUT__466,
    _extra1: LAYOUT__467,
    _extra2: LAYOUT__470,
    _extra3: LAYOUT__471,
    _extra4: LAYOUT__474,
    _extra5: LAYOUT__475,
    _extra6: LAYOUT__478,
    _extra7: LAYOUT__479,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__644: &ECall0OutputLayout = &ECall0OutputLayout {
    arm0: LAYOUT__645,
    arm1: LAYOUT__655,
    arm2: LAYOUT__657,
    arm3: LAYOUT__675,
    arm4: LAYOUT__677,
    arm5: LAYOUT__684,
    arm6: LAYOUT__695,
    arm7: LAYOUT__696,
};
pub const LAYOUT__698: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__697: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__698,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
    high16: LAYOUT__457,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
};
pub const LAYOUT__634: &ECall0Layout = &ECall0Layout {
    s0: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    s1: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    s2: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    _0: LAYOUT__635,
    pc_addr: LAYOUT__636,
    _arguments_e_call0_output: LAYOUT__639,
    output: LAYOUT__644,
    is_suspend: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    is_decode: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    is_p2_entry: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    is_sha_ecall: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    is_big_int_ecall: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    add_pc: LAYOUT__697,
};
pub const LAYOUT__700: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 193 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 194 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 195 },
        },
    },
};
pub const LAYOUT__702: &NondetRegLayout24LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 51 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 55 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 56 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 58 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 59 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 60 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 61 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 62 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 63 },
    },
];
pub const LAYOUT__701: &PoseidonStateLayout = &PoseidonStateLayout {
    has_state: &NondetRegLayout {
        _super: &Reg { offset: 29 },
    },
    state_addr: &NondetRegLayout {
        _super: &Reg { offset: 30 },
    },
    buf_out_addr: &NondetRegLayout {
        _super: &Reg { offset: 31 },
    },
    is_elem: &NondetRegLayout {
        _super: &Reg { offset: 32 },
    },
    check_out: &NondetRegLayout {
        _super: &Reg { offset: 33 },
    },
    load_tx_type: &NondetRegLayout {
        _super: &Reg { offset: 34 },
    },
    next_state: &NondetRegLayout {
        _super: &Reg { offset: 35 },
    },
    sub_state: &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
    buf_in_addr: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    count: &NondetRegLayout {
        _super: &Reg { offset: 38 },
    },
    mode: &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
    inner: LAYOUT__702,
    zcheck: &NondetExtRegLayout {
        _super: &Reg { offset: 64 },
    },
};
pub const LAYOUT__705: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
};
pub const LAYOUT__706: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
};
pub const LAYOUT__707: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
};
pub const LAYOUT__708: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
};
pub const LAYOUT__709: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
};
pub const LAYOUT__710: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
};
pub const LAYOUT__711: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
};
pub const LAYOUT__712: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
};
pub const LAYOUT__713: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
};
pub const LAYOUT__714: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
};
pub const LAYOUT__715: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 117 },
    },
};
pub const LAYOUT__716: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
};
pub const LAYOUT__717: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 124 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 125 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
};
pub const LAYOUT__718: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
};
pub const LAYOUT__719: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
};
pub const LAYOUT__720: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
};
pub const LAYOUT__704: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__705,
    LAYOUT__706,
    LAYOUT__707,
    LAYOUT__708,
    LAYOUT__709,
    LAYOUT__710,
    LAYOUT__711,
    LAYOUT__712,
    LAYOUT__713,
    LAYOUT__714,
    LAYOUT__715,
    LAYOUT__716,
    LAYOUT__717,
    LAYOUT__718,
    LAYOUT__719,
    LAYOUT__720,
];
pub const LAYOUT__721: &CycleArgLayout8LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
];
pub const LAYOUT__722: &ArgU16Layout24LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
];
pub const LAYOUT__723: &ArgU8Layout2LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
];
pub const LAYOUT__703: &_Arguments_Poseidon0StateLayout = &_Arguments_Poseidon0StateLayout {
    memory_arg: LAYOUT__704,
    cycle_arg: LAYOUT__721,
    arg_u16: LAYOUT__722,
    arg_u8: LAYOUT__723,
};
pub const LAYOUT__728: &PoseidonEntry_SuperArm0Layout = &PoseidonEntry_SuperArm0Layout {
    _super: LAYOUT__701,
    _extra0: LAYOUT__705,
    _extra1: LAYOUT__706,
    _extra2: LAYOUT__707,
    _extra3: LAYOUT__708,
    _extra4: LAYOUT__709,
    _extra5: LAYOUT__710,
    _extra6: LAYOUT__711,
    _extra7: LAYOUT__712,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__732: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__705,
    new_txn: LAYOUT__706,
};
pub const LAYOUT__734: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__733: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__734 };
pub const LAYOUT__731: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__732,
    _0: LAYOUT__733,
};
pub const LAYOUT__730: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__731,
};
pub const LAYOUT__737: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__707,
    new_txn: LAYOUT__708,
};
pub const LAYOUT__739: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__738: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__739 };
pub const LAYOUT__736: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__737,
    _0: LAYOUT__738,
};
pub const LAYOUT__735: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__736,
};
pub const LAYOUT__742: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__709,
    new_txn: LAYOUT__710,
};
pub const LAYOUT__744: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__743: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__744 };
pub const LAYOUT__741: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__742,
    _0: LAYOUT__743,
};
pub const LAYOUT__740: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__741,
};
pub const LAYOUT__746: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__711,
    new_txn: LAYOUT__712,
};
pub const LAYOUT__748: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__747: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__748 };
pub const LAYOUT__745: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__746,
    _0: LAYOUT__747,
};
pub const LAYOUT__729: &PoseidonEcallLayout = &PoseidonEcallLayout {
    _super: LAYOUT__701,
    state_addr: LAYOUT__730,
    buf_in_addr: LAYOUT__735,
    buf_out_addr: LAYOUT__740,
    bits_and_count: LAYOUT__745,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 196 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 197 },
        },
    },
    is_elem: &NondetRegLayout {
        _super: &Reg { offset: 198 },
    },
    check_out: &NondetRegLayout {
        _super: &Reg { offset: 199 },
    },
    count_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 200 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 201 },
        },
    },
};
pub const LAYOUT__727: &PoseidonEntry_SuperLayout = &PoseidonEntry_SuperLayout {
    _super: LAYOUT__701,
    arm0: LAYOUT__728,
    arm1: LAYOUT__729,
};
pub const LAYOUT__750: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__705,
    LAYOUT__706,
    LAYOUT__707,
    LAYOUT__708,
    LAYOUT__709,
    LAYOUT__710,
    LAYOUT__711,
    LAYOUT__712,
];
pub const LAYOUT__751: &CycleArgLayout4LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
];
pub const LAYOUT__749: &_Arguments_PoseidonEntry_SuperLayout =
    &_Arguments_PoseidonEntry_SuperLayout {
        memory_arg: LAYOUT__750,
        cycle_arg: LAYOUT__751,
    };
pub const LAYOUT__726: &PoseidonEntryLayout = &PoseidonEntryLayout {
    _super: LAYOUT__727,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 202 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 203 },
        },
    },
    _arguments_poseidon_entry__super: LAYOUT__749,
};
pub const LAYOUT__725: &Poseidon0StateArm0Layout = &Poseidon0StateArm0Layout {
    _super: LAYOUT__726,
    _extra0: LAYOUT__713,
    _extra1: LAYOUT__714,
    _extra2: LAYOUT__715,
    _extra3: LAYOUT__716,
    _extra4: LAYOUT__717,
    _extra5: LAYOUT__718,
    _extra6: LAYOUT__719,
    _extra7: LAYOUT__720,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
};
pub const LAYOUT__755: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__731,
};
pub const LAYOUT__756: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__736,
};
pub const LAYOUT__757: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__741,
};
pub const LAYOUT__758: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__745,
};
pub const LAYOUT__761: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__713,
    new_txn: LAYOUT__714,
};
pub const LAYOUT__763: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
};
pub const LAYOUT__762: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__763 };
pub const LAYOUT__760: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__761,
    _0: LAYOUT__762,
};
pub const LAYOUT__759: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__760,
};
pub const LAYOUT__766: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__715,
    new_txn: LAYOUT__716,
};
pub const LAYOUT__768: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
};
pub const LAYOUT__767: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__768 };
pub const LAYOUT__765: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__766,
    _0: LAYOUT__767,
};
pub const LAYOUT__764: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__765,
};
pub const LAYOUT__771: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__717,
    new_txn: LAYOUT__718,
};
pub const LAYOUT__773: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
};
pub const LAYOUT__772: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__773 };
pub const LAYOUT__770: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__771,
    _0: LAYOUT__772,
};
pub const LAYOUT__769: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__770,
};
pub const LAYOUT__776: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__719,
    new_txn: LAYOUT__720,
};
pub const LAYOUT__778: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
};
pub const LAYOUT__777: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__778 };
pub const LAYOUT__775: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__776,
    _0: LAYOUT__777,
};
pub const LAYOUT__774: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__775,
};
pub const LAYOUT__754: &ReadElemLayout8LayoutArray = &[
    LAYOUT__755,
    LAYOUT__756,
    LAYOUT__757,
    LAYOUT__758,
    LAYOUT__759,
    LAYOUT__764,
    LAYOUT__769,
    LAYOUT__774,
];
pub const LAYOUT__753: &PoseidonLoadStateLayout = &PoseidonLoadStateLayout {
    _super: LAYOUT__701,
    load_list: LAYOUT__754,
};
pub const LAYOUT__752: &Poseidon0StateArm1Layout = &Poseidon0StateArm1Layout {
    _super: LAYOUT__753,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
};
pub const LAYOUT__783: &OneHot_3_Layout = &OneHot_3_Layout {
    _super: &[
        &NondetRegLayout {
            _super: &Reg { offset: 196 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 197 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 198 },
        },
    ],
};
pub const LAYOUT__788: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__732 };
pub const LAYOUT__787: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__788,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__789: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__732,
    _0: LAYOUT__733,
};
pub const LAYOUT__786: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__731,
    arm1: LAYOUT__787,
    arm2: LAYOUT__789,
};
pub const LAYOUT__791: &MemoryArgLayout2LayoutArray = &[LAYOUT__705, LAYOUT__706];
pub const LAYOUT__790: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__791,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    }],
};
pub const LAYOUT__785: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__786,
    _arguments_memory_get__super: LAYOUT__790,
};
pub const LAYOUT__795: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__737 };
pub const LAYOUT__794: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__795,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__796: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__737,
    _0: LAYOUT__738,
};
pub const LAYOUT__793: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__736,
    arm1: LAYOUT__794,
    arm2: LAYOUT__796,
};
pub const LAYOUT__798: &MemoryArgLayout2LayoutArray = &[LAYOUT__707, LAYOUT__708];
pub const LAYOUT__797: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__798,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    }],
};
pub const LAYOUT__792: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__793,
    _arguments_memory_get__super: LAYOUT__797,
};
pub const LAYOUT__802: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__742 };
pub const LAYOUT__801: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__802,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__803: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__742,
    _0: LAYOUT__743,
};
pub const LAYOUT__800: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__741,
    arm1: LAYOUT__801,
    arm2: LAYOUT__803,
};
pub const LAYOUT__805: &MemoryArgLayout2LayoutArray = &[LAYOUT__709, LAYOUT__710];
pub const LAYOUT__804: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__805,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    }],
};
pub const LAYOUT__799: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__800,
    _arguments_memory_get__super: LAYOUT__804,
};
pub const LAYOUT__809: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__746 };
pub const LAYOUT__808: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__809,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__810: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__746,
    _0: LAYOUT__747,
};
pub const LAYOUT__807: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__745,
    arm1: LAYOUT__808,
    arm2: LAYOUT__810,
};
pub const LAYOUT__812: &MemoryArgLayout2LayoutArray = &[LAYOUT__711, LAYOUT__712];
pub const LAYOUT__811: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__812,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    }],
};
pub const LAYOUT__806: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__807,
    _arguments_memory_get__super: LAYOUT__811,
};
pub const LAYOUT__816: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__761 };
pub const LAYOUT__815: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__816,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
};
pub const LAYOUT__817: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__761,
    _0: LAYOUT__762,
};
pub const LAYOUT__814: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__760,
    arm1: LAYOUT__815,
    arm2: LAYOUT__817,
};
pub const LAYOUT__819: &MemoryArgLayout2LayoutArray = &[LAYOUT__713, LAYOUT__714];
pub const LAYOUT__818: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__819,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    }],
};
pub const LAYOUT__813: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__814,
    _arguments_memory_get__super: LAYOUT__818,
};
pub const LAYOUT__823: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__766 };
pub const LAYOUT__822: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__823,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
};
pub const LAYOUT__824: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__766,
    _0: LAYOUT__767,
};
pub const LAYOUT__821: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__765,
    arm1: LAYOUT__822,
    arm2: LAYOUT__824,
};
pub const LAYOUT__826: &MemoryArgLayout2LayoutArray = &[LAYOUT__715, LAYOUT__716];
pub const LAYOUT__825: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__826,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    }],
};
pub const LAYOUT__820: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__821,
    _arguments_memory_get__super: LAYOUT__825,
};
pub const LAYOUT__830: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__771 };
pub const LAYOUT__829: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__830,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
};
pub const LAYOUT__831: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__771,
    _0: LAYOUT__772,
};
pub const LAYOUT__828: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__770,
    arm1: LAYOUT__829,
    arm2: LAYOUT__831,
};
pub const LAYOUT__833: &MemoryArgLayout2LayoutArray = &[LAYOUT__717, LAYOUT__718];
pub const LAYOUT__832: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__833,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    }],
};
pub const LAYOUT__827: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__828,
    _arguments_memory_get__super: LAYOUT__832,
};
pub const LAYOUT__837: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__776 };
pub const LAYOUT__836: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__837,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
};
pub const LAYOUT__838: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__776,
    _0: LAYOUT__777,
};
pub const LAYOUT__835: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__775,
    arm1: LAYOUT__836,
    arm2: LAYOUT__838,
};
pub const LAYOUT__840: &MemoryArgLayout2LayoutArray = &[LAYOUT__719, LAYOUT__720];
pub const LAYOUT__839: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__840,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    }],
};
pub const LAYOUT__834: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__835,
    _arguments_memory_get__super: LAYOUT__839,
};
pub const LAYOUT__784: &MemoryGetLayout8LayoutArray = &[
    LAYOUT__785,
    LAYOUT__792,
    LAYOUT__799,
    LAYOUT__806,
    LAYOUT__813,
    LAYOUT__820,
    LAYOUT__827,
    LAYOUT__834,
];
pub const LAYOUT__782: &PoseidonLoadInShortLayout = &PoseidonLoadInShortLayout {
    _super: LAYOUT__701,
    tx_type: LAYOUT__783,
    load_list: LAYOUT__784,
};
pub const LAYOUT__841: &PoseidonLoadInLowLayout = &PoseidonLoadInLowLayout {
    _super: LAYOUT__701,
    tx_type: LAYOUT__783,
    load_list: LAYOUT__784,
};
pub const LAYOUT__842: &PoseidonLoadInHighLayout = &PoseidonLoadInHighLayout {
    _super: LAYOUT__701,
    tx_type: LAYOUT__783,
    load_list: LAYOUT__784,
};
pub const LAYOUT__781: &PoseidonLoadIn_SuperLayout = &PoseidonLoadIn_SuperLayout {
    _super: LAYOUT__701,
    arm0: LAYOUT__782,
    arm1: LAYOUT__841,
    arm2: LAYOUT__842,
};
pub const LAYOUT__843: &OneHot_3_Layout = &OneHot_3_Layout {
    _super: &[
        &NondetRegLayout {
            _super: &Reg { offset: 199 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 200 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 201 },
        },
    ],
};
pub const LAYOUT__844: &_Arguments_PoseidonLoadIn_SuperLayout =
    &_Arguments_PoseidonLoadIn_SuperLayout {
        memory_arg: LAYOUT__704,
        cycle_arg: LAYOUT__721,
    };
pub const LAYOUT__780: &PoseidonLoadInLayout = &PoseidonLoadInLayout {
    _super: LAYOUT__781,
    _0: LAYOUT__843,
    _arguments_poseidon_load_in__super: LAYOUT__844,
};
pub const LAYOUT__779: &Poseidon0StateArm2Layout = &Poseidon0StateArm2Layout {
    _super: LAYOUT__780,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
};
pub const LAYOUT__845: &Poseidon0StateArm3Layout = &Poseidon0StateArm3Layout {
    _super: LAYOUT__701,
    _extra0: LAYOUT__705,
    _extra1: LAYOUT__706,
    _extra2: LAYOUT__707,
    _extra3: LAYOUT__708,
    _extra4: LAYOUT__709,
    _extra5: LAYOUT__710,
    _extra6: LAYOUT__711,
    _extra7: LAYOUT__712,
    _extra8: LAYOUT__713,
    _extra9: LAYOUT__714,
    _extra10: LAYOUT__715,
    _extra11: LAYOUT__716,
    _extra12: LAYOUT__717,
    _extra13: LAYOUT__718,
    _extra14: LAYOUT__719,
    _extra15: LAYOUT__720,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra40: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra41: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra42: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra43: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra44: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra45: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra46: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra47: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra48: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
    _extra49: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
};
pub const LAYOUT__846: &Poseidon0StateArm4Layout = &Poseidon0StateArm4Layout {
    _super: LAYOUT__701,
    _extra0: LAYOUT__705,
    _extra1: LAYOUT__706,
    _extra2: LAYOUT__707,
    _extra3: LAYOUT__708,
    _extra4: LAYOUT__709,
    _extra5: LAYOUT__710,
    _extra6: LAYOUT__711,
    _extra7: LAYOUT__712,
    _extra8: LAYOUT__713,
    _extra9: LAYOUT__714,
    _extra10: LAYOUT__715,
    _extra11: LAYOUT__716,
    _extra12: LAYOUT__717,
    _extra13: LAYOUT__718,
    _extra14: LAYOUT__719,
    _extra15: LAYOUT__720,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra40: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra41: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra42: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra43: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra44: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra45: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra46: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra47: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra48: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
    _extra49: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
};
pub const LAYOUT__853: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__755 };
pub const LAYOUT__854: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__756 };
pub const LAYOUT__855: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__757 };
pub const LAYOUT__856: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__758 };
pub const LAYOUT__857: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__759 };
pub const LAYOUT__858: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__764 };
pub const LAYOUT__859: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__769 };
pub const LAYOUT__860: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__774 };
pub const LAYOUT__852: &PoseidonCheckOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__853,
    LAYOUT__854,
    LAYOUT__855,
    LAYOUT__856,
    LAYOUT__857,
    LAYOUT__858,
    LAYOUT__859,
    LAYOUT__860,
];
pub const LAYOUT__851: &PoseidonCheckOutLayout = &PoseidonCheckOutLayout {
    _super: LAYOUT__701,
    _1: LAYOUT__852,
    is_normal: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 196 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 197 },
        },
    },
};
pub const LAYOUT__850: &PoseidonDoOut_SuperArm0Layout = &PoseidonDoOut_SuperArm0Layout {
    _super: LAYOUT__851,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
};
pub const LAYOUT__865: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__866: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
};
pub const LAYOUT__867: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    }],
};
pub const LAYOUT__870: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
};
pub const LAYOUT__869: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__870 };
pub const LAYOUT__871: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__870 };
pub const LAYOUT__868: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__869,
    arm1: LAYOUT__871,
};
pub const LAYOUT__864: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__865,
    high: LAYOUT__866,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    _arguments_field_to_word__0: LAYOUT__867,
    _2: LAYOUT__868,
};
pub const LAYOUT__872: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__732,
    _0: LAYOUT__733,
};
pub const LAYOUT__863: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__864,
    mw: LAYOUT__872,
};
pub const LAYOUT__875: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
};
pub const LAYOUT__876: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__877: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    }],
};
pub const LAYOUT__880: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
};
pub const LAYOUT__879: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__880 };
pub const LAYOUT__881: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__880 };
pub const LAYOUT__878: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__879,
    arm1: LAYOUT__881,
};
pub const LAYOUT__874: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__875,
    high: LAYOUT__876,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    _arguments_field_to_word__0: LAYOUT__877,
    _2: LAYOUT__878,
};
pub const LAYOUT__882: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__737,
    _0: LAYOUT__738,
};
pub const LAYOUT__873: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__874,
    mw: LAYOUT__882,
};
pub const LAYOUT__885: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__886: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
};
pub const LAYOUT__887: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    }],
};
pub const LAYOUT__890: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
};
pub const LAYOUT__889: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__890 };
pub const LAYOUT__891: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__890 };
pub const LAYOUT__888: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__889,
    arm1: LAYOUT__891,
};
pub const LAYOUT__884: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__885,
    high: LAYOUT__886,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 198 },
    },
    _arguments_field_to_word__0: LAYOUT__887,
    _2: LAYOUT__888,
};
pub const LAYOUT__892: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__742,
    _0: LAYOUT__743,
};
pub const LAYOUT__883: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__884,
    mw: LAYOUT__892,
};
pub const LAYOUT__895: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__896: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__897: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    }],
};
pub const LAYOUT__899: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__224 };
pub const LAYOUT__900: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__224 };
pub const LAYOUT__898: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__899,
    arm1: LAYOUT__900,
};
pub const LAYOUT__894: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__895,
    high: LAYOUT__896,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 199 },
    },
    _arguments_field_to_word__0: LAYOUT__897,
    _2: LAYOUT__898,
};
pub const LAYOUT__901: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__746,
    _0: LAYOUT__747,
};
pub const LAYOUT__893: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__894,
    mw: LAYOUT__901,
};
pub const LAYOUT__904: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__905: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__906: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    }],
};
pub const LAYOUT__909: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
};
pub const LAYOUT__908: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__909 };
pub const LAYOUT__910: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__909 };
pub const LAYOUT__907: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__908,
    arm1: LAYOUT__910,
};
pub const LAYOUT__903: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__904,
    high: LAYOUT__905,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 200 },
    },
    _arguments_field_to_word__0: LAYOUT__906,
    _2: LAYOUT__907,
};
pub const LAYOUT__911: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__761,
    _0: LAYOUT__762,
};
pub const LAYOUT__902: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__903,
    mw: LAYOUT__911,
};
pub const LAYOUT__914: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__915: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
};
pub const LAYOUT__916: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    }],
};
pub const LAYOUT__919: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__918: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__919 };
pub const LAYOUT__920: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__919 };
pub const LAYOUT__917: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__918,
    arm1: LAYOUT__920,
};
pub const LAYOUT__913: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__914,
    high: LAYOUT__915,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 201 },
    },
    _arguments_field_to_word__0: LAYOUT__916,
    _2: LAYOUT__917,
};
pub const LAYOUT__921: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__766,
    _0: LAYOUT__767,
};
pub const LAYOUT__912: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__913,
    mw: LAYOUT__921,
};
pub const LAYOUT__924: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
};
pub const LAYOUT__925: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
};
pub const LAYOUT__926: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    }],
};
pub const LAYOUT__929: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
};
pub const LAYOUT__928: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__929 };
pub const LAYOUT__930: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__929 };
pub const LAYOUT__927: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__928,
    arm1: LAYOUT__930,
};
pub const LAYOUT__923: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__924,
    high: LAYOUT__925,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 202 },
    },
    _arguments_field_to_word__0: LAYOUT__926,
    _2: LAYOUT__927,
};
pub const LAYOUT__931: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__771,
    _0: LAYOUT__772,
};
pub const LAYOUT__922: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__923,
    mw: LAYOUT__931,
};
pub const LAYOUT__934: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__935: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__936: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    }],
};
pub const LAYOUT__939: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
};
pub const LAYOUT__938: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__939 };
pub const LAYOUT__940: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__939 };
pub const LAYOUT__937: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__938,
    arm1: LAYOUT__940,
};
pub const LAYOUT__933: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__934,
    high: LAYOUT__935,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 203 },
    },
    _arguments_field_to_word__0: LAYOUT__936,
    _2: LAYOUT__937,
};
pub const LAYOUT__941: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__776,
    _0: LAYOUT__777,
};
pub const LAYOUT__932: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__933,
    mw: LAYOUT__941,
};
pub const LAYOUT__862: &PoseidonStoreOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__863,
    LAYOUT__873,
    LAYOUT__883,
    LAYOUT__893,
    LAYOUT__902,
    LAYOUT__912,
    LAYOUT__922,
    LAYOUT__932,
];
pub const LAYOUT__861: &PoseidonStoreOutLayout = &PoseidonStoreOutLayout {
    _super: LAYOUT__701,
    _1: LAYOUT__862,
    is_normal: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 204 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 205 },
        },
    },
    ext_inv: &NondetExtRegLayout {
        _super: &Reg { offset: 206 },
    },
};
pub const LAYOUT__849: &PoseidonDoOut_SuperLayout = &PoseidonDoOut_SuperLayout {
    _super: LAYOUT__701,
    arm0: LAYOUT__850,
    arm1: LAYOUT__861,
};
pub const LAYOUT__942: &_Arguments_PoseidonDoOut_SuperLayout =
    &_Arguments_PoseidonDoOut_SuperLayout {
        memory_arg: LAYOUT__704,
        cycle_arg: LAYOUT__721,
        arg_u16: LAYOUT__722,
    };
pub const LAYOUT__848: &PoseidonDoOutLayout = &PoseidonDoOutLayout {
    _super: LAYOUT__849,
    _arguments_poseidon_do_out__super: LAYOUT__942,
};
pub const LAYOUT__847: &Poseidon0StateArm5Layout = &Poseidon0StateArm5Layout {
    _super: LAYOUT__848,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
};
pub const LAYOUT__945: &PoseidonPaging_SuperLayout = &PoseidonPaging_SuperLayout {
    _super: LAYOUT__701,
    arm0: LAYOUT__701,
    arm1: LAYOUT__701,
    arm2: LAYOUT__701,
    arm3: LAYOUT__701,
    arm4: LAYOUT__701,
    arm5: LAYOUT__701,
};
pub const LAYOUT__947: &NondetRegLayout6LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 198 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 199 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 200 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 201 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 202 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 203 },
    },
];
pub const LAYOUT__946: &OneHot_6_Layout = &OneHot_6_Layout {
    _super: LAYOUT__947,
};
pub const LAYOUT__949: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__948: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__865,
    _0: LAYOUT__949,
};
pub const LAYOUT__950: &_Arguments_PoseidonPaging__1Layout = &_Arguments_PoseidonPaging__1Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    }],
    arg_u8: &[&ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    }],
};
pub const LAYOUT__954: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
};
pub const LAYOUT__953: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__866,
    _0: LAYOUT__954,
};
pub const LAYOUT__952: &PoseidonPaging__1Arm0_SuperLayout =
    &PoseidonPaging__1Arm0_SuperLayout { _0: LAYOUT__953 };
pub const LAYOUT__955: &PoseidonPaging__1Arm1_SuperLayout =
    &PoseidonPaging__1Arm1_SuperLayout { _0: LAYOUT__953 };
pub const LAYOUT__951: &PoseidonPaging__1Layout = &PoseidonPaging__1Layout {
    arm0: LAYOUT__952,
    arm1: LAYOUT__955,
};
pub const LAYOUT__944: &PoseidonPagingLayout = &PoseidonPagingLayout {
    _super: LAYOUT__945,
    cur_idx: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    cur_mode: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    mode_split: LAYOUT__946,
    _0: LAYOUT__948,
    _arguments_poseidon_paging__1: LAYOUT__950,
    _3: LAYOUT__951,
    _4: &NondetRegLayout {
        _super: &Reg { offset: 204 },
    },
};
pub const LAYOUT__943: &Poseidon0StateArm6Layout = &Poseidon0StateArm6Layout {
    _super: LAYOUT__944,
    _extra0: LAYOUT__705,
    _extra1: LAYOUT__706,
    _extra2: LAYOUT__707,
    _extra3: LAYOUT__708,
    _extra4: LAYOUT__709,
    _extra5: LAYOUT__710,
    _extra6: LAYOUT__711,
    _extra7: LAYOUT__712,
    _extra8: LAYOUT__713,
    _extra9: LAYOUT__714,
    _extra10: LAYOUT__715,
    _extra11: LAYOUT__716,
    _extra12: LAYOUT__717,
    _extra13: LAYOUT__718,
    _extra14: LAYOUT__719,
    _extra15: LAYOUT__720,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra40: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra41: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra42: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra43: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra44: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra45: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
};
pub const LAYOUT__959: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__864,
    mw: LAYOUT__872,
};
pub const LAYOUT__960: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__874,
    mw: LAYOUT__882,
};
pub const LAYOUT__961: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__884,
    mw: LAYOUT__892,
};
pub const LAYOUT__962: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__894,
    mw: LAYOUT__901,
};
pub const LAYOUT__963: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__903,
    mw: LAYOUT__911,
};
pub const LAYOUT__964: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__913,
    mw: LAYOUT__921,
};
pub const LAYOUT__965: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__923,
    mw: LAYOUT__931,
};
pub const LAYOUT__966: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__933,
    mw: LAYOUT__941,
};
pub const LAYOUT__958: &PoseidonStoreState__0_SuperLayout8LayoutArray = &[
    LAYOUT__959,
    LAYOUT__960,
    LAYOUT__961,
    LAYOUT__962,
    LAYOUT__963,
    LAYOUT__964,
    LAYOUT__965,
    LAYOUT__966,
];
pub const LAYOUT__957: &PoseidonStoreStateLayout = &PoseidonStoreStateLayout {
    _super: LAYOUT__701,
    _1: LAYOUT__958,
};
pub const LAYOUT__956: &Poseidon0StateArm7Layout = &Poseidon0StateArm7Layout {
    _super: LAYOUT__957,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
};
pub const LAYOUT__724: &Poseidon0StateLayout = &Poseidon0StateLayout {
    _super: LAYOUT__701,
    arm0: LAYOUT__725,
    arm1: LAYOUT__752,
    arm2: LAYOUT__779,
    arm3: LAYOUT__845,
    arm4: LAYOUT__846,
    arm5: LAYOUT__847,
    arm6: LAYOUT__943,
    arm7: LAYOUT__956,
};
pub const LAYOUT__699: &Poseidon0Layout = &Poseidon0Layout {
    _0: LAYOUT__700,
    state: LAYOUT__701,
    _arguments_poseidon0_state: LAYOUT__703,
    state_redef: LAYOUT__724,
};
pub const LAYOUT__968: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
};
pub const LAYOUT__973: &SBoxLayout24LayoutArray = &[
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
];
pub const LAYOUT__972: &DoExtRoundLayout = &DoExtRoundLayout { _1: LAYOUT__973 };
pub const LAYOUT__975: &NondetRegLayout8LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
];
pub const LAYOUT__974: &OneHot_8_Layout = &OneHot_8_Layout {
    _super: LAYOUT__975,
};
pub const LAYOUT__971: &DoExtRoundByIdxLayout = &DoExtRoundByIdxLayout {
    _super: LAYOUT__972,
    idx_hot: LAYOUT__974,
};
pub const LAYOUT__970: &PoseidonExtRoundLayout = &PoseidonExtRoundLayout {
    _super: LAYOUT__701,
    is_round3: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
    is_round7: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    last_block: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
    next_inner: LAYOUT__971,
};
pub const LAYOUT__979: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
};
pub const LAYOUT__980: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__981: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
};
pub const LAYOUT__982: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__983: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
};
pub const LAYOUT__984: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
};
pub const LAYOUT__985: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__986: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
};
pub const LAYOUT__987: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__988: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
};
pub const LAYOUT__989: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__990: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
};
pub const LAYOUT__991: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
    },
};
pub const LAYOUT__992: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
    },
};
pub const LAYOUT__993: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
};
pub const LAYOUT__994: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__995: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
};
pub const LAYOUT__996: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
};
pub const LAYOUT__997: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
};
pub const LAYOUT__998: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__999: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
};
pub const LAYOUT__978: &DoIntRoundLayout21LayoutArray = &[
    LAYOUT__979,
    LAYOUT__980,
    LAYOUT__981,
    LAYOUT__982,
    LAYOUT__983,
    LAYOUT__984,
    LAYOUT__985,
    LAYOUT__986,
    LAYOUT__987,
    LAYOUT__988,
    LAYOUT__989,
    LAYOUT__990,
    LAYOUT__991,
    LAYOUT__992,
    LAYOUT__993,
    LAYOUT__994,
    LAYOUT__995,
    LAYOUT__996,
    LAYOUT__997,
    LAYOUT__998,
    LAYOUT__999,
];
pub const LAYOUT__977: &DoIntRoundsLayout = &DoIntRoundsLayout {
    _super: LAYOUT__978,
};
pub const LAYOUT__976: &PoseidonIntRoundsLayout = &PoseidonIntRoundsLayout {
    _super: LAYOUT__701,
    next_inner: LAYOUT__977,
};
pub const LAYOUT__969: &Poseidon1StateLayout = &Poseidon1StateLayout {
    _super: LAYOUT__701,
    arm0: LAYOUT__970,
    arm1: LAYOUT__976,
    arm2: LAYOUT__701,
    arm3: LAYOUT__701,
    arm4: LAYOUT__701,
    arm5: LAYOUT__701,
    arm6: LAYOUT__701,
    arm7: LAYOUT__701,
};
pub const LAYOUT__967: &Poseidon1Layout = &Poseidon1Layout {
    _0: LAYOUT__968,
    state: LAYOUT__701,
    state_redef: LAYOUT__969,
};
pub const LAYOUT__1001: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    },
};
pub const LAYOUT__1003: &NondetRegLayout32LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 38 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 51 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 55 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 56 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 58 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 59 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 60 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 61 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 62 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 63 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 65 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 66 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
];
pub const LAYOUT__1004: &NondetRegLayout32LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
];
pub const LAYOUT__1005: &NondetRegLayout32LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 117 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 124 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 125 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
];
pub const LAYOUT__1002: &ShaStateLayout = &ShaStateLayout {
    state_in_addr: &NondetRegLayout {
        _super: &Reg { offset: 29 },
    },
    state_out_addr: &NondetRegLayout {
        _super: &Reg { offset: 30 },
    },
    data_addr: &NondetRegLayout {
        _super: &Reg { offset: 31 },
    },
    count: &NondetRegLayout {
        _super: &Reg { offset: 32 },
    },
    k_addr: &NondetRegLayout {
        _super: &Reg { offset: 33 },
    },
    round: &NondetRegLayout {
        _super: &Reg { offset: 34 },
    },
    next_state: &NondetRegLayout {
        _super: &Reg { offset: 35 },
    },
    a: LAYOUT__1003,
    e: LAYOUT__1004,
    w: LAYOUT__1005,
};
pub const LAYOUT__1008: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
};
pub const LAYOUT__1009: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 140 },
    },
};
pub const LAYOUT__1010: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 141 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 143 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 144 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 145 },
    },
};
pub const LAYOUT__1011: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 146 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 147 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 148 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 149 },
    },
};
pub const LAYOUT__1012: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 150 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 151 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 152 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 153 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
};
pub const LAYOUT__1013: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 151 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
};
pub const LAYOUT__1014: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 161 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 162 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 163 },
    },
};
pub const LAYOUT__1015: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 167 },
    },
};
pub const LAYOUT__1016: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 168 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 170 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 172 },
    },
};
pub const LAYOUT__1017: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 173 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 174 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
};
pub const LAYOUT__1007: &MemoryArgLayout10LayoutArray = &[
    LAYOUT__1008,
    LAYOUT__1009,
    LAYOUT__1010,
    LAYOUT__1011,
    LAYOUT__1012,
    LAYOUT__1013,
    LAYOUT__1014,
    LAYOUT__1015,
    LAYOUT__1016,
    LAYOUT__1017,
];
pub const LAYOUT__1018: &CycleArgLayout5LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
];
pub const LAYOUT__1006: &_Arguments_Sha0StateLayout = &_Arguments_Sha0StateLayout {
    memory_arg: LAYOUT__1007,
    cycle_arg: LAYOUT__1018,
};
pub const LAYOUT__1023: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1008,
    new_txn: LAYOUT__1009,
};
pub const LAYOUT__1025: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__1024: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1025 };
pub const LAYOUT__1022: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1023,
    _0: LAYOUT__1024,
};
pub const LAYOUT__1021: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1022,
};
pub const LAYOUT__1028: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1010,
    new_txn: LAYOUT__1011,
};
pub const LAYOUT__1030: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__1029: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1030 };
pub const LAYOUT__1027: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1028,
    _0: LAYOUT__1029,
};
pub const LAYOUT__1026: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1027,
};
pub const LAYOUT__1033: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1012,
    new_txn: LAYOUT__1013,
};
pub const LAYOUT__1035: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
};
pub const LAYOUT__1034: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1035 };
pub const LAYOUT__1032: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1033,
    _0: LAYOUT__1034,
};
pub const LAYOUT__1031: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1032,
};
pub const LAYOUT__1037: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1014,
    new_txn: LAYOUT__1015,
};
pub const LAYOUT__1039: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    },
};
pub const LAYOUT__1038: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1039 };
pub const LAYOUT__1036: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1037,
    _0: LAYOUT__1038,
};
pub const LAYOUT__1042: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1016,
    new_txn: LAYOUT__1017,
};
pub const LAYOUT__1044: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1043: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1044 };
pub const LAYOUT__1041: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1042,
    _0: LAYOUT__1043,
};
pub const LAYOUT__1040: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1041,
};
pub const LAYOUT__1020: &ShaEcallLayout = &ShaEcallLayout {
    _super: LAYOUT__1002,
    state_in_addr: LAYOUT__1021,
    state_out_addr: LAYOUT__1026,
    data_addr: LAYOUT__1031,
    _0: LAYOUT__1036,
    k_addr: LAYOUT__1040,
};
pub const LAYOUT__1047: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1033,
    _0: LAYOUT__1034,
};
pub const LAYOUT__1048: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1037,
    _0: LAYOUT__1038,
};
pub const LAYOUT__1046: &ShaLoadStateLayout = &ShaLoadStateLayout {
    _super: LAYOUT__1002,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
    },
    count_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 193 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 194 },
        },
    },
    a32: LAYOUT__1022,
    e32: LAYOUT__1027,
    _0: LAYOUT__1047,
    _1: LAYOUT__1048,
};
pub const LAYOUT__1045: &Sha0StateArm1Layout = &Sha0StateArm1Layout {
    _super: LAYOUT__1046,
    _extra0: LAYOUT__1016,
    _extra1: LAYOUT__1017,
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1052: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__1003,
};
pub const LAYOUT__1053: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 193 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 194 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 195 },
    },
};
pub const LAYOUT__1054: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 198 },
    },
};
pub const LAYOUT__1051: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1052,
    low_carry: LAYOUT__1053,
    high_carry: LAYOUT__1054,
};
pub const LAYOUT__1056: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__1004,
};
pub const LAYOUT__1057: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 199 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 200 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 201 },
    },
};
pub const LAYOUT__1058: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 202 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 203 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 204 },
    },
};
pub const LAYOUT__1055: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1056,
    low_carry: LAYOUT__1057,
    high_carry: LAYOUT__1058,
};
pub const LAYOUT__1050: &ShaLoadDataLayout = &ShaLoadDataLayout {
    _super: LAYOUT__1002,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
    },
    k: LAYOUT__1022,
    w_mem: LAYOUT__1027,
    w_bits: LAYOUT__1005,
    a: LAYOUT__1051,
    e: LAYOUT__1055,
};
pub const LAYOUT__1049: &Sha0StateArm2Layout = &Sha0StateArm2Layout {
    _super: LAYOUT__1050,
    _extra0: LAYOUT__1012,
    _extra1: LAYOUT__1013,
    _extra2: LAYOUT__1014,
    _extra3: LAYOUT__1015,
    _extra4: LAYOUT__1016,
    _extra5: LAYOUT__1017,
    _extra6: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra7: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    },
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1062: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__1005,
};
pub const LAYOUT__1061: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1062,
    low_carry: LAYOUT__1053,
    high_carry: LAYOUT__1054,
};
pub const LAYOUT__1063: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1052,
    low_carry: LAYOUT__1057,
    high_carry: LAYOUT__1058,
};
pub const LAYOUT__1065: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 205 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 206 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 207 },
    },
};
pub const LAYOUT__1066: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 208 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 209 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 210 },
    },
};
pub const LAYOUT__1064: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1056,
    low_carry: LAYOUT__1065,
    high_carry: LAYOUT__1066,
};
pub const LAYOUT__1060: &ShaMixLayout = &ShaMixLayout {
    _super: LAYOUT__1002,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
    },
    k: LAYOUT__1022,
    w_bits: LAYOUT__1061,
    a: LAYOUT__1063,
    e: LAYOUT__1064,
};
pub const LAYOUT__1059: &Sha0StateArm3Layout = &Sha0StateArm3Layout {
    _super: LAYOUT__1060,
    _extra0: LAYOUT__1010,
    _extra1: LAYOUT__1011,
    _extra2: LAYOUT__1012,
    _extra3: LAYOUT__1013,
    _extra4: LAYOUT__1014,
    _extra5: LAYOUT__1015,
    _extra6: LAYOUT__1016,
    _extra7: LAYOUT__1017,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1070: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 195 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
};
pub const LAYOUT__1071: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 198 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 199 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 200 },
    },
};
pub const LAYOUT__1069: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1052,
    low_carry: LAYOUT__1070,
    high_carry: LAYOUT__1071,
};
pub const LAYOUT__1073: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 201 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 202 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 203 },
    },
};
pub const LAYOUT__1074: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 204 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 205 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 206 },
    },
};
pub const LAYOUT__1072: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1056,
    low_carry: LAYOUT__1073,
    high_carry: LAYOUT__1074,
};
pub const LAYOUT__1075: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1023,
    _0: LAYOUT__1024,
};
pub const LAYOUT__1076: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1028,
    _0: LAYOUT__1029,
};
pub const LAYOUT__1068: &ShaStoreStateLayout = &ShaStoreStateLayout {
    _super: LAYOUT__1002,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
    },
    count_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 193 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 194 },
        },
    },
    a: LAYOUT__1069,
    e: LAYOUT__1072,
    _1: LAYOUT__1075,
    _2: LAYOUT__1076,
};
pub const LAYOUT__1067: &Sha0StateArm4Layout = &Sha0StateArm4Layout {
    _super: LAYOUT__1068,
    _extra0: LAYOUT__1012,
    _extra1: LAYOUT__1013,
    _extra2: LAYOUT__1014,
    _extra3: LAYOUT__1015,
    _extra4: LAYOUT__1016,
    _extra5: LAYOUT__1017,
    _extra6: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra7: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    },
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1077: &Sha0StateArm5Layout = &Sha0StateArm5Layout {
    _super: LAYOUT__1002,
    _extra0: LAYOUT__1008,
    _extra1: LAYOUT__1009,
    _extra2: LAYOUT__1010,
    _extra3: LAYOUT__1011,
    _extra4: LAYOUT__1012,
    _extra5: LAYOUT__1013,
    _extra6: LAYOUT__1014,
    _extra7: LAYOUT__1015,
    _extra8: LAYOUT__1016,
    _extra9: LAYOUT__1017,
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1078: &Sha0StateArm6Layout = &Sha0StateArm6Layout {
    _super: LAYOUT__1002,
    _extra0: LAYOUT__1008,
    _extra1: LAYOUT__1009,
    _extra2: LAYOUT__1010,
    _extra3: LAYOUT__1011,
    _extra4: LAYOUT__1012,
    _extra5: LAYOUT__1013,
    _extra6: LAYOUT__1014,
    _extra7: LAYOUT__1015,
    _extra8: LAYOUT__1016,
    _extra9: LAYOUT__1017,
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1079: &Sha0StateArm7Layout = &Sha0StateArm7Layout {
    _super: LAYOUT__1002,
    _extra0: LAYOUT__1008,
    _extra1: LAYOUT__1009,
    _extra2: LAYOUT__1010,
    _extra3: LAYOUT__1011,
    _extra4: LAYOUT__1012,
    _extra5: LAYOUT__1013,
    _extra6: LAYOUT__1014,
    _extra7: LAYOUT__1015,
    _extra8: LAYOUT__1016,
    _extra9: LAYOUT__1017,
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1019: &Sha0StateLayout = &Sha0StateLayout {
    _super: LAYOUT__1002,
    arm0: LAYOUT__1020,
    arm1: LAYOUT__1045,
    arm2: LAYOUT__1049,
    arm3: LAYOUT__1059,
    arm4: LAYOUT__1067,
    arm5: LAYOUT__1077,
    arm6: LAYOUT__1078,
    arm7: LAYOUT__1079,
};
pub const LAYOUT__1000: &Sha0Layout = &Sha0Layout {
    _0: LAYOUT__1001,
    state: LAYOUT__1002,
    _arguments_sha0_state: LAYOUT__1006,
    state_redef: LAYOUT__1019,
};
pub const LAYOUT__1081: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
};
pub const LAYOUT__1083: &NondetRegLayout16LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 34 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 35 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 38 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
];
pub const LAYOUT__1082: &BigIntStateLayout = &BigIntStateLayout {
    is_ecall: &NondetRegLayout {
        _super: &Reg { offset: 29 },
    },
    mode: &NondetRegLayout {
        _super: &Reg { offset: 30 },
    },
    pc: &NondetRegLayout {
        _super: &Reg { offset: 31 },
    },
    poly_op: &NondetRegLayout {
        _super: &Reg { offset: 32 },
    },
    coeff: &NondetRegLayout {
        _super: &Reg { offset: 33 },
    },
    bytes: LAYOUT__1083,
    next_state: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
};
pub const LAYOUT__1086: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 51 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 55 },
    },
};
pub const LAYOUT__1087: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 56 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 58 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 59 },
    },
};
pub const LAYOUT__1088: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 60 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 61 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 62 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 63 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
};
pub const LAYOUT__1089: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 65 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 61 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 66 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
};
pub const LAYOUT__1090: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
};
pub const LAYOUT__1091: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
};
pub const LAYOUT__1092: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
};
pub const LAYOUT__1093: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
};
pub const LAYOUT__1094: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
};
pub const LAYOUT__1095: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
};
pub const LAYOUT__1096: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
};
pub const LAYOUT__1097: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
};
pub const LAYOUT__1085: &MemoryArgLayout12LayoutArray = &[
    LAYOUT__1086,
    LAYOUT__1087,
    LAYOUT__1088,
    LAYOUT__1089,
    LAYOUT__1090,
    LAYOUT__1091,
    LAYOUT__1092,
    LAYOUT__1093,
    LAYOUT__1094,
    LAYOUT__1095,
    LAYOUT__1096,
    LAYOUT__1097,
];
pub const LAYOUT__1098: &CycleArgLayout6LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
];
pub const LAYOUT__1099: &ArgU8Layout18LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
];
pub const LAYOUT__1100: &ArgU16Layout4LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
];
pub const LAYOUT__1084: &_Arguments_BigInt0StateLayout = &_Arguments_BigInt0StateLayout {
    memory_arg: LAYOUT__1085,
    cycle_arg: LAYOUT__1098,
    arg_u8: LAYOUT__1099,
    arg_u16: LAYOUT__1100,
};
pub const LAYOUT__1105: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1086,
    new_txn: LAYOUT__1087,
};
pub const LAYOUT__1104: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1105,
    _0: LAYOUT__511,
};
pub const LAYOUT__1108: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1088,
    new_txn: LAYOUT__1089,
};
pub const LAYOUT__1107: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1108,
    _0: LAYOUT__515,
};
pub const LAYOUT__1106: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1107,
};
pub const LAYOUT__1103: &BigIntEcallLayout = &BigIntEcallLayout {
    _super: LAYOUT__1082,
    mode: LAYOUT__1104,
    pc: LAYOUT__1106,
};
pub const LAYOUT__1102: &BigInt0StateArm0Layout = &BigInt0StateArm0Layout {
    _super: LAYOUT__1103,
    _extra0: LAYOUT__1090,
    _extra1: LAYOUT__1091,
    _extra2: LAYOUT__1092,
    _extra3: LAYOUT__1093,
    _extra4: LAYOUT__1094,
    _extra5: LAYOUT__1095,
    _extra6: LAYOUT__1096,
    _extra7: LAYOUT__1097,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra14: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra15: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__1111: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
};
pub const LAYOUT__1112: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__1110: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1111,
    byte1: LAYOUT__1112,
};
pub const LAYOUT__1113: &NondetRegLayout5LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 167 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 168 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 170 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
];
pub const LAYOUT__1115: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
};
pub const LAYOUT__1116: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
};
pub const LAYOUT__1114: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__1115,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
    high16: LAYOUT__1116,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
};
pub const LAYOUT__1117: &OneHot_3_Layout = &OneHot_3_Layout {
    _super: &[
        &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    ],
};
pub const LAYOUT__1119: &ArgU16Layout2LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
];
pub const LAYOUT__1120: &ArgU8Layout16LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
];
pub const LAYOUT__1121: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__1090,
    LAYOUT__1091,
    LAYOUT__1092,
    LAYOUT__1093,
    LAYOUT__1094,
    LAYOUT__1095,
    LAYOUT__1096,
    LAYOUT__1097,
];
pub const LAYOUT__1122: &CycleArgLayout4LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
];
pub const LAYOUT__1118: &_Arguments_BigIntStepBytesLayout = &_Arguments_BigIntStepBytesLayout {
    arg_u16: LAYOUT__1119,
    arg_u8: LAYOUT__1120,
    memory_arg: LAYOUT__1121,
    cycle_arg: LAYOUT__1122,
};
pub const LAYOUT__1127: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
};
pub const LAYOUT__1128: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__1126: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    upper_diff: LAYOUT__1127,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    med14: LAYOUT__1128,
};
pub const LAYOUT__1125: &BigIntAddrLayout = &BigIntAddrLayout {
    _super: LAYOUT__1126,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__1133: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
};
pub const LAYOUT__1134: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__1132: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1133,
    byte1: LAYOUT__1134,
};
pub const LAYOUT__1136: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
};
pub const LAYOUT__1137: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
};
pub const LAYOUT__1135: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1136,
    byte1: LAYOUT__1137,
};
pub const LAYOUT__1131: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1132,
    high: LAYOUT__1135,
};
pub const LAYOUT__1139: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1090,
    new_txn: LAYOUT__1091,
};
pub const LAYOUT__1138: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1139,
    _0: LAYOUT__519,
};
pub const LAYOUT__1130: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1131,
    _0: LAYOUT__1138,
};
pub const LAYOUT__1143: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
};
pub const LAYOUT__1144: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
};
pub const LAYOUT__1142: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1143,
    byte1: LAYOUT__1144,
};
pub const LAYOUT__1146: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
};
pub const LAYOUT__1147: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
};
pub const LAYOUT__1145: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1146,
    byte1: LAYOUT__1147,
};
pub const LAYOUT__1141: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1142,
    high: LAYOUT__1145,
};
pub const LAYOUT__1149: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1092,
    new_txn: LAYOUT__1093,
};
pub const LAYOUT__1148: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1149,
    _0: LAYOUT__523,
};
pub const LAYOUT__1140: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1141,
    _0: LAYOUT__1148,
};
pub const LAYOUT__1153: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__1154: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
};
pub const LAYOUT__1152: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1153,
    byte1: LAYOUT__1154,
};
pub const LAYOUT__1156: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
};
pub const LAYOUT__1157: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__1155: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1156,
    byte1: LAYOUT__1157,
};
pub const LAYOUT__1151: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1152,
    high: LAYOUT__1155,
};
pub const LAYOUT__1159: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1094,
    new_txn: LAYOUT__1095,
};
pub const LAYOUT__1158: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1159,
    _0: LAYOUT__527,
};
pub const LAYOUT__1150: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1151,
    _0: LAYOUT__1158,
};
pub const LAYOUT__1163: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__1164: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
};
pub const LAYOUT__1162: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1163,
    byte1: LAYOUT__1164,
};
pub const LAYOUT__1166: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
};
pub const LAYOUT__1167: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
};
pub const LAYOUT__1165: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1166,
    byte1: LAYOUT__1167,
};
pub const LAYOUT__1161: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1162,
    high: LAYOUT__1165,
};
pub const LAYOUT__1169: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1096,
    new_txn: LAYOUT__1097,
};
pub const LAYOUT__1168: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1169,
    _0: LAYOUT__531,
};
pub const LAYOUT__1160: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1161,
    _0: LAYOUT__1168,
};
pub const LAYOUT__1129: &BigIntReadWords_SuperLayout4LayoutArray =
    &[LAYOUT__1130, LAYOUT__1140, LAYOUT__1150, LAYOUT__1160];
pub const LAYOUT__1124: &BigIntReadLayout = &BigIntReadLayout {
    addr: LAYOUT__1125,
    words: LAYOUT__1129,
};
pub const LAYOUT__1172: &NondetU8RegLayout16LayoutArray = &[
    LAYOUT__1133,
    LAYOUT__1134,
    LAYOUT__1136,
    LAYOUT__1137,
    LAYOUT__1143,
    LAYOUT__1144,
    LAYOUT__1146,
    LAYOUT__1147,
    LAYOUT__1153,
    LAYOUT__1154,
    LAYOUT__1156,
    LAYOUT__1157,
    LAYOUT__1163,
    LAYOUT__1164,
    LAYOUT__1166,
    LAYOUT__1167,
];
pub const LAYOUT__1171: &BigIntWitnessLayout = &BigIntWitnessLayout {
    _super: LAYOUT__1172,
};
pub const LAYOUT__1175: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1139,
    _0: LAYOUT__519,
};
pub const LAYOUT__1174: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1175 };
pub const LAYOUT__1177: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1149,
    _0: LAYOUT__523,
};
pub const LAYOUT__1176: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1177 };
pub const LAYOUT__1179: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1159,
    _0: LAYOUT__527,
};
pub const LAYOUT__1178: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1179 };
pub const LAYOUT__1181: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1169,
    _0: LAYOUT__531,
};
pub const LAYOUT__1180: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1181 };
pub const LAYOUT__1173: &BigIntWrite__0_SuperLayout4LayoutArray =
    &[LAYOUT__1174, LAYOUT__1176, LAYOUT__1178, LAYOUT__1180];
pub const LAYOUT__1170: &BigIntWriteLayout = &BigIntWriteLayout {
    _super: LAYOUT__1171,
    addr: LAYOUT__1125,
    _1: LAYOUT__1173,
};
pub const LAYOUT__1182: &BigIntStepBytesArm2Layout = &BigIntStepBytesArm2Layout {
    _super: LAYOUT__1171,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra2: LAYOUT__1090,
    _extra3: LAYOUT__1091,
    _extra4: LAYOUT__1092,
    _extra5: LAYOUT__1093,
    _extra6: LAYOUT__1094,
    _extra7: LAYOUT__1095,
    _extra8: LAYOUT__1096,
    _extra9: LAYOUT__1097,
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
};
pub const LAYOUT__1123: &BigIntStepBytesLayout = &BigIntStepBytesLayout {
    arm0: LAYOUT__1124,
    arm1: LAYOUT__1170,
    arm2: LAYOUT__1182,
};
pub const LAYOUT__1109: &BigIntStepLayout = &BigIntStepLayout {
    _super: LAYOUT__1082,
    load_inst_0: LAYOUT__1104,
    inst_high: LAYOUT__1110,
    poly_op: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
    mem_op: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
    reg_bits: LAYOUT__1113,
    coeff_bits: &[
        &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    ],
    base_addr_u32: LAYOUT__1107,
    data_addr_u32: LAYOUT__1114,
    mem_op_one_hot: LAYOUT__1117,
    _arguments_big_int_step_bytes: LAYOUT__1118,
    bytes: LAYOUT__1123,
    _2: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
};
pub const LAYOUT__1183: &BigInt0StateArm2Layout = &BigInt0StateArm2Layout {
    _super: LAYOUT__1082,
    _extra0: LAYOUT__1086,
    _extra1: LAYOUT__1087,
    _extra2: LAYOUT__1088,
    _extra3: LAYOUT__1089,
    _extra4: LAYOUT__1090,
    _extra5: LAYOUT__1091,
    _extra6: LAYOUT__1092,
    _extra7: LAYOUT__1093,
    _extra8: LAYOUT__1094,
    _extra9: LAYOUT__1095,
    _extra10: LAYOUT__1096,
    _extra11: LAYOUT__1097,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__1184: &BigInt0StateArm3Layout = &BigInt0StateArm3Layout {
    _super: LAYOUT__1082,
    _extra0: LAYOUT__1086,
    _extra1: LAYOUT__1087,
    _extra2: LAYOUT__1088,
    _extra3: LAYOUT__1089,
    _extra4: LAYOUT__1090,
    _extra5: LAYOUT__1091,
    _extra6: LAYOUT__1092,
    _extra7: LAYOUT__1093,
    _extra8: LAYOUT__1094,
    _extra9: LAYOUT__1095,
    _extra10: LAYOUT__1096,
    _extra11: LAYOUT__1097,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__1185: &BigInt0StateArm4Layout = &BigInt0StateArm4Layout {
    _super: LAYOUT__1082,
    _extra0: LAYOUT__1086,
    _extra1: LAYOUT__1087,
    _extra2: LAYOUT__1088,
    _extra3: LAYOUT__1089,
    _extra4: LAYOUT__1090,
    _extra5: LAYOUT__1091,
    _extra6: LAYOUT__1092,
    _extra7: LAYOUT__1093,
    _extra8: LAYOUT__1094,
    _extra9: LAYOUT__1095,
    _extra10: LAYOUT__1096,
    _extra11: LAYOUT__1097,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__1186: &BigInt0StateArm5Layout = &BigInt0StateArm5Layout {
    _super: LAYOUT__1082,
    _extra0: LAYOUT__1086,
    _extra1: LAYOUT__1087,
    _extra2: LAYOUT__1088,
    _extra3: LAYOUT__1089,
    _extra4: LAYOUT__1090,
    _extra5: LAYOUT__1091,
    _extra6: LAYOUT__1092,
    _extra7: LAYOUT__1093,
    _extra8: LAYOUT__1094,
    _extra9: LAYOUT__1095,
    _extra10: LAYOUT__1096,
    _extra11: LAYOUT__1097,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__1187: &BigInt0StateArm6Layout = &BigInt0StateArm6Layout {
    _super: LAYOUT__1082,
    _extra0: LAYOUT__1086,
    _extra1: LAYOUT__1087,
    _extra2: LAYOUT__1088,
    _extra3: LAYOUT__1089,
    _extra4: LAYOUT__1090,
    _extra5: LAYOUT__1091,
    _extra6: LAYOUT__1092,
    _extra7: LAYOUT__1093,
    _extra8: LAYOUT__1094,
    _extra9: LAYOUT__1095,
    _extra10: LAYOUT__1096,
    _extra11: LAYOUT__1097,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__1188: &BigInt0StateArm7Layout = &BigInt0StateArm7Layout {
    _super: LAYOUT__1082,
    _extra0: LAYOUT__1086,
    _extra1: LAYOUT__1087,
    _extra2: LAYOUT__1088,
    _extra3: LAYOUT__1089,
    _extra4: LAYOUT__1090,
    _extra5: LAYOUT__1091,
    _extra6: LAYOUT__1092,
    _extra7: LAYOUT__1093,
    _extra8: LAYOUT__1094,
    _extra9: LAYOUT__1095,
    _extra10: LAYOUT__1096,
    _extra11: LAYOUT__1097,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__1101: &BigInt0StateLayout = &BigInt0StateLayout {
    _super: LAYOUT__1082,
    arm0: LAYOUT__1102,
    arm1: LAYOUT__1109,
    arm2: LAYOUT__1183,
    arm3: LAYOUT__1184,
    arm4: LAYOUT__1185,
    arm5: LAYOUT__1186,
    arm6: LAYOUT__1187,
    arm7: LAYOUT__1188,
};
pub const LAYOUT__1080: &BigInt0Layout = &BigInt0Layout {
    _0: LAYOUT__1081,
    state: LAYOUT__1082,
    _arguments_big_int0_state: LAYOUT__1084,
    state_redef: LAYOUT__1101,
};
pub const LAYOUT__13: &TopInstResultLayout = &TopInstResultLayout {
    _selector: LAYOUT__12,
    arm0: LAYOUT__14,
    arm1: LAYOUT__103,
    arm2: LAYOUT__121,
    arm3: LAYOUT__135,
    arm4: LAYOUT__225,
    arm5: LAYOUT__343,
    arm6: LAYOUT__401,
    arm7: LAYOUT__459,
    arm8: LAYOUT__634,
    arm9: LAYOUT__699,
    arm10: LAYOUT__967,
    arm11: LAYOUT__1000,
    arm12: LAYOUT__1080,
};
pub const LAYOUT__7: &TopLayout = &TopLayout {
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    next_pc_low: &NondetRegLayout {
        _super: &Reg { offset: 14 },
    },
    next_pc_high: &NondetRegLayout {
        _super: &Reg { offset: 15 },
    },
    next_state_0: &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    next_machine_mode: &NondetRegLayout {
        _super: &Reg { offset: 17 },
    },
    is_first_cycle: &NondetRegLayout {
        _super: &Reg { offset: 18 },
    },
    cycle_redef: &TopCycleLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
        arm0: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
        arm1: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
    major: &NondetRegLayout {
        _super: &Reg { offset: 19 },
    },
    minor: &NondetRegLayout {
        _super: &Reg { offset: 20 },
    },
    inst_input: LAYOUT__8,
    major_onehot: LAYOUT__11,
    inst_result: LAYOUT__13,
};
pub const LAYOUT__1190: &DigestRegValues_SuperLayout8LayoutArray = &[
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 1 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 2 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 3 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 4 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 5 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 6 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 7 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 8 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 9 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 10 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 11 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 12 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 13 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 14 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 15 },
        },
    },
];
pub const LAYOUT__1189: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1190,
};
pub const LAYOUT__1192: &DigestRegValues_SuperLayout8LayoutArray = &[
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 17 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 18 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 19 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 20 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 21 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 22 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 23 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 24 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 25 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 26 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
];
pub const LAYOUT__1191: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1192,
};
pub const LAYOUT__1194: &DigestRegValues_SuperLayout8LayoutArray = &[
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
];
pub const LAYOUT__1193: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1194,
};
pub const LAYOUT__1196: &DigestRegValues_SuperLayout8LayoutArray = &[
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
];
pub const LAYOUT__1195: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1196,
};
pub const LAYOUT__1198: &DigestRegValues_SuperLayout8LayoutArray = &[
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
];
pub const LAYOUT__1197: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1198,
};
pub const LAYOUT__1199: &_accumLayout = &_accumLayout {
    arg_u8: &Arg_ArgU8Layout {
        val: &Reg { offset: 0 },
    },
    arg_u16: &Arg_ArgU16Layout {
        val: &Reg { offset: 4 },
    },
    memory_arg: &Arg_MemoryArgLayout {
        addr: &Reg { offset: 8 },
        cycle: &Reg { offset: 12 },
        data_low: &Reg { offset: 16 },
        data_high: &Reg { offset: 20 },
    },
    cycle_arg: &Arg_CycleArgLayout {
        cycle: &Reg { offset: 24 },
    },
    _offset: &Reg { offset: 28 },
    _user: &[&Reg { offset: 32 }],
};
pub const LAYOUT_TEST_SUCC_RUN_ACCUM: &LayoutAccumLayout = &LayoutAccumLayout {
    user: LAYOUT__0,
    columns: &[
        &Reg { offset: 23 },
        &Reg { offset: 27 },
        &Reg { offset: 31 },
        &Reg { offset: 35 },
        &Reg { offset: 39 },
        &Reg { offset: 43 },
        &Reg { offset: 47 },
        &Reg { offset: 51 },
        &Reg { offset: 55 },
        &Reg { offset: 59 },
        &Reg { offset: 63 },
        &Reg { offset: 67 },
        &Reg { offset: 71 },
        &Reg { offset: 75 },
        &Reg { offset: 79 },
        &Reg { offset: 83 },
        &Reg { offset: 87 },
        &Reg { offset: 91 },
        &Reg { offset: 95 },
        &Reg { offset: 99 },
    ],
};
pub const LAYOUT_TOP_ACCUM: &LayoutAccumLayout = &LayoutAccumLayout {
    user: LAYOUT__0,
    columns: &[
        &Reg { offset: 23 },
        &Reg { offset: 27 },
        &Reg { offset: 31 },
        &Reg { offset: 35 },
        &Reg { offset: 39 },
        &Reg { offset: 43 },
        &Reg { offset: 47 },
        &Reg { offset: 51 },
        &Reg { offset: 55 },
        &Reg { offset: 59 },
        &Reg { offset: 63 },
        &Reg { offset: 67 },
        &Reg { offset: 71 },
        &Reg { offset: 75 },
        &Reg { offset: 79 },
        &Reg { offset: 83 },
        &Reg { offset: 87 },
        &Reg { offset: 91 },
        &Reg { offset: 95 },
        &Reg { offset: 99 },
    ],
};
pub const LAYOUT_TEST_SUCC_RUN: &TestSuccRunLayout = &TestSuccRunLayout { _0: LAYOUT__7 };
pub const LAYOUT_TOP: &TopLayout = &TopLayout {
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    next_pc_low: &NondetRegLayout {
        _super: &Reg { offset: 14 },
    },
    next_pc_high: &NondetRegLayout {
        _super: &Reg { offset: 15 },
    },
    next_state_0: &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    next_machine_mode: &NondetRegLayout {
        _super: &Reg { offset: 17 },
    },
    is_first_cycle: &NondetRegLayout {
        _super: &Reg { offset: 18 },
    },
    cycle_redef: &TopCycleLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
        arm0: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
        arm1: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
    major: &NondetRegLayout {
        _super: &Reg { offset: 19 },
    },
    minor: &NondetRegLayout {
        _super: &Reg { offset: 20 },
    },
    inst_input: LAYOUT__8,
    major_onehot: LAYOUT__11,
    inst_result: LAYOUT__13,
};
pub const LAYOUT_GLOBAL: &_globalLayout = &_globalLayout {
    input: LAYOUT__1189,
    is_terminate: &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    output: LAYOUT__1191,
    povw_nonce: LAYOUT__1193,
    rng: &NondetExtRegLayout {
        _super: &Reg { offset: 49 },
    },
    shutdown_cycle: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    state_in: LAYOUT__1195,
    state_out: LAYOUT__1197,
    term_a0high: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    term_a0low: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    term_a1high: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    term_a1low: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
};
pub const LAYOUT_MIX: &_mixLayout = &_mixLayout {
    randomness: LAYOUT__1199,
};
