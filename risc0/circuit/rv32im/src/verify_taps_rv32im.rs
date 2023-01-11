// Copyright 2022 RISC Zero, Inc.
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

// This code is automatically generated

#![cfg_attr(not(target_os = "zkvm"), allow(dead_code, unused_variables))]

const EXT_ELEM_SIZE: usize = 4;

// TODO: Don't extend these field elements; instead, ffpu should be
// aware of whether field elements are extension elements or not, but
// cirgen needs to be aware of it first.
const DATA: &[u32] = &[];

const CODE: &[u32] = &[
    0x00000100, // %0 = get($0x0000, 0x01): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":115:0)
    0x00010100, // %1 = get($0x0001, 0x01): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":115:0)
    0x00020100, // %2 = get($0x0002, 0x01): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":115:0)
    0x00030100, // %3 = get($0x0003, 0x01): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":115:0)
    0x00000200, // %4 = get($0x0000, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00010200, // %5 = get($0x0001, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00020200, // %6 = get($0x0002, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00030200, // %7 = get($0x0003, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00040200, // %8 = get($0x0004, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00050200, // %9 = get($0x0005, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00060200, // %10 = get($0x0006, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00070200, // %11 = get($0x0007, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00080200, // %12 = get($0x0008, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00090200, // %13 = get($0x0009, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x000a0200, // %14 = get($0x000a, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x000b0200, // %15 = get($0x000b, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x000c0200, // %16 = get($0x000c, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x000d0200, // %17 = get($0x000d, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x000e0200, // %18 = get($0x000e, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x000f0200, // %19 = get($0x000f, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00100200, // %20 = get($0x0010, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00110200, // %21 = get($0x0011, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00120200, // %22 = get($0x0012, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00130200, // %23 = get($0x0013, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00140200, // %24 = get($0x0014, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00150200, // %25 = get($0x0015, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00160200, // %26 = get($0x0016, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00170200, // %27 = get($0x0017, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":123:0)
    0x00000300, // %28 = get($0x0000, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00010300, // %29 = get($0x0001, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00020300, // %30 = get($0x0002, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00030300, // %31 = get($0x0003, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00040300, // %32 = get($0x0004, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00050300, // %33 = get($0x0005, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00060300, // %34 = get($0x0006, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00070300, // %35 = get($0x0007, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00080300, // %36 = get($0x0008, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00090300, // %37 = get($0x0009, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x000a0300, // %38 = get($0x000a, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x000b0300, // %39 = get($0x000b, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x000c0300, // %40 = get($0x000c, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x000d0300, // %41 = get($0x000d, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x000e0300, // %42 = get($0x000e, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x000f0300, // %43 = get($0x000f, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00000400, // %44 = get($0x0000, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00010400, // %45 = get($0x0001, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00020400, // %46 = get($0x0002, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00030400, // %47 = get($0x0003, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00040400, // %48 = get($0x0004, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00050400, // %49 = get($0x0005, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00060400, // %50 = get($0x0006, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00070400, // %51 = get($0x0007, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00080400, // %52 = get($0x0008, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00090400, // %53 = get($0x0009, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x000a0400, // %54 = get($0x000a, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x000b0400, // %55 = get($0x000b, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x000c0400, // %56 = get($0x000c, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x000d0400, // %57 = get($0x000d, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x000e0400, // %58 = get($0x000e, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x000f0400, // %59 = get($0x000f, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00100400, // %60 = get($0x0010, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00110400, // %61 = get($0x0011, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00120400, // %62 = get($0x0012, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00130400, // %63 = get($0x0013, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00140400, // %64 = get($0x0014, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00150400, // %65 = get($0x0015, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00160400, // %66 = get($0x0016, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00170400, // %67 = get($0x0017, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00180400, // %68 = get($0x0018, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00190400, // %69 = get($0x0019, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x001a0400, // %70 = get($0x001a, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x001b0400, // %71 = get($0x001b, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x001c0400, // %72 = get($0x001c, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x001d0400, // %73 = get($0x001d, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x001e0400, // %74 = get($0x001e, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x001f0400, // %75 = get($0x001f, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00200400, // %76 = get($0x0020, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00210400, // %77 = get($0x0021, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00220400, // %78 = get($0x0022, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00230400, // %79 = get($0x0023, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00240400, // %80 = get($0x0024, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00250400, // %81 = get($0x0025, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00260400, // %82 = get($0x0026, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00270400, // %83 = get($0x0027, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":128:0)
    0x00000500, // %84 = get($0x0000, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00010500, // %85 = get($0x0001, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00020500, // %86 = get($0x0002, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00030500, // %87 = get($0x0003, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00040500, // %88 = get($0x0004, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00050500, // %89 = get($0x0005, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00060500, // %90 = get($0x0006, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00070500, // %91 = get($0x0007, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00080500, // %92 = get($0x0008, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00090500, // %93 = get($0x0009, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x000a0500, // %94 = get($0x000a, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x000b0500, // %95 = get($0x000b, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x000c0500, // %96 = get($0x000c, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x000d0500, // %97 = get($0x000d, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x000e0500, // %98 = get($0x000e, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00000600, // %99 = get($0x0000, 0x06): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0)
    0x00010600, /* %100 = get($0x0001, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00020600, /* %101 = get($0x0002, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00030600, /* %102 = get($0x0003, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00040600, /* %103 = get($0x0004, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00050600, /* %104 = get($0x0005, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00060600, /* %105 = get($0x0006, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00070600, /* %106 = get($0x0007, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00080600, /* %107 = get($0x0008, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00090600, /* %108 = get($0x0009, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000a0600, /* %109 = get($0x000a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000b0600, /* %110 = get($0x000b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000c0600, /* %111 = get($0x000c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000d0600, /* %112 = get($0x000d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000e0600, /* %113 = get($0x000e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000f0600, /* %114 = get($0x000f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00100600, /* %115 = get($0x0010, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00110600, /* %116 = get($0x0011, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00120600, /* %117 = get($0x0012, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00130600, /* %118 = get($0x0013, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00140600, /* %119 = get($0x0014, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00150600, /* %120 = get($0x0015, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00160600, /* %121 = get($0x0016, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00170600, /* %122 = get($0x0017, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00180600, /* %123 = get($0x0018, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00190600, /* %124 = get($0x0019, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001a0600, /* %125 = get($0x001a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001b0600, /* %126 = get($0x001b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001c0600, /* %127 = get($0x001c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001d0600, /* %128 = get($0x001d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001e0600, /* %129 = get($0x001e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001f0600, /* %130 = get($0x001f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00200600, /* %131 = get($0x0020, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00210600, /* %132 = get($0x0021, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00220600, /* %133 = get($0x0022, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00230600, /* %134 = get($0x0023, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00240600, /* %135 = get($0x0024, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00250600, /* %136 = get($0x0025, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00260600, /* %137 = get($0x0026, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00270600, /* %138 = get($0x0027, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00280600, /* %139 = get($0x0028, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00290600, /* %140 = get($0x0029, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002a0600, /* %141 = get($0x002a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002b0600, /* %142 = get($0x002b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002c0600, /* %143 = get($0x002c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002d0600, /* %144 = get($0x002d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002e0600, /* %145 = get($0x002e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002f0600, /* %146 = get($0x002f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00300600, /* %147 = get($0x0030, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00310600, /* %148 = get($0x0031, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00320600, /* %149 = get($0x0032, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00330600, /* %150 = get($0x0033, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00340600, /* %151 = get($0x0034, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00350600, /* %152 = get($0x0035, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00360600, /* %153 = get($0x0036, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00370600, /* %154 = get($0x0037, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00380600, /* %155 = get($0x0038, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00390600, /* %156 = get($0x0039, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003a0600, /* %157 = get($0x003a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003b0600, /* %158 = get($0x003b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003c0600, /* %159 = get($0x003c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003d0600, /* %160 = get($0x003d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003e0600, /* %161 = get($0x003e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003f0600, /* %162 = get($0x003f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00400600, /* %163 = get($0x0040, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00410600, /* %164 = get($0x0041, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00420600, /* %165 = get($0x0042, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00430600, /* %166 = get($0x0043, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00440600, /* %167 = get($0x0044, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00450600, /* %168 = get($0x0045, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00460600, /* %169 = get($0x0046, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00470600, /* %170 = get($0x0047, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00480600, /* %171 = get($0x0048, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00490600, /* %172 = get($0x0049, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004a0600, /* %173 = get($0x004a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004b0600, /* %174 = get($0x004b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004c0600, /* %175 = get($0x004c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004d0600, /* %176 = get($0x004d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004e0600, /* %177 = get($0x004e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004f0600, /* %178 = get($0x004f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00500600, /* %179 = get($0x0050, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00510600, /* %180 = get($0x0051, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00520600, /* %181 = get($0x0052, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00530600, /* %182 = get($0x0053, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00540600, /* %183 = get($0x0054, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00550600, /* %184 = get($0x0055, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00560600, /* %185 = get($0x0056, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00570600, /* %186 = get($0x0057, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00580600, /* %187 = get($0x0058, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00590600, /* %188 = get($0x0059, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005a0600, /* %189 = get($0x005a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005b0600, /* %190 = get($0x005b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005c0600, /* %191 = get($0x005c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005d0600, /* %192 = get($0x005d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005e0600, /* %193 = get($0x005e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005f0600, /* %194 = get($0x005f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00600600, /* %195 = get($0x0060, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00610600, /* %196 = get($0x0061, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00620600, /* %197 = get($0x0062, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00630600, /* %198 = get($0x0063, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00640600, /* %199 = get($0x0064, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00650600, /* %200 = get($0x0065, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00660600, /* %201 = get($0x0066, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00670600, /* %202 = get($0x0067, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00680600, /* %203 = get($0x0068, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00690600, /* %204 = get($0x0069, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006a0600, /* %205 = get($0x006a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006b0600, /* %206 = get($0x006b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006c0600, /* %207 = get($0x006c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006d0600, /* %208 = get($0x006d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006e0600, /* %209 = get($0x006e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006f0600, /* %210 = get($0x006f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00700600, /* %211 = get($0x0070, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00710600, /* %212 = get($0x0071, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00720600, /* %213 = get($0x0072, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00730600, /* %214 = get($0x0073, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00740600, /* %215 = get($0x0074, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00750600, /* %216 = get($0x0075, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00760600, /* %217 = get($0x0076, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00770600, /* %218 = get($0x0077, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00780600, /* %219 = get($0x0078, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00790600, /* %220 = get($0x0079, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007a0600, /* %221 = get($0x007a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007b0600, /* %222 = get($0x007b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007c0600, /* %223 = get($0x007c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007d0600, /* %224 = get($0x007d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007e0600, /* %225 = get($0x007e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007f0600, /* %226 = get($0x007f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00800600, /* %227 = get($0x0080, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00810600, /* %228 = get($0x0081, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00820600, /* %229 = get($0x0082, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00830600, /* %230 = get($0x0083, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00840600, /* %231 = get($0x0084, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00850600, /* %232 = get($0x0085, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00860600, /* %233 = get($0x0086, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00870600, /* %234 = get($0x0087, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00880600, /* %235 = get($0x0088, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00890600, /* %236 = get($0x0089, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008a0600, /* %237 = get($0x008a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008b0600, /* %238 = get($0x008b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008c0600, /* %239 = get($0x008c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008d0600, /* %240 = get($0x008d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008e0600, /* %241 = get($0x008e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008f0600, /* %242 = get($0x008f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00900600, /* %243 = get($0x0090, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00910600, /* %244 = get($0x0091, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00920600, /* %245 = get($0x0092, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00930600, /* %246 = get($0x0093, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00940600, /* %247 = get($0x0094, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00950600, /* %248 = get($0x0095, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00960600, /* %249 = get($0x0096, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00970600, /* %250 = get($0x0097, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00980600, /* %251 = get($0x0098, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00990600, /* %252 = get($0x0099, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009a0600, /* %253 = get($0x009a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009b0600, /* %254 = get($0x009b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009c0600, /* %255 = get($0x009c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009d0600, /* %256 = get($0x009d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009e0600, /* %257 = get($0x009e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009f0600, /* %258 = get($0x009f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a00600, /* %259 = get($0x00a0, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a10600, /* %260 = get($0x00a1, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a20600, /* %261 = get($0x00a2, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a30600, /* %262 = get($0x00a3, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a40600, /* %263 = get($0x00a4, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a50600, /* %264 = get($0x00a5, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a60600, /* %265 = get($0x00a6, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a70600, /* %266 = get($0x00a7, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a80600, /* %267 = get($0x00a8, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a90600, /* %268 = get($0x00a9, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00aa0600, /* %269 = get($0x00aa, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ab0600, /* %270 = get($0x00ab, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ac0600, /* %271 = get($0x00ac, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ad0600, /* %272 = get($0x00ad, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ae0600, /* %273 = get($0x00ae, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00af0600, /* %274 = get($0x00af, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b00600, /* %275 = get($0x00b0, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b10600, /* %276 = get($0x00b1, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b20600, /* %277 = get($0x00b2, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b30600, /* %278 = get($0x00b3, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b40600, /* %279 = get($0x00b4, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b50600, /* %280 = get($0x00b5, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b60600, /* %281 = get($0x00b6, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b70600, /* %282 = get($0x00b7, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b80600, /* %283 = get($0x00b8, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b90600, /* %284 = get($0x00b9, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ba0600, /* %285 = get($0x00ba, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00bb0600, /* %286 = get($0x00bb, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00bc0600, /* %287 = get($0x00bc, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00bd0600, /* %288 = get($0x00bd, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00be0600, /* %289 = get($0x00be, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00bf0600, /* %290 = get($0x00bf, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c00600, /* %291 = get($0x00c0, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c10600, /* %292 = get($0x00c1, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c20600, /* %293 = get($0x00c2, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c30600, /* %294 = get($0x00c3, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c40600, /* %295 = get($0x00c4, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c50600, /* %296 = get($0x00c5, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c60600, /* %297 = get($0x00c6, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c70600, /* %298 = get($0x00c7, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c80600, /* %299 = get($0x00c8, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c90600, /* %300 = get($0x00c9, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ca0600, /* %301 = get($0x00ca, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00cb0600, /* %302 = get($0x00cb, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00cc0600, /* %303 = get($0x00cc, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00cd0600, /* %304 = get($0x00cd, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ce0600, /* %305 = get($0x00ce, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00cf0600, /* %306 = get($0x00cf, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d00600, /* %307 = get($0x00d0, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d10600, /* %308 = get($0x00d1, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d20600, /* %309 = get($0x00d2, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d30600, /* %310 = get($0x00d3, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d40600, /* %311 = get($0x00d4, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d50600, /* %312 = get($0x00d5, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000000b7, // %313 = mul(%0, %45): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x002c04e5, // %314 = add(%44, %313): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x00000003, // %315 = mul(%0, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x013b00bb, // %316 = mul(%315, %46): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x013a04f1, // %317 = add(%314, %316): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x013b0003, // %318 = mul(%315, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x013e00bf, // %319 = mul(%318, %47): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x013d04fd, // %320 = add(%317, %319): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x013e0003, // %321 = mul(%318, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014100c3, // %322 = mul(%321, %48): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01400509, // %323 = add(%320, %322): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01410003, // %324 = mul(%321, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014400c7, // %325 = mul(%324, %49): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01430515, // %326 = add(%323, %325): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01440003, // %327 = mul(%324, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014700cb, // %328 = mul(%327, %50): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01460521, // %329 = add(%326, %328): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01470003, // %330 = mul(%327, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014a00cf, // %331 = mul(%330, %51): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0149052d, // %332 = add(%329, %331): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x014a0003, // %333 = mul(%330, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014d00d3, // %334 = mul(%333, %52): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x014d0003, // %335 = mul(%333, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014f00d7, // %336 = mul(%335, %53): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x014e0541, // %337 = add(%334, %336): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x014f0003, // %338 = mul(%335, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015200db, // %339 = mul(%338, %54): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0151054d, // %340 = add(%337, %339): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01520003, // %341 = mul(%338, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015500df, // %342 = mul(%341, %55): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01540559, // %343 = add(%340, %342): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01550003, // %344 = mul(%341, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015800e3, // %345 = mul(%344, %56): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01570565, // %346 = add(%343, %345): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01580003, // %347 = mul(%344, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015b00e7, // %348 = mul(%347, %57): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x015a0571, // %349 = add(%346, %348): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x015b0003, // %350 = mul(%347, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015e00eb, // %351 = mul(%350, %58): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x015d057d, // %352 = add(%349, %351): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x015e0003, // %353 = mul(%350, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016100ef, // %354 = mul(%353, %59): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01600589, // %355 = add(%352, %354): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01610003, // %356 = mul(%353, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016400f3, // %357 = mul(%356, %60): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01630595, // %358 = add(%355, %357): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01640003, // %359 = mul(%356, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016700f7, // %360 = mul(%359, %61): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x016605a1, // %361 = add(%358, %360): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01670003, // %362 = mul(%359, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016a00fb, // %363 = mul(%362, %62): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x016905ad, // %364 = add(%361, %363): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x016a0003, // %365 = mul(%362, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016d00ff, // %366 = mul(%365, %63): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x016c05b9, // %367 = add(%364, %366): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x016d0003, // %368 = mul(%365, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01700103, // %369 = mul(%368, %64): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x016f05c5, // %370 = add(%367, %369): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01700003, // %371 = mul(%368, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01730107, // %372 = mul(%371, %65): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017205d1, // %373 = add(%370, %372): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01730003, // %374 = mul(%371, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0176010b, // %375 = mul(%374, %66): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017505dd, // %376 = add(%373, %375): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01760003, // %377 = mul(%374, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0179010f, // %378 = mul(%377, %67): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017805e9, // %379 = add(%376, %378): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01790003, // %380 = mul(%377, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x017c0113, // %381 = mul(%380, %68): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017b05f5, // %382 = add(%379, %381): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x017c0003, // %383 = mul(%380, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x017f0117, // %384 = mul(%383, %69): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017e0601, // %385 = add(%382, %384): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x017f0003, // %386 = mul(%383, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0182011b, // %387 = mul(%386, %70): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0181060d, // %388 = add(%385, %387): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01820003, // %389 = mul(%386, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0185011f, // %390 = mul(%389, %71): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01840619, // %391 = add(%388, %390): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01850003, // %392 = mul(%389, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01880123, // %393 = mul(%392, %72): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01870625, // %394 = add(%391, %393): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01880003, // %395 = mul(%392, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x018b0127, // %396 = mul(%395, %73): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x018a0631, // %397 = add(%394, %396): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x018b0003, // %398 = mul(%395, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x018e012b, // %399 = mul(%398, %74): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x018d063d, // %400 = add(%397, %399): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x018e0003, // %401 = mul(%398, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0191012f, // %402 = mul(%401, %75): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01900649, // %403 = add(%400, %402): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01910003, // %404 = mul(%401, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01940133, // %405 = mul(%404, %76): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01930655, // %406 = add(%403, %405): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01940003, // %407 = mul(%404, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01970137, // %408 = mul(%407, %77): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01960661, // %409 = add(%406, %408): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01970003, // %410 = mul(%407, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x019a013b, // %411 = mul(%410, %78): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0199066d, // %412 = add(%409, %411): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x019a0003, // %413 = mul(%410, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x019d013f, // %414 = mul(%413, %79): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x019c0679, // %415 = add(%412, %414): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x019d0003, // %416 = mul(%413, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01a00143, // %417 = mul(%416, %80): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x019f0685, // %418 = add(%415, %417): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01a00003, // %419 = mul(%416, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01a30147, // %420 = mul(%419, %81): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01a20691, // %421 = add(%418, %420): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01a30003, // %422 = mul(%419, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01a6014b, // %423 = mul(%422, %82): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01a5069d, // %424 = add(%421, %423): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01a60003, // %425 = mul(%422, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01a9014f, // %426 = mul(%425, %83): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01a806a9, // %427 = add(%424, %426): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01a90003, // %428 = mul(%425, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ac0153, // %429 = mul(%428, %84): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ab06b5, // %430 = add(%427, %429): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ac0003, // %431 = mul(%428, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01af0157, // %432 = mul(%431, %85): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ae06c1, // %433 = add(%430, %432): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01af0003, // %434 = mul(%431, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01b2015b, // %435 = mul(%434, %86): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x014c06cd, // %436 = add(%332, %435): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01b20003, // %437 = mul(%434, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01b5015f, // %438 = mul(%437, %87): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01b106d9, // %439 = add(%433, %438): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01b50003, // %440 = mul(%437, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01b80163, // %441 = mul(%440, %88): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01b706e5, // %442 = add(%439, %441): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01b80003, // %443 = mul(%440, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01bb0167, // %444 = mul(%443, %89): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01b406f1, // %445 = add(%436, %444): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01bb0003, // %446 = mul(%443, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01be016b, // %447 = mul(%446, %90): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ba06fd, // %448 = add(%442, %447): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01be0003, // %449 = mul(%446, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01c1016f, // %450 = mul(%449, %91): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01c00709, // %451 = add(%448, %450): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01c10003, // %452 = mul(%449, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01c40173, // %453 = mul(%452, %92): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01c30715, // %454 = add(%451, %453): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01c40003, // %455 = mul(%452, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01c70177, // %456 = mul(%455, %93): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01c60721, // %457 = add(%454, %456): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01c70003, // %458 = mul(%455, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ca017b, // %459 = mul(%458, %94): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01c9072d, // %460 = add(%457, %459): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ca0003, // %461 = mul(%458, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01cd017f, // %462 = mul(%461, %95): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01cc0739, // %463 = add(%460, %462): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01cd0003, // %464 = mul(%461, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01d00183, // %465 = mul(%464, %96): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01cf0745, // %466 = add(%463, %465): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01d00003, // %467 = mul(%464, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01d30187, // %468 = mul(%467, %97): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01d20751, // %469 = add(%466, %468): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01d30003, // %470 = mul(%467, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01d6018b, // %471 = mul(%470, %98): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01d5075d, // %472 = add(%469, %471): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01d60003, // %473 = mul(%470, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01d9018f, // %474 = mul(%473, %99): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01bd0769, // %475 = add(%445, %474): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01d90003, // %476 = mul(%473, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01dc0193, // %477 = mul(%476, %100): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01db0775, // %478 = add(%475, %477): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01dc0003, // %479 = mul(%476, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01df0197, // %480 = mul(%479, %101): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01de0781, // %481 = add(%478, %480): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01df0003, // %482 = mul(%479, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01e2019b, // %483 = mul(%482, %102): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01e1078d, // %484 = add(%481, %483): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01e20003, // %485 = mul(%482, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01e5019f, // %486 = mul(%485, %103): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01e40799, // %487 = add(%484, %486): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01e50003, // %488 = mul(%485, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01e801a3, // %489 = mul(%488, %104): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01e707a5, // %490 = add(%487, %489): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01e80003, // %491 = mul(%488, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01eb01a7, // %492 = mul(%491, %105): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ea07b1, // %493 = add(%490, %492): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01eb0003, // %494 = mul(%491, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ee01ab, // %495 = mul(%494, %106): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ed07bd, // %496 = add(%493, %495): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ee0003, // %497 = mul(%494, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01f101af, // %498 = mul(%497, %107): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01f007c9, // %499 = add(%496, %498): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01f10003, // %500 = mul(%497, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01f401b3, // %501 = mul(%500, %108): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01d807d5, // %502 = add(%472, %501): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01f40003, // %503 = mul(%500, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01f701b7, // %504 = mul(%503, %109): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01f307e1, // %505 = add(%499, %504): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01f70003, // %506 = mul(%503, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01fa01bb, // %507 = mul(%506, %110): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01f907ed, // %508 = add(%505, %507): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01fa0003, // %509 = mul(%506, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01fd01bf, // %510 = mul(%509, %111): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01fc07f9, // %511 = add(%508, %510): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01fd0003, // %512 = mul(%509, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020001c3, // %513 = mul(%512, %112): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01f60805, // %514 = add(%502, %513): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02000003, // %515 = mul(%512, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020301c7, // %516 = mul(%515, %113): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02020811, // %517 = add(%514, %516): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02030003, // %518 = mul(%515, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020601cb, // %519 = mul(%518, %114): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0205081d, // %520 = add(%517, %519): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02060003, // %521 = mul(%518, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020901cf, // %522 = mul(%521, %115): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02080829, // %523 = add(%520, %522): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02090003, // %524 = mul(%521, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020c01d3, // %525 = mul(%524, %116): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x020b0835, // %526 = add(%523, %525): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x020c0003, // %527 = mul(%524, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020f01d7, // %528 = mul(%527, %117): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x020e0841, // %529 = add(%526, %528): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x020f0003, // %530 = mul(%527, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021201db, // %531 = mul(%530, %118): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02120003, // %532 = mul(%530, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021401df, // %533 = mul(%532, %119): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02130855, // %534 = add(%531, %533): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02140003, // %535 = mul(%532, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021701e3, // %536 = mul(%535, %120): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02160861, // %537 = add(%534, %536): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02170003, // %538 = mul(%535, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021a01e7, // %539 = mul(%538, %121): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0219086d, // %540 = add(%537, %539): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x021a0003, // %541 = mul(%538, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021d01eb, // %542 = mul(%541, %122): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x021c0879, // %543 = add(%540, %542): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x021d0003, // %544 = mul(%541, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022001ef, // %545 = mul(%544, %123): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x021f0885, // %546 = add(%543, %545): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02200003, // %547 = mul(%544, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022301f3, // %548 = mul(%547, %124): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02230003, // %549 = mul(%547, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022501f7, // %550 = mul(%549, %125): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02240899, // %551 = add(%548, %550): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02250003, // %552 = mul(%549, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022801fb, // %553 = mul(%552, %126): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x022708a5, // %554 = add(%551, %553): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02280003, // %555 = mul(%552, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022b01ff, // %556 = mul(%555, %127): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x022a08b1, // %557 = add(%554, %556): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x022b0003, // %558 = mul(%555, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022e0203, // %559 = mul(%558, %128): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x022d08bd, // %560 = add(%557, %559): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x022e0003, // %561 = mul(%558, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02310207, // %562 = mul(%561, %129): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023008c9, // %563 = add(%560, %562): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02310003, // %564 = mul(%561, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0234020b, // %565 = mul(%564, %130): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023308d5, // %566 = add(%563, %565): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02340003, // %567 = mul(%564, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0237020f, // %568 = mul(%567, %131): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023608e1, // %569 = add(%566, %568): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02370003, // %570 = mul(%567, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x023a0213, // %571 = mul(%570, %132): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023908ed, // %572 = add(%569, %571): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x023a0003, // %573 = mul(%570, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x023d0217, // %574 = mul(%573, %133): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023c08f9, // %575 = add(%572, %574): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x023d0003, // %576 = mul(%573, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0240021b, // %577 = mul(%576, %134): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023f0905, // %578 = add(%575, %577): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02400003, // %579 = mul(%576, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0243021f, // %580 = mul(%579, %135): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02420911, // %581 = add(%578, %580): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02430003, // %582 = mul(%579, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02460223, // %583 = mul(%582, %136): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0222091d, // %584 = add(%546, %583): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02460003, // %585 = mul(%582, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02490227, // %586 = mul(%585, %137): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02480929, // %587 = add(%584, %586): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02490003, // %588 = mul(%585, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x024c022b, // %589 = mul(%588, %138): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x024b0935, // %590 = add(%587, %589): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x024c0003, // %591 = mul(%588, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x024f022f, // %592 = mul(%591, %139): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x024e0941, // %593 = add(%590, %592): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x024f0003, // %594 = mul(%591, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02520233, // %595 = mul(%594, %140): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0211094d, // %596 = add(%529, %595): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02520003, // %597 = mul(%594, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02550237, // %598 = mul(%597, %141): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02540959, // %599 = add(%596, %598): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02550003, // %600 = mul(%597, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0258023b, // %601 = mul(%600, %142): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02570965, // %602 = add(%599, %601): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02580003, // %603 = mul(%600, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x025b023f, // %604 = mul(%603, %143): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x025a0971, // %605 = add(%602, %604): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x025b0003, // %606 = mul(%603, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x025e0243, // %607 = mul(%606, %144): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x025d097d, // %608 = add(%605, %607): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x025e0003, // %609 = mul(%606, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02610247, // %610 = mul(%609, %145): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02600989, // %611 = add(%608, %610): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02610003, // %612 = mul(%609, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0264024b, // %613 = mul(%612, %146): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02630995, // %614 = add(%611, %613): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02640003, // %615 = mul(%612, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0267024f, // %616 = mul(%615, %147): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x026609a1, // %617 = add(%614, %616): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02670003, // %618 = mul(%615, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x026a0253, // %619 = mul(%618, %148): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x026909ad, // %620 = add(%617, %619): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x026a0003, // %621 = mul(%618, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x026d0257, // %622 = mul(%621, %149): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ff09b9, // %623 = add(%511, %622): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x026d0003, // %624 = mul(%621, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0270025b, // %625 = mul(%624, %150): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x026f09c5, // %626 = add(%623, %625): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02700003, // %627 = mul(%624, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0273025f, // %628 = mul(%627, %151): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x026c09d1, // %629 = add(%620, %628): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02730003, // %630 = mul(%627, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02760263, // %631 = mul(%630, %152): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027509dd, // %632 = add(%629, %631): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02760003, // %633 = mul(%630, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02790267, // %634 = mul(%633, %153): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027809e9, // %635 = add(%632, %634): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02790003, // %636 = mul(%633, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x027c026b, // %637 = mul(%636, %154): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027b09f5, // %638 = add(%635, %637): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x027c0003, // %639 = mul(%636, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x027f026f, // %640 = mul(%639, %155): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027e0a01, // %641 = add(%638, %640): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x027f0003, // %642 = mul(%639, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02820273, // %643 = mul(%642, %156): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02810a0d, // %644 = add(%641, %643): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02820003, // %645 = mul(%642, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02850277, // %646 = mul(%645, %157): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02840a19, // %647 = add(%644, %646): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02850003, // %648 = mul(%645, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0288027b, // %649 = mul(%648, %158): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02870a25, // %650 = add(%647, %649): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02880003, // %651 = mul(%648, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x028b027f, // %652 = mul(%651, %159): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x028a0a31, // %653 = add(%650, %652): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x028b0003, // %654 = mul(%651, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x028e0283, // %655 = mul(%654, %160): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x028d0a3d, // %656 = add(%653, %655): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x028e0003, // %657 = mul(%654, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02910287, // %658 = mul(%657, %161): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02900a49, // %659 = add(%656, %658): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02910003, // %660 = mul(%657, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0294028b, // %661 = mul(%660, %162): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02930a55, // %662 = add(%659, %661): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02940003, // %663 = mul(%660, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0297028f, // %664 = mul(%663, %163): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02960a61, // %665 = add(%662, %664): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02970003, // %666 = mul(%663, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x029a0293, // %667 = mul(%666, %164): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02990a6d, // %668 = add(%665, %667): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x029a0003, // %669 = mul(%666, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x029d0297, // %670 = mul(%669, %165): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x029c0a79, // %671 = add(%668, %670): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x029d0003, // %672 = mul(%669, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02a0029b, // %673 = mul(%672, %166): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x029f0a85, // %674 = add(%671, %673): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02a00003, // %675 = mul(%672, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02a3029f, // %676 = mul(%675, %167): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02a20a91, // %677 = add(%674, %676): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02a30003, // %678 = mul(%675, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02a602a3, // %679 = mul(%678, %168): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02a50a9d, // %680 = add(%677, %679): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02a60003, // %681 = mul(%678, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02a902a7, // %682 = mul(%681, %169): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02a80aa9, // %683 = add(%680, %682): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02a90003, // %684 = mul(%681, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ac02ab, // %685 = mul(%684, %170): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ab0ab5, // %686 = add(%683, %685): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ac0003, // %687 = mul(%684, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02af02af, // %688 = mul(%687, %171): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02720ac1, // %689 = add(%626, %688): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02af0003, // %690 = mul(%687, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02b202b3, // %691 = mul(%690, %172): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02b10acd, // %692 = add(%689, %691): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02b20003, // %693 = mul(%690, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02b502b7, // %694 = mul(%693, %173): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ae0ad9, // %695 = add(%686, %694): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02b50003, // %696 = mul(%693, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02b802bb, // %697 = mul(%696, %174): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02b70ae5, // %698 = add(%695, %697): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02b80003, // %699 = mul(%696, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02bb02bf, // %700 = mul(%699, %175): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ba0af1, // %701 = add(%698, %700): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02bb0003, // %702 = mul(%699, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02be02c3, // %703 = mul(%702, %176): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02bd0afd, // %704 = add(%701, %703): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02be0003, // %705 = mul(%702, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02c102c7, // %706 = mul(%705, %177): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02c00b09, // %707 = add(%704, %706): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02c10003, // %708 = mul(%705, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02c402cb, // %709 = mul(%708, %178): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02c30b15, // %710 = add(%707, %709): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02c40003, // %711 = mul(%708, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02c702cf, // %712 = mul(%711, %179): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02c60b21, // %713 = add(%710, %712): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02c70003, // %714 = mul(%711, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ca02d3, // %715 = mul(%714, %180): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02c90b2d, // %716 = add(%713, %715): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ca0003, // %717 = mul(%714, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02cd02d7, // %718 = mul(%717, %181): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02510b39, // %719 = add(%593, %718): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02cd0003, // %720 = mul(%717, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02d002db, // %721 = mul(%720, %182): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02cf0b45, // %722 = add(%719, %721): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02d00003, // %723 = mul(%720, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02d302df, // %724 = mul(%723, %183): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02d20b51, // %725 = add(%722, %724): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02d30003, // %726 = mul(%723, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02d602e3, // %727 = mul(%726, %184): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02d50b5d, // %728 = add(%725, %727): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02d60003, // %729 = mul(%726, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02d902e7, // %730 = mul(%729, %185): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02d80b69, // %731 = add(%728, %730): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02d90003, // %732 = mul(%729, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02dc02eb, // %733 = mul(%732, %186): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02db0b75, // %734 = add(%731, %733): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02dc0003, // %735 = mul(%732, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02df02ef, // %736 = mul(%735, %187): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02de0b81, // %737 = add(%734, %736): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02df0003, // %738 = mul(%735, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02e202f3, // %739 = mul(%738, %188): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02e10b8d, // %740 = add(%737, %739): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02e20003, // %741 = mul(%738, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02e502f7, // %742 = mul(%741, %189): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02e40b99, // %743 = add(%740, %742): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02e50003, // %744 = mul(%741, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02e802fb, // %745 = mul(%744, %190): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02e70ba5, // %746 = add(%743, %745): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02e80003, // %747 = mul(%744, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02eb02ff, // %748 = mul(%747, %191): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02cc0bb1, // %749 = add(%716, %748): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02eb0003, // %750 = mul(%747, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ee0303, // %751 = mul(%750, %192): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ed0bbd, // %752 = add(%749, %751): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ee0003, // %753 = mul(%750, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02f10307, // %754 = mul(%753, %193): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02f00bc9, // %755 = add(%752, %754): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02f10003, // %756 = mul(%753, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02f4030b, // %757 = mul(%756, %194): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02b40bd5, // %758 = add(%692, %757): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02f40003, // %759 = mul(%756, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02f7030f, // %760 = mul(%759, %195): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02f60be1, // %761 = add(%758, %760): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02f70003, // %762 = mul(%759, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02fa0313, // %763 = mul(%762, %196): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02f90bed, // %764 = add(%761, %763): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02fa0003, // %765 = mul(%762, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02fd0317, // %766 = mul(%765, %197): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02fc0bf9, // %767 = add(%764, %766): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02fd0003, // %768 = mul(%765, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0300031b, // %769 = mul(%768, %198): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ff0c05, // %770 = add(%767, %769): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03000003, // %771 = mul(%768, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0303031f, // %772 = mul(%771, %199): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03020c11, // %773 = add(%770, %772): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03030003, // %774 = mul(%771, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03060323, // %775 = mul(%774, %200): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03050c1d, // %776 = add(%773, %775): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03060003, // %777 = mul(%774, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03090327, // %778 = mul(%777, %201): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03080c29, // %779 = add(%776, %778): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03090003, // %780 = mul(%777, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x030c032b, // %781 = mul(%780, %202): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x030b0c35, // %782 = add(%779, %781): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x030c0003, // %783 = mul(%780, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x030f032f, // %784 = mul(%783, %203): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x030e0c41, // %785 = add(%782, %784): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x030f0003, // %786 = mul(%783, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03120333, // %787 = mul(%786, %204): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03110c4d, // %788 = add(%785, %787): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03120003, // %789 = mul(%786, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03150337, // %790 = mul(%789, %205): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03140c59, // %791 = add(%788, %790): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03150003, // %792 = mul(%789, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0318033b, // %793 = mul(%792, %206): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03170c65, // %794 = add(%791, %793): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03180003, // %795 = mul(%792, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x031b033f, // %796 = mul(%795, %207): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02f30c71, // %797 = add(%755, %796): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x031b0003, // %798 = mul(%795, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x031e0343, // %799 = mul(%798, %208): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x031a0c7d, // %800 = add(%794, %799): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x031e0003, // %801 = mul(%798, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03210347, // %802 = mul(%801, %209): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03200c89, // %803 = add(%800, %802): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03210003, // %804 = mul(%801, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0324034b, // %805 = mul(%804, %210): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03230c95, // %806 = add(%803, %805): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03240003, // %807 = mul(%804, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0327034f, // %808 = mul(%807, %211): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03260ca1, // %809 = add(%806, %808): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03270003, // %810 = mul(%807, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x032a0353, // %811 = mul(%810, %212): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x031d0cad, // %812 = add(%797, %811): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x032a0003, // %813 = mul(%810, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x032d0357, // %814 = mul(%813, %213): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x032c0cb9, // %815 = add(%812, %814): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x032d0003, // %816 = mul(%813, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0330035b, // %817 = mul(%816, %214): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x032f0cc5, // %818 = add(%815, %817): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03300003, // %819 = mul(%816, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0333035f, // %820 = mul(%819, %215): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03320cd1, // %821 = add(%818, %820): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03330003, // %822 = mul(%819, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03360363, // %823 = mul(%822, %216): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03350cdd, // %824 = add(%821, %823): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03360003, // %825 = mul(%822, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03390367, // %826 = mul(%825, %217): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03290ce9, // %827 = add(%809, %826): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03390003, // %828 = mul(%825, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x033c036b, // %829 = mul(%828, %218): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x033b0cf5, // %830 = add(%827, %829): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x033c0003, // %831 = mul(%828, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x033f036f, // %832 = mul(%831, %219): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x033e0d01, // %833 = add(%830, %832): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x033f0003, // %834 = mul(%831, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03420373, // %835 = mul(%834, %220): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03410d0d, // %836 = add(%833, %835): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03420003, // %837 = mul(%834, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03450377, // %838 = mul(%837, %221): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03380d19, // %839 = add(%824, %838): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03450003, // %840 = mul(%837, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0348037b, // %841 = mul(%840, %222): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03470d25, // %842 = add(%839, %841): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03480003, // %843 = mul(%840, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x034b037f, // %844 = mul(%843, %223): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x034a0d31, // %845 = add(%842, %844): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x034b0003, // %846 = mul(%843, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x034e0383, // %847 = mul(%846, %224): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03440d3d, // %848 = add(%836, %847): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x034e0003, // %849 = mul(%846, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03510387, // %850 = mul(%849, %225): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03500d49, // %851 = add(%848, %850): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03510003, // %852 = mul(%849, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0354038b, // %853 = mul(%852, %226): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03530d55, // %854 = add(%851, %853): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03540003, // %855 = mul(%852, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0357038f, // %856 = mul(%855, %227): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03560d61, // %857 = add(%854, %856): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03570003, // %858 = mul(%855, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x035a0393, // %859 = mul(%858, %228): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x034d0d6d, // %860 = add(%845, %859): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x035a0003, // %861 = mul(%858, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x035d0397, // %862 = mul(%861, %229): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x035c0d79, // %863 = add(%860, %862): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x035d0003, // %864 = mul(%861, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0360039b, // %865 = mul(%864, %230): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03590d85, // %866 = add(%857, %865): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03600003, // %867 = mul(%864, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0363039f, // %868 = mul(%867, %231): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03620d91, // %869 = add(%866, %868): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03630003, // %870 = mul(%867, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036603a3, // %871 = mul(%870, %232): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03650d9d, // %872 = add(%869, %871): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03660003, // %873 = mul(%870, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036903a7, // %874 = mul(%873, %233): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03690003, // %875 = mul(%873, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036b03ab, // %876 = mul(%875, %234): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x036a0db1, // %877 = add(%874, %876): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x036b0003, // %878 = mul(%875, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036e03af, // %879 = mul(%878, %235): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03680dbd, // %880 = add(%872, %879): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x036e0003, // %881 = mul(%878, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037103b3, // %882 = mul(%881, %236): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x035f0dc9, // %883 = add(%863, %882): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03710003, // %884 = mul(%881, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037403b7, // %885 = mul(%884, %237): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03700dd5, // %886 = add(%880, %885): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03740003, // %887 = mul(%884, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037703bb, // %888 = mul(%887, %238): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03760de1, // %889 = add(%886, %888): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03770003, // %890 = mul(%887, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037a03bf, // %891 = mul(%890, %239): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03790ded, // %892 = add(%889, %891): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x037a0003, // %893 = mul(%890, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037d03c3, // %894 = mul(%893, %240): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x037c0df9, // %895 = add(%892, %894): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x037d0003, // %896 = mul(%893, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038003c7, // %897 = mul(%896, %241): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x037f0e05, // %898 = add(%895, %897): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03800003, // %899 = mul(%896, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038303cb, // %900 = mul(%899, %242): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03820e11, // %901 = add(%898, %900): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03830003, // %902 = mul(%899, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038603cf, // %903 = mul(%902, %243): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03730e1d, // %904 = add(%883, %903): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03860003, // %905 = mul(%902, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038903d3, // %906 = mul(%905, %244): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03880e29, // %907 = add(%904, %906): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03890003, // %908 = mul(%905, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038c03d7, // %909 = mul(%908, %245): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x038b0e35, // %910 = add(%907, %909): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x038c0003, // %911 = mul(%908, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038f03db, // %912 = mul(%911, %246): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x038e0e41, // %913 = add(%910, %912): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x038f0003, // %914 = mul(%911, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039203df, // %915 = mul(%914, %247): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03910e4d, // %916 = add(%913, %915): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03920003, // %917 = mul(%914, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039503e3, // %918 = mul(%917, %248): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03940e59, // %919 = add(%916, %918): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03950003, // %920 = mul(%917, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039803e7, // %921 = mul(%920, %249): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03980003, // %922 = mul(%920, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039a03eb, // %923 = mul(%922, %250): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03990e6d, // %924 = add(%921, %923): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x039a0003, // %925 = mul(%922, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039d03ef, // %926 = mul(%925, %251): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x039c0e79, // %927 = add(%924, %926): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x039d0003, // %928 = mul(%925, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03a003f3, // %929 = mul(%928, %252): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x039f0e85, // %930 = add(%927, %929): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03a00003, // %931 = mul(%928, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03a303f7, // %932 = mul(%931, %253): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03a20e91, // %933 = add(%930, %932): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03a30003, // %934 = mul(%931, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03a603fb, // %935 = mul(%934, %254): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03a50e9d, // %936 = add(%933, %935): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03a60003, // %937 = mul(%934, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03a903ff, // %938 = mul(%937, %255): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03a80ea9, // %939 = add(%936, %938): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03a90003, // %940 = mul(%937, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ac0403, // %941 = mul(%940, %256): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ab0eb5, // %942 = add(%939, %941): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03ac0003, // %943 = mul(%940, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03af0407, // %944 = mul(%943, %257): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ae0ec1, // %945 = add(%942, %944): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03af0003, // %946 = mul(%943, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03b2040b, // %947 = mul(%946, %258): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03b10ecd, // %948 = add(%945, %947): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03b20003, // %949 = mul(%946, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03b5040f, // %950 = mul(%949, %259): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03b40ed9, // %951 = add(%948, %950): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03b50003, // %952 = mul(%949, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03b80413, // %953 = mul(%952, %260): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03b70ee5, // %954 = add(%951, %953): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03b80003, // %955 = mul(%952, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03bb0417, // %956 = mul(%955, %261): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ba0ef1, // %957 = add(%954, %956): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03bb0003, // %958 = mul(%955, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03be041b, // %959 = mul(%958, %262): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03bd0efd, // %960 = add(%957, %959): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03be0003, // %961 = mul(%958, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03c1041f, // %962 = mul(%961, %263): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03c00f09, // %963 = add(%960, %962): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03c10003, // %964 = mul(%961, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03c40423, // %965 = mul(%964, %264): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03c30f15, // %966 = add(%963, %965): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03c40003, // %967 = mul(%964, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03c70427, // %968 = mul(%967, %265): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03c60f21, // %969 = add(%966, %968): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03c70003, // %970 = mul(%967, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ca042b, // %971 = mul(%970, %266): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03c90f2d, // %972 = add(%969, %971): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03ca0003, // %973 = mul(%970, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03cd042f, // %974 = mul(%973, %267): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03cc0f39, // %975 = add(%972, %974): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03cd0003, // %976 = mul(%973, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03d00433, // %977 = mul(%976, %268): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03cf0f45, // %978 = add(%975, %977): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03d00003, // %979 = mul(%976, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03d30437, // %980 = mul(%979, %269): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03d20f51, // %981 = add(%978, %980): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03d30003, // %982 = mul(%979, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03d6043b, // %983 = mul(%982, %270): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03d50f5d, // %984 = add(%981, %983): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03d60003, // %985 = mul(%982, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03d9043f, // %986 = mul(%985, %271): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03d80f69, // %987 = add(%984, %986): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03d90003, // %988 = mul(%985, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03dc0443, // %989 = mul(%988, %272): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03db0f75, // %990 = add(%987, %989): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03dc0003, // %991 = mul(%988, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03df0447, // %992 = mul(%991, %273): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03de0f81, // %993 = add(%990, %992): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03df0003, // %994 = mul(%991, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03e2044b, // %995 = mul(%994, %274): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03e10f8d, // %996 = add(%993, %995): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03e20003, // %997 = mul(%994, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03e5044f, // %998 = mul(%997, %275): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03e40f99, // %999 = add(%996, %998): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03e50003, // %1000 = mul(%997, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03e80453, // %1001 = mul(%1000, %276): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03e70fa5, // %1002 = add(%999, %1001): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03e80003, // %1003 = mul(%1000, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03eb0457, // %1004 = mul(%1003, %277): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ea0fb1, /* %1005 = add(%1002, %1004):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03eb0003, // %1006 = mul(%1003, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ee045b, // %1007 = mul(%1006, %278): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ed0fbd, /* %1008 = add(%1005, %1007):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03ee0003, // %1009 = mul(%1006, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03f1045f, // %1010 = mul(%1009, %279): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03f00fc9, /* %1011 = add(%1008, %1010):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03f10003, // %1012 = mul(%1009, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03f40463, // %1013 = mul(%1012, %280): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03f30fd5, /* %1014 = add(%1011, %1013):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03f40003, // %1015 = mul(%1012, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03f70467, // %1016 = mul(%1015, %281): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03f60fe1, /* %1017 = add(%1014, %1016):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03f70003, // %1018 = mul(%1015, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03fa046b, // %1019 = mul(%1018, %282): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03f90fed, /* %1020 = add(%1017, %1019):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03fa0003, // %1021 = mul(%1018, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03fd046f, // %1022 = mul(%1021, %283): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03fc0ff9, /* %1023 = add(%1020, %1022):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03fd0003, // %1024 = mul(%1021, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04000473, // %1025 = mul(%1024, %284): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ff1005, /* %1026 = add(%1023, %1025):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04000003, // %1027 = mul(%1024, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04030477, // %1028 = mul(%1027, %285): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04021011, /* %1029 = add(%1026, %1028):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04030003, // %1030 = mul(%1027, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0406047b, // %1031 = mul(%1030, %286): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0405101d, /* %1032 = add(%1029, %1031):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04060003, // %1033 = mul(%1030, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0409047f, // %1034 = mul(%1033, %287): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04081029, /* %1035 = add(%1032, %1034):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04090003, // %1036 = mul(%1033, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x040c0483, // %1037 = mul(%1036, %288): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x040b1035, /* %1038 = add(%1035, %1037):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x040c0003, // %1039 = mul(%1036, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x040f0487, // %1040 = mul(%1039, %289): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x040e1041, /* %1041 = add(%1038, %1040):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x040f0003, // %1042 = mul(%1039, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0412048b, // %1043 = mul(%1042, %290): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0411104d, /* %1044 = add(%1041, %1043):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04120003, // %1045 = mul(%1042, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0415048f, // %1046 = mul(%1045, %291): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04141059, /* %1047 = add(%1044, %1046):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04150003, // %1048 = mul(%1045, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04180493, // %1049 = mul(%1048, %292): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04171065, /* %1050 = add(%1047, %1049):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04180003, // %1051 = mul(%1048, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x041b0497, // %1052 = mul(%1051, %293): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x041a1071, /* %1053 = add(%1050, %1052):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x041b0003, // %1054 = mul(%1051, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x041e049b, // %1055 = mul(%1054, %294): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x041d107d, /* %1056 = add(%1053, %1055):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x041e0003, // %1057 = mul(%1054, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0421049f, // %1058 = mul(%1057, %295): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04201089, /* %1059 = add(%1056, %1058):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04210003, // %1060 = mul(%1057, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042404a3, // %1061 = mul(%1060, %296): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04231095, /* %1062 = add(%1059, %1061):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04240003, // %1063 = mul(%1060, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042704a7, // %1064 = mul(%1063, %297): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x042610a1, /* %1065 = add(%1062, %1064):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04270003, // %1066 = mul(%1063, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042a04ab, // %1067 = mul(%1066, %298): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x042910ad, /* %1068 = add(%1065, %1067):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x042a0003, // %1069 = mul(%1066, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042d04af, // %1070 = mul(%1069, %299): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x042c10b9, /* %1071 = add(%1068, %1070):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x042d0003, // %1072 = mul(%1069, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043004b3, // %1073 = mul(%1072, %300): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x042f10c5, /* %1074 = add(%1071, %1073):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04300003, // %1075 = mul(%1072, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043304b7, // %1076 = mul(%1075, %301): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043210d1, /* %1077 = add(%1074, %1076):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04330003, // %1078 = mul(%1075, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043604bb, // %1079 = mul(%1078, %302): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043510dd, /* %1080 = add(%1077, %1079):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04360003, // %1081 = mul(%1078, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043904bf, // %1082 = mul(%1081, %303): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043810e9, /* %1083 = add(%1080, %1082):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04390003, // %1084 = mul(%1081, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043c04c3, // %1085 = mul(%1084, %304): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043b10f5, /* %1086 = add(%1083, %1085):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x043c0003, // %1087 = mul(%1084, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043f04c7, // %1088 = mul(%1087, %305): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043e1101, /* %1089 = add(%1086, %1088):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x043f0003, // %1090 = mul(%1087, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x044204cb, // %1091 = mul(%1090, %306): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0441110d, /* %1092 = add(%1089, %1091):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04420003, // %1093 = mul(%1090, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x044504cf, // %1094 = mul(%1093, %307): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04441119, /* %1095 = add(%1092, %1094):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04450003, // %1096 = mul(%1093, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x044804d3, // %1097 = mul(%1096, %308): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04471125, /* %1098 = add(%1095, %1097):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04480003, // %1099 = mul(%1096, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x044b04d7, // %1100 = mul(%1099, %309): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x044a1131, /* %1101 = add(%1098, %1100):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x044b0003, // %1102 = mul(%1099, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x044e04db, // %1103 = mul(%1102, %310): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x044d113d, /* %1104 = add(%1101, %1103):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x044e0003, // %1105 = mul(%1102, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x045104df, // %1106 = mul(%1105, %311): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04501149, /* %1107 = add(%1104, %1106):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04510003, // %1108 = mul(%1105, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x045404e3, // %1109 = mul(%1108, %312): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04531155, /* %1110 = add(%1107, %1109):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04540003, // %1111 = mul(%1108, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04570073, // %1112 = mul(%1111, %28): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04570003, // %1113 = mul(%1111, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x04590077, // %1114 = mul(%1113, %29): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04581169, /* %1115 = add(%1112, %1114):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04590003, // %1116 = mul(%1113, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x045c007b, // %1117 = mul(%1116, %30): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x045b1175, /* %1118 = add(%1115, %1117):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x045c0003, // %1119 = mul(%1116, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x045f007f, // %1120 = mul(%1119, %31): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x045e1181, /* %1121 = add(%1118, %1120):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x045f0003, // %1122 = mul(%1119, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x04620083, // %1123 = mul(%1122, %32): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x0461118d, /* %1124 = add(%1121, %1123):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04620003, // %1125 = mul(%1122, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x04650087, // %1126 = mul(%1125, %33): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04641199, /* %1127 = add(%1124, %1126):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04650003, // %1128 = mul(%1125, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x0468008b, // %1129 = mul(%1128, %34): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x046711a5, /* %1130 = add(%1127, %1129):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04680003, // %1131 = mul(%1128, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x046b008f, // %1132 = mul(%1131, %35): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x046a11b1, /* %1133 = add(%1130, %1132):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x046b0003, // %1134 = mul(%1131, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x046e0093, // %1135 = mul(%1134, %36): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x046d11bd, /* %1136 = add(%1133, %1135):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x046e0003, // %1137 = mul(%1134, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x04710097, // %1138 = mul(%1137, %37): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x047011c9, /* %1139 = add(%1136, %1138):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04710003, // %1140 = mul(%1137, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x0474009b, // %1141 = mul(%1140, %38): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x047311d5, /* %1142 = add(%1139, %1141):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04740003, // %1143 = mul(%1140, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x0477009f, // %1144 = mul(%1143, %39): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x047611e1, /* %1145 = add(%1142, %1144):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04770003, // %1146 = mul(%1143, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x047a00a3, // %1147 = mul(%1146, %40): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x047911ed, /* %1148 = add(%1145, %1147):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x047a0003, // %1149 = mul(%1146, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x047d00a7, // %1150 = mul(%1149, %41): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x047c11f9, /* %1151 = add(%1148, %1150):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x047d0003, // %1152 = mul(%1149, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x048000ab, // %1153 = mul(%1152, %42): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x047f1205, /* %1154 = add(%1151, %1153):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04800003, // %1155 = mul(%1152, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x048300af, // %1156 = mul(%1155, %43): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04821211, /* %1157 = add(%1154, %1156):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x03970012, // %1158 = sub(%919, %4): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0002000e, // %1159 = sub(%2, %3): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04870108, // %1160 = inv(%1159): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04861223, /* %1161 = mul(%1158, %1160):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x03850016, // %1162 = sub(%901, %5): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0006000b, // %1163 = mul(%6, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x048a122e, /* %1164 = sub(%1162, %1163):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00030007, // %1165 = mul(%3, %1): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x00021236, // %1166 = sub(%2, %1165): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0487123b, /* %1167 = mul(%1159, %1166):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x048f0108, // %1168 = inv(%1167): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x048c1243, /* %1169 = mul(%1164, %1168):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x04891245, /* %1170 = add(%1161, %1169):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x036d001e, // %1171 = sub(%877, %7): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0008000b, // %1172 = mul(%8, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04931252, /* %1173 = sub(%1171, %1172):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0002000b, // %1174 = mul(%2, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x0009125b, // %1175 = mul(%9, %1174): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x0495125e, /* %1176 = sub(%1173, %1175):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00010007, // %1177 = mul(%1, %1): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x00031267, // %1178 = mul(%3, %1177): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002126a, // %1179 = sub(%2, %1178): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x048f126f, /* %1180 = mul(%1167, %1179):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x049c0108, // %1181 = inv(%1180): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04981277, /* %1182 = mul(%1176, %1181):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x04921279, /* %1183 = add(%1170, %1182):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x0456002a, // %1184 = sub(%1110, %10): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x000b000b, // %1185 = mul(%11, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04a01286, /* %1186 = sub(%1184, %1185):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x000c125b, // %1187 = mul(%12, %1174): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04a2128e, /* %1188 = sub(%1186, %1187):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0002125b, // %1189 = mul(%2, %1174): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x000d1297, // %1190 = mul(%13, %1189): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04a4129a, /* %1191 = sub(%1188, %1190):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0496125b, /* %1192 = mul(%1174, %1174):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0) */
    0x000e12a3, // %1193 = mul(%14, %1192): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04a712a6, /* %1194 = sub(%1191, %1193):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x000212a3, // %1195 = mul(%2, %1192): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x000f12af, // %1196 = mul(%15, %1195): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04aa12b2, /* %1197 = sub(%1194, %1196):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00011267, // %1198 = mul(%1, %1177): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000312bb, // %1199 = mul(%3, %1198): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000212be, // %1200 = sub(%2, %1199): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x049c12c3, /* %1201 = mul(%1180, %1200):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04991267, /* %1202 = mul(%1177, %1177):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x000312cb, // %1203 = mul(%3, %1202): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000212ce, // %1204 = sub(%2, %1203): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04b112d3, /* %1205 = mul(%1201, %1204):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04b212cb, /* %1206 = mul(%1202, %1202):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x04b612db, /* %1207 = mul(%1206, %1206):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x000112df, // %1208 = mul(%1, %1207): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04b812e3, /* %1209 = mul(%1208, %1208):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x04b912e7, /* %1210 = mul(%1209, %1209):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x000312eb, // %1211 = mul(%3, %1210): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000212ee, // %1212 = sub(%2, %1211): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04b512f3, /* %1213 = mul(%1205, %1212):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04bd0108, // %1214 = inv(%1213): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04ad12fb, /* %1215 = mul(%1197, %1214):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x049f12fd, /* %1216 = add(%1183, %1215):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x02450042, // %1217 = sub(%581, %16): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0011000b, // %1218 = mul(%17, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04c1130a, /* %1219 = sub(%1217, %1218):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0012125b, // %1220 = mul(%18, %1174): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04c31312, /* %1221 = sub(%1219, %1220):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00131297, // %1222 = mul(%19, %1189): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04c5131a, /* %1223 = sub(%1221, %1222):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x001412a3, // %1224 = mul(%20, %1192): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04c71322, /* %1225 = sub(%1223, %1224):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x001512af, // %1226 = mul(%21, %1195): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04c9132a, /* %1227 = sub(%1225, %1226):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x04ae12bb, /* %1228 = mul(%1198, %1198):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x00011333, // %1229 = mul(%1, %1228): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x00031337, // %1230 = mul(%3, %1229): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002133a, // %1231 = sub(%2, %1230): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x049c133f, /* %1232 = mul(%1180, %1231):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04cd1337, /* %1233 = mul(%1229, %1229):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x00011347, // %1234 = mul(%1, %1233): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0003134b, // %1235 = mul(%3, %1234): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002134e, // %1236 = sub(%2, %1235): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04d01353, /* %1237 = mul(%1232, %1236):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x000312df, // %1238 = mul(%3, %1207): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002135a, // %1239 = sub(%2, %1238): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04d5135f, /* %1240 = mul(%1237, %1239):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04d80108, // %1241 = inv(%1240): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04cb1367, /* %1242 = mul(%1227, %1241):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x04c01369, /* %1243 = add(%1216, %1242):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x02ea005a, // %1244 = sub(%746, %22): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0017000b, // %1245 = mul(%23, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04dc1376, /* %1246 = sub(%1244, %1245):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0018125b, // %1247 = mul(%24, %1174): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04de137e, /* %1248 = sub(%1246, %1247):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00191297, // %1249 = mul(%25, %1189): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04e01386, /* %1250 = sub(%1248, %1249):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x001a12a3, // %1251 = mul(%26, %1192): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04e2138e, /* %1252 = sub(%1250, %1251):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0487126f, /* %1253 = mul(%1159, %1179):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04e5133f, /* %1254 = mul(%1253, %1231):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04e61353, /* %1255 = mul(%1254, %1236):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04e7135f, /* %1256 = mul(%1255, %1239):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04e80108, // %1257 = inv(%1256): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04e413a7, /* %1258 = mul(%1252, %1257):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x04db13a9, /* %1259 = add(%1243, %1258):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x0485006e, // %1260 = sub(%1157, %27): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":181:0)
    0x0003000f, // %1261 = mul(%3, %3): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":182:0)
    0x04ed13b7, /* %1262 = mul(%1261, %1261):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":182:0) */
    0x000213ba, // %1263 = sub(%2, %1262): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":182:0)
    0x04ef0108, // %1264 = inv(%1263): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":184:0)
    0x04ec13c3, /* %1265 = mul(%1260, %1264):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":184:0) */
    0x04eb13c5, /* %1266 = add(%1259, %1265):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":184:0) */
    0x00000704, // set($0x0000, 0x07): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":186:0)
];

#[inline(always)]
pub fn verify_taps_rv32im(
    arg0: &[u32; 4 * EXT_ELEM_SIZE],
    arg1: &[u32; 24 * EXT_ELEM_SIZE],
    arg2: &[u32; 16 * EXT_ELEM_SIZE],
    arg3: &[u32; 40 * EXT_ELEM_SIZE],
    arg4: &[u32; 15 * EXT_ELEM_SIZE],
    arg5: &[u32; 214 * EXT_ELEM_SIZE],
    arg6: &mut [u32; 1 * EXT_ELEM_SIZE],
) {
    #[cfg(target_os = "zkvm")]
    unsafe {
        risc0_zkvm_platform::syscall::sys_ffpu(
            CODE,
            &[
                DATA.as_ptr() as *mut u32,
                arg0.as_ptr() as *mut u32,
                arg1.as_ptr() as *mut u32,
                arg2.as_ptr() as *mut u32,
                arg3.as_ptr() as *mut u32,
                arg4.as_ptr() as *mut u32,
                arg5.as_ptr() as *mut u32,
                arg6.as_ptr() as *mut u32,
            ],
        )
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}
