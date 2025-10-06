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
pub struct ProofResult {
    is_error: bool,   // Is this an error
    data: *const u32, // Transcript or null
    error: *const u8, // Error string or null
    len: usize,       // Size of transcript or string
}

unsafe extern "C" {
    pub fn risc0_circuit_rv32im_m3_prove(elf_ptr: *const u8, elf_len: usize) -> *const ProofResult;
    pub fn proof_dealloc(res: *const ProofResult) -> ();
}

pub fn prove(elf: &[u8]) -> Result<Vec<u32>, String> {
    unsafe {
        let result = risc0_circuit_rv32im_m3_prove(elf.as_ptr(), elf.len());
        if (*result).is_error {
            let slice = std::slice::from_raw_parts((*result).error, (*result).len);
            let s = std::str::from_utf8(slice).unwrap();
            let string = s.to_owned();
            proof_dealloc(result);
            Err(string)
        } else {
            let vec = std::slice::from_raw_parts((*result).data, (*result).len).to_vec();
            proof_dealloc(result);
            Ok(vec)
        }
    }
}

// Convert the &str to an owned
//                                             String
//                                                     s.to_owned()
//
