# Local Proving

:::info

The `stark2snark` prover currently _only_ works on x86 architecture, and so Apple Silicon is _currently unsupported_ (even via Docker).

You can find out more info in the relevant issues [here](https://github.com/risc0/risc0/issues/1520) and [here](https://github.com/risc0/risc0/issues/1749).

:::

---

RISC Zero offers a fully [open-source] prover.
Users can run the [zkVM] locally, generating proofs using their own hardware.
The [feature flags] include options to toggle between CPU and GPU proving.

## Local vs. Remote Proving

For most use cases, we recommend remote proving using [Bonsai].
The primary reason to consider using local proof generation for your application is to manage private data.

> Whoever is generating the proofs can see all private information involved.

_With local proof generation, you can generate proofs about your private data, while your private data never leaves your machine._

[Bonsai]: ./remote-proving.md
[open-source]: https://risczero.com/news/open-source
[zkVM]: ../zkvm/zkvm_overview.md
[feature flags]: https://github.com/risc0/risc0#feature-flags
