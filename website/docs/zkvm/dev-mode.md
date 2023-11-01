---
slug: ./
---

# What is dev-mode, and how can you use it safely?

We support a development-only mode for standalone risc0 projects in which code is executed but not proven. This adds efficiency to the development cycle during development stages where proving correct execution is not yet critical.

A risc0 project, when run in dev-mode by setting the `RISC0_DEV_MODE` environment variable, supports ([fake](https://docs.rs/risc0-zkvm/0.19.0/risc0_zkvm/enum.InnerReceipt.html#variant.Fake)) receipt creation and pass-through (fake) 'verification' function, so that dev-mode may be switched on and off at runtime without impacting project workflows.
In particular, receipts generated in dev-mode still include public outputs written to the [journal](https://dev.risczero.com/terminology#journal).

However, because the proving process is bypassed, receipts generated when dev-mode is enabled will fail a standard receipt verification check. Only when the verifier is also run with dev-mode enabled will it perform pass-through 'verification' of the fake receipt.

**To keep this mode out of production environments, we recommend building production-ready projects with the "disable-dev-mode" [feature flag](https://github.com/risc0/risc0/#feature-flags); it is absent by default.**

Only projects built without this flag may run dev-mode. Enabling dev-mode requires also that the environment variable `RISC0_DEV_MODE` be set.

As additional protection, if the dev-mode [environment variable](https://docs.rs/risc0-zkvm/*/risc0_zkvm/fn.is_dev_mode.html) is present alongside a project built with the "disable-dev-mode" feature flag, the project will panic.

For further reference, take a look at the table below. To learn more about usage, see the [risc0 project README](https://github.com/risc0/risc0/#readme). For a closer look at implementation, take a look at the [dev-mode source](https://github.com/risc0/risc0/blob/v0.19.0-rc.1/risc0/zkvm/src/host/server/prove/dev_mode.rs).

|                               | `disable-dev-mode` off   | `disable-dev-mode` on    |
| ----------------------------- | ------------------------ | ------------------------ |
| RISC0_DEV_MODE=true           | dev-mode activated       | Prover panic             |
| RISCO_DEV_MODE={false, unset} | Default project behavior | Default project behavior |
