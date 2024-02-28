# Remote Proving using Bonsai

Bonsai lets users generate proofs for their zkVM applications, without using their own hardware for proof generation.
Users specify which zkVM application they want to run, as well as the inputs to that program, and Bonsai returns a proof.

Bonsai is highly parallelized and highly performant: proving work on Bonsai is split among a dynamically-sized GPU cluster, offering ultra-fast proving.
To get a taste of what you can do with Bonsai, check out [Zeth], our [Governance Showcase], [Bonsai Pay], and our twitter thread about using [Bonsai as a zk coprocessor].

If you already have an API key, you can request proofs from Bonsai in any of the following ways:

- via **[cargo risczero]** (great for experimenting or for non-blockchain applications)
  - Enable Bonsai by setting the environment variables `BONSAI_API_KEY=<YOUR_API_KEY>` and `BONSAI_API_URL=<BONSAI_URL>` when running your program
- via the **[Bonsai Foundry Template]** (for accessing Bonsai via Ethereum)
- via the **[Bonsai SDK]** (for accessing Bonsai from Rust)
- via the **[Bonsai REST API]** (for building your own client or accessing Bonsai directly)

If you don't have an API key, you can [request access].
While you wait, you can make use of the local proving option on the Bonsai Foundry Template, or you can focus on developing for the [zkVM].

[litepaper]: /litepaper
[request access]: https://bonsai.xyz/apply
[Bonsai SDK]: https://crates.io/crates/bonsai-sdk
[Bonsai REST API]: https://api.bonsai.xyz/swagger-ui/
[Bonsai as a zk coprocessor]: https://twitter.com/RiscZero/status/1677316664772132864
[Governance Showcase]: https://github.com/risc0/risc0/tree/main/bonsai/examples/governance#readme
[Zeth]: https://www.risczero.com/news/zeth-release
[guest program]: /terminology#guest-program
[receipt]: /terminology#receipt
[journal]: /terminology#journal
[Bonsai Pay]: https://www.risczero.com/news/bonsai-pay
[Bonsai Foundry Template]: https://github.com/risc0/bonsai-foundry-template/blob/main/README.md
[cargo risczero]: https://crates.io/crates/cargo-risczero
[zkVM]: ../zkvm/zkvm_overview.md
