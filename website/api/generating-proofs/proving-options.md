# Options for Proof Generation

Users can choose between:

1. [dev-mode]: No proofs are generated, enabling rapid prototyping.
2. [Local Proving]: Proofs are generated on the user's own hardware.

We recommend dev-mode during development, and local proving for generating real proofs.

:::tip
[`prove_with_opts`] allows users to choose between [composite, succinct or groth16 receipts].
See the [Shrink-Wrapping] page for more details about groth16 receipts.
:::

[`prove_with_opts`]: https://docs.rs/risc0-zkvm/1.0/risc0_zkvm/trait.Prover.html#method.prove_with_opts
[composite, succinct or groth16 receipts]: https://docs.rs/risc0-zkvm/1.0/risc0_zkvm/enum.ReceiptKind.html
[dev-mode]: ./dev-mode.md
[Local Proving]: ./local-proving.md
[Shrink-Wrapping]: ../blockchain-integration/shrink-wrapping.md
