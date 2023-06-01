use getrandom::{register_custom_getrandom, Error};

use crate::{syscall::sys_rand, WORD_SIZE};

extern crate alloc;

/// This is a getrandom handler for the zkvm. It's intended to hook into a
/// getrandom crate or a depdent of the getrandom crate used by the guest code.
pub fn zkvm_getrandom(dest: &mut [u8]) -> Result<(), Error> {
    if dest.is_empty() {
        return Ok(());
    }

    let words = (dest.len() + WORD_SIZE - 1) / WORD_SIZE;
    let mut buf = alloc::vec![0u32; words];
    unsafe {
        sys_rand(buf.as_mut_ptr(), words);
    }
    dest.clone_from_slice(&bytemuck::cast_slice(buf.as_slice())[..dest.len()]);
    Ok(())
}

register_custom_getrandom!(zkvm_getrandom);
