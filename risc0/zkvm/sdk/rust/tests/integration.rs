// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use anyhow::Result;
use risc0_zkvm::{method_id::MethodId, prove::Prover, receipt::Receipt};
use risc0_zkvm_methods::{IO_ID, IO_PATH};

fn run_memio(pairs: &[(usize, usize)]) -> Result<Receipt> {
    let mut vec = Vec::new();
    vec.push(pairs.len() as u32);
    for (first, second) in pairs {
        vec.push(*first as u32);
        vec.push(*second as u32);
    }
    let elf_contents = std::fs::read(IO_PATH).unwrap();
    // let method_id = MethodId::load(IO_ID).unwrap();
    log::debug!("io_path: {IO_PATH}");
    let mut prover = Prover::new(&elf_contents)?;
    prover.add_input_u32_slice(vec.as_slice());
    prover.run()
}

mod integration {
    use risc0_zkvm::platform::memory::{COMMIT, HEAP};

    use crate::run_memio;

    fn init() {
        let _ = env_logger::builder().is_test(true).try_init();
    }

    #[test]
    fn memory_io() {
        init();

        // Double write to WOM are fine
        assert!(run_memio(&[(COMMIT.start(), 1), (COMMIT.start(), 1)]).is_ok());

        // FIXME
        // Double write to WOM with different values throw
        // assert!(run_memio(&[(COMMIT.start(), 1), (COMMIT.start(), 2)]).is_err());

        // But they are OK at different addresses
        assert!(run_memio(&[(COMMIT.start(), 1), (COMMIT.start() + 4, 2)]).is_ok());

        // Aligned write is fine
        assert!(run_memio(&[(HEAP.start(), 1)]).is_ok());

        // FIXME
        // Unaligned write is bad
        // assert!(run_memio(&[(HEAP.start() + 1, 1)]).is_err());

        // Aligned read is fine
        assert!(run_memio(&[(HEAP.start(), 0)]).is_ok());

        // FIXME
        // Unaligned read is bad
        // assert!(run_memio(&[(HEAP.start() + 1, 0)]).is_err());
    }
}
