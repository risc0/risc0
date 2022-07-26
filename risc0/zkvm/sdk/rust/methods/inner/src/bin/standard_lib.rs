risc0_zkvm_guest::entry!(main);

pub fn main() {
    println!("Hello world on stdout!");
    eprintln!("Hello world on stderr!");
}
