load("@rules_cuda//cuda:defs.bzl", "cuda_library", "requires_cuda")

cuda_library(
    name = "risc0_sys",
    srcs = [
        "kernels/zkp/cuda/kernels.cu",
        "kernels/zkp/cuda/supra/ntt.cu",
        "kernels/zkp/cuda/supra/poseidon2.cu",
    ],
    hdrs = [
        "kernels/zkp/cuda/fp.h",
        "kernels/zkp/cuda/fpext.h",
        "kernels/zkp/cuda/kernels.h",
        "kernels/zkp/cuda/supra/poseidon2.cuh",
        "kernels/zkp/cuda/supra/poseidon2_constants.cuh",
    ],
    defines = ["FEATURE_BABY_BEAR"],
    includes = ["kernels"],
    target_compatible_with = requires_cuda(),
    visibility = ["//visibility:public"],
    deps = ["@sppark"],
)
