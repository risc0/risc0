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

To learn more about this use case, check out our Twitter thread about using Bonsai as a [zk coprocessor] or its direct implementation in our [Bonsai Pay Demonstration Application] using Google's Sign-In-with-Google SDK.

[Bonsai application]: https://dev.bonsai.xyz
[zk coprocessor]: https://twitter.com/RiscZero/status/1677316664772132864
[Bonsai Pay Demonstration Application]: https://github.com/risc0/demos/tree/main/bonsai-pay

## Project Organization

zkVM applications consist of a [host program] and a [guest program]. The host program resides in [`src/main.rs`], and the guest program is in [`methods/guest/src/main.rs`]. The foundational JWT issuing/validation library is located in [`core/src/lib.rs`].

The [host] executes the guest program, then proves this execution to generate a [receipt]. This receipt, when presented to a third party, allows them to inspect the [journal] for the program's outputs and verify the receipt, confirming the [guest program]'s execution integrity. In this instance, the JWT's integrity is validated against a public key in the guest, and the decoded token subject is committed to the [journal] for demonstration.

## Approach

This zkVM application showcases how to utilize existing Rust crates and libraries. It employs the [jwt-compact] crate for issuing and validating JWTs using RSA key pairs. This process is encapsulated in a higher-level JWT crate to distinctly demonstrate symmetric key verification.

For more insights into using Rust crates within the zkVM, visit our [Rust Resources] page.

The [guest code] confirms the JWT's integrity using the public key and records the decoded JWT claim subject if successful. Meanwhile, the [host code] is responsible for generating and signing the JWT, including the claim subject string, with the private key.

## More Resources

- For more information about building, running, and testing zkVM applications, see our [developer docs].

[`src/main.rs`]: src/main.rs
[`methods/guest/src/main.rs`]: methods/guest/src/main.rs
[`core/src/lib.rs`]: core/src/lib.rs
[host]: https://dev.risczero.com/terminology#host
[executes]: https://dev.risczero.com/terminology#execute
[guest program]: https://dev.risczero.com/terminology#guest-program
[host program]: https://dev.risczero.com/terminology#host-program
[proves the execution]: https://dev.risczero.com/terminology#prove
[receipt]: https://dev.risczero.com/terminology#receipt
[verify]: https://dev.risczero.com/terminology#verify
[journal]: https://dev.risczero.com/terminology#journal
[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[here]: https://github.com/risc0/risc0/blob/main/examples/chess/src/main.rs#L29
[zkVM]: https://dev.risczero.com/zkvm
[shakmaty]: https://docs.rs/shakmaty/latest/shakmaty/
[Rust Resources]: https://dev.risczero.com/api/zkvm/rust-resources
[guest code]: https://github.com/risc0/risc0-rust-examples/blob/main/chess/methods/guest/src/bin/checkmate.rs
[host code]: https://github.com/risc0/risc0/blob/main/examples/chess/methods/guest/src/main.rs
[journal]: https://dev.risczero.com/terminology#journal
[developer docs]: https://dev.risczero.com
[excerpt from our workshop at ZK HACK III]: https://www.youtube.com/watch?v=vxqxRiTXGBI&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=9
[jwt-compact]: https://github.com/slowli/jwt-compact
