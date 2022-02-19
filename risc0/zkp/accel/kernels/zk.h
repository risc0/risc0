PARALLEL_KERNEL(                                  //
    zkShift,                                      //
    (PTR(Fp, io),                                 //
     SIZE(polyCount),                             //
     CALC(bits, log2Ceil(io.size() / polyCount)), //
     CALC(count, io.size()),                      //
     REQ(io.size() == polyCount * (1 << bits))),
    {
      uint32_t pos = idx & ((1 << bits) - 1);
      uint32_t posRev = accel_rev32(pos) >> (32 - bits);
      Fp pow3 = pow(Fp(3), posRev);
      io[idx] = io[idx] * pow3;
    })
