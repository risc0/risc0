# Proof Composition

RISC Zero's zkVM offers a convenient API for efficiently verifying proofs inside the guest program.

This feature enables rich possibilities for building modular applications. Check out the [blog post] to learn more about the power of proof composition.

:::info

Although the "obvious" approach to proof composition would be to simply run the verifier inside the guest program, this approach doesn't result in compression.
Instead, RISC Zero's approach to composition relies on _adding_ [assumptions] to the [ReceiptClaim] and then _resolving_ them.

This approach allows us to offer users a simple API for composition while still being able to access the benefits of our hyper-efficient [recursion circuit].

:::

## Start Building

To use proof composition in your program, you'll need to call [`add_assumption()`] on the host-side and [`env::verify()`] on the guest-side, as demonstrated in this [code example].

Assumptions will be automatically resolved when you call [Prover::prove\_with\_opts][Prover::prove_with_opts] using `ReceiptKind::Succinct` or `ReceiptKind::Groth16`.

## How it works

Under the hood, proof composition works by _adding assumptions_ to the [ReceiptClaim] struct, and then _resolving_ those assumptions.

![ReceiptClaim with no assumptions][composition-no-assumptions]

### Adding assumptions

When [`env::verify()`] is called inside the guest program, an [assumption][assumptions] is added to the [ReceiptClaim].
This results in a "conditional receipt."

![Adding an assumption][composition-add-assumption]

### Resolve an assumption

In order to finish the process of proof composition, assumptions must be resolved.
This is accomplished via `resolve`, which is called automatically when users call [Prover::prove\_with\_opts][Prover::prove_with_opts] using `ReceiptKind::Succinct` or `ReceiptKind::Groth16`.

![Resolving an assumption][composition-resolve]

For a more detailed dive into proof composition and RISC Zero's approach to recursive proving, check out the [Study Club recording].

[`add_assumption()`]: https://github.com/risc0/risc0/blob/release-1.0/examples/composition/src/main.rs#L29
[assumptions]: /terminology#assumption
[blog post]: https://www.risczero.com/blog/proof-composition
[code example]: https://github.com/risc0/risc0/tree/release-1.0/examples/composition#readme
[`env::verify()`]: https://github.com/risc0/risc0/blob/release-1.0/examples/composition/methods/guest/src/main.rs#L24
[ReceiptClaim]: https://docs.rs/risc0-zkvm/1.0/risc0_zkvm/struct.ReceiptClaim.html
[Study Club recording]: https://www.youtube.com/watch?v=x0-7Y46bQO0&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=1
[composition-no-assumptions]: /diagrams/composition-no-assumptions.png
[composition-add-assumption]: /diagrams/composition-add-assumption.png
[composition-resolve]: /diagrams/composition-resolve.png
[Prover::prove_with_opts]: https://docs.rs/risc0-zkvm/1.0/risc0_zkvm/trait.Prover.html#method.prove_with_opts
[recursion circuit]: ../recursion.md
