use getrandom::{register_custom_getrandom, Error};

use crate::{syscall::sys_rand, WORD_SIZE};

/// This is a getrandom handler for the zkvm. It's intended to hook into a
/// getrandom crate or a depdent of the getrandom crate used by the guest code.
pub fn zkvm_getrandom(dest: &mut [u8]) -> Result<(), Error> {
    if dest.is_empty() {
        return Ok(());
    }

    let (head, aligned, tail) = bytemuck::pod_align_to_mut::<_, u32>(dest);

    // Fill the aligned portion of the dest buffer with random words.
    // sys_rand uses copy-in to fill the buffer at 4-words per cycle.
    if aligned.len() > 0 {
        unsafe {
            sys_rand(aligned.as_mut_ptr(), aligned.len());
        }
    }

    // Up to 4 bytes may be split between the head and tail.
    // Sample an additional word and do an unaligned write to fill the last parts.
    if head.len() > 0 || tail.len() > 0 {
        assert!(head.len() < WORD_SIZE);
        assert!(tail.len() < WORD_SIZE);

        let mut words = [0u32; 2];
        unsafe {
            sys_rand(words.as_mut_ptr(), 2);
        }

        head.copy_from_slice(&words[0].to_ne_bytes()[..head.len()]);
        tail.copy_from_slice(&words[1].to_ne_bytes()[..tail.len()]);
    }
    Ok(())
}

register_custom_getrandom!(zkvm_getrandom);
