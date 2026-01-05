#!/bin/bash

set -euxo pipefail

echo "=== GPU readiness gate ==="
date -Is
id
uname -a

# echo "--- FS sanity ---"
# echo "HOME=$HOME"
# ls -ld "$HOME" /tmp || true
# mount | egrep ' /tmp | noexec' || true

# mkdir -p "$HOME/.nv/ComputeCache" || true
# touch "$HOME/.nv/ComputeCache/_write_test" || true

# export CUDA_CACHE_PATH=/tmp/cuda_cache
# mkdir -p "$CUDA_CACHE_PATH"

echo "--- /dev nodes ---"
ls -l /dev/nvidia* || true

echo "--- nvidia-smi ---"
nvidia-smi || true

echo "--- compute procs ---"
nvidia-smi --query-compute-apps=pid,process_name,gpu_uuid,used_memory --format=csv || true

echo "--- CUDA smoke ---"
mkdir -p ./tmp
nvcc --version
nvcc ./tools/cuda-smoke/cuda_smoke.cu -o ./tmp/cuda_smoke

ldd ./tmp/cuda_smoke | egrep 'libcuda|cudart|nvidia'

# Show which libcuda would be resolved
ldconfig -p | grep -E '^(\s*)libcuda\.so\.1' || true

# Find obvious stub locations
ls -l /usr/local/cuda*/lib64/stubs/libcuda.so 2>/dev/null || true
ls -l /usr/lib/x86_64-linux-gnu/libcuda.so.1 2>/dev/null || true

strace -f -e openat ./tmp/cuda_smoke 2>&1 | egrep 'libcuda|libcudart|stubs' | head -n 50
