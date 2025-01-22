# ECDSA Example

This example demonstrates how to verify an ECDSA signature inside the zkVM using secp256r1 signatures.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

## Use Cases

Verifying digital signatures is a primary method of authentication for many protocols, and ECDSA is
a widely deployed cryptographic signature scheme. This example shows how to efficiently verify an
ECDSA signature on curve secp256r1.

Signature verification can be combined with other application logic for powerful results such as
[anonymous group signatures][1], [applying transformations to authenticated data][2], and [fully succinct
transaction ledgers][3].

## Precompile Patch

ECDSA verification is relatively expensive in the zkVM guest. In order to speed this up, the zkVM 
implements a 256-bit big integer multiplication precompile, which targets
the main bottleneck for signature verification. Additionally, RISC Zero implements a patched version
of the `p256` crate which uses this precompile. Using these patches, **ECDSA
signature verification takes about 220k cycles**, down from ~12m cycles.

You can see an example of how to apply these patches in the [`methods/guest/Cargo.toml`][4] file.

For more information on how to use the precompile, see the [precompile documentation][5].

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[RustCrypto]: https://docs.rs/p256/latest/p256/
[1]: https://semaphore.appliedzkp.org/
[2]: https://medium.com/@boneh/using-zk-proofs-to-fight-disinformation-17e7d57fe52f
[3]: https://minaprotocol.com/
[4]: methods/guest/Cargo.toml
[5]: https://dev.risczero.com/api/zkvm/precompiles