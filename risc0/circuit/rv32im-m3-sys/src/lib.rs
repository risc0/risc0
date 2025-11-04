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

use std::ffi::CStr;
use std::os::raw::{c_char, c_int};

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
    pub suspend_cycle: u32,
}

type RawError = *const std::os::raw::c_char;

unsafe extern "C" {
    pub fn risc0_circuit_rv32im_m3_prover_new_cpu(po2: usize) -> *const ProverContext;

    #[cfg(feature = "cuda")]
    pub fn risc0_circuit_rv32im_m3_prover_new_cuda(po2: usize) -> *const ProverContext;

    pub fn risc0_circuit_rv32im_m3_prover_free(ctx: *const ProverContext);

    pub fn risc0_circuit_rv32im_m3_prover_transcript(ctx: *const ProverContext) -> RawSlice<u32>;

    pub fn risc0_circuit_rv32im_m3_load_segment(
        ctx: *const ProverContext,
        segment: *const RawSegment,
    ) -> RawError;

    pub fn risc0_circuit_rv32im_m3_preflight(
        ctx: *const ProverContext,
        is_done: *mut u32,
    ) -> RawError;

    pub fn risc0_circuit_rv32im_m3_prove(ctx: *const ProverContext) -> RawError;
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
