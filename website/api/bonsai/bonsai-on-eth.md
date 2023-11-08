# Bonsai on Ethereum

_Warning: Bonsai is still in early development. Do not use in production._

Bonsai can be used as a [zk coprocessor] for Ethereum, allowing you to request [verified proofs] via an off-chain REST API interface or on-chain directly from your smart contract.

At a high level, here's how it works:

![Bonsai ETH Relay overview](/img/bonsai_ethereum.png)

1. Users can delegate their smart contract's logic to Bonsai via a `Request Callback` interface. This interface is accessible both _off-chain_ through the HTTP REST API of the `Bonsai Relayer` and _on-chain_ via the [Bonsai Relay Contract].
2. The `Bonsai Relayer` sends the proof request to Bonsai.
3. Bonsai generates a [Groth16 SNARK proof] and its result, encapsulated in a journal.
4. The `Bonsai Relayer` submits this proof and journal on-chain to the [Bonsai Relay Contract] for validation.
5. If validated, the journal is dispatched to the user's smart contract via the specified callback.

To integrate your application with Bonsai, you'll need to:

1. Write the [program] you want proven and upload it to Bonsai
2. Write the on-chain part of your application and deploy it

## Interfaces

The Bonsai Ethereum Relay provides both an _off-chain_ (vie the HTTP REST API of the `Bonsai Relayer`) and an _on-chain_ (via the [Bonsai Relay Contract]) interface to send `Callback requests`.

### Off-chain

A typical flow works as follows:

1. Deploy the `Bonsai Relay Contract` to Ethereum using address `0xB..`.
2. Launch the `Bonsai Relayer`, setting `--contract-address` to `0xB..`.
3. To delegate off-chain computation for the new Smart Contract `A` to Bonsai, register its `Image` or `ELF` (the binary executing the computation on RISC Zero ZKVM) with Bonsai.
4. Use the generated `Image ID` and the `Bonsai Relay Contract` address 0xB.. to deploy Smart Contract `A` on Ethereum.
5. Initiate a `Callback request` through the `Bonsai Relayer`'s off-chain REST API. This request is sent to Bonsai.
6. After Bonsai produces an execution proof, the `Bonsai Relayer` relays the proof and computation result to the `Bonsai Relay Contract`.
7. Ethereum verifies the proof on-chain. If validated, Smart Contract `A` receives the computation result via the `invoke_callback` function.

#### Example

The following example assumes that the `Bonsai Relayer` is up and running with the server API enabled,
and that the memory image of your `ELF` is already registered against Bonsai with a given `IMAGE_ID` as its identifier.

```rust no_run
# use alloy_primitives::U256;
# use alloy_sol_types::SolValue;
# use anyhow::Context;
# use bonsai_ethereum_relay::sdk::client::{CallbackRequest, Client};
# use clap::Parser;
# use ethers::{types::Address, utils::id};
# use fibonacci_methods::FIBONACCI_ID;
# use risc0_zkvm::sha::Digest;

/// Example code for sending a REST API request to the Bonsai relay service to
/// requests, execution, proving, and on-chain callback for a zkVM guest
/// application.
#[derive(Parser, Debug)]
#[command(author, version, about, long_about)]
struct Args {
    /// Adress for the BonsaiStarter application contract.
    address: Address,

    /// Input N for calculating the Nth Fibonacci number.
    number: u32,

    /// Bonsai Relay API URL.
    #[arg(long, env, default_value = "http://localhost:8080")]
    bonsai_relay_api_url: String,

    /// Bonsai API key. Used by the relay to send requests to the Bonsai proving
    /// service. Defaults to empty, providing no authentication.
    #[arg(long, env, default_value = "")]
    bonsai_api_key: String,
}

#[tokio::main]
async fn main() -> anyhow::Result<()> {
    let args = Args::parse();
    // initialize a relay client
    let relay_client = Client::from_parts(
        args.bonsai_relay_api_url.clone(), // Set BONSAI_API_URL or replace this line.
        args.bonsai_api_key.clone(),       // Set BONSAI_API_KEY or replace this line.
    )
    .context("Failed to initialize the relay client")?;

    // Initialize the input for the FIBONACCI guest.
    let input = U256::from(args.number).abi_encode();

    // Set the function selector of the callback function.
    let function_signature = "storeResult(uint256,uint256)";
    let function_selector = id(function_signature);

    // Create a CallbackRequest for your contract
    // example: (contracts/BonsaiStarter.sol).
    let request = CallbackRequest {
        callback_contract: args.address.into(),
        function_selector,
        gas_limit: 3000000,
        image_id: Digest::from(FIBONACCI_ID).into(),
        input,
    };

    // Send the callback request to the Bonsai Relay.
    relay_client
        .callback_request(request)
        .await
        .context("Callback request failed")?;

    Ok(())
}

```

### On-chain

As an alternative to sending a `Callback request` from the REST API as described by step 5 of the previous section, the request can be sent via the _on-chain_ `Callback request` interface provided by the [Bonsai Relay Contract]:

- Send a transaction to Smart Contract `A` to trigger a `Callback request` event that the Bonsai Relay will catch and forward to Bonsai.

#### Example

Using `cast`:

```bash
cast send --private-key 0x59c6995e998f97a5a0044966f0945389dc9e86dae88c7a8412f4603b6b78690d --gas-limit 100000 "$APP_ADDRESS" 'calculateFibonacci(uint256)' 5
```

where:

- `$APP_ADDRESS` is an env variable containing the address of your Smart Contract `A`
- `calculateFibonacci(uint256)` is the function selector of your Smart Contract `A` triggering the `Callback request`
- `5` is the input for your FIBONACCI program

## Getting Started

The [Bonsai Foundry Template] is the best place to get started building Bonsai applications for Ethereum.
You may also want to check out our [Bonsai Quick Start](quickstart.md) page.

[verified proofs]: https://risczero.com/news/on-chain-verification
[zk coprocessor]: https://twitter.com/RiscZero/status/1677316664772132864
[Bonsai Foundry Template]: https://github.com/risc0/bonsai-foundry-template
[smart contract]: https://github.com/risc0/bonsai-foundry-template/tree/main/contracts
[program]: https://github.com/risc0/bonsai-foundry-template/tree/main/methods/guest/src/bin
[Bonsai Relay Contract]: https://github.com/risc0/risc0/blob/main/bonsai/ethereum/contracts/BonsaiRelay.sol
[Groth16 SNARK proof]: https://www.risczero.com/news/on-chain-verification
