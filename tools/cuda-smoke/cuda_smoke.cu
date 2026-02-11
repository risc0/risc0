#include <cuda_runtime.h>
#include <stdio.h>

#define CK(call)                                                                                   \
  do {                                                                                             \
    cudaError_t e = (call);                                                                        \
    if (e != cudaSuccess) {                                                                        \
      fprintf(stderr,                                                                              \
              "%s:%d %s -> %d (%s)\n",                                                             \
              __FILE__,                                                                            \
              __LINE__,                                                                            \
              #call,                                                                               \
              (int)e,                                                                              \
              cudaGetErrorString(e));                                                              \
      return 1;                                                                                    \
    }                                                                                              \
  } while (0)

int main() {
  CK(cudaSetDevice(0));
  CK(cudaFree(0)); // forces context creation
  cudaStream_t s;
  CK(cudaStreamCreate(&s));
  CK(cudaStreamDestroy(s));
  printf("OK\n");
  return 0;
}
