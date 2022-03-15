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

#define ELTWISE_UNARY_KERNEL(type, name, expr)                                                     \
  PARALLEL_KERNEL(                                                                                 \
      eltwise##name##type,                                                                         \
      (PTR(type, oArr), CPTR(type, aArr), CALC(count, oArr.size()), REQ(count == aArr.size())),    \
      {                                                                                            \
        type a = aArr[idx];                                                                        \
        oArr[idx] = (expr);                                                                        \
      })

#define ELTWISE_BINARY_KERNEL(type, name, expr)                                                    \
  PARALLEL_KERNEL(eltwise##name##type,                                                             \
                  (PTR(type, oArr),                                                                \
                   CPTR(type, aArr),                                                               \
                   CPTR(type, bArr),                                                               \
                   CALC(count, oArr.size()),                                                       \
                   REQ(count == aArr.size()),                                                      \
                   REQ(count == bArr.size())),                                                     \
                  {                                                                                \
                    type a = aArr[idx];                                                            \
                    type b = bArr[idx];                                                            \
                    oArr[idx] = (expr);                                                            \
                  })

ELTWISE_BINARY_KERNEL(Fp, Add, a + b)
ELTWISE_BINARY_KERNEL(Fp, Sub, a - b)
ELTWISE_BINARY_KERNEL(Fp, Mul, a* b)
ELTWISE_UNARY_KERNEL(Fp, Neg, -a)
ELTWISE_UNARY_KERNEL(Fp, Inv, inv(a))
ELTWISE_UNARY_KERNEL(Fp, Copy, a)

ELTWISE_BINARY_KERNEL(Fp4, Add, a + b)
ELTWISE_BINARY_KERNEL(Fp4, Sub, a - b)
ELTWISE_BINARY_KERNEL(Fp4, Mul, a* b)
ELTWISE_UNARY_KERNEL(Fp4, Neg, -a)
ELTWISE_UNARY_KERNEL(Fp4, Inv, inv(a))
ELTWISE_UNARY_KERNEL(Fp4, Copy, a)

ELTWISE_UNARY_KERNEL(ShaDigest, Copy, a)

PARALLEL_KERNEL(                       //
    eltwiseSumFp4,                     //
    (PTR(Fp, oArr),                    //
     CPTR(Fp4, iArr),                  //
     CALC(count, oArr.size() / 4),     //
     CALC(toAdd, iArr.size() / count), //
     REQ(oArr.size() == count * 4),    //
     REQ(iArr.size() == count * toAdd)),
    {
      Fp4 tot;
      for (size_t i = 0; i < toAdd; i++) {
        tot += iArr[count * i + idx];
      }
      oArr[idx + 0 * count] = tot.elems[0];
      oArr[idx + 1 * count] = tot.elems[1];
      oArr[idx + 2 * count] = tot.elems[2];
      oArr[idx + 3 * count] = tot.elems[3];
    })

#undef ELTWISE_UNARY_KERNEL
#undef ELTWISE_BINARY_KERNEL
