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

#[cfg(feature = "prove")]
pub mod fp;

#[cfg(feature = "prove")]
mod prove;

#[cfg(feature = "prove")]
pub use prove::*;

#[cfg_attr(
    any(all(target_os = "macos", target_arch = "aarch64"), target_os = "ios"),
    link(name = "Foundation", kind = "framework")
)]
unsafe extern "C" {}

#[cfg_attr(
    any(all(target_os = "macos", target_arch = "aarch64"), target_os = "ios"),
    link(name = "Metal", kind = "framework")
)]
unsafe extern "C" {}

#[derive(Debug)]
pub struct Rv32imInstrInfo {
    pub name: &'static str,
    pub idx: u8,
    pub opcode: u8,
    pub imm_type: &'static str,
    pub func3: &'static str,
    pub func7: &'static str,
    pub itype: &'static str,
    pub params: &'static [&'static str],
}

include!(concat!(env!("OUT_DIR"), "/rv32im_table.rs"));

include!(concat!(env!("OUT_DIR"), "/block_types.rs"));

pub trait HasBlockType {
    const BLOCK_TYPE: BlockType;
}
