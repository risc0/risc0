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

use async_trait::async_trait;
use serde::{Deserialize, Serialize};
use wasm_bindgen::JsValue;

#[async_trait(?Send)]
pub trait Contract {
    async fn list_games(&self) -> Result<Vec<String>, JsValue>;

    async fn clear_games(&self) -> Result<(), JsValue>;

    async fn get_state(&self, name: &str) -> Result<ContractState, JsValue>;

    async fn new_game(&self, name: &str, receipt: &str) -> Result<(), JsValue>;

    async fn join_game(
        &self,
        name: &str,
        receipt: &str,
        shot_x: u32,
        shot_y: u32,
    ) -> Result<(), JsValue>;

    async fn turn(
        &self,
        name: &str,
        receipt: &str,
        shot_x: u32,
        shot_y: u32,
    ) -> Result<(), JsValue>;
}

#[derive(Default, Debug, Serialize, Deserialize, Clone, PartialEq)]
pub struct PlayerState {
    pub id: String,
    pub board: [u32; 8],
    pub shot_x: u32,
    pub shot_y: u32,
}

#[derive(Default, Debug, Serialize, Deserialize, Clone, PartialEq)]
pub struct ContractState {
    // 0 means p1 has setup game, and p2 needs to do setup
    // 1 means p1 needs to process p2's shot and make it's own
    // 2 means p2 needs to process p1's shot and make it's own
    pub next_turn: u32,
    pub p1: PlayerState,
    pub p2: PlayerState,
    pub last_hit: Option<u8>,  // 0 = miss, 1 = hit, 2 = sunk
    pub sunk_what: Option<u8>, // Which ship was sunk
}

impl ContractState {
    pub fn from_jsvalue(value: JsValue) -> Self {
        serde_wasm_bindgen::from_value(value).unwrap()
    }
}
