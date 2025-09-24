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

#pragma once

#include "core/elf.h"
#include "core/util.h"

#include <cstdint>
#include <map>
#include <string>

namespace risc0::rv32im {

void loadWithKernel(std::map<uint32_t, uint32_t>& words,
                    const std::string& kernelElf,
                    const std::string& userElf);

void loadRaw(std::map<uint32_t, uint32_t>& words, const std::string& elf);

void loadRawBytes(std::map<uint32_t, uint32_t>& words, const ArrayRef<uint8_t>& elfBytes);

} // namespace risc0::rv32im
