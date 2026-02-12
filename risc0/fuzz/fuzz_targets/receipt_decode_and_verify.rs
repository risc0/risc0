// Copyright 2026 RISC Zero, Inc.
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

#![no_main]

use libfuzzer_sys::{fuzz_target, Corpus};
use risc0_zkvm::Receipt;

fuzz_target!(|data: &[u8]| -> Corpus {
    // Deserialize the receipt. Do not add items to the corpus that fail to deserialize.
    // We are not trying to fuzz bincode. We use it to make specifying the input more convenient
    // and avoid implementing a method for generating Receipts directly as structs.
    let Ok(receipt) = bincode::deserialize::<Receipt>(data) else {
        return Corpus::Reject;
    };

    // Call the verify function. If it panics, then the fuzzer has found an example.
    let _ = receipt.verify_integrity_with_context(&Default::default());
    Corpus::Keep
});
