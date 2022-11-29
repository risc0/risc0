// This code is automatically generated

#![cfg_attr(not(target_os = "zkvm"), allow(dead_code, unused_variables))]

const EXT_ELEM_SIZE: usize = 4;

// TODO: Don't extend these field elements; instead, ffpu should be
// aware of whether field elements are extension elements or not, but
// cirgen needs to be aware of it first.
const DATA: &[u32] = &[];

const CODE: &[u32] = &[
    0x00000100, // %0 = get($0x0000, 0x01): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":111:0)
    0x00010100, // %1 = get($0x0001, 0x01): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":111:0)
    0x00020100, // %2 = get($0x0002, 0x01): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":111:0)
    0x00030100, // %3 = get($0x0003, 0x01): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":111:0)
    0x00000200, // %4 = get($0x0000, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00010200, // %5 = get($0x0001, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00020200, // %6 = get($0x0002, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00030200, // %7 = get($0x0003, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00040200, // %8 = get($0x0004, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00050200, // %9 = get($0x0005, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00060200, // %10 = get($0x0006, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00070200, // %11 = get($0x0007, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00080200, // %12 = get($0x0008, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00090200, // %13 = get($0x0009, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x000a0200, // %14 = get($0x000a, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x000b0200, // %15 = get($0x000b, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x000c0200, // %16 = get($0x000c, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x000d0200, // %17 = get($0x000d, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x000e0200, // %18 = get($0x000e, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x000f0200, // %19 = get($0x000f, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00100200, // %20 = get($0x0010, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00110200, // %21 = get($0x0011, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00120200, // %22 = get($0x0012, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00130200, // %23 = get($0x0013, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00140200, // %24 = get($0x0014, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00150200, // %25 = get($0x0015, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00160200, // %26 = get($0x0016, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00170200, // %27 = get($0x0017, 0x02): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":119:0)
    0x00000300, // %28 = get($0x0000, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x00010300, // %29 = get($0x0001, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x00020300, // %30 = get($0x0002, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x00030300, // %31 = get($0x0003, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x00040300, // %32 = get($0x0004, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x00050300, // %33 = get($0x0005, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x00060300, // %34 = get($0x0006, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x00070300, // %35 = get($0x0007, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x00080300, // %36 = get($0x0008, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x00090300, // %37 = get($0x0009, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x000a0300, // %38 = get($0x000a, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x000b0300, // %39 = get($0x000b, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x000c0300, // %40 = get($0x000c, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x000d0300, // %41 = get($0x000d, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x000e0300, // %42 = get($0x000e, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x000f0300, // %43 = get($0x000f, 0x03): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":121:0)
    0x00000400, // %44 = get($0x0000, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00010400, // %45 = get($0x0001, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00020400, // %46 = get($0x0002, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00030400, // %47 = get($0x0003, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00040400, // %48 = get($0x0004, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00050400, // %49 = get($0x0005, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00060400, // %50 = get($0x0006, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00070400, // %51 = get($0x0007, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00080400, // %52 = get($0x0008, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00090400, // %53 = get($0x0009, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x000a0400, // %54 = get($0x000a, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x000b0400, // %55 = get($0x000b, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x000c0400, // %56 = get($0x000c, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x000d0400, // %57 = get($0x000d, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x000e0400, // %58 = get($0x000e, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x000f0400, // %59 = get($0x000f, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00100400, // %60 = get($0x0010, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00110400, // %61 = get($0x0011, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00120400, // %62 = get($0x0012, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00130400, // %63 = get($0x0013, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00140400, // %64 = get($0x0014, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00150400, // %65 = get($0x0015, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00160400, // %66 = get($0x0016, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00170400, // %67 = get($0x0017, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00180400, // %68 = get($0x0018, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00190400, // %69 = get($0x0019, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x001a0400, // %70 = get($0x001a, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x001b0400, // %71 = get($0x001b, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x001c0400, // %72 = get($0x001c, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x001d0400, // %73 = get($0x001d, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x001e0400, // %74 = get($0x001e, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x001f0400, // %75 = get($0x001f, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00200400, // %76 = get($0x0020, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00210400, // %77 = get($0x0021, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00220400, // %78 = get($0x0022, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00230400, // %79 = get($0x0023, 0x04): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":124:0)
    0x00000500, // %80 = get($0x0000, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00010500, // %81 = get($0x0001, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00020500, // %82 = get($0x0002, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00030500, // %83 = get($0x0003, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00040500, // %84 = get($0x0004, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00050500, // %85 = get($0x0005, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00060500, // %86 = get($0x0006, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00070500, // %87 = get($0x0007, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00080500, // %88 = get($0x0008, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00090500, // %89 = get($0x0009, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x000a0500, // %90 = get($0x000a, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x000b0500, // %91 = get($0x000b, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x000c0500, // %92 = get($0x000c, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x000d0500, // %93 = get($0x000d, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x000e0500, // %94 = get($0x000e, 0x05): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":125:0)
    0x00000600, // %95 = get($0x0000, 0x06): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0)
    0x00010600, // %96 = get($0x0001, 0x06): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0)
    0x00020600, // %97 = get($0x0002, 0x06): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0)
    0x00030600, // %98 = get($0x0003, 0x06): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0)
    0x00040600, // %99 = get($0x0004, 0x06): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0)
    0x00050600, /* %100 = get($0x0005, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00060600, /* %101 = get($0x0006, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00070600, /* %102 = get($0x0007, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00080600, /* %103 = get($0x0008, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00090600, /* %104 = get($0x0009, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x000a0600, /* %105 = get($0x000a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x000b0600, /* %106 = get($0x000b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x000c0600, /* %107 = get($0x000c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x000d0600, /* %108 = get($0x000d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x000e0600, /* %109 = get($0x000e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x000f0600, /* %110 = get($0x000f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00100600, /* %111 = get($0x0010, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00110600, /* %112 = get($0x0011, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00120600, /* %113 = get($0x0012, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00130600, /* %114 = get($0x0013, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00140600, /* %115 = get($0x0014, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00150600, /* %116 = get($0x0015, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00160600, /* %117 = get($0x0016, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00170600, /* %118 = get($0x0017, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00180600, /* %119 = get($0x0018, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00190600, /* %120 = get($0x0019, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x001a0600, /* %121 = get($0x001a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x001b0600, /* %122 = get($0x001b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x001c0600, /* %123 = get($0x001c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x001d0600, /* %124 = get($0x001d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x001e0600, /* %125 = get($0x001e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x001f0600, /* %126 = get($0x001f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00200600, /* %127 = get($0x0020, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00210600, /* %128 = get($0x0021, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00220600, /* %129 = get($0x0022, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00230600, /* %130 = get($0x0023, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00240600, /* %131 = get($0x0024, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00250600, /* %132 = get($0x0025, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00260600, /* %133 = get($0x0026, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00270600, /* %134 = get($0x0027, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00280600, /* %135 = get($0x0028, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00290600, /* %136 = get($0x0029, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x002a0600, /* %137 = get($0x002a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x002b0600, /* %138 = get($0x002b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x002c0600, /* %139 = get($0x002c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x002d0600, /* %140 = get($0x002d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x002e0600, /* %141 = get($0x002e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x002f0600, /* %142 = get($0x002f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00300600, /* %143 = get($0x0030, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00310600, /* %144 = get($0x0031, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00320600, /* %145 = get($0x0032, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00330600, /* %146 = get($0x0033, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00340600, /* %147 = get($0x0034, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00350600, /* %148 = get($0x0035, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00360600, /* %149 = get($0x0036, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00370600, /* %150 = get($0x0037, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00380600, /* %151 = get($0x0038, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00390600, /* %152 = get($0x0039, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x003a0600, /* %153 = get($0x003a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x003b0600, /* %154 = get($0x003b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x003c0600, /* %155 = get($0x003c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x003d0600, /* %156 = get($0x003d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x003e0600, /* %157 = get($0x003e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x003f0600, /* %158 = get($0x003f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00400600, /* %159 = get($0x0040, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00410600, /* %160 = get($0x0041, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00420600, /* %161 = get($0x0042, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00430600, /* %162 = get($0x0043, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00440600, /* %163 = get($0x0044, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00450600, /* %164 = get($0x0045, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00460600, /* %165 = get($0x0046, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00470600, /* %166 = get($0x0047, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00480600, /* %167 = get($0x0048, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00490600, /* %168 = get($0x0049, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x004a0600, /* %169 = get($0x004a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x004b0600, /* %170 = get($0x004b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x004c0600, /* %171 = get($0x004c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x004d0600, /* %172 = get($0x004d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x004e0600, /* %173 = get($0x004e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x004f0600, /* %174 = get($0x004f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00500600, /* %175 = get($0x0050, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00510600, /* %176 = get($0x0051, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00520600, /* %177 = get($0x0052, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00530600, /* %178 = get($0x0053, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00540600, /* %179 = get($0x0054, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00550600, /* %180 = get($0x0055, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00560600, /* %181 = get($0x0056, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00570600, /* %182 = get($0x0057, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00580600, /* %183 = get($0x0058, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00590600, /* %184 = get($0x0059, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x005a0600, /* %185 = get($0x005a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x005b0600, /* %186 = get($0x005b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x005c0600, /* %187 = get($0x005c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x005d0600, /* %188 = get($0x005d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x005e0600, /* %189 = get($0x005e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x005f0600, /* %190 = get($0x005f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00600600, /* %191 = get($0x0060, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00610600, /* %192 = get($0x0061, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00620600, /* %193 = get($0x0062, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00630600, /* %194 = get($0x0063, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00640600, /* %195 = get($0x0064, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00650600, /* %196 = get($0x0065, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00660600, /* %197 = get($0x0066, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00670600, /* %198 = get($0x0067, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00680600, /* %199 = get($0x0068, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00690600, /* %200 = get($0x0069, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x006a0600, /* %201 = get($0x006a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x006b0600, /* %202 = get($0x006b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x006c0600, /* %203 = get($0x006c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x006d0600, /* %204 = get($0x006d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x006e0600, /* %205 = get($0x006e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x006f0600, /* %206 = get($0x006f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00700600, /* %207 = get($0x0070, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00710600, /* %208 = get($0x0071, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00720600, /* %209 = get($0x0072, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00730600, /* %210 = get($0x0073, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00740600, /* %211 = get($0x0074, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00750600, /* %212 = get($0x0075, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00760600, /* %213 = get($0x0076, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00770600, /* %214 = get($0x0077, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00780600, /* %215 = get($0x0078, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00790600, /* %216 = get($0x0079, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x007a0600, /* %217 = get($0x007a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x007b0600, /* %218 = get($0x007b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x007c0600, /* %219 = get($0x007c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x007d0600, /* %220 = get($0x007d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x007e0600, /* %221 = get($0x007e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x007f0600, /* %222 = get($0x007f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00800600, /* %223 = get($0x0080, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00810600, /* %224 = get($0x0081, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00820600, /* %225 = get($0x0082, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00830600, /* %226 = get($0x0083, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00840600, /* %227 = get($0x0084, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00850600, /* %228 = get($0x0085, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00860600, /* %229 = get($0x0086, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00870600, /* %230 = get($0x0087, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00880600, /* %231 = get($0x0088, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00890600, /* %232 = get($0x0089, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x008a0600, /* %233 = get($0x008a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x008b0600, /* %234 = get($0x008b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x008c0600, /* %235 = get($0x008c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x008d0600, /* %236 = get($0x008d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x008e0600, /* %237 = get($0x008e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x008f0600, /* %238 = get($0x008f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00900600, /* %239 = get($0x0090, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00910600, /* %240 = get($0x0091, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00920600, /* %241 = get($0x0092, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00930600, /* %242 = get($0x0093, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00940600, /* %243 = get($0x0094, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00950600, /* %244 = get($0x0095, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00960600, /* %245 = get($0x0096, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00970600, /* %246 = get($0x0097, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00980600, /* %247 = get($0x0098, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00990600, /* %248 = get($0x0099, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x009a0600, /* %249 = get($0x009a, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x009b0600, /* %250 = get($0x009b, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x009c0600, /* %251 = get($0x009c, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x009d0600, /* %252 = get($0x009d, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x009e0600, /* %253 = get($0x009e, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x009f0600, /* %254 = get($0x009f, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00a00600, /* %255 = get($0x00a0, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00a10600, /* %256 = get($0x00a1, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00a20600, /* %257 = get($0x00a2, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00a30600, /* %258 = get($0x00a3, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00a40600, /* %259 = get($0x00a4, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00a50600, /* %260 = get($0x00a5, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00a60600, /* %261 = get($0x00a6, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00a70600, /* %262 = get($0x00a7, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00a80600, /* %263 = get($0x00a8, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00a90600, /* %264 = get($0x00a9, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00aa0600, /* %265 = get($0x00aa, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00ab0600, /* %266 = get($0x00ab, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00ac0600, /* %267 = get($0x00ac, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00ad0600, /* %268 = get($0x00ad, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00ae0600, /* %269 = get($0x00ae, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00af0600, /* %270 = get($0x00af, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00b00600, /* %271 = get($0x00b0, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00b10600, /* %272 = get($0x00b1, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00b20600, /* %273 = get($0x00b2, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00b30600, /* %274 = get($0x00b3, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00b40600, /* %275 = get($0x00b4, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00b50600, /* %276 = get($0x00b5, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00b60600, /* %277 = get($0x00b6, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00b70600, /* %278 = get($0x00b7, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00b80600, /* %279 = get($0x00b8, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00b90600, /* %280 = get($0x00b9, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00ba0600, /* %281 = get($0x00ba, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00bb0600, /* %282 = get($0x00bb, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00bc0600, /* %283 = get($0x00bc, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00bd0600, /* %284 = get($0x00bd, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00be0600, /* %285 = get($0x00be, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00bf0600, /* %286 = get($0x00bf, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00c00600, /* %287 = get($0x00c0, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00c10600, /* %288 = get($0x00c1, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00c20600, /* %289 = get($0x00c2, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00c30600, /* %290 = get($0x00c3, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00c40600, /* %291 = get($0x00c4, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00c50600, /* %292 = get($0x00c5, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00c60600, /* %293 = get($0x00c6, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00c70600, /* %294 = get($0x00c7, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00c80600, /* %295 = get($0x00c8, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00c90600, /* %296 = get($0x00c9, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00ca0600, /* %297 = get($0x00ca, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00cb0600, /* %298 = get($0x00cb, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00cc0600, /* %299 = get($0x00cc, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00cd0600, /* %300 = get($0x00cd, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00ce0600, /* %301 = get($0x00ce, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x00cf0600, /* %302 = get($0x00cf, 0x06):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":126:0) */
    0x000000b7, // %303 = mul(%0, %45): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x002c04bd, // %304 = add(%44, %303): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x00000003, // %305 = mul(%0, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x013100bb, // %306 = mul(%305, %46): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x013004c9, // %307 = add(%304, %306): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01310003, // %308 = mul(%305, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x013400bf, // %309 = mul(%308, %47): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x013304d5, // %310 = add(%307, %309): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01340003, // %311 = mul(%308, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x013700c3, // %312 = mul(%311, %48): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x013604e1, // %313 = add(%310, %312): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01370003, // %314 = mul(%311, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x013a00c7, // %315 = mul(%314, %49): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x013904ed, // %316 = add(%313, %315): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x013a0003, // %317 = mul(%314, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x013d00cb, // %318 = mul(%317, %50): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x013c04f9, // %319 = add(%316, %318): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x013d0003, // %320 = mul(%317, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x014000cf, // %321 = mul(%320, %51): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x013f0505, // %322 = add(%319, %321): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01400003, // %323 = mul(%320, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x014300d3, // %324 = mul(%323, %52): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01430003, // %325 = mul(%323, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x014500d7, // %326 = mul(%325, %53): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01440519, // %327 = add(%324, %326): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01450003, // %328 = mul(%325, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x014800db, // %329 = mul(%328, %54): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01470525, // %330 = add(%327, %329): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01480003, // %331 = mul(%328, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x014b00df, // %332 = mul(%331, %55): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x014a0531, // %333 = add(%330, %332): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x014b0003, // %334 = mul(%331, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x014e00e3, // %335 = mul(%334, %56): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x014d053d, // %336 = add(%333, %335): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x014e0003, // %337 = mul(%334, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x015100e7, // %338 = mul(%337, %57): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01500549, // %339 = add(%336, %338): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01510003, // %340 = mul(%337, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x015400eb, // %341 = mul(%340, %58): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01530555, // %342 = add(%339, %341): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01540003, // %343 = mul(%340, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x015700ef, // %344 = mul(%343, %59): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01560561, // %345 = add(%342, %344): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01570003, // %346 = mul(%343, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x015a00f3, // %347 = mul(%346, %60): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0159056d, // %348 = add(%345, %347): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x015a0003, // %349 = mul(%346, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x015d00f7, // %350 = mul(%349, %61): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x015c0579, // %351 = add(%348, %350): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x015d0003, // %352 = mul(%349, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x016000fb, // %353 = mul(%352, %62): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x015f0585, // %354 = add(%351, %353): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01600003, // %355 = mul(%352, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x016300ff, // %356 = mul(%355, %63): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01620591, // %357 = add(%354, %356): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01630003, // %358 = mul(%355, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01660103, // %359 = mul(%358, %64): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0165059d, // %360 = add(%357, %359): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01660003, // %361 = mul(%358, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01690107, // %362 = mul(%361, %65): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x016805a9, // %363 = add(%360, %362): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01690003, // %364 = mul(%361, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x016c010b, // %365 = mul(%364, %66): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x016b05b5, // %366 = add(%363, %365): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x016c0003, // %367 = mul(%364, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x016f010f, // %368 = mul(%367, %67): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x016e05c1, // %369 = add(%366, %368): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x016f0003, // %370 = mul(%367, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01720113, // %371 = mul(%370, %68): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x017105cd, // %372 = add(%369, %371): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01720003, // %373 = mul(%370, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01750117, // %374 = mul(%373, %69): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x017405d9, // %375 = add(%372, %374): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01750003, // %376 = mul(%373, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0178011b, // %377 = mul(%376, %70): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x017705e5, // %378 = add(%375, %377): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01780003, // %379 = mul(%376, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x017b011f, // %380 = mul(%379, %71): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x017a05f1, // %381 = add(%378, %380): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x017b0003, // %382 = mul(%379, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x017e0123, // %383 = mul(%382, %72): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x017d05fd, // %384 = add(%381, %383): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x017e0003, // %385 = mul(%382, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01810127, // %386 = mul(%385, %73): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01800609, // %387 = add(%384, %386): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01810003, // %388 = mul(%385, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0184012b, // %389 = mul(%388, %74): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01830615, // %390 = add(%387, %389): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01840003, // %391 = mul(%388, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0187012f, // %392 = mul(%391, %75): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01860621, // %393 = add(%390, %392): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01870003, // %394 = mul(%391, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x018a0133, // %395 = mul(%394, %76): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0189062d, // %396 = add(%393, %395): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x018a0003, // %397 = mul(%394, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x018d0137, // %398 = mul(%397, %77): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x018c0639, // %399 = add(%396, %398): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x018d0003, // %400 = mul(%397, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0190013b, // %401 = mul(%400, %78): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x018f0645, // %402 = add(%399, %401): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01900003, // %403 = mul(%400, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0193013f, // %404 = mul(%403, %79): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01920651, // %405 = add(%402, %404): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01930003, // %406 = mul(%403, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01960143, // %407 = mul(%406, %80): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0195065d, // %408 = add(%405, %407): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01960003, // %409 = mul(%406, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01990147, // %410 = mul(%409, %81): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01980669, // %411 = add(%408, %410): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01990003, // %412 = mul(%409, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x019c014b, // %413 = mul(%412, %82): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01420675, // %414 = add(%322, %413): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x019c0003, // %415 = mul(%412, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x019f014f, // %416 = mul(%415, %83): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x019b0681, // %417 = add(%411, %416): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x019f0003, // %418 = mul(%415, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01a20153, // %419 = mul(%418, %84): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01a1068d, // %420 = add(%417, %419): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01a20003, // %421 = mul(%418, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01a50157, // %422 = mul(%421, %85): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01a40699, // %423 = add(%420, %422): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01a50003, // %424 = mul(%421, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01a8015b, // %425 = mul(%424, %86): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01a706a5, // %426 = add(%423, %425): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01a80003, // %427 = mul(%424, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01ab015f, // %428 = mul(%427, %87): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01aa06b1, // %429 = add(%426, %428): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01ab0003, // %430 = mul(%427, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01ae0163, // %431 = mul(%430, %88): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01ad06bd, // %432 = add(%429, %431): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01ae0003, // %433 = mul(%430, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01b10167, // %434 = mul(%433, %89): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01b006c9, // %435 = add(%432, %434): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01b10003, // %436 = mul(%433, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01b4016b, // %437 = mul(%436, %90): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01b306d5, // %438 = add(%435, %437): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01b40003, // %439 = mul(%436, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01b7016f, // %440 = mul(%439, %91): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01b606e1, // %441 = add(%438, %440): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01b70003, // %442 = mul(%439, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01ba0173, // %443 = mul(%442, %92): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01b906ed, // %444 = add(%441, %443): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01ba0003, // %445 = mul(%442, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01bd0177, // %446 = mul(%445, %93): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01bc06f9, // %447 = add(%444, %446): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01bd0003, // %448 = mul(%445, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01c0017b, // %449 = mul(%448, %94): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01bf0705, // %450 = add(%447, %449): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01c00003, // %451 = mul(%448, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01c3017f, // %452 = mul(%451, %95): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x019e0711, // %453 = add(%414, %452): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01c30003, // %454 = mul(%451, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01c60183, // %455 = mul(%454, %96): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01c5071d, // %456 = add(%453, %455): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01c60003, // %457 = mul(%454, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01c90187, // %458 = mul(%457, %97): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01c80729, // %459 = add(%456, %458): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01c90003, // %460 = mul(%457, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01cc018b, // %461 = mul(%460, %98): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01cb0735, // %462 = add(%459, %461): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01cc0003, // %463 = mul(%460, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01cf018f, // %464 = mul(%463, %99): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01ce0741, // %465 = add(%462, %464): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01cf0003, // %466 = mul(%463, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01d20193, // %467 = mul(%466, %100): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01d1074d, // %468 = add(%465, %467): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01d20003, // %469 = mul(%466, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01d50197, // %470 = mul(%469, %101): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01d40759, // %471 = add(%468, %470): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01d50003, // %472 = mul(%469, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01d8019b, // %473 = mul(%472, %102): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01d70765, // %474 = add(%471, %473): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01d80003, // %475 = mul(%472, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01db019f, // %476 = mul(%475, %103): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01da0771, // %477 = add(%474, %476): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01db0003, // %478 = mul(%475, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01de01a3, // %479 = mul(%478, %104): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01c2077d, // %480 = add(%450, %479): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01de0003, // %481 = mul(%478, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01e101a7, // %482 = mul(%481, %105): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01dd0789, // %483 = add(%477, %482): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01e10003, // %484 = mul(%481, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01e401ab, // %485 = mul(%484, %106): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01e30795, // %486 = add(%483, %485): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01e40003, // %487 = mul(%484, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01e701af, // %488 = mul(%487, %107): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01e607a1, // %489 = add(%486, %488): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01e70003, // %490 = mul(%487, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01ea01b3, // %491 = mul(%490, %108): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01e007ad, // %492 = add(%480, %491): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01ea0003, // %493 = mul(%490, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01ed01b7, // %494 = mul(%493, %109): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01ec07b9, // %495 = add(%492, %494): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01ed0003, // %496 = mul(%493, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01f001bb, // %497 = mul(%496, %110): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01ef07c5, // %498 = add(%495, %497): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01f00003, // %499 = mul(%496, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01f301bf, // %500 = mul(%499, %111): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01f207d1, // %501 = add(%498, %500): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01f30003, // %502 = mul(%499, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01f601c3, // %503 = mul(%502, %112): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01f507dd, // %504 = add(%501, %503): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01f60003, // %505 = mul(%502, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01f901c7, // %506 = mul(%505, %113): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01f807e9, // %507 = add(%504, %506): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01f90003, // %508 = mul(%505, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01fc01cb, // %509 = mul(%508, %114): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01fb07f5, // %510 = add(%507, %509): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x01fc0003, // %511 = mul(%508, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x01ff01cf, // %512 = mul(%511, %115): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01ff0003, // %513 = mul(%511, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x020101d3, // %514 = mul(%513, %116): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02000809, // %515 = add(%512, %514): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02010003, // %516 = mul(%513, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x020401d7, // %517 = mul(%516, %117): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02030815, // %518 = add(%515, %517): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02040003, // %519 = mul(%516, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x020701db, // %520 = mul(%519, %118): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02060821, // %521 = add(%518, %520): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02070003, // %522 = mul(%519, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x020a01df, // %523 = mul(%522, %119): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0209082d, // %524 = add(%521, %523): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x020a0003, // %525 = mul(%522, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x020d01e3, // %526 = mul(%525, %120): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x020d0003, // %527 = mul(%525, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x020f01e7, // %528 = mul(%527, %121): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x020e0841, // %529 = add(%526, %528): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x020f0003, // %530 = mul(%527, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x021201eb, // %531 = mul(%530, %122): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0211084d, // %532 = add(%529, %531): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02120003, // %533 = mul(%530, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x021501ef, // %534 = mul(%533, %123): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02140859, // %535 = add(%532, %534): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02150003, // %536 = mul(%533, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x021801f3, // %537 = mul(%536, %124): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02170865, // %538 = add(%535, %537): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02180003, // %539 = mul(%536, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x021b01f7, // %540 = mul(%539, %125): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x021a0871, // %541 = add(%538, %540): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x021b0003, // %542 = mul(%539, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x021e01fb, // %543 = mul(%542, %126): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x021d087d, // %544 = add(%541, %543): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x021e0003, // %545 = mul(%542, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x022101ff, // %546 = mul(%545, %127): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02200889, // %547 = add(%544, %546): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02210003, // %548 = mul(%545, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02240203, // %549 = mul(%548, %128): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02230895, // %550 = add(%547, %549): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02240003, // %551 = mul(%548, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02270207, // %552 = mul(%551, %129): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x022608a1, // %553 = add(%550, %552): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02270003, // %554 = mul(%551, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x022a020b, // %555 = mul(%554, %130): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x022908ad, // %556 = add(%553, %555): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x022a0003, // %557 = mul(%554, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x022d020f, // %558 = mul(%557, %131): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x022c08b9, // %559 = add(%556, %558): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x022d0003, // %560 = mul(%557, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02300213, // %561 = mul(%560, %132): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x020c08c5, // %562 = add(%524, %561): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02300003, // %563 = mul(%560, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02330217, // %564 = mul(%563, %133): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x023208d1, // %565 = add(%562, %564): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02330003, // %566 = mul(%563, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0236021b, // %567 = mul(%566, %134): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x023508dd, // %568 = add(%565, %567): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02360003, // %569 = mul(%566, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0239021f, // %570 = mul(%569, %135): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x023808e9, // %571 = add(%568, %570): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02390003, // %572 = mul(%569, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x023c0223, // %573 = mul(%572, %136): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x023b08f5, // %574 = add(%571, %573): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x023c0003, // %575 = mul(%572, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x023f0227, // %576 = mul(%575, %137): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01fe0901, // %577 = add(%510, %576): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x023f0003, // %578 = mul(%575, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0242022b, // %579 = mul(%578, %138): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0241090d, // %580 = add(%577, %579): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02420003, // %581 = mul(%578, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0245022f, // %582 = mul(%581, %139): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02440919, // %583 = add(%580, %582): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02450003, // %584 = mul(%581, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02480233, // %585 = mul(%584, %140): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02470925, // %586 = add(%583, %585): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02480003, // %587 = mul(%584, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x024b0237, // %588 = mul(%587, %141): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x024a0931, // %589 = add(%586, %588): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x024b0003, // %590 = mul(%587, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x024e023b, // %591 = mul(%590, %142): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x024d093d, // %592 = add(%589, %591): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x024e0003, // %593 = mul(%590, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0251023f, // %594 = mul(%593, %143): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02500949, // %595 = add(%592, %594): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02510003, // %596 = mul(%593, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02540243, // %597 = mul(%596, %144): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02530955, // %598 = add(%595, %597): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02540003, // %599 = mul(%596, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02570247, // %600 = mul(%599, %145): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x01e90961, // %601 = add(%489, %600): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02570003, // %602 = mul(%599, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x025a024b, // %603 = mul(%602, %146): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0259096d, // %604 = add(%601, %603): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x025a0003, // %605 = mul(%602, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x025d024f, // %606 = mul(%605, %147): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02560979, // %607 = add(%598, %606): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x025d0003, // %608 = mul(%605, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02600253, // %609 = mul(%608, %148): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x025f0985, // %610 = add(%607, %609): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02600003, // %611 = mul(%608, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02630257, // %612 = mul(%611, %149): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02620991, // %613 = add(%610, %612): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02630003, // %614 = mul(%611, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0266025b, // %615 = mul(%614, %150): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0265099d, // %616 = add(%613, %615): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02660003, // %617 = mul(%614, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0269025f, // %618 = mul(%617, %151): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x026809a9, // %619 = add(%616, %618): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02690003, // %620 = mul(%617, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x026c0263, // %621 = mul(%620, %152): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x026b09b5, // %622 = add(%619, %621): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x026c0003, // %623 = mul(%620, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x026f0267, // %624 = mul(%623, %153): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x026e09c1, // %625 = add(%622, %624): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x026f0003, // %626 = mul(%623, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0272026b, // %627 = mul(%626, %154): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x027109cd, // %628 = add(%625, %627): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02720003, // %629 = mul(%626, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0275026f, // %630 = mul(%629, %155): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x027409d9, // %631 = add(%628, %630): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02750003, // %632 = mul(%629, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02780273, // %633 = mul(%632, %156): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x027709e5, // %634 = add(%631, %633): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02780003, // %635 = mul(%632, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x027b0277, // %636 = mul(%635, %157): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x027a09f1, // %637 = add(%634, %636): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x027b0003, // %638 = mul(%635, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x027e027b, // %639 = mul(%638, %158): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x027d09fd, // %640 = add(%637, %639): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x027e0003, // %641 = mul(%638, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0281027f, // %642 = mul(%641, %159): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02800a09, // %643 = add(%640, %642): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02810003, // %644 = mul(%641, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02840283, // %645 = mul(%644, %160): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02830a15, // %646 = add(%643, %645): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02840003, // %647 = mul(%644, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02870287, // %648 = mul(%647, %161): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02860a21, // %649 = add(%646, %648): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02870003, // %650 = mul(%647, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x028a028b, // %651 = mul(%650, %162): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02890a2d, // %652 = add(%649, %651): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x028a0003, // %653 = mul(%650, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x028d028f, // %654 = mul(%653, %163): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x028c0a39, // %655 = add(%652, %654): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x028d0003, // %656 = mul(%653, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02900293, // %657 = mul(%656, %164): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x028f0a45, // %658 = add(%655, %657): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02900003, // %659 = mul(%656, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02930297, // %660 = mul(%659, %165): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02920a51, // %661 = add(%658, %660): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02930003, // %662 = mul(%659, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0296029b, // %663 = mul(%662, %166): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02950a5d, // %664 = add(%661, %663): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02960003, // %665 = mul(%662, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0299029f, // %666 = mul(%665, %167): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x025c0a69, // %667 = add(%604, %666): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02990003, // %668 = mul(%665, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x029c02a3, // %669 = mul(%668, %168): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x029b0a75, // %670 = add(%667, %669): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x029c0003, // %671 = mul(%668, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x029f02a7, // %672 = mul(%671, %169): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02980a81, // %673 = add(%664, %672): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x029f0003, // %674 = mul(%671, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02a202ab, // %675 = mul(%674, %170): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02a10a8d, // %676 = add(%673, %675): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02a20003, // %677 = mul(%674, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02a502af, // %678 = mul(%677, %171): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02a40a99, // %679 = add(%676, %678): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02a50003, // %680 = mul(%677, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02a802b3, // %681 = mul(%680, %172): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02a70aa5, // %682 = add(%679, %681): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02a80003, // %683 = mul(%680, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02ab02b7, // %684 = mul(%683, %173): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02aa0ab1, // %685 = add(%682, %684): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02ab0003, // %686 = mul(%683, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02ae02bb, // %687 = mul(%686, %174): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02ad0abd, // %688 = add(%685, %687): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02ae0003, // %689 = mul(%686, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02b102bf, // %690 = mul(%689, %175): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02b00ac9, // %691 = add(%688, %690): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02b10003, // %692 = mul(%689, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02b402c3, // %693 = mul(%692, %176): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02b30ad5, // %694 = add(%691, %693): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02b40003, // %695 = mul(%692, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02b702c7, // %696 = mul(%695, %177): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x023e0ae1, // %697 = add(%574, %696): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02b70003, // %698 = mul(%695, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02ba02cb, // %699 = mul(%698, %178): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02b90aed, // %700 = add(%697, %699): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02ba0003, // %701 = mul(%698, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02bd02cf, // %702 = mul(%701, %179): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02bc0af9, // %703 = add(%700, %702): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02bd0003, // %704 = mul(%701, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02c002d3, // %705 = mul(%704, %180): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02bf0b05, // %706 = add(%703, %705): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02c00003, // %707 = mul(%704, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02c302d7, // %708 = mul(%707, %181): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02c20b11, // %709 = add(%706, %708): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02c30003, // %710 = mul(%707, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02c602db, // %711 = mul(%710, %182): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02c50b1d, // %712 = add(%709, %711): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02c60003, // %713 = mul(%710, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02c902df, // %714 = mul(%713, %183): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02c80b29, // %715 = add(%712, %714): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02c90003, // %716 = mul(%713, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02cc02e3, // %717 = mul(%716, %184): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02cb0b35, // %718 = add(%715, %717): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02cc0003, // %719 = mul(%716, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02cf02e7, // %720 = mul(%719, %185): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02ce0b41, // %721 = add(%718, %720): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02cf0003, // %722 = mul(%719, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02d202eb, // %723 = mul(%722, %186): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02d10b4d, // %724 = add(%721, %723): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02d20003, // %725 = mul(%722, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02d502ef, // %726 = mul(%725, %187): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02b60b59, // %727 = add(%694, %726): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02d50003, // %728 = mul(%725, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02d802f3, // %729 = mul(%728, %188): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02d70b65, // %730 = add(%727, %729): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02d80003, // %731 = mul(%728, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02db02f7, // %732 = mul(%731, %189): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02da0b71, // %733 = add(%730, %732): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02db0003, // %734 = mul(%731, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02de02fb, // %735 = mul(%734, %190): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x029e0b7d, // %736 = add(%670, %735): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02de0003, // %737 = mul(%734, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02e102ff, // %738 = mul(%737, %191): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02e00b89, // %739 = add(%736, %738): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02e10003, // %740 = mul(%737, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02e40303, // %741 = mul(%740, %192): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02e30b95, // %742 = add(%739, %741): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02e40003, // %743 = mul(%740, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02e70307, // %744 = mul(%743, %193): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02e60ba1, // %745 = add(%742, %744): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02e70003, // %746 = mul(%743, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02ea030b, // %747 = mul(%746, %194): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02e90bad, // %748 = add(%745, %747): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02ea0003, // %749 = mul(%746, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02ed030f, // %750 = mul(%749, %195): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02ec0bb9, // %751 = add(%748, %750): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02ed0003, // %752 = mul(%749, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02f00313, // %753 = mul(%752, %196): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02ef0bc5, // %754 = add(%751, %753): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02f00003, // %755 = mul(%752, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02f30317, // %756 = mul(%755, %197): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02f20bd1, // %757 = add(%754, %756): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02f30003, // %758 = mul(%755, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02f6031b, // %759 = mul(%758, %198): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02f50bdd, // %760 = add(%757, %759): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02f60003, // %761 = mul(%758, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02f9031f, // %762 = mul(%761, %199): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02f80be9, // %763 = add(%760, %762): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02f90003, // %764 = mul(%761, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02fc0323, // %765 = mul(%764, %200): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02fb0bf5, // %766 = add(%763, %765): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02fc0003, // %767 = mul(%764, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x02ff0327, // %768 = mul(%767, %201): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02fe0c01, // %769 = add(%766, %768): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x02ff0003, // %770 = mul(%767, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0302032b, // %771 = mul(%770, %202): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x02dd0c0d, // %772 = add(%733, %771): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03020003, // %773 = mul(%770, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0305032f, // %774 = mul(%773, %203): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03040c19, // %775 = add(%772, %774): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03050003, // %776 = mul(%773, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03080333, // %777 = mul(%776, %204): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03070c25, // %778 = add(%775, %777): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03080003, // %779 = mul(%776, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x030b0337, // %780 = mul(%779, %205): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x030a0c31, // %781 = add(%778, %780): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x030b0003, // %782 = mul(%779, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x030e033b, // %783 = mul(%782, %206): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x030d0c3d, // %784 = add(%781, %783): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x030e0003, // %785 = mul(%782, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0311033f, // %786 = mul(%785, %207): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03100c49, // %787 = add(%784, %786): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03110003, // %788 = mul(%785, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03140343, // %789 = mul(%788, %208): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03130c55, // %790 = add(%787, %789): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03140003, // %791 = mul(%788, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03170347, // %792 = mul(%791, %209): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03160c61, // %793 = add(%790, %792): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03170003, // %794 = mul(%791, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x031a034b, // %795 = mul(%794, %210): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03190c6d, // %796 = add(%793, %795): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x031a0003, // %797 = mul(%794, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x031d034f, // %798 = mul(%797, %211): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x031c0c79, // %799 = add(%796, %798): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x031d0003, // %800 = mul(%797, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03200353, // %801 = mul(%800, %212): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03010c85, // %802 = add(%769, %801): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03200003, // %803 = mul(%800, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03230357, // %804 = mul(%803, %213): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03220c91, // %805 = add(%802, %804): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03230003, // %806 = mul(%803, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0326035b, // %807 = mul(%806, %214): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03250c9d, // %808 = add(%805, %807): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03260003, // %809 = mul(%806, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0329035f, // %810 = mul(%809, %215): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03280ca9, // %811 = add(%808, %810): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03290003, // %812 = mul(%809, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x032c0363, // %813 = mul(%812, %216): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x031f0cb5, // %814 = add(%799, %813): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x032c0003, // %815 = mul(%812, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x032f0367, // %816 = mul(%815, %217): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x032e0cc1, // %817 = add(%814, %816): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x032f0003, // %818 = mul(%815, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0332036b, // %819 = mul(%818, %218): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03310ccd, // %820 = add(%817, %819): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03320003, // %821 = mul(%818, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0335036f, // %822 = mul(%821, %219): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x032b0cd9, // %823 = add(%811, %822): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03350003, // %824 = mul(%821, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03380373, // %825 = mul(%824, %220): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03370ce5, // %826 = add(%823, %825): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03380003, // %827 = mul(%824, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x033b0377, // %828 = mul(%827, %221): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x033a0cf1, // %829 = add(%826, %828): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x033b0003, // %830 = mul(%827, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x033e037b, // %831 = mul(%830, %222): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x033d0cfd, // %832 = add(%829, %831): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x033e0003, // %833 = mul(%830, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0341037f, // %834 = mul(%833, %223): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03340d09, // %835 = add(%820, %834): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03410003, // %836 = mul(%833, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03440383, // %837 = mul(%836, %224): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03430d15, // %838 = add(%835, %837): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03440003, // %839 = mul(%836, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03470387, // %840 = mul(%839, %225): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03400d21, // %841 = add(%832, %840): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03470003, // %842 = mul(%839, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x034a038b, // %843 = mul(%842, %226): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03490d2d, // %844 = add(%841, %843): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x034a0003, // %845 = mul(%842, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x034d038f, // %846 = mul(%845, %227): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x034c0d39, // %847 = add(%844, %846): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x034d0003, // %848 = mul(%845, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03500393, // %849 = mul(%848, %228): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03500003, // %850 = mul(%848, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03520397, // %851 = mul(%850, %229): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03510d4d, // %852 = add(%849, %851): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03520003, // %853 = mul(%850, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0355039b, // %854 = mul(%853, %230): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03460d59, // %855 = add(%838, %854): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03550003, // %856 = mul(%853, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0358039f, // %857 = mul(%856, %231): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03570d65, // %858 = add(%855, %857): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03580003, // %859 = mul(%856, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x035b03a3, // %860 = mul(%859, %232): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x034f0d71, // %861 = add(%847, %860): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x035b0003, // %862 = mul(%859, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x035e03a7, // %863 = mul(%862, %233): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x035a0d7d, // %864 = add(%858, %863): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x035e0003, // %865 = mul(%862, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x036103ab, // %866 = mul(%865, %234): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03600d89, // %867 = add(%864, %866): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03610003, // %868 = mul(%865, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x036403af, // %869 = mul(%868, %235): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03630d95, // %870 = add(%867, %869): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03640003, // %871 = mul(%868, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x036703b3, // %872 = mul(%871, %236): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03660da1, // %873 = add(%870, %872): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03670003, // %874 = mul(%871, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x036a03b7, // %875 = mul(%874, %237): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03690dad, // %876 = add(%873, %875): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x036a0003, // %877 = mul(%874, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x036d03bb, // %878 = mul(%877, %238): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x036c0db9, // %879 = add(%876, %878): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x036d0003, // %880 = mul(%877, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x037003bf, // %881 = mul(%880, %239): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03700003, // %882 = mul(%880, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x037203c3, // %883 = mul(%882, %240): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03710dcd, // %884 = add(%881, %883): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03720003, // %885 = mul(%882, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x037503c7, // %886 = mul(%885, %241): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03740dd9, // %887 = add(%884, %886): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03750003, // %888 = mul(%885, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x037803cb, // %889 = mul(%888, %242): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03770de5, // %890 = add(%887, %889): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03780003, // %891 = mul(%888, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x037b03cf, // %892 = mul(%891, %243): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x037a0df1, // %893 = add(%890, %892): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x037b0003, // %894 = mul(%891, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x037e03d3, // %895 = mul(%894, %244): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x037d0dfd, // %896 = add(%893, %895): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x037e0003, // %897 = mul(%894, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x038103d7, // %898 = mul(%897, %245): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03800e09, // %899 = add(%896, %898): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03810003, // %900 = mul(%897, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x038403db, // %901 = mul(%900, %246): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03830e15, // %902 = add(%899, %901): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03840003, // %903 = mul(%900, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x038703df, // %904 = mul(%903, %247): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03860e21, // %905 = add(%902, %904): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03870003, // %906 = mul(%903, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x038a03e3, // %907 = mul(%906, %248): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03890e2d, // %908 = add(%905, %907): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x038a0003, // %909 = mul(%906, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x038d03e7, // %910 = mul(%909, %249): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x038c0e39, // %911 = add(%908, %910): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x038d0003, // %912 = mul(%909, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x039003eb, // %913 = mul(%912, %250): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x038f0e45, // %914 = add(%911, %913): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03900003, // %915 = mul(%912, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x039303ef, // %916 = mul(%915, %251): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03920e51, // %917 = add(%914, %916): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03930003, // %918 = mul(%915, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x039603f3, // %919 = mul(%918, %252): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03950e5d, // %920 = add(%917, %919): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03960003, // %921 = mul(%918, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x039903f7, // %922 = mul(%921, %253): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03980e69, // %923 = add(%920, %922): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03990003, // %924 = mul(%921, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x039c03fb, // %925 = mul(%924, %254): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x039b0e75, // %926 = add(%923, %925): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x039c0003, // %927 = mul(%924, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x039f03ff, // %928 = mul(%927, %255): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x039e0e81, // %929 = add(%926, %928): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x039f0003, // %930 = mul(%927, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03a20403, // %931 = mul(%930, %256): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03a10e8d, // %932 = add(%929, %931): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03a20003, // %933 = mul(%930, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03a50407, // %934 = mul(%933, %257): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03a40e99, // %935 = add(%932, %934): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03a50003, // %936 = mul(%933, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03a8040b, // %937 = mul(%936, %258): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03a70ea5, // %938 = add(%935, %937): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03a80003, // %939 = mul(%936, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03ab040f, // %940 = mul(%939, %259): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03aa0eb1, // %941 = add(%938, %940): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03ab0003, // %942 = mul(%939, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03ae0413, // %943 = mul(%942, %260): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03ad0ebd, // %944 = add(%941, %943): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03ae0003, // %945 = mul(%942, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03b10417, // %946 = mul(%945, %261): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03b00ec9, // %947 = add(%944, %946): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03b10003, // %948 = mul(%945, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03b4041b, // %949 = mul(%948, %262): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03b30ed5, // %950 = add(%947, %949): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03b40003, // %951 = mul(%948, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03b7041f, // %952 = mul(%951, %263): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03b60ee1, // %953 = add(%950, %952): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03b70003, // %954 = mul(%951, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03ba0423, // %955 = mul(%954, %264): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03b90eed, // %956 = add(%953, %955): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03ba0003, // %957 = mul(%954, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03bd0427, // %958 = mul(%957, %265): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03bc0ef9, // %959 = add(%956, %958): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03bd0003, // %960 = mul(%957, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03c0042b, // %961 = mul(%960, %266): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03bf0f05, // %962 = add(%959, %961): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03c00003, // %963 = mul(%960, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03c3042f, // %964 = mul(%963, %267): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03c20f11, // %965 = add(%962, %964): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03c30003, // %966 = mul(%963, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03c60433, // %967 = mul(%966, %268): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03c50f1d, // %968 = add(%965, %967): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03c60003, // %969 = mul(%966, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03c90437, // %970 = mul(%969, %269): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03c80f29, // %971 = add(%968, %970): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03c90003, // %972 = mul(%969, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03cc043b, // %973 = mul(%972, %270): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03cb0f35, // %974 = add(%971, %973): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03cc0003, // %975 = mul(%972, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03cf043f, // %976 = mul(%975, %271): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03ce0f41, // %977 = add(%974, %976): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03cf0003, // %978 = mul(%975, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03d20443, // %979 = mul(%978, %272): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03d10f4d, // %980 = add(%977, %979): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03d20003, // %981 = mul(%978, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03d50447, // %982 = mul(%981, %273): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03d40f59, // %983 = add(%980, %982): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03d50003, // %984 = mul(%981, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03d8044b, // %985 = mul(%984, %274): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03d70f65, // %986 = add(%983, %985): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03d80003, // %987 = mul(%984, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03db044f, // %988 = mul(%987, %275): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03da0f71, // %989 = add(%986, %988): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03db0003, // %990 = mul(%987, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03de0453, // %991 = mul(%990, %276): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03dd0f7d, // %992 = add(%989, %991): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03de0003, // %993 = mul(%990, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03e10457, // %994 = mul(%993, %277): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03e00f89, // %995 = add(%992, %994): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03e10003, // %996 = mul(%993, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03e4045b, // %997 = mul(%996, %278): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03e30f95, // %998 = add(%995, %997): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03e40003, // %999 = mul(%996, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03e7045f, // %1000 = mul(%999, %279): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03e60fa1, // %1001 = add(%998, %1000): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0)
    0x03e70003, // %1002 = mul(%999, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03ea0463, // %1003 = mul(%1002, %280): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03e90fad, /* %1004 = add(%1001, %1003):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x03ea0003, // %1005 = mul(%1002, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03ed0467, // %1006 = mul(%1005, %281): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03ec0fb9, /* %1007 = add(%1004, %1006):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x03ed0003, // %1008 = mul(%1005, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03f0046b, // %1009 = mul(%1008, %282): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03ef0fc5, /* %1010 = add(%1007, %1009):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x03f00003, // %1011 = mul(%1008, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03f3046f, // %1012 = mul(%1011, %283): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03f20fd1, /* %1013 = add(%1010, %1012):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x03f30003, // %1014 = mul(%1011, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03f60473, // %1015 = mul(%1014, %284): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03f50fdd, /* %1016 = add(%1013, %1015):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x03f60003, // %1017 = mul(%1014, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03f90477, // %1018 = mul(%1017, %285): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03f80fe9, /* %1019 = add(%1016, %1018):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x03f90003, // %1020 = mul(%1017, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03fc047b, // %1021 = mul(%1020, %286): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03fb0ff5, /* %1022 = add(%1019, %1021):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x03fc0003, // %1023 = mul(%1020, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x03ff047f, // %1024 = mul(%1023, %287): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x03fe1001, /* %1025 = add(%1022, %1024):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x03ff0003, // %1026 = mul(%1023, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x04020483, // %1027 = mul(%1026, %288): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0401100d, /* %1028 = add(%1025, %1027):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x04020003, // %1029 = mul(%1026, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x04050487, // %1030 = mul(%1029, %289): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x04041019, /* %1031 = add(%1028, %1030):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x04050003, // %1032 = mul(%1029, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0408048b, // %1033 = mul(%1032, %290): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x04071025, /* %1034 = add(%1031, %1033):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x04080003, // %1035 = mul(%1032, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x040b048f, // %1036 = mul(%1035, %291): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x040a1031, /* %1037 = add(%1034, %1036):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x040b0003, // %1038 = mul(%1035, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x040e0493, // %1039 = mul(%1038, %292): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x040d103d, /* %1040 = add(%1037, %1039):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x040e0003, // %1041 = mul(%1038, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x04110497, // %1042 = mul(%1041, %293): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x04101049, /* %1043 = add(%1040, %1042):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x04110003, // %1044 = mul(%1041, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0414049b, // %1045 = mul(%1044, %294): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x04131055, /* %1046 = add(%1043, %1045):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x04140003, // %1047 = mul(%1044, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x0417049f, // %1048 = mul(%1047, %295): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x04161061, /* %1049 = add(%1046, %1048):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x04170003, // %1050 = mul(%1047, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x041a04a3, // %1051 = mul(%1050, %296): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0419106d, /* %1052 = add(%1049, %1051):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x041a0003, // %1053 = mul(%1050, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x041d04a7, // %1054 = mul(%1053, %297): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x041c1079, /* %1055 = add(%1052, %1054):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x041d0003, // %1056 = mul(%1053, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x042004ab, // %1057 = mul(%1056, %298): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x041f1085, /* %1058 = add(%1055, %1057):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x04200003, // %1059 = mul(%1056, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x042304af, // %1060 = mul(%1059, %299): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x04221091, /* %1061 = add(%1058, %1060):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x04230003, // %1062 = mul(%1059, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x042604b3, // %1063 = mul(%1062, %300): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x0425109d, /* %1064 = add(%1061, %1063):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x04260003, // %1065 = mul(%1062, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x042904b7, // %1066 = mul(%1065, %301): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x042810a9, /* %1067 = add(%1064, %1066):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x04290003, // %1068 = mul(%1065, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x042c04bb, // %1069 = mul(%1068, %302): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":144:0)
    0x042b10b5, /* %1070 = add(%1067, %1069):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":142:0) */
    0x042c0003, // %1071 = mul(%1068, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":145:0)
    0x042f0073, // %1072 = mul(%1071, %28): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x042f0003, // %1073 = mul(%1071, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x04310077, // %1074 = mul(%1073, %29): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043010c9, /* %1075 = add(%1072, %1074):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x04310003, // %1076 = mul(%1073, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x0434007b, // %1077 = mul(%1076, %30): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043310d5, /* %1078 = add(%1075, %1077):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x04340003, // %1079 = mul(%1076, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x0437007f, // %1080 = mul(%1079, %31): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043610e1, /* %1081 = add(%1078, %1080):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x04370003, // %1082 = mul(%1079, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x043a0083, // %1083 = mul(%1082, %32): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043910ed, /* %1084 = add(%1081, %1083):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x043a0003, // %1085 = mul(%1082, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x043d0087, // %1086 = mul(%1085, %33): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043c10f9, /* %1087 = add(%1084, %1086):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x043d0003, // %1088 = mul(%1085, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x0440008b, // %1089 = mul(%1088, %34): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x043f1105, /* %1090 = add(%1087, %1089):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x04400003, // %1091 = mul(%1088, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x0443008f, // %1092 = mul(%1091, %35): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04421111, /* %1093 = add(%1090, %1092):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x04430003, // %1094 = mul(%1091, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x04460093, // %1095 = mul(%1094, %36): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0445111d, /* %1096 = add(%1093, %1095):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x04460003, // %1097 = mul(%1094, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x04490097, // %1098 = mul(%1097, %37): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04481129, /* %1099 = add(%1096, %1098):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x04490003, // %1100 = mul(%1097, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x044c009b, // %1101 = mul(%1100, %38): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x044b1135, /* %1102 = add(%1099, %1101):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x044c0003, // %1103 = mul(%1100, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x044f009f, // %1104 = mul(%1103, %39): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x044e1141, /* %1105 = add(%1102, %1104):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x044f0003, // %1106 = mul(%1103, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x045200a3, // %1107 = mul(%1106, %40): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x0451114d, /* %1108 = add(%1105, %1107):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x04520003, // %1109 = mul(%1106, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x045500a7, // %1110 = mul(%1109, %41): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04541159, /* %1111 = add(%1108, %1110):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x04550003, // %1112 = mul(%1109, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x045800ab, // %1113 = mul(%1112, %42): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x04571165, /* %1114 = add(%1111, %1113):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x04580003, // %1115 = mul(%1112, %0): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":150:0)
    0x045b00af, // %1116 = mul(%1115, %43): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0)
    0x045a1171, /* %1117 = add(%1114, %1116):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":149:0) */
    0x036f0012, // %1118 = sub(%879, %4): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0)
    0x0002000e, // %1119 = sub(%2, %3): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x045f0108, // %1120 = inv(%1119): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0)
    0x045e1183, /* %1121 = mul(%1118, %1120):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0) */
    0x035d0016, // %1122 = sub(%861, %5): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0)
    0x0006000b, // %1123 = mul(%6, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x0462118e, /* %1124 = sub(%1122, %1123):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x00030007, // %1125 = mul(%3, %1): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x00021196, // %1126 = sub(%2, %1125): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x045f119b, /* %1127 = mul(%1119, %1126):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x04670108, // %1128 = inv(%1127): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0)
    0x046411a3, /* %1129 = mul(%1124, %1128):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0) */
    0x046111a5, /* %1130 = add(%1121, %1129):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0) */
    0x0354001e, // %1131 = sub(%852, %7): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0)
    0x0008000b, // %1132 = mul(%8, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x046b11b2, /* %1133 = sub(%1131, %1132):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x0002000b, // %1134 = mul(%2, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x000911bb, // %1135 = mul(%9, %1134): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x046d11be, /* %1136 = sub(%1133, %1135):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x00010007, // %1137 = mul(%1, %1): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x000311c7, // %1138 = mul(%3, %1137): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x000211ca, // %1139 = sub(%2, %1138): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x046711cf, /* %1140 = mul(%1127, %1139):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x04740108, // %1141 = inv(%1140): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0)
    0x047011d7, /* %1142 = mul(%1136, %1141):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0) */
    0x046a11d9, /* %1143 = add(%1130, %1142):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0) */
    0x042e002a, // %1144 = sub(%1070, %10): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0)
    0x000b000b, // %1145 = mul(%11, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x047811e6, /* %1146 = sub(%1144, %1145):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x000c11bb, // %1147 = mul(%12, %1134): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x047a11ee, /* %1148 = sub(%1146, %1147):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x000211bb, // %1149 = mul(%2, %1134): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x000d11f7, // %1150 = mul(%13, %1149): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x047c11fa, /* %1151 = sub(%1148, %1150):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x046e11bb, /* %1152 = mul(%1134, %1134):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0) */
    0x000e1203, // %1153 = mul(%14, %1152): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x047f1206, /* %1154 = sub(%1151, %1153):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x00021203, // %1155 = mul(%2, %1152): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x000f120f, // %1156 = mul(%15, %1155): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x04821212, /* %1157 = sub(%1154, %1156):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x000111c7, // %1158 = mul(%1, %1137): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x0003121b, // %1159 = mul(%3, %1158): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x0002121e, // %1160 = sub(%2, %1159): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x04741223, /* %1161 = mul(%1140, %1160):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x047111c7, /* %1162 = mul(%1137, %1137):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0) */
    0x0003122b, // %1163 = mul(%3, %1162): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x0002122e, // %1164 = sub(%2, %1163): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x04891233, /* %1165 = mul(%1161, %1164):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x048a122b, /* %1166 = mul(%1162, %1162):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0) */
    0x048e123b, /* %1167 = mul(%1166, %1166):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0) */
    0x0001123f, // %1168 = mul(%1, %1167): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x04901243, /* %1169 = mul(%1168, %1168):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0) */
    0x04911247, /* %1170 = mul(%1169, %1169):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0) */
    0x0003124b, // %1171 = mul(%3, %1170): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x0002124e, // %1172 = sub(%2, %1171): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x048d1253, /* %1173 = mul(%1165, %1172):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x04950108, // %1174 = inv(%1173): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0)
    0x0485125b, /* %1175 = mul(%1157, %1174):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0) */
    0x0477125d, /* %1176 = add(%1143, %1175):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0) */
    0x022f0042, // %1177 = sub(%559, %16): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0)
    0x0011000b, // %1178 = mul(%17, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x0499126a, /* %1179 = sub(%1177, %1178):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x001211bb, // %1180 = mul(%18, %1134): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x049b1272, /* %1181 = sub(%1179, %1180):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x001311f7, // %1182 = mul(%19, %1149): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x049d127a, /* %1183 = sub(%1181, %1182):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x00141203, // %1184 = mul(%20, %1152): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x049f1282, /* %1185 = sub(%1183, %1184):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x0015120f, // %1186 = mul(%21, %1155): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x04a1128a, /* %1187 = sub(%1185, %1186):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x0486121b, /* %1188 = mul(%1158, %1158):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0) */
    0x00011293, // %1189 = mul(%1, %1188): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x00031297, // %1190 = mul(%3, %1189): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x0002129a, // %1191 = sub(%2, %1190): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x0474129f, /* %1192 = mul(%1140, %1191):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x04a51297, /* %1193 = mul(%1189, %1189):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0) */
    0x000112a7, // %1194 = mul(%1, %1193): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x000312ab, // %1195 = mul(%3, %1194): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x000212ae, // %1196 = sub(%2, %1195): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x04a812b3, /* %1197 = mul(%1192, %1196):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x0003123f, // %1198 = mul(%3, %1167): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x000212ba, // %1199 = sub(%2, %1198): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":171:0)
    0x04ad12bf, /* %1200 = mul(%1197, %1199):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x04b00108, // %1201 = inv(%1200): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0)
    0x04a312c7, /* %1202 = mul(%1187, %1201):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0) */
    0x049812c9, /* %1203 = add(%1176, %1202):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0) */
    0x02d4005a, // %1204 = sub(%724, %22): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0)
    0x0017000b, // %1205 = mul(%23, %2): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x04b412d6, /* %1206 = sub(%1204, %1205):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x001811bb, // %1207 = mul(%24, %1134): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x04b612de, /* %1208 = sub(%1206, %1207):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x001911f7, // %1209 = mul(%25, %1149): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x04b812e6, /* %1210 = sub(%1208, %1209):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x001a1203, // %1211 = mul(%26, %1152): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":161:0)
    0x04ba12ee, /* %1212 = sub(%1210, %1211):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":159:0) */
    0x045f11cf, /* %1213 = mul(%1119, %1139):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x04bd129f, /* %1214 = mul(%1213, %1191):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x04be12b3, /* %1215 = mul(%1214, %1196):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x04bf12bf, /* %1216 = mul(%1215, %1199):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":168:0) */
    0x04c00108, // %1217 = inv(%1216): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0)
    0x04bc1307, /* %1218 = mul(%1212, %1217):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0) */
    0x04b31309, /* %1219 = add(%1203, %1218):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":174:0) */
    0x045d006e, // %1220 = sub(%1117, %27): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":177:0)
    0x0003000f, // %1221 = mul(%3, %3): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04c51317, /* %1222 = mul(%1221, %1221):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0) */
    0x0002131a, // %1223 = sub(%2, %1222): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":178:0)
    0x04c70108, // %1224 = inv(%1223): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":180:0)
    0x04c41323, /* %1225 = mul(%1220, %1224):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":180:0) */
    0x04c31325, /* %1226 = add(%1219, %1225):
                 * loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":180:0) */
    0x00000704, // set($0x0000, 0x07): loc("cirgen/compiler/passes/MakeVerifyTaps.cpp":182:0)
];

#[inline(always)]
pub fn verify_taps_rv32im(
    arg0: &[u32; 4 * EXT_ELEM_SIZE],
    arg1: &[u32; 24 * EXT_ELEM_SIZE],
    arg2: &[u32; 16 * EXT_ELEM_SIZE],
    arg3: &[u32; 36 * EXT_ELEM_SIZE],
    arg4: &[u32; 15 * EXT_ELEM_SIZE],
    arg5: &[u32; 208 * EXT_ELEM_SIZE],
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
