#[no_mangle]
pub extern "C" fn rust_rand_random() -> u32 {
    rand::random()
}
