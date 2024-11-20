constexpr TopLayout kLayout_Top = TopLayout{
    .op = NondetRegLayout{._super = /*offset=*/0},
    .arg1 = NondetRegLayout{._super = /*offset=*/1},
    .arg2 = NondetRegLayout{._super = /*offset=*/2},
    .expected = NondetRegLayout{._super = /*offset=*/3},
    ._0 = OneHotLayout{._super =
                           NondetRegLayout2LayoutArray{NondetRegLayout{._super = /*offset=*/4},
                                                       NondetRegLayout{._super = /*offset=*/5}}},
    .result = TopResultLayout{._super = NondetRegLayout{._super = /*offset=*/6},
                              .arm0 = NondetRegLayout{._super = /*offset=*/6},
                              .arm1 = NondetRegLayout{._super = /*offset=*/6}}};
constexpr _globalLayout kLayoutGlobal =
    _globalLayout{.result = NondetRegLayout{._super = /*offset=*/0}};
