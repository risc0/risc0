# XGBoost example

This example is meant to serve a guide for developers interested in using the RISC Zero for zkML applications using the popular XGBoost machine learning model. The model can be trained in Python and exported as a JSON file to into the RISC Zero zkVM.  Inference is computed within the guest code, allowing developers to submit a cryptographic receipt attesting to the correct execution of the trained model without revealing either the inputs or the model parameters.

Model training takes place in a Python Jupyter Notebook using the XGBoost model from the Forust machine learning package.  The package is a pure Rust implementation of the XGBoost algorithm, complete with Python bindings.  This allowing developers to focus on data collection, feature engineering, and other machine learning related pre-processing tasks using all of the tools available in the Python machine learning ecosystem.

The layout of this example is intended as a template for developers to train XGBoost models with their own data with minimal modifications to the host and guest code of the zkVM.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

## Install Jupyter Notebook

Instructions for installing Jupyter Notebooks can be found on the [Jupyter Website].

## Running proofs remotely on Bonsai

_Note: The Bonsai proving service is still in early Alpha; an API key is
required for access. [Click here to request access][bonsai access]._

If you have access to the URL and API key to Bonsai you can run your proofs
remotely. To prove in Bonsai mode, invoke `cargo run` with two additional
environment variables:

```bash
BONSAI_API_KEY="YOUR_API_KEY" BONSAI_API_URL="BONSAI_URL" cargo run
```

## Directory Structure

It is possible to organize the files for these components in various ways.
However, in this starter template we use a standard directory structure for zkVM
applications with the addition of a Python Jupyter notebook, which we think is a
good starting point for your applications.

```text
project_name
├── spice-ai-template.ipynb                <-- [Model training happens here]
├── Cargo.toml
├── host
│   ├── Cargo.toml
│   └── src
│       └── main.rs                        <-- [Host code goes here]
└── methods
    ├── Cargo.toml
    ├── build.rs
    ├── guest
    │   ├── Cargo.toml
    │   └── src
    │       └── bin
    │           └── method_name.rs         <-- [Guest code goes here]
    └── src
        └── lib.rs
```

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[bonsai access]: https://bonsai.xyz/apply
[Jupyter Website]: https://jupyter.org/install
