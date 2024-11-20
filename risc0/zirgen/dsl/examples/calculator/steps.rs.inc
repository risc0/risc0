pub fn back_nondet_reg(
    ctx: &ExecContext,
    distance0: Index,
    layout1: &BoundLayout<NondetRegLayout, impl BufferRow<ValType = Val>>,
) -> Result<NondetRegStruct> {
    let x2: NondetRegStruct = NondetRegStruct {
        _super: (&layout1.map(|c| c._super)).load(ctx, distance0),
    };
    return Ok(x2);
}
pub fn exec_nondet_reg(
    ctx: &ExecContext,
    arg0: Val,
    layout1: &BoundLayout<NondetRegLayout, impl BufferRow<ValType = Val>>,
) -> Result<NondetRegStruct> {
    let x2: &BoundLayout<Reg, _> = (&layout1.map(|c| c._super));
    x2.store(ctx, arg0);
    return Ok(NondetRegStruct {
        _super: x2.load(ctx, 0),
    });
}
pub fn back_reg(
    ctx: &ExecContext,
    distance0: Index,
    layout1: &BoundLayout<NondetRegLayout, impl BufferRow<ValType = Val>>,
) -> Result<NondetRegStruct> {
    // Reg(<preamble>:4)
    let x2: NondetRegStruct = back_nondet_reg(ctx, distance0, layout1)?;
    return Ok(x2);
}
pub fn exec_reg(
    ctx: &ExecContext,
    arg0: Val,
    layout1: &BoundLayout<NondetRegLayout, impl BufferRow<ValType = Val>>,
) -> Result<NondetRegStruct> {
    let x2: NondetRegStruct = exec_nondet_reg(ctx, arg0, layout1)?;
    // Reg(<preamble>:5)
    eqz!((arg0 - x2._super), "Reg(<preamble>:5)");
    return Ok(x2);
}
pub fn exec_one_hot(
    ctx: &ExecContext,
    arg0: Val,
    layout1: &BoundLayout<OneHotLayout, impl BufferRow<ValType = Val>>,
) -> Result<OneHotStruct> {
    // OneHot(zirgen/dsl/examples/calculator/calculator.zir:13)
    let x2: NondetRegStruct2Array = map_layout(
        [Val::new(0), Val::new(1)],
        (&layout1.map(|c| c._super)),
        |x3, x4| {
            let x5: NondetRegStruct = exec_nondet_reg(ctx, isz((x3 - arg0))?, x4)?;
            return Ok(x5);
        },
    )?;
    // OneHot(zirgen/dsl/examples/calculator/calculator.zir:15)
    let x6: Val = x2[to_usize(Val::new(0))]._super;
    eqz!(
        (x6 * (Val::new(1) - x6)),
        "OneHot(zirgen/dsl/examples/calculator/calculator.zir:15)"
    );
    let x7: Val = x2[to_usize(Val::new(1))]._super;
    eqz!(
        (x7 * (Val::new(1) - x7)),
        "OneHot(zirgen/dsl/examples/calculator/calculator.zir:15)"
    );
    // OneHot(zirgen/dsl/examples/calculator/calculator.zir:17)
    eqz!(
        ((x6 + x7) - Val::new(1)),
        "OneHot(zirgen/dsl/examples/calculator/calculator.zir:17)"
    );
    // OneHot(zirgen/dsl/examples/calculator/calculator.zir:19)
    eqz!(
        (x7 - arg0),
        "OneHot(zirgen/dsl/examples/calculator/calculator.zir:19)"
    );
    return Ok(OneHotStruct { _super: x2 });
}
pub fn exec_top(
    ctx: &ExecContext,
    layout0: &BoundLayout<TopLayout, impl BufferRow<ValType = Val>>,
    global1: &impl BufferRow<ValType = Val>,
) -> Result<TopStruct> {
    // Top(zirgen/dsl/examples/calculator/calculator.zir:33)
    let x2: &BoundLayout<TopResultLayout, _> = (&layout0.map(|c| c.result));
    // GetValFromUser(zirgen/dsl/examples/calculator/calculator.zir:5)
    // Top(zirgen/dsl/examples/calculator/calculator.zir:29)
    let x3: Val = invoke_extern!(ctx, get_val_from_user);
    let x4: NondetRegStruct = exec_nondet_reg(ctx, x3, (&layout0.map(|c| c.op)))?;
    // GetValFromUser(zirgen/dsl/examples/calculator/calculator.zir:5)
    // Top(zirgen/dsl/examples/calculator/calculator.zir:30)
    let x5: Val = invoke_extern!(ctx, get_val_from_user);
    let x6: NondetRegStruct = exec_nondet_reg(ctx, x5, (&layout0.map(|c| c.arg1)))?;
    // GetValFromUser(zirgen/dsl/examples/calculator/calculator.zir:5)
    // Top(zirgen/dsl/examples/calculator/calculator.zir:31)
    let x7: Val = invoke_extern!(ctx, get_val_from_user);
    let x8: NondetRegStruct = exec_nondet_reg(ctx, x7, (&layout0.map(|c| c.arg2)))?;
    // GetValFromUser(zirgen/dsl/examples/calculator/calculator.zir:5)
    // Top(zirgen/dsl/examples/calculator/calculator.zir:32)
    let x9: Val = invoke_extern!(ctx, get_val_from_user);
    let x10: NondetRegStruct = exec_nondet_reg(ctx, x9, (&layout0.map(|c| c.expected)))?;
    // Top(zirgen/dsl/examples/calculator/calculator.zir:29)
    let x11: Val = x4._super;
    // Top(zirgen/dsl/examples/calculator/calculator.zir:33)
    let x12: OneHotStruct = exec_one_hot(ctx, x11, (&layout0.map(|c| c._0)))?;
    let x13: NondetRegStruct2Array = x12._super;
    let x14: &BoundLayout<NondetRegLayout, _> = (&x2.map(|c| c._super));
    // Top(zirgen/dsl/examples/calculator/calculator.zir:30)
    let x15: Val = x6._super;
    // Top(zirgen/dsl/examples/calculator/calculator.zir:31)
    let x16: Val = x8._super;
    let x17: NondetRegStruct;
    if is_true(x13[to_usize(Val::new(0))]._super) {
        // Top(zirgen/dsl/examples/calculator/calculator.zir:35)
        let x18: NondetRegStruct = exec_reg(ctx, (x15 + x16), (&x2.map(|c| c.arm0)))?;
        x17 = x18;
    } else if is_true(x13[to_usize(Val::new(1))]._super) {
        // Top(zirgen/dsl/examples/calculator/calculator.zir:37)
        let x19: NondetRegStruct = exec_reg(ctx, (x15 - x16), (&x2.map(|c| c.arm1)))?;
        x17 = x19;
    } else {
        bail!("Reached unreachable mux arm")
    } // Top(zirgen/dsl/examples/calculator/calculator.zir:33)
    let x20: NondetRegStruct = back_reg(ctx, 0, x14)?;
    // Top(zirgen/dsl/examples/calculator/calculator.zir:32)
    let x21: Val = x10._super;
    // Log(<preamble>:16)
    // Top(zirgen/dsl/examples/calculator/calculator.zir:39)
    invoke_extern!(
        ctx,
        log,
        "op = %u, arg1 = %u arg2 = %u result = %u expected = %u",
        [x11, x15, x16, x20._super, x21]
    );
    // Top(zirgen/dsl/examples/calculator/calculator.zir:33)
    let x22: NondetRegStruct = back_reg(ctx, 0, x14)?;
    // Top(zirgen/dsl/examples/calculator/calculator.zir:40)
    eqz!(
        (x22._super - x21),
        "Top(zirgen/dsl/examples/calculator/calculator.zir:40)"
    );
    // SetGlobalResult(zirgen/dsl/examples/calculator/calculator.zir:23)
    // Top(zirgen/dsl/examples/calculator/calculator.zir:41)
    let x23: &BoundLayout<_globalLayout, _> = bind_layout!(LAYOUT_GLOBAL, global1);
    // SetGlobalResult(zirgen/dsl/examples/calculator/calculator.zir:24)
    let x24: NondetRegStruct = exec_reg(ctx, Val::new(5), (&x23.map(|c| c.result)))?;
    // Top(zirgen/dsl/examples/calculator/calculator.zir:33)
    let x25: NondetRegStruct = back_reg(ctx, 0, x14)?;
    // OutputToUser(zirgen/dsl/examples/calculator/calculator.zir:6)
    // Top(zirgen/dsl/examples/calculator/calculator.zir:42)
    invoke_extern!(ctx, output_to_user, x25._super);
    return Ok(TopStruct {});
}
pub fn step_top(
    ctx: &ExecContext,
    data0: &impl BufferRow<ValType = Val>,
    global1: &impl BufferRow<ValType = Val>,
) -> Result<()> {
    // Top(zirgen/dsl/examples/calculator/calculator.zir:28)
    let x2: &BoundLayout<TopLayout, _> = bind_layout!(LAYOUT_TOP, data0);
    let x3: TopStruct = exec_top(ctx, x2, global1)?;
    return Ok(());
}
