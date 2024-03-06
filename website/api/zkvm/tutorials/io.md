 ```rust no_run
 use bytemuck::{Pod, Zeroable};
 use risc0_zkvm::guest::env;

 const CANVAS_SIZE: usize = 10_000;

 #[repr(C)]
 #[derive(Copy, Clone)]
 #[derive(Pod, Zeroable)]
 struct Rgba {
   red: u8,
   green: u8,
   blue: u8,
   alpha: u8,
 }

 #[repr(C)]
 #[derive(Copy, Clone)]
 #[derive(Pod, Zeroable)]
 struct Pixel {
   x: u32,
   y: u32,
   color: Rgba,
 }

 #[repr(C)]
 #[derive(Copy, Clone)]
 #[derive(Pod, Zeroable)]
 struct Canvas<CanvasSize: usize> {
   width: u32,
   height: u32,
   pixels: [Pixel; CanvasSize],
 }

 let rgba = Rgba { red: 0, green: 128, blue: 255, alpha: 42 };
 let pixel = Pixel { x: 0, y: 0, color: rgba };
 let canvas = Canvas { width: 100, height: 100, pixels: [pixel; CANVAS_SIZE] };
 env::commit_slice(&[canvas]);
 ```

In the zkVM, a good pattern to follow on how to handle shared data
structures between host and guest is to have a common `core` module that
contains the shared data structures. The host and guest can then use the
same data structures to communicate with each other.

```rust no_run title="core/src/lib.rs"
# pub mod app_core {
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
pub struct Input {
    a: u32,
    b: u32,
}
# }
```

In the host, add the input data to the environment.
See also [write][source-env::write]

```rust no_run title="src/main.rs"
# use serde::{Serialize, Deserialize};
# #[derive(Serialize, Deserialize)]
# pub struct Input { a: u32, b: u32 }
use risc0_zkvm::ExecutorEnv;
// use app_core::Input;

let input1 = Input{ a: 1, b: 2 };
let input2 = Input{ a: 3, b: 4 };
let env = ExecutorEnv::builder()
    .write(&input1).unwrap()
    .write(&input2).unwrap()
    .build()
    .unwrap();
```

```rust no_run title="methods/guest/src/main.rs"
use std::collections::{BTreeMap, LinkedList};

let input: Result<BTreeMap<u64, bool>> = read();
```

:::tip
In this guide we'll first discuss the technical details about I/O and the
reasoning behind it. If you're in a rush and just want to see some code, you can
jump to the section [Putting it all together].
:::

# Understanding I/O in the zkVM

In the [Hello World Tutorial][docs-hello-world], we had a brief introduction to
how to perform I/O operations in the zkVM. Now we'll dive deeper into the subject.
By following the steps in this guide, you will learn:

- What are the different types of data in the zkVM
- How to handle inputs and outputs
- Best practices for handling I/O in the zkVM

## Setting the Stage

We can think of programming in the zkVM as transitioning between two worlds; The
[host], where computation works the same as in any other regular program, and
the [guest], where computation is done in a zero-knowledge environment.

Since the guest works in a zk environment, it has access to a limited set of
ways to get data if compared to the host.
The only way to send data between the host and guest is through the
[Executor Environment][source-executor-env].
Such data transfer is done through file descriptors.
The zkVM specify four default file descriptors, [`stdin`][stdin],
[`stdout`][stdout], [`stderr`][stderr], and [`journal`][journal];
They're defined in the [fileno][source-fileno] module.

## The zkVM Data Model

The zkVM has a data model that distinguishes between public and private data.
By _"public"_ we mean data that is included in the [journal][term-journal] and
becomes part of the proof, while _"private"_ data is only accessible by the host
and guest.

If your application handles sensitive data, it's important to be aware of
specifically which data is [`commit`][source-env::commit]ed to the journal, avoiding
any sensitive data to be included in the proof.

## Sending data from the host to the guest

The [`stdin`][stdin] file descriptor is used to send input data from the host to
the guest.
In the host, it's possible to set the input data in the [Executor Environment][source-executor-env] through the methods [`write`][source-ExecutorEnvBuilder::write] and [`write_slice`][source-ExecutorEnvBuilder::write_slice].
The guest has corresponding functions [`read`][source-env::read] and [`read_slice`][source-env::read_slice] to read the input data.

Since we mentioned the `read`/`write` methods and their `_slice` variants, it's
important to take some time to understand why the zkVM provides both options.

## A note on performance

During the process of sending data from host to guest and vice-versa, we can
either do so while (de)serializing the data or by sending raw bytes.
It's a trade-off between convenience and performance.
By using the standard functions [`read`][source-env::read],
[`write`][source-env::write] and [`commit`][source-env::commit] (that we'll
cover in the next section), the zkVM performs automatic (de)serialization of the
data.
This enables easy handling of complex data structures, but it comes with a performance cost.
Using the `_slice` variants, on the other hand, allows for sending raw bytes,
which is faster but usually requires less ergonomic code.

It is good practice to use the standard functions first, switching to the
`_slice` variants when performance becomes an issue or when optimizing the code
to save on [cycles][term-cycles].
Since both approaches can be used concomitantly, moving from one to another
shouldn't be a problem.
We have a [more detailed explanation][docs-guest-code-optmization] on guest code
optimization if you want to learn more about this topic.

## Sending _Private_ data from the guest to the host

Back where we were, after getting data from the host and performing some
transformations on it, we might want to send _private_ data back.
Both [`stdout`][stdout] and [`stderr`][stderr] file descriptor are used to send
data from the guest to the host in a _private_ manner.

On the host side, it's possible to read data coming from the guest by reading
the buffer that was originally passed to the [Executor
Environment][source-executor-env] through its methods
[`stdout`][source-ExecutorEnvBuilder::stdout] and
[`stderr`][source-ExecutorEnvBuilder::stderr].

:::info
The _private_ data alluded to here is not included in the proof, but it _**is**_
accessible to the host.
This means that the party performing the proving can access the data, so if
there is sensitive information during the proving process, it's important to be
aware of this.
If you don't want to let private data leak to any other party, it's possible to
achieve full secrecy by doing the proving locally.
:::

:::tip
A good practice to handle sensitive data is to use [proof
composition][article-composition];
Essentially splitting the proving process into smaller parts, proving the
sensitive data locally and combining the larger program later through
composition in a capable proving service like [Bonsai][docs-remote-proving] to
speed up the proof generation.
:::

## Sending _Public_ data from the guest

We saw how to send _private_ data directly to the host, but we might also want
to [`commit`][source-env::commit] _public_ data, attesting to some fact that we
want to share with the world.
We can do so by sending this data to the [`journal`][journal] file descriptor.
This data will be included in the proof and can be accessed by any party through
the [`Receipt`][source-Receipt] after the proving process.
Writing to the journal is done through the methods
[`commit`][source-env::commit] and [`commit_slice`][source-env::commit_slice].

On the host side, (or any other regular program that has access to the
[`Receipt`][source-Receipt]), reading from the journal can be achieved by simply
calling the [`Journal`][source-Journal]'s method
[`decode`][source-Journal::decode].

## Putting it all together

Enough theory, let's see how to handle I/O in the zkVM by putting it all in an example.
Let's say we have a simple program that

## Best Practices

TODO: Mention the architecture of having a `core` crate that would share data structures and functions between the host and guest, and how to handle I/O in this context.

TODO: Give concrete examples of how to handle I/O in a zkVM application by pointing to existing example applications in `risc0/examples`

## Further examples

For further examples on how to handle I/O in the zkVM, you can check the [examples page].

[Putting it all together]: #putting-it-all-together
[guest-code-101-io]: ../guest-code-101.md#basic-guest-functionality-reading-writing-and-committing
[env-module-functions]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/index.html#functions
[stdin]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.stdin.html
[stdout]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.stdout.html
[stderr]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.stderr.html
[journal]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.journal.html
[source-env::read]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.read.html
[source-env::read_slice]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.read_slice.html
[source-env::write]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.write.html
[source-ExecutorEnvBuilder::write]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ExecutorEnvBuilder.html#method.write
[source-ExecutorEnvBuilder::stdout]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ExecutorEnvBuilder.html#method.stdout
[source-ExecutorEnvBuilder::stderr]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ExecutorEnvBuilder.html#method.stderr
[source-ExecutorEnvBuilder::write_slice]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ExecutorEnvBuilder.html#method.write_slice
[write_slice_method]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.write_slice.html
[source-env::commit]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit.html
[source-env::commit_slice]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit_slice.html
[term-journal]: https://dev.risczero.com/terminology#journal
[term-cycles]: https://dev.risczero.com/terminology#clock-cycles
[session]: https://dev.risczero.com/terminology#session
[examples page]: ../examples.md
[docs-hello-world]: ./hello-world.md
[docs-remote-proving]: ../../generating-proofs/remote-proving.md
[docs-guest-code-optmization]: ../optimization.md#when-reading-data-as-raw-bytes-use-envread_slice
[article-composition]: https://www.risczero.com/blog/proof-composition
[source-executor-env]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ExecutorEnv.html
[source-receipt]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html
[source-fileno]: https://docs.rs/risc0-zkvm-platform/*/risc0_zkvm_platform/fileno/index.html
[source-Journal]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Journal.html
[source-Journal::decode]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Journal.html#method.decode
[guest]: https://dev.risczero.com/terminology#guest
[host]: https://dev.risczero.com/terminology#host
