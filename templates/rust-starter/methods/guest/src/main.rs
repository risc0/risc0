#![no_main]
{% unless risc0_std -%}
// If you want to try `std` support, also update the guest Cargo.toml file
// *NOTE* that `std` support is experimental
#![no_std]
{% endunless %}

use risc0_zkvm::guest::env;

// Define a main entrypoint to the guest program.
risc0_zkvm::guest::entry!(main);

pub fn main() {
    // TODO: Implement your guest code here

    // Read the input
    // NOTE: The input is basically the only thing kept in secret from verifiers.
    // It is not a good idea to make it public by outputting it to journal.
    let _input: u32 = env::read();

    // TODO: do something with the input
    let output = "Hello, World!";

    // Write public output to the journal.
    env::commit(&output);
}