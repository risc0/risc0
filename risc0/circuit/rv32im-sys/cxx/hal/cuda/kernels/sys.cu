// Copyright 2026 RISC Zero, Inc.
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

#include <cuda_runtime.h>

#include <iostream>

extern "C" void* cuda_malloc(size_t size) {
  void* out;
  cudaError_t err = cudaMalloc(&out, size);
  if (err != cudaSuccess) {
    return nullptr;
  }
  return out;
}

extern "C" void cuda_free(void* buf) {
  cudaFree(buf);
}

extern "C" bool cuda_sync(cudaStream_t stream) {
  cudaError_t err = cudaStreamSynchronize(stream);
  if (err != cudaSuccess) {
    fprintf(stderr, "Failed to sync: %s\n", cudaGetErrorString(err));
  }
  return err == cudaSuccess;
}

extern "C" bool
cuda_copy_to_host_sync(cudaStream_t stream, void* host, const void* dev, size_t size) {
  cudaError_t err = cudaMemcpyAsync(host, dev, size, cudaMemcpyDeviceToHost, stream);
  if (!cuda_sync(stream))
    return false;
  return err == cudaSuccess;
}

extern "C" bool
cuda_copy_to_dev_sync(cudaStream_t stream, void* dev, const void* host, size_t size) {
  cudaError_t err = cudaMemcpyAsync(dev, host, size, cudaMemcpyHostToDevice, stream);
  if (!cuda_sync(stream))
    return false;
  return err == cudaSuccess;
}

extern "C" bool cuda_copy_dev(cudaStream_t stream, void* dst, void* src, size_t size) {
  cudaError_t err = cudaMemcpyAsync(dst, src, size, cudaMemcpyDeviceToDevice, stream);
  if (!cuda_sync(stream))
    return false;
  return err == cudaSuccess;
}

extern "C" bool cuda_zero_dev(cudaStream_t stream, void* buf, size_t size) {
  cudaError_t err = cudaMemsetAsync(buf, 0, size, stream);
  if (!cuda_sync(stream))
    return false;
  return err == cudaSuccess;
}

extern "C" bool cuda_stream_create(cudaStream_t* stream) {
  cudaError_t err = cudaStreamCreate(stream);
  return err == cudaSuccess;
}

extern "C" bool cuda_stream_destroy(cudaStream_t stream) {
  cudaError_t err = cudaStreamDestroy(stream);
  return err == cudaSuccess;
}
