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

/// This example assumes that:
/// - there's a redis instance running on `redis://localhost:6379/`
/// - r0vm is installed with the `redis` feature: `cargo install --force --path risc0/r0vm --features redis`
fn main() -> anyhow::Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    let _iterations: u32 = 100000000;

    #[cfg(feature = "redis")]
    if cfg!(feature = "redis") {
        use risc0_zkvm::{ApiClient, Asset, AssetRequest, ExecutorEnv, RedisParams};

        let url = String::from("redis://localhost:6379/");
        let key = String::from("key");
        let ttl = 180;
        let client = ApiClient::from_env().unwrap();
        let env = ExecutorEnv::builder().write(&_iterations)?.build()?;
        let timer = std::time::SystemTime::now();
        let session = client.execute(
            &env,
            Asset::Inline(fibonacci_methods::FIBONACCI_ELF.into()),
            AssetRequest::Redis(RedisParams { url, key, ttl }),
            |_info, _segment| {
                let Asset::Redis(_) = _segment else {
                    anyhow::bail!("wrong asset request type")
                };
                Ok(())
            },
        )?;

        let perf = (session.cycles() as f64 / timer.elapsed()?.as_secs_f64()) / 1_000_000.0;
        println!(
            "redis executor: {:?} Mhz, {} segments",
            perf,
            session.segments.len()
        );
    }

    #[cfg(feature = "prove")]
    if cfg!(feature = "prove") {
        use risc0_zkvm::{default_executor, ExecutorEnv};

        let env = ExecutorEnv::builder().write(&_iterations)?.build()?;
        let exec = default_executor();
        let timer = std::time::SystemTime::now();
        let session = exec.execute(env, fibonacci_methods::FIBONACCI_ELF)?;

        let perf = (session.cycles() as f64 / timer.elapsed()?.as_secs_f64()) / 1_000_000.0;
        println!(
            "default_executor: {:?} Mhz, {} segments",
            perf,
            session.segments.len()
        );
    }

    Ok(())
}
