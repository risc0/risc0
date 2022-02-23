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
