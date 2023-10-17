// Copyright 2023 RISC Zero, Inc.
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

use std::{
    cmp::Ordering,
    collections::HashMap,
    sync::{Arc, RwLock},
};

use crate::storage::{
    Error, ProofID, ProofRequestInformation, ProofRequestState, Storage, MAX_PROOF_RETRIES,
};

#[derive(Debug, Clone)]
pub(crate) struct InMemoryStorage {
    proof_retries: Arc<RwLock<HashMap<String, u64>>>,
    proof_states: Arc<RwLock<HashMap<String, ProofRequestState>>>,
    new_proofs: Arc<RwLock<HashMap<String, ProofRequestInformation>>>,
    pending_proofs: Arc<RwLock<HashMap<String, ProofRequestInformation>>>,
    completed_proofs: Arc<RwLock<HashMap<String, ProofRequestInformation>>>,
    preparing_onchain_proofs: Arc<RwLock<HashMap<String, ProofRequestInformation>>>,
}

#[derive(Debug, thiserror::Error)]
pub(crate) enum InMemoryStorageError {
    #[error("Invalid proof state transition_proof_request")]
    InvalidProofStateTransition {
        proof_id: ProofID,
        from_state: ProofRequestState,
        new_state: ProofRequestState,
    },
}

impl Default for InMemoryStorage {
    fn default() -> Self {
        Self::new()
    }
}

impl InMemoryStorage {
    pub(crate) fn new() -> Self {
        Self {
            // TODO: Shouldn't we derive `Default` instead, and delete this call to `new`?
            proof_retries: Arc::new(RwLock::new(HashMap::new())),
            proof_states: Arc::new(RwLock::new(HashMap::new())),
            new_proofs: Arc::new(RwLock::new(HashMap::new())),
            pending_proofs: Arc::new(RwLock::new(HashMap::new())),
            completed_proofs: Arc::new(RwLock::new(HashMap::new())),
            preparing_onchain_proofs: Arc::new(RwLock::new(HashMap::new())),
        }
    }

    fn get_proof_request_set_for_state(
        &self,
        state: ProofRequestState,
    ) -> Arc<RwLock<HashMap<String, ProofRequestInformation>>> {
        match state {
            ProofRequestState::New => self.new_proofs.clone(),
            ProofRequestState::Pending => self.pending_proofs.clone(),
            // TODO: What do we exactly do with failed proofs?
            // I can't find any code that uses this state. Am I correct in
            // assuming this data structure will always increase given a
            // long-running process?
            ProofRequestState::Failed => Arc::new(RwLock::new(HashMap::new())),
            ProofRequestState::Completed => self.completed_proofs.clone(),
            ProofRequestState::PreparingOnchain => self.preparing_onchain_proofs.clone(),
            ProofRequestState::CompletedOnchain(_) => Arc::new(RwLock::new(HashMap::new())),
        }
    }

    async fn get_proof_retries(&self, proof_id: &ProofID) -> Result<u64, Error> {
        let id = proof_id.clone();
        self.proof_retries
            .read()?
            .get(&id.uuid)
            .cloned()
            .ok_or(Error::ProofNotFound { id })
    }

    async fn increment_proof_retries(&self, proof_id: ProofID) -> Result<(), Error> {
        let current_retries = self.get_proof_retries(&proof_id).await?;
        match current_retries.cmp(&MAX_PROOF_RETRIES) {
            Ordering::Less => {
                self.proof_retries
                    .write()?
                    .insert(proof_id.uuid, current_retries + 1);
                Ok(())
            }
            _ => Err(Error::MaxRetriesExceeded { id: proof_id }),
        }
    }

    async fn get_current_proof_state(
        &self,
        proof_id: &ProofID,
    ) -> Result<ProofRequestState, Error> {
        self.proof_states
            .read()?
            .get(&proof_id.uuid)
            .cloned()
            .ok_or(Error::ProofNotFound {
                id: proof_id.clone(),
            })
    }
}

#[async_trait::async_trait]
impl Storage for InMemoryStorage {
    async fn add_new_bonsai_proof_request(
        &self,
        proof: ProofRequestInformation,
    ) -> Result<(), Error> {
        if self
            .new_proofs
            .read()?
            .contains_key(&proof.proof_request_id.uuid)
        {
            return Err(Error::ProofAlreadyExists {
                id: proof.proof_request_id,
            });
        }

        self.proof_retries
            .write()?
            .insert(proof.proof_request_id.uuid.clone(), 0);
        self.proof_states
            .write()?
            .insert(proof.proof_request_id.uuid.clone(), ProofRequestState::New);
        self.new_proofs
            .write()?
            .insert(proof.proof_request_id.uuid.clone(), proof);

        Ok(())
    }

    async fn fetch_new_bonsai_requests(
        &self,
        _limit: Option<u64>,
    ) -> Result<Vec<ProofRequestInformation>, Error> {
        let hashmap = self.new_proofs.read()?;

        Ok(hashmap.values().cloned().collect())
    }

    async fn fetch_completed_bonsai_requests(
        &self,
        _limit: Option<u64>,
    ) -> Result<Vec<ProofRequestInformation>, Error> {
        let hashmap = self.completed_proofs.read()?;

        Ok(hashmap.values().cloned().collect())
    }

    async fn fetch_preparing_onchain_proof_requests(
        &self,
        _limit: Option<u64>,
    ) -> Result<Vec<ProofRequestInformation>, Error> {
        let hashmap = self.preparing_onchain_proofs.read()?;

        Ok(hashmap.values().cloned().collect())
    }

    async fn get_proof_request_state(&self, proof_id: ProofID) -> Result<ProofRequestState, Error> {
        match self.proof_states.read()?.get(&proof_id.uuid) {
            Some(state) => Ok(*state),
            None => Err(Error::ProofNotFound { id: proof_id })?,
        }
    }

    async fn transition_proof_request(
        &self,
        proof_id: ProofID,
        new_state: ProofRequestState,
    ) -> Result<(), Error> {
        let retries = self.get_proof_retries(&proof_id).await?;
        let current_state = self.get_current_proof_state(&proof_id).await?;

        if !current_state.is_valid_state_transition(new_state, retries) {
            return Err(InMemoryStorageError::InvalidProofStateTransition {
                proof_id,
                from_state: current_state,
                new_state,
            })?;
        }

        if current_state.should_increment_retries(&new_state) {
            self.increment_proof_retries(proof_id.clone()).await?;
        }

        let from_set = self.get_proof_request_set_for_state(current_state);
        let to_set = self.get_proof_request_set_for_state(new_state);

        // remove from the from_set and add to the to_set
        let mut from_set_locked = from_set.write()?;
        let mut to_set_locked = to_set.write()?;

        let proof = {
            let proof = match from_set_locked.get(&proof_id.uuid) {
                Some(proof) => proof.clone(),
                None => return Err(Error::ProofNotFound { id: proof_id }),
            };

            from_set_locked.remove(&proof_id.uuid);
            proof
        };

        let mut proof_states_locked = self.proof_states.write()?;
        if let ProofRequestState::CompletedOnchain(_) = new_state {
            // We don't need to store onchain transactions in memory
            proof_states_locked.remove(&proof_id.uuid);
            return Ok(());
        };

        to_set_locked.insert(proof.proof_request_id.uuid.clone(), proof);

        proof_states_locked.insert(proof_id.uuid, new_state);

        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use bonsai_ethereum_contracts::i_bonsai_relay::CallbackRequestFilter;
    use ethers::types::{Address, Bytes, H256};
    use rstest::*;

    use super::*;

    #[fixture]
    fn storage() -> InMemoryStorage {
        InMemoryStorage::new()
    }

    #[fixture]
    fn proof_id(#[default("test")] id: String) -> ProofID {
        ProofID::new(id.into())
    }

    #[fixture]
    fn proof_request_information(#[default("test")] id: String) -> ProofRequestInformation {
        ProofRequestInformation {
            proof_request_id: proof_id(id),
            callback_proof_request_event: CallbackRequestFilter {
                account: Address::default(),
                image_id: H256::default().into(),
                input: Bytes::default(),
                callback_contract: Address::default(),
                function_selector: [0xab, 0xcd, 0xef, 0xab],
                gas_limit: 3000000,
            },
        }
    }

    struct Transition<'a> {
        storage: &'a InMemoryStorage,
        proof_id: ProofID,
    }

    impl<'a> Transition<'_> {
        async fn to(&self, to_state: ProofRequestState) -> Result<(), Error> {
            self.storage
                .transition_proof_request(self.proof_id.clone(), to_state)
                .await
        }
    }

    #[rstest]
    #[tokio::test]
    async fn enforce_max_retries(
        storage: InMemoryStorage,
        proof_request_information: ProofRequestInformation,
    ) {
        let proof_id = proof_request_information.proof_request_id.clone();

        // Add a new proof request
        storage
            .add_new_bonsai_proof_request(proof_request_information)
            .await
            .unwrap();

        // Increment the proof retries MAX_PROOF_RETRIES times
        for _ in 0..MAX_PROOF_RETRIES {
            storage
                .increment_proof_retries(proof_id.clone())
                .await
                .unwrap()
        }

        // The next increment should fail
        let result = storage.increment_proof_retries(proof_id.clone()).await;
        assert!(result.is_err());

        // Ensure we incremented the proof retries the correct number of times
        assert_eq!(
            storage.get_proof_retries(&proof_id).await.unwrap(),
            MAX_PROOF_RETRIES
        );
    }

    #[rstest]
    #[tokio::test]
    async fn enforce_non_duplicated_proof_ids(
        storage: InMemoryStorage,
        proof_request_information: ProofRequestInformation,
    ) {
        // First proof request should succeed
        storage
            .add_new_bonsai_proof_request(proof_request_information.clone())
            .await
            .unwrap();

        // Second proof request should fail
        let result = storage
            .add_new_bonsai_proof_request(proof_request_information)
            .await;
        assert!(result.is_err());
    }

    #[rstest]
    #[tokio::test]
    async fn failed_proofs_retry_only_max_retries(
        storage: InMemoryStorage,
        proof_request_information: ProofRequestInformation,
    ) {
        let proof_id = proof_request_information.proof_request_id.clone();
        let transition = Transition {
            storage: &storage,
            proof_id: proof_id.clone(),
        };

        // Create a new proof request
        storage
            .add_new_bonsai_proof_request(proof_request_information)
            .await
            .unwrap();

        for _ in 0..MAX_PROOF_RETRIES {
            // Simulate progress on the proof request
            transition.to(ProofRequestState::Pending).await.unwrap();

            // Simulate a failure & retry
            transition.to(ProofRequestState::New).await.unwrap();
        }

        // The next transition should fail
        transition.to(ProofRequestState::Pending).await.unwrap();
        let result = transition.to(ProofRequestState::New).await;
        assert!(result.is_err());

        // Ensure we incremented the proof retries the correct number of times
        assert_eq!(
            storage.get_proof_retries(&proof_id).await.unwrap(),
            MAX_PROOF_RETRIES
        );
    }
}
