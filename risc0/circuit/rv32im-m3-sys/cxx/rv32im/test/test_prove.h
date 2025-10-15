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

#include <string>

#include "rv32im/emu/emu.h"

namespace risc0 {

void runTestBinary(const std::string& elf, rv32im::HostIO& io, size_t po2 = 12);
void runTestBinary(const std::string& kernel,
                   const std::string& guest,
                   rv32im::HostIO& io,
                   size_t po2 = 12);

} // namespace risc0
