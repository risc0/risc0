# Introduction to Input/Output in the zkVM

This document provides an overview of how to perform I/O operations in the zkVM,
going over the different file descriptors and methods used to handle inputs and
outputs, the distinction between public and private data and additional
considerations when working with I/O in the zkVM.

As briefly mentioned in [Guest Code 101][guest-code-101-io], we can perform I/O
between the [guest] and [host] by using some methods under the [`env`
module][env-module-functions]. These methods allow sending private data between
them. In the zkVM, there is a distinction between public and private data.
Public data is included in the journal and is part of the proof, while private
data is sent between the guest and host and is not included in the journal nor
consists in part of the proof.

## Public and Private Data

We draw a distinction between public and private data in the zkVM. Whereas
public data is included in the journal and becomes part of the proof, private
data is only accessible by the host and guest. It's important to understand this
distinction in order to handle data correctly and ensure that sensitive
information is not publicly disclosed.

Public data comprises everything that is included in the
[journal][journal_terminology] as a result of a zkVM application's execution.
Since this data is the _output_ of the application, public data is often also
referred to as _public outputs_.

On the other hand, private data is everything that is not included in the proof.
In other words, private data is only accessible by the host and guest. This kind
of data can be both in the form of _inputs_ from the host to the guest and
_outputs_ from the guest to the host.

While private data is not included in the proof, it is still important to take
into consideration that it _is_ included in the [session], and therefore any
party that has access to it will also have access to the private data.

## File Descriptors and I/O

In the zkVM, private I/O happens through file descriptors. A file descriptor is
a unique identifier that represents an open file or input/output resource in a
computer program. It serves as an abstract representation of a file or device,
enabling the program to read from or write to it. To perform input and output
operations in the zkVM, we need to specify the file descriptors to work as the
input and output. This allows the program to read input data from a specific
source and write output data to a specific destination. By specifying the file
descriptors, the program can establish connections with the desired input/output
resources and perform the necessary operations.

By default, the zkVM provides four file descriptors for I/O operations:

- [`stdin`][stdin]: The standard input file descriptor. It is used to read input
  data from the host to the guest.
- [`stdout`][stdout]: The standard output file descriptor. It is used to write output
  data from the guest to the host.
- [`stderr`][stderr]: The standard error file descriptor. It is used to write error from the guest to the host.
- [`journal`][journal]: The journal file descriptor. It is used to write public
  data.

For the [`stdin`][stdin], [`stdout`][stdout], and [`journal`][journal] file
descriptors, there are some helper methods to read and write data, that we'll
cover in the next sections.

:::info
It's important to highlight that from those file descriptors, only the [`journal`][journal] has a public nature. All the other file descriptors are private and will not be part of the proof.
:::

## Handling Inputs

The [`stdin`][stdin] file descriptor is used to send input data from the host to
the guest. The zkVM provides some convenience methods to read data from this
file descriptor.

- [`env::read`][read_method]: Reads a value from the `stdin` file descriptor.
- [`env::read_slice`][read_slice_method]: Reads a slice from the `stdin` file
  descriptor.

For example, in the host program, we could:

`/src/main.rs`

```rust,no_run
use risc0_zkvm::ExecutorEnv;

fn main() {
  let env = ExecutorEnv::builder()
              // Write a single value to [stdin]
              .write(&42u64)
              .unwrap()
              // Write a slice to [stdin]
              .write_slice(&[1u8, 2u8, 3u8])
              .build()
              .unwrap();

  // Do something with the ExecutorEnv...
}
```

And in the guest program, we could:

`/methods/guest/src/main.rs`

```rust,no_run
#![no_main]
use risc0_zkvm::guest::env;
risc0_zkvm::guest::entry!(main);

fn main() {
  // Read a single value from the standard input
  let input = env::read::<u64>();

  // Read a slice from the standard input
  let mut buffer = [0u8; 3];
  env::read_slice(&mut buffer);

  // Ensure we read the expected input
  assert_eq!(input, 42);
  assert_eq!(buffer, [1u8, 2u8, 3u8]);

  // Do something with the input data...
}
```

## Handling Private Outputs

The [`stdout`][stdout] file descriptor is used to send private output from the
guest to the host. The zkVM provides some convenience methods to write data to
this file descriptor.

- [`env::write`][write_method]: Writes a value to the `stdout` file descriptor.
- [`env::write_slice`][write_slice_method]: Writes a slice to the `stdout` file
  descriptor.

Differently from the [`stdin`][stdin] file descriptor, in the [`stdout`][stdout]
we need to provide a buffer to write the data to.

The basic flow is that we need to instantiate a buffer in the host program, and
then pass it to the guest program. The guest program will write the output to
the [`stdout`][stdout] file descriptor, and the host program will read the
output from the buffer.

For example, in the host program, we could:

`/src/main.rs`

```rust,ignore
use risc0_zkvm::{
  ExecutorEnv,
  Receipt,
  default_prover,   // convenience method to create a default prover
  serde::from_slice // necessary to deserialize the output
};

use app::{ExampleStruct, EXAMPLE_ELF};

fn main() {
  // Step 1: Create a buffer to store the output
  let mut output: Vec<u8> = Vec::new();
  let env = ExecutorEnv::builder()
              // Step 2: Instruct the guest to write to the desired buffer
              .stdout(&mut output)
              .build()
              .unwrap();
  let prover = default_prover();
  let receipt = prover.prove(env, EXAMPLE_ELF).unwrap();

  // Step 3: Deserialize the output
  let example_struct: ExampleStruct = from_slice(&output).unwrap();
  let example_slice: [u8; 3] = from_slice(&output).unwrap();

  // Do something with the output...
}
```

And in the guest program, we could:

`/methods/guest/src/main.rs`

```rust,ignore
#![no_main]
use risc0_zkvm::guest::env;
risc0_zkvm::guest::entry!(main);
use app::ExampleStruct;

fn main() {
  // Write a single value to [stdout]
  env::write(ExampleStruct {
    field1: 42,
    field2: "Hello, World!".to_string()
  });

  // Write a slice to [stdout]
  env::write_slice(&[1u8, 2u8, 3u8]);

  // Do more things...
}
```

## Handling Public Outputs

The [`journal`][journal] file descriptor is used to send public output. This
will be part of the proof and will be included in the journal. The zkVM provides
some convenience methods to write data to this file descriptor.

- [`env::commit`][commit_method]: Writes a value to the `journal` file descriptor.
- [`env::commit_slice`][commit_method]: Writes a slice to the `journal` file descriptor.

Differently from the [`stdout`][stdout] file descriptor, in the
[`journal`][journal] we just need to provide the data to be written, no buffer
is necessary.

For example, in the host program, we could instantiate the `ExecutorEnv` as usual, and then get the journal data from the receipt.

`/src/main.rs`

```rust,ignore
use risc0_zkvm::{default_prover, ExecutorEnv};

fn main() {
  let env = ExecutorEnv::builder()
              .build()
              .unwrap();
  let prover = default_prover();
  let receipt = prover.prove(env, EXAMPLE_ELF).unwrap();

  // Get the journal data from the receipt
  let journal = receipt.journal;

  // Do something with the journal data...
}
```

And in the guest program, we would write to the journal as follows:

`/methods/guest/src/main.rs`

```rust,no_run
#![no_main]

use risc0_zkvm::guest::env;
risc0_zkvm::guest::entry!(main);

fn main() {
  // Commit single value to the journal
  env::commit(&42u64);

  // Commit a slice to the journal
  env::commit_slice(&[1u8, 2u8, 3u8]);

  // Do more things...
}
```

## Best Practices

TODO: Mention the architecture of having a `core` crate that would share data structures and functions between the host and guest, and how to handle I/O in this context.

TODO: Give concrete examples of how to handle I/O in a zkVM application by pointing to existing example applications in `risc0/examples`

## Further examples

For further examples on how to handle I/O in the zkVM, you can check the [examples page].

[guest-code-101-io]: guest-code-101.md#basic-guest-functionality-reading-writing-and-committing
[env-module-functions]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/index.html#functions
[stdin]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.stdin.html
[stdout]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.stdout.html
[stderr]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.stderr.html
[journal]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.journal.html
[read_method]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.read.html
[read_slice_method]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.read_slice.html
[write_method]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.write.html
[write_slice_method]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.write_slice.html
[commit_method]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit.html
[journal_terminology]: https://dev.risczero.com/terminology#journal
[session]: https://dev.risczero.com/terminology#session
[examples page]: examples.md
[guest]: https://dev.risczero.com/terminology#guest
[host]: https://dev.risczero.com/terminology#host
