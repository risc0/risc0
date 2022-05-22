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

#include "risc0/core/log.h"
#include "risc0/zkvm/circuit/make_circuit.h"

int main(int argc, char* argv[]) {
  risc0::setLogLevel(1);

  if (argc < 2) {
    LOG(1, "usage: make-circuit <output_path>");
    return 1;
  }

  risc0::circuit::make_circuit(argv[1]);
  return 0;
}
