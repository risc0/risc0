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
pub const LAYOUT__130: &Misc2MiscOutputArm4Layout = &Misc2MiscOutputArm4Layout {
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
pub const LAYOUT__131: &Misc2MiscOutputArm5Layout = &Misc2MiscOutputArm5Layout {
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
pub const LAYOUT__132: &Misc2MiscOutputArm6Layout = &Misc2MiscOutputArm6Layout {
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
pub const LAYOUT__133: &Misc2MiscOutputArm7Layout = &Misc2MiscOutputArm7Layout {
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
    arm5: LAYOUT__131,
    arm6: LAYOUT__132,
    arm7: LAYOUT__133,
};
pub const LAYOUT__121: &Misc2Layout = &Misc2Layout {
    _super: LAYOUT__15,
    _0: LAYOUT__29,
    input: LAYOUT__30,
    _arguments_misc2_misc_output: LAYOUT__122,
    misc_output: LAYOUT__123,
};
pub const LAYOUT__135: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__138: &DecoderLayout = &DecoderLayout {
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
pub const LAYOUT__140: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__141: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__139: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    upper_diff: LAYOUT__140,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
    med14: LAYOUT__141,
};
pub const LAYOUT__144: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__145: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__143: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__144,
    new_txn: LAYOUT__145,
};
pub const LAYOUT__147: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
};
pub const LAYOUT__146: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__147 };
pub const LAYOUT__142: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__143,
    _0: LAYOUT__146,
};
pub const LAYOUT__137: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__138,
    pc_addr: LAYOUT__139,
    load_inst: LAYOUT__142,
};
pub const LAYOUT__151: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__152: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__153: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__154: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__150: &MemoryArgLayout4LayoutArray =
    &[LAYOUT__151, LAYOUT__152, LAYOUT__153, LAYOUT__154];
pub const LAYOUT__155: &CycleArgLayout2LayoutArray = &[
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
pub const LAYOUT__149: &_Arguments_ReadSourceRegsSourceRegsLayout =
    &_Arguments_ReadSourceRegsSourceRegsLayout {
        memory_arg: LAYOUT__150,
        cycle_arg: LAYOUT__155,
    };
pub const LAYOUT__161: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__151,
    new_txn: LAYOUT__152,
};
pub const LAYOUT__160: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__161,
    _0: LAYOUT__62,
};
pub const LAYOUT__159: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__160,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
};
pub const LAYOUT__158: &ReadSourceRegsSourceRegsArm0_SuperLayout =
    &ReadSourceRegsSourceRegsArm0_SuperLayout { rboth: LAYOUT__159 };
pub const LAYOUT__157: &ReadSourceRegsSourceRegsArm0Layout = &ReadSourceRegsSourceRegsArm0Layout {
    _super: LAYOUT__158,
    _extra0: LAYOUT__153,
    _extra1: LAYOUT__154,
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
};
pub const LAYOUT__165: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__153,
    new_txn: LAYOUT__154,
};
pub const LAYOUT__167: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
};
pub const LAYOUT__166: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__167 };
pub const LAYOUT__164: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__165,
    _0: LAYOUT__166,
};
pub const LAYOUT__163: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__164,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
};
pub const LAYOUT__162: &ReadSourceRegsSourceRegsArm1_SuperLayout =
    &ReadSourceRegsSourceRegsArm1_SuperLayout {
        _0: LAYOUT__159,
        _1: LAYOUT__163,
    };
pub const LAYOUT__156: &ReadSourceRegsSourceRegsLayout = &ReadSourceRegsSourceRegsLayout {
    arm0: LAYOUT__157,
    arm1: LAYOUT__162,
};
pub const LAYOUT__148: &ReadSourceRegsLayout = &ReadSourceRegsLayout {
    is_same_reg: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    _arguments_read_source_regs_source_regs: LAYOUT__149,
    source_regs: LAYOUT__156,
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
pub const LAYOUT__136: &MulInputLayout = &MulInputLayout {
    decoded: LAYOUT__137,
    source_regs: LAYOUT__148,
};
pub const LAYOUT__169: &ArgU16Layout6LayoutArray = &[
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
pub const LAYOUT__170: &ArgU8Layout13LayoutArray = &[
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
pub const LAYOUT__168: &_Arguments_Mul0MulOutputLayout = &_Arguments_Mul0MulOutputLayout {
    arg_u16: LAYOUT__169,
    arg_u8: LAYOUT__170,
};
pub const LAYOUT__175: &NondetRegLayout5LayoutArray = &[
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
pub const LAYOUT__174: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__175,
};
pub const LAYOUT__173: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__174,
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
pub const LAYOUT__179: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
};
pub const LAYOUT__180: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__181: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
};
pub const LAYOUT__182: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
};
pub const LAYOUT__183: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
};
pub const LAYOUT__178: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__179,
    b1: LAYOUT__180,
    b2: LAYOUT__181,
    b3: LAYOUT__182,
    b3_top7times2: LAYOUT__183,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
};
pub const LAYOUT__185: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
};
pub const LAYOUT__186: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
};
pub const LAYOUT__187: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
};
pub const LAYOUT__188: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
};
pub const LAYOUT__189: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__184: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__185,
    b1: LAYOUT__186,
    b2: LAYOUT__187,
    b3: LAYOUT__188,
    b3_top7times2: LAYOUT__189,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 143 },
    },
};
pub const LAYOUT__191: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
};
pub const LAYOUT__190: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__94,
    carry_byte: LAYOUT__191,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__193: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
};
pub const LAYOUT__192: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__96,
    carry_byte: LAYOUT__193,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
};
pub const LAYOUT__195: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__194: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__98,
    carry_byte: LAYOUT__195,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
};
pub const LAYOUT__177: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__178,
    bx: LAYOUT__184,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 144 },
    },
    c_rest_times2: LAYOUT__92,
    s0: LAYOUT__190,
    s1: LAYOUT__192,
    s2: LAYOUT__194,
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
pub const LAYOUT__176: &DoMulLayout = &DoMulLayout { mul: LAYOUT__177 };
pub const LAYOUT__172: &OpSLLLayout = &OpSLLLayout {
    shift_mul: LAYOUT__173,
    _0: LAYOUT__176,
};
pub const LAYOUT__196: &OpSLLILayout = &OpSLLILayout {
    shift_mul: LAYOUT__173,
    _0: LAYOUT__176,
};
pub const LAYOUT__201: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__179,
    b1: LAYOUT__180,
    b2: LAYOUT__181,
    b3: LAYOUT__182,
    b3_top7times2: LAYOUT__183,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
};
pub const LAYOUT__202: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__185,
    b1: LAYOUT__186,
    b2: LAYOUT__187,
    b3: LAYOUT__188,
    b3_top7times2: LAYOUT__189,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
};
pub const LAYOUT__203: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__92,
    carry_byte: LAYOUT__191,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__204: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__94,
    carry_byte: LAYOUT__193,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
};
pub const LAYOUT__205: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__96,
    carry_byte: LAYOUT__195,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
};
pub const LAYOUT__200: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__201,
    bx: LAYOUT__202,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    c_rest_times2: LAYOUT__91,
    s0: LAYOUT__203,
    s1: LAYOUT__204,
    s2: LAYOUT__205,
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
pub const LAYOUT__199: &DoMulLayout = &DoMulLayout { mul: LAYOUT__200 };
pub const LAYOUT__198: &OpMULLayout = &OpMULLayout { _0: LAYOUT__199 };
pub const LAYOUT__197: &Mul0MulOutputArm2Layout = &Mul0MulOutputArm2Layout {
    _super: LAYOUT__198,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__207: &OpMULHLayout = &OpMULHLayout { _0: LAYOUT__199 };
pub const LAYOUT__206: &Mul0MulOutputArm3Layout = &Mul0MulOutputArm3Layout {
    _super: LAYOUT__207,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__209: &OpMULHSULayout = &OpMULHSULayout { _0: LAYOUT__199 };
pub const LAYOUT__208: &Mul0MulOutputArm4Layout = &Mul0MulOutputArm4Layout {
    _super: LAYOUT__209,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__211: &OpMULHULayout = &OpMULHULayout { _0: LAYOUT__199 };
pub const LAYOUT__210: &Mul0MulOutputArm5Layout = &Mul0MulOutputArm5Layout {
    _super: LAYOUT__211,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__212: &Mul0MulOutputArm6Layout = &Mul0MulOutputArm6Layout {
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
pub const LAYOUT__213: &Mul0MulOutputArm7Layout = &Mul0MulOutputArm7Layout {
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
pub const LAYOUT__171: &Mul0MulOutputLayout = &Mul0MulOutputLayout {
    arm0: LAYOUT__172,
    arm1: LAYOUT__196,
    arm2: LAYOUT__197,
    arm3: LAYOUT__206,
    arm4: LAYOUT__208,
    arm5: LAYOUT__210,
    arm6: LAYOUT__212,
    arm7: LAYOUT__213,
};
pub const LAYOUT__217: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__218: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__216: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__217,
    new_txn: LAYOUT__218,
};
pub const LAYOUT__220: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
};
pub const LAYOUT__219: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__220 };
pub const LAYOUT__215: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__216,
    _0: LAYOUT__219,
};
pub const LAYOUT__214: &WriteRdLayout = &WriteRdLayout {
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
    _0: LAYOUT__215,
};
pub const LAYOUT__222: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
};
pub const LAYOUT__223: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
};
pub const LAYOUT__221: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__222,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
    high16: LAYOUT__223,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 172 },
    },
};
pub const LAYOUT__134: &Mul0Layout = &Mul0Layout {
    _0: LAYOUT__135,
    input: LAYOUT__136,
    _arguments_mul0_mul_output: LAYOUT__168,
    mul_output: LAYOUT__171,
    _1: LAYOUT__214,
    pc_add: LAYOUT__221,
};
pub const LAYOUT__225: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__228: &DecoderLayout = &DecoderLayout {
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
pub const LAYOUT__230: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
};
pub const LAYOUT__231: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
};
pub const LAYOUT__229: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    upper_diff: LAYOUT__230,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    med14: LAYOUT__231,
};
pub const LAYOUT__234: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__235: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__233: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__234,
    new_txn: LAYOUT__235,
};
pub const LAYOUT__232: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__233,
    _0: LAYOUT__62,
};
pub const LAYOUT__227: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__228,
    pc_addr: LAYOUT__229,
    load_inst: LAYOUT__232,
};
pub const LAYOUT__239: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__240: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__241: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__242: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__238: &MemoryArgLayout4LayoutArray =
    &[LAYOUT__239, LAYOUT__240, LAYOUT__241, LAYOUT__242];
pub const LAYOUT__243: &CycleArgLayout2LayoutArray = &[
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
pub const LAYOUT__237: &_Arguments_ReadSourceRegsSourceRegsLayout =
    &_Arguments_ReadSourceRegsSourceRegsLayout {
        memory_arg: LAYOUT__238,
        cycle_arg: LAYOUT__243,
    };
pub const LAYOUT__249: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__239,
    new_txn: LAYOUT__240,
};
pub const LAYOUT__251: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__250: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__251 };
pub const LAYOUT__248: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__249,
    _0: LAYOUT__250,
};
pub const LAYOUT__247: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__248,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 148 },
    },
};
pub const LAYOUT__246: &ReadSourceRegsSourceRegsArm0_SuperLayout =
    &ReadSourceRegsSourceRegsArm0_SuperLayout { rboth: LAYOUT__247 };
pub const LAYOUT__245: &ReadSourceRegsSourceRegsArm0Layout = &ReadSourceRegsSourceRegsArm0Layout {
    _super: LAYOUT__246,
    _extra0: LAYOUT__241,
    _extra1: LAYOUT__242,
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__255: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__241,
    new_txn: LAYOUT__242,
};
pub const LAYOUT__257: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__256: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__257 };
pub const LAYOUT__254: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__255,
    _0: LAYOUT__256,
};
pub const LAYOUT__253: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__254,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 149 },
    },
};
pub const LAYOUT__252: &ReadSourceRegsSourceRegsArm1_SuperLayout =
    &ReadSourceRegsSourceRegsArm1_SuperLayout {
        _0: LAYOUT__247,
        _1: LAYOUT__253,
    };
pub const LAYOUT__244: &ReadSourceRegsSourceRegsLayout = &ReadSourceRegsSourceRegsLayout {
    arm0: LAYOUT__245,
    arm1: LAYOUT__252,
};
pub const LAYOUT__236: &ReadSourceRegsLayout = &ReadSourceRegsLayout {
    is_same_reg: &NondetRegLayout {
        _super: &Reg { offset: 147 },
    },
    _arguments_read_source_regs_source_regs: LAYOUT__237,
    source_regs: LAYOUT__244,
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
pub const LAYOUT__226: &DivInputLayout = &DivInputLayout {
    decoded: LAYOUT__227,
    source_regs: LAYOUT__236,
};
pub const LAYOUT__259: &ArgU16Layout16LayoutArray = &[
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
pub const LAYOUT__260: &ArgU8Layout13LayoutArray = &[
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
pub const LAYOUT__258: &_Arguments_Div0MulOutputLayout = &_Arguments_Div0MulOutputLayout {
    arg_u16: LAYOUT__259,
    arg_u8: LAYOUT__260,
};
pub const LAYOUT__266: &NondetRegLayout5LayoutArray = &[
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
pub const LAYOUT__265: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__266,
};
pub const LAYOUT__264: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__265,
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
pub const LAYOUT__270: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__271: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__269: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__191,
    b1: LAYOUT__193,
    b2: LAYOUT__195,
    b3: LAYOUT__270,
    b3_top7times2: LAYOUT__271,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
};
pub const LAYOUT__273: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
};
pub const LAYOUT__274: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__275: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
};
pub const LAYOUT__276: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
};
pub const LAYOUT__277: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
};
pub const LAYOUT__272: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__273,
    b1: LAYOUT__274,
    b2: LAYOUT__275,
    b3: LAYOUT__276,
    b3_top7times2: LAYOUT__277,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
};
pub const LAYOUT__279: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
};
pub const LAYOUT__278: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__98,
    carry_byte: LAYOUT__279,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
};
pub const LAYOUT__281: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
};
pub const LAYOUT__280: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__17,
    carry_byte: LAYOUT__281,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
};
pub const LAYOUT__283: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
};
pub const LAYOUT__284: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
};
pub const LAYOUT__282: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__283,
    carry_byte: LAYOUT__284,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
};
pub const LAYOUT__285: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__268: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__269,
    bx: LAYOUT__272,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
    c_rest_times2: LAYOUT__96,
    s0: LAYOUT__278,
    s1: LAYOUT__280,
    s2: LAYOUT__282,
    s3_out: LAYOUT__285,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
};
pub const LAYOUT__287: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
};
pub const LAYOUT__288: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
};
pub const LAYOUT__286: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__287,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 177 },
    },
    high16: LAYOUT__288,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 178 },
    },
};
pub const LAYOUT__290: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
};
pub const LAYOUT__291: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
};
pub const LAYOUT__289: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__290,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 179 },
    },
    high16: LAYOUT__291,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
};
pub const LAYOUT__294: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
};
pub const LAYOUT__295: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
};
pub const LAYOUT__293: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__294,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    high16: LAYOUT__295,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
};
pub const LAYOUT__292: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__293 };
pub const LAYOUT__267: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 162 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 163 },
    },
    rem_low: LAYOUT__92,
    rem_high: LAYOUT__94,
    mul: LAYOUT__268,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
    top_num: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
    _0: LAYOUT__20,
    denom_abs: LAYOUT__286,
    rem_normal: LAYOUT__289,
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    signed_overflow_case: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    lt: LAYOUT__292,
};
pub const LAYOUT__263: &OpSRLLayout = &OpSRLLayout {
    shift_mul: LAYOUT__264,
    _0: LAYOUT__267,
};
pub const LAYOUT__262: &Div0MulOutputArm0Layout = &Div0MulOutputArm0Layout {
    _super: LAYOUT__263,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__297: &TopBitLayout = &TopBitLayout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 162 },
    },
    rest: LAYOUT__92,
};
pub const LAYOUT__300: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__191,
    b1: LAYOUT__193,
    b2: LAYOUT__195,
    b3: LAYOUT__270,
    b3_top7times2: LAYOUT__271,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
};
pub const LAYOUT__301: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__273,
    b1: LAYOUT__274,
    b2: LAYOUT__275,
    b3: LAYOUT__276,
    b3_top7times2: LAYOUT__277,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
};
pub const LAYOUT__302: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__17,
    carry_byte: LAYOUT__279,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
};
pub const LAYOUT__303: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__283,
    carry_byte: LAYOUT__281,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
};
pub const LAYOUT__304: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__285,
    carry_byte: LAYOUT__284,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
};
pub const LAYOUT__299: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__300,
    bx: LAYOUT__301,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 167 },
    },
    c_rest_times2: LAYOUT__98,
    s0: LAYOUT__302,
    s1: LAYOUT__303,
    s2: LAYOUT__304,
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
pub const LAYOUT__305: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__288,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 178 },
    },
    high16: LAYOUT__290,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 179 },
    },
};
pub const LAYOUT__306: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__291,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
    high16: LAYOUT__294,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
};
pub const LAYOUT__309: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__308: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__295,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    high16: LAYOUT__309,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 185 },
    },
};
pub const LAYOUT__307: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__308 };
pub const LAYOUT__298: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 163 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
    rem_low: LAYOUT__94,
    rem_high: LAYOUT__96,
    mul: LAYOUT__299,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
    top_num: &NondetRegLayout {
        _super: &Reg { offset: 177 },
    },
    _0: LAYOUT__287,
    denom_abs: LAYOUT__305,
    rem_normal: LAYOUT__306,
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    signed_overflow_case: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    lt: LAYOUT__307,
};
pub const LAYOUT__296: &OpSRALayout = &OpSRALayout {
    shift_mul: LAYOUT__264,
    flip: LAYOUT__297,
    _0: LAYOUT__298,
};
pub const LAYOUT__311: &OpSRLILayout = &OpSRLILayout {
    shift_mul: LAYOUT__264,
    _0: LAYOUT__267,
};
pub const LAYOUT__310: &Div0MulOutputArm2Layout = &Div0MulOutputArm2Layout {
    _super: LAYOUT__311,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__312: &OpSRAILayout = &OpSRAILayout {
    shift_mul: LAYOUT__264,
    flip: LAYOUT__297,
    _0: LAYOUT__298,
};
pub const LAYOUT__317: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__191,
    b1: LAYOUT__193,
    b2: LAYOUT__195,
    b3: LAYOUT__270,
    b3_top7times2: LAYOUT__271,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
};
pub const LAYOUT__318: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__273,
    b1: LAYOUT__274,
    b2: LAYOUT__275,
    b3: LAYOUT__276,
    b3_top7times2: LAYOUT__277,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
};
pub const LAYOUT__319: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__96,
    carry_byte: LAYOUT__279,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__320: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__98,
    carry_byte: LAYOUT__281,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
};
pub const LAYOUT__321: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__17,
    carry_byte: LAYOUT__284,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
};
pub const LAYOUT__316: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__317,
    bx: LAYOUT__318,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
    c_rest_times2: LAYOUT__94,
    s0: LAYOUT__319,
    s1: LAYOUT__320,
    s2: LAYOUT__321,
    s3_out: LAYOUT__283,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
};
pub const LAYOUT__322: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__20,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
    high16: LAYOUT__287,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 170 },
    },
};
pub const LAYOUT__323: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__288,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
    high16: LAYOUT__290,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 172 },
    },
};
pub const LAYOUT__325: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__291,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
    high16: LAYOUT__294,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
};
pub const LAYOUT__324: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__325 };
pub const LAYOUT__315: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
    rem_low: LAYOUT__91,
    rem_high: LAYOUT__92,
    mul: LAYOUT__316,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 167 },
    },
    top_num: &NondetRegLayout {
        _super: &Reg { offset: 168 },
    },
    _0: LAYOUT__285,
    denom_abs: LAYOUT__322,
    rem_normal: LAYOUT__323,
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 173 },
    },
    signed_overflow_case: &NondetRegLayout {
        _super: &Reg { offset: 174 },
    },
    lt: LAYOUT__324,
};
pub const LAYOUT__314: &OpDIVLayout = &OpDIVLayout { _0: LAYOUT__315 };
pub const LAYOUT__313: &Div0MulOutputArm4Layout = &Div0MulOutputArm4Layout {
    _super: LAYOUT__314,
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
pub const LAYOUT__327: &OpDIVULayout = &OpDIVULayout { _0: LAYOUT__315 };
pub const LAYOUT__326: &Div0MulOutputArm5Layout = &Div0MulOutputArm5Layout {
    _super: LAYOUT__327,
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
pub const LAYOUT__329: &OpREMLayout = &OpREMLayout { _0: LAYOUT__315 };
pub const LAYOUT__328: &Div0MulOutputArm6Layout = &Div0MulOutputArm6Layout {
    _super: LAYOUT__329,
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
pub const LAYOUT__331: &OpREMULayout = &OpREMULayout { _0: LAYOUT__315 };
pub const LAYOUT__330: &Div0MulOutputArm7Layout = &Div0MulOutputArm7Layout {
    _super: LAYOUT__331,
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
pub const LAYOUT__261: &Div0MulOutputLayout = &Div0MulOutputLayout {
    arm0: LAYOUT__262,
    arm1: LAYOUT__296,
    arm2: LAYOUT__310,
    arm3: LAYOUT__312,
    arm4: LAYOUT__313,
    arm5: LAYOUT__326,
    arm6: LAYOUT__328,
    arm7: LAYOUT__330,
};
pub const LAYOUT__335: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__336: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__334: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__335,
    new_txn: LAYOUT__336,
};
pub const LAYOUT__338: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 198 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 199 },
        },
    },
};
pub const LAYOUT__337: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__338 };
pub const LAYOUT__333: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__334,
    _0: LAYOUT__337,
};
pub const LAYOUT__332: &WriteRdLayout = &WriteRdLayout {
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
    _0: LAYOUT__333,
};
pub const LAYOUT__340: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 200 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 201 },
        },
    },
};
pub const LAYOUT__341: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 203 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 204 },
        },
    },
};
pub const LAYOUT__339: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__340,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 202 },
    },
    high16: LAYOUT__341,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 205 },
    },
};
pub const LAYOUT__224: &Div0Layout = &Div0Layout {
    _0: LAYOUT__225,
    input: LAYOUT__226,
    _arguments_div0_mul_output: LAYOUT__258,
    mul_output: LAYOUT__261,
    _1: LAYOUT__332,
    pc_add: LAYOUT__339,
};
pub const LAYOUT__343: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__346: &DecoderLayout = &DecoderLayout {
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
pub const LAYOUT__348: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__349: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
    },
};
pub const LAYOUT__347: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    upper_diff: LAYOUT__348,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
    },
    med14: LAYOUT__349,
};
pub const LAYOUT__352: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__353: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__351: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__352,
    new_txn: LAYOUT__353,
};
pub const LAYOUT__355: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__354: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__355 };
pub const LAYOUT__350: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__351,
    _0: LAYOUT__354,
};
pub const LAYOUT__345: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__346,
    pc_addr: LAYOUT__347,
    load_inst: LAYOUT__350,
};
pub const LAYOUT__359: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__360: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__358: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__359,
    new_txn: LAYOUT__360,
};
pub const LAYOUT__362: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__361: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__362 };
pub const LAYOUT__357: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__358,
    _0: LAYOUT__361,
};
pub const LAYOUT__356: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__357,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
};
pub const LAYOUT__364: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__363: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__364,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    high16: LAYOUT__35,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
};
pub const LAYOUT__366: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
};
pub const LAYOUT__367: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
};
pub const LAYOUT__365: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    upper_diff: LAYOUT__366,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
    med14: LAYOUT__367,
};
pub const LAYOUT__370: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__371: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__369: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__370,
    new_txn: LAYOUT__371,
};
pub const LAYOUT__373: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__372: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__373 };
pub const LAYOUT__368: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__369,
    _0: LAYOUT__372,
};
pub const LAYOUT__344: &MemLoadInputLayout = &MemLoadInputLayout {
    decoded: LAYOUT__345,
    rs1: LAYOUT__356,
    addr_u32: LAYOUT__363,
    addr: LAYOUT__365,
    data_0: LAYOUT__368,
};
pub const LAYOUT__375: &ArgU8Layout3LayoutArray = &[
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
pub const LAYOUT__374: &_Arguments_Mem0OutputLayout = &_Arguments_Mem0OutputLayout {
    arg_u8: LAYOUT__375,
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    }],
};
pub const LAYOUT__380: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
};
pub const LAYOUT__381: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__379: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__380,
    byte1: LAYOUT__381,
};
pub const LAYOUT__382: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__378: &OpLBLayout = &OpLBLayout {
    bytes: LAYOUT__379,
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low7x2: LAYOUT__382,
};
pub const LAYOUT__377: &Mem0OutputArm0Layout = &Mem0OutputArm0Layout {
    _super: LAYOUT__378,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__384: &OpLHLayout = &OpLHLayout {
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low15x2: LAYOUT__96,
};
pub const LAYOUT__383: &Mem0OutputArm1Layout = &Mem0OutputArm1Layout {
    _super: LAYOUT__384,
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
pub const LAYOUT__385: &Mem0OutputArm2Layout = &Mem0OutputArm2Layout {
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
pub const LAYOUT__387: &OpLBULayout = &OpLBULayout { bytes: LAYOUT__379 };
pub const LAYOUT__386: &Mem0OutputArm3Layout = &Mem0OutputArm3Layout {
    _super: LAYOUT__387,
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
pub const LAYOUT__388: &Mem0OutputArm4Layout = &Mem0OutputArm4Layout {
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
pub const LAYOUT__389: &Mem0OutputArm5Layout = &Mem0OutputArm5Layout {
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
pub const LAYOUT__390: &Mem0OutputArm6Layout = &Mem0OutputArm6Layout {
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
pub const LAYOUT__391: &Mem0OutputArm7Layout = &Mem0OutputArm7Layout {
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
pub const LAYOUT__376: &Mem0OutputLayout = &Mem0OutputLayout {
    arm0: LAYOUT__377,
    arm1: LAYOUT__383,
    arm2: LAYOUT__385,
    arm3: LAYOUT__386,
    arm4: LAYOUT__388,
    arm5: LAYOUT__389,
    arm6: LAYOUT__390,
    arm7: LAYOUT__391,
};
pub const LAYOUT__395: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__396: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__394: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__395,
    new_txn: LAYOUT__396,
};
pub const LAYOUT__393: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__394,
    _0: LAYOUT__166,
};
pub const LAYOUT__392: &WriteRdLayout = &WriteRdLayout {
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
    _0: LAYOUT__393,
};
pub const LAYOUT__398: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
};
pub const LAYOUT__399: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
};
pub const LAYOUT__397: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__398,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    high16: LAYOUT__399,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
};
pub const LAYOUT__342: &Mem0Layout = &Mem0Layout {
    _0: LAYOUT__343,
    input: LAYOUT__344,
    _arguments_mem0_output: LAYOUT__374,
    output: LAYOUT__376,
    _1: LAYOUT__392,
    pc_add: LAYOUT__397,
};
pub const LAYOUT__405: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__406: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__407: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__408: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__404: &MemoryArgLayout4LayoutArray =
    &[LAYOUT__405, LAYOUT__406, LAYOUT__407, LAYOUT__408];
pub const LAYOUT__409: &CycleArgLayout2LayoutArray = &[
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
pub const LAYOUT__403: &_Arguments_ReadSourceRegsSourceRegsLayout =
    &_Arguments_ReadSourceRegsSourceRegsLayout {
        memory_arg: LAYOUT__404,
        cycle_arg: LAYOUT__409,
    };
pub const LAYOUT__415: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__405,
    new_txn: LAYOUT__406,
};
pub const LAYOUT__417: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
};
pub const LAYOUT__416: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__417 };
pub const LAYOUT__414: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__415,
    _0: LAYOUT__416,
};
pub const LAYOUT__413: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__414,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
};
pub const LAYOUT__412: &ReadSourceRegsSourceRegsArm0_SuperLayout =
    &ReadSourceRegsSourceRegsArm0_SuperLayout { rboth: LAYOUT__413 };
pub const LAYOUT__411: &ReadSourceRegsSourceRegsArm0Layout = &ReadSourceRegsSourceRegsArm0Layout {
    _super: LAYOUT__412,
    _extra0: LAYOUT__407,
    _extra1: LAYOUT__408,
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
};
pub const LAYOUT__421: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__407,
    new_txn: LAYOUT__408,
};
pub const LAYOUT__423: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
};
pub const LAYOUT__422: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__423 };
pub const LAYOUT__420: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__421,
    _0: LAYOUT__422,
};
pub const LAYOUT__419: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__420,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
};
pub const LAYOUT__418: &ReadSourceRegsSourceRegsArm1_SuperLayout =
    &ReadSourceRegsSourceRegsArm1_SuperLayout {
        _0: LAYOUT__413,
        _1: LAYOUT__419,
    };
pub const LAYOUT__410: &ReadSourceRegsSourceRegsLayout = &ReadSourceRegsSourceRegsLayout {
    arm0: LAYOUT__411,
    arm1: LAYOUT__418,
};
pub const LAYOUT__402: &ReadSourceRegsLayout = &ReadSourceRegsLayout {
    is_same_reg: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    _arguments_read_source_regs_source_regs: LAYOUT__403,
    source_regs: LAYOUT__410,
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
pub const LAYOUT__425: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
};
pub const LAYOUT__426: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
};
pub const LAYOUT__424: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__425,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    high16: LAYOUT__426,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
};
pub const LAYOUT__428: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
};
pub const LAYOUT__427: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    upper_diff: LAYOUT__231,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
    med14: LAYOUT__428,
};
pub const LAYOUT__431: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__432: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__430: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__431,
    new_txn: LAYOUT__432,
};
pub const LAYOUT__434: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
};
pub const LAYOUT__433: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__434 };
pub const LAYOUT__429: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__430,
    _0: LAYOUT__433,
};
pub const LAYOUT__401: &MemStoreInputLayout = &MemStoreInputLayout {
    decoded: LAYOUT__345,
    source_regs: LAYOUT__402,
    addr_u32: LAYOUT__424,
    addr: LAYOUT__427,
    data_0: LAYOUT__429,
};
pub const LAYOUT__436: &ArgU8Layout4LayoutArray = &[
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
pub const LAYOUT__435: &_Arguments_Mem1OutputLayout = &_Arguments_Mem1OutputLayout {
    arg_u8: LAYOUT__436,
};
pub const LAYOUT__440: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__439: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__382,
    byte1: LAYOUT__440,
};
pub const LAYOUT__438: &OpSBLayout = &OpSBLayout {
    orig_bytes: LAYOUT__379,
    new_bytes: LAYOUT__439,
};
pub const LAYOUT__441: &Mem1OutputArm1Layout = &Mem1OutputArm1Layout {
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
pub const LAYOUT__442: &Mem1OutputArm2Layout = &Mem1OutputArm2Layout {
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
pub const LAYOUT__443: &Mem1OutputArm3Layout = &Mem1OutputArm3Layout {
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
pub const LAYOUT__444: &Mem1OutputArm4Layout = &Mem1OutputArm4Layout {
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
pub const LAYOUT__445: &Mem1OutputArm5Layout = &Mem1OutputArm5Layout {
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
pub const LAYOUT__446: &Mem1OutputArm6Layout = &Mem1OutputArm6Layout {
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
pub const LAYOUT__447: &Mem1OutputArm7Layout = &Mem1OutputArm7Layout {
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
pub const LAYOUT__437: &Mem1OutputLayout = &Mem1OutputLayout {
    arm0: LAYOUT__438,
    arm1: LAYOUT__441,
    arm2: LAYOUT__442,
    arm3: LAYOUT__443,
    arm4: LAYOUT__444,
    arm5: LAYOUT__445,
    arm6: LAYOUT__446,
    arm7: LAYOUT__447,
};
pub const LAYOUT__451: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__452: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__450: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__451,
    new_txn: LAYOUT__452,
};
pub const LAYOUT__454: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__453: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__454 };
pub const LAYOUT__449: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__450,
    _0: LAYOUT__453,
};
pub const LAYOUT__448: &MemStoreFinalizeLayout = &MemStoreFinalizeLayout { _0: LAYOUT__449 };
pub const LAYOUT__456: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__457: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__455: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__456,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
    high16: LAYOUT__457,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 145 },
    },
};
pub const LAYOUT__400: &Mem1Layout = &Mem1Layout {
    _0: LAYOUT__343,
    input: LAYOUT__401,
    _arguments_mem1_output: LAYOUT__435,
    output: LAYOUT__437,
    _1: LAYOUT__448,
    pc_add: LAYOUT__455,
};
pub const LAYOUT__468: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__469: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__467: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__468,
    new_txn: LAYOUT__469,
};
pub const LAYOUT__466: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__467 };
pub const LAYOUT__465: &ControlLoadRoot_SuperArm0_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm0_Super__0_SuperLayout { mem: LAYOUT__466 };
pub const LAYOUT__473: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__474: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__472: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__473,
    new_txn: LAYOUT__474,
};
pub const LAYOUT__471: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__472 };
pub const LAYOUT__470: &ControlLoadRoot_SuperArm0_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm0_Super__0_SuperLayout { mem: LAYOUT__471 };
pub const LAYOUT__478: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__479: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__477: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__478,
    new_txn: LAYOUT__479,
};
pub const LAYOUT__476: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__477 };
pub const LAYOUT__475: &ControlLoadRoot_SuperArm0_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm0_Super__0_SuperLayout { mem: LAYOUT__476 };
pub const LAYOUT__483: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__484: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__482: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__483,
    new_txn: LAYOUT__484,
};
pub const LAYOUT__481: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__482 };
pub const LAYOUT__480: &ControlLoadRoot_SuperArm0_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm0_Super__0_SuperLayout { mem: LAYOUT__481 };
pub const LAYOUT__488: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__489: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__487: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__488,
    new_txn: LAYOUT__489,
};
pub const LAYOUT__486: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__487 };
pub const LAYOUT__485: &ControlLoadRoot_SuperArm0_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm0_Super__0_SuperLayout { mem: LAYOUT__486 };
pub const LAYOUT__493: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__494: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__492: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__493,
    new_txn: LAYOUT__494,
};
pub const LAYOUT__491: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__492 };
pub const LAYOUT__490: &ControlLoadRoot_SuperArm0_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm0_Super__0_SuperLayout { mem: LAYOUT__491 };
pub const LAYOUT__498: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__499: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__497: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__498,
    new_txn: LAYOUT__499,
};
pub const LAYOUT__496: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__497 };
pub const LAYOUT__495: &ControlLoadRoot_SuperArm0_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm0_Super__0_SuperLayout { mem: LAYOUT__496 };
pub const LAYOUT__503: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__504: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__502: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__503,
    new_txn: LAYOUT__504,
};
pub const LAYOUT__501: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__502 };
pub const LAYOUT__500: &ControlLoadRoot_SuperArm0_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm0_Super__0_SuperLayout { mem: LAYOUT__501 };
pub const LAYOUT__464: &ControlLoadRoot_SuperArm0_Super__0_SuperLayout8LayoutArray = &[
    LAYOUT__465,
    LAYOUT__470,
    LAYOUT__475,
    LAYOUT__480,
    LAYOUT__485,
    LAYOUT__490,
    LAYOUT__495,
    LAYOUT__500,
];
pub const LAYOUT__463: &ControlLoadRoot_SuperArm0_SuperLayout =
    &ControlLoadRoot_SuperArm0_SuperLayout { _1: LAYOUT__464 };
pub const LAYOUT__507: &ControlLoadRoot_SuperArm1_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm1_Super__0_SuperLayout { mem: LAYOUT__466 };
pub const LAYOUT__508: &ControlLoadRoot_SuperArm1_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm1_Super__0_SuperLayout { mem: LAYOUT__471 };
pub const LAYOUT__509: &ControlLoadRoot_SuperArm1_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm1_Super__0_SuperLayout { mem: LAYOUT__476 };
pub const LAYOUT__510: &ControlLoadRoot_SuperArm1_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm1_Super__0_SuperLayout { mem: LAYOUT__481 };
pub const LAYOUT__511: &ControlLoadRoot_SuperArm1_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm1_Super__0_SuperLayout { mem: LAYOUT__486 };
pub const LAYOUT__512: &ControlLoadRoot_SuperArm1_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm1_Super__0_SuperLayout { mem: LAYOUT__491 };
pub const LAYOUT__513: &ControlLoadRoot_SuperArm1_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm1_Super__0_SuperLayout { mem: LAYOUT__496 };
pub const LAYOUT__514: &ControlLoadRoot_SuperArm1_Super__0_SuperLayout =
    &ControlLoadRoot_SuperArm1_Super__0_SuperLayout { mem: LAYOUT__501 };
pub const LAYOUT__506: &ControlLoadRoot_SuperArm1_Super__0_SuperLayout8LayoutArray = &[
    LAYOUT__507,
    LAYOUT__508,
    LAYOUT__509,
    LAYOUT__510,
    LAYOUT__511,
    LAYOUT__512,
    LAYOUT__513,
    LAYOUT__514,
];
pub const LAYOUT__505: &ControlLoadRoot_SuperArm1_SuperLayout =
    &ControlLoadRoot_SuperArm1_SuperLayout { _1: LAYOUT__506 };
pub const LAYOUT__462: &ControlLoadRoot_SuperLayout = &ControlLoadRoot_SuperLayout {
    arm0: LAYOUT__463,
    arm1: LAYOUT__505,
};
pub const LAYOUT__516: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__468,
    LAYOUT__469,
    LAYOUT__473,
    LAYOUT__474,
    LAYOUT__478,
    LAYOUT__479,
    LAYOUT__483,
    LAYOUT__484,
    LAYOUT__488,
    LAYOUT__489,
    LAYOUT__493,
    LAYOUT__494,
    LAYOUT__498,
    LAYOUT__499,
    LAYOUT__503,
    LAYOUT__504,
];
pub const LAYOUT__515: &_Arguments_ControlLoadRoot_SuperLayout =
    &_Arguments_ControlLoadRoot_SuperLayout {
        memory_arg: LAYOUT__516,
    };
pub const LAYOUT__461: &ControlLoadRootLayout = &ControlLoadRootLayout {
    _super: LAYOUT__462,
    _arguments_control_load_root__super: LAYOUT__515,
};
pub const LAYOUT__460: &Control0_SuperArm0Layout = &Control0_SuperArm0Layout {
    _super: LAYOUT__461,
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
pub const LAYOUT__522: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__467,
    _0: LAYOUT__40,
};
pub const LAYOUT__523: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__472,
    _0: LAYOUT__146,
};
pub const LAYOUT__521: &ControlResume_SuperArm0_SuperLayout =
    &ControlResume_SuperArm0_SuperLayout {
        pc: LAYOUT__522,
        mode: LAYOUT__523,
    };
pub const LAYOUT__520: &ControlResume_SuperArm0Layout = &ControlResume_SuperArm0Layout {
    _super: LAYOUT__521,
    _extra0: LAYOUT__478,
    _extra1: LAYOUT__479,
    _extra2: LAYOUT__483,
    _extra3: LAYOUT__484,
    _extra4: LAYOUT__488,
    _extra5: LAYOUT__489,
    _extra6: LAYOUT__493,
    _extra7: LAYOUT__494,
    _extra8: LAYOUT__498,
    _extra9: LAYOUT__499,
    _extra10: LAYOUT__503,
    _extra11: LAYOUT__504,
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
pub const LAYOUT__527: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__467,
    _0: LAYOUT__40,
};
pub const LAYOUT__526: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__527 };
pub const LAYOUT__529: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__472,
    _0: LAYOUT__146,
};
pub const LAYOUT__528: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__529 };
pub const LAYOUT__533: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
};
pub const LAYOUT__532: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__533 };
pub const LAYOUT__531: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__477,
    _0: LAYOUT__532,
};
pub const LAYOUT__530: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__531 };
pub const LAYOUT__537: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
};
pub const LAYOUT__536: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__537 };
pub const LAYOUT__535: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__482,
    _0: LAYOUT__536,
};
pub const LAYOUT__534: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__535 };
pub const LAYOUT__541: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
};
pub const LAYOUT__540: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__541 };
pub const LAYOUT__539: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__487,
    _0: LAYOUT__540,
};
pub const LAYOUT__538: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__539 };
pub const LAYOUT__545: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__544: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__545 };
pub const LAYOUT__543: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__492,
    _0: LAYOUT__544,
};
pub const LAYOUT__542: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__543 };
pub const LAYOUT__549: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
};
pub const LAYOUT__548: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__549 };
pub const LAYOUT__547: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__497,
    _0: LAYOUT__548,
};
pub const LAYOUT__546: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__547 };
pub const LAYOUT__553: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
};
pub const LAYOUT__552: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__553 };
pub const LAYOUT__551: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__502,
    _0: LAYOUT__552,
};
pub const LAYOUT__550: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__551 };
pub const LAYOUT__525: &ControlResume_SuperArm1_Super__0_SuperLayout8LayoutArray = &[
    LAYOUT__526,
    LAYOUT__528,
    LAYOUT__530,
    LAYOUT__534,
    LAYOUT__538,
    LAYOUT__542,
    LAYOUT__546,
    LAYOUT__550,
];
pub const LAYOUT__524: &ControlResume_SuperArm1_SuperLayout =
    &ControlResume_SuperArm1_SuperLayout { _1: LAYOUT__525 };
pub const LAYOUT__519: &ControlResume_SuperLayout = &ControlResume_SuperLayout {
    arm0: LAYOUT__520,
    arm1: LAYOUT__524,
};
pub const LAYOUT__555: &CycleArgLayout8LayoutArray = &[
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
pub const LAYOUT__554: &_Arguments_ControlResume_SuperLayout =
    &_Arguments_ControlResume_SuperLayout {
        memory_arg: LAYOUT__516,
        cycle_arg: LAYOUT__555,
    };
pub const LAYOUT__518: &ControlResumeLayout = &ControlResumeLayout {
    _super: LAYOUT__519,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _arguments_control_resume__super: LAYOUT__554,
};
pub const LAYOUT__517: &Control0_SuperArm1Layout = &Control0_SuperArm1Layout {
    _super: LAYOUT__518,
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
pub const LAYOUT__559: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
};
pub const LAYOUT__560: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__558: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    upper_diff: LAYOUT__559,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
    med14: LAYOUT__560,
};
pub const LAYOUT__557: &ControlUserECALLLayout = &ControlUserECALLLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    pc_addr: LAYOUT__558,
    load_inst: LAYOUT__522,
    new_pc_addr: LAYOUT__523,
    _0: LAYOUT__531,
};
pub const LAYOUT__556: &Control0_SuperArm2Layout = &Control0_SuperArm2Layout {
    _super: LAYOUT__557,
    _extra0: LAYOUT__483,
    _extra1: LAYOUT__484,
    _extra2: LAYOUT__488,
    _extra3: LAYOUT__489,
    _extra4: LAYOUT__493,
    _extra5: LAYOUT__494,
    _extra6: LAYOUT__498,
    _extra7: LAYOUT__499,
    _extra8: LAYOUT__503,
    _extra9: LAYOUT__504,
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
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra38: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra42: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra43: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra44: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__564: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
};
pub const LAYOUT__565: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__563: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__564,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 186 },
    },
    high16: LAYOUT__565,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 187 },
    },
};
pub const LAYOUT__562: &ControlMRETLayout = &ControlMRETLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    pc_addr: LAYOUT__558,
    load_inst: LAYOUT__522,
    pc: LAYOUT__523,
    pc_add: LAYOUT__563,
};
pub const LAYOUT__561: &Control0_SuperArm3Layout = &Control0_SuperArm3Layout {
    _super: LAYOUT__562,
    _extra0: LAYOUT__478,
    _extra1: LAYOUT__479,
    _extra2: LAYOUT__483,
    _extra3: LAYOUT__484,
    _extra4: LAYOUT__488,
    _extra5: LAYOUT__489,
    _extra6: LAYOUT__493,
    _extra7: LAYOUT__494,
    _extra8: LAYOUT__498,
    _extra9: LAYOUT__499,
    _extra10: LAYOUT__503,
    _extra11: LAYOUT__504,
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
pub const LAYOUT__571: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__477,
    _0: LAYOUT__532,
};
pub const LAYOUT__572: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__482,
    _0: LAYOUT__536,
};
pub const LAYOUT__573: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__487,
    _0: LAYOUT__540,
};
pub const LAYOUT__574: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__492,
    _0: LAYOUT__544,
};
pub const LAYOUT__575: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__497,
    _0: LAYOUT__548,
};
pub const LAYOUT__576: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__502,
    _0: LAYOUT__552,
};
pub const LAYOUT__570: &MemoryReadLayout8LayoutArray = &[
    LAYOUT__522,
    LAYOUT__523,
    LAYOUT__571,
    LAYOUT__572,
    LAYOUT__573,
    LAYOUT__574,
    LAYOUT__575,
    LAYOUT__576,
];
pub const LAYOUT__569: &ControlSuspend_SuperArm0_SuperLayout =
    &ControlSuspend_SuperArm0_SuperLayout { _1: LAYOUT__570 };
pub const LAYOUT__578: &ControlSuspend_SuperArm1_SuperLayout =
    &ControlSuspend_SuperArm1_SuperLayout {
        state: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        _0: LAYOUT__527,
        _1: LAYOUT__529,
    };
pub const LAYOUT__577: &ControlSuspend_SuperArm1Layout = &ControlSuspend_SuperArm1Layout {
    _super: LAYOUT__578,
    _extra0: LAYOUT__478,
    _extra1: LAYOUT__479,
    _extra2: LAYOUT__483,
    _extra3: LAYOUT__484,
    _extra4: LAYOUT__488,
    _extra5: LAYOUT__489,
    _extra6: LAYOUT__493,
    _extra7: LAYOUT__494,
    _extra8: LAYOUT__498,
    _extra9: LAYOUT__499,
    _extra10: LAYOUT__503,
    _extra11: LAYOUT__504,
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
pub const LAYOUT__568: &ControlSuspend_SuperLayout = &ControlSuspend_SuperLayout {
    arm0: LAYOUT__569,
    arm1: LAYOUT__577,
};
pub const LAYOUT__579: &_Arguments_ControlSuspend_SuperLayout =
    &_Arguments_ControlSuspend_SuperLayout {
        memory_arg: LAYOUT__516,
        cycle_arg: LAYOUT__555,
    };
pub const LAYOUT__567: &ControlSuspendLayout = &ControlSuspendLayout {
    _super: LAYOUT__568,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _arguments_control_suspend__super: LAYOUT__579,
};
pub const LAYOUT__566: &Control0_SuperArm4Layout = &Control0_SuperArm4Layout {
    _super: LAYOUT__567,
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
pub const LAYOUT__583: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__467,
    _0: LAYOUT__40,
};
pub const LAYOUT__584: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__472,
    _0: LAYOUT__146,
};
pub const LAYOUT__585: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__477,
    _0: LAYOUT__532,
};
pub const LAYOUT__586: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__482,
    _0: LAYOUT__536,
};
pub const LAYOUT__587: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__487,
    _0: LAYOUT__540,
};
pub const LAYOUT__588: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__492,
    _0: LAYOUT__544,
};
pub const LAYOUT__589: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__497,
    _0: LAYOUT__548,
};
pub const LAYOUT__590: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__502,
    _0: LAYOUT__552,
};
pub const LAYOUT__582: &MemoryPageOutLayout8LayoutArray = &[
    LAYOUT__583,
    LAYOUT__584,
    LAYOUT__585,
    LAYOUT__586,
    LAYOUT__587,
    LAYOUT__588,
    LAYOUT__589,
    LAYOUT__590,
];
pub const LAYOUT__581: &ControlStoreRootLayout = &ControlStoreRootLayout { _1: LAYOUT__582 };
pub const LAYOUT__580: &Control0_SuperArm5Layout = &Control0_SuperArm5Layout {
    _super: LAYOUT__581,
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
pub const LAYOUT__597: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__598: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__599: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__600: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__601: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__602: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__603: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__604: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__605: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__606: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__607: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__608: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__609: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__610: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__611: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__612: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__596: &ControlTable_SuperArm0_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__597,
    LAYOUT__598,
    LAYOUT__599,
    LAYOUT__600,
    LAYOUT__601,
    LAYOUT__602,
    LAYOUT__603,
    LAYOUT__604,
    LAYOUT__605,
    LAYOUT__606,
    LAYOUT__607,
    LAYOUT__608,
    LAYOUT__609,
    LAYOUT__610,
    LAYOUT__611,
    LAYOUT__612,
];
pub const LAYOUT__595: &ControlTable_SuperArm0_SuperLayout = &ControlTable_SuperArm0_SuperLayout {
    _1: LAYOUT__596,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
};
pub const LAYOUT__594: &ControlTable_SuperArm0Layout = &ControlTable_SuperArm0Layout {
    _super: LAYOUT__595,
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
pub const LAYOUT__616: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__617: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__618: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__619: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__620: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__621: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__622: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__623: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__624: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__625: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__626: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__627: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__628: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__629: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__630: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__631: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__615: &ControlTable_SuperArm1_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__616,
    LAYOUT__617,
    LAYOUT__618,
    LAYOUT__619,
    LAYOUT__620,
    LAYOUT__621,
    LAYOUT__622,
    LAYOUT__623,
    LAYOUT__624,
    LAYOUT__625,
    LAYOUT__626,
    LAYOUT__627,
    LAYOUT__628,
    LAYOUT__629,
    LAYOUT__630,
    LAYOUT__631,
];
pub const LAYOUT__614: &ControlTable_SuperArm1_SuperLayout = &ControlTable_SuperArm1_SuperLayout {
    _1: LAYOUT__615,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
};
pub const LAYOUT__613: &ControlTable_SuperArm1Layout = &ControlTable_SuperArm1Layout {
    _super: LAYOUT__614,
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
pub const LAYOUT__593: &ControlTable_SuperLayout = &ControlTable_SuperLayout {
    arm0: LAYOUT__594,
    arm1: LAYOUT__613,
};
pub const LAYOUT__633: &ArgU16Layout16LayoutArray = &[
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
pub const LAYOUT__634: &ArgU8Layout16LayoutArray = &[
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
pub const LAYOUT__632: &_Arguments_ControlTable_SuperLayout =
    &_Arguments_ControlTable_SuperLayout {
        arg_u16: LAYOUT__633,
        arg_u8: LAYOUT__634,
    };
pub const LAYOUT__592: &ControlTableLayout = &ControlTableLayout {
    _super: LAYOUT__593,
    entry: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    mode: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    _arguments_control_table__super: LAYOUT__632,
};
pub const LAYOUT__591: &Control0_SuperArm6Layout = &Control0_SuperArm6Layout {
    _super: LAYOUT__592,
    _extra0: LAYOUT__468,
    _extra1: LAYOUT__469,
    _extra2: LAYOUT__473,
    _extra3: LAYOUT__474,
    _extra4: LAYOUT__478,
    _extra5: LAYOUT__479,
    _extra6: LAYOUT__483,
    _extra7: LAYOUT__484,
    _extra8: LAYOUT__488,
    _extra9: LAYOUT__489,
    _extra10: LAYOUT__493,
    _extra11: LAYOUT__494,
    _extra12: LAYOUT__498,
    _extra13: LAYOUT__499,
    _extra14: LAYOUT__503,
    _extra15: LAYOUT__504,
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
pub const LAYOUT__637: &_Arguments_ControlDone__0Layout = &_Arguments_ControlDone__0Layout {
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    }],
};
pub const LAYOUT__639: &ControlDone__0Arm0_SuperLayout =
    &ControlDone__0Arm0_SuperLayout { _0: LAYOUT__41 };
pub const LAYOUT__640: &ControlDone__0Arm1Layout = &ControlDone__0Arm1Layout {
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__638: &ControlDone__0Layout = &ControlDone__0Layout {
    arm0: LAYOUT__639,
    arm1: LAYOUT__640,
};
pub const LAYOUT__636: &ControlDoneLayout = &ControlDoneLayout {
    _arguments_control_done__0: LAYOUT__637,
    _2: LAYOUT__638,
};
pub const LAYOUT__635: &Control0_SuperArm7Layout = &Control0_SuperArm7Layout {
    _super: LAYOUT__636,
    _extra0: LAYOUT__468,
    _extra1: LAYOUT__469,
    _extra2: LAYOUT__473,
    _extra3: LAYOUT__474,
    _extra4: LAYOUT__478,
    _extra5: LAYOUT__479,
    _extra6: LAYOUT__483,
    _extra7: LAYOUT__484,
    _extra8: LAYOUT__488,
    _extra9: LAYOUT__489,
    _extra10: LAYOUT__493,
    _extra11: LAYOUT__494,
    _extra12: LAYOUT__498,
    _extra13: LAYOUT__499,
    _extra14: LAYOUT__503,
    _extra15: LAYOUT__504,
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
pub const LAYOUT__459: &Control0_SuperLayout = &Control0_SuperLayout {
    arm0: LAYOUT__460,
    arm1: LAYOUT__517,
    arm2: LAYOUT__556,
    arm3: LAYOUT__561,
    arm4: LAYOUT__566,
    arm5: LAYOUT__580,
    arm6: LAYOUT__591,
    arm7: LAYOUT__635,
};
pub const LAYOUT__641: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
};
pub const LAYOUT__642: &_Arguments_Control0_SuperLayout = &_Arguments_Control0_SuperLayout {
    memory_arg: LAYOUT__516,
    cycle_arg: LAYOUT__555,
    arg_u16: LAYOUT__633,
    arg_u8: LAYOUT__634,
};
pub const LAYOUT__458: &Control0Layout = &Control0Layout {
    _super: LAYOUT__459,
    _0: LAYOUT__641,
    _arguments_control0__super: LAYOUT__642,
};
pub const LAYOUT__644: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__646: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
    },
};
pub const LAYOUT__647: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__645: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    upper_diff: LAYOUT__646,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    med14: LAYOUT__647,
};
pub const LAYOUT__649: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__468,
    LAYOUT__469,
    LAYOUT__473,
    LAYOUT__474,
    LAYOUT__478,
    LAYOUT__479,
    LAYOUT__483,
    LAYOUT__484,
];
pub const LAYOUT__650: &CycleArgLayout4LayoutArray = &[
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
pub const LAYOUT__651: &ArgU16Layout4LayoutArray = &[
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
pub const LAYOUT__652: &ArgU8Layout4LayoutArray = &[
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
pub const LAYOUT__648: &_Arguments_ECall0OutputLayout = &_Arguments_ECall0OutputLayout {
    memory_arg: LAYOUT__649,
    cycle_arg: LAYOUT__650,
    arg_u16: LAYOUT__651,
    arg_u8: LAYOUT__652,
};
pub const LAYOUT__658: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__657: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__658 };
pub const LAYOUT__656: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__467,
    _0: LAYOUT__657,
};
pub const LAYOUT__661: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__660: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__661 };
pub const LAYOUT__659: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__472,
    _0: LAYOUT__660,
};
pub const LAYOUT__663: &NondetRegLayout6LayoutArray = &[
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
pub const LAYOUT__662: &OneHot_6_Layout = &OneHot_6_Layout {
    _super: LAYOUT__663,
};
pub const LAYOUT__655: &MachineECallLayout = &MachineECallLayout {
    load_inst: LAYOUT__656,
    dispatch_idx: LAYOUT__659,
    dispatch: LAYOUT__662,
};
pub const LAYOUT__654: &ECall0OutputArm0Layout = &ECall0OutputArm0Layout {
    _super: LAYOUT__655,
    _extra0: LAYOUT__478,
    _extra1: LAYOUT__479,
    _extra2: LAYOUT__483,
    _extra3: LAYOUT__484,
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
pub const LAYOUT__665: &ECallTerminateLayout = &ECallTerminateLayout {
    a0: LAYOUT__656,
    a1: LAYOUT__659,
};
pub const LAYOUT__664: &ECall0OutputArm1Layout = &ECall0OutputArm1Layout {
    _super: LAYOUT__665,
    _extra0: LAYOUT__478,
    _extra1: LAYOUT__479,
    _extra2: LAYOUT__483,
    _extra3: LAYOUT__484,
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
pub const LAYOUT__670: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__669: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__670 };
pub const LAYOUT__668: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__477,
    _0: LAYOUT__669,
};
pub const LAYOUT__671: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__672: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
};
pub const LAYOUT__675: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
};
pub const LAYOUT__674: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__675 };
pub const LAYOUT__673: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__482,
    _0: LAYOUT__674,
};
pub const LAYOUT__677: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
};
pub const LAYOUT__679: &NondetRegLayout4LayoutArray = &[
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
pub const LAYOUT__678: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__679,
};
pub const LAYOUT__676: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__677,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    low2_hot: LAYOUT__678,
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
pub const LAYOUT__681: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
};
pub const LAYOUT__683: &NondetRegLayout4LayoutArray = &[
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
pub const LAYOUT__682: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__683,
};
pub const LAYOUT__680: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__681,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low2_hot: LAYOUT__682,
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
pub const LAYOUT__667: &ECallHostReadSetupLayout = &ECallHostReadSetupLayout {
    fd: LAYOUT__656,
    ptr: LAYOUT__659,
    len: LAYOUT__668,
    new_len: LAYOUT__671,
    diff: LAYOUT__672,
    _0: LAYOUT__673,
    ptr_decomp: LAYOUT__676,
    len_decomp: LAYOUT__680,
    len123: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    uneven: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
};
pub const LAYOUT__666: &ECall0OutputArm2Layout = &ECall0OutputArm2Layout {
    _super: LAYOUT__667,
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
pub const LAYOUT__685: &ECallHostWriteLayout = &ECallHostWriteLayout {
    fd: LAYOUT__656,
    ptr: LAYOUT__659,
    len: LAYOUT__668,
    new_len: LAYOUT__671,
    diff: LAYOUT__672,
    _0: LAYOUT__673,
};
pub const LAYOUT__684: &ECall0OutputArm3Layout = &ECall0OutputArm3Layout {
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
pub const LAYOUT__688: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__671,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    low2_hot: LAYOUT__678,
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
pub const LAYOUT__689: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__472,
    _0: LAYOUT__660,
};
pub const LAYOUT__690: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__279,
    byte1: LAYOUT__281,
};
pub const LAYOUT__692: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__691: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__284,
    byte1: LAYOUT__692,
};
pub const LAYOUT__687: &ECallHostReadBytesLayout = &ECallHostReadBytesLayout {
    len_decomp: LAYOUT__688,
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
    orig_word: LAYOUT__656,
    _0: LAYOUT__689,
    old_bytes: LAYOUT__690,
    new_bytes_0: LAYOUT__691,
};
pub const LAYOUT__686: &ECall0OutputArm4Layout = &ECall0OutputArm4Layout {
    _super: LAYOUT__687,
    _extra0: LAYOUT__478,
    _extra1: LAYOUT__479,
    _extra2: LAYOUT__483,
    _extra3: LAYOUT__484,
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
pub const LAYOUT__695: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__672,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low2_hot: LAYOUT__682,
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
pub const LAYOUT__698: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__467,
    _0: LAYOUT__657,
};
pub const LAYOUT__697: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    _0: LAYOUT__698,
};
pub const LAYOUT__699: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    _0: LAYOUT__689,
};
pub const LAYOUT__701: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__477,
    _0: LAYOUT__669,
};
pub const LAYOUT__700: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
    _0: LAYOUT__701,
};
pub const LAYOUT__703: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__482,
    _0: LAYOUT__674,
};
pub const LAYOUT__702: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    _0: LAYOUT__703,
};
pub const LAYOUT__696: &ECallHostReadWords__0_SuperLayout4LayoutArray =
    &[LAYOUT__697, LAYOUT__699, LAYOUT__700, LAYOUT__702];
pub const LAYOUT__694: &ECallHostReadWordsLayout = &ECallHostReadWordsLayout {
    len_decomp: LAYOUT__688,
    words_decomp: LAYOUT__695,
    _1: LAYOUT__696,
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
pub const LAYOUT__693: &ECall0OutputArm5Layout = &ECall0OutputArm5Layout {
    _super: LAYOUT__694,
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
pub const LAYOUT__704: &ECall0OutputArm6Layout = &ECall0OutputArm6Layout {
    _extra0: LAYOUT__468,
    _extra1: LAYOUT__469,
    _extra2: LAYOUT__473,
    _extra3: LAYOUT__474,
    _extra4: LAYOUT__478,
    _extra5: LAYOUT__479,
    _extra6: LAYOUT__483,
    _extra7: LAYOUT__484,
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
pub const LAYOUT__705: &ECall0OutputArm7Layout = &ECall0OutputArm7Layout {
    _extra0: LAYOUT__468,
    _extra1: LAYOUT__469,
    _extra2: LAYOUT__473,
    _extra3: LAYOUT__474,
    _extra4: LAYOUT__478,
    _extra5: LAYOUT__479,
    _extra6: LAYOUT__483,
    _extra7: LAYOUT__484,
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
pub const LAYOUT__653: &ECall0OutputLayout = &ECall0OutputLayout {
    arm0: LAYOUT__654,
    arm1: LAYOUT__664,
    arm2: LAYOUT__666,
    arm3: LAYOUT__684,
    arm4: LAYOUT__686,
    arm5: LAYOUT__693,
    arm6: LAYOUT__704,
    arm7: LAYOUT__705,
};
pub const LAYOUT__707: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__706: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__707,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
    high16: LAYOUT__456,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
};
pub const LAYOUT__643: &ECall0Layout = &ECall0Layout {
    s0: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    s1: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    s2: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    _0: LAYOUT__644,
    pc_addr: LAYOUT__645,
    _arguments_e_call0_output: LAYOUT__648,
    output: LAYOUT__653,
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
    add_pc: LAYOUT__706,
};
pub const LAYOUT__709: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__711: &NondetRegLayout24LayoutArray = &[
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
pub const LAYOUT__710: &PoseidonStateLayout = &PoseidonStateLayout {
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
    inner: LAYOUT__711,
    zcheck: &NondetExtRegLayout {
        _super: &Reg { offset: 64 },
    },
};
pub const LAYOUT__714: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__715: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__716: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__717: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__718: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__719: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__720: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__721: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__722: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__723: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__724: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__725: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__726: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__727: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__728: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__729: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__713: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__714,
    LAYOUT__715,
    LAYOUT__716,
    LAYOUT__717,
    LAYOUT__718,
    LAYOUT__719,
    LAYOUT__720,
    LAYOUT__721,
    LAYOUT__722,
    LAYOUT__723,
    LAYOUT__724,
    LAYOUT__725,
    LAYOUT__726,
    LAYOUT__727,
    LAYOUT__728,
    LAYOUT__729,
];
pub const LAYOUT__730: &CycleArgLayout8LayoutArray = &[
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
pub const LAYOUT__731: &ArgU16Layout24LayoutArray = &[
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
pub const LAYOUT__732: &ArgU8Layout2LayoutArray = &[
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
pub const LAYOUT__712: &_Arguments_Poseidon0StateLayout = &_Arguments_Poseidon0StateLayout {
    memory_arg: LAYOUT__713,
    cycle_arg: LAYOUT__730,
    arg_u16: LAYOUT__731,
    arg_u8: LAYOUT__732,
};
pub const LAYOUT__737: &PoseidonEntry_SuperArm0Layout = &PoseidonEntry_SuperArm0Layout {
    _super: LAYOUT__710,
    _extra0: LAYOUT__714,
    _extra1: LAYOUT__715,
    _extra2: LAYOUT__716,
    _extra3: LAYOUT__717,
    _extra4: LAYOUT__718,
    _extra5: LAYOUT__719,
    _extra6: LAYOUT__720,
    _extra7: LAYOUT__721,
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
pub const LAYOUT__741: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__714,
    new_txn: LAYOUT__715,
};
pub const LAYOUT__743: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__742: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__743 };
pub const LAYOUT__740: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__741,
    _0: LAYOUT__742,
};
pub const LAYOUT__739: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__740,
};
pub const LAYOUT__746: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__716,
    new_txn: LAYOUT__717,
};
pub const LAYOUT__748: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__747: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__748 };
pub const LAYOUT__745: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__746,
    _0: LAYOUT__747,
};
pub const LAYOUT__744: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__745,
};
pub const LAYOUT__751: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__718,
    new_txn: LAYOUT__719,
};
pub const LAYOUT__753: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__752: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__753 };
pub const LAYOUT__750: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__751,
    _0: LAYOUT__752,
};
pub const LAYOUT__749: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__750,
};
pub const LAYOUT__755: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__720,
    new_txn: LAYOUT__721,
};
pub const LAYOUT__757: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__756: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__757 };
pub const LAYOUT__754: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__755,
    _0: LAYOUT__756,
};
pub const LAYOUT__738: &PoseidonEcallLayout = &PoseidonEcallLayout {
    _super: LAYOUT__710,
    state_addr: LAYOUT__739,
    buf_in_addr: LAYOUT__744,
    buf_out_addr: LAYOUT__749,
    bits_and_count: LAYOUT__754,
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
pub const LAYOUT__736: &PoseidonEntry_SuperLayout = &PoseidonEntry_SuperLayout {
    _super: LAYOUT__710,
    arm0: LAYOUT__737,
    arm1: LAYOUT__738,
};
pub const LAYOUT__759: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__714,
    LAYOUT__715,
    LAYOUT__716,
    LAYOUT__717,
    LAYOUT__718,
    LAYOUT__719,
    LAYOUT__720,
    LAYOUT__721,
];
pub const LAYOUT__760: &CycleArgLayout4LayoutArray = &[
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
pub const LAYOUT__758: &_Arguments_PoseidonEntry_SuperLayout =
    &_Arguments_PoseidonEntry_SuperLayout {
        memory_arg: LAYOUT__759,
        cycle_arg: LAYOUT__760,
    };
pub const LAYOUT__735: &PoseidonEntryLayout = &PoseidonEntryLayout {
    _super: LAYOUT__736,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 202 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 203 },
        },
    },
    _arguments_poseidon_entry__super: LAYOUT__758,
};
pub const LAYOUT__734: &Poseidon0StateArm0Layout = &Poseidon0StateArm0Layout {
    _super: LAYOUT__735,
    _extra0: LAYOUT__722,
    _extra1: LAYOUT__723,
    _extra2: LAYOUT__724,
    _extra3: LAYOUT__725,
    _extra4: LAYOUT__726,
    _extra5: LAYOUT__727,
    _extra6: LAYOUT__728,
    _extra7: LAYOUT__729,
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
pub const LAYOUT__764: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__740,
};
pub const LAYOUT__765: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__745,
};
pub const LAYOUT__766: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__750,
};
pub const LAYOUT__767: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__754,
};
pub const LAYOUT__770: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__722,
    new_txn: LAYOUT__723,
};
pub const LAYOUT__772: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
};
pub const LAYOUT__771: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__772 };
pub const LAYOUT__769: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__770,
    _0: LAYOUT__771,
};
pub const LAYOUT__768: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__769,
};
pub const LAYOUT__775: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__724,
    new_txn: LAYOUT__725,
};
pub const LAYOUT__777: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
};
pub const LAYOUT__776: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__777 };
pub const LAYOUT__774: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__775,
    _0: LAYOUT__776,
};
pub const LAYOUT__773: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__774,
};
pub const LAYOUT__780: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__726,
    new_txn: LAYOUT__727,
};
pub const LAYOUT__782: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
};
pub const LAYOUT__781: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__782 };
pub const LAYOUT__779: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__780,
    _0: LAYOUT__781,
};
pub const LAYOUT__778: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__779,
};
pub const LAYOUT__785: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__728,
    new_txn: LAYOUT__729,
};
pub const LAYOUT__787: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
};
pub const LAYOUT__786: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__787 };
pub const LAYOUT__784: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__785,
    _0: LAYOUT__786,
};
pub const LAYOUT__783: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__784,
};
pub const LAYOUT__763: &ReadElemLayout8LayoutArray = &[
    LAYOUT__764,
    LAYOUT__765,
    LAYOUT__766,
    LAYOUT__767,
    LAYOUT__768,
    LAYOUT__773,
    LAYOUT__778,
    LAYOUT__783,
];
pub const LAYOUT__762: &PoseidonLoadStateLayout = &PoseidonLoadStateLayout {
    _super: LAYOUT__710,
    load_list: LAYOUT__763,
};
pub const LAYOUT__761: &Poseidon0StateArm1Layout = &Poseidon0StateArm1Layout {
    _super: LAYOUT__762,
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
pub const LAYOUT__792: &OneHot_3_Layout = &OneHot_3_Layout {
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
pub const LAYOUT__797: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__741 };
pub const LAYOUT__796: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__797,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__798: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__741,
    _0: LAYOUT__742,
};
pub const LAYOUT__795: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__740,
    arm1: LAYOUT__796,
    arm2: LAYOUT__798,
};
pub const LAYOUT__800: &MemoryArgLayout2LayoutArray = &[LAYOUT__714, LAYOUT__715];
pub const LAYOUT__799: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__800,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    }],
};
pub const LAYOUT__794: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__795,
    _arguments_memory_get__super: LAYOUT__799,
};
pub const LAYOUT__804: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__746 };
pub const LAYOUT__803: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__804,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__805: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__746,
    _0: LAYOUT__747,
};
pub const LAYOUT__802: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__745,
    arm1: LAYOUT__803,
    arm2: LAYOUT__805,
};
pub const LAYOUT__807: &MemoryArgLayout2LayoutArray = &[LAYOUT__716, LAYOUT__717];
pub const LAYOUT__806: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__807,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    }],
};
pub const LAYOUT__801: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__802,
    _arguments_memory_get__super: LAYOUT__806,
};
pub const LAYOUT__811: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__751 };
pub const LAYOUT__810: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__811,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__812: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__751,
    _0: LAYOUT__752,
};
pub const LAYOUT__809: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__750,
    arm1: LAYOUT__810,
    arm2: LAYOUT__812,
};
pub const LAYOUT__814: &MemoryArgLayout2LayoutArray = &[LAYOUT__718, LAYOUT__719];
pub const LAYOUT__813: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__814,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    }],
};
pub const LAYOUT__808: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__809,
    _arguments_memory_get__super: LAYOUT__813,
};
pub const LAYOUT__818: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__755 };
pub const LAYOUT__817: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__818,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__819: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__755,
    _0: LAYOUT__756,
};
pub const LAYOUT__816: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__754,
    arm1: LAYOUT__817,
    arm2: LAYOUT__819,
};
pub const LAYOUT__821: &MemoryArgLayout2LayoutArray = &[LAYOUT__720, LAYOUT__721];
pub const LAYOUT__820: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__821,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    }],
};
pub const LAYOUT__815: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__816,
    _arguments_memory_get__super: LAYOUT__820,
};
pub const LAYOUT__825: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__770 };
pub const LAYOUT__824: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__825,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
};
pub const LAYOUT__826: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__770,
    _0: LAYOUT__771,
};
pub const LAYOUT__823: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__769,
    arm1: LAYOUT__824,
    arm2: LAYOUT__826,
};
pub const LAYOUT__828: &MemoryArgLayout2LayoutArray = &[LAYOUT__722, LAYOUT__723];
pub const LAYOUT__827: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__828,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    }],
};
pub const LAYOUT__822: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__823,
    _arguments_memory_get__super: LAYOUT__827,
};
pub const LAYOUT__832: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__775 };
pub const LAYOUT__831: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__832,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
};
pub const LAYOUT__833: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__775,
    _0: LAYOUT__776,
};
pub const LAYOUT__830: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__774,
    arm1: LAYOUT__831,
    arm2: LAYOUT__833,
};
pub const LAYOUT__835: &MemoryArgLayout2LayoutArray = &[LAYOUT__724, LAYOUT__725];
pub const LAYOUT__834: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__835,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    }],
};
pub const LAYOUT__829: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__830,
    _arguments_memory_get__super: LAYOUT__834,
};
pub const LAYOUT__839: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__780 };
pub const LAYOUT__838: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__839,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
};
pub const LAYOUT__840: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__780,
    _0: LAYOUT__781,
};
pub const LAYOUT__837: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__779,
    arm1: LAYOUT__838,
    arm2: LAYOUT__840,
};
pub const LAYOUT__842: &MemoryArgLayout2LayoutArray = &[LAYOUT__726, LAYOUT__727];
pub const LAYOUT__841: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__842,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    }],
};
pub const LAYOUT__836: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__837,
    _arguments_memory_get__super: LAYOUT__841,
};
pub const LAYOUT__846: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__785 };
pub const LAYOUT__845: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__846,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
};
pub const LAYOUT__847: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__785,
    _0: LAYOUT__786,
};
pub const LAYOUT__844: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__784,
    arm1: LAYOUT__845,
    arm2: LAYOUT__847,
};
pub const LAYOUT__849: &MemoryArgLayout2LayoutArray = &[LAYOUT__728, LAYOUT__729];
pub const LAYOUT__848: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__849,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    }],
};
pub const LAYOUT__843: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__844,
    _arguments_memory_get__super: LAYOUT__848,
};
pub const LAYOUT__793: &MemoryGetLayout8LayoutArray = &[
    LAYOUT__794,
    LAYOUT__801,
    LAYOUT__808,
    LAYOUT__815,
    LAYOUT__822,
    LAYOUT__829,
    LAYOUT__836,
    LAYOUT__843,
];
pub const LAYOUT__791: &PoseidonLoadInShortLayout = &PoseidonLoadInShortLayout {
    _super: LAYOUT__710,
    tx_type: LAYOUT__792,
    load_list: LAYOUT__793,
};
pub const LAYOUT__850: &PoseidonLoadInLowLayout = &PoseidonLoadInLowLayout {
    _super: LAYOUT__710,
    tx_type: LAYOUT__792,
    load_list: LAYOUT__793,
};
pub const LAYOUT__851: &PoseidonLoadInHighLayout = &PoseidonLoadInHighLayout {
    _super: LAYOUT__710,
    tx_type: LAYOUT__792,
    load_list: LAYOUT__793,
};
pub const LAYOUT__790: &PoseidonLoadIn_SuperLayout = &PoseidonLoadIn_SuperLayout {
    _super: LAYOUT__710,
    arm0: LAYOUT__791,
    arm1: LAYOUT__850,
    arm2: LAYOUT__851,
};
pub const LAYOUT__852: &OneHot_3_Layout = &OneHot_3_Layout {
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
pub const LAYOUT__853: &_Arguments_PoseidonLoadIn_SuperLayout =
    &_Arguments_PoseidonLoadIn_SuperLayout {
        memory_arg: LAYOUT__713,
        cycle_arg: LAYOUT__730,
    };
pub const LAYOUT__789: &PoseidonLoadInLayout = &PoseidonLoadInLayout {
    _super: LAYOUT__790,
    _0: LAYOUT__852,
    _arguments_poseidon_load_in__super: LAYOUT__853,
};
pub const LAYOUT__788: &Poseidon0StateArm2Layout = &Poseidon0StateArm2Layout {
    _super: LAYOUT__789,
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
pub const LAYOUT__854: &Poseidon0StateArm3Layout = &Poseidon0StateArm3Layout {
    _super: LAYOUT__710,
    _extra0: LAYOUT__714,
    _extra1: LAYOUT__715,
    _extra2: LAYOUT__716,
    _extra3: LAYOUT__717,
    _extra4: LAYOUT__718,
    _extra5: LAYOUT__719,
    _extra6: LAYOUT__720,
    _extra7: LAYOUT__721,
    _extra8: LAYOUT__722,
    _extra9: LAYOUT__723,
    _extra10: LAYOUT__724,
    _extra11: LAYOUT__725,
    _extra12: LAYOUT__726,
    _extra13: LAYOUT__727,
    _extra14: LAYOUT__728,
    _extra15: LAYOUT__729,
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
pub const LAYOUT__855: &Poseidon0StateArm4Layout = &Poseidon0StateArm4Layout {
    _super: LAYOUT__710,
    _extra0: LAYOUT__714,
    _extra1: LAYOUT__715,
    _extra2: LAYOUT__716,
    _extra3: LAYOUT__717,
    _extra4: LAYOUT__718,
    _extra5: LAYOUT__719,
    _extra6: LAYOUT__720,
    _extra7: LAYOUT__721,
    _extra8: LAYOUT__722,
    _extra9: LAYOUT__723,
    _extra10: LAYOUT__724,
    _extra11: LAYOUT__725,
    _extra12: LAYOUT__726,
    _extra13: LAYOUT__727,
    _extra14: LAYOUT__728,
    _extra15: LAYOUT__729,
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
pub const LAYOUT__862: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__764 };
pub const LAYOUT__863: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__765 };
pub const LAYOUT__864: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__766 };
pub const LAYOUT__865: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__767 };
pub const LAYOUT__866: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__768 };
pub const LAYOUT__867: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__773 };
pub const LAYOUT__868: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__778 };
pub const LAYOUT__869: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__783 };
pub const LAYOUT__861: &PoseidonCheckOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__862,
    LAYOUT__863,
    LAYOUT__864,
    LAYOUT__865,
    LAYOUT__866,
    LAYOUT__867,
    LAYOUT__868,
    LAYOUT__869,
];
pub const LAYOUT__860: &PoseidonCheckOutLayout = &PoseidonCheckOutLayout {
    _super: LAYOUT__710,
    _1: LAYOUT__861,
    is_normal: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 196 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 197 },
        },
    },
};
pub const LAYOUT__859: &PoseidonDoOut_SuperArm0Layout = &PoseidonDoOut_SuperArm0Layout {
    _super: LAYOUT__860,
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
pub const LAYOUT__874: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__875: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
};
pub const LAYOUT__876: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    }],
};
pub const LAYOUT__879: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
};
pub const LAYOUT__878: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__879 };
pub const LAYOUT__880: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__879 };
pub const LAYOUT__877: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__878,
    arm1: LAYOUT__880,
};
pub const LAYOUT__873: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__874,
    high: LAYOUT__875,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    _arguments_field_to_word__0: LAYOUT__876,
    _2: LAYOUT__877,
};
pub const LAYOUT__881: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__741,
    _0: LAYOUT__742,
};
pub const LAYOUT__872: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__873,
    mw: LAYOUT__881,
};
pub const LAYOUT__884: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
};
pub const LAYOUT__885: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__886: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    }],
};
pub const LAYOUT__889: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
};
pub const LAYOUT__888: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__889 };
pub const LAYOUT__890: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__889 };
pub const LAYOUT__887: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__888,
    arm1: LAYOUT__890,
};
pub const LAYOUT__883: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__884,
    high: LAYOUT__885,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    _arguments_field_to_word__0: LAYOUT__886,
    _2: LAYOUT__887,
};
pub const LAYOUT__891: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__746,
    _0: LAYOUT__747,
};
pub const LAYOUT__882: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__883,
    mw: LAYOUT__891,
};
pub const LAYOUT__894: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__895: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
};
pub const LAYOUT__896: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    }],
};
pub const LAYOUT__899: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
};
pub const LAYOUT__898: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__899 };
pub const LAYOUT__900: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__899 };
pub const LAYOUT__897: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__898,
    arm1: LAYOUT__900,
};
pub const LAYOUT__893: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__894,
    high: LAYOUT__895,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 198 },
    },
    _arguments_field_to_word__0: LAYOUT__896,
    _2: LAYOUT__897,
};
pub const LAYOUT__901: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__751,
    _0: LAYOUT__752,
};
pub const LAYOUT__892: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__893,
    mw: LAYOUT__901,
};
pub const LAYOUT__904: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__905: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__906: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    }],
};
pub const LAYOUT__908: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__223 };
pub const LAYOUT__909: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__223 };
pub const LAYOUT__907: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__908,
    arm1: LAYOUT__909,
};
pub const LAYOUT__903: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__904,
    high: LAYOUT__905,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 199 },
    },
    _arguments_field_to_word__0: LAYOUT__906,
    _2: LAYOUT__907,
};
pub const LAYOUT__910: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__755,
    _0: LAYOUT__756,
};
pub const LAYOUT__902: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__903,
    mw: LAYOUT__910,
};
pub const LAYOUT__913: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__914: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__915: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    }],
};
pub const LAYOUT__918: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
};
pub const LAYOUT__917: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__918 };
pub const LAYOUT__919: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__918 };
pub const LAYOUT__916: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__917,
    arm1: LAYOUT__919,
};
pub const LAYOUT__912: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__913,
    high: LAYOUT__914,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 200 },
    },
    _arguments_field_to_word__0: LAYOUT__915,
    _2: LAYOUT__916,
};
pub const LAYOUT__920: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__770,
    _0: LAYOUT__771,
};
pub const LAYOUT__911: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__912,
    mw: LAYOUT__920,
};
pub const LAYOUT__923: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__924: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
};
pub const LAYOUT__925: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    }],
};
pub const LAYOUT__928: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__927: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__928 };
pub const LAYOUT__929: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__928 };
pub const LAYOUT__926: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__927,
    arm1: LAYOUT__929,
};
pub const LAYOUT__922: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__923,
    high: LAYOUT__924,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 201 },
    },
    _arguments_field_to_word__0: LAYOUT__925,
    _2: LAYOUT__926,
};
pub const LAYOUT__930: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__775,
    _0: LAYOUT__776,
};
pub const LAYOUT__921: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__922,
    mw: LAYOUT__930,
};
pub const LAYOUT__933: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
};
pub const LAYOUT__934: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
};
pub const LAYOUT__935: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    }],
};
pub const LAYOUT__938: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
};
pub const LAYOUT__937: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__938 };
pub const LAYOUT__939: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__938 };
pub const LAYOUT__936: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__937,
    arm1: LAYOUT__939,
};
pub const LAYOUT__932: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__933,
    high: LAYOUT__934,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 202 },
    },
    _arguments_field_to_word__0: LAYOUT__935,
    _2: LAYOUT__936,
};
pub const LAYOUT__940: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__780,
    _0: LAYOUT__781,
};
pub const LAYOUT__931: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__932,
    mw: LAYOUT__940,
};
pub const LAYOUT__943: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__944: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__945: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    }],
};
pub const LAYOUT__948: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
};
pub const LAYOUT__947: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__948 };
pub const LAYOUT__949: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__948 };
pub const LAYOUT__946: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__947,
    arm1: LAYOUT__949,
};
pub const LAYOUT__942: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__943,
    high: LAYOUT__944,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 203 },
    },
    _arguments_field_to_word__0: LAYOUT__945,
    _2: LAYOUT__946,
};
pub const LAYOUT__950: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__785,
    _0: LAYOUT__786,
};
pub const LAYOUT__941: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__942,
    mw: LAYOUT__950,
};
pub const LAYOUT__871: &PoseidonStoreOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__872,
    LAYOUT__882,
    LAYOUT__892,
    LAYOUT__902,
    LAYOUT__911,
    LAYOUT__921,
    LAYOUT__931,
    LAYOUT__941,
];
pub const LAYOUT__870: &PoseidonStoreOutLayout = &PoseidonStoreOutLayout {
    _super: LAYOUT__710,
    _1: LAYOUT__871,
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
pub const LAYOUT__858: &PoseidonDoOut_SuperLayout = &PoseidonDoOut_SuperLayout {
    _super: LAYOUT__710,
    arm0: LAYOUT__859,
    arm1: LAYOUT__870,
};
pub const LAYOUT__951: &_Arguments_PoseidonDoOut_SuperLayout =
    &_Arguments_PoseidonDoOut_SuperLayout {
        memory_arg: LAYOUT__713,
        cycle_arg: LAYOUT__730,
        arg_u16: LAYOUT__731,
    };
pub const LAYOUT__857: &PoseidonDoOutLayout = &PoseidonDoOutLayout {
    _super: LAYOUT__858,
    _arguments_poseidon_do_out__super: LAYOUT__951,
};
pub const LAYOUT__856: &Poseidon0StateArm5Layout = &Poseidon0StateArm5Layout {
    _super: LAYOUT__857,
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
pub const LAYOUT__954: &PoseidonPaging_SuperLayout = &PoseidonPaging_SuperLayout {
    _super: LAYOUT__710,
    arm0: LAYOUT__710,
    arm1: LAYOUT__710,
    arm2: LAYOUT__710,
    arm3: LAYOUT__710,
    arm4: LAYOUT__710,
    arm5: LAYOUT__710,
};
pub const LAYOUT__956: &NondetRegLayout6LayoutArray = &[
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
pub const LAYOUT__955: &OneHot_6_Layout = &OneHot_6_Layout {
    _super: LAYOUT__956,
};
pub const LAYOUT__958: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__957: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__874,
    _0: LAYOUT__958,
};
pub const LAYOUT__959: &_Arguments_PoseidonPaging__1Layout = &_Arguments_PoseidonPaging__1Layout {
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
pub const LAYOUT__963: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
};
pub const LAYOUT__962: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__875,
    _0: LAYOUT__963,
};
pub const LAYOUT__961: &PoseidonPaging__1Arm0_SuperLayout =
    &PoseidonPaging__1Arm0_SuperLayout { _0: LAYOUT__962 };
pub const LAYOUT__964: &PoseidonPaging__1Arm1_SuperLayout =
    &PoseidonPaging__1Arm1_SuperLayout { _0: LAYOUT__962 };
pub const LAYOUT__960: &PoseidonPaging__1Layout = &PoseidonPaging__1Layout {
    arm0: LAYOUT__961,
    arm1: LAYOUT__964,
};
pub const LAYOUT__953: &PoseidonPagingLayout = &PoseidonPagingLayout {
    _super: LAYOUT__954,
    cur_idx: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    cur_mode: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    mode_split: LAYOUT__955,
    _0: LAYOUT__957,
    _arguments_poseidon_paging__1: LAYOUT__959,
    _3: LAYOUT__960,
    _4: &NondetRegLayout {
        _super: &Reg { offset: 204 },
    },
};
pub const LAYOUT__952: &Poseidon0StateArm6Layout = &Poseidon0StateArm6Layout {
    _super: LAYOUT__953,
    _extra0: LAYOUT__714,
    _extra1: LAYOUT__715,
    _extra2: LAYOUT__716,
    _extra3: LAYOUT__717,
    _extra4: LAYOUT__718,
    _extra5: LAYOUT__719,
    _extra6: LAYOUT__720,
    _extra7: LAYOUT__721,
    _extra8: LAYOUT__722,
    _extra9: LAYOUT__723,
    _extra10: LAYOUT__724,
    _extra11: LAYOUT__725,
    _extra12: LAYOUT__726,
    _extra13: LAYOUT__727,
    _extra14: LAYOUT__728,
    _extra15: LAYOUT__729,
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
pub const LAYOUT__968: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__873,
    mw: LAYOUT__881,
};
pub const LAYOUT__969: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__883,
    mw: LAYOUT__891,
};
pub const LAYOUT__970: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__893,
    mw: LAYOUT__901,
};
pub const LAYOUT__971: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__903,
    mw: LAYOUT__910,
};
pub const LAYOUT__972: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__912,
    mw: LAYOUT__920,
};
pub const LAYOUT__973: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__922,
    mw: LAYOUT__930,
};
pub const LAYOUT__974: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__932,
    mw: LAYOUT__940,
};
pub const LAYOUT__975: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__942,
    mw: LAYOUT__950,
};
pub const LAYOUT__967: &PoseidonStoreState__0_SuperLayout8LayoutArray = &[
    LAYOUT__968,
    LAYOUT__969,
    LAYOUT__970,
    LAYOUT__971,
    LAYOUT__972,
    LAYOUT__973,
    LAYOUT__974,
    LAYOUT__975,
];
pub const LAYOUT__966: &PoseidonStoreStateLayout = &PoseidonStoreStateLayout {
    _super: LAYOUT__710,
    _1: LAYOUT__967,
};
pub const LAYOUT__965: &Poseidon0StateArm7Layout = &Poseidon0StateArm7Layout {
    _super: LAYOUT__966,
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
pub const LAYOUT__733: &Poseidon0StateLayout = &Poseidon0StateLayout {
    _super: LAYOUT__710,
    arm0: LAYOUT__734,
    arm1: LAYOUT__761,
    arm2: LAYOUT__788,
    arm3: LAYOUT__854,
    arm4: LAYOUT__855,
    arm5: LAYOUT__856,
    arm6: LAYOUT__952,
    arm7: LAYOUT__965,
};
pub const LAYOUT__708: &Poseidon0Layout = &Poseidon0Layout {
    _0: LAYOUT__709,
    state: LAYOUT__710,
    _arguments_poseidon0_state: LAYOUT__712,
    state_redef: LAYOUT__733,
};
pub const LAYOUT__977: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__982: &SBoxLayout24LayoutArray = &[
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
pub const LAYOUT__981: &DoExtRoundLayout = &DoExtRoundLayout { _1: LAYOUT__982 };
pub const LAYOUT__984: &NondetRegLayout8LayoutArray = &[
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
pub const LAYOUT__983: &OneHot_8_Layout = &OneHot_8_Layout {
    _super: LAYOUT__984,
};
pub const LAYOUT__980: &DoExtRoundByIdxLayout = &DoExtRoundByIdxLayout {
    _super: LAYOUT__981,
    idx_hot: LAYOUT__983,
};
pub const LAYOUT__979: &PoseidonExtRoundLayout = &PoseidonExtRoundLayout {
    _super: LAYOUT__710,
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
    next_inner: LAYOUT__980,
};
pub const LAYOUT__988: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
};
pub const LAYOUT__989: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__990: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
};
pub const LAYOUT__991: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__992: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
};
pub const LAYOUT__993: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
};
pub const LAYOUT__994: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__995: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
};
pub const LAYOUT__996: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__997: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
};
pub const LAYOUT__998: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__999: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
};
pub const LAYOUT__1000: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
    },
};
pub const LAYOUT__1001: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
    },
};
pub const LAYOUT__1002: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
};
pub const LAYOUT__1003: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__1004: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
};
pub const LAYOUT__1005: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
};
pub const LAYOUT__1006: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
};
pub const LAYOUT__1007: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__1008: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
};
pub const LAYOUT__987: &DoIntRoundLayout21LayoutArray = &[
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
    LAYOUT__1000,
    LAYOUT__1001,
    LAYOUT__1002,
    LAYOUT__1003,
    LAYOUT__1004,
    LAYOUT__1005,
    LAYOUT__1006,
    LAYOUT__1007,
    LAYOUT__1008,
];
pub const LAYOUT__986: &DoIntRoundsLayout = &DoIntRoundsLayout {
    _super: LAYOUT__987,
};
pub const LAYOUT__985: &PoseidonIntRoundsLayout = &PoseidonIntRoundsLayout {
    _super: LAYOUT__710,
    next_inner: LAYOUT__986,
};
pub const LAYOUT__978: &Poseidon1StateLayout = &Poseidon1StateLayout {
    _super: LAYOUT__710,
    arm0: LAYOUT__979,
    arm1: LAYOUT__985,
    arm2: LAYOUT__710,
    arm3: LAYOUT__710,
    arm4: LAYOUT__710,
    arm5: LAYOUT__710,
    arm6: LAYOUT__710,
    arm7: LAYOUT__710,
};
pub const LAYOUT__976: &Poseidon1Layout = &Poseidon1Layout {
    _0: LAYOUT__977,
    state: LAYOUT__710,
    state_redef: LAYOUT__978,
};
pub const LAYOUT__1010: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__1012: &NondetRegLayout32LayoutArray = &[
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
pub const LAYOUT__1013: &NondetRegLayout32LayoutArray = &[
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
pub const LAYOUT__1014: &NondetRegLayout32LayoutArray = &[
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
pub const LAYOUT__1011: &ShaStateLayout = &ShaStateLayout {
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
    a: LAYOUT__1012,
    e: LAYOUT__1013,
    w: LAYOUT__1014,
};
pub const LAYOUT__1017: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1018: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1019: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1020: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1021: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1022: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1023: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1024: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1025: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1026: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1016: &MemoryArgLayout10LayoutArray = &[
    LAYOUT__1017,
    LAYOUT__1018,
    LAYOUT__1019,
    LAYOUT__1020,
    LAYOUT__1021,
    LAYOUT__1022,
    LAYOUT__1023,
    LAYOUT__1024,
    LAYOUT__1025,
    LAYOUT__1026,
];
pub const LAYOUT__1027: &CycleArgLayout5LayoutArray = &[
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
pub const LAYOUT__1015: &_Arguments_Sha0StateLayout = &_Arguments_Sha0StateLayout {
    memory_arg: LAYOUT__1016,
    cycle_arg: LAYOUT__1027,
};
pub const LAYOUT__1032: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1017,
    new_txn: LAYOUT__1018,
};
pub const LAYOUT__1034: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__1033: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1034 };
pub const LAYOUT__1031: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1032,
    _0: LAYOUT__1033,
};
pub const LAYOUT__1030: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1031,
};
pub const LAYOUT__1037: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1019,
    new_txn: LAYOUT__1020,
};
pub const LAYOUT__1039: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__1038: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1039 };
pub const LAYOUT__1036: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1037,
    _0: LAYOUT__1038,
};
pub const LAYOUT__1035: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1036,
};
pub const LAYOUT__1042: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1021,
    new_txn: LAYOUT__1022,
};
pub const LAYOUT__1044: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 182 },
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
pub const LAYOUT__1046: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1023,
    new_txn: LAYOUT__1024,
};
pub const LAYOUT__1048: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    },
};
pub const LAYOUT__1047: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1048 };
pub const LAYOUT__1045: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1046,
    _0: LAYOUT__1047,
};
pub const LAYOUT__1051: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1025,
    new_txn: LAYOUT__1026,
};
pub const LAYOUT__1053: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1052: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1053 };
pub const LAYOUT__1050: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1051,
    _0: LAYOUT__1052,
};
pub const LAYOUT__1049: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1050,
};
pub const LAYOUT__1029: &ShaEcallLayout = &ShaEcallLayout {
    _super: LAYOUT__1011,
    state_in_addr: LAYOUT__1030,
    state_out_addr: LAYOUT__1035,
    data_addr: LAYOUT__1040,
    _0: LAYOUT__1045,
    k_addr: LAYOUT__1049,
};
pub const LAYOUT__1056: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1042,
    _0: LAYOUT__1043,
};
pub const LAYOUT__1057: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1046,
    _0: LAYOUT__1047,
};
pub const LAYOUT__1055: &ShaLoadStateLayout = &ShaLoadStateLayout {
    _super: LAYOUT__1011,
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
    a32: LAYOUT__1031,
    e32: LAYOUT__1036,
    _0: LAYOUT__1056,
    _1: LAYOUT__1057,
};
pub const LAYOUT__1054: &Sha0StateArm1Layout = &Sha0StateArm1Layout {
    _super: LAYOUT__1055,
    _extra0: LAYOUT__1025,
    _extra1: LAYOUT__1026,
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1061: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__1012,
};
pub const LAYOUT__1062: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1063: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1060: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1061,
    low_carry: LAYOUT__1062,
    high_carry: LAYOUT__1063,
};
pub const LAYOUT__1065: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__1013,
};
pub const LAYOUT__1066: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1067: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1064: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1065,
    low_carry: LAYOUT__1066,
    high_carry: LAYOUT__1067,
};
pub const LAYOUT__1059: &ShaLoadDataLayout = &ShaLoadDataLayout {
    _super: LAYOUT__1011,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
    },
    k: LAYOUT__1031,
    w_mem: LAYOUT__1036,
    w_bits: LAYOUT__1014,
    a: LAYOUT__1060,
    e: LAYOUT__1064,
};
pub const LAYOUT__1058: &Sha0StateArm2Layout = &Sha0StateArm2Layout {
    _super: LAYOUT__1059,
    _extra0: LAYOUT__1021,
    _extra1: LAYOUT__1022,
    _extra2: LAYOUT__1023,
    _extra3: LAYOUT__1024,
    _extra4: LAYOUT__1025,
    _extra5: LAYOUT__1026,
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
pub const LAYOUT__1071: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__1014,
};
pub const LAYOUT__1070: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1071,
    low_carry: LAYOUT__1062,
    high_carry: LAYOUT__1063,
};
pub const LAYOUT__1072: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1061,
    low_carry: LAYOUT__1066,
    high_carry: LAYOUT__1067,
};
pub const LAYOUT__1074: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1075: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1073: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1065,
    low_carry: LAYOUT__1074,
    high_carry: LAYOUT__1075,
};
pub const LAYOUT__1069: &ShaMixLayout = &ShaMixLayout {
    _super: LAYOUT__1011,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
    },
    k: LAYOUT__1031,
    w_bits: LAYOUT__1070,
    a: LAYOUT__1072,
    e: LAYOUT__1073,
};
pub const LAYOUT__1068: &Sha0StateArm3Layout = &Sha0StateArm3Layout {
    _super: LAYOUT__1069,
    _extra0: LAYOUT__1019,
    _extra1: LAYOUT__1020,
    _extra2: LAYOUT__1021,
    _extra3: LAYOUT__1022,
    _extra4: LAYOUT__1023,
    _extra5: LAYOUT__1024,
    _extra6: LAYOUT__1025,
    _extra7: LAYOUT__1026,
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
pub const LAYOUT__1079: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1080: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1078: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1061,
    low_carry: LAYOUT__1079,
    high_carry: LAYOUT__1080,
};
pub const LAYOUT__1082: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1083: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1081: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1065,
    low_carry: LAYOUT__1082,
    high_carry: LAYOUT__1083,
};
pub const LAYOUT__1084: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1032,
    _0: LAYOUT__1033,
};
pub const LAYOUT__1085: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1037,
    _0: LAYOUT__1038,
};
pub const LAYOUT__1077: &ShaStoreStateLayout = &ShaStoreStateLayout {
    _super: LAYOUT__1011,
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
    a: LAYOUT__1078,
    e: LAYOUT__1081,
    _1: LAYOUT__1084,
    _2: LAYOUT__1085,
};
pub const LAYOUT__1076: &Sha0StateArm4Layout = &Sha0StateArm4Layout {
    _super: LAYOUT__1077,
    _extra0: LAYOUT__1021,
    _extra1: LAYOUT__1022,
    _extra2: LAYOUT__1023,
    _extra3: LAYOUT__1024,
    _extra4: LAYOUT__1025,
    _extra5: LAYOUT__1026,
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
pub const LAYOUT__1086: &Sha0StateArm5Layout = &Sha0StateArm5Layout {
    _super: LAYOUT__1011,
    _extra0: LAYOUT__1017,
    _extra1: LAYOUT__1018,
    _extra2: LAYOUT__1019,
    _extra3: LAYOUT__1020,
    _extra4: LAYOUT__1021,
    _extra5: LAYOUT__1022,
    _extra6: LAYOUT__1023,
    _extra7: LAYOUT__1024,
    _extra8: LAYOUT__1025,
    _extra9: LAYOUT__1026,
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
pub const LAYOUT__1087: &Sha0StateArm6Layout = &Sha0StateArm6Layout {
    _super: LAYOUT__1011,
    _extra0: LAYOUT__1017,
    _extra1: LAYOUT__1018,
    _extra2: LAYOUT__1019,
    _extra3: LAYOUT__1020,
    _extra4: LAYOUT__1021,
    _extra5: LAYOUT__1022,
    _extra6: LAYOUT__1023,
    _extra7: LAYOUT__1024,
    _extra8: LAYOUT__1025,
    _extra9: LAYOUT__1026,
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
pub const LAYOUT__1088: &Sha0StateArm7Layout = &Sha0StateArm7Layout {
    _super: LAYOUT__1011,
    _extra0: LAYOUT__1017,
    _extra1: LAYOUT__1018,
    _extra2: LAYOUT__1019,
    _extra3: LAYOUT__1020,
    _extra4: LAYOUT__1021,
    _extra5: LAYOUT__1022,
    _extra6: LAYOUT__1023,
    _extra7: LAYOUT__1024,
    _extra8: LAYOUT__1025,
    _extra9: LAYOUT__1026,
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
pub const LAYOUT__1028: &Sha0StateLayout = &Sha0StateLayout {
    _super: LAYOUT__1011,
    arm0: LAYOUT__1029,
    arm1: LAYOUT__1054,
    arm2: LAYOUT__1058,
    arm3: LAYOUT__1068,
    arm4: LAYOUT__1076,
    arm5: LAYOUT__1086,
    arm6: LAYOUT__1087,
    arm7: LAYOUT__1088,
};
pub const LAYOUT__1009: &Sha0Layout = &Sha0Layout {
    _0: LAYOUT__1010,
    state: LAYOUT__1011,
    _arguments_sha0_state: LAYOUT__1015,
    state_redef: LAYOUT__1028,
};
pub const LAYOUT__1090: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__1092: &NondetRegLayout16LayoutArray = &[
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
pub const LAYOUT__1091: &BigIntStateLayout = &BigIntStateLayout {
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
    bytes: LAYOUT__1092,
    next_state: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
};
pub const LAYOUT__1095: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1096: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1097: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1098: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1099: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1100: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1101: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1102: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1103: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1104: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1105: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1106: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1094: &MemoryArgLayout12LayoutArray = &[
    LAYOUT__1095,
    LAYOUT__1096,
    LAYOUT__1097,
    LAYOUT__1098,
    LAYOUT__1099,
    LAYOUT__1100,
    LAYOUT__1101,
    LAYOUT__1102,
    LAYOUT__1103,
    LAYOUT__1104,
    LAYOUT__1105,
    LAYOUT__1106,
];
pub const LAYOUT__1107: &CycleArgLayout6LayoutArray = &[
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
pub const LAYOUT__1108: &ArgU8Layout18LayoutArray = &[
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
pub const LAYOUT__1109: &ArgU16Layout4LayoutArray = &[
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
pub const LAYOUT__1093: &_Arguments_BigInt0StateLayout = &_Arguments_BigInt0StateLayout {
    memory_arg: LAYOUT__1094,
    cycle_arg: LAYOUT__1107,
    arg_u8: LAYOUT__1108,
    arg_u16: LAYOUT__1109,
};
pub const LAYOUT__1114: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1095,
    new_txn: LAYOUT__1096,
};
pub const LAYOUT__1113: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1114,
    _0: LAYOUT__532,
};
pub const LAYOUT__1117: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1097,
    new_txn: LAYOUT__1098,
};
pub const LAYOUT__1116: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1117,
    _0: LAYOUT__536,
};
pub const LAYOUT__1115: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1116,
};
pub const LAYOUT__1112: &BigIntEcallLayout = &BigIntEcallLayout {
    _super: LAYOUT__1091,
    mode: LAYOUT__1113,
    pc: LAYOUT__1115,
};
pub const LAYOUT__1111: &BigInt0StateArm0Layout = &BigInt0StateArm0Layout {
    _super: LAYOUT__1112,
    _extra0: LAYOUT__1099,
    _extra1: LAYOUT__1100,
    _extra2: LAYOUT__1101,
    _extra3: LAYOUT__1102,
    _extra4: LAYOUT__1103,
    _extra5: LAYOUT__1104,
    _extra6: LAYOUT__1105,
    _extra7: LAYOUT__1106,
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
pub const LAYOUT__1120: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
};
pub const LAYOUT__1121: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__1119: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1120,
    byte1: LAYOUT__1121,
};
pub const LAYOUT__1122: &NondetRegLayout5LayoutArray = &[
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
pub const LAYOUT__1124: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
};
pub const LAYOUT__1125: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
};
pub const LAYOUT__1123: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__1124,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
    high16: LAYOUT__1125,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
};
pub const LAYOUT__1126: &OneHot_3_Layout = &OneHot_3_Layout {
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
pub const LAYOUT__1128: &ArgU16Layout2LayoutArray = &[
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
pub const LAYOUT__1129: &ArgU8Layout16LayoutArray = &[
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
pub const LAYOUT__1130: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__1099,
    LAYOUT__1100,
    LAYOUT__1101,
    LAYOUT__1102,
    LAYOUT__1103,
    LAYOUT__1104,
    LAYOUT__1105,
    LAYOUT__1106,
];
pub const LAYOUT__1131: &CycleArgLayout4LayoutArray = &[
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
pub const LAYOUT__1127: &_Arguments_BigIntStepBytesLayout = &_Arguments_BigIntStepBytesLayout {
    arg_u16: LAYOUT__1128,
    arg_u8: LAYOUT__1129,
    memory_arg: LAYOUT__1130,
    cycle_arg: LAYOUT__1131,
};
pub const LAYOUT__1136: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
};
pub const LAYOUT__1137: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__1135: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    upper_diff: LAYOUT__1136,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    med14: LAYOUT__1137,
};
pub const LAYOUT__1134: &BigIntAddrLayout = &BigIntAddrLayout {
    _super: LAYOUT__1135,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__1142: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
};
pub const LAYOUT__1143: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__1141: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1142,
    byte1: LAYOUT__1143,
};
pub const LAYOUT__1145: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
};
pub const LAYOUT__1146: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
};
pub const LAYOUT__1144: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1145,
    byte1: LAYOUT__1146,
};
pub const LAYOUT__1140: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1141,
    high: LAYOUT__1144,
};
pub const LAYOUT__1148: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1099,
    new_txn: LAYOUT__1100,
};
pub const LAYOUT__1147: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1148,
    _0: LAYOUT__540,
};
pub const LAYOUT__1139: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1140,
    _0: LAYOUT__1147,
};
pub const LAYOUT__1152: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
};
pub const LAYOUT__1153: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
};
pub const LAYOUT__1151: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1152,
    byte1: LAYOUT__1153,
};
pub const LAYOUT__1155: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
};
pub const LAYOUT__1156: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
};
pub const LAYOUT__1154: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1155,
    byte1: LAYOUT__1156,
};
pub const LAYOUT__1150: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1151,
    high: LAYOUT__1154,
};
pub const LAYOUT__1158: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1101,
    new_txn: LAYOUT__1102,
};
pub const LAYOUT__1157: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1158,
    _0: LAYOUT__544,
};
pub const LAYOUT__1149: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1150,
    _0: LAYOUT__1157,
};
pub const LAYOUT__1162: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__1163: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
};
pub const LAYOUT__1161: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1162,
    byte1: LAYOUT__1163,
};
pub const LAYOUT__1165: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
};
pub const LAYOUT__1166: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__1164: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1165,
    byte1: LAYOUT__1166,
};
pub const LAYOUT__1160: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1161,
    high: LAYOUT__1164,
};
pub const LAYOUT__1168: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1103,
    new_txn: LAYOUT__1104,
};
pub const LAYOUT__1167: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1168,
    _0: LAYOUT__548,
};
pub const LAYOUT__1159: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1160,
    _0: LAYOUT__1167,
};
pub const LAYOUT__1172: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__1173: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
};
pub const LAYOUT__1171: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1172,
    byte1: LAYOUT__1173,
};
pub const LAYOUT__1175: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
};
pub const LAYOUT__1176: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
};
pub const LAYOUT__1174: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1175,
    byte1: LAYOUT__1176,
};
pub const LAYOUT__1170: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1171,
    high: LAYOUT__1174,
};
pub const LAYOUT__1178: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1105,
    new_txn: LAYOUT__1106,
};
pub const LAYOUT__1177: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1178,
    _0: LAYOUT__552,
};
pub const LAYOUT__1169: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1170,
    _0: LAYOUT__1177,
};
pub const LAYOUT__1138: &BigIntReadWords_SuperLayout4LayoutArray =
    &[LAYOUT__1139, LAYOUT__1149, LAYOUT__1159, LAYOUT__1169];
pub const LAYOUT__1133: &BigIntReadLayout = &BigIntReadLayout {
    addr: LAYOUT__1134,
    words: LAYOUT__1138,
};
pub const LAYOUT__1181: &NondetU8RegLayout16LayoutArray = &[
    LAYOUT__1142,
    LAYOUT__1143,
    LAYOUT__1145,
    LAYOUT__1146,
    LAYOUT__1152,
    LAYOUT__1153,
    LAYOUT__1155,
    LAYOUT__1156,
    LAYOUT__1162,
    LAYOUT__1163,
    LAYOUT__1165,
    LAYOUT__1166,
    LAYOUT__1172,
    LAYOUT__1173,
    LAYOUT__1175,
    LAYOUT__1176,
];
pub const LAYOUT__1180: &BigIntWitnessLayout = &BigIntWitnessLayout {
    _super: LAYOUT__1181,
};
pub const LAYOUT__1184: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1148,
    _0: LAYOUT__540,
};
pub const LAYOUT__1183: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1184 };
pub const LAYOUT__1186: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1158,
    _0: LAYOUT__544,
};
pub const LAYOUT__1185: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1186 };
pub const LAYOUT__1188: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1168,
    _0: LAYOUT__548,
};
pub const LAYOUT__1187: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1188 };
pub const LAYOUT__1190: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1178,
    _0: LAYOUT__552,
};
pub const LAYOUT__1189: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1190 };
pub const LAYOUT__1182: &BigIntWrite__0_SuperLayout4LayoutArray =
    &[LAYOUT__1183, LAYOUT__1185, LAYOUT__1187, LAYOUT__1189];
pub const LAYOUT__1179: &BigIntWriteLayout = &BigIntWriteLayout {
    _super: LAYOUT__1180,
    addr: LAYOUT__1134,
    _1: LAYOUT__1182,
};
pub const LAYOUT__1191: &BigIntStepBytesArm2Layout = &BigIntStepBytesArm2Layout {
    _super: LAYOUT__1180,
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
    _extra2: LAYOUT__1099,
    _extra3: LAYOUT__1100,
    _extra4: LAYOUT__1101,
    _extra5: LAYOUT__1102,
    _extra6: LAYOUT__1103,
    _extra7: LAYOUT__1104,
    _extra8: LAYOUT__1105,
    _extra9: LAYOUT__1106,
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
pub const LAYOUT__1132: &BigIntStepBytesLayout = &BigIntStepBytesLayout {
    arm0: LAYOUT__1133,
    arm1: LAYOUT__1179,
    arm2: LAYOUT__1191,
};
pub const LAYOUT__1118: &BigIntStepLayout = &BigIntStepLayout {
    _super: LAYOUT__1091,
    load_inst_0: LAYOUT__1113,
    inst_high: LAYOUT__1119,
    poly_op: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
    mem_op: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
    reg_bits: LAYOUT__1122,
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
    base_addr_u32: LAYOUT__1116,
    data_addr_u32: LAYOUT__1123,
    mem_op_one_hot: LAYOUT__1126,
    _arguments_big_int_step_bytes: LAYOUT__1127,
    bytes: LAYOUT__1132,
    _2: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
};
pub const LAYOUT__1192: &BigInt0StateArm2Layout = &BigInt0StateArm2Layout {
    _super: LAYOUT__1091,
    _extra0: LAYOUT__1095,
    _extra1: LAYOUT__1096,
    _extra2: LAYOUT__1097,
    _extra3: LAYOUT__1098,
    _extra4: LAYOUT__1099,
    _extra5: LAYOUT__1100,
    _extra6: LAYOUT__1101,
    _extra7: LAYOUT__1102,
    _extra8: LAYOUT__1103,
    _extra9: LAYOUT__1104,
    _extra10: LAYOUT__1105,
    _extra11: LAYOUT__1106,
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
pub const LAYOUT__1193: &BigInt0StateArm3Layout = &BigInt0StateArm3Layout {
    _super: LAYOUT__1091,
    _extra0: LAYOUT__1095,
    _extra1: LAYOUT__1096,
    _extra2: LAYOUT__1097,
    _extra3: LAYOUT__1098,
    _extra4: LAYOUT__1099,
    _extra5: LAYOUT__1100,
    _extra6: LAYOUT__1101,
    _extra7: LAYOUT__1102,
    _extra8: LAYOUT__1103,
    _extra9: LAYOUT__1104,
    _extra10: LAYOUT__1105,
    _extra11: LAYOUT__1106,
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
pub const LAYOUT__1194: &BigInt0StateArm4Layout = &BigInt0StateArm4Layout {
    _super: LAYOUT__1091,
    _extra0: LAYOUT__1095,
    _extra1: LAYOUT__1096,
    _extra2: LAYOUT__1097,
    _extra3: LAYOUT__1098,
    _extra4: LAYOUT__1099,
    _extra5: LAYOUT__1100,
    _extra6: LAYOUT__1101,
    _extra7: LAYOUT__1102,
    _extra8: LAYOUT__1103,
    _extra9: LAYOUT__1104,
    _extra10: LAYOUT__1105,
    _extra11: LAYOUT__1106,
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
pub const LAYOUT__1195: &BigInt0StateArm5Layout = &BigInt0StateArm5Layout {
    _super: LAYOUT__1091,
    _extra0: LAYOUT__1095,
    _extra1: LAYOUT__1096,
    _extra2: LAYOUT__1097,
    _extra3: LAYOUT__1098,
    _extra4: LAYOUT__1099,
    _extra5: LAYOUT__1100,
    _extra6: LAYOUT__1101,
    _extra7: LAYOUT__1102,
    _extra8: LAYOUT__1103,
    _extra9: LAYOUT__1104,
    _extra10: LAYOUT__1105,
    _extra11: LAYOUT__1106,
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
pub const LAYOUT__1196: &BigInt0StateArm6Layout = &BigInt0StateArm6Layout {
    _super: LAYOUT__1091,
    _extra0: LAYOUT__1095,
    _extra1: LAYOUT__1096,
    _extra2: LAYOUT__1097,
    _extra3: LAYOUT__1098,
    _extra4: LAYOUT__1099,
    _extra5: LAYOUT__1100,
    _extra6: LAYOUT__1101,
    _extra7: LAYOUT__1102,
    _extra8: LAYOUT__1103,
    _extra9: LAYOUT__1104,
    _extra10: LAYOUT__1105,
    _extra11: LAYOUT__1106,
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
pub const LAYOUT__1197: &BigInt0StateArm7Layout = &BigInt0StateArm7Layout {
    _super: LAYOUT__1091,
    _extra0: LAYOUT__1095,
    _extra1: LAYOUT__1096,
    _extra2: LAYOUT__1097,
    _extra3: LAYOUT__1098,
    _extra4: LAYOUT__1099,
    _extra5: LAYOUT__1100,
    _extra6: LAYOUT__1101,
    _extra7: LAYOUT__1102,
    _extra8: LAYOUT__1103,
    _extra9: LAYOUT__1104,
    _extra10: LAYOUT__1105,
    _extra11: LAYOUT__1106,
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
pub const LAYOUT__1110: &BigInt0StateLayout = &BigInt0StateLayout {
    _super: LAYOUT__1091,
    arm0: LAYOUT__1111,
    arm1: LAYOUT__1118,
    arm2: LAYOUT__1192,
    arm3: LAYOUT__1193,
    arm4: LAYOUT__1194,
    arm5: LAYOUT__1195,
    arm6: LAYOUT__1196,
    arm7: LAYOUT__1197,
};
pub const LAYOUT__1089: &BigInt0Layout = &BigInt0Layout {
    _0: LAYOUT__1090,
    state: LAYOUT__1091,
    _arguments_big_int0_state: LAYOUT__1093,
    state_redef: LAYOUT__1110,
};
pub const LAYOUT__13: &TopInstResultLayout = &TopInstResultLayout {
    _selector: LAYOUT__12,
    arm0: LAYOUT__14,
    arm1: LAYOUT__103,
    arm2: LAYOUT__121,
    arm3: LAYOUT__134,
    arm4: LAYOUT__224,
    arm5: LAYOUT__342,
    arm6: LAYOUT__400,
    arm7: LAYOUT__458,
    arm8: LAYOUT__643,
    arm9: LAYOUT__708,
    arm10: LAYOUT__976,
    arm11: LAYOUT__1009,
    arm12: LAYOUT__1089,
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
pub const LAYOUT__1199: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1198: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1199,
};
pub const LAYOUT__1201: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1200: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1201,
};
pub const LAYOUT__1203: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1202: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1203,
};
pub const LAYOUT__1205: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1204: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1205,
};
pub const LAYOUT__1207: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1206: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1207,
};
pub const LAYOUT__1208: &_accumLayout = &_accumLayout {
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
    input: LAYOUT__1198,
    is_terminate: &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    output: LAYOUT__1200,
    povw_nonce: LAYOUT__1202,
    rng: &NondetExtRegLayout {
        _super: &Reg { offset: 49 },
    },
    shutdown_cycle: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    state_in: LAYOUT__1204,
    state_out: LAYOUT__1206,
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
    randomness: LAYOUT__1208,
};
