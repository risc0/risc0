// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::serde::to_vec;

use crate::Job;

pub fn new_jobs() -> Vec<Job> {
    let mut jobs = Vec::new();
    for spec in [1, 10, 100] {
        let guest_input = (spec, vec![0u8; 32]);
        jobs.push(Job::new(
            format!("iter_blake2b-{spec}"),
            risc0_benchmark_methods::ITER_BLAKE2B_ELF,
            risc0_benchmark_methods::ITER_BLAKE2B_ID.into(),
            to_vec(&guest_input).unwrap(),
            spec,
        ));
    }
    jobs
}
