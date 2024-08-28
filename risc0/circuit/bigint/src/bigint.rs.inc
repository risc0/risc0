bigint_declare_byte_poly!(BytePoly_32, 32);
bigint_declare_byte_poly!(BytePoly_64, 64);
bigint_declare_byte_poly!(BytePoly_34, 34);
bigint_declare_byte_poly!(BytePoly_66, 66);
bigint_declare_byte_poly!(BytePoly_384, 384);
bigint_declare_byte_poly!(BytePoly_768, 768);
bigint_declare_byte_poly!(BytePoly_387, 387);
bigint_declare_byte_poly!(BytePoly_771, 771);
bigint_declare_byte_poly!(BytePoly_1, 1);
bigint_declare_byte_poly!(BytePoly_2, 2);
bigint_declare_byte_poly!(BytePoly_3, 3);
bigint_declare_byte_poly!(BytePoly_4, 4);
bigint_declare_byte_poly!(BytePoly_16, 16);
bigint_declare_byte_poly!(BytePoly_17, 17);
pub fn rsa_256_x1(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_32 = bigint_def!(ctx, 32, 0, 1);
    let x1: BytePoly_32 = bigint_def!(ctx, 32, 1, 1);
    let x2: BytePoly_32 = bigint_def!(ctx, 32, 2, 1);
    let x3: BytePoly_64 = bigint_mul!(x1, x1, 64);
    let x4: BytePoly_34 = bigint_nondet_quot!(ctx, x3, x0, 34);
    let x5: BytePoly_32 = bigint_nondet_rem!(ctx, x3, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x4, x0, 66), x5, 66), x3, 66),
        276359,
        4,
    )?;
    let x6: BytePoly_64 = bigint_mul!(x5, x5, 64);
    let x7: BytePoly_34 = bigint_nondet_quot!(ctx, x6, x0, 34);
    let x8: BytePoly_32 = bigint_nondet_rem!(ctx, x6, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x7, x0, 66), x8, 66), x6, 66),
        276359,
        4,
    )?;
    let x9: BytePoly_64 = bigint_mul!(x8, x8, 64);
    let x10: BytePoly_34 = bigint_nondet_quot!(ctx, x9, x0, 34);
    let x11: BytePoly_32 = bigint_nondet_rem!(ctx, x9, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x10, x0, 66), x11, 66), x9, 66),
        276359,
        4,
    )?;
    let x12: BytePoly_64 = bigint_mul!(x11, x11, 64);
    let x13: BytePoly_34 = bigint_nondet_quot!(ctx, x12, x0, 34);
    let x14: BytePoly_32 = bigint_nondet_rem!(ctx, x12, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x13, x0, 66), x14, 66), x12, 66),
        276359,
        4,
    )?;
    let x15: BytePoly_64 = bigint_mul!(x14, x14, 64);
    let x16: BytePoly_34 = bigint_nondet_quot!(ctx, x15, x0, 34);
    let x17: BytePoly_32 = bigint_nondet_rem!(ctx, x15, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x16, x0, 66), x17, 66), x15, 66),
        276359,
        4,
    )?;
    let x18: BytePoly_64 = bigint_mul!(x17, x17, 64);
    let x19: BytePoly_34 = bigint_nondet_quot!(ctx, x18, x0, 34);
    let x20: BytePoly_32 = bigint_nondet_rem!(ctx, x18, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x19, x0, 66), x20, 66), x18, 66),
        276359,
        4,
    )?;
    let x21: BytePoly_64 = bigint_mul!(x20, x20, 64);
    let x22: BytePoly_34 = bigint_nondet_quot!(ctx, x21, x0, 34);
    let x23: BytePoly_32 = bigint_nondet_rem!(ctx, x21, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x22, x0, 66), x23, 66), x21, 66),
        276359,
        4,
    )?;
    let x24: BytePoly_64 = bigint_mul!(x23, x23, 64);
    let x25: BytePoly_34 = bigint_nondet_quot!(ctx, x24, x0, 34);
    let x26: BytePoly_32 = bigint_nondet_rem!(ctx, x24, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x25, x0, 66), x26, 66), x24, 66),
        276359,
        4,
    )?;
    let x27: BytePoly_64 = bigint_mul!(x26, x26, 64);
    let x28: BytePoly_34 = bigint_nondet_quot!(ctx, x27, x0, 34);
    let x29: BytePoly_32 = bigint_nondet_rem!(ctx, x27, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x28, x0, 66), x29, 66), x27, 66),
        276359,
        4,
    )?;
    let x30: BytePoly_64 = bigint_mul!(x29, x29, 64);
    let x31: BytePoly_34 = bigint_nondet_quot!(ctx, x30, x0, 34);
    let x32: BytePoly_32 = bigint_nondet_rem!(ctx, x30, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x31, x0, 66), x32, 66), x30, 66),
        276359,
        4,
    )?;
    let x33: BytePoly_64 = bigint_mul!(x32, x32, 64);
    let x34: BytePoly_34 = bigint_nondet_quot!(ctx, x33, x0, 34);
    let x35: BytePoly_32 = bigint_nondet_rem!(ctx, x33, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x34, x0, 66), x35, 66), x33, 66),
        276359,
        4,
    )?;
    let x36: BytePoly_64 = bigint_mul!(x35, x35, 64);
    let x37: BytePoly_34 = bigint_nondet_quot!(ctx, x36, x0, 34);
    let x38: BytePoly_32 = bigint_nondet_rem!(ctx, x36, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x37, x0, 66), x38, 66), x36, 66),
        276359,
        4,
    )?;
    let x39: BytePoly_64 = bigint_mul!(x38, x38, 64);
    let x40: BytePoly_34 = bigint_nondet_quot!(ctx, x39, x0, 34);
    let x41: BytePoly_32 = bigint_nondet_rem!(ctx, x39, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x40, x0, 66), x41, 66), x39, 66),
        276359,
        4,
    )?;
    let x42: BytePoly_64 = bigint_mul!(x41, x41, 64);
    let x43: BytePoly_34 = bigint_nondet_quot!(ctx, x42, x0, 34);
    let x44: BytePoly_32 = bigint_nondet_rem!(ctx, x42, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x43, x0, 66), x44, 66), x42, 66),
        276359,
        4,
    )?;
    let x45: BytePoly_64 = bigint_mul!(x44, x44, 64);
    let x46: BytePoly_34 = bigint_nondet_quot!(ctx, x45, x0, 34);
    let x47: BytePoly_32 = bigint_nondet_rem!(ctx, x45, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x46, x0, 66), x47, 66), x45, 66),
        276359,
        4,
    )?;
    let x48: BytePoly_64 = bigint_mul!(x47, x47, 64);
    let x49: BytePoly_34 = bigint_nondet_quot!(ctx, x48, x0, 34);
    let x50: BytePoly_32 = bigint_nondet_rem!(ctx, x48, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x49, x0, 66), x50, 66), x48, 66),
        276359,
        4,
    )?;
    let x51: BytePoly_64 = bigint_mul!(x50, x1, 64);
    let x52: BytePoly_34 = bigint_nondet_quot!(ctx, x51, x0, 34);
    let x53: BytePoly_32 = bigint_nondet_rem!(ctx, x51, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x52, x0, 66), x53, 66), x51, 66),
        276359,
        4,
    )?;
    eqz(ctx, &bigint_sub!(x53, x2, 32), 34, 1)?;
    return Ok(());
}
pub fn rsa_256_x2(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_32 = bigint_def!(ctx, 32, 0, 1);
    let x1: BytePoly_32 = bigint_def!(ctx, 32, 1, 1);
    let x2: BytePoly_32 = bigint_def!(ctx, 32, 2, 1);
    let x3: BytePoly_64 = bigint_mul!(x1, x1, 64);
    let x4: BytePoly_34 = bigint_nondet_quot!(ctx, x3, x0, 34);
    let x5: BytePoly_32 = bigint_nondet_rem!(ctx, x3, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x4, x0, 66), x5, 66), x3, 66),
        276359,
        4,
    )?;
    let x6: BytePoly_64 = bigint_mul!(x5, x5, 64);
    let x7: BytePoly_34 = bigint_nondet_quot!(ctx, x6, x0, 34);
    let x8: BytePoly_32 = bigint_nondet_rem!(ctx, x6, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x7, x0, 66), x8, 66), x6, 66),
        276359,
        4,
    )?;
    let x9: BytePoly_64 = bigint_mul!(x8, x8, 64);
    let x10: BytePoly_34 = bigint_nondet_quot!(ctx, x9, x0, 34);
    let x11: BytePoly_32 = bigint_nondet_rem!(ctx, x9, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x10, x0, 66), x11, 66), x9, 66),
        276359,
        4,
    )?;
    let x12: BytePoly_64 = bigint_mul!(x11, x11, 64);
    let x13: BytePoly_34 = bigint_nondet_quot!(ctx, x12, x0, 34);
    let x14: BytePoly_32 = bigint_nondet_rem!(ctx, x12, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x13, x0, 66), x14, 66), x12, 66),
        276359,
        4,
    )?;
    let x15: BytePoly_64 = bigint_mul!(x14, x14, 64);
    let x16: BytePoly_34 = bigint_nondet_quot!(ctx, x15, x0, 34);
    let x17: BytePoly_32 = bigint_nondet_rem!(ctx, x15, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x16, x0, 66), x17, 66), x15, 66),
        276359,
        4,
    )?;
    let x18: BytePoly_64 = bigint_mul!(x17, x17, 64);
    let x19: BytePoly_34 = bigint_nondet_quot!(ctx, x18, x0, 34);
    let x20: BytePoly_32 = bigint_nondet_rem!(ctx, x18, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x19, x0, 66), x20, 66), x18, 66),
        276359,
        4,
    )?;
    let x21: BytePoly_64 = bigint_mul!(x20, x20, 64);
    let x22: BytePoly_34 = bigint_nondet_quot!(ctx, x21, x0, 34);
    let x23: BytePoly_32 = bigint_nondet_rem!(ctx, x21, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x22, x0, 66), x23, 66), x21, 66),
        276359,
        4,
    )?;
    let x24: BytePoly_64 = bigint_mul!(x23, x23, 64);
    let x25: BytePoly_34 = bigint_nondet_quot!(ctx, x24, x0, 34);
    let x26: BytePoly_32 = bigint_nondet_rem!(ctx, x24, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x25, x0, 66), x26, 66), x24, 66),
        276359,
        4,
    )?;
    let x27: BytePoly_64 = bigint_mul!(x26, x26, 64);
    let x28: BytePoly_34 = bigint_nondet_quot!(ctx, x27, x0, 34);
    let x29: BytePoly_32 = bigint_nondet_rem!(ctx, x27, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x28, x0, 66), x29, 66), x27, 66),
        276359,
        4,
    )?;
    let x30: BytePoly_64 = bigint_mul!(x29, x29, 64);
    let x31: BytePoly_34 = bigint_nondet_quot!(ctx, x30, x0, 34);
    let x32: BytePoly_32 = bigint_nondet_rem!(ctx, x30, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x31, x0, 66), x32, 66), x30, 66),
        276359,
        4,
    )?;
    let x33: BytePoly_64 = bigint_mul!(x32, x32, 64);
    let x34: BytePoly_34 = bigint_nondet_quot!(ctx, x33, x0, 34);
    let x35: BytePoly_32 = bigint_nondet_rem!(ctx, x33, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x34, x0, 66), x35, 66), x33, 66),
        276359,
        4,
    )?;
    let x36: BytePoly_64 = bigint_mul!(x35, x35, 64);
    let x37: BytePoly_34 = bigint_nondet_quot!(ctx, x36, x0, 34);
    let x38: BytePoly_32 = bigint_nondet_rem!(ctx, x36, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x37, x0, 66), x38, 66), x36, 66),
        276359,
        4,
    )?;
    let x39: BytePoly_64 = bigint_mul!(x38, x38, 64);
    let x40: BytePoly_34 = bigint_nondet_quot!(ctx, x39, x0, 34);
    let x41: BytePoly_32 = bigint_nondet_rem!(ctx, x39, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x40, x0, 66), x41, 66), x39, 66),
        276359,
        4,
    )?;
    let x42: BytePoly_64 = bigint_mul!(x41, x41, 64);
    let x43: BytePoly_34 = bigint_nondet_quot!(ctx, x42, x0, 34);
    let x44: BytePoly_32 = bigint_nondet_rem!(ctx, x42, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x43, x0, 66), x44, 66), x42, 66),
        276359,
        4,
    )?;
    let x45: BytePoly_64 = bigint_mul!(x44, x44, 64);
    let x46: BytePoly_34 = bigint_nondet_quot!(ctx, x45, x0, 34);
    let x47: BytePoly_32 = bigint_nondet_rem!(ctx, x45, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x46, x0, 66), x47, 66), x45, 66),
        276359,
        4,
    )?;
    let x48: BytePoly_64 = bigint_mul!(x47, x47, 64);
    let x49: BytePoly_34 = bigint_nondet_quot!(ctx, x48, x0, 34);
    let x50: BytePoly_32 = bigint_nondet_rem!(ctx, x48, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x49, x0, 66), x50, 66), x48, 66),
        276359,
        4,
    )?;
    let x51: BytePoly_64 = bigint_mul!(x50, x1, 64);
    let x52: BytePoly_34 = bigint_nondet_quot!(ctx, x51, x0, 34);
    let x53: BytePoly_32 = bigint_nondet_rem!(ctx, x51, x0, 32);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x52, x0, 66), x53, 66), x51, 66),
        276359,
        4,
    )?;
    eqz(ctx, &bigint_sub!(x53, x2, 32), 34, 1)?;
    return Ok(());
}
pub fn rsa_3072_x15(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_384 = bigint_def!(ctx, 384, 0, 1);
    let x1: BytePoly_384 = bigint_def!(ctx, 384, 1, 1);
    let x2: BytePoly_384 = bigint_def!(ctx, 384, 2, 1);
    let x3: BytePoly_768 = bigint_mul!(x1, x1, 768);
    let x4: BytePoly_387 = bigint_nondet_quot!(ctx, x3, x0, 387);
    let x5: BytePoly_384 = bigint_nondet_rem!(ctx, x3, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x4, x0, 771), x5, 771), x3, 771),
        3145587,
        4,
    )?;
    let x6: BytePoly_768 = bigint_mul!(x5, x5, 768);
    let x7: BytePoly_387 = bigint_nondet_quot!(ctx, x6, x0, 387);
    let x8: BytePoly_384 = bigint_nondet_rem!(ctx, x6, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x7, x0, 771), x8, 771), x6, 771),
        3145587,
        4,
    )?;
    let x9: BytePoly_768 = bigint_mul!(x8, x8, 768);
    let x10: BytePoly_387 = bigint_nondet_quot!(ctx, x9, x0, 387);
    let x11: BytePoly_384 = bigint_nondet_rem!(ctx, x9, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x10, x0, 771), x11, 771), x9, 771),
        3145587,
        4,
    )?;
    let x12: BytePoly_768 = bigint_mul!(x11, x11, 768);
    let x13: BytePoly_387 = bigint_nondet_quot!(ctx, x12, x0, 387);
    let x14: BytePoly_384 = bigint_nondet_rem!(ctx, x12, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x13, x0, 771), x14, 771), x12, 771),
        3145587,
        4,
    )?;
    let x15: BytePoly_768 = bigint_mul!(x14, x14, 768);
    let x16: BytePoly_387 = bigint_nondet_quot!(ctx, x15, x0, 387);
    let x17: BytePoly_384 = bigint_nondet_rem!(ctx, x15, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x16, x0, 771), x17, 771), x15, 771),
        3145587,
        4,
    )?;
    let x18: BytePoly_768 = bigint_mul!(x17, x17, 768);
    let x19: BytePoly_387 = bigint_nondet_quot!(ctx, x18, x0, 387);
    let x20: BytePoly_384 = bigint_nondet_rem!(ctx, x18, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x19, x0, 771), x20, 771), x18, 771),
        3145587,
        4,
    )?;
    let x21: BytePoly_768 = bigint_mul!(x20, x20, 768);
    let x22: BytePoly_387 = bigint_nondet_quot!(ctx, x21, x0, 387);
    let x23: BytePoly_384 = bigint_nondet_rem!(ctx, x21, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x22, x0, 771), x23, 771), x21, 771),
        3145587,
        4,
    )?;
    let x24: BytePoly_768 = bigint_mul!(x23, x23, 768);
    let x25: BytePoly_387 = bigint_nondet_quot!(ctx, x24, x0, 387);
    let x26: BytePoly_384 = bigint_nondet_rem!(ctx, x24, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x25, x0, 771), x26, 771), x24, 771),
        3145587,
        4,
    )?;
    let x27: BytePoly_768 = bigint_mul!(x26, x26, 768);
    let x28: BytePoly_387 = bigint_nondet_quot!(ctx, x27, x0, 387);
    let x29: BytePoly_384 = bigint_nondet_rem!(ctx, x27, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x28, x0, 771), x29, 771), x27, 771),
        3145587,
        4,
    )?;
    let x30: BytePoly_768 = bigint_mul!(x29, x29, 768);
    let x31: BytePoly_387 = bigint_nondet_quot!(ctx, x30, x0, 387);
    let x32: BytePoly_384 = bigint_nondet_rem!(ctx, x30, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x31, x0, 771), x32, 771), x30, 771),
        3145587,
        4,
    )?;
    let x33: BytePoly_768 = bigint_mul!(x32, x32, 768);
    let x34: BytePoly_387 = bigint_nondet_quot!(ctx, x33, x0, 387);
    let x35: BytePoly_384 = bigint_nondet_rem!(ctx, x33, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x34, x0, 771), x35, 771), x33, 771),
        3145587,
        4,
    )?;
    let x36: BytePoly_768 = bigint_mul!(x35, x35, 768);
    let x37: BytePoly_387 = bigint_nondet_quot!(ctx, x36, x0, 387);
    let x38: BytePoly_384 = bigint_nondet_rem!(ctx, x36, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x37, x0, 771), x38, 771), x36, 771),
        3145587,
        4,
    )?;
    let x39: BytePoly_768 = bigint_mul!(x38, x38, 768);
    let x40: BytePoly_387 = bigint_nondet_quot!(ctx, x39, x0, 387);
    let x41: BytePoly_384 = bigint_nondet_rem!(ctx, x39, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x40, x0, 771), x41, 771), x39, 771),
        3145587,
        4,
    )?;
    let x42: BytePoly_768 = bigint_mul!(x41, x41, 768);
    let x43: BytePoly_387 = bigint_nondet_quot!(ctx, x42, x0, 387);
    let x44: BytePoly_384 = bigint_nondet_rem!(ctx, x42, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x43, x0, 771), x44, 771), x42, 771),
        3145587,
        4,
    )?;
    let x45: BytePoly_768 = bigint_mul!(x44, x44, 768);
    let x46: BytePoly_387 = bigint_nondet_quot!(ctx, x45, x0, 387);
    let x47: BytePoly_384 = bigint_nondet_rem!(ctx, x45, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x46, x0, 771), x47, 771), x45, 771),
        3145587,
        4,
    )?;
    let x48: BytePoly_768 = bigint_mul!(x47, x47, 768);
    let x49: BytePoly_387 = bigint_nondet_quot!(ctx, x48, x0, 387);
    let x50: BytePoly_384 = bigint_nondet_rem!(ctx, x48, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x49, x0, 771), x50, 771), x48, 771),
        3145587,
        4,
    )?;
    let x51: BytePoly_768 = bigint_mul!(x50, x1, 768);
    let x52: BytePoly_387 = bigint_nondet_quot!(ctx, x51, x0, 387);
    let x53: BytePoly_384 = bigint_nondet_rem!(ctx, x51, x0, 384);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x52, x0, 771), x53, 771), x51, 771),
        3145587,
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
    let x5: BytePoly_2 = bigint_mul!(x1, x4, 2);
    let x6: BytePoly_3 = bigint_nondet_quot!(ctx, x5, x2, 3);
    let x7: BytePoly_1 = bigint_nondet_rem!(ctx, x5, x2, 1);
    eqz(
        ctx,
        &bigint_sub!(bigint_add!(bigint_mul!(x6, x2, 4), x7, 4), x5, 4),
        24387,
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
    eqz(ctx, &bigint_sub!(bigint_add!(x1, x0, 2), x2, 3), 34, 1)?;
    return Ok(());
}
pub fn const_add_alt_test_16(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_2 = bigint_const!(ctx, 50, 84);
    let x1: BytePoly_2 = bigint_def!(ctx, 2, 0, 1);
    let x2: BytePoly_3 = bigint_def!(ctx, 3, 1, 1);
    eqz(ctx, &bigint_sub!(bigint_add!(x1, x0, 2), x2, 3), 34, 1)?;
    return Ok(());
}
pub fn const_mul_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_2 = bigint_const!(ctx, 50, 84);
    let x1: BytePoly_1 = bigint_def!(ctx, 1, 0, 1);
    let x2: BytePoly_3 = bigint_def!(ctx, 3, 1, 1);
    eqz(ctx, &bigint_sub!(bigint_mul!(x1, x0, 3), x2, 3), 16259, 2)?;
    return Ok(());
}
pub fn add_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_1 = bigint_def!(ctx, 1, 0, 1);
    let x1: BytePoly_1 = bigint_def!(ctx, 1, 1, 1);
    let x2: BytePoly_2 = bigint_def!(ctx, 2, 2, 1);
    eqz(ctx, &bigint_sub!(bigint_add!(x0, x1, 1), x2, 2), 34, 1)?;
    return Ok(());
}
pub fn add_test_16(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_2 = bigint_def!(ctx, 2, 0, 1);
    let x1: BytePoly_2 = bigint_def!(ctx, 2, 1, 1);
    let x2: BytePoly_3 = bigint_def!(ctx, 3, 2, 1);
    eqz(ctx, &bigint_sub!(bigint_add!(x0, x1, 2), x2, 3), 34, 1)?;
    return Ok(());
}
pub fn add_test_128(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_16 = bigint_def!(ctx, 16, 0, 1);
    let x1: BytePoly_16 = bigint_def!(ctx, 16, 1, 1);
    let x2: BytePoly_17 = bigint_def!(ctx, 17, 2, 1);
    eqz(ctx, &bigint_sub!(bigint_add!(x0, x1, 16), x2, 17), 34, 1)?;
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
    eqz(ctx, &bigint_sub!(bigint_sub!(x0, x1, 1), x2, 1), 34, 1)?;
    return Ok(());
}
pub fn sub_test_128(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_16 = bigint_def!(ctx, 16, 0, 1);
    let x1: BytePoly_16 = bigint_def!(ctx, 16, 1, 1);
    let x2: BytePoly_16 = bigint_def!(ctx, 16, 2, 1);
    eqz(ctx, &bigint_sub!(bigint_sub!(x0, x1, 16), x2, 16), 34, 1)?;
    return Ok(());
}
pub fn mul_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_1 = bigint_def!(ctx, 1, 0, 1);
    let x1: BytePoly_1 = bigint_def!(ctx, 1, 1, 1);
    let x2: BytePoly_2 = bigint_def!(ctx, 2, 2, 1);
    eqz(ctx, &bigint_sub!(bigint_mul!(x0, x1, 2), x2, 2), 8131, 2)?;
    return Ok(());
}
pub fn mul_test_128(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly_16 = bigint_def!(ctx, 16, 0, 1);
    let x1: BytePoly_16 = bigint_def!(ctx, 16, 1, 1);
    let x2: BytePoly_32 = bigint_def!(ctx, 32, 2, 1);
    eqz(
        ctx,
        &bigint_sub!(bigint_mul!(x0, x1, 32), x2, 32),
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
        &bigint_sub!(bigint_add!(bigint_mul!(x3, x1, 2), x4, 2), x0, 2),
        8131,
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
        &bigint_sub!(bigint_add!(bigint_mul!(x3, x1, 32), x4, 32), x0, 32),
        130053,
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
bigint_program_list! {rsa_256_x1, rsa_256_x2, rsa_3072_x15, nondet_inv_test_8, const_add_test_8, const_add_alt_test_16, const_mul_test_8, add_test_8, add_test_16, add_test_128, const_one_test_8, const_twobyte_test_16, sub_test_8, sub_test_128, mul_test_8, mul_test_128, reduce_test_8, reduce_test_128}
