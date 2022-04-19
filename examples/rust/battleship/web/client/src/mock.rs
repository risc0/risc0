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

use std::cell::Cell;

use async_trait::async_trait;
use wasm_bindgen::JsValue;

use crate::contract::{Contract, ContractState};

pub struct Mock {
    next_turn: Cell<u32>,
}

impl Mock {
    pub fn new() -> Self {
        Mock {
            next_turn: Cell::new(0),
        }
    }
}

#[async_trait(?Send)]
impl Contract for Mock {
    async fn list_games(&self) -> Result<Vec<String>, JsValue> {
        todo!()
    }

    async fn clear_games(&self) -> Result<(), JsValue> {
        todo!()
    }

    async fn get_state(&self, _name: &str) -> Result<ContractState, JsValue> {
        let mut state = ContractState::default();
        state.next_turn = self.next_turn.get();
        let next_turn = match state.next_turn {
            0 => 1,
            1 => 2,
            2 => 1,
            _ => unreachable!(),
        };
        log::info!("next_turn: {}", next_turn);
        self.next_turn.set(next_turn);
        Ok(state)
    }

    async fn new_game(&self, _name: &str, _receipt: &str) -> Result<(), JsValue> {
        Ok(())
    }

    async fn join_game(
        &self,
        _name: &str,
        _receipt: &str,
        _shot_x: u32,
        _shot_y: u32,
    ) -> Result<(), JsValue> {
        Ok(())
    }

    async fn turn(
        &self,
        _name: &str,
        _receipt: &str,
        _shot_x: u32,
        _shot_y: u32,
    ) -> Result<(), JsValue> {
        Ok(())
    }
}
