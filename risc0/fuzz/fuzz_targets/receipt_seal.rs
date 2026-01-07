#![no_main]

use libfuzzer_sys::fuzz_target;

fuzz_target!(|data: &[u8]| {
    // Reinterpret the aligned portion of the fuzzing data as a seal.
    // This drops any unaligned prefix or postfix.
    let seal = bytemuck::pod_align_to(data).1;

    // Call the verify function. If it panics, then the fuzzer has found an example.
    let _ = risc0_circuit_rv32im::verify(seal);
});
