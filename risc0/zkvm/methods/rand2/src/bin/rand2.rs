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

#![no_std]
#![no_main]

extern crate alloc;

use alloc::vec;
use getrandom::getrandom;

risc0_zkvm::entry!(main);

fn main() {
    let rand_buf = &mut vec![0u8; 8];
    let _res = getrandom(rand_buf);
    assert_ne!(&rand_buf, &vec![0u8; 8].as_slice());
}
