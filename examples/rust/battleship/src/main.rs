// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use battleship_core::{GameState, HitType, Ship, ShipDirection};
use lib::Battleship;
use std::io::stdin;

struct Players {
    name: String,
    battleship: Battleship,
}

fn round(player1: &mut Battleship, player2: &mut Battleship, x: u32, y: u32) -> HitType {
    let turn = player1.turn(x, y);
    player1
        .on_round_msg(&player2.on_turn_msg(&turn).unwrap())
        .unwrap()
}

fn run_auto_bot() {
    println!("You selected 0 players, we'll play Alice vs Bob then...");
    println!("Alice sets carrier in (2,3) in Vertical.");
    println!("Alice sets battleship in (3,1) in Horizontal.");
    println!("Alice sets cruiser in (4,7) in Vertical.");
    println!("Alice sets submarine in (7,5) in Horizontal.");
    println!("Alice sets destroyer in (7,7) in Horizontal.");
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

    println!("Bob sets carrier in (9,0) in Vertical.");
    println!("Bob sets battleship in (0,0) in Horizontal.");
    println!("Bob sets cruiser in (0,1) in Vertical.");
    println!("Bob sets submarine in (0,4) in Vertical.");
    println!("Bob sets destroyer in (0,7) in Vertical.");
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

    println!("Alice attacks position (1,1).");
    let mut y = round(&mut alice, &mut bob, 1, 1);
    println!("It's a {:?}", y);

    println!("Bob attacks position (3,1).");
    y = round(&mut bob, &mut alice, 3, 1);
    println!("It's a {:?}", y);

    println!("Alice attacks position (0,0).");
    y = round(&mut alice, &mut bob, 0, 0);
    println!("It's a {:?}", y);

    println!("Bob attacks position (4,1).");
    y = round(&mut bob, &mut alice, 4, 1);
    println!("It's a {:?}", y);

    println!("Alice attacks position (0,1).");
    y = round(&mut alice, &mut bob, 0, 1);
    println!("It's a {:?}", y);

    println!("Bob attacks position (5,1).");
    y = round(&mut bob, &mut alice, 5, 1);
    println!("It's a {:?}", y);

    println!("Alice attacks position (0,2).");
    y = round(&mut alice, &mut bob, 0, 2);
    println!("It's a {:?}", y);

    println!("Bob attacks position (6,1).");
    y = round(&mut bob, &mut alice, 6, 1);
    println!("It's a {:?}", y);
}

fn main() {
    println!("Welcome to R0 Battleship's example in Rust...");
    println!("How many players today? (0|1|2)");
    let mut number = String::new();
    stdin().read_line(&mut number).expect("Failed to read line");
    let count_players: u32 = number.trim().parse().expect("Not a number");
    if count_players > 2 {
        println!("Too many players...");
    } else if count_players == 0 {
        run_auto_bot();
    } else {
        let mut player1 = setup_player(1);
        let mut player2 = setup_player(2);
        let player1_init = player1.battleship.init().unwrap();
        let player2_init = player2.battleship.init().unwrap();
        player1.battleship.on_init_msg(&player2_init).unwrap();
        player2.battleship.on_init_msg(&player1_init).unwrap();

        for n in 1..10 {
            if n % 2 == 0 {
                println!(
                    "{} turn, what are your attack coordiantes? (i.e.: 0,0)",
                    player1.name
                );
                let mut attack_coord1 = String::new();
                stdin()
                    .read_line(&mut attack_coord1)
                    .expect("Failed to read line");
                let vec: Vec<&str> = attack_coord1.split(",").collect();

                let j = round(
                    &mut player1.battleship,
                    &mut player2.battleship,
                    vec[0].trim().parse::<u32>().unwrap(),
                    vec[1].trim().parse::<u32>().unwrap(),
                );
                println!("It's a {:?}", j);
            } else {
                println!(
                    "{} turn, what are your attack coordiantes? (i.e.: 0,0)",
                    player2.name
                );
                let mut attack_coord2 = String::new();
                stdin()
                    .read_line(&mut attack_coord2)
                    .expect("Failed to read line");
                let vec: Vec<&str> = attack_coord2.split(",").collect();

                let k = round(
                    &mut player2.battleship,
                    &mut player1.battleship,
                    vec[0].trim().parse::<u32>().unwrap(),
                    vec[1].trim().parse::<u32>().unwrap(),
                );
                println!("It's a {:?}", k);
            }
        }
    }
}

fn setup_player(player: i32) -> Players {
    println!("What's player {} name?", player);
    let mut player_string = String::new();
    stdin()
        .read_line(&mut player_string)
        .expect("Failed to read line");

    let player_state = GameState {
        ships: [
            setup_ship("Carrier".to_string()),
            setup_ship("Battleship".to_string()),
            setup_ship("Cruiser".to_string()),
            setup_ship("Submarine".to_string()),
            setup_ship("Destroyer".to_string()),
        ],
        salt: 0xCAFECAFE,
    };

    return Players {
        name: player_string,
        battleship: Battleship::new(player_state),
    };
}

fn setup_ship(ship_name: String) -> Ship {
    println!(
        "Where do you want your {}'s coordinates? (i.e.: 0,0)",
        ship_name
    );
    let mut carrier = String::new();
    stdin()
        .read_line(&mut carrier)
        .expect("Failed to read line");
    let carrier_coordinates = carrier.split(",");
    let vec: Vec<&str> = carrier_coordinates.collect();

    println!(
        "What do you want your {}'s direction to be? (vV|hH)",
        ship_name
    );
    let mut direction = String::new();
    stdin()
        .read_line(&mut direction)
        .expect("Failed to read line");

    let dir: ShipDirection = if direction == "v" || direction == "V" {
        ShipDirection::Vertical
    } else if direction == "h" || direction == "H" {
        ShipDirection::Horizontal
    } else {
        ShipDirection::Vertical
    };
    return Ship::new(
        vec[0].trim().parse::<u32>().unwrap(),
        vec[1].trim().parse::<u32>().unwrap(),
        dir,
    );
}
