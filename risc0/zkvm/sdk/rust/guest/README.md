# risc0-zkvm-guest

The RISC Zero ZKVM's guest-side RISC-V APIs.

Code that is validated by the [RISC Zero zkVM](risc0_zkvm) is run inside the guest. In the minimal case, an entrypoint (the guest's "`main`" function) must be provided by calling [entry]. The code executed when the entrypoint function is called is what will be proven by the zkVM and available for verification later. In almost all practical cases, the guest will want to read private input data using [env::read] and commit public output data using [env::commit]; additional I/O functionality is also available in [mod@env].

[comment]: # (TODO: The following would ideally be a reference to the starter example guest code, not a copy of it)

For example[^starter-ex], the following guest code proves a number is composite by multiplying two unsigned integers, and panicking if either is `1` or if the multiplication overflows:
```
use risc0_zkvm_guest::env;

risc0_zkvm_guest::entry!(main);

pub fn main() {
    // Load the first number from the host
    let a: u64 = env::read();
    // Load the second number from the host
    let b: u64 = env::read();
    // Verify that neither of them are 1 (i.e. nontrivial factors)
    if a == 1 || b == 1 {
        panic!("Trivial factors")
    }
    // Compute the product while being careful with integer overflow
    let product = a.checked_mul(b).expect("Integer overflow");
    env::commit(&product);
}
```
Notice how [entry] is used to indicate the entrypoint, [env::read] is used to load the two factors, and [env::commit] is used to make their composite product publically available.

[^starter-ex]: The example is based on the [Risc Zero Rust Starter repository](https://github.com/risc0/risc0-rust-starter). 
