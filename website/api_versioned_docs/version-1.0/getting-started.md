# Getting Started

To harness the power of ZK, you'll need to:

1. [Write an application for the RISC Zero zkVM][zkvm-quickstart].
2. [Generate proofs for your zkVM application][bonsai-quickstart].
3. [Integrate your proofs into on-chain applications][bonsai-on-eth].

```mermaid
flowchart TD
    %% Level 0
    getting_started["Getting Started
    To use the zkVM and/or Bonsai for blockchain applications, users will need to:
    1. Build a zkVM app.
    2. Generate proofs for their zkVM app.
    3. Integrate proofs into blockchain applications."]



    zkvm_app["1. zkVM Application Development"]
        zkvm_quickstart["zkVM Quickstart"]
    proof_generation["2. Generating proofs for your zkVM application"]

    chain_integration["3. Blockchain Integration"]
        getting_proofs_on_chain["Post proofs on-chain"]
        onchain_verifier["Call our on-chain verifier"]


    dev_mode["Dev Mode
    - Skips proving enabling fast prototyping"]
    local_proving["Local Proving
    - Made possible by open-source tech
    - Important for privacy applications"]
    remote_proving["Remote Proving
    - Bonsai is a scalable proving service, <br/>ready to generate proofs as needed."]



    getting_started --> zkvm_app
        zkvm_app --> zkvm_quickstart
    getting_started --> proof_generation
            proof_generation --> dev_mode
            proof_generation --> local_proving
            proof_generation --> remote_proving
    getting_started --> chain_integration
        chain_integration --> getting_proofs_on_chain
        chain_integration --> onchain_verifier
```

[zkvm-quickstart]: ./zkvm/quickstart.md
[bonsai-quickstart]: ./generating-proofs/proving-options.md
[bonsai-on-eth]: ./blockchain-integration/bonsai-on-eth.md
