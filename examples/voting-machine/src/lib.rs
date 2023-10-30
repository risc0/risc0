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

use risc0_zkvm::{default_prover, serde::from_slice, ExecutorEnv, Receipt, Result};
use voting_machine_core::{
    Ballot, FreezeVotingMachineCommit, FreezeVotingMachineParams, FreezeVotingMachineResult,
    InitializeVotingMachineCommit, SubmitBallotCommit, SubmitBallotParams, VotingMachineState,
};
use voting_machine_methods::{FREEZE_ELF, FREEZE_ID, INIT_ELF, INIT_ID, SUBMIT_ELF, SUBMIT_ID};

pub struct InitMessage {
    receipt: Receipt,
}

impl InitMessage {
    pub fn get_state(&self) -> Result<InitializeVotingMachineCommit> {
        Ok(self.receipt.journal.decode()?)
    }

    pub fn verify_and_get_commit(&self) -> Result<InitializeVotingMachineCommit> {
        self.receipt.verify(INIT_ID)?;
        self.get_state()
    }
}

pub struct SubmitBallotMessage {
    receipt: Receipt,
}

impl SubmitBallotMessage {
    pub fn get_commit(&self) -> Result<SubmitBallotCommit> {
        Ok(self.receipt.journal.decode()?)
    }

    pub fn verify_and_get_commit(&self) -> Result<SubmitBallotCommit> {
        self.receipt.verify(SUBMIT_ID)?;
        self.get_commit()
    }
}

pub struct FreezeStationMessage {
    receipt: Receipt,
}

impl FreezeStationMessage {
    pub fn get_commit(&self) -> Result<FreezeVotingMachineCommit> {
        Ok(self.receipt.journal.decode()?)
    }

    pub fn verify_and_get_commit(&self) -> Result<FreezeVotingMachineCommit> {
        self.receipt.verify(FREEZE_ID)?;
        self.get_commit()
    }
}

#[derive(Debug)]
pub struct PollingStation {
    state: VotingMachineState,
}

impl PollingStation {
    pub fn new(state: VotingMachineState) -> Self {
        PollingStation { state }
    }

    pub fn init(&self) -> Result<InitMessage> {
        log::info!("init");
        let env = ExecutorEnv::builder().write(&self.state)?.build()?;
        let prover = default_prover();
        let receipt = prover.prove_elf(env, INIT_ELF)?;
        Ok(InitMessage { receipt })
    }

    pub fn submit(&mut self, ballot: &Ballot) -> Result<SubmitBallotMessage> {
        log::info!("submit: {:?}", ballot);
        let params = SubmitBallotParams::new(self.state.clone(), ballot.clone());
        let mut output = Vec::new();
        let env = ExecutorEnv::builder()
            .write(&params)?
            .stdout(&mut output)
            .build()?;
        let prover = default_prover();
        let receipt = prover.prove_elf(env, SUBMIT_ELF)?;
        self.state = from_slice(&output)?;
        Ok(SubmitBallotMessage { receipt })
    }

    pub fn freeze(&mut self) -> Result<FreezeStationMessage> {
        log::info!("freeze");
        let params = FreezeVotingMachineParams::new(self.state.clone());
        let mut output = Vec::new();
        let env = ExecutorEnv::builder()
            .write(&params)?
            .stdout(&mut output)
            .build()?;
        let prover = default_prover();
        let receipt = prover.prove_elf(env, FREEZE_ELF)?;
        let result: FreezeVotingMachineResult = from_slice(&output)?;
        self.state = result.state;
        Ok(FreezeStationMessage { receipt })
    }
}

#[cfg(test)]
mod tests {
    use test_log::test;

    use super::*;

    #[test]
    fn protocol() {
        let polling_station_state = VotingMachineState {
            polls_open: true,
            voter_bitfield: 0,
            count: 0,
        };

        let mut polling_station = PollingStation::new(polling_station_state);

        let ballot1 = Ballot {
            voter: 0,
            vote_yes: false,
        };
        let ballot2 = Ballot {
            voter: 1,
            vote_yes: true,
        };
        let ballot3 = Ballot {
            voter: 2,
            vote_yes: true,
        };
        let ballot4 = Ballot {
            voter: 1,
            vote_yes: false,
        };
        let ballot5 = Ballot {
            voter: 3,
            vote_yes: false,
        };
        let ballot6 = Ballot {
            voter: 4,
            vote_yes: true,
        };

        let init_msg = polling_station.init().unwrap();
        let ballot_msg1 = polling_station.submit(&ballot1).unwrap();
        let ballot_msg2 = polling_station.submit(&ballot2).unwrap();
        let ballot_msg3 = polling_station.submit(&ballot3).unwrap();
        let ballot_msg4 = polling_station.submit(&ballot4).unwrap();
        let ballot_msg5 = polling_station.submit(&ballot5).unwrap();
        let close_msg = polling_station.freeze().unwrap();
        let ballot_msg6 = polling_station.submit(&ballot6).unwrap();

        assert_eq!(polling_station.state.count, 2);

        let init_state = init_msg.verify_and_get_commit();
        let ballot_commit1 = ballot_msg1.verify_and_get_commit();
        let ballot_commit2 = ballot_msg2.verify_and_get_commit();
        let ballot_commit3 = ballot_msg3.verify_and_get_commit();
        let ballot_commit4 = ballot_msg4.verify_and_get_commit();
        let ballot_commit5 = ballot_msg5.verify_and_get_commit();
        let close_state = close_msg.verify_and_get_commit();
        let ballot_commit6 = ballot_msg6.verify_and_get_commit();

        log::info!("initial commit: {:?}", init_state);
        log::info!("ballot 1: {:?}", ballot1);
        log::info!("ballot 1 commit: {:?}", ballot_commit1);
        log::info!("ballot 2: {:?}", ballot2);
        log::info!("ballot 2 commit: {:?}", ballot_commit2);
        log::info!("ballot 3: {:?}", ballot3);
        log::info!("ballot 3 commit: {:?}", ballot_commit3);
        log::info!("ballot 4: {:?}", ballot4);
        log::info!("ballot 4 commit: {:?}", ballot_commit4);
        log::info!("ballot 5: {:?}", ballot5);
        log::info!("ballot 5 commit: {:?}", ballot_commit5);
        log::info!("freeze commit: {:?}", close_state);
        log::info!("ballot 6: {:?}", ballot6);
        log::info!("ballot 6 commit: {:?}", ballot_commit6);
        log::info!("Final vote count: {:?}", polling_station.state.count);
    }
}
