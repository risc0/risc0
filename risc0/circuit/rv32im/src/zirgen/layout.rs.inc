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
        _super: &Reg { offset: 104 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 103 },
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
        _super: &Reg { offset: 103 },
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
pub const LAYOUT__44: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__45,
    new_txn: LAYOUT__46,
};
pub const LAYOUT__48: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
};
pub const LAYOUT__47: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__48 };
pub const LAYOUT__43: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__44,
    _0: LAYOUT__47,
};
pub const LAYOUT__42: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__43,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
};
pub const LAYOUT__52: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 117 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
};
pub const LAYOUT__53: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
};
pub const LAYOUT__51: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__52,
    new_txn: LAYOUT__53,
};
pub const LAYOUT__55: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
};
pub const LAYOUT__54: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__55 };
pub const LAYOUT__50: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__51,
    _0: LAYOUT__54,
};
pub const LAYOUT__49: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__50,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
};
pub const LAYOUT__30: &MiscInputLayout = &MiscInputLayout {
    decoded: LAYOUT__31,
    rs1: LAYOUT__42,
    rs2: LAYOUT__49,
};
pub const LAYOUT__57: &ArgU16Layout5LayoutArray = &[
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
pub const LAYOUT__56: &_Arguments_Misc0MiscOutputLayout = &_Arguments_Misc0MiscOutputLayout {
    arg_u16: LAYOUT__57,
};
pub const LAYOUT__59: &Misc0MiscOutputArm0Layout = &Misc0MiscOutputArm0Layout {
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
pub const LAYOUT__60: &Misc0MiscOutputArm1Layout = &Misc0MiscOutputArm1Layout {
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
pub const LAYOUT__67: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__66: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__67 };
pub const LAYOUT__69: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__68: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__69 };
pub const LAYOUT__65: &BitwiseAndU16Layout = &BitwiseAndU16Layout {
    bits_x: LAYOUT__66,
    bits_y: LAYOUT__68,
};
pub const LAYOUT__72: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__71: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__72 };
pub const LAYOUT__74: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__73: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__74 };
pub const LAYOUT__70: &BitwiseAndU16Layout = &BitwiseAndU16Layout {
    bits_x: LAYOUT__71,
    bits_y: LAYOUT__73,
};
pub const LAYOUT__64: &BitwiseAndLayout = &BitwiseAndLayout {
    _0: LAYOUT__65,
    _1: LAYOUT__70,
};
pub const LAYOUT__63: &BitwiseXorLayout = &BitwiseXorLayout { and_xy: LAYOUT__64 };
pub const LAYOUT__62: &OpXORLayout = &OpXORLayout { _0: LAYOUT__63 };
pub const LAYOUT__61: &Misc0MiscOutputArm2Layout = &Misc0MiscOutputArm2Layout {
    _super: LAYOUT__62,
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
pub const LAYOUT__77: &BitwiseOrLayout = &BitwiseOrLayout { and_xy: LAYOUT__64 };
pub const LAYOUT__76: &OpORLayout = &OpORLayout { _0: LAYOUT__77 };
pub const LAYOUT__75: &Misc0MiscOutputArm3Layout = &Misc0MiscOutputArm3Layout {
    _super: LAYOUT__76,
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
pub const LAYOUT__79: &OpANDLayout = &OpANDLayout { _0: LAYOUT__64 };
pub const LAYOUT__78: &Misc0MiscOutputArm4Layout = &Misc0MiscOutputArm4Layout {
    _super: LAYOUT__79,
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
pub const LAYOUT__83: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
};
pub const LAYOUT__84: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__82: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__83,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    high16: LAYOUT__84,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
};
pub const LAYOUT__86: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__85: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    rest_times_two: LAYOUT__86,
};
pub const LAYOUT__88: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__87: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    rest_times_two: LAYOUT__88,
};
pub const LAYOUT__90: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__89: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    rest_times_two: LAYOUT__90,
};
pub const LAYOUT__81: &CmpLessThanLayout = &CmpLessThanLayout {
    diff: LAYOUT__82,
    s1: LAYOUT__85,
    s2: LAYOUT__87,
    s3: LAYOUT__89,
    overflow: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    is_less_than: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
};
pub const LAYOUT__80: &OpSLTLayout = &OpSLTLayout { cmp: LAYOUT__81 };
pub const LAYOUT__93: &CmpLessThanUnsignedLayout = &CmpLessThanUnsignedLayout { diff: LAYOUT__82 };
pub const LAYOUT__92: &OpSLTULayout = &OpSLTULayout { cmp: LAYOUT__93 };
pub const LAYOUT__91: &Misc0MiscOutputArm6Layout = &Misc0MiscOutputArm6Layout {
    _super: LAYOUT__92,
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
pub const LAYOUT__94: &Misc0MiscOutputArm7Layout = &Misc0MiscOutputArm7Layout {
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
pub const LAYOUT__58: &Misc0MiscOutputLayout = &Misc0MiscOutputLayout {
    arm0: LAYOUT__59,
    arm1: LAYOUT__60,
    arm2: LAYOUT__61,
    arm3: LAYOUT__75,
    arm4: LAYOUT__78,
    arm5: LAYOUT__80,
    arm6: LAYOUT__91,
    arm7: LAYOUT__94,
};
pub const LAYOUT__14: &Misc0Layout = &Misc0Layout {
    _super: LAYOUT__15,
    _0: LAYOUT__29,
    input: LAYOUT__30,
    _arguments_misc0_misc_output: LAYOUT__56,
    misc_output: LAYOUT__58,
};
pub const LAYOUT__96: &_Arguments_Misc1MiscOutputLayout = &_Arguments_Misc1MiscOutputLayout {
    arg_u16: LAYOUT__57,
};
pub const LAYOUT__99: &OpXORILayout = &OpXORILayout { _0: LAYOUT__63 };
pub const LAYOUT__98: &Misc1MiscOutputArm0Layout = &Misc1MiscOutputArm0Layout {
    _super: LAYOUT__99,
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
pub const LAYOUT__101: &OpORILayout = &OpORILayout { _0: LAYOUT__77 };
pub const LAYOUT__100: &Misc1MiscOutputArm1Layout = &Misc1MiscOutputArm1Layout {
    _super: LAYOUT__101,
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
pub const LAYOUT__103: &OpANDILayout = &OpANDILayout { _0: LAYOUT__64 };
pub const LAYOUT__102: &Misc1MiscOutputArm2Layout = &Misc1MiscOutputArm2Layout {
    _super: LAYOUT__103,
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
pub const LAYOUT__104: &OpSLTILayout = &OpSLTILayout { cmp: LAYOUT__81 };
pub const LAYOUT__106: &OpSLTIULayout = &OpSLTIULayout { cmp: LAYOUT__93 };
pub const LAYOUT__105: &Misc1MiscOutputArm4Layout = &Misc1MiscOutputArm4Layout {
    _super: LAYOUT__106,
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
pub const LAYOUT__109: &CmpEqualLayout = &CmpEqualLayout {
    low_same: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    high_same: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    is_equal: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
};
pub const LAYOUT__108: &OpBEQLayout = &OpBEQLayout { cmp: LAYOUT__109 };
pub const LAYOUT__107: &Misc1MiscOutputArm5Layout = &Misc1MiscOutputArm5Layout {
    _super: LAYOUT__108,
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
pub const LAYOUT__111: &OpBNELayout = &OpBNELayout { cmp: LAYOUT__109 };
pub const LAYOUT__110: &Misc1MiscOutputArm6Layout = &Misc1MiscOutputArm6Layout {
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
pub const LAYOUT__112: &OpBLTLayout = &OpBLTLayout { cmp: LAYOUT__81 };
pub const LAYOUT__97: &Misc1MiscOutputLayout = &Misc1MiscOutputLayout {
    arm0: LAYOUT__98,
    arm1: LAYOUT__100,
    arm2: LAYOUT__102,
    arm3: LAYOUT__104,
    arm4: LAYOUT__105,
    arm5: LAYOUT__107,
    arm6: LAYOUT__110,
    arm7: LAYOUT__112,
};
pub const LAYOUT__95: &Misc1Layout = &Misc1Layout {
    _super: LAYOUT__15,
    _0: LAYOUT__29,
    input: LAYOUT__30,
    _arguments_misc1_misc_output: LAYOUT__96,
    misc_output: LAYOUT__97,
};
pub const LAYOUT__114: &_Arguments_Misc2MiscOutputLayout = &_Arguments_Misc2MiscOutputLayout {
    arg_u16: LAYOUT__57,
};
pub const LAYOUT__116: &OpBGELayout = &OpBGELayout { cmp: LAYOUT__81 };
pub const LAYOUT__118: &OpBLTULayout = &OpBLTULayout { cmp: LAYOUT__93 };
pub const LAYOUT__117: &Misc2MiscOutputArm1Layout = &Misc2MiscOutputArm1Layout {
    _super: LAYOUT__118,
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
pub const LAYOUT__120: &OpBGEULayout = &OpBGEULayout { cmp: LAYOUT__93 };
pub const LAYOUT__119: &Misc2MiscOutputArm2Layout = &Misc2MiscOutputArm2Layout {
    _super: LAYOUT__120,
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
pub const LAYOUT__121: &Misc2MiscOutputArm3Layout = &Misc2MiscOutputArm3Layout {
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
pub const LAYOUT__122: &Misc2MiscOutputArm4Layout = &Misc2MiscOutputArm4Layout {
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
pub const LAYOUT__123: &Misc2MiscOutputArm5Layout = &Misc2MiscOutputArm5Layout {
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
pub const LAYOUT__124: &Misc2MiscOutputArm6Layout = &Misc2MiscOutputArm6Layout {
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
pub const LAYOUT__125: &Misc2MiscOutputArm7Layout = &Misc2MiscOutputArm7Layout {
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
pub const LAYOUT__115: &Misc2MiscOutputLayout = &Misc2MiscOutputLayout {
    arm0: LAYOUT__116,
    arm1: LAYOUT__117,
    arm2: LAYOUT__119,
    arm3: LAYOUT__121,
    arm4: LAYOUT__122,
    arm5: LAYOUT__123,
    arm6: LAYOUT__124,
    arm7: LAYOUT__125,
};
pub const LAYOUT__113: &Misc2Layout = &Misc2Layout {
    _super: LAYOUT__15,
    _0: LAYOUT__29,
    input: LAYOUT__30,
    _arguments_misc2_misc_output: LAYOUT__114,
    misc_output: LAYOUT__115,
};
pub const LAYOUT__127: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__130: &DecoderLayout = &DecoderLayout {
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
pub const LAYOUT__132: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__133: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__131: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    upper_diff: LAYOUT__132,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
    med14: LAYOUT__133,
};
pub const LAYOUT__136: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__137: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__135: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__136,
    new_txn: LAYOUT__137,
};
pub const LAYOUT__139: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
};
pub const LAYOUT__138: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__139 };
pub const LAYOUT__134: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__135,
    _0: LAYOUT__138,
};
pub const LAYOUT__129: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__130,
    pc_addr: LAYOUT__131,
    load_inst: LAYOUT__134,
};
pub const LAYOUT__143: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 105 },
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
pub const LAYOUT__144: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 105 },
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
pub const LAYOUT__142: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__143,
    new_txn: LAYOUT__144,
};
pub const LAYOUT__146: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
};
pub const LAYOUT__145: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__146 };
pub const LAYOUT__141: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__142,
    _0: LAYOUT__145,
};
pub const LAYOUT__140: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__141,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
};
pub const LAYOUT__150: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 117 },
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
pub const LAYOUT__151: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 117 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 124 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 125 },
    },
};
pub const LAYOUT__149: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__150,
    new_txn: LAYOUT__151,
};
pub const LAYOUT__153: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
};
pub const LAYOUT__152: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__153 };
pub const LAYOUT__148: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__149,
    _0: LAYOUT__152,
};
pub const LAYOUT__147: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__148,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
};
pub const LAYOUT__128: &MulInputLayout = &MulInputLayout {
    decoded: LAYOUT__129,
    rs1: LAYOUT__140,
    rs2: LAYOUT__147,
};
pub const LAYOUT__155: &ArgU16Layout6LayoutArray = &[
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
pub const LAYOUT__156: &ArgU8Layout13LayoutArray = &[
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
pub const LAYOUT__154: &_Arguments_Mul0MulOutputLayout = &_Arguments_Mul0MulOutputLayout {
    arg_u16: LAYOUT__155,
    arg_u8: LAYOUT__156,
};
pub const LAYOUT__161: &NondetRegLayout5LayoutArray = &[
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
pub const LAYOUT__160: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__161,
};
pub const LAYOUT__159: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__160,
    check_u16: LAYOUT__83,
    b3: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
    low: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    high: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
};
pub const LAYOUT__165: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
};
pub const LAYOUT__166: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__167: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
};
pub const LAYOUT__168: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
};
pub const LAYOUT__169: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
};
pub const LAYOUT__164: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__165,
    b1: LAYOUT__166,
    b2: LAYOUT__167,
    b3: LAYOUT__168,
    b3_top7times2: LAYOUT__169,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
};
pub const LAYOUT__171: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
};
pub const LAYOUT__172: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
};
pub const LAYOUT__173: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
};
pub const LAYOUT__174: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
};
pub const LAYOUT__175: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__170: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__171,
    b1: LAYOUT__172,
    b2: LAYOUT__173,
    b3: LAYOUT__174,
    b3_top7times2: LAYOUT__175,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
};
pub const LAYOUT__177: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
};
pub const LAYOUT__176: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__86,
    carry_byte: LAYOUT__177,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__179: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
};
pub const LAYOUT__178: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__88,
    carry_byte: LAYOUT__179,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__181: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__180: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__90,
    carry_byte: LAYOUT__181,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__163: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__164,
    bx: LAYOUT__170,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
    c_rest_times2: LAYOUT__84,
    s0: LAYOUT__176,
    s1: LAYOUT__178,
    s2: LAYOUT__180,
    s3_out: LAYOUT__17,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__162: &DoMulLayout = &DoMulLayout { mul: LAYOUT__163 };
pub const LAYOUT__158: &OpSLLLayout = &OpSLLLayout {
    shift_mul: LAYOUT__159,
    _0: LAYOUT__162,
};
pub const LAYOUT__182: &OpSLLILayout = &OpSLLILayout {
    shift_mul: LAYOUT__159,
    _0: LAYOUT__162,
};
pub const LAYOUT__187: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__165,
    b1: LAYOUT__166,
    b2: LAYOUT__167,
    b3: LAYOUT__168,
    b3_top7times2: LAYOUT__169,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
};
pub const LAYOUT__188: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__171,
    b1: LAYOUT__172,
    b2: LAYOUT__173,
    b3: LAYOUT__174,
    b3_top7times2: LAYOUT__175,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
};
pub const LAYOUT__189: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__84,
    carry_byte: LAYOUT__177,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
};
pub const LAYOUT__190: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__86,
    carry_byte: LAYOUT__179,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
};
pub const LAYOUT__191: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__88,
    carry_byte: LAYOUT__181,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
};
pub const LAYOUT__186: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__187,
    bx: LAYOUT__188,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    c_rest_times2: LAYOUT__83,
    s0: LAYOUT__189,
    s1: LAYOUT__190,
    s2: LAYOUT__191,
    s3_out: LAYOUT__90,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__185: &DoMulLayout = &DoMulLayout { mul: LAYOUT__186 };
pub const LAYOUT__184: &OpMULLayout = &OpMULLayout { _0: LAYOUT__185 };
pub const LAYOUT__183: &Mul0MulOutputArm2Layout = &Mul0MulOutputArm2Layout {
    _super: LAYOUT__184,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__193: &OpMULHLayout = &OpMULHLayout { _0: LAYOUT__185 };
pub const LAYOUT__192: &Mul0MulOutputArm3Layout = &Mul0MulOutputArm3Layout {
    _super: LAYOUT__193,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__195: &OpMULHSULayout = &OpMULHSULayout { _0: LAYOUT__185 };
pub const LAYOUT__194: &Mul0MulOutputArm4Layout = &Mul0MulOutputArm4Layout {
    _super: LAYOUT__195,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__197: &OpMULHULayout = &OpMULHULayout { _0: LAYOUT__185 };
pub const LAYOUT__196: &Mul0MulOutputArm5Layout = &Mul0MulOutputArm5Layout {
    _super: LAYOUT__197,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__198: &Mul0MulOutputArm6Layout = &Mul0MulOutputArm6Layout {
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
pub const LAYOUT__199: &Mul0MulOutputArm7Layout = &Mul0MulOutputArm7Layout {
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
pub const LAYOUT__157: &Mul0MulOutputLayout = &Mul0MulOutputLayout {
    arm0: LAYOUT__158,
    arm1: LAYOUT__182,
    arm2: LAYOUT__183,
    arm3: LAYOUT__192,
    arm4: LAYOUT__194,
    arm5: LAYOUT__196,
    arm6: LAYOUT__198,
    arm7: LAYOUT__199,
};
pub const LAYOUT__203: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 152 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 151 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 153 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
};
pub const LAYOUT__204: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 151 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
};
pub const LAYOUT__202: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__203,
    new_txn: LAYOUT__204,
};
pub const LAYOUT__206: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
};
pub const LAYOUT__205: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__206 };
pub const LAYOUT__201: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__202,
    _0: LAYOUT__205,
};
pub const LAYOUT__200: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 150 },
    },
    _0: LAYOUT__201,
};
pub const LAYOUT__208: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
};
pub const LAYOUT__209: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
};
pub const LAYOUT__207: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__208,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
    high16: LAYOUT__209,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 167 },
    },
};
pub const LAYOUT__126: &Mul0Layout = &Mul0Layout {
    _0: LAYOUT__127,
    input: LAYOUT__128,
    _arguments_mul0_mul_output: LAYOUT__154,
    mul_output: LAYOUT__157,
    _1: LAYOUT__200,
    pc_add: LAYOUT__207,
};
pub const LAYOUT__211: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__214: &DecoderLayout = &DecoderLayout {
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
pub const LAYOUT__216: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
};
pub const LAYOUT__217: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
};
pub const LAYOUT__215: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    upper_diff: LAYOUT__216,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    med14: LAYOUT__217,
};
pub const LAYOUT__220: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__221: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__219: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__220,
    new_txn: LAYOUT__221,
};
pub const LAYOUT__223: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__222: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__223 };
pub const LAYOUT__218: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__219,
    _0: LAYOUT__222,
};
pub const LAYOUT__213: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__214,
    pc_addr: LAYOUT__215,
    load_inst: LAYOUT__218,
};
pub const LAYOUT__227: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 125 },
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
pub const LAYOUT__228: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 125 },
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
pub const LAYOUT__226: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__227,
    new_txn: LAYOUT__228,
};
pub const LAYOUT__230: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
};
pub const LAYOUT__229: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__230 };
pub const LAYOUT__225: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__226,
    _0: LAYOUT__229,
};
pub const LAYOUT__224: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__225,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
};
pub const LAYOUT__234: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 140 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 141 },
    },
};
pub const LAYOUT__235: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 137 },
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
pub const LAYOUT__233: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__234,
    new_txn: LAYOUT__235,
};
pub const LAYOUT__237: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__236: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__237 };
pub const LAYOUT__232: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__233,
    _0: LAYOUT__236,
};
pub const LAYOUT__231: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__232,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 148 },
    },
};
pub const LAYOUT__212: &DivInputLayout = &DivInputLayout {
    decoded: LAYOUT__213,
    rs1: LAYOUT__224,
    rs2: LAYOUT__231,
};
pub const LAYOUT__239: &ArgU16Layout16LayoutArray = &[
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
pub const LAYOUT__240: &ArgU8Layout13LayoutArray = &[
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
pub const LAYOUT__238: &_Arguments_Div0MulOutputLayout = &_Arguments_Div0MulOutputLayout {
    arg_u16: LAYOUT__239,
    arg_u8: LAYOUT__240,
};
pub const LAYOUT__246: &NondetRegLayout5LayoutArray = &[
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
];
pub const LAYOUT__245: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__246,
};
pub const LAYOUT__244: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__245,
    check_u16: LAYOUT__83,
    b3: &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
    low: &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
    high: &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
};
pub const LAYOUT__250: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__251: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__249: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__177,
    b1: LAYOUT__179,
    b2: LAYOUT__181,
    b3: LAYOUT__250,
    b3_top7times2: LAYOUT__251,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
};
pub const LAYOUT__253: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
};
pub const LAYOUT__254: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__255: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
};
pub const LAYOUT__256: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
};
pub const LAYOUT__257: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
};
pub const LAYOUT__252: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__253,
    b1: LAYOUT__254,
    b2: LAYOUT__255,
    b3: LAYOUT__256,
    b3_top7times2: LAYOUT__257,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
};
pub const LAYOUT__259: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
};
pub const LAYOUT__258: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__90,
    carry_byte: LAYOUT__259,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
};
pub const LAYOUT__261: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
};
pub const LAYOUT__260: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__17,
    carry_byte: LAYOUT__261,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
};
pub const LAYOUT__263: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
};
pub const LAYOUT__264: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
};
pub const LAYOUT__262: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__263,
    carry_byte: LAYOUT__264,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
};
pub const LAYOUT__265: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__248: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__249,
    bx: LAYOUT__252,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 161 },
    },
    c_rest_times2: LAYOUT__88,
    s0: LAYOUT__258,
    s1: LAYOUT__260,
    s2: LAYOUT__262,
    s3_out: LAYOUT__265,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
};
pub const LAYOUT__267: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
};
pub const LAYOUT__268: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
};
pub const LAYOUT__266: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__267,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 174 },
    },
    high16: LAYOUT__268,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
};
pub const LAYOUT__270: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
};
pub const LAYOUT__271: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
};
pub const LAYOUT__269: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__270,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
    high16: LAYOUT__271,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 177 },
    },
};
pub const LAYOUT__273: &ArgU16Layout2LayoutArray = &[
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
];
pub const LAYOUT__272: &_Arguments_DoDiv__1Layout = &_Arguments_DoDiv__1Layout {
    arg_u16: LAYOUT__273,
};
pub const LAYOUT__275: &DoDiv__1Arm0Layout = &DoDiv__1Arm0Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
};
pub const LAYOUT__279: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
};
pub const LAYOUT__280: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
};
pub const LAYOUT__278: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__279,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 178 },
    },
    high16: LAYOUT__280,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 179 },
    },
};
pub const LAYOUT__277: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__278 };
pub const LAYOUT__276: &DoDiv__1Arm1_SuperLayout = &DoDiv__1Arm1_SuperLayout { lt: LAYOUT__277 };
pub const LAYOUT__274: &DoDiv__1Layout = &DoDiv__1Layout {
    arm0: LAYOUT__275,
    arm1: LAYOUT__276,
};
pub const LAYOUT__247: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
    rem_low: LAYOUT__84,
    rem_high: LAYOUT__86,
    mul: LAYOUT__248,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 170 },
    },
    is_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    top_num: &NondetRegLayout {
        _super: &Reg { offset: 173 },
    },
    _0: LAYOUT__20,
    denom_abs: LAYOUT__266,
    rem_normal: LAYOUT__269,
    _arguments_do_div__1: LAYOUT__272,
    _3: LAYOUT__274,
};
pub const LAYOUT__243: &OpSRLLayout = &OpSRLLayout {
    shift_mul: LAYOUT__244,
    _0: LAYOUT__247,
};
pub const LAYOUT__242: &Div0MulOutputArm0Layout = &Div0MulOutputArm0Layout {
    _super: LAYOUT__243,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__282: &TopBitLayout = &TopBitLayout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
    rest: LAYOUT__84,
};
pub const LAYOUT__285: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__177,
    b1: LAYOUT__179,
    b2: LAYOUT__181,
    b3: LAYOUT__250,
    b3_top7times2: LAYOUT__251,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
};
pub const LAYOUT__286: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__253,
    b1: LAYOUT__254,
    b2: LAYOUT__255,
    b3: LAYOUT__256,
    b3_top7times2: LAYOUT__257,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 161 },
    },
};
pub const LAYOUT__287: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__17,
    carry_byte: LAYOUT__259,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
};
pub const LAYOUT__288: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__263,
    carry_byte: LAYOUT__261,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
};
pub const LAYOUT__289: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__265,
    carry_byte: LAYOUT__264,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
};
pub const LAYOUT__284: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__285,
    bx: LAYOUT__286,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 162 },
    },
    c_rest_times2: LAYOUT__90,
    s0: LAYOUT__287,
    s1: LAYOUT__288,
    s2: LAYOUT__289,
    s3_out: LAYOUT__20,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
};
pub const LAYOUT__290: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__268,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
    high16: LAYOUT__270,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
};
pub const LAYOUT__291: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__271,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 177 },
    },
    high16: LAYOUT__279,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 178 },
    },
};
pub const LAYOUT__293: &ArgU16Layout2LayoutArray = &[
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
pub const LAYOUT__292: &_Arguments_DoDiv__1Layout = &_Arguments_DoDiv__1Layout {
    arg_u16: LAYOUT__293,
};
pub const LAYOUT__295: &DoDiv__1Arm0Layout = &DoDiv__1Arm0Layout {
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
pub const LAYOUT__299: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__298: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__280,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 179 },
    },
    high16: LAYOUT__299,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
};
pub const LAYOUT__297: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__298 };
pub const LAYOUT__296: &DoDiv__1Arm1_SuperLayout = &DoDiv__1Arm1_SuperLayout { lt: LAYOUT__297 };
pub const LAYOUT__294: &DoDiv__1Layout = &DoDiv__1Layout {
    arm0: LAYOUT__295,
    arm1: LAYOUT__296,
};
pub const LAYOUT__283: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
    rem_low: LAYOUT__86,
    rem_high: LAYOUT__88,
    mul: LAYOUT__284,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
    is_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    top_num: &NondetRegLayout {
        _super: &Reg { offset: 174 },
    },
    _0: LAYOUT__267,
    denom_abs: LAYOUT__290,
    rem_normal: LAYOUT__291,
    _arguments_do_div__1: LAYOUT__292,
    _3: LAYOUT__294,
};
pub const LAYOUT__281: &OpSRALayout = &OpSRALayout {
    shift_mul: LAYOUT__244,
    flip: LAYOUT__282,
    _0: LAYOUT__283,
};
pub const LAYOUT__301: &OpSRLILayout = &OpSRLILayout {
    shift_mul: LAYOUT__244,
    _0: LAYOUT__247,
};
pub const LAYOUT__300: &Div0MulOutputArm2Layout = &Div0MulOutputArm2Layout {
    _super: LAYOUT__301,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__302: &OpSRAILayout = &OpSRAILayout {
    shift_mul: LAYOUT__244,
    flip: LAYOUT__282,
    _0: LAYOUT__283,
};
pub const LAYOUT__307: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__177,
    b1: LAYOUT__179,
    b2: LAYOUT__181,
    b3: LAYOUT__250,
    b3_top7times2: LAYOUT__251,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 151 },
    },
};
pub const LAYOUT__308: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__253,
    b1: LAYOUT__254,
    b2: LAYOUT__255,
    b3: LAYOUT__256,
    b3_top7times2: LAYOUT__257,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 152 },
    },
};
pub const LAYOUT__309: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__88,
    carry_byte: LAYOUT__259,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
};
pub const LAYOUT__310: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__90,
    carry_byte: LAYOUT__261,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
};
pub const LAYOUT__311: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__17,
    carry_byte: LAYOUT__264,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
};
pub const LAYOUT__306: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__307,
    bx: LAYOUT__308,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 153 },
    },
    c_rest_times2: LAYOUT__86,
    s0: LAYOUT__309,
    s1: LAYOUT__310,
    s2: LAYOUT__311,
    s3_out: LAYOUT__263,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
};
pub const LAYOUT__312: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__20,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
    high16: LAYOUT__267,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 167 },
    },
};
pub const LAYOUT__313: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__268,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 168 },
    },
    high16: LAYOUT__270,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
};
pub const LAYOUT__315: &ArgU16Layout2LayoutArray = &[
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
];
pub const LAYOUT__314: &_Arguments_DoDiv__1Layout = &_Arguments_DoDiv__1Layout {
    arg_u16: LAYOUT__315,
};
pub const LAYOUT__317: &DoDiv__1Arm0Layout = &DoDiv__1Arm0Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
};
pub const LAYOUT__320: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__271,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 170 },
    },
    high16: LAYOUT__279,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
};
pub const LAYOUT__319: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__320 };
pub const LAYOUT__318: &DoDiv__1Arm1_SuperLayout = &DoDiv__1Arm1_SuperLayout { lt: LAYOUT__319 };
pub const LAYOUT__316: &DoDiv__1Layout = &DoDiv__1Layout {
    arm0: LAYOUT__317,
    arm1: LAYOUT__318,
};
pub const LAYOUT__305: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 149 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 150 },
    },
    rem_low: LAYOUT__83,
    rem_high: LAYOUT__84,
    mul: LAYOUT__306,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 162 },
    },
    is_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    top_num: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
    _0: LAYOUT__265,
    denom_abs: LAYOUT__312,
    rem_normal: LAYOUT__313,
    _arguments_do_div__1: LAYOUT__314,
    _3: LAYOUT__316,
};
pub const LAYOUT__304: &OpDIVLayout = &OpDIVLayout { _0: LAYOUT__305 };
pub const LAYOUT__303: &Div0MulOutputArm4Layout = &Div0MulOutputArm4Layout {
    _super: LAYOUT__304,
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
pub const LAYOUT__322: &OpDIVULayout = &OpDIVULayout { _0: LAYOUT__305 };
pub const LAYOUT__321: &Div0MulOutputArm5Layout = &Div0MulOutputArm5Layout {
    _super: LAYOUT__322,
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
pub const LAYOUT__324: &OpREMLayout = &OpREMLayout { _0: LAYOUT__305 };
pub const LAYOUT__323: &Div0MulOutputArm6Layout = &Div0MulOutputArm6Layout {
    _super: LAYOUT__324,
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
pub const LAYOUT__326: &OpREMULayout = &OpREMULayout { _0: LAYOUT__305 };
pub const LAYOUT__325: &Div0MulOutputArm7Layout = &Div0MulOutputArm7Layout {
    _super: LAYOUT__326,
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
pub const LAYOUT__241: &Div0MulOutputLayout = &Div0MulOutputLayout {
    arm0: LAYOUT__242,
    arm1: LAYOUT__281,
    arm2: LAYOUT__300,
    arm3: LAYOUT__302,
    arm4: LAYOUT__303,
    arm5: LAYOUT__321,
    arm6: LAYOUT__323,
    arm7: LAYOUT__325,
};
pub const LAYOUT__330: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 185 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 186 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 187 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 188 },
    },
};
pub const LAYOUT__331: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 189 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 190 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 191 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 192 },
    },
};
pub const LAYOUT__329: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__330,
    new_txn: LAYOUT__331,
};
pub const LAYOUT__333: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 193 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 194 },
        },
    },
};
pub const LAYOUT__332: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__333 };
pub const LAYOUT__328: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__329,
    _0: LAYOUT__332,
};
pub const LAYOUT__327: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    _0: LAYOUT__328,
};
pub const LAYOUT__335: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 195 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 196 },
        },
    },
};
pub const LAYOUT__336: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 198 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 199 },
        },
    },
};
pub const LAYOUT__334: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__335,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    high16: LAYOUT__336,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 200 },
    },
};
pub const LAYOUT__210: &Div0Layout = &Div0Layout {
    _0: LAYOUT__211,
    input: LAYOUT__212,
    _arguments_div0_mul_output: LAYOUT__238,
    mul_output: LAYOUT__241,
    _1: LAYOUT__327,
    pc_add: LAYOUT__334,
};
pub const LAYOUT__338: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__341: &DecoderLayout = &DecoderLayout {
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
pub const LAYOUT__343: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__344: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
    },
};
pub const LAYOUT__342: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    upper_diff: LAYOUT__343,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
    },
    med14: LAYOUT__344,
};
pub const LAYOUT__347: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__348: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__346: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__347,
    new_txn: LAYOUT__348,
};
pub const LAYOUT__350: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__349: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__350 };
pub const LAYOUT__345: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__346,
    _0: LAYOUT__349,
};
pub const LAYOUT__340: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__341,
    pc_addr: LAYOUT__342,
    load_inst: LAYOUT__345,
};
pub const LAYOUT__354: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__355: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__353: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__354,
    new_txn: LAYOUT__355,
};
pub const LAYOUT__357: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__356: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__357 };
pub const LAYOUT__352: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__353,
    _0: LAYOUT__356,
};
pub const LAYOUT__351: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__352,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
};
pub const LAYOUT__359: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__358: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__359,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    high16: LAYOUT__35,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
};
pub const LAYOUT__361: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
};
pub const LAYOUT__362: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
};
pub const LAYOUT__360: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    upper_diff: LAYOUT__361,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
    med14: LAYOUT__362,
};
pub const LAYOUT__365: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__366: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__364: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__365,
    new_txn: LAYOUT__366,
};
pub const LAYOUT__368: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__367: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__368 };
pub const LAYOUT__363: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__364,
    _0: LAYOUT__367,
};
pub const LAYOUT__339: &MemLoadInputLayout = &MemLoadInputLayout {
    decoded: LAYOUT__340,
    rs1: LAYOUT__351,
    addr_u32: LAYOUT__358,
    addr: LAYOUT__360,
    data_0: LAYOUT__363,
};
pub const LAYOUT__370: &ArgU8Layout3LayoutArray = &[
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
pub const LAYOUT__369: &_Arguments_Mem0OutputLayout = &_Arguments_Mem0OutputLayout {
    arg_u8: LAYOUT__370,
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    }],
};
pub const LAYOUT__375: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
};
pub const LAYOUT__376: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__374: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__375,
    byte1: LAYOUT__376,
};
pub const LAYOUT__377: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__373: &OpLBLayout = &OpLBLayout {
    bytes: LAYOUT__374,
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low7x2: LAYOUT__377,
};
pub const LAYOUT__372: &Mem0OutputArm0Layout = &Mem0OutputArm0Layout {
    _super: LAYOUT__373,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__379: &OpLHLayout = &OpLHLayout {
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low15x2: LAYOUT__88,
};
pub const LAYOUT__378: &Mem0OutputArm1Layout = &Mem0OutputArm1Layout {
    _super: LAYOUT__379,
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
pub const LAYOUT__380: &Mem0OutputArm2Layout = &Mem0OutputArm2Layout {
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
pub const LAYOUT__382: &OpLBULayout = &OpLBULayout { bytes: LAYOUT__374 };
pub const LAYOUT__381: &Mem0OutputArm3Layout = &Mem0OutputArm3Layout {
    _super: LAYOUT__382,
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
pub const LAYOUT__383: &Mem0OutputArm4Layout = &Mem0OutputArm4Layout {
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
pub const LAYOUT__384: &Mem0OutputArm5Layout = &Mem0OutputArm5Layout {
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
pub const LAYOUT__385: &Mem0OutputArm6Layout = &Mem0OutputArm6Layout {
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
pub const LAYOUT__386: &Mem0OutputArm7Layout = &Mem0OutputArm7Layout {
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
pub const LAYOUT__371: &Mem0OutputLayout = &Mem0OutputLayout {
    arm0: LAYOUT__372,
    arm1: LAYOUT__378,
    arm2: LAYOUT__380,
    arm3: LAYOUT__381,
    arm4: LAYOUT__383,
    arm5: LAYOUT__384,
    arm6: LAYOUT__385,
    arm7: LAYOUT__386,
};
pub const LAYOUT__390: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__391: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__389: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__390,
    new_txn: LAYOUT__391,
};
pub const LAYOUT__393: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
};
pub const LAYOUT__392: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__393 };
pub const LAYOUT__388: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__389,
    _0: LAYOUT__392,
};
pub const LAYOUT__387: &WriteRdLayout = &WriteRdLayout {
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
    _0: LAYOUT__388,
};
pub const LAYOUT__395: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
};
pub const LAYOUT__396: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
};
pub const LAYOUT__394: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__395,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    high16: LAYOUT__396,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
};
pub const LAYOUT__337: &Mem0Layout = &Mem0Layout {
    _0: LAYOUT__338,
    input: LAYOUT__339,
    _arguments_mem0_output: LAYOUT__369,
    output: LAYOUT__371,
    _1: LAYOUT__387,
    pc_add: LAYOUT__394,
};
pub const LAYOUT__402: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 87 },
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
pub const LAYOUT__403: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 87 },
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
pub const LAYOUT__401: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__402,
    new_txn: LAYOUT__403,
};
pub const LAYOUT__405: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
    },
};
pub const LAYOUT__404: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__405 };
pub const LAYOUT__400: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__401,
    _0: LAYOUT__404,
};
pub const LAYOUT__399: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__400,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
};
pub const LAYOUT__407: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__406: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__362,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    high16: LAYOUT__407,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
};
pub const LAYOUT__409: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
};
pub const LAYOUT__410: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__408: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    upper_diff: LAYOUT__409,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    med14: LAYOUT__410,
};
pub const LAYOUT__413: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 113 },
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
pub const LAYOUT__414: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 113 },
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
pub const LAYOUT__412: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__413,
    new_txn: LAYOUT__414,
};
pub const LAYOUT__416: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
};
pub const LAYOUT__415: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__416 };
pub const LAYOUT__411: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__412,
    _0: LAYOUT__415,
};
pub const LAYOUT__398: &MemStoreInputLayout = &MemStoreInputLayout {
    decoded: LAYOUT__340,
    rs1: LAYOUT__351,
    rs2: LAYOUT__399,
    addr_u32: LAYOUT__406,
    addr: LAYOUT__408,
    data_0: LAYOUT__411,
};
pub const LAYOUT__418: &ArgU8Layout4LayoutArray = &[
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
pub const LAYOUT__417: &_Arguments_Mem1OutputLayout = &_Arguments_Mem1OutputLayout {
    arg_u8: LAYOUT__418,
};
pub const LAYOUT__422: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__421: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__377,
    byte1: LAYOUT__422,
};
pub const LAYOUT__420: &OpSBLayout = &OpSBLayout {
    orig_bytes: LAYOUT__374,
    new_bytes: LAYOUT__421,
};
pub const LAYOUT__423: &Mem1OutputArm1Layout = &Mem1OutputArm1Layout {
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
pub const LAYOUT__424: &Mem1OutputArm2Layout = &Mem1OutputArm2Layout {
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
pub const LAYOUT__425: &Mem1OutputArm3Layout = &Mem1OutputArm3Layout {
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
pub const LAYOUT__426: &Mem1OutputArm4Layout = &Mem1OutputArm4Layout {
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
pub const LAYOUT__427: &Mem1OutputArm5Layout = &Mem1OutputArm5Layout {
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
pub const LAYOUT__428: &Mem1OutputArm6Layout = &Mem1OutputArm6Layout {
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
pub const LAYOUT__429: &Mem1OutputArm7Layout = &Mem1OutputArm7Layout {
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
pub const LAYOUT__419: &Mem1OutputLayout = &Mem1OutputLayout {
    arm0: LAYOUT__420,
    arm1: LAYOUT__423,
    arm2: LAYOUT__424,
    arm3: LAYOUT__425,
    arm4: LAYOUT__426,
    arm5: LAYOUT__427,
    arm6: LAYOUT__428,
    arm7: LAYOUT__429,
};
pub const LAYOUT__433: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 125 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 124 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
};
pub const LAYOUT__434: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 124 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
};
pub const LAYOUT__432: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__433,
    new_txn: LAYOUT__434,
};
pub const LAYOUT__436: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
};
pub const LAYOUT__435: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__436 };
pub const LAYOUT__431: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__432,
    _0: LAYOUT__435,
};
pub const LAYOUT__430: &MemStoreFinalizeLayout = &MemStoreFinalizeLayout { _0: LAYOUT__431 };
pub const LAYOUT__438: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
};
pub const LAYOUT__439: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__437: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__438,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    high16: LAYOUT__439,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 140 },
    },
};
pub const LAYOUT__397: &Mem1Layout = &Mem1Layout {
    _0: LAYOUT__338,
    input: LAYOUT__398,
    _arguments_mem1_output: LAYOUT__417,
    output: LAYOUT__419,
    _1: LAYOUT__430,
    pc_add: LAYOUT__437,
};
pub const LAYOUT__448: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__449: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__447: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__448,
    new_txn: LAYOUT__449,
};
pub const LAYOUT__446: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__447 };
pub const LAYOUT__445: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__446 };
pub const LAYOUT__453: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__454: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__452: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__453,
    new_txn: LAYOUT__454,
};
pub const LAYOUT__451: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__452 };
pub const LAYOUT__450: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__451 };
pub const LAYOUT__458: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__459: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__457: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__458,
    new_txn: LAYOUT__459,
};
pub const LAYOUT__456: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__457 };
pub const LAYOUT__455: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__456 };
pub const LAYOUT__463: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__464: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__462: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__463,
    new_txn: LAYOUT__464,
};
pub const LAYOUT__461: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__462 };
pub const LAYOUT__460: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__461 };
pub const LAYOUT__468: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__469: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__467: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__468,
    new_txn: LAYOUT__469,
};
pub const LAYOUT__466: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__467 };
pub const LAYOUT__465: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__466 };
pub const LAYOUT__473: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__474: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__472: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__473,
    new_txn: LAYOUT__474,
};
pub const LAYOUT__471: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__472 };
pub const LAYOUT__470: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__471 };
pub const LAYOUT__478: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__479: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__477: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__478,
    new_txn: LAYOUT__479,
};
pub const LAYOUT__476: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__477 };
pub const LAYOUT__475: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__476 };
pub const LAYOUT__483: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__484: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__482: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__483,
    new_txn: LAYOUT__484,
};
pub const LAYOUT__481: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__482 };
pub const LAYOUT__480: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__481 };
pub const LAYOUT__444: &ControlLoadRoot__0_SuperLayout8LayoutArray = &[
    LAYOUT__445,
    LAYOUT__450,
    LAYOUT__455,
    LAYOUT__460,
    LAYOUT__465,
    LAYOUT__470,
    LAYOUT__475,
    LAYOUT__480,
];
pub const LAYOUT__443: &ControlLoadRootLayout = &ControlLoadRootLayout { _1: LAYOUT__444 };
pub const LAYOUT__442: &Control0_SuperArm0Layout = &Control0_SuperArm0Layout {
    _super: LAYOUT__443,
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
pub const LAYOUT__490: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__447,
    _0: LAYOUT__40,
};
pub const LAYOUT__491: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__452,
    _0: LAYOUT__138,
};
pub const LAYOUT__489: &ControlResume_SuperArm0_SuperLayout =
    &ControlResume_SuperArm0_SuperLayout {
        pc: LAYOUT__490,
        mode: LAYOUT__491,
    };
pub const LAYOUT__488: &ControlResume_SuperArm0Layout = &ControlResume_SuperArm0Layout {
    _super: LAYOUT__489,
    _extra0: LAYOUT__458,
    _extra1: LAYOUT__459,
    _extra2: LAYOUT__463,
    _extra3: LAYOUT__464,
    _extra4: LAYOUT__468,
    _extra5: LAYOUT__469,
    _extra6: LAYOUT__473,
    _extra7: LAYOUT__474,
    _extra8: LAYOUT__478,
    _extra9: LAYOUT__479,
    _extra10: LAYOUT__483,
    _extra11: LAYOUT__484,
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
pub const LAYOUT__495: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__447,
    _0: LAYOUT__40,
};
pub const LAYOUT__494: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__495 };
pub const LAYOUT__497: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__452,
    _0: LAYOUT__138,
};
pub const LAYOUT__496: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__497 };
pub const LAYOUT__501: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
};
pub const LAYOUT__500: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__501 };
pub const LAYOUT__499: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__457,
    _0: LAYOUT__500,
};
pub const LAYOUT__498: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__499 };
pub const LAYOUT__505: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
};
pub const LAYOUT__504: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__505 };
pub const LAYOUT__503: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__462,
    _0: LAYOUT__504,
};
pub const LAYOUT__502: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__503 };
pub const LAYOUT__509: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
};
pub const LAYOUT__508: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__509 };
pub const LAYOUT__507: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__467,
    _0: LAYOUT__508,
};
pub const LAYOUT__506: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__507 };
pub const LAYOUT__513: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__512: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__513 };
pub const LAYOUT__511: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__472,
    _0: LAYOUT__512,
};
pub const LAYOUT__510: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__511 };
pub const LAYOUT__517: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
};
pub const LAYOUT__516: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__517 };
pub const LAYOUT__515: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__477,
    _0: LAYOUT__516,
};
pub const LAYOUT__514: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__515 };
pub const LAYOUT__521: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
};
pub const LAYOUT__520: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__521 };
pub const LAYOUT__519: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__482,
    _0: LAYOUT__520,
};
pub const LAYOUT__518: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__519 };
pub const LAYOUT__493: &ControlResume_SuperArm1_Super__0_SuperLayout8LayoutArray = &[
    LAYOUT__494,
    LAYOUT__496,
    LAYOUT__498,
    LAYOUT__502,
    LAYOUT__506,
    LAYOUT__510,
    LAYOUT__514,
    LAYOUT__518,
];
pub const LAYOUT__492: &ControlResume_SuperArm1_SuperLayout =
    &ControlResume_SuperArm1_SuperLayout { _1: LAYOUT__493 };
pub const LAYOUT__487: &ControlResume_SuperLayout = &ControlResume_SuperLayout {
    arm0: LAYOUT__488,
    arm1: LAYOUT__492,
};
pub const LAYOUT__523: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__448,
    LAYOUT__449,
    LAYOUT__453,
    LAYOUT__454,
    LAYOUT__458,
    LAYOUT__459,
    LAYOUT__463,
    LAYOUT__464,
    LAYOUT__468,
    LAYOUT__469,
    LAYOUT__473,
    LAYOUT__474,
    LAYOUT__478,
    LAYOUT__479,
    LAYOUT__483,
    LAYOUT__484,
];
pub const LAYOUT__524: &CycleArgLayout8LayoutArray = &[
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
pub const LAYOUT__522: &_Arguments_ControlResume_SuperLayout =
    &_Arguments_ControlResume_SuperLayout {
        memory_arg: LAYOUT__523,
        cycle_arg: LAYOUT__524,
    };
pub const LAYOUT__486: &ControlResumeLayout = &ControlResumeLayout {
    _super: LAYOUT__487,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _arguments_control_resume__super: LAYOUT__522,
};
pub const LAYOUT__485: &Control0_SuperArm1Layout = &Control0_SuperArm1Layout {
    _super: LAYOUT__486,
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
pub const LAYOUT__528: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
};
pub const LAYOUT__529: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__527: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    upper_diff: LAYOUT__528,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
    med14: LAYOUT__529,
};
pub const LAYOUT__526: &ControlUserECALLLayout = &ControlUserECALLLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    pc_addr: LAYOUT__527,
    load_inst: LAYOUT__490,
    new_pc_addr: LAYOUT__491,
    _0: LAYOUT__499,
};
pub const LAYOUT__525: &Control0_SuperArm2Layout = &Control0_SuperArm2Layout {
    _super: LAYOUT__526,
    _extra0: LAYOUT__463,
    _extra1: LAYOUT__464,
    _extra2: LAYOUT__468,
    _extra3: LAYOUT__469,
    _extra4: LAYOUT__473,
    _extra5: LAYOUT__474,
    _extra6: LAYOUT__478,
    _extra7: LAYOUT__479,
    _extra8: LAYOUT__483,
    _extra9: LAYOUT__484,
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
pub const LAYOUT__533: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
};
pub const LAYOUT__534: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__532: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__533,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 186 },
    },
    high16: LAYOUT__534,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 187 },
    },
};
pub const LAYOUT__531: &ControlMRETLayout = &ControlMRETLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    pc_addr: LAYOUT__527,
    load_inst: LAYOUT__490,
    pc: LAYOUT__491,
    pc_add: LAYOUT__532,
};
pub const LAYOUT__530: &Control0_SuperArm3Layout = &Control0_SuperArm3Layout {
    _super: LAYOUT__531,
    _extra0: LAYOUT__458,
    _extra1: LAYOUT__459,
    _extra2: LAYOUT__463,
    _extra3: LAYOUT__464,
    _extra4: LAYOUT__468,
    _extra5: LAYOUT__469,
    _extra6: LAYOUT__473,
    _extra7: LAYOUT__474,
    _extra8: LAYOUT__478,
    _extra9: LAYOUT__479,
    _extra10: LAYOUT__483,
    _extra11: LAYOUT__484,
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
pub const LAYOUT__540: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__457,
    _0: LAYOUT__500,
};
pub const LAYOUT__541: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__462,
    _0: LAYOUT__504,
};
pub const LAYOUT__542: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__467,
    _0: LAYOUT__508,
};
pub const LAYOUT__543: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__472,
    _0: LAYOUT__512,
};
pub const LAYOUT__544: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__477,
    _0: LAYOUT__516,
};
pub const LAYOUT__545: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__482,
    _0: LAYOUT__520,
};
pub const LAYOUT__539: &MemoryReadLayout8LayoutArray = &[
    LAYOUT__490,
    LAYOUT__491,
    LAYOUT__540,
    LAYOUT__541,
    LAYOUT__542,
    LAYOUT__543,
    LAYOUT__544,
    LAYOUT__545,
];
pub const LAYOUT__538: &ControlSuspend_SuperArm0_SuperLayout =
    &ControlSuspend_SuperArm0_SuperLayout { _1: LAYOUT__539 };
pub const LAYOUT__547: &ControlSuspend_SuperArm1_SuperLayout =
    &ControlSuspend_SuperArm1_SuperLayout {
        state: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        _0: LAYOUT__495,
        _1: LAYOUT__497,
    };
pub const LAYOUT__546: &ControlSuspend_SuperArm1Layout = &ControlSuspend_SuperArm1Layout {
    _super: LAYOUT__547,
    _extra0: LAYOUT__458,
    _extra1: LAYOUT__459,
    _extra2: LAYOUT__463,
    _extra3: LAYOUT__464,
    _extra4: LAYOUT__468,
    _extra5: LAYOUT__469,
    _extra6: LAYOUT__473,
    _extra7: LAYOUT__474,
    _extra8: LAYOUT__478,
    _extra9: LAYOUT__479,
    _extra10: LAYOUT__483,
    _extra11: LAYOUT__484,
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
pub const LAYOUT__537: &ControlSuspend_SuperLayout = &ControlSuspend_SuperLayout {
    arm0: LAYOUT__538,
    arm1: LAYOUT__546,
};
pub const LAYOUT__548: &_Arguments_ControlSuspend_SuperLayout =
    &_Arguments_ControlSuspend_SuperLayout {
        memory_arg: LAYOUT__523,
        cycle_arg: LAYOUT__524,
    };
pub const LAYOUT__536: &ControlSuspendLayout = &ControlSuspendLayout {
    _super: LAYOUT__537,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _arguments_control_suspend__super: LAYOUT__548,
};
pub const LAYOUT__535: &Control0_SuperArm4Layout = &Control0_SuperArm4Layout {
    _super: LAYOUT__536,
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
pub const LAYOUT__552: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__447,
    _0: LAYOUT__40,
};
pub const LAYOUT__553: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__452,
    _0: LAYOUT__138,
};
pub const LAYOUT__554: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__457,
    _0: LAYOUT__500,
};
pub const LAYOUT__555: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__462,
    _0: LAYOUT__504,
};
pub const LAYOUT__556: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__467,
    _0: LAYOUT__508,
};
pub const LAYOUT__557: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__472,
    _0: LAYOUT__512,
};
pub const LAYOUT__558: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__477,
    _0: LAYOUT__516,
};
pub const LAYOUT__559: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__482,
    _0: LAYOUT__520,
};
pub const LAYOUT__551: &MemoryPageOutLayout8LayoutArray = &[
    LAYOUT__552,
    LAYOUT__553,
    LAYOUT__554,
    LAYOUT__555,
    LAYOUT__556,
    LAYOUT__557,
    LAYOUT__558,
    LAYOUT__559,
];
pub const LAYOUT__550: &ControlStoreRootLayout = &ControlStoreRootLayout { _1: LAYOUT__551 };
pub const LAYOUT__549: &Control0_SuperArm5Layout = &Control0_SuperArm5Layout {
    _super: LAYOUT__550,
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
pub const LAYOUT__566: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__567: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__568: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__569: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__570: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__571: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__572: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__573: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__574: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__575: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__576: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__577: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__578: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__579: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__580: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__581: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__565: &ControlTable_SuperArm0_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__566,
    LAYOUT__567,
    LAYOUT__568,
    LAYOUT__569,
    LAYOUT__570,
    LAYOUT__571,
    LAYOUT__572,
    LAYOUT__573,
    LAYOUT__574,
    LAYOUT__575,
    LAYOUT__576,
    LAYOUT__577,
    LAYOUT__578,
    LAYOUT__579,
    LAYOUT__580,
    LAYOUT__581,
];
pub const LAYOUT__564: &ControlTable_SuperArm0_SuperLayout = &ControlTable_SuperArm0_SuperLayout {
    _1: LAYOUT__565,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
};
pub const LAYOUT__563: &ControlTable_SuperArm0Layout = &ControlTable_SuperArm0Layout {
    _super: LAYOUT__564,
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
pub const LAYOUT__585: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__586: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__587: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__588: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__589: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__590: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__591: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__592: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__593: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__594: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__595: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__596: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__597: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__598: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__599: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__600: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__584: &ControlTable_SuperArm1_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__585,
    LAYOUT__586,
    LAYOUT__587,
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
];
pub const LAYOUT__583: &ControlTable_SuperArm1_SuperLayout = &ControlTable_SuperArm1_SuperLayout {
    _1: LAYOUT__584,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
};
pub const LAYOUT__582: &ControlTable_SuperArm1Layout = &ControlTable_SuperArm1Layout {
    _super: LAYOUT__583,
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
pub const LAYOUT__562: &ControlTable_SuperLayout = &ControlTable_SuperLayout {
    arm0: LAYOUT__563,
    arm1: LAYOUT__582,
};
pub const LAYOUT__602: &ArgU16Layout16LayoutArray = &[
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
pub const LAYOUT__603: &ArgU8Layout16LayoutArray = &[
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
pub const LAYOUT__601: &_Arguments_ControlTable_SuperLayout =
    &_Arguments_ControlTable_SuperLayout {
        arg_u16: LAYOUT__602,
        arg_u8: LAYOUT__603,
    };
pub const LAYOUT__561: &ControlTableLayout = &ControlTableLayout {
    _super: LAYOUT__562,
    entry: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    mode: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    _arguments_control_table__super: LAYOUT__601,
};
pub const LAYOUT__560: &Control0_SuperArm6Layout = &Control0_SuperArm6Layout {
    _super: LAYOUT__561,
    _extra0: LAYOUT__448,
    _extra1: LAYOUT__449,
    _extra2: LAYOUT__453,
    _extra3: LAYOUT__454,
    _extra4: LAYOUT__458,
    _extra5: LAYOUT__459,
    _extra6: LAYOUT__463,
    _extra7: LAYOUT__464,
    _extra8: LAYOUT__468,
    _extra9: LAYOUT__469,
    _extra10: LAYOUT__473,
    _extra11: LAYOUT__474,
    _extra12: LAYOUT__478,
    _extra13: LAYOUT__479,
    _extra14: LAYOUT__483,
    _extra15: LAYOUT__484,
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
pub const LAYOUT__606: &_Arguments_ControlDone__0Layout = &_Arguments_ControlDone__0Layout {
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    }],
};
pub const LAYOUT__608: &ControlDone__0Arm0_SuperLayout =
    &ControlDone__0Arm0_SuperLayout { _0: LAYOUT__41 };
pub const LAYOUT__609: &ControlDone__0Arm1Layout = &ControlDone__0Arm1Layout {
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__607: &ControlDone__0Layout = &ControlDone__0Layout {
    arm0: LAYOUT__608,
    arm1: LAYOUT__609,
};
pub const LAYOUT__605: &ControlDoneLayout = &ControlDoneLayout {
    _arguments_control_done__0: LAYOUT__606,
    _2: LAYOUT__607,
};
pub const LAYOUT__604: &Control0_SuperArm7Layout = &Control0_SuperArm7Layout {
    _super: LAYOUT__605,
    _extra0: LAYOUT__448,
    _extra1: LAYOUT__449,
    _extra2: LAYOUT__453,
    _extra3: LAYOUT__454,
    _extra4: LAYOUT__458,
    _extra5: LAYOUT__459,
    _extra6: LAYOUT__463,
    _extra7: LAYOUT__464,
    _extra8: LAYOUT__468,
    _extra9: LAYOUT__469,
    _extra10: LAYOUT__473,
    _extra11: LAYOUT__474,
    _extra12: LAYOUT__478,
    _extra13: LAYOUT__479,
    _extra14: LAYOUT__483,
    _extra15: LAYOUT__484,
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
pub const LAYOUT__441: &Control0_SuperLayout = &Control0_SuperLayout {
    arm0: LAYOUT__442,
    arm1: LAYOUT__485,
    arm2: LAYOUT__525,
    arm3: LAYOUT__530,
    arm4: LAYOUT__535,
    arm5: LAYOUT__549,
    arm6: LAYOUT__560,
    arm7: LAYOUT__604,
};
pub const LAYOUT__610: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__611: &_Arguments_Control0_SuperLayout = &_Arguments_Control0_SuperLayout {
    memory_arg: LAYOUT__523,
    cycle_arg: LAYOUT__524,
    arg_u16: LAYOUT__602,
    arg_u8: LAYOUT__603,
};
pub const LAYOUT__440: &Control0Layout = &Control0Layout {
    _super: LAYOUT__441,
    _0: LAYOUT__610,
    _arguments_control0__super: LAYOUT__611,
};
pub const LAYOUT__613: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__615: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
    },
};
pub const LAYOUT__614: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    upper_diff: LAYOUT__615,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    med14: LAYOUT__407,
};
pub const LAYOUT__617: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__448,
    LAYOUT__449,
    LAYOUT__453,
    LAYOUT__454,
    LAYOUT__458,
    LAYOUT__459,
    LAYOUT__463,
    LAYOUT__464,
];
pub const LAYOUT__618: &CycleArgLayout4LayoutArray = &[
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
pub const LAYOUT__619: &ArgU16Layout4LayoutArray = &[
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
pub const LAYOUT__620: &ArgU8Layout4LayoutArray = &[
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
pub const LAYOUT__616: &_Arguments_ECall0OutputLayout = &_Arguments_ECall0OutputLayout {
    memory_arg: LAYOUT__617,
    cycle_arg: LAYOUT__618,
    arg_u16: LAYOUT__619,
    arg_u8: LAYOUT__620,
};
pub const LAYOUT__626: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__625: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__626 };
pub const LAYOUT__624: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__447,
    _0: LAYOUT__625,
};
pub const LAYOUT__629: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__628: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__629 };
pub const LAYOUT__627: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__452,
    _0: LAYOUT__628,
};
pub const LAYOUT__631: &NondetRegLayout6LayoutArray = &[
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
pub const LAYOUT__630: &OneHot_6_Layout = &OneHot_6_Layout {
    _super: LAYOUT__631,
};
pub const LAYOUT__623: &MachineECallLayout = &MachineECallLayout {
    load_inst: LAYOUT__624,
    dispatch_idx: LAYOUT__627,
    dispatch: LAYOUT__630,
};
pub const LAYOUT__622: &ECall0OutputArm0Layout = &ECall0OutputArm0Layout {
    _super: LAYOUT__623,
    _extra0: LAYOUT__458,
    _extra1: LAYOUT__459,
    _extra2: LAYOUT__463,
    _extra3: LAYOUT__464,
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
pub const LAYOUT__633: &ECallTerminateLayout = &ECallTerminateLayout {
    a0: LAYOUT__624,
    a1: LAYOUT__627,
};
pub const LAYOUT__632: &ECall0OutputArm1Layout = &ECall0OutputArm1Layout {
    _super: LAYOUT__633,
    _extra0: LAYOUT__458,
    _extra1: LAYOUT__459,
    _extra2: LAYOUT__463,
    _extra3: LAYOUT__464,
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
pub const LAYOUT__638: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__637: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__638 };
pub const LAYOUT__636: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__457,
    _0: LAYOUT__637,
};
pub const LAYOUT__639: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__640: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
};
pub const LAYOUT__643: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
};
pub const LAYOUT__642: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__643 };
pub const LAYOUT__641: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__462,
    _0: LAYOUT__642,
};
pub const LAYOUT__645: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
};
pub const LAYOUT__647: &NondetRegLayout4LayoutArray = &[
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
pub const LAYOUT__646: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__647,
};
pub const LAYOUT__644: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__645,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    low2_hot: LAYOUT__646,
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
pub const LAYOUT__649: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
};
pub const LAYOUT__651: &NondetRegLayout4LayoutArray = &[
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
pub const LAYOUT__650: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__651,
};
pub const LAYOUT__648: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__649,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low2_hot: LAYOUT__650,
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
pub const LAYOUT__635: &ECallHostReadSetupLayout = &ECallHostReadSetupLayout {
    fd: LAYOUT__624,
    ptr: LAYOUT__627,
    len: LAYOUT__636,
    new_len: LAYOUT__639,
    diff: LAYOUT__640,
    _0: LAYOUT__641,
    ptr_decomp: LAYOUT__644,
    len_decomp: LAYOUT__648,
    len123: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    uneven: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
};
pub const LAYOUT__634: &ECall0OutputArm2Layout = &ECall0OutputArm2Layout {
    _super: LAYOUT__635,
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
pub const LAYOUT__653: &ECallHostWriteLayout = &ECallHostWriteLayout {
    fd: LAYOUT__624,
    ptr: LAYOUT__627,
    len: LAYOUT__636,
    new_len: LAYOUT__639,
    diff: LAYOUT__640,
    _0: LAYOUT__641,
};
pub const LAYOUT__652: &ECall0OutputArm3Layout = &ECall0OutputArm3Layout {
    _super: LAYOUT__653,
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
pub const LAYOUT__656: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__639,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    low2_hot: LAYOUT__646,
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
pub const LAYOUT__657: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__452,
    _0: LAYOUT__628,
};
pub const LAYOUT__658: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__259,
    byte1: LAYOUT__261,
};
pub const LAYOUT__660: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__659: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__264,
    byte1: LAYOUT__660,
};
pub const LAYOUT__655: &ECallHostReadBytesLayout = &ECallHostReadBytesLayout {
    len_decomp: LAYOUT__656,
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
    orig_word: LAYOUT__624,
    _0: LAYOUT__657,
    old_bytes: LAYOUT__658,
    new_bytes_0: LAYOUT__659,
};
pub const LAYOUT__654: &ECall0OutputArm4Layout = &ECall0OutputArm4Layout {
    _super: LAYOUT__655,
    _extra0: LAYOUT__458,
    _extra1: LAYOUT__459,
    _extra2: LAYOUT__463,
    _extra3: LAYOUT__464,
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
pub const LAYOUT__663: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__640,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    low2_hot: LAYOUT__650,
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
pub const LAYOUT__666: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__447,
    _0: LAYOUT__625,
};
pub const LAYOUT__665: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    _0: LAYOUT__666,
};
pub const LAYOUT__667: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    _0: LAYOUT__657,
};
pub const LAYOUT__669: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__457,
    _0: LAYOUT__637,
};
pub const LAYOUT__668: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
    _0: LAYOUT__669,
};
pub const LAYOUT__671: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__462,
    _0: LAYOUT__642,
};
pub const LAYOUT__670: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    _0: LAYOUT__671,
};
pub const LAYOUT__664: &ECallHostReadWords__0_SuperLayout4LayoutArray =
    &[LAYOUT__665, LAYOUT__667, LAYOUT__668, LAYOUT__670];
pub const LAYOUT__662: &ECallHostReadWordsLayout = &ECallHostReadWordsLayout {
    len_decomp: LAYOUT__656,
    words_decomp: LAYOUT__663,
    _1: LAYOUT__664,
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
pub const LAYOUT__661: &ECall0OutputArm5Layout = &ECall0OutputArm5Layout {
    _super: LAYOUT__662,
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
pub const LAYOUT__672: &ECall0OutputArm6Layout = &ECall0OutputArm6Layout {
    _extra0: LAYOUT__448,
    _extra1: LAYOUT__449,
    _extra2: LAYOUT__453,
    _extra3: LAYOUT__454,
    _extra4: LAYOUT__458,
    _extra5: LAYOUT__459,
    _extra6: LAYOUT__463,
    _extra7: LAYOUT__464,
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
pub const LAYOUT__673: &ECall0OutputArm7Layout = &ECall0OutputArm7Layout {
    _extra0: LAYOUT__448,
    _extra1: LAYOUT__449,
    _extra2: LAYOUT__453,
    _extra3: LAYOUT__454,
    _extra4: LAYOUT__458,
    _extra5: LAYOUT__459,
    _extra6: LAYOUT__463,
    _extra7: LAYOUT__464,
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
pub const LAYOUT__621: &ECall0OutputLayout = &ECall0OutputLayout {
    arm0: LAYOUT__622,
    arm1: LAYOUT__632,
    arm2: LAYOUT__634,
    arm3: LAYOUT__652,
    arm4: LAYOUT__654,
    arm5: LAYOUT__661,
    arm6: LAYOUT__672,
    arm7: LAYOUT__673,
};
pub const LAYOUT__675: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__676: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__674: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__675,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
    high16: LAYOUT__676,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
};
pub const LAYOUT__612: &ECall0Layout = &ECall0Layout {
    s0: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    s1: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    s2: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    _0: LAYOUT__613,
    pc_addr: LAYOUT__614,
    _arguments_e_call0_output: LAYOUT__616,
    output: LAYOUT__621,
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
    add_pc: LAYOUT__674,
};
pub const LAYOUT__678: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__680: &NondetRegLayout24LayoutArray = &[
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
pub const LAYOUT__679: &PoseidonStateLayout = &PoseidonStateLayout {
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
    inner: LAYOUT__680,
    zcheck: &NondetExtRegLayout {
        _super: &Reg { offset: 64 },
    },
};
pub const LAYOUT__683: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__684: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__685: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__686: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__687: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__688: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__689: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__690: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__691: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__692: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__693: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__694: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__695: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__696: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__697: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__698: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__682: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__683,
    LAYOUT__684,
    LAYOUT__685,
    LAYOUT__686,
    LAYOUT__687,
    LAYOUT__688,
    LAYOUT__689,
    LAYOUT__690,
    LAYOUT__691,
    LAYOUT__692,
    LAYOUT__693,
    LAYOUT__694,
    LAYOUT__695,
    LAYOUT__696,
    LAYOUT__697,
    LAYOUT__698,
];
pub const LAYOUT__699: &CycleArgLayout8LayoutArray = &[
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
pub const LAYOUT__700: &ArgU16Layout24LayoutArray = &[
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
pub const LAYOUT__701: &ArgU8Layout2LayoutArray = &[
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
pub const LAYOUT__681: &_Arguments_Poseidon0StateLayout = &_Arguments_Poseidon0StateLayout {
    memory_arg: LAYOUT__682,
    cycle_arg: LAYOUT__699,
    arg_u16: LAYOUT__700,
    arg_u8: LAYOUT__701,
};
pub const LAYOUT__706: &PoseidonEntry_SuperArm0Layout = &PoseidonEntry_SuperArm0Layout {
    _super: LAYOUT__679,
    _extra0: LAYOUT__683,
    _extra1: LAYOUT__684,
    _extra2: LAYOUT__685,
    _extra3: LAYOUT__686,
    _extra4: LAYOUT__687,
    _extra5: LAYOUT__688,
    _extra6: LAYOUT__689,
    _extra7: LAYOUT__690,
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
pub const LAYOUT__710: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__683,
    new_txn: LAYOUT__684,
};
pub const LAYOUT__712: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__711: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__712 };
pub const LAYOUT__709: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__710,
    _0: LAYOUT__711,
};
pub const LAYOUT__708: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__709,
};
pub const LAYOUT__715: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__685,
    new_txn: LAYOUT__686,
};
pub const LAYOUT__717: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__716: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__717 };
pub const LAYOUT__714: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__715,
    _0: LAYOUT__716,
};
pub const LAYOUT__713: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__714,
};
pub const LAYOUT__720: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__687,
    new_txn: LAYOUT__688,
};
pub const LAYOUT__722: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__721: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__722 };
pub const LAYOUT__719: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__720,
    _0: LAYOUT__721,
};
pub const LAYOUT__718: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__719,
};
pub const LAYOUT__724: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__689,
    new_txn: LAYOUT__690,
};
pub const LAYOUT__723: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__724,
    _0: LAYOUT__236,
};
pub const LAYOUT__707: &PoseidonEcallLayout = &PoseidonEcallLayout {
    _super: LAYOUT__679,
    state_addr: LAYOUT__708,
    buf_in_addr: LAYOUT__713,
    buf_out_addr: LAYOUT__718,
    bits_and_count: LAYOUT__723,
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
pub const LAYOUT__705: &PoseidonEntry_SuperLayout = &PoseidonEntry_SuperLayout {
    _super: LAYOUT__679,
    arm0: LAYOUT__706,
    arm1: LAYOUT__707,
};
pub const LAYOUT__726: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__683,
    LAYOUT__684,
    LAYOUT__685,
    LAYOUT__686,
    LAYOUT__687,
    LAYOUT__688,
    LAYOUT__689,
    LAYOUT__690,
];
pub const LAYOUT__727: &CycleArgLayout4LayoutArray = &[
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
pub const LAYOUT__725: &_Arguments_PoseidonEntry_SuperLayout =
    &_Arguments_PoseidonEntry_SuperLayout {
        memory_arg: LAYOUT__726,
        cycle_arg: LAYOUT__727,
    };
pub const LAYOUT__704: &PoseidonEntryLayout = &PoseidonEntryLayout {
    _super: LAYOUT__705,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 202 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 203 },
        },
    },
    _arguments_poseidon_entry__super: LAYOUT__725,
};
pub const LAYOUT__703: &Poseidon0StateArm0Layout = &Poseidon0StateArm0Layout {
    _super: LAYOUT__704,
    _extra0: LAYOUT__691,
    _extra1: LAYOUT__692,
    _extra2: LAYOUT__693,
    _extra3: LAYOUT__694,
    _extra4: LAYOUT__695,
    _extra5: LAYOUT__696,
    _extra6: LAYOUT__697,
    _extra7: LAYOUT__698,
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
pub const LAYOUT__731: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__709,
};
pub const LAYOUT__732: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__714,
};
pub const LAYOUT__733: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__719,
};
pub const LAYOUT__734: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__723,
};
pub const LAYOUT__737: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__691,
    new_txn: LAYOUT__692,
};
pub const LAYOUT__739: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
};
pub const LAYOUT__738: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__739 };
pub const LAYOUT__736: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__737,
    _0: LAYOUT__738,
};
pub const LAYOUT__735: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__736,
};
pub const LAYOUT__742: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__693,
    new_txn: LAYOUT__694,
};
pub const LAYOUT__744: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
};
pub const LAYOUT__743: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__744 };
pub const LAYOUT__741: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__742,
    _0: LAYOUT__743,
};
pub const LAYOUT__740: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__741,
};
pub const LAYOUT__747: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__695,
    new_txn: LAYOUT__696,
};
pub const LAYOUT__749: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
};
pub const LAYOUT__748: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__749 };
pub const LAYOUT__746: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__747,
    _0: LAYOUT__748,
};
pub const LAYOUT__745: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__746,
};
pub const LAYOUT__752: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__697,
    new_txn: LAYOUT__698,
};
pub const LAYOUT__754: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
};
pub const LAYOUT__753: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__754 };
pub const LAYOUT__751: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__752,
    _0: LAYOUT__753,
};
pub const LAYOUT__750: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__751,
};
pub const LAYOUT__730: &ReadElemLayout8LayoutArray = &[
    LAYOUT__731,
    LAYOUT__732,
    LAYOUT__733,
    LAYOUT__734,
    LAYOUT__735,
    LAYOUT__740,
    LAYOUT__745,
    LAYOUT__750,
];
pub const LAYOUT__729: &PoseidonLoadStateLayout = &PoseidonLoadStateLayout {
    _super: LAYOUT__679,
    load_list: LAYOUT__730,
};
pub const LAYOUT__728: &Poseidon0StateArm1Layout = &Poseidon0StateArm1Layout {
    _super: LAYOUT__729,
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
pub const LAYOUT__759: &OneHot_3_Layout = &OneHot_3_Layout {
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
pub const LAYOUT__764: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__710 };
pub const LAYOUT__763: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__764,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__765: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__710,
    _0: LAYOUT__711,
};
pub const LAYOUT__762: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__709,
    arm1: LAYOUT__763,
    arm2: LAYOUT__765,
};
pub const LAYOUT__767: &MemoryArgLayout2LayoutArray = &[LAYOUT__683, LAYOUT__684];
pub const LAYOUT__766: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__767,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    }],
};
pub const LAYOUT__761: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__762,
    _arguments_memory_get__super: LAYOUT__766,
};
pub const LAYOUT__771: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__715 };
pub const LAYOUT__770: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__771,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__772: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__715,
    _0: LAYOUT__716,
};
pub const LAYOUT__769: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__714,
    arm1: LAYOUT__770,
    arm2: LAYOUT__772,
};
pub const LAYOUT__774: &MemoryArgLayout2LayoutArray = &[LAYOUT__685, LAYOUT__686];
pub const LAYOUT__773: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__774,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    }],
};
pub const LAYOUT__768: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__769,
    _arguments_memory_get__super: LAYOUT__773,
};
pub const LAYOUT__778: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__720 };
pub const LAYOUT__777: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__778,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__779: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__720,
    _0: LAYOUT__721,
};
pub const LAYOUT__776: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__719,
    arm1: LAYOUT__777,
    arm2: LAYOUT__779,
};
pub const LAYOUT__781: &MemoryArgLayout2LayoutArray = &[LAYOUT__687, LAYOUT__688];
pub const LAYOUT__780: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__781,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    }],
};
pub const LAYOUT__775: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__776,
    _arguments_memory_get__super: LAYOUT__780,
};
pub const LAYOUT__785: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__724 };
pub const LAYOUT__784: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__785,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__786: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__724,
    _0: LAYOUT__236,
};
pub const LAYOUT__783: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__723,
    arm1: LAYOUT__784,
    arm2: LAYOUT__786,
};
pub const LAYOUT__788: &MemoryArgLayout2LayoutArray = &[LAYOUT__689, LAYOUT__690];
pub const LAYOUT__787: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__788,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    }],
};
pub const LAYOUT__782: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__783,
    _arguments_memory_get__super: LAYOUT__787,
};
pub const LAYOUT__792: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__737 };
pub const LAYOUT__791: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__792,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
};
pub const LAYOUT__793: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__737,
    _0: LAYOUT__738,
};
pub const LAYOUT__790: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__736,
    arm1: LAYOUT__791,
    arm2: LAYOUT__793,
};
pub const LAYOUT__795: &MemoryArgLayout2LayoutArray = &[LAYOUT__691, LAYOUT__692];
pub const LAYOUT__794: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__795,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    }],
};
pub const LAYOUT__789: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__790,
    _arguments_memory_get__super: LAYOUT__794,
};
pub const LAYOUT__799: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__742 };
pub const LAYOUT__798: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__799,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
};
pub const LAYOUT__800: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__742,
    _0: LAYOUT__743,
};
pub const LAYOUT__797: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__741,
    arm1: LAYOUT__798,
    arm2: LAYOUT__800,
};
pub const LAYOUT__802: &MemoryArgLayout2LayoutArray = &[LAYOUT__693, LAYOUT__694];
pub const LAYOUT__801: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__802,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    }],
};
pub const LAYOUT__796: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__797,
    _arguments_memory_get__super: LAYOUT__801,
};
pub const LAYOUT__806: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__747 };
pub const LAYOUT__805: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__806,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
};
pub const LAYOUT__807: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__747,
    _0: LAYOUT__748,
};
pub const LAYOUT__804: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__746,
    arm1: LAYOUT__805,
    arm2: LAYOUT__807,
};
pub const LAYOUT__809: &MemoryArgLayout2LayoutArray = &[LAYOUT__695, LAYOUT__696];
pub const LAYOUT__808: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__809,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    }],
};
pub const LAYOUT__803: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__804,
    _arguments_memory_get__super: LAYOUT__808,
};
pub const LAYOUT__813: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__752 };
pub const LAYOUT__812: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__813,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
};
pub const LAYOUT__814: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__752,
    _0: LAYOUT__753,
};
pub const LAYOUT__811: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__751,
    arm1: LAYOUT__812,
    arm2: LAYOUT__814,
};
pub const LAYOUT__816: &MemoryArgLayout2LayoutArray = &[LAYOUT__697, LAYOUT__698];
pub const LAYOUT__815: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__816,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    }],
};
pub const LAYOUT__810: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__811,
    _arguments_memory_get__super: LAYOUT__815,
};
pub const LAYOUT__760: &MemoryGetLayout8LayoutArray = &[
    LAYOUT__761,
    LAYOUT__768,
    LAYOUT__775,
    LAYOUT__782,
    LAYOUT__789,
    LAYOUT__796,
    LAYOUT__803,
    LAYOUT__810,
];
pub const LAYOUT__758: &PoseidonLoadInShortLayout = &PoseidonLoadInShortLayout {
    _super: LAYOUT__679,
    tx_type: LAYOUT__759,
    load_list: LAYOUT__760,
};
pub const LAYOUT__817: &PoseidonLoadInLowLayout = &PoseidonLoadInLowLayout {
    _super: LAYOUT__679,
    tx_type: LAYOUT__759,
    load_list: LAYOUT__760,
};
pub const LAYOUT__818: &PoseidonLoadInHighLayout = &PoseidonLoadInHighLayout {
    _super: LAYOUT__679,
    tx_type: LAYOUT__759,
    load_list: LAYOUT__760,
};
pub const LAYOUT__757: &PoseidonLoadIn_SuperLayout = &PoseidonLoadIn_SuperLayout {
    _super: LAYOUT__679,
    arm0: LAYOUT__758,
    arm1: LAYOUT__817,
    arm2: LAYOUT__818,
};
pub const LAYOUT__819: &OneHot_3_Layout = &OneHot_3_Layout {
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
pub const LAYOUT__820: &_Arguments_PoseidonLoadIn_SuperLayout =
    &_Arguments_PoseidonLoadIn_SuperLayout {
        memory_arg: LAYOUT__682,
        cycle_arg: LAYOUT__699,
    };
pub const LAYOUT__756: &PoseidonLoadInLayout = &PoseidonLoadInLayout {
    _super: LAYOUT__757,
    _0: LAYOUT__819,
    _arguments_poseidon_load_in__super: LAYOUT__820,
};
pub const LAYOUT__755: &Poseidon0StateArm2Layout = &Poseidon0StateArm2Layout {
    _super: LAYOUT__756,
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
pub const LAYOUT__821: &Poseidon0StateArm3Layout = &Poseidon0StateArm3Layout {
    _super: LAYOUT__679,
    _extra0: LAYOUT__683,
    _extra1: LAYOUT__684,
    _extra2: LAYOUT__685,
    _extra3: LAYOUT__686,
    _extra4: LAYOUT__687,
    _extra5: LAYOUT__688,
    _extra6: LAYOUT__689,
    _extra7: LAYOUT__690,
    _extra8: LAYOUT__691,
    _extra9: LAYOUT__692,
    _extra10: LAYOUT__693,
    _extra11: LAYOUT__694,
    _extra12: LAYOUT__695,
    _extra13: LAYOUT__696,
    _extra14: LAYOUT__697,
    _extra15: LAYOUT__698,
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
pub const LAYOUT__822: &Poseidon0StateArm4Layout = &Poseidon0StateArm4Layout {
    _super: LAYOUT__679,
    _extra0: LAYOUT__683,
    _extra1: LAYOUT__684,
    _extra2: LAYOUT__685,
    _extra3: LAYOUT__686,
    _extra4: LAYOUT__687,
    _extra5: LAYOUT__688,
    _extra6: LAYOUT__689,
    _extra7: LAYOUT__690,
    _extra8: LAYOUT__691,
    _extra9: LAYOUT__692,
    _extra10: LAYOUT__693,
    _extra11: LAYOUT__694,
    _extra12: LAYOUT__695,
    _extra13: LAYOUT__696,
    _extra14: LAYOUT__697,
    _extra15: LAYOUT__698,
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
pub const LAYOUT__829: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__731 };
pub const LAYOUT__830: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__732 };
pub const LAYOUT__831: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__733 };
pub const LAYOUT__832: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__734 };
pub const LAYOUT__833: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__735 };
pub const LAYOUT__834: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__740 };
pub const LAYOUT__835: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__745 };
pub const LAYOUT__836: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__750 };
pub const LAYOUT__828: &PoseidonCheckOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__829,
    LAYOUT__830,
    LAYOUT__831,
    LAYOUT__832,
    LAYOUT__833,
    LAYOUT__834,
    LAYOUT__835,
    LAYOUT__836,
];
pub const LAYOUT__827: &PoseidonCheckOutLayout = &PoseidonCheckOutLayout {
    _super: LAYOUT__679,
    _1: LAYOUT__828,
    is_normal: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 196 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 197 },
        },
    },
};
pub const LAYOUT__826: &PoseidonDoOut_SuperArm0Layout = &PoseidonDoOut_SuperArm0Layout {
    _super: LAYOUT__827,
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
pub const LAYOUT__841: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__842: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
};
pub const LAYOUT__843: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    }],
};
pub const LAYOUT__846: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
};
pub const LAYOUT__845: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__846 };
pub const LAYOUT__847: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__846 };
pub const LAYOUT__844: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__845,
    arm1: LAYOUT__847,
};
pub const LAYOUT__840: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__841,
    high: LAYOUT__842,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    _arguments_field_to_word__0: LAYOUT__843,
    _2: LAYOUT__844,
};
pub const LAYOUT__848: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__710,
    _0: LAYOUT__711,
};
pub const LAYOUT__839: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__840,
    mw: LAYOUT__848,
};
pub const LAYOUT__851: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
};
pub const LAYOUT__852: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__853: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    }],
};
pub const LAYOUT__855: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__208 };
pub const LAYOUT__856: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__208 };
pub const LAYOUT__854: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__855,
    arm1: LAYOUT__856,
};
pub const LAYOUT__850: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__851,
    high: LAYOUT__852,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    _arguments_field_to_word__0: LAYOUT__853,
    _2: LAYOUT__854,
};
pub const LAYOUT__857: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__715,
    _0: LAYOUT__716,
};
pub const LAYOUT__849: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__850,
    mw: LAYOUT__857,
};
pub const LAYOUT__860: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__861: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
};
pub const LAYOUT__862: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    }],
};
pub const LAYOUT__865: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
};
pub const LAYOUT__864: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__865 };
pub const LAYOUT__866: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__865 };
pub const LAYOUT__863: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__864,
    arm1: LAYOUT__866,
};
pub const LAYOUT__859: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__860,
    high: LAYOUT__861,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 198 },
    },
    _arguments_field_to_word__0: LAYOUT__862,
    _2: LAYOUT__863,
};
pub const LAYOUT__867: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__720,
    _0: LAYOUT__721,
};
pub const LAYOUT__858: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__859,
    mw: LAYOUT__867,
};
pub const LAYOUT__870: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__871: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__872: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    }],
};
pub const LAYOUT__875: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
};
pub const LAYOUT__874: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__875 };
pub const LAYOUT__876: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__875 };
pub const LAYOUT__873: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__874,
    arm1: LAYOUT__876,
};
pub const LAYOUT__869: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__870,
    high: LAYOUT__871,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 199 },
    },
    _arguments_field_to_word__0: LAYOUT__872,
    _2: LAYOUT__873,
};
pub const LAYOUT__877: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__724,
    _0: LAYOUT__236,
};
pub const LAYOUT__868: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__869,
    mw: LAYOUT__877,
};
pub const LAYOUT__880: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__881: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__882: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    }],
};
pub const LAYOUT__885: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
};
pub const LAYOUT__884: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__885 };
pub const LAYOUT__886: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__885 };
pub const LAYOUT__883: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__884,
    arm1: LAYOUT__886,
};
pub const LAYOUT__879: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__880,
    high: LAYOUT__881,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 200 },
    },
    _arguments_field_to_word__0: LAYOUT__882,
    _2: LAYOUT__883,
};
pub const LAYOUT__887: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__737,
    _0: LAYOUT__738,
};
pub const LAYOUT__878: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__879,
    mw: LAYOUT__887,
};
pub const LAYOUT__890: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__891: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
};
pub const LAYOUT__892: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    }],
};
pub const LAYOUT__895: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__894: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__895 };
pub const LAYOUT__896: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__895 };
pub const LAYOUT__893: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__894,
    arm1: LAYOUT__896,
};
pub const LAYOUT__889: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__890,
    high: LAYOUT__891,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 201 },
    },
    _arguments_field_to_word__0: LAYOUT__892,
    _2: LAYOUT__893,
};
pub const LAYOUT__897: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__742,
    _0: LAYOUT__743,
};
pub const LAYOUT__888: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__889,
    mw: LAYOUT__897,
};
pub const LAYOUT__900: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
};
pub const LAYOUT__901: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
};
pub const LAYOUT__902: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    }],
};
pub const LAYOUT__905: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
};
pub const LAYOUT__904: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__905 };
pub const LAYOUT__906: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__905 };
pub const LAYOUT__903: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__904,
    arm1: LAYOUT__906,
};
pub const LAYOUT__899: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__900,
    high: LAYOUT__901,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 202 },
    },
    _arguments_field_to_word__0: LAYOUT__902,
    _2: LAYOUT__903,
};
pub const LAYOUT__907: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__747,
    _0: LAYOUT__748,
};
pub const LAYOUT__898: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__899,
    mw: LAYOUT__907,
};
pub const LAYOUT__910: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__911: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__912: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    }],
};
pub const LAYOUT__915: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
};
pub const LAYOUT__914: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__915 };
pub const LAYOUT__916: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__915 };
pub const LAYOUT__913: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__914,
    arm1: LAYOUT__916,
};
pub const LAYOUT__909: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__910,
    high: LAYOUT__911,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 203 },
    },
    _arguments_field_to_word__0: LAYOUT__912,
    _2: LAYOUT__913,
};
pub const LAYOUT__917: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__752,
    _0: LAYOUT__753,
};
pub const LAYOUT__908: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__909,
    mw: LAYOUT__917,
};
pub const LAYOUT__838: &PoseidonStoreOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__839,
    LAYOUT__849,
    LAYOUT__858,
    LAYOUT__868,
    LAYOUT__878,
    LAYOUT__888,
    LAYOUT__898,
    LAYOUT__908,
];
pub const LAYOUT__837: &PoseidonStoreOutLayout = &PoseidonStoreOutLayout {
    _super: LAYOUT__679,
    _1: LAYOUT__838,
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
pub const LAYOUT__825: &PoseidonDoOut_SuperLayout = &PoseidonDoOut_SuperLayout {
    _super: LAYOUT__679,
    arm0: LAYOUT__826,
    arm1: LAYOUT__837,
};
pub const LAYOUT__918: &_Arguments_PoseidonDoOut_SuperLayout =
    &_Arguments_PoseidonDoOut_SuperLayout {
        memory_arg: LAYOUT__682,
        cycle_arg: LAYOUT__699,
        arg_u16: LAYOUT__700,
    };
pub const LAYOUT__824: &PoseidonDoOutLayout = &PoseidonDoOutLayout {
    _super: LAYOUT__825,
    _arguments_poseidon_do_out__super: LAYOUT__918,
};
pub const LAYOUT__823: &Poseidon0StateArm5Layout = &Poseidon0StateArm5Layout {
    _super: LAYOUT__824,
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
pub const LAYOUT__921: &PoseidonPaging_SuperLayout = &PoseidonPaging_SuperLayout {
    _super: LAYOUT__679,
    arm0: LAYOUT__679,
    arm1: LAYOUT__679,
    arm2: LAYOUT__679,
    arm3: LAYOUT__679,
    arm4: LAYOUT__679,
    arm5: LAYOUT__679,
};
pub const LAYOUT__923: &NondetRegLayout6LayoutArray = &[
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
pub const LAYOUT__922: &OneHot_6_Layout = &OneHot_6_Layout {
    _super: LAYOUT__923,
};
pub const LAYOUT__925: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__924: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__841,
    _0: LAYOUT__925,
};
pub const LAYOUT__926: &_Arguments_PoseidonPaging__1Layout = &_Arguments_PoseidonPaging__1Layout {
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
pub const LAYOUT__930: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
};
pub const LAYOUT__929: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__842,
    _0: LAYOUT__930,
};
pub const LAYOUT__928: &PoseidonPaging__1Arm0_SuperLayout =
    &PoseidonPaging__1Arm0_SuperLayout { _0: LAYOUT__929 };
pub const LAYOUT__931: &PoseidonPaging__1Arm1_SuperLayout =
    &PoseidonPaging__1Arm1_SuperLayout { _0: LAYOUT__929 };
pub const LAYOUT__927: &PoseidonPaging__1Layout = &PoseidonPaging__1Layout {
    arm0: LAYOUT__928,
    arm1: LAYOUT__931,
};
pub const LAYOUT__920: &PoseidonPagingLayout = &PoseidonPagingLayout {
    _super: LAYOUT__921,
    cur_idx: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    cur_mode: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    mode_split: LAYOUT__922,
    _0: LAYOUT__924,
    _arguments_poseidon_paging__1: LAYOUT__926,
    _3: LAYOUT__927,
    _4: &NondetRegLayout {
        _super: &Reg { offset: 204 },
    },
};
pub const LAYOUT__919: &Poseidon0StateArm6Layout = &Poseidon0StateArm6Layout {
    _super: LAYOUT__920,
    _extra0: LAYOUT__683,
    _extra1: LAYOUT__684,
    _extra2: LAYOUT__685,
    _extra3: LAYOUT__686,
    _extra4: LAYOUT__687,
    _extra5: LAYOUT__688,
    _extra6: LAYOUT__689,
    _extra7: LAYOUT__690,
    _extra8: LAYOUT__691,
    _extra9: LAYOUT__692,
    _extra10: LAYOUT__693,
    _extra11: LAYOUT__694,
    _extra12: LAYOUT__695,
    _extra13: LAYOUT__696,
    _extra14: LAYOUT__697,
    _extra15: LAYOUT__698,
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
pub const LAYOUT__935: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__840,
    mw: LAYOUT__848,
};
pub const LAYOUT__936: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__850,
    mw: LAYOUT__857,
};
pub const LAYOUT__937: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__859,
    mw: LAYOUT__867,
};
pub const LAYOUT__938: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__869,
    mw: LAYOUT__877,
};
pub const LAYOUT__939: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__879,
    mw: LAYOUT__887,
};
pub const LAYOUT__940: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__889,
    mw: LAYOUT__897,
};
pub const LAYOUT__941: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__899,
    mw: LAYOUT__907,
};
pub const LAYOUT__942: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__909,
    mw: LAYOUT__917,
};
pub const LAYOUT__934: &PoseidonStoreState__0_SuperLayout8LayoutArray = &[
    LAYOUT__935,
    LAYOUT__936,
    LAYOUT__937,
    LAYOUT__938,
    LAYOUT__939,
    LAYOUT__940,
    LAYOUT__941,
    LAYOUT__942,
];
pub const LAYOUT__933: &PoseidonStoreStateLayout = &PoseidonStoreStateLayout {
    _super: LAYOUT__679,
    _1: LAYOUT__934,
};
pub const LAYOUT__932: &Poseidon0StateArm7Layout = &Poseidon0StateArm7Layout {
    _super: LAYOUT__933,
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
pub const LAYOUT__702: &Poseidon0StateLayout = &Poseidon0StateLayout {
    _super: LAYOUT__679,
    arm0: LAYOUT__703,
    arm1: LAYOUT__728,
    arm2: LAYOUT__755,
    arm3: LAYOUT__821,
    arm4: LAYOUT__822,
    arm5: LAYOUT__823,
    arm6: LAYOUT__919,
    arm7: LAYOUT__932,
};
pub const LAYOUT__677: &Poseidon0Layout = &Poseidon0Layout {
    _0: LAYOUT__678,
    state: LAYOUT__679,
    _arguments_poseidon0_state: LAYOUT__681,
    state_redef: LAYOUT__702,
};
pub const LAYOUT__944: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__949: &SBoxLayout24LayoutArray = &[
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
pub const LAYOUT__948: &DoExtRoundLayout = &DoExtRoundLayout { _1: LAYOUT__949 };
pub const LAYOUT__951: &NondetRegLayout8LayoutArray = &[
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
pub const LAYOUT__950: &OneHot_8_Layout = &OneHot_8_Layout {
    _super: LAYOUT__951,
};
pub const LAYOUT__947: &DoExtRoundByIdxLayout = &DoExtRoundByIdxLayout {
    _super: LAYOUT__948,
    idx_hot: LAYOUT__950,
};
pub const LAYOUT__946: &PoseidonExtRoundLayout = &PoseidonExtRoundLayout {
    _super: LAYOUT__679,
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
    next_inner: LAYOUT__947,
};
pub const LAYOUT__955: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
};
pub const LAYOUT__956: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__957: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
};
pub const LAYOUT__958: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__959: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
};
pub const LAYOUT__960: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
};
pub const LAYOUT__961: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__962: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
};
pub const LAYOUT__963: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__964: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
};
pub const LAYOUT__965: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__966: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
};
pub const LAYOUT__967: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
    },
};
pub const LAYOUT__968: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
    },
};
pub const LAYOUT__969: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
};
pub const LAYOUT__970: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__971: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
};
pub const LAYOUT__972: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
};
pub const LAYOUT__973: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
};
pub const LAYOUT__974: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__975: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
};
pub const LAYOUT__954: &DoIntRoundLayout21LayoutArray = &[
    LAYOUT__955,
    LAYOUT__956,
    LAYOUT__957,
    LAYOUT__958,
    LAYOUT__959,
    LAYOUT__960,
    LAYOUT__961,
    LAYOUT__962,
    LAYOUT__963,
    LAYOUT__964,
    LAYOUT__965,
    LAYOUT__966,
    LAYOUT__967,
    LAYOUT__968,
    LAYOUT__969,
    LAYOUT__970,
    LAYOUT__971,
    LAYOUT__972,
    LAYOUT__973,
    LAYOUT__974,
    LAYOUT__975,
];
pub const LAYOUT__953: &DoIntRoundsLayout = &DoIntRoundsLayout {
    _super: LAYOUT__954,
};
pub const LAYOUT__952: &PoseidonIntRoundsLayout = &PoseidonIntRoundsLayout {
    _super: LAYOUT__679,
    next_inner: LAYOUT__953,
};
pub const LAYOUT__945: &Poseidon1StateLayout = &Poseidon1StateLayout {
    _super: LAYOUT__679,
    arm0: LAYOUT__946,
    arm1: LAYOUT__952,
    arm2: LAYOUT__679,
    arm3: LAYOUT__679,
    arm4: LAYOUT__679,
    arm5: LAYOUT__679,
    arm6: LAYOUT__679,
    arm7: LAYOUT__679,
};
pub const LAYOUT__943: &Poseidon1Layout = &Poseidon1Layout {
    _0: LAYOUT__944,
    state: LAYOUT__679,
    state_redef: LAYOUT__945,
};
pub const LAYOUT__977: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__979: &NondetRegLayout32LayoutArray = &[
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
pub const LAYOUT__980: &NondetRegLayout32LayoutArray = &[
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
pub const LAYOUT__981: &NondetRegLayout32LayoutArray = &[
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
pub const LAYOUT__978: &ShaStateLayout = &ShaStateLayout {
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
    a: LAYOUT__979,
    e: LAYOUT__980,
    w: LAYOUT__981,
};
pub const LAYOUT__984: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__985: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__986: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__987: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__988: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__989: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__990: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__991: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__992: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__993: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__983: &MemoryArgLayout10LayoutArray = &[
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
];
pub const LAYOUT__994: &CycleArgLayout5LayoutArray = &[
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
pub const LAYOUT__982: &_Arguments_Sha0StateLayout = &_Arguments_Sha0StateLayout {
    memory_arg: LAYOUT__983,
    cycle_arg: LAYOUT__994,
};
pub const LAYOUT__999: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__984,
    new_txn: LAYOUT__985,
};
pub const LAYOUT__1001: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__1000: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1001 };
pub const LAYOUT__998: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__999,
    _0: LAYOUT__1000,
};
pub const LAYOUT__997: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__998,
};
pub const LAYOUT__1004: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__986,
    new_txn: LAYOUT__987,
};
pub const LAYOUT__1006: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__1005: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1006 };
pub const LAYOUT__1003: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1004,
    _0: LAYOUT__1005,
};
pub const LAYOUT__1002: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1003,
};
pub const LAYOUT__1009: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__988,
    new_txn: LAYOUT__989,
};
pub const LAYOUT__1011: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
};
pub const LAYOUT__1010: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1011 };
pub const LAYOUT__1008: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1009,
    _0: LAYOUT__1010,
};
pub const LAYOUT__1007: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1008,
};
pub const LAYOUT__1013: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__990,
    new_txn: LAYOUT__991,
};
pub const LAYOUT__1015: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    },
};
pub const LAYOUT__1014: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1015 };
pub const LAYOUT__1012: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1013,
    _0: LAYOUT__1014,
};
pub const LAYOUT__1018: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__992,
    new_txn: LAYOUT__993,
};
pub const LAYOUT__1020: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1019: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1020 };
pub const LAYOUT__1017: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1018,
    _0: LAYOUT__1019,
};
pub const LAYOUT__1016: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1017,
};
pub const LAYOUT__996: &ShaEcallLayout = &ShaEcallLayout {
    _super: LAYOUT__978,
    state_in_addr: LAYOUT__997,
    state_out_addr: LAYOUT__1002,
    data_addr: LAYOUT__1007,
    _0: LAYOUT__1012,
    k_addr: LAYOUT__1016,
};
pub const LAYOUT__1023: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1009,
    _0: LAYOUT__1010,
};
pub const LAYOUT__1024: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1013,
    _0: LAYOUT__1014,
};
pub const LAYOUT__1022: &ShaLoadStateLayout = &ShaLoadStateLayout {
    _super: LAYOUT__978,
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
    a32: LAYOUT__998,
    e32: LAYOUT__1003,
    _0: LAYOUT__1023,
    _1: LAYOUT__1024,
};
pub const LAYOUT__1021: &Sha0StateArm1Layout = &Sha0StateArm1Layout {
    _super: LAYOUT__1022,
    _extra0: LAYOUT__992,
    _extra1: LAYOUT__993,
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__1028: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__979,
};
pub const LAYOUT__1029: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1030: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1027: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1028,
    low_carry: LAYOUT__1029,
    high_carry: LAYOUT__1030,
};
pub const LAYOUT__1032: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__980,
};
pub const LAYOUT__1033: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1034: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1031: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1032,
    low_carry: LAYOUT__1033,
    high_carry: LAYOUT__1034,
};
pub const LAYOUT__1026: &ShaLoadDataLayout = &ShaLoadDataLayout {
    _super: LAYOUT__978,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
    },
    k: LAYOUT__998,
    w_mem: LAYOUT__1003,
    w_bits: LAYOUT__981,
    a: LAYOUT__1027,
    e: LAYOUT__1031,
};
pub const LAYOUT__1025: &Sha0StateArm2Layout = &Sha0StateArm2Layout {
    _super: LAYOUT__1026,
    _extra0: LAYOUT__988,
    _extra1: LAYOUT__989,
    _extra2: LAYOUT__990,
    _extra3: LAYOUT__991,
    _extra4: LAYOUT__992,
    _extra5: LAYOUT__993,
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
pub const LAYOUT__1038: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__981,
};
pub const LAYOUT__1037: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1038,
    low_carry: LAYOUT__1029,
    high_carry: LAYOUT__1030,
};
pub const LAYOUT__1039: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1028,
    low_carry: LAYOUT__1033,
    high_carry: LAYOUT__1034,
};
pub const LAYOUT__1041: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1042: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1040: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1032,
    low_carry: LAYOUT__1041,
    high_carry: LAYOUT__1042,
};
pub const LAYOUT__1036: &ShaMixLayout = &ShaMixLayout {
    _super: LAYOUT__978,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
    },
    k: LAYOUT__998,
    w_bits: LAYOUT__1037,
    a: LAYOUT__1039,
    e: LAYOUT__1040,
};
pub const LAYOUT__1035: &Sha0StateArm3Layout = &Sha0StateArm3Layout {
    _super: LAYOUT__1036,
    _extra0: LAYOUT__986,
    _extra1: LAYOUT__987,
    _extra2: LAYOUT__988,
    _extra3: LAYOUT__989,
    _extra4: LAYOUT__990,
    _extra5: LAYOUT__991,
    _extra6: LAYOUT__992,
    _extra7: LAYOUT__993,
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
pub const LAYOUT__1046: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1047: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1045: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1028,
    low_carry: LAYOUT__1046,
    high_carry: LAYOUT__1047,
};
pub const LAYOUT__1049: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1050: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1048: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1032,
    low_carry: LAYOUT__1049,
    high_carry: LAYOUT__1050,
};
pub const LAYOUT__1051: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__999,
    _0: LAYOUT__1000,
};
pub const LAYOUT__1052: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1004,
    _0: LAYOUT__1005,
};
pub const LAYOUT__1044: &ShaStoreStateLayout = &ShaStoreStateLayout {
    _super: LAYOUT__978,
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
    a: LAYOUT__1045,
    e: LAYOUT__1048,
    _1: LAYOUT__1051,
    _2: LAYOUT__1052,
};
pub const LAYOUT__1043: &Sha0StateArm4Layout = &Sha0StateArm4Layout {
    _super: LAYOUT__1044,
    _extra0: LAYOUT__988,
    _extra1: LAYOUT__989,
    _extra2: LAYOUT__990,
    _extra3: LAYOUT__991,
    _extra4: LAYOUT__992,
    _extra5: LAYOUT__993,
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
pub const LAYOUT__1053: &Sha0StateArm5Layout = &Sha0StateArm5Layout {
    _super: LAYOUT__978,
    _extra0: LAYOUT__984,
    _extra1: LAYOUT__985,
    _extra2: LAYOUT__986,
    _extra3: LAYOUT__987,
    _extra4: LAYOUT__988,
    _extra5: LAYOUT__989,
    _extra6: LAYOUT__990,
    _extra7: LAYOUT__991,
    _extra8: LAYOUT__992,
    _extra9: LAYOUT__993,
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
pub const LAYOUT__1054: &Sha0StateArm6Layout = &Sha0StateArm6Layout {
    _super: LAYOUT__978,
    _extra0: LAYOUT__984,
    _extra1: LAYOUT__985,
    _extra2: LAYOUT__986,
    _extra3: LAYOUT__987,
    _extra4: LAYOUT__988,
    _extra5: LAYOUT__989,
    _extra6: LAYOUT__990,
    _extra7: LAYOUT__991,
    _extra8: LAYOUT__992,
    _extra9: LAYOUT__993,
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
pub const LAYOUT__1055: &Sha0StateArm7Layout = &Sha0StateArm7Layout {
    _super: LAYOUT__978,
    _extra0: LAYOUT__984,
    _extra1: LAYOUT__985,
    _extra2: LAYOUT__986,
    _extra3: LAYOUT__987,
    _extra4: LAYOUT__988,
    _extra5: LAYOUT__989,
    _extra6: LAYOUT__990,
    _extra7: LAYOUT__991,
    _extra8: LAYOUT__992,
    _extra9: LAYOUT__993,
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
pub const LAYOUT__995: &Sha0StateLayout = &Sha0StateLayout {
    _super: LAYOUT__978,
    arm0: LAYOUT__996,
    arm1: LAYOUT__1021,
    arm2: LAYOUT__1025,
    arm3: LAYOUT__1035,
    arm4: LAYOUT__1043,
    arm5: LAYOUT__1053,
    arm6: LAYOUT__1054,
    arm7: LAYOUT__1055,
};
pub const LAYOUT__976: &Sha0Layout = &Sha0Layout {
    _0: LAYOUT__977,
    state: LAYOUT__978,
    _arguments_sha0_state: LAYOUT__982,
    state_redef: LAYOUT__995,
};
pub const LAYOUT__1057: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__1059: &NondetRegLayout16LayoutArray = &[
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
pub const LAYOUT__1058: &BigIntStateLayout = &BigIntStateLayout {
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
    bytes: LAYOUT__1059,
    next_state: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
};
pub const LAYOUT__1062: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1063: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1064: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1065: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1066: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1067: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1068: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1069: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1070: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1071: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1072: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1073: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__1061: &MemoryArgLayout12LayoutArray = &[
    LAYOUT__1062,
    LAYOUT__1063,
    LAYOUT__1064,
    LAYOUT__1065,
    LAYOUT__1066,
    LAYOUT__1067,
    LAYOUT__1068,
    LAYOUT__1069,
    LAYOUT__1070,
    LAYOUT__1071,
    LAYOUT__1072,
    LAYOUT__1073,
];
pub const LAYOUT__1074: &CycleArgLayout6LayoutArray = &[
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
pub const LAYOUT__1075: &ArgU8Layout18LayoutArray = &[
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
pub const LAYOUT__1076: &ArgU16Layout4LayoutArray = &[
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
pub const LAYOUT__1060: &_Arguments_BigInt0StateLayout = &_Arguments_BigInt0StateLayout {
    memory_arg: LAYOUT__1061,
    cycle_arg: LAYOUT__1074,
    arg_u8: LAYOUT__1075,
    arg_u16: LAYOUT__1076,
};
pub const LAYOUT__1081: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1062,
    new_txn: LAYOUT__1063,
};
pub const LAYOUT__1080: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1081,
    _0: LAYOUT__500,
};
pub const LAYOUT__1084: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1064,
    new_txn: LAYOUT__1065,
};
pub const LAYOUT__1083: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1084,
    _0: LAYOUT__504,
};
pub const LAYOUT__1082: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__1083,
};
pub const LAYOUT__1079: &BigIntEcallLayout = &BigIntEcallLayout {
    _super: LAYOUT__1058,
    mode: LAYOUT__1080,
    pc: LAYOUT__1082,
};
pub const LAYOUT__1078: &BigInt0StateArm0Layout = &BigInt0StateArm0Layout {
    _super: LAYOUT__1079,
    _extra0: LAYOUT__1066,
    _extra1: LAYOUT__1067,
    _extra2: LAYOUT__1068,
    _extra3: LAYOUT__1069,
    _extra4: LAYOUT__1070,
    _extra5: LAYOUT__1071,
    _extra6: LAYOUT__1072,
    _extra7: LAYOUT__1073,
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
pub const LAYOUT__1087: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
};
pub const LAYOUT__1088: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__1086: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1087,
    byte1: LAYOUT__1088,
};
pub const LAYOUT__1089: &NondetRegLayout5LayoutArray = &[
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
pub const LAYOUT__1091: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
};
pub const LAYOUT__1092: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
};
pub const LAYOUT__1090: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__1091,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
    high16: LAYOUT__1092,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
};
pub const LAYOUT__1093: &OneHot_3_Layout = &OneHot_3_Layout {
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
pub const LAYOUT__1095: &ArgU16Layout2LayoutArray = &[
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
pub const LAYOUT__1096: &ArgU8Layout16LayoutArray = &[
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
pub const LAYOUT__1097: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__1066,
    LAYOUT__1067,
    LAYOUT__1068,
    LAYOUT__1069,
    LAYOUT__1070,
    LAYOUT__1071,
    LAYOUT__1072,
    LAYOUT__1073,
];
pub const LAYOUT__1098: &CycleArgLayout4LayoutArray = &[
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
pub const LAYOUT__1094: &_Arguments_BigIntStepBytesLayout = &_Arguments_BigIntStepBytesLayout {
    arg_u16: LAYOUT__1095,
    arg_u8: LAYOUT__1096,
    memory_arg: LAYOUT__1097,
    cycle_arg: LAYOUT__1098,
};
pub const LAYOUT__1103: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
};
pub const LAYOUT__1104: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__1102: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    upper_diff: LAYOUT__1103,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    med14: LAYOUT__1104,
};
pub const LAYOUT__1101: &BigIntAddrLayout = &BigIntAddrLayout {
    _super: LAYOUT__1102,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__1109: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
};
pub const LAYOUT__1110: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__1108: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1109,
    byte1: LAYOUT__1110,
};
pub const LAYOUT__1112: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
};
pub const LAYOUT__1113: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
};
pub const LAYOUT__1111: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1112,
    byte1: LAYOUT__1113,
};
pub const LAYOUT__1107: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1108,
    high: LAYOUT__1111,
};
pub const LAYOUT__1115: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1066,
    new_txn: LAYOUT__1067,
};
pub const LAYOUT__1114: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1115,
    _0: LAYOUT__508,
};
pub const LAYOUT__1106: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1107,
    _0: LAYOUT__1114,
};
pub const LAYOUT__1119: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
};
pub const LAYOUT__1120: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
};
pub const LAYOUT__1118: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1119,
    byte1: LAYOUT__1120,
};
pub const LAYOUT__1122: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
};
pub const LAYOUT__1123: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
};
pub const LAYOUT__1121: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1122,
    byte1: LAYOUT__1123,
};
pub const LAYOUT__1117: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1118,
    high: LAYOUT__1121,
};
pub const LAYOUT__1125: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1068,
    new_txn: LAYOUT__1069,
};
pub const LAYOUT__1124: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1125,
    _0: LAYOUT__512,
};
pub const LAYOUT__1116: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1117,
    _0: LAYOUT__1124,
};
pub const LAYOUT__1129: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__1130: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
};
pub const LAYOUT__1128: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1129,
    byte1: LAYOUT__1130,
};
pub const LAYOUT__1132: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
};
pub const LAYOUT__1133: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__1131: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1132,
    byte1: LAYOUT__1133,
};
pub const LAYOUT__1127: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1128,
    high: LAYOUT__1131,
};
pub const LAYOUT__1135: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1070,
    new_txn: LAYOUT__1071,
};
pub const LAYOUT__1134: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1135,
    _0: LAYOUT__516,
};
pub const LAYOUT__1126: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1127,
    _0: LAYOUT__1134,
};
pub const LAYOUT__1139: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__1140: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
};
pub const LAYOUT__1138: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1139,
    byte1: LAYOUT__1140,
};
pub const LAYOUT__1142: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
};
pub const LAYOUT__1143: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
};
pub const LAYOUT__1141: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__1142,
    byte1: LAYOUT__1143,
};
pub const LAYOUT__1137: &SplitU32Layout = &SplitU32Layout {
    low: LAYOUT__1138,
    high: LAYOUT__1141,
};
pub const LAYOUT__1145: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__1072,
    new_txn: LAYOUT__1073,
};
pub const LAYOUT__1144: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__1145,
    _0: LAYOUT__520,
};
pub const LAYOUT__1136: &BigIntReadWords_SuperLayout = &BigIntReadWords_SuperLayout {
    _super: LAYOUT__1137,
    _0: LAYOUT__1144,
};
pub const LAYOUT__1105: &BigIntReadWords_SuperLayout4LayoutArray =
    &[LAYOUT__1106, LAYOUT__1116, LAYOUT__1126, LAYOUT__1136];
pub const LAYOUT__1100: &BigIntReadLayout = &BigIntReadLayout {
    addr: LAYOUT__1101,
    words: LAYOUT__1105,
};
pub const LAYOUT__1148: &NondetU8RegLayout16LayoutArray = &[
    LAYOUT__1109,
    LAYOUT__1110,
    LAYOUT__1112,
    LAYOUT__1113,
    LAYOUT__1119,
    LAYOUT__1120,
    LAYOUT__1122,
    LAYOUT__1123,
    LAYOUT__1129,
    LAYOUT__1130,
    LAYOUT__1132,
    LAYOUT__1133,
    LAYOUT__1139,
    LAYOUT__1140,
    LAYOUT__1142,
    LAYOUT__1143,
];
pub const LAYOUT__1147: &BigIntWitnessLayout = &BigIntWitnessLayout {
    _super: LAYOUT__1148,
};
pub const LAYOUT__1151: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1115,
    _0: LAYOUT__508,
};
pub const LAYOUT__1150: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1151 };
pub const LAYOUT__1153: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1125,
    _0: LAYOUT__512,
};
pub const LAYOUT__1152: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1153 };
pub const LAYOUT__1155: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1135,
    _0: LAYOUT__516,
};
pub const LAYOUT__1154: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1155 };
pub const LAYOUT__1157: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__1145,
    _0: LAYOUT__520,
};
pub const LAYOUT__1156: &BigIntWrite__0_SuperLayout =
    &BigIntWrite__0_SuperLayout { _0: LAYOUT__1157 };
pub const LAYOUT__1149: &BigIntWrite__0_SuperLayout4LayoutArray =
    &[LAYOUT__1150, LAYOUT__1152, LAYOUT__1154, LAYOUT__1156];
pub const LAYOUT__1146: &BigIntWriteLayout = &BigIntWriteLayout {
    _super: LAYOUT__1147,
    addr: LAYOUT__1101,
    _1: LAYOUT__1149,
};
pub const LAYOUT__1158: &BigIntStepBytesArm2Layout = &BigIntStepBytesArm2Layout {
    _super: LAYOUT__1147,
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
    _extra2: LAYOUT__1066,
    _extra3: LAYOUT__1067,
    _extra4: LAYOUT__1068,
    _extra5: LAYOUT__1069,
    _extra6: LAYOUT__1070,
    _extra7: LAYOUT__1071,
    _extra8: LAYOUT__1072,
    _extra9: LAYOUT__1073,
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
pub const LAYOUT__1099: &BigIntStepBytesLayout = &BigIntStepBytesLayout {
    arm0: LAYOUT__1100,
    arm1: LAYOUT__1146,
    arm2: LAYOUT__1158,
};
pub const LAYOUT__1085: &BigIntStepLayout = &BigIntStepLayout {
    _super: LAYOUT__1058,
    load_inst_0: LAYOUT__1080,
    inst_high: LAYOUT__1086,
    poly_op: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
    mem_op: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
    reg_bits: LAYOUT__1089,
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
    base_addr_u32: LAYOUT__1083,
    data_addr_u32: LAYOUT__1090,
    mem_op_one_hot: LAYOUT__1093,
    _arguments_big_int_step_bytes: LAYOUT__1094,
    bytes: LAYOUT__1099,
    _2: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
};
pub const LAYOUT__1159: &BigInt0StateArm2Layout = &BigInt0StateArm2Layout {
    _super: LAYOUT__1058,
    _extra0: LAYOUT__1062,
    _extra1: LAYOUT__1063,
    _extra2: LAYOUT__1064,
    _extra3: LAYOUT__1065,
    _extra4: LAYOUT__1066,
    _extra5: LAYOUT__1067,
    _extra6: LAYOUT__1068,
    _extra7: LAYOUT__1069,
    _extra8: LAYOUT__1070,
    _extra9: LAYOUT__1071,
    _extra10: LAYOUT__1072,
    _extra11: LAYOUT__1073,
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
pub const LAYOUT__1160: &BigInt0StateArm3Layout = &BigInt0StateArm3Layout {
    _super: LAYOUT__1058,
    _extra0: LAYOUT__1062,
    _extra1: LAYOUT__1063,
    _extra2: LAYOUT__1064,
    _extra3: LAYOUT__1065,
    _extra4: LAYOUT__1066,
    _extra5: LAYOUT__1067,
    _extra6: LAYOUT__1068,
    _extra7: LAYOUT__1069,
    _extra8: LAYOUT__1070,
    _extra9: LAYOUT__1071,
    _extra10: LAYOUT__1072,
    _extra11: LAYOUT__1073,
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
pub const LAYOUT__1161: &BigInt0StateArm4Layout = &BigInt0StateArm4Layout {
    _super: LAYOUT__1058,
    _extra0: LAYOUT__1062,
    _extra1: LAYOUT__1063,
    _extra2: LAYOUT__1064,
    _extra3: LAYOUT__1065,
    _extra4: LAYOUT__1066,
    _extra5: LAYOUT__1067,
    _extra6: LAYOUT__1068,
    _extra7: LAYOUT__1069,
    _extra8: LAYOUT__1070,
    _extra9: LAYOUT__1071,
    _extra10: LAYOUT__1072,
    _extra11: LAYOUT__1073,
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
pub const LAYOUT__1162: &BigInt0StateArm5Layout = &BigInt0StateArm5Layout {
    _super: LAYOUT__1058,
    _extra0: LAYOUT__1062,
    _extra1: LAYOUT__1063,
    _extra2: LAYOUT__1064,
    _extra3: LAYOUT__1065,
    _extra4: LAYOUT__1066,
    _extra5: LAYOUT__1067,
    _extra6: LAYOUT__1068,
    _extra7: LAYOUT__1069,
    _extra8: LAYOUT__1070,
    _extra9: LAYOUT__1071,
    _extra10: LAYOUT__1072,
    _extra11: LAYOUT__1073,
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
pub const LAYOUT__1163: &BigInt0StateArm6Layout = &BigInt0StateArm6Layout {
    _super: LAYOUT__1058,
    _extra0: LAYOUT__1062,
    _extra1: LAYOUT__1063,
    _extra2: LAYOUT__1064,
    _extra3: LAYOUT__1065,
    _extra4: LAYOUT__1066,
    _extra5: LAYOUT__1067,
    _extra6: LAYOUT__1068,
    _extra7: LAYOUT__1069,
    _extra8: LAYOUT__1070,
    _extra9: LAYOUT__1071,
    _extra10: LAYOUT__1072,
    _extra11: LAYOUT__1073,
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
pub const LAYOUT__1164: &BigInt0StateArm7Layout = &BigInt0StateArm7Layout {
    _super: LAYOUT__1058,
    _extra0: LAYOUT__1062,
    _extra1: LAYOUT__1063,
    _extra2: LAYOUT__1064,
    _extra3: LAYOUT__1065,
    _extra4: LAYOUT__1066,
    _extra5: LAYOUT__1067,
    _extra6: LAYOUT__1068,
    _extra7: LAYOUT__1069,
    _extra8: LAYOUT__1070,
    _extra9: LAYOUT__1071,
    _extra10: LAYOUT__1072,
    _extra11: LAYOUT__1073,
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
pub const LAYOUT__1077: &BigInt0StateLayout = &BigInt0StateLayout {
    _super: LAYOUT__1058,
    arm0: LAYOUT__1078,
    arm1: LAYOUT__1085,
    arm2: LAYOUT__1159,
    arm3: LAYOUT__1160,
    arm4: LAYOUT__1161,
    arm5: LAYOUT__1162,
    arm6: LAYOUT__1163,
    arm7: LAYOUT__1164,
};
pub const LAYOUT__1056: &BigInt0Layout = &BigInt0Layout {
    _0: LAYOUT__1057,
    state: LAYOUT__1058,
    _arguments_big_int0_state: LAYOUT__1060,
    state_redef: LAYOUT__1077,
};
pub const LAYOUT__13: &TopInstResultLayout = &TopInstResultLayout {
    _selector: LAYOUT__12,
    arm0: LAYOUT__14,
    arm1: LAYOUT__95,
    arm2: LAYOUT__113,
    arm3: LAYOUT__126,
    arm4: LAYOUT__210,
    arm5: LAYOUT__337,
    arm6: LAYOUT__397,
    arm7: LAYOUT__440,
    arm8: LAYOUT__612,
    arm9: LAYOUT__677,
    arm10: LAYOUT__943,
    arm11: LAYOUT__976,
    arm12: LAYOUT__1056,
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
pub const LAYOUT__1166: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1165: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1166,
};
pub const LAYOUT__1168: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1167: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1168,
};
pub const LAYOUT__1170: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1169: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1170,
};
pub const LAYOUT__1172: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1171: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1172,
};
pub const LAYOUT__1174: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1173: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1174,
};
pub const LAYOUT__1175: &_accumLayout = &_accumLayout {
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
    input: LAYOUT__1165,
    is_terminate: &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    output: LAYOUT__1167,
    povw_nonce: LAYOUT__1169,
    rng: &NondetExtRegLayout {
        _super: &Reg { offset: 49 },
    },
    shutdown_cycle: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    state_in: LAYOUT__1171,
    state_out: LAYOUT__1173,
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
    randomness: LAYOUT__1175,
};
