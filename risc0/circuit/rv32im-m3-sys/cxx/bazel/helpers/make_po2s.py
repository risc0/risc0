#!/usr/bin/env python3

import sys

template = '''
#define NUM_ROWS_PO2 {po2}
#define NAMESPACE {func}_{platform}_impl_{po2}
#define FUNCNAME {func}_{platform}_{po2}
#define FUNCNAME_APPEND(x) {func}_{platform}_{po2}_ ## x
#include "{base_dir}/{func}_impl.h"
'''

func = sys.argv[1]
ext = sys.argv[2]
platform = sys.argv[3]
odir = sys.argv[4]
base_dir = odir[odir.find("bin/") + 4:]
for i in range(12, 23):
  file = open("{odir}/{func}_{po2}.{ext}".format(odir=odir, func=func, ext=ext, po2=i), "w")
  file.write(template.format(func=func, platform=platform, base_dir=base_dir, po2=i))
  file.close()
