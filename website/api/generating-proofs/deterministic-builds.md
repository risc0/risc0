# Deterministic Guest Program Builds

In the context of RISC Zero application development, [deterministic builds][term-deterministic-builds] are necessary to ensure a clear linkage between the source code for the [guest program][term-guest-program] and the resulting [Image ID][term-image-id].

<!-- TODO: link to issue -->

Deterministic builds are made possible by running the `rustc` compiler inside a Docker container.

There are a few ways to access deterministic builds for your zkVM application:

## Using `cargo risczero build`

For CLI driven workflows, [`cargo risczero build`][cargo-risczero-crates-page] has options to enable deterministic builds in scripts for CI and as one-off commands.

## Using `build.rs`

For requiring deterministic builds at compile time, set [`GuestOptions`][rustdocs-GuestOptions] and [`DockerOptions`][rustdocs-DockerOptions] for use with [`embed_methods_with_options()`][rustdocs-embed_methods_with_options] to enable deterministic builds in the `methods/build.rs` file:

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

[cargo-risczero-crates-page]: https://crates.io/crates/cargo-risczero
[rustdocs-DockerOptions]: https://docs.rs/risc0-build/latest/risc0_build/struct.DockerOptions.html
[rustdocs-embed_methods_with_options]: https://docs.rs/risc0-build/latest/risc0_build/fn.embed_methods_with_options.html
[rustdocs-GuestOptions]: https://docs.rs/risc0-build/latest/risc0_build/struct.GuestOptions.html
[term-deterministic-builds]: /terminology#deterministic-builds
[term-guest-program]: /terminology#guest-program
[term-image-id]: /terminology#image-id
