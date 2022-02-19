PARALLEL_KERNEL(       //
    mixPolyCoeffs,     //
    (PTR(Fp4, out),    //
     CPTR(Fp, code),   //
     CPTR(Fp, data),   //
     CPTR(Fp, accum),  //
     CPTR(Fp, check),  //
     CPTR(Fp, global), //
     SIZE(count)),     //
    { mixPoly(out, code, data, accum, check, global, idx, count); });
