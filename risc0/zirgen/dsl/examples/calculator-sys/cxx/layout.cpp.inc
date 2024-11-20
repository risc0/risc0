constexpr TopLayout kLayout_Top = TopLayout{
    .op = NondetRegLayout{._super = /*offset=*/0},
    .left = NondetRegLayout{._super = /*offset=*/1},
    .right = NondetRegLayout{._super = /*offset=*/2},
    ._0 = OneHotLayout{._super =
                           NondetRegLayout2LayoutArray{NondetRegLayout{._super = /*offset=*/3},
                                                       NondetRegLayout{._super = /*offset=*/4}}},
    .result = TopResultLayout{._super = NondetRegLayout{._super = /*offset=*/5},
                              .arm0 = NondetRegLayout{._super = /*offset=*/5},
                              .arm1 = NondetRegLayout{._super = /*offset=*/5}}};
constexpr _globalLayout kLayoutGlobal =
    _globalLayout{.result = NondetRegLayout{._super = /*offset=*/0}};
