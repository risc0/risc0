use std::os::raw::{c_char, c_void};

pub enum RawString {}

#[repr(C)]
pub struct RawError {
    pub msg: *const RawString,
}

impl Default for RawError {
    fn default() -> Self {
        Self {
            msg: std::ptr::null(),
        }
    }
}

// Babybear types
const EXT_SIZE: usize = 4;
#[repr(transparent)]
pub struct BabyBearElemSys(pub u32);

#[repr(transparent)]
pub struct BabyBearExtElemSys(pub [BabyBearElemSys; EXT_SIZE]);

pub type Callback = unsafe extern "C" fn(
    ctx: *mut c_void,
    name: *const c_char,
    extra: *const c_char,
    args_ptr: *const BabyBearElemSys,
    args_len: usize,
    outs_ptr: *mut BabyBearElemSys,
    outs_len: usize,
) -> bool;

extern "C" {
    pub fn risc0_circuit_string_ptr(str: *const RawString) -> *const c_char;

    pub fn risc0_circuit_string_free(str: *const RawString);

    pub fn risc0_circuit_rv32im_step_compute_accum(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElemSys,
        args_len: usize,
    ) -> BabyBearElemSys;

    pub fn risc0_circuit_rv32im_step_verify_accum(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElemSys,
        args_len: usize,
    ) -> BabyBearElemSys;

    pub fn risc0_circuit_rv32im_step_exec(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElemSys,
        args_len: usize,
    ) -> BabyBearElemSys;

    pub fn risc0_circuit_rv32im_step_verify_bytes(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElemSys,
        args_len: usize,
    ) -> BabyBearElemSys;

    pub fn risc0_circuit_rv32im_step_verify_mem(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElemSys,
        args_len: usize,
    ) -> BabyBearElemSys;

    pub fn risc0_circuit_rv32im_poly_fp(
        cycle: usize,
        steps: usize,
        poly_mix: *const BabyBearExtElemSys,
        args_ptr: *const *const BabyBearElemSys,
        args_len: usize,
    ) -> BabyBearExtElemSys;
}
