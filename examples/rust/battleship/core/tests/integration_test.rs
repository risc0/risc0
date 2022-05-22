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

use std::fs;

use battleship_core::{
    GameState, HitType, Position, RoundCommit, RoundParams, RoundResult, Ship, ShipDirection,
};
use battleship_methods::methods::{INIT_ID, INIT_PATH, TURN_ID, TURN_PATH};
use log::LevelFilter;
use risc0_zkvm_core::Digest;
use risc0_zkvm_host::{Exception, Prover, Receipt, Result};
use risc0_zkvm_serde::{from_slice, to_slice, to_vec};
use tempfile::tempdir;

pub struct InitMessage {
    receipt: Receipt,
}

#[derive(Debug)]
pub struct TurnMessage {
    shot: Position,
}

pub struct RoundMessage {
    receipt: Receipt,
}

#[derive(Debug)]
pub struct Battleship {
    state: GameState,
    last_shot: Position,
    peer_state: Digest,
}

impl InitMessage {
    pub fn get_state(&self) -> Result<Digest> {
        let msg = self.receipt.get_journal_vec()?;
        Ok(from_slice(msg.as_slice()).unwrap())
    }
}

impl RoundMessage {
    pub fn get_commit(&self) -> Result<RoundCommit> {
        let msg = self.receipt.get_journal_vec()?;
        Ok(from_slice(msg.as_slice()).unwrap())
    }
}

impl Battleship {
    pub fn new(state: GameState) -> Self {
        Battleship {
            state,
            last_shot: Position::new(0, 0),
            peer_state: Digest::default(),
        }
    }

    pub fn init(&self) -> Result<InitMessage> {
        let temp_dir = tempdir().unwrap();
        let init_id = temp_dir
            .path()
            .join("init.id")
            .to_str()
            .unwrap()
            .to_string();
        fs::write(&init_id, INIT_ID).unwrap();

        let mut prover = Prover::new(INIT_PATH, &init_id)?;
        let vec = to_vec(&self.state).unwrap();
        prover.add_input(vec.as_slice())?;
        let receipt = prover.run()?;
        Ok(InitMessage { receipt })
    }

    pub fn on_init_msg(&mut self, msg: &InitMessage) -> Result<()> {
        log::info!("on_init_msg");

        let temp_dir = tempdir().unwrap();
        let init_id = temp_dir
            .path()
            .join("init.id")
            .to_str()
            .unwrap()
            .to_string();
        fs::write(&init_id, INIT_ID).unwrap();

        msg.receipt.verify(&init_id)?;
        self.peer_state = msg.get_state()?;
        log::info!("  peer_state: {:?}", self.peer_state);
        Ok(())
    }

    pub fn turn(&mut self, x: u32, y: u32) -> TurnMessage {
        let shot = Position::new(x, y);
        log::info!("turn: {}", shot);
        self.last_shot = shot.clone();
        TurnMessage { shot: shot.clone() }
    }

    pub fn on_turn_msg(&mut self, msg: &TurnMessage) -> Result<RoundMessage> {
        log::info!("on_turn_msg: {:?}", msg);
        let params = RoundParams::new(self.state.clone(), msg.shot.x, msg.shot.y);

        let temp_dir = tempdir().unwrap();
        let turn_id = temp_dir
            .path()
            .join("turn.id")
            .to_str()
            .unwrap()
            .to_string();
        fs::write(&turn_id, TURN_ID).unwrap();

        let mut prover = Prover::new(TURN_PATH, &turn_id)?;
        let vec = to_vec(&params).unwrap();
        prover.add_input(vec.as_slice())?;
        let receipt = prover.run()?;
        let vec = prover.get_output_vec()?;
        let result = from_slice::<RoundResult>(vec.as_slice()).unwrap();
        self.state = result.state.clone();
        Ok(RoundMessage { receipt })
    }

    pub fn on_round_msg(&mut self, msg: &RoundMessage) -> Result<HitType> {
        log::info!("on_round_msg");

        let temp_dir = tempdir().unwrap();
        let turn_id = temp_dir
            .path()
            .join("turn.id")
            .to_str()
            .unwrap()
            .to_string();
        fs::write(&turn_id, TURN_ID).unwrap();

        msg.receipt.verify(&turn_id)?;
        let commit = msg.get_commit()?;
        log::info!("  commit: {:?}", commit);

        if commit.old_state != self.peer_state {
            return Err(Exception::new(
                format!(
                    "Cheater: state mismatch. old_state ({}) != peer_state ({})",
                    commit.old_state, self.peer_state
                )
                .as_str(),
            ));
        }

        if commit.shot != self.last_shot {
            return Err(Exception::new(
                format!(
                    "Cheater: shot mismatch. cur_shot ({}) != last_shot ({})",
                    commit.shot, self.last_shot
                )
                .as_str(),
            ));
        }

        self.peer_state = commit.new_state.clone();

        Ok(commit.hit.clone())
    }
}

fn round(player1: &mut Battleship, player2: &mut Battleship, x: u32, y: u32) -> HitType {
    let turn = player1.turn(x, y);
    player1
        .on_round_msg(&player2.on_turn_msg(&turn).unwrap())
        .unwrap()
}

#[ctor::ctor]
fn init() {
    env_logger::builder().filter_level(LevelFilter::Info).init();
}

#[test]
fn serde() {
    struct Logger;
    impl risc0_zkvm_core::Log for Logger {
        fn log(&self, msg: &str) {
            log::info!("{}", msg);
        }
    }
    static LOGGER: Logger = Logger;
    risc0_zkvm_core::set_logger(&LOGGER);
    let commit = RoundCommit {
        old_state: Digest::new([0, 1, 2, 3, 4, 5, 6, 7]),
        new_state: Digest::new([8, 7, 6, 5, 4, 3, 2, 1]),
        shot: Position::new(1, 9),
        hit: HitType::Hit,
    };
    let buf: &mut [u32] = &mut [0; 256];
    let buf = to_slice(&commit, buf).unwrap();
    log::info!("buf: {}, {:x?}", buf.len(), buf);
    let result = from_slice(buf).unwrap();
    assert_eq!(commit, result);
}

#[test]
fn protocol() {
    // Player Alice
    //  | 0 1 2 3 4 5 6 7 8 9 |
    // 0|                     |
    // 1|       B B B B       |
    // 2|                     |
    // 3|     A               |
    // 4|     A               |
    // 5|     A         D D D |
    // 6|     A               |
    // 7|     A   C     E E   |
    // 8|         C           |
    // 9|         C           |
    let alice_state = GameState {
        ships: [
            Ship::new(2, 3, ShipDirection::Vertical),
            Ship::new(3, 1, ShipDirection::Horizontal),
            Ship::new(4, 7, ShipDirection::Vertical),
            Ship::new(7, 5, ShipDirection::Horizontal),
            Ship::new(7, 7, ShipDirection::Horizontal),
        ],
        salt: 0xDEADBEEF,
    };

    // Player Bob
    //  | 0 1 2 3 4 5 6 7 8 9 |
    // 0| B B B B           A |
    // 1| C                 A |
    // 2| C                 A |
    // 3| C                 A |
    // 4| D                 A |
    // 5| D                   |
    // 6| D                   |
    // 7| E                   |
    // 8| E                   |
    // 9|                     |
    let bob_state = GameState {
        ships: [
            Ship::new(9, 0, ShipDirection::Vertical),
            Ship::new(0, 0, ShipDirection::Horizontal),
            Ship::new(0, 1, ShipDirection::Vertical),
            Ship::new(0, 4, ShipDirection::Vertical),
            Ship::new(0, 7, ShipDirection::Vertical),
        ],
        salt: 0xCAFECAFE,
    };

    let mut alice = Battleship::new(alice_state);
    let mut bob = Battleship::new(bob_state);

    let init = alice.init().unwrap();

    bob.on_init_msg(&init).unwrap();
    alice.on_init_msg(&bob.init().unwrap()).unwrap();

    assert_eq!(round(&mut alice, &mut bob, 1, 1), HitType::Miss);
    assert_eq!(round(&mut bob, &mut alice, 3, 1), HitType::Hit);

    assert_eq!(round(&mut alice, &mut bob, 0, 0), HitType::Hit);
    assert_eq!(round(&mut bob, &mut alice, 4, 1), HitType::Hit);

    assert_eq!(round(&mut alice, &mut bob, 0, 1), HitType::Hit);
    assert_eq!(round(&mut bob, &mut alice, 5, 1), HitType::Hit);

    assert_eq!(round(&mut alice, &mut bob, 0, 2), HitType::Hit);
    assert_eq!(round(&mut bob, &mut alice, 6, 1), HitType::Sunk(1));
}
