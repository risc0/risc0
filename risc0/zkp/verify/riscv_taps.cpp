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

#include "risc0/zkp/verify/taps.h"

namespace risc0 {

TapSetRef getRiscVTaps() {
  static TapSet tapSet;
  static bool computed = false;
  if (!computed) {
    RegisterGroup accum = RegisterGroup::ACCUM;
    RegisterGroup code = RegisterGroup::CODE;
    RegisterGroup data = RegisterGroup::DATA;
#define tap(base, offset, back) tapSet.addTap(base, offset, back);
#define TAPS
#include "risc0/zkp/prove/step/step.cpp.inc"
    computed = true;
  }
  return tapSet.getRef();
}

} // namespace risc0
