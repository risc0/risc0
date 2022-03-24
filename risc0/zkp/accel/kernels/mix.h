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
//
PARALLEL_KERNEL(             //
    mixPolyCoeffs,           //
    (PTR(Fp4, out),          //
     CPTR(Fp4, mixStart),    //
     CPTR(Fp4, mixPtr),      //
     CPTR(Fp, in),           //
     CPTR(uint32_t, combos), //
     SIZE(inSize),           //
     SIZE(count)),
    {
      Fp4 cur = *mixStart;
      Fp4 mix = *mixPtr;
      for (size_t i = 0; i < inSize; i++) {
        out[count * combos[i] + idx] += cur * in[count * i + idx];
        cur *= mix;
      }
    });
