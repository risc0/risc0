#!/usr/bin/env python

import sys
import os
from pathlib import Path
import subprocess
import re

EXTENSIONS = [
    ".md",
]

EXCEPTIONS = [
    # allow refs to trusted setup ceremony assets
    "d4e427283027c28b38b8eda1562e8e0e68d1b0e2",
    # allow link to risc0-ethereum before versioning started to match with 1.0
    "github.com/risc0/risc0-ethereum/blob/release-0.7",
    "github.com/risc0/risc0-ethereum/blob/release-0.10",
    # allow links to v1.1.0-rc.3, which is referenced as a deployed version of contracts.
    "github.com/risc0/risc0-ethereum/tree/v1.1.0-rc.3/contracts/",
    # For 2.1, we didn't release a new version of risc0-zkvm-platform
    "https://docs.rs/risc0-zkvm-platform/2.0/risc0_zkvm_platform/fileno/index.html"
]

REPOS = [
    "risc0",
    "risc0-ethereum",
]

VERSIONED_DOCS_DIR = "website/api_versioned_docs"
VERSIONED_PATH_RE = re.compile(r"api_versioned_docs/version-(?P<version>\d+\.\d+)")
GITHUB_LINK_RE = re.compile(r"github\.com/risc0/(?P<repo>\S+?)/(?:tree|blob)/(?P<ref>\S+?)/")
DOCSRS_LINK_RE = re.compile(r"docs\.rs/(?P<crate>risc0-[^/]+)/(?P<ref>\S+?)/")


def check_file(root, file):
    rel_path = file.relative_to(root)

    match = VERSIONED_PATH_RE.search(str(rel_path))
    if match is None:
        print(f"{rel_path}: could not determine version from path")
        return 1
    version = match.group("version")

    status = 0
    lines = file.read_text().splitlines()
    for linenum, line in enumerate(lines, 1):
        # Check the line for any of the strings in the exceptions list.
        if any(e in line for e in EXCEPTIONS):
            continue

        # Check links to files in versioned GitHub repos.
        for link in GITHUB_LINK_RE.finditer(line):
            repo = link.group("repo")

            # Only cover repos that use consistent versioning schemes.
            if repo not in REPOS:
                continue

            ref = link.group("ref")
            expected_ref = f"release-{version}"
            if ref != expected_ref:
                print(
                    f"{rel_path}:{linenum}\n{line}\ngithub link to {repo} at ref {ref}; expected {expected_ref}\n"
                )
                status = 1

        # Check links to crate documentation on docs.rs.
        for link in DOCSRS_LINK_RE.finditer(line):
            crate = link.group("crate")
            ref = link.group("ref")
            expected_ref = f"{version}"
            if ref != expected_ref:
                print(
                    f"{rel_path}:{linenum}\n{line}\ndocs.rs link to {crate} at ref {ref}; expected {expected_ref}\n"
                )
                status = 1
    return status


def repo_root():
    """Return an absolute Path to the repo root"""
    cmd = ["git", "rev-parse", "--show-toplevel"]
    return Path(subprocess.check_output(cmd, encoding="UTF-8").strip())


def tracked_files_in(directory):
    """Yield file paths tracked by git within a directory"""
    cmd = ["git", "ls-tree", "--full-tree", "--name-only", "-r", "HEAD", directory]
    tree = subprocess.check_output(cmd, encoding="UTF-8").strip()
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
