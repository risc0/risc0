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

const GAS = "300000000000000";
const CONTRACT_ID = 'dev-1650384630199-84450568731492';
const NETWORK_ID = 'testnet';

const VIEW_METHODS = [
  'game_state',
  'list_games',
];

const CHANGE_METHODS = [
  'new_game',
  'join_game',
  'turn',
  'clear_games',
  'delete_game',
];

const ALL_METHODS = VIEW_METHODS.concat(CHANGE_METHODS);

export class NearWallet {
  wallet;

  constructor() {
    // connect to NEAR
    const near = new nearApi.Near({
      NETWORK_ID,
      keyStore: new nearApi.keyStores.BrowserLocalStorageKeyStore(),
      nodeUrl: 'https://rpc.testnet.near.org',
      walletUrl: 'https://wallet.testnet.near.org',
    });

    // connect to the NEAR Wallet
    this.wallet = new nearApi.WalletConnection(near);
    console.log(this.wallet);
  }

  cmp(other) {
    return this === other;
  }

  sign_in() {
    this.wallet.requestSignIn({
      contractId: CONTRACT_ID,
      methodNames: ALL_METHODS,
    });
  }

  sign_out() {
    this.wallet.signOut();
  }

  current_user() {
    return this.wallet.getAccountId();
  }

  get_contract() {
    if (!this.wallet.isSignedIn()) {
      throw "Not signed in";
    }

    // connect to a NEAR smart contract
    let contract = new nearApi.Contract(this.wallet.account(), CONTRACT_ID, {
      viewMethods: VIEW_METHODS,
      changeMethods: CHANGE_METHODS,
      sender: this.wallet.getAccountId(),
    });
    return new NearContract(contract);
  }
}

export class NearContract {
  contract;

  constructor(contract) {
    this.contract = contract;
  }

  contract_id() {
    return this.contract.contractId;
  }

  list_games() {
    return this.contract.list_games();
  }

  clear_games() {
    return this.contract.clear_games({}, GAS);
  }

  game_state(name) {
    return this.contract.game_state({ name });
  }

  new_game(name, receipt_str) {
    return this.contract.new_game({ name, receipt_str }, GAS);
  }

  join_game(name, receipt_str, shot_x, shot_y) {
    return this.contract.join_game({ name, receipt_str, shot_x, shot_y }, GAS);
  }

  turn(name, receipt_str, shot_x, shot_y) {
    return this.contract.turn({ name, receipt_str, shot_x, shot_y }, GAS);
  }
}
