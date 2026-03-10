# Local Proving

RISC Zero offers a fully [open-source] prover.
Users can run the [zkVM] locally, generating proofs using their own hardware.
The [feature flags] include options to toggle between CPU and GPU proving.

## Local vs. Remote Proving

For most use cases, we recommend remote proving using [Bonsai], our scalable and highly parallel proving service.

Proving with **private data** is a key reason to consider using local proof generation, as whoever is generating the proofs can see all private information involved.
With local proof generation your private data never leaves your machine.

## Proving hardware

RISC Zero's proving system for multiple hardware targets.

:::info
The Groth16 prover currently _only_ works on x86 architecture, and so Apple Silicon is _currently unsupported_ (even via Docker).

You can find out more info in the relevant issues [#1520] and [#1749].
:::

> TIP: In cases where memory is constrained (i.e. less than 10 GB is available), it may be necessary to change the [segment size limit][segment-limit-docs].

> NOTE: When run for the first time, the GPU (e.g. Metal or CUDA) kernels may need to be JIT compiled.
> This can take a few minutes, but should only happen once.

### CPU

RISC Zero proving will run on nearly any modern CPU (x86 or ARM).
Proving on CPU is the easiest to setup, and the most portable, but will not result in the highest performance or compute costs.

### NVIDIA GPU

RISC Zero is highly optimized for running on GPUs. Currently, RISC Zero targets NVIDIA GPUs using the CUDA framework.

Running on NVIDIA GPUS requires the CUDA runtime, and building the GPU kernels requires the NVIDIA toolkit.

Using Ubuntu as an example, the following steps will install and configure the necessary dependencies, and build RISC Zero to use CUDA.

```bash
# install driver install tool
sudo apt install ubuntu-drivers-common
# install drivers
sudo ubuntu-drivers install
# install compiling tools for risc0
sudo apt install build-essential libssl-dev -y
# install the cuda toolkit to compile the required codebase
sudo apt install cuda-toolkit -y
# install rust
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
# setup your paths
echo 'export PATH=/usr/local/cuda/bin:$PATH' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc
# clone the risc0 repo
git clone https://github.com/risc0/risc0.git
cd risc0
# install the r0vm
cargo run --bin rzup install
# run a benchmark on your GPU!
# NOTE: Building the GPU kernels may take a long time.
RUSTFLAGS="-C target-cpu=native" cargo run -F cuda -r --example datasheet
```

### Apple Metal

On MacOS, when using a machine with Apple Silicon (such as the M-series MacBooks), RISC Zero will use the integrated [Metal][apple-metal] compute cores.
No options need to be configured to take advantage of acceleration through the use of Metal.

[#1520]: https://github.com/risc0/risc0/issues/1520
[#1749]: https://github.com/risc0/risc0/issues/1749
[apple-metal]: https://developer.apple.com/metal
[Bonsai]: ./remote-proving.md
[feature flags]: https://github.com/risc0/risc0#feature-flags
[open-source]: https://risczero.com/news/open-source
[segment-limit-docs]: https://docs.rs/risc0-zkvm/2.1/risc0_zkvm/struct.ExecutorEnvBuilder.html#method.segment_limit_po2
[zkVM]: ../zkvm/zkvm-overview.md
