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

use risc0_zkp::{
    MAX_CYCLES_PO2,
    adapter::{CircuitCoreDefV3, CircuitInfoV3, GroupInfo, MixState, PolyExt},
    core::hash::poseidon2::Poseidon2HashSuite,
    field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    verify::VerificationError,
};

use crate::{RV32IM_SEAL_VERSION, zirgen::poly_ext::POLY_EXT_DEF};

pub struct CircuitInfo;

impl CircuitInfoV3 for CircuitInfo {
    fn get_groups(&self) -> &'static [GroupInfo] {
        &[
            GroupInfo {
                global_count: 54,
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

pub fn verify(mut seal: &[u32]) -> Result<(), VerificationError> {
    let circuit = CircuitInfo;
    let suite = Poseidon2HashSuite::new_suite();

    let version = *seal
        .split_off_first()
        .ok_or(VerificationError::ReceiptFormatError)?;
    if version != RV32IM_SEAL_VERSION {
        tracing::debug!(
            "version decoded from seal does not match the expected version: {version} != {RV32IM_SEAL_VERSION}",
        );
        return Err(VerificationError::ReceiptFormatError);
    }

    let po2 = *seal
        .split_off_first()
        .ok_or(VerificationError::ReceiptFormatError)? as usize;
    if po2 > MAX_CYCLES_PO2 {
        tracing::debug!("po2 in seal is larger than the max po2: {po2} > {MAX_CYCLES_PO2}");
        return Err(VerificationError::ReceiptFormatError);
    }

    risc0_zkp::verify::verify_v3(&circuit, &suite, seal, po2)
}
