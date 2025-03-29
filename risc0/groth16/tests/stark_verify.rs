// Copyright 2025 RISC Zero, Inc.
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

#[cfg(test)]
mod tests {
    use risc0_groth16::stark_verify;
    use std::{
        fs::File,
        io::Write,
    };
    use tempfile::tempdir;

    fn test_witgen(input: &[u8], expect: &[u8]) {
        let dir = tempdir().unwrap();
        let in_path = dir.path().join("input.json");
        let mut in_file = File::create(&in_path).unwrap();
        in_file.write_all(&input).unwrap();
        let out_path = dir.path().join("output.wtns");
        let ret = stark_verify::calc_witness(&in_path, &out_path);
        assert!(0 == ret);
        let wtns = std::fs::read(out_path).unwrap();
        assert_eq!(wtns, &*expect);
        drop(in_file);
        dir.close().unwrap();
    }

    #[test]
    fn test_loop() {
        const INPUT: &[u8] = include_bytes!("data/loop-seal.json");
        const EXPECT: &[u8] = include_bytes!("data/loop.wtns");
        test_witgen(INPUT, EXPECT);
    }

    #[test]
    fn test_fib() {
        const INPUT: &[u8] = include_bytes!("data/fib-seal.json");
        const EXPECT: &[u8] = include_bytes!("data/fib.wtns");
        test_witgen(INPUT, EXPECT);
    }

}
