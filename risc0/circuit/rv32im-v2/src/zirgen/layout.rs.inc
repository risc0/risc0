pub const LAYOUT__3: &NondetRegLayout8LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 19 },
    },
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
];
pub const LAYOUT__2: &OneHot_8_Layout = &OneHot_8_Layout { _super: LAYOUT__3 };
pub const LAYOUT__1: &InstInputLayout = &InstInputLayout {
    minor_onehot: LAYOUT__2,
};
pub const LAYOUT__5: &NondetRegLayout11LayoutArray = &[
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
];
pub const LAYOUT__4: &OneHot_11_Layout = &OneHot_11_Layout { _super: LAYOUT__5 };
pub const LAYOUT__10: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__11: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
    },
};
pub const LAYOUT__9: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__10,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
    high16: LAYOUT__11,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
};
pub const LAYOUT__13: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__14: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
    },
};
pub const LAYOUT__12: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__13,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    high16: LAYOUT__14,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
};
pub const LAYOUT__18: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 55 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 56 },
    },
};
pub const LAYOUT__19: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 52 },
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
pub const LAYOUT__17: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__18,
    new_txn: LAYOUT__19,
};
pub const LAYOUT__21: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 62 },
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
            _super: &Reg { offset: 49 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 51 },
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
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__25: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
};
pub const LAYOUT__28: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__27: &U16RegLayout = &U16RegLayout { ret: LAYOUT__28 };
pub const LAYOUT__29: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__26: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    upper_diff: LAYOUT__27,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
    med14: LAYOUT__29,
};
pub const LAYOUT__32: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 90 },
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
pub const LAYOUT__33: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 90 },
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
pub const LAYOUT__31: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__32,
    new_txn: LAYOUT__33,
};
pub const LAYOUT__35: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
};
pub const LAYOUT__34: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__35 };
pub const LAYOUT__30: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__31,
    _0: LAYOUT__34,
};
pub const LAYOUT__24: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__25,
    pc_addr: LAYOUT__26,
    load_inst: LAYOUT__30,
};
pub const LAYOUT__39: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__40: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__38: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__39,
    new_txn: LAYOUT__40,
};
pub const LAYOUT__42: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__41: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__42 };
pub const LAYOUT__37: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__38,
    _0: LAYOUT__41,
};
pub const LAYOUT__36: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__37,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
};
pub const LAYOUT__46: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__47: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__45: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__46,
    new_txn: LAYOUT__47,
};
pub const LAYOUT__49: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
    },
};
pub const LAYOUT__48: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__49 };
pub const LAYOUT__44: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__45,
    _0: LAYOUT__48,
};
pub const LAYOUT__43: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__44,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 124 },
    },
};
pub const LAYOUT__23: &MiscInputLayout = &MiscInputLayout {
    decoded: LAYOUT__24,
    rs1: LAYOUT__36,
    rs2: LAYOUT__43,
};
pub const LAYOUT__51: &ArgU16Layout5LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
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
];
pub const LAYOUT__50: &_Arguments_Misc0MiscOutputLayout = &_Arguments_Misc0MiscOutputLayout {
    arg_u16: LAYOUT__51,
};
pub const LAYOUT__53: &Misc0MiscOutputArm0Layout = &Misc0MiscOutputArm0Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__54: &Misc0MiscOutputArm1Layout = &Misc0MiscOutputArm1Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__61: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__60: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__61 };
pub const LAYOUT__63: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__62: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__63 };
pub const LAYOUT__59: &BitwiseAndU16Layout = &BitwiseAndU16Layout {
    bits_x: LAYOUT__60,
    bits_y: LAYOUT__62,
};
pub const LAYOUT__66: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__65: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__66 };
pub const LAYOUT__68: &NondetRegLayout16LayoutArray = &[
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
];
pub const LAYOUT__67: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__68 };
pub const LAYOUT__64: &BitwiseAndU16Layout = &BitwiseAndU16Layout {
    bits_x: LAYOUT__65,
    bits_y: LAYOUT__67,
};
pub const LAYOUT__58: &BitwiseAndLayout = &BitwiseAndLayout {
    _0: LAYOUT__59,
    _1: LAYOUT__64,
};
pub const LAYOUT__57: &BitwiseXorLayout = &BitwiseXorLayout { and_xy: LAYOUT__58 };
pub const LAYOUT__56: &OpXORLayout = &OpXORLayout { _0: LAYOUT__57 };
pub const LAYOUT__55: &Misc0MiscOutputArm2Layout = &Misc0MiscOutputArm2Layout {
    _super: LAYOUT__56,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__71: &BitwiseOrLayout = &BitwiseOrLayout { and_xy: LAYOUT__58 };
pub const LAYOUT__70: &OpORLayout = &OpORLayout { _0: LAYOUT__71 };
pub const LAYOUT__69: &Misc0MiscOutputArm3Layout = &Misc0MiscOutputArm3Layout {
    _super: LAYOUT__70,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__73: &OpANDLayout = &OpANDLayout { _0: LAYOUT__58 };
pub const LAYOUT__72: &Misc0MiscOutputArm4Layout = &Misc0MiscOutputArm4Layout {
    _super: LAYOUT__73,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__77: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
};
pub const LAYOUT__78: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
};
pub const LAYOUT__76: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__77,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 125 },
    },
    high16: LAYOUT__78,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
};
pub const LAYOUT__80: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__79: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    rest_times_two: LAYOUT__80,
};
pub const LAYOUT__82: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__81: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
    rest_times_two: LAYOUT__82,
};
pub const LAYOUT__84: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__83: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    rest_times_two: LAYOUT__84,
};
pub const LAYOUT__75: &CmpLessThanLayout = &CmpLessThanLayout {
    diff: LAYOUT__76,
    s1: LAYOUT__79,
    s2: LAYOUT__81,
    s3: LAYOUT__83,
    overflow: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
    is_less_than: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
};
pub const LAYOUT__74: &OpSLTLayout = &OpSLTLayout { cmp: LAYOUT__75 };
pub const LAYOUT__87: &CmpLessThanUnsignedLayout = &CmpLessThanUnsignedLayout { diff: LAYOUT__76 };
pub const LAYOUT__86: &OpSLTULayout = &OpSLTULayout { cmp: LAYOUT__87 };
pub const LAYOUT__85: &Misc0MiscOutputArm6Layout = &Misc0MiscOutputArm6Layout {
    _super: LAYOUT__86,
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
};
pub const LAYOUT__88: &Misc0MiscOutputArm7Layout = &Misc0MiscOutputArm7Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__52: &Misc0MiscOutputLayout = &Misc0MiscOutputLayout {
    arm0: LAYOUT__53,
    arm1: LAYOUT__54,
    arm2: LAYOUT__55,
    arm3: LAYOUT__69,
    arm4: LAYOUT__72,
    arm5: LAYOUT__74,
    arm6: LAYOUT__85,
    arm7: LAYOUT__88,
};
pub const LAYOUT__7: &Misc0Layout = &Misc0Layout {
    _super: LAYOUT__8,
    _0: LAYOUT__22,
    input: LAYOUT__23,
    _arguments_misc0_misc_output: LAYOUT__50,
    misc_output: LAYOUT__52,
};
pub const LAYOUT__90: &_Arguments_Misc1MiscOutputLayout = &_Arguments_Misc1MiscOutputLayout {
    arg_u16: LAYOUT__51,
};
pub const LAYOUT__93: &OpXORILayout = &OpXORILayout { _0: LAYOUT__57 };
pub const LAYOUT__92: &Misc1MiscOutputArm0Layout = &Misc1MiscOutputArm0Layout {
    _super: LAYOUT__93,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__95: &OpORILayout = &OpORILayout { _0: LAYOUT__71 };
pub const LAYOUT__94: &Misc1MiscOutputArm1Layout = &Misc1MiscOutputArm1Layout {
    _super: LAYOUT__95,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__97: &OpANDILayout = &OpANDILayout { _0: LAYOUT__58 };
pub const LAYOUT__96: &Misc1MiscOutputArm2Layout = &Misc1MiscOutputArm2Layout {
    _super: LAYOUT__97,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__98: &OpSLTILayout = &OpSLTILayout { cmp: LAYOUT__75 };
pub const LAYOUT__100: &OpSLTIULayout = &OpSLTIULayout { cmp: LAYOUT__87 };
pub const LAYOUT__99: &Misc1MiscOutputArm4Layout = &Misc1MiscOutputArm4Layout {
    _super: LAYOUT__100,
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
};
pub const LAYOUT__103: &CmpEqualLayout = &CmpEqualLayout {
    low_same: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    high_same: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    is_equal: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
};
pub const LAYOUT__102: &OpBEQLayout = &OpBEQLayout { cmp: LAYOUT__103 };
pub const LAYOUT__101: &Misc1MiscOutputArm5Layout = &Misc1MiscOutputArm5Layout {
    _super: LAYOUT__102,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__105: &OpBNELayout = &OpBNELayout { cmp: LAYOUT__103 };
pub const LAYOUT__104: &Misc1MiscOutputArm6Layout = &Misc1MiscOutputArm6Layout {
    _super: LAYOUT__105,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__106: &OpBLTLayout = &OpBLTLayout { cmp: LAYOUT__75 };
pub const LAYOUT__91: &Misc1MiscOutputLayout = &Misc1MiscOutputLayout {
    arm0: LAYOUT__92,
    arm1: LAYOUT__94,
    arm2: LAYOUT__96,
    arm3: LAYOUT__98,
    arm4: LAYOUT__99,
    arm5: LAYOUT__101,
    arm6: LAYOUT__104,
    arm7: LAYOUT__106,
};
pub const LAYOUT__89: &Misc1Layout = &Misc1Layout {
    _super: LAYOUT__8,
    _0: LAYOUT__22,
    input: LAYOUT__23,
    _arguments_misc1_misc_output: LAYOUT__90,
    misc_output: LAYOUT__91,
};
pub const LAYOUT__108: &_Arguments_Misc2MiscOutputLayout = &_Arguments_Misc2MiscOutputLayout {
    arg_u16: LAYOUT__51,
};
pub const LAYOUT__110: &OpBGELayout = &OpBGELayout { cmp: LAYOUT__75 };
pub const LAYOUT__112: &OpBLTULayout = &OpBLTULayout { cmp: LAYOUT__87 };
pub const LAYOUT__111: &Misc2MiscOutputArm1Layout = &Misc2MiscOutputArm1Layout {
    _super: LAYOUT__112,
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
};
pub const LAYOUT__114: &OpBGEULayout = &OpBGEULayout { cmp: LAYOUT__87 };
pub const LAYOUT__113: &Misc2MiscOutputArm2Layout = &Misc2MiscOutputArm2Layout {
    _super: LAYOUT__114,
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
};
pub const LAYOUT__115: &Misc2MiscOutputArm3Layout = &Misc2MiscOutputArm3Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__116: &Misc2MiscOutputArm4Layout = &Misc2MiscOutputArm4Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__117: &Misc2MiscOutputArm5Layout = &Misc2MiscOutputArm5Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__118: &Misc2MiscOutputArm6Layout = &Misc2MiscOutputArm6Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__119: &Misc2MiscOutputArm7Layout = &Misc2MiscOutputArm7Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__109: &Misc2MiscOutputLayout = &Misc2MiscOutputLayout {
    arm0: LAYOUT__110,
    arm1: LAYOUT__111,
    arm2: LAYOUT__113,
    arm3: LAYOUT__115,
    arm4: LAYOUT__116,
    arm5: LAYOUT__117,
    arm6: LAYOUT__118,
    arm7: LAYOUT__119,
};
pub const LAYOUT__107: &Misc2Layout = &Misc2Layout {
    _super: LAYOUT__8,
    _0: LAYOUT__22,
    input: LAYOUT__23,
    _arguments_misc2_misc_output: LAYOUT__108,
    misc_output: LAYOUT__109,
};
pub const LAYOUT__121: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__124: &DecoderLayout = &DecoderLayout {
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
pub const LAYOUT__127: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
};
pub const LAYOUT__126: &U16RegLayout = &U16RegLayout { ret: LAYOUT__127 };
pub const LAYOUT__128: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
};
pub const LAYOUT__125: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    upper_diff: LAYOUT__126,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
    med14: LAYOUT__128,
};
pub const LAYOUT__131: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__132: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__130: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__131,
    new_txn: LAYOUT__132,
};
pub const LAYOUT__134: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__133: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__134 };
pub const LAYOUT__129: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__130,
    _0: LAYOUT__133,
};
pub const LAYOUT__123: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__124,
    pc_addr: LAYOUT__125,
    load_inst: LAYOUT__129,
};
pub const LAYOUT__138: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__139: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__137: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__138,
    new_txn: LAYOUT__139,
};
pub const LAYOUT__141: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
};
pub const LAYOUT__140: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__141 };
pub const LAYOUT__136: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__137,
    _0: LAYOUT__140,
};
pub const LAYOUT__135: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__136,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
};
pub const LAYOUT__145: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__146: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__144: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__145,
    new_txn: LAYOUT__146,
};
pub const LAYOUT__148: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
};
pub const LAYOUT__147: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__148 };
pub const LAYOUT__143: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__144,
    _0: LAYOUT__147,
};
pub const LAYOUT__142: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__143,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
};
pub const LAYOUT__122: &MulInputLayout = &MulInputLayout {
    decoded: LAYOUT__123,
    rs1: LAYOUT__135,
    rs2: LAYOUT__142,
};
pub const LAYOUT__150: &ArgU16Layout6LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
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
pub const LAYOUT__151: &ArgU8Layout13LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
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
];
pub const LAYOUT__149: &_Arguments_Mul0MulOutputLayout = &_Arguments_Mul0MulOutputLayout {
    arg_u16: LAYOUT__150,
    arg_u8: LAYOUT__151,
};
pub const LAYOUT__156: &NondetRegLayout5LayoutArray = &[
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
pub const LAYOUT__155: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__156,
};
pub const LAYOUT__154: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__155,
    check_u16: LAYOUT__77,
    b3: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    low: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
    high: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
};
pub const LAYOUT__160: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__161: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
};
pub const LAYOUT__162: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__163: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
};
pub const LAYOUT__164: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
};
pub const LAYOUT__159: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__160,
    b1: LAYOUT__161,
    b2: LAYOUT__162,
    b3: LAYOUT__163,
    b3_top7times2: LAYOUT__164,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
};
pub const LAYOUT__166: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
};
pub const LAYOUT__167: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
};
pub const LAYOUT__168: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
};
pub const LAYOUT__169: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
};
pub const LAYOUT__170: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
};
pub const LAYOUT__165: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__166,
    b1: LAYOUT__167,
    b2: LAYOUT__168,
    b3: LAYOUT__169,
    b3_top7times2: LAYOUT__170,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
};
pub const LAYOUT__172: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__171: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__80,
    carry_byte: LAYOUT__172,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__174: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
};
pub const LAYOUT__173: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__82,
    carry_byte: LAYOUT__174,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__176: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
};
pub const LAYOUT__175: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__84,
    carry_byte: LAYOUT__176,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__158: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__159,
    bx: LAYOUT__165,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    c_rest_times2: LAYOUT__78,
    s0: LAYOUT__171,
    s1: LAYOUT__173,
    s2: LAYOUT__175,
    s3_out: LAYOUT__10,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__157: &DoMulLayout = &DoMulLayout { mul: LAYOUT__158 };
pub const LAYOUT__153: &OpSLLLayout = &OpSLLLayout {
    shift_mul: LAYOUT__154,
    _0: LAYOUT__157,
};
pub const LAYOUT__177: &OpSLLILayout = &OpSLLILayout {
    shift_mul: LAYOUT__154,
    _0: LAYOUT__157,
};
pub const LAYOUT__182: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__160,
    b1: LAYOUT__161,
    b2: LAYOUT__162,
    b3: LAYOUT__163,
    b3_top7times2: LAYOUT__164,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
};
pub const LAYOUT__183: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__166,
    b1: LAYOUT__167,
    b2: LAYOUT__168,
    b3: LAYOUT__169,
    b3_top7times2: LAYOUT__170,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
};
pub const LAYOUT__184: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__78,
    carry_byte: LAYOUT__172,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
};
pub const LAYOUT__185: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__80,
    carry_byte: LAYOUT__174,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
};
pub const LAYOUT__186: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__82,
    carry_byte: LAYOUT__176,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
};
pub const LAYOUT__181: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__182,
    bx: LAYOUT__183,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    c_rest_times2: LAYOUT__77,
    s0: LAYOUT__184,
    s1: LAYOUT__185,
    s2: LAYOUT__186,
    s3_out: LAYOUT__84,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
};
pub const LAYOUT__180: &DoMulLayout = &DoMulLayout { mul: LAYOUT__181 };
pub const LAYOUT__179: &OpMULLayout = &OpMULLayout { _0: LAYOUT__180 };
pub const LAYOUT__178: &Mul0MulOutputArm2Layout = &Mul0MulOutputArm2Layout {
    _super: LAYOUT__179,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__188: &OpMULHLayout = &OpMULHLayout { _0: LAYOUT__180 };
pub const LAYOUT__187: &Mul0MulOutputArm3Layout = &Mul0MulOutputArm3Layout {
    _super: LAYOUT__188,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__190: &OpMULHSULayout = &OpMULHSULayout { _0: LAYOUT__180 };
pub const LAYOUT__189: &Mul0MulOutputArm4Layout = &Mul0MulOutputArm4Layout {
    _super: LAYOUT__190,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__192: &OpMULHULayout = &OpMULHULayout { _0: LAYOUT__180 };
pub const LAYOUT__191: &Mul0MulOutputArm5Layout = &Mul0MulOutputArm5Layout {
    _super: LAYOUT__192,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__193: &Mul0MulOutputArm6Layout = &Mul0MulOutputArm6Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
    _extra6: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
    _extra7: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
    _extra8: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
    _extra9: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
    _extra14: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
    _extra15: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
};
pub const LAYOUT__194: &Mul0MulOutputArm7Layout = &Mul0MulOutputArm7Layout {
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
    _extra6: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
    _extra7: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
    _extra8: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
    _extra9: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
    _extra14: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
    _extra15: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
};
pub const LAYOUT__152: &Mul0MulOutputLayout = &Mul0MulOutputLayout {
    arm0: LAYOUT__153,
    arm1: LAYOUT__177,
    arm2: LAYOUT__178,
    arm3: LAYOUT__187,
    arm4: LAYOUT__189,
    arm5: LAYOUT__191,
    arm6: LAYOUT__193,
    arm7: LAYOUT__194,
};
pub const LAYOUT__198: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 150 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 149 },
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
pub const LAYOUT__199: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 149 },
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
pub const LAYOUT__197: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__198,
    new_txn: LAYOUT__199,
};
pub const LAYOUT__201: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
};
pub const LAYOUT__200: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__201 };
pub const LAYOUT__196: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__197,
    _0: LAYOUT__200,
};
pub const LAYOUT__195: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 148 },
    },
    _0: LAYOUT__196,
};
pub const LAYOUT__203: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
};
pub const LAYOUT__204: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
};
pub const LAYOUT__202: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__203,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 162 },
    },
    high16: LAYOUT__204,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
};
pub const LAYOUT__120: &Mul0Layout = &Mul0Layout {
    _0: LAYOUT__121,
    input: LAYOUT__122,
    _arguments_mul0_mul_output: LAYOUT__149,
    mul_output: LAYOUT__152,
    _1: LAYOUT__195,
    pc_add: LAYOUT__202,
};
pub const LAYOUT__206: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__209: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
};
pub const LAYOUT__212: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__211: &U16RegLayout = &U16RegLayout { ret: LAYOUT__212 };
pub const LAYOUT__213: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
    },
};
pub const LAYOUT__210: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    upper_diff: LAYOUT__211,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
    med14: LAYOUT__213,
};
pub const LAYOUT__216: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 98 },
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
pub const LAYOUT__217: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 98 },
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
pub const LAYOUT__215: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__216,
    new_txn: LAYOUT__217,
};
pub const LAYOUT__219: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
};
pub const LAYOUT__218: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__219 };
pub const LAYOUT__214: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__215,
    _0: LAYOUT__218,
};
pub const LAYOUT__208: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__209,
    pc_addr: LAYOUT__210,
    load_inst: LAYOUT__214,
};
pub const LAYOUT__223: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 109 },
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
pub const LAYOUT__224: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 109 },
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
pub const LAYOUT__222: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__223,
    new_txn: LAYOUT__224,
};
pub const LAYOUT__226: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
};
pub const LAYOUT__225: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__226 };
pub const LAYOUT__221: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__222,
    _0: LAYOUT__225,
};
pub const LAYOUT__220: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__221,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
};
pub const LAYOUT__230: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 121 },
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
pub const LAYOUT__231: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 121 },
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
pub const LAYOUT__229: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__230,
    new_txn: LAYOUT__231,
};
pub const LAYOUT__233: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
};
pub const LAYOUT__232: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__233 };
pub const LAYOUT__228: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__229,
    _0: LAYOUT__232,
};
pub const LAYOUT__227: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__228,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
};
pub const LAYOUT__207: &DivInputLayout = &DivInputLayout {
    decoded: LAYOUT__208,
    rs1: LAYOUT__220,
    rs2: LAYOUT__227,
};
pub const LAYOUT__235: &ArgU16Layout9LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
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
];
pub const LAYOUT__236: &ArgU8Layout13LayoutArray = &[
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
];
pub const LAYOUT__234: &_Arguments_Div0MulOutputLayout = &_Arguments_Div0MulOutputLayout {
    arg_u16: LAYOUT__235,
    arg_u8: LAYOUT__236,
};
pub const LAYOUT__242: &NondetRegLayout5LayoutArray = &[
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
];
pub const LAYOUT__241: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__242,
};
pub const LAYOUT__240: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__241,
    check_u16: LAYOUT__77,
    b3: &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
    low: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
    high: &NondetRegLayout {
        _super: &Reg { offset: 140 },
    },
};
pub const LAYOUT__245: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__163,
    b1: LAYOUT__164,
    b2: LAYOUT__166,
    b3: LAYOUT__167,
    b3_top7times2: LAYOUT__168,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 143 },
    },
};
pub const LAYOUT__246: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__169,
    b1: LAYOUT__170,
    b2: LAYOUT__172,
    b3: LAYOUT__174,
    b3_top7times2: LAYOUT__176,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 144 },
    },
};
pub const LAYOUT__248: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__247: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__84,
    carry_byte: LAYOUT__248,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
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
pub const LAYOUT__249: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__10,
    carry_byte: LAYOUT__250,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
};
pub const LAYOUT__252: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__253: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__251: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__252,
    carry_byte: LAYOUT__253,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
};
pub const LAYOUT__254: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
};
pub const LAYOUT__244: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__245,
    bx: LAYOUT__246,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 145 },
    },
    c_rest_times2: LAYOUT__82,
    s0: LAYOUT__247,
    s1: LAYOUT__249,
    s2: LAYOUT__251,
    s3_out: LAYOUT__254,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
};
pub const LAYOUT__243: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 141 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
    rem_low: LAYOUT__78,
    rem_high: LAYOUT__80,
    mul: LAYOUT__244,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
};
pub const LAYOUT__239: &OpSRLLayout = &OpSRLLayout {
    shift_mul: LAYOUT__240,
    _0: LAYOUT__243,
};
pub const LAYOUT__238: &Div0MulOutputArm0Layout = &Div0MulOutputArm0Layout {
    _super: LAYOUT__239,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__256: &TopBitLayout = &TopBitLayout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 141 },
    },
    rest: LAYOUT__78,
};
pub const LAYOUT__259: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__163,
    b1: LAYOUT__164,
    b2: LAYOUT__166,
    b3: LAYOUT__167,
    b3_top7times2: LAYOUT__168,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 144 },
    },
};
pub const LAYOUT__260: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__169,
    b1: LAYOUT__170,
    b2: LAYOUT__172,
    b3: LAYOUT__174,
    b3_top7times2: LAYOUT__176,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 145 },
    },
};
pub const LAYOUT__261: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__10,
    carry_byte: LAYOUT__248,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
};
pub const LAYOUT__262: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__252,
    carry_byte: LAYOUT__250,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
};
pub const LAYOUT__263: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__254,
    carry_byte: LAYOUT__253,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
};
pub const LAYOUT__258: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__259,
    bx: LAYOUT__260,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 146 },
    },
    c_rest_times2: LAYOUT__84,
    s0: LAYOUT__261,
    s1: LAYOUT__262,
    s2: LAYOUT__263,
    s3_out: LAYOUT__13,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
};
pub const LAYOUT__257: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 143 },
    },
    rem_low: LAYOUT__80,
    rem_high: LAYOUT__82,
    mul: LAYOUT__258,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
};
pub const LAYOUT__255: &OpSRALayout = &OpSRALayout {
    shift_mul: LAYOUT__240,
    flip: LAYOUT__256,
    _0: LAYOUT__257,
};
pub const LAYOUT__265: &OpSRLILayout = &OpSRLILayout {
    shift_mul: LAYOUT__240,
    _0: LAYOUT__243,
};
pub const LAYOUT__264: &Div0MulOutputArm2Layout = &Div0MulOutputArm2Layout {
    _super: LAYOUT__265,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__266: &OpSRAILayout = &OpSRAILayout {
    shift_mul: LAYOUT__240,
    flip: LAYOUT__256,
    _0: LAYOUT__257,
};
pub const LAYOUT__271: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__163,
    b1: LAYOUT__164,
    b2: LAYOUT__166,
    b3: LAYOUT__167,
    b3_top7times2: LAYOUT__168,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
};
pub const LAYOUT__272: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__169,
    b1: LAYOUT__170,
    b2: LAYOUT__172,
    b3: LAYOUT__174,
    b3_top7times2: LAYOUT__176,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
};
pub const LAYOUT__273: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__82,
    carry_byte: LAYOUT__248,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__274: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__84,
    carry_byte: LAYOUT__250,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__275: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__10,
    carry_byte: LAYOUT__253,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__270: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__271,
    bx: LAYOUT__272,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    c_rest_times2: LAYOUT__80,
    s0: LAYOUT__273,
    s1: LAYOUT__274,
    s2: LAYOUT__275,
    s3_out: LAYOUT__252,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__269: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
    rem_low: LAYOUT__77,
    rem_high: LAYOUT__78,
    mul: LAYOUT__270,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 146 },
    },
};
pub const LAYOUT__268: &OpDIVLayout = &OpDIVLayout { _0: LAYOUT__269 };
pub const LAYOUT__267: &Div0MulOutputArm4Layout = &Div0MulOutputArm4Layout {
    _super: LAYOUT__268,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__277: &OpDIVULayout = &OpDIVULayout { _0: LAYOUT__269 };
pub const LAYOUT__276: &Div0MulOutputArm5Layout = &Div0MulOutputArm5Layout {
    _super: LAYOUT__277,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__279: &OpREMLayout = &OpREMLayout { _0: LAYOUT__269 };
pub const LAYOUT__278: &Div0MulOutputArm6Layout = &Div0MulOutputArm6Layout {
    _super: LAYOUT__279,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__281: &OpREMULayout = &OpREMULayout { _0: LAYOUT__269 };
pub const LAYOUT__280: &Div0MulOutputArm7Layout = &Div0MulOutputArm7Layout {
    _super: LAYOUT__281,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__237: &Div0MulOutputLayout = &Div0MulOutputLayout {
    arm0: LAYOUT__238,
    arm1: LAYOUT__255,
    arm2: LAYOUT__264,
    arm3: LAYOUT__266,
    arm4: LAYOUT__267,
    arm5: LAYOUT__276,
    arm6: LAYOUT__278,
    arm7: LAYOUT__280,
};
pub const LAYOUT__285: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 159 },
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
pub const LAYOUT__286: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 159 },
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
pub const LAYOUT__284: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__285,
    new_txn: LAYOUT__286,
};
pub const LAYOUT__288: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
};
pub const LAYOUT__287: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__288 };
pub const LAYOUT__283: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__284,
    _0: LAYOUT__287,
};
pub const LAYOUT__282: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
    _0: LAYOUT__283,
};
pub const LAYOUT__290: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
};
pub const LAYOUT__291: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
};
pub const LAYOUT__289: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__290,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 172 },
    },
    high16: LAYOUT__291,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 175 },
    },
};
pub const LAYOUT__205: &Div0Layout = &Div0Layout {
    _0: LAYOUT__206,
    input: LAYOUT__207,
    _arguments_div0_mul_output: LAYOUT__234,
    mul_output: LAYOUT__237,
    _1: LAYOUT__282,
    pc_add: LAYOUT__289,
};
pub const LAYOUT__293: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__296: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 51 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
};
pub const LAYOUT__299: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
    },
};
pub const LAYOUT__298: &U16RegLayout = &U16RegLayout { ret: LAYOUT__299 };
pub const LAYOUT__300: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
    },
};
pub const LAYOUT__297: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 55 },
    },
    upper_diff: LAYOUT__298,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
    },
    med14: LAYOUT__300,
};
pub const LAYOUT__303: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 63 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 62 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 65 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 66 },
    },
};
pub const LAYOUT__304: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 62 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
};
pub const LAYOUT__302: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__303,
    new_txn: LAYOUT__304,
};
pub const LAYOUT__306: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
};
pub const LAYOUT__305: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__306 };
pub const LAYOUT__301: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__302,
    _0: LAYOUT__305,
};
pub const LAYOUT__295: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__296,
    pc_addr: LAYOUT__297,
    load_inst: LAYOUT__301,
};
pub const LAYOUT__310: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 73 },
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
pub const LAYOUT__311: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 73 },
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
pub const LAYOUT__309: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__310,
    new_txn: LAYOUT__311,
};
pub const LAYOUT__313: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
};
pub const LAYOUT__312: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__313 };
pub const LAYOUT__308: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__309,
    _0: LAYOUT__312,
};
pub const LAYOUT__307: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__308,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
};
pub const LAYOUT__315: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
};
pub const LAYOUT__314: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__315,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    high16: LAYOUT__29,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
};
pub const LAYOUT__318: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
};
pub const LAYOUT__317: &U16RegLayout = &U16RegLayout { ret: LAYOUT__318 };
pub const LAYOUT__319: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
};
pub const LAYOUT__316: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    upper_diff: LAYOUT__317,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
    med14: LAYOUT__319,
};
pub const LAYOUT__322: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 99 },
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
pub const LAYOUT__323: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 99 },
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
pub const LAYOUT__321: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__322,
    new_txn: LAYOUT__323,
};
pub const LAYOUT__325: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
};
pub const LAYOUT__324: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__325 };
pub const LAYOUT__320: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__321,
    _0: LAYOUT__324,
};
pub const LAYOUT__294: &MemLoadInputLayout = &MemLoadInputLayout {
    decoded: LAYOUT__295,
    rs1: LAYOUT__307,
    addr_u32: LAYOUT__314,
    addr: LAYOUT__316,
    data_0: LAYOUT__320,
};
pub const LAYOUT__327: &ArgU8Layout3LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
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
];
pub const LAYOUT__326: &_Arguments_Mem0OutputLayout = &_Arguments_Mem0OutputLayout {
    arg_u8: LAYOUT__327,
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    }],
};
pub const LAYOUT__332: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
};
pub const LAYOUT__333: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
};
pub const LAYOUT__331: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__332,
    byte1: LAYOUT__333,
};
pub const LAYOUT__334: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__330: &OpLBLayout = &OpLBLayout {
    bytes: LAYOUT__331,
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    low7x2: LAYOUT__334,
};
pub const LAYOUT__329: &Mem0OutputArm0Layout = &Mem0OutputArm0Layout {
    _super: LAYOUT__330,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__336: &OpLHLayout = &OpLHLayout {
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    low15x2: LAYOUT__82,
};
pub const LAYOUT__335: &Mem0OutputArm1Layout = &Mem0OutputArm1Layout {
    _super: LAYOUT__336,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__337: &Mem0OutputArm2Layout = &Mem0OutputArm2Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__339: &OpLBULayout = &OpLBULayout { bytes: LAYOUT__331 };
pub const LAYOUT__338: &Mem0OutputArm3Layout = &Mem0OutputArm3Layout {
    _super: LAYOUT__339,
    _extra0: &ArgU8Layout {
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
};
pub const LAYOUT__340: &Mem0OutputArm4Layout = &Mem0OutputArm4Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__341: &Mem0OutputArm5Layout = &Mem0OutputArm5Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__342: &Mem0OutputArm6Layout = &Mem0OutputArm6Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__343: &Mem0OutputArm7Layout = &Mem0OutputArm7Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__328: &Mem0OutputLayout = &Mem0OutputLayout {
    arm0: LAYOUT__329,
    arm1: LAYOUT__335,
    arm2: LAYOUT__337,
    arm3: LAYOUT__338,
    arm4: LAYOUT__340,
    arm5: LAYOUT__341,
    arm6: LAYOUT__342,
    arm7: LAYOUT__343,
};
pub const LAYOUT__347: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__348: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__346: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__347,
    new_txn: LAYOUT__348,
};
pub const LAYOUT__350: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__349: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__350 };
pub const LAYOUT__345: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__346,
    _0: LAYOUT__349,
};
pub const LAYOUT__344: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    _0: LAYOUT__345,
};
pub const LAYOUT__352: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
};
pub const LAYOUT__353: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
};
pub const LAYOUT__351: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__352,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    high16: LAYOUT__353,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
};
pub const LAYOUT__292: &Mem0Layout = &Mem0Layout {
    _0: LAYOUT__293,
    input: LAYOUT__294,
    _arguments_mem0_output: LAYOUT__326,
    output: LAYOUT__328,
    _1: LAYOUT__344,
    pc_add: LAYOUT__351,
};
pub const LAYOUT__359: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 85 },
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
pub const LAYOUT__360: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 85 },
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
pub const LAYOUT__358: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__359,
    new_txn: LAYOUT__360,
};
pub const LAYOUT__362: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 95 },
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
        _super: &Reg { offset: 96 },
    },
};
pub const LAYOUT__364: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
};
pub const LAYOUT__363: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__319,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    high16: LAYOUT__364,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
};
pub const LAYOUT__367: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
};
pub const LAYOUT__366: &U16RegLayout = &U16RegLayout { ret: LAYOUT__367 };
pub const LAYOUT__368: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
};
pub const LAYOUT__365: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    upper_diff: LAYOUT__366,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    med14: LAYOUT__368,
};
pub const LAYOUT__371: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
};
pub const LAYOUT__372: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 111 },
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
pub const LAYOUT__370: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__371,
    new_txn: LAYOUT__372,
};
pub const LAYOUT__374: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
};
pub const LAYOUT__373: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__374 };
pub const LAYOUT__369: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__370,
    _0: LAYOUT__373,
};
pub const LAYOUT__355: &MemStoreInputLayout = &MemStoreInputLayout {
    decoded: LAYOUT__295,
    rs1: LAYOUT__307,
    rs2: LAYOUT__356,
    addr_u32: LAYOUT__363,
    addr: LAYOUT__365,
    data_0: LAYOUT__369,
};
pub const LAYOUT__376: &ArgU8Layout4LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
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
pub const LAYOUT__375: &_Arguments_Mem1OutputLayout = &_Arguments_Mem1OutputLayout {
    arg_u8: LAYOUT__376,
};
pub const LAYOUT__380: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__379: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__334,
    byte1: LAYOUT__380,
};
pub const LAYOUT__378: &OpSBLayout = &OpSBLayout {
    orig_bytes: LAYOUT__331,
    new_bytes: LAYOUT__379,
};
pub const LAYOUT__381: &Mem1OutputArm1Layout = &Mem1OutputArm1Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__382: &Mem1OutputArm2Layout = &Mem1OutputArm2Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__383: &Mem1OutputArm3Layout = &Mem1OutputArm3Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__384: &Mem1OutputArm4Layout = &Mem1OutputArm4Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__385: &Mem1OutputArm5Layout = &Mem1OutputArm5Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__386: &Mem1OutputArm6Layout = &Mem1OutputArm6Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__387: &Mem1OutputArm7Layout = &Mem1OutputArm7Layout {
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__377: &Mem1OutputLayout = &Mem1OutputLayout {
    arm0: LAYOUT__378,
    arm1: LAYOUT__381,
    arm2: LAYOUT__382,
    arm3: LAYOUT__383,
    arm4: LAYOUT__384,
    arm5: LAYOUT__385,
    arm6: LAYOUT__386,
    arm7: LAYOUT__387,
};
pub const LAYOUT__391: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 122 },
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
pub const LAYOUT__392: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 122 },
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
pub const LAYOUT__390: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__391,
    new_txn: LAYOUT__392,
};
pub const LAYOUT__394: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
};
pub const LAYOUT__393: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__394 };
pub const LAYOUT__389: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__390,
    _0: LAYOUT__393,
};
pub const LAYOUT__388: &MemStoreFinalizeLayout = &MemStoreFinalizeLayout { _0: LAYOUT__389 };
pub const LAYOUT__396: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
};
pub const LAYOUT__397: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
};
pub const LAYOUT__395: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__396,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    high16: LAYOUT__397,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
};
pub const LAYOUT__354: &Mem1Layout = &Mem1Layout {
    _0: LAYOUT__293,
    input: LAYOUT__355,
    _arguments_mem1_output: LAYOUT__375,
    output: LAYOUT__377,
    _1: LAYOUT__388,
    pc_add: LAYOUT__395,
};
pub const LAYOUT__406: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 27 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 28 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 29 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 30 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 31 },
    },
};
pub const LAYOUT__407: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 32 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 28 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 33 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 34 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 35 },
    },
};
pub const LAYOUT__405: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__406,
    new_txn: LAYOUT__407,
};
pub const LAYOUT__404: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__405 };
pub const LAYOUT__403: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__404 };
pub const LAYOUT__411: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 38 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
};
pub const LAYOUT__412: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
};
pub const LAYOUT__410: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__411,
    new_txn: LAYOUT__412,
};
pub const LAYOUT__409: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__410 };
pub const LAYOUT__408: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__409 };
pub const LAYOUT__416: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
};
pub const LAYOUT__417: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 51 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 53 },
    },
};
pub const LAYOUT__415: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__416,
    new_txn: LAYOUT__417,
};
pub const LAYOUT__414: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__415 };
pub const LAYOUT__413: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__414 };
pub const LAYOUT__421: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 54 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 55 },
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
pub const LAYOUT__422: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 59 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 55 },
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
pub const LAYOUT__420: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__421,
    new_txn: LAYOUT__422,
};
pub const LAYOUT__419: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__420 };
pub const LAYOUT__418: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__419 };
pub const LAYOUT__426: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 63 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 64 },
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
pub const LAYOUT__427: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 64 },
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
pub const LAYOUT__425: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__426,
    new_txn: LAYOUT__427,
};
pub const LAYOUT__424: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__425 };
pub const LAYOUT__423: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__424 };
pub const LAYOUT__431: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 73 },
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
pub const LAYOUT__432: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 73 },
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
pub const LAYOUT__430: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__431,
    new_txn: LAYOUT__432,
};
pub const LAYOUT__429: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__430 };
pub const LAYOUT__428: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__429 };
pub const LAYOUT__436: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 82 },
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
pub const LAYOUT__437: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 82 },
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
pub const LAYOUT__435: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__436,
    new_txn: LAYOUT__437,
};
pub const LAYOUT__434: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__435 };
pub const LAYOUT__433: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__434 };
pub const LAYOUT__441: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 91 },
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
pub const LAYOUT__442: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 91 },
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
pub const LAYOUT__440: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__441,
    new_txn: LAYOUT__442,
};
pub const LAYOUT__439: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__440 };
pub const LAYOUT__438: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__439 };
pub const LAYOUT__402: &ControlLoadRoot__0_SuperLayout8LayoutArray = &[
    LAYOUT__403,
    LAYOUT__408,
    LAYOUT__413,
    LAYOUT__418,
    LAYOUT__423,
    LAYOUT__428,
    LAYOUT__433,
    LAYOUT__438,
];
pub const LAYOUT__401: &ControlLoadRootLayout = &ControlLoadRootLayout { _1: LAYOUT__402 };
pub const LAYOUT__400: &Control0_SuperArm0Layout = &Control0_SuperArm0Layout {
    _super: LAYOUT__401,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
    _extra1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra3: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra6: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra7: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra38: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__448: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__405,
    _0: LAYOUT__34,
};
pub const LAYOUT__449: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__410,
    _0: LAYOUT__133,
};
pub const LAYOUT__447: &ControlResume_SuperArm0_SuperLayout =
    &ControlResume_SuperArm0_SuperLayout {
        pc: LAYOUT__448,
        mode: LAYOUT__449,
    };
pub const LAYOUT__446: &ControlResume_SuperArm0Layout = &ControlResume_SuperArm0Layout {
    _super: LAYOUT__447,
    _extra0: LAYOUT__416,
    _extra1: LAYOUT__417,
    _extra2: LAYOUT__421,
    _extra3: LAYOUT__422,
    _extra4: LAYOUT__426,
    _extra5: LAYOUT__427,
    _extra6: LAYOUT__431,
    _extra7: LAYOUT__432,
    _extra8: LAYOUT__436,
    _extra9: LAYOUT__437,
    _extra10: LAYOUT__441,
    _extra11: LAYOUT__442,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
};
pub const LAYOUT__453: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__405,
    _0: LAYOUT__34,
};
pub const LAYOUT__452: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__453 };
pub const LAYOUT__455: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__410,
    _0: LAYOUT__133,
};
pub const LAYOUT__454: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__455 };
pub const LAYOUT__459: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
};
pub const LAYOUT__458: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__459 };
pub const LAYOUT__457: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__415,
    _0: LAYOUT__458,
};
pub const LAYOUT__456: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__457 };
pub const LAYOUT__463: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
};
pub const LAYOUT__462: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__463 };
pub const LAYOUT__461: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__420,
    _0: LAYOUT__462,
};
pub const LAYOUT__460: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__461 };
pub const LAYOUT__465: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__425,
    _0: LAYOUT__218,
};
pub const LAYOUT__464: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__465 };
pub const LAYOUT__469: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
};
pub const LAYOUT__468: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__469 };
pub const LAYOUT__467: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__430,
    _0: LAYOUT__468,
};
pub const LAYOUT__466: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__467 };
pub const LAYOUT__473: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__472: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__473 };
pub const LAYOUT__471: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__435,
    _0: LAYOUT__472,
};
pub const LAYOUT__470: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__471 };
pub const LAYOUT__477: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
};
pub const LAYOUT__476: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__477 };
pub const LAYOUT__475: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__440,
    _0: LAYOUT__476,
};
pub const LAYOUT__474: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__475 };
pub const LAYOUT__451: &ControlResume_SuperArm1_Super__0_SuperLayout8LayoutArray = &[
    LAYOUT__452,
    LAYOUT__454,
    LAYOUT__456,
    LAYOUT__460,
    LAYOUT__464,
    LAYOUT__466,
    LAYOUT__470,
    LAYOUT__474,
];
pub const LAYOUT__450: &ControlResume_SuperArm1_SuperLayout =
    &ControlResume_SuperArm1_SuperLayout { _1: LAYOUT__451 };
pub const LAYOUT__445: &ControlResume_SuperLayout = &ControlResume_SuperLayout {
    arm0: LAYOUT__446,
    arm1: LAYOUT__450,
};
pub const LAYOUT__479: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__406,
    LAYOUT__407,
    LAYOUT__411,
    LAYOUT__412,
    LAYOUT__416,
    LAYOUT__417,
    LAYOUT__421,
    LAYOUT__422,
    LAYOUT__426,
    LAYOUT__427,
    LAYOUT__431,
    LAYOUT__432,
    LAYOUT__436,
    LAYOUT__437,
    LAYOUT__441,
    LAYOUT__442,
];
pub const LAYOUT__480: &CycleArgLayout8LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
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
];
pub const LAYOUT__478: &_Arguments_ControlResume_SuperLayout =
    &_Arguments_ControlResume_SuperLayout {
        memory_arg: LAYOUT__479,
        cycle_arg: LAYOUT__480,
    };
pub const LAYOUT__444: &ControlResumeLayout = &ControlResumeLayout {
    _super: LAYOUT__445,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
    _arguments_control_resume__super: LAYOUT__478,
};
pub const LAYOUT__443: &Control0_SuperArm1Layout = &Control0_SuperArm1Layout {
    _super: LAYOUT__444,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__485: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
};
pub const LAYOUT__484: &U16RegLayout = &U16RegLayout { ret: LAYOUT__485 };
pub const LAYOUT__486: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
};
pub const LAYOUT__483: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    upper_diff: LAYOUT__484,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    med14: LAYOUT__486,
};
pub const LAYOUT__488: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__487: &U16RegLayout = &U16RegLayout { ret: LAYOUT__488 };
pub const LAYOUT__489: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__415,
    _0: LAYOUT__458,
};
pub const LAYOUT__482: &ControlUserECALLLayout = &ControlUserECALLLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 179 },
    },
    pc_addr: LAYOUT__483,
    load_inst: LAYOUT__448,
    dispatch_idx: LAYOUT__449,
    _0: LAYOUT__487,
    new_pc_addr: LAYOUT__489,
    _1: LAYOUT__461,
};
pub const LAYOUT__481: &Control0_SuperArm2Layout = &Control0_SuperArm2Layout {
    _super: LAYOUT__482,
    _extra0: LAYOUT__426,
    _extra1: LAYOUT__427,
    _extra2: LAYOUT__431,
    _extra3: LAYOUT__432,
    _extra4: LAYOUT__436,
    _extra5: LAYOUT__437,
    _extra6: LAYOUT__441,
    _extra7: LAYOUT__442,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra38: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__493: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
};
pub const LAYOUT__492: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__488,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    high16: LAYOUT__493,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 185 },
    },
};
pub const LAYOUT__491: &ControlMRETLayout = &ControlMRETLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 179 },
    },
    pc_addr: LAYOUT__483,
    load_inst: LAYOUT__448,
    pc: LAYOUT__449,
    pc_add: LAYOUT__492,
};
pub const LAYOUT__490: &Control0_SuperArm3Layout = &Control0_SuperArm3Layout {
    _super: LAYOUT__491,
    _extra0: LAYOUT__416,
    _extra1: LAYOUT__417,
    _extra2: LAYOUT__421,
    _extra3: LAYOUT__422,
    _extra4: LAYOUT__426,
    _extra5: LAYOUT__427,
    _extra6: LAYOUT__431,
    _extra7: LAYOUT__432,
    _extra8: LAYOUT__436,
    _extra9: LAYOUT__437,
    _extra10: LAYOUT__441,
    _extra11: LAYOUT__442,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra38: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra42: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra43: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra44: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra45: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__499: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__420,
    _0: LAYOUT__462,
};
pub const LAYOUT__500: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__425,
    _0: LAYOUT__218,
};
pub const LAYOUT__501: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__430,
    _0: LAYOUT__468,
};
pub const LAYOUT__502: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__435,
    _0: LAYOUT__472,
};
pub const LAYOUT__503: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__440,
    _0: LAYOUT__476,
};
pub const LAYOUT__498: &MemoryReadLayout8LayoutArray = &[
    LAYOUT__448,
    LAYOUT__449,
    LAYOUT__489,
    LAYOUT__499,
    LAYOUT__500,
    LAYOUT__501,
    LAYOUT__502,
    LAYOUT__503,
];
pub const LAYOUT__497: &ControlSuspend_SuperArm0_SuperLayout =
    &ControlSuspend_SuperArm0_SuperLayout { _1: LAYOUT__498 };
pub const LAYOUT__505: &ControlSuspend_SuperArm1_SuperLayout =
    &ControlSuspend_SuperArm1_SuperLayout {
        state: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        _0: LAYOUT__453,
        _1: LAYOUT__455,
    };
pub const LAYOUT__504: &ControlSuspend_SuperArm1Layout = &ControlSuspend_SuperArm1Layout {
    _super: LAYOUT__505,
    _extra0: LAYOUT__416,
    _extra1: LAYOUT__417,
    _extra2: LAYOUT__421,
    _extra3: LAYOUT__422,
    _extra4: LAYOUT__426,
    _extra5: LAYOUT__427,
    _extra6: LAYOUT__431,
    _extra7: LAYOUT__432,
    _extra8: LAYOUT__436,
    _extra9: LAYOUT__437,
    _extra10: LAYOUT__441,
    _extra11: LAYOUT__442,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
};
pub const LAYOUT__496: &ControlSuspend_SuperLayout = &ControlSuspend_SuperLayout {
    arm0: LAYOUT__497,
    arm1: LAYOUT__504,
};
pub const LAYOUT__506: &_Arguments_ControlSuspend_SuperLayout =
    &_Arguments_ControlSuspend_SuperLayout {
        memory_arg: LAYOUT__479,
        cycle_arg: LAYOUT__480,
    };
pub const LAYOUT__495: &ControlSuspendLayout = &ControlSuspendLayout {
    _super: LAYOUT__496,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _arguments_control_suspend__super: LAYOUT__506,
};
pub const LAYOUT__494: &Control0_SuperArm4Layout = &Control0_SuperArm4Layout {
    _super: LAYOUT__495,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__510: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__405,
    _0: LAYOUT__34,
};
pub const LAYOUT__511: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__410,
    _0: LAYOUT__133,
};
pub const LAYOUT__512: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__415,
    _0: LAYOUT__458,
};
pub const LAYOUT__513: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__420,
    _0: LAYOUT__462,
};
pub const LAYOUT__514: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__425,
    _0: LAYOUT__218,
};
pub const LAYOUT__515: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__430,
    _0: LAYOUT__468,
};
pub const LAYOUT__516: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__435,
    _0: LAYOUT__472,
};
pub const LAYOUT__517: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__440,
    _0: LAYOUT__476,
};
pub const LAYOUT__509: &MemoryPageOutLayout8LayoutArray = &[
    LAYOUT__510,
    LAYOUT__511,
    LAYOUT__512,
    LAYOUT__513,
    LAYOUT__514,
    LAYOUT__515,
    LAYOUT__516,
    LAYOUT__517,
];
pub const LAYOUT__508: &ControlStoreRootLayout = &ControlStoreRootLayout { _1: LAYOUT__509 };
pub const LAYOUT__507: &Control0_SuperArm5Layout = &Control0_SuperArm5Layout {
    _super: LAYOUT__508,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__524: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 115 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 116 },
            },
        },
    };
pub const LAYOUT__525: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__526: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__527: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__528: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__529: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__530: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__531: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__532: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__533: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__534: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__535: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__536: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__537: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__538: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__539: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__523: &ControlTable_SuperArm0_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__524,
    LAYOUT__525,
    LAYOUT__526,
    LAYOUT__527,
    LAYOUT__528,
    LAYOUT__529,
    LAYOUT__530,
    LAYOUT__531,
    LAYOUT__532,
    LAYOUT__533,
    LAYOUT__534,
    LAYOUT__535,
    LAYOUT__536,
    LAYOUT__537,
    LAYOUT__538,
    LAYOUT__539,
];
pub const LAYOUT__522: &ControlTable_SuperArm0_SuperLayout = &ControlTable_SuperArm0_SuperLayout {
    _1: LAYOUT__523,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__521: &ControlTable_SuperArm0Layout = &ControlTable_SuperArm0Layout {
    _super: LAYOUT__522,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra4: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra5: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra6: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra7: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra8: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra9: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra14: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra15: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__543: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 147 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 148 },
            },
        },
    };
pub const LAYOUT__544: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__545: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__546: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__547: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__548: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__549: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__550: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__551: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__552: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__553: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__554: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__555: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__556: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__557: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__558: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__542: &ControlTable_SuperArm1_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__543,
    LAYOUT__544,
    LAYOUT__545,
    LAYOUT__546,
    LAYOUT__547,
    LAYOUT__548,
    LAYOUT__549,
    LAYOUT__550,
    LAYOUT__551,
    LAYOUT__552,
    LAYOUT__553,
    LAYOUT__554,
    LAYOUT__555,
    LAYOUT__556,
    LAYOUT__557,
    LAYOUT__558,
];
pub const LAYOUT__541: &ControlTable_SuperArm1_SuperLayout = &ControlTable_SuperArm1_SuperLayout {
    _1: LAYOUT__542,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
    },
};
pub const LAYOUT__540: &ControlTable_SuperArm1Layout = &ControlTable_SuperArm1Layout {
    _super: LAYOUT__541,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__520: &ControlTable_SuperLayout = &ControlTable_SuperLayout {
    arm0: LAYOUT__521,
    arm1: LAYOUT__540,
};
pub const LAYOUT__560: &ArgU16Layout16LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
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
];
pub const LAYOUT__561: &ArgU8Layout16LayoutArray = &[
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
];
pub const LAYOUT__559: &_Arguments_ControlTable_SuperLayout =
    &_Arguments_ControlTable_SuperLayout {
        arg_u16: LAYOUT__560,
        arg_u8: LAYOUT__561,
    };
pub const LAYOUT__519: &ControlTableLayout = &ControlTableLayout {
    _super: LAYOUT__520,
    entry: &NondetRegLayout {
        _super: &Reg { offset: 181 },
    },
    mode: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    _arguments_control_table__super: LAYOUT__559,
};
pub const LAYOUT__518: &Control0_SuperArm6Layout = &Control0_SuperArm6Layout {
    _super: LAYOUT__519,
    _extra0: LAYOUT__406,
    _extra1: LAYOUT__407,
    _extra2: LAYOUT__411,
    _extra3: LAYOUT__412,
    _extra4: LAYOUT__416,
    _extra5: LAYOUT__417,
    _extra6: LAYOUT__421,
    _extra7: LAYOUT__422,
    _extra8: LAYOUT__426,
    _extra9: LAYOUT__427,
    _extra10: LAYOUT__431,
    _extra11: LAYOUT__432,
    _extra12: LAYOUT__436,
    _extra13: LAYOUT__437,
    _extra14: LAYOUT__441,
    _extra15: LAYOUT__442,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
};
pub const LAYOUT__564: &_Arguments_ControlDone__0Layout = &_Arguments_ControlDone__0Layout {
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    }],
};
pub const LAYOUT__566: &ControlDone__0Arm0_SuperLayout =
    &ControlDone__0Arm0_SuperLayout { _0: LAYOUT__35 };
pub const LAYOUT__567: &ControlDone__0Arm1Layout = &ControlDone__0Arm1Layout {
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
};
pub const LAYOUT__565: &ControlDone__0Layout = &ControlDone__0Layout {
    arm0: LAYOUT__566,
    arm1: LAYOUT__567,
};
pub const LAYOUT__563: &ControlDoneLayout = &ControlDoneLayout {
    _arguments_control_done__0: LAYOUT__564,
    _2: LAYOUT__565,
};
pub const LAYOUT__562: &Control0_SuperArm7Layout = &Control0_SuperArm7Layout {
    _super: LAYOUT__563,
    _extra0: LAYOUT__406,
    _extra1: LAYOUT__407,
    _extra2: LAYOUT__411,
    _extra3: LAYOUT__412,
    _extra4: LAYOUT__416,
    _extra5: LAYOUT__417,
    _extra6: LAYOUT__421,
    _extra7: LAYOUT__422,
    _extra8: LAYOUT__426,
    _extra9: LAYOUT__427,
    _extra10: LAYOUT__431,
    _extra11: LAYOUT__432,
    _extra12: LAYOUT__436,
    _extra13: LAYOUT__437,
    _extra14: LAYOUT__441,
    _extra15: LAYOUT__442,
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
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra42: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra43: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra44: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra45: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra46: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra47: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra48: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra49: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra50: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
    _extra51: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _extra52: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
    },
    _extra53: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
    },
    _extra54: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
    },
};
pub const LAYOUT__399: &Control0_SuperLayout = &Control0_SuperLayout {
    arm0: LAYOUT__400,
    arm1: LAYOUT__443,
    arm2: LAYOUT__481,
    arm3: LAYOUT__490,
    arm4: LAYOUT__494,
    arm5: LAYOUT__507,
    arm6: LAYOUT__518,
    arm7: LAYOUT__562,
};
pub const LAYOUT__568: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__569: &_Arguments_Control0_SuperLayout = &_Arguments_Control0_SuperLayout {
    memory_arg: LAYOUT__479,
    cycle_arg: LAYOUT__480,
    arg_u16: LAYOUT__560,
    arg_u8: LAYOUT__561,
};
pub const LAYOUT__398: &Control0Layout = &Control0Layout {
    _super: LAYOUT__399,
    _0: LAYOUT__568,
    _arguments_control0__super: LAYOUT__569,
};
pub const LAYOUT__571: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
};
pub const LAYOUT__572: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    upper_diff: LAYOUT__27,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
    med14: LAYOUT__29,
};
pub const LAYOUT__574: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__406,
    LAYOUT__407,
    LAYOUT__411,
    LAYOUT__412,
    LAYOUT__416,
    LAYOUT__417,
    LAYOUT__421,
    LAYOUT__422,
];
pub const LAYOUT__575: &CycleArgLayout4LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
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
];
pub const LAYOUT__576: &ArgU16Layout2LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
];
pub const LAYOUT__573: &_Arguments_ECall0OutputLayout = &_Arguments_ECall0OutputLayout {
    memory_arg: LAYOUT__574,
    cycle_arg: LAYOUT__575,
    arg_u16: LAYOUT__576,
};
pub const LAYOUT__582: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
};
pub const LAYOUT__581: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__582 };
pub const LAYOUT__580: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__405,
    _0: LAYOUT__581,
};
pub const LAYOUT__585: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__584: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__585 };
pub const LAYOUT__583: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__410,
    _0: LAYOUT__584,
};
pub const LAYOUT__587: &NondetRegLayout4LayoutArray = &[
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
];
pub const LAYOUT__586: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__587,
};
pub const LAYOUT__579: &MachineECallLayout = &MachineECallLayout {
    load_inst: LAYOUT__580,
    dispatch_idx: LAYOUT__583,
    dispatch: LAYOUT__586,
};
pub const LAYOUT__578: &ECall0OutputArm0Layout = &ECall0OutputArm0Layout {
    _super: LAYOUT__579,
    _extra0: LAYOUT__416,
    _extra1: LAYOUT__417,
    _extra2: LAYOUT__421,
    _extra3: LAYOUT__422,
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__589: &ECallTerminateLayout = &ECallTerminateLayout {
    a0: LAYOUT__580,
    a1: LAYOUT__583,
};
pub const LAYOUT__588: &ECall0OutputArm1Layout = &ECall0OutputArm1Layout {
    _super: LAYOUT__589,
    _extra0: LAYOUT__416,
    _extra1: LAYOUT__417,
    _extra2: LAYOUT__421,
    _extra3: LAYOUT__422,
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__593: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__592: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__593 };
pub const LAYOUT__591: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__415,
    _0: LAYOUT__592,
};
pub const LAYOUT__594: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
};
pub const LAYOUT__596: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__595: &U16RegLayout = &U16RegLayout { ret: LAYOUT__596 };
pub const LAYOUT__599: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__598: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__599 };
pub const LAYOUT__597: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__420,
    _0: LAYOUT__598,
};
pub const LAYOUT__602: &NondetRegLayout4LayoutArray = &[
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
];
pub const LAYOUT__601: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__602,
};
pub const LAYOUT__600: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    low2: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    low2_hot: LAYOUT__601,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
};
pub const LAYOUT__605: &NondetRegLayout4LayoutArray = &[
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
];
pub const LAYOUT__604: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__605,
};
pub const LAYOUT__603: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    low2: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    low2_hot: LAYOUT__604,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
};
pub const LAYOUT__590: &ECallHostReadSetupLayout = &ECallHostReadSetupLayout {
    fd: LAYOUT__580,
    ptr: LAYOUT__583,
    len: LAYOUT__591,
    new_len: LAYOUT__594,
    diff: LAYOUT__595,
    _0: LAYOUT__597,
    ptr_decomp: LAYOUT__600,
    len_decomp: LAYOUT__603,
    len123: &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
    uneven: &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
};
pub const LAYOUT__606: &ECallHostWriteLayout = &ECallHostWriteLayout {
    fd: LAYOUT__580,
    ptr: LAYOUT__583,
    len: LAYOUT__591,
    new_len: LAYOUT__594,
    diff: LAYOUT__595,
    _0: LAYOUT__597,
};
pub const LAYOUT__607: &ECall0OutputArm4Layout = &ECall0OutputArm4Layout {
    _extra0: LAYOUT__406,
    _extra1: LAYOUT__407,
    _extra2: LAYOUT__411,
    _extra3: LAYOUT__412,
    _extra4: LAYOUT__416,
    _extra5: LAYOUT__417,
    _extra6: LAYOUT__421,
    _extra7: LAYOUT__422,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__612: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__405,
    _0: LAYOUT__581,
};
pub const LAYOUT__611: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
    _0: LAYOUT__612,
};
pub const LAYOUT__614: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__410,
    _0: LAYOUT__584,
};
pub const LAYOUT__613: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
    _0: LAYOUT__614,
};
pub const LAYOUT__616: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__415,
    _0: LAYOUT__592,
};
pub const LAYOUT__615: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    _0: LAYOUT__616,
};
pub const LAYOUT__618: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__420,
    _0: LAYOUT__598,
};
pub const LAYOUT__617: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    _0: LAYOUT__618,
};
pub const LAYOUT__610: &ECallHostReadWords__0_SuperLayout4LayoutArray =
    &[LAYOUT__611, LAYOUT__613, LAYOUT__615, LAYOUT__617];
pub const LAYOUT__609: &ECallHostReadWordsLayout = &ECallHostReadWordsLayout {
    len_decomp: LAYOUT__600,
    words_decomp: LAYOUT__603,
    _1: LAYOUT__610,
    len_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
    },
};
pub const LAYOUT__608: &ECall0OutputArm5Layout = &ECall0OutputArm5Layout {
    _super: LAYOUT__609,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__619: &ECall0OutputArm6Layout = &ECall0OutputArm6Layout {
    _extra0: LAYOUT__406,
    _extra1: LAYOUT__407,
    _extra2: LAYOUT__411,
    _extra3: LAYOUT__412,
    _extra4: LAYOUT__416,
    _extra5: LAYOUT__417,
    _extra6: LAYOUT__421,
    _extra7: LAYOUT__422,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__620: &ECall0OutputArm7Layout = &ECall0OutputArm7Layout {
    _extra0: LAYOUT__406,
    _extra1: LAYOUT__407,
    _extra2: LAYOUT__411,
    _extra3: LAYOUT__412,
    _extra4: LAYOUT__416,
    _extra5: LAYOUT__417,
    _extra6: LAYOUT__421,
    _extra7: LAYOUT__422,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
    },
};
pub const LAYOUT__577: &ECall0OutputLayout = &ECall0OutputLayout {
    arm0: LAYOUT__578,
    arm1: LAYOUT__588,
    arm2: LAYOUT__590,
    arm3: LAYOUT__606,
    arm4: LAYOUT__607,
    arm5: LAYOUT__608,
    arm6: LAYOUT__619,
    arm7: LAYOUT__620,
};
pub const LAYOUT__622: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
};
pub const LAYOUT__621: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__622,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    high16: LAYOUT__493,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
};
pub const LAYOUT__570: &ECall0Layout = &ECall0Layout {
    s0: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    s1: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    s2: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    _0: LAYOUT__571,
    pc_addr: LAYOUT__572,
    _arguments_e_call0_output: LAYOUT__573,
    output: LAYOUT__577,
    is_decode: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
    is_p2_entry: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
    add_pc: LAYOUT__621,
};
pub const LAYOUT__624: &DoCycleTableLayout = &DoCycleTableLayout {
    arg1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 190 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
    },
    arg2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 192 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 193 },
        },
    },
};
pub const LAYOUT__626: &NondetRegLayout24LayoutArray = &[
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
];
pub const LAYOUT__625: &PoseidonStateLayout = &PoseidonStateLayout {
    has_state: &NondetRegLayout {
        _super: &Reg { offset: 27 },
    },
    state_addr: &NondetRegLayout {
        _super: &Reg { offset: 28 },
    },
    buf_out_addr: &NondetRegLayout {
        _super: &Reg { offset: 29 },
    },
    is_elem: &NondetRegLayout {
        _super: &Reg { offset: 30 },
    },
    check_out: &NondetRegLayout {
        _super: &Reg { offset: 31 },
    },
    load_tx_type: &NondetRegLayout {
        _super: &Reg { offset: 32 },
    },
    next_state: &NondetRegLayout {
        _super: &Reg { offset: 33 },
    },
    sub_state: &NondetRegLayout {
        _super: &Reg { offset: 34 },
    },
    buf_in_addr: &NondetRegLayout {
        _super: &Reg { offset: 35 },
    },
    count: &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
    mode: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    inner: LAYOUT__626,
    zcheck: &NondetExtRegLayout {
        _super: &Reg { offset: 62 },
    },
};
pub const LAYOUT__629: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 66 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
};
pub const LAYOUT__630: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
};
pub const LAYOUT__631: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__632: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__633: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__634: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__635: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 94 },
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
pub const LAYOUT__636: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 94 },
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
pub const LAYOUT__637: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 103 },
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
pub const LAYOUT__638: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 103 },
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
pub const LAYOUT__639: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
};
pub const LAYOUT__640: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 112 },
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
pub const LAYOUT__641: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 121 },
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
pub const LAYOUT__642: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 125 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 121 },
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
pub const LAYOUT__643: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 130 },
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
pub const LAYOUT__644: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 134 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 130 },
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
pub const LAYOUT__628: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__629,
    LAYOUT__630,
    LAYOUT__631,
    LAYOUT__632,
    LAYOUT__633,
    LAYOUT__634,
    LAYOUT__635,
    LAYOUT__636,
    LAYOUT__637,
    LAYOUT__638,
    LAYOUT__639,
    LAYOUT__640,
    LAYOUT__641,
    LAYOUT__642,
    LAYOUT__643,
    LAYOUT__644,
];
pub const LAYOUT__645: &CycleArgLayout8LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
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
];
pub const LAYOUT__646: &ArgU16Layout16LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
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
            _super: &Reg { offset: 161 },
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
            _super: &Reg { offset: 165 },
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
            _super: &Reg { offset: 169 },
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
            _super: &Reg { offset: 173 },
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
            _super: &Reg { offset: 177 },
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
            _super: &Reg { offset: 181 },
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
            _super: &Reg { offset: 185 },
        },
    },
];
pub const LAYOUT__647: &ArgU8Layout2LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
];
pub const LAYOUT__627: &_Arguments_Poseidon0StateLayout = &_Arguments_Poseidon0StateLayout {
    memory_arg: LAYOUT__628,
    cycle_arg: LAYOUT__645,
    arg_u16: LAYOUT__646,
    arg_u8: LAYOUT__647,
};
pub const LAYOUT__652: &PoseidonEntry_SuperArm0Layout = &PoseidonEntry_SuperArm0Layout {
    _super: LAYOUT__625,
    _extra0: LAYOUT__629,
    _extra1: LAYOUT__630,
    _extra2: LAYOUT__631,
    _extra3: LAYOUT__632,
    _extra4: LAYOUT__633,
    _extra5: LAYOUT__634,
    _extra6: LAYOUT__635,
    _extra7: LAYOUT__636,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__656: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__629,
    new_txn: LAYOUT__630,
};
pub const LAYOUT__658: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__657: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__658 };
pub const LAYOUT__655: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__656,
    _0: LAYOUT__657,
};
pub const LAYOUT__654: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__655,
};
pub const LAYOUT__661: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__631,
    new_txn: LAYOUT__632,
};
pub const LAYOUT__663: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__662: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__663 };
pub const LAYOUT__660: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__661,
    _0: LAYOUT__662,
};
pub const LAYOUT__659: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__660,
};
pub const LAYOUT__666: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__633,
    new_txn: LAYOUT__634,
};
pub const LAYOUT__668: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__667: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__668 };
pub const LAYOUT__665: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__666,
    _0: LAYOUT__667,
};
pub const LAYOUT__664: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__665,
};
pub const LAYOUT__670: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__635,
    new_txn: LAYOUT__636,
};
pub const LAYOUT__672: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__671: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__672 };
pub const LAYOUT__669: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__670,
    _0: LAYOUT__671,
};
pub const LAYOUT__653: &PoseidonEcallLayout = &PoseidonEcallLayout {
    _super: LAYOUT__625,
    state_addr: LAYOUT__654,
    buf_in_addr: LAYOUT__659,
    buf_out_addr: LAYOUT__664,
    bits_and_count: LAYOUT__669,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 194 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 195 },
        },
    },
    is_elem: &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
    check_out: &NondetRegLayout {
        _super: &Reg { offset: 197 },
    },
    count_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 198 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 199 },
        },
    },
};
pub const LAYOUT__651: &PoseidonEntry_SuperLayout = &PoseidonEntry_SuperLayout {
    _super: LAYOUT__625,
    arm0: LAYOUT__652,
    arm1: LAYOUT__653,
};
pub const LAYOUT__674: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__629,
    LAYOUT__630,
    LAYOUT__631,
    LAYOUT__632,
    LAYOUT__633,
    LAYOUT__634,
    LAYOUT__635,
    LAYOUT__636,
];
pub const LAYOUT__675: &CycleArgLayout4LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
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
];
pub const LAYOUT__673: &_Arguments_PoseidonEntry_SuperLayout =
    &_Arguments_PoseidonEntry_SuperLayout {
        memory_arg: LAYOUT__674,
        cycle_arg: LAYOUT__675,
    };
pub const LAYOUT__650: &PoseidonEntryLayout = &PoseidonEntryLayout {
    _super: LAYOUT__651,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 200 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 201 },
        },
    },
    _arguments_poseidon_entry__super: LAYOUT__673,
};
pub const LAYOUT__649: &Poseidon0StateArm0Layout = &Poseidon0StateArm0Layout {
    _super: LAYOUT__650,
    _extra0: LAYOUT__637,
    _extra1: LAYOUT__638,
    _extra2: LAYOUT__639,
    _extra3: LAYOUT__640,
    _extra4: LAYOUT__641,
    _extra5: LAYOUT__642,
    _extra6: LAYOUT__643,
    _extra7: LAYOUT__644,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
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
            _super: &Reg { offset: 161 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__679: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__655,
};
pub const LAYOUT__680: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__660,
};
pub const LAYOUT__681: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__665,
};
pub const LAYOUT__682: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__669,
};
pub const LAYOUT__685: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__637,
    new_txn: LAYOUT__638,
};
pub const LAYOUT__687: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__686: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__687 };
pub const LAYOUT__684: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__685,
    _0: LAYOUT__686,
};
pub const LAYOUT__683: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__684,
};
pub const LAYOUT__690: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__639,
    new_txn: LAYOUT__640,
};
pub const LAYOUT__692: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
};
pub const LAYOUT__691: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__692 };
pub const LAYOUT__689: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__690,
    _0: LAYOUT__691,
};
pub const LAYOUT__688: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__689,
};
pub const LAYOUT__695: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__641,
    new_txn: LAYOUT__642,
};
pub const LAYOUT__697: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
};
pub const LAYOUT__696: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__697 };
pub const LAYOUT__694: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__695,
    _0: LAYOUT__696,
};
pub const LAYOUT__693: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__694,
};
pub const LAYOUT__700: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__643,
    new_txn: LAYOUT__644,
};
pub const LAYOUT__702: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
};
pub const LAYOUT__701: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__702 };
pub const LAYOUT__699: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__700,
    _0: LAYOUT__701,
};
pub const LAYOUT__698: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__699,
};
pub const LAYOUT__678: &ReadElemLayout8LayoutArray = &[
    LAYOUT__679,
    LAYOUT__680,
    LAYOUT__681,
    LAYOUT__682,
    LAYOUT__683,
    LAYOUT__688,
    LAYOUT__693,
    LAYOUT__698,
];
pub const LAYOUT__677: &PoseidonLoadStateLayout = &PoseidonLoadStateLayout {
    _super: LAYOUT__625,
    load_list: LAYOUT__678,
};
pub const LAYOUT__676: &Poseidon0StateArm1Layout = &Poseidon0StateArm1Layout {
    _super: LAYOUT__677,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
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
            _super: &Reg { offset: 161 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__707: &OneHot_3_Layout = &OneHot_3_Layout {
    _super: &[
        &NondetRegLayout {
            _super: &Reg { offset: 194 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 195 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 196 },
        },
    ],
};
pub const LAYOUT__712: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__656 };
pub const LAYOUT__711: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__712,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__713: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__656,
    _0: LAYOUT__657,
};
pub const LAYOUT__710: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__655,
    arm1: LAYOUT__711,
    arm2: LAYOUT__713,
};
pub const LAYOUT__715: &MemoryArgLayout2LayoutArray = &[LAYOUT__629, LAYOUT__630];
pub const LAYOUT__714: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__715,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    }],
};
pub const LAYOUT__709: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__710,
    _arguments_memory_get__super: LAYOUT__714,
};
pub const LAYOUT__719: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__661 };
pub const LAYOUT__718: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__719,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__720: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__661,
    _0: LAYOUT__662,
};
pub const LAYOUT__717: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__660,
    arm1: LAYOUT__718,
    arm2: LAYOUT__720,
};
pub const LAYOUT__722: &MemoryArgLayout2LayoutArray = &[LAYOUT__631, LAYOUT__632];
pub const LAYOUT__721: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__722,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    }],
};
pub const LAYOUT__716: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__717,
    _arguments_memory_get__super: LAYOUT__721,
};
pub const LAYOUT__726: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__666 };
pub const LAYOUT__725: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__726,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__727: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__666,
    _0: LAYOUT__667,
};
pub const LAYOUT__724: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__665,
    arm1: LAYOUT__725,
    arm2: LAYOUT__727,
};
pub const LAYOUT__729: &MemoryArgLayout2LayoutArray = &[LAYOUT__633, LAYOUT__634];
pub const LAYOUT__728: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__729,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    }],
};
pub const LAYOUT__723: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__724,
    _arguments_memory_get__super: LAYOUT__728,
};
pub const LAYOUT__733: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__670 };
pub const LAYOUT__732: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__733,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__734: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__670,
    _0: LAYOUT__671,
};
pub const LAYOUT__731: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__669,
    arm1: LAYOUT__732,
    arm2: LAYOUT__734,
};
pub const LAYOUT__736: &MemoryArgLayout2LayoutArray = &[LAYOUT__635, LAYOUT__636];
pub const LAYOUT__735: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__736,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    }],
};
pub const LAYOUT__730: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__731,
    _arguments_memory_get__super: LAYOUT__735,
};
pub const LAYOUT__740: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__685 };
pub const LAYOUT__739: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__740,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__741: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__685,
    _0: LAYOUT__686,
};
pub const LAYOUT__738: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__684,
    arm1: LAYOUT__739,
    arm2: LAYOUT__741,
};
pub const LAYOUT__743: &MemoryArgLayout2LayoutArray = &[LAYOUT__637, LAYOUT__638];
pub const LAYOUT__742: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__743,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    }],
};
pub const LAYOUT__737: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__738,
    _arguments_memory_get__super: LAYOUT__742,
};
pub const LAYOUT__747: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__690 };
pub const LAYOUT__746: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__747,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
};
pub const LAYOUT__748: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__690,
    _0: LAYOUT__691,
};
pub const LAYOUT__745: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__689,
    arm1: LAYOUT__746,
    arm2: LAYOUT__748,
};
pub const LAYOUT__750: &MemoryArgLayout2LayoutArray = &[LAYOUT__639, LAYOUT__640];
pub const LAYOUT__749: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__750,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    }],
};
pub const LAYOUT__744: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__745,
    _arguments_memory_get__super: LAYOUT__749,
};
pub const LAYOUT__754: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__695 };
pub const LAYOUT__753: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__754,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
};
pub const LAYOUT__755: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__695,
    _0: LAYOUT__696,
};
pub const LAYOUT__752: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__694,
    arm1: LAYOUT__753,
    arm2: LAYOUT__755,
};
pub const LAYOUT__757: &MemoryArgLayout2LayoutArray = &[LAYOUT__641, LAYOUT__642];
pub const LAYOUT__756: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__757,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    }],
};
pub const LAYOUT__751: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__752,
    _arguments_memory_get__super: LAYOUT__756,
};
pub const LAYOUT__761: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__700 };
pub const LAYOUT__760: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__761,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
};
pub const LAYOUT__762: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__700,
    _0: LAYOUT__701,
};
pub const LAYOUT__759: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__699,
    arm1: LAYOUT__760,
    arm2: LAYOUT__762,
};
pub const LAYOUT__764: &MemoryArgLayout2LayoutArray = &[LAYOUT__643, LAYOUT__644];
pub const LAYOUT__763: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__764,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    }],
};
pub const LAYOUT__758: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__759,
    _arguments_memory_get__super: LAYOUT__763,
};
pub const LAYOUT__708: &MemoryGetLayout8LayoutArray = &[
    LAYOUT__709,
    LAYOUT__716,
    LAYOUT__723,
    LAYOUT__730,
    LAYOUT__737,
    LAYOUT__744,
    LAYOUT__751,
    LAYOUT__758,
];
pub const LAYOUT__706: &PoseidonLoadInShortLayout = &PoseidonLoadInShortLayout {
    _super: LAYOUT__625,
    tx_type: LAYOUT__707,
    load_list: LAYOUT__708,
};
pub const LAYOUT__765: &PoseidonLoadInLowLayout = &PoseidonLoadInLowLayout {
    _super: LAYOUT__625,
    tx_type: LAYOUT__707,
    load_list: LAYOUT__708,
};
pub const LAYOUT__766: &PoseidonLoadInHighLayout = &PoseidonLoadInHighLayout {
    _super: LAYOUT__625,
    tx_type: LAYOUT__707,
    load_list: LAYOUT__708,
};
pub const LAYOUT__705: &PoseidonLoadIn_SuperLayout = &PoseidonLoadIn_SuperLayout {
    _super: LAYOUT__625,
    arm0: LAYOUT__706,
    arm1: LAYOUT__765,
    arm2: LAYOUT__766,
};
pub const LAYOUT__767: &OneHot_3_Layout = &OneHot_3_Layout {
    _super: &[
        &NondetRegLayout {
            _super: &Reg { offset: 197 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 198 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 199 },
        },
    ],
};
pub const LAYOUT__768: &_Arguments_PoseidonLoadIn_SuperLayout =
    &_Arguments_PoseidonLoadIn_SuperLayout {
        memory_arg: LAYOUT__628,
        cycle_arg: LAYOUT__645,
    };
pub const LAYOUT__704: &PoseidonLoadInLayout = &PoseidonLoadInLayout {
    _super: LAYOUT__705,
    _0: LAYOUT__767,
    _arguments_poseidon_load_in__super: LAYOUT__768,
};
pub const LAYOUT__703: &Poseidon0StateArm2Layout = &Poseidon0StateArm2Layout {
    _super: LAYOUT__704,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
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
            _super: &Reg { offset: 161 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__769: &Poseidon0StateArm3Layout = &Poseidon0StateArm3Layout {
    _super: LAYOUT__625,
    _extra0: LAYOUT__629,
    _extra1: LAYOUT__630,
    _extra2: LAYOUT__631,
    _extra3: LAYOUT__632,
    _extra4: LAYOUT__633,
    _extra5: LAYOUT__634,
    _extra6: LAYOUT__635,
    _extra7: LAYOUT__636,
    _extra8: LAYOUT__637,
    _extra9: LAYOUT__638,
    _extra10: LAYOUT__639,
    _extra11: LAYOUT__640,
    _extra12: LAYOUT__641,
    _extra13: LAYOUT__642,
    _extra14: LAYOUT__643,
    _extra15: LAYOUT__644,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
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
            _super: &Reg { offset: 161 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
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
            _super: &Reg { offset: 169 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__770: &Poseidon0StateArm4Layout = &Poseidon0StateArm4Layout {
    _super: LAYOUT__625,
    _extra0: LAYOUT__629,
    _extra1: LAYOUT__630,
    _extra2: LAYOUT__631,
    _extra3: LAYOUT__632,
    _extra4: LAYOUT__633,
    _extra5: LAYOUT__634,
    _extra6: LAYOUT__635,
    _extra7: LAYOUT__636,
    _extra8: LAYOUT__637,
    _extra9: LAYOUT__638,
    _extra10: LAYOUT__639,
    _extra11: LAYOUT__640,
    _extra12: LAYOUT__641,
    _extra13: LAYOUT__642,
    _extra14: LAYOUT__643,
    _extra15: LAYOUT__644,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
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
            _super: &Reg { offset: 161 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
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
            _super: &Reg { offset: 169 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__777: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__679 };
pub const LAYOUT__778: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__680 };
pub const LAYOUT__779: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__681 };
pub const LAYOUT__780: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__682 };
pub const LAYOUT__781: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__683 };
pub const LAYOUT__782: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__688 };
pub const LAYOUT__783: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__693 };
pub const LAYOUT__784: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__698 };
pub const LAYOUT__776: &PoseidonCheckOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__777,
    LAYOUT__778,
    LAYOUT__779,
    LAYOUT__780,
    LAYOUT__781,
    LAYOUT__782,
    LAYOUT__783,
    LAYOUT__784,
];
pub const LAYOUT__775: &PoseidonCheckOutLayout = &PoseidonCheckOutLayout {
    _super: LAYOUT__625,
    _1: LAYOUT__776,
    is_normal: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 194 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 195 },
        },
    },
    ext_inv: &NondetExtRegLayout {
        _super: &Reg { offset: 196 },
    },
};
pub const LAYOUT__774: &PoseidonDoOut_SuperArm0Layout = &PoseidonDoOut_SuperArm0Layout {
    _super: LAYOUT__775,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
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
            _super: &Reg { offset: 161 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__788: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
};
pub const LAYOUT__790: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
};
pub const LAYOUT__789: &U16RegLayout = &U16RegLayout { ret: LAYOUT__790 };
pub const LAYOUT__791: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__656,
    _0: LAYOUT__657,
};
pub const LAYOUT__787: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__788,
    high: LAYOUT__789,
    _0: LAYOUT__791,
};
pub const LAYOUT__793: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
};
pub const LAYOUT__794: &U16RegLayout = &U16RegLayout { ret: LAYOUT__203 };
pub const LAYOUT__795: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__661,
    _0: LAYOUT__662,
};
pub const LAYOUT__792: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__793,
    high: LAYOUT__794,
    _0: LAYOUT__795,
};
pub const LAYOUT__797: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
};
pub const LAYOUT__799: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
};
pub const LAYOUT__798: &U16RegLayout = &U16RegLayout { ret: LAYOUT__799 };
pub const LAYOUT__800: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__666,
    _0: LAYOUT__667,
};
pub const LAYOUT__796: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__797,
    high: LAYOUT__798,
    _0: LAYOUT__800,
};
pub const LAYOUT__802: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
};
pub const LAYOUT__804: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
};
pub const LAYOUT__803: &U16RegLayout = &U16RegLayout { ret: LAYOUT__804 };
pub const LAYOUT__805: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__670,
    _0: LAYOUT__671,
};
pub const LAYOUT__801: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__802,
    high: LAYOUT__803,
    _0: LAYOUT__805,
};
pub const LAYOUT__808: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
};
pub const LAYOUT__807: &U16RegLayout = &U16RegLayout { ret: LAYOUT__808 };
pub const LAYOUT__809: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__685,
    _0: LAYOUT__686,
};
pub const LAYOUT__806: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__290,
    high: LAYOUT__807,
    _0: LAYOUT__809,
};
pub const LAYOUT__811: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
};
pub const LAYOUT__813: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
};
pub const LAYOUT__812: &U16RegLayout = &U16RegLayout { ret: LAYOUT__813 };
pub const LAYOUT__814: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__690,
    _0: LAYOUT__691,
};
pub const LAYOUT__810: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__811,
    high: LAYOUT__812,
    _0: LAYOUT__814,
};
pub const LAYOUT__816: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__818: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__817: &U16RegLayout = &U16RegLayout { ret: LAYOUT__818 };
pub const LAYOUT__819: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__695,
    _0: LAYOUT__696,
};
pub const LAYOUT__815: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__816,
    high: LAYOUT__817,
    _0: LAYOUT__819,
};
pub const LAYOUT__821: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
};
pub const LAYOUT__823: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__822: &U16RegLayout = &U16RegLayout { ret: LAYOUT__823 };
pub const LAYOUT__824: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__700,
    _0: LAYOUT__701,
};
pub const LAYOUT__820: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__821,
    high: LAYOUT__822,
    _0: LAYOUT__824,
};
pub const LAYOUT__786: &PoseidonStoreOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__787,
    LAYOUT__792,
    LAYOUT__796,
    LAYOUT__801,
    LAYOUT__806,
    LAYOUT__810,
    LAYOUT__815,
    LAYOUT__820,
];
pub const LAYOUT__785: &PoseidonStoreOutLayout = &PoseidonStoreOutLayout {
    _super: LAYOUT__625,
    _1: LAYOUT__786,
    is_normal: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 194 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 195 },
        },
    },
    ext_inv: &NondetExtRegLayout {
        _super: &Reg { offset: 196 },
    },
};
pub const LAYOUT__773: &PoseidonDoOut_SuperLayout = &PoseidonDoOut_SuperLayout {
    _super: LAYOUT__625,
    arm0: LAYOUT__774,
    arm1: LAYOUT__785,
};
pub const LAYOUT__825: &_Arguments_PoseidonDoOut_SuperLayout =
    &_Arguments_PoseidonDoOut_SuperLayout {
        memory_arg: LAYOUT__628,
        cycle_arg: LAYOUT__645,
        arg_u16: LAYOUT__646,
    };
pub const LAYOUT__772: &PoseidonDoOutLayout = &PoseidonDoOutLayout {
    _super: LAYOUT__773,
    _arguments_poseidon_do_out__super: LAYOUT__825,
};
pub const LAYOUT__771: &Poseidon0StateArm5Layout = &Poseidon0StateArm5Layout {
    _super: LAYOUT__772,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__828: &PoseidonPaging_SuperLayout = &PoseidonPaging_SuperLayout {
    _super: LAYOUT__625,
    arm0: LAYOUT__625,
    arm1: LAYOUT__625,
    arm2: LAYOUT__625,
    arm3: LAYOUT__625,
    arm4: LAYOUT__625,
    arm5: LAYOUT__625,
};
pub const LAYOUT__830: &NondetRegLayout6LayoutArray = &[
    &NondetRegLayout {
        _super: &Reg { offset: 196 },
    },
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
];
pub const LAYOUT__829: &OneHot_6_Layout = &OneHot_6_Layout {
    _super: LAYOUT__830,
};
pub const LAYOUT__833: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
};
pub const LAYOUT__832: &U8RegLayout = &U8RegLayout { ret: LAYOUT__833 };
pub const LAYOUT__831: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__788,
    _0: LAYOUT__832,
};
pub const LAYOUT__834: &_Arguments_PoseidonPaging__1Layout = &_Arguments_PoseidonPaging__1Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    }],
    arg_u8: &[&ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    }],
};
pub const LAYOUT__839: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__838: &U8RegLayout = &U8RegLayout { ret: LAYOUT__839 };
pub const LAYOUT__837: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__790,
    _0: LAYOUT__838,
};
pub const LAYOUT__836: &PoseidonPaging__1Arm0_SuperLayout =
    &PoseidonPaging__1Arm0_SuperLayout { _0: LAYOUT__837 };
pub const LAYOUT__840: &PoseidonPaging__1Arm1_SuperLayout =
    &PoseidonPaging__1Arm1_SuperLayout { _0: LAYOUT__837 };
pub const LAYOUT__835: &PoseidonPaging__1Layout = &PoseidonPaging__1Layout {
    arm0: LAYOUT__836,
    arm1: LAYOUT__840,
};
pub const LAYOUT__827: &PoseidonPagingLayout = &PoseidonPagingLayout {
    _super: LAYOUT__828,
    cur_idx: &NondetRegLayout {
        _super: &Reg { offset: 194 },
    },
    cur_mode: &NondetRegLayout {
        _super: &Reg { offset: 195 },
    },
    mode_split: LAYOUT__829,
    _0: LAYOUT__831,
    _arguments_poseidon_paging__1: LAYOUT__834,
    _3: LAYOUT__835,
    _4: &NondetRegLayout {
        _super: &Reg { offset: 202 },
    },
};
pub const LAYOUT__826: &Poseidon0StateArm6Layout = &Poseidon0StateArm6Layout {
    _super: LAYOUT__827,
    _extra0: LAYOUT__629,
    _extra1: LAYOUT__630,
    _extra2: LAYOUT__631,
    _extra3: LAYOUT__632,
    _extra4: LAYOUT__633,
    _extra5: LAYOUT__634,
    _extra6: LAYOUT__635,
    _extra7: LAYOUT__636,
    _extra8: LAYOUT__637,
    _extra9: LAYOUT__638,
    _extra10: LAYOUT__639,
    _extra11: LAYOUT__640,
    _extra12: LAYOUT__641,
    _extra13: LAYOUT__642,
    _extra14: LAYOUT__643,
    _extra15: LAYOUT__644,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 153 },
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
            _super: &Reg { offset: 161 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
    },
};
pub const LAYOUT__844: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__788,
    high: LAYOUT__789,
    _0: LAYOUT__791,
};
pub const LAYOUT__845: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__793,
    high: LAYOUT__794,
    _0: LAYOUT__795,
};
pub const LAYOUT__846: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__797,
    high: LAYOUT__798,
    _0: LAYOUT__800,
};
pub const LAYOUT__847: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__802,
    high: LAYOUT__803,
    _0: LAYOUT__805,
};
pub const LAYOUT__848: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__290,
    high: LAYOUT__807,
    _0: LAYOUT__809,
};
pub const LAYOUT__849: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__811,
    high: LAYOUT__812,
    _0: LAYOUT__814,
};
pub const LAYOUT__850: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__816,
    high: LAYOUT__817,
    _0: LAYOUT__819,
};
pub const LAYOUT__851: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__821,
    high: LAYOUT__822,
    _0: LAYOUT__824,
};
pub const LAYOUT__843: &PoseidonStoreState__0_SuperLayout8LayoutArray = &[
    LAYOUT__844,
    LAYOUT__845,
    LAYOUT__846,
    LAYOUT__847,
    LAYOUT__848,
    LAYOUT__849,
    LAYOUT__850,
    LAYOUT__851,
];
pub const LAYOUT__842: &PoseidonStoreStateLayout = &PoseidonStoreStateLayout {
    _super: LAYOUT__625,
    _1: LAYOUT__843,
};
pub const LAYOUT__841: &Poseidon0StateArm7Layout = &Poseidon0StateArm7Layout {
    _super: LAYOUT__842,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
};
pub const LAYOUT__648: &Poseidon0StateLayout = &Poseidon0StateLayout {
    _super: LAYOUT__625,
    arm0: LAYOUT__649,
    arm1: LAYOUT__676,
    arm2: LAYOUT__703,
    arm3: LAYOUT__769,
    arm4: LAYOUT__770,
    arm5: LAYOUT__771,
    arm6: LAYOUT__826,
    arm7: LAYOUT__841,
};
pub const LAYOUT__623: &Poseidon0Layout = &Poseidon0Layout {
    _0: LAYOUT__624,
    state: LAYOUT__625,
    _arguments_poseidon0_state: LAYOUT__627,
    state_redef: LAYOUT__648,
};
pub const LAYOUT__853: &DoCycleTableLayout = &DoCycleTableLayout {
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
pub const LAYOUT__858: &SBoxLayout24LayoutArray = &[
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
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
];
pub const LAYOUT__857: &DoExtRoundLayout = &DoExtRoundLayout { _1: LAYOUT__858 };
pub const LAYOUT__860: &NondetRegLayout8LayoutArray = &[
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
pub const LAYOUT__859: &OneHot_8_Layout = &OneHot_8_Layout {
    _super: LAYOUT__860,
};
pub const LAYOUT__856: &DoExtRoundByIdxLayout = &DoExtRoundByIdxLayout {
    _super: LAYOUT__857,
    idx_hot: LAYOUT__859,
};
pub const LAYOUT__855: &PoseidonExtRoundLayout = &PoseidonExtRoundLayout {
    _super: LAYOUT__625,
    is_round3: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
    is_round7: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
    last_block: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
    next_inner: LAYOUT__856,
};
pub const LAYOUT__864: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
};
pub const LAYOUT__865: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
};
pub const LAYOUT__866: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__867: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
};
pub const LAYOUT__868: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__869: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
};
pub const LAYOUT__870: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
};
pub const LAYOUT__871: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__872: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
};
pub const LAYOUT__873: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__874: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
};
pub const LAYOUT__875: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__876: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
};
pub const LAYOUT__877: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
    },
};
pub const LAYOUT__878: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
    },
};
pub const LAYOUT__879: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
};
pub const LAYOUT__880: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__881: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
};
pub const LAYOUT__882: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
};
pub const LAYOUT__883: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
};
pub const LAYOUT__884: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__863: &DoIntRoundLayout21LayoutArray = &[
    LAYOUT__864,
    LAYOUT__865,
    LAYOUT__866,
    LAYOUT__867,
    LAYOUT__868,
    LAYOUT__869,
    LAYOUT__870,
    LAYOUT__871,
    LAYOUT__872,
    LAYOUT__873,
    LAYOUT__874,
    LAYOUT__875,
    LAYOUT__876,
    LAYOUT__877,
    LAYOUT__878,
    LAYOUT__879,
    LAYOUT__880,
    LAYOUT__881,
    LAYOUT__882,
    LAYOUT__883,
    LAYOUT__884,
];
pub const LAYOUT__862: &DoIntRoundsLayout = &DoIntRoundsLayout {
    _super: LAYOUT__863,
};
pub const LAYOUT__861: &PoseidonIntRoundsLayout = &PoseidonIntRoundsLayout {
    _super: LAYOUT__625,
    next_inner: LAYOUT__862,
};
pub const LAYOUT__854: &Poseidon1StateLayout = &Poseidon1StateLayout {
    _super: LAYOUT__625,
    arm0: LAYOUT__855,
    arm1: LAYOUT__861,
    arm2: LAYOUT__625,
    arm3: LAYOUT__625,
    arm4: LAYOUT__625,
    arm5: LAYOUT__625,
    arm6: LAYOUT__625,
    arm7: LAYOUT__625,
};
pub const LAYOUT__852: &Poseidon1Layout = &Poseidon1Layout {
    _0: LAYOUT__853,
    state: LAYOUT__625,
    state_redef: LAYOUT__854,
};
pub const LAYOUT__6: &TopInstResultLayout = &TopInstResultLayout {
    _selector: LAYOUT__5,
    arm0: LAYOUT__7,
    arm1: LAYOUT__89,
    arm2: LAYOUT__107,
    arm3: LAYOUT__120,
    arm4: LAYOUT__205,
    arm5: LAYOUT__292,
    arm6: LAYOUT__354,
    arm7: LAYOUT__398,
    arm8: LAYOUT__570,
    arm9: LAYOUT__623,
    arm10: LAYOUT__852,
};
pub const LAYOUT__0: &TopLayout = &TopLayout {
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    next_pc_low: &NondetRegLayout {
        _super: &Reg { offset: 12 },
    },
    next_pc_high: &NondetRegLayout {
        _super: &Reg { offset: 13 },
    },
    next_state_0: &NondetRegLayout {
        _super: &Reg { offset: 14 },
    },
    next_machine_mode: &NondetRegLayout {
        _super: &Reg { offset: 15 },
    },
    is_first_cycle: &NondetRegLayout {
        _super: &Reg { offset: 16 },
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
        _super: &Reg { offset: 17 },
    },
    minor: &NondetRegLayout {
        _super: &Reg { offset: 18 },
    },
    inst_input: LAYOUT__1,
    major_onehot: LAYOUT__4,
    inst_result: LAYOUT__6,
};
pub const LAYOUT__886: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__885: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__886,
};
pub const LAYOUT__888: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__887: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__888,
};
pub const LAYOUT__890: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__889: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__890,
};
pub const LAYOUT__892: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__891: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__892,
};
pub const LAYOUT__893: &_accumLayout = &_accumLayout {
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
        _super: &Reg { offset: 12 },
    },
    next_pc_high: &NondetRegLayout {
        _super: &Reg { offset: 13 },
    },
    next_state_0: &NondetRegLayout {
        _super: &Reg { offset: 14 },
    },
    next_machine_mode: &NondetRegLayout {
        _super: &Reg { offset: 15 },
    },
    is_first_cycle: &NondetRegLayout {
        _super: &Reg { offset: 16 },
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
        _super: &Reg { offset: 17 },
    },
    minor: &NondetRegLayout {
        _super: &Reg { offset: 18 },
    },
    inst_input: LAYOUT__1,
    major_onehot: LAYOUT__4,
    inst_result: LAYOUT__6,
};
pub const LAYOUT_GLOBAL: &_globalLayout = &_globalLayout {
    input: LAYOUT__885,
    is_terminate: &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    output: LAYOUT__887,
    rng: &NondetExtRegLayout {
        _super: &Reg { offset: 33 },
    },
    shutdown_cycle: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    state_in: LAYOUT__889,
    state_out: LAYOUT__891,
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
    randomness: LAYOUT__893,
};
