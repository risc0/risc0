# Remote Proving using Bonsai

Bonsai lets users generate proofs for their zkVM applications, without using their own hardware for proof generation.
Users specify which zkVM application they want to run, as well as the inputs to that program, and Bonsai returns a proof.

Bonsai is highly parallelized and highly performant: proving work on Bonsai is split among a dynamically-sized GPU cluster, offering ultra-fast proving.
To get a taste of what you can do with Bonsai, check out [Zeth][external-zeth], our [Governance Showcase][external-governance-showcase], [Bonsai Pay][external-bonsai-pay], and our blog post about using [Bonsai as a zk coprocessor][external-zkcoprocessor].

If you already have an API key, you can request proofs from Bonsai in any of the following ways:

- via **[cargo risczero][external-cargo-risczero]** (great for experimenting or for non-blockchain applications)
  - Enable Bonsai by setting the environment variables `BONSAI_API_KEY=<YOUR_API_KEY>` and `BONSAI_API_URL=<BONSAI_URL>` when running your program
- via the **[Bonsai Foundry Template][external-foundry-template]** (for accessing Bonsai via Ethereum)
- via the **[Bonsai SDK][external-bonsai-sdk]** (for accessing Bonsai from Rust)
- via the **[Bonsai REST API][external-bonsai-rest-api]** (for building your own client or accessing Bonsai directly)

If you don't have an API key, you can [request access][external-bonsai-apply].
While you wait, you can make use of the local proving option on the [Bonsai Foundry Template][external-foundry-template], or you can focus on developing for the [zkVM][docs-zkvm].

## API Limits

Bonsai enforces a number of API limits. These limits are configurable on a per API key basis. If your limits are too low to support your use case or you run out cycles, email us at [`devrel@risczero.com`][email-devrel] to request more.

These limits are:

- **Concurrent proofs**: The max number of proofs you can generate simultaneously.
- **Cycle budget**: The max number of [cycles][term-cycles] you can prove on Bonsai.
- **Cycle usage**: The historical count of cycles used by your API key.
- **Executor cycle limit**: The max number of cycles your API key can prove for an individual proof.
- **Max parallelism**: The maximum number of workers an individual proof can be parallelized across (this limit is currently inactive).

### Checking your limits

You can request your individual limits using the [user/quotas][external-api-user-quotas] API route.

### Understanding cycle counts

You can log the cycle count and other performance info for your zkVM Guest program by following the instructions [here][docs-executor-statistics].

[docs-executor-statistics]: ../zkvm/quickstart.md#executor-statistics
[docs-zkVM]: ../zkvm/zkvm_overview.md
[email-devrel]: mailto:devrel@risczero.com
[external-api-user-quotas]: https://api.bonsai.xyz/swagger-ui/#/user/route_user_quota
[external-bonsai-apply]: https://bonsai.xyz/apply
[external-bonsai-pay]: https://www.risczero.com/news/bonsai-pay
[external-bonsai-rest-api]: https://api.bonsai.xyz/swagger-ui/
[external-bonsai-sdk]: https://crates.io/crates/bonsai-sdk
[external-cargo-risczero]: https://crates.io/crates/cargo-risczero
[external-foundry-template]: https://github.com/risc0/bonsai-foundry-template/blob/main/README.md
[external-governance-showcase]: https://github.com/risc0/risc0/tree/release-0.21/bonsai/examples/governance#readme
[external-zeth]: https://www.risczero.com/news/zeth-release
[external-zkcoprocessor]: https://www.risczero.com/news/a-guide-to-zk-coprocessors-for-scalability
[term-cycles]: /terminology#clock-cycles
