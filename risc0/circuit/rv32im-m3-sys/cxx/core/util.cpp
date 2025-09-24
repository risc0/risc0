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

#include "core/util.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace risc0 {

std::vector<uint8_t> loadFile(const std::string& path) {
  std::ifstream is(path, std::ios::binary);
  is.exceptions(std::ios_base::failbit | std::ios_base::badbit);
  is.seekg(0, std::ios::end);
  size_t nbytes = is.tellg();
  is.seekg(0, std::ios::beg);
  std::vector<uint8_t> elfContents(nbytes, 0);
  is.read(reinterpret_cast<char*>(elfContents.data()), nbytes);
  is.close();
  return elfContents;
}

} // namespace risc0
