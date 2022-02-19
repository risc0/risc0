#include "risc0/r0vm/cpp/device/risc0.h"

#include "battleship.h"

using namespace risc0;

extern "C" void risc0_main(Env* env) {
  const GameState& state = env->read<GameState>();
  if (!check_board(state))
    fail("Invalid board state");
  env->commit(shaDigest(state));
}
