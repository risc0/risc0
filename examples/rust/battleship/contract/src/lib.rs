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

use arrayref::array_ref;
use near_sdk::{
    borsh::{self, BorshDeserialize, BorshSerialize},
    collections::UnorderedMap,
    env, near_bindgen, AccountId,
};
use serde::{Deserialize, Serialize};

use risc0_zkvm_core::Digest;
use risc0_zkvm_verify::zkvm::{MethodID, Receipt};

use battleship_core::{HitType, RoundCommit};
use battleship_methods::methods::{INIT_ID, TURN_ID};

#[derive(Default, Deserialize, Serialize, BorshDeserialize, BorshSerialize)]
pub struct PlayerState {
    id: AccountId,
    board: [u32; 8],
    shot_x: u32,
    shot_y: u32,
}

#[derive(Default, Deserialize, Serialize, BorshDeserialize, BorshSerialize)]
pub struct GameState {
    // 0 means p1 has setup game, and p2 needs to do setup
    // 1 means p1 needs to process p2's shot and make it's own
    // 2 means p2 needs to process p1's shot and make it's own
    next_turn: u32,
    p1: PlayerState,
    p2: PlayerState,
    last_hit: u8,  // 0 = miss, 1 = hit, 2 = sunk
    sunk_what: u8, // Which ship was sunk
}

#[near_bindgen]
#[derive(BorshDeserialize, BorshSerialize)]
pub struct BattleshipContract {
    games: UnorderedMap<String, GameState>,
}

impl Default for BattleshipContract {
    fn default() -> Self {
        BattleshipContract {
            games: UnorderedMap::<String, GameState>::new(0 as u8),
        }
    }
}

pub fn verify_receipt(str: &String, method_id: &MethodID) -> Vec<u32> {
    let as_bytes = base64::decode(str).unwrap();
    let receipt = bincode::deserialize::<Receipt>(&as_bytes).unwrap();
    receipt.verify(&method_id);
    receipt.get_journal_u32()
}

#[near_bindgen]
impl BattleshipContract {
    // View state of a game
    pub fn game_state(&self, name: String) -> Option<GameState> {
        self.games.get(&name)
    }

    pub fn list_games(&self) -> Vec<String> {
        self.games.keys().collect()
    }

    pub fn delete_game(&mut self, name: String) {
        self.games.remove(&name);
    }

    pub fn clear_games(&mut self) {
        self.games.clear();
    }

    // Set's p1's initial state
    pub fn new_game(&mut self, name: String, receipt_str: String) -> GameState {
        // Game must not exist
        assert!(self.games.get(&name).is_none());
        let method_id = MethodID::try_from(INIT_ID).unwrap();
        let journal = verify_receipt(&receipt_str, &method_id);
        let digest = risc0_zkvm_serde::from_slice::<Digest>(&journal).unwrap();
        let state = GameState {
            next_turn: 0,
            p1: PlayerState {
                id: env::signer_account_id(),
                board: *array_ref![digest.as_slice(), 0, 8],
                shot_x: 0,
                shot_y: 0,
            },
            p2: PlayerState::default(),
            last_hit: 0,
            sunk_what: 0,
        };
        self.games.insert(&name, &state);
        state
    }

    // Set's p2's state, and makes the first shot at p1
    pub fn join_game(
        &mut self,
        name: String,
        receipt_str: String,
        shot_x: u32,
        shot_y: u32,
    ) -> GameState {
        // Get game record (panic if not there)
        let mut state = self.games.get(&name).unwrap();
        // Verify we are are on turn 0
        assert!(state.next_turn == 0);
        // Set turn to 1
        state.next_turn = 1;
        // Verify the player has a valid initial state
        let method_id = MethodID::try_from(INIT_ID).unwrap();
        let journal = verify_receipt(&receipt_str, &method_id);
        let digest = risc0_zkvm_serde::from_slice::<Digest>(&journal).unwrap();
        // Update player 2 starting state + set shot
        state.p2 = PlayerState {
            id: env::signer_account_id(),
            board: *array_ref![digest.as_slice(), 0, 8],
            shot_x,
            shot_y,
        };
        // Write back to contract
        self.games.insert(&name, &state);
        state
    }

    // Do a normal turn
    pub fn turn(
        &mut self,
        name: String,
        receipt_str: String,
        shot_x: u32,
        shot_y: u32,
    ) -> GameState {
        // Get game record (panic if not there)
        let mut state = self.games.get(&name).unwrap();
        // Verify we are are on turn 1 or 2
        assert!(state.next_turn >= 1);
        // Get ref to player current player (responding prior shot, making new one)
        let (cur_player, prev_player) = if state.next_turn == 1 {
            (&mut state.p1, &mut state.p2)
        } else {
            (&mut state.p2, &mut state.p1)
        };
        // Verify the right user is playing
        assert!(cur_player.id == env::signer_account_id());
        // Verify the proof and extract as a RoundCommit
        let method_id = MethodID::try_from(TURN_ID).unwrap();
        let journal = verify_receipt(&receipt_str, &method_id);
        let commit = risc0_zkvm_serde::from_slice::<RoundCommit>(&journal).unwrap();
        // Make sure the prior state matches the current state
        assert!(cur_player.board.as_slice() == commit.old_state.as_slice());
        // Make sure the response matches the prior shot
        assert!(commit.shot.x == prev_player.shot_x);
        assert!(commit.shot.y == prev_player.shot_y);
        // Set the hit status
        match commit.hit {
            HitType::Miss => {
                state.last_hit = 0;
            }
            HitType::Hit => {
                state.last_hit = 1;
            }
            HitType::Sunk(ship) => {
                state.last_hit = 2;
                state.sunk_what = ship;
            }
        };
        // Update the current players state
        cur_player.board = *array_ref![commit.new_state.as_slice(), 0, 8];
        // Set the new shot
        cur_player.shot_x = shot_x;
        cur_player.shot_y = shot_y;
        // Update which player's turn it is
        state.next_turn = 3 - state.next_turn;
        // Write back to contract
        self.games.insert(&name, &state);
        state
    }
}
