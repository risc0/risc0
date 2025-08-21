// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::guest::env;

use bevy_core::Outputs;
use bevy_ecs::{prelude::*, world::World};

#[derive(Component)]
struct Position {
    x: f32,
    y: f32,
}

#[derive(Component)]
struct Velocity {
    x: f32,
    y: f32,
}

#[derive(StageLabel)]
pub struct UpdateLabel;

// This system moves each entity with a Position and Velocity component
fn movement(mut query: Query<(&mut Position, &Velocity)>) {
    for (mut position, velocity) in &mut query {
        position.x += velocity.x;
        position.y += velocity.y;
    }
}

fn main() {
    let turns: u32 = env::read();
    let mut world = World::new();
    let entity = world
        .spawn((Position { x: 0.0, y: 0.0 }, Velocity { x: 1.0, y: 0.0 }))
        .id();

    let mut schedule = Schedule::default();

    schedule.add_stage(
        UpdateLabel,
        SystemStage::single_threaded().with_system(movement),
    );
    {
        let entity_ref = world.entity(entity);
        let position = entity_ref.get::<Position>().unwrap();
        assert!(position.x == 0.0);
    }

    // Run timesteps
    for _ in 0..turns {
        env::log("running timestep...");
        schedule.run(&mut world);
    }
    {
        let entity_ref = world.entity(entity);
        let position = entity_ref.get::<Position>().unwrap();
        let out = Outputs {
            position: position.x,
        };
        env::commit(&out);
    }
}
