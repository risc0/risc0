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

use yew::prelude::*;

use crate::near::{NearContract, NearWallet};

#[derive(PartialEq, Clone)]
pub struct WalletContext {
    wallet: Rc<NearWallet>,
    pub contract: Rc<NearContract>,
}

pub struct WalletProvider {
    wallet: Rc<NearWallet>,
    contract: Rc<NearContract>,
}

#[derive(Properties, PartialEq)]
pub struct Props {
    pub wallet: Rc<NearWallet>,
    #[prop_or_default]
    pub children: Children,
}

impl Component for WalletProvider {
    type Message = ();
    type Properties = Props;

    fn create(ctx: &Context<Self>) -> Self {
        let wallet = ctx.props().wallet.clone();
        let contract = Rc::new(wallet.get_contract().unwrap());
        WalletProvider { wallet, contract }
    }

    fn view(&self, ctx: &Context<Self>) -> Html {
        let context = WalletContext {
            wallet: self.wallet.clone(),
            contract: self.contract.clone(),
        };
        html! {
            <ContextProvider<WalletContext> {context}>
                {ctx.props().children.clone()}
            </ContextProvider<WalletContext>>
        }
    }
}
