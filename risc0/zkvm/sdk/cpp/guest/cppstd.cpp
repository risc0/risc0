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

#include "risc0/zkvm/sdk/cpp/guest/risc0.h"

void* operator new(std::size_t count) {
  return malloc(count);
}

void* operator new[](std::size_t count) {
  return malloc(count);
}

void operator delete(void*) {
  // no-op
}

void operator delete[](void*) {
  // no-op
}

void operator delete(void*, unsigned int) {
  // no-op
}

void operator delete[](void*, unsigned int) {
  // no-op
}

namespace std {

void __throw_length_error(char const* msg) {
  risc0::fail(msg);
}

void __throw_bad_alloc() {
  risc0::fail("bad_alloc");
}

} // namespace std
