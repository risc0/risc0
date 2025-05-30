# R0VM Browser Verifier

This repository contains a full-stack example for an in-browser ZK proof verifier.

The stack:
- [R0VM](https://dev.risczero.com/api/zkvm/quickstart) for ZK proving.
- [Next.JS](https://nextjs.org/) for the browser app.
- [wasm-pack](https://github.com/rustwasm/wasm-pack) for building the [verifier library](./rust/verifier/src/lib.rs) to [browser compatible JS](./web/public/wasm/pkg/package.json).

## Video Walkthrough

[![Watch the video walkthrough](/web/public/thumbnail.png)](https://www.youtube.com/watch?v=aTCPCf8ff-c)

## Project Structure

The project is organized like below:

```
browser_verifier/
├── guest/       # R0VM guest code that gets executed and proven
├── host/        # R0VM host code for generating proofs
├── verifier/    # WebAssembly-compatible proof verification library
└── web/         # Next.js web application for in-browser proof verification
```

### Running the Web App

```bash
cd web
npm run dev
```

Open [http://localhost:3000](http://localhost:3000) to view the application.

The `web/` directory contains a Next.js application that demonstrates in-browser proof verification:

- Loads the WebAssembly verifier module from [pkg](./web/public/wasm/pkg/) (see [Building the Verifier](#building-the-verifier)).
- Fetches the proof and image ID from [binary files](./web/public/proof_data/).
- Provides UI for proof verification.
- Displays verification result and time it took.
- Displays a time comparison between direct calculation and proof verification.

The web interface allows users to:
1. Calculate the 1000000th Fibonacci number directly in the browser.
2. Verify a pre-generated proof of the calculation in a fraction of the time.
3. Compare the performance difference between direct calculation and proof verification.

## Rust Components

### guest/

The guest code contains the program that runs inside the R0VM (RISC Zero Virtual Machine). This is the computation that gets proven. In this project, it calculates the 1000000th Fibonacci number and commits the length of that number to the journal.

### host/

The host code is responsible for:
- Loading and executing the guest program in the R0VM
- Generating proofs of correct execution
- Serializing the proof and the imageID into binary files that can be used by the verifier in the browser.

The host serializes these into 'receipt.bin' and 'image_id.bin' in the web application's public folder.

### Running proving yourself

> 💡 **Tip: If you want to modify the example to run proving yourself**
> This example's host/guest use R0VM v2.0.2; if you want to run proving yourself, before following the instructions below, make sure to switch to the correct branch: `git checkout release-2.0`

To run the host yourself, with proving:

```bash
cargo run --release
```

This will overwrite the proof files in the web app which could cause failure. The proof data files are included directly in the repo, so you shouldn't need to do this unless you're modifying things. The host is set up to save the necessary files straight to the correct `web/public/proof_data` folder. After you run the proving, you can go ahead and run the web app again with `npm run dev` and click 'Verify a Proof'.

### verifier/

The verifier is a Rust library that:
- Takes the proof and image ID as input
- Verifies that the guest program was executed correctly
- Is compiled to WebAssembly for in-browser verification
- Exposes the `verify_proof` function to JavaScript

The [verifier library](src/lib.rs) contains one function: `verify_proof`.

`verify_proof`:
- takes two `u8` arrays as input; `proof_bytes` and `image_id_bytes`.
- using `risc0_zkvm::Receipt`, the [Receipt](https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Receipt.html) struct is built from `proof_bytes`.
- using `risc0_zkvm::sha::Digest`, the [image_id](https://dev.risczero.com/terminology#image-id) digest is built from `image_id_bytes`.
- the receipt is verified using [receipt.verify](https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Receipt.html#method.verify).
- the output is logged to the console using [web_sys](https://rustwasm.github.io/wasm-bindgen/web-sys/using-web-sys.html).

#### Building the Verifier

To compile the verifier library to WebAssembly:

```bash
cd verifier
wasm-pack build --release --target web --out-dir ../web/public/wasm/pkg
```

The output is in the `wasm/pkg/` directory in the public folder for the web app.

