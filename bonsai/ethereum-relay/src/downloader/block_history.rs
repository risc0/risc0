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

use std::{
    cmp::{max, min},
    sync::Arc,
    time::Duration,
};

use anyhow::{anyhow, Result};
use ethers::{
    core::types::{BlockNumber, Filter},
    prelude::{k256::ecdsa::SigningKey, signer::SignerMiddlewareError, SignerMiddleware},
    providers::{Middleware, MiddlewareError, Provider, ProviderError, StreamExt, Ws},
    types::{Log, U64},
    utils::__serde_json::Value,
};
use ethers_signers::Wallet;
use futures::FutureExt;
use tokio::sync::mpsc::{self, Sender};
use tracing::{debug, error, trace, warn};

use super::block_history;
use crate::EthersClientConfig;

#[tracing::instrument(skip_all)]
pub(crate) async fn recover_delay(state: State, sender: mpsc::Sender<Log>) -> Result<State> {
    match (state.from.as_number(), state.to.as_number()) {
        (Some(from), Some(to)) if from > to => {
            error!(?from, ?to, "Invalid block numbers.");
            Ok(state)
        }
        _ => process_logs_until_block(state, sender).await,
    }
}

async fn process_logs_until_block(state: State, sender: mpsc::Sender<Log>) -> Result<State> {
    let State {
        mut from,
        to,
        client_config,
        ..
    } = state.clone();
    debug!(?from, ?to, "Starting to recover delay.");
    let mut last_processed_block = from.as_number().unwrap_or_default();
    let mut offset = to;
    let mut done = false;
    let mut iterations: u64 = 0;
    let mut rebuild_client = false;
    let mut client = Arc::new(client_config.get_client_with_reconnects().await?);
    loop {
        iterations += 1;
        debug!("Starting iteration {iterations}.");
        trace!(?from, ?offset, ?to, "Current state.");
        if rebuild_client {
            debug!("Rebuilding client");
            client = Arc::new(client_config.get_client_with_reconnects().await?);
            rebuild_client = false;
        }
        if done {
            debug!("Finished recovering delay.");
            return Ok(State {
                from,
                last_processed_block,
                ..state
            });
        }
        let filter = Filter::new()
            .event("Transfer(address,address,uint256)")
            .from_block(from)
            .to_block(offset);
        let start = std::time::Instant::now();
        match client.subscribe_logs(&filter).await {
            Err(SignerMiddlewareError::MiddlewareError(error)) => {
                match_error_response(error, &mut from, &mut offset, to, &mut rebuild_client)?
            }
            Err(error) => {
                error!(?error, "Unknown error found in logs subscription.");
            }
            Ok(mut stream) => {
                debug!("Subscribed to logs.");
                while let Some(log) = stream.next().now_or_never().flatten() {
                    trace!(?log, "Processing log.");
                    if let Some(block_number) = log.block_number {
                        last_processed_block = max(block_number, last_processed_block);
                    }
                    if let Err(error) = sender.send(log).await {
                        error!(?error, "Failed to send log to channel.");
                    }
                }
                debug!("finished processing logs.");
                match_block_numbers(&mut from, &mut offset, to, &mut done);
            }
        };
        debug!("End of iteration {iterations:?}");
        let end = std::time::Instant::now();
        if end - start < Duration::from_secs(1) {
            warn!("Processing logs took less than 1 second.");
            warn!("Sleeping for {:?} seconds.", client_config.wait_time);
            tokio::time::sleep(client_config.wait_time).await;
        }
    }
}

fn hex_to_u64(hex: &str) -> Option<u64> {
    let hex = hex.trim_start_matches("0x");
    let hex = if hex.is_empty() { "0" } else { hex };
    u64::from_str_radix(hex, 16).ok()
}

fn parse_error_response(error: ProviderError) -> Option<(BlockNumber, BlockNumber)> {
    error.as_error_response().and_then(|response| {
        response.data.clone().and_then(|object| {
            object.get("from").and_then(|from| {
                object.get("to").and_then(|to| {
                    if let (Value::String(from), Value::String(to)) = (from, to) {
                        let from = BlockNumber::Number(hex_to_u64(from)?.into());
                        let to = BlockNumber::Number(hex_to_u64(to)?.into());
                        Some((from, to))
                    } else {
                        None
                    }
                })
            })
        })
    })
}

#[tracing::instrument(skip_all)]
pub(crate) async fn get_latest_block(client: &Provider<Ws>) -> Result<Option<BlockNumber>> {
    Ok(client
        .get_block(BlockNumber::Latest)
        .await?
        .and_then(|block| block.number)
        .map(BlockNumber::Number))
}

fn update_from_and_offset_from_error_response(
    old_from: BlockNumber,
    old_offset: BlockNumber,
    to: BlockNumber,
    new_from: BlockNumber,
    new_to: BlockNumber,
) -> Result<(BlockNumber, BlockNumber)> {
    match (old_from, old_offset, to, new_from, new_to) {
        (
            BlockNumber::Number(old_from),
            BlockNumber::Number(_old_offset),
            BlockNumber::Number(to),
            BlockNumber::Number(new_from),
            BlockNumber::Number(new_to),
        ) => {
            let from = max(old_from, min(new_from, to));
            let offset = min(to, max(from + 1, new_to));
            Ok((from.into(), offset.into()))
        }
        (
            BlockNumber::Earliest,
            BlockNumber::Number(_old_offset),
            BlockNumber::Number(to),
            BlockNumber::Number(new_from),
            BlockNumber::Number(new_to),
        ) => {
            let from = min(new_from, to);
            let offset = min(to, max(from + 1, new_to));
            Ok((from.into(), offset.into()))
        }
        _ => {
            error!(
                ?old_from,
                ?old_offset,
                ?new_from,
                ?new_to,
                ?to,
                "Invalid block numbers."
            );
            Err(anyhow!("Invalid block numbers."))
        }
    }
}

fn match_error_response(
    error: ProviderError,
    from: &mut BlockNumber,
    offset: &mut BlockNumber,
    to: BlockNumber,
    rebuild_client: &mut bool,
) -> Result<()> {
    let error_string = error.to_string();
    match parse_error_response(error) {
        Some((new_from, new_to)) => {
            trace!(
                ?from,
                ?new_from,
                ?to,
                ?new_to,
                "Got updated values to request in next iteration."
            );
            (*from, *offset) =
                update_from_and_offset_from_error_response(*from, *offset, to, new_from, new_to)?;
            trace!(?from, ?offset, "Updated values for `from` and `offset`.");
        }
        None => {
            error!(error = %error_string, "Failed to parse error response, rebuilding client to try again.");
            *rebuild_client = true;
        }
    }
    Ok(())
}

fn match_block_numbers(
    from: &mut BlockNumber,
    offset: &mut BlockNumber,
    to: BlockNumber,
    done: &mut bool,
) {
    match (from.as_number(), offset.as_number(), to.as_number()) {
        (_, Some(offset_block), Some(to_block)) if offset_block > to_block => {
            warn!(
                %offset_block,
                %to_block,
                "`offset` is greater than `to`, setting `offset` to `to`."
            );
            *offset = to;
        }
        (_, Some(offset_block), Some(to_block)) if offset_block == to_block => {
            *done = true;
        }
        (Some(from_block), Some(offset_block), Some(to_block)) => {
            trace!(%from, %offset, "Old values");
            let new_offset = offset_block + (offset_block - from_block);
            *from = *offset;
            *offset = min(new_offset, to_block).into();
            trace!(%from, %offset, "New values");
        }
        (None, Some(offset_block), Some(to_block)) => {
            *from = *offset;
            *offset = min(offset_block * 2, to_block).into();
        }
        _ => {
            warn!(?from, ?offset, ?to, "Unknown state of block numbers.");
        }
    }
}

#[derive(Clone, Debug)]
pub(crate) struct State {
    pub client_config: EthersClientConfig,
    pub client: SignerMiddleware<Provider<Ws>, Wallet<SigningKey>>,
    pub recreate_client: bool,
    pub last_processed_block: U64,
    pub latest_block: U64,
    pub filter: Filter,
    pub from: BlockNumber,
    pub to: BlockNumber,
}

impl State {
    pub async fn recreate_client(&self) -> Result<Self> {
        let client = self.client_config.get_client_with_reconnects().await?;
        Ok(Self {
            client,
            recreate_client: false,
            ..self.clone()
        })
    }
}

#[tracing::instrument(skip_all)]
pub(crate) async fn recover_lost_blocks(state: State, sender: Sender<Log>) -> Result<State> {
    let latest_block = match block_history::get_latest_block(state.client.provider()).await {
        Ok(Some(block)) => match block.as_number() {
            block @ Some(..) => block,
            None => {
                error!("Latest block is not a number");
                None
            }
        },
        Ok(None) => {
            warn!("Latest block is not available, retrying...");
            None
        }
        Err(error) => {
            error!(?error, "Failed to get latest block number");
            None
        }
    };
    if let Some(latest_block) = latest_block {
        debug!(?latest_block, "Got latest block number.");
        let state = State {
            latest_block,
            ..state
        };
        block_history::recover_delay(state, sender).await
    } else {
        Ok(State {
            recreate_client: true,
            ..state
        })
    }
}
