#include "gpu_t.cuh"

#if defined(__NVCC__)
# define PROP_MAJOR_MIN 7   // Volta and forward
#elif defined(__HIPCC__)
# define PROP_MAJOR_MIN 9   // CDNA/RDNA
#else
# error "unknown platform"
#endif

class gpus_t {
    std::vector<const gpu_t*> gpus;
public:
    gpus_t()
    {
        int n;
        if (cudaGetDeviceCount(&n) != cudaSuccess)
            return;
        for (int id = 0; id < n; id++) {
            cudaDeviceProp prop;
            if (cudaGetDeviceProperties(&prop, id) == cudaSuccess &&
                prop.major >= PROP_MAJOR_MIN && prop.cooperativeLaunch) {
                (void)cudaSetDevice(id);
                gpus.push_back(new gpu_t(gpus.size(), id, prop));
            }
        }
        (void)cudaSetDevice(0);
    }
    ~gpus_t()
    {   for (auto* ptr: gpus) delete ptr;   }

    static const auto& all()
    {
        static gpus_t all_gpus;
        return all_gpus.gpus;
    }
};

const gpu_t& select_gpu(int id)
{
    auto& gpus = gpus_t::all();
    if (gpus.size() == 0)
        CUDA_OK(cudaErrorNoDevice);
    if (id == -1) {
        int cuda_id;
        CUDA_OK(cudaGetDevice(&cuda_id));
        for (auto* gpu: gpus)
           if (gpu->cid() == cuda_id) return *gpu;
        id = 0;
    }
    auto* gpu = gpus[id];
    gpu->select();
    return *gpu;
}

const cudaDeviceProp& gpu_props(int id)
{   return gpus_t::all()[id]->props();   }

size_t ngpus()
{   return gpus_t::all().size();   }

const std::vector<const gpu_t*>& all_gpus()
{   return gpus_t::all();   }

SPPARK_FFI bool cuda_available()
{   return gpus_t::all().size() != 0;   }

SPPARK_FFI void drop_gpu_ptr_t(gpu_ptr_t<void>& ref)
{   ref.~gpu_ptr_t();   }

#ifdef __clang__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
#endif

SPPARK_FFI gpu_ptr_t<void>::by_value clone_gpu_ptr_t(const gpu_ptr_t<void>& rhs)
{   return rhs;   }

#ifdef __clang__
# pragma clang diagnostic pop
#endif

#ifdef TAKE_RESPONSIBILITY_FOR_ERROR_MESSAGE
SPPARK_FFI void drop_error_message(char *ptr)
{   free(ptr);   }
#endif
