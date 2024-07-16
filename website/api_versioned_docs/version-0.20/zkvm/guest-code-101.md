# Guest Code 101

In a [zkVM application][zkVM], the [guest code] is the code that will be
executed and proven by the zkVM.

![From Guest Code to Receipt][from-rust-to-receipt]

This page serves as an introduction to writing RISC Zero [guest code], to help
you get started building applications for [Bonsai] and the [zkVM].

- For a guide to writing and running your first guest code, check out our [zkVM
  Quick Start][quickstart].
- For a simple example, check out the [Hello World tutorial][hello-world], where
  the [guest] receives two inputs from the [host] and commits their product to
  the [journal].

The full functionality of the guest is documented in the [`guest`
module][risc0-zkvm-guest] of the [`risc0-zkvm` Rust crate][risc0-zkvm].

## Basic Guest Functionality: Reading, Writing, and Committing

To build a zkVM application, we need our guest program to be able to:

1. read inputs,
2. write private outputs to the [host], and
3. commit public outputs to the [journal].

To support various use cases, there are a number of functions that can be called
from the guest for reading/writing/committing. For a complete list, see the
[`guest` module][risc0-zkvm-guest] documentation; we include a brief list which
should be sufficient for building your first application:

- **Reading inputs** <br/>
  [`env::read`], [`env::read_slice`], and [`env::stdin`]

- **Writing private outputs to [host]**<br/>
  [`env::write`], [`env::write_slice`], [`env::stdout`], [`env::stderr`]

- **Committing public outputs to [journal]**<br/>
  [`env::commit`], [`env::commit_slice`]

## Tools for Debugging & Optimization

There are also a number of functions available to support with debugging and
performance analysis. As above, we refer to the \[`guest` module] for a full
list, but include some highlights here:

- **Count Cycles** <br/>
  [`env::cycle_count`]

- **Print a debug message**<br/>
  [`env::log`]

For more information on optimization & performance, see our pages on
[Cryptography Acceleration][acceleration] and [Benchmarking][benchmarks].

## Boilerplate before `main()`

In our [template] and [examples], there's a bit of boilerplate code before
`main()`. In this section, we explain what each of those lines is doing:

- `#![no_std]` <br/>
  The guest code should be as lightweight as possible for performance reasons.
  So, since we aren't using `std`, we exclude it.

- `#![no_main]` <br/>
  The guest code is never launched as a standalone Rust executable, so we
  specify `#![no_main]`.

- `risc0_zkvm_guest::entry!(main);` <br/>
  We must make the guest code available for the host to launch, and to do that
  we must specify which function to call when the host starts executing this
  guest code. We use the `risc0_zkvm_guest::entry!` macro to indicate the
  initial guest function to call, which in this case is `main`.

## Happy Building!

Hopefully, this guide and the [zkVM Quick Start][quickstart] page will be
sufficient for you to build your first [zkVM application][zkVM]!

If you run into problems, don't be a stranger! You can file an issue on \[these
docs] or the [examples], and we're happy to answer questions on [Discord].

[acceleration]: ./acceleration.md
[benchmarks]: ./benchmarks.md
[Bonsai]: ../bonsai/bonsai-overview.md
[Discord]: https://discord.gg/risczero
[`env::read`]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest/env/fn.read.html
[`env::read_slice`]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest/env/fn.read_slice.html
[`env::stdin`]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest/env/fn.stdin.html
[`env::cycle_count`]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest/env/fn.cycle_count.html
[`env::log`]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest/env/fn.log.html
[`env::write`]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest/env/fn.write.html
[`env::write_slice`]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest/env/fn.write_slice.html
[`env::stdout`]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest/env/fn.stdout.html
[`env::stderr`]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest/env/fn.stderr.html
[`env::commit`]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest/env/fn.commit.html
[`env::commit_slice`]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest/env/fn.commit_slice.html
[examples]: ./examples.md
[from-rust-to-receipt]: /diagrams/from-rust-to-receipt.png
[guest]: /terminology#guest
[guest code]: /terminology#guest
[hello-world]: ./tutorials/hello-world.md
[host]: /terminology#host
[journal]: /terminology#journal
[quickstart]: ./quickstart.md
[risc0-zkvm]: https://docs.rs/risc0-zkvm
[risc0-zkvm-guest]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/guest
[template]: https://github.com/risc0/risc0/tree/release-0.20/templates/rust-starter
[zkVM]: ./zkvm_overview.md
