pragma circom 2.0.4;

// Decompose the signal in into an array of bits of length N.
// out[0] will be the least-significant bit, out[N-1] the most.
template to_bits_exact(N) {
  signal input in;
  signal output out[N];
  var cur = in;
  for (var i = 0; i < N; i++) {
    out[i] <-- cur & 1;
    out[i] * (1 - out[i]) === 0;
    cur = (cur - out[i]) / 2;
  }
  cur === 0;
}

// Verify a bit-decomposed baby bear is valid
// PRECONDITION: in must be constrained as bits.
template valid_baby_bear() {
  signal input in[31];
  // If high_bits == 15, low_bits must == 0
  // Compute the sum of the high bits (0-4)
  // and the sum of the low bits
  var high_bits = 0;
  var low_bits = 0;
  for (var i = 0; i < 27; i++) {
    low_bits = low_bits + in[i];
  }
  for (var i = 27; i < 31; i++) {
    high_bits = high_bits + in[i];
  }

  // high_bits_sub4 will be 0 iff high_bits == 4.
  // If high_bits_sub4 is zero, then high_bits_eq4 must be 1.
  // If high_bits_sub4 is non-zero, then high_bits_eq4 may be 0.
  // (If the prover is not faulty, high_bits_eq4 will be 0)
  var high_bits_sub4 = high_bits - 4;
  signal sub4_inv <-- high_bits_sub4 == 0 ? 0 : -1/high_bits_sub4;
  signal high_bits_eq4 <== high_bits_sub4 * sub4_inv + 1;

  // valid baby bear elem if high_bits != 4 OR low_bits == 0.
  high_bits_eq4 * low_bits === 0;
}

// Normalize a Baby Bear field element to be less than P.
// signal in is an element with value at most N bits in size.
// signal out is the normalized representative field element.
// PRECONDITION: N <= 252; such that 2^(N-30) * baby_bear + baby_bear-1 < bn254_r
template normalize_impl(N) {
  signal input in;
  signal output out;
  // P is the Baby Bear prime.
  var P = 15 * (1 << 27) + 1;
  var K = N - 30;

  // Constrain the quotient to K bits and remainder to 31 bits.
  component k_bits = to_bits_exact(K);
  component out_bits = to_bits_exact(31);
  k_bits.in <-- in \ P;
  out_bits.in <-- in % P;

  // Constrain the bit decomposed remainder to be less than P.
  component vbb = valid_baby_bear();
  vbb.in <== out_bits.out;

  // Constrain the quotient and remainder to have been computed correctly.
  // Solution is unique because (quotient * P) <= 2^(N + 1) < GLOBAL_FIELD_P - P and remainder < P.
  k_bits.in * P + out_bits.in === in;

  // Final output
  out <== out_bits.in;
}

// From poseidon_params_n254_t3_alpha8_M128.txt
function ROUND_CONSTANTS() {
  return [
    0x0d04d54605fc012e6c6330aaa2628317b1386912b37ebef8b89d18f844222b41,
    0x28e06fb8fd15cd8f64ef366a1d3c1907817991ff2250373c5e1a8b67f2104258,
    0x1f54a0b10baf3d108c05afdb07c1404ecd931ec3c8a2c33f50b0653c127f66a6,
    0x11957f8d6773b764c6bb91899ef402613462f3cde78f7d158f252bddd2e0d82f,
    0x09823bd5607e30505c1f9384f49671b7039e287d53208fedf1378b7bf4c08f63,
    0x0936afcad7cfbfd539be0d1ff07280bc4ed7ba0cd6cd19fe6fa8c5d97a8b0fda,
    0x27aecc10c41fb5a131a0729fb54d3fbf6387530c57374aa66801b8d1a22bc7c9,
    0x2e1f2349f20b4e20fb72c12d320116ecfc9ec59fb98cbeb434bceeaad5b923ab,
    0x100e6127c4ef096018df6b5012c1154c2721b9cbb38c8c0881db8c98d11e8b4f,
    0x1b41f6061675d4c0691a7d0412e036e36daf2c1a900682d8f268cbf1f6c69e20,
    0x081380dabd9b760f4227f7c8d2405aa75947f19afb05b202c8808c5e28d1538e,
    0x04be1c3a4f5cb73aff2b3bd49aff6b12b5291a20e438227c85cb7acc866878d3,
    0x166032efff10cd76558ade77237be4e0de528e72df704cd97554071a059892dc,
    0x1987eb836197e22d8558a817fc12f158b04696ea981ec6721a3f0f58ee0c3bae,
    0x2a66f089ac2faa7a957caf7e5baf6b5348cde252053e6b954b2f4bb005f6c667,
    0x1433f00e6a11e36a148e02934b382f0af00135f6bb7b0009260ab1bce94a43e6,
    0x2c9a0a4b1a0e1f5aa0adaa5a4a57698d79ff9e0ca7b4d959a634548dc8b68628,
    0x15f84666f82f05eea3fa243db58233652dc435eb275738fea027fa7054d44d22,
    0x2b824ca4d5a2cafc80537cfa2b6042542c93264d51aaac8b18c1258f02831dd0,
    0x1abfbecb5540dfe5be8109290617b83313305096af5f2e099ceede07e09e8c28,
    0x2c7d47f30cc465dcd0fb61b51071cf4dcf98805490a2a64c1d3ab6ce966ca398,
    0x26c6dd50ffcb20a4ffe69e800c04ba188863a5b1ab5b3818f381578fe1499f8c,
    0x07fc227b5a453dc21ecc8632ccfbd72548a559a53529e66d22c70dc2876e8205,
    0x0a360843aeaac2322d5b3e8b0f474717db0fbf7824e04bd1ebe15f745a5bd2ab,
    0x1f5462bbd8f4fdf9fb12973b22956d9e5e9cd586abb30f9db1dab589ab31bd02,
    0x075d479b3cdc65a0081b6dfacb01d4f5492fff97814bd145fa1bb89d2de16ce4,
    0x20cbd45bffbaafd86fdcd26ae86ae8618ca352065f464aa73e89cd6f773ae9ea,
    0x25de3f0853759fddf1ccc0f2c91ef53f77e4da613e37e58a04b8881c4d1ae8cb,
    0x2e35c11021c589cc01dca344a1bcafa4fcd7272d9622c857b73e5bae696e1cd2,
    0x22c560510c4b993e8aa3ed2ee6eff9c9a212b28424cc7cf6bb41b76eb9af1db4,
    0x0cfaeb71bf3bef69f681fdc6ca0987ad7035ac907943ffb6c9d7da7734e16ef4,
    0x1b08ea6f918648bbbe4fced5824b13ea03ec34b9ae5d0ae2673b2d8740f37cca,
    0x0340f70b164187706e04fa5fe7b477025afe0fb3801905c349b537685a1f4d53,
    0x303291e436665735926b9ee3188741e762aebd8fae3c122b28234d08c7753707,
    0x09c9f490c3e3793b30ec60f687ef24248081447c1d380b98ca1c0660b40c45d6,
    0x16e229a1ed00e808f297464fa4b64b90f7670f1e82d6628451792ba43c778da1,
    0x1644ff9e2d72c6b2433c542e08b7f47bedd86ac9286a5c76779ac52f497a832a,
    0x0a67bbfbc1d318254950eabf3a052dd8f7ea4c2f0b8490ee81ed03712c76b4e0,
    0x0d5a79dadaf4333e1f8c33414f84b9b4f8f796ddd4364e89a9f483c6e3fa53ad,
    0x08890a6444b2a8db2677a5fc48d962291818e87ff39079bbb4ca55e32cc12d0d,
    0x2a77241498cc2b433f3063b1acd29458c9d0e76a3302985ca8885e68342e743d,
    0x10f3f55b3ddefd2b5ad33c4597cba79e7cacabb02dfefdee212fc03b90f260ae,
    0x1de35fdaac5978f983744a6ebd4f2922ec4cd2abc4e64fb9b985e8014a93dca0,
    0x1c00dd9cf36381832aedfaf8cb7d246227b7961bc939805a938401ae5b49b930,
    0x053bce588be1f3a9cfc29bc8592866b366a3b73535d8f1b080346545addc62e2,
    0x24cb21f8a872e380b8e61d4536b6eaf5dec54c9983e9a41f529cf83bd4b70c5b,
    0x15b24ece7a4bc656c7a0ff5234b78bd7ff0ac67011b626014c7bab1c6cfa73fe,
    0x2bef0aa05a002741b38709ce695a78630e1b80d56ff3d969342e512261bf5012,
    0x023d95da671925165dc643c2e830cd9a3a2aebe146970b77ba155a9bf6ef3c92,
    0x12e9fee2a16453e18afe1e32a46c934f20bb08745e91d490320e27fc621cd894,
    0x1bb9c5e0bb9720138cf63ff8a016f56dd3e7dd09133703d14567d8d020803c8c,
    0x15b9e54fe9a45e58fc56f2ca036d475d773c54fce97ac51e18adfee1ddb174bd,
    0x130cd6416c0de48279ebfaaebae6d177952c38267b6bf13f09abc6afdbae8ec5,
    0x02c2377ee7ce97c1b88662d698efc27d30487b700d2f4aaadb850b0fc448c0cf,
    0x1ecc9a1c5042ddc2c82a59f6e7e8cfb42b73268b36f3229a8c2cb5b2da417e25,
    0x215137edb3d95b16fb22cd048e3bbe040dbeebfa7e29f187430615e9802d1c8a,
    0x140ed20b218105dab70d8707ab1651ecc2dfdc173b9429bc7f9f45d3c0582ee5,
    0x20eb28fcee792f5cf75c24d56ddef72d8aedb9eb45786f714930179491dc935b,
    0x1e0170e1be70ae2a000ecc6e1e4eb67c1ec6228440963fa771efddcc90301ab1,
    0x0ffad7d0c308bc8dfff33a7bdfb8d86a274c46c31b4b135450bebf95990b6555,
    0x1fa070c1201f198c4e89e02c6d04faa7fad1ea289a235edf64f87c7742fc84d6,
    0x032467decae7755b66ea7f2bf91b4556c84d16f5b3468643908ac61ce3a7e4a8,
    0x0ca9bf5146906e02dd90c7e61f70ffd97080903108ff71c5d190b7fd1268d230,
    0x196fcdca9abde3cfaf67ebc6d43920d04ed062a90cc51c63925b06dfba8da9e8,
    0x18660dbc52858f4411d93a71f15e0c9b0483fdbb25950ad184d27791d3aa72c2,
    0x04b1aa9c8ac028770bbec9098965a79edf41b9180544e4a3f9f2209af82240c8,
    0x1539bf7dc106fc1d97c9f99184b068f95bb98df43fbba66ed20f659c4148242d,
    0x0878d6da90bf8c0def2a1ba0a8ce9bca3fe016f0c1222e25d677965f97c79d0c,
    0x250610a6fd6f7a4431f0dacd19e64c7c9b48a4880e202857628d3402d5008d09,
    0x01045a745b6923df0e4829a56c9c46c0408d2a5b9641aae3174a98428b47f654,
    0x2a7399c4d4cb725c250a6a524c6d3dba2039864b56c44e96677dc5a11b4bf003,
    0x21ca172b985aa1e7b60ccf63aac7a0603c16739b3baa40756f8a1347f0a1788f,
    0x1b7b85eead92e2494544939622d11e596d145bbd601d22f9210397bc215eb631,
    0x283806f539264f098bc323ba6d6d807c9e7157c912d9807fd97367ed3854afe7,
    0x04f970949efda9b8a226883898f5b3ad644c0bd09d5c21d19d96644b4f8574e8,
    0x2e4f6bbf57b43a75cd553f186c4d10984146390d6253a73eb55bf9a13a07dd16,
    0x251dc5df46ee0a89ffae6aed614dc56865e7743894501549071f17e3261a4bde,
    0x29dfaba0b6d76889ecf32fc99646fbb4b72afa19f520c3192fbbffc1d60e2cdf,
    0x011b5f15a590611f3615a12faf21aa7bcef16320060e220785cf0a28afaf3779,
    0x0243427d7935263a37c7656268db223f53e8dbe27585ab78c0d161b0f80be1c1,
    0x2265329cb3caffaf4f3b64033f63af0da1251756961cbaf1ff7d87e783d06cbb,
    0x1e5fdc14cfce488885427c8049938f6f5d73ab9b7d6749f0cd39c41f09e49fd4,
    0x0e52fbec4e516e5b1a6ca4b4a4fd8df9d4da1a44b3b3f5921ad5f58dd6d905d3,
    0x18236a644fac2f9f621afd13cf534fd7996d490cc41acb097a1224d260480135,
    0x16d2681f38fce7e23e14e8afd39136c58c2657f81bc2111ab43a6820afdcfd33,
    0x2b669dfe17709cee7293c0e0546ef6861a5f6f4ba816be56b1a86952a849a33b,
    0x3033268bdd97a4cd4d024901f896b4cf7bcc79087b3f414c7212d9802c1cb01c,
    0x06d5fc4e498eb14fcf0273825bf9f5ee1f4f3445882f715cbccbec56e730d523,
    0x1407dee75f102ba166a64b5b44752c96c05150d32d396d6bf54eb3b021dce237,
    0x26acc53aabdf50ab7c7ec3a7e95f22ed4bff6f0c16d3a680f619163bbf16a3d0,
    0x30145b98931c6948b07750df79060549278c8f67f30d51d68093cb87412650d4,
    0x0e6207abd203f6b5301b8d25204d26f75290e9277b47584658c3017c67014e39,
    0x09a08257e0b96040aacef7883f67d9b1b09dadc1067ea42659839932cb75cc9d,
    0x0b3012e462e3ac220058e13f6587d8271428d687245505df891b5a1a01eeda4a,
    0x23409334ed7ea7c4a2826142dd19e3eb6416177570fc919dc8eda6936156f099,
    0x18e7af7c4e1f71fd5bba331bc33adac3bf97795535249e14263e3db91ebcd0ce,
    0x1e125d67314df0314bc6111744a8914a5dfb2e0b794624e4efeabfc34c6f125a,
    0x28c4fffe9e33a15b53d3159c3cff388ae0870b1bfa4ea8f0e2260b401419e5d0,
    0x23cb1037e01c3c97a488f9272d138af148e6328c838ac2c54932b997eed9a62a,
    0x255b948cb4abb3c3a2fba30295dd5ae1a8216c15c2c01d461207bfdd57f44bbb,
    0x2d53e896989f78b2c784e142a7359cc0c1e3fb7f66d3f9ab8be5a2ca226820bc,
    0x07bb487020c3c502ba442ddab39639e60ee89ef4754de256d68b457ffe39088c,
    0x1d054eeee076f732fbfc2cad75ca6581a04bcd82c3c8bd55b6002bf5550d0134,
    0x02c4c1ac2299ef8d09c600f9681282ff6259b8676954cf4b7c50b1ff493d71ba,
    0x2e50469df84cc7ac05354fe508787b4b2b7266e690e8dbaa43d16cc27eff0d32,
    0x1af0f9598040cb4c0ab854e1a2e08d5d8d77722633c1de04dfe5cc448988dcf7,
    0x25571b94d190a4cee35e2e31f7a25890f86def094f5adf6f283cdbb05fc98841,
    0x07914effc1174a2c8f291614118f1464fc0effd5138feb3bbd6d61be7cf8f30b,
    0x07eb3bd301624061b1cff6bb8f7b8382d5ddc486f9d64efeb587a4ad26b9546f,
    0x17fefceec2752f7491d7878a238735d3129d371caee4abed76c023604c764448,
    0x057e4d432e867b9b78ad6ed203f482731f1a34c271a57de6c6d425f8b4d552bf,
    0x0c9c309c05354b351bb9f8e40cd7eed1c5f34d3abe3985451ca2e0b0f26d691b,
    0x1207a8a1dad92770af3ae27972a138cfd43626268b69e76e32c7efae9eb716c2,
    0x1071c457551a63459087575f79d404ec36b0940f9783e574e92107fde282269b,
    0x168bb33890d11d3fc16c11cb99c430a5f844aa9e4c35c6f8a5dd6a77bc6a5866,
    0x1dddd521377ebaba54c2d0509bd5de54b7dcaab1857862821a5d231d50cd8feb,
    0x110889f705085f9b4a2e2be644c4713936e435f519d2cff126d5343444859faf,
    0x0be67c22f79a1521994275596278a3622d713841fb0b98bfa72268ca1b6fa3c4,
    0x24722abad33581b0e471c3cd23f23ce5de764ad4bf5d62c85b36f3499bfb51e3,
    0x189f529694f650bd59367b706e48464a6a385af48af83a4372bc91033b7b6214,
    0x0fa18e0eec60a50cf99647301390460c043e81b26ee724c3df14d8570a514677,
    0x072a304d3c7f148138bf0ff1b95243050b6e2deb107123882bd51c11e7ad2f50,
    0x13ce4d6a6892ead955423a5c32d5e8d6dca06df2efa426fb78f8698d9458a379,
    0x29104ffdc395bd32dc3ab64aa20de823f80a8952cea9ef641510a911cdf06941,
    0x2a5c60b9aa0e451d53a8d4f4995695439b93257a183a9535dc756eaf84ede0ff,
    0x2a3a296c56d45782fedb021f781105fe184c52a9adcced9462ac09cd0a3dbf97,
    0x1cb3f5501d8f08470a37fb583906905733e38c49475e98acb1314d0dbdbe0e0e,
    0x0f820c72947e398f1eb86e2b22bbf9eb81800eb62ecc6d1b9682933006293232,
    0x01b3ec57439c5bb6f200af372f1aa1702d11447b7018b319c6f0655a69f2f5f0,
    0x088c6027fa16497d6b5f52901b99333283126e8f1b16c560d3553cf72203e5fb,
    0x2891a81c51826effce9c8a465d6911adcd82d013bcc7be7209770d5655ad7261,
    0x00a1e975fbb45cdf33e98fb3aab21a25b56f4cf90f2fa457a8deac8108532789,
    0x214d94f556d303ba8f90245b657782d89b6b6894109f5428323e5a2e627b7314,
    0x05509c404f336bfaa01a144b57774ad075cab8fe0e19793c082998701bc52193,
    0x23c0396a5c338f7f916a801cf605d57a527c42e2700e4257cf6cf6b549feda2c,
    0x1595f0b8b9b574b93bb94e3b2175dca93000e7cbd909964010bb7a86e7cf5e68,
    0x008148acddd2ce5af10525335f37a0b2f9b5e48d3811509e27e71fc646c7eae4,
    0x30234b35cbc04717e4c1d9ec057e921b25ea3b588b0b243fe0ae8b34b3952614,
    0x0965f52f71a990e038495fcd6e22f9f732cbd9d00db63b2f1437ab21e20d1256,
    0x1c0be3599b0289bc14a8a37a03bcfe17ec1bf5862c5bdf12e18710b3b8a68787,
    0x08b71d61f14758b0beb6470fad6dbac8dfe36387e26efcea149860792cdb30f8,
    0x1dbee0b56078243444e82a1369df8a2d74f019de62ca4e9adbce2fae4f18c4fd,
    0x2837caf1ea7138be801a581afd91bdd8fa639d51d3247b3f387127a9fc40c8bd,
    0x157c7be59f7f227a927c8d8def42a91d548332ad3cb659c8b2ec03ff426ead7c,
    0x22ccaab05b081978e6340d1cb1102cf6842a3b84f56dc667649a18dcabb4990b,
    0x1045728e6c02ab8d0f09eb575fcfb5c3d3f6dbf898297132e96b9fecec1b93f1,
    0x071d8f20cb2b91dd350fdfc45642d55fd8bab5832dac7d953429b83a9e521449,
    0x2c00c7757ff9ed99a448d7143064d476ed358b0e4e30aeb98ec280c22942fabc,
    0x1bf0373aaa017f5858da7367a5d2839ab4ac05baf9c4cf36a704ba30bedbcd74,
    0x2021dd73ceecdfc37642c714504a99f7357eae6c13d290532c4137d33d923ec4
  ];
}

function MDS() {
  return [[
      0x023f9d67429aa39fdb4725691ed4dbeab87db25641d144cb05123e1c8eef69fa,
      0x094aa38324aa8c2dde9ad5a02adae96211691d2b9830fbeef0b6493bbc578021,
      0x0813757ae01a100b5b5b5487db9d3a439f0b96c4fceadc47ba8f783ede009cb4
    ], [
      0x0ffe281554a17e4c19a6dd677ed03db72b75bfef9ed964fd567d5d48084a730d,
      0x0ae2a0d853671d61bbb8b0b3c4c5a10073bbe445a1343bb079854ea850f9ec12,
      0x0bfc8075aba465d09c5a1705bc178f6e7af4c33769cd1ee11b5c117ecc3a6240
    ], [
      0x177eb4e491168706dc7ee548a5eae72958a0731a4c2fa1309c9b7c9c1e93ea3c,
      0x0b700d0937fed3aa2cfe7895d3a04e284f6fe8fd75d4aff42ec03d29395ae470,
      0x072af6ea9ffa0a472fbf40f13f03fcfa2a6ab9f16f02c301f722079f66f2406a
    ]
  ];
}

template sbox() {
  signal input in;
  signal output out;
  signal x2, x4;
  x2 <== in * in;
  x4 <== x2 * x2;
  out <== x4 * x4;
}

template full_round(round_num) {
  signal input in[3];
  signal output out[3];
  var rc[150] = ROUND_CONSTANTS();
  var mds[3][3] = MDS();
  component sboxes[3];
  for (var i = 0; i < 3; i++) {
    sboxes[i] = sbox();
    sboxes[i].in <== in[i] + rc[round_num * 3 + i];
  }

  for (var i = 0; i < 3; i++) {
    var tot = 0;
    for (var j = 0; j < 3; j++) {
      tot = tot + mds[i][j] * sboxes[j].out;
    }
    out[i] <== tot;
  }
}

template partial_round(round_num) {
  signal input in[3];
  signal output out[3];
  signal pre_mds[3];
  var rc[150] = ROUND_CONSTANTS();
  var mds[3][3] = MDS();
  component sb = sbox();
  sb.in <== in[0] + rc[round_num * 3];
  pre_mds[0] <== sb.out;
  pre_mds[1] <== in[1] + rc[round_num * 3 + 1];
  pre_mds[2] <== in[2] + rc[round_num * 3 + 2];
  for (var i = 0; i < 3; i++) {
    var tot = 0;
    for (var j = 0; j < 3; j++) {
      tot = tot + mds[i][j] * pre_mds[j];
    }
    out[i] <== tot;
  }
}

template poseidon() {
  signal input in[3];
  signal output out[3];

  component init[4];
  component mid[42];
  component fini[4];
  init[0] = full_round(0);
  init[0].in <== in;
  for (var i =  1; i < 4; i++) {
    init[i] = full_round(i);
    init[i].in <== init[i-1].out;
  }
  mid[0] = partial_round(4);
  mid[0].in <== init[3].out;
  for (var i =  1; i < 42; i++) {
    mid[i] = partial_round(4 + i);
    mid[i].in <== mid[i-1].out;
  }
  fini[0] = full_round(46);
  fini[0].in <== mid[41].out;
  for (var i =  1; i < 4; i++) {
    fini[i] = full_round(46 + i);
    fini[i].in <== fini[i-1].out;
  }
  out <== fini[3].out;
}

template hash_impl(nInputs) {
  signal input in[nInputs];
  signal output out;
  var P = 15 * (1 << 27) + 1;
  var blocks = (nInputs + 15) \ 16;
  component permute[blocks];
  for (var b = 0; b < blocks; b++) {
    permute[b] = poseidon();
    if (b == 0) {
      permute[b].in[0] <== 0;
    } else {
      permute[b].in[0] <== permute[b-1].out[0];
    }
    for (var n = 0; n < 2; n++) {
      var tot = 0;
      var mul = 1;
      for (var i = 0; i < 8; i++) {
        var idx = b * 16 + n * 8 + i;
        if (idx < nInputs) {
          tot = tot + mul * in[idx];
        }
        mul = mul * P;
      }
      permute[b].in[1 + n] <== tot;
    }
  }
  out <== permute[blocks - 1].out[0];
}

template hash_fold_impl(nInputs) {
  signal input in[nInputs];
  signal output out;
  component p = poseidon();
  p.in[0] <== 0;
  p.in[1] <== in[0];
  p.in[2] <== in[1];
  out <== p.out[0];
}

template bit_and_impl(nInputs) {
  signal input in[2];
  signal output out;
  component bits_a = to_bits_exact(31);
  component vbb_a = valid_baby_bear();
  component bits_b = to_bits_exact(31);
  component vbb_b = valid_baby_bear();
  bits_a.in <== in[0];
  bits_b.in <== in[1];
  vbb_a.in <== bits_a.out;
  vbb_b.in <== bits_b.out;
  signal out_bits[31];
  for (var i = 0; i < 31; i++) {
    out_bits[i] <== bits_a.out[i] * bits_b.out[i];
  }
  var outVal = 0;
  for (var i = 0; i < 31; i++) {
    outVal = outVal + (1 << i) * out_bits[i];
  }
  out <== outVal;
}

function inverse(a, n) {
  var mul = a;
  var prod = 1;
  var x = n - 2;
  while (x != 0) {
    if (x % 2 == 1) {
      x = x - 1;
      prod *= mul;
      prod %= n;
    }
    mul *= mul;
    mul %= n;
    x = x / 2;
  }
  return prod;
}

template inv_impl(nInputs) {
  signal input in[1];
  signal output out;
  var P = 15 * (1 << 27) + 1;
  var inv_res = inverse(in[0], P);
  out <-- inv_res;
  component bits_k = to_bits_exact(31);
  bits_k.in <-- out * in[0] \ P;
  component bits = to_bits_exact(31);
  component vbb = valid_baby_bear();
  bits.in <== out;
  vbb.in <== bits.out;
  out * in[0] - 1 === bits_k.in * P;
}

template select_impl(nInputs) {
  signal input elems[nInputs];
  signal input idx;
  signal output out;
  signal one_hot[nInputs];
  signal mults[nInputs];
  var idx2 = 0;
  var count = 0;
  var tot = 0;
  for (var i = 0; i < nInputs; i++) {
    one_hot[i] <-- (idx == i ? 1 : 0);
    one_hot[i] * (1 - one_hot[i]) === 0;
    idx2 = idx2 + i * one_hot[i];
    count = count + one_hot[i];
    mults[i] <== one_hot[i] * elems[i];
    tot = tot + mults[i];
  }
  count === 1;
  idx2 === idx;
  out <== tot;
}

template iop_init_impl() {
  signal output iop[3];
  iop[0] <== 0;
  iop[1] <== 0;
  iop[2] <== 0;
}

template iop_commit_impl() {
  signal input old_iop[3];
  signal input digest;
  signal output new_iop[3];
  component permute = poseidon();
  permute.in[0] <== old_iop[0];
  permute.in[1] <== old_iop[1] + digest;
  permute.in[2] <== old_iop[2];
  new_iop <== permute.out;
}


template valid_254() {
  signal input in[254];
  signal cur[255];
  var bits_P[254] = [
     1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0,
     1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
     0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1,
     0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1,
     0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0,
     0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0,
     0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1,
     0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  ];
  cur[0] <== 1;
  for (var i = 0; i < 254; i++) {
    if (bits_P[i] == 0) {
      // Either we are already OK, or we must not be 1
      cur[i] * in[253 - i] === 0;
      cur[i + 1] <== cur[i];
    } else {
      // Set cur to zero if we are == 0
      cur[i + 1] <== cur[i] * in[253 - i];
    }
  }
}

template iop_rng_val_impl() {
  signal input old_iop[3];
  signal output new_iop[3];
  signal output rng_out;
  component permute = poseidon();
  component bits = to_bits_exact(254);
  component valid = valid_254();
  bits.in <== old_iop[2];
  valid.in <== bits.out;
  permute.in <== old_iop;
  new_iop <== permute.out;
  var tot = 0;
  for (var i = 0; i < 160; i++) {
    tot = tot + (1 << i) * bits.out[i];
  }
  component norm = normalize_impl(160);
  norm.in <== tot;
  rng_out <== norm.out;
}

template iop_rng_bits_impl(numBits) {
  signal input old_iop[3];
  signal output new_iop[3];
  signal output rng_out;
  component permute = poseidon();
  component bits = to_bits_exact(254);
  component valid = valid_254();
  bits.in <== old_iop[2];
  valid.in <== bits.out;
  permute.in <== old_iop;
  new_iop <== permute.out;
  var tot = 0;
  for (var i = 0; i < numBits; i++) {
    tot = tot + (1 << i) * bits.out[i];
  }
  rng_out <== tot;
}

