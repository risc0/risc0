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
  // Top(zirgen/dsl/examples/calculator/calculator.zir:36)
  BoundLayout<TopResultLayout> x2 = LAYOUT_LOOKUP(layout0, result);
  // GetValFromUser(zirgen/dsl/examples/calculator/calculator.zir:5)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:33)
  Val x3 = INVOKE_EXTERN(ctx, getValFromUser);
  NondetRegStruct x4 = exec_NondetReg(ctx, x3, LAYOUT_LOOKUP(layout0, op));
  // GetValFromUser(zirgen/dsl/examples/calculator/calculator.zir:5)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:34)
  Val x5 = INVOKE_EXTERN(ctx, getValFromUser);
  NondetRegStruct x6 = exec_NondetReg(ctx, x5, LAYOUT_LOOKUP(layout0, left));
  // GetValFromUser(zirgen/dsl/examples/calculator/calculator.zir:5)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:35)
  Val x7 = INVOKE_EXTERN(ctx, getValFromUser);
  NondetRegStruct x8 = exec_NondetReg(ctx, x7, LAYOUT_LOOKUP(layout0, right));
  // Top(zirgen/dsl/examples/calculator/calculator.zir:36)
  OneHotStruct x9 = exec_OneHot(ctx, x4._super, LAYOUT_LOOKUP(layout0, _0));
  NondetRegStruct2Array x10 = x9._super;
  BoundLayout<NondetRegLayout> x11 = LAYOUT_LOOKUP(x2, _super);
  // Top(zirgen/dsl/examples/calculator/calculator.zir:34)
  Val x12 = x6._super;
  // Top(zirgen/dsl/examples/calculator/calculator.zir:35)
  Val x13 = x8._super;
  NondetRegStruct x14;
  if (to_size_t(x10[0]._super)) {
    // Top(zirgen/dsl/examples/calculator/calculator.zir:37)
    NondetRegStruct x15 = exec_Reg(ctx, (x12 + x13), LAYOUT_LOOKUP(x2, arm0));
    x14 = x15;
  } else if (to_size_t(x10[1]._super)) {
    // Top(zirgen/dsl/examples/calculator/calculator.zir:38)
    NondetRegStruct x16 = exec_Reg(ctx, (x12 - x13), LAYOUT_LOOKUP(x2, arm1));
    x14 = x16;
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  // Top(zirgen/dsl/examples/calculator/calculator.zir:36)
  NondetRegStruct x17 = back_Reg(ctx, 0, x11);
  // Log(<preamble>:16)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:40)
  INVOKE_EXTERN(ctx, log, "result = %u", std::initializer_list<Val>{x17._super});
  // Top(zirgen/dsl/examples/calculator/calculator.zir:36)
  NondetRegStruct x18 = back_Reg(ctx, 0, x11);
  // SetGlobalResult(zirgen/dsl/examples/calculator/calculator.zir:28)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:41)
  BoundLayout<_globalLayout> x19 = BIND_LAYOUT(kLayoutGlobal, global1);
  // SetGlobalResult(zirgen/dsl/examples/calculator/calculator.zir:29)
  BoundLayout<NondetRegLayout> x20 = LAYOUT_LOOKUP(x19, result);
  NondetRegStruct x21 = exec_Reg(ctx, x18._super, x20);
  // GetGlobalResult(zirgen/dsl/examples/calculator/calculator.zir:24)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:42)
  NondetRegStruct x22 = back_Reg(ctx, 0, x20);
  // Top(zirgen/dsl/examples/calculator/calculator.zir:36)
  NondetRegStruct x23 = back_Reg(ctx, 0, x11);
  // Top(zirgen/dsl/examples/calculator/calculator.zir:42)
  EQZ((x22._super - x23._super), "Top(zirgen/dsl/examples/calculator/calculator.zir:42)");
  // Top(zirgen/dsl/examples/calculator/calculator.zir:36)
  NondetRegStruct x24 = back_Reg(ctx, 0, x11);
  // OutputToUser(zirgen/dsl/examples/calculator/calculator.zir:6)
  // Top(zirgen/dsl/examples/calculator/calculator.zir:43)
  INVOKE_EXTERN(ctx, outputToUser, x24._super);
  return TopStruct{};
}
void step_Top(ExecContext& ctx, MutableBuf data0, GlobalBuf global1) {
  // Top(zirgen/dsl/examples/calculator/calculator.zir:32)
  BoundLayout<TopLayout> x2 = BIND_LAYOUT(kLayout_Top, data0);
  TopStruct x3 = exec_Top(ctx, x2, global1);
  return;
}
