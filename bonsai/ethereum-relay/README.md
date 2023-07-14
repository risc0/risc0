# Bonsai Relay

## Usage
```console
Usage: bonsai-ethereum-relay [OPTIONS] --contract-address <CONTRACT_ADDRESS> --eth-node-url <ETH_NODE_URL> --wallet-key-identifier <WALLET_KEY_IDENTIFIER>

Options:
  -p, --port <PORT>
          The port of the relay server API [default: 8080]
      --publish-mode
          Toggle to disable the relay server API
      --contract-address <CONTRACT_ADDRESS>
          Bonsai Relay contract address on Ethereum
      --eth-node-url <ETH_NODE_URL>
          Ethereum Node endpoint
      --eth-chain-id <ETH_CHAIN_ID>
          Ethereum chain ID [default: 5]
  -w, --wallet-key-identifier <WALLET_KEY_IDENTIFIER>
          Wallet Key Identifier. Can be a private key as a hex string, or an AWS KMS key identifier [env: WALLET_KEY_IDENTIFIER=]
      --use-kms
          Toggle to use a KMS client
  -h, --help
          Print help
  -V, --version
          Print version
```

## Bonsai Relay SDK
A library to handle HTTP REST requests to the Bonsai Relay interface

### Example Usage
The following example assumes that the Bonsai Relay is up and running with the server API enabled,
and that the memory image of the TRUE ELF is already registered against Bonsai.

```rust
// initialize a relay client
let relay_client = Client::from_parts(
        "http://localhost:8080".to_string(), // here goes the actual url of the Bonsai Relay
        "BONSAI_API_KEY" // here goes the actual Bonsai API-Key
    )
    .expect("Failed to initialize the relay client");

// Initialize the input for the guest.
// Since in this example we are using the True ELF,
// the first 4 bytes need to be the length
// of the slice (in little endian).
let mut input = vec![0; 36];
input[0] = 32;
input[35] = 100;

// Create a CallbackRequest for the Counter contract
// (tests/solidity/contracts/Counter.sol).
let image_id: [u8; 32] = bytemuck::cast(TRUE_ID);
let request = CallbackRequest {
    callback_contract: counter.address(),
    // you can use the command `solc --hashes tests/solidity/contracts/Counter.sol`
    // to get the value for your actual contract
    function_selector: [0xff, 0x58, 0x5c, 0xaf],
    gas_limit: 3000000,
    image_id,
    input,
};

// Send the callback request to the Bonsai Relay.
relay_client
    .callback_request(request)
    .await
    .expect("Callback request failed");

```
