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

#[repr(C)]
pub struct RawProver {
    _private: (),
}

#[repr(C)]
pub struct RawSlice {
    pub ptr: *const u32,
    pub len: usize,
}

unsafe extern "C" {
    pub fn risc0_circuit_rv32im_m3_prover_new_cpu(po2: usize) -> *const RawProver;

    #[cfg(feature = "cuda")]
    pub fn risc0_circuit_rv32im_m3_prover_new_cuda(po2: usize) -> *const RawProver;

    pub fn risc0_circuit_rv32im_m3_prover_free(prover: *const RawProver);

    pub fn risc0_circuit_rv32im_m3_prover_transcript(prover: *const RawProver) -> RawSlice;

    pub fn risc0_circuit_rv32im_m3_preflight(
        prover: *const RawProver,
        elf_ptr: *const u8,
        elf_len: usize,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_rv32im_m3_prove(prover: *const RawProver) -> *const std::os::raw::c_char;
}
