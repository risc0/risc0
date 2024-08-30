// Copyright 2024 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Manages system calls for accelerators and other proof composition

use crate::{
    host::client::env::AssumptionReceipts,
    receipt::merkle::MerkleGroup,
    receipt_claim::Unknown,
    sha::Digestible,
    sha::{Digest, DIGEST_BYTES},
    Assumption, AssumptionReceipt, MaybePruned, SuccinctReceipt, SuccinctReceiptVerifierParameters,
};
use anyhow::{anyhow, bail, Context, Result};
use risc0_zkp::{core::hash::poseidon2::Poseidon2HashSuite, field::baby_bear::BabyBearElem};
use std::{cell::RefCell, collections::VecDeque, rc::Rc};

#[derive(Clone)]
pub(crate) struct SysCompose {
    pub(crate) assumptions: Rc<RefCell<AssumptionReceipts>>,
}

impl SysCompose {
    pub(crate) fn new(assumptions: Rc<RefCell<AssumptionReceipts>>) -> Self {
        Self { assumptions }
    }

    fn add_assumption(&mut self, claim_digest: &Digest, control_root: &Digest) -> Result<()> {
        // Iterate over the list looking for a matching assumption.
        let mut assumption: Option<(Assumption, AssumptionReceipt)> = None;
        for cached_assumption in self.assumptions.borrow().cached.iter() {
            let cached_claim_digest = cached_assumption
                .claim_digest()
                .context("failed to access claim digest on cached assumption")?;
            if cached_claim_digest != *claim_digest {
                tracing::debug!(
                    "SYS_VERIFY_INTEGRITY: receipt with claim {cached_claim_digest} does not match"
                );
                continue;
            }
            // If the control root supplied by the guest is not zero, then they are requesting a
            // specific set of recursion programs be used to resolve the assumption. Check that the
            // given receipt can indeed resolve the assumption.
            // NOTE: We currently only support using Succinct receipts here.
            if *control_root != Digest::ZERO {
                let Some(cached_control_root) = (match cached_assumption {
                    AssumptionReceipt::Proven(receipt) => receipt
                        .succinct()
                        .ok()
                        .map(|r| r.control_root())
                        .transpose()?,
                    AssumptionReceipt::Unresolved(unresolved) => Some(unresolved.control_root),
                }) else {
                    // Elevate to warning because this really is likely an error.
                    tracing::warn!(
                        "SYS_VERIFY_INTEGRITY: receipt with claim {cached_claim_digest} is not a succinct receipt"
                    );
                    continue;
                };
                if cached_control_root != *control_root {
                    // Elevate to warning because this really is likely an error.
                    tracing::warn!(
                        "SYS_VERIFY_INTEGRITY: receipt with claim {cached_claim_digest} has control root {cached_control_root}; guest requested {control_root}"
                    );
                    continue;
                }
            }
            assumption = Some((
                Assumption {
                    claim: *claim_digest,
                    control_root: *control_root,
                },
                cached_assumption.clone(),
            ));
            break;
        }

        let Some(assumption) = assumption else {
            return Err(anyhow!(
                "sys_verify_integrity: no receipt found to resolve assumption: claim digest {claim_digest}, control root {control_root}"
            ));
        };

        // Mark the assumption as accessed, pushing it to the head of the list, and return the success code.
        self.assumptions.borrow_mut().accessed.insert(0, assumption);
        Ok(())
    }

    pub(crate) fn sys_verify_integrity(&mut self, from_guest: Vec<u8>) -> Result<(u32, u32)> {
        let claim_digest: Digest = from_guest[..DIGEST_BYTES]
            .try_into()
            .map_err(|vec| anyhow!("failed to convert to [u8; DIGEST_BYTES]: {vec:?}"))?;
        let control_root: Digest = from_guest[DIGEST_BYTES..]
            .try_into()
            .map_err(|vec| anyhow!("failed to convert to [u8; DIGEST_BYTES]: {vec:?}"))?;

        tracing::debug!("SYS_VERIFY_INTEGRITY: ({}, {})", claim_digest, control_root);

        self.add_assumption(&claim_digest, &control_root)?;
        Ok((0, 0))
    }

    pub(crate) fn sys_execute_zkr(
        &mut self,
        control_id: &Digest,
        input: &[u32],
    ) -> Result<(u32, u32)> {
        let zkr = get_zkr(control_id)?;
        let hashfn = "poseidon2";
        let mut prover = risc0_circuit_recursion::prove::Prover::new(zkr, hashfn);
        prover.add_input(input);

        tracing::debug!("Running prover");
        let receipt = prover.run()?;

        tracing::debug!("zkr receipt: {receipt:?}");

        // Read the claim digest from the second of the global output slots.
        const DIGEST_SHORTS: usize = crate::sha::DIGEST_WORDS * 2;
        let claim_digest: Digest = risc0_binfmt::read_sha_halfs(&mut VecDeque::from_iter(
            bytemuck::checked::cast_slice::<_, BabyBearElem>(
                &receipt.seal[DIGEST_SHORTS..2 * DIGEST_SHORTS],
            )
            .iter()
            .copied()
            .map(u32::from),
        ))?;

        let suite = Poseidon2HashSuite::new_suite();
        let control_id_group = MerkleGroup::new([*control_id].into())?;
        let control_inclusion_proof = control_id_group.get_proof_by_index(0, &*suite.hashfn);
        let succinct_receipt = SuccinctReceipt {
            seal: receipt.seal,
            hashfn: "poseidon2".to_string(),
            control_id: *control_id,
            control_inclusion_proof,
            claim: MaybePruned::<Unknown>::Pruned(claim_digest),
            verifier_parameters: SuccinctReceiptVerifierParameters::default().digest(),
        };

        tracing::debug!("succinct receipt: {succinct_receipt:?}");
        self.assumptions
            .borrow_mut()
            .cached
            .push(succinct_receipt.into());
        Ok((0, 0))
    }
}

use risc0_circuit_recursion::prove::Program;
/// A registry to look up programs by control ID.
use std::{collections::BTreeMap, sync::Mutex};
pub(crate) type ZkrRegistry = BTreeMap<Digest, Box<dyn Fn() -> Result<Program> + Send + 'static>>;

pub(crate) static ZKR_REGISTRY: Mutex<ZkrRegistry> = Mutex::new(BTreeMap::new());

/// Registers a function to retrieve a recursion program (zkr) based on a control id.
pub fn register_zkr(
    control_id: &Digest,
    get_program_fn: impl Fn() -> Result<Program> + Send + 'static,
) {
    let mut registry = ZKR_REGISTRY.lock().unwrap();
    let old = registry.insert(*control_id, Box::new(get_program_fn));
    assert!(
        old.is_none(),
        "Duplicate programs registered for control id {control_id}"
    );
}

fn get_zkr(control_id: &Digest) -> Result<Program> {
    let registry = ZKR_REGISTRY.lock().unwrap();
    registry
        .get(control_id)
        .map(|f| f())
        .unwrap_or_else(|| bail!("Control id {control_id} unregistered"))
}
