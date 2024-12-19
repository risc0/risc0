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
pub const LAYOUT__295: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 53 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 54 },
        },
    },
};
pub const LAYOUT__294: &U16RegLayout = &U16RegLayout { ret: LAYOUT__295 };
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
pub const LAYOUT__293: &AddrDecomposeLayout = &AddrDecomposeLayout {
    low2: &NondetRegLayout {
        _super: &Reg { offset: 52 },
    },
    upper_diff: LAYOUT__294,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 55 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 56 },
        },
    },
    med14: LAYOUT__296,
};
pub const LAYOUT__299: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__300: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__298: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__299,
    new_txn: LAYOUT__300,
};
pub const LAYOUT__302: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 68 },
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
            _super: &Reg { offset: 51 },
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
pub const LAYOUT__307: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__305: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__306,
    new_txn: LAYOUT__307,
};
pub const LAYOUT__309: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 78 },
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
        _super: &Reg { offset: 79 },
    },
};
pub const LAYOUT__310: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__27,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    high16: LAYOUT__125,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 85 },
    },
};
pub const LAYOUT__313: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__312: &U16RegLayout = &U16RegLayout { ret: LAYOUT__313 };
pub const LAYOUT__314: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__311: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 86 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 87 },
    },
    upper_diff: LAYOUT__312,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
    med14: LAYOUT__314,
};
pub const LAYOUT__317: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__318: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 99 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 94 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
};
pub const LAYOUT__316: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__317,
    new_txn: LAYOUT__318,
};
pub const LAYOUT__320: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__319: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__320 };
pub const LAYOUT__315: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__316,
    _0: LAYOUT__319,
};
pub const LAYOUT__290: &MemLoadInputLayout = &MemLoadInputLayout {
    decoded: LAYOUT__291,
    rs1: LAYOUT__303,
    addr_u32: LAYOUT__310,
    addr: LAYOUT__311,
    data_0: LAYOUT__315,
};
pub const LAYOUT__322: &ArgU8Layout3LayoutArray = &[
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
pub const LAYOUT__321: &_Arguments_Mem0OutputLayout = &_Arguments_Mem0OutputLayout {
    arg_u8: LAYOUT__322,
    arg_u16: &[&ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    }],
};
pub const LAYOUT__327: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 27 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 28 },
        },
    },
};
pub const LAYOUT__328: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 29 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 30 },
        },
    },
};
pub const LAYOUT__326: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__327,
    byte1: LAYOUT__328,
};
pub const LAYOUT__329: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 31 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 32 },
        },
    },
};
pub const LAYOUT__325: &OpLBLayout = &OpLBLayout {
    bytes: LAYOUT__326,
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    low7x2: LAYOUT__329,
};
pub const LAYOUT__324: &Mem0OutputArm0Layout = &Mem0OutputArm0Layout {
    _super: LAYOUT__325,
    _extra0: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__331: &OpLHLayout = &OpLHLayout {
    high_bit: &NondetRegLayout {
        _super: &Reg { offset: 104 },
    },
    low15x2: LAYOUT__81,
};
pub const LAYOUT__330: &Mem0OutputArm1Layout = &Mem0OutputArm1Layout {
    _super: LAYOUT__331,
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
pub const LAYOUT__332: &Mem0OutputArm2Layout = &Mem0OutputArm2Layout {
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
pub const LAYOUT__334: &OpLBULayout = &OpLBULayout { bytes: LAYOUT__326 };
pub const LAYOUT__333: &Mem0OutputArm3Layout = &Mem0OutputArm3Layout {
    _super: LAYOUT__334,
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
pub const LAYOUT__335: &Mem0OutputArm4Layout = &Mem0OutputArm4Layout {
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
pub const LAYOUT__336: &Mem0OutputArm5Layout = &Mem0OutputArm5Layout {
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
pub const LAYOUT__337: &Mem0OutputArm6Layout = &Mem0OutputArm6Layout {
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
pub const LAYOUT__338: &Mem0OutputArm7Layout = &Mem0OutputArm7Layout {
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
pub const LAYOUT__323: &Mem0OutputLayout = &Mem0OutputLayout {
    arm0: LAYOUT__324,
    arm1: LAYOUT__330,
    arm2: LAYOUT__332,
    arm3: LAYOUT__333,
    arm4: LAYOUT__335,
    arm5: LAYOUT__336,
    arm6: LAYOUT__337,
    arm7: LAYOUT__338,
};
pub const LAYOUT__342: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 109 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 108 },
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
pub const LAYOUT__343: &MemoryArgLayout = &MemoryArgLayout {
    count: &NondetRegLayout {
        _super: &Reg { offset: 113 },
    },
    addr: &NondetRegLayout {
        _super: &Reg { offset: 108 },
    },
    cycle: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    data_low: &NondetRegLayout {
        _super: &Reg { offset: 114 },
    },
    data_high: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
};
pub const LAYOUT__341: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__342,
    new_txn: LAYOUT__343,
};
pub const LAYOUT__345: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 117 },
        },
    },
};
pub const LAYOUT__344: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__345 };
pub const LAYOUT__340: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__341,
    _0: LAYOUT__344,
};
pub const LAYOUT__339: &WriteRdLayout = &WriteRdLayout {
    is_rd0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
    },
    write_addr: &NondetRegLayout {
        _super: &Reg { offset: 107 },
    },
    _0: LAYOUT__340,
};
pub const LAYOUT__347: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 118 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 119 },
        },
    },
};
pub const LAYOUT__348: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 121 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 122 },
        },
    },
};
pub const LAYOUT__346: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__347,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 120 },
    },
    high16: LAYOUT__348,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 123 },
    },
};
pub const LAYOUT__289: &Mem0Layout = &Mem0Layout {
    input: LAYOUT__290,
    _arguments_mem0_output: LAYOUT__321,
    output: LAYOUT__323,
    _0: LAYOUT__339,
    pc_add: LAYOUT__346,
};
pub const LAYOUT__354: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__355: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__353: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__354,
    new_txn: LAYOUT__355,
};
pub const LAYOUT__357: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 89 },
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
        _super: &Reg { offset: 90 },
    },
};
pub const LAYOUT__359: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
};
pub const LAYOUT__360: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
};
pub const LAYOUT__358: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__359,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 93 },
    },
    high16: LAYOUT__360,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 96 },
    },
};
pub const LAYOUT__363: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
    },
};
pub const LAYOUT__362: &U16RegLayout = &U16RegLayout { ret: LAYOUT__363 };
pub const LAYOUT__364: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
    },
};
pub const LAYOUT__361: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 97 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 98 },
    },
    upper_diff: LAYOUT__362,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
    },
    med14: LAYOUT__364,
};
pub const LAYOUT__350: &MemStoreInputLayout = &MemStoreInputLayout {
    decoded: LAYOUT__291,
    rs1: LAYOUT__303,
    rs2: LAYOUT__351,
    addr_u32: LAYOUT__358,
    addr: LAYOUT__361,
    data_0: LAYOUT__218,
};
pub const LAYOUT__366: &ArgU8Layout4LayoutArray = &[
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
pub const LAYOUT__365: &_Arguments_Mem1OutputLayout = &_Arguments_Mem1OutputLayout {
    arg_u8: LAYOUT__366,
};
pub const LAYOUT__370: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 33 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 34 },
        },
    },
};
pub const LAYOUT__369: &SplitWordLayout = &SplitWordLayout {
    byte0: LAYOUT__329,
    byte1: LAYOUT__370,
};
pub const LAYOUT__368: &OpSBLayout = &OpSBLayout {
    orig_bytes: LAYOUT__326,
    new_bytes: LAYOUT__369,
};
pub const LAYOUT__371: &Mem1OutputArm1Layout = &Mem1OutputArm1Layout {
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
pub const LAYOUT__372: &Mem1OutputArm2Layout = &Mem1OutputArm2Layout {
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
pub const LAYOUT__373: &Mem1OutputArm3Layout = &Mem1OutputArm3Layout {
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
pub const LAYOUT__374: &Mem1OutputArm4Layout = &Mem1OutputArm4Layout {
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
pub const LAYOUT__375: &Mem1OutputArm5Layout = &Mem1OutputArm5Layout {
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
pub const LAYOUT__376: &Mem1OutputArm6Layout = &Mem1OutputArm6Layout {
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
pub const LAYOUT__377: &Mem1OutputArm7Layout = &Mem1OutputArm7Layout {
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
pub const LAYOUT__367: &Mem1OutputLayout = &Mem1OutputLayout {
    arm0: LAYOUT__368,
    arm1: LAYOUT__371,
    arm2: LAYOUT__372,
    arm3: LAYOUT__373,
    arm4: LAYOUT__374,
    arm5: LAYOUT__375,
    arm6: LAYOUT__376,
    arm7: LAYOUT__377,
};
pub const LAYOUT__381: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__382: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__380: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__381,
    new_txn: LAYOUT__382,
};
pub const LAYOUT__384: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 123 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 124 },
        },
    },
};
pub const LAYOUT__383: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__384 };
pub const LAYOUT__379: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__380,
    _0: LAYOUT__383,
};
pub const LAYOUT__378: &MemStoreFinalizeLayout = &MemStoreFinalizeLayout { _0: LAYOUT__379 };
pub const LAYOUT__386: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 125 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 126 },
        },
    },
};
pub const LAYOUT__387: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 128 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 129 },
        },
    },
};
pub const LAYOUT__385: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__386,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 127 },
    },
    high16: LAYOUT__387,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 130 },
    },
};
pub const LAYOUT__349: &Mem1Layout = &Mem1Layout {
    input: LAYOUT__350,
    _arguments_mem1_output: LAYOUT__365,
    output: LAYOUT__367,
    _0: LAYOUT__378,
    pc_add: LAYOUT__385,
};
pub const LAYOUT__396: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__397: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__395: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__396,
    new_txn: LAYOUT__397,
};
pub const LAYOUT__394: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__395 };
pub const LAYOUT__393: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__394 };
pub const LAYOUT__401: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__402: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__400: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__401,
    new_txn: LAYOUT__402,
};
pub const LAYOUT__399: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__400 };
pub const LAYOUT__398: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__399 };
pub const LAYOUT__406: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__407: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__405: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__406,
    new_txn: LAYOUT__407,
};
pub const LAYOUT__404: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__405 };
pub const LAYOUT__403: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__404 };
pub const LAYOUT__411: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__412: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__410: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__411,
    new_txn: LAYOUT__412,
};
pub const LAYOUT__409: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__410 };
pub const LAYOUT__408: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__409 };
pub const LAYOUT__416: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__417: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__415: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__416,
    new_txn: LAYOUT__417,
};
pub const LAYOUT__414: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__415 };
pub const LAYOUT__413: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__414 };
pub const LAYOUT__421: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__422: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__420: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__421,
    new_txn: LAYOUT__422,
};
pub const LAYOUT__419: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__420 };
pub const LAYOUT__418: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__419 };
pub const LAYOUT__426: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__427: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__425: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__426,
    new_txn: LAYOUT__427,
};
pub const LAYOUT__424: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__425 };
pub const LAYOUT__423: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__424 };
pub const LAYOUT__431: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__432: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__430: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__431,
    new_txn: LAYOUT__432,
};
pub const LAYOUT__429: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__430 };
pub const LAYOUT__428: &ControlLoadRoot__0_SuperLayout =
    &ControlLoadRoot__0_SuperLayout { mem: LAYOUT__429 };
pub const LAYOUT__392: &ControlLoadRoot__0_SuperLayout8LayoutArray = &[
    LAYOUT__393,
    LAYOUT__398,
    LAYOUT__403,
    LAYOUT__408,
    LAYOUT__413,
    LAYOUT__418,
    LAYOUT__423,
    LAYOUT__428,
];
pub const LAYOUT__391: &ControlLoadRootLayout = &ControlLoadRootLayout { _1: LAYOUT__392 };
pub const LAYOUT__390: &Control0_SuperArm0Layout = &Control0_SuperArm0Layout {
    _super: LAYOUT__391,
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
pub const LAYOUT__440: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
    },
};
pub const LAYOUT__439: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__440 };
pub const LAYOUT__438: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__395,
    _0: LAYOUT__439,
};
pub const LAYOUT__443: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
    },
};
pub const LAYOUT__442: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__443 };
pub const LAYOUT__441: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__400,
    _0: LAYOUT__442,
};
pub const LAYOUT__437: &ControlResume_SuperArm0_SuperLayout =
    &ControlResume_SuperArm0_SuperLayout {
        pc: LAYOUT__438,
        mode: LAYOUT__441,
    };
pub const LAYOUT__436: &ControlResume_SuperArm0Layout = &ControlResume_SuperArm0Layout {
    _super: LAYOUT__437,
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
pub const LAYOUT__447: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__395,
    _0: LAYOUT__439,
};
pub const LAYOUT__446: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__447 };
pub const LAYOUT__449: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__400,
    _0: LAYOUT__442,
};
pub const LAYOUT__448: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__449 };
pub const LAYOUT__453: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
    },
};
pub const LAYOUT__452: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__453 };
pub const LAYOUT__451: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__405,
    _0: LAYOUT__452,
};
pub const LAYOUT__450: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__451 };
pub const LAYOUT__455: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__410,
    _0: LAYOUT__131,
};
pub const LAYOUT__454: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__455 };
pub const LAYOUT__459: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 100 },
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
            _super: &Reg { offset: 101 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 102 },
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
    _0: LAYOUT__215,
};
pub const LAYOUT__464: &ControlResume_SuperArm1_Super__0_SuperLayout =
    &ControlResume_SuperArm1_Super__0_SuperLayout { _0: LAYOUT__465 };
pub const LAYOUT__469: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 106 },
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
pub const LAYOUT__445: &ControlResume_SuperArm1_Super__0_SuperLayout8LayoutArray = &[
    LAYOUT__446,
    LAYOUT__448,
    LAYOUT__450,
    LAYOUT__454,
    LAYOUT__456,
    LAYOUT__460,
    LAYOUT__464,
    LAYOUT__466,
];
pub const LAYOUT__444: &ControlResume_SuperArm1_SuperLayout =
    &ControlResume_SuperArm1_SuperLayout { _1: LAYOUT__445 };
pub const LAYOUT__435: &ControlResume_SuperLayout = &ControlResume_SuperLayout {
    arm0: LAYOUT__436,
    arm1: LAYOUT__444,
};
pub const LAYOUT__471: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__396,
    LAYOUT__397,
    LAYOUT__401,
    LAYOUT__402,
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
];
pub const LAYOUT__472: &CycleArgLayout8LayoutArray = &[
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
pub const LAYOUT__470: &_Arguments_ControlResume_SuperLayout =
    &_Arguments_ControlResume_SuperLayout {
        memory_arg: LAYOUT__471,
        cycle_arg: LAYOUT__472,
    };
pub const LAYOUT__434: &ControlResumeLayout = &ControlResumeLayout {
    _super: LAYOUT__435,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
    _arguments_control_resume__super: LAYOUT__470,
};
pub const LAYOUT__433: &Control0_SuperArm1Layout = &Control0_SuperArm1Layout {
    _super: LAYOUT__434,
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
pub const LAYOUT__477: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 108 },
        },
    },
};
pub const LAYOUT__476: &U16RegLayout = &U16RegLayout { ret: LAYOUT__477 };
pub const LAYOUT__478: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 109 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
    },
};
pub const LAYOUT__475: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 172 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 173 },
    },
    upper_diff: LAYOUT__476,
    _0: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
    med14: LAYOUT__478,
};
pub const LAYOUT__480: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 112 },
        },
    },
};
pub const LAYOUT__479: &U16RegLayout = &U16RegLayout { ret: LAYOUT__480 };
pub const LAYOUT__481: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__405,
    _0: LAYOUT__452,
};
pub const LAYOUT__474: &ControlUserECALLLayout = &ControlUserECALLLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
    pc_addr: LAYOUT__475,
    load_inst: LAYOUT__438,
    dispatch_idx: LAYOUT__441,
    _0: LAYOUT__479,
    new_pc_addr: LAYOUT__481,
    _1: LAYOUT__455,
};
pub const LAYOUT__473: &Control0_SuperArm2Layout = &Control0_SuperArm2Layout {
    _super: LAYOUT__474,
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
pub const LAYOUT__485: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 113 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 114 },
        },
    },
};
pub const LAYOUT__484: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__480,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 176 },
    },
    high16: LAYOUT__485,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 177 },
    },
};
pub const LAYOUT__483: &ControlMRETLayout = &ControlMRETLayout {
    safe_mode: &NondetRegLayout {
        _super: &Reg { offset: 171 },
    },
    pc_addr: LAYOUT__475,
    load_inst: LAYOUT__438,
    pc: LAYOUT__441,
    pc_add: LAYOUT__484,
};
pub const LAYOUT__482: &Control0_SuperArm3Layout = &Control0_SuperArm3Layout {
    _super: LAYOUT__483,
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
pub const LAYOUT__491: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__410,
    _0: LAYOUT__131,
};
pub const LAYOUT__492: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__415,
    _0: LAYOUT__458,
};
pub const LAYOUT__493: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__420,
    _0: LAYOUT__462,
};
pub const LAYOUT__494: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__425,
    _0: LAYOUT__215,
};
pub const LAYOUT__495: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__430,
    _0: LAYOUT__468,
};
pub const LAYOUT__490: &MemoryReadLayout8LayoutArray = &[
    LAYOUT__438,
    LAYOUT__441,
    LAYOUT__481,
    LAYOUT__491,
    LAYOUT__492,
    LAYOUT__493,
    LAYOUT__494,
    LAYOUT__495,
];
pub const LAYOUT__489: &ControlSuspend_SuperArm0_SuperLayout =
    &ControlSuspend_SuperArm0_SuperLayout { _1: LAYOUT__490 };
pub const LAYOUT__497: &ControlSuspend_SuperArm1_SuperLayout =
    &ControlSuspend_SuperArm1_SuperLayout {
        state: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        _0: LAYOUT__447,
        _1: LAYOUT__449,
    };
pub const LAYOUT__496: &ControlSuspend_SuperArm1Layout = &ControlSuspend_SuperArm1Layout {
    _super: LAYOUT__497,
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
pub const LAYOUT__488: &ControlSuspend_SuperLayout = &ControlSuspend_SuperLayout {
    arm0: LAYOUT__489,
    arm1: LAYOUT__496,
};
pub const LAYOUT__498: &_Arguments_ControlSuspend_SuperLayout =
    &_Arguments_ControlSuspend_SuperLayout {
        memory_arg: LAYOUT__471,
        cycle_arg: LAYOUT__472,
    };
pub const LAYOUT__487: &ControlSuspendLayout = &ControlSuspendLayout {
    _super: LAYOUT__488,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
    _arguments_control_suspend__super: LAYOUT__498,
};
pub const LAYOUT__486: &Control0_SuperArm4Layout = &Control0_SuperArm4Layout {
    _super: LAYOUT__487,
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
pub const LAYOUT__502: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__395,
    _0: LAYOUT__439,
};
pub const LAYOUT__503: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__400,
    _0: LAYOUT__442,
};
pub const LAYOUT__504: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__405,
    _0: LAYOUT__452,
};
pub const LAYOUT__505: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__410,
    _0: LAYOUT__131,
};
pub const LAYOUT__506: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__415,
    _0: LAYOUT__458,
};
pub const LAYOUT__507: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__420,
    _0: LAYOUT__462,
};
pub const LAYOUT__508: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__425,
    _0: LAYOUT__215,
};
pub const LAYOUT__509: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__430,
    _0: LAYOUT__468,
};
pub const LAYOUT__501: &MemoryPageOutLayout8LayoutArray = &[
    LAYOUT__502,
    LAYOUT__503,
    LAYOUT__504,
    LAYOUT__505,
    LAYOUT__506,
    LAYOUT__507,
    LAYOUT__508,
    LAYOUT__509,
];
pub const LAYOUT__500: &ControlStoreRootLayout = &ControlStoreRootLayout { _1: LAYOUT__501 };
pub const LAYOUT__499: &Control0_SuperArm5Layout = &Control0_SuperArm5Layout {
    _super: LAYOUT__500,
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
pub const LAYOUT__516: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__517: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__518: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__519: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__520: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__521: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__522: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__523: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__524: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__525: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__526: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__527: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__528: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__529: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__530: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__531: &ControlTable_SuperArm0_Super__0_SuperLayout =
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
pub const LAYOUT__515: &ControlTable_SuperArm0_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__516,
    LAYOUT__517,
    LAYOUT__518,
    LAYOUT__519,
    LAYOUT__520,
    LAYOUT__521,
    LAYOUT__522,
    LAYOUT__523,
    LAYOUT__524,
    LAYOUT__525,
    LAYOUT__526,
    LAYOUT__527,
    LAYOUT__528,
    LAYOUT__529,
    LAYOUT__530,
    LAYOUT__531,
];
pub const LAYOUT__514: &ControlTable_SuperArm0_SuperLayout = &ControlTable_SuperArm0_SuperLayout {
    _1: LAYOUT__515,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
};
pub const LAYOUT__513: &ControlTable_SuperArm0Layout = &ControlTable_SuperArm0Layout {
    _super: LAYOUT__514,
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
pub const LAYOUT__535: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__536: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__537: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__538: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__539: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__540: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__541: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__542: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__543: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__544: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__545: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__546: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__547: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__548: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__549: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__550: &ControlTable_SuperArm1_Super__0_SuperLayout =
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
pub const LAYOUT__534: &ControlTable_SuperArm1_Super__0_SuperLayout16LayoutArray = &[
    LAYOUT__535,
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
];
pub const LAYOUT__533: &ControlTable_SuperArm1_SuperLayout = &ControlTable_SuperArm1_SuperLayout {
    _1: LAYOUT__534,
    done: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
    },
};
pub const LAYOUT__532: &ControlTable_SuperArm1Layout = &ControlTable_SuperArm1Layout {
    _super: LAYOUT__533,
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
pub const LAYOUT__512: &ControlTable_SuperLayout = &ControlTable_SuperLayout {
    arm0: LAYOUT__513,
    arm1: LAYOUT__532,
};
pub const LAYOUT__552: &ArgU16Layout16LayoutArray = &[
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
pub const LAYOUT__553: &ArgU8Layout16LayoutArray = &[
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
pub const LAYOUT__551: &_Arguments_ControlTable_SuperLayout =
    &_Arguments_ControlTable_SuperLayout {
        arg_u16: LAYOUT__552,
        arg_u8: LAYOUT__553,
    };
pub const LAYOUT__511: &ControlTableLayout = &ControlTableLayout {
    _super: LAYOUT__512,
    entry: &NondetRegLayout {
        _super: &Reg { offset: 173 },
    },
    mode: &NondetRegLayout {
        _super: &Reg { offset: 174 },
    },
    _arguments_control_table__super: LAYOUT__551,
};
pub const LAYOUT__510: &Control0_SuperArm6Layout = &Control0_SuperArm6Layout {
    _super: LAYOUT__511,
    _extra0: LAYOUT__396,
    _extra1: LAYOUT__397,
    _extra2: LAYOUT__401,
    _extra3: LAYOUT__402,
    _extra4: LAYOUT__406,
    _extra5: LAYOUT__407,
    _extra6: LAYOUT__411,
    _extra7: LAYOUT__412,
    _extra8: LAYOUT__416,
    _extra9: LAYOUT__417,
    _extra10: LAYOUT__421,
    _extra11: LAYOUT__422,
    _extra12: LAYOUT__426,
    _extra13: LAYOUT__427,
    _extra14: LAYOUT__431,
    _extra15: LAYOUT__432,
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
pub const LAYOUT__554: &Control0_SuperArm7Layout = &Control0_SuperArm7Layout {
    _extra0: LAYOUT__396,
    _extra1: LAYOUT__397,
    _extra2: LAYOUT__401,
    _extra3: LAYOUT__402,
    _extra4: LAYOUT__406,
    _extra5: LAYOUT__407,
    _extra6: LAYOUT__411,
    _extra7: LAYOUT__412,
    _extra8: LAYOUT__416,
    _extra9: LAYOUT__417,
    _extra10: LAYOUT__421,
    _extra11: LAYOUT__422,
    _extra12: LAYOUT__426,
    _extra13: LAYOUT__427,
    _extra14: LAYOUT__431,
    _extra15: LAYOUT__432,
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
pub const LAYOUT__389: &Control0_SuperLayout = &Control0_SuperLayout {
    arm0: LAYOUT__390,
    arm1: LAYOUT__433,
    arm2: LAYOUT__473,
    arm3: LAYOUT__482,
    arm4: LAYOUT__486,
    arm5: LAYOUT__499,
    arm6: LAYOUT__510,
    arm7: LAYOUT__554,
};
pub const LAYOUT__555: &_Arguments_Control0_SuperLayout = &_Arguments_Control0_SuperLayout {
    memory_arg: LAYOUT__471,
    cycle_arg: LAYOUT__472,
    arg_u16: LAYOUT__552,
    arg_u8: LAYOUT__553,
};
pub const LAYOUT__388: &Control0Layout = &Control0Layout {
    _super: LAYOUT__389,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
    _arguments_control0__super: LAYOUT__555,
};
pub const LAYOUT__559: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
};
pub const LAYOUT__558: &U16RegLayout = &U16RegLayout { ret: LAYOUT__559 };
pub const LAYOUT__557: &AddrDecomposeBitsLayout = &AddrDecomposeBitsLayout {
    low0: &NondetRegLayout {
        _super: &Reg { offset: 74 },
    },
    low1: &NondetRegLayout {
        _super: &Reg { offset: 75 },
    },
    upper_diff: LAYOUT__558,
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
pub const LAYOUT__561: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__396,
    LAYOUT__397,
    LAYOUT__401,
    LAYOUT__402,
    LAYOUT__406,
    LAYOUT__407,
    LAYOUT__411,
    LAYOUT__412,
];
pub const LAYOUT__562: &CycleArgLayout4LayoutArray = &[
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
pub const LAYOUT__563: &ArgU16Layout2LayoutArray = &[
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
pub const LAYOUT__560: &_Arguments_ECall0OutputLayout = &_Arguments_ECall0OutputLayout {
    memory_arg: LAYOUT__561,
    cycle_arg: LAYOUT__562,
    arg_u16: LAYOUT__563,
};
pub const LAYOUT__569: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 59 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 60 },
        },
    },
};
pub const LAYOUT__568: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__569 };
pub const LAYOUT__567: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__395,
    _0: LAYOUT__568,
};
pub const LAYOUT__572: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 61 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 62 },
        },
    },
};
pub const LAYOUT__571: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__572 };
pub const LAYOUT__570: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__400,
    _0: LAYOUT__571,
};
pub const LAYOUT__574: &NondetRegLayout4LayoutArray = &[
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
pub const LAYOUT__573: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__574,
};
pub const LAYOUT__566: &MachineECallLayout = &MachineECallLayout {
    load_inst: LAYOUT__567,
    dispatch_idx: LAYOUT__570,
    dispatch: LAYOUT__573,
};
pub const LAYOUT__565: &ECall0OutputArm0Layout = &ECall0OutputArm0Layout {
    _super: LAYOUT__566,
    _extra0: LAYOUT__406,
    _extra1: LAYOUT__407,
    _extra2: LAYOUT__411,
    _extra3: LAYOUT__412,
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
pub const LAYOUT__576: &ECallTerminateLayout = &ECallTerminateLayout {
    a0: LAYOUT__567,
    a1: LAYOUT__570,
};
pub const LAYOUT__575: &ECall0OutputArm1Layout = &ECall0OutputArm1Layout {
    _super: LAYOUT__576,
    _extra0: LAYOUT__406,
    _extra1: LAYOUT__407,
    _extra2: LAYOUT__411,
    _extra3: LAYOUT__412,
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
pub const LAYOUT__580: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 63 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 64 },
        },
    },
};
pub const LAYOUT__579: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__580 };
pub const LAYOUT__578: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__405,
    _0: LAYOUT__579,
};
pub const LAYOUT__581: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
    },
};
pub const LAYOUT__583: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
    },
};
pub const LAYOUT__582: &U16RegLayout = &U16RegLayout { ret: LAYOUT__583 };
pub const LAYOUT__586: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 65 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
    },
};
pub const LAYOUT__585: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__586 };
pub const LAYOUT__584: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__410,
    _0: LAYOUT__585,
};
pub const LAYOUT__589: &NondetRegLayout4LayoutArray = &[
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
pub const LAYOUT__588: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__589,
};
pub const LAYOUT__587: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: &NondetRegLayout {
        _super: &Reg { offset: 82 },
    },
    low2: &NondetRegLayout {
        _super: &Reg { offset: 83 },
    },
    low2_hot: LAYOUT__588,
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
pub const LAYOUT__592: &NondetRegLayout4LayoutArray = &[
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
pub const LAYOUT__591: &OneHot_4_Layout = &OneHot_4_Layout {
    _super: LAYOUT__592,
};
pub const LAYOUT__590: &DecomposeLow2Layout = &DecomposeLow2Layout {
    high: &NondetRegLayout {
        _super: &Reg { offset: 91 },
    },
    low2: &NondetRegLayout {
        _super: &Reg { offset: 92 },
    },
    low2_hot: LAYOUT__591,
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
pub const LAYOUT__577: &ECallHostReadSetupLayout = &ECallHostReadSetupLayout {
    fd: LAYOUT__567,
    ptr: LAYOUT__570,
    len: LAYOUT__578,
    new_len: LAYOUT__581,
    diff: LAYOUT__582,
    _0: LAYOUT__584,
    ptr_decomp: LAYOUT__587,
    len_decomp: LAYOUT__590,
    len123: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    uneven: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
};
pub const LAYOUT__593: &ECallHostWriteLayout = &ECallHostWriteLayout {
    fd: LAYOUT__567,
    ptr: LAYOUT__570,
    len: LAYOUT__578,
    new_len: LAYOUT__581,
    diff: LAYOUT__582,
    _0: LAYOUT__584,
};
pub const LAYOUT__594: &ECall0OutputArm4Layout = &ECall0OutputArm4Layout {
    _extra0: LAYOUT__396,
    _extra1: LAYOUT__397,
    _extra2: LAYOUT__401,
    _extra3: LAYOUT__402,
    _extra4: LAYOUT__406,
    _extra5: LAYOUT__407,
    _extra6: LAYOUT__411,
    _extra7: LAYOUT__412,
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
pub const LAYOUT__599: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__395,
    _0: LAYOUT__568,
};
pub const LAYOUT__598: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 100 },
    },
    _0: LAYOUT__599,
};
pub const LAYOUT__601: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__400,
    _0: LAYOUT__571,
};
pub const LAYOUT__600: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 101 },
    },
    _0: LAYOUT__601,
};
pub const LAYOUT__603: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__405,
    _0: LAYOUT__579,
};
pub const LAYOUT__602: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 102 },
    },
    _0: LAYOUT__603,
};
pub const LAYOUT__605: &MemoryWriteUnconstrainedLayout = &MemoryWriteUnconstrainedLayout {
    io: LAYOUT__410,
    _0: LAYOUT__585,
};
pub const LAYOUT__604: &ECallHostReadWords__0_SuperLayout = &ECallHostReadWords__0_SuperLayout {
    addr: &NondetRegLayout {
        _super: &Reg { offset: 103 },
    },
    _0: LAYOUT__605,
};
pub const LAYOUT__597: &ECallHostReadWords__0_SuperLayout4LayoutArray =
    &[LAYOUT__598, LAYOUT__600, LAYOUT__602, LAYOUT__604];
pub const LAYOUT__596: &ECallHostReadWordsLayout = &ECallHostReadWordsLayout {
    len_decomp: LAYOUT__587,
    words_decomp: LAYOUT__590,
    _1: LAYOUT__597,
    len_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
};
pub const LAYOUT__595: &ECall0OutputArm5Layout = &ECall0OutputArm5Layout {
    _super: LAYOUT__596,
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
pub const LAYOUT__606: &ECall0OutputArm6Layout = &ECall0OutputArm6Layout {
    _extra0: LAYOUT__396,
    _extra1: LAYOUT__397,
    _extra2: LAYOUT__401,
    _extra3: LAYOUT__402,
    _extra4: LAYOUT__406,
    _extra5: LAYOUT__407,
    _extra6: LAYOUT__411,
    _extra7: LAYOUT__412,
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
pub const LAYOUT__607: &ECall0OutputArm7Layout = &ECall0OutputArm7Layout {
    _extra0: LAYOUT__396,
    _extra1: LAYOUT__397,
    _extra2: LAYOUT__401,
    _extra3: LAYOUT__402,
    _extra4: LAYOUT__406,
    _extra5: LAYOUT__407,
    _extra6: LAYOUT__411,
    _extra7: LAYOUT__412,
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
pub const LAYOUT__564: &ECall0OutputLayout = &ECall0OutputLayout {
    arm0: LAYOUT__565,
    arm1: LAYOUT__575,
    arm2: LAYOUT__577,
    arm3: LAYOUT__593,
    arm4: LAYOUT__594,
    arm5: LAYOUT__595,
    arm6: LAYOUT__606,
    arm7: LAYOUT__607,
};
pub const LAYOUT__609: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 110 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 111 },
        },
    },
};
pub const LAYOUT__608: &NormalizeU32Layout = &NormalizeU32Layout {
    low16: LAYOUT__609,
    low_carry: &NondetRegLayout {
        _super: &Reg { offset: 112 },
    },
    high16: LAYOUT__485,
    high_carry: &NondetRegLayout {
        _super: &Reg { offset: 115 },
    },
};
pub const LAYOUT__556: &ECall0Layout = &ECall0Layout {
    s0: &NondetRegLayout {
        _super: &Reg { offset: 71 },
    },
    s1: &NondetRegLayout {
        _super: &Reg { offset: 72 },
    },
    s2: &NondetRegLayout {
        _super: &Reg { offset: 73 },
    },
    pc_addr: LAYOUT__557,
    _arguments_e_call0_output: LAYOUT__560,
    output: LAYOUT__564,
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
    add_pc: LAYOUT__608,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 116 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
};
pub const LAYOUT__612: &NondetRegLayout24LayoutArray = &[
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
pub const LAYOUT__611: &PoseidonStateLayout = &PoseidonStateLayout {
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
    inner: LAYOUT__612,
    zcheck: &NondetExtRegLayout {
        _super: &Reg { offset: 62 },
    },
};
pub const LAYOUT__615: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__616: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__617: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__618: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__619: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__620: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__621: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__622: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__623: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__624: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__625: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__626: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__627: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__628: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__629: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__630: &MemoryArgLayout = &MemoryArgLayout {
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
pub const LAYOUT__614: &MemoryArgLayout16LayoutArray = &[
    LAYOUT__615,
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
];
pub const LAYOUT__631: &CycleArgLayout8LayoutArray = &[
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
pub const LAYOUT__632: &ArgU16Layout16LayoutArray = &[
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
pub const LAYOUT__633: &ArgU8Layout2LayoutArray = &[
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
pub const LAYOUT__613: &_Arguments_Poseidon0StateLayout = &_Arguments_Poseidon0StateLayout {
    memory_arg: LAYOUT__614,
    cycle_arg: LAYOUT__631,
    arg_u16: LAYOUT__632,
    arg_u8: LAYOUT__633,
};
pub const LAYOUT__638: &PoseidonEntry_SuperArm0Layout = &PoseidonEntry_SuperArm0Layout {
    _super: LAYOUT__611,
    _extra0: LAYOUT__615,
    _extra1: LAYOUT__616,
    _extra2: LAYOUT__617,
    _extra3: LAYOUT__618,
    _extra4: LAYOUT__619,
    _extra5: LAYOUT__620,
    _extra6: LAYOUT__621,
    _extra7: LAYOUT__622,
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
pub const LAYOUT__642: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__615,
    new_txn: LAYOUT__616,
};
pub const LAYOUT__644: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
};
pub const LAYOUT__643: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__644 };
pub const LAYOUT__641: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__642,
    _0: LAYOUT__643,
};
pub const LAYOUT__640: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__641,
};
pub const LAYOUT__647: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__617,
    new_txn: LAYOUT__618,
};
pub const LAYOUT__649: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
};
pub const LAYOUT__648: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__649 };
pub const LAYOUT__646: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__647,
    _0: LAYOUT__648,
};
pub const LAYOUT__645: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__646,
};
pub const LAYOUT__652: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__619,
    new_txn: LAYOUT__620,
};
pub const LAYOUT__654: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
};
pub const LAYOUT__653: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__654 };
pub const LAYOUT__651: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__652,
    _0: LAYOUT__653,
};
pub const LAYOUT__650: &ReadAddrLayout = &ReadAddrLayout {
    addr32: LAYOUT__651,
};
pub const LAYOUT__656: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__621,
    new_txn: LAYOUT__622,
};
pub const LAYOUT__658: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
};
pub const LAYOUT__657: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__658 };
pub const LAYOUT__655: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__656,
    _0: LAYOUT__657,
};
pub const LAYOUT__639: &PoseidonEcallLayout = &PoseidonEcallLayout {
    _super: LAYOUT__611,
    state_addr: LAYOUT__640,
    buf_in_addr: LAYOUT__645,
    buf_out_addr: LAYOUT__650,
    bits_and_count: LAYOUT__655,
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
pub const LAYOUT__637: &PoseidonEntry_SuperLayout = &PoseidonEntry_SuperLayout {
    _super: LAYOUT__611,
    arm0: LAYOUT__638,
    arm1: LAYOUT__639,
};
pub const LAYOUT__660: &MemoryArgLayout8LayoutArray = &[
    LAYOUT__615,
    LAYOUT__616,
    LAYOUT__617,
    LAYOUT__618,
    LAYOUT__619,
    LAYOUT__620,
    LAYOUT__621,
    LAYOUT__622,
];
pub const LAYOUT__661: &CycleArgLayout4LayoutArray = &[
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
pub const LAYOUT__659: &_Arguments_PoseidonEntry_SuperLayout =
    &_Arguments_PoseidonEntry_SuperLayout {
        memory_arg: LAYOUT__660,
        cycle_arg: LAYOUT__661,
    };
pub const LAYOUT__636: &PoseidonEntryLayout = &PoseidonEntryLayout {
    _super: LAYOUT__637,
    pc_zero: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 188 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 189 },
        },
    },
    _arguments_poseidon_entry__super: LAYOUT__659,
};
pub const LAYOUT__635: &Poseidon0StateArm0Layout = &Poseidon0StateArm0Layout {
    _super: LAYOUT__636,
    _extra0: LAYOUT__623,
    _extra1: LAYOUT__624,
    _extra2: LAYOUT__625,
    _extra3: LAYOUT__626,
    _extra4: LAYOUT__627,
    _extra5: LAYOUT__628,
    _extra6: LAYOUT__629,
    _extra7: LAYOUT__630,
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
pub const LAYOUT__665: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__641,
};
pub const LAYOUT__666: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__646,
};
pub const LAYOUT__667: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__651,
};
pub const LAYOUT__668: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__655,
};
pub const LAYOUT__671: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__623,
    new_txn: LAYOUT__624,
};
pub const LAYOUT__673: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__672: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__673 };
pub const LAYOUT__670: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__671,
    _0: LAYOUT__672,
};
pub const LAYOUT__669: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__670,
};
pub const LAYOUT__676: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__625,
    new_txn: LAYOUT__626,
};
pub const LAYOUT__678: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__677: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__678 };
pub const LAYOUT__675: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__676,
    _0: LAYOUT__677,
};
pub const LAYOUT__674: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__675,
};
pub const LAYOUT__681: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__627,
    new_txn: LAYOUT__628,
};
pub const LAYOUT__683: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__682: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__683 };
pub const LAYOUT__680: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__681,
    _0: LAYOUT__682,
};
pub const LAYOUT__679: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__680,
};
pub const LAYOUT__686: &MemoryIOLayout = &MemoryIOLayout {
    old_txn: LAYOUT__629,
    new_txn: LAYOUT__630,
};
pub const LAYOUT__688: &IsCycleLayout = &IsCycleLayout {
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__687: &IsForwardLayout = &IsForwardLayout { _0: LAYOUT__688 };
pub const LAYOUT__685: &MemoryReadLayout = &MemoryReadLayout {
    io: LAYOUT__686,
    _0: LAYOUT__687,
};
pub const LAYOUT__684: &ReadElemLayout = &ReadElemLayout {
    elem32: LAYOUT__685,
};
pub const LAYOUT__664: &ReadElemLayout8LayoutArray = &[
    LAYOUT__665,
    LAYOUT__666,
    LAYOUT__667,
    LAYOUT__668,
    LAYOUT__669,
    LAYOUT__674,
    LAYOUT__679,
    LAYOUT__684,
];
pub const LAYOUT__663: &PoseidonLoadStateLayout = &PoseidonLoadStateLayout {
    _super: LAYOUT__611,
    load_list: LAYOUT__664,
};
pub const LAYOUT__662: &Poseidon0StateArm1Layout = &Poseidon0StateArm1Layout {
    _super: LAYOUT__663,
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
pub const LAYOUT__693: &OneHot_3_Layout = &OneHot_3_Layout {
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
pub const LAYOUT__698: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__642 };
pub const LAYOUT__697: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__698,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    },
};
pub const LAYOUT__699: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__642,
    _0: LAYOUT__643,
};
pub const LAYOUT__696: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__641,
    arm1: LAYOUT__697,
    arm2: LAYOUT__699,
};
pub const LAYOUT__701: &MemoryArgLayout2LayoutArray = &[LAYOUT__615, LAYOUT__616];
pub const LAYOUT__700: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__701,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 130 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 131 },
        },
    }],
};
pub const LAYOUT__695: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__696,
    _arguments_memory_get__super: LAYOUT__700,
};
pub const LAYOUT__705: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__647 };
pub const LAYOUT__704: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__705,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    },
};
pub const LAYOUT__706: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__647,
    _0: LAYOUT__648,
};
pub const LAYOUT__703: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__646,
    arm1: LAYOUT__704,
    arm2: LAYOUT__706,
};
pub const LAYOUT__708: &MemoryArgLayout2LayoutArray = &[LAYOUT__617, LAYOUT__618];
pub const LAYOUT__707: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__708,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 132 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 133 },
        },
    }],
};
pub const LAYOUT__702: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__703,
    _arguments_memory_get__super: LAYOUT__707,
};
pub const LAYOUT__712: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__652 };
pub const LAYOUT__711: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__712,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    },
};
pub const LAYOUT__713: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__652,
    _0: LAYOUT__653,
};
pub const LAYOUT__710: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__651,
    arm1: LAYOUT__711,
    arm2: LAYOUT__713,
};
pub const LAYOUT__715: &MemoryArgLayout2LayoutArray = &[LAYOUT__619, LAYOUT__620];
pub const LAYOUT__714: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__715,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 134 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 135 },
        },
    }],
};
pub const LAYOUT__709: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__710,
    _arguments_memory_get__super: LAYOUT__714,
};
pub const LAYOUT__719: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__656 };
pub const LAYOUT__718: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__719,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    },
};
pub const LAYOUT__720: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__656,
    _0: LAYOUT__657,
};
pub const LAYOUT__717: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__655,
    arm1: LAYOUT__718,
    arm2: LAYOUT__720,
};
pub const LAYOUT__722: &MemoryArgLayout2LayoutArray = &[LAYOUT__621, LAYOUT__622];
pub const LAYOUT__721: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__722,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 136 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 137 },
        },
    }],
};
pub const LAYOUT__716: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__717,
    _arguments_memory_get__super: LAYOUT__721,
};
pub const LAYOUT__726: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__671 };
pub const LAYOUT__725: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__726,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    },
};
pub const LAYOUT__727: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__671,
    _0: LAYOUT__672,
};
pub const LAYOUT__724: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__670,
    arm1: LAYOUT__725,
    arm2: LAYOUT__727,
};
pub const LAYOUT__729: &MemoryArgLayout2LayoutArray = &[LAYOUT__623, LAYOUT__624];
pub const LAYOUT__728: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__729,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 138 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 139 },
        },
    }],
};
pub const LAYOUT__723: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__724,
    _arguments_memory_get__super: LAYOUT__728,
};
pub const LAYOUT__733: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__676 };
pub const LAYOUT__732: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__733,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    },
};
pub const LAYOUT__734: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__676,
    _0: LAYOUT__677,
};
pub const LAYOUT__731: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__675,
    arm1: LAYOUT__732,
    arm2: LAYOUT__734,
};
pub const LAYOUT__736: &MemoryArgLayout2LayoutArray = &[LAYOUT__625, LAYOUT__626];
pub const LAYOUT__735: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__736,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 140 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 141 },
        },
    }],
};
pub const LAYOUT__730: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__731,
    _arguments_memory_get__super: LAYOUT__735,
};
pub const LAYOUT__740: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__681 };
pub const LAYOUT__739: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__740,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    },
};
pub const LAYOUT__741: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__681,
    _0: LAYOUT__682,
};
pub const LAYOUT__738: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__680,
    arm1: LAYOUT__739,
    arm2: LAYOUT__741,
};
pub const LAYOUT__743: &MemoryArgLayout2LayoutArray = &[LAYOUT__627, LAYOUT__628];
pub const LAYOUT__742: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__743,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 142 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 143 },
        },
    }],
};
pub const LAYOUT__737: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__738,
    _arguments_memory_get__super: LAYOUT__742,
};
pub const LAYOUT__747: &MemoryPageInLayout = &MemoryPageInLayout { io: LAYOUT__686 };
pub const LAYOUT__746: &MemoryGet_SuperArm1Layout = &MemoryGet_SuperArm1Layout {
    _super: LAYOUT__747,
    _extra0: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    },
};
pub const LAYOUT__748: &MemoryPageOutLayout = &MemoryPageOutLayout {
    io: LAYOUT__686,
    _0: LAYOUT__687,
};
pub const LAYOUT__745: &MemoryGet_SuperLayout = &MemoryGet_SuperLayout {
    arm0: LAYOUT__685,
    arm1: LAYOUT__746,
    arm2: LAYOUT__748,
};
pub const LAYOUT__750: &MemoryArgLayout2LayoutArray = &[LAYOUT__629, LAYOUT__630];
pub const LAYOUT__749: &_Arguments_MemoryGet_SuperLayout = &_Arguments_MemoryGet_SuperLayout {
    memory_arg: LAYOUT__750,
    cycle_arg: &[&CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 144 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 145 },
        },
    }],
};
pub const LAYOUT__744: &MemoryGetLayout = &MemoryGetLayout {
    _super: LAYOUT__745,
    _arguments_memory_get__super: LAYOUT__749,
};
pub const LAYOUT__694: &MemoryGetLayout8LayoutArray = &[
    LAYOUT__695,
    LAYOUT__702,
    LAYOUT__709,
    LAYOUT__716,
    LAYOUT__723,
    LAYOUT__730,
    LAYOUT__737,
    LAYOUT__744,
];
pub const LAYOUT__692: &PoseidonLoadInShortLayout = &PoseidonLoadInShortLayout {
    _super: LAYOUT__611,
    tx_type: LAYOUT__693,
    load_list: LAYOUT__694,
};
pub const LAYOUT__751: &PoseidonLoadInLowLayout = &PoseidonLoadInLowLayout {
    _super: LAYOUT__611,
    tx_type: LAYOUT__693,
    load_list: LAYOUT__694,
};
pub const LAYOUT__752: &PoseidonLoadInHighLayout = &PoseidonLoadInHighLayout {
    _super: LAYOUT__611,
    tx_type: LAYOUT__693,
    load_list: LAYOUT__694,
};
pub const LAYOUT__691: &PoseidonLoadIn_SuperLayout = &PoseidonLoadIn_SuperLayout {
    _super: LAYOUT__611,
    arm0: LAYOUT__692,
    arm1: LAYOUT__751,
    arm2: LAYOUT__752,
};
pub const LAYOUT__753: &OneHot_3_Layout = &OneHot_3_Layout {
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
pub const LAYOUT__754: &_Arguments_PoseidonLoadIn_SuperLayout =
    &_Arguments_PoseidonLoadIn_SuperLayout {
        memory_arg: LAYOUT__614,
        cycle_arg: LAYOUT__631,
    };
pub const LAYOUT__690: &PoseidonLoadInLayout = &PoseidonLoadInLayout {
    _super: LAYOUT__691,
    _0: LAYOUT__753,
    _arguments_poseidon_load_in__super: LAYOUT__754,
};
pub const LAYOUT__689: &Poseidon0StateArm2Layout = &Poseidon0StateArm2Layout {
    _super: LAYOUT__690,
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
pub const LAYOUT__755: &Poseidon0StateArm3Layout = &Poseidon0StateArm3Layout {
    _super: LAYOUT__611,
    _extra0: LAYOUT__615,
    _extra1: LAYOUT__616,
    _extra2: LAYOUT__617,
    _extra3: LAYOUT__618,
    _extra4: LAYOUT__619,
    _extra5: LAYOUT__620,
    _extra6: LAYOUT__621,
    _extra7: LAYOUT__622,
    _extra8: LAYOUT__623,
    _extra9: LAYOUT__624,
    _extra10: LAYOUT__625,
    _extra11: LAYOUT__626,
    _extra12: LAYOUT__627,
    _extra13: LAYOUT__628,
    _extra14: LAYOUT__629,
    _extra15: LAYOUT__630,
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
pub const LAYOUT__756: &Poseidon0StateArm4Layout = &Poseidon0StateArm4Layout {
    _super: LAYOUT__611,
    _extra0: LAYOUT__615,
    _extra1: LAYOUT__616,
    _extra2: LAYOUT__617,
    _extra3: LAYOUT__618,
    _extra4: LAYOUT__619,
    _extra5: LAYOUT__620,
    _extra6: LAYOUT__621,
    _extra7: LAYOUT__622,
    _extra8: LAYOUT__623,
    _extra9: LAYOUT__624,
    _extra10: LAYOUT__625,
    _extra11: LAYOUT__626,
    _extra12: LAYOUT__627,
    _extra13: LAYOUT__628,
    _extra14: LAYOUT__629,
    _extra15: LAYOUT__630,
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
pub const LAYOUT__763: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__665 };
pub const LAYOUT__764: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__666 };
pub const LAYOUT__765: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__667 };
pub const LAYOUT__766: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__668 };
pub const LAYOUT__767: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__669 };
pub const LAYOUT__768: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__674 };
pub const LAYOUT__769: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__679 };
pub const LAYOUT__770: &PoseidonCheckOut__0_SuperLayout =
    &PoseidonCheckOut__0_SuperLayout { goal: LAYOUT__684 };
pub const LAYOUT__762: &PoseidonCheckOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__763,
    LAYOUT__764,
    LAYOUT__765,
    LAYOUT__766,
    LAYOUT__767,
    LAYOUT__768,
    LAYOUT__769,
    LAYOUT__770,
];
pub const LAYOUT__761: &PoseidonCheckOutLayout = &PoseidonCheckOutLayout {
    _super: LAYOUT__611,
    _1: LAYOUT__762,
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
pub const LAYOUT__760: &PoseidonDoOut_SuperArm0Layout = &PoseidonDoOut_SuperArm0Layout {
    _super: LAYOUT__761,
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
pub const LAYOUT__774: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 146 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 147 },
        },
    },
};
pub const LAYOUT__776: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 148 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 149 },
        },
    },
};
pub const LAYOUT__775: &U16RegLayout = &U16RegLayout { ret: LAYOUT__776 };
pub const LAYOUT__777: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__642,
    _0: LAYOUT__643,
};
pub const LAYOUT__773: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__774,
    high: LAYOUT__775,
    _0: LAYOUT__777,
};
pub const LAYOUT__779: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 150 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 151 },
        },
    },
};
pub const LAYOUT__781: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 152 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 153 },
        },
    },
};
pub const LAYOUT__780: &U16RegLayout = &U16RegLayout { ret: LAYOUT__781 };
pub const LAYOUT__782: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__647,
    _0: LAYOUT__648,
};
pub const LAYOUT__778: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__779,
    high: LAYOUT__780,
    _0: LAYOUT__782,
};
pub const LAYOUT__784: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 154 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 155 },
        },
    },
};
pub const LAYOUT__785: &U16RegLayout = &U16RegLayout { ret: LAYOUT__202 };
pub const LAYOUT__786: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__652,
    _0: LAYOUT__653,
};
pub const LAYOUT__783: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__784,
    high: LAYOUT__785,
    _0: LAYOUT__786,
};
pub const LAYOUT__788: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 158 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 159 },
        },
    },
};
pub const LAYOUT__790: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 160 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 161 },
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
            _super: &Reg { offset: 162 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 163 },
        },
    },
};
pub const LAYOUT__795: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 164 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 165 },
        },
    },
};
pub const LAYOUT__794: &U16RegLayout = &U16RegLayout { ret: LAYOUT__795 };
pub const LAYOUT__796: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__671,
    _0: LAYOUT__672,
};
pub const LAYOUT__792: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__793,
    high: LAYOUT__794,
    _0: LAYOUT__796,
};
pub const LAYOUT__799: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 168 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 169 },
        },
    },
};
pub const LAYOUT__798: &U16RegLayout = &U16RegLayout { ret: LAYOUT__799 };
pub const LAYOUT__800: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__676,
    _0: LAYOUT__677,
};
pub const LAYOUT__797: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__288,
    high: LAYOUT__798,
    _0: LAYOUT__800,
};
pub const LAYOUT__802: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 170 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 171 },
        },
    },
};
pub const LAYOUT__804: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 172 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 173 },
        },
    },
};
pub const LAYOUT__803: &U16RegLayout = &U16RegLayout { ret: LAYOUT__804 };
pub const LAYOUT__805: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__681,
    _0: LAYOUT__682,
};
pub const LAYOUT__801: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__802,
    high: LAYOUT__803,
    _0: LAYOUT__805,
};
pub const LAYOUT__807: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 174 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 175 },
        },
    },
};
pub const LAYOUT__809: &NondetU16RegLayout = &NondetU16RegLayout {
    arg: &ArgU16Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 176 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 177 },
        },
    },
};
pub const LAYOUT__808: &U16RegLayout = &U16RegLayout { ret: LAYOUT__809 };
pub const LAYOUT__810: &MemoryWriteLayout = &MemoryWriteLayout {
    io: LAYOUT__686,
    _0: LAYOUT__687,
};
pub const LAYOUT__806: &PoseidonStoreOut__0_SuperLayout = &PoseidonStoreOut__0_SuperLayout {
    low: LAYOUT__807,
    high: LAYOUT__808,
    _0: LAYOUT__810,
};
pub const LAYOUT__772: &PoseidonStoreOut__0_SuperLayout8LayoutArray = &[
    LAYOUT__773,
    LAYOUT__778,
    LAYOUT__783,
    LAYOUT__787,
    LAYOUT__792,
    LAYOUT__797,
    LAYOUT__801,
    LAYOUT__806,
];
pub const LAYOUT__771: &PoseidonStoreOutLayout = &PoseidonStoreOutLayout {
    _super: LAYOUT__611,
    _1: LAYOUT__772,
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
pub const LAYOUT__759: &PoseidonDoOut_SuperLayout = &PoseidonDoOut_SuperLayout {
    _super: LAYOUT__611,
    arm0: LAYOUT__760,
    arm1: LAYOUT__771,
};
pub const LAYOUT__811: &_Arguments_PoseidonDoOut_SuperLayout =
    &_Arguments_PoseidonDoOut_SuperLayout {
        memory_arg: LAYOUT__614,
        cycle_arg: LAYOUT__631,
        arg_u16: LAYOUT__632,
    };
pub const LAYOUT__758: &PoseidonDoOutLayout = &PoseidonDoOutLayout {
    _super: LAYOUT__759,
    _arguments_poseidon_do_out__super: LAYOUT__811,
};
pub const LAYOUT__757: &Poseidon0StateArm5Layout = &Poseidon0StateArm5Layout {
    _super: LAYOUT__758,
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
pub const LAYOUT__814: &PoseidonPaging_SuperLayout = &PoseidonPaging_SuperLayout {
    _super: LAYOUT__611,
    arm0: LAYOUT__611,
    arm1: LAYOUT__611,
    arm2: LAYOUT__611,
    arm3: LAYOUT__611,
    arm4: LAYOUT__611,
    arm5: LAYOUT__611,
};
pub const LAYOUT__816: &NondetRegLayout6LayoutArray = &[
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
pub const LAYOUT__815: &OneHot_6_Layout = &OneHot_6_Layout {
    _super: LAYOUT__816,
};
pub const LAYOUT__819: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 178 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 179 },
        },
    },
};
pub const LAYOUT__818: &U8RegLayout = &U8RegLayout { ret: LAYOUT__819 };
pub const LAYOUT__817: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__774,
    _0: LAYOUT__818,
};
pub const LAYOUT__820: &_Arguments_PoseidonPaging__1Layout = &_Arguments_PoseidonPaging__1Layout {
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
pub const LAYOUT__825: &NondetU8RegLayout = &NondetU8RegLayout {
    arg: &ArgU8Layout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 180 },
        },
        val: &NondetRegLayout {
            _super: &Reg { offset: 181 },
        },
    },
};
pub const LAYOUT__824: &U8RegLayout = &U8RegLayout { ret: LAYOUT__825 };
pub const LAYOUT__823: &IsU24Layout = &IsU24Layout {
    low16: LAYOUT__776,
    _0: LAYOUT__824,
};
pub const LAYOUT__822: &PoseidonPaging__1Arm0_SuperLayout =
    &PoseidonPaging__1Arm0_SuperLayout { _0: LAYOUT__823 };
pub const LAYOUT__826: &PoseidonPaging__1Arm1_SuperLayout =
    &PoseidonPaging__1Arm1_SuperLayout { _0: LAYOUT__823 };
pub const LAYOUT__821: &PoseidonPaging__1Layout = &PoseidonPaging__1Layout {
    arm0: LAYOUT__822,
    arm1: LAYOUT__826,
};
pub const LAYOUT__813: &PoseidonPagingLayout = &PoseidonPagingLayout {
    _super: LAYOUT__814,
    cur_idx: &NondetRegLayout {
        _super: &Reg { offset: 182 },
    },
    cur_mode: &NondetRegLayout {
        _super: &Reg { offset: 183 },
    },
    mode_split: LAYOUT__815,
    _0: LAYOUT__817,
    _arguments_poseidon_paging__1: LAYOUT__820,
    _3: LAYOUT__821,
    _4: &NondetRegLayout {
        _super: &Reg { offset: 190 },
    },
};
pub const LAYOUT__812: &Poseidon0StateArm6Layout = &Poseidon0StateArm6Layout {
    _super: LAYOUT__813,
    _extra0: LAYOUT__615,
    _extra1: LAYOUT__616,
    _extra2: LAYOUT__617,
    _extra3: LAYOUT__618,
    _extra4: LAYOUT__619,
    _extra5: LAYOUT__620,
    _extra6: LAYOUT__621,
    _extra7: LAYOUT__622,
    _extra8: LAYOUT__623,
    _extra9: LAYOUT__624,
    _extra10: LAYOUT__625,
    _extra11: LAYOUT__626,
    _extra12: LAYOUT__627,
    _extra13: LAYOUT__628,
    _extra14: LAYOUT__629,
    _extra15: LAYOUT__630,
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
pub const LAYOUT__830: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__774,
    high: LAYOUT__775,
    _0: LAYOUT__777,
};
pub const LAYOUT__831: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__779,
    high: LAYOUT__780,
    _0: LAYOUT__782,
};
pub const LAYOUT__832: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__784,
    high: LAYOUT__785,
    _0: LAYOUT__786,
};
pub const LAYOUT__833: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__788,
    high: LAYOUT__789,
    _0: LAYOUT__791,
};
pub const LAYOUT__834: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__793,
    high: LAYOUT__794,
    _0: LAYOUT__796,
};
pub const LAYOUT__835: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__288,
    high: LAYOUT__798,
    _0: LAYOUT__800,
};
pub const LAYOUT__836: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__802,
    high: LAYOUT__803,
    _0: LAYOUT__805,
};
pub const LAYOUT__837: &PoseidonStoreState__0_SuperLayout = &PoseidonStoreState__0_SuperLayout {
    low: LAYOUT__807,
    high: LAYOUT__808,
    _0: LAYOUT__810,
};
pub const LAYOUT__829: &PoseidonStoreState__0_SuperLayout8LayoutArray = &[
    LAYOUT__830,
    LAYOUT__831,
    LAYOUT__832,
    LAYOUT__833,
    LAYOUT__834,
    LAYOUT__835,
    LAYOUT__836,
    LAYOUT__837,
];
pub const LAYOUT__828: &PoseidonStoreStateLayout = &PoseidonStoreStateLayout {
    _super: LAYOUT__611,
    _1: LAYOUT__829,
};
pub const LAYOUT__827: &Poseidon0StateArm7Layout = &Poseidon0StateArm7Layout {
    _super: LAYOUT__828,
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
pub const LAYOUT__634: &Poseidon0StateLayout = &Poseidon0StateLayout {
    _super: LAYOUT__611,
    arm0: LAYOUT__635,
    arm1: LAYOUT__662,
    arm2: LAYOUT__689,
    arm3: LAYOUT__755,
    arm4: LAYOUT__756,
    arm5: LAYOUT__757,
    arm6: LAYOUT__812,
    arm7: LAYOUT__827,
};
pub const LAYOUT__610: &Poseidon0Layout = &Poseidon0Layout {
    state: LAYOUT__611,
    _arguments_poseidon0_state: LAYOUT__613,
    state_redef: LAYOUT__634,
    arg: &CycleArgLayout {
        count: &NondetRegLayout {
            _super: &Reg { offset: 191 },
        },
        cycle: &NondetRegLayout {
            _super: &Reg { offset: 0 },
        },
    },
};
pub const LAYOUT__843: &SBoxLayout24LayoutArray = &[
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
pub const LAYOUT__842: &DoExtRoundLayout = &DoExtRoundLayout { _1: LAYOUT__843 };
pub const LAYOUT__845: &NondetRegLayout8LayoutArray = &[
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
pub const LAYOUT__844: &OneHot_8_Layout = &OneHot_8_Layout {
    _super: LAYOUT__845,
};
pub const LAYOUT__841: &DoExtRoundByIdxLayout = &DoExtRoundByIdxLayout {
    _super: LAYOUT__842,
    idx_hot: LAYOUT__844,
};
pub const LAYOUT__840: &PoseidonExtRoundLayout = &PoseidonExtRoundLayout {
    _super: LAYOUT__611,
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
    next_inner: LAYOUT__841,
};
pub const LAYOUT__849: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 66 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 67 },
        },
    },
};
pub const LAYOUT__850: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 68 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 69 },
        },
    },
};
pub const LAYOUT__851: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 70 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 71 },
        },
    },
};
pub const LAYOUT__852: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 72 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 73 },
        },
    },
};
pub const LAYOUT__853: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 74 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 75 },
        },
    },
};
pub const LAYOUT__854: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 76 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 77 },
        },
    },
};
pub const LAYOUT__855: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 78 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 79 },
        },
    },
};
pub const LAYOUT__856: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 80 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 81 },
        },
    },
};
pub const LAYOUT__857: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 82 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 83 },
        },
    },
};
pub const LAYOUT__858: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 84 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 85 },
        },
    },
};
pub const LAYOUT__859: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 86 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 87 },
        },
    },
};
pub const LAYOUT__860: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 88 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 89 },
        },
    },
};
pub const LAYOUT__861: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 90 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 91 },
        },
    },
};
pub const LAYOUT__862: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 92 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 93 },
        },
    },
};
pub const LAYOUT__863: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 94 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 95 },
        },
    },
};
pub const LAYOUT__864: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 96 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 97 },
        },
    },
};
pub const LAYOUT__865: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 98 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 99 },
        },
    },
};
pub const LAYOUT__866: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 100 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 101 },
        },
    },
};
pub const LAYOUT__867: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 102 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 103 },
        },
    },
};
pub const LAYOUT__868: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 104 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 105 },
        },
    },
};
pub const LAYOUT__869: &DoIntRoundLayout = &DoIntRoundLayout {
    sbox: &SBoxLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 106 },
        },
        cubed: &NondetRegLayout {
            _super: &Reg { offset: 107 },
        },
    },
};
pub const LAYOUT__848: &DoIntRoundLayout21LayoutArray = &[
    LAYOUT__849,
    LAYOUT__850,
    LAYOUT__851,
    LAYOUT__852,
    LAYOUT__853,
    LAYOUT__854,
    LAYOUT__855,
    LAYOUT__856,
    LAYOUT__857,
    LAYOUT__858,
    LAYOUT__859,
    LAYOUT__860,
    LAYOUT__861,
    LAYOUT__862,
    LAYOUT__863,
    LAYOUT__864,
    LAYOUT__865,
    LAYOUT__866,
    LAYOUT__867,
    LAYOUT__868,
    LAYOUT__869,
];
pub const LAYOUT__847: &DoIntRoundsLayout = &DoIntRoundsLayout {
    _super: LAYOUT__848,
};
pub const LAYOUT__846: &PoseidonIntRoundsLayout = &PoseidonIntRoundsLayout {
    _super: LAYOUT__611,
    next_inner: LAYOUT__847,
};
pub const LAYOUT__839: &Poseidon1StateLayout = &Poseidon1StateLayout {
    _super: LAYOUT__611,
    arm0: LAYOUT__840,
    arm1: LAYOUT__846,
    arm2: LAYOUT__611,
    arm3: LAYOUT__611,
    arm4: LAYOUT__611,
    arm5: LAYOUT__611,
    arm6: LAYOUT__611,
    arm7: LAYOUT__611,
};
pub const LAYOUT__838: &Poseidon1Layout = &Poseidon1Layout {
    state: LAYOUT__611,
    state_redef: LAYOUT__839,
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
    arm6: LAYOUT__349,
    arm7: LAYOUT__388,
    arm8: LAYOUT__556,
    arm9: LAYOUT__610,
    arm10: LAYOUT__838,
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
pub const LAYOUT__871: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__870: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__871,
};
pub const LAYOUT__873: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__872: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__873,
};
pub const LAYOUT__875: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__874: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__875,
};
pub const LAYOUT__877: &DigestRegValues_SuperLayout8LayoutArray = &[
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
pub const LAYOUT__876: &DigestRegLayout = &DigestRegLayout {
    values: LAYOUT__877,
};
pub const LAYOUT__878: &_accumLayout = &_accumLayout {
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
    input: LAYOUT__870,
    is_terminate: &NondetRegLayout {
        _super: &Reg { offset: 16 },
    },
    output: LAYOUT__872,
    rng: &NondetExtRegLayout {
        _super: &Reg { offset: 33 },
    },
    state_in: LAYOUT__874,
    state_out: LAYOUT__876,
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
    randomness: LAYOUT__878,
};
