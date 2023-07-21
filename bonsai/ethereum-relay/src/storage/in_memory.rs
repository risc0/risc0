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
    collections::HashMap,
    sync::{Arc, RwLock},
};

use crate::storage::{Error, ProofID, ProofRequestInformation, ProofRequestState, Storage};

#[derive(Debug, Clone)]
pub(crate) struct InMemoryStorage {
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
            ProofRequestState::Failed => Arc::new(RwLock::new(HashMap::new())),
            ProofRequestState::Completed => self.completed_proofs.clone(),
            ProofRequestState::PreparingOnchain => self.preparing_onchain_proofs.clone(),
            ProofRequestState::CompletedOnchain(_) => Arc::new(RwLock::new(HashMap::new())),
        }
    }
}

#[async_trait::async_trait]
impl Storage for InMemoryStorage {
    async fn add_new_bonsai_proof_request(
        &self,
        proof: ProofRequestInformation,
    ) -> Result<(), Error> {
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
        let mut proof_states_locked = self.proof_states.write()?;

        let current_state = match proof_states_locked.get(&proof_id.uuid) {
            Some(proof_state) => *proof_state,
            None => return Err(Error::ProofNotFound { id: proof_id }),
        };

        if !current_state.is_valid_state_transition(new_state) {
            return Err(InMemoryStorageError::InvalidProofStateTransition {
                proof_id,
                from_state: current_state,
                new_state,
            })?;
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
