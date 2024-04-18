# SHA Example

This code demonstrates how to provably compute the SHA-256 hash of a string using RISC Zero.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples

Notable details:

* We show two ways of calling the hash function:
  * Using `risc0_zkvm::sha`, which is the SHA-256 interface included in the `risc0_zkvm` crate.
  * Using a patched version of the [RustCrypto] `sha2` crate. Including this patch will accelerate _all_ usages of SHA-256 that use the `sha2` crate in any transitive dependency.
  * Either approach will use the RISC Zero SHA-256 accelerator in the zkVM guest, which has _much_ higher performance than any software implementation.
* We could have passed the guest a `String` rather than a string literal for the same result.
* Interpreting the output on the host side as a `risc0_zkp::core::sha::Digest` is useful for quality of life. We could also directly read the bytes written in the journal, but then we need to be careful about endianness, printing the bytes (`Digest` implements the `Display` trait), etc.

[RustCrypto]: https://docs.rs/sha2/latest/sha2/

For a video walkthrough of this example, we suggest [this video from Web3Dev - Web in Chains](https://www.youtube.com/watch?v=Nmxe8cnuO-0&list=PLcPzhUaCxlCjHQleuRhYN09zXgj6b_s-e&index=4).
Thanks to Pawel from [Discord](https://discord.gg/risczero) for creating and sharing this content!
Note that the code snippets in this video are based on the 0.14 version of the zkVM, and some APIs shown have changed in more recent versions.
