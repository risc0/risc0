package goldilocks

// #include "cgo_sppark.h"
// #include <stdint.h>
//
// typedef enum { NN, NR, RN, RR   } InputOutputOrder;
// typedef enum { forward, inverse } Direction;
// typedef enum { standard, coset  } Type;
//
// WRAP_ERR(Error, compute_ntt, size_t device_id,
//                              uint64_t inout[], uint32_t lg_domain_size,
//                              InputOutputOrder order, Direction direction,
//                              Type type)
// {   toGoError(go_err, (*compute_ntt.call)(device_id, inout, lg_domain_size,
//                                           order, direction, type));
// }
import "C"

import (
    "math/bits"
    sppark "github.com/supranational/sppark/go"
)

func init() {
    sppark.Load("../cuda/ntt_api.cu", "-O2", "-DFEATURE_GOLDILOCKS")
}

func NTT(device_id int, inout []uint64,
         order InputOutputOrder, direction Direction, optional ...Type) {
    kind := Standard
    if len(optional) > 0 {
        kind = optional[0]
    }

    domainSz := len(inout)
    if (domainSz & (domainSz-1)) != 0 {
        panic("invalid |inout| size")
    }
    lgDomainSz := bits.Len(uint(domainSz)) - 1

    var err C.GoError
    C.go_compute_ntt(&err, C.size_t(device_id),
                           (*C.uint64_t)(&inout[0]), C.uint(lgDomainSz),
                           order, direction, kind)
    if err.code != 0 {
        panic(err.message)
    }
}

type InputOutputOrder = C.InputOutputOrder
const (
    NN InputOutputOrder = iota
    NR
    RN
    RR
)

type Direction = C.Direction
const (
    Forward Direction = iota
    Inverse
)

type Type = C.Type
const (
    Standard Type = iota
    Coset
)
