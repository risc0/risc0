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

PARALLEL_KERNEL(                 //
    evalCheckPoly,               //
    (PTR(Fp, out),               //
     CPTR(Fp, code),             //
     CPTR(Fp, data),             //
     CPTR(Fp, accum),            //
     CPTR(Fp, global),           //
     CPTR(Fp, rou),              //
     SIZE(count),                //
     CALC(po2, log2Ceil(count)), //
     REQ(1 << po2 == count)),
    {
      Fp4 ret = computePoly(code, data, accum, global, idx, count);
      Fp x = pow(rou[po2], idx);
      ret = ret * inv(pow(Fp(3) * x, (1 << (po2 - 2))) - 1);
      out[0 * count + idx] = ret.elems[0];
      out[1 * count + idx] = ret.elems[1];
      out[2 * count + idx] = ret.elems[2];
      out[3 * count + idx] = ret.elems[3];
    });
