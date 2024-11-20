NondetRegStruct
back_NondetReg(ExecContext& ctx, Index distance0, BoundLayout<NondetRegLayout> layout1) {
  NondetRegStruct x2 = NondetRegStruct{._super = LOAD(LAYOUT_LOOKUP(layout1, _super), distance0)};
  return x2;
}
NondetRegStruct exec_NondetReg(ExecContext& ctx, Val arg0, BoundLayout<NondetRegLayout> layout1) {
  BoundLayout<Reg> x2 = LAYOUT_LOOKUP(layout1, _super);
  STORE(x2, arg0);
  return NondetRegStruct{._super = LOAD(x2, 0)};
}
NondetRegStruct back_Reg(ExecContext& ctx, Index distance0, BoundLayout<NondetRegLayout> layout1) {
  // Reg(<preamble>:4)
  NondetRegStruct x2 = back_NondetReg(ctx, distance0, layout1);
  return x2;
}
NondetRegStruct exec_Reg(ExecContext& ctx, Val arg0, BoundLayout<NondetRegLayout> layout1) {
  NondetRegStruct x2 = exec_NondetReg(ctx, arg0, layout1);
  // Reg(<preamble>:5)
  EQZ((arg0 - x2._super), "Reg(<preamble>:5)");
  return x2;
}
OneHotStruct exec_OneHot(ExecContext& ctx, Val arg0, BoundLayout<OneHotLayout> layout1) {
  // OneHot(zirgen/dsl/examples/calculator/calculator.zir:13)
  NondetRegStruct2Array x2 =
      map(Val2Array{Val(0), Val(1)},
          LAYOUT_LOOKUP(layout1, _super),
          std::function([&](Val2Array::value_type x3,
                            BoundLayout<NondetRegLayout2LayoutArray::value_type> x4) {
            NondetRegStruct x5 = exec_NondetReg(ctx, isz((x3 - arg0)), x4);
            return x5;
          }));
  // OneHot(zirgen/dsl/examples/calculator/calculator.zir:15)
  Val x6 = x2[0]._super;
  EQZ((x6 * (Val(1) - x6)), "OneHot(zirgen/dsl/examples/calculator/calculator.zir:15)");
  Val x7 = x2[1]._super;
  EQZ((x7 * (Val(1) - x7)), "OneHot(zirgen/dsl/examples/calculator/calculator.zir:15)");
  // OneHot(zirgen/dsl/examples/calculator/calculator.zir:17)
  EQZ(((x6 + x7) - Val(1)), "OneHot(zirgen/dsl/examples/calculator/calculator.zir:17)");
  // OneHot(zirgen/dsl/examples/calculator/calculator.zir:19)
  EQZ((x7 - arg0), "OneHot(zirgen/dsl/examples/calculator/calculator.zir:19)");
  return OneHotStruct{._super = x2};
}
TopStruct exec_Top(ExecContext& ctx, BoundLayout<TopLayout> layout0, GlobalBuf global1) {
  // Top(zirgen/dsl/examples/calculator/calculator.zir:33)
  BoundLayout<TopResultLayout> x2 = LAYOUT_LOOKUP(layout0, result);
  // GetValFromUser(zirgen/dsl/examples/calculator/calculator.zir:5)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:29)
  Val x3 = INVOKE_EXTERN(ctx, getValFromUser);
  NondetRegStruct x4 = exec_NondetReg(ctx, x3, LAYOUT_LOOKUP(layout0, op));
  // GetValFromUser(zirgen/dsl/examples/calculator/calculator.zir:5)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:30)
  Val x5 = INVOKE_EXTERN(ctx, getValFromUser);
  NondetRegStruct x6 = exec_NondetReg(ctx, x5, LAYOUT_LOOKUP(layout0, arg1));
  // GetValFromUser(zirgen/dsl/examples/calculator/calculator.zir:5)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:31)
  Val x7 = INVOKE_EXTERN(ctx, getValFromUser);
  NondetRegStruct x8 = exec_NondetReg(ctx, x7, LAYOUT_LOOKUP(layout0, arg2));
  // GetValFromUser(zirgen/dsl/examples/calculator/calculator.zir:5)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:32)
  Val x9 = INVOKE_EXTERN(ctx, getValFromUser);
  NondetRegStruct x10 = exec_NondetReg(ctx, x9, LAYOUT_LOOKUP(layout0, expected));
  // Top(zirgen/dsl/examples/calculator/calculator.zir:29)
  Val x11 = x4._super;
  // Top(zirgen/dsl/examples/calculator/calculator.zir:33)
  OneHotStruct x12 = exec_OneHot(ctx, x11, LAYOUT_LOOKUP(layout0, _0));
  NondetRegStruct2Array x13 = x12._super;
  BoundLayout<NondetRegLayout> x14 = LAYOUT_LOOKUP(x2, _super);
  // Top(zirgen/dsl/examples/calculator/calculator.zir:30)
  Val x15 = x6._super;
  // Top(zirgen/dsl/examples/calculator/calculator.zir:31)
  Val x16 = x8._super;
  NondetRegStruct x17;
  if (to_size_t(x13[0]._super)) {
    // Top(zirgen/dsl/examples/calculator/calculator.zir:35)
    NondetRegStruct x18 = exec_Reg(ctx, (x15 + x16), LAYOUT_LOOKUP(x2, arm0));
    x17 = x18;
  } else if (to_size_t(x13[1]._super)) {
    // Top(zirgen/dsl/examples/calculator/calculator.zir:37)
    NondetRegStruct x19 = exec_Reg(ctx, (x15 - x16), LAYOUT_LOOKUP(x2, arm1));
    x17 = x19;
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  // Top(zirgen/dsl/examples/calculator/calculator.zir:33)
  NondetRegStruct x20 = back_Reg(ctx, 0, x14);
  // Top(zirgen/dsl/examples/calculator/calculator.zir:32)
  Val x21 = x10._super;
  // Log(<preamble>:16)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:39)
  INVOKE_EXTERN(ctx,
                log,
                "op = %u, arg1 = %u arg2 = %u result = %u expected = %u",
                std::initializer_list<Val>{x11, x15, x16, x20._super, x21});
  // Top(zirgen/dsl/examples/calculator/calculator.zir:33)
  NondetRegStruct x22 = back_Reg(ctx, 0, x14);
  // Top(zirgen/dsl/examples/calculator/calculator.zir:40)
  EQZ((x22._super - x21), "Top(zirgen/dsl/examples/calculator/calculator.zir:40)");
  // SetGlobalResult(zirgen/dsl/examples/calculator/calculator.zir:23)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:41)
  BoundLayout<_globalLayout> x23 = BIND_LAYOUT(kLayoutGlobal, global1);
  // SetGlobalResult(zirgen/dsl/examples/calculator/calculator.zir:24)
  NondetRegStruct x24 = exec_Reg(ctx, Val(5), LAYOUT_LOOKUP(x23, result));
  // Top(zirgen/dsl/examples/calculator/calculator.zir:33)
  NondetRegStruct x25 = back_Reg(ctx, 0, x14);
  // OutputToUser(zirgen/dsl/examples/calculator/calculator.zir:6)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:42)
  INVOKE_EXTERN(ctx, outputToUser, x25._super);
  return TopStruct{};
}
void step_Top(ExecContext& ctx, MutableBuf data0, GlobalBuf global1) {
  // Top(zirgen/dsl/examples/calculator/calculator.zir:28)
  BoundLayout<TopLayout> x2 = BIND_LAYOUT(kLayout_Top, data0);
  TopStruct x3 = exec_Top(ctx, x2, global1);
  return;
}
