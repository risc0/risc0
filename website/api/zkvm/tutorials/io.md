# Understanding I/O in the zkVM

In the [Hello World Tutorial][docs-hello-world], we had a brief introduction to
how to perform I/O operations in the zkVM. Now we'll dive deeper into the subject.
Keep reading to learn more about:

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
In the host, it's possible to set the input data in the [Executor
Environment][source-executor-env] through the methods
[`write`][source-ExecutorEnvBuilder::write] and
[`write_slice`][source-ExecutorEnvBuilder::write_slice].
The guest has corresponding functions [`read`][source-env::read] and
[`read_slice`][source-env::read_slice] to read the input data.

Writing to the guest's stdin can be done as simply as the code below.
For a real example, check the [Voting Machine's example][example-voting-machine-host-init-write].

```rust no_run title="src/main.rs"
use risc0_zkvm::ExecutorEnv;

let input = "Hello, guest!";
let env = ExecutorEnv::builder().write(&input)?.build()?;
# Ok::<(), anyhow::Error>(())
```

Since we mentioned the `read`/`write` methods and their `_slice` variants, let's
take a moment to understand the difference between them.

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

## Sending _Private_ data from the guest

Back where we were, after getting data from the host and performing some
transformations on it, we might want to send _private_ data back.
Both [`stdout`][stdout] and [`stderr`][stderr] file descriptor are used to send
data from the guest to the host in a _private_ manner, and a convenient way to
send data to the host's [`stdout`][stdout] is by using the
[`write`][source-env::write] method.

Writing to the host's stdout can be done as simply as the code below.
For a real example, check the [Voting Machine's example][example-voting-machine-guest-elf-submit-write].

```rust no_run title="methods/guest/src/main.rs"
# use risc0_zkvm::guest::env;
let data = "Hello, host!";
env::write(&data);
```

On the host side, it's possible to read data coming from the guest by reading
the buffer that was originally passed to the [Executor
Environment][source-executor-env] through its methods
[`stdout`][source-ExecutorEnvBuilder::stdout] and
[`stderr`][source-ExecutorEnvBuilder::stderr].

:::info
The _private_ data alluded to here is not included in the proof, but it _**is**_
accessible to the host.
This means that the party generating the proof can access the data, so you
should take this into consideration.
If you don't want to let private data leak to any other party, it's possible to
achieve full secrecy by proving locally.
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

Writing to the journal can be done as simply as the code below.
For a real example, check the [Voting Machine's example][example-voting-machine-guest-elf-submit-commit].

```rust ignore title="src/main.rs"
let data = "Hello, journal!";
env::commit(&data);
```

On the host side, (or any other regular program that has access to the
[`Receipt`][source-Receipt]), reading from the journal can be achieved by simply
calling the [`Journal`][source-Journal]'s method
[`decode`][source-Journal::decode].

## Reading _Private_ data in the host

Once we sent data from the guest, we can read it back in the host by leveraging
the [`from_slice`][source-from_slice] method. This method is used to deserialize
the data from a buffer into the desired type.

Reading from the host's stdout can be done as simply as the code below.
For a real example, check the [Voting Machine's example][example-voting-machine-host-submit-output-from_slice].

```rust ignore title="src/main.rs"
let result: Type = from_slice(&output)?;
```

If data was sent in its raw form by using a `_slice` variant, you'll need to
handle the bit fiddling manually.

## Reading _Public_ data in the host

Reading _public_ data is done by accessing the [`Journal`][source-Journal] that
is contained in the resulting [`Receipt`][source-Receipt] after the proving
process.
This can be done by calling the [`decode`][source-Journal::decode] method on the
journal instance.

```rust ignore title="src/main.rs"
// Produce a receipt by proving the specified ELF binary.
let receipt = prover.prove(env, ELF).unwrap().receipt;
// Decode the journal to access the public data.
let public_data = receipt.journal.decode()?;
```

## Sharing data structures between host and guest

A good pattern to follow when handling shared data structures between the host
and guest is to have a common `core` module that contains the shared data
structures.
This way, both host and guest can import common data structures and consume them
as needed.

A good example of this pattern being used is the [JWT
Validator][example-jwt-validator].
In its [`core`][example-jwt-validator-core] module, it defines common structures that will
be later used in the [`host`][example-jwt-validator-host] and
[`guest`][example-jwt-validator-guest] modules.
Similarly, the [Chess example][example-chess] does the same with its
[`core`][example-chess-core] being used by the [`host`][example-chess-host] and
[`guest`][example-chess-guest].

Other examples leveraging this pattern can be found in the [examples page].

## Putting it all together

Now that we've covered some details about I/O in the zkVM, let's see how a real
program implements it in practice.

We'll cover the [Voting Machine example][example-voting-machine].
This example is a simple voting machine that allows users to vote for a
candidate.
We'll link to relevant parts of the code as we go along, and it's expected that
you open the linked files in a separate tab to follow along.

The program is a state machine that supports three operations:

- `Init`: Configures initial state
- `Submit`: Which allows a user to submit a vote
- `Freeze`: Which reveals the result of the election and closes the voting

First, we can see that all common data structures are defined in the
[`core`][example-voting-machine-core] module.

The [`host`][example-voting-machine-host] has functions for each of the
operations, and on each of them some input is sent to the guest.
In the [`submit`][example-voting-machine-host-submit] and
[`freeze`][example-voting-machine-host-freeze] functions the host also passes a
buffer to the guest to be filled with the result of the operation, but we'll
get there in time.

Analyzing the [`init`][example-voting-machine-host-init] function first, we can
see that the host simply sends the initial state to the guest using the
[`write`][example-voting-machine-host-init-write] method.
Such data is then [`read`][example-voting-machine-guest-elf-init-read] by the
[`init` guest][example-voting-machine-guest-elf-init] program and immediately
[`commit`][example-voting-machine-guest-elf-init-commit]ed to the journal.
Note how easy it is to operate on data structures when using the standard
[`read`][source-env::read] and [`commit`][source-env::commit] functions, no bit
manipulation needed. It'd be a different story if we were using the `_slice`
variants. Since we don't have to worry about performance critical code here, we
can safely use the standard functions.

Moving on to the [`submit`][example-voting-machine-host-submit] function, we can
see that in the host an [`output`
buffer][example-voting-machine-host-submit-output-buffer] is passed to the
[`stdout`][example-voting-machine-host-submit-output-stdout] file descriptor of
the guest.
It'll be filled with values produced by the guest and then read by calling the
[`from_slice`][source-from_slice] method on the buffer.
This can be seen in [this
line][example-voting-machine-host-submit-output-from_slice].
The result that was filled in the buffer came from the
[`write`][example-voting-machine-guest-elf-submit-write] method call in the
guest.
Remember, the [`write`][source-env::write] method is used to send data to the
host's [`stdout`][stdout] file descriptor.

Still in the [`submit`][example-voting-machine-host-submit] function, note how
the _private_ output from the guest is used, and how it's relevant to the
distinction between _public_ and _private_ data in this case.
In the example presented, the `VotingMachineState` struct is changed during the
guest's execution. But we don't want to commit (make public) the state of the
voting machine, so we use the `stdout` file descriptor to send the result back
to the host.
This way, we can update the voting machine state at each iteration while
preserving its privacy.

Finally, in the [`freeze`][example-voting-machine-host-freeze] function, the
same patterns of sending and receiving data are repeated.

## Conclusions

In this guide, we've covered the basics of I/O in the zkVM. We've seen how to
send data from the host to the guest and vice-versa, how _private_ and _public_
data are distinguished, and how to commit data to the journal.
We also covered the trade-offs between using the standard functions and their
`_slice` variants and showed through the [Voting Machine
example][example-voting-machine] how to implement I/O in practice.
There are more examples available in the [examples page] that you can use as
reference if you wish.

Happy coding!

[article-composition]: https://www.risczero.com/blog/proof-composition
[docs-guest-code-optmization]: ../optimization.md#when-reading-data-as-raw-bytes-use-envread_slice
[docs-hello-world]: ./hello-world.md
[docs-remote-proving]: ../../generating-proofs/remote-proving.md
[example-chess-core]: https://github.com/risc0/risc0/blob/main/examples/chess/core/src/lib.rs
[example-chess-guest]: https://github.com/risc0/risc0/blob/main/examples/chess/methods/guest/src/main.rs
[example-chess-host]: https://github.com/risc0/risc0/blob/main/examples/chess/src/main.rs
[example-chess]: https://github.com/risc0/risc0/tree/main/examples/chess
[example-jwt-validator-core]: https://github.com/risc0/risc0/blob/main/examples/jwt-validator/core/src/lib.rs
[example-jwt-validator-guest]: https://github.com/risc0/risc0/blob/main/examples/jwt-validator/methods/guest/src/main.rs
[example-jwt-validator-host]: https://github.com/risc0/risc0/blob/main/examples/jwt-validator/src/lib.rs
[example-jwt-validator]: https://github.com/risc0/risc0/blob/main/examples/jwt-validator/README.md
[example-voting-machine-core]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/core/src/lib.rs
[example-voting-machine-guest-elf-init-commit]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/methods/guest/src/bin/init.rs#L29-L33
[example-voting-machine-guest-elf-init-read]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/methods/guest/src/bin/init.rs#L28
[example-voting-machine-guest-elf-init]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/methods/guest/src/bin/init.rs
[example-voting-machine-guest-elf-submit-commit]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/methods/guest/src/bin/submit.rs#L31-L39
[example-voting-machine-guest-elf-submit-write]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/methods/guest/src/bin/submit.rs#L30
[example-voting-machine-host-freeze]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/src/lib.rs#L99-L112
[example-voting-machine-host-init-write]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/src/lib.rs#L79
[example-voting-machine-host-init]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/src/lib.rs#L77-L83
[example-voting-machine-host-submit-output-buffer]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/src/lib.rs#L88
[example-voting-machine-host-submit-output-from_slice]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/src/lib.rs#L95
[example-voting-machine-host-submit-output-stdout]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/src/lib.rs#L91
[example-voting-machine-host-submit]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/src/lib.rs#L85-L97
[example-voting-machine-host]: https://github.com/risc0/risc0/blob/main/examples/voting-machine/src/lib.rs
[example-voting-machine]: https://github.com/risc0/risc0/tree/main/examples/voting-machine
[examples page]: ../examples.md
[guest]: https://dev.risczero.com/terminology#guest
[host]: https://dev.risczero.com/terminology#host
[journal]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.journal.html
[source-ExecutorEnvBuilder::stderr]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ExecutorEnvBuilder.html#method.stderr
[source-ExecutorEnvBuilder::stdout]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ExecutorEnvBuilder.html#method.stdout
[source-ExecutorEnvBuilder::write]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ExecutorEnvBuilder.html#method.write
[source-ExecutorEnvBuilder::write_slice]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ExecutorEnvBuilder.html#method.write_slice
[source-Journal::decode]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Journal.html#method.decode
[source-Journal]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Journal.html
[source-env::commit]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit.html
[source-env::commit_slice]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit_slice.html
[source-env::read]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.read.html
[source-env::read_slice]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.read_slice.html
[source-env::write]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.write.html
[source-executor-env]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ExecutorEnv.html
[source-fileno]: https://docs.rs/risc0-zkvm-platform/*/risc0_zkvm_platform/fileno/index.html
[source-from_slice]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/serde/fn.from_slice.html
[source-receipt]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html
[stderr]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.stderr.html
[stdin]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.stdin.html
[stdout]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.stdout.html
[term-cycles]: https://dev.risczero.com/terminology#clock-cycles
[term-journal]: https://dev.risczero.com/terminology#journal
