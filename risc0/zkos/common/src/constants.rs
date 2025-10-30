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

pub const MEPC_PTR: *mut usize = 0xffff_0200 as *mut usize;

// Shadow register storage area for supervisor CSRs (starting at 0xffff_5000)
pub const SHADOW_REGS_PTR: *mut u32 = 0xffff_5000 as *mut u32;
pub const ILRSC_OFFSET: usize = 11; // Instruction LR/SC register
pub const ILRSC_SET_OFFSET: usize = 12; // Instruction LR/SC set register
pub const USER_REGS_PTR: *mut u32 = 0xffff_0080 as *mut u32;

pub const KERNEL_START_ADDR: usize = 0xc000_0000;
