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
    0x00000500, // %80 = get($0x0000, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00010500, // %81 = get($0x0001, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00020500, // %82 = get($0x0002, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00030500, // %83 = get($0x0003, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00040500, // %84 = get($0x0004, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00050500, // %85 = get($0x0005, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00060500, // %86 = get($0x0006, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00070500, // %87 = get($0x0007, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00080500, // %88 = get($0x0008, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00090500, // %89 = get($0x0009, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x000a0500, // %90 = get($0x000a, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x000b0500, // %91 = get($0x000b, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x000c0500, // %92 = get($0x000c, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x000d0500, // %93 = get($0x000d, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x000e0500, // %94 = get($0x000e, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":129:0)
    0x00000600, // %95 = get($0x0000, 0x06): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0)
    0x00010600, // %96 = get($0x0001, 0x06): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0)
    0x00020600, // %97 = get($0x0002, 0x06): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0)
    0x00030600, // %98 = get($0x0003, 0x06): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0)
    0x00040600, // %99 = get($0x0004, 0x06): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0)
    0x00050600, /* %100 = get($0x0005, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00060600, /* %101 = get($0x0006, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00070600, /* %102 = get($0x0007, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00080600, /* %103 = get($0x0008, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00090600, /* %104 = get($0x0009, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000a0600, /* %105 = get($0x000a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000b0600, /* %106 = get($0x000b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000c0600, /* %107 = get($0x000c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000d0600, /* %108 = get($0x000d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000e0600, /* %109 = get($0x000e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000f0600, /* %110 = get($0x000f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00100600, /* %111 = get($0x0010, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00110600, /* %112 = get($0x0011, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00120600, /* %113 = get($0x0012, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00130600, /* %114 = get($0x0013, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00140600, /* %115 = get($0x0014, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00150600, /* %116 = get($0x0015, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00160600, /* %117 = get($0x0016, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00170600, /* %118 = get($0x0017, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00180600, /* %119 = get($0x0018, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00190600, /* %120 = get($0x0019, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001a0600, /* %121 = get($0x001a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001b0600, /* %122 = get($0x001b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001c0600, /* %123 = get($0x001c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001d0600, /* %124 = get($0x001d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001e0600, /* %125 = get($0x001e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x001f0600, /* %126 = get($0x001f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00200600, /* %127 = get($0x0020, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00210600, /* %128 = get($0x0021, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00220600, /* %129 = get($0x0022, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00230600, /* %130 = get($0x0023, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00240600, /* %131 = get($0x0024, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00250600, /* %132 = get($0x0025, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00260600, /* %133 = get($0x0026, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00270600, /* %134 = get($0x0027, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00280600, /* %135 = get($0x0028, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00290600, /* %136 = get($0x0029, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002a0600, /* %137 = get($0x002a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002b0600, /* %138 = get($0x002b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002c0600, /* %139 = get($0x002c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002d0600, /* %140 = get($0x002d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002e0600, /* %141 = get($0x002e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x002f0600, /* %142 = get($0x002f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00300600, /* %143 = get($0x0030, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00310600, /* %144 = get($0x0031, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00320600, /* %145 = get($0x0032, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00330600, /* %146 = get($0x0033, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00340600, /* %147 = get($0x0034, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00350600, /* %148 = get($0x0035, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00360600, /* %149 = get($0x0036, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00370600, /* %150 = get($0x0037, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00380600, /* %151 = get($0x0038, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00390600, /* %152 = get($0x0039, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003a0600, /* %153 = get($0x003a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003b0600, /* %154 = get($0x003b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003c0600, /* %155 = get($0x003c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003d0600, /* %156 = get($0x003d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003e0600, /* %157 = get($0x003e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x003f0600, /* %158 = get($0x003f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00400600, /* %159 = get($0x0040, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00410600, /* %160 = get($0x0041, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00420600, /* %161 = get($0x0042, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00430600, /* %162 = get($0x0043, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00440600, /* %163 = get($0x0044, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00450600, /* %164 = get($0x0045, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00460600, /* %165 = get($0x0046, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00470600, /* %166 = get($0x0047, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00480600, /* %167 = get($0x0048, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00490600, /* %168 = get($0x0049, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004a0600, /* %169 = get($0x004a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004b0600, /* %170 = get($0x004b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004c0600, /* %171 = get($0x004c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004d0600, /* %172 = get($0x004d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004e0600, /* %173 = get($0x004e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x004f0600, /* %174 = get($0x004f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00500600, /* %175 = get($0x0050, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00510600, /* %176 = get($0x0051, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00520600, /* %177 = get($0x0052, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00530600, /* %178 = get($0x0053, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00540600, /* %179 = get($0x0054, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00550600, /* %180 = get($0x0055, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00560600, /* %181 = get($0x0056, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00570600, /* %182 = get($0x0057, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00580600, /* %183 = get($0x0058, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00590600, /* %184 = get($0x0059, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005a0600, /* %185 = get($0x005a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005b0600, /* %186 = get($0x005b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005c0600, /* %187 = get($0x005c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005d0600, /* %188 = get($0x005d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005e0600, /* %189 = get($0x005e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x005f0600, /* %190 = get($0x005f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00600600, /* %191 = get($0x0060, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00610600, /* %192 = get($0x0061, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00620600, /* %193 = get($0x0062, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00630600, /* %194 = get($0x0063, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00640600, /* %195 = get($0x0064, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00650600, /* %196 = get($0x0065, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00660600, /* %197 = get($0x0066, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00670600, /* %198 = get($0x0067, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00680600, /* %199 = get($0x0068, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00690600, /* %200 = get($0x0069, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006a0600, /* %201 = get($0x006a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006b0600, /* %202 = get($0x006b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006c0600, /* %203 = get($0x006c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006d0600, /* %204 = get($0x006d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006e0600, /* %205 = get($0x006e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x006f0600, /* %206 = get($0x006f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00700600, /* %207 = get($0x0070, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00710600, /* %208 = get($0x0071, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00720600, /* %209 = get($0x0072, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00730600, /* %210 = get($0x0073, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00740600, /* %211 = get($0x0074, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00750600, /* %212 = get($0x0075, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00760600, /* %213 = get($0x0076, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00770600, /* %214 = get($0x0077, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00780600, /* %215 = get($0x0078, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00790600, /* %216 = get($0x0079, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007a0600, /* %217 = get($0x007a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007b0600, /* %218 = get($0x007b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007c0600, /* %219 = get($0x007c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007d0600, /* %220 = get($0x007d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007e0600, /* %221 = get($0x007e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x007f0600, /* %222 = get($0x007f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00800600, /* %223 = get($0x0080, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00810600, /* %224 = get($0x0081, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00820600, /* %225 = get($0x0082, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00830600, /* %226 = get($0x0083, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00840600, /* %227 = get($0x0084, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00850600, /* %228 = get($0x0085, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00860600, /* %229 = get($0x0086, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00870600, /* %230 = get($0x0087, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00880600, /* %231 = get($0x0088, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00890600, /* %232 = get($0x0089, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008a0600, /* %233 = get($0x008a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008b0600, /* %234 = get($0x008b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008c0600, /* %235 = get($0x008c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008d0600, /* %236 = get($0x008d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008e0600, /* %237 = get($0x008e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x008f0600, /* %238 = get($0x008f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00900600, /* %239 = get($0x0090, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00910600, /* %240 = get($0x0091, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00920600, /* %241 = get($0x0092, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00930600, /* %242 = get($0x0093, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00940600, /* %243 = get($0x0094, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00950600, /* %244 = get($0x0095, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00960600, /* %245 = get($0x0096, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00970600, /* %246 = get($0x0097, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00980600, /* %247 = get($0x0098, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00990600, /* %248 = get($0x0099, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009a0600, /* %249 = get($0x009a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009b0600, /* %250 = get($0x009b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009c0600, /* %251 = get($0x009c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009d0600, /* %252 = get($0x009d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009e0600, /* %253 = get($0x009e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x009f0600, /* %254 = get($0x009f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a00600, /* %255 = get($0x00a0, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a10600, /* %256 = get($0x00a1, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a20600, /* %257 = get($0x00a2, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a30600, /* %258 = get($0x00a3, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a40600, /* %259 = get($0x00a4, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a50600, /* %260 = get($0x00a5, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a60600, /* %261 = get($0x00a6, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a70600, /* %262 = get($0x00a7, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a80600, /* %263 = get($0x00a8, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00a90600, /* %264 = get($0x00a9, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00aa0600, /* %265 = get($0x00aa, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ab0600, /* %266 = get($0x00ab, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ac0600, /* %267 = get($0x00ac, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ad0600, /* %268 = get($0x00ad, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ae0600, /* %269 = get($0x00ae, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00af0600, /* %270 = get($0x00af, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b00600, /* %271 = get($0x00b0, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b10600, /* %272 = get($0x00b1, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b20600, /* %273 = get($0x00b2, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b30600, /* %274 = get($0x00b3, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b40600, /* %275 = get($0x00b4, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b50600, /* %276 = get($0x00b5, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b60600, /* %277 = get($0x00b6, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b70600, /* %278 = get($0x00b7, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b80600, /* %279 = get($0x00b8, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00b90600, /* %280 = get($0x00b9, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ba0600, /* %281 = get($0x00ba, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00bb0600, /* %282 = get($0x00bb, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00bc0600, /* %283 = get($0x00bc, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00bd0600, /* %284 = get($0x00bd, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00be0600, /* %285 = get($0x00be, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00bf0600, /* %286 = get($0x00bf, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c00600, /* %287 = get($0x00c0, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c10600, /* %288 = get($0x00c1, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c20600, /* %289 = get($0x00c2, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c30600, /* %290 = get($0x00c3, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c40600, /* %291 = get($0x00c4, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c50600, /* %292 = get($0x00c5, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c60600, /* %293 = get($0x00c6, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c70600, /* %294 = get($0x00c7, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c80600, /* %295 = get($0x00c8, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00c90600, /* %296 = get($0x00c9, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ca0600, /* %297 = get($0x00ca, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00cb0600, /* %298 = get($0x00cb, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00cc0600, /* %299 = get($0x00cc, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00cd0600, /* %300 = get($0x00cd, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00ce0600, /* %301 = get($0x00ce, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00cf0600, /* %302 = get($0x00cf, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d00600, /* %303 = get($0x00d0, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d10600, /* %304 = get($0x00d1, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d20600, /* %305 = get($0x00d2, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d30600, /* %306 = get($0x00d3, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d40600, /* %307 = get($0x00d4, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x00d50600, /* %308 = get($0x00d5, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":130:0) */
    0x000000b7, // %309 = mul(%0, %45): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x002c04d5, // %310 = add(%44, %309): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x00000003, // %311 = mul(%0, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x013700bb, // %312 = mul(%311, %46): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x013604e1, // %313 = add(%310, %312): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01370003, // %314 = mul(%311, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x013a00bf, // %315 = mul(%314, %47): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x013904ed, // %316 = add(%313, %315): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x013a0003, // %317 = mul(%314, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x013d00c3, // %318 = mul(%317, %48): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x013c04f9, // %319 = add(%316, %318): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x013d0003, // %320 = mul(%317, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014000c7, // %321 = mul(%320, %49): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x013f0505, // %322 = add(%319, %321): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01400003, // %323 = mul(%320, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014300cb, // %324 = mul(%323, %50): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01420511, // %325 = add(%322, %324): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01430003, // %326 = mul(%323, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014600cf, // %327 = mul(%326, %51): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0145051d, // %328 = add(%325, %327): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01460003, // %329 = mul(%326, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014900d3, // %330 = mul(%329, %52): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01490003, // %331 = mul(%329, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014b00d7, // %332 = mul(%331, %53): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x014a0531, // %333 = add(%330, %332): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x014b0003, // %334 = mul(%331, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014e00db, // %335 = mul(%334, %54): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x014d053d, // %336 = add(%333, %335): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x014e0003, // %337 = mul(%334, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015100df, // %338 = mul(%337, %55): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01500549, // %339 = add(%336, %338): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01510003, // %340 = mul(%337, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015400e3, // %341 = mul(%340, %56): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01530555, // %342 = add(%339, %341): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01540003, // %343 = mul(%340, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015700e7, // %344 = mul(%343, %57): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01560561, // %345 = add(%342, %344): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01570003, // %346 = mul(%343, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015a00eb, // %347 = mul(%346, %58): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0159056d, // %348 = add(%345, %347): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x015a0003, // %349 = mul(%346, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015d00ef, // %350 = mul(%349, %59): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x015c0579, // %351 = add(%348, %350): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x015d0003, // %352 = mul(%349, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016000f3, // %353 = mul(%352, %60): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x015f0585, // %354 = add(%351, %353): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01600003, // %355 = mul(%352, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016300f7, // %356 = mul(%355, %61): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01620591, // %357 = add(%354, %356): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01630003, // %358 = mul(%355, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016600fb, // %359 = mul(%358, %62): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0165059d, // %360 = add(%357, %359): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01660003, // %361 = mul(%358, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016900ff, // %362 = mul(%361, %63): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x016805a9, // %363 = add(%360, %362): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01690003, // %364 = mul(%361, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016c0103, // %365 = mul(%364, %64): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x016b05b5, // %366 = add(%363, %365): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x016c0003, // %367 = mul(%364, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016f0107, // %368 = mul(%367, %65): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x016e05c1, // %369 = add(%366, %368): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x016f0003, // %370 = mul(%367, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0172010b, // %371 = mul(%370, %66): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017105cd, // %372 = add(%369, %371): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01720003, // %373 = mul(%370, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0175010f, // %374 = mul(%373, %67): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017405d9, // %375 = add(%372, %374): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01750003, // %376 = mul(%373, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01780113, // %377 = mul(%376, %68): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017705e5, // %378 = add(%375, %377): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01780003, // %379 = mul(%376, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x017b0117, // %380 = mul(%379, %69): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017a05f1, // %381 = add(%378, %380): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x017b0003, // %382 = mul(%379, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x017e011b, // %383 = mul(%382, %70): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017d05fd, // %384 = add(%381, %383): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x017e0003, // %385 = mul(%382, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0181011f, // %386 = mul(%385, %71): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01800609, // %387 = add(%384, %386): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01810003, // %388 = mul(%385, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01840123, // %389 = mul(%388, %72): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01830615, // %390 = add(%387, %389): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01840003, // %391 = mul(%388, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01870127, // %392 = mul(%391, %73): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01860621, // %393 = add(%390, %392): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01870003, // %394 = mul(%391, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x018a012b, // %395 = mul(%394, %74): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0189062d, // %396 = add(%393, %395): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x018a0003, // %397 = mul(%394, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x018d012f, // %398 = mul(%397, %75): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x018c0639, // %399 = add(%396, %398): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x018d0003, // %400 = mul(%397, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01900133, // %401 = mul(%400, %76): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x018f0645, // %402 = add(%399, %401): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01900003, // %403 = mul(%400, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01930137, // %404 = mul(%403, %77): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01920651, // %405 = add(%402, %404): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01930003, // %406 = mul(%403, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0196013b, // %407 = mul(%406, %78): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0195065d, // %408 = add(%405, %407): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01960003, // %409 = mul(%406, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0199013f, // %410 = mul(%409, %79): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01980669, // %411 = add(%408, %410): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01990003, // %412 = mul(%409, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x019c0143, // %413 = mul(%412, %80): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x019b0675, // %414 = add(%411, %413): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x019c0003, // %415 = mul(%412, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x019f0147, // %416 = mul(%415, %81): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x019e0681, // %417 = add(%414, %416): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x019f0003, // %418 = mul(%415, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01a2014b, // %419 = mul(%418, %82): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0148068d, // %420 = add(%328, %419): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01a20003, // %421 = mul(%418, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01a5014f, // %422 = mul(%421, %83): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01a10699, // %423 = add(%417, %422): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01a50003, // %424 = mul(%421, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01a80153, // %425 = mul(%424, %84): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01a706a5, // %426 = add(%423, %425): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01a80003, // %427 = mul(%424, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ab0157, // %428 = mul(%427, %85): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01a406b1, // %429 = add(%420, %428): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ab0003, // %430 = mul(%427, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ae015b, // %431 = mul(%430, %86): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01aa06bd, // %432 = add(%426, %431): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ae0003, // %433 = mul(%430, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01b1015f, // %434 = mul(%433, %87): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01b006c9, // %435 = add(%432, %434): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01b10003, // %436 = mul(%433, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01b40163, // %437 = mul(%436, %88): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01b306d5, // %438 = add(%435, %437): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01b40003, // %439 = mul(%436, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01b70167, // %440 = mul(%439, %89): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01b606e1, // %441 = add(%438, %440): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01b70003, // %442 = mul(%439, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ba016b, // %443 = mul(%442, %90): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01b906ed, // %444 = add(%441, %443): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ba0003, // %445 = mul(%442, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01bd016f, // %446 = mul(%445, %91): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01bc06f9, // %447 = add(%444, %446): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01bd0003, // %448 = mul(%445, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01c00173, // %449 = mul(%448, %92): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01bf0705, // %450 = add(%447, %449): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01c00003, // %451 = mul(%448, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01c30177, // %452 = mul(%451, %93): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01c20711, // %453 = add(%450, %452): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01c30003, // %454 = mul(%451, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01c6017b, // %455 = mul(%454, %94): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01c5071d, // %456 = add(%453, %455): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01c60003, // %457 = mul(%454, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01c9017f, // %458 = mul(%457, %95): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ad0729, // %459 = add(%429, %458): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01c90003, // %460 = mul(%457, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01cc0183, // %461 = mul(%460, %96): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01cb0735, // %462 = add(%459, %461): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01cc0003, // %463 = mul(%460, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01cf0187, // %464 = mul(%463, %97): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ce0741, // %465 = add(%462, %464): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01cf0003, // %466 = mul(%463, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01d2018b, // %467 = mul(%466, %98): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01d1074d, // %468 = add(%465, %467): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01d20003, // %469 = mul(%466, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01d5018f, // %470 = mul(%469, %99): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01d40759, // %471 = add(%468, %470): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01d50003, // %472 = mul(%469, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01d80193, // %473 = mul(%472, %100): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01d70765, // %474 = add(%471, %473): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01d80003, // %475 = mul(%472, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01db0197, // %476 = mul(%475, %101): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01da0771, // %477 = add(%474, %476): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01db0003, // %478 = mul(%475, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01de019b, // %479 = mul(%478, %102): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01dd077d, // %480 = add(%477, %479): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01de0003, // %481 = mul(%478, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01e1019f, // %482 = mul(%481, %103): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01e00789, // %483 = add(%480, %482): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01e10003, // %484 = mul(%481, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01e401a3, // %485 = mul(%484, %104): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01c80795, // %486 = add(%456, %485): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01e40003, // %487 = mul(%484, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01e701a7, // %488 = mul(%487, %105): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01e307a1, // %489 = add(%483, %488): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01e70003, // %490 = mul(%487, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ea01ab, // %491 = mul(%490, %106): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01e907ad, // %492 = add(%489, %491): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ea0003, // %493 = mul(%490, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ed01af, // %494 = mul(%493, %107): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ec07b9, // %495 = add(%492, %494): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ed0003, // %496 = mul(%493, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01f001b3, // %497 = mul(%496, %108): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01e607c5, // %498 = add(%486, %497): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01f00003, // %499 = mul(%496, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01f301b7, // %500 = mul(%499, %109): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01f207d1, // %501 = add(%498, %500): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01f30003, // %502 = mul(%499, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01f601bb, // %503 = mul(%502, %110): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01f507dd, // %504 = add(%501, %503): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01f60003, // %505 = mul(%502, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01f901bf, // %506 = mul(%505, %111): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01f807e9, // %507 = add(%504, %506): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01f90003, // %508 = mul(%505, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01fc01c3, // %509 = mul(%508, %112): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01fb07f5, // %510 = add(%507, %509): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01fc0003, // %511 = mul(%508, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ff01c7, // %512 = mul(%511, %113): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01fe0801, // %513 = add(%510, %512): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ff0003, // %514 = mul(%511, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020201cb, // %515 = mul(%514, %114): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02020003, // %516 = mul(%514, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020401cf, // %517 = mul(%516, %115): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02030815, // %518 = add(%515, %517): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02040003, // %519 = mul(%516, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020701d3, // %520 = mul(%519, %116): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02060821, // %521 = add(%518, %520): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02070003, // %522 = mul(%519, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020a01d7, // %523 = mul(%522, %117): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0209082d, // %524 = add(%521, %523): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x020a0003, // %525 = mul(%522, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020d01db, // %526 = mul(%525, %118): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x020c0839, // %527 = add(%524, %526): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x020d0003, // %528 = mul(%525, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021001df, // %529 = mul(%528, %119): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x020f0845, // %530 = add(%527, %529): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02100003, // %531 = mul(%528, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021301e3, // %532 = mul(%531, %120): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02130003, // %533 = mul(%531, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021501e7, // %534 = mul(%533, %121): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02140859, // %535 = add(%532, %534): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02150003, // %536 = mul(%533, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021801eb, // %537 = mul(%536, %122): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02170865, // %538 = add(%535, %537): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02180003, // %539 = mul(%536, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021b01ef, // %540 = mul(%539, %123): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x021a0871, // %541 = add(%538, %540): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x021b0003, // %542 = mul(%539, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021e01f3, // %543 = mul(%542, %124): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x021d087d, // %544 = add(%541, %543): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x021e0003, // %545 = mul(%542, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022101f7, // %546 = mul(%545, %125): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02200889, // %547 = add(%544, %546): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02210003, // %548 = mul(%545, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022401fb, // %549 = mul(%548, %126): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02230895, // %550 = add(%547, %549): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02240003, // %551 = mul(%548, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022701ff, // %552 = mul(%551, %127): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x022608a1, // %553 = add(%550, %552): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02270003, // %554 = mul(%551, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022a0203, // %555 = mul(%554, %128): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x022908ad, // %556 = add(%553, %555): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x022a0003, // %557 = mul(%554, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022d0207, // %558 = mul(%557, %129): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x022c08b9, // %559 = add(%556, %558): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x022d0003, // %560 = mul(%557, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0230020b, // %561 = mul(%560, %130): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x022f08c5, // %562 = add(%559, %561): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02300003, // %563 = mul(%560, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0233020f, // %564 = mul(%563, %131): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023208d1, // %565 = add(%562, %564): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02330003, // %566 = mul(%563, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02360213, // %567 = mul(%566, %132): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x021208dd, // %568 = add(%530, %567): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02360003, // %569 = mul(%566, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02390217, // %570 = mul(%569, %133): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023808e9, // %571 = add(%568, %570): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02390003, // %572 = mul(%569, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x023c021b, // %573 = mul(%572, %134): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023b08f5, // %574 = add(%571, %573): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x023c0003, // %575 = mul(%572, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x023f021f, // %576 = mul(%575, %135): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023e0901, // %577 = add(%574, %576): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x023f0003, // %578 = mul(%575, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02420223, // %579 = mul(%578, %136): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0201090d, // %580 = add(%513, %579): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02420003, // %581 = mul(%578, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02450227, // %582 = mul(%581, %137): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02440919, // %583 = add(%580, %582): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02450003, // %584 = mul(%581, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0248022b, // %585 = mul(%584, %138): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02470925, // %586 = add(%583, %585): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02480003, // %587 = mul(%584, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x024b022f, // %588 = mul(%587, %139): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x024a0931, // %589 = add(%586, %588): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x024b0003, // %590 = mul(%587, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x024e0233, // %591 = mul(%590, %140): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x024d093d, // %592 = add(%589, %591): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x024e0003, // %593 = mul(%590, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02510237, // %594 = mul(%593, %141): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02500949, // %595 = add(%592, %594): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02510003, // %596 = mul(%593, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0254023b, // %597 = mul(%596, %142): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02530955, // %598 = add(%595, %597): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02540003, // %599 = mul(%596, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0257023f, // %600 = mul(%599, %143): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02560961, // %601 = add(%598, %600): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02570003, // %602 = mul(%599, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x025a0243, // %603 = mul(%602, %144): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0259096d, // %604 = add(%601, %603): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x025a0003, // %605 = mul(%602, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x025d0247, // %606 = mul(%605, %145): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ef0979, // %607 = add(%495, %606): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x025d0003, // %608 = mul(%605, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0260024b, // %609 = mul(%608, %146): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x025f0985, // %610 = add(%607, %609): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02600003, // %611 = mul(%608, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0263024f, // %612 = mul(%611, %147): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x025c0991, // %613 = add(%604, %612): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02630003, // %614 = mul(%611, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02660253, // %615 = mul(%614, %148): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0265099d, // %616 = add(%613, %615): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02660003, // %617 = mul(%614, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02690257, // %618 = mul(%617, %149): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x026809a9, // %619 = add(%616, %618): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02690003, // %620 = mul(%617, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x026c025b, // %621 = mul(%620, %150): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x026b09b5, // %622 = add(%619, %621): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x026c0003, // %623 = mul(%620, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x026f025f, // %624 = mul(%623, %151): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x026e09c1, // %625 = add(%622, %624): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x026f0003, // %626 = mul(%623, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02720263, // %627 = mul(%626, %152): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027109cd, // %628 = add(%625, %627): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02720003, // %629 = mul(%626, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02750267, // %630 = mul(%629, %153): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027409d9, // %631 = add(%628, %630): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02750003, // %632 = mul(%629, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0278026b, // %633 = mul(%632, %154): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027709e5, // %634 = add(%631, %633): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02780003, // %635 = mul(%632, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x027b026f, // %636 = mul(%635, %155): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027a09f1, // %637 = add(%634, %636): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x027b0003, // %638 = mul(%635, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x027e0273, // %639 = mul(%638, %156): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027d09fd, // %640 = add(%637, %639): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x027e0003, // %641 = mul(%638, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02810277, // %642 = mul(%641, %157): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02800a09, // %643 = add(%640, %642): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02810003, // %644 = mul(%641, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0284027b, // %645 = mul(%644, %158): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02830a15, // %646 = add(%643, %645): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02840003, // %647 = mul(%644, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0287027f, // %648 = mul(%647, %159): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02860a21, // %649 = add(%646, %648): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02870003, // %650 = mul(%647, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x028a0283, // %651 = mul(%650, %160): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02890a2d, // %652 = add(%649, %651): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x028a0003, // %653 = mul(%650, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x028d0287, // %654 = mul(%653, %161): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x028c0a39, // %655 = add(%652, %654): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x028d0003, // %656 = mul(%653, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0290028b, // %657 = mul(%656, %162): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x028f0a45, // %658 = add(%655, %657): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02900003, // %659 = mul(%656, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0293028f, // %660 = mul(%659, %163): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02920a51, // %661 = add(%658, %660): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02930003, // %662 = mul(%659, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02960293, // %663 = mul(%662, %164): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02950a5d, // %664 = add(%661, %663): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02960003, // %665 = mul(%662, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02990297, // %666 = mul(%665, %165): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02980a69, // %667 = add(%664, %666): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02990003, // %668 = mul(%665, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x029c029b, // %669 = mul(%668, %166): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x029b0a75, // %670 = add(%667, %669): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x029c0003, // %671 = mul(%668, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x029f029f, // %672 = mul(%671, %167): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02620a81, // %673 = add(%610, %672): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x029f0003, // %674 = mul(%671, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02a202a3, // %675 = mul(%674, %168): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02a10a8d, // %676 = add(%673, %675): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02a20003, // %677 = mul(%674, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02a502a7, // %678 = mul(%677, %169): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x029e0a99, // %679 = add(%670, %678): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02a50003, // %680 = mul(%677, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02a802ab, // %681 = mul(%680, %170): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02a70aa5, // %682 = add(%679, %681): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02a80003, // %683 = mul(%680, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ab02af, // %684 = mul(%683, %171): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02aa0ab1, // %685 = add(%682, %684): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ab0003, // %686 = mul(%683, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ae02b3, // %687 = mul(%686, %172): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ad0abd, // %688 = add(%685, %687): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ae0003, // %689 = mul(%686, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02b102b7, // %690 = mul(%689, %173): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02b00ac9, // %691 = add(%688, %690): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02b10003, // %692 = mul(%689, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02b402bb, // %693 = mul(%692, %174): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02b30ad5, // %694 = add(%691, %693): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02b40003, // %695 = mul(%692, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02b702bf, // %696 = mul(%695, %175): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02b60ae1, // %697 = add(%694, %696): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02b70003, // %698 = mul(%695, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ba02c3, // %699 = mul(%698, %176): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02b90aed, // %700 = add(%697, %699): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ba0003, // %701 = mul(%698, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02bd02c7, // %702 = mul(%701, %177): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02410af9, // %703 = add(%577, %702): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02bd0003, // %704 = mul(%701, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02c002cb, // %705 = mul(%704, %178): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02bf0b05, // %706 = add(%703, %705): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02c00003, // %707 = mul(%704, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02c302cf, // %708 = mul(%707, %179): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02c20b11, // %709 = add(%706, %708): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02c30003, // %710 = mul(%707, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02c602d3, // %711 = mul(%710, %180): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02c50b1d, // %712 = add(%709, %711): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02c60003, // %713 = mul(%710, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02c902d7, // %714 = mul(%713, %181): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02c80b29, // %715 = add(%712, %714): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02c90003, // %716 = mul(%713, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02cc02db, // %717 = mul(%716, %182): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02cb0b35, // %718 = add(%715, %717): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02cc0003, // %719 = mul(%716, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02cf02df, // %720 = mul(%719, %183): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ce0b41, // %721 = add(%718, %720): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02cf0003, // %722 = mul(%719, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02d202e3, // %723 = mul(%722, %184): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02d10b4d, // %724 = add(%721, %723): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02d20003, // %725 = mul(%722, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02d502e7, // %726 = mul(%725, %185): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02d40b59, // %727 = add(%724, %726): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02d50003, // %728 = mul(%725, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02d802eb, // %729 = mul(%728, %186): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02d70b65, // %730 = add(%727, %729): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02d80003, // %731 = mul(%728, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02db02ef, // %732 = mul(%731, %187): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02bc0b71, // %733 = add(%700, %732): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02db0003, // %734 = mul(%731, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02de02f3, // %735 = mul(%734, %188): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02dd0b7d, // %736 = add(%733, %735): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02de0003, // %737 = mul(%734, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02e102f7, // %738 = mul(%737, %189): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02e00b89, // %739 = add(%736, %738): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02e10003, // %740 = mul(%737, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02e402fb, // %741 = mul(%740, %190): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02a40b95, // %742 = add(%676, %741): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02e40003, // %743 = mul(%740, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02e702ff, // %744 = mul(%743, %191): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02e60ba1, // %745 = add(%742, %744): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02e70003, // %746 = mul(%743, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ea0303, // %747 = mul(%746, %192): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02e90bad, // %748 = add(%745, %747): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ea0003, // %749 = mul(%746, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ed0307, // %750 = mul(%749, %193): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ec0bb9, // %751 = add(%748, %750): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ed0003, // %752 = mul(%749, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02f0030b, // %753 = mul(%752, %194): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ef0bc5, // %754 = add(%751, %753): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02f00003, // %755 = mul(%752, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02f3030f, // %756 = mul(%755, %195): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02f20bd1, // %757 = add(%754, %756): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02f30003, // %758 = mul(%755, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02f60313, // %759 = mul(%758, %196): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02f50bdd, // %760 = add(%757, %759): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02f60003, // %761 = mul(%758, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02f90317, // %762 = mul(%761, %197): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02f80be9, // %763 = add(%760, %762): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02f90003, // %764 = mul(%761, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02fc031b, // %765 = mul(%764, %198): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02fb0bf5, // %766 = add(%763, %765): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02fc0003, // %767 = mul(%764, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ff031f, // %768 = mul(%767, %199): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02fe0c01, // %769 = add(%766, %768): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ff0003, // %770 = mul(%767, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03020323, // %771 = mul(%770, %200): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03010c0d, // %772 = add(%769, %771): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03020003, // %773 = mul(%770, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03050327, // %774 = mul(%773, %201): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03040c19, // %775 = add(%772, %774): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03050003, // %776 = mul(%773, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0308032b, // %777 = mul(%776, %202): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03070c25, // %778 = add(%775, %777): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03080003, // %779 = mul(%776, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x030b032f, // %780 = mul(%779, %203): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02e30c31, // %781 = add(%739, %780): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x030b0003, // %782 = mul(%779, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x030e0333, // %783 = mul(%782, %204): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x030d0c3d, // %784 = add(%781, %783): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x030e0003, // %785 = mul(%782, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03110337, // %786 = mul(%785, %205): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03100c49, // %787 = add(%784, %786): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03110003, // %788 = mul(%785, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0314033b, // %789 = mul(%788, %206): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03130c55, // %790 = add(%787, %789): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03140003, // %791 = mul(%788, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0317033f, // %792 = mul(%791, %207): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03160c61, // %793 = add(%790, %792): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03170003, // %794 = mul(%791, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x031a0343, // %795 = mul(%794, %208): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03190c6d, // %796 = add(%793, %795): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x031a0003, // %797 = mul(%794, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x031d0347, // %798 = mul(%797, %209): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x031c0c79, // %799 = add(%796, %798): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x031d0003, // %800 = mul(%797, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0320034b, // %801 = mul(%800, %210): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x031f0c85, // %802 = add(%799, %801): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03200003, // %803 = mul(%800, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0323034f, // %804 = mul(%803, %211): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03220c91, // %805 = add(%802, %804): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03230003, // %806 = mul(%803, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03260353, // %807 = mul(%806, %212): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03250c9d, // %808 = add(%805, %807): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03260003, // %809 = mul(%806, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03290357, // %810 = mul(%809, %213): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x030a0ca9, // %811 = add(%778, %810): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03290003, // %812 = mul(%809, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x032c035b, // %813 = mul(%812, %214): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x032b0cb5, // %814 = add(%811, %813): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x032c0003, // %815 = mul(%812, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x032f035f, // %816 = mul(%815, %215): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x032e0cc1, // %817 = add(%814, %816): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x032f0003, // %818 = mul(%815, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03320363, // %819 = mul(%818, %216): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03310ccd, // %820 = add(%817, %819): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03320003, // %821 = mul(%818, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03350367, // %822 = mul(%821, %217): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03280cd9, // %823 = add(%808, %822): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03350003, // %824 = mul(%821, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0338036b, // %825 = mul(%824, %218): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03370ce5, // %826 = add(%823, %825): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03380003, // %827 = mul(%824, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x033b036f, // %828 = mul(%827, %219): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x033a0cf1, // %829 = add(%826, %828): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x033b0003, // %830 = mul(%827, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x033e0373, // %831 = mul(%830, %220): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03340cfd, // %832 = add(%820, %831): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x033e0003, // %833 = mul(%830, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03410377, // %834 = mul(%833, %221): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03400d09, // %835 = add(%832, %834): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03410003, // %836 = mul(%833, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0344037b, // %837 = mul(%836, %222): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03430d15, // %838 = add(%835, %837): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03440003, // %839 = mul(%836, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0347037f, // %840 = mul(%839, %223): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03460d21, // %841 = add(%838, %840): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03470003, // %842 = mul(%839, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x034a0383, // %843 = mul(%842, %224): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x033d0d2d, // %844 = add(%829, %843): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x034a0003, // %845 = mul(%842, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x034d0387, // %846 = mul(%845, %225): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x034c0d39, // %847 = add(%844, %846): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x034d0003, // %848 = mul(%845, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0350038b, // %849 = mul(%848, %226): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03490d45, // %850 = add(%841, %849): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03500003, // %851 = mul(%848, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0353038f, // %852 = mul(%851, %227): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03520d51, // %853 = add(%850, %852): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03530003, // %854 = mul(%851, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03560393, // %855 = mul(%854, %228): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03550d5d, // %856 = add(%853, %855): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03560003, // %857 = mul(%854, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03590397, // %858 = mul(%857, %229): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03590003, // %859 = mul(%857, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x035b039b, // %860 = mul(%859, %230): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x035a0d71, // %861 = add(%858, %860): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x035b0003, // %862 = mul(%859, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x035e039f, // %863 = mul(%862, %231): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03580d7d, // %864 = add(%856, %863): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x035e0003, // %865 = mul(%862, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036103a3, // %866 = mul(%865, %232): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x034f0d89, // %867 = add(%847, %866): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03610003, // %868 = mul(%865, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036403a7, // %869 = mul(%868, %233): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03600d95, // %870 = add(%864, %869): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03640003, // %871 = mul(%868, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036703ab, // %872 = mul(%871, %234): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03660da1, // %873 = add(%870, %872): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03670003, // %874 = mul(%871, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036a03af, // %875 = mul(%874, %235): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03690dad, // %876 = add(%873, %875): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x036a0003, // %877 = mul(%874, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036d03b3, // %878 = mul(%877, %236): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x036c0db9, // %879 = add(%876, %878): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x036d0003, // %880 = mul(%877, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037003b7, // %881 = mul(%880, %237): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x036f0dc5, // %882 = add(%879, %881): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03700003, // %883 = mul(%880, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037303bb, // %884 = mul(%883, %238): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03720dd1, // %885 = add(%882, %884): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03730003, // %886 = mul(%883, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037603bf, // %887 = mul(%886, %239): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03630ddd, // %888 = add(%867, %887): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03760003, // %889 = mul(%886, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037903c3, // %890 = mul(%889, %240): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03780de9, // %891 = add(%888, %890): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03790003, // %892 = mul(%889, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037c03c7, // %893 = mul(%892, %241): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x037b0df5, // %894 = add(%891, %893): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x037c0003, // %895 = mul(%892, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037f03cb, // %896 = mul(%895, %242): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x037e0e01, // %897 = add(%894, %896): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x037f0003, // %898 = mul(%895, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038203cf, // %899 = mul(%898, %243): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03810e0d, // %900 = add(%897, %899): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03820003, // %901 = mul(%898, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038503d3, // %902 = mul(%901, %244): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03840e19, // %903 = add(%900, %902): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03850003, // %904 = mul(%901, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038803d7, // %905 = mul(%904, %245): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03880003, // %906 = mul(%904, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038a03db, // %907 = mul(%906, %246): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03890e2d, // %908 = add(%905, %907): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x038a0003, // %909 = mul(%906, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038d03df, // %910 = mul(%909, %247): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x038c0e39, // %911 = add(%908, %910): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x038d0003, // %912 = mul(%909, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039003e3, // %913 = mul(%912, %248): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x038f0e45, // %914 = add(%911, %913): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03900003, // %915 = mul(%912, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039303e7, // %916 = mul(%915, %249): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03920e51, // %917 = add(%914, %916): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03930003, // %918 = mul(%915, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039603eb, // %919 = mul(%918, %250): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03950e5d, // %920 = add(%917, %919): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03960003, // %921 = mul(%918, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039903ef, // %922 = mul(%921, %251): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03980e69, // %923 = add(%920, %922): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03990003, // %924 = mul(%921, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039c03f3, // %925 = mul(%924, %252): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x039b0e75, // %926 = add(%923, %925): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x039c0003, // %927 = mul(%924, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039f03f7, // %928 = mul(%927, %253): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x039e0e81, // %929 = add(%926, %928): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x039f0003, // %930 = mul(%927, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03a203fb, // %931 = mul(%930, %254): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03a10e8d, // %932 = add(%929, %931): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03a20003, // %933 = mul(%930, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03a503ff, // %934 = mul(%933, %255): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03a40e99, // %935 = add(%932, %934): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03a50003, // %936 = mul(%933, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03a80403, // %937 = mul(%936, %256): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03a70ea5, // %938 = add(%935, %937): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03a80003, // %939 = mul(%936, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ab0407, // %940 = mul(%939, %257): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03aa0eb1, // %941 = add(%938, %940): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03ab0003, // %942 = mul(%939, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ae040b, // %943 = mul(%942, %258): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ad0ebd, // %944 = add(%941, %943): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03ae0003, // %945 = mul(%942, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03b1040f, // %946 = mul(%945, %259): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03b00ec9, // %947 = add(%944, %946): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03b10003, // %948 = mul(%945, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03b40413, // %949 = mul(%948, %260): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03b30ed5, // %950 = add(%947, %949): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03b40003, // %951 = mul(%948, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03b70417, // %952 = mul(%951, %261): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03b60ee1, // %953 = add(%950, %952): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03b70003, // %954 = mul(%951, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ba041b, // %955 = mul(%954, %262): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03b90eed, // %956 = add(%953, %955): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03ba0003, // %957 = mul(%954, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03bd041f, // %958 = mul(%957, %263): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03bc0ef9, // %959 = add(%956, %958): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03bd0003, // %960 = mul(%957, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03c00423, // %961 = mul(%960, %264): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03bf0f05, // %962 = add(%959, %961): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03c00003, // %963 = mul(%960, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03c30427, // %964 = mul(%963, %265): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03c20f11, // %965 = add(%962, %964): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03c30003, // %966 = mul(%963, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03c6042b, // %967 = mul(%966, %266): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03c50f1d, // %968 = add(%965, %967): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03c60003, // %969 = mul(%966, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03c9042f, // %970 = mul(%969, %267): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03c80f29, // %971 = add(%968, %970): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03c90003, // %972 = mul(%969, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03cc0433, // %973 = mul(%972, %268): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03cb0f35, // %974 = add(%971, %973): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03cc0003, // %975 = mul(%972, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03cf0437, // %976 = mul(%975, %269): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ce0f41, // %977 = add(%974, %976): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03cf0003, // %978 = mul(%975, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03d2043b, // %979 = mul(%978, %270): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03d10f4d, // %980 = add(%977, %979): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03d20003, // %981 = mul(%978, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03d5043f, // %982 = mul(%981, %271): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03d40f59, // %983 = add(%980, %982): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03d50003, // %984 = mul(%981, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03d80443, // %985 = mul(%984, %272): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03d70f65, // %986 = add(%983, %985): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03d80003, // %987 = mul(%984, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03db0447, // %988 = mul(%987, %273): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03da0f71, // %989 = add(%986, %988): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03db0003, // %990 = mul(%987, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03de044b, // %991 = mul(%990, %274): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03dd0f7d, // %992 = add(%989, %991): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03de0003, // %993 = mul(%990, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03e1044f, // %994 = mul(%993, %275): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03e00f89, // %995 = add(%992, %994): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03e10003, // %996 = mul(%993, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03e40453, // %997 = mul(%996, %276): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03e30f95, // %998 = add(%995, %997): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03e40003, // %999 = mul(%996, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03e70457, // %1000 = mul(%999, %277): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03e60fa1, // %1001 = add(%998, %1000): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03e70003, // %1002 = mul(%999, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ea045b, // %1003 = mul(%1002, %278): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03e90fad, /* %1004 = add(%1001, %1003):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03ea0003, // %1005 = mul(%1002, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ed045f, // %1006 = mul(%1005, %279): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ec0fb9, /* %1007 = add(%1004, %1006):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03ed0003, // %1008 = mul(%1005, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03f00463, // %1009 = mul(%1008, %280): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ef0fc5, /* %1010 = add(%1007, %1009):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03f00003, // %1011 = mul(%1008, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03f30467, // %1012 = mul(%1011, %281): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03f20fd1, /* %1013 = add(%1010, %1012):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03f30003, // %1014 = mul(%1011, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03f6046b, // %1015 = mul(%1014, %282): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03f50fdd, /* %1016 = add(%1013, %1015):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03f60003, // %1017 = mul(%1014, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03f9046f, // %1018 = mul(%1017, %283): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03f80fe9, /* %1019 = add(%1016, %1018):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03f90003, // %1020 = mul(%1017, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03fc0473, // %1021 = mul(%1020, %284): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03fb0ff5, /* %1022 = add(%1019, %1021):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03fc0003, // %1023 = mul(%1020, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ff0477, // %1024 = mul(%1023, %285): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03fe1001, /* %1025 = add(%1022, %1024):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03ff0003, // %1026 = mul(%1023, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0402047b, // %1027 = mul(%1026, %286): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0401100d, /* %1028 = add(%1025, %1027):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04020003, // %1029 = mul(%1026, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0405047f, // %1030 = mul(%1029, %287): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04041019, /* %1031 = add(%1028, %1030):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04050003, // %1032 = mul(%1029, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04080483, // %1033 = mul(%1032, %288): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04071025, /* %1034 = add(%1031, %1033):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04080003, // %1035 = mul(%1032, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x040b0487, // %1036 = mul(%1035, %289): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x040a1031, /* %1037 = add(%1034, %1036):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x040b0003, // %1038 = mul(%1035, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x040e048b, // %1039 = mul(%1038, %290): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x040d103d, /* %1040 = add(%1037, %1039):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x040e0003, // %1041 = mul(%1038, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0411048f, // %1042 = mul(%1041, %291): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04101049, /* %1043 = add(%1040, %1042):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04110003, // %1044 = mul(%1041, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04140493, // %1045 = mul(%1044, %292): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04131055, /* %1046 = add(%1043, %1045):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04140003, // %1047 = mul(%1044, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04170497, // %1048 = mul(%1047, %293): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04161061, /* %1049 = add(%1046, %1048):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04170003, // %1050 = mul(%1047, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x041a049b, // %1051 = mul(%1050, %294): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0419106d, /* %1052 = add(%1049, %1051):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x041a0003, // %1053 = mul(%1050, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x041d049f, // %1054 = mul(%1053, %295): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x041c1079, /* %1055 = add(%1052, %1054):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x041d0003, // %1056 = mul(%1053, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042004a3, // %1057 = mul(%1056, %296): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x041f1085, /* %1058 = add(%1055, %1057):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04200003, // %1059 = mul(%1056, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042304a7, // %1060 = mul(%1059, %297): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04221091, /* %1061 = add(%1058, %1060):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04230003, // %1062 = mul(%1059, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042604ab, // %1063 = mul(%1062, %298): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0425109d, /* %1064 = add(%1061, %1063):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04260003, // %1065 = mul(%1062, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042904af, // %1066 = mul(%1065, %299): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x042810a9, /* %1067 = add(%1064, %1066):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04290003, // %1068 = mul(%1065, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042c04b3, // %1069 = mul(%1068, %300): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x042b10b5, /* %1070 = add(%1067, %1069):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x042c0003, // %1071 = mul(%1068, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042f04b7, // %1072 = mul(%1071, %301): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x042e10c1, /* %1073 = add(%1070, %1072):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x042f0003, // %1074 = mul(%1071, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043204bb, // %1075 = mul(%1074, %302): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043110cd, /* %1076 = add(%1073, %1075):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04320003, // %1077 = mul(%1074, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043504bf, // %1078 = mul(%1077, %303): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043410d9, /* %1079 = add(%1076, %1078):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04350003, // %1080 = mul(%1077, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043804c3, // %1081 = mul(%1080, %304): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043710e5, /* %1082 = add(%1079, %1081):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04380003, // %1083 = mul(%1080, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043b04c7, // %1084 = mul(%1083, %305): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043a10f1, /* %1085 = add(%1082, %1084):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x043b0003, // %1086 = mul(%1083, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043e04cb, // %1087 = mul(%1086, %306): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043d10fd, /* %1088 = add(%1085, %1087):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x043e0003, // %1089 = mul(%1086, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x044104cf, // %1090 = mul(%1089, %307): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04401109, /* %1091 = add(%1088, %1090):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04410003, // %1092 = mul(%1089, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x044404d3, // %1093 = mul(%1092, %308): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04431115, /* %1094 = add(%1091, %1093):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04440003, // %1095 = mul(%1092, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04470073, // %1096 = mul(%1095, %28): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04470003, // %1097 = mul(%1095, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x04490077, // %1098 = mul(%1097, %29): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04481129, /* %1099 = add(%1096, %1098):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04490003, // %1100 = mul(%1097, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x044c007b, // %1101 = mul(%1100, %30): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x044b1135, /* %1102 = add(%1099, %1101):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x044c0003, // %1103 = mul(%1100, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x044f007f, // %1104 = mul(%1103, %31): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x044e1141, /* %1105 = add(%1102, %1104):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x044f0003, // %1106 = mul(%1103, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x04520083, // %1107 = mul(%1106, %32): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x0451114d, /* %1108 = add(%1105, %1107):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04520003, // %1109 = mul(%1106, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x04550087, // %1110 = mul(%1109, %33): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04541159, /* %1111 = add(%1108, %1110):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04550003, // %1112 = mul(%1109, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x0458008b, // %1113 = mul(%1112, %34): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04571165, /* %1114 = add(%1111, %1113):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04580003, // %1115 = mul(%1112, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x045b008f, // %1116 = mul(%1115, %35): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x045a1171, /* %1117 = add(%1114, %1116):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x045b0003, // %1118 = mul(%1115, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x045e0093, // %1119 = mul(%1118, %36): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x045d117d, /* %1120 = add(%1117, %1119):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x045e0003, // %1121 = mul(%1118, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x04610097, // %1122 = mul(%1121, %37): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04601189, /* %1123 = add(%1120, %1122):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04610003, // %1124 = mul(%1121, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x0464009b, // %1125 = mul(%1124, %38): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04631195, /* %1126 = add(%1123, %1125):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04640003, // %1127 = mul(%1124, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x0467009f, // %1128 = mul(%1127, %39): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x046611a1, /* %1129 = add(%1126, %1128):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04670003, // %1130 = mul(%1127, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x046a00a3, // %1131 = mul(%1130, %40): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x046911ad, /* %1132 = add(%1129, %1131):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x046a0003, // %1133 = mul(%1130, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x046d00a7, // %1134 = mul(%1133, %41): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x046c11b9, /* %1135 = add(%1132, %1134):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x046d0003, // %1136 = mul(%1133, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x047000ab, // %1137 = mul(%1136, %42): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x046f11c5, /* %1138 = add(%1135, %1137):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04700003, // %1139 = mul(%1136, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x047300af, // %1140 = mul(%1139, %43): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x047211d1, /* %1141 = add(%1138, %1140):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x03870012, // %1142 = sub(%903, %4): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0002000e, // %1143 = sub(%2, %3): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04770108, // %1144 = inv(%1143): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x047611e3, /* %1145 = mul(%1142, %1144):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x03750016, // %1146 = sub(%885, %5): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0006000b, // %1147 = mul(%6, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x047a11ee, /* %1148 = sub(%1146, %1147):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00030007, // %1149 = mul(%3, %1): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000211f6, // %1150 = sub(%2, %1149): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x047711fb, /* %1151 = mul(%1143, %1150):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x047f0108, // %1152 = inv(%1151): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x047c1203, /* %1153 = mul(%1148, %1152):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x04791205, /* %1154 = add(%1145, %1153):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x035d001e, // %1155 = sub(%861, %7): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0008000b, // %1156 = mul(%8, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04831212, /* %1157 = sub(%1155, %1156):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0002000b, // %1158 = mul(%2, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x0009121b, // %1159 = mul(%9, %1158): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x0485121e, /* %1160 = sub(%1157, %1159):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00010007, // %1161 = mul(%1, %1): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x00031227, // %1162 = mul(%3, %1161): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002122a, // %1163 = sub(%2, %1162): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x047f122f, /* %1164 = mul(%1151, %1163):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x048c0108, // %1165 = inv(%1164): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04881237, /* %1166 = mul(%1160, %1165):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x04821239, /* %1167 = add(%1154, %1166):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x0446002a, // %1168 = sub(%1094, %10): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x000b000b, // %1169 = mul(%11, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04901246, /* %1170 = sub(%1168, %1169):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x000c121b, // %1171 = mul(%12, %1158): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x0492124e, /* %1172 = sub(%1170, %1171):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0002121b, // %1173 = mul(%2, %1158): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x000d1257, // %1174 = mul(%13, %1173): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x0494125a, /* %1175 = sub(%1172, %1174):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0486121b, /* %1176 = mul(%1158, %1158):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0) */
    0x000e1263, // %1177 = mul(%14, %1176): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04971266, /* %1178 = sub(%1175, %1177):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00021263, // %1179 = mul(%2, %1176): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x000f126f, // %1180 = mul(%15, %1179): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x049a1272, /* %1181 = sub(%1178, %1180):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00011227, // %1182 = mul(%1, %1161): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0003127b, // %1183 = mul(%3, %1182): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002127e, // %1184 = sub(%2, %1183): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x048c1283, /* %1185 = mul(%1164, %1184):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04891227, /* %1186 = mul(%1161, %1161):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x0003128b, // %1187 = mul(%3, %1186): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002128e, // %1188 = sub(%2, %1187): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04a11293, /* %1189 = mul(%1185, %1188):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04a2128b, /* %1190 = mul(%1186, %1186):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x04a6129b, /* %1191 = mul(%1190, %1190):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x0001129f, // %1192 = mul(%1, %1191): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04a812a3, /* %1193 = mul(%1192, %1192):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x04a912a7, /* %1194 = mul(%1193, %1193):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x000312ab, // %1195 = mul(%3, %1194): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000212ae, // %1196 = sub(%2, %1195): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04a512b3, /* %1197 = mul(%1189, %1196):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04ad0108, // %1198 = inv(%1197): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x049d12bb, /* %1199 = mul(%1181, %1198):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x048f12bd, /* %1200 = add(%1167, %1199):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x02350042, // %1201 = sub(%565, %16): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0011000b, // %1202 = mul(%17, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04b112ca, /* %1203 = sub(%1201, %1202):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0012121b, // %1204 = mul(%18, %1158): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04b312d2, /* %1205 = sub(%1203, %1204):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00131257, // %1206 = mul(%19, %1173): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04b512da, /* %1207 = sub(%1205, %1206):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00141263, // %1208 = mul(%20, %1176): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04b712e2, /* %1209 = sub(%1207, %1208):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0015126f, // %1210 = mul(%21, %1179): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04b912ea, /* %1211 = sub(%1209, %1210):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x049e127b, /* %1212 = mul(%1182, %1182):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x000112f3, // %1213 = mul(%1, %1212): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000312f7, // %1214 = mul(%3, %1213): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000212fa, // %1215 = sub(%2, %1214): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x048c12ff, /* %1216 = mul(%1164, %1215):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04bd12f7, /* %1217 = mul(%1213, %1213):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x00011307, // %1218 = mul(%1, %1217): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0003130b, // %1219 = mul(%3, %1218): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002130e, // %1220 = sub(%2, %1219): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04c01313, /* %1221 = mul(%1216, %1220):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x0003129f, // %1222 = mul(%3, %1191): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002131a, // %1223 = sub(%2, %1222): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04c5131f, /* %1224 = mul(%1221, %1223):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04c80108, // %1225 = inv(%1224): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04bb1327, /* %1226 = mul(%1211, %1225):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x04b01329, /* %1227 = add(%1200, %1226):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x02da005a, // %1228 = sub(%730, %22): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0017000b, // %1229 = mul(%23, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04cc1336, /* %1230 = sub(%1228, %1229):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0018121b, // %1231 = mul(%24, %1158): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04ce133e, /* %1232 = sub(%1230, %1231):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00191257, // %1233 = mul(%25, %1173): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04d01346, /* %1234 = sub(%1232, %1233):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x001a1263, // %1235 = mul(%26, %1176): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04d2134e, /* %1236 = sub(%1234, %1235):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0477122f, /* %1237 = mul(%1143, %1163):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04d512ff, /* %1238 = mul(%1237, %1215):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04d61313, /* %1239 = mul(%1238, %1220):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04d7131f, /* %1240 = mul(%1239, %1223):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04d80108, // %1241 = inv(%1240): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04d41367, /* %1242 = mul(%1236, %1241):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x04cb1369, /* %1243 = add(%1227, %1242):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x0475006e, // %1244 = sub(%1141, %27): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":181:0)
    0x0003000f, // %1245 = mul(%3, %3): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":182:0)
    0x04dd1377, /* %1246 = mul(%1245, %1245):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":182:0) */
    0x0002137a, // %1247 = sub(%2, %1246): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":182:0)
    0x04df0108, // %1248 = inv(%1247): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":184:0)
    0x04dc1383, /* %1249 = mul(%1244, %1248):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":184:0) */
    0x04db1385, /* %1250 = add(%1243, %1249):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":184:0) */
    0x00000704, // set($0x0000, 0x07): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":186:0)
];

#[inline(always)]
pub fn verify_taps_rv32im(
    arg0: &[u32; 4 * EXT_ELEM_SIZE],
    arg1: &[u32; 24 * EXT_ELEM_SIZE],
    arg2: &[u32; 16 * EXT_ELEM_SIZE],
    arg3: &[u32; 36 * EXT_ELEM_SIZE],
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
