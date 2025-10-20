# Remote Proving

## Bonsai

Bonsai lets users generate proofs for their zkVM applications, without using their own hardware for proof generation.
Users specify which zkVM application they want to run, as well as the inputs to that program, and Bonsai returns a proof.

Bonsai is highly parallelized and highly performant: proving work on Bonsai is split among a dynamically-sized GPU cluster, offering ultra-fast proving.
To get a taste of what you can do with Bonsai, check out [Zeth][external-zeth] and our blog post about using [RISC Zero as a zk coprocessor with Bonsai proving][external-zkcoprocessor].

If you already have an API key, you can request proofs from Bonsai in any of the following ways:

- Set the environment variables `BONSAI_API_KEY=<YOUR_API_KEY>` and `BONSAI_API_URL=<BONSAI_URL>`. <br />
  When using [`default_prover()`][external-default-prover-fn] in your [host code][docs-host-code], setting these variables will automatically send your proving jobs to Bonsai.
- via the **[Bonsai SDK][external-bonsai-sdk]** (for accessing Bonsai from Rust)
- via the **[Bonsai REST API][external-bonsai-rest-api]** (for building your own client or accessing Bonsai directly)

If you don't have an API key, you can [request access][external-bonsai-apply].
While you wait, you can make use of the [local proving][docs-local-proving] option, or you can focus on developing for the [zkVM][docs-zkvm].

### API Limits

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

You can log the cycle count and other performance info for your zkVM Guest program by following [these instructions][docs-executor-statistics].

## Boundless

Boundless is a decentralized proving marketplace which lets users generate proofs for their zkVM applications, without using their own hardware for proof generation. At a high level, users request proofs to the Boundless protocol and permissionless provers generate proofs on behalf of the user. In each proof request, users specify which zkVM application they want to run, as well as inputs to that program, and Boundless returns a proof.

Boundless is highly decentralized, offering high reliability and reducing the impact of any single entity on proof generation and delivery. To get a taste of what you can do with Boundless, check out the [Boundless Docs][external-boundless-docs], specifically the [Quick Start][external-boundless-quick-start] and the [Request a Proof Tutorial][external-boundless-request-tutorial].

[docs-executor-statistics]: ../zkvm/quickstart.md#executor-statistics
[docs-host-code]: ../zkvm/host-code-101.md#a-very-simple-host
[docs-local-proving]: ../generating-proofs/local-proving.md
[docs-zkVM]: ../zkvm/zkvm-overview.md
[email-devrel]: mailto:devrel@risczero.com
[external-api-user-quotas]: https://api.bonsai.xyz/swagger-ui#/user/route_user_quota
[external-bonsai-apply]: https://bonsai.xyz/apply
[external-bonsai-rest-api]: https://api.bonsai.xyz/swagger-ui
[external-bonsai-sdk]: https://crates.io/crates/bonsai-sdk
[external-boundless-docs]: https://docs.beboundless.xyz/
[external-boundless-quick-start]: https://docs.beboundless.xyz/developers/quick-start
[external-boundless-request-tutorial]: https://docs.beboundless.xyz/developers/tutorials/request
[external-default-prover-fn]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/fn.default_prover.html
[external-zeth]: https://www.risczero.com/blog/zeth-release
[external-zkcoprocessor]: https://www.risczero.com/blog/a-guide-to-zk-coprocessors-for-scalability
[term-cycles]: /terminology#clock-cycles
