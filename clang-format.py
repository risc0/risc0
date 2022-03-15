# Copyright 2022 Risc0, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#!/usr/bin/env python

import os
import subprocess
import pathlib
import sys

EXTENSIONS = [
    '.cpp',
    '.h',
]

def main():
    clang_format = pathlib.Path(sys.prefix) / 'bin' / 'clang-format'
    root = pathlib.Path(os.getenv('BUILD_WORKSPACE_DIRECTORY')) / 'risc0'
    for root, _, files in os.walk(root):
        for file in files:
            path = pathlib.Path(root) / file
            if path.suffix in EXTENSIONS:
                print('.', end='', flush=True)
                subprocess.run([clang_format, '-i', path])
    print()


if __name__ == "__main__":
    main()
