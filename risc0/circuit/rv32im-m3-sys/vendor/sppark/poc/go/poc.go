package poc_cu

// #include "cgo_sppark.h"
// WRAP_ERR(Error, cuda_func, void *ptr)
// {   toGoError(go_err, (*cuda_func.call)(ptr));   }
import "C"

import (
    sppark "github.com/supranational/sppark/go"
)

func init() {
    sppark.Load("poc.cu", "-O2")
}

func CudaFunc() {
    var err C.GoError
    C.go_cuda_func(&err, nil)
    if err.code != 0 {
        panic(err.message)
    }
}
