# In-Browser Proof Verification

Verify a RISC Zero program in your browser using WASM!

## Quickstart

### Dependencies

In addition to [Rust] and [Node.js], you will need
```
cargo xtask install
cargo xtask gen-receipt
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

[Rust]: https://www.rust-lang.org/tools/install
[Node.js]: https://nodejs.dev/en/learn/how-to-install-nodejs/
