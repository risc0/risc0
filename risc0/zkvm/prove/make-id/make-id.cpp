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

#include <iostream>

#include "risc0/zkvm/prove/method_id.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "usage: make-id <elf_in> <id_out>" << std::endl;
    return 1;
  }
  try {
    risc0::MethodID id = risc0::makeMethodID(argv[1]);
    risc0::writeMethodID(argv[2], id);
  } catch (const std::exception& e) {
    std::cerr << "Unable to make code ID: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
