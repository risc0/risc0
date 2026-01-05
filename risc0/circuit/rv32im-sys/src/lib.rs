// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{
    ffi::CStr,
    os::raw::{c_char, c_int},
    ptr::NonNull,
};

use anyhow::{Result, anyhow};

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

#[repr(C)]
pub struct SegmentContext {
    _private: (),
}

#[repr(C)]
pub struct PreflightContext {
    _private: (),
}

#[repr(C)]
pub struct ProverContext {
    _private: (),
}

#[repr(C)]
pub struct RawSlice<T> {
    pub ptr: *const T,
    pub len: usize,
}

#[repr(C)]
pub struct RawPage {
    pub addr: u32,
    pub data: *const u32,
}

#[repr(C)]
pub struct RawDigestEntry {
    pub idx: u32,
    pub digest: [u32; 8],
}

#[repr(C)]
pub struct RawMemoryImage {
    pub pages: RawSlice<RawPage>,
    pub digests: RawSlice<RawDigestEntry>,
}

#[repr(C)]
pub struct RawSegment {
    pub image: RawMemoryImage,
    pub reads: RawSlice<RawSlice<u8>>,
    pub writes: RawSlice<u32>,
    pub insn_counter: u32,
}

#[repr(C)]
pub struct RowInfo {
    pub row_type: u8,
    pub block_count: u8,
    pub padding: u16,
    pub aux_offset: u32,
}

type RawError = *const std::os::raw::c_char;

unsafe extern "C" {
    pub fn risc0_circuit_rv32im_m3_last_error() -> RawError;
    pub fn risc0_circuit_rv32im_m3_clear_last_error();

    pub fn risc0_circuit_rv32im_m3_segment_free(ctx: *const SegmentContext);
    pub fn risc0_circuit_rv32im_m3_preflight_free(ctx: *const PreflightContext);
    pub fn risc0_circuit_rv32im_m3_prover_free(ctx: *const ProverContext);

    pub fn risc0_circuit_rv32im_m3_segment_new(segment: *const RawSegment) -> *mut SegmentContext;

    pub fn risc0_circuit_rv32im_m3_segment_preflight(
        sctx: *mut SegmentContext,
        po2: usize,
    ) -> *mut PreflightContext;

    pub fn risc0_circuit_rv32im_m3_preflight_is_final(ctx: *const PreflightContext) -> usize;

    pub fn risc0_circuit_rv32im_m3_preflight_row_info(
        ctx: *const PreflightContext,
    ) -> *const RowInfo;

    pub fn risc0_circuit_rv32im_m3_preflight_row_info_size(ctx: *const PreflightContext) -> usize;

    pub fn risc0_circuit_rv32im_m3_preflight_aux(ctx: *const PreflightContext) -> *const u32;

    pub fn risc0_circuit_rv32im_m3_preflight_aux_size(ctx: *const PreflightContext) -> usize;

    pub fn risc0_circuit_rv32im_m3_prover_new_cpu(po2: usize) -> *mut ProverContext;

    #[cfg(feature = "cuda")]
    pub fn risc0_circuit_rv32im_m3_prover_new_cuda(po2: usize) -> *mut ProverContext;

    pub fn risc0_circuit_rv32im_m3_prove(
        ctx: *const ProverContext,
        rowInfo: *const RowInfo,
        rowInfoSize: usize,
        aux: *const u32,
        auxSize: usize,
    );

    pub fn risc0_circuit_rv32im_m3_prover_transcript(ctx: *const ProverContext) -> RawSlice<u32>;
}

#[repr(C)]
pub enum LogLevel {
    Error = 0,
    Info = 1,
    Debug = 2,
    Trace = 3,
}

/// Callback into the Rust logging system from C/C++ code.
///
/// # Safety
///
/// - `msg` must be a valid, non-null pointer to a NUL-terminated C string.
/// - The string pointed to by `msg` must remain valid for the duration of this call.
/// - `level` should be an integer corresponding to a known log level (0 = error, 1 = info, etc).
#[unsafe(no_mangle)]
pub unsafe extern "C" fn risc0_log_callback(level: c_int, msg: *const c_char) {
    let str = unsafe { CStr::from_ptr(msg) }.to_string_lossy();
    match level {
        0 => tracing::error!("{str}"),
        1 => tracing::info!("{str}"),
        2 => tracing::debug!("{str}"),
        3 => tracing::trace!("{str}"),
        _ => (),
    }
}

/// Wrap a pointer-returning FFI call:
///   - Success: returns NonNull<T>
///   - Error:   returns Err(anyhow!("...")) from TLS last error
pub fn ffi_wrap_ptr<T, F>(mut inner: F) -> Result<*const T>
where
    F: FnMut() -> *const T,
{
    unsafe {
        risc0_circuit_rv32im_m3_clear_last_error();
        let ptr = inner();
        if ptr.is_null() {
            Err(take_last_error())
        } else {
            Ok(ptr)
        }
    }
}

/// Wrap a pointer-returning FFI call:
///   - Success: returns NonNull<T>
///   - Error:   returns Err(anyhow!("...")) from TLS last error
pub fn ffi_wrap_ptr_mut<T, F>(mut inner: F) -> Result<NonNull<T>>
where
    F: FnMut() -> *mut T,
{
    unsafe {
        risc0_circuit_rv32im_m3_clear_last_error();
        match NonNull::new(inner()) {
            Some(x) => Ok(x),
            None => Err(take_last_error()),
        }
    }
}

/// Wrap a void-returning FFI call that signals failure only by setting the TLS error.
///
/// Convention: on success, the C++ function simply returns (no set_last_error call);
/// on failure, it catches exceptions and sets the thread-local last error.
pub fn ffi_wrap_void<F>(mut inner: F) -> Result<()>
where
    F: FnMut(),
{
    unsafe {
        // Clear stale error before the call
        risc0_circuit_rv32im_m3_clear_last_error();
        inner();

        // After the call, see if an error message was set
        let ptr = risc0_circuit_rv32im_m3_last_error();
        if ptr.is_null() {
            Ok(())
        } else {
            let msg = CStr::from_ptr(ptr).to_string_lossy().into_owned();
            Err(anyhow!(msg))
        }
    }
}

/// Read the TLS error string from the C++ side and convert to anyhow::Error.
/// If there's nothing set, synthesize a generic message (optionally include an error code).
fn take_last_error() -> anyhow::Error {
    unsafe {
        let ptr = risc0_circuit_rv32im_m3_last_error();
        let msg = if ptr.is_null() {
            "FFI call failed with no message".to_string()
        } else {
            CStr::from_ptr(ptr).to_string_lossy().into_owned()
        };
        anyhow!(msg)
    }
}
