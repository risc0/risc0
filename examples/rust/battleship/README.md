# Battleship (Rust)
*This README includes instructions to install and play RISC Zero Battleship on your own machine. For more information about RISC Zero Battleship, check out the tutorials at [www.risczero.com](http://www.risczero.com). For questions, find us on [Discord](https://discord.gg/risczero).*

`RISC Zero Battleship` is a 2-player hidden information game implemented in Rust on the NEAR Network. 

Players produce proofs of game-state and the result of their actions to enable
two players to play fairly with no intermediaries.

## Components

* Web UI (client)
* Prover web service
* NEAR smart contract

## Requirements

### Yew

Follow the instructions for [Yew Project Setup](https://yew.rs/docs/getting-started/introduction).

### NEAR

Install the `near-cli`:
```
npm install -g near-cli
```

Create a NEAR account: https://wallet.testnet.near.org/create

## Running

Deploy the NEAR smart contract (optional):
```
cd examples/rust/battleship/contract
cargo build --target wasm32-unknown-unknown --release
near dev-deploy target/wasm32-unknown-unknown/release/battleship_contract.wasm
```

NOTE: If you deploy your own smart contract, you'll need to update the code to point to this new contract.

See: https://github.com/risc0/risc0/blob/main/examples/rust/battleship/web/client/near.js#L16

Launch the web service:
```
bazelisk run //examples/rust/battleship/web/server
```

Launch the web client:
```
trunk serve --open -- examples/rust/battleship/web/client/index.html
```

## Unit tests

```
RISC0_LOG=1 bazelisk run //examples/rust/battleship:test
cargo test
```
