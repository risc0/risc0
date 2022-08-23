// This code is automatically generated

use crate::taps::{RegisterGroup, Tap, TapData, TapSet};

#[allow(dead_code)]
pub(crate) const TAPS: &[Tap] = &[
    Tap::new(RegisterGroup::Code, 0, 0, 1),
    Tap::new(RegisterGroup::Data, 0, 0, 4),
    Tap::new(RegisterGroup::Code, 1, 0, 2),
    Tap::new(RegisterGroup::Data, 0, 1, 5),
    Tap::new(RegisterGroup::Data, 0, 2, 6),
    Tap::new(RegisterGroup::Code, 2, 0, 3),
    Tap::new(RegisterGroup::Accum, 0, 0, 0),
];

pub(crate) const TAPSET: &'static TapSet = &TapSet::<'static> {
    taps: &[
        TapData {
            offset: 0,
            back: 0,
            group: RegisterGroup::Accum,
            combo: 0,
            skip: 1,
        },
        TapData {
            offset: 0,
            back: 0,
            group: RegisterGroup::Code,
            combo: 0,
            skip: 1,
        },
        TapData {
            offset: 1,
            back: 0,
            group: RegisterGroup::Code,
            combo: 0,
            skip: 1,
        },
        TapData {
            offset: 2,
            back: 0,
            group: RegisterGroup::Code,
            combo: 0,
            skip: 1,
        },
        TapData {
            offset: 0,
            back: 0,
            group: RegisterGroup::Data,
            combo: 1,
            skip: 3,
        },
        TapData {
            offset: 0,
            back: 1,
            group: RegisterGroup::Data,
            combo: 1,
            skip: 3,
        },
        TapData {
            offset: 0,
            back: 2,
            group: RegisterGroup::Data,
            combo: 1,
            skip: 3,
        },
    ],
    combo_taps: &[0, 0, 1, 2],
    combo_begin: &[0, 1, 4],
    group_begin: [0, 1, 4, 7],
    combos_count: 2,
};
