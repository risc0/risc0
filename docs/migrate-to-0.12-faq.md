# Migrating to v0.12 FAQs

There are breaking changes between v0.11 and v0.12. We have information about the updates required to migrate your code in the Breaking Changes section of the v0.12.0 release notes, and we recommend starting there when migrating. This document will focus on come errors when migrating and their solutions.

## Update rust-toolchain

**Q:** I’ve updated my `risc0-build` package to a known good version and am seeing the following error:

```
error: no matching package named `risc0-build` found
```

What’s going on?

**A:** If you’re encountering a build error with `risc0-build`, it’s possible that you need to update your `rust-toolchain` to a new version of rust nightly. An example line follows:

```
channel = "nightly-2022-10-28"
```

## Missing guest `std` support

**Q:** How do I fix the error “found duplicate lang item `panic_impl`" (or `oom`)?

**A:** This happens if you use Rust Standard Library code in the zkVM guest without telling Cargo you need `std` support for the guest. If you are using `std` code in the guest, include `"std"` as one of the `features` of `risc0_zkvm` in the Cargo file for the guest code. (In the directory structure as our [Rust starter template](https://github.com/risc0/risc0-rust-starter), this file is `methods/guest/Cargo.toml`.) You do still need to disable the default features of `risc0_zkvm` when it’s a guest dependency (since those include host-side features incompatible with the guest), so the line in the Cargo file will look something like this:

```toml
risc0-zkvm = { version = "0.12", default-features = false, features = [ "std" ] }
```

## Extraneous `build.rs` file

**Q:** When building the guest methods crate, I’m getting a link error like this:

```
cannot find function `link` in crate `risc0_build`
```

What should I do?

**A:** For version 0.12, the `risc0_build::link` function is no longer necessary and was removed. Delete any `[build.rs](http://build.rs)` files that call this function as they aren't needed in this version.

## Dependencies won't update

**Q:** When I update I get an error “failed to select a version for `bytemuck`" (or some other package), but the details about the error don’t show a conflict. What’s wrong?

**A:** We believe this is related to yanked crate versions. You need to update your Cargo `.lock` files for both the host and guest side. If you are using the same directory structure as our [Rust starter template](https://github.com/risc0/risc0-rust-starter), you can do this by running `cargo update` in both the root directory and `methods/guest`.
