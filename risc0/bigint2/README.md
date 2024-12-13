BigInt2 provides precompiles for the RISC Zero zkVM that accelerate big integer algebra, including finite field arithmetic.
This includes both our pre-built precompiles and the syscall interfaces necessary to call both these and any custom application-defined precompiles.

Note that the precompile functionality of this crate is not yet stable.
If you want to opt-in to using this unstable functionality, set the "unstable" feature flag.
