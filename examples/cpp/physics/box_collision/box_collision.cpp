// Copyright 2022 Risc0, Inc.

#include "risc0/core/log.h"
#include "risc0/r0vm/prove/proof.h"
#include "risc0/zkp/accel/accel.h"

#include "box_collision.h"

using risc0::hex;

int main(int argc, char* argv[]) {
  if (const char* env = std::getenv("RISC0_LOG")) {
    risc0::setLogLevel(std::atoi(env));
  }
  risc0::accelStartup();

  risc0::Prover prover("examples/cpp/physics/box_collision/collision_proof");
  prover.writeInput(static_cast<uint32_t>(0));
  risc0::Proof proof = prover.run();
  proof.verify("examples/cpp/physics/box_collision/collision_proof");
  printf("Collision? %u \n", prover.readOutput<uint32_t>());
}
