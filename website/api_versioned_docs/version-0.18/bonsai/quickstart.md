# Bonsai Quick Start

_Note: The Bonsai proving service is still in early Alpha; an API key is required for access.
[Click here to request access]._

If you already have an API key, you can start building on Bonsai in any of the following ways:

- via **[cargo risczero]** (great for experimenting or for non-blockchain applications)
  - Enable Bonsai by setting the environment variables `BONSAI_API_KEY=<YOUR_API_KEY>` and `BONSAI_API_URL=<BONSAI_URL>` when running your program
- via the **[Bonsai Foundry Template]** (for accessing Bonsai via Ethereum)
- via the **[Bonsai SDK]** (for accessing Bonsai from Rust)
- via the **[Bonsai REST API]** (for building your own client or accessing Bonsai directly)

If you don't have an API key, you can [request access].
While you wait, you can make use of the local proving option on the Bonsai Foundry Template, or you can focus on developing for the [zkVM].

[Bonsai Foundry Template]: https://github.com/risc0/bonsai-foundry-template/blob/main/README.md
[readme]: https://github.com/risc0/bonsai-foundry-template/blob/main/README.md
[cargo risczero]: https://crates.io/crates/cargo-risczero
[Bonsai SDK]: https://crates.io/crates/bonsai-sdk
[Bonsai REST API]: https://api.bonsai.xyz/swagger-ui/
[Click here to request access]: https://bonsai.xyz/apply
[request access]: https://bonsai.xyz/apply
[zkVM]: ../zkvm
