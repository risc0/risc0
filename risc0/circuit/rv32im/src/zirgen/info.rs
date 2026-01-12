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

// This code is automatically generated

use risc0_zkp::{
    adapter::{CircuitInfo, ProtocolInfo, TapsProvider},
    taps::TapSet,
};

use super::CircuitImpl;

impl CircuitInfo for CircuitImpl {
    const CIRCUIT_INFO: ProtocolInfo = ProtocolInfo(*b"RV32IM:v2rev2___");
    const OUTPUT_SIZE: usize = 90;
    const MIX_SIZE: usize = 36;
}

impl TapsProvider for CircuitImpl {
    fn get_taps(&self) -> &'static TapSet<'static> {
        super::taps::TAPSET
    }
}
