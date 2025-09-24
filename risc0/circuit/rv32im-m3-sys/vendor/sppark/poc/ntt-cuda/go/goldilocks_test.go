package goldilocks

import (
    sppark "github.com/supranational/sppark/go"
    "crypto/rand"
    "math/big"
    "reflect"
    "testing"
)

func TestSelfConsistency(t *testing.T) {
    var mod big.Int
    mod.SetUint64(0xffffffff00000001)

    ref := make([]uint64, 1<<20)
    for i := range ref {
        if rnd, err := rand.Int(rand.Reader, &mod); err == nil {
            ref[i] = rnd.Uint64()
        }
    }

    work := append([]uint64{}, ref...)

    NTT(0, work, NR, Forward)
    NTT(0, work, RN, Inverse)

    if !reflect.DeepEqual(ref, work) {
        t.Errorf("result mismatch")
    } else if err := sppark.Exfiltrate("."); err != nil {
        t.Error(err)
    }
}
