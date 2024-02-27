# Bonsai Quick Start

To use Bonsai, you need an API key. If you don't have one, [request access]. Meanwhile, consider using the local proving option on the [Bonsai Foundry Template] or focusing on [zkVM] development.

If you already have an API key, you can start building on Bonsai in any of the following ways:

- via **[cargo risczero]** (great for experimenting or for non-blockchain applications)
  - Enable Bonsai by setting the environment variables `BONSAI_API_KEY=<YOUR_API_KEY>` and `BONSAI_API_URL=<BONSAI_URL>` when running your program
- via the **[Bonsai Foundry Template]** (for accessing Bonsai via Ethereum)
- via the **[Bonsai SDK]** (for accessing Bonsai from Rust)
- via the **[Bonsai REST API]** (for building your own client or accessing Bonsai directly)

[Bonsai Foundry Template]: https://github.com/risc0/bonsai-foundry-template
[cargo risczero]: https://crates.io/crates/cargo-risczero
[Bonsai SDK]: https://crates.io/crates/bonsai-sdk
[Bonsai REST API]: https://api.bonsai.xyz/swagger-ui/
[request access]: https://bonsai.xyz/apply
[zkVM]: ../zkvm/zkvm_overview.md
