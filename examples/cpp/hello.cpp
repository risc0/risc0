// Copyright 2023 RISC Zero, Inc.
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

#include <cstddef>
#include <cstdint>
#include <unistd.h>

// TODO: Provide these definitions in a header file for all zkvm C++ programs.
extern "C" {
  extern void sys_write(uint32_t fd, void* msg, uint32_t msglen);
  extern void sys_halt();
}

char msg[] = "Hello world!\n";
size_t msg_len = sizeof(msg) - 1;

int main()
{
  sys_write(STDOUT_FILENO, msg, msg_len);
  sys_halt();
}
