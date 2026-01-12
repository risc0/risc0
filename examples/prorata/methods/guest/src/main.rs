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

use prorata_core::AllocationQuery;
use risc0_zkvm::guest::env;

fn main() {
    // Load the amount, recipients, and target user sent from the host:
    let query: AllocationQuery = env::read();

    // Compute the allocation for the requested target recipient:
    let result = query.compute_result();

    // Commit the allocation and query to the journal for inclusion in the receipt:
    env::commit(&result);
}
