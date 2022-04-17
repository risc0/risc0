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

use std::{cell::Cell, rc::Rc};

use async_trait::async_trait;
use gloo::timers::future::TimeoutFuture;
use js_sys::Date;
use rand::{rngs::SmallRng, Rng, SeedableRng};
use reqwasm::http;
use serde::{Deserialize, Serialize};
use wasm_bindgen::prelude::*;
use weblog::console_log;
use yew::prelude::*;

use battleship_core::{GameState, Position, RoundParams, Ship, ShipDirection};

const WAIT_TURN_INTERVAL: u32 = 5_000;

#[wasm_bindgen]
extern "C" {
    pub type NearContract;

    #[wasm_bindgen(catch)]
    pub fn near_connect() -> Result<NearContract, JsValue>;

    #[wasm_bindgen(catch)]
    pub async fn game_state(contract: &NearContract, name: &str) -> Result<JsValue, JsValue>;

    #[wasm_bindgen(catch)]
    pub async fn new_game(
        contract: &NearContract,
        name: &str,
        receipt: &str,
    ) -> Result<(), JsValue>;

    #[wasm_bindgen(catch)]
    pub async fn join_game(
        contract: &NearContract,
        name: &str,
        receipt: &str,
        shot_x: u32,
        shot_y: u32,
    ) -> Result<(), JsValue>;

    #[wasm_bindgen(catch)]
    pub async fn turn(
        contract: &NearContract,
        name: &str,
        receipt: &str,
        shot_x: u32,
        shot_y: u32,
    ) -> Result<(), JsValue>;
}

#[derive(Default, Debug, Serialize, Deserialize)]
pub struct PlayerState {
    id: String,
    board: [u32; 8],
    shot_x: u32,
    shot_y: u32,
}

#[derive(Default, Debug, Serialize, Deserialize)]
pub struct ContractState {
    // 0 means p1 has setup game, and p2 needs to do setup
    // 1 means p1 needs to process p2's shot and make it's own
    // 2 means p2 needs to process p1's shot and make it's own
    next_turn: u32,
    p1: PlayerState,
    p2: PlayerState,
    last_hit: u8,  // 0 = miss, 1 = hit, 2 = sunk
    sunk_what: u8, // Which ship was sunk
}

impl ContractState {
    fn new(value: JsValue) -> Self {
        log::info!("ContractState::new");
        console_log!(&value);
        serde_wasm_bindgen::from_value(value).unwrap()
    }
}

#[async_trait(?Send)]
trait Contract {
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

struct Near {
    contract: NearContract,
}

impl Near {
    fn new() -> Result<Self, JsValue> {
        Ok(Near {
            contract: near_connect()?,
        })
    }
}

#[async_trait(?Send)]
impl Contract for Near {
    async fn get_state(&self, name: &str) -> Result<ContractState, JsValue> {
        let value: JsValue = game_state(&self.contract, name).await?;
        let state = ContractState::new(value);
        log::info!("{:?}", state);
        Ok(state)
    }

    async fn new_game(&self, name: &str, receipt: &str) -> Result<(), JsValue> {
        new_game(&self.contract, name, receipt).await
    }

    async fn join_game(
        &self,
        name: &str,
        receipt: &str,
        shot_x: u32,
        shot_y: u32,
    ) -> Result<(), JsValue> {
        join_game(&self.contract, name, receipt, shot_x, shot_y).await
    }

    async fn turn(
        &self,
        name: &str,
        receipt: &str,
        shot_x: u32,
        shot_y: u32,
    ) -> Result<(), JsValue> {
        turn(&self.contract, name, receipt, shot_x, shot_y).await
    }
}

struct Mock {
    next_turn: Cell<u32>,
}

impl Mock {
    fn new() -> Self {
        Mock {
            next_turn: Cell::new(0),
        }
    }
}

#[async_trait(?Send)]
impl Contract for Mock {
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

enum Msg {
    NewGame { receipt: String },
    JoinGame { receipt: String },
    WaitTurn,
    ProcessTurn { contract_state: ContractState },
    UpdateState { receipt: String, state: GameState },
    SelectShot { pos: Position },
    Error(String),
}

// Start -> NewGame, JoinGame
// NewGame -> WaitTurn(1)
// JoinGame -> WaitTurn(2)
// WaitTurn(x) -> WaitTurn(x), ProcessTurn
// ProcessTurn -> UpdateState
// SelectShot -> WaitTurn(x)

struct App {
    lines: Vec<String>,
    contract: Rc<Mock>,
    // contract: Rc<Near>,
    state: GameState,
    game_id: String,
    side: u32,
    rng: SmallRng,
    last_receipt: String,
}

impl Component for App {
    type Message = Msg;
    type Properties = ();

    fn create(ctx: &Context<Self>) -> Self {
        let contract = Rc::new(Mock::new());
        // let contract = Rc::new(Near::new().unwrap());
        // console_log!(near.contract.as_ref());
        let state = GameState {
            ships: [
                Ship::new(2, 3, ShipDirection::Vertical),
                Ship::new(3, 1, ShipDirection::Horizontal),
                Ship::new(4, 7, ShipDirection::Vertical),
                Ship::new(7, 5, ShipDirection::Horizontal),
                Ship::new(7, 7, ShipDirection::Horizontal),
            ],
            salt: 0xDEADBEEF,
        };
        let body = serde_json::to_string(&state).unwrap();
        ctx.link().send_future(async {
            let response = http::Request::post("/prove/init")
                .header("Content-Type", "application/json")
                .body(body)
                .send()
                .await;
            match response {
                Ok(response) => {
                    log::info!("{:?}", response);
                    let receipt = response.text().await.unwrap();
                    Msg::NewGame { receipt }
                }
                Err(err) => {
                    log::info!("Error: {:?}", err);
                    let msg = format!("Error: {}", err);
                    Msg::Error(msg)
                }
            }
        });

        Self {
            lines: vec!["App.create".into()],
            contract,
            state,
            game_id: format!("game-{}", Date::now()),
            side: 1,
            rng: SmallRng::from_entropy(),
            last_receipt: String::new(),
        }
    }

    fn update(&mut self, ctx: &Context<Self>, msg: Self::Message) -> bool {
        log::info!("update");
        let contract = self.contract.clone();
        let game_id = self.game_id.clone();
        match msg {
            Msg::NewGame { receipt } => {
                self.lines.push(format!("NewGame: {}", receipt.len()));
                ctx.link().send_future(async move {
                    match contract.new_game(&game_id, &receipt).await {
                        Ok(()) => Msg::WaitTurn,
                        Err(err) => {
                            console_log!(&err);
                            Msg::Error(format!("{:?}", err))
                        }
                    }
                });
                true
            }
            Msg::JoinGame { receipt } => {
                self.lines.push(format!("JoinGame: {}", receipt.len()));
                ctx.link().send_future(async move {
                    contract.join_game(&game_id, &receipt, 5, 5).await.unwrap();
                    Msg::WaitTurn
                });
                true
            }
            Msg::WaitTurn => {
                self.lines.push(format!("WaitTurn"));
                let side = self.side;
                ctx.link().send_future(async move {
                    let contract_state = contract.get_state(&game_id).await.unwrap();
                    log::info!("contract_state: {:?}", contract_state);
                    if contract_state.next_turn == side {
                        Msg::ProcessTurn { contract_state }
                    } else {
                        TimeoutFuture::new(WAIT_TURN_INTERVAL).await;
                        Msg::WaitTurn
                    }
                });
                true
            }
            Msg::ProcessTurn { contract_state } => {
                self.lines.push(format!("ProcessTurn"));
                let state = self.state.clone();
                let side = self.side;
                ctx.link().send_future(async move {
                    let player = if side == 1 {
                        contract_state.p1
                    } else {
                        contract_state.p2
                    };
                    let params = RoundParams {
                        state: state.clone(),
                        shot: Position::new(player.shot_x, player.shot_y),
                    };
                    let body = serde_json::to_string(&params).unwrap();
                    let response = http::Request::post("/prove/turn")
                        .header("Content-Type", "application/json")
                        .body(body)
                        .send()
                        .await;
                    // TODO: /prove/turn needs to return a RoundResult
                    match response {
                        Ok(response) => {
                            log::info!("{:?}", response);
                            let receipt = response.text().await.unwrap();
                            Msg::UpdateState { receipt, state }
                        }
                        Err(err) => {
                            log::info!("Error: {:?}", err);
                            let msg = format!("Error: {}", err);
                            Msg::Error(msg)
                        }
                    }
                });
                true
            }
            Msg::UpdateState { receipt, state } => {
                self.lines.push(format!("UpdateState: {:?}", state));
                self.state = state;
                self.last_receipt = receipt;
                // TODO: replace bot with human
                let pos = Position::new(self.rng.gen_range(0..=9), self.rng.gen_range(0..=9));
                ctx.link().send_message(Msg::SelectShot { pos });
                true
            }
            Msg::SelectShot { pos } => {
                self.lines.push(format!("SelectShot: {:?}", pos));
                let last_receipt = self.last_receipt.clone();
                ctx.link().send_future(async move {
                    contract
                        .turn(&game_id, &last_receipt, pos.x, pos.y)
                        .await
                        .unwrap();
                    Msg::WaitTurn
                });
                true
            }
            Msg::Error(msg) => {
                self.lines.push(format!("Error: {}", msg));
                true
            }
        }
    }

    fn view(&self, _ctx: &Context<Self>) -> Html {
        // let onclick = ctx.link().callback(|_| Msg::AddOne);
        html! {
            <div>
                <h1>{ "Battleship!" }</h1>
                <ul>
                    { for self.lines.iter().map(|line| html! { <ul>{line.clone()}</ul> }) }
                </ul>
                // <div>
                //     <button {onclick}>{ "+1" }</button>
                //     <p>{ self.value }</p>
                // </div>
            </div>
        }
    }
}

fn main() {
    wasm_logger::init(wasm_logger::Config::default());
    log::info!("Hello world!");
    yew::start_app::<App>();
}
