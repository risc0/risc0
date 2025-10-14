#include <cuda_runtime.h>

int main()
{
    int n;
    if (cudaGetDeviceCount(&n)!=cudaSuccess || n==0)
        return 1;
    bool found = false;
    while (n--) {
        cudaDeviceProp prop;
        found |= cudaGetDeviceProperties(&prop, n)==cudaSuccess &&
                 prop.major>=7;
    }
    return !found;
}
