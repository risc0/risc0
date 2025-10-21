// Copyright 2025 RISC Zero, Inc.
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

#include "prove/write_iop.h"

#include "zkp/params.h"

namespace risc0 {

void WriteIop::write(const Fp* buf, size_t size) {
  transcript.insert(transcript.end(), buf, buf + size);
}

void WriteIop::write(const FpExt* buf, size_t size) {
  const Fp* castBuf = reinterpret_cast<const Fp*>(buf);
  write(castBuf, size * kExtSize);
}

void WriteIop::write(const Digest* buf, size_t size) {
  const Fp* castBuf = reinterpret_cast<const Fp*>(buf);
  write(castBuf, size * 8);
}

void WriteIop::write(uint32_t value) {
  Fp fpValue = Fp::fromRaw(value);
  write(&fpValue, 1);
}

const std::vector<Fp>& WriteIop::getTranscript() {
  return transcript;
}

void WriteIop::commit(const Digest& digest) {
  rng.mix(digest);
}

Fp WriteIop::rngFp() {
  return rng.rngFp();
}

FpExt WriteIop::rngFpExt() {
  return rng.rngFpExt();
}

size_t WriteIop::rngBits(size_t bits) {
  return rng.rngBits(bits);
}

} // namespace risc0
