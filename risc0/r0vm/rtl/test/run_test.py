#!/usr/bin/env python

import subprocess
import sys

subprocess.run(["risc0/r0vm/rtl/test/risc0-simulate", "risc0/r0vm/rtl/test/" + sys.argv[1], "2048"])
