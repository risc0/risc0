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

PARALLEL_KERNEL(                        //
    friFold,                            //
    (PTR(Fp, out),                      //
     CPTR(Fp, in),                      //
     CPTR(Fp4, mixPtr),                 //
     CALC(count, out.size() / 4),       //
     REQ(out.size() == count * 4),      //
     REQ(in.size() == out.size() * 16), // 16 = kFriFold
     REQ(mixPtr.size() == 1)),
    {
      Fp4 mix = *mixPtr;
      Fp4 tot;
      Fp4 curMix(1);
      for (uint32_t i = 0; i < kFriFold; i++) {
        uint32_t rev_i = accel_rev32(i) >> (32 - 4); // 4 = log2Ceil(kFriFold))
        Fp4 val(in[0 * count * kFriFold + rev_i * count + idx],
                in[1 * count * kFriFold + rev_i * count + idx],
                in[2 * count * kFriFold + rev_i * count + idx],
                in[3 * count * kFriFold + rev_i * count + idx]);
        tot += curMix * val;
        curMix *= mix;
      }
      for (uint32_t i = 0; i < 4; i++) {
        out[count * i + idx] = tot.elems[i];
      }
    })
