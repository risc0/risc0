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

use anyhow::{Result, ensure};
use risc0_circuit_keccak::{
    KECCAK_CONTROL_IDS, get_control_id,
    prove::{keccak_prover, zkr::get_keccak_zkr},
};
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::core::digest::{DIGEST_WORDS, Digest};

use crate::{
    Unknown,
    host::{client::env::ProveKeccakRequest, recursion::prove::prove_zkr},
    receipt::SuccinctReceipt,
};

/// Generate a keccak proof that has been lifted.
pub(crate) fn prove_keccak(request: &ProveKeccakRequest) -> Result<SuccinctReceipt<Unknown>> {
    let zkr_input = {
        let prover = keccak_prover()?;
        let seal = prover.prove(&request.input, request.po2)?;

        let claim_digest = read_digest_from_words(&seal[..DIGEST_WORDS])?;
        ensure!(
            request.claim_digest == claim_digest,
            "keccak claim digest mismatch, expected: {:?}, actual: {claim_digest:?}",
            request.claim_digest
        );

        // Make sure we have a valid seal so we can fail early if anything went wrong
        prover.verify(&seal)?;

        let claim_sha_input = claim_digest
            .as_words()
            .iter()
            .copied()
            .flat_map(|x| [x & 0xffff, x >> 16])
            .map(BabyBearElem::new)
            .collect::<Vec<_>>();

        let mut zkr_input: Vec<u32> = Vec::new();
        zkr_input.extend(request.control_root.as_words());
        zkr_input.extend(seal);
        zkr_input.extend(bytemuck::cast_slice(claim_sha_input.as_slice()));
        zkr_input.push(1 << request.po2);

        zkr_input
    };

    prove_zkr(
        get_keccak_zkr(request.po2)?,
        get_control_id(request.po2),
        KECCAK_CONTROL_IDS.to_vec(),
        bytemuck::cast_slice(zkr_input.as_slice()),
    )
}

fn read_digest_from_words(slice: &[u32]) -> Result<Digest> {
    let mut buf = slice.to_vec();
    for word in buf.iter_mut() {
        *word = BabyBearElem::new_raw(*word).as_u32();
    }
    Ok(Digest::try_from(buf.as_slice())?)
}
