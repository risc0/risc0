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

use wasm_bindgen::prelude::*;

#[wasm_bindgen(module = "/near.js")]
extern "C" {
    pub type NearWallet;

    #[wasm_bindgen(constructor, catch)]
    pub fn new() -> Result<NearWallet, JsValue>;

    #[wasm_bindgen(method, catch)]
    pub fn sign_in(this: &NearWallet) -> Result<(), JsValue>;

    #[wasm_bindgen(method, catch)]
    pub fn sign_out(this: &NearWallet) -> Result<(), JsValue>;

    #[wasm_bindgen(method, catch)]
    pub fn current_user(this: &NearWallet) -> Result<String, JsValue>;

    #[wasm_bindgen(method, catch)]
    pub fn get_contract(this: &NearWallet) -> Result<NearContract, JsValue>;

    #[wasm_bindgen(method, catch)]
    pub fn cmp(this: &NearWallet, other: &NearWallet) -> Result<bool, JsValue>;
}

#[wasm_bindgen(module = "/near.js")]
extern "C" {
    pub type NearContract;

    #[wasm_bindgen(method)]
    pub fn contract_id(this: &NearContract) -> String;

    #[wasm_bindgen(method, catch)]
    pub async fn list_games(this: &NearContract) -> Result<JsValue, JsValue>;

    #[wasm_bindgen(method, catch)]
    pub async fn clear_games(this: &NearContract) -> Result<(), JsValue>;

    #[wasm_bindgen(method, catch)]
    pub async fn game_state(this: &NearContract, name: &str) -> Result<JsValue, JsValue>;

    #[wasm_bindgen(method, catch)]
    pub async fn new_game(this: &NearContract, name: &str, receipt: &str) -> Result<(), JsValue>;

    #[wasm_bindgen(method, catch)]
    pub async fn join_game(
        this: &NearContract,
        name: &str,
        receipt: &str,
        shot_x: u32,
        shot_y: u32,
    ) -> Result<(), JsValue>;

    #[wasm_bindgen(method, catch)]
    pub async fn turn(
        this: &NearContract,
        name: &str,
        receipt: &str,
        shot_x: u32,
        shot_y: u32,
    ) -> Result<(), JsValue>;
}
