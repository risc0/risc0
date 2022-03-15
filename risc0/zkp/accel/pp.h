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

#pragma once

// Tiny collection of nasty preprocessor hacks

#define PP_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, N, ...) N
#define PP_RSEQ_N() 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define PP_PASS(...) __VA_ARGS__
#define PP_NARG_(...) PP_PASS(PP_PASS(PP_ARG_N)(__VA_ARGS__))
#define PP_NARG(...) PP_PASS(PP_PASS(PP_NARG_)(__VA_ARGS__, PP_RSEQ_N()))
#define PP_UNWRAP(...) __VA_ARGS__
#define PP_PASTE_(a, b) a##b
#define PP_PASTE(a, b) PP_PASTE_(a, b)
#define PP_APPLY_0(f) /**/
#define PP_APPLY_1(f, _1) f(_1)
#define PP_APPLY_2(f, _1, _2) f(_1) f(_2)
#define PP_APPLY_3(f, _1, _2, _3) f(_1) f(_2) f(_3)
#define PP_APPLY_4(f, _1, _2, _3, _4) f(_1) f(_2) f(_3) f(_4)
#define PP_APPLY_5(f, _1, _2, _3, _4, _5) f(_1) f(_2) f(_3) f(_4) f(_5)
#define PP_APPLY_6(f, _1, _2, _3, _4, _5, _6) f(_1) f(_2) f(_3) f(_4) f(_5) f(_6)
#define PP_APPLY_7(f, _1, _2, _3, _4, _5, _6, _7) f(_1) f(_2) f(_3) f(_4) f(_5) f(_6) f(_7)
#define PP_APPLY_8(f, _1, _2, _3, _4, _5, _6, _7, _8)                                              \
  f(_1) f(_2) f(_3) f(_4) f(_5) f(_6) f(_7) f(_8)
#define PP_APPLY_9(f, _1, _2, _3, _4, _5, _6, _7, _8, _9)                                          \
  f(_1) f(_2) f(_3) f(_4) f(_5) f(_6) f(_7) f(_8) f(_9)
#define PP_APPLY_10(f, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10)                                    \
  f(_1) f(_2) f(_3) f(_4) f(_5) f(_6) f(_7) f(_8) f(_9) f(_10)
#define PP_APPLY_11(f, _1, _2, _3, _4, _5, _6, _7, _8, _9, _11)                                    \
  f(_1) f(_2) f(_3) f(_4) f(_5) f(_6) f(_7) f(_8) f(_9) f(_10) f(_11)
#define PP_APPLY_12(f, _1, _2, _3, _4, _5, _6, _7, _8, _9, _11, _12)                               \
  f(_1) f(_2) f(_3) f(_4) f(_5) f(_6) f(_7) f(_8) f(_9) f(_10) f(_11) f(_12)
#define PP_APPLY_VA(func, ...)                                                                     \
  PP_PASS(PP_PASS(PP_PASTE)(PP_APPLY_, PP_PASS(PP_PASS(PP_NARG)(__VA_ARGS__)))(func, __VA_ARGS__))
#define PP_APPLY_LST(func, lst) PP_APPLY_VA(func, PP_UNWRAP lst)
