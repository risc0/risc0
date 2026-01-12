// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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
