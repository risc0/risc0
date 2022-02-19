PARALLEL_KERNEL(                 //
    evalCheckPoly,               //
    (PTR(Fp, out),               //
     CPTR(Fp, code),             //
     CPTR(Fp, data),             //
     CPTR(Fp, accum),            //
     CPTR(Fp, global),           //
     CPTR(Fp, rou),              //
     SIZE(count),                //
     CALC(po2, log2Ceil(count)), //
     REQ(1 << po2 == count)),
    {
      Fp4 ret = computePoly(code, data, accum, global, idx, count);
      Fp x = pow(rou[po2], idx);
      ret = ret * inv(pow(Fp(3) * x, (1 << (po2 - 2))) - 1);
      out[0 * count + idx] = ret.elems[0];
      out[1 * count + idx] = ret.elems[1];
      out[2 * count + idx] = ret.elems[2];
      out[3 * count + idx] = ret.elems[3];
    });
