#include "protocol.h"

#include "risc0/core/log.h"
#include "risc0/zkp/core/sha256_cpu.h"
#include "risc0/zkp/prove/proof.h"
#include "risc0/zkp/verify/verify.h"

using risc0::hex;

const InitMessage::Parts& InitMessage::getParts() const {
  if (proof.message.size() != sizeof(InitMessage::Parts)) {
    throw std::runtime_error("InitMessage parts size mismatch");
  }
  const InitMessage::Parts* parts =
      reinterpret_cast<const InitMessage::Parts*>(proof.message.data());
  return *parts;
}

const RoundMessage::Parts& RoundMessage::getParts() const {
  if (proof.message.size() != sizeof(RoundMessage::Parts)) {
    throw std::runtime_error("RoundMessage parts size mismatch");
  }
  const RoundMessage::Parts* parts =
      reinterpret_cast<const RoundMessage::Parts*>(proof.message.data());
  return *parts;
}

InitMessage Battleship::init() {
  risc0::Prover prover("examples/cpp/battleship/init_proof");
  prover.addInput(state);
  risc0::Proof proof = prover.run();
  LOG(1, name << "> InitProof: " << proof.core.size());
  LOG(1, name << "> InitProof outputs: " << prover.getNumOutputs());
  return InitMessage{proof};
}

void Battleship::onInitMsg(const InitMessage& msg) {
  LOG(1, name << "> onInitMsg");
  msg.proof.verify();
  peer_state = msg.getParts().state;
  LOG(1, name << "> peer_state: " << peer_state);
}

TurnMessage Battleship::turn(const Position& shot) {
  LOG(1, name << "> turn: " << shot);
  last_shot = shot;
  return TurnMessage{shot};
}

RoundMessage Battleship::onTurnMsg(const TurnMessage& msg) {
  LOG(1, name << "> onTurnMsg");
  RoundParams params{state, msg.shot};
  risc0::Prover prover("examples/cpp/battleship/round_proof");
  prover.addInput(params);
  risc0::Proof proof = prover.run();
  LOG(1, name << "> RoundProof: " << proof.core.size());
  LOG(1, name << "> RoundProof outputs: " << prover.getNumOutputs());
  const RoundResult& round = prover.getOutput<RoundResult>(0);
  LOG(1, name << "> RoundResult: " << round);
  state = round.state;
  return RoundMessage{proof};
}

void Battleship::onRoundMsg(const RoundMessage& msg) {
  LOG(1, name << "> onRoundMsg");

  msg.proof.verify();
  const RoundMessage::Parts& parts = msg.getParts();

  if (parts.old_state != peer_state) {
    throw new std::runtime_error("Cheater: state mismatch");
  }

  if (parts.shot != last_shot) {
    throw new std::runtime_error("Cheater: shot mismatch");
  }

  LOG(0, name << "> shot: " << parts.shot << " -> hit: " << parts.hit);

  peer_state = parts.new_state;
}
