use alloc::vec::Vec;

use anyhow::Result;

use crate::zkvm::Receipt;

pub struct Prover {}

impl Prover {
    /// Create a new [Prover] with the given method (specified via `elf_path`)
    /// and an associated method ID (specified via `id_path`).
    pub fn new(_elf_path: &str, _id_path: &str) -> Result<Self> {
        todo!()
    }

    /// Provide private input data that is availble to guest-side method code
    /// to 'read'.
    pub fn add_input(&mut self, _slice: &[u32]) -> Result<()> {
        todo!()
    }

    /// Provide access to private output data written by guest-side method code.
    pub fn get_output(&self) -> Result<&[u8]> {
        todo!()
    }

    /// Provide access to private output data written to by guest-side method
    /// code.
    ///
    /// This returns the data as a [`Vec<u32>`].
    pub fn get_output_vec(&self) -> Result<Vec<u32>> {
        todo!()
    }

    /// Execute the ZKVM to produce a [Receipt].
    pub fn run(&self) -> Result<Receipt> {
        todo!()

        // let circuit = Risc0Circuit::new(code_id);

        // // Set the memory handlers to call back to the impl
        // MemoryHandler handler(impl.get());
        // // Make the circuit
        // std::unique_ptr<ProveCircuit> circuit =
        // getRiscVProveCircuit(impl->elfPath.c_str(), handler);
        // BufferU32 seal = prove(*circuit);
        // // Attach the full version of the output journal + construct receipt
        // object Receipt receipt{getCommit(), seal};
        // // Verify receipt to make sure it works
        // receipt.verify(impl->idPath);
        // return receipt;
    }
}
