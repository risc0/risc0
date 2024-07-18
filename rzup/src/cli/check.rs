// Copyright 2024 RISC Zero, Inc.
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

use anyhow::Result;
use termcolor::{Color, ColorChoice, StandardStream};

use crate::{
    pretty_msg, pretty_msgln,
    utils::{get_updatable_active, UpdateInfo},
};

pub async fn handler() -> Result<()> {
    let updates = get_updatable_active().await?;
    print_updates(&updates)?;
    Ok(())
}

fn print_updates(updates: &[UpdateInfo]) -> Result<()> {
    // TODO: Check for rzup updates
    let mut stdout = StandardStream::stdout(ColorChoice::Always);

    for update in updates {
        if update.up_to_date {
            pretty_msg!(&mut stdout, true, None, &format!("{} - ", update.name));
            pretty_msg!(&mut stdout, true, Some(Color::Green), "Up to date ");
            pretty_msgln!(
                &mut stdout,
                false,
                None,
                format!(
                    ": {} ({})",
                    update.current_version, update.current_published_at
                )
            );
        } else {
            pretty_msg!(&mut stdout, true, None, &format!("{} - ", update.name));
            pretty_msg!(&mut stdout, true, Some(Color::Yellow), "Update available ");
            pretty_msgln!(
                &mut stdout,
                false,
                None,
                format!(
                    ": {} ({}) -> {} ({})",
                    update.current_version,
                    update.current_published_at,
                    update.latest_version,
                    update.latest_published_at,
                )
            );
        }
    }
    Ok(())
}
