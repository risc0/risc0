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
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 58 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 59 },
    },
};
pub const LAYOUT__17: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__18,
    new_txn: LAYOUT__19,
};
pub const LAYOUT__21: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 61 },
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
pub const LAYOUT__24: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 62 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 63 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 65 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 66 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
};
pub const LAYOUT__27: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
};
pub const LAYOUT__26: &U16RegLayout = &U16RegLayout { ret: LAYOUT__27 };
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
pub const LAYOUT__25: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    upper_diff: LAYOUT__26,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
    med14: LAYOUT__28,
};
pub const LAYOUT__31: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__32: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
};
pub const LAYOUT__30: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__31,
    new_txn: LAYOUT__32,
};
pub const LAYOUT__34: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
};
pub const LAYOUT__33: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__34 };
pub const LAYOUT__29: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__30,
    _0: LAYOUT__33,
};
pub const LAYOUT__23: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__24,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
    pc_addr: LAYOUT__25,
    load_inst: LAYOUT__29,
};
pub const LAYOUT__38: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 96 },
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
pub const LAYOUT__39: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
};
pub const LAYOUT__37: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__38,
    new_txn: LAYOUT__39,
};
pub const LAYOUT__41: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 105 },
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
        _super: &Reg { offset: 106 },
    },
};
pub const LAYOUT__45: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 107 },
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
pub const LAYOUT__46: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
};
pub const LAYOUT__44: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__45,
    new_txn: LAYOUT__46,
};
pub const LAYOUT__48: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 116 },
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
        _super: &Reg { offset: 117 },
    },
};
pub const LAYOUT__22: &MiscInputLayout = &MiscInputLayout {
    decoded: LAYOUT__23,
    rs1: LAYOUT__35,
    rs2: LAYOUT__42,
};
pub const LAYOUT__50: &ArgU16Layout5LayoutArray = &[
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
pub const LAYOUT__49: &_Arguments_Misc0MiscOutputLayout = &_Arguments_Misc0MiscOutputLayout {
    arg_u16: LAYOUT__50,
};
pub const LAYOUT__52: &Misc0MiscOutputArm0Layout = &Misc0MiscOutputArm0Layout {
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
pub const LAYOUT__53: &Misc0MiscOutputArm1Layout = &Misc0MiscOutputArm1Layout {
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
pub const LAYOUT__60: &NondetRegLayout16LayoutArray = &[
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
    &NondetRegLayout {
        _super: &Reg { offset: 132 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 133 },
    },
];
pub const LAYOUT__59: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__60 };
pub const LAYOUT__62: &NondetRegLayout16LayoutArray = &[
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
    &NondetRegLayout {
        _super: &Reg { offset: 148 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 149 },
    },
];
pub const LAYOUT__61: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__62 };
pub const LAYOUT__58: &BitwiseAndU16Layout = &BitwiseAndU16Layout {
    bits_x: LAYOUT__59,
    bits_y: LAYOUT__61,
};
pub const LAYOUT__65: &NondetRegLayout16LayoutArray = &[
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
    &NondetRegLayout {
        _super: &Reg { offset: 164 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
];
pub const LAYOUT__64: &ToBits_16_Layout = &ToBits_16_Layout { _super: LAYOUT__65 };
pub const LAYOUT__67: &NondetRegLayout16LayoutArray = &[
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
    &NondetRegLayout {
        _super: &Reg { offset: 180 },
    },
    &NondetRegLayout {
        _super: &Reg { offset: 181 },
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
pub const LAYOUT__70: &BitwiseOrLayout = &BitwiseOrLayout { and_xy: LAYOUT__57 };
pub const LAYOUT__69: &OpORLayout = &OpORLayout { _0: LAYOUT__70 };
pub const LAYOUT__68: &Misc0MiscOutputArm3Layout = &Misc0MiscOutputArm3Layout {
    _super: LAYOUT__69,
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
pub const LAYOUT__72: &OpANDLayout = &OpANDLayout { _0: LAYOUT__57 };
pub const LAYOUT__71: &Misc0MiscOutputArm4Layout = &Misc0MiscOutputArm4Layout {
    _super: LAYOUT__72,
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
pub const LAYOUT__76: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
};
pub const LAYOUT__77: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
};
pub const LAYOUT__75: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__76,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    high16: LAYOUT__77,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
};
pub const LAYOUT__79: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__78: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    rest_times_two: LAYOUT__79,
};
pub const LAYOUT__81: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__80: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    rest_times_two: LAYOUT__81,
};
pub const LAYOUT__83: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 35 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 36 },
        },
    },
};
pub const LAYOUT__82: &GetSignU32Layout = &GetSignU32Layout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
    rest_times_two: LAYOUT__83,
};
pub const LAYOUT__74: &CmpLessThanLayout = &CmpLessThanLayout {
    diff: LAYOUT__75,
    s1: LAYOUT__78,
    s2: LAYOUT__80,
    s3: LAYOUT__82,
    overflow: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    is_less_than: &NondetRegLayout {
        _super: &Reg { offset: 124 },
    },
};
pub const LAYOUT__73: &OpSLTLayout = &OpSLTLayout { cmp: LAYOUT__74 };
pub const LAYOUT__86: &CmpLessThanUnsignedLayout = &CmpLessThanUnsignedLayout { diff: LAYOUT__75 };
pub const LAYOUT__85: &OpSLTULayout = &OpSLTULayout { cmp: LAYOUT__86 };
pub const LAYOUT__84: &Misc0MiscOutputArm6Layout = &Misc0MiscOutputArm6Layout {
    _super: LAYOUT__85,
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
pub const LAYOUT__87: &Misc0MiscOutputArm7Layout = &Misc0MiscOutputArm7Layout {
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
    input: LAYOUT__22,
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
pub const LAYOUT__94: &OpORILayout = &OpORILayout { _0: LAYOUT__70 };
pub const LAYOUT__93: &Misc1MiscOutputArm1Layout = &Misc1MiscOutputArm1Layout {
    _super: LAYOUT__94,
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
pub const LAYOUT__96: &OpANDILayout = &OpANDILayout { _0: LAYOUT__57 };
pub const LAYOUT__95: &Misc1MiscOutputArm2Layout = &Misc1MiscOutputArm2Layout {
    _super: LAYOUT__96,
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
pub const LAYOUT__97: &OpSLTILayout = &OpSLTILayout { cmp: LAYOUT__74 };
pub const LAYOUT__99: &OpSLTIULayout = &OpSLTIULayout { cmp: LAYOUT__86 };
pub const LAYOUT__98: &Misc1MiscOutputArm4Layout = &Misc1MiscOutputArm4Layout {
    _super: LAYOUT__99,
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
pub const LAYOUT__102: &CmpEqualLayout = &CmpEqualLayout {
    low_same: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
    high_same: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
    },
    is_equal: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
};
pub const LAYOUT__101: &OpBEQLayout = &OpBEQLayout { cmp: LAYOUT__102 };
pub const LAYOUT__100: &Misc1MiscOutputArm5Layout = &Misc1MiscOutputArm5Layout {
    _super: LAYOUT__101,
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
pub const LAYOUT__104: &OpBNELayout = &OpBNELayout { cmp: LAYOUT__102 };
pub const LAYOUT__103: &Misc1MiscOutputArm6Layout = &Misc1MiscOutputArm6Layout {
    _super: LAYOUT__104,
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
    input: LAYOUT__22,
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
pub const LAYOUT__113: &OpBGEULayout = &OpBGEULayout { cmp: LAYOUT__86 };
pub const LAYOUT__112: &Misc2MiscOutputArm2Layout = &Misc2MiscOutputArm2Layout {
    _super: LAYOUT__113,
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
pub const LAYOUT__114: &Misc2MiscOutputArm3Layout = &Misc2MiscOutputArm3Layout {
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
pub const LAYOUT__115: &Misc2MiscOutputArm4Layout = &Misc2MiscOutputArm4Layout {
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
pub const LAYOUT__116: &Misc2MiscOutputArm5Layout = &Misc2MiscOutputArm5Layout {
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
pub const LAYOUT__117: &Misc2MiscOutputArm6Layout = &Misc2MiscOutputArm6Layout {
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
pub const LAYOUT__118: &Misc2MiscOutputArm7Layout = &Misc2MiscOutputArm7Layout {
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
    input: LAYOUT__22,
    _arguments_misc2_misc_output: LAYOUT__107,
    misc_output: LAYOUT__108,
};
pub const LAYOUT__122: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 65 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 66 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 78 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
};
pub const LAYOUT__125: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
    },
};
pub const LAYOUT__124: &U16RegLayout = &U16RegLayout { ret: LAYOUT__125 };
pub const LAYOUT__126: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
    },
};
pub const LAYOUT__123: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    upper_diff: LAYOUT__124,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
    },
    med14: LAYOUT__126,
};
pub const LAYOUT__129: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 89 },
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
pub const LAYOUT__130: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
};
pub const LAYOUT__128: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__129,
    new_txn: LAYOUT__130,
};
pub const LAYOUT__132: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
};
pub const LAYOUT__131: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__132 };
pub const LAYOUT__127: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__128,
    _0: LAYOUT__131,
};
pub const LAYOUT__121: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__122,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
    pc_addr: LAYOUT__123,
    load_inst: LAYOUT__127,
};
pub const LAYOUT__136: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__137: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
};
pub const LAYOUT__135: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__136,
    new_txn: LAYOUT__137,
};
pub const LAYOUT__139: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 108 },
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
        _super: &Reg { offset: 109 },
    },
};
pub const LAYOUT__143: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
};
pub const LAYOUT__144: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 117 },
    },
};
pub const LAYOUT__142: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__143,
    new_txn: LAYOUT__144,
};
pub const LAYOUT__146: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 119 },
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
        _super: &Reg { offset: 120 },
    },
};
pub const LAYOUT__120: &MulInputLayout = &MulInputLayout {
    decoded: LAYOUT__121,
    rs1: LAYOUT__133,
    rs2: LAYOUT__140,
};
pub const LAYOUT__148: &ArgU16Layout6LayoutArray = &[
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
pub const LAYOUT__149: &ArgU8Layout13LayoutArray = &[
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
pub const LAYOUT__147: &_Arguments_Mul0MulOutputLayout = &_Arguments_Mul0MulOutputLayout {
    arg_u16: LAYOUT__148,
    arg_u8: LAYOUT__149,
};
pub const LAYOUT__154: &NondetRegLayout5LayoutArray = &[
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
];
pub const LAYOUT__153: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__154,
};
pub const LAYOUT__152: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__153,
    check_u16: LAYOUT__76,
    b3: &NondetRegLayout {
        _super: &Reg { offset: 126 },
    },
    low: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    high: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
};
pub const LAYOUT__158: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__159: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
};
pub const LAYOUT__160: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__161: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 45 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 46 },
        },
    },
};
pub const LAYOUT__162: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 47 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 48 },
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
        _super: &Reg { offset: 129 },
    },
};
pub const LAYOUT__164: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
};
pub const LAYOUT__165: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
};
pub const LAYOUT__166: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
};
pub const LAYOUT__167: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
};
pub const LAYOUT__168: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
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
        _super: &Reg { offset: 130 },
    },
};
pub const LAYOUT__170: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__169: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__79,
    carry_byte: LAYOUT__170,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
};
pub const LAYOUT__172: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
};
pub const LAYOUT__171: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__81,
    carry_byte: LAYOUT__172,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
};
pub const LAYOUT__174: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
};
pub const LAYOUT__173: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__83,
    carry_byte: LAYOUT__174,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
};
pub const LAYOUT__156: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__157,
    bx: LAYOUT__163,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    c_rest_times2: LAYOUT__77,
    s0: LAYOUT__169,
    s1: LAYOUT__171,
    s2: LAYOUT__173,
    s3_out: LAYOUT__10,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 139 },
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
        _super: &Reg { offset: 121 },
    },
};
pub const LAYOUT__181: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__164,
    b1: LAYOUT__165,
    b2: LAYOUT__166,
    b3: LAYOUT__167,
    b3_top7times2: LAYOUT__168,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
};
pub const LAYOUT__182: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__77,
    carry_byte: LAYOUT__170,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
    },
};
pub const LAYOUT__183: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__79,
    carry_byte: LAYOUT__172,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
    },
};
pub const LAYOUT__184: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__81,
    carry_byte: LAYOUT__174,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
};
pub const LAYOUT__179: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__180,
    bx: LAYOUT__181,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    c_rest_times2: LAYOUT__76,
    s0: LAYOUT__182,
    s1: LAYOUT__183,
    s2: LAYOUT__184,
    s3_out: LAYOUT__83,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
};
pub const LAYOUT__178: &DoMulLayout = &DoMulLayout { mul: LAYOUT__179 };
pub const LAYOUT__177: &OpMULLayout = &OpMULLayout { _0: LAYOUT__178 };
pub const LAYOUT__176: &Mul0MulOutputArm2Layout = &Mul0MulOutputArm2Layout {
    _super: LAYOUT__177,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__186: &OpMULHLayout = &OpMULHLayout { _0: LAYOUT__178 };
pub const LAYOUT__185: &Mul0MulOutputArm3Layout = &Mul0MulOutputArm3Layout {
    _super: LAYOUT__186,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 37 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 38 },
        },
    },
};
pub const LAYOUT__188: &OpMULHSULayout = &OpMULHSULayout { _0: LAYOUT__178 };
pub const LAYOUT__187: &Mul0MulOutputArm4Layout = &Mul0MulOutputArm4Layout {
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
pub const LAYOUT__190: &OpMULHULayout = &OpMULHULayout { _0: LAYOUT__178 };
pub const LAYOUT__189: &Mul0MulOutputArm5Layout = &Mul0MulOutputArm5Layout {
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
pub const LAYOUT__191: &Mul0MulOutputArm6Layout = &Mul0MulOutputArm6Layout {
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
pub const LAYOUT__192: &Mul0MulOutputArm7Layout = &Mul0MulOutputArm7Layout {
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
        _super: &Reg { offset: 144 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 143 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 145 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 146 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 147 },
    },
};
pub const LAYOUT__197: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 148 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 143 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 149 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 150 },
    },
};
pub const LAYOUT__195: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__196,
    new_txn: LAYOUT__197,
};
pub const LAYOUT__199: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 152 },
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
            _super: &Reg { offset: 140 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 142 },
    },
    _0: LAYOUT__194,
};
pub const LAYOUT__201: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
};
pub const LAYOUT__202: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
};
pub const LAYOUT__200: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__201,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 155 },
    },
    high16: LAYOUT__202,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
};
pub const LAYOUT__119: &Mul0Layout = &Mul0Layout {
    input: LAYOUT__120,
    _arguments_mul0_mul_output: LAYOUT__147,
    mul_output: LAYOUT__150,
    _0: LAYOUT__193,
    pc_add: LAYOUT__200,
};
pub const LAYOUT__206: &DecoderLayout = &DecoderLayout {
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
pub const LAYOUT__209: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
    },
};
pub const LAYOUT__208: &U16RegLayout = &U16RegLayout { ret: LAYOUT__209 };
pub const LAYOUT__210: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
};
pub const LAYOUT__207: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    upper_diff: LAYOUT__208,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    med14: LAYOUT__210,
};
pub const LAYOUT__213: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 95 },
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
pub const LAYOUT__214: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
};
pub const LAYOUT__212: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__213,
    new_txn: LAYOUT__214,
};
pub const LAYOUT__216: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
};
pub const LAYOUT__215: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__216 };
pub const LAYOUT__211: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__212,
    _0: LAYOUT__215,
};
pub const LAYOUT__205: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__206,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
    pc_addr: LAYOUT__207,
    load_inst: LAYOUT__211,
};
pub const LAYOUT__220: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__221: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 110 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
};
pub const LAYOUT__219: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__220,
    new_txn: LAYOUT__221,
};
pub const LAYOUT__223: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 114 },
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
        _super: &Reg { offset: 115 },
    },
};
pub const LAYOUT__227: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__228: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 116 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
};
pub const LAYOUT__226: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__227,
    new_txn: LAYOUT__228,
};
pub const LAYOUT__230: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 125 },
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
        _super: &Reg { offset: 126 },
    },
};
pub const LAYOUT__204: &DivInputLayout = &DivInputLayout {
    decoded: LAYOUT__205,
    rs1: LAYOUT__217,
    rs2: LAYOUT__224,
};
pub const LAYOUT__232: &ArgU16Layout9LayoutArray = &[
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
pub const LAYOUT__233: &ArgU8Layout13LayoutArray = &[
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
pub const LAYOUT__231: &_Arguments_Div0MulOutputLayout = &_Arguments_Div0MulOutputLayout {
    arg_u16: LAYOUT__232,
    arg_u8: LAYOUT__233,
};
pub const LAYOUT__239: &NondetRegLayout5LayoutArray = &[
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
pub const LAYOUT__238: &ToBits_5_Layout = &ToBits_5_Layout {
    _super: LAYOUT__239,
};
pub const LAYOUT__237: &DynPo2Layout = &DynPo2Layout {
    low5: LAYOUT__238,
    check_u16: LAYOUT__76,
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
pub const LAYOUT__242: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__161,
    b1: LAYOUT__162,
    b2: LAYOUT__164,
    b3: LAYOUT__165,
    b3_top7times2: LAYOUT__166,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
};
pub const LAYOUT__243: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__167,
    b1: LAYOUT__168,
    b2: LAYOUT__170,
    b3: LAYOUT__172,
    b3_top7times2: LAYOUT__174,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
};
pub const LAYOUT__245: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__244: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__83,
    carry_byte: LAYOUT__245,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__247: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__246: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__10,
    carry_byte: LAYOUT__247,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__249: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 39 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 40 },
        },
    },
};
pub const LAYOUT__250: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__248: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__249,
    carry_byte: LAYOUT__250,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__251: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 41 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 42 },
        },
    },
};
pub const LAYOUT__241: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__242,
    bx: LAYOUT__243,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
    c_rest_times2: LAYOUT__81,
    s0: LAYOUT__244,
    s1: LAYOUT__246,
    s2: LAYOUT__248,
    s3_out: LAYOUT__251,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__240: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    rem_low: LAYOUT__77,
    rem_high: LAYOUT__79,
    mul: LAYOUT__241,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 148 },
    },
};
pub const LAYOUT__236: &OpSRLLayout = &OpSRLLayout {
    shift_mul: LAYOUT__237,
    _0: LAYOUT__240,
};
pub const LAYOUT__235: &Div0MulOutputArm0Layout = &Div0MulOutputArm0Layout {
    _super: LAYOUT__236,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__253: &TopBitLayout = &TopBitLayout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 135 },
    },
    rest: LAYOUT__77,
};
pub const LAYOUT__256: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__161,
    b1: LAYOUT__162,
    b2: LAYOUT__164,
    b3: LAYOUT__165,
    b3_top7times2: LAYOUT__166,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 138 },
    },
};
pub const LAYOUT__257: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__167,
    b1: LAYOUT__168,
    b2: LAYOUT__170,
    b3: LAYOUT__172,
    b3_top7times2: LAYOUT__174,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 139 },
    },
};
pub const LAYOUT__258: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__10,
    carry_byte: LAYOUT__245,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
};
pub const LAYOUT__259: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__249,
    carry_byte: LAYOUT__247,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
};
pub const LAYOUT__260: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__251,
    carry_byte: LAYOUT__250,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
};
pub const LAYOUT__255: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__256,
    bx: LAYOUT__257,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 140 },
    },
    c_rest_times2: LAYOUT__83,
    s0: LAYOUT__258,
    s1: LAYOUT__259,
    s2: LAYOUT__260,
    s3_out: LAYOUT__13,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
};
pub const LAYOUT__254: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 136 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 137 },
    },
    rem_low: LAYOUT__79,
    rem_high: LAYOUT__81,
    mul: LAYOUT__255,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 149 },
    },
};
pub const LAYOUT__252: &OpSRALayout = &OpSRALayout {
    shift_mul: LAYOUT__237,
    flip: LAYOUT__253,
    _0: LAYOUT__254,
};
pub const LAYOUT__262: &OpSRLILayout = &OpSRLILayout {
    shift_mul: LAYOUT__237,
    _0: LAYOUT__240,
};
pub const LAYOUT__261: &Div0MulOutputArm2Layout = &Div0MulOutputArm2Layout {
    _super: LAYOUT__262,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 43 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 44 },
        },
    },
};
pub const LAYOUT__263: &OpSRAILayout = &OpSRAILayout {
    shift_mul: LAYOUT__237,
    flip: LAYOUT__253,
    _0: LAYOUT__254,
};
pub const LAYOUT__268: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__161,
    b1: LAYOUT__162,
    b2: LAYOUT__164,
    b3: LAYOUT__165,
    b3_top7times2: LAYOUT__166,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
};
pub const LAYOUT__269: &ExpandU32Layout = &ExpandU32Layout {
    b0: LAYOUT__167,
    b1: LAYOUT__168,
    b2: LAYOUT__170,
    b3: LAYOUT__172,
    b3_top7times2: LAYOUT__174,
    top_bit: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
};
pub const LAYOUT__270: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__81,
    carry_byte: LAYOUT__245,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
};
pub const LAYOUT__271: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__83,
    carry_byte: LAYOUT__247,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
};
pub const LAYOUT__272: &SplitTotalLayout = &SplitTotalLayout {
    out: LAYOUT__10,
    carry_byte: LAYOUT__250,
    carry_extra: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
};
pub const LAYOUT__267: &MultiplyAccumulateLayout = &MultiplyAccumulateLayout {
    ax: LAYOUT__268,
    bx: LAYOUT__269,
    c_sign: &NondetRegLayout {
        _super: &Reg { offset: 131 },
    },
    c_rest_times2: LAYOUT__79,
    s0: LAYOUT__270,
    s1: LAYOUT__271,
    s2: LAYOUT__272,
    s3_out: LAYOUT__249,
    s3_carry: &NondetFakeTwitRegLayout {
        reg0: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        reg1: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__266: &DoDivLayout = &DoDivLayout {
    quot_low: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    quot_high: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
    rem_low: LAYOUT__76,
    rem_high: LAYOUT__77,
    mul: LAYOUT__267,
    top_bit_type: &NondetRegLayout {
        _super: &Reg { offset: 140 },
    },
};
pub const LAYOUT__265: &OpDIVLayout = &OpDIVLayout { _0: LAYOUT__266 };
pub const LAYOUT__264: &Div0MulOutputArm4Layout = &Div0MulOutputArm4Layout {
    _super: LAYOUT__265,
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
pub const LAYOUT__274: &OpDIVULayout = &OpDIVULayout { _0: LAYOUT__266 };
pub const LAYOUT__273: &Div0MulOutputArm5Layout = &Div0MulOutputArm5Layout {
    _super: LAYOUT__274,
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
pub const LAYOUT__276: &OpREMLayout = &OpREMLayout { _0: LAYOUT__266 };
pub const LAYOUT__275: &Div0MulOutputArm6Layout = &Div0MulOutputArm6Layout {
    _super: LAYOUT__276,
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
pub const LAYOUT__278: &OpREMULayout = &OpREMULayout { _0: LAYOUT__266 };
pub const LAYOUT__277: &Div0MulOutputArm7Layout = &Div0MulOutputArm7Layout {
    _super: LAYOUT__278,
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
pub const LAYOUT__234: &Div0MulOutputLayout = &Div0MulOutputLayout {
    arm0: LAYOUT__235,
    arm1: LAYOUT__252,
    arm2: LAYOUT__261,
    arm3: LAYOUT__263,
    arm4: LAYOUT__264,
    arm5: LAYOUT__273,
    arm6: LAYOUT__275,
    arm7: LAYOUT__277,
};
pub const LAYOUT__282: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 154 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 153 },
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
pub const LAYOUT__283: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 158 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 153 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 159 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 160 },
    },
};
pub const LAYOUT__281: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__282,
    new_txn: LAYOUT__283,
};
pub const LAYOUT__285: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
};
pub const LAYOUT__284: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__285 };
pub const LAYOUT__280: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__281,
    _0: LAYOUT__284,
};
pub const LAYOUT__279: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 152 },
    },
    _0: LAYOUT__280,
};
pub const LAYOUT__287: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
};
pub const LAYOUT__288: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
};
pub const LAYOUT__286: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__287,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 165 },
    },
    high16: LAYOUT__288,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 168 },
    },
};
pub const LAYOUT__203: &Div0Layout = &Div0Layout {
    input: LAYOUT__204,
    _arguments_div0_mul_output: LAYOUT__231,
    mul_output: LAYOUT__234,
    _0: LAYOUT__279,
    pc_add: LAYOUT__286,
};
pub const LAYOUT__292: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 33 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 34 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 35 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 38 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
};
pub const LAYOUT__295: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
};
pub const LAYOUT__294: &U16RegLayout = &U16RegLayout { ret: LAYOUT__295 };
pub const LAYOUT__296: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
};
pub const LAYOUT__293: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
    upper_diff: LAYOUT__294,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
    med14: LAYOUT__296,
};
pub const LAYOUT__299: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 58 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 57 },
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
pub const LAYOUT__300: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 62 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 63 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
};
pub const LAYOUT__298: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__299,
    new_txn: LAYOUT__300,
};
pub const LAYOUT__302: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__301: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__302 };
pub const LAYOUT__297: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__298,
    _0: LAYOUT__301,
};
pub const LAYOUT__291: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__292,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
    pc_addr: LAYOUT__293,
    load_inst: LAYOUT__297,
};
pub const LAYOUT__306: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 67 },
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
pub const LAYOUT__307: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
};
pub const LAYOUT__305: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__306,
    new_txn: LAYOUT__307,
};
pub const LAYOUT__309: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
    },
};
pub const LAYOUT__308: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__309 };
pub const LAYOUT__304: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__305,
    _0: LAYOUT__308,
};
pub const LAYOUT__303: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__304,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 77 },
    },
};
pub const LAYOUT__311: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__312: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
    },
};
pub const LAYOUT__310: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__311,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    high16: LAYOUT__312,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
};
pub const LAYOUT__315: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
};
pub const LAYOUT__314: &U16RegLayout = &U16RegLayout { ret: LAYOUT__315 };
pub const LAYOUT__316: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
};
pub const LAYOUT__313: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    upper_diff: LAYOUT__314,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
    med14: LAYOUT__316,
};
pub const LAYOUT__319: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__320: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
};
pub const LAYOUT__318: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__319,
    new_txn: LAYOUT__320,
};
pub const LAYOUT__322: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
};
pub const LAYOUT__321: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__322 };
pub const LAYOUT__317: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__318,
    _0: LAYOUT__321,
};
pub const LAYOUT__290: &MemLoadInputLayout = &MemLoadInputLayout {
    decoded: LAYOUT__291,
    rs1: LAYOUT__303,
    addr_u32: LAYOUT__310,
    addr: LAYOUT__313,
    data_0: LAYOUT__317,
};
pub const LAYOUT__324: &ArgU8Layout3LayoutArray = &[
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
pub const LAYOUT__323: &_Arguments_Mem0OutputLayout = &_Arguments_Mem0OutputLayout {
    arg_u8: LAYOUT__324,
};
pub const LAYOUT__328: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
};
pub const LAYOUT__329: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
};
pub const LAYOUT__327: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__328,
    byte1: LAYOUT__329,
};
pub const LAYOUT__330: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__326: &OpLBLayout = &OpLBLayout {
    bytes: LAYOUT__327,
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    low7x2: LAYOUT__330,
};
pub const LAYOUT__332: &OpLHLayout = &OpLHLayout {
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    low15x2: LAYOUT__328,
};
pub const LAYOUT__331: &Mem0OutputArm1Layout = &Mem0OutputArm1Layout {
    _super: LAYOUT__332,
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
};
pub const LAYOUT__333: &Mem0OutputArm2Layout = &Mem0OutputArm2Layout {
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
pub const LAYOUT__335: &OpLBULayout = &OpLBULayout { bytes: LAYOUT__327 };
pub const LAYOUT__334: &Mem0OutputArm3Layout = &Mem0OutputArm3Layout {
    _super: LAYOUT__335,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__336: &Mem0OutputArm4Layout = &Mem0OutputArm4Layout {
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
pub const LAYOUT__337: &Mem0OutputArm5Layout = &Mem0OutputArm5Layout {
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
pub const LAYOUT__338: &Mem0OutputArm6Layout = &Mem0OutputArm6Layout {
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
pub const LAYOUT__339: &Mem0OutputArm7Layout = &Mem0OutputArm7Layout {
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
pub const LAYOUT__325: &Mem0OutputLayout = &Mem0OutputLayout {
    arm0: LAYOUT__326,
    arm1: LAYOUT__331,
    arm2: LAYOUT__333,
    arm3: LAYOUT__334,
    arm4: LAYOUT__336,
    arm5: LAYOUT__337,
    arm6: LAYOUT__338,
    arm7: LAYOUT__339,
};
pub const LAYOUT__343: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 106 },
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
pub const LAYOUT__344: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
};
pub const LAYOUT__342: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__343,
    new_txn: LAYOUT__344,
};
pub const LAYOUT__346: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
    },
};
pub const LAYOUT__345: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__346 };
pub const LAYOUT__341: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__342,
    _0: LAYOUT__345,
};
pub const LAYOUT__340: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
    _0: LAYOUT__341,
};
pub const LAYOUT__348: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
};
pub const LAYOUT__349: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
};
pub const LAYOUT__347: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__348,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 118 },
    },
    high16: LAYOUT__349,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
};
pub const LAYOUT__289: &Mem0Layout = &Mem0Layout {
    input: LAYOUT__290,
    _arguments_mem0_output: LAYOUT__323,
    output: LAYOUT__325,
    _0: LAYOUT__340,
    pc_add: LAYOUT__347,
};
pub const LAYOUT__353: &DecoderLayout = &DecoderLayout {
    _f7_6: &NondetRegLayout {
        _super: &Reg { offset: 35 },
    },
    _f7_45: &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
    _f7_23: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    _f7_01: &NondetRegLayout {
        _super: &Reg { offset: 38 },
    },
    _rs2_34: &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
    _rs2_12: &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
    _rs2_0: &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    _rs1_34: &NondetRegLayout {
        _super: &Reg { offset: 42 },
    },
    _rs1_12: &NondetRegLayout {
        _super: &Reg { offset: 43 },
    },
    _rs1_0: &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    _f3_2: &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    _f3_01: &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    _rd_34: &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
    _rd_12: &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    _rd_0: &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
    opcode: &NondetRegLayout {
        _super: &Reg { offset: 50 },
    },
};
pub const LAYOUT__356: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
};
pub const LAYOUT__355: &U16RegLayout = &U16RegLayout { ret: LAYOUT__356 };
pub const LAYOUT__357: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
};
pub const LAYOUT__354: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    upper_diff: LAYOUT__355,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
    med14: LAYOUT__357,
};
pub const LAYOUT__360: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 60 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 59 },
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
pub const LAYOUT__361: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 59 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 65 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 66 },
    },
};
pub const LAYOUT__359: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__360,
    new_txn: LAYOUT__361,
};
pub const LAYOUT__363: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__362: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__363 };
pub const LAYOUT__358: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__359,
    _0: LAYOUT__362,
};
pub const LAYOUT__352: &DecodeInstLayout = &DecodeInstLayout {
    _super: LAYOUT__353,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
    pc_addr: LAYOUT__354,
    load_inst: LAYOUT__358,
};
pub const LAYOUT__367: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 69 },
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
pub const LAYOUT__368: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
};
pub const LAYOUT__366: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__367,
    new_txn: LAYOUT__368,
};
pub const LAYOUT__370: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
    },
};
pub const LAYOUT__369: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__370 };
pub const LAYOUT__365: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__366,
    _0: LAYOUT__369,
};
pub const LAYOUT__364: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__365,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
};
pub const LAYOUT__374: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 80 },
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
pub const LAYOUT__375: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
};
pub const LAYOUT__373: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__374,
    new_txn: LAYOUT__375,
};
pub const LAYOUT__377: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__376: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__377 };
pub const LAYOUT__372: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__373,
    _0: LAYOUT__376,
};
pub const LAYOUT__371: &ReadRegLayout = &ReadRegLayout {
    _super: LAYOUT__372,
    addr: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
};
pub const LAYOUT__379: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
};
pub const LAYOUT__380: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
};
pub const LAYOUT__378: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__379,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    high16: LAYOUT__380,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
};
pub const LAYOUT__383: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
};
pub const LAYOUT__382: &U16RegLayout = &U16RegLayout { ret: LAYOUT__383 };
pub const LAYOUT__384: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
};
pub const LAYOUT__381: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    upper_diff: LAYOUT__382,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    med14: LAYOUT__384,
};
pub const LAYOUT__351: &MemStoreInputLayout = &MemStoreInputLayout {
    decoded: LAYOUT__352,
    rs1: LAYOUT__364,
    rs2: LAYOUT__371,
    addr_u32: LAYOUT__378,
    addr: LAYOUT__381,
    data_0: LAYOUT__218,
};
pub const LAYOUT__386: &ArgU8Layout4LayoutArray = &[
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
pub const LAYOUT__385: &_Arguments_Mem1OutputLayout = &_Arguments_Mem1OutputLayout {
    arg_u8: LAYOUT__386,
};
pub const LAYOUT__390: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__389: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__330,
    byte1: LAYOUT__390,
};
pub const LAYOUT__388: &OpSBLayout = &OpSBLayout {
    orig_bytes: LAYOUT__327,
    new_bytes: LAYOUT__389,
};
pub const LAYOUT__391: &Mem1OutputArm1Layout = &Mem1OutputArm1Layout {
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
pub const LAYOUT__392: &Mem1OutputArm2Layout = &Mem1OutputArm2Layout {
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
pub const LAYOUT__393: &Mem1OutputArm3Layout = &Mem1OutputArm3Layout {
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
pub const LAYOUT__394: &Mem1OutputArm4Layout = &Mem1OutputArm4Layout {
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
pub const LAYOUT__395: &Mem1OutputArm5Layout = &Mem1OutputArm5Layout {
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
pub const LAYOUT__396: &Mem1OutputArm6Layout = &Mem1OutputArm6Layout {
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
pub const LAYOUT__397: &Mem1OutputArm7Layout = &Mem1OutputArm7Layout {
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
pub const LAYOUT__387: &Mem1OutputLayout = &Mem1OutputLayout {
    arm0: LAYOUT__388,
    arm1: LAYOUT__391,
    arm2: LAYOUT__392,
    arm3: LAYOUT__393,
    arm4: LAYOUT__394,
    arm5: LAYOUT__395,
    arm6: LAYOUT__396,
    arm7: LAYOUT__397,
};
pub const LAYOUT__401: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__402: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 122 },
    },
};
pub const LAYOUT__400: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__401,
    new_txn: LAYOUT__402,
};
pub const LAYOUT__404: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__403: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__404 };
pub const LAYOUT__399: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__400,
    _0: LAYOUT__403,
};
pub const LAYOUT__398: &MemStoreFinalizeLayout = &MemStoreFinalizeLayout { _0: LAYOUT__399 };
pub const LAYOUT__406: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
};
pub const LAYOUT__407: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
};
pub const LAYOUT__405: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__406,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    high16: LAYOUT__407,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
};
pub const LAYOUT__350: &Mem1Layout = &Mem1Layout {
    input: LAYOUT__351,
    _arguments_mem1_output: LAYOUT__385,
    output: LAYOUT__387,
    _0: LAYOUT__398,
    pc_add: LAYOUT__405,
};
pub const LAYOUT__416: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__417: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 32 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 28 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 33 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 34 },
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
        _super: &Reg { offset: 35 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 37 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 38 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 39 },
    },
};
pub const LAYOUT__422: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 40 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 36 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 41 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 42 },
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
        _super: &Reg { offset: 43 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 45 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 46 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 47 },
    },
};
pub const LAYOUT__427: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 48 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 44 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 49 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 50 },
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
pub const LAYOUT__432: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 56 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 57 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 58 },
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
        _super: &Reg { offset: 59 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 60 },
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
pub const LAYOUT__437: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 64 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 60 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 65 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 66 },
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
pub const LAYOUT__442: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 68 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 74 },
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
pub const LAYOUT__447: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 76 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 82 },
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
pub const LAYOUT__452: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 84 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
};
pub const LAYOUT__450: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__451,
    new_txn: LAYOUT__452,
};
pub const LAYOUT__449: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__450 };
pub const LAYOUT__448: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__449 };
pub const LAYOUT__412: &ControlLoadRoot__0_SuperLayout8LayoutArray = &[
    LAYOUT__413,
    LAYOUT__418,
    LAYOUT__423,
    LAYOUT__428,
    LAYOUT__433,
    LAYOUT__438,
    LAYOUT__443,
    LAYOUT__448,
];
pub const LAYOUT__411: &ControlLoadRootLayout = &ControlLoadRootLayout { _1: LAYOUT__412 };
pub const LAYOUT__410: &Control0_SuperArm0Layout = &Control0_SuperArm0Layout {
    _super: LAYOUT__411,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    _extra1: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    _extra2: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
    _extra3: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra6: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra7: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
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
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra28: &ArgU8Layout {
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
};
pub const LAYOUT__460: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
};
pub const LAYOUT__459: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__460 };
pub const LAYOUT__458: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__415,
    _0: LAYOUT__459,
};
pub const LAYOUT__463: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
};
pub const LAYOUT__462: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__463 };
pub const LAYOUT__461: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__420,
    _0: LAYOUT__462,
};
pub const LAYOUT__457: &ControlResume_SuperArm0_SuperLayout =
    &ControlResume_SuperArm0_SuperLayout {
        pc: LAYOUT__458,
        mode: LAYOUT__461,
    };
pub const LAYOUT__456: &ControlResume_SuperArm0Layout = &ControlResume_SuperArm0Layout {
    _super: LAYOUT__457,
    _extra0: LAYOUT__426,
    _extra1: LAYOUT__427,
    _extra2: LAYOUT__431,
    _extra3: LAYOUT__432,
    _extra4: LAYOUT__436,
    _extra5: LAYOUT__437,
    _extra6: LAYOUT__441,
    _extra7: LAYOUT__442,
    _extra8: LAYOUT__446,
    _extra9: LAYOUT__447,
    _extra10: LAYOUT__451,
    _extra11: LAYOUT__452,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
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
};
pub const LAYOUT__467: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__415,
    _0: LAYOUT__459,
};
pub const LAYOUT__466: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__467 };
pub const LAYOUT__469: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__420,
    _0: LAYOUT__462,
};
pub const LAYOUT__468: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__469 };
pub const LAYOUT__473: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
};
pub const LAYOUT__472: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__473 };
pub const LAYOUT__471: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__425,
    _0: LAYOUT__472,
};
pub const LAYOUT__470: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__471 };
pub const LAYOUT__475: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__430,
    _0: LAYOUT__131,
};
pub const LAYOUT__474: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__475 };
pub const LAYOUT__479: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
};
pub const LAYOUT__478: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__479 };
pub const LAYOUT__477: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__435,
    _0: LAYOUT__478,
};
pub const LAYOUT__476: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__477 };
pub const LAYOUT__483: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
};
pub const LAYOUT__482: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__483 };
pub const LAYOUT__481: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__440,
    _0: LAYOUT__482,
};
pub const LAYOUT__480: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__481 };
pub const LAYOUT__485: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__445,
    _0: LAYOUT__215,
};
pub const LAYOUT__484: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__485 };
pub const LAYOUT__489: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
};
pub const LAYOUT__488: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__489 };
pub const LAYOUT__487: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__450,
    _0: LAYOUT__488,
};
pub const LAYOUT__486: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__487 };
pub const LAYOUT__465: &ControlResume_SuperArm1_Super__0_SuperLayout8LayoutArray = &[
    LAYOUT__466,
    LAYOUT__468,
    LAYOUT__470,
    LAYOUT__474,
    LAYOUT__476,
    LAYOUT__480,
    LAYOUT__484,
    LAYOUT__486,
];
pub const LAYOUT__464: &ControlResume_SuperArm1_SuperLayout =
    &ControlResume_SuperArm1_SuperLayout { _1: LAYOUT__465 };
pub const LAYOUT__455: &ControlResume_SuperLayout = &ControlResume_SuperLayout {
    arm0: LAYOUT__456,
    arm1: LAYOUT__464,
};
pub const LAYOUT__491: &MemoryArgLayout16LayoutArray = &[
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
    LAYOUT__446,
    LAYOUT__447,
    LAYOUT__451,
    LAYOUT__452,
];
pub const LAYOUT__492: &CycleArgLayout8LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
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
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
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
];
pub const LAYOUT__490: &_Arguments_ControlResume_SuperLayout =
    &_Arguments_ControlResume_SuperLayout {
        memory_arg: LAYOUT__491,
        cycle_arg: LAYOUT__492,
    };
pub const LAYOUT__454: &ControlResumeLayout = &ControlResumeLayout {
    _super: LAYOUT__455,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _arguments_control_resume__super: LAYOUT__490,
};
pub const LAYOUT__453: &Control0_SuperArm1Layout = &Control0_SuperArm1Layout {
    _super: LAYOUT__454,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
};
pub const LAYOUT__497: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
};
pub const LAYOUT__496: &U16RegLayout = &U16RegLayout { ret: LAYOUT__497 };
pub const LAYOUT__498: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
};
pub const LAYOUT__495: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 172 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 173 },
    },
    upper_diff: LAYOUT__496,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    med14: LAYOUT__498,
};
pub const LAYOUT__500: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__499: &U16RegLayout = &U16RegLayout { ret: LAYOUT__500 };
pub const LAYOUT__501: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__425,
    _0: LAYOUT__472,
};
pub const LAYOUT__494: &ControlUserECALLLayout = &ControlUserECALLLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
    pc_addr: LAYOUT__495,
    load_inst: LAYOUT__458,
    dispatch_idx: LAYOUT__461,
    _0: LAYOUT__499,
    new_pc_addr: LAYOUT__501,
    _1: LAYOUT__475,
};
pub const LAYOUT__493: &Control0_SuperArm2Layout = &Control0_SuperArm2Layout {
    _super: LAYOUT__494,
    _extra0: LAYOUT__436,
    _extra1: LAYOUT__437,
    _extra2: LAYOUT__441,
    _extra3: LAYOUT__442,
    _extra4: LAYOUT__446,
    _extra5: LAYOUT__447,
    _extra6: LAYOUT__451,
    _extra7: LAYOUT__452,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
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
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra29: &ArgU8Layout {
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
};
pub const LAYOUT__505: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
};
pub const LAYOUT__504: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__500,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
    high16: LAYOUT__505,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 177 },
    },
};
pub const LAYOUT__503: &ControlMRETLayout = &ControlMRETLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
    pc_addr: LAYOUT__495,
    load_inst: LAYOUT__458,
    pc: LAYOUT__461,
    pc_add: LAYOUT__504,
};
pub const LAYOUT__502: &Control0_SuperArm3Layout = &Control0_SuperArm3Layout {
    _super: LAYOUT__503,
    _extra0: LAYOUT__426,
    _extra1: LAYOUT__427,
    _extra2: LAYOUT__431,
    _extra3: LAYOUT__432,
    _extra4: LAYOUT__436,
    _extra5: LAYOUT__437,
    _extra6: LAYOUT__441,
    _extra7: LAYOUT__442,
    _extra8: LAYOUT__446,
    _extra9: LAYOUT__447,
    _extra10: LAYOUT__451,
    _extra11: LAYOUT__452,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
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
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra32: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra33: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra34: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra35: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra36: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra37: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra38: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra39: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra42: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra43: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra44: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra45: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
};
pub const LAYOUT__511: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__430,
    _0: LAYOUT__131,
};
pub const LAYOUT__512: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__435,
    _0: LAYOUT__478,
};
pub const LAYOUT__513: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__440,
    _0: LAYOUT__482,
};
pub const LAYOUT__514: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__445,
    _0: LAYOUT__215,
};
pub const LAYOUT__515: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__450,
    _0: LAYOUT__488,
};
pub const LAYOUT__510: &MemoryReadLayout8LayoutArray = &[
    LAYOUT__458,
    LAYOUT__461,
    LAYOUT__501,
    LAYOUT__511,
    LAYOUT__512,
    LAYOUT__513,
    LAYOUT__514,
    LAYOUT__515,
];
pub const LAYOUT__509: &ControlSuspend_SuperArm0_SuperLayout =
    &ControlSuspend_SuperArm0_SuperLayout { _1: LAYOUT__510 };
pub const LAYOUT__517: &ControlSuspend_SuperArm1_SuperLayout =
    &ControlSuspend_SuperArm1_SuperLayout {
        state: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        _0: LAYOUT__467,
        _1: LAYOUT__469,
    };
pub const LAYOUT__516: &ControlSuspend_SuperArm1Layout = &ControlSuspend_SuperArm1Layout {
    _super: LAYOUT__517,
    _extra0: LAYOUT__426,
    _extra1: LAYOUT__427,
    _extra2: LAYOUT__431,
    _extra3: LAYOUT__432,
    _extra4: LAYOUT__436,
    _extra5: LAYOUT__437,
    _extra6: LAYOUT__441,
    _extra7: LAYOUT__442,
    _extra8: LAYOUT__446,
    _extra9: LAYOUT__447,
    _extra10: LAYOUT__451,
    _extra11: LAYOUT__452,
    _extra12: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
    _extra13: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
    _extra14: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
    _extra15: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
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
};
pub const LAYOUT__508: &ControlSuspend_SuperLayout = &ControlSuspend_SuperLayout {
    arm0: LAYOUT__509,
    arm1: LAYOUT__516,
};
pub const LAYOUT__518: &_Arguments_ControlSuspend_SuperLayout =
    &_Arguments_ControlSuspend_SuperLayout {
        memory_arg: LAYOUT__491,
        cycle_arg: LAYOUT__492,
    };
pub const LAYOUT__507: &ControlSuspendLayout = &ControlSuspendLayout {
    _super: LAYOUT__508,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _arguments_control_suspend__super: LAYOUT__518,
};
pub const LAYOUT__506: &Control0_SuperArm4Layout = &Control0_SuperArm4Layout {
    _super: LAYOUT__507,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
};
pub const LAYOUT__522: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__415,
    _0: LAYOUT__459,
};
pub const LAYOUT__523: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__420,
    _0: LAYOUT__462,
};
pub const LAYOUT__524: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__425,
    _0: LAYOUT__472,
};
pub const LAYOUT__525: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__430,
    _0: LAYOUT__131,
};
pub const LAYOUT__526: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__435,
    _0: LAYOUT__478,
};
pub const LAYOUT__527: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__440,
    _0: LAYOUT__482,
};
pub const LAYOUT__528: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__445,
    _0: LAYOUT__215,
};
pub const LAYOUT__529: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__450,
    _0: LAYOUT__488,
};
pub const LAYOUT__521: &MemoryPageOutLayout8LayoutArray = &[
    LAYOUT__522,
    LAYOUT__523,
    LAYOUT__524,
    LAYOUT__525,
    LAYOUT__526,
    LAYOUT__527,
    LAYOUT__528,
    LAYOUT__529,
];
pub const LAYOUT__520: &ControlStoreRootLayout = &ControlStoreRootLayout { _1: LAYOUT__521 };
pub const LAYOUT__519: &Control0_SuperArm5Layout = &Control0_SuperArm5Layout {
    _super: LAYOUT__520,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra18: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra19: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra20: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra21: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra22: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra23: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra24: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra25: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra26: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra27: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra30: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra31: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
};
pub const LAYOUT__536: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 107 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 108 },
            },
        },
    };
pub const LAYOUT__537: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 109 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 110 },
            },
        },
    };
pub const LAYOUT__538: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 111 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 112 },
            },
        },
    };
pub const LAYOUT__539: &ControlTable_SuperArm0_Super__0_SuperLayout =
    &ControlTable_SuperArm0_Super__0_SuperLayout {
        arg: &ArgU16Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 113 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 114 },
            },
        },
    };
pub const LAYOUT__540: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__541: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__542: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__543: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__544: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__545: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__546: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__547: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__548: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__549: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__550: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__551: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__535: &ControlTable_SuperArm0_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__536,
    LAYOUT__537,
    LAYOUT__538,
    LAYOUT__539,
    LAYOUT__540,
    LAYOUT__541,
    LAYOUT__542,
    LAYOUT__543,
    LAYOUT__544,
    LAYOUT__545,
    LAYOUT__546,
    LAYOUT__547,
    LAYOUT__548,
    LAYOUT__549,
    LAYOUT__550,
    LAYOUT__551,
];
pub const LAYOUT__534: &ControlTable_SuperArm0_SuperLayout = &ControlTable_SuperArm0_SuperLayout {
    _1: LAYOUT__535,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
};
pub const LAYOUT__533: &ControlTable_SuperArm0Layout = &ControlTable_SuperArm0Layout {
    _super: LAYOUT__534,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra2: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra3: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra4: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra5: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra6: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra7: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra8: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra9: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra10: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra11: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra12: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra13: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra14: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra15: &ArgU8Layout {
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
                _super: &Reg { offset: 139 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 140 },
            },
        },
    };
pub const LAYOUT__556: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 141 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 142 },
            },
        },
    };
pub const LAYOUT__557: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 143 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 144 },
            },
        },
    };
pub const LAYOUT__558: &ControlTable_SuperArm1_Super__0_SuperLayout =
    &ControlTable_SuperArm1_Super__0_SuperLayout {
        arg: &ArgU8Layout {
            count: &NondetRegLayout {
                _super: &Reg { offset: 145 },
            },
            val: &NondetRegLayout {
                _super: &Reg { offset: 146 },
            },
        },
    };
pub const LAYOUT__559: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__560: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__561: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__562: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__563: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__564: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__565: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__566: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__567: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__568: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__569: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__570: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__554: &ControlTable_SuperArm1_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__555,
    LAYOUT__556,
    LAYOUT__557,
    LAYOUT__558,
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
];
pub const LAYOUT__553: &ControlTable_SuperArm1_SuperLayout = &ControlTable_SuperArm1_SuperLayout {
    _1: LAYOUT__554,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
};
pub const LAYOUT__552: &ControlTable_SuperArm1Layout = &ControlTable_SuperArm1Layout {
    _super: LAYOUT__553,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
};
pub const LAYOUT__532: &ControlTable_SuperLayout = &ControlTable_SuperLayout {
    arm0: LAYOUT__533,
    arm1: LAYOUT__552,
};
pub const LAYOUT__572: &ArgU16Layout16LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
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
];
pub const LAYOUT__573: &ArgU8Layout16LayoutArray = &[
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
];
pub const LAYOUT__571: &_Arguments_ControlTable_SuperLayout =
    &_Arguments_ControlTable_SuperLayout {
        arg_u16: LAYOUT__572,
        arg_u8: LAYOUT__573,
    };
pub const LAYOUT__531: &ControlTableLayout = &ControlTableLayout {
    _super: LAYOUT__532,
    entry: &NondetRegLayout {
        _super: &Reg { offset: 173 },
    },
    mode: &NondetRegLayout {
        _super: &Reg { offset: 174 },
    },
    _arguments_control_table__super: LAYOUT__571,
};
pub const LAYOUT__530: &Control0_SuperArm6Layout = &Control0_SuperArm6Layout {
    _super: LAYOUT__531,
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
    _extra12: LAYOUT__446,
    _extra13: LAYOUT__447,
    _extra14: LAYOUT__451,
    _extra15: LAYOUT__452,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
};
pub const LAYOUT__574: &Control0_SuperArm7Layout = &Control0_SuperArm7Layout {
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
    _extra12: LAYOUT__446,
    _extra13: LAYOUT__447,
    _extra14: LAYOUT__451,
    _extra15: LAYOUT__452,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 115 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 120 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 127 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
    },
    _extra38: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
    },
    _extra39: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
    },
    _extra40: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
    },
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
    },
    _extra42: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
    },
    _extra43: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
    },
    _extra44: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
    },
    _extra45: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
    },
    _extra46: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
    },
    _extra47: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
    },
    _extra48: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
    },
    _extra49: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
    },
    _extra50: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
    },
    _extra51: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
    },
    _extra52: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
    },
    _extra53: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
    },
    _extra54: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
    },
    _extra55: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
    },
};
pub const LAYOUT__409: &Control0_SuperLayout = &Control0_SuperLayout {
    arm0: LAYOUT__410,
    arm1: LAYOUT__453,
    arm2: LAYOUT__493,
    arm3: LAYOUT__502,
    arm4: LAYOUT__506,
    arm5: LAYOUT__519,
    arm6: LAYOUT__530,
    arm7: LAYOUT__574,
};
pub const LAYOUT__575: &_Arguments_Control0_SuperLayout = &_Arguments_Control0_SuperLayout {
    memory_arg: LAYOUT__491,
    cycle_arg: LAYOUT__492,
    arg_u16: LAYOUT__572,
    arg_u8: LAYOUT__573,
};
pub const LAYOUT__408: &Control0Layout = &Control0Layout {
    _super: LAYOUT__409,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
    _arguments_control0__super: LAYOUT__575,
};
pub const LAYOUT__579: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
};
pub const LAYOUT__578: &U16RegLayout = &U16RegLayout { ret: LAYOUT__579 };
pub const LAYOUT__577: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    upper_diff: LAYOUT__578,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
    med14: LAYOUT__27,
};
pub const LAYOUT__581: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__416,
    LAYOUT__417,
    LAYOUT__421,
    LAYOUT__422,
    LAYOUT__426,
    LAYOUT__427,
    LAYOUT__431,
    LAYOUT__432,
];
pub const LAYOUT__582: &CycleArgLayout4LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
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
];
pub const LAYOUT__583: &ArgU16Layout2LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
];
pub const LAYOUT__580: &_Arguments_ECall0OutputLayout = &_Arguments_ECall0OutputLayout {
    memory_arg: LAYOUT__581,
    cycle_arg: LAYOUT__582,
    arg_u16: LAYOUT__583,
};
pub const LAYOUT__589: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__588: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__589 };
pub const LAYOUT__587: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__415,
    _0: LAYOUT__588,
};
pub const LAYOUT__592: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
};
pub const LAYOUT__591: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__592 };
pub const LAYOUT__590: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__420,
    _0: LAYOUT__591,
};
pub const LAYOUT__594: &NondetRegLayout4LayoutArray = &[
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
];
pub const LAYOUT__593: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__594,
};
pub const LAYOUT__586: &MachineECallLayout = &MachineECallLayout {
    load_inst: LAYOUT__587,
    dispatch_idx: LAYOUT__590,
    dispatch: LAYOUT__593,
};
pub const LAYOUT__585: &ECall0OutputArm0Layout = &ECall0OutputArm0Layout {
    _super: LAYOUT__586,
    _extra0: LAYOUT__426,
    _extra1: LAYOUT__427,
    _extra2: LAYOUT__431,
    _extra3: LAYOUT__432,
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__596: &ECallTerminateLayout = &ECallTerminateLayout {
    a0: LAYOUT__587,
    a1: LAYOUT__590,
};
pub const LAYOUT__595: &ECall0OutputArm1Layout = &ECall0OutputArm1Layout {
    _super: LAYOUT__596,
    _extra0: LAYOUT__426,
    _extra1: LAYOUT__427,
    _extra2: LAYOUT__431,
    _extra3: LAYOUT__432,
    _extra4: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    _extra5: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__600: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
};
pub const LAYOUT__599: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__600 };
pub const LAYOUT__598: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__425,
    _0: LAYOUT__599,
};
pub const LAYOUT__601: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__603: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__602: &U16RegLayout = &U16RegLayout { ret: LAYOUT__603 };
pub const LAYOUT__604: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__430,
    _0: LAYOUT__301,
};
pub const LAYOUT__607: &NondetRegLayout4LayoutArray = &[
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
];
pub const LAYOUT__606: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__607,
};
pub const LAYOUT__605: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    low2: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    low2_hot: LAYOUT__606,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 90 },
    },
};
pub const LAYOUT__610: &NondetRegLayout4LayoutArray = &[
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
];
pub const LAYOUT__609: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__610,
};
pub const LAYOUT__608: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    low2: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    low2_hot: LAYOUT__609,
    high_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
    },
    is_zero: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
};
pub const LAYOUT__597: &ECallHostReadSetupLayout = &ECallHostReadSetupLayout {
    fd: LAYOUT__587,
    ptr: LAYOUT__590,
    len: LAYOUT__598,
    new_len: LAYOUT__601,
    diff: LAYOUT__602,
    _0: LAYOUT__604,
    ptr_decomp: LAYOUT__605,
    len_decomp: LAYOUT__608,
    len123: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    uneven: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
};
pub const LAYOUT__611: &ECallHostWriteLayout = &ECallHostWriteLayout {
    fd: LAYOUT__587,
    ptr: LAYOUT__590,
    len: LAYOUT__598,
    new_len: LAYOUT__601,
    diff: LAYOUT__602,
    _0: LAYOUT__604,
};
pub const LAYOUT__612: &ECall0OutputArm4Layout = &ECall0OutputArm4Layout {
    _extra0: LAYOUT__416,
    _extra1: LAYOUT__417,
    _extra2: LAYOUT__421,
    _extra3: LAYOUT__422,
    _extra4: LAYOUT__426,
    _extra5: LAYOUT__427,
    _extra6: LAYOUT__431,
    _extra7: LAYOUT__432,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__617: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__415,
    _0: LAYOUT__588,
};
pub const LAYOUT__616: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    _0: LAYOUT__617,
};
pub const LAYOUT__619: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__420,
    _0: LAYOUT__591,
};
pub const LAYOUT__618: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    _0: LAYOUT__619,
};
pub const LAYOUT__621: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__425,
    _0: LAYOUT__599,
};
pub const LAYOUT__620: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    _0: LAYOUT__621,
};
pub const LAYOUT__623: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__430,
    _0: LAYOUT__301,
};
pub const LAYOUT__622: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    _0: LAYOUT__623,
};
pub const LAYOUT__615: &ECallHostReadWords__0_SuperLayout4LayoutArray =
    &[LAYOUT__616, LAYOUT__618, LAYOUT__620, LAYOUT__622];
pub const LAYOUT__614: &ECallHostReadWordsLayout = &ECallHostReadWordsLayout {
    len_decomp: LAYOUT__605,
    words_decomp: LAYOUT__608,
    _1: LAYOUT__615,
    len_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
};
pub const LAYOUT__613: &ECall0OutputArm5Layout = &ECall0OutputArm5Layout {
    _super: LAYOUT__614,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__624: &ECall0OutputArm6Layout = &ECall0OutputArm6Layout {
    _extra0: LAYOUT__416,
    _extra1: LAYOUT__417,
    _extra2: LAYOUT__421,
    _extra3: LAYOUT__422,
    _extra4: LAYOUT__426,
    _extra5: LAYOUT__427,
    _extra6: LAYOUT__431,
    _extra7: LAYOUT__432,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__625: &ECall0OutputArm7Layout = &ECall0OutputArm7Layout {
    _extra0: LAYOUT__416,
    _extra1: LAYOUT__417,
    _extra2: LAYOUT__421,
    _extra3: LAYOUT__422,
    _extra4: LAYOUT__426,
    _extra5: LAYOUT__427,
    _extra6: LAYOUT__431,
    _extra7: LAYOUT__432,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__584: &ECall0OutputLayout = &ECall0OutputLayout {
    arm0: LAYOUT__585,
    arm1: LAYOUT__595,
    arm2: LAYOUT__597,
    arm3: LAYOUT__611,
    arm4: LAYOUT__612,
    arm5: LAYOUT__613,
    arm6: LAYOUT__624,
    arm7: LAYOUT__625,
};
pub const LAYOUT__627: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__626: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__627,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    high16: LAYOUT__505,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
};
pub const LAYOUT__576: &ECall0Layout = &ECall0Layout {
    s0: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    s1: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    s2: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    pc_addr: LAYOUT__577,
    _arguments_e_call0_output: LAYOUT__580,
    output: LAYOUT__584,
    is_decode: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
    is_p2_entry: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
    },
    add_pc: LAYOUT__626,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
};
pub const LAYOUT__630: &NondetRegLayout24LayoutArray = &[
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
pub const LAYOUT__629: &PoseidonStateLayout = &PoseidonStateLayout {
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
    inner: LAYOUT__630,
    zcheck: &NondetExtRegLayout {
        _super: &Reg { offset: 62 },
    },
};
pub const LAYOUT__633: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__634: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 67 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
};
pub const LAYOUT__635: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__636: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 79 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 80 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 81 },
    },
};
pub const LAYOUT__637: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__638: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 88 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 89 },
    },
};
pub const LAYOUT__639: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__640: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 95 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
};
pub const LAYOUT__641: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 99 },
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
pub const LAYOUT__642: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 105 },
    },
};
pub const LAYOUT__643: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 106 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 107 },
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
pub const LAYOUT__644: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 111 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
};
pub const LAYOUT__645: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__646: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 119 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 121 },
    },
};
pub const LAYOUT__647: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__648: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 128 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 129 },
    },
};
pub const LAYOUT__632: &MemoryArgLayout16LayoutArray = &[
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
    LAYOUT__645,
    LAYOUT__646,
    LAYOUT__647,
    LAYOUT__648,
];
pub const LAYOUT__649: &CycleArgLayout8LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
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
pub const LAYOUT__650: &ArgU16Layout16LayoutArray = &[
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
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
];
pub const LAYOUT__651: &ArgU8Layout2LayoutArray = &[
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
];
pub const LAYOUT__631: &_Arguments_Poseidon0StateLayout = &_Arguments_Poseidon0StateLayout {
    memory_arg: LAYOUT__632,
    cycle_arg: LAYOUT__649,
    arg_u16: LAYOUT__650,
    arg_u8: LAYOUT__651,
};
pub const LAYOUT__656: &PoseidonEntry_SuperArm0Layout = &PoseidonEntry_SuperArm0Layout {
    _super: LAYOUT__629,
    _extra0: LAYOUT__633,
    _extra1: LAYOUT__634,
    _extra2: LAYOUT__635,
    _extra3: LAYOUT__636,
    _extra4: LAYOUT__637,
    _extra5: LAYOUT__638,
    _extra6: LAYOUT__639,
    _extra7: LAYOUT__640,
    _extra8: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra9: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra10: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra11: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
};
pub const LAYOUT__660: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__633,
    new_txn: LAYOUT__634,
};
pub const LAYOUT__662: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
};
pub const LAYOUT__661: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__662 };
pub const LAYOUT__659: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__660,
    _0: LAYOUT__661,
};
pub const LAYOUT__658: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__659,
};
pub const LAYOUT__665: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__635,
    new_txn: LAYOUT__636,
};
pub const LAYOUT__667: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
};
pub const LAYOUT__666: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__667 };
pub const LAYOUT__664: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__665,
    _0: LAYOUT__666,
};
pub const LAYOUT__663: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__664,
};
pub const LAYOUT__670: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__637,
    new_txn: LAYOUT__638,
};
pub const LAYOUT__672: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
};
pub const LAYOUT__671: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__672 };
pub const LAYOUT__669: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__670,
    _0: LAYOUT__671,
};
pub const LAYOUT__668: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__669,
};
pub const LAYOUT__674: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__639,
    new_txn: LAYOUT__640,
};
pub const LAYOUT__676: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
};
pub const LAYOUT__675: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__676 };
pub const LAYOUT__673: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__674,
    _0: LAYOUT__675,
};
pub const LAYOUT__657: &PoseidonEcallLayout = &PoseidonEcallLayout {
    _super: LAYOUT__629,
    state_addr: LAYOUT__658,
    buf_in_addr: LAYOUT__663,
    buf_out_addr: LAYOUT__668,
    bits_and_count: LAYOUT__673,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    is_elem: &NondetRegLayout {
        _super: &Reg { offset: 184 },
    },
    check_out: &NondetRegLayout {
        _super: &Reg { offset: 185 },
    },
    count_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    },
};
pub const LAYOUT__655: &PoseidonEntry_SuperLayout = &PoseidonEntry_SuperLayout {
    _super: LAYOUT__629,
    arm0: LAYOUT__656,
    arm1: LAYOUT__657,
};
pub const LAYOUT__678: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__633,
    LAYOUT__634,
    LAYOUT__635,
    LAYOUT__636,
    LAYOUT__637,
    LAYOUT__638,
    LAYOUT__639,
    LAYOUT__640,
];
pub const LAYOUT__679: &CycleArgLayout4LayoutArray = &[
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
];
pub const LAYOUT__677: &_Arguments_PoseidonEntry_SuperLayout =
    &_Arguments_PoseidonEntry_SuperLayout {
        memory_arg: LAYOUT__678,
        cycle_arg: LAYOUT__679,
    };
pub const LAYOUT__654: &PoseidonEntryLayout = &PoseidonEntryLayout {
    _super: LAYOUT__655,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
    _arguments_poseidon_entry__super: LAYOUT__677,
};
pub const LAYOUT__653: &Poseidon0StateArm0Layout = &Poseidon0StateArm0Layout {
    _super: LAYOUT__654,
    _extra0: LAYOUT__641,
    _extra1: LAYOUT__642,
    _extra2: LAYOUT__643,
    _extra3: LAYOUT__644,
    _extra4: LAYOUT__645,
    _extra5: LAYOUT__646,
    _extra6: LAYOUT__647,
    _extra7: LAYOUT__648,
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
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra14: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra15: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra16: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra17: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra18: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra19: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra20: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra21: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra22: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra23: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
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
            _super: &Reg { offset: 177 },
        },
    },
    _extra28: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra29: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__683: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__659,
};
pub const LAYOUT__684: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__664,
};
pub const LAYOUT__685: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__669,
};
pub const LAYOUT__686: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__673,
};
pub const LAYOUT__689: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__641,
    new_txn: LAYOUT__642,
};
pub const LAYOUT__691: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__690: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__691 };
pub const LAYOUT__688: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__689,
    _0: LAYOUT__690,
};
pub const LAYOUT__687: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__688,
};
pub const LAYOUT__694: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__643,
    new_txn: LAYOUT__644,
};
pub const LAYOUT__696: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__695: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__696 };
pub const LAYOUT__693: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__694,
    _0: LAYOUT__695,
};
pub const LAYOUT__692: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__693,
};
pub const LAYOUT__699: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__645,
    new_txn: LAYOUT__646,
};
pub const LAYOUT__701: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__700: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__701 };
pub const LAYOUT__698: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__699,
    _0: LAYOUT__700,
};
pub const LAYOUT__697: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__698,
};
pub const LAYOUT__704: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__647,
    new_txn: LAYOUT__648,
};
pub const LAYOUT__706: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__705: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__706 };
pub const LAYOUT__703: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__704,
    _0: LAYOUT__705,
};
pub const LAYOUT__702: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__703,
};
pub const LAYOUT__682: &ReadElemLayout8LayoutArray = &[
    LAYOUT__683,
    LAYOUT__684,
    LAYOUT__685,
    LAYOUT__686,
    LAYOUT__687,
    LAYOUT__692,
    LAYOUT__697,
    LAYOUT__702,
];
pub const LAYOUT__681: &PoseidonLoadStateLayout = &PoseidonLoadStateLayout {
    _super: LAYOUT__629,
    load_list: LAYOUT__682,
};
pub const LAYOUT__680: &Poseidon0StateArm1Layout = &Poseidon0StateArm1Layout {
    _super: LAYOUT__681,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
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
            _super: &Reg { offset: 177 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__711: &OneHot_3_Layout = &OneHot_3_Layout {
    _super: &[
        &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 184 },
        },
    ],
};
pub const LAYOUT__716: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__660 };
pub const LAYOUT__715: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__716,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
};
pub const LAYOUT__717: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__660,
    _0: LAYOUT__661,
};
pub const LAYOUT__714: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__659,
    arm1: LAYOUT__715,
    arm2: LAYOUT__717,
};
pub const LAYOUT__719: &MemoryArgLayout2LayoutArray = &[LAYOUT__633, LAYOUT__634];
pub const LAYOUT__718: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__719,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    }],
};
pub const LAYOUT__713: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__714,
    _arguments_memory_get__super: LAYOUT__718,
};
pub const LAYOUT__723: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__665 };
pub const LAYOUT__722: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__723,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
};
pub const LAYOUT__724: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__665,
    _0: LAYOUT__666,
};
pub const LAYOUT__721: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__664,
    arm1: LAYOUT__722,
    arm2: LAYOUT__724,
};
pub const LAYOUT__726: &MemoryArgLayout2LayoutArray = &[LAYOUT__635, LAYOUT__636];
pub const LAYOUT__725: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__726,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    }],
};
pub const LAYOUT__720: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__721,
    _arguments_memory_get__super: LAYOUT__725,
};
pub const LAYOUT__730: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__670 };
pub const LAYOUT__729: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__730,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
};
pub const LAYOUT__731: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__670,
    _0: LAYOUT__671,
};
pub const LAYOUT__728: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__669,
    arm1: LAYOUT__729,
    arm2: LAYOUT__731,
};
pub const LAYOUT__733: &MemoryArgLayout2LayoutArray = &[LAYOUT__637, LAYOUT__638];
pub const LAYOUT__732: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__733,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    }],
};
pub const LAYOUT__727: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__728,
    _arguments_memory_get__super: LAYOUT__732,
};
pub const LAYOUT__737: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__674 };
pub const LAYOUT__736: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__737,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
};
pub const LAYOUT__738: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__674,
    _0: LAYOUT__675,
};
pub const LAYOUT__735: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__673,
    arm1: LAYOUT__736,
    arm2: LAYOUT__738,
};
pub const LAYOUT__740: &MemoryArgLayout2LayoutArray = &[LAYOUT__639, LAYOUT__640];
pub const LAYOUT__739: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__740,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    }],
};
pub const LAYOUT__734: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__735,
    _arguments_memory_get__super: LAYOUT__739,
};
pub const LAYOUT__744: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__689 };
pub const LAYOUT__743: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__744,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__745: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__689,
    _0: LAYOUT__690,
};
pub const LAYOUT__742: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__688,
    arm1: LAYOUT__743,
    arm2: LAYOUT__745,
};
pub const LAYOUT__747: &MemoryArgLayout2LayoutArray = &[LAYOUT__641, LAYOUT__642];
pub const LAYOUT__746: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__747,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    }],
};
pub const LAYOUT__741: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__742,
    _arguments_memory_get__super: LAYOUT__746,
};
pub const LAYOUT__751: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__694 };
pub const LAYOUT__750: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__751,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__752: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__694,
    _0: LAYOUT__695,
};
pub const LAYOUT__749: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__693,
    arm1: LAYOUT__750,
    arm2: LAYOUT__752,
};
pub const LAYOUT__754: &MemoryArgLayout2LayoutArray = &[LAYOUT__643, LAYOUT__644];
pub const LAYOUT__753: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__754,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    }],
};
pub const LAYOUT__748: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__749,
    _arguments_memory_get__super: LAYOUT__753,
};
pub const LAYOUT__758: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__699 };
pub const LAYOUT__757: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__758,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__759: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__699,
    _0: LAYOUT__700,
};
pub const LAYOUT__756: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__698,
    arm1: LAYOUT__757,
    arm2: LAYOUT__759,
};
pub const LAYOUT__761: &MemoryArgLayout2LayoutArray = &[LAYOUT__645, LAYOUT__646];
pub const LAYOUT__760: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__761,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    }],
};
pub const LAYOUT__755: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__756,
    _arguments_memory_get__super: LAYOUT__760,
};
pub const LAYOUT__765: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__704 };
pub const LAYOUT__764: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__765,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__766: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__704,
    _0: LAYOUT__705,
};
pub const LAYOUT__763: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__703,
    arm1: LAYOUT__764,
    arm2: LAYOUT__766,
};
pub const LAYOUT__768: &MemoryArgLayout2LayoutArray = &[LAYOUT__647, LAYOUT__648];
pub const LAYOUT__767: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__768,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    }],
};
pub const LAYOUT__762: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__763,
    _arguments_memory_get__super: LAYOUT__767,
};
pub const LAYOUT__712: &MemoryGetLayout8LayoutArray = &[
    LAYOUT__713,
    LAYOUT__720,
    LAYOUT__727,
    LAYOUT__734,
    LAYOUT__741,
    LAYOUT__748,
    LAYOUT__755,
    LAYOUT__762,
];
pub const LAYOUT__710: &PoseidonLoadInShortLayout = &PoseidonLoadInShortLayout {
    _super: LAYOUT__629,
    tx_type: LAYOUT__711,
    load_list: LAYOUT__712,
};
pub const LAYOUT__769: &PoseidonLoadInLowLayout = &PoseidonLoadInLowLayout {
    _super: LAYOUT__629,
    tx_type: LAYOUT__711,
    load_list: LAYOUT__712,
};
pub const LAYOUT__770: &PoseidonLoadInHighLayout = &PoseidonLoadInHighLayout {
    _super: LAYOUT__629,
    tx_type: LAYOUT__711,
    load_list: LAYOUT__712,
};
pub const LAYOUT__709: &PoseidonLoadIn_SuperLayout = &PoseidonLoadIn_SuperLayout {
    _super: LAYOUT__629,
    arm0: LAYOUT__710,
    arm1: LAYOUT__769,
    arm2: LAYOUT__770,
};
pub const LAYOUT__771: &OneHot_3_Layout = &OneHot_3_Layout {
    _super: &[
        &NondetRegLayout {
            _super: &Reg { offset: 185 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 186 },
        },
        &NondetRegLayout {
            _super: &Reg { offset: 187 },
        },
    ],
};
pub const LAYOUT__772: &_Arguments_PoseidonLoadIn_SuperLayout =
    &_Arguments_PoseidonLoadIn_SuperLayout {
        memory_arg: LAYOUT__632,
        cycle_arg: LAYOUT__649,
    };
pub const LAYOUT__708: &PoseidonLoadInLayout = &PoseidonLoadInLayout {
    _super: LAYOUT__709,
    _0: LAYOUT__771,
    _arguments_poseidon_load_in__super: LAYOUT__772,
};
pub const LAYOUT__707: &Poseidon0StateArm2Layout = &Poseidon0StateArm2Layout {
    _super: LAYOUT__708,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
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
            _super: &Reg { offset: 177 },
        },
    },
    _extra16: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra17: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__773: &Poseidon0StateArm3Layout = &Poseidon0StateArm3Layout {
    _super: LAYOUT__629,
    _extra0: LAYOUT__633,
    _extra1: LAYOUT__634,
    _extra2: LAYOUT__635,
    _extra3: LAYOUT__636,
    _extra4: LAYOUT__637,
    _extra5: LAYOUT__638,
    _extra6: LAYOUT__639,
    _extra7: LAYOUT__640,
    _extra8: LAYOUT__641,
    _extra9: LAYOUT__642,
    _extra10: LAYOUT__643,
    _extra11: LAYOUT__644,
    _extra12: LAYOUT__645,
    _extra13: LAYOUT__646,
    _extra14: LAYOUT__647,
    _extra15: LAYOUT__648,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
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
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
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
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__774: &Poseidon0StateArm4Layout = &Poseidon0StateArm4Layout {
    _super: LAYOUT__629,
    _extra0: LAYOUT__633,
    _extra1: LAYOUT__634,
    _extra2: LAYOUT__635,
    _extra3: LAYOUT__636,
    _extra4: LAYOUT__637,
    _extra5: LAYOUT__638,
    _extra6: LAYOUT__639,
    _extra7: LAYOUT__640,
    _extra8: LAYOUT__641,
    _extra9: LAYOUT__642,
    _extra10: LAYOUT__643,
    _extra11: LAYOUT__644,
    _extra12: LAYOUT__645,
    _extra13: LAYOUT__646,
    _extra14: LAYOUT__647,
    _extra15: LAYOUT__648,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
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
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra32: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra33: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra36: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra37: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
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
    _extra41: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__781: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__683 };
pub const LAYOUT__782: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__684 };
pub const LAYOUT__783: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__685 };
pub const LAYOUT__784: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__686 };
pub const LAYOUT__785: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__687 };
pub const LAYOUT__786: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__692 };
pub const LAYOUT__787: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__697 };
pub const LAYOUT__788: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__702 };
pub const LAYOUT__780: &PoseidonCheckOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__781,
    LAYOUT__782,
    LAYOUT__783,
    LAYOUT__784,
    LAYOUT__785,
    LAYOUT__786,
    LAYOUT__787,
    LAYOUT__788,
];
pub const LAYOUT__779: &PoseidonCheckOutLayout = &PoseidonCheckOutLayout {
    _super: LAYOUT__629,
    _1: LAYOUT__780,
    is_normal: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    ext_inv: &NondetExtRegLayout {
        _super: &Reg { offset: 184 },
    },
};
pub const LAYOUT__778: &PoseidonDoOut_SuperArm0Layout = &PoseidonDoOut_SuperArm0Layout {
    _super: LAYOUT__779,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
    _extra1: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
    _extra2: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra3: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra4: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra5: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra6: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra7: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra8: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra9: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
    _extra10: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 166 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 167 },
        },
    },
    _extra11: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
    _extra12: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra13: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
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
            _super: &Reg { offset: 177 },
        },
    },
};
pub const LAYOUT__792: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__794: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
};
pub const LAYOUT__793: &U16RegLayout = &U16RegLayout { ret: LAYOUT__794 };
pub const LAYOUT__795: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__660,
    _0: LAYOUT__661,
};
pub const LAYOUT__791: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__792,
    high: LAYOUT__793,
    _0: LAYOUT__795,
};
pub const LAYOUT__797: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
};
pub const LAYOUT__799: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
};
pub const LAYOUT__798: &U16RegLayout = &U16RegLayout { ret: LAYOUT__799 };
pub const LAYOUT__800: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__665,
    _0: LAYOUT__666,
};
pub const LAYOUT__796: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__797,
    high: LAYOUT__798,
    _0: LAYOUT__800,
};
pub const LAYOUT__802: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
};
pub const LAYOUT__803: &U16RegLayout = &U16RegLayout { ret: LAYOUT__202 };
pub const LAYOUT__804: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__670,
    _0: LAYOUT__671,
};
pub const LAYOUT__801: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__802,
    high: LAYOUT__803,
    _0: LAYOUT__804,
};
pub const LAYOUT__806: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
};
pub const LAYOUT__808: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
};
pub const LAYOUT__807: &U16RegLayout = &U16RegLayout { ret: LAYOUT__808 };
pub const LAYOUT__809: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__674,
    _0: LAYOUT__675,
};
pub const LAYOUT__805: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__806,
    high: LAYOUT__807,
    _0: LAYOUT__809,
};
pub const LAYOUT__811: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
};
pub const LAYOUT__813: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
};
pub const LAYOUT__812: &U16RegLayout = &U16RegLayout { ret: LAYOUT__813 };
pub const LAYOUT__814: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__689,
    _0: LAYOUT__690,
};
pub const LAYOUT__810: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__811,
    high: LAYOUT__812,
    _0: LAYOUT__814,
};
pub const LAYOUT__817: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
};
pub const LAYOUT__816: &U16RegLayout = &U16RegLayout { ret: LAYOUT__817 };
pub const LAYOUT__818: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__694,
    _0: LAYOUT__695,
};
pub const LAYOUT__815: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__288,
    high: LAYOUT__816,
    _0: LAYOUT__818,
};
pub const LAYOUT__820: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
};
pub const LAYOUT__822: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
};
pub const LAYOUT__821: &U16RegLayout = &U16RegLayout { ret: LAYOUT__822 };
pub const LAYOUT__823: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__699,
    _0: LAYOUT__700,
};
pub const LAYOUT__819: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__820,
    high: LAYOUT__821,
    _0: LAYOUT__823,
};
pub const LAYOUT__825: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
};
pub const LAYOUT__827: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
};
pub const LAYOUT__826: &U16RegLayout = &U16RegLayout { ret: LAYOUT__827 };
pub const LAYOUT__828: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__704,
    _0: LAYOUT__705,
};
pub const LAYOUT__824: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__825,
    high: LAYOUT__826,
    _0: LAYOUT__828,
};
pub const LAYOUT__790: &PoseidonStoreOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__791,
    LAYOUT__796,
    LAYOUT__801,
    LAYOUT__805,
    LAYOUT__810,
    LAYOUT__815,
    LAYOUT__819,
    LAYOUT__824,
];
pub const LAYOUT__789: &PoseidonStoreOutLayout = &PoseidonStoreOutLayout {
    _super: LAYOUT__629,
    _1: LAYOUT__790,
    is_normal: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 182 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 183 },
        },
    },
    ext_inv: &NondetExtRegLayout {
        _super: &Reg { offset: 184 },
    },
};
pub const LAYOUT__777: &PoseidonDoOut_SuperLayout = &PoseidonDoOut_SuperLayout {
    _super: LAYOUT__629,
    arm0: LAYOUT__778,
    arm1: LAYOUT__789,
};
pub const LAYOUT__829: &_Arguments_PoseidonDoOut_SuperLayout =
    &_Arguments_PoseidonDoOut_SuperLayout {
        memory_arg: LAYOUT__632,
        cycle_arg: LAYOUT__649,
        arg_u16: LAYOUT__650,
    };
pub const LAYOUT__776: &PoseidonDoOutLayout = &PoseidonDoOutLayout {
    _super: LAYOUT__777,
    _arguments_poseidon_do_out__super: LAYOUT__829,
};
pub const LAYOUT__775: &Poseidon0StateArm5Layout = &Poseidon0StateArm5Layout {
    _super: LAYOUT__776,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__832: &PoseidonPaging_SuperLayout = &PoseidonPaging_SuperLayout {
    _super: LAYOUT__629,
    arm0: LAYOUT__629,
    arm1: LAYOUT__629,
    arm2: LAYOUT__629,
    arm3: LAYOUT__629,
    arm4: LAYOUT__629,
    arm5: LAYOUT__629,
};
pub const LAYOUT__834: &NondetRegLayout6LayoutArray = &[
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
pub const LAYOUT__833: &OneHot_6_Layout = &OneHot_6_Layout {
    _super: LAYOUT__834,
};
pub const LAYOUT__837: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__836: &U8RegLayout = &U8RegLayout { ret: LAYOUT__837 };
pub const LAYOUT__835: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__792,
    _0: LAYOUT__836,
};
pub const LAYOUT__838: &_Arguments_PoseidonPaging__1Layout = &_Arguments_PoseidonPaging__1Layout {
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    }],
    arg_u8: &[&ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    }],
};
pub const LAYOUT__843: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__842: &U8RegLayout = &U8RegLayout { ret: LAYOUT__843 };
pub const LAYOUT__841: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__794,
    _0: LAYOUT__842,
};
pub const LAYOUT__840: &PoseidonPaging__1Arm0_SuperLayout =
    &PoseidonPaging__1Arm0_SuperLayout { _0: LAYOUT__841 };
pub const LAYOUT__844: &PoseidonPaging__1Arm1_SuperLayout =
    &PoseidonPaging__1Arm1_SuperLayout { _0: LAYOUT__841 };
pub const LAYOUT__839: &PoseidonPaging__1Layout = &PoseidonPaging__1Layout {
    arm0: LAYOUT__840,
    arm1: LAYOUT__844,
};
pub const LAYOUT__831: &PoseidonPagingLayout = &PoseidonPagingLayout {
    _super: LAYOUT__832,
    cur_idx: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    cur_mode: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    mode_split: LAYOUT__833,
    _0: LAYOUT__835,
    _arguments_poseidon_paging__1: LAYOUT__838,
    _3: LAYOUT__839,
    _4: &NondetRegLayout {
        _super: &Reg { offset: 190 },
    },
};
pub const LAYOUT__830: &Poseidon0StateArm6Layout = &Poseidon0StateArm6Layout {
    _super: LAYOUT__831,
    _extra0: LAYOUT__633,
    _extra1: LAYOUT__634,
    _extra2: LAYOUT__635,
    _extra3: LAYOUT__636,
    _extra4: LAYOUT__637,
    _extra5: LAYOUT__638,
    _extra6: LAYOUT__639,
    _extra7: LAYOUT__640,
    _extra8: LAYOUT__641,
    _extra9: LAYOUT__642,
    _extra10: LAYOUT__643,
    _extra11: LAYOUT__644,
    _extra12: LAYOUT__645,
    _extra13: LAYOUT__646,
    _extra14: LAYOUT__647,
    _extra15: LAYOUT__648,
    _extra16: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
    _extra17: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
    _extra18: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
    _extra19: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
    _extra20: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
    _extra21: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
    _extra22: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
    _extra23: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
    _extra24: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
    _extra25: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
    _extra26: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
    _extra27: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 156 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 157 },
        },
    },
    _extra28: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
    _extra29: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
        },
    },
    _extra30: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
    _extra31: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
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
            _super: &Reg { offset: 169 },
        },
    },
    _extra34: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
    _extra35: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
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
            _super: &Reg { offset: 177 },
        },
    },
};
pub const LAYOUT__848: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__792,
    high: LAYOUT__793,
    _0: LAYOUT__795,
};
pub const LAYOUT__849: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__797,
    high: LAYOUT__798,
    _0: LAYOUT__800,
};
pub const LAYOUT__850: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__802,
    high: LAYOUT__803,
    _0: LAYOUT__804,
};
pub const LAYOUT__851: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__806,
    high: LAYOUT__807,
    _0: LAYOUT__809,
};
pub const LAYOUT__852: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__811,
    high: LAYOUT__812,
    _0: LAYOUT__814,
};
pub const LAYOUT__853: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__288,
    high: LAYOUT__816,
    _0: LAYOUT__818,
};
pub const LAYOUT__854: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__820,
    high: LAYOUT__821,
    _0: LAYOUT__823,
};
pub const LAYOUT__855: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__825,
    high: LAYOUT__826,
    _0: LAYOUT__828,
};
pub const LAYOUT__847: &PoseidonStoreState__0_SuperLayout8LayoutArray = &[
    LAYOUT__848,
    LAYOUT__849,
    LAYOUT__850,
    LAYOUT__851,
    LAYOUT__852,
    LAYOUT__853,
    LAYOUT__854,
    LAYOUT__855,
];
pub const LAYOUT__846: &PoseidonStoreStateLayout = &PoseidonStoreStateLayout {
    _super: LAYOUT__629,
    _1: LAYOUT__847,
};
pub const LAYOUT__845: &Poseidon0StateArm7Layout = &Poseidon0StateArm7Layout {
    _super: LAYOUT__846,
    _extra0: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
    _extra1: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__652: &Poseidon0StateLayout = &Poseidon0StateLayout {
    _super: LAYOUT__629,
    arm0: LAYOUT__653,
    arm1: LAYOUT__680,
    arm2: LAYOUT__707,
    arm3: LAYOUT__773,
    arm4: LAYOUT__774,
    arm5: LAYOUT__775,
    arm6: LAYOUT__830,
    arm7: LAYOUT__845,
};
pub const LAYOUT__628: &Poseidon0Layout = &Poseidon0Layout {
    state: LAYOUT__629,
    _arguments_poseidon0_state: LAYOUT__631,
    state_redef: LAYOUT__652,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
};
pub const LAYOUT__861: &SBoxLayout24LayoutArray = &[
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
    &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
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
];
pub const LAYOUT__860: &DoExtRoundLayout = &DoExtRoundLayout { _1: LAYOUT__861 };
pub const LAYOUT__863: &NondetRegLayout8LayoutArray = &[
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
];
pub const LAYOUT__862: &OneHot_8_Layout = &OneHot_8_Layout {
    _super: LAYOUT__863,
};
pub const LAYOUT__859: &DoExtRoundByIdxLayout = &DoExtRoundByIdxLayout {
    _super: LAYOUT__860,
    idx_hot: LAYOUT__862,
};
pub const LAYOUT__858: &PoseidonExtRoundLayout = &PoseidonExtRoundLayout {
    _super: LAYOUT__629,
    is_round3: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
    is_round7: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
    last_block: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
    next_inner: LAYOUT__859,
};
pub const LAYOUT__867: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
};
pub const LAYOUT__868: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
};
pub const LAYOUT__869: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
};
pub const LAYOUT__870: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
};
pub const LAYOUT__871: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__872: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
};
pub const LAYOUT__873: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__874: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
};
pub const LAYOUT__875: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
};
pub const LAYOUT__876: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__877: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
};
pub const LAYOUT__878: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__879: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
};
pub const LAYOUT__880: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__881: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
};
pub const LAYOUT__882: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
    },
};
pub const LAYOUT__883: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
    },
};
pub const LAYOUT__884: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
};
pub const LAYOUT__885: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__886: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
};
pub const LAYOUT__887: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
};
pub const LAYOUT__866: &DoIntRoundLayout21LayoutArray = &[
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
    LAYOUT__885,
    LAYOUT__886,
    LAYOUT__887,
];
pub const LAYOUT__865: &DoIntRoundsLayout = &DoIntRoundsLayout {
    _super: LAYOUT__866,
};
pub const LAYOUT__864: &PoseidonIntRoundsLayout = &PoseidonIntRoundsLayout {
    _super: LAYOUT__629,
    next_inner: LAYOUT__865,
};
pub const LAYOUT__857: &Poseidon1StateLayout = &Poseidon1StateLayout {
    _super: LAYOUT__629,
    arm0: LAYOUT__858,
    arm1: LAYOUT__864,
    arm2: LAYOUT__629,
    arm3: LAYOUT__629,
    arm4: LAYOUT__629,
    arm5: LAYOUT__629,
    arm6: LAYOUT__629,
    arm7: LAYOUT__629,
};
pub const LAYOUT__856: &Poseidon1Layout = &Poseidon1Layout {
    state: LAYOUT__629,
    state_redef: LAYOUT__857,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
};
pub const LAYOUT__6: &TopInstResultLayout = &TopInstResultLayout {
    _selector: LAYOUT__5,
    arm0: LAYOUT__7,
    arm1: LAYOUT__88,
    arm2: LAYOUT__106,
    arm3: LAYOUT__119,
    arm4: LAYOUT__203,
    arm5: LAYOUT__289,
    arm6: LAYOUT__350,
    arm7: LAYOUT__408,
    arm8: LAYOUT__576,
    arm9: LAYOUT__628,
    arm10: LAYOUT__856,
};
pub const LAYOUT__0: &TopLayout = &TopLayout {
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
    cycle_nd: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
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
pub const LAYOUT__889: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__888: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__889,
};
pub const LAYOUT__891: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__890: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__891,
};
pub const LAYOUT__893: &DigestRegValues_SuperLayout8LayoutArray = &[
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
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 49 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 50 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 51 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 52 },
        },
    },
];
pub const LAYOUT__892: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__893,
};
pub const LAYOUT__895: &DigestRegValues_SuperLayout8LayoutArray = &[
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 57 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 58 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
    &DigestRegValues_SuperLayout {
        low: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        high: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
];
pub const LAYOUT__894: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__895,
};
pub const LAYOUT__896: &_accumLayout = &_accumLayout {
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
    ],
};
pub const LAYOUT_TEST_SUCC_RUN: &TestSuccRunLayout = &TestSuccRunLayout { _0: LAYOUT__0 };
pub const LAYOUT_TOP: &TopLayout = &TopLayout {
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
    cycle_nd: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
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
    input: LAYOUT__888,
    is_terminate: &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    output: LAYOUT__890,
    rng: &NondetExtRegLayout {
        _super: &Reg { offset: 33 },
    },
    state_in: LAYOUT__892,
    state_out: LAYOUT__894,
    term_a0high: &NondetRegLayout {
        _super: &Reg { offset: 69 },
    },
    term_a0low: &NondetRegLayout {
        _super: &Reg { offset: 70 },
    },
    term_a1high: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    term_a1low: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
};
pub const LAYOUT_MIX: &_mixLayout = &_mixLayout {
    randomness: LAYOUT__896,
};
