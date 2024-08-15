pub fn rsa_256_x1(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 32, 0, 1)?;
    let x1: BytePoly = def(ctx, 32, 1, 1)?;
    let x2: BytePoly = def(ctx, 32, 2, 1)?;
    let x3: BytePoly = mul(&x1, &x1)?;
    let x4: BytePoly = nondet_quot(ctx, &x3, &x0, 34)?;
    let x5: BytePoly = nondet_rem(ctx, &x3, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x4, &x0)?, &x5)?, &x3)?, 276359, 4)?;
    let x6: BytePoly = mul(&x5, &x5)?;
    let x7: BytePoly = nondet_quot(ctx, &x6, &x0, 34)?;
    let x8: BytePoly = nondet_rem(ctx, &x6, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x7, &x0)?, &x8)?, &x6)?, 276359, 4)?;
    let x9: BytePoly = mul(&x8, &x8)?;
    let x10: BytePoly = nondet_quot(ctx, &x9, &x0, 34)?;
    let x11: BytePoly = nondet_rem(ctx, &x9, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x10, &x0)?, &x11)?, &x9)?, 276359, 4)?;
    let x12: BytePoly = mul(&x11, &x11)?;
    let x13: BytePoly = nondet_quot(ctx, &x12, &x0, 34)?;
    let x14: BytePoly = nondet_rem(ctx, &x12, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x13, &x0)?, &x14)?, &x12)?, 276359, 4)?;
    let x15: BytePoly = mul(&x14, &x14)?;
    let x16: BytePoly = nondet_quot(ctx, &x15, &x0, 34)?;
    let x17: BytePoly = nondet_rem(ctx, &x15, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x16, &x0)?, &x17)?, &x15)?, 276359, 4)?;
    let x18: BytePoly = mul(&x17, &x17)?;
    let x19: BytePoly = nondet_quot(ctx, &x18, &x0, 34)?;
    let x20: BytePoly = nondet_rem(ctx, &x18, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x19, &x0)?, &x20)?, &x18)?, 276359, 4)?;
    let x21: BytePoly = mul(&x20, &x20)?;
    let x22: BytePoly = nondet_quot(ctx, &x21, &x0, 34)?;
    let x23: BytePoly = nondet_rem(ctx, &x21, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x22, &x0)?, &x23)?, &x21)?, 276359, 4)?;
    let x24: BytePoly = mul(&x23, &x23)?;
    let x25: BytePoly = nondet_quot(ctx, &x24, &x0, 34)?;
    let x26: BytePoly = nondet_rem(ctx, &x24, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x25, &x0)?, &x26)?, &x24)?, 276359, 4)?;
    let x27: BytePoly = mul(&x26, &x26)?;
    let x28: BytePoly = nondet_quot(ctx, &x27, &x0, 34)?;
    let x29: BytePoly = nondet_rem(ctx, &x27, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x28, &x0)?, &x29)?, &x27)?, 276359, 4)?;
    let x30: BytePoly = mul(&x29, &x29)?;
    let x31: BytePoly = nondet_quot(ctx, &x30, &x0, 34)?;
    let x32: BytePoly = nondet_rem(ctx, &x30, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x31, &x0)?, &x32)?, &x30)?, 276359, 4)?;
    let x33: BytePoly = mul(&x32, &x32)?;
    let x34: BytePoly = nondet_quot(ctx, &x33, &x0, 34)?;
    let x35: BytePoly = nondet_rem(ctx, &x33, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x34, &x0)?, &x35)?, &x33)?, 276359, 4)?;
    let x36: BytePoly = mul(&x35, &x35)?;
    let x37: BytePoly = nondet_quot(ctx, &x36, &x0, 34)?;
    let x38: BytePoly = nondet_rem(ctx, &x36, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x37, &x0)?, &x38)?, &x36)?, 276359, 4)?;
    let x39: BytePoly = mul(&x38, &x38)?;
    let x40: BytePoly = nondet_quot(ctx, &x39, &x0, 34)?;
    let x41: BytePoly = nondet_rem(ctx, &x39, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x40, &x0)?, &x41)?, &x39)?, 276359, 4)?;
    let x42: BytePoly = mul(&x41, &x41)?;
    let x43: BytePoly = nondet_quot(ctx, &x42, &x0, 34)?;
    let x44: BytePoly = nondet_rem(ctx, &x42, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x43, &x0)?, &x44)?, &x42)?, 276359, 4)?;
    let x45: BytePoly = mul(&x44, &x44)?;
    let x46: BytePoly = nondet_quot(ctx, &x45, &x0, 34)?;
    let x47: BytePoly = nondet_rem(ctx, &x45, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x46, &x0)?, &x47)?, &x45)?, 276359, 4)?;
    let x48: BytePoly = mul(&x47, &x47)?;
    let x49: BytePoly = nondet_quot(ctx, &x48, &x0, 34)?;
    let x50: BytePoly = nondet_rem(ctx, &x48, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x49, &x0)?, &x50)?, &x48)?, 276359, 4)?;
    let x51: BytePoly = mul(&x50, &x1)?;
    let x52: BytePoly = nondet_quot(ctx, &x51, &x0, 34)?;
    let x53: BytePoly = nondet_rem(ctx, &x51, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x52, &x0)?, &x53)?, &x51)?, 276359, 4)?;
    eqz(ctx, &sub(&x53, &x2)?, 34, 1)?;
    return Ok(());
}
pub fn rsa_256_x2(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 32, 0, 1)?;
    let x1: BytePoly = def(ctx, 32, 1, 1)?;
    let x2: BytePoly = def(ctx, 32, 2, 1)?;
    let x3: BytePoly = mul(&x1, &x1)?;
    let x4: BytePoly = nondet_quot(ctx, &x3, &x0, 34)?;
    let x5: BytePoly = nondet_rem(ctx, &x3, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x4, &x0)?, &x5)?, &x3)?, 276359, 4)?;
    let x6: BytePoly = mul(&x5, &x5)?;
    let x7: BytePoly = nondet_quot(ctx, &x6, &x0, 34)?;
    let x8: BytePoly = nondet_rem(ctx, &x6, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x7, &x0)?, &x8)?, &x6)?, 276359, 4)?;
    let x9: BytePoly = mul(&x8, &x8)?;
    let x10: BytePoly = nondet_quot(ctx, &x9, &x0, 34)?;
    let x11: BytePoly = nondet_rem(ctx, &x9, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x10, &x0)?, &x11)?, &x9)?, 276359, 4)?;
    let x12: BytePoly = mul(&x11, &x11)?;
    let x13: BytePoly = nondet_quot(ctx, &x12, &x0, 34)?;
    let x14: BytePoly = nondet_rem(ctx, &x12, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x13, &x0)?, &x14)?, &x12)?, 276359, 4)?;
    let x15: BytePoly = mul(&x14, &x14)?;
    let x16: BytePoly = nondet_quot(ctx, &x15, &x0, 34)?;
    let x17: BytePoly = nondet_rem(ctx, &x15, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x16, &x0)?, &x17)?, &x15)?, 276359, 4)?;
    let x18: BytePoly = mul(&x17, &x17)?;
    let x19: BytePoly = nondet_quot(ctx, &x18, &x0, 34)?;
    let x20: BytePoly = nondet_rem(ctx, &x18, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x19, &x0)?, &x20)?, &x18)?, 276359, 4)?;
    let x21: BytePoly = mul(&x20, &x20)?;
    let x22: BytePoly = nondet_quot(ctx, &x21, &x0, 34)?;
    let x23: BytePoly = nondet_rem(ctx, &x21, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x22, &x0)?, &x23)?, &x21)?, 276359, 4)?;
    let x24: BytePoly = mul(&x23, &x23)?;
    let x25: BytePoly = nondet_quot(ctx, &x24, &x0, 34)?;
    let x26: BytePoly = nondet_rem(ctx, &x24, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x25, &x0)?, &x26)?, &x24)?, 276359, 4)?;
    let x27: BytePoly = mul(&x26, &x26)?;
    let x28: BytePoly = nondet_quot(ctx, &x27, &x0, 34)?;
    let x29: BytePoly = nondet_rem(ctx, &x27, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x28, &x0)?, &x29)?, &x27)?, 276359, 4)?;
    let x30: BytePoly = mul(&x29, &x29)?;
    let x31: BytePoly = nondet_quot(ctx, &x30, &x0, 34)?;
    let x32: BytePoly = nondet_rem(ctx, &x30, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x31, &x0)?, &x32)?, &x30)?, 276359, 4)?;
    let x33: BytePoly = mul(&x32, &x32)?;
    let x34: BytePoly = nondet_quot(ctx, &x33, &x0, 34)?;
    let x35: BytePoly = nondet_rem(ctx, &x33, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x34, &x0)?, &x35)?, &x33)?, 276359, 4)?;
    let x36: BytePoly = mul(&x35, &x35)?;
    let x37: BytePoly = nondet_quot(ctx, &x36, &x0, 34)?;
    let x38: BytePoly = nondet_rem(ctx, &x36, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x37, &x0)?, &x38)?, &x36)?, 276359, 4)?;
    let x39: BytePoly = mul(&x38, &x38)?;
    let x40: BytePoly = nondet_quot(ctx, &x39, &x0, 34)?;
    let x41: BytePoly = nondet_rem(ctx, &x39, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x40, &x0)?, &x41)?, &x39)?, 276359, 4)?;
    let x42: BytePoly = mul(&x41, &x41)?;
    let x43: BytePoly = nondet_quot(ctx, &x42, &x0, 34)?;
    let x44: BytePoly = nondet_rem(ctx, &x42, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x43, &x0)?, &x44)?, &x42)?, 276359, 4)?;
    let x45: BytePoly = mul(&x44, &x44)?;
    let x46: BytePoly = nondet_quot(ctx, &x45, &x0, 34)?;
    let x47: BytePoly = nondet_rem(ctx, &x45, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x46, &x0)?, &x47)?, &x45)?, 276359, 4)?;
    let x48: BytePoly = mul(&x47, &x47)?;
    let x49: BytePoly = nondet_quot(ctx, &x48, &x0, 34)?;
    let x50: BytePoly = nondet_rem(ctx, &x48, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x49, &x0)?, &x50)?, &x48)?, 276359, 4)?;
    let x51: BytePoly = mul(&x50, &x1)?;
    let x52: BytePoly = nondet_quot(ctx, &x51, &x0, 34)?;
    let x53: BytePoly = nondet_rem(ctx, &x51, &x0, 32)?;
    eqz(ctx, &sub(&add(&mul(&x52, &x0)?, &x53)?, &x51)?, 276359, 4)?;
    eqz(ctx, &sub(&x53, &x2)?, 34, 1)?;
    return Ok(());
}
pub fn rsa_3072_x15(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 384, 0, 1)?;
    let x1: BytePoly = def(ctx, 384, 1, 1)?;
    let x2: BytePoly = def(ctx, 384, 2, 1)?;
    let x3: BytePoly = mul(&x1, &x1)?;
    let x4: BytePoly = nondet_quot(ctx, &x3, &x0, 387)?;
    let x5: BytePoly = nondet_rem(ctx, &x3, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x4, &x0)?, &x5)?, &x3)?, 3145587, 4)?;
    let x6: BytePoly = mul(&x5, &x5)?;
    let x7: BytePoly = nondet_quot(ctx, &x6, &x0, 387)?;
    let x8: BytePoly = nondet_rem(ctx, &x6, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x7, &x0)?, &x8)?, &x6)?, 3145587, 4)?;
    let x9: BytePoly = mul(&x8, &x8)?;
    let x10: BytePoly = nondet_quot(ctx, &x9, &x0, 387)?;
    let x11: BytePoly = nondet_rem(ctx, &x9, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x10, &x0)?, &x11)?, &x9)?, 3145587, 4)?;
    let x12: BytePoly = mul(&x11, &x11)?;
    let x13: BytePoly = nondet_quot(ctx, &x12, &x0, 387)?;
    let x14: BytePoly = nondet_rem(ctx, &x12, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x13, &x0)?, &x14)?, &x12)?, 3145587, 4)?;
    let x15: BytePoly = mul(&x14, &x14)?;
    let x16: BytePoly = nondet_quot(ctx, &x15, &x0, 387)?;
    let x17: BytePoly = nondet_rem(ctx, &x15, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x16, &x0)?, &x17)?, &x15)?, 3145587, 4)?;
    let x18: BytePoly = mul(&x17, &x17)?;
    let x19: BytePoly = nondet_quot(ctx, &x18, &x0, 387)?;
    let x20: BytePoly = nondet_rem(ctx, &x18, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x19, &x0)?, &x20)?, &x18)?, 3145587, 4)?;
    let x21: BytePoly = mul(&x20, &x20)?;
    let x22: BytePoly = nondet_quot(ctx, &x21, &x0, 387)?;
    let x23: BytePoly = nondet_rem(ctx, &x21, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x22, &x0)?, &x23)?, &x21)?, 3145587, 4)?;
    let x24: BytePoly = mul(&x23, &x23)?;
    let x25: BytePoly = nondet_quot(ctx, &x24, &x0, 387)?;
    let x26: BytePoly = nondet_rem(ctx, &x24, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x25, &x0)?, &x26)?, &x24)?, 3145587, 4)?;
    let x27: BytePoly = mul(&x26, &x26)?;
    let x28: BytePoly = nondet_quot(ctx, &x27, &x0, 387)?;
    let x29: BytePoly = nondet_rem(ctx, &x27, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x28, &x0)?, &x29)?, &x27)?, 3145587, 4)?;
    let x30: BytePoly = mul(&x29, &x29)?;
    let x31: BytePoly = nondet_quot(ctx, &x30, &x0, 387)?;
    let x32: BytePoly = nondet_rem(ctx, &x30, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x31, &x0)?, &x32)?, &x30)?, 3145587, 4)?;
    let x33: BytePoly = mul(&x32, &x32)?;
    let x34: BytePoly = nondet_quot(ctx, &x33, &x0, 387)?;
    let x35: BytePoly = nondet_rem(ctx, &x33, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x34, &x0)?, &x35)?, &x33)?, 3145587, 4)?;
    let x36: BytePoly = mul(&x35, &x35)?;
    let x37: BytePoly = nondet_quot(ctx, &x36, &x0, 387)?;
    let x38: BytePoly = nondet_rem(ctx, &x36, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x37, &x0)?, &x38)?, &x36)?, 3145587, 4)?;
    let x39: BytePoly = mul(&x38, &x38)?;
    let x40: BytePoly = nondet_quot(ctx, &x39, &x0, 387)?;
    let x41: BytePoly = nondet_rem(ctx, &x39, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x40, &x0)?, &x41)?, &x39)?, 3145587, 4)?;
    let x42: BytePoly = mul(&x41, &x41)?;
    let x43: BytePoly = nondet_quot(ctx, &x42, &x0, 387)?;
    let x44: BytePoly = nondet_rem(ctx, &x42, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x43, &x0)?, &x44)?, &x42)?, 3145587, 4)?;
    let x45: BytePoly = mul(&x44, &x44)?;
    let x46: BytePoly = nondet_quot(ctx, &x45, &x0, 387)?;
    let x47: BytePoly = nondet_rem(ctx, &x45, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x46, &x0)?, &x47)?, &x45)?, 3145587, 4)?;
    let x48: BytePoly = mul(&x47, &x47)?;
    let x49: BytePoly = nondet_quot(ctx, &x48, &x0, 387)?;
    let x50: BytePoly = nondet_rem(ctx, &x48, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x49, &x0)?, &x50)?, &x48)?, 3145587, 4)?;
    let x51: BytePoly = mul(&x50, &x1)?;
    let x52: BytePoly = nondet_quot(ctx, &x51, &x0, 387)?;
    let x53: BytePoly = nondet_rem(ctx, &x51, &x0, 384)?;
    eqz(ctx, &sub(&add(&mul(&x52, &x0)?, &x53)?, &x51)?, 3145587, 4)?;
    eqz(ctx, &sub(&x53, &x2)?, 34, 1)?;
    return Ok(());
}
pub fn nondet_inv_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = bigint_const!(ctx, 1);
    let x1: BytePoly = def(ctx, 1, 0, 1)?;
    let x2: BytePoly = def(ctx, 1, 1, 1)?;
    let x3: BytePoly = nondet_inv(ctx, &x1, &x2, 1)?;
    let x4: BytePoly = mul(&x1, &x3)?;
    let x5: BytePoly = nondet_quot(ctx, &x4, &x2, 3)?;
    let x6: BytePoly = nondet_rem(ctx, &x4, &x2, 1)?;
    eqz(ctx, &sub(&add(&mul(&x5, &x2)?, &x6)?, &x4)?, 24387, 2)?;
    eqz(ctx, &sub(&x6, &x0)?, 34, 1)?;
    return Ok(());
}
pub fn const_add_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = bigint_const!(ctx, 71, 71);
    let x1: BytePoly = def(ctx, 1, 0, 1)?;
    let x2: BytePoly = def(ctx, 3, 1, 1)?;
    eqz(ctx, &sub(&add(&x1, &x0)?, &x2)?, 34, 1)?;
    return Ok(());
}
pub fn const_add_alt_test_16(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = bigint_const!(ctx, 50, 84);
    let x1: BytePoly = def(ctx, 2, 0, 1)?;
    let x2: BytePoly = def(ctx, 3, 1, 1)?;
    eqz(ctx, &sub(&add(&x1, &x0)?, &x2)?, 34, 1)?;
    return Ok(());
}
pub fn const_mul_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = bigint_const!(ctx, 50, 84);
    let x1: BytePoly = def(ctx, 1, 0, 1)?;
    let x2: BytePoly = def(ctx, 3, 1, 1)?;
    eqz(ctx, &sub(&mul(&x1, &x0)?, &x2)?, 16259, 2)?;
    return Ok(());
}
pub fn add_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 1, 0, 1)?;
    let x1: BytePoly = def(ctx, 1, 1, 1)?;
    let x2: BytePoly = def(ctx, 2, 2, 1)?;
    eqz(ctx, &sub(&add(&x0, &x1)?, &x2)?, 34, 1)?;
    return Ok(());
}
pub fn add_test_16(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 2, 0, 1)?;
    let x1: BytePoly = def(ctx, 2, 1, 1)?;
    let x2: BytePoly = def(ctx, 3, 2, 1)?;
    eqz(ctx, &sub(&add(&x0, &x1)?, &x2)?, 34, 1)?;
    return Ok(());
}
pub fn add_test_128(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 16, 0, 1)?;
    let x1: BytePoly = def(ctx, 16, 1, 1)?;
    let x2: BytePoly = def(ctx, 17, 2, 1)?;
    eqz(ctx, &sub(&add(&x0, &x1)?, &x2)?, 34, 1)?;
    return Ok(());
}
pub fn const_one_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = bigint_const!(ctx, 1);
    let x1: BytePoly = def(ctx, 1, 0, 1)?;
    eqz(ctx, &sub(&x0, &x1)?, 34, 1)?;
    return Ok(());
}
pub fn const_twobyte_test_16(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = bigint_const!(ctx, 52, 18);
    let x1: BytePoly = def(ctx, 2, 0, 1)?;
    eqz(ctx, &sub(&x0, &x1)?, 34, 1)?;
    return Ok(());
}
pub fn sub_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 1, 0, 1)?;
    let x1: BytePoly = def(ctx, 1, 1, 1)?;
    let x2: BytePoly = def(ctx, 1, 2, 1)?;
    eqz(ctx, &sub(&sub(&x0, &x1)?, &x2)?, 34, 1)?;
    return Ok(());
}
pub fn sub_test_128(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 16, 0, 1)?;
    let x1: BytePoly = def(ctx, 16, 1, 1)?;
    let x2: BytePoly = def(ctx, 16, 2, 1)?;
    eqz(ctx, &sub(&sub(&x0, &x1)?, &x2)?, 34, 1)?;
    return Ok(());
}
pub fn mul_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 1, 0, 1)?;
    let x1: BytePoly = def(ctx, 1, 1, 1)?;
    let x2: BytePoly = def(ctx, 2, 2, 1)?;
    eqz(ctx, &sub(&mul(&x0, &x1)?, &x2)?, 8131, 2)?;
    return Ok(());
}
pub fn mul_test_128(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 16, 0, 1)?;
    let x1: BytePoly = def(ctx, 16, 1, 1)?;
    let x2: BytePoly = def(ctx, 32, 2, 1)?;
    eqz(ctx, &sub(&mul(&x0, &x1)?, &x2)?, 130053, 4)?;
    return Ok(());
}
pub fn reduce_test_8(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 1, 0, 1)?;
    let x1: BytePoly = def(ctx, 1, 1, 1)?;
    let x2: BytePoly = def(ctx, 1, 2, 1)?;
    let x3: BytePoly = nondet_quot(ctx, &x0, &x1, 1)?;
    let x4: BytePoly = nondet_rem(ctx, &x0, &x1, 1)?;
    eqz(ctx, &sub(&add(&mul(&x3, &x1)?, &x4)?, &x0)?, 8131, 2)?;
    eqz(ctx, &sub(&x4, &x2)?, 34, 1)?;
    return Ok(());
}
pub fn reduce_test_128(ctx: &mut BigIntContext) -> Result<()> {
    let x0: BytePoly = def(ctx, 16, 0, 1)?;
    let x1: BytePoly = def(ctx, 16, 1, 1)?;
    let x2: BytePoly = def(ctx, 16, 2, 1)?;
    let x3: BytePoly = nondet_quot(ctx, &x0, &x1, 16)?;
    let x4: BytePoly = nondet_rem(ctx, &x0, &x1, 16)?;
    eqz(ctx, &sub(&add(&mul(&x3, &x1)?, &x4)?, &x0)?, 130053, 4)?;
    eqz(ctx, &sub(&x4, &x2)?, 34, 1)?;
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
bigint_witness_info!(/*bits=*/8, /*label=*/1, /*public=*/ true, /*min_bits=*/7)}
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
