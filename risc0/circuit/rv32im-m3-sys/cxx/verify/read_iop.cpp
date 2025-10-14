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

#include "verify/read_iop.h"

#include "zkp/params.h"

namespace risc0 {

ReadIop::ReadIop(const Fp* buf, uint32_t size) : buf(buf), size(size), offset(0) {}

void ReadIop::read(Fp* buf, size_t size) {
  if (offset + size > this->size) {
    throw std::runtime_error("Invalid read");
  }
  std::copy(this->buf + offset, this->buf + offset + size, buf);
  offset += size;
}

void ReadIop::read(FpExt* buf, size_t size) {
  Fp* castBuf = reinterpret_cast<Fp*>(buf);
  read(castBuf, size * kExtSize);
}

void ReadIop::read(Digest* buf, size_t size) {
  Fp* castBuf = reinterpret_cast<Fp*>(buf);
  read(castBuf, size * 8);
}

void ReadIop::done() {
  if (offset != size) {
    throw std::runtime_error("Unread data");
  }
}

void ReadIop::commit(const Digest& digest) {
  rng.mix(digest);
}

Fp ReadIop::rngFp() {
  return rng.rngFp();
}

FpExt ReadIop::rngFpExt() {
  return rng.rngFpExt();
}

size_t ReadIop::rngBits(size_t bits) {
  return rng.rngBits(bits);
}

} // namespace risc0
