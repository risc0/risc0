// Copyright 2022 Risc0, Inc.
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

use r0vm_host::{Proof, Prover, Result};
use r0vm_serde::{from_slice, to_vec};
use votingmachine_proof::{Ballot, SubmitBallotCommit, SubmitBallotParams, SubmitBallotResult};
use votingmachine_proof::{
    FreezeVotingMachineCommit, FreezeVotingMachineParams, FreezeVotingMachineResult,
};
use votingmachine_proof::{InitializeVotingMachineCommit, VotingMachineState};

pub struct InitMessage {
    proof: Proof,
}

impl InitMessage {
    pub fn get_state(&self) -> Result<InitializeVotingMachineCommit> {
        let msg = self.proof.get_message_vec()?;
        Ok(from_slice(msg.as_slice()).unwrap())
    }

    pub fn verify_and_get_commit(&self) -> Result<InitializeVotingMachineCommit> {
        self.proof
            .verify("examples/rust/votingmachine/proof/init")?;
        self.get_state()
    }
}

pub struct SubmitBallotMessage {
    proof: Proof,
}

impl SubmitBallotMessage {
    pub fn get_commit(&self) -> Result<SubmitBallotCommit> {
        let msg = self.proof.get_message_vec()?;
        Ok(from_slice(msg.as_slice()).unwrap())
    }

    pub fn verify_and_get_commit(&self) -> Result<SubmitBallotCommit> {
        self.proof
            .verify("examples/rust/votingmachine/proof/submit")?;
        self.get_commit()
    }
}

pub struct FreezeStationMessage {
    proof: Proof,
}

impl FreezeStationMessage {
    pub fn get_commit(&self) -> Result<FreezeVotingMachineCommit> {
        let msg = self.proof.get_message_vec()?;
        Ok(from_slice(msg.as_slice()).unwrap())
    }

    pub fn verify_and_get_commit(&self) -> Result<FreezeVotingMachineCommit> {
        self.proof
            .verify("examples/rust/votingmachine/proof/freeze")?;
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
        let mut prover = Prover::new("examples/rust/votingmachine/proof/init")?;
        let vec = to_vec(&self.state).unwrap();
        prover.add_input(vec.as_slice())?;
        let proof = prover.run()?;
        Ok(InitMessage { proof })
    }

    pub fn submit(&mut self, ballot: &Ballot) -> Result<SubmitBallotMessage> {
        log::info!("submit: {:?}", ballot);
        let params = SubmitBallotParams::new(self.state.clone(), ballot.clone());
        let mut prover = Prover::new("examples/rust/votingmachine/proof/submit")?;
        let vec = to_vec(&params).unwrap();
        prover.add_input(vec.as_slice())?;
        let proof = prover.run()?;
        let vec = prover.get_output_vec()?;
        let result = from_slice::<SubmitBallotResult>(vec.as_slice()).unwrap();
        self.state = result.state.clone();
        Ok(SubmitBallotMessage { proof })
    }

    pub fn freeze(&mut self) -> Result<FreezeStationMessage> {
        log::info!("freeze");
        let params = FreezeVotingMachineParams::new(self.state.clone());
        let mut prover = Prover::new("examples/rust/votingmachine/proof/freeze")?;
        let vec = to_vec(&params).unwrap();
        prover.add_input(vec.as_slice())?;
        let proof = prover.run()?;
        let vec = prover.get_output_vec()?;
        let result = from_slice::<FreezeVotingMachineResult>(vec.as_slice()).unwrap();
        self.state = result.state.clone();
        Ok(FreezeStationMessage { proof })
    }
}

#[cfg(test)]
mod tests {
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
