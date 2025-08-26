#!/usr/bin/env python

import sys
import os
import re
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
""".strip()

PUBLIC_HEADER_RE = re.compile(
    "^"
    + PUBLIC_HEADER.replace("(", "\\(")
    .replace(")", "\\)")
    .replace("{YEAR}", "(?P<year>[0-9]+)"),
)

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


def fix_file(file_obj, file_contents, start, end, insert):
    file_contents = file_contents[:start] + insert + file_contents[end:]
    file_obj.seek(0)
    file_obj.truncate()
    file_obj.write(file_contents)


def check_file(root, file, fix):
    cmd = ["git", "log", "-1", "--format=%ad", "--date=format:%Y", file]
    expected_year = subprocess.check_output(cmd, encoding="UTF-8").strip()
    rel_path = file.relative_to(root)

    with open(file, "r+") as file_obj:
        file_contents = file_obj.read()
        match = PUBLIC_HEADER_RE.match(file_contents)

        if match:
            actual_year = match.group("year")
            if actual_year != expected_year:
                print(f"{rel_path}: invalid header!")
                print(f"license has wrong year {actual_year}, expected {expected_year}")
                if fix:
                    print(f"fixing {rel_path}")
                    start, end = match.span(1)
                    fix_file(file_obj, file_contents, start, end, expected_year)
                else:
                    return 1
        else:
            print(f"{rel_path}: invalid header!")
            print("license completely missing")
            if fix:
                print(f"fixing {rel_path}")
                header = PUBLIC_HEADER.replace("{YEAR}", expected_year) + "\n"
                fix_file(file_obj, file_contents, 0, 0, header)
            else:
                return 1

    return 0


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

    parser = argparse.ArgumentParser(
        description="to update years, use the --fix option"
    )
    parser.add_argument(
        "--fix", action="store_true", help="modify files with correct year"
    )
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

            ret |= check_file(root, path, args.fix)
    sys.exit(ret)


if __name__ == "__main__":
    main()
