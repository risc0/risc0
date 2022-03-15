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

PARALLEL_KERNEL(                                //
    shaRows,                                    //
    (PTR(ShaDigest, out),                       //
     CPTR(Fp, matrix),                          //
     CALC(count, out.size()),                   //
     CALC(colSize, matrix.size() / out.size()), //
     REQ(matrix.size() == colSize * count)),
    { out[idx] = shaHash(matrix + idx, colSize, count, false); })

PARALLEL_KERNEL(              //
    shaFold,                  //
    (PTR(ShaDigest, out),     //
     CPTR(ShaDigest, in),     //
     CALC(count, out.size()), //
     REQ(in.size() == 2 * out.size())),
    { out[idx] = shaHashPair(in[2 * idx], in[2 * idx + 1]); })

PARALLEL_KERNEL(                                //
    getRow,                                     //
    (PTR(Fp, out),                              //
     CPTR(Fp, matrix),                          //
     SIZE(offset),                              //
     CALC(count, out.size()),                   //
     CALC(rowSize, matrix.size() / out.size()), //
     REQ(offset < rowSize),                     //
     REQ(matrix.size() == rowSize * count)),
    { out[idx] = matrix[offset + idx * rowSize]; })
