# JSON Web Token Validation

This code provides a minimal example for using RISC Zero's [zkVM] to create zero-knowledge proofs that confirm the integrity of a signed JSON Web Token (JWT). It leverages the [jwt-compact] crate to verify the RS256 JWT signature and claim within the [zkVM].

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

Congratulations! You've successfully constructed a zero-knowledge proof attesting to the validity of an issued JWT, verified against a public key.

## Use Cases

By using this demo as part of a [Bonsai application], you could build an app where an onchain application would like to verify an offchain account.
For example, you might want an identity provider to issue a JWT through a sign-in web-application, whereby a proof of the issued authentication or session token can be used to validate the users connected wallet address and account ownership for later onchain use.

To learn more about this use case, check out our blog post Bonsai as a [zk coprocessor] or its direct implementation in our [Bonsai Pay Demonstration Application] using Google's Sign-In-with-Google SDK.

## Project Organization

zkVM applications consist of a [host program] and a [guest program]. The host program resides in [`src/main.rs`], and the guest program is in [`methods/guest/src/main.rs`]. The foundational JWT issuing/validation library is located in [`core/src/lib.rs`].

The [host] executes the guest program, then proves this execution to generate a [receipt]. This receipt, when presented to a third party, allows them to inspect the [journal] for the program's outputs and verify the receipt, confirming the [guest program]'s execution integrity. In this instance, the JWT's integrity is validated against a public key in the guest, and the decoded token subject is committed to the [journal] for demonstration.

## Approach

This zkVM application showcases how to utilize existing Rust crates and libraries. It employs the [jwt-compact] crate for issuing and validating JWTs using RSA key pairs. This process is encapsulated in a higher-level JWT crate to distinctly demonstrate symmetric key verification.

For more insights into using Rust crates within the zkVM, visit our [Rust Resources] page.

The [guest code] confirms the JWT's integrity using the public key and records the decoded JWT claim subject if successful. Meanwhile, the [host code] is responsible for generating and signing the JWT, including the claim subject string, with the private key.

## More Resources

- For more information about building, running, and testing zkVM applications, see our [developer docs].

[`core/src/lib.rs`]: core/src/lib.rs
[`methods/guest/src/main.rs`]: methods/guest/src/main.rs
[`src/main.rs`]: src/main.rs
[Bonsai application]: https://dev.bonsai.xyz
[Bonsai Pay Demonstration Application]: https://github.com/risc0/demos/tree/main/bonsai-pay
[developer docs]: https://dev.risczero.com
[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[guest code]: https://github.com/risc0/risc0/blob/main/examples/jwt-validator/methods/guest/src/main.rs
[guest program]: https://dev.risczero.com/terminology#guest-program
[host]: https://dev.risczero.com/terminology#host
[host code]: https://github.com/risc0/risc0/blob/main/examples/jwt-validator/src/main.rs
[host program]: https://dev.risczero.com/terminology#host-program
[journal]: https://dev.risczero.com/terminology#journal
[jwt-compact]: https://github.com/slowli/jwt-compact
[receipt]: https://dev.risczero.com/terminology#receipt
[Rust Resources]: https://dev.risczero.com/api/zkvm/rust-resources
[zk coprocessor]: https://www.risczero.com/blog/a-guide-to-zk-coprocessors-for-scalability
[zkVM]: https://dev.risczero.com/zkvm
