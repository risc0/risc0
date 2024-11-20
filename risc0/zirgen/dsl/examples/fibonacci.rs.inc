set_field!(BabyBear);
define_buffer_list! {
all: [accum,code,data,global,mix,],
rows: [accum,code,data,],
taps: [accum,code,data,],
globals: [global,mix,],}
define_tap_buffer! {accum, /*count=*/1, /*groupId=*/0}
define_tap_buffer! {code, /*count=*/1, /*groupId=*/1}
define_tap_buffer! {data, /*count=*/8, /*groupId=*/2}
define_global_buffer! {global, /*count=*/5}
define_global_buffer! {mix, /*count=*/4}
pub struct NondetRegLayout {
    pub _super: &'static Reg,
}
impl risc0_zkp::layout::Component for NondetRegLayout {
    fn ty_name(&self) -> &'static str {
        "NondetRegLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        Ok(())
    }
}
pub struct IsZeroLayout {
    pub _super: &'static NondetRegLayout,
    pub inv: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for IsZeroLayout {
    fn ty_name(&self) -> &'static str {
        "IsZeroLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("inv", self.inv)?;
        Ok(())
    }
}
pub struct CycleCounterLayout {
    pub _super: &'static NondetRegLayout,
    pub is_first_cycle: &'static IsZeroLayout,
}
impl risc0_zkp::layout::Component for CycleCounterLayout {
    fn ty_name(&self) -> &'static str {
        "CycleCounterLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("_super", self._super)?;
        v.visit_component("is_first_cycle", self.is_first_cycle)?;
        Ok(())
    }
}
pub type Tap13Array = [Tap; 13];
pub struct TopLayout {
    pub cycle: &'static CycleCounterLayout,
    pub d2: &'static NondetRegLayout,
    pub d3: &'static NondetRegLayout,
    pub d1: &'static NondetRegLayout,
    pub terminate: &'static IsZeroLayout,
}
impl risc0_zkp::layout::Component for TopLayout {
    fn ty_name(&self) -> &'static str {
        "TopLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("cycle", self.cycle)?;
        v.visit_component("d2", self.d2)?;
        v.visit_component("d3", self.d3)?;
        v.visit_component("d1", self.d1)?;
        v.visit_component("terminate", self.terminate)?;
        Ok(())
    }
}
pub struct _globalLayout {
    pub f0: &'static NondetRegLayout,
    pub f1: &'static NondetRegLayout,
    pub f_last: &'static NondetRegLayout,
    pub steps: &'static NondetRegLayout,
    pub total_cycles: &'static NondetRegLayout,
}
impl risc0_zkp::layout::Component for _globalLayout {
    fn ty_name(&self) -> &'static str {
        "_globalLayout"
    }
    #[allow(unused_variables)]
    fn walk<V: risc0_zkp::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
        v.visit_component("f0", self.f0)?;
        v.visit_component("f1", self.f1)?;
        v.visit_component("f_last", self.f_last)?;
        v.visit_component("steps", self.steps)?;
        v.visit_component("total_cycles", self.total_cycles)?;
        Ok(())
    }
}
#[derive(Copy, Clone, Debug)]
pub struct NondetRegStruct {
    pub _super: Val,
}
#[derive(Copy, Clone, Debug)]
pub struct ComponentStruct {}
#[derive(Copy, Clone, Debug)]
pub struct RegStruct {
    pub _super: NondetRegStruct,
    pub reg: NondetRegStruct,
}
#[derive(Copy, Clone, Debug)]
pub struct GetCycleStruct {
    pub _super: Val,
}
#[derive(Copy, Clone, Debug)]
pub struct IsZeroStruct {
    pub _super: NondetRegStruct,
    pub is_zero: NondetRegStruct,
    pub inv: NondetRegStruct,
}
#[derive(Copy, Clone, Debug)]
pub struct CycleCounterStruct {
    pub _super: NondetRegStruct,
    pub cycle: NondetRegStruct,
    pub is_first_cycle: IsZeroStruct,
}
#[derive(Copy, Clone, Debug)]
pub struct TopStruct {
    pub _super: ComponentStruct,
    pub cycle: CycleCounterStruct,
    pub first: IsZeroStruct,
    pub d1: RegStruct,
    pub d2: RegStruct,
    pub d3: RegStruct,
    pub terminate: IsZeroStruct,
}
pub const LAYOUT__0: &CycleCounterLayout = &CycleCounterLayout {
    _super: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    is_first_cycle: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 1 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 2 },
        },
    },
};
pub const TAP_LIST: Tap13Array = [
    make_tap!(0, 0, 0),
    make_tap!(1, 0, 0),
    make_tap!(2, 0, 0),
    make_tap!(2, 0, 1),
    make_tap!(2, 1, 0),
    make_tap!(2, 2, 0),
    make_tap!(2, 3, 0),
    make_tap!(2, 3, 1),
    make_tap!(2, 4, 0),
    make_tap!(2, 4, 1),
    make_tap!(2, 5, 0),
    make_tap!(2, 6, 0),
    make_tap!(2, 7, 0),
];
pub const LAYOUT_TOP: &TopLayout = &TopLayout {
    cycle: LAYOUT__0,
    d2: &NondetRegLayout {
        _super: &Reg { offset: 3 },
    },
    d3: &NondetRegLayout {
        _super: &Reg { offset: 4 },
    },
    d1: &NondetRegLayout {
        _super: &Reg { offset: 5 },
    },
    terminate: &IsZeroLayout {
        _super: &NondetRegLayout {
            _super: &Reg { offset: 6 },
        },
        inv: &NondetRegLayout {
            _super: &Reg { offset: 7 },
        },
    },
};
pub const LAYOUT_GLOBAL: &_globalLayout = &_globalLayout {
    f0: &NondetRegLayout {
        _super: &Reg { offset: 0 },
    },
    f1: &NondetRegLayout {
        _super: &Reg { offset: 1 },
    },
    f_last: &NondetRegLayout {
        _super: &Reg { offset: 2 },
    },
    steps: &NondetRegLayout {
        _super: &Reg { offset: 3 },
    },
    total_cycles: &NondetRegLayout {
        _super: &Reg { offset: 4 },
    },
};
pub fn exec_inv(ctx: &ExecContext, arg0: Val) -> Result<Val> {
    return Ok(inv_0(arg0)?);
}
pub fn exec_isz(ctx: &ExecContext, arg0: Val) -> Result<Val> {
    return Ok(isz(arg0)?);
}
pub fn exec_add(ctx: &ExecContext, arg0: Val, arg1: Val) -> Result<Val> {
    return Ok((arg0 + arg1));
}
pub fn exec_sub(ctx: &ExecContext, arg0: Val, arg1: Val) -> Result<Val> {
    return Ok((arg0 - arg1));
}
pub fn exec_mul(ctx: &ExecContext, arg0: Val, arg1: Val) -> Result<Val> {
    return Ok((arg0 * arg1));
}
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
pub fn exec_component(ctx: &ExecContext) -> Result<ComponentStruct> {
    return Ok(ComponentStruct {});
}
pub fn back_reg(
    ctx: &ExecContext,
    distance0: Index,
    layout1: &BoundLayout<NondetRegLayout, impl BufferRow<ValType = Val>>,
) -> Result<RegStruct> {
    // Reg(<preamble>:4)
    let x2: NondetRegStruct = back_nondet_reg(ctx, distance0, layout1)?;
    return Ok(RegStruct {
        _super: x2.clone(),
        reg: x2,
    });
}
pub fn exec_reg(
    ctx: &ExecContext,
    arg0: Val,
    layout1: &BoundLayout<NondetRegLayout, impl BufferRow<ValType = Val>>,
) -> Result<RegStruct> {
    let x2: NondetRegStruct = exec_nondet_reg(ctx, arg0, layout1)?;
    // Reg(<preamble>:5)
    eqz!((arg0 - x2._super), "Reg(<preamble>:5)");
    return Ok(RegStruct {
        _super: x2.clone(),
        reg: x2,
    });
}
pub fn exec_log(ctx: &ExecContext, arg0: &str, arg1: &[Val]) -> Result<ComponentStruct> {
    // Log(<preamble>:16)
    invoke_extern!(ctx, log, arg0, arg1);
    return Ok(ComponentStruct {});
}
pub fn exec_get_cycle(ctx: &ExecContext) -> Result<GetCycleStruct> {
    // GetCycle(zirgen/dsl/examples/fibonacci.zir:2)
    let x0: Val = invoke_extern!(ctx, get_cycle);
    return Ok(GetCycleStruct { _super: x0 });
}
pub fn exec_is_zero(
    ctx: &ExecContext,
    arg0: Val,
    layout1: &BoundLayout<IsZeroLayout, impl BufferRow<ValType = Val>>,
) -> Result<IsZeroStruct> {
    // IsZero(zirgen/dsl/examples/fibonacci.zir:6)
    let x2: Val = exec_isz(ctx, arg0)?;
    let x3: NondetRegStruct = exec_nondet_reg(ctx, x2, (&layout1.map(|c| c._super)))?;
    // IsZero(zirgen/dsl/examples/fibonacci.zir:9)
    let x4: Val = exec_inv(ctx, arg0)?;
    let x5: NondetRegStruct = exec_nondet_reg(ctx, x4, (&layout1.map(|c| c.inv)))?;
    // IsZero(zirgen/dsl/examples/fibonacci.zir:6)
    let x6: Val = x3._super;
    // IsZero(zirgen/dsl/examples/fibonacci.zir:12)
    let x7: Val = exec_sub(ctx, Val::new(1), x6)?;
    let x8: Val = exec_mul(ctx, x6, x7)?;
    eqz!(x8, "IsZero(zirgen/dsl/examples/fibonacci.zir:12)");
    // IsZero(zirgen/dsl/examples/fibonacci.zir:9)
    let x9: Val = x5._super;
    // IsZero(zirgen/dsl/examples/fibonacci.zir:14)
    let x10: Val = exec_mul(ctx, arg0, x9)?;
    let x11: Val = exec_sub(ctx, Val::new(1), x6)?;
    eqz!((x10 - x11), "IsZero(zirgen/dsl/examples/fibonacci.zir:14)");
    // IsZero(zirgen/dsl/examples/fibonacci.zir:16)
    let x12: Val = exec_mul(ctx, x6, arg0)?;
    eqz!(x12, "IsZero(zirgen/dsl/examples/fibonacci.zir:16)");
    // IsZero(zirgen/dsl/examples/fibonacci.zir:18)
    let x13: Val = exec_mul(ctx, x6, x9)?;
    eqz!(x13, "IsZero(zirgen/dsl/examples/fibonacci.zir:18)");
    return Ok(IsZeroStruct {
        _super: x3.clone(),
        is_zero: x3,
        inv: x5,
    });
}
pub fn exec_cycle_counter(
    ctx: &ExecContext,
    layout0: &BoundLayout<CycleCounterLayout, impl BufferRow<ValType = Val>>,
    global1: &impl BufferRow<ValType = Val>,
) -> Result<CycleCounterStruct> {
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:28)
    let x2: &BoundLayout<_globalLayout, _> = bind_layout!(LAYOUT_GLOBAL, global1);
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:31)
    let x3: &BoundLayout<NondetRegLayout, _> = (&layout0.map(|c| c._super));
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:29)
    let x4: NondetRegStruct = exec_nondet_reg(ctx, Val::new(6), (&x2.map(|c| c.total_cycles)))?;
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:31)
    let x5: GetCycleStruct = exec_get_cycle(ctx)?;
    let x6: NondetRegStruct = exec_nondet_reg(ctx, x5._super, x3)?;
    let x7: Val = x6._super;
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:32)
    let x8: IsZeroStruct = exec_is_zero(ctx, x7, (&layout0.map(|c| c.is_first_cycle)))?;
    let x9: Val = x8._super._super;
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:34)
    let x10: Val = exec_sub(ctx, Val::new(1), x9)?;
    let x11: ComponentStruct;
    if is_true(x9) {
        let x12: ComponentStruct = exec_component(ctx)?;
        x11 = x12;
    } else if is_true(x10) {
        // CycleCounter(zirgen/dsl/examples/fibonacci.zir:39)
        let x13: NondetRegStruct = back_nondet_reg(ctx, 1, x3)?;
        let x14: Val = exec_add(ctx, x13._super, Val::new(1))?;
        eqz!(
            (x7 - x14),
            "CycleCounter(zirgen/dsl/examples/fibonacci.zir:39)"
        );
        // CycleCounter(zirgen/dsl/examples/fibonacci.zir:37)
        let x15: ComponentStruct = exec_component(ctx)?;
        x11 = x15;
    } else {
        bail!("Reached unreachable mux arm")
    }
    return Ok(CycleCounterStruct {
        _super: x6.clone(),
        cycle: x6,
        is_first_cycle: x8,
    });
}
pub fn exec_top(
    ctx: &ExecContext,
    layout0: &BoundLayout<TopLayout, impl BufferRow<ValType = Val>>,
    global1: &impl BufferRow<ValType = Val>,
) -> Result<TopStruct> {
    // Top(zirgen/dsl/examples/fibonacci.zir:44)
    let x2: &BoundLayout<_globalLayout, _> = bind_layout!(LAYOUT_GLOBAL, global1);
    // Top(zirgen/dsl/examples/fibonacci.zir:53)
    let x3: &BoundLayout<NondetRegLayout, _> = (&layout0.map(|c| c.d2));
    // Top(zirgen/dsl/examples/fibonacci.zir:54)
    let x4: &BoundLayout<NondetRegLayout, _> = (&layout0.map(|c| c.d3));
    // Top(zirgen/dsl/examples/fibonacci.zir:49)
    let x5: CycleCounterStruct = exec_cycle_counter(ctx, (&layout0.map(|c| c.cycle)), global1)?;
    let x6: IsZeroStruct = x5.is_first_cycle;
    let x7: Val = x6._super._super;
    // Top(zirgen/dsl/examples/fibonacci.zir:55)
    let x8: Val = exec_sub(ctx, Val::new(1), x7)?;
    let x9: RegStruct;
    if is_true(x7) {
        // Top(zirgen/dsl/examples/fibonacci.zir:45)
        let x10: RegStruct = back_reg(ctx, 0, (&x2.map(|c| c.f0)))?;
        x9 = x10;
    } else if is_true(x8) {
        // Top(zirgen/dsl/examples/fibonacci.zir:55)
        let x11: RegStruct = back_reg(ctx, 1, x3)?;
        x9 = x11;
    } else {
        bail!("Reached unreachable mux arm")
    }
    let x12: RegStruct = exec_reg(ctx, x9._super._super, (&layout0.map(|c| c.d1)))?;
    // Top(zirgen/dsl/examples/fibonacci.zir:56)
    let x13: Val = exec_sub(ctx, Val::new(1), x7)?;
    let x14: RegStruct;
    if is_true(x7) {
        // Top(zirgen/dsl/examples/fibonacci.zir:46)
        let x15: RegStruct = back_reg(ctx, 0, (&x2.map(|c| c.f1)))?;
        x14 = x15;
    } else if is_true(x13) {
        // Top(zirgen/dsl/examples/fibonacci.zir:56)
        let x16: RegStruct = back_reg(ctx, 1, x4)?;
        x14 = x16;
    } else {
        bail!("Reached unreachable mux arm")
    }
    let x17: RegStruct = exec_reg(ctx, x14._super._super, x3)?;
    // Top(zirgen/dsl/examples/fibonacci.zir:59)
    let x18: Val = exec_add(ctx, x12._super._super, x17._super._super)?;
    let x19: RegStruct = exec_reg(ctx, x18, x4)?;
    // Top(zirgen/dsl/examples/fibonacci.zir:47)
    let x20: RegStruct = back_reg(ctx, 0, (&x2.map(|c| c.steps)))?;
    // Top(zirgen/dsl/examples/fibonacci.zir:62)
    let x21: Val = exec_sub(ctx, x5._super._super, x20._super._super)?;
    let x22: Val = exec_add(ctx, x21, Val::new(1))?;
    let x23: IsZeroStruct = exec_is_zero(ctx, x22, (&layout0.map(|c| c.terminate)))?;
    let x24: Val = x23._super._super;
    // Top(zirgen/dsl/examples/fibonacci.zir:63)
    let x25: Val = exec_sub(ctx, Val::new(1), x24)?;
    let x26: ComponentStruct;
    if is_true(x24) {
        // Top(zirgen/dsl/examples/fibonacci.zir:64)
        let x27: &BoundLayout<NondetRegLayout, _> = (&x2.map(|c| c.f_last));
        let x28: RegStruct = exec_reg(ctx, x19._super._super, x27)?;
        let x29: RegStruct = back_reg(ctx, 0, x27)?;
        // Top(zirgen/dsl/examples/fibonacci.zir:65)
        let x30: [Val] = [x29._super._super];
        let x31: ComponentStruct = exec_log(ctx, "f_last = %u", &x30)?;
        // Top(zirgen/dsl/examples/fibonacci.zir:63)
        let x32: ComponentStruct = exec_component(ctx)?;
        x26 = x32;
    } else if is_true(x25) {
        // Top(zirgen/dsl/examples/fibonacci.zir:66)
        let x33: ComponentStruct = exec_component(ctx)?;
        x26 = x33;
    } else {
        bail!("Reached unreachable mux arm")
    } // Top(zirgen/dsl/examples/fibonacci.zir:44)
    let x34: ComponentStruct = exec_component(ctx)?;
    return Ok(TopStruct {
        _super: x34,
        cycle: x5,
        first: x6,
        d1: x12,
        d2: x17,
        d3: x19,
        terminate: x23,
    });
}
pub fn step_top(
    ctx: &ExecContext,
    data0: &impl BufferRow<ValType = Val>,
    global1: &impl BufferRow<ValType = Val>,
) -> Result<()> {
    let x2: &BoundLayout<TopLayout, _> = bind_layout!(LAYOUT_TOP, data0);
    let x3: TopStruct = exec_top(ctx, x2, global1)?;
    return Ok(());
}
pub fn validity_taps(
    ctx: &ValidityTapsContext,
    taps0: &impl BufferRow<ValType = ExtVal>,
    poly_mix1: PolyMix,
    global2: &impl BufferRow<ValType = Val>,
) -> Result<MixState> {
    let x3: ExtVal = get(ctx, taps0, 2, 0)?;
    let x4: ExtVal = get(ctx, taps0, 4, 0)?;
    let x5: ExtVal = get(ctx, taps0, 5, 0)?;
    let x6: ExtVal = get(ctx, taps0, 6, 0)?;
    let x7: ExtVal = get(ctx, taps0, 8, 0)?;
    let x8: ExtVal = get(ctx, taps0, 10, 0)?;
    let x9: ExtVal = get(ctx, taps0, 11, 0)?;
    let x10: ExtVal = get(ctx, taps0, 12, 0)?;
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:34)
    // Top(zirgen/dsl/examples/fibonacci.zir:49)
    let x11: MixState = trivial_constraint()?;
    let x12: &BoundLayout<_globalLayout, _> = bind_layout!(LAYOUT_GLOBAL, global2);
    // Top(zirgen/dsl/examples/fibonacci.zir:62)
    let x13: ExtVal = ((x3 - (&(&x12.map(|c| c.steps)).map(|c| c._super)).load(ctx, 0))
        + ExtVal::new(Val::new(1), Val::new(0), Val::new(0), Val::new(0)));
    // IsZero(zirgen/dsl/examples/fibonacci.zir:12)
    let x14: ExtVal = (ExtVal::new(Val::new(1), Val::new(0), Val::new(0), Val::new(0)) - x9);
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:32)
    // Top(zirgen/dsl/examples/fibonacci.zir:49)
    let x15: ExtVal = (ExtVal::new(Val::new(1), Val::new(0), Val::new(0), Val::new(0)) - x4);
    // IsZero(zirgen/dsl/examples/fibonacci.zir:14)
    let x16: MixState = and_eqz_ext(ctx, and_eqz_ext(ctx, x11, (x4 * x15))?, ((x3 * x5) - x15))?;
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:34)
    let x17: MixState = and_cond_ext(
        and_eqz_ext(ctx, and_eqz_ext(ctx, x16, (x4 * x3))?, (x4 * x5))?,
        x15,
        and_eqz_ext(
            ctx,
            x11,
            (x3 - (get(ctx, taps0, 3, 0)?
                + ExtVal::new(Val::new(1), Val::new(0), Val::new(0), Val::new(0)))),
        )?,
    )?;
    // Top(zirgen/dsl/examples/fibonacci.zir:55)
    let x18: ExtVal = ((&(&x12.map(|c| c.f0)).map(|c| c._super)).load_unchecked(ctx, 0) * x4);
    // Top(zirgen/dsl/examples/fibonacci.zir:56)
    let x19: ExtVal = ((&(&x12.map(|c| c.f1)).map(|c| c._super)).load_unchecked(ctx, 0) * x4);
    // Reg(<preamble>:5)
    let x20: MixState = and_eqz_ext(
        ctx,
        and_eqz_ext(ctx, x17, ((x18 + (get(ctx, taps0, 7, 0)? * x15)) - x8))?,
        ((x19 + (get(ctx, taps0, 9, 0)? * x15)) - x6),
    )?;
    // IsZero(zirgen/dsl/examples/fibonacci.zir:14)
    // Top(zirgen/dsl/examples/fibonacci.zir:62)
    let x21: MixState = and_eqz_ext(
        ctx,
        and_eqz_ext(ctx, and_eqz_ext(ctx, x20, ((x8 + x6) - x7))?, (x9 * x14))?,
        ((x13 * x10) - x14),
    )?;
    // Top(zirgen/dsl/examples/fibonacci.zir:63)
    let x22: MixState = and_cond_ext(
        and_eqz_ext(ctx, and_eqz_ext(ctx, x21, (x9 * x13))?, (x9 * x10))?,
        x9,
        and_eqz_ext(
            ctx,
            x11,
            (x7 - (&(&x12.map(|c| c.f_last)).map(|c| c._super)).load(ctx, 0)),
        )?,
    )?;
    return Ok(x22);
}
pub fn validity_regs(
    ctx: &ValidityRegsContext,
    poly_mix0: PolyMix,
    data1: &impl BufferRow<ValType = Val>,
    global2: &impl BufferRow<ValType = Val>,
) -> Result<MixState> {
    let x3: &BoundLayout<TopLayout, _> = bind_layout!(LAYOUT_TOP, data1);
    let x4: &BoundLayout<_globalLayout, _> = bind_layout!(LAYOUT_GLOBAL, global2);
    // Top(zirgen/dsl/examples/fibonacci.zir:62)
    let x5: &BoundLayout<IsZeroLayout, _> = (&x3.map(|c| c.terminate));
    // Top(zirgen/dsl/examples/fibonacci.zir:54)
    let x6: &BoundLayout<NondetRegLayout, _> = (&x3.map(|c| c.d3));
    // Top(zirgen/dsl/examples/fibonacci.zir:53)
    let x7: &BoundLayout<NondetRegLayout, _> = (&x3.map(|c| c.d2));
    // Top(zirgen/dsl/examples/fibonacci.zir:49)
    let x8: &BoundLayout<CycleCounterLayout, _> = (&x3.map(|c| c.cycle));
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:32)
    let x9: &BoundLayout<IsZeroLayout, _> = (&x8.map(|c| c.is_first_cycle));
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:31)
    let x10: &BoundLayout<NondetRegLayout, _> = (&x8.map(|c| c._super));
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:39)
    let x11: Val = ((&x10.map(|c| c._super)).load(ctx, 1) + Val::new(1));
    let x12: Val = ((&x10.map(|c| c._super)).load(ctx, 0) - x11);
    // Top(zirgen/dsl/examples/fibonacci.zir:59)
    let x13: Val = ((&(&x3.map(|c| c.d1)).map(|c| c._super)).load(ctx, 0)
        + (&x7.map(|c| c._super)).load(ctx, 0));
    // Top(zirgen/dsl/examples/fibonacci.zir:62)
    let x14: Val = ((&x10.map(|c| c._super)).load(ctx, 0)
        - (&(&x4.map(|c| c.steps)).map(|c| c._super)).load(ctx, 0));
    let x15: Val = (x14 + Val::new(1));
    // IsZero(zirgen/dsl/examples/fibonacci.zir:12)
    let x16: Val = (Val::new(1) - (&(&x5.map(|c| c._super)).map(|c| c._super)).load(ctx, 0));
    let x17: Val = ((&(&x5.map(|c| c._super)).map(|c| c._super)).load(ctx, 0) * x16);
    // IsZero(zirgen/dsl/examples/fibonacci.zir:14)
    let x18: Val = (Val::new(1) - (&(&x5.map(|c| c._super)).map(|c| c._super)).load(ctx, 0));
    // IsZero(zirgen/dsl/examples/fibonacci.zir:16)
    let x19: Val = ((&(&x5.map(|c| c._super)).map(|c| c._super)).load(ctx, 0) * x15);
    // IsZero(zirgen/dsl/examples/fibonacci.zir:18)
    let x20: Val = ((&(&x5.map(|c| c._super)).map(|c| c._super)).load(ctx, 0)
        * (&(&x5.map(|c| c.inv)).map(|c| c._super)).load(ctx, 0));
    // Reg(<preamble>:5)
    // Top(zirgen/dsl/examples/fibonacci.zir:64)
    let x21: Val = ((&x6.map(|c| c._super)).load(ctx, 0)
        - (&(&x4.map(|c| c.f_last)).map(|c| c._super)).load(ctx, 0));
    // IsZero(zirgen/dsl/examples/fibonacci.zir:12)
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:32)
    // Top(zirgen/dsl/examples/fibonacci.zir:49)
    let x22: Val = (Val::new(1) - (&(&x9.map(|c| c._super)).map(|c| c._super)).load(ctx, 0));
    let x23: Val = ((&(&x9.map(|c| c._super)).map(|c| c._super)).load(ctx, 0) * x22);
    // IsZero(zirgen/dsl/examples/fibonacci.zir:14)
    let x24: Val = ((&x10.map(|c| c._super)).load(ctx, 0)
        * (&(&x9.map(|c| c.inv)).map(|c| c._super)).load(ctx, 0));
    let x25: Val = (Val::new(1) - (&(&x9.map(|c| c._super)).map(|c| c._super)).load(ctx, 0));
    let x26: MixState = and_eqz(ctx, and_eqz(ctx, trivial_constraint()?, x23)?, (x24 - x25))?;
    // IsZero(zirgen/dsl/examples/fibonacci.zir:16)
    let x27: Val = ((&(&x9.map(|c| c._super)).map(|c| c._super)).load(ctx, 0)
        * (&x10.map(|c| c._super)).load(ctx, 0));
    // IsZero(zirgen/dsl/examples/fibonacci.zir:18)
    let x28: Val = ((&(&x9.map(|c| c._super)).map(|c| c._super)).load(ctx, 0)
        * (&(&x9.map(|c| c.inv)).map(|c| c._super)).load(ctx, 0));
    // CycleCounter(zirgen/dsl/examples/fibonacci.zir:34)
    let x29: Val = (Val::new(1) - (&(&x9.map(|c| c._super)).map(|c| c._super)).load(ctx, 0));
    let x30: MixState = and_cond(
        and_eqz(ctx, and_eqz(ctx, x26, x27)?, x28)?,
        x29,
        and_eqz(ctx, trivial_constraint()?, x12)?,
    )?;
    // Top(zirgen/dsl/examples/fibonacci.zir:55)
    let x31: Val = (Val::new(1) - (&(&x9.map(|c| c._super)).map(|c| c._super)).load(ctx, 0));
    let x32: Val = ((&(&x4.map(|c| c.f0)).map(|c| c._super)).load_unchecked(ctx, 0)
        * (&(&x9.map(|c| c._super)).map(|c| c._super)).load(ctx, 0));
    let x33: Val = ((&x7.map(|c| c._super)).load_unchecked(ctx, 1) * x31);
    // Reg(<preamble>:5)
    let x34: Val = ((x32 + x33) - (&(&x3.map(|c| c.d1)).map(|c| c._super)).load(ctx, 0));
    // Top(zirgen/dsl/examples/fibonacci.zir:56)
    let x35: Val = (Val::new(1) - (&(&x9.map(|c| c._super)).map(|c| c._super)).load(ctx, 0));
    let x36: Val = ((&(&x4.map(|c| c.f1)).map(|c| c._super)).load_unchecked(ctx, 0)
        * (&(&x9.map(|c| c._super)).map(|c| c._super)).load(ctx, 0));
    let x37: Val = ((&x6.map(|c| c._super)).load_unchecked(ctx, 1) * x35);
    // Reg(<preamble>:5)
    let x38: Val = ((x36 + x37) - (&x7.map(|c| c._super)).load(ctx, 0));
    // Top(zirgen/dsl/examples/fibonacci.zir:59)
    let x39: MixState = and_eqz(
        ctx,
        and_eqz(ctx, and_eqz(ctx, x30, x34)?, x38)?,
        (x13 - (&x6.map(|c| c._super)).load(ctx, 0)),
    )?;
    // IsZero(zirgen/dsl/examples/fibonacci.zir:14)
    // Top(zirgen/dsl/examples/fibonacci.zir:62)
    let x40: MixState = and_eqz(
        ctx,
        and_eqz(ctx, x39, x17)?,
        ((x15 * (&(&x5.map(|c| c.inv)).map(|c| c._super)).load(ctx, 0)) - x18),
    )?;
    // Top(zirgen/dsl/examples/fibonacci.zir:63)
    let x41: MixState = and_cond(
        and_eqz(ctx, and_eqz(ctx, x40, x19)?, x20)?,
        (&(&x5.map(|c| c._super)).map(|c| c._super)).load(ctx, 0),
        and_eqz(ctx, trivial_constraint()?, x21)?,
    )?;
    return Ok(x41);
}
