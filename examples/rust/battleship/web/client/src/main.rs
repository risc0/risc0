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
use yew::prelude::*;

use battleship_core::{GameState, Ship, ShipDirection};

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
        ctx.link().send_future(async {
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
                .body(body)
                .header("Content-Type", "application/json")
                .send()
                .await;
            match response {
                Ok(response) => {
                    log::info!("Response: {:?}", response);
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
