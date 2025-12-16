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

### Memory argument and paging

The memory bus is 32 bits wide and addressed via 30-bit addresses, with the top quarter protected for machine mode.
All memory transactions flow through the `Memory` argument, which tracks `(cycle, addr, data)`.
`PageInPart` pushes the initial `(addr, 0, data)` at cycle 0, instruction blocks pull and push updated memory to advance the cycle (and optionally data), and a `PageOutPart` pulls the final state so it can be rehashed into the new memory root.
Reads pull `(addr, cycle_in, data)` and push `(addr, cycle_out, data)` with `cycle_in < cycle_out` and `cycle_out` equal to the instruction’s current cycle; writes add the analogous data in/out constraints.

Paging proves that cycle-0 memory matches a Merkleized address space and that execution produces a new Merkle root.
`PageIn`/`PageOut` arguments carry `(index, digest)` for nodes in a binary Merkle tree (1 = root, 2/3 = children, etc.).
`Globals` pushes `(1, <initial_root_hash>)` into `PageIn`, `PageInNode` expands nodes by hashing children, `PageInPage` pages in leaf data with `PageInPart`, and `PageOutPage` rehashes updated leaves into `PageOut`.
Unexpanded nodes are transferred via `PageUncle` and rejoined by `PageOutNode`, and `Globals` pulls the final root.

### Instructions

The circuit implements the RV32IM ISA with general-purpose registers memory mapped in machine-only high memory, maintaining separate user and machine sets for easy context switching.
Instruction ordering uses the `CpuState` argument `(cycle, PC, mode)` where mode is user, machine, or suspended.
`Globals` pushes `(0, 0, suspended)`, `InstResume` reads persisted PC/mode from memory, normal instruction blocks pull `CpuState`, perform work (usually touching `Memory`), and push the advanced state.
`InstSuspend` writes back PC/mode and pushes `(final_cycle, 0, suspended)` for `Globals` to pull.

Instruction block types group related opcodes rather than mapping 1:1.
For example, `InstReg` covers three-register ALU operations, performing register reads/writes and pulling the appropriate unit block for the computation.
All instruction blocks read the encoded instruction from `PC` and delegate decoding to a `Decode` block; `Decode` pushes to `Decode` with multiplicity so repeated instructions need only be decoded once.

### Units

Units perform the actual arithmetic/logic, communicating via the `Unit` argument `(options, a, b, out0, out1)`.
`options` selects the operation; `out0`/`out1` hold results (e.g. low/high 32 bits for multiply).
Units push their enforced relation and can push with multiplicity to memoize repeated computations (though current preflight does not lean on it).
Units may call other units (e.g. division guesses a quotient/remainder and verifies via multiplication).
Details vary between BabyBear and Binius (e.g. multiplication strategy), but the interface remains the same.

### Decoding

The decoder packs everything needed to distinguish an instruction into the `options` field of `Decode`.
In BabyBear this is arithmetic encoding; in Binius it’s bitfields.
Instruction classes unpack portions of `options` to pick the class, select unit outputs, choose unit type and sub-operation, and then feed the unit’s `options`.
Because `Decode` pushes with multiplicity, frequently executed instructions amortize decoding across uses.

### Tables

Lookup tables provide U8 and U16 range checks and a cycle table.
The `Table` argument is `(table, value)` where table `0` = U8, `1` = U16, `2` = cycle numbers.
To show a value is in range, blocks pull the corresponding entry; `MakeTable` produces sequential entries with multiplicity equal to usage, advancing via `MakeTable` arguments.
`Globals` seeds and bounds each table (e.g. U8 from 0 to 256).
Cycle ordering reduces `old_cycle < new_cycle` to showing `(new_cycle - 1 - old_cycle)` is in the cycle table.

### Hashing

`P2CallArgument` verifies Poseidon2 hashing steps using `P2Block`, `P2ExtRound`, and `P2IntRounds`.
`P2Call` is memoized, so repeated hashes of the same data are cheap—crucial for paging since read-only pages pay the hash cost once.
Poseidon2 is BabyBear-specific and will be swapped for a Binius-friendly hash (e.g. Grostl for speed or SHA2 for compatibility).

### Instantiation in the RISC Zero proof system

The current RISC Zero system lacks first-class support for multiple logical tables, so multiple block types are packed into one physical table.
Selector columns choose the block type per row, smaller blocks may share rows, and arguments use a LogUp-style mechanism.

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
