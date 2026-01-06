#!/bin/bash

set -euxo pipefail

echo "=== GPU readiness gate ==="
date -Is
id
uname -a

echo "--- /dev nodes ---"
ls -l /dev/nvidia* || true

required=(/dev/nvidiactl /dev/nvidia0 /dev/nvidia-uvm)
missing=0
for n in "${required[@]}"; do
  if [[ ! -e "$n" ]]; then
    echo "ERROR: missing required NVIDIA node: $n"
    missing=1
  fi
done

if [[ "$missing" -ne 0 ]]; then
  echo "ERROR: GPU device nodes incomplete inside container; likely created before host UVM was ready."
  echo "Hint: restart container or fix host boot ordering (load nvidia_uvm earlier)."
  exit 1
fi

echo "--- nvidia-smi ---"
nvidia-smi || true

echo "--- compute procs ---"
nvidia-smi --query-compute-apps=pid,process_name,gpu_uuid,used_memory --format=csv || true

echo "--- CUDA smoke ---"
mkdir -p ./tmp
nvcc --version
nvcc ./tools/cuda-smoke/cuda_smoke.cu -o ./tmp/cuda_smoke

ldd ./tmp/cuda_smoke

# Show which libcuda would be resolved
ldconfig -p | grep -E '^(\s*)libcuda\.so\.1' || true

# Find obvious stub locations
ls -l /usr/local/cuda*/lib64/stubs/libcuda.so 2>/dev/null || true
ls -l /usr/lib/x86_64-linux-gnu/libcuda.so.1 2>/dev/null || true

strace -f -e openat ./tmp/cuda_smoke 2>&1 | egrep 'libcuda|libcudart|stubs' | head -n 50
