# Digital signatures on Risc0

A simple digital signature scheme built on the Risc0 platform.

## Overview

A *digital signature* is a mathematical scheme for verifying the authenticity of a digital message. A typical digital signature consists of a *message*, the sender's *identity*, and some additional data that proves (1) the message came from the sender and (2) the message has not been altered in transit.

This example shows how to build a simple digital signature scheme on the Risc0 platform. In this scheme, the sender possesses a *passphrase* which they use to sign messages. Their *identity* is simply the SHA-256 hash of their passphrase.

To sign a message `m`, the sender uses the ZKVM to run `sign(passphrase, m)`, which simply returns `(SHA256(passphrase), m)`. Since execution takes place within the Risc0 platform, the ZKVM also produces a *receipt* that can be used to check the signature.

## Running the tests

Using [Bazelisk](https://github.com/bazelbuild/bazelisk), simply run

```console
$ RISC0_LOG=1 bazelisk run //examples/rust/digital_signature:test
...
[2022-03-29T22:41:01Z INFO  test::tests] msg: Message { msg: 12648430 }
[2022-03-29T22:41:01Z INFO  test::tests] commit: Ok(SignMessageCommit { identity: 9552bd3d48a275d93f301efc4dcc70dd03f9ab1f6af721f6aa3a7f6feb0d64e1, msg: Message { msg: 12648430 } })
...
`
