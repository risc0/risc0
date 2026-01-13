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

#include "core/log.h"
#include "examples/hello/hello.h"
#include "zkp/fp.h"
// #include <fstream>

using namespace risc0;

int main() {
  size_t po2 = 12;

  IHalPtr hal = getCpuHal();
  CircuitInfo& ci = *hello_m3::getCircuitInfo(hal, po2);
  Prover prover(hal, ci, po2);

  WriteIop wiop;
  prover.prove(wiop);
  const std::vector<Fp>& transcript = wiop.getTranscript();

  LOG(0, "Finished proving, begin verifying...");

  VerifyCircuitInfo& vci = *hello_m3::getVerifyCircuitInfo();
  ReadIop riop(transcript.data(), transcript.size());
  verify(vci, riop, po2);
  riop.done();

  // This code can be used to write the proof to a file for consumption by the
  // Rust verifier.
  // auto myfile = std::fstream("/path/to/risc0/zkp/src/prove/proof.bin", std::ios::out |
  // std::ios::binary); myfile.write((const char*) (wiop.getTranscript().data()), 4 *
  // wiop.getTranscript().size()); myfile.close();

  return 0;
}
