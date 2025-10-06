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

use super::zirgen::poly_ext::POLY_EXT_DEF;
use risc0_zkp::{
    adapter::{CircuitCoreDefV3, CircuitInfoV3, GroupInfo, MixState, PolyExt},
    core::hash::poseidon2::Poseidon2HashSuite,
    field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    verify::{VerificationError, verify_v3},
};
pub struct CircuitInfo {}

impl CircuitInfoV3 for CircuitInfo {
    fn get_groups(&self) -> &'static [GroupInfo] {
        &[
            GroupInfo {
                global_count: 16,
                mix_count: 0,
            },
            GroupInfo {
                global_count: 0,
                mix_count: 200,
            },
        ]
    }
}

impl PolyExt<BabyBear> for CircuitInfo {
    fn poly_ext(
        &self,
        mix: &BabyBearExtElem,
        u: &[BabyBearExtElem],
        args: &[&[BabyBearElem]],
    ) -> MixState<BabyBearExtElem> {
        POLY_EXT_DEF.step::<BabyBear>(mix, u, args)
    }
}

impl CircuitCoreDefV3<BabyBear> for CircuitInfo {}

pub fn verify_m3(transcript: &[u32], po2: usize) -> Result<(), VerificationError> {
    let circuit = CircuitInfo {};
    let suite = Poseidon2HashSuite::new_suite();
    verify_v3(&circuit, &suite, transcript, po2)
}
