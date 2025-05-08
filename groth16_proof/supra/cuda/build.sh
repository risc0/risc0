#!/bin/bash

set -e
set -x

if [ ! -f "libblst.a" ]; then
    git clone https://github.com/supranational/blst.git
    sh blst/build.sh
fi

if [ ! -d "sppark" ]; then
    git clone https://github.com/dot-asm/sppark -b rc0.1.12
fi

INCLUDES="-Isppark -Iblst/src"
CXXFLAGS="-Xcompiler -Wall,-Wextra,-O2 -std=c++14 -D__ADX__ -g"
NVCCFLAGS="-O2 -arch=sm_80 -gencode arch=compute_70,code=sm_70 -t0"
LIB_WITNESSCALC="../circom-witnesscalc/target/release/libcircom_witnesscalc.a"

nvcc -DSRS_READ_COEFFS -DFEATURE_BN254 $CXXFLAGS $NVCCFLAGS $INCLUDES sppark/util/all_gpus.cpp setup_prover.cu -o setup_prover libblst.a &
nvcc -DFEATURE_BN254 $CXXFLAGS $NVCCFLAGS $INCLUDES sppark/util/all_gpus.cpp run_prover.cu -o run_prover $LIB_WITNESSCALC libblst.a &

wait
