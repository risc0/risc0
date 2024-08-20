# About Reed Solomon Codes

[Reed Solomon codes](https://en.wikipedia.org/wiki/Reed–Solomon_error_correction) (RS codes) are a family of [error correcting codes](https://en.wikipedia.org/wiki/Error_correction_code) based on polynomials over [finite fields](about-finite-fields.md).

## Documentation

Implementation and documentation for Reed-Solomon encoding is in the `risc0-zkp-core` [Rust crate](https://github.com/risc0/risc0#rust-crates).

## Basic Function

A RISC Zero [receipt] demonstrates the validity of the associated [execution trace](../proof-system/what-is-a-trace.md) by encoding the execution instructions and the trace data into polynomials and then making various assertions about those polynomials.
We refer to this process as _arithmetization of the trace_, and RISC Zero's arithmetization is based on Reed Solomon encoding.

## Background

Adding a [parity bit](https://en.wikipedia.org/wiki/Parity_bit) to a binary string offers a form of error detection.
Error correcting codes extend this line of thinking: when sending data that may get corrupted, we can allow the recipient to detect and correct errors by adding some error correcting bits.
Reed-Solomon codes are an industry standard for error correction; they're used in many signal processing applications, including cell communication, QR codes, and [STARKs](about-starks.md).

In the context of RISC Zero's receipts, the relevance of Reed-Solomon codes is quite a bit more nuanced than the standard error correction use cases.
The error amplification of Reed-Solomon encoding provides cryptographic soundness to RISC Zero's computational receipts.
During the process of generating a receipt, any errors in the trace are _amplified_ by the process of arithmetization.
This error amplification means that even a single error in the execution trace can be easily identified.

## Suggested Reading and Videos

- [Slides](https://drive.google.com/file/d/1p0AZ3E4kLIDmFslW_c47YGb-EgeXc_YZ/view), [recording](https://youtu.be/Yu9DHhdSqQo), and [practice problems](https://drive.google.com/file/d/1JtzBGxz1c-PDVIIRmWa85_A22NS9dlL-/view?usp=share_link) from RISC Zero Study Club
- 3blue1brown has two videos that offer a great introduction to error correcting codes: [Part 1](https://www.youtube.com/watch?v=X8jsijhllIA) and [Part 2](https://www.youtube.com/watch?v=b3NxrZOu_CE\&t=0s).
- Mary Wootters has a fantastic course on Algebraic Coding Theory. The [YouTube](https://www.youtube.com/playlist?list=PLkvhuSoxwjI_UudECvFYArvG0cLbFlzSr) and the [course website](https://web.stanford.edu/class/cs250/) are both great resources.
  - [Reed-Solomon Lesson](https://www.youtube.com/watch?v=yQkEnde2lNg\&list=PLkvhuSoxwjI_UudECvFYArvG0cLbFlzSr\&index=16)
- The [Reed-Solomon paper](https://epubs.siam.org/doi/10.1137/0108018) is quite clear and only a few pages long.
- The [Proximity Gaps for Reed-Solomon Codes](https://eprint.iacr.org/2020/654.pdf) paper is central to the soundness of the RISC Zero proof system.
  - See also [Dan Carmon's talk](https://www.youtube.com/watch?v=v0ZHUPzKotY) at the IEEE Symposium on the Foundations of Computer Science

[receipt]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html
