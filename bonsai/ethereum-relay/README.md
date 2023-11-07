# Bonsai Ethereum Relay

This repository provides the `bonsai-ethereum-relay`, a tool to integrate Ethereum with Bonsai.
It is coupled with an Ethereum Smart Contract able to relay the interaction from Ethereum to Bonsai and vice versa.

## Usage

```console
A relayer to integrate Ethereum with Bonsai.

Usage: bonsai-ethereum-relay [OPTIONS] --contract-address <CONTRACT_ADDRESS> --eth-node-url <ETH_NODE_URL> --wallet-key-identifier <WALLET_KEY_IDENTIFIER>

Options:
  -p, --port <PORT>
          The port of the relay REST API [default: 8080]
      --rest-api
          Toggle to disable the relay REST API
      --contract-address <CONTRACT_ADDRESS>
          Bonsai Relay contract address on Ethereum
      --eth-node-url <ETH_NODE_URL>
          Ethereum Node endpoint
      --eth-chain-id <ETH_CHAIN_ID>
          Ethereum chain ID [default: 5]
  -w, --wallet-key-identifier <WALLET_KEY_IDENTIFIER>
          Wallet Key Identifier. Can be a private key as a hex string, or an AWS KMS key identifier [env: WALLET_KEY_IDENTIFIER=]
      --bonsai-api-url <BONSAI_API_URL>
          Bonsai API URL [env: BONSAI_API_URL=http://localhost:8081] [default: http://localhost:8081]
      --bonsai-api-key <BONSAI_API_KEY>
          Bonsai API Key Defaults to empty, providing no authentication [env: BONSAI_API_KEY=none] [default: ]
      --risc0-dev-mode
          Toggle to enable dev_mode: only a local executor runs your zkVM program and no proof is generated [env: RISC0_DEV_MODE=]
  -h, --help
          Print help
  -V, --version
          Print version
```

For additional instructions please refer to our [documentation] and our [Bonsai Foundry template].

[documentation]: https://dev.risczero.com/api/bonsai/bonsai-on-eth
[Bonsai Foundry template]: https://github.com/risc0/bonsai-foundry-template
