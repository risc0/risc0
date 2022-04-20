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
use wasm_bindgen::JsValue;

use crate::{contract::Contract, contract::ContractState, ffi};

pub struct NearWallet {
    wallet: ffi::NearWallet,
}

impl PartialEq for NearWallet {
    fn eq(&self, other: &Self) -> bool {
        self.wallet.cmp(&other.wallet).unwrap()
    }
}

impl NearWallet {
    pub fn new() -> Result<Self, JsValue> {
        Ok(NearWallet {
            wallet: ffi::NearWallet::new()?,
        })
    }

    pub fn sign_in(&self) -> Result<(), JsValue> {
        self.wallet.sign_in()
    }

    pub fn sign_out(&self) -> Result<(), JsValue> {
        self.wallet.sign_out()
    }

    pub fn current_user(&self) -> Result<String, JsValue> {
        self.wallet.current_user()
    }

    pub fn get_contract(&self) -> Result<NearContract, JsValue> {
        let contract = self.wallet.get_contract()?;
        Ok(NearContract::new(contract))
    }
}

pub struct NearContract {
    contract: ffi::NearContract,
}

impl NearContract {
    fn new(contract: ffi::NearContract) -> Self {
        NearContract { contract }
    }
}

impl PartialEq for NearContract {
    fn eq(&self, other: &Self) -> bool {
        self.contract.contract_id() == other.contract.contract_id()
    }
}

#[async_trait(?Send)]
impl Contract for NearContract {
    async fn get_state(&self, name: &str) -> Result<ContractState, JsValue> {
        let value: JsValue = self.contract.game_state(name).await?;
        Ok(ContractState::from_jsvalue(value))
    }

    async fn list_games(&self) -> Result<Vec<String>, JsValue> {
        let games = self.contract.list_games().await?;
        Ok(games.into_serde().unwrap())
    }

    async fn clear_games(&self) -> Result<(), JsValue> {
        self.contract.clear_games().await
    }

    async fn new_game(&self, name: &str, receipt: &str) -> Result<(), JsValue> {
        self.contract.new_game(name, receipt).await
    }

    async fn join_game(
        &self,
        name: &str,
        receipt: &str,
        shot_x: u32,
        shot_y: u32,
    ) -> Result<(), JsValue> {
        self.contract.join_game(name, receipt, shot_x, shot_y).await
    }

    async fn turn(
        &self,
        name: &str,
        receipt: &str,
        shot_x: u32,
        shot_y: u32,
    ) -> Result<(), JsValue> {
        self.contract.turn(name, receipt, shot_x, shot_y).await
    }
}
