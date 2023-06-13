# Migration Guide

We have made substantial changes to our API, both in support of continuations and as part of more general upgrades. Essentially every project using the RISC Zero zkVM will need to make changes in order to upgrade to 0.15. This migration guide is intended to help you do so. Our [examples](https://github.com/risc0/risc0/tree/main/examples) have already been updated.

## Host code update: code execution and receipt generation

Instead of `Prover` and `Receipt`, your host code should now include `ExecutorEnv`,  `Executor`, and `SessionReceipt` from the  `risc0_zkvm` crate. There are significant accompanying code change requirements, outlined below.

 **Old process (0.14):**

In 0.14, you created a new instance of`Prover` that takes a program ELF, as in the following code snippet:

```bash
let mut prover = Prover::new(PROGRAM_ELF);
```

You then added any program inputs you wanted to make available at compile time:

```bash
prover.add_input_u32_slice(&to_vec(input).unwrap());
```

Finally, you ran the `Prover` and generated a `Receipt`:

```bash
let receipt = prover.run().unwrap();
```

**********New process (0.15):**********

In 0.15, you’ll be creating an instance of type `Executor` that takes a program ELF and an environment `ExecutorEnv`. Initial guest inputs will be added to the environment. The setup process will happen in two steps:

- Build the `ExecutorEnv` environment. Notice that here we’re adding our starting inputs to the environment:

```bash
let env = ExecutorEnv::builder()
		.add_input(&to_vec(input).unwrap())
		.build()
                .unwrap();
```

- Construct an `Executor` using your program ELF and the instance of `ExecutorEnv`:

```bash
let mut exec = Executor::from_elf(env, PROGRAM_ELF).unwrap();
```

You’ll use the `Executor`to generate a `Session`:

```bash
let session = exec.run().unwrap();
```

At this stage, nothing has been proven yet. To prove guest code execution and produce a `SessionReceipt`, take one final step:

```bash
let receipt = session.prove().unwrap();
```

This is a significant code change, so let’s recap.

**Old process (0.14):**

- Create `Prover` using program ELF
- Add inputs to `Prover`
- Call `Prover::run()` to generate a receipt

**New process (0.15):**

- Create `ExecutorEnv`
- Add inputs to `ExecutorEnv`
- Create `Executor` using `ExecutorEnv` and program ELF
- Run `Executor::run()` to generate a `Session`
- Call `Session::prove()` to generate a receipt

## Host code update: adding guest inputs

## Old process (0.14):

To pass input to the prover in 0.14, you could call `Prover::add_input_u32_slice` or `Prover::add_input_u8_slice`.

```bash
prover.add_input_u32_slice(&to_vec(&input1).unwrap());
prover.add_input_u8_slice(&to_vec(&input2).unwrap());
```

Input could be added before calling `Prover::run` and initiating guest code execution.

## New process (0.15):

As described in the above section on code execution and receipt generation, inputs are added to the `ExecutorEnv` using `ExecutorEnvBuilder::add_input`. This happens during executor environment construction:

```bash
let env = ExecutorEnv::builder()
        .add_input(&to_vec(input1).unwrap())
        .add_input(&to_vec(input2).unwrap())
        .build()
        .unwrap();
```

If you are interested in providing the guest program with interactive I/O, `ExecutorEnvBuilder` includes a variety of other options; consult [its documentation](https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.ExecutorEnvBuilder.html) for details.

## Host update: adding guest callbacks

If you previously supplied inputs with callback via `ProverOpts::with_send_recv_callback`, the most similar option in 0.15 is `ExecutorEnvBuilder::io_callback`. Other options, such as `ExecutorEnvBuilder::stdin` and `ExecutorEnvBuilder::stdout`, may make more sense for some use cases. If you want more details or are considering refactoring to different callbacks, look at our [ExecutorEnvBuilder documentation](https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.ExecutorEnvBuilder.html).
