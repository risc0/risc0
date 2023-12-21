#!/usr/bin/env python

import sys
import os
from pathlib import Path
import subprocess
import re

EXTENSIONS = [
    '.md',
]

VERSIONED_DOCS_DIR = "website/api_versioned_docs"
VERSIONED_PATH_RE = re.compile(r"api_versioned_docs/version-(?P<version>\d+\.\d+)")
GITHUB_LINK_RE = re.compile(r"github\.com/risc0/risc0/(?:tree|blob)/(?P<ref>\S+?)/")

def check_file(root, file):
    rel_path = file.relative_to(root)

    match = VERSIONED_PATH_RE.search(str(rel_path))
    if match is None:
        print(f'{rel_path}: could not determine version from path')
        return 1
    version = match.group('version')
    expected_ref = f"release-{version}"

    status = 0
    lines = file.read_text().splitlines()
    for (linenum, line) in enumerate(lines, 1):
        for link in GITHUB_LINK_RE.finditer(line):
            ref = link.group('ref')
            if ref != expected_ref:
                print(f"{rel_path}:{linenum}\ngithub link to git ref {ref}; expected {expected_ref}\n")
                status = 1
    return status


def repo_root():
    """Return an absolute Path to the repo root"""
    cmd = ["git", "rev-parse", "--show-toplevel"]
    return Path(subprocess.check_output(cmd, encoding='UTF-8').strip())


def tracked_files_in(directory):
    """Yield file paths tracked by git within a directory"""
    cmd = ["git", "ls-tree", "--full-tree", "--name-only", "-r", "HEAD", directory]
    tree = subprocess.check_output(cmd, encoding='UTF-8').strip()
    for path in tree.splitlines():
        yield (repo_root() / Path(path)).absolute()


def main():
    root = repo_root()
    ret = 0
    for path in tracked_files_in(VERSIONED_DOCS_DIR):
        if path.suffix in EXTENSIONS:
            ret |= check_file(root, path)
    sys.exit(ret)


if __name__ == "__main__":
    main()
