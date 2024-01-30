# dev-mode

We support a development-only mode for standalone risc0 projects in which code
is executed but not proven. This adds efficiency to the development cycle during
development stages where proving correct execution is not yet critical.

A risc0 project, when run in dev-mode by setting the `RISC0_DEV_MODE`
environment variable, supports ([fake]) receipt creation and pass-through
'verification' function, so that dev-mode may be switched on and off at runtime
without impacting project workflows. In particular, receipts generated in
dev-mode still include public outputs written to the [journal].

However, because the proving process is bypassed, receipts generated when
dev-mode is enabled will fail a standard receipt verification check. Only when
the verifier is also run with dev-mode enabled will it perform pass-through
'verification' of the fake receipt.

**To keep this mode out of production environments, we recommend building
production-ready projects with the `disable-dev-mode` [feature flag]; it is
absent by default.**

Only projects built without this flag may run dev-mode. Enabling dev-mode
requires also that the environment variable `RISC0_DEV_MODE` be set.

As additional protection, if the dev-mode environment variable is present
alongside a project built with the `disable-dev-mode` feature flag, the project
will panic.

For further reference, take a look at the table below.

|                                 | `disable-dev-mode` off   | `disable-dev-mode` on    |
| ------------------------------- | ------------------------ | ------------------------ |
| `RISC0_DEV_MODE=true`           | dev-mode activated       | Prover panic             |
| `RISC0_DEV_MODE=false` or unset | Default project behavior | Default project behavior |

[fake]: https://docs.rs/risc0-zkvm/0.20/risc0_zkvm/enum.InnerReceipt.html#variant.Fake
[feature flag]: https://github.com/risc0/risc0/#feature-flags
[journal]: /terminology#journal
