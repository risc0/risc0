use core::{ptr, slice};
use risc0_binfmt::tagged_struct;
use risc0_zkp::core::digest::Digest;
use risc0_zkp::core::hash::sha::guest::Impl;
use risc0_zkp::core::hash::sha::rust_crypto::{Digest as _, Sha256};
use risc0_zkvm_platform::fileno;
use risc0_zkvm_platform::syscall::{sys_halt, sys_panic, sys_write};

const ERR_FREED: &[u8] = b"error: sha256_state has not been initialized or has already been freed";

/// C wrapper for guest sha256 implementation.
///
/// This is used in the guest to generate any sha256
/// hash, but also to accumulate the Sha256 state of all data written to journal through
/// [commit].
///
/// Initialize with [init_sha256], and can retrieve the final hash through [sha256_finalize],
/// or pass it into [zkvm_exit] to exit the program.
#[repr(C)]
#[allow(non_camel_case_types)]
pub struct sha256_state {
    inner: *mut Sha256<Impl>,
}

#[no_mangle]
pub extern "C" fn init_sha256() -> *mut sha256_state {
    Box::into_raw(Box::new(sha256_state {
        inner: Box::into_raw(Box::new(Sha256::new())),
    }))
}

/// Update the sha256 state with the bytes passed in.
///
/// # Safety
/// This is safe assuming that pointers have not been manually modified, and len does not go past
/// the buffer of the data in memory.
#[no_mangle]
pub unsafe extern "C" fn sha256_update(hasher: *mut sha256_state, data: *const u8, len: u32) {
    if hasher.is_null() || data.is_null() || (*hasher).inner.is_null() {
        sys_panic(ERR_FREED.as_ptr(), ERR_FREED.len())
    }
    let data_slice = slice::from_raw_parts(data, len as usize);
    (*(*hasher).inner).update(data_slice);
}

/// Finalize the hasher, returning an allocated digest of the output hash.
///
/// Note: This digest is leaked, as the zkvm currently uses a bump allocator so it does not need to
/// be freed. If switching allocator, should implement a free method for [Digest].
///
/// # Safety
/// Assumes [sha256_state] has not been freed previously.
#[no_mangle]
pub unsafe extern "C" fn sha256_finalize(hasher: *mut sha256_state) -> *mut Digest {
    if hasher.is_null() || (*hasher).inner.is_null() {
        sys_panic(ERR_FREED.as_ptr(), ERR_FREED.len())
    }
    let inner = unsafe { Box::from_raw((*hasher).inner) };
    let result = inner.finalize();
    // Free hasher to assert it is unused after finalize.
    sha256_free(hasher);
    let arr: [u8; 32] = result.into();
    Box::into_raw(Box::new(arr.into()))
}

/// Free allocations from [sha256_state].
///
/// # Safety
/// This assumes the state has not already been freed or manually modified.
#[no_mangle]
pub unsafe extern "C" fn sha256_free(hasher: *mut sha256_state) {
    if !hasher.is_null() {
        let mut boxed_hasher = Box::from_raw(hasher);

        let inner = Box::from_raw(boxed_hasher.inner);
        // Set pointer to null to avoid double free. `black_box` to avoid compiler optimizing away.
        boxed_hasher.inner = ptr::null_mut();
        drop(inner);

        drop(boxed_hasher);
    }
}

/// Exit the zkvm, using the [sha256_state].
///
/// # Safety
/// Assumes hasher has not been freed.
#[no_mangle]
pub unsafe extern "C" fn env_exit(hasher: *mut sha256_state, exit_code: u8) -> ! {
    let journal_digest = sha256_finalize(hasher);
    let output_words: [u32; 8] =
        tagged_struct::<Impl>("risc0.Output", &[&*journal_digest, &Digest::ZERO], &[]).into();
    sys_halt(exit_code, &output_words)
}

/// Write data to the journal, updating the sha256 state accumulation with that data.
///
/// # Safety
/// This is safe assuming that pointers have not been manually modified, and len does not go past
/// the buffer of the data in memory.
#[no_mangle]
pub unsafe extern "C" fn env_commit(hasher: *mut sha256_state, bytes_ptr: *const u8, len: u32) {
    sha256_update(hasher, bytes_ptr, len);
    sys_write(fileno::JOURNAL, bytes_ptr, len as usize);
}
