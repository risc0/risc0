// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use getrandom::Error;

/// This is a getrandom handler for the zkvm. It's intended to hook into a
/// getrandom crate or a dependent of the getrandom crate used by the guest code.
#[cfg(feature = "getrandom")]
#[no_mangle]
unsafe extern "Rust" fn __getrandom_v03_custom(dest_ptr: *mut u8, len: usize) -> Result<(), Error> {
    use crate::{syscall::sys_rand, WORD_SIZE};

    let dest = core::slice::from_raw_parts_mut(dest_ptr, len);

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

#[cfg(not(feature = "getrandom"))]
#[no_mangle]
unsafe extern "Rust" fn __getrandom_v03_custom(
    _dest_ptr: *mut u8,
    _len: usize,
) -> Result<(), Error> {
    panic!(
        r#"

WARNING: `getrandom()` called from guest.
=========================================

This panic was generated from the guest program calling `getrandom()`.
Using randomness in the zkVM requires careful attention to your
application’s security requirements. Therefore, the default behavior is
for the zkVM to generate this panic message when the guest calls
`getrandom()`. If you wrote this guest program, it is crucial that you
understand the implications of using randomness in your guest code and
make changes to fit your needs.


The zkVM supports providing random data from the host in response to
`getrandom()`. When the randomness is being used to protect private data, this
is a good option. However, it is not appropriate for all use cases. Consider a
situation when random data is needed to ensure the honesty of the prover (e.g.
to flip a coin for a game between the prover and verifier). In this scenario,
host provided randomness is not suitable because the prover may alter the source
of randomness. For such use cases, great care must be taken to provide a source
of randomness that the prover cannot manipulate or predict. Host provided
randomness can be enabled with the `getrandom` feature flag on the `risc0-zkvm`
crate used for the guest.

"#
    );
}

/// This entrypoint for getrandom is used for versions < 0.3
#[no_mangle]
unsafe fn __getrandom_custom(dest: *mut u8, len: usize) -> u32 {
    __getrandom_v03_custom(dest, len)
        .map_err(|e| e.raw_os_error().unwrap_or(2))
        .err()
        .unwrap_or(0) as u32
}
