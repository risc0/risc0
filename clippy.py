#!/usr/bin/env python3

import argparse
import subprocess
import sys

CRATES = [
    ("bonsai-sdk", None),
    ("hotbench", None),
    ("risc0-binfmt", None),
    ("risc0-build", None),
    ("risc0-build-kernel", None),
    ("risc0-circuit-recursion", "default"),
    ("risc0-circuit-recursion-sys", "default"),
    ("risc0-circuit-rv32im", "default"),
    ("risc0-circuit-rv32im-sys", "default"),
    ("risc0-core", None),
    ("risc0-groth16", None),
    ("risc0-r0vm", None),
    ("risc0-sys", None),
    ("risc0-tools", None),
    ("risc0-zkp", "prove"),
    ("risc0-zkvm", "prove"),
    ("risc0-zkvm-platform", None),
    ("risc0-zkvm-receipts", None),
]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-F", "--feature", default="default")
    args = parser.parse_args()

    for crate, default in CRATES:
        print(f"::group::{crate}")

        cmd = ["cargo", "clippy", "-p", crate]

        if args.feature == "default":
            feature = default
        elif default:
            feature = args.feature
        else:
            feature = None

        if feature:
            cmd.append("-F")
            cmd.append(feature)

        # print(cmd)
        subprocess.run(cmd, check=True)
        print("::endgroup::")


if __name__ == "__main__":
    try:
        main()
    except:
        sys.exit("clippy failure")
