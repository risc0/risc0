#!/usr/bin/env python

from typing import Optional
from pydantic import BaseModel
import buildkite_sdk as bk

ENV = dict(
    RISC0_RUST_TOOLCHAIN_VERSION="1.91.1",
    RISC0_CPP_TOOLCHAIN_VERSION="2024.01.05",
    RISC0_GROTH16_VERSION="0.1.0",
)

FILTERS = dict(
    base=[
        ".buildkite/**",
        "Cargo.toml",
        "Cargo.lock",
        "rust-toolchain.toml",
    ],
)

PLUGINS = [
    ".buildkite/plugins/cuda",
    ".buildkite/plugins/rustup",
    ".buildkite/plugins/sccache",
    ".buildkite/plugins/protoc",
]


class TestVariant(BaseModel):
    arch: str
    os: str
    device: str
    feature: str = "default"
    nvcc_arch: Optional[str] = None
    test_cmd: str
    partition: int
    ci_profile: str
    skip: Optional[bool] = False


class Pipeline:
    def __init__(self):
        self.pipeline = bk.Pipeline(env=ENV)

    def step_check(self):
        self.pipeline.add_step(
            bk.CommandStep(
                label=":white_check_mark:",
                agents=dict(os="linux"),
                plugins=[".buildkite/plugins/rustup"],
                command=".buildkite/steps/check.sh",
            )
        )

    def step_clippy(self):
        VARIANTS = [
            ("linux", "x64", "default"),
            ("linux", "x64", "cuda"),
        ]

        group_steps = [
            bk.CommandStep(
                label=f":rust: :clippy: {os}/{arch}/{feature}",
                if_changed=FILTERS["base"]
                + [
                    "risc0/**",
                    "rzup/**",
                ],
                agents=dict(arch=arch, os=os),
                env=dict(
                    FEATURE=feature,
                    RISC0_SKIP_BUILD=1,
                    RISC0_SKIP_BUILD_KERNELS=1,
                ),
                plugins=PLUGINS,
                command=".buildkite/steps/clippy.sh",
            )
            for os, arch, feature in VARIANTS
        ]

        self.pipeline.add_step(
            bk.GroupStep(
                group="clippy",
                steps=group_steps,
            )
        )

    def step_test(self):
        VARIANTS = [
            TestVariant(
                os="linux",
                arch="x64",
                device="nvidia_rtx_4000_ada",
                feature="cuda",
                nvcc_arch="sm_89",
                test_cmd="cargo nextest run",
                partition=1,
                ci_profile="slow",
            ),
            TestVariant(
                skip=True,
                os="macos",
                arch="arm64",
                device="apple_m2_pro",
                test_cmd="cargo nextest run --partition hash:1/2",
                partition=1,
                ci_profile="fast",
            ),
            TestVariant(
                skip=True,
                os="macos",
                arch="arm64",
                device="apple_m2_pro",
                test_cmd="cargo nextest run --partition hash:2/2",
                partition=2,
                ci_profile="fast",
            ),
        ]

        group_steps = [
            bk.CommandStep(
                label=f":rust: test {var.os}/{var.arch}/{var.device}",
                skip=var.skip,
                if_changed=FILTERS["base"]
                + [
                    "bonsai/sdk/**",
                    "external/**",
                    "groth16_proof/**",
                    "risc0/**",
                    "rzup/**",
                    "xtask/**",
                ],
                agents=dict(arch=var.arch, os=var.os, device=var.device),
                env=dict(
                    FEATURE=var.feature,
                    NVCC_APPEND_FLAGS=f"-arch={var.nvcc_arch}",
                    RISC0_BUILD_LOCKED=1,
                    RISC0_DEFAULT_PROVER_NUM_GPUS=1,
                    RUST_BACKTRACE="full",
                    RUSTFLAGS=f'--cfg ci --cfg ci_profile="{var.ci_profile}"',
                    # SCCACHE_RECACHE=1,
                    TEST_CMD=var.test_cmd,
                ),
                plugins=PLUGINS,
                command=".buildkite/steps/test.sh",
                artifact_paths=["target/cargo-timings/**"],
            )
            for var in VARIANTS
        ]

        self.pipeline.add_step(
            bk.GroupStep(
                group="test",
                steps=group_steps,
            )
        )

    def to_yaml(self):
        return self.pipeline.to_yaml()


def main():
    pipeline = Pipeline()

    pipeline.step_check()
    pipeline.step_clippy()
    pipeline.step_test()

    print(pipeline.to_yaml())


if __name__ == "__main__":
    main()
