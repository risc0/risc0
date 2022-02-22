use std::{mem, slice};

use battleship_proof::{GameState, HitType, Position, RoundParams, RoundResult};
use risc0_host::{Digest, Exception, Proof, Prover, Result};

pub struct InitMessage {
    proof: Proof,
}

pub struct TurnMessage {
    shot: Position,
}

pub struct RoundMessage {
    proof: Proof,
}

#[derive(Debug)]
pub struct RoundParts {
    old_state: Digest,
    new_state: Digest,
    shot: Position,
    hit: HitType,
}

pub struct Battleship {
    state: GameState,
    last_shot: Position,
    peer_state: Digest,
}

impl InitMessage {
    pub fn get_state(&self) -> Result<Digest> {
        let msg = self.proof.get_message()?;
        Digest::try_from(msg)
    }
}

impl RoundMessage {
    pub fn get_parts(&self) -> Result<&RoundParts> {
        let msg = self.proof.get_message()?;
        let ptr: *const RoundParts = msg.as_ptr().cast();
        Ok(unsafe { &*ptr })
    }
}

impl Battleship {
    pub fn new(state: GameState) -> Self {
        Battleship {
            state,
            last_shot: Position::new(0, 0),
            peer_state: Digest::default(),
        }
    }

    pub fn init(&self) -> Result<InitMessage> {
        let mut prover = Prover::new("examples/rust/battleship/proof/init")?;
        let ptr: *const GameState = &self.state;
        let slice = unsafe { slice::from_raw_parts(ptr.cast(), mem::size_of::<GameState>()) };
        prover.add_input(slice)?;
        let proof = prover.run()?;
        Ok(InitMessage { proof })
    }

    pub fn on_init_msg(&mut self, msg: &InitMessage) -> Result<()> {
        msg.proof.verify("examples/rust/battleship/proof/init")?;
        self.peer_state = msg.get_state()?;
        Ok(())
    }

    pub fn turn(&mut self, x: u32, y: u32) -> TurnMessage {
        let shot = Position::new(x, y);
        self.last_shot = shot.clone();
        TurnMessage { shot: shot.clone() }
    }

    pub fn on_turn_msg(&mut self, msg: &TurnMessage) -> Result<RoundMessage> {
        let params = RoundParams::new(self.state.clone(), msg.shot.x, msg.shot.y);
        let mut prover = Prover::new("examples/rust/battleship/proof/turn")?;
        let ptr: *const RoundParams = &params;
        let slice = unsafe { slice::from_raw_parts(ptr.cast(), mem::size_of::<RoundParams>()) };
        prover.add_input(slice)?;
        let proof = prover.run()?;
        let slice = prover.get_output(0, mem::size_of::<RoundResult>())?;
        let ptr: *const RoundResult = slice.as_ptr().cast();
        let result = unsafe { &*ptr };
        self.state = result.state.clone();
        Ok(RoundMessage { proof })
    }

    pub fn on_round_msg(&mut self, msg: &RoundMessage) -> Result<HitType> {
        msg.proof.verify("examples/rust/battleship/proof/turn")?;
        let parts = msg.get_parts()?;

        if parts.old_state != self.peer_state {
            return Err(Exception::new(
                format!(
                    "Cheater: state mismatch. old_state ({}) != peer_state ({})",
                    parts.old_state, self.peer_state
                )
                .as_str(),
            ));
        }

        if parts.shot != self.last_shot {
            return Err(Exception::new(
                format!(
                    "Cheater: shot mismatch. cur_shot ({}) != last_shot ({})",
                    parts.shot, self.last_shot
                )
                .as_str(),
            ));
        }

        self.peer_state = parts.new_state.clone();

        Ok(parts.hit.clone())
    }
}

#[cfg(test)]
mod tests {
    use battleship_proof::{Ship, ShipDirection};

    use super::*;

    fn round(player1: &mut Battleship, player2: &mut Battleship, x: u32, y: u32) -> HitType {
        let turn = player1.turn(x, y);
        player1
            .on_round_msg(&player2.on_turn_msg(&turn).unwrap())
            .unwrap()
    }

    #[test]
    fn protocol() {
        // Player Alice
        //  | 0 1 2 3 4 5 6 7 8 9 |
        // 0|                     |
        // 1|       B B B B       |
        // 2|                     |
        // 3|     A               |
        // 4|     A               |
        // 5|     A         D D D |
        // 6|     A               |
        // 7|     A   C     E E   |
        // 8|         C           |
        // 9|         C           |
        let alice_state = GameState {
            ships: [
                Ship::new(2, 3, ShipDirection::Vertical),
                Ship::new(3, 1, ShipDirection::Horizontal),
                Ship::new(4, 7, ShipDirection::Vertical),
                Ship::new(7, 5, ShipDirection::Horizontal),
                Ship::new(7, 7, ShipDirection::Horizontal),
            ],
            salt: 0xDEADBEEF,
        };

        // Player Bob
        //  | 0 1 2 3 4 5 6 7 8 9 |
        // 0| B B B B           A |
        // 1| C                 A |
        // 2| C                 A |
        // 3| C                 A |
        // 4| D                 A |
        // 5| D                   |
        // 6| D                   |
        // 7| E                   |
        // 8| E                   |
        // 9|                     |
        let bob_state = GameState {
            ships: [
                Ship::new(9, 0, ShipDirection::Vertical),
                Ship::new(0, 0, ShipDirection::Horizontal),
                Ship::new(0, 1, ShipDirection::Vertical),
                Ship::new(0, 4, ShipDirection::Vertical),
                Ship::new(0, 7, ShipDirection::Vertical),
            ],
            salt: 0xCAFECAFE,
        };

        let mut alice = Battleship::new(alice_state);
        let mut bob = Battleship::new(bob_state);

        bob.on_init_msg(&alice.init().unwrap()).unwrap();
        alice.on_init_msg(&bob.init().unwrap()).unwrap();

        assert_eq!(round(&mut alice, &mut bob, 1, 1), HitType::Miss);
        assert_eq!(round(&mut bob, &mut alice, 3, 1), HitType::Hit);

        assert_eq!(round(&mut alice, &mut bob, 0, 0), HitType::Hit);
        assert_eq!(round(&mut bob, &mut alice, 4, 1), HitType::Hit);

        assert_eq!(round(&mut alice, &mut bob, 0, 1), HitType::Hit);
        assert_eq!(round(&mut bob, &mut alice, 5, 1), HitType::Hit);

        assert_eq!(round(&mut alice, &mut bob, 0, 2), HitType::Hit);
        assert_eq!(round(&mut bob, &mut alice, 6, 1), HitType::Sunk(1));
    }
}
