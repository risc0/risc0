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

#include "risc0/r0vm/cpp/device/risc0.h"

#include "box_collision.h"

using namespace risc0;

extern "C" void risc0_main(Env* env) {
  const int& params = env->read<uint32_t>();
  bool result = test_box_collision();
  env->write(static_cast<uint32_t>(result));
  env->commit(static_cast<uint32_t>(0));
  //env->commit(shaDigest(params.state));
  //env->commit(shaDigest(result.state));
  //env->commit(params.shot);
  //env->commit(static_cast<uint32_t>(result.hit));
}
