struct NondetRegLayout {
  Reg _super;
};
using NondetRegLayout2LayoutArray = std::array<NondetRegLayout, 2>;
struct OneHotLayout {
  NondetRegLayout2LayoutArray _super;
};
struct TopResultLayout {
  NondetRegLayout _super;
  NondetRegLayout arm0;
  NondetRegLayout arm1;
};
struct TopLayout {
  NondetRegLayout op;
  NondetRegLayout arg1;
  NondetRegLayout arg2;
  NondetRegLayout expected;
  OneHotLayout _0;
  TopResultLayout result;
};
struct _globalLayout {
  NondetRegLayout result;
};
struct NondetRegStruct {
  Val _super;
};
using Val2Array = std::array<Val, 2>;
using NondetRegStruct2Array = std::array<NondetRegStruct, 2>;
struct OneHotStruct {
  NondetRegStruct2Array _super;
};
struct TopStruct {
};
