# Simple Digital Signature

A simple digital signature scheme built on the RISC Zero platform.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release -- "This is a signed message" --passphrase="passw0rd"
```

## Summary

From [Wikipedia](https://en.wikipedia.org/wiki/Digital_signature):

> A digital signature is a mathematical scheme for verifying the authenticity of
> digital messages or documents. A valid digital signature, where the
> prerequisites are satisfied, gives a recipient very high confidence that the
> message was created by a known sender (authenticity), and that the message was
> not altered in transit (integrity).

This example shows how to build a simple digital signature scheme on the Risc0
platform. In this scheme, the sender possesses a passphrase that they use to
sign messages. Their identity is simply the SHA-256d hash of their passphrase.

In our scheme, we would send the message, the commitment (message and
identity), and the receipt. This allows the recipient to know that we have the
passphrase (authenticity) and used it to sign the message in question
(integrity).

Specifically, the sender uses the zkVM to run `sign(message, passphrase)`. This
returns a data structure that includes the important components: commitment and
receipt. The commitment shows the message and the signer's identity, and the
receipt proves that the identity was computed by taking the SHA-256d of
the signer's passphrase (i.e. not just copied). Thus the signer must possess the
passphrase. Sending those along with the message covers the full scope of a
typical digital signature scheme.

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
