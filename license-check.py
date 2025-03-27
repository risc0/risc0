#!/usr/bin/env python

import sys
import os
from pathlib import Path
import subprocess
import argparse

PUBLIC_HEADER = """
// Copyright {YEAR} RISC Zero, Inc.
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
""".strip().splitlines()

EXTENSIONS = [
    ".cpp",
    ".h",
    ".rs",
]

SKIP_DIRS = [
    str(Path.cwd()) + "/risc0/cargo-risczero/templates/rust-starter",
    str(Path.cwd()) + "/risc0/sys/cxx/vendor",
    str(Path.cwd()) + "/risc0/zkvm/src/host/protos",
    str(Path.cwd()) + "/risc0/zkvm/src/host/server/exec",
    str(Path.cwd()) + "/risc0/cargo-risczero/tests/test_crate",
]


def check_header(expected_year, lines_actual):
    for expected, actual in zip(PUBLIC_HEADER, lines_actual):
        expected = expected.replace("{YEAR}", expected_year)
        if expected != actual:
            return (expected, actual)
    return None


def check_file(root, file, replace):
    cmd = ["git", "log", "-1", "--format=%ad", "--date=format:%Y", file]
    expected_year = subprocess.check_output(cmd, encoding="UTF-8").strip()
    rel_path = file.relative_to(root)
    lines = file.read_text().splitlines()
    result = check_header(expected_year, lines)
    if result:
        print(f"{rel_path}: invalid header!")
        print(f"  expected: {result[0]}")
        print(f"    actual: {result[1]}")
        if replace:
            replace_header(file, result[0], result[1])
        return 1
    return 0

def replace_header(file, expected, actual):
    content=""
    with open(file, 'r', encoding='utf-8') as f:
        content = f.read()

    new_content = content.replace(actual, expected)
    with open(file, 'w', encoding='utf-8') as f:
        f.write(new_content)

    return None

def repo_root():
    """Return an absolute Path to the repo root"""
    cmd = ["git", "rev-parse", "--show-toplevel"]
    return Path(subprocess.check_output(cmd, encoding="UTF-8").strip())


def tracked_files():
    """Yield all file paths tracked by git"""
    cmd = ["git", "ls-tree", "--full-tree", "--name-only", "-r", "HEAD"]
    tree = subprocess.check_output(cmd, encoding="UTF-8").strip()
    for path in tree.splitlines():
        yield (repo_root() / Path(path)).absolute()


def main():

    parser = argparse.ArgumentParser(description="to update years, use the --write option")
    parser.add_argument("--write", action="store_true", help="modify files with correct year")
    args = parser.parse_args()

    root = repo_root()
    ret = 0
    for path in tracked_files():
        if path.suffix in EXTENSIONS and ".inc" not in path.suffixes:
            skip = False
            for path_start in SKIP_DIRS:
                if str(path).startswith(path_start):
                    skip = True
                    break
            if skip:
                continue

            ret |= check_file(root, path, args.write)
    sys.exit(ret)


if __name__ == "__main__":
    main()
