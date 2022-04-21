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

mod board;
mod bus;
mod contract;
mod ffi;
mod game;
mod journal;
mod layout;
mod lobby;
mod near;
mod wallet;

use std::rc::Rc;

use bus::EventBus;
use near::NearWallet;
use yew::prelude::*;
use yew_agent::{Dispatched, Dispatcher};
use yew_router::prelude::*;

use crate::{
    game::GameProvider, journal::Journal, layout::Layout, lobby::Lobby, wallet::WalletProvider,
};

#[derive(Debug, Clone, PartialEq, Routable)]
enum Route {
    #[at("/")]
    Lobby,
    #[at("/new/:name")]
    NewGame { name: String },
    #[at("/join/:name")]
    JoinGame { name: String },
    #[not_found]
    #[at("/404")]
    NotFound,
}

enum Msg {
    SignIn,
    SignOut,
}

struct App {
    journal: Dispatcher<EventBus<String>>,
    wallet: Rc<NearWallet>,
}

impl Component for App {
    type Message = Msg;
    type Properties = ();

    fn create(_ctx: &Context<Self>) -> Self {
        let wallet = Rc::new(NearWallet::new().unwrap());
        Self {
            journal: EventBus::dispatcher(),
            wallet,
        }
    }

    fn update(&mut self, _ctx: &Context<Self>, msg: Self::Message) -> bool {
        match msg {
            Msg::SignIn => {
                self.journal.send("App::SignIn".into());
                self.wallet.sign_in().unwrap();
                true
            }
            Msg::SignOut => {
                self.journal.send("App::SignOut".into());
                self.wallet.sign_out().unwrap();
                true
            }
        }
    }

    fn view(&self, ctx: &Context<Self>) -> Html {
        let user = self.wallet.current_user().unwrap();
        let has_user = !user.is_empty();
        html! {
            <BrowserRouter>
                <div class="container">
                    <nav class="navbar navbar-expand-lg navbar-light bg-light">
                        <div class="container-fluid">
                            <a class="navbar-brand" href="https://risczero.com">
                                {"RISC Zero"}
                            </a>
                            <div class="collapse navbar-collapse">
                                <div class="navbar-nav">
                                    <Link<Route> to={Route::Lobby}>
                                        {"Lobby"}
                                    </Link<Route>>
                                </div>
                            </div>
                            <div class="d-flex">
                                if !has_user {
                                    <button
                                        class="button is-primary"
                                        onclick={ctx.link().callback(|_| Msg::SignIn)}>
                                        {"Sign In"}
                                    </button>
                                } else {
                                    <span class="navbar-text col-sm-6">
                                        {"Account: "} {user}
                                    </span>
                                    <button
                                        class="btn btn-primary"
                                        onclick={ctx.link().callback(|_| Msg::SignOut)}>
                                        {"Sign Out"}
                                    </button>
                                }
                            </div>
                        </div>
                    </nav>
                    if has_user {
                        {self.view_main(&self.wallet)}
                    } else {
                        <p>{"Please Sign In to start."}</p>
                    }
                    <hr/>
                    <Journal />
                    <footer class="py-3 my-4 border-top">
                        <p class="text-center text-muted">{"Battleship!"}</p>
                    </footer>
                </div>
            </BrowserRouter>
        }
    }
}

impl App {
    fn view_main(&self, wallet: &Rc<NearWallet>) -> Html {
        let render = Switch::render(move |routes| switch(routes));
        html! {
            <WalletProvider wallet={wallet.clone()}>
                <Switch<Route> {render} />
            </WalletProvider>
        }
    }
}

fn switch(routes: &Route) -> Html {
    match routes.clone() {
        Route::Lobby => html! { <Lobby /> },
        Route::NewGame { name } => html! {
            <GameProvider {name} until={1}>
                <Layout />
            </GameProvider>
        },
        Route::JoinGame { name } => html! {
            <GameProvider {name} until={2}>
                <Layout />
            </GameProvider>
        },
        Route::NotFound => html! { <h1>{ "404" }</h1> },
    }
}

fn main() {
    wasm_logger::init(wasm_logger::Config::default());
    yew::start_app::<App>();
}
