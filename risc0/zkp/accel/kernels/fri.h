PARALLEL_KERNEL(                        //
    friFold,                            //
    (PTR(Fp, out),                      //
     CPTR(Fp, in),                      //
     CPTR(Fp4, mixPtr),                 //
     CALC(count, out.size() / 4),       //
     REQ(out.size() == count * 4),      //
     REQ(in.size() == out.size() * 16), // 16 = kFriFold
     REQ(mixPtr.size() == 1)),
    {
      Fp4 mix = *mixPtr;
      Fp4 tot;
      Fp4 curMix(1);
      for (uint32_t i = 0; i < kFriFold; i++) {
        uint32_t rev_i = accel_rev32(i) >> (32 - 4); // 4 = log2Ceil(kFriFold))
        Fp4 val(in[0 * count * kFriFold + rev_i * count + idx],
                in[1 * count * kFriFold + rev_i * count + idx],
                in[2 * count * kFriFold + rev_i * count + idx],
                in[3 * count * kFriFold + rev_i * count + idx]);
        tot += curMix * val;
        curMix *= mix;
      }
      for (uint32_t i = 0; i < 4; i++) {
        out[count * i + idx] = tot.elems[i];
      }
    })
