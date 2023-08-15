# In-Browser Proof Verification

Verify a RISC Zero program in your browser using WASM!

## Quickstart
In addition to [Rust] and [Node.js], you will need
```
cargo xtask install
cargo xtask gen-receipt
```

Next, install the `cargo-risczero` tool and install the toolchain with:
```bash
cargo install cargo-risczero
cargo risczero install
```
### Running a test of in-browser verification

From this directory, run
```
npm install
npm test -- --$BROWSER
```
where `$BROWSER` is one of
- `chrome`
- `firefox`
- `safari`

[Rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[Node.js]: https://nodejs.dev/en/learn/how-to-install-nodejs/
