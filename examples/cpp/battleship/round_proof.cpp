#include "risc0/r0vm/cpp/device/risc0.h"

#include "battleship.h"

using namespace risc0;

extern "C" void risc0_main(Env* env) {
  const RoundParams& params = env->read<RoundParams>();
  RoundResult result = process_round(params);
  env->write(result);
  env->commit(shaDigest(params.state));
  env->commit(shaDigest(result.state));
  env->commit(params.shot);
  env->commit(result.hit);
}
