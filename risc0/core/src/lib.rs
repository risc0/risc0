use rand_core::{OsRng, RngCore};

#[no_mangle]
pub extern "C" fn rust_rand_u32() -> u32 {
    OsRng.next_u32()
}
