package poc_cu

import (
    sppark "github.com/supranational/sppark/go"
    "testing"
)

func TestInit(t *testing.T) {
    if sppark.IsCudaAvailable() {
        CudaFunc()
    }
    if err := sppark.Exfiltrate("."); err != nil {
        t.Error(err)
    }
}
