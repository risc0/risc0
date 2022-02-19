PARALLEL_KERNEL(                                //
    shaRows,                                    //
    (PTR(ShaDigest, out),                       //
     CPTR(Fp, matrix),                          //
     CALC(count, out.size()),                   //
     CALC(colSize, matrix.size() / out.size()), //
     REQ(matrix.size() == colSize * count)),
    { out[idx] = shaHash(matrix + idx, colSize, count, false); })

PARALLEL_KERNEL(              //
    shaFold,                  //
    (PTR(ShaDigest, out),     //
     CPTR(ShaDigest, in),     //
     CALC(count, out.size()), //
     REQ(in.size() == 2 * out.size())),
    { out[idx] = shaHashPair(in[2 * idx], in[2 * idx + 1]); })

PARALLEL_KERNEL(                                //
    getRow,                                     //
    (PTR(Fp, out),                              //
     CPTR(Fp, matrix),                          //
     SIZE(offset),                              //
     CALC(count, out.size()),                   //
     CALC(rowSize, matrix.size() / out.size()), //
     REQ(offset < rowSize),                     //
     REQ(matrix.size() == rowSize * count)),
    { out[idx] = matrix[offset + idx * rowSize]; })
