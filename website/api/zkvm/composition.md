# Proof Composition

RISC Zero's zkVM is the only zkVM that offers a convenient API for efficiently verifying proofs inside the guest program.

This feature enables rich possibilities for building modular applications. Check out the [blog post] to learn more about the power of proof composition.


## Start Building
To use proof composition in your program, you'll need to call [`add_assumption()`] on the host-side and [`env::verify()`] on the guest-side, as demonstrated in this [code example].

## How it works
Under the hood, proof composition works by *adding assumptions* to the [ReceiptClaim] struct, and then *resolving* those assumptions.

![ReceiptClaim with no assumptions](composition-no-assumptions.png)

### Adding assumptions
When [`env::verify()`] is called inside the guest program, an [assumption] is added to the [ReceiptClaim].
This results in a "conditional receipt."

![Adding an assumption](composition-add-assumption.png)

### Resolve an assumption
In order to finish the process of proof composition, assumptions must be resolved.
This is accomplished via [`resolve()`], which is called automatically when users [`verify()`][TODO - is this right?] a conditional receipt.

![Resolving an assumption](composition-resolve.png)

For a more detailed dive into proof composition and RISC Zero's approach to recursive proving, check out the [Study Club recording].

[`add_assumption()`]: https://github.com/risc0/risc0/blob/v1.0.1/examples/composition/src/main.rs#L29
[assumption]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Assumption.html
[blog post]: https://www.risczero.com/blog/proof-composition
[code example]: https://github.com/risc0/risc0/tree/v1.0.1/examples/composition#readme
[`env::verify()`]: https://github.com/risc0/risc0/blob/v1.0.1/examples/composition/methods/guest/src/main.rs#L24
[`resolve()`]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.ApiClient.html#method.resolve
[ReceiptClaim]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.ReceiptClaim.html
[Study Club recording]: https://www.youtube.com/watch?v=x0-7Y46bQO0&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=1
