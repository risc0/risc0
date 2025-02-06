# In-Browser Proof Verification

Verify that a RISC Zero program is in your browser using WASM!

## Quickstart

In addition to [Rust] and [Node.js], you will need to run from the root of the repository:

```bash
cargo xtask install
cargo xtask gen-receipt
```

Next, install the `cargo-risczero` tool and install the toolchain with:

```bash
curl -L https://risczero.com/install | bash
rzup install
```

### Running a test of in-browser verification

From this directory, run:

```bash
npm install
npm test -- --$BROWSER
```

where `$BROWSER` is one of

- `chrome`
- `firefox`
- `safari`

[Node.js]: https://nodejs.org/en/learn/getting-started/how-to-install-nodejs
[Rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
