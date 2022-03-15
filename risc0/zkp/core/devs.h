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

#ifndef RISCV
#define CPU
#endif // #ifndef RISCV

#ifdef RISCV
#include <cstddef>
#include <cstdint>
#define DEVSPEC  /**/
#define DEVADDR  /**/
#define DEVLOCAL /**/
#define CONSTSCALAR constexpr
#endif // #ifdef RISCV

#ifdef CPU
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#define DEVSPEC  /**/
#define DEVADDR  /**/
#define DEVLOCAL /**/
#define CONSTSCALAR constexpr
#endif // #ifdef CPU
