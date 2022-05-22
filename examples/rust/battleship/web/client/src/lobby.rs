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

use std::rc::Rc;

use web_sys::HtmlInputElement;
use yew::prelude::*;
use yew_agent::{Dispatched, Dispatcher};
use yew_router::{components::Link, history::History, prelude::RouterScopeExt};

use crate::{bus::EventBus, contract::Contract, near::NearContract, wallet::WalletContext, Route};

pub struct Lobby {
    journal: Dispatcher<EventBus<String>>,
    contract: Rc<NearContract>,
    games: Vec<String>,
}

#[derive(Clone)]
pub enum Msg {
    ClearGames,
    ListGames(Vec<String>),
    NewGame(String),
}

impl Component for Lobby {
    type Message = Msg;
    type Properties = ();

    fn create(ctx: &yew::Context<Self>) -> Self {
        let (wallet, _) = ctx
            .link()
            .context::<WalletContext>(Callback::noop())
            .unwrap();
        let contract = wallet.contract.clone();
        ctx.link()
            .send_future(async move { Msg::ListGames(contract.list_games().await.unwrap()) });
        Lobby {
            journal: EventBus::dispatcher(),
            contract: wallet.contract.clone(),
            games: Vec::new(),
        }
    }

    fn update(&mut self, ctx: &Context<Self>, msg: Self::Message) -> bool {
        match msg {
            Msg::ListGames(games) => {
                self.journal.send("Lobby::ListGames".into());
                self.games = games;
                true
            }
            Msg::ClearGames => {
                self.journal.send("Lobby::ClearGames".into());
                let contract = self.contract.clone();
                ctx.link().send_future(async move {
                    contract.clear_games().await.unwrap();
                    Msg::ListGames(contract.list_games().await.unwrap())
                });
                true
            }
            Msg::NewGame(name) => {
                self.journal.send("Lobby::NewGame".into());
                ctx.link().history().unwrap().push(Route::NewGame { name });
                true
            }
        }
    }

    fn view(&self, ctx: &yew::Context<Self>) -> yew::Html {
        let onkeypress = ctx.link().batch_callback(|e: KeyboardEvent| {
            if e.key() == "Enter" {
                let input: HtmlInputElement = e.target_unchecked_into();
                let value = input.value();
                input.set_value("");
                Some(Msg::NewGame(value))
            } else {
                None
            }
        });
        let games = self.games.clone();
        html! {
            <div>
                <h3>{"Games"}</h3>
                if games.is_empty() {
                    <p>{"No games"}</p>
                } else {
                    <ul>
                    {
                        games.into_iter().map(|name| {
                            html! {
                                <li key={name.clone()}>
                                    <Link<Route> to={Route::JoinGame { name: name.clone() }}>
                                        {name}
                                    </Link<Route>>
                                </li>
                            }
                        }).collect::<Html>()
                    }
                    </ul>
                }
                <button
                    class="btn btn-primary"
                    onclick={ctx.link().callback(|_|Msg::ClearGames)}>
                    {"Clear"}
                </button>
                <form>
                    <input
                        placeholder="Enter new game name"
                        {onkeypress}
                    />
                </form>
            </div>
        }
    }
}
