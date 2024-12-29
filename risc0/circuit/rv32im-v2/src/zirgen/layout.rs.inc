pub const LAYOUT__3: &NondetRegLayout8LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 20 },
    },
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
];
pub const LAYOUT__2: &OneHot_8_Layout = &OneHot_8_Layout { _super: LAYOUT__3 };
pub const LAYOUT__1: &InstInputLayout = &InstInputLayout {
    minor_onehot: LAYOUT__2,
};
pub const LAYOUT__5: &NondetRegLayout12LayoutArray = &[
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
];
pub const LAYOUT__4: &OneHot_12_Layout = &OneHot_12_Layout { _super: LAYOUT__5 };
pub const LAYOUT__10: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
    },
};
pub const LAYOUT__11: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
};
pub const LAYOUT__9: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__10,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
    high16: LAYOUT__11,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
};
pub const LAYOUT__13: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
    },
};
pub const LAYOUT__14: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
};
pub const LAYOUT__12: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__13,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    high16: LAYOUT__14,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
};
pub const LAYOUT__18: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 55 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 56 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
};
pub const LAYOUT__19: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 58 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 59 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 60 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 61 },
    },
};
pub const LAYOUT__17: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__18,
    new_txn: LAYOUT__19,
};
pub const LAYOUT__21: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
    },
};
pub const LAYOUT__20: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__21 };
pub const LAYOUT__16: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__17,
    _0: LAYOUT__20,
};
pub const LAYOUT__15: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    _0: LAYOUT__16,
};
pub const LAYOUT__8: &FinalizeMiscLayout = &FinalizeMiscLayout {
    write_data: LAYOUT__9,
    pc_norm: LAYOUT__12,
    _0: LAYOUT__15,
};
pub const LAYOUT__22: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
};
pub const LAYOUT__25: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
};
pub const LAYOUT__27: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
};
pub const LAYOUT__28: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
    },
};
pub const LAYOUT__26: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    upper_diff: LAYOUT__27,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
    med14: LAYOUT__28,
};
pub const LAYOUT__31: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 91 },
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
pub const LAYOUT__32: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 91 },
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
pub const LAYOUT__30: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__31,
    new_txn: LAYOUT__32,
};
pub const LAYOUT__34: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
};
pub const LAYOUT__33: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__34 };
pub const LAYOUT__29: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__30,
    _0: LAYOUT__33,
};
pub const LAYOUT__24: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__25,
    pc_addr: LAYOUT__26,
    load_inst: LAYOUT__29,
};
pub const LAYOUT__38: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
};
pub const LAYOUT__39: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
};
pub const LAYOUT__37: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__38,
    new_txn: LAYOUT__39,
};
pub const LAYOUT__41: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__40: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__41 };
pub const LAYOUT__36: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__37,
    _0: LAYOUT__40,
};
pub const LAYOUT__35: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__36,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
};
pub const LAYOUT__45: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__46: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__44: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__45,
    new_txn: LAYOUT__46,
};
pub const LAYOUT__48: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 124 },
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
        _super: &Reg { offset: 125 },
    },
};
pub const LAYOUT__23: &MiscInputLayout = &MiscInputLayout {
    decoded: LAYOUT__24,
    rs1: LAYOUT__35,
    rs2: LAYOUT__42,
};
pub const LAYOUT__50: &ArgU16Layout5LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
];
pub const LAYOUT__49: &_Arguments_Misc0MiscOutputLayout = &_Arguments_Misc0MiscOutputLayout {
    arg_u16: LAYOUT__50,
};
pub const LAYOUT__52: &Misc0MiscOutputArm0Layout = &Misc0MiscOutputArm0Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__53: &Misc0MiscOutputArm1Layout = &Misc0MiscOutputArm1Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__60: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__59: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__60 };
pub const LAYOUT__62: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__61: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__62 };
pub const LAYOUT__58: &BitwiseAndU16Layout = &BitwiseAndU16Layout {
    bits_x: LAYOUT__59,
    bits_y: LAYOUT__61,
};
pub const LAYOUT__65: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__64: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__65 };
pub const LAYOUT__67: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__66: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__67 };
pub const LAYOUT__63: &BitwiseAndU16Layout = &BitwiseAndU16Layout {
    bits_x: LAYOUT__64,
    bits_y: LAYOUT__66,
};
pub const LAYOUT__57: &BitwiseAndLayout = &BitwiseAndLayout {
    _0: LAYOUT__58,
    _1: LAYOUT__63,
};
pub const LAYOUT__56: &BitwiseXorLayout = &BitwiseXorLayout { and_xy: LAYOUT__57 };
pub const LAYOUT__55: &OpXORLayout = &OpXORLayout { _0: LAYOUT__56 };
pub const LAYOUT__54: &Misc0MiscOutputArm2Layout = &Misc0MiscOutputArm2Layout {
    _super: LAYOUT__55,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__70: &BitwiseOrLayout = &BitwiseOrLayout { and_xy: LAYOUT__57 };
pub const LAYOUT__69: &OpORLayout = &OpORLayout { _0: LAYOUT__70 };
pub const LAYOUT__68: &Misc0MiscOutputArm3Layout = &Misc0MiscOutputArm3Layout {
    _super: LAYOUT__69,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__72: &OpANDLayout = &OpANDLayout { _0: LAYOUT__57 };
pub const LAYOUT__71: &Misc0MiscOutputArm4Layout = &Misc0MiscOutputArm4Layout {
    _super: LAYOUT__72,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__76: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
};
pub const LAYOUT__77: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
};
pub const LAYOUT__75: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__76,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
    high16: LAYOUT__77,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
};
pub const LAYOUT__79: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
};
pub const LAYOUT__78: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
    rest_times_two: LAYOUT__79,
};
pub const LAYOUT__81: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__80: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    rest_times_two: LAYOUT__81,
};
pub const LAYOUT__83: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__82: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    rest_times_two: LAYOUT__83,
};
pub const LAYOUT__74: &CmpLessThanLayout = &CmpLessThanLayout {
    diff: LAYOUT__75,
    s1: LAYOUT__78,
    s2: LAYOUT__80,
    s3: LAYOUT__82,
    overflow: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    is_less_than: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
};
pub const LAYOUT__73: &OpSLTLayout = &OpSLTLayout { cmp: LAYOUT__74 };
pub const LAYOUT__86: &CmpLessThanUnsignedLayout = &CmpLessThanUnsignedLayout { diff: LAYOUT__75 };
pub const LAYOUT__85: &OpSLTULayout = &OpSLTULayout { cmp: LAYOUT__86 };
pub const LAYOUT__84: &Misc0MiscOutputArm6Layout = &Misc0MiscOutputArm6Layout {
    _super: LAYOUT__85,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__87: &Misc0MiscOutputArm7Layout = &Misc0MiscOutputArm7Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__51: &Misc0MiscOutputLayout = &Misc0MiscOutputLayout {
    arm0: LAYOUT__52,
    arm1: LAYOUT__53,
    arm2: LAYOUT__54,
    arm3: LAYOUT__68,
    arm4: LAYOUT__71,
    arm5: LAYOUT__73,
    arm6: LAYOUT__84,
    arm7: LAYOUT__87,
};
pub const LAYOUT__7: &Misc0Layout = &Misc0Layout {
    _super: LAYOUT__8,
    _0: LAYOUT__22,
    input: LAYOUT__23,
    _arguments_misc0_misc_output: LAYOUT__49,
    misc_output: LAYOUT__51,
};
pub const LAYOUT__89: &_Arguments_Misc1MiscOutputLayout = &_Arguments_Misc1MiscOutputLayout {
    arg_u16: LAYOUT__50,
};
pub const LAYOUT__92: &OpXORILayout = &OpXORILayout { _0: LAYOUT__56 };
pub const LAYOUT__91: &Misc1MiscOutputArm0Layout = &Misc1MiscOutputArm0Layout {
    _super: LAYOUT__92,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__94: &OpORILayout = &OpORILayout { _0: LAYOUT__70 };
pub const LAYOUT__93: &Misc1MiscOutputArm1Layout = &Misc1MiscOutputArm1Layout {
    _super: LAYOUT__94,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__96: &OpANDILayout = &OpANDILayout { _0: LAYOUT__57 };
pub const LAYOUT__95: &Misc1MiscOutputArm2Layout = &Misc1MiscOutputArm2Layout {
    _super: LAYOUT__96,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__97: &OpSLTILayout = &OpSLTILayout { cmp: LAYOUT__74 };
pub const LAYOUT__99: &OpSLTIULayout = &OpSLTIULayout { cmp: LAYOUT__86 };
pub const LAYOUT__98: &Misc1MiscOutputArm4Layout = &Misc1MiscOutputArm4Layout {
    _super: LAYOUT__99,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__102: &CmpEqualLayout = &CmpEqualLayout {
    low_same: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
    high_same: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    is_equal: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
};
pub const LAYOUT__101: &OpBEQLayout = &OpBEQLayout { cmp: LAYOUT__102 };
pub const LAYOUT__100: &Misc1MiscOutputArm5Layout = &Misc1MiscOutputArm5Layout {
    _super: LAYOUT__101,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__104: &OpBNELayout = &OpBNELayout { cmp: LAYOUT__102 };
pub const LAYOUT__103: &Misc1MiscOutputArm6Layout = &Misc1MiscOutputArm6Layout {
    _super: LAYOUT__104,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__105: &OpBLTLayout = &OpBLTLayout { cmp: LAYOUT__74 };
pub const LAYOUT__90: &Misc1MiscOutputLayout = &Misc1MiscOutputLayout {
    arm0: LAYOUT__91,
    arm1: LAYOUT__93,
    arm2: LAYOUT__95,
    arm3: LAYOUT__97,
    arm4: LAYOUT__98,
    arm5: LAYOUT__100,
    arm6: LAYOUT__103,
    arm7: LAYOUT__105,
};
pub const LAYOUT__88: &Misc1Layout = &Misc1Layout {
    _super: LAYOUT__8,
    _0: LAYOUT__22,
    input: LAYOUT__23,
    _arguments_misc1_misc_output: LAYOUT__89,
    misc_output: LAYOUT__90,
};
pub const LAYOUT__107: &_Arguments_Misc2MiscOutputLayout = &_Arguments_Misc2MiscOutputLayout {
    arg_u16: LAYOUT__50,
};
pub const LAYOUT__109: &OpBGELayout = &OpBGELayout { cmp: LAYOUT__74 };
pub const LAYOUT__111: &OpBLTULayout = &OpBLTULayout { cmp: LAYOUT__86 };
pub const LAYOUT__110: &Misc2MiscOutputArm1Layout = &Misc2MiscOutputArm1Layout {
    _super: LAYOUT__111,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__113: &OpBGEULayout = &OpBGEULayout { cmp: LAYOUT__86 };
pub const LAYOUT__112: &Misc2MiscOutputArm2Layout = &Misc2MiscOutputArm2Layout {
    _super: LAYOUT__113,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__114: &Misc2MiscOutputArm3Layout = &Misc2MiscOutputArm3Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__115: &Misc2MiscOutputArm4Layout = &Misc2MiscOutputArm4Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__116: &Misc2MiscOutputArm5Layout = &Misc2MiscOutputArm5Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__117: &Misc2MiscOutputArm6Layout = &Misc2MiscOutputArm6Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__118: &Misc2MiscOutputArm7Layout = &Misc2MiscOutputArm7Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
};
pub const LAYOUT__108: &Misc2MiscOutputLayout = &Misc2MiscOutputLayout {
    arm0: LAYOUT__109,
    arm1: LAYOUT__110,
    arm2: LAYOUT__112,
    arm3: LAYOUT__114,
    arm4: LAYOUT__115,
    arm5: LAYOUT__116,
    arm6: LAYOUT__117,
    arm7: LAYOUT__118,
};
pub const LAYOUT__106: &Misc2Layout = &Misc2Layout {
    _super: LAYOUT__8,
    _0: LAYOUT__22,
    input: LAYOUT__23,
    _arguments_misc2_misc_output: LAYOUT__107,
    misc_output: LAYOUT__108,
};
pub const LAYOUT__120: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
};
pub const LAYOUT__123: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
};
pub const LAYOUT__125: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__126: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
};
pub const LAYOUT__124: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    upper_diff: LAYOUT__125,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
    },
    med14: LAYOUT__126,
};
pub const LAYOUT__129: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
};
pub const LAYOUT__130: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
};
pub const LAYOUT__128: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__129,
    new_txn: LAYOUT__130,
};
pub const LAYOUT__132: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__131: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__132 };
pub const LAYOUT__127: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__128,
    _0: LAYOUT__131,
};
pub const LAYOUT__122: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__123,
    pc_addr: LAYOUT__124,
    load_inst: LAYOUT__127,
};
pub const LAYOUT__136: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 104 },
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
pub const LAYOUT__137: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 104 },
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
pub const LAYOUT__135: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__136,
    new_txn: LAYOUT__137,
};
pub const LAYOUT__139: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
};
pub const LAYOUT__138: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__139 };
pub const LAYOUT__134: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__135,
    _0: LAYOUT__138,
};
pub const LAYOUT__133: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__134,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
};
pub const LAYOUT__143: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__144: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__142: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__143,
    new_txn: LAYOUT__144,
};
pub const LAYOUT__146: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 126 },
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
        _super: &Reg { offset: 127 },
    },
};
pub const LAYOUT__121: &MulInputLayout = &MulInputLayout {
    decoded: LAYOUT__122,
    rs1: LAYOUT__133,
    rs2: LAYOUT__140,
};
pub const LAYOUT__148: &ArgU16Layout6LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
    },
];
pub const LAYOUT__149: &ArgU8Layout13LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
];
pub const LAYOUT__147: &_Arguments_Mul0MulOutputLayout = &_Arguments_Mul0MulOutputLayout {
    arg_u16: LAYOUT__148,
    arg_u8: LAYOUT__149,
};
pub const LAYOUT__154: &NondetRegLayout5LayoutArray = &[
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
];
pub const LAYOUT__153: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__154,
};
pub const LAYOUT__152: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__153,
    check_u16: LAYOUT__76,
    b3: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
    low: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
    high: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
};
pub const LAYOUT__158: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
    },
};
pub const LAYOUT__159: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
    },
};
pub const LAYOUT__160: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
    },
};
pub const LAYOUT__161: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
    },
};
pub const LAYOUT__162: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
    },
};
pub const LAYOUT__157: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__158,
    b1: LAYOUT__159,
    b2: LAYOUT__160,
    b3: LAYOUT__161,
    b3_top7times2: LAYOUT__162,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
};
pub const LAYOUT__164: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
    },
};
pub const LAYOUT__165: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
    },
};
pub const LAYOUT__166: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
    },
};
pub const LAYOUT__167: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
};
pub const LAYOUT__168: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__163: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__164,
    b1: LAYOUT__165,
    b2: LAYOUT__166,
    b3: LAYOUT__167,
    b3_top7times2: LAYOUT__168,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
};
pub const LAYOUT__170: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
    },
};
pub const LAYOUT__169: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__79,
    carry_byte: LAYOUT__170,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
};
pub const LAYOUT__172: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
    },
};
pub const LAYOUT__171: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__81,
    carry_byte: LAYOUT__172,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
};
pub const LAYOUT__174: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
};
pub const LAYOUT__173: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__83,
    carry_byte: LAYOUT__174,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__156: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__157,
    bx: LAYOUT__163,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
    c_rest_times2: LAYOUT__77,
    s0: LAYOUT__169,
    s1: LAYOUT__171,
    s2: LAYOUT__173,
    s3_out: LAYOUT__10,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__155: &DoMulLayout = &DoMulLayout { mul: LAYOUT__156 };
pub const LAYOUT__151: &OpSLLLayout = &OpSLLLayout {
    shift_mul: LAYOUT__152,
    _0: LAYOUT__155,
};
pub const LAYOUT__175: &OpSLLILayout = &OpSLLILayout {
    shift_mul: LAYOUT__152,
    _0: LAYOUT__155,
};
pub const LAYOUT__180: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__158,
    b1: LAYOUT__159,
    b2: LAYOUT__160,
    b3: LAYOUT__161,
    b3_top7times2: LAYOUT__162,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
};
pub const LAYOUT__181: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__164,
    b1: LAYOUT__165,
    b2: LAYOUT__166,
    b3: LAYOUT__167,
    b3_top7times2: LAYOUT__168,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
};
pub const LAYOUT__182: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__77,
    carry_byte: LAYOUT__170,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
};
pub const LAYOUT__183: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__79,
    carry_byte: LAYOUT__172,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
};
pub const LAYOUT__184: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__81,
    carry_byte: LAYOUT__174,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
};
pub const LAYOUT__179: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__180,
    bx: LAYOUT__181,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    c_rest_times2: LAYOUT__76,
    s0: LAYOUT__182,
    s1: LAYOUT__183,
    s2: LAYOUT__184,
    s3_out: LAYOUT__83,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__178: &DoMulLayout = &DoMulLayout { mul: LAYOUT__179 };
pub const LAYOUT__177: &OpMULLayout = &OpMULLayout { _0: LAYOUT__178 };
pub const LAYOUT__176: &Mul0MulOutputArm2Layout = &Mul0MulOutputArm2Layout {
    _super: LAYOUT__177,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
    },
};
pub const LAYOUT__186: &OpMULHLayout = &OpMULHLayout { _0: LAYOUT__178 };
pub const LAYOUT__185: &Mul0MulOutputArm3Layout = &Mul0MulOutputArm3Layout {
    _super: LAYOUT__186,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
    },
};
pub const LAYOUT__188: &OpMULHSULayout = &OpMULHSULayout { _0: LAYOUT__178 };
pub const LAYOUT__187: &Mul0MulOutputArm4Layout = &Mul0MulOutputArm4Layout {
    _super: LAYOUT__188,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
    },
};
pub const LAYOUT__190: &OpMULHULayout = &OpMULHULayout { _0: LAYOUT__178 };
pub const LAYOUT__189: &Mul0MulOutputArm5Layout = &Mul0MulOutputArm5Layout {
    _super: LAYOUT__190,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
    },
};
pub const LAYOUT__191: &Mul0MulOutputArm6Layout = &Mul0MulOutputArm6Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
    },
    _extra6: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
    },
    _extra7: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
    },
    _extra8: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
    },
    _extra9: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
    },
    _extra14: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
    _extra15: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
};
pub const LAYOUT__192: &Mul0MulOutputArm7Layout = &Mul0MulOutputArm7Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
    },
    _extra6: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
    },
    _extra7: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
    },
    _extra8: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
    },
    _extra9: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
    },
    _extra14: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
    _extra15: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
};
pub const LAYOUT__150: &Mul0MulOutputLayout = &Mul0MulOutputLayout {
    arm0: LAYOUT__151,
    arm1: LAYOUT__175,
    arm2: LAYOUT__176,
    arm3: LAYOUT__185,
    arm4: LAYOUT__187,
    arm5: LAYOUT__189,
    arm6: LAYOUT__191,
    arm7: LAYOUT__192,
};
pub const LAYOUT__196: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 151 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 150 },
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
pub const LAYOUT__197: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 150 },
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
pub const LAYOUT__195: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__196,
    new_txn: LAYOUT__197,
};
pub const LAYOUT__199: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__198: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__199 };
pub const LAYOUT__194: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__195,
    _0: LAYOUT__198,
};
pub const LAYOUT__193: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 149 },
    },
    _0: LAYOUT__194,
};
pub const LAYOUT__201: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
};
pub const LAYOUT__202: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
};
pub const LAYOUT__200: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__201,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 163 },
    },
    high16: LAYOUT__202,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
};
pub const LAYOUT__119: &Mul0Layout = &Mul0Layout {
    _0: LAYOUT__120,
    input: LAYOUT__121,
    _arguments_mul0_mul_output: LAYOUT__147,
    mul_output: LAYOUT__150,
    _1: LAYOUT__193,
    pc_add: LAYOUT__200,
};
pub const LAYOUT__204: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__207: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
};
pub const LAYOUT__209: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
};
pub const LAYOUT__210: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__208: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    upper_diff: LAYOUT__209,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    med14: LAYOUT__210,
};
pub const LAYOUT__213: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__214: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__212: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__213,
    new_txn: LAYOUT__214,
};
pub const LAYOUT__216: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
};
pub const LAYOUT__215: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__216 };
pub const LAYOUT__211: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__212,
    _0: LAYOUT__215,
};
pub const LAYOUT__206: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__207,
    pc_addr: LAYOUT__208,
    load_inst: LAYOUT__211,
};
pub const LAYOUT__220: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__221: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__219: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__220,
    new_txn: LAYOUT__221,
};
pub const LAYOUT__223: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
};
pub const LAYOUT__222: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__223 };
pub const LAYOUT__218: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__219,
    _0: LAYOUT__222,
};
pub const LAYOUT__217: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__218,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
};
pub const LAYOUT__227: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 136 },
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
pub const LAYOUT__228: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 141 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 143 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 144 },
    },
};
pub const LAYOUT__226: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__227,
    new_txn: LAYOUT__228,
};
pub const LAYOUT__230: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
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
        _super: &Reg { offset: 147 },
    },
};
pub const LAYOUT__205: &DivInputLayout = &DivInputLayout {
    decoded: LAYOUT__206,
    rs1: LAYOUT__217,
    rs2: LAYOUT__224,
};
pub const LAYOUT__232: &ArgU16Layout16LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
];
pub const LAYOUT__233: &ArgU8Layout13LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
];
pub const LAYOUT__231: &_Arguments_Div0MulOutputLayout = &_Arguments_Div0MulOutputLayout {
    arg_u16: LAYOUT__232,
    arg_u8: LAYOUT__233,
};
pub const LAYOUT__239: &NondetRegLayout5LayoutArray = &[
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
];
pub const LAYOUT__238: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__239,
};
pub const LAYOUT__237: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__238,
    check_u16: LAYOUT__76,
    b3: &NondetRegLayout {
        _super: &Reg { offset: 153 },
    },
    low: &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
    high: &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
};
pub const LAYOUT__243: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
};
pub const LAYOUT__244: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
};
pub const LAYOUT__242: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__170,
    b1: LAYOUT__172,
    b2: LAYOUT__174,
    b3: LAYOUT__243,
    b3_top7times2: LAYOUT__244,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
};
pub const LAYOUT__246: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
};
pub const LAYOUT__247: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
};
pub const LAYOUT__248: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__249: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
};
pub const LAYOUT__250: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__245: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__246,
    b1: LAYOUT__247,
    b2: LAYOUT__248,
    b3: LAYOUT__249,
    b3_top7times2: LAYOUT__250,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
};
pub const LAYOUT__252: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
};
pub const LAYOUT__251: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__83,
    carry_byte: LAYOUT__252,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
};
pub const LAYOUT__254: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
};
pub const LAYOUT__253: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__10,
    carry_byte: LAYOUT__254,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
};
pub const LAYOUT__256: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
    },
};
pub const LAYOUT__257: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__255: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__256,
    carry_byte: LAYOUT__257,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
};
pub const LAYOUT__258: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
    },
};
pub const LAYOUT__241: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__242,
    bx: LAYOUT__245,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
    c_rest_times2: LAYOUT__81,
    s0: LAYOUT__251,
    s1: LAYOUT__253,
    s2: LAYOUT__255,
    s3_out: LAYOUT__258,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
};
pub const LAYOUT__260: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
    },
};
pub const LAYOUT__261: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
    },
};
pub const LAYOUT__259: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__260,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 173 },
    },
    high16: LAYOUT__261,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 174 },
    },
};
pub const LAYOUT__263: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
    },
};
pub const LAYOUT__264: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
    },
};
pub const LAYOUT__262: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__263,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
    high16: LAYOUT__264,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
};
pub const LAYOUT__266: &ArgU16Layout2LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
];
pub const LAYOUT__265: &_Arguments_DoDiv__1Layout = &_Arguments_DoDiv__1Layout {
    arg_u16: LAYOUT__266,
};
pub const LAYOUT__268: &DoDiv__1Arm0Layout = &DoDiv__1Arm0Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
};
pub const LAYOUT__272: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
    },
};
pub const LAYOUT__273: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
};
pub const LAYOUT__271: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__272,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 177 },
    },
    high16: LAYOUT__273,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 178 },
    },
};
pub const LAYOUT__270: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__271 };
pub const LAYOUT__269: &DoDiv__1Arm1_SuperLayout = &DoDiv__1Arm1_SuperLayout { lt: LAYOUT__270 };
pub const LAYOUT__267: &DoDiv__1Layout = &DoDiv__1Layout {
    arm0: LAYOUT__268,
    arm1: LAYOUT__269,
};
pub const LAYOUT__240: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
    rem_low: LAYOUT__77,
    rem_high: LAYOUT__79,
    mul: LAYOUT__241,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
    is_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    top_num: &NondetRegLayout {
        _super: &Reg { offset: 172 },
    },
    _0: LAYOUT__13,
    denom_abs: LAYOUT__259,
    rem_normal: LAYOUT__262,
    _arguments_do_div__1: LAYOUT__265,
    _3: LAYOUT__267,
};
pub const LAYOUT__236: &OpSRLLayout = &OpSRLLayout {
    shift_mul: LAYOUT__237,
    _0: LAYOUT__240,
};
pub const LAYOUT__235: &Div0MulOutputArm0Layout = &Div0MulOutputArm0Layout {
    _super: LAYOUT__236,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__275: &TopBitLayout = &TopBitLayout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
    rest: LAYOUT__77,
};
pub const LAYOUT__278: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__170,
    b1: LAYOUT__172,
    b2: LAYOUT__174,
    b3: LAYOUT__243,
    b3_top7times2: LAYOUT__244,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
};
pub const LAYOUT__279: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__246,
    b1: LAYOUT__247,
    b2: LAYOUT__248,
    b3: LAYOUT__249,
    b3_top7times2: LAYOUT__250,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
};
pub const LAYOUT__280: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__10,
    carry_byte: LAYOUT__252,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
};
pub const LAYOUT__281: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__256,
    carry_byte: LAYOUT__254,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
};
pub const LAYOUT__282: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__258,
    carry_byte: LAYOUT__257,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
};
pub const LAYOUT__277: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__278,
    bx: LAYOUT__279,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 161 },
    },
    c_rest_times2: LAYOUT__83,
    s0: LAYOUT__280,
    s1: LAYOUT__281,
    s2: LAYOUT__282,
    s3_out: LAYOUT__13,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
};
pub const LAYOUT__283: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__261,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 174 },
    },
    high16: LAYOUT__263,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
};
pub const LAYOUT__284: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__264,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
    high16: LAYOUT__272,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 177 },
    },
};
pub const LAYOUT__286: &ArgU16Layout2LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
];
pub const LAYOUT__285: &_Arguments_DoDiv__1Layout = &_Arguments_DoDiv__1Layout {
    arg_u16: LAYOUT__286,
};
pub const LAYOUT__288: &DoDiv__1Arm0Layout = &DoDiv__1Arm0Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__292: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__291: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__273,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 178 },
    },
    high16: LAYOUT__292,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 179 },
    },
};
pub const LAYOUT__290: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__291 };
pub const LAYOUT__289: &DoDiv__1Arm1_SuperLayout = &DoDiv__1Arm1_SuperLayout { lt: LAYOUT__290 };
pub const LAYOUT__287: &DoDiv__1Layout = &DoDiv__1Layout {
    arm0: LAYOUT__288,
    arm1: LAYOUT__289,
};
pub const LAYOUT__276: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
    rem_low: LAYOUT__79,
    rem_high: LAYOUT__81,
    mul: LAYOUT__277,
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
    _0: LAYOUT__260,
    denom_abs: LAYOUT__283,
    rem_normal: LAYOUT__284,
    _arguments_do_div__1: LAYOUT__285,
    _3: LAYOUT__287,
};
pub const LAYOUT__274: &OpSRALayout = &OpSRALayout {
    shift_mul: LAYOUT__237,
    flip: LAYOUT__275,
    _0: LAYOUT__276,
};
pub const LAYOUT__294: &OpSRLILayout = &OpSRLILayout {
    shift_mul: LAYOUT__237,
    _0: LAYOUT__240,
};
pub const LAYOUT__293: &Div0MulOutputArm2Layout = &Div0MulOutputArm2Layout {
    _super: LAYOUT__294,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__295: &OpSRAILayout = &OpSRAILayout {
    shift_mul: LAYOUT__237,
    flip: LAYOUT__275,
    _0: LAYOUT__276,
};
pub const LAYOUT__300: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__170,
    b1: LAYOUT__172,
    b2: LAYOUT__174,
    b3: LAYOUT__243,
    b3_top7times2: LAYOUT__244,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 150 },
    },
};
pub const LAYOUT__301: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__246,
    b1: LAYOUT__247,
    b2: LAYOUT__248,
    b3: LAYOUT__249,
    b3_top7times2: LAYOUT__250,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 151 },
    },
};
pub const LAYOUT__302: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__81,
    carry_byte: LAYOUT__252,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
};
pub const LAYOUT__303: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__83,
    carry_byte: LAYOUT__254,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
};
pub const LAYOUT__304: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__10,
    carry_byte: LAYOUT__257,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
};
pub const LAYOUT__299: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__300,
    bx: LAYOUT__301,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 152 },
    },
    c_rest_times2: LAYOUT__79,
    s0: LAYOUT__302,
    s1: LAYOUT__303,
    s2: LAYOUT__304,
    s3_out: LAYOUT__256,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
};
pub const LAYOUT__305: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__13,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
    high16: LAYOUT__260,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
};
pub const LAYOUT__306: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__261,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 167 },
    },
    high16: LAYOUT__263,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 168 },
    },
};
pub const LAYOUT__308: &ArgU16Layout2LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
    },
];
pub const LAYOUT__307: &_Arguments_DoDiv__1Layout = &_Arguments_DoDiv__1Layout {
    arg_u16: LAYOUT__308,
};
pub const LAYOUT__310: &DoDiv__1Arm0Layout = &DoDiv__1Arm0Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
    },
};
pub const LAYOUT__313: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__264,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
    high16: LAYOUT__272,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 170 },
    },
};
pub const LAYOUT__312: &CmpLessThanUnsignedLayout =
    &CmpLessThanUnsignedLayout { diff: LAYOUT__313 };
pub const LAYOUT__311: &DoDiv__1Arm1_SuperLayout = &DoDiv__1Arm1_SuperLayout { lt: LAYOUT__312 };
pub const LAYOUT__309: &DoDiv__1Layout = &DoDiv__1Layout {
    arm0: LAYOUT__310,
    arm1: LAYOUT__311,
};
pub const LAYOUT__298: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 148 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 149 },
    },
    rem_low: LAYOUT__76,
    rem_high: LAYOUT__77,
    mul: LAYOUT__299,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 161 },
    },
    is_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    top_num: &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
    _0: LAYOUT__258,
    denom_abs: LAYOUT__305,
    rem_normal: LAYOUT__306,
    _arguments_do_div__1: LAYOUT__307,
    _3: LAYOUT__309,
};
pub const LAYOUT__297: &OpDIVLayout = &OpDIVLayout { _0: LAYOUT__298 };
pub const LAYOUT__296: &Div0MulOutputArm4Layout = &Div0MulOutputArm4Layout {
    _super: LAYOUT__297,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__315: &OpDIVULayout = &OpDIVULayout { _0: LAYOUT__298 };
pub const LAYOUT__314: &Div0MulOutputArm5Layout = &Div0MulOutputArm5Layout {
    _super: LAYOUT__315,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__317: &OpREMLayout = &OpREMLayout { _0: LAYOUT__298 };
pub const LAYOUT__316: &Div0MulOutputArm6Layout = &Div0MulOutputArm6Layout {
    _super: LAYOUT__317,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__319: &OpREMULayout = &OpREMULayout { _0: LAYOUT__298 };
pub const LAYOUT__318: &Div0MulOutputArm7Layout = &Div0MulOutputArm7Layout {
    _super: LAYOUT__319,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
};
pub const LAYOUT__234: &Div0MulOutputLayout = &Div0MulOutputLayout {
    arm0: LAYOUT__235,
    arm1: LAYOUT__274,
    arm2: LAYOUT__293,
    arm3: LAYOUT__295,
    arm4: LAYOUT__296,
    arm5: LAYOUT__314,
    arm6: LAYOUT__316,
    arm7: LAYOUT__318,
};
pub const LAYOUT__323: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 185 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 186 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 187 },
    },
};
pub const LAYOUT__324: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 188 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 189 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 190 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 191 },
    },
};
pub const LAYOUT__322: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__323,
    new_txn: LAYOUT__324,
};
pub const LAYOUT__326: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 193 },
        },
    },
};
pub const LAYOUT__325: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__326 };
pub const LAYOUT__321: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__322,
    _0: LAYOUT__325,
};
pub const LAYOUT__320: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    _0: LAYOUT__321,
};
pub const LAYOUT__328: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 194 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 195 },
        },
    },
};
pub const LAYOUT__329: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 197 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 198 },
        },
    },
};
pub const LAYOUT__327: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__328,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    high16: LAYOUT__329,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 199 },
    },
};
pub const LAYOUT__203: &Div0Layout = &Div0Layout {
    _0: LAYOUT__204,
    input: LAYOUT__205,
    _arguments_div0_mul_output: LAYOUT__231,
    mul_output: LAYOUT__234,
    _1: LAYOUT__320,
    pc_add: LAYOUT__327,
};
pub const LAYOUT__331: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
    },
};
pub const LAYOUT__334: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 51 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 55 },
    },
};
pub const LAYOUT__336: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
};
pub const LAYOUT__337: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
};
pub const LAYOUT__335: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 56 },
    },
    upper_diff: LAYOUT__336,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
    med14: LAYOUT__337,
};
pub const LAYOUT__340: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 63 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 65 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 66 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
};
pub const LAYOUT__341: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 63 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
};
pub const LAYOUT__339: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__340,
    new_txn: LAYOUT__341,
};
pub const LAYOUT__343: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
};
pub const LAYOUT__342: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__343 };
pub const LAYOUT__338: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__339,
    _0: LAYOUT__342,
};
pub const LAYOUT__333: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__334,
    pc_addr: LAYOUT__335,
    load_inst: LAYOUT__338,
};
pub const LAYOUT__347: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 74 },
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
pub const LAYOUT__348: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 74 },
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
pub const LAYOUT__346: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__347,
    new_txn: LAYOUT__348,
};
pub const LAYOUT__350: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
};
pub const LAYOUT__349: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__350 };
pub const LAYOUT__345: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__346,
    _0: LAYOUT__349,
};
pub const LAYOUT__344: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__345,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
};
pub const LAYOUT__352: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
};
pub const LAYOUT__351: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__352,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    high16: LAYOUT__28,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
};
pub const LAYOUT__354: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
};
pub const LAYOUT__355: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
    },
};
pub const LAYOUT__353: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    upper_diff: LAYOUT__354,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
    },
    med14: LAYOUT__355,
};
pub const LAYOUT__358: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 100 },
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
pub const LAYOUT__359: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 100 },
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
pub const LAYOUT__357: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__358,
    new_txn: LAYOUT__359,
};
pub const LAYOUT__361: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
};
pub const LAYOUT__360: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__361 };
pub const LAYOUT__356: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__357,
    _0: LAYOUT__360,
};
pub const LAYOUT__332: &MemLoadInputLayout = &MemLoadInputLayout {
    decoded: LAYOUT__333,
    rs1: LAYOUT__344,
    addr_u32: LAYOUT__351,
    addr: LAYOUT__353,
    data_0: LAYOUT__356,
};
pub const LAYOUT__363: &ArgU8Layout3LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
];
pub const LAYOUT__362: &_Arguments_Mem0OutputLayout = &_Arguments_Mem0OutputLayout {
    arg_u8: LAYOUT__363,
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    }],
};
pub const LAYOUT__368: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
};
pub const LAYOUT__369: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
};
pub const LAYOUT__367: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__368,
    byte1: LAYOUT__369,
};
pub const LAYOUT__370: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
};
pub const LAYOUT__366: &OpLBLayout = &OpLBLayout {
    bytes: LAYOUT__367,
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    low7x2: LAYOUT__370,
};
pub const LAYOUT__365: &Mem0OutputArm0Layout = &Mem0OutputArm0Layout {
    _super: LAYOUT__366,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__372: &OpLHLayout = &OpLHLayout {
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    low15x2: LAYOUT__81,
};
pub const LAYOUT__371: &Mem0OutputArm1Layout = &Mem0OutputArm1Layout {
    _super: LAYOUT__372,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
};
pub const LAYOUT__373: &Mem0OutputArm2Layout = &Mem0OutputArm2Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__375: &OpLBULayout = &OpLBULayout { bytes: LAYOUT__367 };
pub const LAYOUT__374: &Mem0OutputArm3Layout = &Mem0OutputArm3Layout {
    _super: LAYOUT__375,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__376: &Mem0OutputArm4Layout = &Mem0OutputArm4Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__377: &Mem0OutputArm5Layout = &Mem0OutputArm5Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__378: &Mem0OutputArm6Layout = &Mem0OutputArm6Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__379: &Mem0OutputArm7Layout = &Mem0OutputArm7Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__364: &Mem0OutputLayout = &Mem0OutputLayout {
    arm0: LAYOUT__365,
    arm1: LAYOUT__371,
    arm2: LAYOUT__373,
    arm3: LAYOUT__374,
    arm4: LAYOUT__376,
    arm5: LAYOUT__377,
    arm6: LAYOUT__378,
    arm7: LAYOUT__379,
};
pub const LAYOUT__383: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__384: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__382: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__383,
    new_txn: LAYOUT__384,
};
pub const LAYOUT__386: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
};
pub const LAYOUT__385: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__386 };
pub const LAYOUT__381: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__382,
    _0: LAYOUT__385,
};
pub const LAYOUT__380: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    _0: LAYOUT__381,
};
pub const LAYOUT__388: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
};
pub const LAYOUT__389: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
};
pub const LAYOUT__387: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__388,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
    high16: LAYOUT__389,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
};
pub const LAYOUT__330: &Mem0Layout = &Mem0Layout {
    _0: LAYOUT__331,
    input: LAYOUT__332,
    _arguments_mem0_output: LAYOUT__362,
    output: LAYOUT__364,
    _1: LAYOUT__380,
    pc_add: LAYOUT__387,
};
pub const LAYOUT__395: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 86 },
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
pub const LAYOUT__396: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 86 },
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
pub const LAYOUT__394: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__395,
    new_txn: LAYOUT__396,
};
pub const LAYOUT__398: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
};
pub const LAYOUT__397: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__398 };
pub const LAYOUT__393: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__394,
    _0: LAYOUT__397,
};
pub const LAYOUT__392: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__393,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
};
pub const LAYOUT__400: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__399: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__355,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    high16: LAYOUT__400,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
};
pub const LAYOUT__402: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
};
pub const LAYOUT__403: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__401: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    upper_diff: LAYOUT__402,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    med14: LAYOUT__403,
};
pub const LAYOUT__406: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 112 },
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
pub const LAYOUT__407: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 117 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 112 },
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
pub const LAYOUT__405: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__406,
    new_txn: LAYOUT__407,
};
pub const LAYOUT__409: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
};
pub const LAYOUT__408: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__409 };
pub const LAYOUT__404: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__405,
    _0: LAYOUT__408,
};
pub const LAYOUT__391: &MemStoreInputLayout = &MemStoreInputLayout {
    decoded: LAYOUT__333,
    rs1: LAYOUT__344,
    rs2: LAYOUT__392,
    addr_u32: LAYOUT__399,
    addr: LAYOUT__401,
    data_0: LAYOUT__404,
};
pub const LAYOUT__411: &ArgU8Layout4LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
];
pub const LAYOUT__410: &_Arguments_Mem1OutputLayout = &_Arguments_Mem1OutputLayout {
    arg_u8: LAYOUT__411,
};
pub const LAYOUT__415: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__414: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__370,
    byte1: LAYOUT__415,
};
pub const LAYOUT__413: &OpSBLayout = &OpSBLayout {
    orig_bytes: LAYOUT__367,
    new_bytes: LAYOUT__414,
};
pub const LAYOUT__416: &Mem1OutputArm1Layout = &Mem1OutputArm1Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__417: &Mem1OutputArm2Layout = &Mem1OutputArm2Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__418: &Mem1OutputArm3Layout = &Mem1OutputArm3Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__419: &Mem1OutputArm4Layout = &Mem1OutputArm4Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__420: &Mem1OutputArm5Layout = &Mem1OutputArm5Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__421: &Mem1OutputArm6Layout = &Mem1OutputArm6Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__422: &Mem1OutputArm7Layout = &Mem1OutputArm7Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
    },
};
pub const LAYOUT__412: &Mem1OutputLayout = &Mem1OutputLayout {
    arm0: LAYOUT__413,
    arm1: LAYOUT__416,
    arm2: LAYOUT__417,
    arm3: LAYOUT__418,
    arm4: LAYOUT__419,
    arm5: LAYOUT__420,
    arm6: LAYOUT__421,
    arm7: LAYOUT__422,
};
pub const LAYOUT__426: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 124 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 125 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
};
pub const LAYOUT__427: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
};
pub const LAYOUT__425: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__426,
    new_txn: LAYOUT__427,
};
pub const LAYOUT__429: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
};
pub const LAYOUT__428: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__429 };
pub const LAYOUT__424: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__425,
    _0: LAYOUT__428,
};
pub const LAYOUT__423: &MemStoreFinalizeLayout = &MemStoreFinalizeLayout { _0: LAYOUT__424 };
pub const LAYOUT__431: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
};
pub const LAYOUT__432: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__430: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__431,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    high16: LAYOUT__432,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
};
pub const LAYOUT__390: &Mem1Layout = &Mem1Layout {
    _0: LAYOUT__331,
    input: LAYOUT__391,
    _arguments_mem1_output: LAYOUT__410,
    output: LAYOUT__412,
    _1: LAYOUT__423,
    pc_add: LAYOUT__430,
};
pub const LAYOUT__441: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 28 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 29 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 30 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 31 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 32 },
    },
};
pub const LAYOUT__442: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 33 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 29 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 34 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 35 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
};
pub const LAYOUT__440: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__441,
    new_txn: LAYOUT__442,
};
pub const LAYOUT__439: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__440 };
pub const LAYOUT__438: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__439 };
pub const LAYOUT__446: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 38 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
};
pub const LAYOUT__447: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 38 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
};
pub const LAYOUT__445: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__446,
    new_txn: LAYOUT__447,
};
pub const LAYOUT__444: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__445 };
pub const LAYOUT__443: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__444 };
pub const LAYOUT__451: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
};
pub const LAYOUT__452: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 51 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
};
pub const LAYOUT__450: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__451,
    new_txn: LAYOUT__452,
};
pub const LAYOUT__449: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__450 };
pub const LAYOUT__448: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__449 };
pub const LAYOUT__456: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 55 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 56 },
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
pub const LAYOUT__457: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 60 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 56 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 61 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 62 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 63 },
    },
};
pub const LAYOUT__455: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__456,
    new_txn: LAYOUT__457,
};
pub const LAYOUT__454: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__455 };
pub const LAYOUT__453: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__454 };
pub const LAYOUT__461: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 65 },
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
pub const LAYOUT__462: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 65 },
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
pub const LAYOUT__460: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__461,
    new_txn: LAYOUT__462,
};
pub const LAYOUT__459: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__460 };
pub const LAYOUT__458: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__459 };
pub const LAYOUT__466: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 74 },
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
pub const LAYOUT__467: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 74 },
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
pub const LAYOUT__465: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__466,
    new_txn: LAYOUT__467,
};
pub const LAYOUT__464: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__465 };
pub const LAYOUT__463: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__464 };
pub const LAYOUT__471: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 83 },
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
pub const LAYOUT__472: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 83 },
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
pub const LAYOUT__470: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__471,
    new_txn: LAYOUT__472,
};
pub const LAYOUT__469: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__470 };
pub const LAYOUT__468: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__469 };
pub const LAYOUT__476: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 92 },
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
pub const LAYOUT__477: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 92 },
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
pub const LAYOUT__475: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__476,
    new_txn: LAYOUT__477,
};
pub const LAYOUT__474: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__475 };
pub const LAYOUT__473: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__474 };
pub const LAYOUT__437: &ControlLoadRoot__0_SuperLayout8LayoutArray = &[
    LAYOUT__438,
    LAYOUT__443,
    LAYOUT__448,
    LAYOUT__453,
    LAYOUT__458,
    LAYOUT__463,
    LAYOUT__468,
    LAYOUT__473,
];
pub const LAYOUT__436: &ControlLoadRootLayout = &ControlLoadRootLayout { _1: LAYOUT__437 };
pub const LAYOUT__435: &Control0_SuperArm0Layout = &Control0_SuperArm0Layout {
    _super: LAYOUT__436,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    _extra1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
    _extra3: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra6: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
    _extra7: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra38: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__483: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__440,
    _0: LAYOUT__33,
};
pub const LAYOUT__484: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__445,
    _0: LAYOUT__131,
};
pub const LAYOUT__482: &ControlResume_SuperArm0_SuperLayout =
    &ControlResume_SuperArm0_SuperLayout {
        pc: LAYOUT__483,
        mode: LAYOUT__484,
    };
pub const LAYOUT__481: &ControlResume_SuperArm0Layout = &ControlResume_SuperArm0Layout {
    _super: LAYOUT__482,
    _extra0: LAYOUT__451,
    _extra1: LAYOUT__452,
    _extra2: LAYOUT__456,
    _extra3: LAYOUT__457,
    _extra4: LAYOUT__461,
    _extra5: LAYOUT__462,
    _extra6: LAYOUT__466,
    _extra7: LAYOUT__467,
    _extra8: LAYOUT__471,
    _extra9: LAYOUT__472,
    _extra10: LAYOUT__476,
    _extra11: LAYOUT__477,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
};
pub const LAYOUT__488: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__440,
    _0: LAYOUT__33,
};
pub const LAYOUT__487: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__488 };
pub const LAYOUT__490: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__445,
    _0: LAYOUT__131,
};
pub const LAYOUT__489: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__490 };
pub const LAYOUT__494: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
};
pub const LAYOUT__493: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__494 };
pub const LAYOUT__492: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__450,
    _0: LAYOUT__493,
};
pub const LAYOUT__491: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__492 };
pub const LAYOUT__498: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
};
pub const LAYOUT__497: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__498 };
pub const LAYOUT__496: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__455,
    _0: LAYOUT__497,
};
pub const LAYOUT__495: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__496 };
pub const LAYOUT__502: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
};
pub const LAYOUT__501: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__502 };
pub const LAYOUT__500: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__460,
    _0: LAYOUT__501,
};
pub const LAYOUT__499: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__500 };
pub const LAYOUT__506: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__505: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__506 };
pub const LAYOUT__504: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__465,
    _0: LAYOUT__505,
};
pub const LAYOUT__503: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__504 };
pub const LAYOUT__510: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
};
pub const LAYOUT__509: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__510 };
pub const LAYOUT__508: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__470,
    _0: LAYOUT__509,
};
pub const LAYOUT__507: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__508 };
pub const LAYOUT__514: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
};
pub const LAYOUT__513: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__514 };
pub const LAYOUT__512: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__475,
    _0: LAYOUT__513,
};
pub const LAYOUT__511: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__512 };
pub const LAYOUT__486: &ControlResume_SuperArm1_Super__0_SuperLayout8LayoutArray = &[
    LAYOUT__487,
    LAYOUT__489,
    LAYOUT__491,
    LAYOUT__495,
    LAYOUT__499,
    LAYOUT__503,
    LAYOUT__507,
    LAYOUT__511,
];
pub const LAYOUT__485: &ControlResume_SuperArm1_SuperLayout =
    &ControlResume_SuperArm1_SuperLayout { _1: LAYOUT__486 };
pub const LAYOUT__480: &ControlResume_SuperLayout = &ControlResume_SuperLayout {
    arm0: LAYOUT__481,
    arm1: LAYOUT__485,
};
pub const LAYOUT__516: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__441,
    LAYOUT__442,
    LAYOUT__446,
    LAYOUT__447,
    LAYOUT__451,
    LAYOUT__452,
    LAYOUT__456,
    LAYOUT__457,
    LAYOUT__461,
    LAYOUT__462,
    LAYOUT__466,
    LAYOUT__467,
    LAYOUT__471,
    LAYOUT__472,
    LAYOUT__476,
    LAYOUT__477,
];
pub const LAYOUT__517: &CycleArgLayout8LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
];
pub const LAYOUT__515: &_Arguments_ControlResume_SuperLayout =
    &_Arguments_ControlResume_SuperLayout {
        memory_arg: LAYOUT__516,
        cycle_arg: LAYOUT__517,
    };
pub const LAYOUT__479: &ControlResumeLayout = &ControlResumeLayout {
    _super: LAYOUT__480,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _arguments_control_resume__super: LAYOUT__515,
};
pub const LAYOUT__478: &Control0_SuperArm1Layout = &Control0_SuperArm1Layout {
    _super: LAYOUT__479,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__521: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
};
pub const LAYOUT__522: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
};
pub const LAYOUT__520: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    upper_diff: LAYOUT__521,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    },
    med14: LAYOUT__522,
};
pub const LAYOUT__523: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
};
pub const LAYOUT__524: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__450,
    _0: LAYOUT__493,
};
pub const LAYOUT__519: &ControlUserECALLLayout = &ControlUserECALLLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
    pc_addr: LAYOUT__520,
    load_inst: LAYOUT__483,
    dispatch_idx: LAYOUT__484,
    _0: LAYOUT__523,
    new_pc_addr: LAYOUT__524,
    _1: LAYOUT__496,
};
pub const LAYOUT__518: &Control0_SuperArm2Layout = &Control0_SuperArm2Layout {
    _super: LAYOUT__519,
    _extra0: LAYOUT__461,
    _extra1: LAYOUT__462,
    _extra2: LAYOUT__466,
    _extra3: LAYOUT__467,
    _extra4: LAYOUT__471,
    _extra5: LAYOUT__472,
    _extra6: LAYOUT__476,
    _extra7: LAYOUT__477,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra38: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__528: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
};
pub const LAYOUT__527: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__523,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 185 },
    },
    high16: LAYOUT__528,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 186 },
    },
};
pub const LAYOUT__526: &ControlMRETLayout = &ControlMRETLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
    pc_addr: LAYOUT__520,
    load_inst: LAYOUT__483,
    pc: LAYOUT__484,
    pc_add: LAYOUT__527,
};
pub const LAYOUT__525: &Control0_SuperArm3Layout = &Control0_SuperArm3Layout {
    _super: LAYOUT__526,
    _extra0: LAYOUT__451,
    _extra1: LAYOUT__452,
    _extra2: LAYOUT__456,
    _extra3: LAYOUT__457,
    _extra4: LAYOUT__461,
    _extra5: LAYOUT__462,
    _extra6: LAYOUT__466,
    _extra7: LAYOUT__467,
    _extra8: LAYOUT__471,
    _extra9: LAYOUT__472,
    _extra10: LAYOUT__476,
    _extra11: LAYOUT__477,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra38: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra42: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra43: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra44: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra45: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__534: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__455,
    _0: LAYOUT__497,
};
pub const LAYOUT__535: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__460,
    _0: LAYOUT__501,
};
pub const LAYOUT__536: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__465,
    _0: LAYOUT__505,
};
pub const LAYOUT__537: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__470,
    _0: LAYOUT__509,
};
pub const LAYOUT__538: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__475,
    _0: LAYOUT__513,
};
pub const LAYOUT__533: &MemoryReadLayout8LayoutArray = &[
    LAYOUT__483,
    LAYOUT__484,
    LAYOUT__524,
    LAYOUT__534,
    LAYOUT__535,
    LAYOUT__536,
    LAYOUT__537,
    LAYOUT__538,
];
pub const LAYOUT__532: &ControlSuspend_SuperArm0_SuperLayout =
    &ControlSuspend_SuperArm0_SuperLayout { _1: LAYOUT__533 };
pub const LAYOUT__540: &ControlSuspend_SuperArm1_SuperLayout =
    &ControlSuspend_SuperArm1_SuperLayout {
        state: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        _0: LAYOUT__488,
        _1: LAYOUT__490,
    };
pub const LAYOUT__539: &ControlSuspend_SuperArm1Layout = &ControlSuspend_SuperArm1Layout {
    _super: LAYOUT__540,
    _extra0: LAYOUT__451,
    _extra1: LAYOUT__452,
    _extra2: LAYOUT__456,
    _extra3: LAYOUT__457,
    _extra4: LAYOUT__461,
    _extra5: LAYOUT__462,
    _extra6: LAYOUT__466,
    _extra7: LAYOUT__467,
    _extra8: LAYOUT__471,
    _extra9: LAYOUT__472,
    _extra10: LAYOUT__476,
    _extra11: LAYOUT__477,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
};
pub const LAYOUT__531: &ControlSuspend_SuperLayout = &ControlSuspend_SuperLayout {
    arm0: LAYOUT__532,
    arm1: LAYOUT__539,
};
pub const LAYOUT__541: &_Arguments_ControlSuspend_SuperLayout =
    &_Arguments_ControlSuspend_SuperLayout {
        memory_arg: LAYOUT__516,
        cycle_arg: LAYOUT__517,
    };
pub const LAYOUT__530: &ControlSuspendLayout = &ControlSuspendLayout {
    _super: LAYOUT__531,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _arguments_control_suspend__super: LAYOUT__541,
};
pub const LAYOUT__529: &Control0_SuperArm4Layout = &Control0_SuperArm4Layout {
    _super: LAYOUT__530,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__545: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__440,
    _0: LAYOUT__33,
};
pub const LAYOUT__546: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__445,
    _0: LAYOUT__131,
};
pub const LAYOUT__547: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__450,
    _0: LAYOUT__493,
};
pub const LAYOUT__548: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__455,
    _0: LAYOUT__497,
};
pub const LAYOUT__549: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__460,
    _0: LAYOUT__501,
};
pub const LAYOUT__550: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__465,
    _0: LAYOUT__505,
};
pub const LAYOUT__551: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__470,
    _0: LAYOUT__509,
};
pub const LAYOUT__552: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__475,
    _0: LAYOUT__513,
};
pub const LAYOUT__544: &MemoryPageOutLayout8LayoutArray = &[
    LAYOUT__545,
    LAYOUT__546,
    LAYOUT__547,
    LAYOUT__548,
    LAYOUT__549,
    LAYOUT__550,
    LAYOUT__551,
    LAYOUT__552,
];
pub const LAYOUT__543: &ControlStoreRootLayout = &ControlStoreRootLayout { _1: LAYOUT__544 };
pub const LAYOUT__542: &Control0_SuperArm5Layout = &Control0_SuperArm5Layout {
    _super: LAYOUT__543,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__559: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 116 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 117 },
            },
        },
    };
pub const LAYOUT__560: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 118 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 119 },
            },
        },
    };
pub const LAYOUT__561: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 120 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 121 },
            },
        },
    };
pub const LAYOUT__562: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 122 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 123 },
            },
        },
    };
pub const LAYOUT__563: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 124 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 125 },
            },
        },
    };
pub const LAYOUT__564: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 126 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 127 },
            },
        },
    };
pub const LAYOUT__565: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 128 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 129 },
            },
        },
    };
pub const LAYOUT__566: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 130 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 131 },
            },
        },
    };
pub const LAYOUT__567: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 132 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 133 },
            },
        },
    };
pub const LAYOUT__568: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 134 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 135 },
            },
        },
    };
pub const LAYOUT__569: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 136 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 137 },
            },
        },
    };
pub const LAYOUT__570: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 138 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 139 },
            },
        },
    };
pub const LAYOUT__571: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 140 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 141 },
            },
        },
    };
pub const LAYOUT__572: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 142 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 143 },
            },
        },
    };
pub const LAYOUT__573: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 144 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 145 },
            },
        },
    };
pub const LAYOUT__574: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 146 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 147 },
            },
        },
    };
pub const LAYOUT__558: &ControlTable_SuperArm0_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__559,
    LAYOUT__560,
    LAYOUT__561,
    LAYOUT__562,
    LAYOUT__563,
    LAYOUT__564,
    LAYOUT__565,
    LAYOUT__566,
    LAYOUT__567,
    LAYOUT__568,
    LAYOUT__569,
    LAYOUT__570,
    LAYOUT__571,
    LAYOUT__572,
    LAYOUT__573,
    LAYOUT__574,
];
pub const LAYOUT__557: &ControlTable_SuperArm0_SuperLayout = &ControlTable_SuperArm0_SuperLayout {
    _1: LAYOUT__558,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__556: &ControlTable_SuperArm0Layout = &ControlTable_SuperArm0Layout {
    _super: LAYOUT__557,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra4: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra5: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra6: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra7: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra8: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra9: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra14: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra15: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__578: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 148 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 149 },
            },
        },
    };
pub const LAYOUT__579: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 150 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 151 },
            },
        },
    };
pub const LAYOUT__580: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 152 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 153 },
            },
        },
    };
pub const LAYOUT__581: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 154 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 155 },
            },
        },
    };
pub const LAYOUT__582: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 156 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 157 },
            },
        },
    };
pub const LAYOUT__583: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 158 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 159 },
            },
        },
    };
pub const LAYOUT__584: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 160 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 161 },
            },
        },
    };
pub const LAYOUT__585: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 162 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 163 },
            },
        },
    };
pub const LAYOUT__586: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 164 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 165 },
            },
        },
    };
pub const LAYOUT__587: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 166 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 167 },
            },
        },
    };
pub const LAYOUT__588: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 168 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 169 },
            },
        },
    };
pub const LAYOUT__589: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 170 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 171 },
            },
        },
    };
pub const LAYOUT__590: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 172 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 173 },
            },
        },
    };
pub const LAYOUT__591: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 174 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 175 },
            },
        },
    };
pub const LAYOUT__592: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 176 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 177 },
            },
        },
    };
pub const LAYOUT__593: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 178 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 179 },
            },
        },
    };
pub const LAYOUT__577: &ControlTable_SuperArm1_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__578,
    LAYOUT__579,
    LAYOUT__580,
    LAYOUT__581,
    LAYOUT__582,
    LAYOUT__583,
    LAYOUT__584,
    LAYOUT__585,
    LAYOUT__586,
    LAYOUT__587,
    LAYOUT__588,
    LAYOUT__589,
    LAYOUT__590,
    LAYOUT__591,
    LAYOUT__592,
    LAYOUT__593,
];
pub const LAYOUT__576: &ControlTable_SuperArm1_SuperLayout = &ControlTable_SuperArm1_SuperLayout {
    _1: LAYOUT__577,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__575: &ControlTable_SuperArm1Layout = &ControlTable_SuperArm1Layout {
    _super: LAYOUT__576,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__555: &ControlTable_SuperLayout = &ControlTable_SuperLayout {
    arm0: LAYOUT__556,
    arm1: LAYOUT__575,
};
pub const LAYOUT__595: &ArgU16Layout16LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
];
pub const LAYOUT__596: &ArgU8Layout16LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
];
pub const LAYOUT__594: &_Arguments_ControlTable_SuperLayout =
    &_Arguments_ControlTable_SuperLayout {
        arg_u16: LAYOUT__595,
        arg_u8: LAYOUT__596,
    };
pub const LAYOUT__554: &ControlTableLayout = &ControlTableLayout {
    _super: LAYOUT__555,
    entry: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    mode: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    _arguments_control_table__super: LAYOUT__594,
};
pub const LAYOUT__553: &Control0_SuperArm6Layout = &Control0_SuperArm6Layout {
    _super: LAYOUT__554,
    _extra0: LAYOUT__441,
    _extra1: LAYOUT__442,
    _extra2: LAYOUT__446,
    _extra3: LAYOUT__447,
    _extra4: LAYOUT__451,
    _extra5: LAYOUT__452,
    _extra6: LAYOUT__456,
    _extra7: LAYOUT__457,
    _extra8: LAYOUT__461,
    _extra9: LAYOUT__462,
    _extra10: LAYOUT__466,
    _extra11: LAYOUT__467,
    _extra12: LAYOUT__471,
    _extra13: LAYOUT__472,
    _extra14: LAYOUT__476,
    _extra15: LAYOUT__477,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
};
pub const LAYOUT__599: &_Arguments_ControlDone__0Layout = &_Arguments_ControlDone__0Layout {
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    }],
};
pub const LAYOUT__601: &ControlDone__0Arm0_SuperLayout =
    &ControlDone__0Arm0_SuperLayout { _0: LAYOUT__34 };
pub const LAYOUT__602: &ControlDone__0Arm1Layout = &ControlDone__0Arm1Layout {
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
};
pub const LAYOUT__600: &ControlDone__0Layout = &ControlDone__0Layout {
    arm0: LAYOUT__601,
    arm1: LAYOUT__602,
};
pub const LAYOUT__598: &ControlDoneLayout = &ControlDoneLayout {
    _arguments_control_done__0: LAYOUT__599,
    _2: LAYOUT__600,
};
pub const LAYOUT__597: &Control0_SuperArm7Layout = &Control0_SuperArm7Layout {
    _super: LAYOUT__598,
    _extra0: LAYOUT__441,
    _extra1: LAYOUT__442,
    _extra2: LAYOUT__446,
    _extra3: LAYOUT__447,
    _extra4: LAYOUT__451,
    _extra5: LAYOUT__452,
    _extra6: LAYOUT__456,
    _extra7: LAYOUT__457,
    _extra8: LAYOUT__461,
    _extra9: LAYOUT__462,
    _extra10: LAYOUT__466,
    _extra11: LAYOUT__467,
    _extra12: LAYOUT__471,
    _extra13: LAYOUT__472,
    _extra14: LAYOUT__476,
    _extra15: LAYOUT__477,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra42: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra43: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra44: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra45: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra46: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra47: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra48: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra49: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra50: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra51: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra52: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra53: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra54: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__434: &Control0_SuperLayout = &Control0_SuperLayout {
    arm0: LAYOUT__435,
    arm1: LAYOUT__478,
    arm2: LAYOUT__518,
    arm3: LAYOUT__525,
    arm4: LAYOUT__529,
    arm5: LAYOUT__542,
    arm6: LAYOUT__553,
    arm7: LAYOUT__597,
};
pub const LAYOUT__603: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__604: &_Arguments_Control0_SuperLayout = &_Arguments_Control0_SuperLayout {
    memory_arg: LAYOUT__516,
    cycle_arg: LAYOUT__517,
    arg_u16: LAYOUT__595,
    arg_u8: LAYOUT__596,
};
pub const LAYOUT__433: &Control0Layout = &Control0Layout {
    _super: LAYOUT__434,
    _0: LAYOUT__603,
    _arguments_control0__super: LAYOUT__604,
};
pub const LAYOUT__606: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
};
pub const LAYOUT__608: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
};
pub const LAYOUT__607: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    upper_diff: LAYOUT__28,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    med14: LAYOUT__608,
};
pub const LAYOUT__610: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__441,
    LAYOUT__442,
    LAYOUT__446,
    LAYOUT__447,
    LAYOUT__451,
    LAYOUT__452,
    LAYOUT__456,
    LAYOUT__457,
];
pub const LAYOUT__611: &CycleArgLayout4LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
];
pub const LAYOUT__612: &ArgU16Layout4LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
];
pub const LAYOUT__609: &_Arguments_ECall0OutputLayout = &_Arguments_ECall0OutputLayout {
    memory_arg: LAYOUT__610,
    cycle_arg: LAYOUT__611,
    arg_u16: LAYOUT__612,
};
pub const LAYOUT__618: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
};
pub const LAYOUT__617: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__618 };
pub const LAYOUT__616: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__440,
    _0: LAYOUT__617,
};
pub const LAYOUT__621: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
};
pub const LAYOUT__620: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__621 };
pub const LAYOUT__619: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__445,
    _0: LAYOUT__620,
};
pub const LAYOUT__623: &NondetRegLayout5LayoutArray = &[
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
pub const LAYOUT__622: &OneHot_5_Layout = &OneHot_5_Layout {
    _super: LAYOUT__623,
};
pub const LAYOUT__615: &MachineECallLayout = &MachineECallLayout {
    load_inst: LAYOUT__616,
    dispatch_idx: LAYOUT__619,
    dispatch: LAYOUT__622,
};
pub const LAYOUT__614: &ECall0OutputArm0Layout = &ECall0OutputArm0Layout {
    _super: LAYOUT__615,
    _extra0: LAYOUT__451,
    _extra1: LAYOUT__452,
    _extra2: LAYOUT__456,
    _extra3: LAYOUT__457,
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__625: &ECallTerminateLayout = &ECallTerminateLayout {
    a0: LAYOUT__616,
    a1: LAYOUT__619,
};
pub const LAYOUT__624: &ECall0OutputArm1Layout = &ECall0OutputArm1Layout {
    _super: LAYOUT__625,
    _extra0: LAYOUT__451,
    _extra1: LAYOUT__452,
    _extra2: LAYOUT__456,
    _extra3: LAYOUT__457,
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__629: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
};
pub const LAYOUT__628: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__629 };
pub const LAYOUT__627: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__450,
    _0: LAYOUT__628,
};
pub const LAYOUT__630: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
};
pub const LAYOUT__631: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__634: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
};
pub const LAYOUT__633: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__634 };
pub const LAYOUT__632: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__455,
    _0: LAYOUT__633,
};
pub const LAYOUT__636: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
};
pub const LAYOUT__638: &NondetRegLayout4LayoutArray = &[
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
pub const LAYOUT__637: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__638,
};
pub const LAYOUT__635: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__636,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    low2_hot: LAYOUT__637,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
};
pub const LAYOUT__640: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__642: &NondetRegLayout4LayoutArray = &[
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
];
pub const LAYOUT__641: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__642,
};
pub const LAYOUT__639: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__640,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    low2_hot: LAYOUT__641,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
};
pub const LAYOUT__626: &ECallHostReadSetupLayout = &ECallHostReadSetupLayout {
    fd: LAYOUT__616,
    ptr: LAYOUT__619,
    len: LAYOUT__627,
    new_len: LAYOUT__630,
    diff: LAYOUT__631,
    _0: LAYOUT__632,
    ptr_decomp: LAYOUT__635,
    len_decomp: LAYOUT__639,
    len123: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    uneven: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
};
pub const LAYOUT__644: &ECallHostWriteLayout = &ECallHostWriteLayout {
    fd: LAYOUT__616,
    ptr: LAYOUT__619,
    len: LAYOUT__627,
    new_len: LAYOUT__630,
    diff: LAYOUT__631,
    _0: LAYOUT__632,
};
pub const LAYOUT__643: &ECall0OutputArm3Layout = &ECall0OutputArm3Layout {
    _super: LAYOUT__644,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__645: &ECall0OutputArm4Layout = &ECall0OutputArm4Layout {
    _extra0: LAYOUT__441,
    _extra1: LAYOUT__442,
    _extra2: LAYOUT__446,
    _extra3: LAYOUT__447,
    _extra4: LAYOUT__451,
    _extra5: LAYOUT__452,
    _extra6: LAYOUT__456,
    _extra7: LAYOUT__457,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__648: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__630,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    low2_hot: LAYOUT__637,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
};
pub const LAYOUT__649: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: LAYOUT__631,
    low2: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    low2_hot: LAYOUT__641,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
};
pub const LAYOUT__652: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__440,
    _0: LAYOUT__617,
};
pub const LAYOUT__651: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    _0: LAYOUT__652,
};
pub const LAYOUT__654: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__445,
    _0: LAYOUT__620,
};
pub const LAYOUT__653: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    _0: LAYOUT__654,
};
pub const LAYOUT__656: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__450,
    _0: LAYOUT__628,
};
pub const LAYOUT__655: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    _0: LAYOUT__656,
};
pub const LAYOUT__658: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__455,
    _0: LAYOUT__633,
};
pub const LAYOUT__657: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    _0: LAYOUT__658,
};
pub const LAYOUT__650: &ECallHostReadWords__0_SuperLayout4LayoutArray =
    &[LAYOUT__651, LAYOUT__653, LAYOUT__655, LAYOUT__657];
pub const LAYOUT__647: &ECallHostReadWordsLayout = &ECallHostReadWordsLayout {
    len_decomp: LAYOUT__648,
    words_decomp: LAYOUT__649,
    _1: LAYOUT__650,
    len_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
};
pub const LAYOUT__646: &ECall0OutputArm5Layout = &ECall0OutputArm5Layout {
    _super: LAYOUT__647,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__659: &ECall0OutputArm6Layout = &ECall0OutputArm6Layout {
    _extra0: LAYOUT__441,
    _extra1: LAYOUT__442,
    _extra2: LAYOUT__446,
    _extra3: LAYOUT__447,
    _extra4: LAYOUT__451,
    _extra5: LAYOUT__452,
    _extra6: LAYOUT__456,
    _extra7: LAYOUT__457,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__660: &ECall0OutputArm7Layout = &ECall0OutputArm7Layout {
    _extra0: LAYOUT__441,
    _extra1: LAYOUT__442,
    _extra2: LAYOUT__446,
    _extra3: LAYOUT__447,
    _extra4: LAYOUT__451,
    _extra5: LAYOUT__452,
    _extra6: LAYOUT__456,
    _extra7: LAYOUT__457,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__613: &ECall0OutputLayout = &ECall0OutputLayout {
    arm0: LAYOUT__614,
    arm1: LAYOUT__624,
    arm2: LAYOUT__626,
    arm3: LAYOUT__643,
    arm4: LAYOUT__645,
    arm5: LAYOUT__646,
    arm6: LAYOUT__659,
    arm7: LAYOUT__660,
};
pub const LAYOUT__662: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__661: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__662,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 125 },
    },
    high16: LAYOUT__388,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
};
pub const LAYOUT__605: &ECall0Layout = &ECall0Layout {
    s0: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    s1: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    s2: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    _0: LAYOUT__606,
    pc_addr: LAYOUT__607,
    _arguments_e_call0_output: LAYOUT__609,
    output: LAYOUT__613,
    is_decode: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    is_p2_entry: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    is_sha_ecall: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    add_pc: LAYOUT__661,
};
pub const LAYOUT__664: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 193 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 194 },
        },
    },
};
pub const LAYOUT__666: &NondetRegLayout24LayoutArray = &[
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
];
pub const LAYOUT__665: &PoseidonStateLayout = &PoseidonStateLayout {
    has_state: &NondetRegLayout {
        _super: &Reg { offset: 28 },
    },
    state_addr: &NondetRegLayout {
        _super: &Reg { offset: 29 },
    },
    buf_out_addr: &NondetRegLayout {
        _super: &Reg { offset: 30 },
    },
    is_elem: &NondetRegLayout {
        _super: &Reg { offset: 31 },
    },
    check_out: &NondetRegLayout {
        _super: &Reg { offset: 32 },
    },
    load_tx_type: &NondetRegLayout {
        _super: &Reg { offset: 33 },
    },
    next_state: &NondetRegLayout {
        _super: &Reg { offset: 34 },
    },
    sub_state: &NondetRegLayout {
        _super: &Reg { offset: 35 },
    },
    buf_in_addr: &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
    count: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    mode: &NondetRegLayout {
        _super: &Reg { offset: 38 },
    },
    inner: LAYOUT__666,
    zcheck: &NondetExtRegLayout {
        _super: &Reg { offset: 63 },
    },
};
pub const LAYOUT__669: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
};
pub const LAYOUT__670: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
};
pub const LAYOUT__671: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
};
pub const LAYOUT__672: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
};
pub const LAYOUT__673: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
};
pub const LAYOUT__674: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
};
pub const LAYOUT__675: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 95 },
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
pub const LAYOUT__676: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 95 },
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
pub const LAYOUT__677: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__678: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__679: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__680: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__681: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 122 },
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
pub const LAYOUT__682: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 122 },
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
pub const LAYOUT__683: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
};
pub const LAYOUT__684: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 131 },
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
pub const LAYOUT__668: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__669,
    LAYOUT__670,
    LAYOUT__671,
    LAYOUT__672,
    LAYOUT__673,
    LAYOUT__674,
    LAYOUT__675,
    LAYOUT__676,
    LAYOUT__677,
    LAYOUT__678,
    LAYOUT__679,
    LAYOUT__680,
    LAYOUT__681,
    LAYOUT__682,
    LAYOUT__683,
    LAYOUT__684,
];
pub const LAYOUT__685: &CycleArgLayout8LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
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
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
];
pub const LAYOUT__686: &ArgU16Layout24LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
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
            _super: &Reg { offset: 158 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 83 },
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
            _super: &Reg { offset: 162 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
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
            _super: &Reg { offset: 166 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 101 },
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
            _super: &Reg { offset: 170 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
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
            _super: &Reg { offset: 174 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
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
            _super: &Reg { offset: 178 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
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
            _super: &Reg { offset: 182 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
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
            _super: &Reg { offset: 186 },
        },
    },
];
pub const LAYOUT__687: &ArgU8Layout2LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    },
];
pub const LAYOUT__667: &_Arguments_Poseidon0StateLayout = &_Arguments_Poseidon0StateLayout {
    memory_arg: LAYOUT__668,
    cycle_arg: LAYOUT__685,
    arg_u16: LAYOUT__686,
    arg_u8: LAYOUT__687,
};
pub const LAYOUT__692: &PoseidonEntry_SuperArm0Layout = &PoseidonEntry_SuperArm0Layout {
    _super: LAYOUT__665,
    _extra0: LAYOUT__669,
    _extra1: LAYOUT__670,
    _extra2: LAYOUT__671,
    _extra3: LAYOUT__672,
    _extra4: LAYOUT__673,
    _extra5: LAYOUT__674,
    _extra6: LAYOUT__675,
    _extra7: LAYOUT__676,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__696: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__669,
    new_txn: LAYOUT__670,
};
pub const LAYOUT__698: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
};
pub const LAYOUT__697: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__698 };
pub const LAYOUT__695: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__696,
    _0: LAYOUT__697,
};
pub const LAYOUT__694: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__695,
};
pub const LAYOUT__701: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__671,
    new_txn: LAYOUT__672,
};
pub const LAYOUT__703: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
};
pub const LAYOUT__702: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__703 };
pub const LAYOUT__700: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__701,
    _0: LAYOUT__702,
};
pub const LAYOUT__699: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__700,
};
pub const LAYOUT__706: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__673,
    new_txn: LAYOUT__674,
};
pub const LAYOUT__708: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__707: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__708 };
pub const LAYOUT__705: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__706,
    _0: LAYOUT__707,
};
pub const LAYOUT__704: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__705,
};
pub const LAYOUT__710: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__675,
    new_txn: LAYOUT__676,
};
pub const LAYOUT__709: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__710,
    _0: LAYOUT__229,
};
pub const LAYOUT__693: &PoseidonEcallLayout = &PoseidonEcallLayout {
    _super: LAYOUT__665,
    state_addr: LAYOUT__694,
    buf_in_addr: LAYOUT__699,
    buf_out_addr: LAYOUT__704,
    bits_and_count: LAYOUT__709,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 195 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 196 },
        },
    },
    is_elem: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    check_out: &NondetRegLayout {
        _super: &Reg { offset: 198 },
    },
    count_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 199 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 200 },
        },
    },
};
pub const LAYOUT__691: &PoseidonEntry_SuperLayout = &PoseidonEntry_SuperLayout {
    _super: LAYOUT__665,
    arm0: LAYOUT__692,
    arm1: LAYOUT__693,
};
pub const LAYOUT__712: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__669,
    LAYOUT__670,
    LAYOUT__671,
    LAYOUT__672,
    LAYOUT__673,
    LAYOUT__674,
    LAYOUT__675,
    LAYOUT__676,
];
pub const LAYOUT__713: &CycleArgLayout4LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
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
pub const LAYOUT__711: &_Arguments_PoseidonEntry_SuperLayout =
    &_Arguments_PoseidonEntry_SuperLayout {
        memory_arg: LAYOUT__712,
        cycle_arg: LAYOUT__713,
    };
pub const LAYOUT__690: &PoseidonEntryLayout = &PoseidonEntryLayout {
    _super: LAYOUT__691,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 201 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 202 },
        },
    },
    _arguments_poseidon_entry__super: LAYOUT__711,
};
pub const LAYOUT__689: &Poseidon0StateArm0Layout = &Poseidon0StateArm0Layout {
    _super: LAYOUT__690,
    _extra0: LAYOUT__677,
    _extra1: LAYOUT__678,
    _extra2: LAYOUT__679,
    _extra3: LAYOUT__680,
    _extra4: LAYOUT__681,
    _extra5: LAYOUT__682,
    _extra6: LAYOUT__683,
    _extra7: LAYOUT__684,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    },
};
pub const LAYOUT__717: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__695,
};
pub const LAYOUT__718: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__700,
};
pub const LAYOUT__719: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__705,
};
pub const LAYOUT__720: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__709,
};
pub const LAYOUT__723: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__677,
    new_txn: LAYOUT__678,
};
pub const LAYOUT__725: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
};
pub const LAYOUT__724: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__725 };
pub const LAYOUT__722: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__723,
    _0: LAYOUT__724,
};
pub const LAYOUT__721: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__722,
};
pub const LAYOUT__728: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__679,
    new_txn: LAYOUT__680,
};
pub const LAYOUT__730: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
};
pub const LAYOUT__729: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__730 };
pub const LAYOUT__727: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__728,
    _0: LAYOUT__729,
};
pub const LAYOUT__726: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__727,
};
pub const LAYOUT__733: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__681,
    new_txn: LAYOUT__682,
};
pub const LAYOUT__735: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
};
pub const LAYOUT__734: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__735 };
pub const LAYOUT__732: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__733,
    _0: LAYOUT__734,
};
pub const LAYOUT__731: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__732,
};
pub const LAYOUT__738: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__683,
    new_txn: LAYOUT__684,
};
pub const LAYOUT__740: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
};
pub const LAYOUT__739: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__740 };
pub const LAYOUT__737: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__738,
    _0: LAYOUT__739,
};
pub const LAYOUT__736: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__737,
};
pub const LAYOUT__716: &ReadElemLayout8LayoutArray = &[
    LAYOUT__717,
    LAYOUT__718,
    LAYOUT__719,
    LAYOUT__720,
    LAYOUT__721,
    LAYOUT__726,
    LAYOUT__731,
    LAYOUT__736,
];
pub const LAYOUT__715: &PoseidonLoadStateLayout = &PoseidonLoadStateLayout {
    _super: LAYOUT__665,
    load_list: LAYOUT__716,
};
pub const LAYOUT__714: &Poseidon0StateArm1Layout = &Poseidon0StateArm1Layout {
    _super: LAYOUT__715,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    },
};
pub const LAYOUT__745: &OneHot_3_Layout = &OneHot_3_Layout {
    _super: &[
        &NondetRegLayout {
            _super: &Reg { offset: 195 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 196 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 197 },
        },
    ],
};
pub const LAYOUT__750: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__696 };
pub const LAYOUT__749: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__750,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
};
pub const LAYOUT__751: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__696,
    _0: LAYOUT__697,
};
pub const LAYOUT__748: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__695,
    arm1: LAYOUT__749,
    arm2: LAYOUT__751,
};
pub const LAYOUT__753: &MemoryArgLayout2LayoutArray = &[LAYOUT__669, LAYOUT__670];
pub const LAYOUT__752: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__753,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    }],
};
pub const LAYOUT__747: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__748,
    _arguments_memory_get__super: LAYOUT__752,
};
pub const LAYOUT__757: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__701 };
pub const LAYOUT__756: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__757,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
};
pub const LAYOUT__758: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__701,
    _0: LAYOUT__702,
};
pub const LAYOUT__755: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__700,
    arm1: LAYOUT__756,
    arm2: LAYOUT__758,
};
pub const LAYOUT__760: &MemoryArgLayout2LayoutArray = &[LAYOUT__671, LAYOUT__672];
pub const LAYOUT__759: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__760,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    }],
};
pub const LAYOUT__754: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__755,
    _arguments_memory_get__super: LAYOUT__759,
};
pub const LAYOUT__764: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__706 };
pub const LAYOUT__763: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__764,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__765: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__706,
    _0: LAYOUT__707,
};
pub const LAYOUT__762: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__705,
    arm1: LAYOUT__763,
    arm2: LAYOUT__765,
};
pub const LAYOUT__767: &MemoryArgLayout2LayoutArray = &[LAYOUT__673, LAYOUT__674];
pub const LAYOUT__766: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__767,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    }],
};
pub const LAYOUT__761: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__762,
    _arguments_memory_get__super: LAYOUT__766,
};
pub const LAYOUT__771: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__710 };
pub const LAYOUT__770: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__771,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__772: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__710,
    _0: LAYOUT__229,
};
pub const LAYOUT__769: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__709,
    arm1: LAYOUT__770,
    arm2: LAYOUT__772,
};
pub const LAYOUT__774: &MemoryArgLayout2LayoutArray = &[LAYOUT__675, LAYOUT__676];
pub const LAYOUT__773: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__774,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    }],
};
pub const LAYOUT__768: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__769,
    _arguments_memory_get__super: LAYOUT__773,
};
pub const LAYOUT__778: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__723 };
pub const LAYOUT__777: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__778,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
};
pub const LAYOUT__779: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__723,
    _0: LAYOUT__724,
};
pub const LAYOUT__776: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__722,
    arm1: LAYOUT__777,
    arm2: LAYOUT__779,
};
pub const LAYOUT__781: &MemoryArgLayout2LayoutArray = &[LAYOUT__677, LAYOUT__678];
pub const LAYOUT__780: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__781,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    }],
};
pub const LAYOUT__775: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__776,
    _arguments_memory_get__super: LAYOUT__780,
};
pub const LAYOUT__785: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__728 };
pub const LAYOUT__784: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__785,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
};
pub const LAYOUT__786: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__728,
    _0: LAYOUT__729,
};
pub const LAYOUT__783: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__727,
    arm1: LAYOUT__784,
    arm2: LAYOUT__786,
};
pub const LAYOUT__788: &MemoryArgLayout2LayoutArray = &[LAYOUT__679, LAYOUT__680];
pub const LAYOUT__787: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__788,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    }],
};
pub const LAYOUT__782: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__783,
    _arguments_memory_get__super: LAYOUT__787,
};
pub const LAYOUT__792: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__733 };
pub const LAYOUT__791: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__792,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
};
pub const LAYOUT__793: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__733,
    _0: LAYOUT__734,
};
pub const LAYOUT__790: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__732,
    arm1: LAYOUT__791,
    arm2: LAYOUT__793,
};
pub const LAYOUT__795: &MemoryArgLayout2LayoutArray = &[LAYOUT__681, LAYOUT__682];
pub const LAYOUT__794: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__795,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    }],
};
pub const LAYOUT__789: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__790,
    _arguments_memory_get__super: LAYOUT__794,
};
pub const LAYOUT__799: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__738 };
pub const LAYOUT__798: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__799,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
};
pub const LAYOUT__800: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__738,
    _0: LAYOUT__739,
};
pub const LAYOUT__797: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__737,
    arm1: LAYOUT__798,
    arm2: LAYOUT__800,
};
pub const LAYOUT__802: &MemoryArgLayout2LayoutArray = &[LAYOUT__683, LAYOUT__684];
pub const LAYOUT__801: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__802,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    }],
};
pub const LAYOUT__796: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__797,
    _arguments_memory_get__super: LAYOUT__801,
};
pub const LAYOUT__746: &MemoryGetLayout8LayoutArray = &[
    LAYOUT__747,
    LAYOUT__754,
    LAYOUT__761,
    LAYOUT__768,
    LAYOUT__775,
    LAYOUT__782,
    LAYOUT__789,
    LAYOUT__796,
];
pub const LAYOUT__744: &PoseidonLoadInShortLayout = &PoseidonLoadInShortLayout {
    _super: LAYOUT__665,
    tx_type: LAYOUT__745,
    load_list: LAYOUT__746,
};
pub const LAYOUT__803: &PoseidonLoadInLowLayout = &PoseidonLoadInLowLayout {
    _super: LAYOUT__665,
    tx_type: LAYOUT__745,
    load_list: LAYOUT__746,
};
pub const LAYOUT__804: &PoseidonLoadInHighLayout = &PoseidonLoadInHighLayout {
    _super: LAYOUT__665,
    tx_type: LAYOUT__745,
    load_list: LAYOUT__746,
};
pub const LAYOUT__743: &PoseidonLoadIn_SuperLayout = &PoseidonLoadIn_SuperLayout {
    _super: LAYOUT__665,
    arm0: LAYOUT__744,
    arm1: LAYOUT__803,
    arm2: LAYOUT__804,
};
pub const LAYOUT__805: &OneHot_3_Layout = &OneHot_3_Layout {
    _super: &[
        &NondetRegLayout {
            _super: &Reg { offset: 198 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 199 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 200 },
        },
    ],
};
pub const LAYOUT__806: &_Arguments_PoseidonLoadIn_SuperLayout =
    &_Arguments_PoseidonLoadIn_SuperLayout {
        memory_arg: LAYOUT__668,
        cycle_arg: LAYOUT__685,
    };
pub const LAYOUT__742: &PoseidonLoadInLayout = &PoseidonLoadInLayout {
    _super: LAYOUT__743,
    _0: LAYOUT__805,
    _arguments_poseidon_load_in__super: LAYOUT__806,
};
pub const LAYOUT__741: &Poseidon0StateArm2Layout = &Poseidon0StateArm2Layout {
    _super: LAYOUT__742,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    },
};
pub const LAYOUT__807: &Poseidon0StateArm3Layout = &Poseidon0StateArm3Layout {
    _super: LAYOUT__665,
    _extra0: LAYOUT__669,
    _extra1: LAYOUT__670,
    _extra2: LAYOUT__671,
    _extra3: LAYOUT__672,
    _extra4: LAYOUT__673,
    _extra5: LAYOUT__674,
    _extra6: LAYOUT__675,
    _extra7: LAYOUT__676,
    _extra8: LAYOUT__677,
    _extra9: LAYOUT__678,
    _extra10: LAYOUT__679,
    _extra11: LAYOUT__680,
    _extra12: LAYOUT__681,
    _extra13: LAYOUT__682,
    _extra14: LAYOUT__683,
    _extra15: LAYOUT__684,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra40: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra41: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra42: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra43: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra44: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra45: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra46: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra47: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
    _extra48: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
    },
    _extra49: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    },
};
pub const LAYOUT__808: &Poseidon0StateArm4Layout = &Poseidon0StateArm4Layout {
    _super: LAYOUT__665,
    _extra0: LAYOUT__669,
    _extra1: LAYOUT__670,
    _extra2: LAYOUT__671,
    _extra3: LAYOUT__672,
    _extra4: LAYOUT__673,
    _extra5: LAYOUT__674,
    _extra6: LAYOUT__675,
    _extra7: LAYOUT__676,
    _extra8: LAYOUT__677,
    _extra9: LAYOUT__678,
    _extra10: LAYOUT__679,
    _extra11: LAYOUT__680,
    _extra12: LAYOUT__681,
    _extra13: LAYOUT__682,
    _extra14: LAYOUT__683,
    _extra15: LAYOUT__684,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra40: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra41: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra42: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra43: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra44: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra45: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra46: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra47: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
    _extra48: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
    },
    _extra49: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    },
};
pub const LAYOUT__815: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__717 };
pub const LAYOUT__816: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__718 };
pub const LAYOUT__817: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__719 };
pub const LAYOUT__818: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__720 };
pub const LAYOUT__819: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__721 };
pub const LAYOUT__820: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__726 };
pub const LAYOUT__821: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__731 };
pub const LAYOUT__822: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__736 };
pub const LAYOUT__814: &PoseidonCheckOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__815,
    LAYOUT__816,
    LAYOUT__817,
    LAYOUT__818,
    LAYOUT__819,
    LAYOUT__820,
    LAYOUT__821,
    LAYOUT__822,
];
pub const LAYOUT__813: &PoseidonCheckOutLayout = &PoseidonCheckOutLayout {
    _super: LAYOUT__665,
    _1: LAYOUT__814,
    is_normal: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 195 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 196 },
        },
    },
    ext_inv: &NondetExtRegLayout {
        _super: &Reg { offset: 197 },
    },
};
pub const LAYOUT__812: &PoseidonDoOut_SuperArm0Layout = &PoseidonDoOut_SuperArm0Layout {
    _super: LAYOUT__813,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__827: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__828: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__829: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    }],
};
pub const LAYOUT__832: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
};
pub const LAYOUT__831: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__832 };
pub const LAYOUT__833: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__832 };
pub const LAYOUT__830: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__831,
    arm1: LAYOUT__833,
};
pub const LAYOUT__826: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__827,
    high: LAYOUT__828,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 195 },
    },
    _arguments_field_to_word__0: LAYOUT__829,
    _2: LAYOUT__830,
};
pub const LAYOUT__834: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__696,
    _0: LAYOUT__697,
};
pub const LAYOUT__825: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__826,
    mw: LAYOUT__834,
};
pub const LAYOUT__837: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
};
pub const LAYOUT__838: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
};
pub const LAYOUT__839: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    }],
};
pub const LAYOUT__841: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__201 };
pub const LAYOUT__842: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__201 };
pub const LAYOUT__840: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__841,
    arm1: LAYOUT__842,
};
pub const LAYOUT__836: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__837,
    high: LAYOUT__838,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    _arguments_field_to_word__0: LAYOUT__839,
    _2: LAYOUT__840,
};
pub const LAYOUT__843: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__701,
    _0: LAYOUT__702,
};
pub const LAYOUT__835: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__836,
    mw: LAYOUT__843,
};
pub const LAYOUT__846: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
};
pub const LAYOUT__847: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__848: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    }],
};
pub const LAYOUT__851: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
};
pub const LAYOUT__850: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__851 };
pub const LAYOUT__852: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__851 };
pub const LAYOUT__849: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__850,
    arm1: LAYOUT__852,
};
pub const LAYOUT__845: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__846,
    high: LAYOUT__847,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    _arguments_field_to_word__0: LAYOUT__848,
    _2: LAYOUT__849,
};
pub const LAYOUT__853: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__706,
    _0: LAYOUT__707,
};
pub const LAYOUT__844: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__845,
    mw: LAYOUT__853,
};
pub const LAYOUT__856: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
};
pub const LAYOUT__857: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__858: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    }],
};
pub const LAYOUT__861: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
};
pub const LAYOUT__860: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__861 };
pub const LAYOUT__862: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__861 };
pub const LAYOUT__859: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__860,
    arm1: LAYOUT__862,
};
pub const LAYOUT__855: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__856,
    high: LAYOUT__857,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 198 },
    },
    _arguments_field_to_word__0: LAYOUT__858,
    _2: LAYOUT__859,
};
pub const LAYOUT__863: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__710,
    _0: LAYOUT__229,
};
pub const LAYOUT__854: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__855,
    mw: LAYOUT__863,
};
pub const LAYOUT__866: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
};
pub const LAYOUT__867: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__868: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    }],
};
pub const LAYOUT__871: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
};
pub const LAYOUT__870: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__871 };
pub const LAYOUT__872: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__871 };
pub const LAYOUT__869: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__870,
    arm1: LAYOUT__872,
};
pub const LAYOUT__865: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__866,
    high: LAYOUT__867,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 199 },
    },
    _arguments_field_to_word__0: LAYOUT__868,
    _2: LAYOUT__869,
};
pub const LAYOUT__873: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__723,
    _0: LAYOUT__724,
};
pub const LAYOUT__864: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__865,
    mw: LAYOUT__873,
};
pub const LAYOUT__876: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
};
pub const LAYOUT__877: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__878: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    }],
};
pub const LAYOUT__881: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__880: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__881 };
pub const LAYOUT__882: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__881 };
pub const LAYOUT__879: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__880,
    arm1: LAYOUT__882,
};
pub const LAYOUT__875: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__876,
    high: LAYOUT__877,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 200 },
    },
    _arguments_field_to_word__0: LAYOUT__878,
    _2: LAYOUT__879,
};
pub const LAYOUT__883: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__728,
    _0: LAYOUT__729,
};
pub const LAYOUT__874: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__875,
    mw: LAYOUT__883,
};
pub const LAYOUT__886: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
};
pub const LAYOUT__887: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
};
pub const LAYOUT__888: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    }],
};
pub const LAYOUT__891: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
};
pub const LAYOUT__890: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__891 };
pub const LAYOUT__892: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__891 };
pub const LAYOUT__889: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__890,
    arm1: LAYOUT__892,
};
pub const LAYOUT__885: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__886,
    high: LAYOUT__887,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 201 },
    },
    _arguments_field_to_word__0: LAYOUT__888,
    _2: LAYOUT__889,
};
pub const LAYOUT__893: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__733,
    _0: LAYOUT__734,
};
pub const LAYOUT__884: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__885,
    mw: LAYOUT__893,
};
pub const LAYOUT__896: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
};
pub const LAYOUT__897: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__898: &_Arguments_FieldToWord__0Layout = &_Arguments_FieldToWord__0Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    }],
};
pub const LAYOUT__901: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__900: &FieldToWord__0Arm0_SuperLayout =
    &FieldToWord__0Arm0_SuperLayout { _0: LAYOUT__901 };
pub const LAYOUT__902: &FieldToWord__0Arm1_SuperLayout =
    &FieldToWord__0Arm1_SuperLayout { _0: LAYOUT__901 };
pub const LAYOUT__899: &FieldToWord__0Layout = &FieldToWord__0Layout {
    arm0: LAYOUT__900,
    arm1: LAYOUT__902,
};
pub const LAYOUT__895: &FieldToWordLayout = &FieldToWordLayout {
    low: LAYOUT__896,
    high: LAYOUT__897,
    low_is_zero: &NondetRegLayout {
        _super: &Reg { offset: 202 },
    },
    _arguments_field_to_word__0: LAYOUT__898,
    _2: LAYOUT__899,
};
pub const LAYOUT__903: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__738,
    _0: LAYOUT__739,
};
pub const LAYOUT__894: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    ftw: LAYOUT__895,
    mw: LAYOUT__903,
};
pub const LAYOUT__824: &PoseidonStoreOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__825,
    LAYOUT__835,
    LAYOUT__844,
    LAYOUT__854,
    LAYOUT__864,
    LAYOUT__874,
    LAYOUT__884,
    LAYOUT__894,
];
pub const LAYOUT__823: &PoseidonStoreOutLayout = &PoseidonStoreOutLayout {
    _super: LAYOUT__665,
    _1: LAYOUT__824,
    is_normal: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 203 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 204 },
        },
    },
    ext_inv: &NondetExtRegLayout {
        _super: &Reg { offset: 205 },
    },
};
pub const LAYOUT__811: &PoseidonDoOut_SuperLayout = &PoseidonDoOut_SuperLayout {
    _super: LAYOUT__665,
    arm0: LAYOUT__812,
    arm1: LAYOUT__823,
};
pub const LAYOUT__904: &_Arguments_PoseidonDoOut_SuperLayout =
    &_Arguments_PoseidonDoOut_SuperLayout {
        memory_arg: LAYOUT__668,
        cycle_arg: LAYOUT__685,
        arg_u16: LAYOUT__686,
    };
pub const LAYOUT__810: &PoseidonDoOutLayout = &PoseidonDoOutLayout {
    _super: LAYOUT__811,
    _arguments_poseidon_do_out__super: LAYOUT__904,
};
pub const LAYOUT__809: &Poseidon0StateArm5Layout = &Poseidon0StateArm5Layout {
    _super: LAYOUT__810,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    },
};
pub const LAYOUT__907: &PoseidonPaging_SuperLayout = &PoseidonPaging_SuperLayout {
    _super: LAYOUT__665,
    arm0: LAYOUT__665,
    arm1: LAYOUT__665,
    arm2: LAYOUT__665,
    arm3: LAYOUT__665,
    arm4: LAYOUT__665,
    arm5: LAYOUT__665,
};
pub const LAYOUT__909: &NondetRegLayout6LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
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
];
pub const LAYOUT__908: &OneHot_6_Layout = &OneHot_6_Layout {
    _super: LAYOUT__909,
};
pub const LAYOUT__911: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
    },
};
pub const LAYOUT__910: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__827,
    _0: LAYOUT__911,
};
pub const LAYOUT__912: &_Arguments_PoseidonPaging__1Layout = &_Arguments_PoseidonPaging__1Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    }],
    arg_u8: &[&ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    }],
};
pub const LAYOUT__916: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    },
};
pub const LAYOUT__915: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__828,
    _0: LAYOUT__916,
};
pub const LAYOUT__914: &PoseidonPaging__1Arm0_SuperLayout =
    &PoseidonPaging__1Arm0_SuperLayout { _0: LAYOUT__915 };
pub const LAYOUT__917: &PoseidonPaging__1Arm1_SuperLayout =
    &PoseidonPaging__1Arm1_SuperLayout { _0: LAYOUT__915 };
pub const LAYOUT__913: &PoseidonPaging__1Layout = &PoseidonPaging__1Layout {
    arm0: LAYOUT__914,
    arm1: LAYOUT__917,
};
pub const LAYOUT__906: &PoseidonPagingLayout = &PoseidonPagingLayout {
    _super: LAYOUT__907,
    cur_idx: &NondetRegLayout {
        _super: &Reg { offset: 195 },
    },
    cur_mode: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    mode_split: LAYOUT__908,
    _0: LAYOUT__910,
    _arguments_poseidon_paging__1: LAYOUT__912,
    _3: LAYOUT__913,
    _4: &NondetRegLayout {
        _super: &Reg { offset: 203 },
    },
};
pub const LAYOUT__905: &Poseidon0StateArm6Layout = &Poseidon0StateArm6Layout {
    _super: LAYOUT__906,
    _extra0: LAYOUT__669,
    _extra1: LAYOUT__670,
    _extra2: LAYOUT__671,
    _extra3: LAYOUT__672,
    _extra4: LAYOUT__673,
    _extra5: LAYOUT__674,
    _extra6: LAYOUT__675,
    _extra7: LAYOUT__676,
    _extra8: LAYOUT__677,
    _extra9: LAYOUT__678,
    _extra10: LAYOUT__679,
    _extra11: LAYOUT__680,
    _extra12: LAYOUT__681,
    _extra13: LAYOUT__682,
    _extra14: LAYOUT__683,
    _extra15: LAYOUT__684,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
    _extra40: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra41: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
    _extra42: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
    },
    _extra43: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra44: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra45: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
    },
};
pub const LAYOUT__921: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__826,
    mw: LAYOUT__834,
};
pub const LAYOUT__922: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__836,
    mw: LAYOUT__843,
};
pub const LAYOUT__923: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__845,
    mw: LAYOUT__853,
};
pub const LAYOUT__924: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__855,
    mw: LAYOUT__863,
};
pub const LAYOUT__925: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__865,
    mw: LAYOUT__873,
};
pub const LAYOUT__926: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__875,
    mw: LAYOUT__883,
};
pub const LAYOUT__927: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__885,
    mw: LAYOUT__893,
};
pub const LAYOUT__928: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    ftw: LAYOUT__895,
    mw: LAYOUT__903,
};
pub const LAYOUT__920: &PoseidonStoreState__0_SuperLayout8LayoutArray = &[
    LAYOUT__921,
    LAYOUT__922,
    LAYOUT__923,
    LAYOUT__924,
    LAYOUT__925,
    LAYOUT__926,
    LAYOUT__927,
    LAYOUT__928,
];
pub const LAYOUT__919: &PoseidonStoreStateLayout = &PoseidonStoreStateLayout {
    _super: LAYOUT__665,
    _1: LAYOUT__920,
};
pub const LAYOUT__918: &Poseidon0StateArm7Layout = &Poseidon0StateArm7Layout {
    _super: LAYOUT__919,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
    },
};
pub const LAYOUT__688: &Poseidon0StateLayout = &Poseidon0StateLayout {
    _super: LAYOUT__665,
    arm0: LAYOUT__689,
    arm1: LAYOUT__714,
    arm2: LAYOUT__741,
    arm3: LAYOUT__807,
    arm4: LAYOUT__808,
    arm5: LAYOUT__809,
    arm6: LAYOUT__905,
    arm7: LAYOUT__918,
};
pub const LAYOUT__663: &Poseidon0Layout = &Poseidon0Layout {
    _0: LAYOUT__664,
    state: LAYOUT__665,
    _arguments_poseidon0_state: LAYOUT__667,
    state_redef: LAYOUT__688,
};
pub const LAYOUT__930: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__935: &SBoxLayout24LayoutArray = &[
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
];
pub const LAYOUT__934: &DoExtRoundLayout = &DoExtRoundLayout { _1: LAYOUT__935 };
pub const LAYOUT__937: &NondetRegLayout8LayoutArray = &[
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
    &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
];
pub const LAYOUT__936: &OneHot_8_Layout = &OneHot_8_Layout {
    _super: LAYOUT__937,
};
pub const LAYOUT__933: &DoExtRoundByIdxLayout = &DoExtRoundByIdxLayout {
    _super: LAYOUT__934,
    idx_hot: LAYOUT__936,
};
pub const LAYOUT__932: &PoseidonExtRoundLayout = &PoseidonExtRoundLayout {
    _super: LAYOUT__665,
    is_round3: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    is_round7: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
    last_block: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
    next_inner: LAYOUT__933,
};
pub const LAYOUT__941: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
};
pub const LAYOUT__942: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__943: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
};
pub const LAYOUT__944: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
};
pub const LAYOUT__945: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
    },
};
pub const LAYOUT__946: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
};
pub const LAYOUT__947: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
};
pub const LAYOUT__948: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
};
pub const LAYOUT__949: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__950: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
    },
};
pub const LAYOUT__951: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
};
pub const LAYOUT__952: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
};
pub const LAYOUT__953: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
};
pub const LAYOUT__954: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
};
pub const LAYOUT__955: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
};
pub const LAYOUT__956: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__957: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
};
pub const LAYOUT__958: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
};
pub const LAYOUT__959: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
};
pub const LAYOUT__960: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
};
pub const LAYOUT__961: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__940: &DoIntRoundLayout21LayoutArray = &[
    LAYOUT__941,
    LAYOUT__942,
    LAYOUT__943,
    LAYOUT__944,
    LAYOUT__945,
    LAYOUT__946,
    LAYOUT__947,
    LAYOUT__948,
    LAYOUT__949,
    LAYOUT__950,
    LAYOUT__951,
    LAYOUT__952,
    LAYOUT__953,
    LAYOUT__954,
    LAYOUT__955,
    LAYOUT__956,
    LAYOUT__957,
    LAYOUT__958,
    LAYOUT__959,
    LAYOUT__960,
    LAYOUT__961,
];
pub const LAYOUT__939: &DoIntRoundsLayout = &DoIntRoundsLayout {
    _super: LAYOUT__940,
};
pub const LAYOUT__938: &PoseidonIntRoundsLayout = &PoseidonIntRoundsLayout {
    _super: LAYOUT__665,
    next_inner: LAYOUT__939,
};
pub const LAYOUT__931: &Poseidon1StateLayout = &Poseidon1StateLayout {
    _super: LAYOUT__665,
    arm0: LAYOUT__932,
    arm1: LAYOUT__938,
    arm2: LAYOUT__665,
    arm3: LAYOUT__665,
    arm4: LAYOUT__665,
    arm5: LAYOUT__665,
    arm6: LAYOUT__665,
    arm7: LAYOUT__665,
};
pub const LAYOUT__929: &Poseidon1Layout = &Poseidon1Layout {
    _0: LAYOUT__930,
    state: LAYOUT__665,
    state_redef: LAYOUT__931,
};
pub const LAYOUT__963: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__965: &NondetRegLayout32LayoutArray = &[
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
];
pub const LAYOUT__966: &NondetRegLayout32LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
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
];
pub const LAYOUT__967: &NondetRegLayout32LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
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
];
pub const LAYOUT__964: &ShaStateLayout = &ShaStateLayout {
    state_in_addr: &NondetRegLayout {
        _super: &Reg { offset: 28 },
    },
    state_out_addr: &NondetRegLayout {
        _super: &Reg { offset: 29 },
    },
    data_addr: &NondetRegLayout {
        _super: &Reg { offset: 30 },
    },
    count: &NondetRegLayout {
        _super: &Reg { offset: 31 },
    },
    k_addr: &NondetRegLayout {
        _super: &Reg { offset: 32 },
    },
    round: &NondetRegLayout {
        _super: &Reg { offset: 33 },
    },
    next_state: &NondetRegLayout {
        _super: &Reg { offset: 34 },
    },
    a: LAYOUT__965,
    e: LAYOUT__966,
    w: LAYOUT__967,
};
pub const LAYOUT__970: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__971: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__972: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 140 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 141 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 143 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 144 },
    },
};
pub const LAYOUT__973: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 145 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 141 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 146 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 147 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 148 },
    },
};
pub const LAYOUT__974: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 149 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 150 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 151 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 152 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 153 },
    },
};
pub const LAYOUT__975: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 150 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 156 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 157 },
    },
};
pub const LAYOUT__976: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 161 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 162 },
    },
};
pub const LAYOUT__977: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 163 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 166 },
    },
};
pub const LAYOUT__978: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 167 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 168 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 169 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 170 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
};
pub const LAYOUT__979: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 172 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 168 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 173 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 174 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
};
pub const LAYOUT__969: &MemoryArgLayout10LayoutArray = &[
    LAYOUT__970,
    LAYOUT__971,
    LAYOUT__972,
    LAYOUT__973,
    LAYOUT__974,
    LAYOUT__975,
    LAYOUT__976,
    LAYOUT__977,
    LAYOUT__978,
    LAYOUT__979,
];
pub const LAYOUT__980: &CycleArgLayout5LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
];
pub const LAYOUT__968: &_Arguments_Sha0StateLayout = &_Arguments_Sha0StateLayout {
    memory_arg: LAYOUT__969,
    cycle_arg: LAYOUT__980,
};
pub const LAYOUT__985: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__970,
    new_txn: LAYOUT__971,
};
pub const LAYOUT__987: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
};
pub const LAYOUT__986: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__987 };
pub const LAYOUT__984: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__985,
    _0: LAYOUT__986,
};
pub const LAYOUT__983: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__984,
};
pub const LAYOUT__990: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__972,
    new_txn: LAYOUT__973,
};
pub const LAYOUT__992: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__991: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__992 };
pub const LAYOUT__989: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__990,
    _0: LAYOUT__991,
};
pub const LAYOUT__988: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__989,
};
pub const LAYOUT__995: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__974,
    new_txn: LAYOUT__975,
};
pub const LAYOUT__997: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__996: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__997 };
pub const LAYOUT__994: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__995,
    _0: LAYOUT__996,
};
pub const LAYOUT__993: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__994,
};
pub const LAYOUT__999: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__976,
    new_txn: LAYOUT__977,
};
pub const LAYOUT__1001: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
};
pub const LAYOUT__1000: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__1001 };
pub const LAYOUT__998: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__999,
    _0: LAYOUT__1000,
};
pub const LAYOUT__1004: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__978,
    new_txn: LAYOUT__979,
};
pub const LAYOUT__1006: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 185 },
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
pub const LAYOUT__982: &ShaEcallLayout = &ShaEcallLayout {
    _super: LAYOUT__964,
    state_in_addr: LAYOUT__983,
    state_out_addr: LAYOUT__988,
    data_addr: LAYOUT__993,
    _0: LAYOUT__998,
    k_addr: LAYOUT__1002,
};
pub const LAYOUT__1009: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__995,
    _0: LAYOUT__996,
};
pub const LAYOUT__1010: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__999,
    _0: LAYOUT__1000,
};
pub const LAYOUT__1008: &ShaLoadStateLayout = &ShaLoadStateLayout {
    _super: LAYOUT__964,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
    count_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 193 },
        },
    },
    a32: LAYOUT__984,
    e32: LAYOUT__989,
    _0: LAYOUT__1009,
    _1: LAYOUT__1010,
};
pub const LAYOUT__1007: &Sha0StateArm1Layout = &Sha0StateArm1Layout {
    _super: LAYOUT__1008,
    _extra0: LAYOUT__978,
    _extra1: LAYOUT__979,
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__1014: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__965,
};
pub const LAYOUT__1015: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 192 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 193 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 194 },
    },
};
pub const LAYOUT__1016: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1013: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1014,
    low_carry: LAYOUT__1015,
    high_carry: LAYOUT__1016,
};
pub const LAYOUT__1018: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__966,
};
pub const LAYOUT__1019: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1020: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1017: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1018,
    low_carry: LAYOUT__1019,
    high_carry: LAYOUT__1020,
};
pub const LAYOUT__1012: &ShaLoadDataLayout = &ShaLoadDataLayout {
    _super: LAYOUT__964,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
    k: LAYOUT__984,
    w_mem: LAYOUT__989,
    w_bits: LAYOUT__967,
    a: LAYOUT__1013,
    e: LAYOUT__1017,
};
pub const LAYOUT__1011: &Sha0StateArm2Layout = &Sha0StateArm2Layout {
    _super: LAYOUT__1012,
    _extra0: LAYOUT__974,
    _extra1: LAYOUT__975,
    _extra2: LAYOUT__976,
    _extra3: LAYOUT__977,
    _extra4: LAYOUT__978,
    _extra5: LAYOUT__979,
    _extra6: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra7: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__1024: &UnpackReg_32__16_Layout = &UnpackReg_32__16_Layout {
    _super: LAYOUT__967,
};
pub const LAYOUT__1023: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1024,
    low_carry: LAYOUT__1015,
    high_carry: LAYOUT__1016,
};
pub const LAYOUT__1025: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1014,
    low_carry: LAYOUT__1019,
    high_carry: LAYOUT__1020,
};
pub const LAYOUT__1027: &CarryExtractLayout = &CarryExtractLayout {
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
pub const LAYOUT__1028: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 207 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 208 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 209 },
    },
};
pub const LAYOUT__1026: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1018,
    low_carry: LAYOUT__1027,
    high_carry: LAYOUT__1028,
};
pub const LAYOUT__1022: &ShaMixLayout = &ShaMixLayout {
    _super: LAYOUT__964,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
    k: LAYOUT__984,
    w_bits: LAYOUT__1023,
    a: LAYOUT__1025,
    e: LAYOUT__1026,
};
pub const LAYOUT__1021: &Sha0StateArm3Layout = &Sha0StateArm3Layout {
    _super: LAYOUT__1022,
    _extra0: LAYOUT__972,
    _extra1: LAYOUT__973,
    _extra2: LAYOUT__974,
    _extra3: LAYOUT__975,
    _extra4: LAYOUT__976,
    _extra5: LAYOUT__977,
    _extra6: LAYOUT__978,
    _extra7: LAYOUT__979,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__1032: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 194 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 195 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
};
pub const LAYOUT__1033: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 198 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 199 },
    },
};
pub const LAYOUT__1031: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1014,
    low_carry: LAYOUT__1032,
    high_carry: LAYOUT__1033,
};
pub const LAYOUT__1035: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 200 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 201 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 202 },
    },
};
pub const LAYOUT__1036: &CarryExtractLayout = &CarryExtractLayout {
    bit0: &NondetRegLayout {
        _super: &Reg { offset: 203 },
    },
    bit1: &NondetRegLayout {
        _super: &Reg { offset: 204 },
    },
    bit2: &NondetRegLayout {
        _super: &Reg { offset: 205 },
    },
};
pub const LAYOUT__1034: &CarryAndExpandLayout = &CarryAndExpandLayout {
    _super: LAYOUT__1018,
    low_carry: LAYOUT__1035,
    high_carry: LAYOUT__1036,
};
pub const LAYOUT__1037: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__985,
    _0: LAYOUT__986,
};
pub const LAYOUT__1038: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__990,
    _0: LAYOUT__991,
};
pub const LAYOUT__1030: &ShaStoreStateLayout = &ShaStoreStateLayout {
    _super: LAYOUT__964,
    last_round: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
    count_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 193 },
        },
    },
    a: LAYOUT__1031,
    e: LAYOUT__1034,
    _1: LAYOUT__1037,
    _2: LAYOUT__1038,
};
pub const LAYOUT__1029: &Sha0StateArm4Layout = &Sha0StateArm4Layout {
    _super: LAYOUT__1030,
    _extra0: LAYOUT__974,
    _extra1: LAYOUT__975,
    _extra2: LAYOUT__976,
    _extra3: LAYOUT__977,
    _extra4: LAYOUT__978,
    _extra5: LAYOUT__979,
    _extra6: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra7: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__1039: &Sha0StateArm5Layout = &Sha0StateArm5Layout {
    _super: LAYOUT__964,
    _extra0: LAYOUT__970,
    _extra1: LAYOUT__971,
    _extra2: LAYOUT__972,
    _extra3: LAYOUT__973,
    _extra4: LAYOUT__974,
    _extra5: LAYOUT__975,
    _extra6: LAYOUT__976,
    _extra7: LAYOUT__977,
    _extra8: LAYOUT__978,
    _extra9: LAYOUT__979,
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__1040: &Sha0StateArm6Layout = &Sha0StateArm6Layout {
    _super: LAYOUT__964,
    _extra0: LAYOUT__970,
    _extra1: LAYOUT__971,
    _extra2: LAYOUT__972,
    _extra3: LAYOUT__973,
    _extra4: LAYOUT__974,
    _extra5: LAYOUT__975,
    _extra6: LAYOUT__976,
    _extra7: LAYOUT__977,
    _extra8: LAYOUT__978,
    _extra9: LAYOUT__979,
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__1041: &Sha0StateArm7Layout = &Sha0StateArm7Layout {
    _super: LAYOUT__964,
    _extra0: LAYOUT__970,
    _extra1: LAYOUT__971,
    _extra2: LAYOUT__972,
    _extra3: LAYOUT__973,
    _extra4: LAYOUT__974,
    _extra5: LAYOUT__975,
    _extra6: LAYOUT__976,
    _extra7: LAYOUT__977,
    _extra8: LAYOUT__978,
    _extra9: LAYOUT__979,
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__981: &Sha0StateLayout = &Sha0StateLayout {
    _super: LAYOUT__964,
    arm0: LAYOUT__982,
    arm1: LAYOUT__1007,
    arm2: LAYOUT__1011,
    arm3: LAYOUT__1021,
    arm4: LAYOUT__1029,
    arm5: LAYOUT__1039,
    arm6: LAYOUT__1040,
    arm7: LAYOUT__1041,
};
pub const LAYOUT__962: &Sha0Layout = &Sha0Layout {
    _0: LAYOUT__963,
    state: LAYOUT__964,
    _arguments_sha0_state: LAYOUT__968,
    state_redef: LAYOUT__981,
};
pub const LAYOUT__6: &TopInstResultLayout = &TopInstResultLayout {
    _selector: LAYOUT__5,
    arm0: LAYOUT__7,
    arm1: LAYOUT__88,
    arm2: LAYOUT__106,
    arm3: LAYOUT__119,
    arm4: LAYOUT__203,
    arm5: LAYOUT__330,
    arm6: LAYOUT__390,
    arm7: LAYOUT__433,
    arm8: LAYOUT__605,
    arm9: LAYOUT__663,
    arm10: LAYOUT__929,
    arm11: LAYOUT__962,
};
pub const LAYOUT__0: &TopLayout = &TopLayout {
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    next_pc_low: &NondetRegLayout {
        _super: &Reg { offset: 13 },
    },
    next_pc_high: &NondetRegLayout {
        _super: &Reg { offset: 14 },
    },
    next_state_0: &NondetRegLayout {
        _super: &Reg { offset: 15 },
    },
    next_machine_mode: &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    is_first_cycle: &NondetRegLayout {
        _super: &Reg { offset: 17 },
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
        _super: &Reg { offset: 18 },
    },
    minor: &NondetRegLayout {
        _super: &Reg { offset: 19 },
    },
    inst_input: LAYOUT__1,
    major_onehot: LAYOUT__4,
    inst_result: LAYOUT__6,
};
pub const LAYOUT__1043: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1042: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1043,
};
pub const LAYOUT__1045: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1044: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1045,
};
pub const LAYOUT__1047: &DigestRegValues_SuperLayout8LayoutArray = &[
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
    },
];
pub const LAYOUT__1046: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1047,
};
pub const LAYOUT__1049: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__1048: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__1049,
};
pub const LAYOUT__1050: &_accumLayout = &_accumLayout {
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
};
pub const LAYOUT_TEST_SUCC_RUN_ACCUM: &LayoutAccumLayout = &LayoutAccumLayout {
    columns: &[
        &Reg { offset: 0 },
        &Reg { offset: 4 },
        &Reg { offset: 8 },
        &Reg { offset: 12 },
        &Reg { offset: 16 },
        &Reg { offset: 20 },
        &Reg { offset: 24 },
        &Reg { offset: 28 },
        &Reg { offset: 32 },
        &Reg { offset: 36 },
        &Reg { offset: 40 },
        &Reg { offset: 44 },
        &Reg { offset: 48 },
        &Reg { offset: 52 },
        &Reg { offset: 56 },
        &Reg { offset: 60 },
        &Reg { offset: 64 },
        &Reg { offset: 68 },
        &Reg { offset: 72 },
        &Reg { offset: 76 },
    ],
};
pub const LAYOUT_TOP_ACCUM: &LayoutAccumLayout = &LayoutAccumLayout {
    columns: &[
        &Reg { offset: 0 },
        &Reg { offset: 4 },
        &Reg { offset: 8 },
        &Reg { offset: 12 },
        &Reg { offset: 16 },
        &Reg { offset: 20 },
        &Reg { offset: 24 },
        &Reg { offset: 28 },
        &Reg { offset: 32 },
        &Reg { offset: 36 },
        &Reg { offset: 40 },
        &Reg { offset: 44 },
        &Reg { offset: 48 },
        &Reg { offset: 52 },
        &Reg { offset: 56 },
        &Reg { offset: 60 },
        &Reg { offset: 64 },
        &Reg { offset: 68 },
        &Reg { offset: 72 },
        &Reg { offset: 76 },
    ],
};
pub const LAYOUT_TEST_SUCC_RUN: &TestSuccRunLayout = &TestSuccRunLayout { _0: LAYOUT__0 };
pub const LAYOUT_TOP: &TopLayout = &TopLayout {
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    next_pc_low: &NondetRegLayout {
        _super: &Reg { offset: 13 },
    },
    next_pc_high: &NondetRegLayout {
        _super: &Reg { offset: 14 },
    },
    next_state_0: &NondetRegLayout {
        _super: &Reg { offset: 15 },
    },
    next_machine_mode: &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    is_first_cycle: &NondetRegLayout {
        _super: &Reg { offset: 17 },
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
        _super: &Reg { offset: 18 },
    },
    minor: &NondetRegLayout {
        _super: &Reg { offset: 19 },
    },
    inst_input: LAYOUT__1,
    major_onehot: LAYOUT__4,
    inst_result: LAYOUT__6,
};
pub const LAYOUT_GLOBAL: &_globalLayout = &_globalLayout {
    input: LAYOUT__1042,
    is_terminate: &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    output: LAYOUT__1044,
    rng: &NondetExtRegLayout {
        _super: &Reg { offset: 33 },
    },
    shutdown_cycle: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    state_in: LAYOUT__1046,
    state_out: LAYOUT__1048,
    term_a0high: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    term_a0low: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    term_a1high: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    term_a1low: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
};
pub const LAYOUT_MIX: &_mixLayout = &_mixLayout {
    randomness: LAYOUT__1050,
};
