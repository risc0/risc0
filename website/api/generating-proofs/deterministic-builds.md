# Deterministic Guest Program Builds

In the context of RISC Zero application development, [Deterministic builds][term-deterministic-builds] are necessary to ensure a clear linkage between the source code for the [guest program][term-guest-program] and the resulting [Image ID][term-image-id].

<!-- TODO: link to issue -->

Deterministic builds are made possible by running the `rustc` compiler inside a Docker container.

There are a few ways to access deterministic builds for your zkVM application:

## Using `cargo risczero build`

For CLI driven workflows, [`cargo risczero build`][cargo-risczero-rust-docs] has options to enable deterministic builds in scripts for CI and as one-off commands.

## Using `build.rs`

For requiring deterministic builds at compile time, you can set options to enable deterministic builds in the `methods/build.rs` file:

```rust
fn main() {
    let docker_opts = DockerOptions {
        root_dir: None, // this can also point to the path where the docker context should be
    };
    let guest_opts = GuestOptions {
        use_docker: Some(docker_opts),
        ..Default::default(),
    };
    embed_methods_with_options(HashMap::from(["guest_name", guest_opts]));
}
```

[cargo-risczero-rust-docs]: https://docs.rs/crate/cargo-risczero/latest
[term-deterministic-builds]: terminology#deterministic-builds
[term-guest-program]: terminology#guest-program
[term-image-id]: terminology#image-id
