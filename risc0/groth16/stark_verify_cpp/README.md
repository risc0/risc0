This directory contains the post-processed output of the circom-emitted
`stark_verify` witness generator produced by running the `groth16_proof` setup
process.

In addition, `main.cpp` has been modified to work as a library instead of a
standalone command-line tool.

If the `stark_verify.circom` circuit were ever modified, it would be necessary
to rebuild the verifier by running `./scripts/build.sh` inside `groth16_proof`,
then update the contents of this directory with the new witness generator,
preserving the local modifications to `main.cpp`.
