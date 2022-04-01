// Copyright 2022 Risc0, Inc.
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

#include "risc0/zkvm/verify/method_id.h"

#include <fstream>

namespace risc0 {

MethodID readMethodID(const std::string& filename) {
  std::ifstream file(filename, std::ios::in | std::ios::binary);
  if (!file) {
    throw std::runtime_error("Unable to open file: " + filename);
  }
  MethodID id;
  file.read(reinterpret_cast<char*>(&id), sizeof(MethodID));
  file.close();
  if (!file.good()) {
    throw std::runtime_error("Error reading MethodID file: " + filename);
  }
  return id;
}

} // namespace risc0
