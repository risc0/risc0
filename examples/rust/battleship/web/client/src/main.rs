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
        Self { value: 0 }
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
        let onclick = ctx.link().callback(|_| Msg::AddOne);
        html! {
            <div>
                <h1>{ "Battleship!" }</h1>
                <div>
                    <button {onclick}>{ "+1" }</button>
                    <p>{ self.value }</p>
                </div>
            </div>
        }
    }
}

fn main() {
    wasm_logger::init(wasm_logger::Config::default());
    log::info!("Hello world!");
    yew::start_app::<App>();
}
