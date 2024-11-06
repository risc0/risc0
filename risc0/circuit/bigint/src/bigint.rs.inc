bigint_declare_byte_poly!(BytePoly_32, 32);
bigint_declare_byte_poly!(BytePoly_63, 63);
bigint_declare_byte_poly!(BytePoly_33, 33);
bigint_declare_byte_poly!(BytePoly_64, 64);
bigint_declare_byte_poly!(BytePoly_384, 384);
bigint_declare_byte_poly!(BytePoly_767, 767);
bigint_declare_byte_poly!(BytePoly_386, 386);
bigint_declare_byte_poly!(BytePoly_769, 769);
bigint_declare_byte_poly!(BytePoly_1, 1);
bigint_declare_byte_poly!(BytePoly_2, 2);
bigint_declare_byte_poly!(BytePoly_3, 3);
bigint_declare_byte_poly!(BytePoly_16, 16);
bigint_declare_byte_poly!(BytePoly_17, 17);
bigint_declare_byte_poly!(BytePoly_31, 31);
pub fn rsa_256_x1(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_32 = bigint_def!(ctx, 32, 0, 1);
    let x1: BytePoly_32 = bigint_def!(ctx, 32, 1, 1);
    let x2: BytePoly_32 = bigint_def!(ctx, 32, 2, 1);
    let x3: BytePoly_63 = bigint_mul!(x1, x1, 63);
    let x4: BytePoly_33 = bigint_nondet_quot!(ctx, x3, x0, 33);
    let x5: BytePoly_32 = bigint_nondet_rem!(ctx, x3, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x4, x0, 64), x5, 64), x3, 64),
        260134,
        4,
    )?;
    let x6: BytePoly_63 = bigint_mul!(x5, x5, 63);
    let x7: BytePoly_33 = bigint_nondet_quot!(ctx, x6, x0, 33);
    let x8: BytePoly_32 = bigint_nondet_rem!(ctx, x6, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x7, x0, 64), x8, 64), x6, 64),
        260134,
        4,
    )?;
    let x9: BytePoly_63 = bigint_mul!(x8, x8, 63);
    let x10: BytePoly_33 = bigint_nondet_quot!(ctx, x9, x0, 33);
    let x11: BytePoly_32 = bigint_nondet_rem!(ctx, x9, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x10, x0, 64), x11, 64), x9, 64),
        260134,
        4,
    )?;
    let x12: BytePoly_63 = bigint_mul!(x11, x11, 63);
    let x13: BytePoly_33 = bigint_nondet_quot!(ctx, x12, x0, 33);
    let x14: BytePoly_32 = bigint_nondet_rem!(ctx, x12, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x13, x0, 64), x14, 64), x12, 64),
        260134,
        4,
    )?;
    let x15: BytePoly_63 = bigint_mul!(x14, x14, 63);
    let x16: BytePoly_33 = bigint_nondet_quot!(ctx, x15, x0, 33);
    let x17: BytePoly_32 = bigint_nondet_rem!(ctx, x15, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x16, x0, 64), x17, 64), x15, 64),
        260134,
        4,
    )?;
    let x18: BytePoly_63 = bigint_mul!(x17, x17, 63);
    let x19: BytePoly_33 = bigint_nondet_quot!(ctx, x18, x0, 33);
    let x20: BytePoly_32 = bigint_nondet_rem!(ctx, x18, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x19, x0, 64), x20, 64), x18, 64),
        260134,
        4,
    )?;
    let x21: BytePoly_63 = bigint_mul!(x20, x20, 63);
    let x22: BytePoly_33 = bigint_nondet_quot!(ctx, x21, x0, 33);
    let x23: BytePoly_32 = bigint_nondet_rem!(ctx, x21, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x22, x0, 64), x23, 64), x21, 64),
        260134,
        4,
    )?;
    let x24: BytePoly_63 = bigint_mul!(x23, x23, 63);
    let x25: BytePoly_33 = bigint_nondet_quot!(ctx, x24, x0, 33);
    let x26: BytePoly_32 = bigint_nondet_rem!(ctx, x24, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x25, x0, 64), x26, 64), x24, 64),
        260134,
        4,
    )?;
    let x27: BytePoly_63 = bigint_mul!(x26, x26, 63);
    let x28: BytePoly_33 = bigint_nondet_quot!(ctx, x27, x0, 33);
    let x29: BytePoly_32 = bigint_nondet_rem!(ctx, x27, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x28, x0, 64), x29, 64), x27, 64),
        260134,
        4,
    )?;
    let x30: BytePoly_63 = bigint_mul!(x29, x29, 63);
    let x31: BytePoly_33 = bigint_nondet_quot!(ctx, x30, x0, 33);
    let x32: BytePoly_32 = bigint_nondet_rem!(ctx, x30, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x31, x0, 64), x32, 64), x30, 64),
        260134,
        4,
    )?;
    let x33: BytePoly_63 = bigint_mul!(x32, x32, 63);
    let x34: BytePoly_33 = bigint_nondet_quot!(ctx, x33, x0, 33);
    let x35: BytePoly_32 = bigint_nondet_rem!(ctx, x33, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x34, x0, 64), x35, 64), x33, 64),
        260134,
        4,
    )?;
    let x36: BytePoly_63 = bigint_mul!(x35, x35, 63);
    let x37: BytePoly_33 = bigint_nondet_quot!(ctx, x36, x0, 33);
    let x38: BytePoly_32 = bigint_nondet_rem!(ctx, x36, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x37, x0, 64), x38, 64), x36, 64),
        260134,
        4,
    )?;
    let x39: BytePoly_63 = bigint_mul!(x38, x38, 63);
    let x40: BytePoly_33 = bigint_nondet_quot!(ctx, x39, x0, 33);
    let x41: BytePoly_32 = bigint_nondet_rem!(ctx, x39, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x40, x0, 64), x41, 64), x39, 64),
        260134,
        4,
    )?;
    let x42: BytePoly_63 = bigint_mul!(x41, x41, 63);
    let x43: BytePoly_33 = bigint_nondet_quot!(ctx, x42, x0, 33);
    let x44: BytePoly_32 = bigint_nondet_rem!(ctx, x42, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x43, x0, 64), x44, 64), x42, 64),
        260134,
        4,
    )?;
    let x45: BytePoly_63 = bigint_mul!(x44, x44, 63);
    let x46: BytePoly_33 = bigint_nondet_quot!(ctx, x45, x0, 33);
    let x47: BytePoly_32 = bigint_nondet_rem!(ctx, x45, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x46, x0, 64), x47, 64), x45, 64),
        260134,
        4,
    )?;
    let x48: BytePoly_63 = bigint_mul!(x47, x47, 63);
    let x49: BytePoly_33 = bigint_nondet_quot!(ctx, x48, x0, 33);
    let x50: BytePoly_32 = bigint_nondet_rem!(ctx, x48, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x49, x0, 64), x50, 64), x48, 64),
        260134,
        4,
    )?;
    let x51: BytePoly_63 = bigint_mul!(x50, x1, 63);
    let x52: BytePoly_33 = bigint_nondet_quot!(ctx, x51, x0, 33);
    let x53: BytePoly_32 = bigint_nondet_rem!(ctx, x51, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x52, x0, 64), x53, 64), x51, 64),
        260134,
        4,
    )?;
    eqz(ctx, &bigint_sub!(x53, x2, 32), 34, 1)?;
    return Ok(());
}
pub fn rsa_256_x2(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_32 = bigint_def!(ctx, 32, 0, 1);
    let x1: BytePoly_32 = bigint_def!(ctx, 32, 1, 1);
    let x2: BytePoly_32 = bigint_def!(ctx, 32, 2, 1);
    let x3: BytePoly_63 = bigint_mul!(x1, x1, 63);
    let x4: BytePoly_33 = bigint_nondet_quot!(ctx, x3, x0, 33);
    let x5: BytePoly_32 = bigint_nondet_rem!(ctx, x3, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x4, x0, 64), x5, 64), x3, 64),
        260134,
        4,
    )?;
    let x6: BytePoly_63 = bigint_mul!(x5, x5, 63);
    let x7: BytePoly_33 = bigint_nondet_quot!(ctx, x6, x0, 33);
    let x8: BytePoly_32 = bigint_nondet_rem!(ctx, x6, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x7, x0, 64), x8, 64), x6, 64),
        260134,
        4,
    )?;
    let x9: BytePoly_63 = bigint_mul!(x8, x8, 63);
    let x10: BytePoly_33 = bigint_nondet_quot!(ctx, x9, x0, 33);
    let x11: BytePoly_32 = bigint_nondet_rem!(ctx, x9, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x10, x0, 64), x11, 64), x9, 64),
        260134,
        4,
    )?;
    let x12: BytePoly_63 = bigint_mul!(x11, x11, 63);
    let x13: BytePoly_33 = bigint_nondet_quot!(ctx, x12, x0, 33);
    let x14: BytePoly_32 = bigint_nondet_rem!(ctx, x12, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x13, x0, 64), x14, 64), x12, 64),
        260134,
        4,
    )?;
    let x15: BytePoly_63 = bigint_mul!(x14, x14, 63);
    let x16: BytePoly_33 = bigint_nondet_quot!(ctx, x15, x0, 33);
    let x17: BytePoly_32 = bigint_nondet_rem!(ctx, x15, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x16, x0, 64), x17, 64), x15, 64),
        260134,
        4,
    )?;
    let x18: BytePoly_63 = bigint_mul!(x17, x17, 63);
    let x19: BytePoly_33 = bigint_nondet_quot!(ctx, x18, x0, 33);
    let x20: BytePoly_32 = bigint_nondet_rem!(ctx, x18, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x19, x0, 64), x20, 64), x18, 64),
        260134,
        4,
    )?;
    let x21: BytePoly_63 = bigint_mul!(x20, x20, 63);
    let x22: BytePoly_33 = bigint_nondet_quot!(ctx, x21, x0, 33);
    let x23: BytePoly_32 = bigint_nondet_rem!(ctx, x21, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x22, x0, 64), x23, 64), x21, 64),
        260134,
        4,
    )?;
    let x24: BytePoly_63 = bigint_mul!(x23, x23, 63);
    let x25: BytePoly_33 = bigint_nondet_quot!(ctx, x24, x0, 33);
    let x26: BytePoly_32 = bigint_nondet_rem!(ctx, x24, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x25, x0, 64), x26, 64), x24, 64),
        260134,
        4,
    )?;
    let x27: BytePoly_63 = bigint_mul!(x26, x26, 63);
    let x28: BytePoly_33 = bigint_nondet_quot!(ctx, x27, x0, 33);
    let x29: BytePoly_32 = bigint_nondet_rem!(ctx, x27, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x28, x0, 64), x29, 64), x27, 64),
        260134,
        4,
    )?;
    let x30: BytePoly_63 = bigint_mul!(x29, x29, 63);
    let x31: BytePoly_33 = bigint_nondet_quot!(ctx, x30, x0, 33);
    let x32: BytePoly_32 = bigint_nondet_rem!(ctx, x30, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x31, x0, 64), x32, 64), x30, 64),
        260134,
        4,
    )?;
    let x33: BytePoly_63 = bigint_mul!(x32, x32, 63);
    let x34: BytePoly_33 = bigint_nondet_quot!(ctx, x33, x0, 33);
    let x35: BytePoly_32 = bigint_nondet_rem!(ctx, x33, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x34, x0, 64), x35, 64), x33, 64),
        260134,
        4,
    )?;
    let x36: BytePoly_63 = bigint_mul!(x35, x35, 63);
    let x37: BytePoly_33 = bigint_nondet_quot!(ctx, x36, x0, 33);
    let x38: BytePoly_32 = bigint_nondet_rem!(ctx, x36, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x37, x0, 64), x38, 64), x36, 64),
        260134,
        4,
    )?;
    let x39: BytePoly_63 = bigint_mul!(x38, x38, 63);
    let x40: BytePoly_33 = bigint_nondet_quot!(ctx, x39, x0, 33);
    let x41: BytePoly_32 = bigint_nondet_rem!(ctx, x39, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x40, x0, 64), x41, 64), x39, 64),
        260134,
        4,
    )?;
    let x42: BytePoly_63 = bigint_mul!(x41, x41, 63);
    let x43: BytePoly_33 = bigint_nondet_quot!(ctx, x42, x0, 33);
    let x44: BytePoly_32 = bigint_nondet_rem!(ctx, x42, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x43, x0, 64), x44, 64), x42, 64),
        260134,
        4,
    )?;
    let x45: BytePoly_63 = bigint_mul!(x44, x44, 63);
    let x46: BytePoly_33 = bigint_nondet_quot!(ctx, x45, x0, 33);
    let x47: BytePoly_32 = bigint_nondet_rem!(ctx, x45, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x46, x0, 64), x47, 64), x45, 64),
        260134,
        4,
    )?;
    let x48: BytePoly_63 = bigint_mul!(x47, x47, 63);
    let x49: BytePoly_33 = bigint_nondet_quot!(ctx, x48, x0, 33);
    let x50: BytePoly_32 = bigint_nondet_rem!(ctx, x48, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x49, x0, 64), x50, 64), x48, 64),
        260134,
        4,
    )?;
    let x51: BytePoly_63 = bigint_mul!(x50, x1, 63);
    let x52: BytePoly_33 = bigint_nondet_quot!(ctx, x51, x0, 33);
    let x53: BytePoly_32 = bigint_nondet_rem!(ctx, x51, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x52, x0, 64), x53, 64), x51, 64),
        260134,
        4,
    )?;
    eqz(ctx, &bigint_sub!(x53, x2, 32), 34, 1)?;
    return Ok(());
}
pub fn rsa_3072_x1(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_384 = bigint_def!(ctx, 384, 0, 1);
    let x1: BytePoly_384 = bigint_def!(ctx, 384, 1, 1);
    let x2: BytePoly_384 = bigint_def!(ctx, 384, 2, 1);
    let x3: BytePoly_767 = bigint_mul!(x1, x1, 767);
    let x4: BytePoly_386 = bigint_nondet_quot!(ctx, x3, x0, 386);
    let x5: BytePoly_384 = bigint_nondet_rem!(ctx, x3, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x4, x0, 769), x5, 769), x3, 769),
        3121234,
        4,
    )?;
    let x6: BytePoly_767 = bigint_mul!(x5, x5, 767);
    let x7: BytePoly_386 = bigint_nondet_quot!(ctx, x6, x0, 386);
    let x8: BytePoly_384 = bigint_nondet_rem!(ctx, x6, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x7, x0, 769), x8, 769), x6, 769),
        3121234,
        4,
    )?;
    let x9: BytePoly_767 = bigint_mul!(x8, x8, 767);
    let x10: BytePoly_386 = bigint_nondet_quot!(ctx, x9, x0, 386);
    let x11: BytePoly_384 = bigint_nondet_rem!(ctx, x9, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x10, x0, 769), x11, 769), x9, 769),
        3121234,
        4,
    )?;
    let x12: BytePoly_767 = bigint_mul!(x11, x11, 767);
    let x13: BytePoly_386 = bigint_nondet_quot!(ctx, x12, x0, 386);
    let x14: BytePoly_384 = bigint_nondet_rem!(ctx, x12, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x13, x0, 769), x14, 769), x12, 769),
        3121234,
        4,
    )?;
    let x15: BytePoly_767 = bigint_mul!(x14, x14, 767);
    let x16: BytePoly_386 = bigint_nondet_quot!(ctx, x15, x0, 386);
    let x17: BytePoly_384 = bigint_nondet_rem!(ctx, x15, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x16, x0, 769), x17, 769), x15, 769),
        3121234,
        4,
    )?;
    let x18: BytePoly_767 = bigint_mul!(x17, x17, 767);
    let x19: BytePoly_386 = bigint_nondet_quot!(ctx, x18, x0, 386);
    let x20: BytePoly_384 = bigint_nondet_rem!(ctx, x18, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x19, x0, 769), x20, 769), x18, 769),
        3121234,
        4,
    )?;
    let x21: BytePoly_767 = bigint_mul!(x20, x20, 767);
    let x22: BytePoly_386 = bigint_nondet_quot!(ctx, x21, x0, 386);
    let x23: BytePoly_384 = bigint_nondet_rem!(ctx, x21, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x22, x0, 769), x23, 769), x21, 769),
        3121234,
        4,
    )?;
    let x24: BytePoly_767 = bigint_mul!(x23, x23, 767);
    let x25: BytePoly_386 = bigint_nondet_quot!(ctx, x24, x0, 386);
    let x26: BytePoly_384 = bigint_nondet_rem!(ctx, x24, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x25, x0, 769), x26, 769), x24, 769),
        3121234,
        4,
    )?;
    let x27: BytePoly_767 = bigint_mul!(x26, x26, 767);
    let x28: BytePoly_386 = bigint_nondet_quot!(ctx, x27, x0, 386);
    let x29: BytePoly_384 = bigint_nondet_rem!(ctx, x27, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x28, x0, 769), x29, 769), x27, 769),
        3121234,
        4,
    )?;
    let x30: BytePoly_767 = bigint_mul!(x29, x29, 767);
    let x31: BytePoly_386 = bigint_nondet_quot!(ctx, x30, x0, 386);
    let x32: BytePoly_384 = bigint_nondet_rem!(ctx, x30, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x31, x0, 769), x32, 769), x30, 769),
        3121234,
        4,
    )?;
    let x33: BytePoly_767 = bigint_mul!(x32, x32, 767);
    let x34: BytePoly_386 = bigint_nondet_quot!(ctx, x33, x0, 386);
    let x35: BytePoly_384 = bigint_nondet_rem!(ctx, x33, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x34, x0, 769), x35, 769), x33, 769),
        3121234,
        4,
    )?;
    let x36: BytePoly_767 = bigint_mul!(x35, x35, 767);
    let x37: BytePoly_386 = bigint_nondet_quot!(ctx, x36, x0, 386);
    let x38: BytePoly_384 = bigint_nondet_rem!(ctx, x36, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x37, x0, 769), x38, 769), x36, 769),
        3121234,
        4,
    )?;
    let x39: BytePoly_767 = bigint_mul!(x38, x38, 767);
    let x40: BytePoly_386 = bigint_nondet_quot!(ctx, x39, x0, 386);
    let x41: BytePoly_384 = bigint_nondet_rem!(ctx, x39, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x40, x0, 769), x41, 769), x39, 769),
        3121234,
        4,
    )?;
    let x42: BytePoly_767 = bigint_mul!(x41, x41, 767);
    let x43: BytePoly_386 = bigint_nondet_quot!(ctx, x42, x0, 386);
    let x44: BytePoly_384 = bigint_nondet_rem!(ctx, x42, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x43, x0, 769), x44, 769), x42, 769),
        3121234,
        4,
    )?;
    let x45: BytePoly_767 = bigint_mul!(x44, x44, 767);
    let x46: BytePoly_386 = bigint_nondet_quot!(ctx, x45, x0, 386);
    let x47: BytePoly_384 = bigint_nondet_rem!(ctx, x45, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x46, x0, 769), x47, 769), x45, 769),
        3121234,
        4,
    )?;
    let x48: BytePoly_767 = bigint_mul!(x47, x47, 767);
    let x49: BytePoly_386 = bigint_nondet_quot!(ctx, x48, x0, 386);
    let x50: BytePoly_384 = bigint_nondet_rem!(ctx, x48, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x49, x0, 769), x50, 769), x48, 769),
        3121234,
        4,
    )?;
    let x51: BytePoly_767 = bigint_mul!(x50, x1, 767);
    let x52: BytePoly_386 = bigint_nondet_quot!(ctx, x51, x0, 386);
    let x53: BytePoly_384 = bigint_nondet_rem!(ctx, x51, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x52, x0, 769), x53, 769), x51, 769),
        3121234,
        4,
    )?;
    eqz(ctx, &bigint_sub!(x53, x2, 384), 34, 1)?;
    return Ok(());
}
pub fn rsa_3072_x15(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_384 = bigint_def!(ctx, 384, 0, 1);
    let x1: BytePoly_384 = bigint_def!(ctx, 384, 1, 1);
    let x2: BytePoly_384 = bigint_def!(ctx, 384, 2, 1);
    let x3: BytePoly_767 = bigint_mul!(x1, x1, 767);
    let x4: BytePoly_386 = bigint_nondet_quot!(ctx, x3, x0, 386);
    let x5: BytePoly_384 = bigint_nondet_rem!(ctx, x3, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x4, x0, 769), x5, 769), x3, 769),
        3121234,
        4,
    )?;
    let x6: BytePoly_767 = bigint_mul!(x5, x5, 767);
    let x7: BytePoly_386 = bigint_nondet_quot!(ctx, x6, x0, 386);
    let x8: BytePoly_384 = bigint_nondet_rem!(ctx, x6, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x7, x0, 769), x8, 769), x6, 769),
        3121234,
        4,
    )?;
    let x9: BytePoly_767 = bigint_mul!(x8, x8, 767);
    let x10: BytePoly_386 = bigint_nondet_quot!(ctx, x9, x0, 386);
    let x11: BytePoly_384 = bigint_nondet_rem!(ctx, x9, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x10, x0, 769), x11, 769), x9, 769),
        3121234,
        4,
    )?;
    let x12: BytePoly_767 = bigint_mul!(x11, x11, 767);
    let x13: BytePoly_386 = bigint_nondet_quot!(ctx, x12, x0, 386);
    let x14: BytePoly_384 = bigint_nondet_rem!(ctx, x12, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x13, x0, 769), x14, 769), x12, 769),
        3121234,
        4,
    )?;
    let x15: BytePoly_767 = bigint_mul!(x14, x14, 767);
    let x16: BytePoly_386 = bigint_nondet_quot!(ctx, x15, x0, 386);
    let x17: BytePoly_384 = bigint_nondet_rem!(ctx, x15, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x16, x0, 769), x17, 769), x15, 769),
        3121234,
        4,
    )?;
    let x18: BytePoly_767 = bigint_mul!(x17, x17, 767);
    let x19: BytePoly_386 = bigint_nondet_quot!(ctx, x18, x0, 386);
    let x20: BytePoly_384 = bigint_nondet_rem!(ctx, x18, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x19, x0, 769), x20, 769), x18, 769),
        3121234,
        4,
    )?;
    let x21: BytePoly_767 = bigint_mul!(x20, x20, 767);
    let x22: BytePoly_386 = bigint_nondet_quot!(ctx, x21, x0, 386);
    let x23: BytePoly_384 = bigint_nondet_rem!(ctx, x21, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x22, x0, 769), x23, 769), x21, 769),
        3121234,
        4,
    )?;
    let x24: BytePoly_767 = bigint_mul!(x23, x23, 767);
    let x25: BytePoly_386 = bigint_nondet_quot!(ctx, x24, x0, 386);
    let x26: BytePoly_384 = bigint_nondet_rem!(ctx, x24, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x25, x0, 769), x26, 769), x24, 769),
        3121234,
        4,
    )?;
    let x27: BytePoly_767 = bigint_mul!(x26, x26, 767);
    let x28: BytePoly_386 = bigint_nondet_quot!(ctx, x27, x0, 386);
    let x29: BytePoly_384 = bigint_nondet_rem!(ctx, x27, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x28, x0, 769), x29, 769), x27, 769),
        3121234,
        4,
    )?;
    let x30: BytePoly_767 = bigint_mul!(x29, x29, 767);
    let x31: BytePoly_386 = bigint_nondet_quot!(ctx, x30, x0, 386);
    let x32: BytePoly_384 = bigint_nondet_rem!(ctx, x30, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x31, x0, 769), x32, 769), x30, 769),
        3121234,
        4,
    )?;
    let x33: BytePoly_767 = bigint_mul!(x32, x32, 767);
    let x34: BytePoly_386 = bigint_nondet_quot!(ctx, x33, x0, 386);
    let x35: BytePoly_384 = bigint_nondet_rem!(ctx, x33, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x34, x0, 769), x35, 769), x33, 769),
        3121234,
        4,
    )?;
    let x36: BytePoly_767 = bigint_mul!(x35, x35, 767);
    let x37: BytePoly_386 = bigint_nondet_quot!(ctx, x36, x0, 386);
    let x38: BytePoly_384 = bigint_nondet_rem!(ctx, x36, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x37, x0, 769), x38, 769), x36, 769),
        3121234,
        4,
    )?;
    let x39: BytePoly_767 = bigint_mul!(x38, x38, 767);
    let x40: BytePoly_386 = bigint_nondet_quot!(ctx, x39, x0, 386);
    let x41: BytePoly_384 = bigint_nondet_rem!(ctx, x39, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x40, x0, 769), x41, 769), x39, 769),
        3121234,
        4,
    )?;
    let x42: BytePoly_767 = bigint_mul!(x41, x41, 767);
    let x43: BytePoly_386 = bigint_nondet_quot!(ctx, x42, x0, 386);
    let x44: BytePoly_384 = bigint_nondet_rem!(ctx, x42, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x43, x0, 769), x44, 769), x42, 769),
        3121234,
        4,
    )?;
    let x45: BytePoly_767 = bigint_mul!(x44, x44, 767);
    let x46: BytePoly_386 = bigint_nondet_quot!(ctx, x45, x0, 386);
    let x47: BytePoly_384 = bigint_nondet_rem!(ctx, x45, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x46, x0, 769), x47, 769), x45, 769),
        3121234,
        4,
    )?;
    let x48: BytePoly_767 = bigint_mul!(x47, x47, 767);
    let x49: BytePoly_386 = bigint_nondet_quot!(ctx, x48, x0, 386);
    let x50: BytePoly_384 = bigint_nondet_rem!(ctx, x48, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x49, x0, 769), x50, 769), x48, 769),
        3121234,
        4,
    )?;
    let x51: BytePoly_767 = bigint_mul!(x50, x1, 767);
    let x52: BytePoly_386 = bigint_nondet_quot!(ctx, x51, x0, 386);
    let x53: BytePoly_384 = bigint_nondet_rem!(ctx, x51, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x52, x0, 769), x53, 769), x51, 769),
        3121234,
        4,
    )?;
    eqz(ctx, &bigint_sub!(x53, x2, 384), 34, 1)?;
    return Ok(());
}
pub fn nondet_inv_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_1 = bigint_const!(ctx, 1);
    let x1: BytePoly_1 = bigint_def!(ctx, 1, 0, 1);
    let x2: BytePoly_1 = bigint_def!(ctx, 1, 1, 1);
    let x3: BytePoly_1 = bigint_def!(ctx, 1, 2, 1);
    let x4: BytePoly_1 = bigint_nondet_inv!(ctx, x1, x2, 1);
    let x5: BytePoly_1 = bigint_mul!(x1, x4, 1);
    let x6: BytePoly_2 = bigint_nondet_quot!(ctx, x5, x2, 2);
    let x7: BytePoly_1 = bigint_nondet_rem!(ctx, x5, x2, 1);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x6, x2, 2), x7, 2), x5, 2),
        8163,
        2,
    )?;
    eqz(ctx, &bigint_sub!(x7, x0, 1), 34, 1)?;
    eqz(ctx, &bigint_sub!(x4, x3, 1), 34, 1)?;
    return Ok(());
}
pub fn const_add_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_2 = bigint_const!(ctx, 71, 71);
    let x1: BytePoly_1 = bigint_def!(ctx, 1, 0, 1);
    let x2: BytePoly_3 = bigint_def!(ctx, 3, 1, 1);
    eqz(ctx, &bigint_sub!(bigint_add!(x1, x0, 2), x2, 3), 66, 1)?;
    return Ok(());
}
pub fn const_add_alt_test_16(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_2 = bigint_const!(ctx, 50, 84);
    let x1: BytePoly_2 = bigint_def!(ctx, 2, 0, 1);
    let x2: BytePoly_3 = bigint_def!(ctx, 3, 1, 1);
    eqz(ctx, &bigint_sub!(bigint_add!(x1, x0, 2), x2, 3), 66, 1)?;
    return Ok(());
}
pub fn const_mul_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_2 = bigint_const!(ctx, 50, 84);
    let x1: BytePoly_1 = bigint_def!(ctx, 1, 0, 1);
    let x2: BytePoly_3 = bigint_def!(ctx, 3, 1, 1);
    eqz(ctx, &bigint_sub!(bigint_mul!(x1, x0, 2), x2, 3), 8131, 2)?;
    return Ok(());
}
pub fn add_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_1 = bigint_def!(ctx, 1, 0, 1);
    let x1: BytePoly_1 = bigint_def!(ctx, 1, 1, 1);
    let x2: BytePoly_2 = bigint_def!(ctx, 2, 2, 1);
    eqz(ctx, &bigint_sub!(bigint_add!(x0, x1, 1), x2, 2), 66, 1)?;
    return Ok(());
}
pub fn add_test_16(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_2 = bigint_def!(ctx, 2, 0, 1);
    let x1: BytePoly_2 = bigint_def!(ctx, 2, 1, 1);
    let x2: BytePoly_3 = bigint_def!(ctx, 3, 2, 1);
    eqz(ctx, &bigint_sub!(bigint_add!(x0, x1, 2), x2, 3), 66, 1)?;
    return Ok(());
}
pub fn add_test_128(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_16 = bigint_def!(ctx, 16, 0, 1);
    let x1: BytePoly_16 = bigint_def!(ctx, 16, 1, 1);
    let x2: BytePoly_17 = bigint_def!(ctx, 17, 2, 1);
    eqz(ctx, &bigint_sub!(bigint_add!(x0, x1, 16), x2, 17), 66, 1)?;
    return Ok(());
}
pub fn const_one_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_1 = bigint_const!(ctx, 1);
    let x1: BytePoly_1 = bigint_def!(ctx, 1, 0, 1);
    eqz(ctx, &bigint_sub!(x0, x1, 1), 34, 1)?;
    return Ok(());
}
pub fn const_twobyte_test_16(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_2 = bigint_const!(ctx, 52, 18);
    let x1: BytePoly_2 = bigint_def!(ctx, 2, 0, 1);
    eqz(ctx, &bigint_sub!(x0, x1, 2), 34, 1)?;
    return Ok(());
}
pub fn sub_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_1 = bigint_def!(ctx, 1, 0, 1);
    let x1: BytePoly_1 = bigint_def!(ctx, 1, 1, 1);
    let x2: BytePoly_1 = bigint_def!(ctx, 1, 2, 1);
    eqz(ctx, &bigint_sub!(bigint_sub!(x0, x1, 1), x2, 1), 66, 1)?;
    return Ok(());
}
pub fn sub_test_128(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_16 = bigint_def!(ctx, 16, 0, 1);
    let x1: BytePoly_16 = bigint_def!(ctx, 16, 1, 1);
    let x2: BytePoly_16 = bigint_def!(ctx, 16, 2, 1);
    eqz(ctx, &bigint_sub!(bigint_sub!(x0, x1, 16), x2, 16), 66, 1)?;
    return Ok(());
}
pub fn mul_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_1 = bigint_def!(ctx, 1, 0, 1);
    let x1: BytePoly_1 = bigint_def!(ctx, 1, 1, 1);
    let x2: BytePoly_2 = bigint_def!(ctx, 2, 2, 1);
    eqz(ctx, &bigint_sub!(bigint_mul!(x0, x1, 1), x2, 2), 8131, 2)?;
    return Ok(());
}
pub fn mul_test_128(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_16 = bigint_def!(ctx, 16, 0, 1);
    let x1: BytePoly_16 = bigint_def!(ctx, 16, 1, 1);
    let x2: BytePoly_32 = bigint_def!(ctx, 32, 2, 1);
    eqz(
        ctx,
        &bigint_sub!(bigint_mul!(x0, x1, 31), x2, 32),
        130053,
        4,
    )?;
    return Ok(());
}
pub fn reduce_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_1 = bigint_def!(ctx, 1, 0, 1);
    let x1: BytePoly_1 = bigint_def!(ctx, 1, 1, 1);
    let x2: BytePoly_1 = bigint_def!(ctx, 1, 2, 1);
    let x3: BytePoly_1 = bigint_nondet_quot!(ctx, x0, x1, 1);
    let x4: BytePoly_1 = bigint_nondet_rem!(ctx, x0, x1, 1);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x3, x1, 1), x4, 1), x0, 1),
        8163,
        2,
    )?;
    eqz(ctx, &bigint_sub!(x4, x2, 1), 34, 1)?;
    return Ok(());
}
pub fn reduce_test_128(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_16 = bigint_def!(ctx, 16, 0, 1);
    let x1: BytePoly_16 = bigint_def!(ctx, 16, 1, 1);
    let x2: BytePoly_16 = bigint_def!(ctx, 16, 2, 1);
    let x3: BytePoly_16 = bigint_nondet_quot!(ctx, x0, x1, 16);
    let x4: BytePoly_16 = bigint_nondet_rem!(ctx, x0, x1, 16);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x3, x1, 31), x4, 31), x0, 31),
        130084,
        4,
    )?;
    eqz(ctx, &bigint_sub!(x4, x2, 16), 34, 1)?;
    return Ok(());
}
bigint_program_info! {rsa_256_x1, /*iters=*/1,
bigint_witness_info!(/*bits=*/256, /*label=*/0, /*public=*/ true, /*min_bits=*/255),
bigint_witness_info!(/*bits=*/256, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/256, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {rsa_256_x2, /*iters=*/2,
bigint_witness_info!(/*bits=*/256, /*label=*/0, /*public=*/ true, /*min_bits=*/255),
bigint_witness_info!(/*bits=*/256, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/256, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {rsa_3072_x1, /*iters=*/1,
bigint_witness_info!(/*bits=*/3072, /*label=*/0, /*public=*/ true, /*min_bits=*/3071),
bigint_witness_info!(/*bits=*/3072, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/3072, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {rsa_3072_x15, /*iters=*/15,
bigint_witness_info!(/*bits=*/3072, /*label=*/0, /*public=*/ true, /*min_bits=*/3071),
bigint_witness_info!(/*bits=*/3072, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/3072, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {nondet_inv_test_8, /*iters=*/1,
bigint_witness_info!(/*bits=*/8, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/8, /*label=*/1, /*public=*/ true, /*min_bits=*/7),
bigint_witness_info!(/*bits=*/8, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {const_add_test_8, /*iters=*/1,
bigint_witness_info!(/*bits=*/8, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/17, /*label=*/1, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {const_add_alt_test_16, /*iters=*/1,
bigint_witness_info!(/*bits=*/16, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/17, /*label=*/1, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {const_mul_test_8, /*iters=*/1,
bigint_witness_info!(/*bits=*/8, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/24, /*label=*/1, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {add_test_8, /*iters=*/1,
bigint_witness_info!(/*bits=*/8, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/8, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/9, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {add_test_16, /*iters=*/1,
bigint_witness_info!(/*bits=*/16, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/16, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/17, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {add_test_128, /*iters=*/1,
bigint_witness_info!(/*bits=*/128, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/128, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/129, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {const_one_test_8, /*iters=*/1,
bigint_witness_info!(/*bits=*/8, /*label=*/0, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {const_twobyte_test_16, /*iters=*/1,
bigint_witness_info!(/*bits=*/16, /*label=*/0, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {sub_test_8, /*iters=*/1,
bigint_witness_info!(/*bits=*/8, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/8, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/8, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {sub_test_128, /*iters=*/1,
bigint_witness_info!(/*bits=*/128, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/128, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/128, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {mul_test_8, /*iters=*/1,
bigint_witness_info!(/*bits=*/8, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/8, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/16, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {mul_test_128, /*iters=*/1,
bigint_witness_info!(/*bits=*/128, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/128, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/256, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {reduce_test_8, /*iters=*/1,
bigint_witness_info!(/*bits=*/8, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/8, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/8, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_info! {reduce_test_128, /*iters=*/1,
bigint_witness_info!(/*bits=*/128, /*label=*/0, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/128, /*label=*/1, /*public=*/ true, /*min_bits=*/0),
bigint_witness_info!(/*bits=*/128, /*label=*/2, /*public=*/ true, /*min_bits=*/0)}
bigint_program_list! {rsa_256_x1, rsa_256_x2, rsa_3072_x1, rsa_3072_x15, nondet_inv_test_8, const_add_test_8, const_add_alt_test_16, const_mul_test_8, add_test_8, add_test_16, add_test_128, const_one_test_8, const_twobyte_test_16, sub_test_8, sub_test_128, mul_test_8, mul_test_128, reduce_test_8, reduce_test_128}
