# rv32im M3

The `rv32im-m3` circuit is the third generation of the RISC Zero virtul machine.
It provides massive improvements in proving performance, while also extending the set supported of RISC-V features (e.g. compressed instructions).
It's new architecture is inspired by the M3 arithmetization developed by [Irreducible](https://www.irreducible.com/), and adapted to the RISC Zero proof system.

## High Level Design

`rv32im-m3` is constructed as set of _blocks_ which represent a specific constraints, connected by _arguments_ which relate the blocks to one another.

Blocks define discrete units of functionality.
Each block has a block type, and all blocks of the same type enforce the same constraints.
Each block has a set of logical witness values, which act as the inputs to the constraints.
For example, an addition block may have 3 witness values, each of which is a 32-bit number, and may enforce the constraint that a = b + c.

Blocks are connected via arguments.
Each argument also has an argument type and be be thought of basically as a typed tuple.
Arguments do not enforce any constraints over their elements, which is handled by blocks.

A given block type will push or pull some specific argument types, and populate the arguments via expressions over it's witness values.
Semantically, a block will "push" arguments for their "result", e.g. `Add { a, b, c}`.
Another block will "pull" an argument to consume this result, e.g. the branch-if-equal instruction will pull an argument from the adder unit.

Some blocks may push with a multiplicity that is based on block witness data.
This is used to basically 'memoize' certain computations, or one can view it as a single writer with multiple readers.

In addition to the requirement that the constraints within each block are satisfied, all of the arguments must balance:
That is, for each argument with a particular type and values pushed by a block, some other block must pull the same argument (i.e. matching type + values).
This global balance condition is basically the way in which relations between blocks are modeled.
In the case of a single push with multiplicity N, this requires that N different blocks pull to maintain the balance.

## Development

### Build

```
bazelisk build //...
```

### Test

```
bazelisk test //...
```

### Format

check:
```
bazelisk build //... --config=clang-format-check
```

fix:
```
bazelisk build //... --config=clang-format
```

### Bootstrap

Integrating the circuit into the Rust codebase of `risc0-zkvm` requires building prover and verifier artifacts (e.g. `taps.rs` and `poly_ext.rs`).

To bootstrap, run the following from the repository root:

```
cargo xfast bazel
cargo run -p xtask -- bootstrap
```
