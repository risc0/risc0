// Copyright 2024 RISC Zero, Inc.
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

    #[test]
    fn test_stark_verify() {
        unsafe {
            let datbuf = stark_verify::CIRCUIT_DATA.as_ptr();
            let datsize = stark_verify::CIRCUIT_DATA.len();
            const JSONFILE: &[u8] = "input.json".as_bytes();
            let jsonfile = JSONFILE.as_ptr();
            const WTNSFILE: &[u8] = "output.wtns".as_bytes();
            let wtnsfile = WTNSFILE.as_ptr();
            let _ret = stark_verify::calc_witness(
                datbuf, datsize as u64, jsonfile, wtnsfile);
        }
    }
}
