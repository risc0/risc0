# risc0-zkp-sys

Contains core C++ classes for actual ZK-Stark system, including proving and
verifying.  This does not include any RISC-V specific parts of the system.

The rust crate builds the C++ code into a lib, but does not export anything to
rust.
