// Copyright (c) 2022 RISC Zero, Inc.
//
// All rights reserved.

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
    0x000000b7, // %307 = mul(%0, %45): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x002c04cd, // %308 = add(%44, %307): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x00000003, // %309 = mul(%0, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x013500bb, // %310 = mul(%309, %46): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x013404d9, // %311 = add(%308, %310): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01350003, // %312 = mul(%309, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x013800bf, // %313 = mul(%312, %47): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x013704e5, // %314 = add(%311, %313): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01380003, // %315 = mul(%312, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x013b00c3, // %316 = mul(%315, %48): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x013a04f1, // %317 = add(%314, %316): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x013b0003, // %318 = mul(%315, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x013e00c7, // %319 = mul(%318, %49): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x013d04fd, // %320 = add(%317, %319): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x013e0003, // %321 = mul(%318, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014100cb, // %322 = mul(%321, %50): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01400509, // %323 = add(%320, %322): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01410003, // %324 = mul(%321, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014400cf, // %325 = mul(%324, %51): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01430515, // %326 = add(%323, %325): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01440003, // %327 = mul(%324, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014700d3, // %328 = mul(%327, %52): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01470003, // %329 = mul(%327, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014900d7, // %330 = mul(%329, %53): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01480529, // %331 = add(%328, %330): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01490003, // %332 = mul(%329, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014c00db, // %333 = mul(%332, %54): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x014b0535, // %334 = add(%331, %333): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x014c0003, // %335 = mul(%332, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x014f00df, // %336 = mul(%335, %55): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x014e0541, // %337 = add(%334, %336): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x014f0003, // %338 = mul(%335, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015200e3, // %339 = mul(%338, %56): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0151054d, // %340 = add(%337, %339): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01520003, // %341 = mul(%338, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015500e7, // %342 = mul(%341, %57): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01540559, // %343 = add(%340, %342): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01550003, // %344 = mul(%341, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015800eb, // %345 = mul(%344, %58): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01570565, // %346 = add(%343, %345): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01580003, // %347 = mul(%344, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015b00ef, // %348 = mul(%347, %59): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x015a0571, // %349 = add(%346, %348): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x015b0003, // %350 = mul(%347, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x015e00f3, // %351 = mul(%350, %60): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x015d057d, // %352 = add(%349, %351): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x015e0003, // %353 = mul(%350, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016100f7, // %354 = mul(%353, %61): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01600589, // %355 = add(%352, %354): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01610003, // %356 = mul(%353, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016400fb, // %357 = mul(%356, %62): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01630595, // %358 = add(%355, %357): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01640003, // %359 = mul(%356, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016700ff, // %360 = mul(%359, %63): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x016605a1, // %361 = add(%358, %360): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01670003, // %362 = mul(%359, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016a0103, // %363 = mul(%362, %64): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x016905ad, // %364 = add(%361, %363): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x016a0003, // %365 = mul(%362, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x016d0107, // %366 = mul(%365, %65): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x016c05b9, // %367 = add(%364, %366): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x016d0003, // %368 = mul(%365, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0170010b, // %369 = mul(%368, %66): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x016f05c5, // %370 = add(%367, %369): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01700003, // %371 = mul(%368, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0173010f, // %372 = mul(%371, %67): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017205d1, // %373 = add(%370, %372): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01730003, // %374 = mul(%371, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01760113, // %375 = mul(%374, %68): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017505dd, // %376 = add(%373, %375): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01760003, // %377 = mul(%374, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01790117, // %378 = mul(%377, %69): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017805e9, // %379 = add(%376, %378): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01790003, // %380 = mul(%377, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x017c011b, // %381 = mul(%380, %70): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017b05f5, // %382 = add(%379, %381): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x017c0003, // %383 = mul(%380, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x017f011f, // %384 = mul(%383, %71): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x017e0601, // %385 = add(%382, %384): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x017f0003, // %386 = mul(%383, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01820123, // %387 = mul(%386, %72): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0181060d, // %388 = add(%385, %387): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01820003, // %389 = mul(%386, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01850127, // %390 = mul(%389, %73): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01840619, // %391 = add(%388, %390): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01850003, // %392 = mul(%389, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0188012b, // %393 = mul(%392, %74): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01870625, // %394 = add(%391, %393): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01880003, // %395 = mul(%392, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x018b012f, // %396 = mul(%395, %75): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x018a0631, // %397 = add(%394, %396): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x018b0003, // %398 = mul(%395, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x018e0133, // %399 = mul(%398, %76): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x018d063d, // %400 = add(%397, %399): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x018e0003, // %401 = mul(%398, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01910137, // %402 = mul(%401, %77): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01900649, // %403 = add(%400, %402): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01910003, // %404 = mul(%401, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0194013b, // %405 = mul(%404, %78): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01930655, // %406 = add(%403, %405): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01940003, // %407 = mul(%404, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0197013f, // %408 = mul(%407, %79): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01960661, // %409 = add(%406, %408): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01970003, // %410 = mul(%407, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x019a0143, // %411 = mul(%410, %80): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0199066d, // %412 = add(%409, %411): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x019a0003, // %413 = mul(%410, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x019d0147, // %414 = mul(%413, %81): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x019c0679, // %415 = add(%412, %414): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x019d0003, // %416 = mul(%413, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01a0014b, // %417 = mul(%416, %82): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01460685, // %418 = add(%326, %417): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01a00003, // %419 = mul(%416, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01a3014f, // %420 = mul(%419, %83): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x019f0691, // %421 = add(%415, %420): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01a30003, // %422 = mul(%419, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01a60153, // %423 = mul(%422, %84): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01a5069d, // %424 = add(%421, %423): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01a60003, // %425 = mul(%422, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01a90157, // %426 = mul(%425, %85): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01a806a9, // %427 = add(%424, %426): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01a90003, // %428 = mul(%425, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ac015b, // %429 = mul(%428, %86): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ab06b5, // %430 = add(%427, %429): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ac0003, // %431 = mul(%428, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01af015f, // %432 = mul(%431, %87): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ae06c1, // %433 = add(%430, %432): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01af0003, // %434 = mul(%431, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01b20163, // %435 = mul(%434, %88): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01b106cd, // %436 = add(%433, %435): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01b20003, // %437 = mul(%434, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01b50167, // %438 = mul(%437, %89): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01b406d9, // %439 = add(%436, %438): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01b50003, // %440 = mul(%437, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01b8016b, // %441 = mul(%440, %90): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01b706e5, // %442 = add(%439, %441): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01b80003, // %443 = mul(%440, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01bb016f, // %444 = mul(%443, %91): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ba06f1, // %445 = add(%442, %444): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01bb0003, // %446 = mul(%443, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01be0173, // %447 = mul(%446, %92): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01bd06fd, // %448 = add(%445, %447): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01be0003, // %449 = mul(%446, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01c10177, // %450 = mul(%449, %93): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01c00709, // %451 = add(%448, %450): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01c10003, // %452 = mul(%449, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01c4017b, // %453 = mul(%452, %94): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01c30715, // %454 = add(%451, %453): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01c40003, // %455 = mul(%452, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01c7017f, // %456 = mul(%455, %95): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01a20721, // %457 = add(%418, %456): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01c70003, // %458 = mul(%455, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ca0183, // %459 = mul(%458, %96): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01c9072d, // %460 = add(%457, %459): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ca0003, // %461 = mul(%458, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01cd0187, // %462 = mul(%461, %97): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01cc0739, // %463 = add(%460, %462): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01cd0003, // %464 = mul(%461, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01d0018b, // %465 = mul(%464, %98): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01cf0745, // %466 = add(%463, %465): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01d00003, // %467 = mul(%464, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01d3018f, // %468 = mul(%467, %99): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01d20751, // %469 = add(%466, %468): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01d30003, // %470 = mul(%467, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01d60193, // %471 = mul(%470, %100): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01d5075d, // %472 = add(%469, %471): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01d60003, // %473 = mul(%470, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01d90197, // %474 = mul(%473, %101): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01d80769, // %475 = add(%472, %474): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01d90003, // %476 = mul(%473, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01dc019b, // %477 = mul(%476, %102): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01db0775, // %478 = add(%475, %477): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01dc0003, // %479 = mul(%476, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01df019f, // %480 = mul(%479, %103): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01de0781, // %481 = add(%478, %480): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01df0003, // %482 = mul(%479, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01e201a3, // %483 = mul(%482, %104): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01c6078d, // %484 = add(%454, %483): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01e20003, // %485 = mul(%482, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01e501a7, // %486 = mul(%485, %105): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01e10799, // %487 = add(%481, %486): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01e50003, // %488 = mul(%485, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01e801ab, // %489 = mul(%488, %106): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01e707a5, // %490 = add(%487, %489): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01e80003, // %491 = mul(%488, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01eb01af, // %492 = mul(%491, %107): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ea07b1, // %493 = add(%490, %492): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01eb0003, // %494 = mul(%491, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01ee01b3, // %495 = mul(%494, %108): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01e407bd, // %496 = add(%484, %495): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01ee0003, // %497 = mul(%494, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01f101b7, // %498 = mul(%497, %109): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01f007c9, // %499 = add(%496, %498): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01f10003, // %500 = mul(%497, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01f401bb, // %501 = mul(%500, %110): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01f307d5, // %502 = add(%499, %501): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01f40003, // %503 = mul(%500, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01f701bf, // %504 = mul(%503, %111): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01f607e1, // %505 = add(%502, %504): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01f70003, // %506 = mul(%503, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01fa01c3, // %507 = mul(%506, %112): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01f907ed, // %508 = add(%505, %507): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01fa0003, // %509 = mul(%506, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x01fd01c7, // %510 = mul(%509, %113): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01fc07f9, // %511 = add(%508, %510): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x01fd0003, // %512 = mul(%509, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020001cb, // %513 = mul(%512, %114): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02000003, // %514 = mul(%512, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020201cf, // %515 = mul(%514, %115): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0201080d, // %516 = add(%513, %515): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02020003, // %517 = mul(%514, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020501d3, // %518 = mul(%517, %116): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02040819, // %519 = add(%516, %518): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02050003, // %520 = mul(%517, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020801d7, // %521 = mul(%520, %117): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02070825, // %522 = add(%519, %521): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02080003, // %523 = mul(%520, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020b01db, // %524 = mul(%523, %118): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x020a0831, // %525 = add(%522, %524): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x020b0003, // %526 = mul(%523, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x020e01df, // %527 = mul(%526, %119): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x020d083d, // %528 = add(%525, %527): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x020e0003, // %529 = mul(%526, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021101e3, // %530 = mul(%529, %120): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02110003, // %531 = mul(%529, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021301e7, // %532 = mul(%531, %121): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02120851, // %533 = add(%530, %532): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02130003, // %534 = mul(%531, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021601eb, // %535 = mul(%534, %122): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0215085d, // %536 = add(%533, %535): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02160003, // %537 = mul(%534, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021901ef, // %538 = mul(%537, %123): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02180869, // %539 = add(%536, %538): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02190003, // %540 = mul(%537, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021c01f3, // %541 = mul(%540, %124): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x021b0875, // %542 = add(%539, %541): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x021c0003, // %543 = mul(%540, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x021f01f7, // %544 = mul(%543, %125): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x021e0881, // %545 = add(%542, %544): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x021f0003, // %546 = mul(%543, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022201fb, // %547 = mul(%546, %126): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0221088d, // %548 = add(%545, %547): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02220003, // %549 = mul(%546, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022501ff, // %550 = mul(%549, %127): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02240899, // %551 = add(%548, %550): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02250003, // %552 = mul(%549, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02280203, // %553 = mul(%552, %128): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x022708a5, // %554 = add(%551, %553): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02280003, // %555 = mul(%552, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022b0207, // %556 = mul(%555, %129): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x022a08b1, // %557 = add(%554, %556): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x022b0003, // %558 = mul(%555, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x022e020b, // %559 = mul(%558, %130): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x022d08bd, // %560 = add(%557, %559): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x022e0003, // %561 = mul(%558, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0231020f, // %562 = mul(%561, %131): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023008c9, // %563 = add(%560, %562): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02310003, // %564 = mul(%561, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02340213, // %565 = mul(%564, %132): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x021008d5, // %566 = add(%528, %565): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02340003, // %567 = mul(%564, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02370217, // %568 = mul(%567, %133): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023608e1, // %569 = add(%566, %568): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02370003, // %570 = mul(%567, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x023a021b, // %571 = mul(%570, %134): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023908ed, // %572 = add(%569, %571): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x023a0003, // %573 = mul(%570, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x023d021f, // %574 = mul(%573, %135): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023c08f9, // %575 = add(%572, %574): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x023d0003, // %576 = mul(%573, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02400223, // %577 = mul(%576, %136): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ff0905, // %578 = add(%511, %577): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02400003, // %579 = mul(%576, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02430227, // %580 = mul(%579, %137): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02420911, // %581 = add(%578, %580): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02430003, // %582 = mul(%579, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0246022b, // %583 = mul(%582, %138): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0245091d, // %584 = add(%581, %583): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02460003, // %585 = mul(%582, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0249022f, // %586 = mul(%585, %139): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02480929, // %587 = add(%584, %586): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02490003, // %588 = mul(%585, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x024c0233, // %589 = mul(%588, %140): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x024b0935, // %590 = add(%587, %589): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x024c0003, // %591 = mul(%588, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x024f0237, // %592 = mul(%591, %141): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x024e0941, // %593 = add(%590, %592): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x024f0003, // %594 = mul(%591, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0252023b, // %595 = mul(%594, %142): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0251094d, // %596 = add(%593, %595): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02520003, // %597 = mul(%594, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0255023f, // %598 = mul(%597, %143): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02540959, // %599 = add(%596, %598): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02550003, // %600 = mul(%597, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02580243, // %601 = mul(%600, %144): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02570965, // %602 = add(%599, %601): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02580003, // %603 = mul(%600, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x025b0247, // %604 = mul(%603, %145): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x01ed0971, // %605 = add(%493, %604): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x025b0003, // %606 = mul(%603, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x025e024b, // %607 = mul(%606, %146): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x025d097d, // %608 = add(%605, %607): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x025e0003, // %609 = mul(%606, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0261024f, // %610 = mul(%609, %147): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x025a0989, // %611 = add(%602, %610): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02610003, // %612 = mul(%609, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02640253, // %613 = mul(%612, %148): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02630995, // %614 = add(%611, %613): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02640003, // %615 = mul(%612, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02670257, // %616 = mul(%615, %149): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x026609a1, // %617 = add(%614, %616): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02670003, // %618 = mul(%615, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x026a025b, // %619 = mul(%618, %150): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x026909ad, // %620 = add(%617, %619): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x026a0003, // %621 = mul(%618, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x026d025f, // %622 = mul(%621, %151): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x026c09b9, // %623 = add(%620, %622): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x026d0003, // %624 = mul(%621, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02700263, // %625 = mul(%624, %152): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x026f09c5, // %626 = add(%623, %625): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02700003, // %627 = mul(%624, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02730267, // %628 = mul(%627, %153): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027209d1, // %629 = add(%626, %628): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02730003, // %630 = mul(%627, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0276026b, // %631 = mul(%630, %154): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027509dd, // %632 = add(%629, %631): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02760003, // %633 = mul(%630, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0279026f, // %634 = mul(%633, %155): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027809e9, // %635 = add(%632, %634): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02790003, // %636 = mul(%633, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x027c0273, // %637 = mul(%636, %156): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027b09f5, // %638 = add(%635, %637): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x027c0003, // %639 = mul(%636, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x027f0277, // %640 = mul(%639, %157): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x027e0a01, // %641 = add(%638, %640): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x027f0003, // %642 = mul(%639, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0282027b, // %643 = mul(%642, %158): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02810a0d, // %644 = add(%641, %643): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02820003, // %645 = mul(%642, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0285027f, // %646 = mul(%645, %159): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02840a19, // %647 = add(%644, %646): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02850003, // %648 = mul(%645, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02880283, // %649 = mul(%648, %160): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02870a25, // %650 = add(%647, %649): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02880003, // %651 = mul(%648, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x028b0287, // %652 = mul(%651, %161): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x028a0a31, // %653 = add(%650, %652): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x028b0003, // %654 = mul(%651, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x028e028b, // %655 = mul(%654, %162): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x028d0a3d, // %656 = add(%653, %655): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x028e0003, // %657 = mul(%654, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0291028f, // %658 = mul(%657, %163): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02900a49, // %659 = add(%656, %658): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02910003, // %660 = mul(%657, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02940293, // %661 = mul(%660, %164): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02930a55, // %662 = add(%659, %661): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02940003, // %663 = mul(%660, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02970297, // %664 = mul(%663, %165): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02960a61, // %665 = add(%662, %664): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02970003, // %666 = mul(%663, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x029a029b, // %667 = mul(%666, %166): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02990a6d, // %668 = add(%665, %667): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x029a0003, // %669 = mul(%666, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x029d029f, // %670 = mul(%669, %167): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02600a79, // %671 = add(%608, %670): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x029d0003, // %672 = mul(%669, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02a002a3, // %673 = mul(%672, %168): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x029f0a85, // %674 = add(%671, %673): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02a00003, // %675 = mul(%672, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02a302a7, // %676 = mul(%675, %169): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x029c0a91, // %677 = add(%668, %676): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02a30003, // %678 = mul(%675, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02a602ab, // %679 = mul(%678, %170): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02a50a9d, // %680 = add(%677, %679): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02a60003, // %681 = mul(%678, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02a902af, // %682 = mul(%681, %171): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02a80aa9, // %683 = add(%680, %682): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02a90003, // %684 = mul(%681, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ac02b3, // %685 = mul(%684, %172): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ab0ab5, // %686 = add(%683, %685): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ac0003, // %687 = mul(%684, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02af02b7, // %688 = mul(%687, %173): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ae0ac1, // %689 = add(%686, %688): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02af0003, // %690 = mul(%687, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02b202bb, // %691 = mul(%690, %174): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02b10acd, // %692 = add(%689, %691): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02b20003, // %693 = mul(%690, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02b502bf, // %694 = mul(%693, %175): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02b40ad9, // %695 = add(%692, %694): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02b50003, // %696 = mul(%693, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02b802c3, // %697 = mul(%696, %176): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02b70ae5, // %698 = add(%695, %697): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02b80003, // %699 = mul(%696, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02bb02c7, // %700 = mul(%699, %177): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x023f0af1, // %701 = add(%575, %700): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02bb0003, // %702 = mul(%699, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02be02cb, // %703 = mul(%702, %178): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02bd0afd, // %704 = add(%701, %703): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02be0003, // %705 = mul(%702, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02c102cf, // %706 = mul(%705, %179): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02c00b09, // %707 = add(%704, %706): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02c10003, // %708 = mul(%705, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02c402d3, // %709 = mul(%708, %180): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02c30b15, // %710 = add(%707, %709): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02c40003, // %711 = mul(%708, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02c702d7, // %712 = mul(%711, %181): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02c60b21, // %713 = add(%710, %712): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02c70003, // %714 = mul(%711, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ca02db, // %715 = mul(%714, %182): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02c90b2d, // %716 = add(%713, %715): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ca0003, // %717 = mul(%714, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02cd02df, // %718 = mul(%717, %183): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02cc0b39, // %719 = add(%716, %718): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02cd0003, // %720 = mul(%717, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02d002e3, // %721 = mul(%720, %184): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02cf0b45, // %722 = add(%719, %721): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02d00003, // %723 = mul(%720, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02d302e7, // %724 = mul(%723, %185): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02d20b51, // %725 = add(%722, %724): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02d30003, // %726 = mul(%723, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02d602eb, // %727 = mul(%726, %186): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02d50b5d, // %728 = add(%725, %727): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02d60003, // %729 = mul(%726, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02d902ef, // %730 = mul(%729, %187): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ba0b69, // %731 = add(%698, %730): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02d90003, // %732 = mul(%729, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02dc02f3, // %733 = mul(%732, %188): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02db0b75, // %734 = add(%731, %733): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02dc0003, // %735 = mul(%732, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02df02f7, // %736 = mul(%735, %189): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02de0b81, // %737 = add(%734, %736): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02df0003, // %738 = mul(%735, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02e202fb, // %739 = mul(%738, %190): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02a20b8d, // %740 = add(%674, %739): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02e20003, // %741 = mul(%738, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02e502ff, // %742 = mul(%741, %191): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02e40b99, // %743 = add(%740, %742): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02e50003, // %744 = mul(%741, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02e80303, // %745 = mul(%744, %192): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02e70ba5, // %746 = add(%743, %745): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02e80003, // %747 = mul(%744, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02eb0307, // %748 = mul(%747, %193): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ea0bb1, // %749 = add(%746, %748): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02eb0003, // %750 = mul(%747, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02ee030b, // %751 = mul(%750, %194): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ed0bbd, // %752 = add(%749, %751): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02ee0003, // %753 = mul(%750, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02f1030f, // %754 = mul(%753, %195): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02f00bc9, // %755 = add(%752, %754): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02f10003, // %756 = mul(%753, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02f40313, // %757 = mul(%756, %196): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02f30bd5, // %758 = add(%755, %757): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02f40003, // %759 = mul(%756, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02f70317, // %760 = mul(%759, %197): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02f60be1, // %761 = add(%758, %760): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02f70003, // %762 = mul(%759, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02fa031b, // %763 = mul(%762, %198): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02f90bed, // %764 = add(%761, %763): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02fa0003, // %765 = mul(%762, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x02fd031f, // %766 = mul(%765, %199): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02fc0bf9, // %767 = add(%764, %766): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x02fd0003, // %768 = mul(%765, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03000323, // %769 = mul(%768, %200): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02ff0c05, // %770 = add(%767, %769): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03000003, // %771 = mul(%768, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03030327, // %772 = mul(%771, %201): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03020c11, // %773 = add(%770, %772): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03030003, // %774 = mul(%771, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0306032b, // %775 = mul(%774, %202): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x02e10c1d, // %776 = add(%737, %775): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03060003, // %777 = mul(%774, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0309032f, // %778 = mul(%777, %203): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03080c29, // %779 = add(%776, %778): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03090003, // %780 = mul(%777, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x030c0333, // %781 = mul(%780, %204): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x030b0c35, // %782 = add(%779, %781): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x030c0003, // %783 = mul(%780, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x030f0337, // %784 = mul(%783, %205): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x030e0c41, // %785 = add(%782, %784): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x030f0003, // %786 = mul(%783, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0312033b, // %787 = mul(%786, %206): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03110c4d, // %788 = add(%785, %787): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03120003, // %789 = mul(%786, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0315033f, // %790 = mul(%789, %207): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03140c59, // %791 = add(%788, %790): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03150003, // %792 = mul(%789, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03180343, // %793 = mul(%792, %208): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03170c65, // %794 = add(%791, %793): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03180003, // %795 = mul(%792, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x031b0347, // %796 = mul(%795, %209): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x031a0c71, // %797 = add(%794, %796): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x031b0003, // %798 = mul(%795, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x031e034b, // %799 = mul(%798, %210): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x031d0c7d, // %800 = add(%797, %799): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x031e0003, // %801 = mul(%798, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0321034f, // %802 = mul(%801, %211): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03200c89, // %803 = add(%800, %802): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03210003, // %804 = mul(%801, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03240353, // %805 = mul(%804, %212): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03050c95, // %806 = add(%773, %805): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03240003, // %807 = mul(%804, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03270357, // %808 = mul(%807, %213): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03260ca1, // %809 = add(%806, %808): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03270003, // %810 = mul(%807, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x032a035b, // %811 = mul(%810, %214): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03290cad, // %812 = add(%809, %811): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x032a0003, // %813 = mul(%810, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x032d035f, // %814 = mul(%813, %215): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x032c0cb9, // %815 = add(%812, %814): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x032d0003, // %816 = mul(%813, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03300363, // %817 = mul(%816, %216): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03230cc5, // %818 = add(%803, %817): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03300003, // %819 = mul(%816, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03330367, // %820 = mul(%819, %217): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03320cd1, // %821 = add(%818, %820): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03330003, // %822 = mul(%819, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0336036b, // %823 = mul(%822, %218): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03350cdd, // %824 = add(%821, %823): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03360003, // %825 = mul(%822, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0339036f, // %826 = mul(%825, %219): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x032f0ce9, // %827 = add(%815, %826): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03390003, // %828 = mul(%825, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x033c0373, // %829 = mul(%828, %220): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x033b0cf5, // %830 = add(%827, %829): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x033c0003, // %831 = mul(%828, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x033f0377, // %832 = mul(%831, %221): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x033e0d01, // %833 = add(%830, %832): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x033f0003, // %834 = mul(%831, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0342037b, // %835 = mul(%834, %222): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03410d0d, // %836 = add(%833, %835): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03420003, // %837 = mul(%834, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0345037f, // %838 = mul(%837, %223): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03380d19, // %839 = add(%824, %838): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03450003, // %840 = mul(%837, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03480383, // %841 = mul(%840, %224): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03470d25, // %842 = add(%839, %841): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03480003, // %843 = mul(%840, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x034b0387, // %844 = mul(%843, %225): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03440d31, // %845 = add(%836, %844): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x034b0003, // %846 = mul(%843, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x034e038b, // %847 = mul(%846, %226): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x034d0d3d, // %848 = add(%845, %847): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x034e0003, // %849 = mul(%846, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0351038f, // %850 = mul(%849, %227): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03500d49, // %851 = add(%848, %850): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03510003, // %852 = mul(%849, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03540393, // %853 = mul(%852, %228): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03540003, // %854 = mul(%852, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03560397, // %855 = mul(%854, %229): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03550d5d, // %856 = add(%853, %855): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03560003, // %857 = mul(%854, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0359039b, // %858 = mul(%857, %230): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03530d69, // %859 = add(%851, %858): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03590003, // %860 = mul(%857, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x035c039f, // %861 = mul(%860, %231): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x034a0d75, // %862 = add(%842, %861): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x035c0003, // %863 = mul(%860, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x035f03a3, // %864 = mul(%863, %232): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x035b0d81, // %865 = add(%859, %864): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x035f0003, // %866 = mul(%863, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036203a7, // %867 = mul(%866, %233): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03610d8d, // %868 = add(%865, %867): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03620003, // %869 = mul(%866, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036503ab, // %870 = mul(%869, %234): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03640d99, // %871 = add(%868, %870): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03650003, // %872 = mul(%869, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036803af, // %873 = mul(%872, %235): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03670da5, // %874 = add(%871, %873): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03680003, // %875 = mul(%872, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036b03b3, // %876 = mul(%875, %236): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x036a0db1, // %877 = add(%874, %876): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x036b0003, // %878 = mul(%875, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x036e03b7, // %879 = mul(%878, %237): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x035e0dbd, // %880 = add(%862, %879): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x036e0003, // %881 = mul(%878, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037103bb, // %882 = mul(%881, %238): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03700dc9, // %883 = add(%880, %882): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03710003, // %884 = mul(%881, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037403bf, // %885 = mul(%884, %239): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03730dd5, // %886 = add(%883, %885): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03740003, // %887 = mul(%884, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037703c3, // %888 = mul(%887, %240): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03760de1, // %889 = add(%886, %888): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03770003, // %890 = mul(%887, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037a03c7, // %891 = mul(%890, %241): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03790ded, // %892 = add(%889, %891): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x037a0003, // %893 = mul(%890, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x037d03cb, // %894 = mul(%893, %242): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x037c0df9, // %895 = add(%892, %894): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x037d0003, // %896 = mul(%893, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038003cf, // %897 = mul(%896, %243): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03800003, // %898 = mul(%896, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038203d3, // %899 = mul(%898, %244): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03810e0d, // %900 = add(%897, %899): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03820003, // %901 = mul(%898, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038503d7, // %902 = mul(%901, %245): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03840e19, // %903 = add(%900, %902): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03850003, // %904 = mul(%901, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038803db, // %905 = mul(%904, %246): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03870e25, // %906 = add(%903, %905): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03880003, // %907 = mul(%904, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038b03df, // %908 = mul(%907, %247): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x038a0e31, // %909 = add(%906, %908): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x038b0003, // %910 = mul(%907, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x038e03e3, // %911 = mul(%910, %248): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x038d0e3d, // %912 = add(%909, %911): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x038e0003, // %913 = mul(%910, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039103e7, // %914 = mul(%913, %249): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03900e49, // %915 = add(%912, %914): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03910003, // %916 = mul(%913, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039403eb, // %917 = mul(%916, %250): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03930e55, // %918 = add(%915, %917): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03940003, // %919 = mul(%916, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039703ef, // %920 = mul(%919, %251): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03960e61, // %921 = add(%918, %920): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03970003, // %922 = mul(%919, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039a03f3, // %923 = mul(%922, %252): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03990e6d, // %924 = add(%921, %923): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x039a0003, // %925 = mul(%922, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x039d03f7, // %926 = mul(%925, %253): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x039c0e79, // %927 = add(%924, %926): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x039d0003, // %928 = mul(%925, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03a003fb, // %929 = mul(%928, %254): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x039f0e85, // %930 = add(%927, %929): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03a00003, // %931 = mul(%928, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03a303ff, // %932 = mul(%931, %255): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03a20e91, // %933 = add(%930, %932): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03a30003, // %934 = mul(%931, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03a60403, // %935 = mul(%934, %256): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03a50e9d, // %936 = add(%933, %935): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03a60003, // %937 = mul(%934, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03a90407, // %938 = mul(%937, %257): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03a80ea9, // %939 = add(%936, %938): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03a90003, // %940 = mul(%937, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ac040b, // %941 = mul(%940, %258): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ab0eb5, // %942 = add(%939, %941): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03ac0003, // %943 = mul(%940, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03af040f, // %944 = mul(%943, %259): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ae0ec1, // %945 = add(%942, %944): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03af0003, // %946 = mul(%943, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03b20413, // %947 = mul(%946, %260): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03b10ecd, // %948 = add(%945, %947): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03b20003, // %949 = mul(%946, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03b50417, // %950 = mul(%949, %261): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03b40ed9, // %951 = add(%948, %950): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03b50003, // %952 = mul(%949, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03b8041b, // %953 = mul(%952, %262): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03b70ee5, // %954 = add(%951, %953): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03b80003, // %955 = mul(%952, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03bb041f, // %956 = mul(%955, %263): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ba0ef1, // %957 = add(%954, %956): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03bb0003, // %958 = mul(%955, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03be0423, // %959 = mul(%958, %264): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03bd0efd, // %960 = add(%957, %959): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03be0003, // %961 = mul(%958, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03c10427, // %962 = mul(%961, %265): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03c00f09, // %963 = add(%960, %962): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03c10003, // %964 = mul(%961, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03c4042b, // %965 = mul(%964, %266): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03c30f15, // %966 = add(%963, %965): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03c40003, // %967 = mul(%964, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03c7042f, // %968 = mul(%967, %267): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03c60f21, // %969 = add(%966, %968): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03c70003, // %970 = mul(%967, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ca0433, // %971 = mul(%970, %268): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03c90f2d, // %972 = add(%969, %971): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03ca0003, // %973 = mul(%970, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03cd0437, // %974 = mul(%973, %269): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03cc0f39, // %975 = add(%972, %974): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03cd0003, // %976 = mul(%973, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03d0043b, // %977 = mul(%976, %270): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03cf0f45, // %978 = add(%975, %977): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03d00003, // %979 = mul(%976, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03d3043f, // %980 = mul(%979, %271): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03d20f51, // %981 = add(%978, %980): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03d30003, // %982 = mul(%979, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03d60443, // %983 = mul(%982, %272): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03d50f5d, // %984 = add(%981, %983): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03d60003, // %985 = mul(%982, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03d90447, // %986 = mul(%985, %273): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03d80f69, // %987 = add(%984, %986): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03d90003, // %988 = mul(%985, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03dc044b, // %989 = mul(%988, %274): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03db0f75, // %990 = add(%987, %989): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03dc0003, // %991 = mul(%988, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03df044f, // %992 = mul(%991, %275): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03de0f81, // %993 = add(%990, %992): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03df0003, // %994 = mul(%991, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03e20453, // %995 = mul(%994, %276): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03e10f8d, // %996 = add(%993, %995): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03e20003, // %997 = mul(%994, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03e50457, // %998 = mul(%997, %277): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03e40f99, // %999 = add(%996, %998): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03e50003, // %1000 = mul(%997, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03e8045b, // %1001 = mul(%1000, %278): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03e70fa5, // %1002 = add(%999, %1001): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0)
    0x03e80003, // %1003 = mul(%1000, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03eb045f, // %1004 = mul(%1003, %279): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ea0fb1, /* %1005 = add(%1002, %1004):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03eb0003, // %1006 = mul(%1003, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03ee0463, // %1007 = mul(%1006, %280): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ed0fbd, /* %1008 = add(%1005, %1007):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03ee0003, // %1009 = mul(%1006, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03f10467, // %1010 = mul(%1009, %281): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03f00fc9, /* %1011 = add(%1008, %1010):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03f10003, // %1012 = mul(%1009, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03f4046b, // %1013 = mul(%1012, %282): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03f30fd5, /* %1014 = add(%1011, %1013):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03f40003, // %1015 = mul(%1012, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03f7046f, // %1016 = mul(%1015, %283): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03f60fe1, /* %1017 = add(%1014, %1016):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03f70003, // %1018 = mul(%1015, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03fa0473, // %1019 = mul(%1018, %284): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03f90fed, /* %1020 = add(%1017, %1019):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03fa0003, // %1021 = mul(%1018, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x03fd0477, // %1022 = mul(%1021, %285): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03fc0ff9, /* %1023 = add(%1020, %1022):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x03fd0003, // %1024 = mul(%1021, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0400047b, // %1025 = mul(%1024, %286): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x03ff1005, /* %1026 = add(%1023, %1025):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04000003, // %1027 = mul(%1024, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0403047f, // %1028 = mul(%1027, %287): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04021011, /* %1029 = add(%1026, %1028):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04030003, // %1030 = mul(%1027, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04060483, // %1031 = mul(%1030, %288): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0405101d, /* %1032 = add(%1029, %1031):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04060003, // %1033 = mul(%1030, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04090487, // %1034 = mul(%1033, %289): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04081029, /* %1035 = add(%1032, %1034):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04090003, // %1036 = mul(%1033, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x040c048b, // %1037 = mul(%1036, %290): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x040b1035, /* %1038 = add(%1035, %1037):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x040c0003, // %1039 = mul(%1036, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x040f048f, // %1040 = mul(%1039, %291): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x040e1041, /* %1041 = add(%1038, %1040):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x040f0003, // %1042 = mul(%1039, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04120493, // %1043 = mul(%1042, %292): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x0411104d, /* %1044 = add(%1041, %1043):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04120003, // %1045 = mul(%1042, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04150497, // %1046 = mul(%1045, %293): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04141059, /* %1047 = add(%1044, %1046):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04150003, // %1048 = mul(%1045, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0418049b, // %1049 = mul(%1048, %294): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04171065, /* %1050 = add(%1047, %1049):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04180003, // %1051 = mul(%1048, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x041b049f, // %1052 = mul(%1051, %295): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x041a1071, /* %1053 = add(%1050, %1052):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x041b0003, // %1054 = mul(%1051, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x041e04a3, // %1055 = mul(%1054, %296): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x041d107d, /* %1056 = add(%1053, %1055):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x041e0003, // %1057 = mul(%1054, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042104a7, // %1058 = mul(%1057, %297): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04201089, /* %1059 = add(%1056, %1058):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04210003, // %1060 = mul(%1057, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042404ab, // %1061 = mul(%1060, %298): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x04231095, /* %1062 = add(%1059, %1061):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04240003, // %1063 = mul(%1060, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042704af, // %1064 = mul(%1063, %299): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x042610a1, /* %1065 = add(%1062, %1064):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04270003, // %1066 = mul(%1063, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042a04b3, // %1067 = mul(%1066, %300): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x042910ad, /* %1068 = add(%1065, %1067):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x042a0003, // %1069 = mul(%1066, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042d04b7, // %1070 = mul(%1069, %301): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x042c10b9, /* %1071 = add(%1068, %1070):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x042d0003, // %1072 = mul(%1069, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043004bb, // %1073 = mul(%1072, %302): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x042f10c5, /* %1074 = add(%1071, %1073):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04300003, // %1075 = mul(%1072, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043304bf, // %1076 = mul(%1075, %303): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043210d1, /* %1077 = add(%1074, %1076):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04330003, // %1078 = mul(%1075, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043604c3, // %1079 = mul(%1078, %304): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043510dd, /* %1080 = add(%1077, %1079):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04360003, // %1081 = mul(%1078, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043904c7, // %1082 = mul(%1081, %305): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043810e9, /* %1083 = add(%1080, %1082):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x04390003, // %1084 = mul(%1081, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043c04cb, // %1085 = mul(%1084, %306): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":148:0)
    0x043b10f5, /* %1086 = add(%1083, %1085):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":146:0) */
    0x043c0003, // %1087 = mul(%1084, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043f0073, // %1088 = mul(%1087, %28): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x043f0003, // %1089 = mul(%1087, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x04410077, // %1090 = mul(%1089, %29): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04401109, /* %1091 = add(%1088, %1090):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04410003, // %1092 = mul(%1089, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x0444007b, // %1093 = mul(%1092, %30): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04431115, /* %1094 = add(%1091, %1093):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04440003, // %1095 = mul(%1092, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x0447007f, // %1096 = mul(%1095, %31): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04461121, /* %1097 = add(%1094, %1096):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04470003, // %1098 = mul(%1095, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x044a0083, // %1099 = mul(%1098, %32): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x0449112d, /* %1100 = add(%1097, %1099):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x044a0003, // %1101 = mul(%1098, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x044d0087, // %1102 = mul(%1101, %33): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x044c1139, /* %1103 = add(%1100, %1102):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x044d0003, // %1104 = mul(%1101, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x0450008b, // %1105 = mul(%1104, %34): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x044f1145, /* %1106 = add(%1103, %1105):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04500003, // %1107 = mul(%1104, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x0453008f, // %1108 = mul(%1107, %35): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04521151, /* %1109 = add(%1106, %1108):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04530003, // %1110 = mul(%1107, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x04560093, // %1111 = mul(%1110, %36): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x0455115d, /* %1112 = add(%1109, %1111):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04560003, // %1113 = mul(%1110, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x04590097, // %1114 = mul(%1113, %37): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04581169, /* %1115 = add(%1112, %1114):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04590003, // %1116 = mul(%1113, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x045c009b, // %1117 = mul(%1116, %38): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x045b1175, /* %1118 = add(%1115, %1117):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x045c0003, // %1119 = mul(%1116, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x045f009f, // %1120 = mul(%1119, %39): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x045e1181, /* %1121 = add(%1118, %1120):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x045f0003, // %1122 = mul(%1119, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x046200a3, // %1123 = mul(%1122, %40): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x0461118d, /* %1124 = add(%1121, %1123):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04620003, // %1125 = mul(%1122, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x046500a7, // %1126 = mul(%1125, %41): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x04641199, /* %1127 = add(%1124, %1126):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04650003, // %1128 = mul(%1125, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x046800ab, // %1129 = mul(%1128, %42): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x046711a5, /* %1130 = add(%1127, %1129):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x04680003, // %1131 = mul(%1128, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":154:0)
    0x046b00af, // %1132 = mul(%1131, %43): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0)
    0x046a11b1, /* %1133 = add(%1130, %1132):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":153:0) */
    0x037f0012, // %1134 = sub(%895, %4): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0002000e, // %1135 = sub(%2, %3): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x046f0108, // %1136 = inv(%1135): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x046e11c3, /* %1137 = mul(%1134, %1136):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x036d0016, // %1138 = sub(%877, %5): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0006000b, // %1139 = mul(%6, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x047211ce, /* %1140 = sub(%1138, %1139):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00030007, // %1141 = mul(%3, %1): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000211d6, // %1142 = sub(%2, %1141): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x046f11db, /* %1143 = mul(%1135, %1142):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04770108, // %1144 = inv(%1143): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x047411e3, /* %1145 = mul(%1140, %1144):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x047111e5, /* %1146 = add(%1137, %1145):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x0358001e, // %1147 = sub(%856, %7): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0008000b, // %1148 = mul(%8, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x047b11f2, /* %1149 = sub(%1147, %1148):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0002000b, // %1150 = mul(%2, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x000911fb, // %1151 = mul(%9, %1150): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x047d11fe, /* %1152 = sub(%1149, %1151):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00010007, // %1153 = mul(%1, %1): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x00031207, // %1154 = mul(%3, %1153): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002120a, // %1155 = sub(%2, %1154): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0477120f, /* %1156 = mul(%1143, %1155):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04840108, // %1157 = inv(%1156): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04801217, /* %1158 = mul(%1152, %1157):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x047a1219, /* %1159 = add(%1146, %1158):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x043e002a, // %1160 = sub(%1086, %10): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x000b000b, // %1161 = mul(%11, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04881226, /* %1162 = sub(%1160, %1161):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x000c11fb, // %1163 = mul(%12, %1150): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x048a122e, /* %1164 = sub(%1162, %1163):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x000211fb, // %1165 = mul(%2, %1150): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x000d1237, // %1166 = mul(%13, %1165): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x048c123a, /* %1167 = sub(%1164, %1166):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x047e11fb, /* %1168 = mul(%1150, %1150):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0) */
    0x000e1243, // %1169 = mul(%14, %1168): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x048f1246, /* %1170 = sub(%1167, %1169):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00021243, // %1171 = mul(%2, %1168): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x000f124f, // %1172 = mul(%15, %1171): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04921252, /* %1173 = sub(%1170, %1172):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00011207, // %1174 = mul(%1, %1153): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0003125b, // %1175 = mul(%3, %1174): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002125e, // %1176 = sub(%2, %1175): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04841263, /* %1177 = mul(%1156, %1176):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04811207, /* %1178 = mul(%1153, %1153):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x0003126b, // %1179 = mul(%3, %1178): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002126e, // %1180 = sub(%2, %1179): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04991273, /* %1181 = mul(%1177, %1180):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x049a126b, /* %1182 = mul(%1178, %1178):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x049e127b, /* %1183 = mul(%1182, %1182):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x0001127f, // %1184 = mul(%1, %1183): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04a01283, /* %1185 = mul(%1184, %1184):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x04a11287, /* %1186 = mul(%1185, %1185):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x0003128b, // %1187 = mul(%3, %1186): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x0002128e, // %1188 = sub(%2, %1187): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x049d1293, /* %1189 = mul(%1181, %1188):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04a50108, // %1190 = inv(%1189): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x0495129b, /* %1191 = mul(%1173, %1190):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x0487129d, /* %1192 = add(%1159, %1191):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x02330042, // %1193 = sub(%563, %16): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0011000b, // %1194 = mul(%17, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04a912aa, /* %1195 = sub(%1193, %1194):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x001211fb, // %1196 = mul(%18, %1150): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04ab12b2, /* %1197 = sub(%1195, %1196):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00131237, // %1198 = mul(%19, %1165): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04ad12ba, /* %1199 = sub(%1197, %1198):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00141243, // %1200 = mul(%20, %1168): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04af12c2, /* %1201 = sub(%1199, %1200):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0015124f, // %1202 = mul(%21, %1171): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04b112ca, /* %1203 = sub(%1201, %1202):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x0496125b, /* %1204 = mul(%1174, %1174):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x000112d3, // %1205 = mul(%1, %1204): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000312d7, // %1206 = mul(%3, %1205): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000212da, // %1207 = sub(%2, %1206): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x048412df, /* %1208 = mul(%1156, %1207):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04b512d7, /* %1209 = mul(%1205, %1205):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0) */
    0x000112e7, // %1210 = mul(%1, %1209): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000312eb, // %1211 = mul(%3, %1210): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000212ee, // %1212 = sub(%2, %1211): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04b812f3, /* %1213 = mul(%1208, %1212):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x0003127f, // %1214 = mul(%3, %1183): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x000212fa, // %1215 = sub(%2, %1214): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":175:0)
    0x04bd12ff, /* %1216 = mul(%1213, %1215):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04c00108, // %1217 = inv(%1216): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04b31307, /* %1218 = mul(%1203, %1217):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x04a81309, /* %1219 = add(%1192, %1218):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x02d8005a, // %1220 = sub(%728, %22): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0)
    0x0017000b, // %1221 = mul(%23, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04c41316, /* %1222 = sub(%1220, %1221):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x001811fb, // %1223 = mul(%24, %1150): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04c6131e, /* %1224 = sub(%1222, %1223):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x00191237, // %1225 = mul(%25, %1165): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04c81326, /* %1226 = sub(%1224, %1225):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x001a1243, // %1227 = mul(%26, %1168): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":165:0)
    0x04ca132e, /* %1228 = sub(%1226, %1227):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":163:0) */
    0x046f120f, /* %1229 = mul(%1135, %1155):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04cd12df, /* %1230 = mul(%1229, %1207):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04ce12f3, /* %1231 = mul(%1230, %1212):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04cf12ff, /* %1232 = mul(%1231, %1215):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":172:0) */
    0x04d00108, // %1233 = inv(%1232): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04cc1347, /* %1234 = mul(%1228, %1233):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x04c31349, /* %1235 = add(%1219, %1234):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x046d006e, // %1236 = sub(%1133, %27): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":181:0)
    0x0003000f, // %1237 = mul(%3, %3): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":182:0)
    0x04d51357, /* %1238 = mul(%1237, %1237):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":182:0) */
    0x0002135a, // %1239 = sub(%2, %1238): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":182:0)
    0x04d70108, // %1240 = inv(%1239): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":184:0)
    0x04d41363, /* %1241 = mul(%1236, %1240):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":184:0) */
    0x04d31365, /* %1242 = add(%1235, %1241):
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
    arg5: &[u32; 212 * EXT_ELEM_SIZE],
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
