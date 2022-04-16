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

use reqwasm::http;
use wasm_bindgen::prelude::*;
use weblog::console_log;
use yew::prelude::*;

use battleship_core::{GameState, Ship, ShipDirection};

#[wasm_bindgen]
extern "C" {
    pub type Contract;

    #[wasm_bindgen]
    pub fn near_connect() -> Contract;

    #[wasm_bindgen]
    pub async fn game_state(contract: &Contract, name: &str) -> JsValue;

    #[wasm_bindgen]
    pub async fn new_game(contract: &Contract, name: &str, receipt: &str);

    #[wasm_bindgen]
    pub async fn join_game(
        contract: &Contract,
        name: &str,
        receipt: &str,
        shot_x: u32,
        shot_y: u32,
    );

    #[wasm_bindgen]
    pub async fn turn(contract: &Contract, name: &str, receipt: &str, shot_x: u32, shot_y: u32);
}

enum Msg {
    AddOne,
}

struct App {
    value: i64,
    player1: String,
    CPU: String,
}

impl Component for App {
    type Message = Msg;
    type Properties = ();

    fn create(ctx: &Context<Self>) -> Self {
        let contract = near_connect();
        console_log!(&contract);

        ctx.link().send_future(async move {
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
            let response = http::Request::post("/prove/init")
                .header("Content-Type", "application/json")
                .body(body)
                .send()
                .await;
            match response {
                Ok(response) => {
                    log::info!("Response: {:?}", response);
                    // join_game(&contract, "game", &response.text().await.unwrap(), 5, 5).await;
                    // new_game(&contract, "game", &response.text().await.unwrap()).await;
                    console_log!(game_state(&contract, "game").await);
                    Msg::AddOne
                }
                Err(err) => {
                    log::info!("Error: {}", err);
                    Msg::AddOne
                }
            }
        });
        Self {
            value: 0,
            player1: "Rami".to_string(),
            CPU: "CPU".to_string(),
         }
    }

    fn update(&mut self, _ctx: &Context<Self>, msg: Self::Message) -> bool {
        log::info!("update");
        match msg {
            Msg::AddOne => {
                self.value += 1;
                // the value has changed so we need to
                // re-render for it to appear on the page
                true
            }
        }
    }

    fn view(&self, ctx: &Context<Self>) -> Html {
        let onclick = ctx.link().callback(|_: App| Msg::AddOne);
        let player = self.player1.to_string();
        let cpu = self.CPU.to_string();
        html! {
            <>
            <div class="header">
            <img src="assets/risc0/banner.png" alt="Risc0 Banner" />
            </div>
            <br />
            <div class="gamefield">
                <div class="playerField">
                <h3 class="playerName">{player}</h3>
                <table class="matrix">
                    <tbody>
                    <tr>
                        <td><span class="dot red"></span></td>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot red"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot red"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    </tbody>
                </table>
                </div>
                <hr />
                <div class="cpuField">
                <h3 class="playerName">{cpu}</h3>
                <table class="matrix">

                    <tbody>
                    <tr>
                        <td><span class="dot red"></span></td>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot red"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    <tr>
                        <td><span class="dot white"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot red"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                        <td><span class="dot"></span></td>
                    </tr>
                    </tbody>
                </table>
                </div>
            </div>
            </>
        }
    }
}

fn main() {
    wasm_logger::init(wasm_logger::Config::default());
    log::info!("Hello world!");
    yew::start_app::<App>();
}
