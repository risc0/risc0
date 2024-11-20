pub const LAYOUT_TOP: &TopLayout = &TopLayout {
    op: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    arg1: &NondetRegLayout {
        _super: &Reg { offset: 1 },
    },
    arg2: &NondetRegLayout {
        _super: &Reg { offset: 2 },
    },
    expected: &NondetRegLayout {
        _super: &Reg { offset: 3 },
    },
    _0: &OneHotLayout {
        _super: &[
            &NondetRegLayout {
                _super: &Reg { offset: 4 },
            },
            &NondetRegLayout {
                _super: &Reg { offset: 5 },
            },
        ],
    },
    result: &TopResultLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 6 },
        },
        arm0: &NondetRegLayout {
            _super: &Reg { offset: 6 },
        },
        arm1: &NondetRegLayout {
            _super: &Reg { offset: 6 },
        },
    },
};
pub const LAYOUT_GLOBAL: &_globalLayout = &_globalLayout {
    result: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
};
