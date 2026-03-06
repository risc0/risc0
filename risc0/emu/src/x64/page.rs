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

use std::sync::{Arc, OnceLock};

use risc0_zkp::core::digest::Digest;

pub const PAGE_SHIFT: usize = 10; // 1 KiB pages
pub const PAGE_SIZE: usize = 1 << PAGE_SHIFT;
pub const PAGE_OFFSET_MASK: u32 = (1 << PAGE_SHIFT) - 1;
pub const PAGE_WRITABLE_FLAG: u16 = 0x8000u16;
pub const PAGE_WRITABLE_MASK: u16 = !PAGE_WRITABLE_FLAG;
pub const PAGE_WRITABLE_BIT: u8 = 15;
