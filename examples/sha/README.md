# SHA Example

This code demonstrates how to provably compute the SHA-256 hash of a string using RISC Zero.

Notable details:
* We use `risc0_zkvm::sha` rather than general-purpose SHA code in the zkVM. This is because the RISC Zero zkVM includes SHA-specific accelerator code, and we therefore get _much_ better performance by using the native SHA code.
* We could have passed the guest a `String` rather than a string literal for the same result.
* Interpretting the output on the host side as a `risc0_zkp::core::sha::Digest` is useful for quality of life. We could also directly read the bytes written in the journal, but then we need to be careful about endianness, printing the bytes (`Digest` implements the `Display` trait), etc.

For a video walkthrough of this example, we suggest [this video from Web3Dev - Web in Chains](https://www.youtube.com/watch?v=Nmxe8cnuO-0&list=PLcPzhUaCxlCjHQleuRhYN09zXgj6b_s-e&index=4).
Thanks to Pawel from [Discord](https://discord.gg/risczero) for creating and sharing this content! 
