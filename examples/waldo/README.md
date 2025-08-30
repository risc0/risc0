# Where's Waldo

_**Check out our [blogpost](https://www.risczero.com/news/waldo) about this example!**_

[Where's Waldo] is a [favorite analogy] for zero-knowledge proofs. In
particular, there is this visual that if you take a Where's Waldo image and
cover it up with a big piece of cardboard with a small cutout that just shows
Waldo, you can prove you _know_ where he is while keeping that location secret.

But these days, why not implement a real zero-knowledge proof to show you know
where Waldo is?

This example implements a RISC0 zero-knowledge program that allows a prover to
convince a verifier they know Waldo's location in a public Where's Waldo puzzle,
without revealing Waldo's coordinates.

## Quick Start

### Installing Dependencies

Follow the [examples guide] to install dependencies and check out the correct version of the example.

### Run the Prover to construct a Receipt

Now, you're ready to construct a receipt that proves you know where Waldo is located. From the `waldo` folder, run:

```bash
# Prove that you know where Waldo is in waldo.webp
cargo run --bin prove -- -i waldo.webp -x 1150 -y 291 --width 58 --height 70 -m waldo_mask.png
```

Congratulations! You just proved that you know where Waldo is!

### Run the Verifier

You can send the `receipt` to a third party, who can `verify` it by running:

```bash
# Verify that the prover actually found Waldo.
cargo run --bin verify -- -i waldo.webp -r receipt.bin
```

Running the verifier proves that the contents of the [journal] were indeed constructed by the binary file associated with the expected [ImageID].

## Approach

The approach for this example is similar to the analogy. It takes the full image
and "cuts out" just Waldo. This cutting out operation takes place in the zkvm
guest such that a commitment to the source image and the cut out image of Waldo
can be revealed, without giving the verifier the coordinates. Key to this proof
is ensuring that the cutout came from the expected source image, and not some
unrelated picture that includes Waldo.

### Merkleization

In the simplest approach, the guest program would simply hash the whole Where's
Waldo image in memory, then perform the crop and mask operations to cut out
Waldo on that image. It would commit the image hash and the cut out image to the
journal. Unfortunately, hashing the whole image, which we expect to be rather
large, is cost prohibitive in the guest.

Because we only need access to a relatively small portion of the image to
produce the cutout, a viable approach is to split the image into a vector of
small image chunks and use a Merkle tree to commit to this vector. The zkVM
guest can then ask the host for image chunks, and along with the chunk the host
can provide a Merkle path that proves the chunk is part of the committed image.

In the `waldo_core::merkle` module a wrapper is implemented on the
`merkle_light` crate with support for using the SHA256 guest circuit, and
providing a `VectorOracle` abstraction. In the `waldo_core::image` module is
implemented a specific MerkleTree type for images, and an `ImageOracle` type
which can be used in the guest for image operations.

Similar Merkle tree abstractions can be used to, for example, ensure a secret
word is part of a dictionary, a payment destination is not in a list of banned
addresses, or that a user is in the set of authorized users.

### zkVM Communication Channels

In the RISC0 zkVM system, the guest and host can communicate over using syscalls
at runtime. These syscalls are currently used to implement the `env::read` and
`env::commit` functions in the guest, and the developer can create new syscalls
for their own needs. In this example, a syscall is used to allow the guest to
request chunks of the Where's Waldo image on demand as a part of the
`MerkleTree` and `VectorOracle` types. Using these syscalls allows us to write
more flexible code that is more readable and follows familiar paradigms.

### Image Manipulation

In order to manipulate the image and cut-out Waldo, and in particular to crop
and apply a mask, this example utilizes the popular `image` crate. This is
enabled by implementing `image::GenericImageView` on `ImageOracle`. With that
trait, many of the image operations provided in the `image` crate, and by
[others], can be used on `ImageOracle` inside the guest. A similar approach
could be used to produce a provable blur, image down-scaling, and more.

## Run this example

First, make sure [rustup](https://rustup.rs) is installed. This project uses a
[nightly](https://doc.rust-lang.org/book/appendix-07-nightly-rust.html) version
of [Rust](https://doc.rust-lang.org/book/ch01-01-installation.html). The
[`rust-toolchain`](/rust-toolchain.toml) file will be used by `cargo` to automatically
install the correct version.

To build and run this example, try using the following commands.

```bash
# Prove that you know where Waldo is in waldo.webp
cargo run --release --bin prove -- -i waldo.webp -x 1150 -y 291 --width 58 --height 70 -m waldo_mask.png

# Verify that the prover actually found Waldo.
cargo run --release --bin verify -- -i waldo.webp -r receipt.bin
```

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[favorite analogy]: https://medium.com/swlh/a-zero-knowledge-proof-for-wheres-wally-930c21e55399
[ImageID]: https://dev.risczero.com/terminology#image-id
[journal]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html#structfield.journal
[others]: https://docs.rs/imageproc/latest/imageproc/
[Where's Waldo]: https://en.wikipedia.org/wiki/Where%27s_Wally%3F
