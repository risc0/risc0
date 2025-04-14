// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use anyhow::{bail, Context, Result};
use clap::Parser;
use rand::{rngs::StdRng, seq::SliceRandom, Rng, SeedableRng};
use sqlx::{
    postgres::PgPoolOptions,
    types::{JsonValue, Uuid},
    PgPool,
};
use std::{
    str::FromStr,
    sync::{
        atomic::{AtomicBool, Ordering},
        Arc,
    },
};
use taskdb::{
    planner::{
        task::{Command as TaskCmd, Task},
        Planner,
    },
    test_helpers, update_task_done, update_task_failed, update_task_retry, JobState, ReadyTask,
};
use tokio::{
    task::JoinSet,
    time::{sleep, Duration},
};
use tracing_subscriber::filter::EnvFilter;

async fn create_customer(pool: &PgPool, user_id: &str) -> Result<(Uuid, Uuid)> {
    let cpu_stream = taskdb::create_stream(pool, "CPU", 0, 1.0, user_id)
        .await
        .context("Failed to create cpu stream")?;
    let gpu_stream = taskdb::create_stream(pool, "GPU", 0, 1.0, user_id)
        .await
        .context("Failed to create cpu stream")?;

    Ok((cpu_stream, gpu_stream))
}

async fn spawner(shutdown: Arc<AtomicBool>, pool: PgPool, args: Args) -> Result<()> {
    tracing::info!("Starting spawner..");
    let mut customers = vec![];
    for idx in 0..args.customers {
        let user_id = format!("user_{idx}");
        customers.push((
            create_customer(&pool, &user_id).await.context("Failed to create customer")?,
            user_id,
        ));
    }
    let mut r = StdRng::seed_from_u64(args.rng_seed);

    while !shutdown.load(Ordering::Relaxed) {
        // Pick a random
        let ((cpu_stream, gpu_stream), user_id) = customers.choose(&mut r).unwrap();
        let segment_count = r.gen_range(1..args.max_job_size);
        let task_def = serde_json::json!({
            "cpu_stream": gpu_stream.to_string(),
            "gpu_stream": gpu_stream.to_string(),
            "segments": segment_count,
            "user_id": user_id,
        });
        let job_id = taskdb::create_job(&pool, cpu_stream, &task_def, 0, 100, user_id)
            .await
            .context("Failed to create job")?;
        tracing::info!("Spawning new job: {job_id} segments; {segment_count}");

        if args.incra_mode {
            loop {
                let job_status = taskdb::get_job_state(&pool, &job_id, user_id).await.unwrap();
                if job_status != JobState::Running {
                    break;
                }
                sleep(Duration::from_millis(100)).await;
            }
        } else {
            sleep(Duration::from_millis(args.job_speed)).await;
        }
    }

    Ok(())
}

async fn process_task(pool: &PgPool, tree_task: &Task, db_task: &ReadyTask) -> Result<()> {
    let user_id = db_task.task_def.get("user_id").unwrap().as_str().unwrap();
    let cpu_stream = db_task.task_def.get("cpu_stream").unwrap().as_str().unwrap();
    let cpu_stream = Uuid::from_str(cpu_stream).unwrap();
    let gpu_stream = db_task.task_def.get("gpu_stream").unwrap().as_str().unwrap();
    let gpu_stream = Uuid::from_str(gpu_stream).unwrap();
    let keccak_stream = db_task.task_def.get("keccak_stream").unwrap().as_str().unwrap();
    let keccak_stream = Uuid::from_str(keccak_stream).unwrap();

    match tree_task.command {
        TaskCmd::Keccak => {
            let task_def = serde_json::json!({"Keccak": { "segment": tree_task.task_number }, "user_id": user_id });
            let prereqs = serde_json::json!([]);
            let task_name = format!("{}", tree_task.task_number);

            // tracing::debug!("inserting: segment {}", task_name);
            taskdb::create_task(
                pool,
                &db_task.job_id,
                &task_name,
                &keccak_stream,
                &task_def,
                &prereqs,
                2,
                60,
            )
            .await
            .context("Failed to create Prove task")?;
        }
        TaskCmd::Segment => {
            let task_def = serde_json::json!({"Prove": { "segment": tree_task.task_number }, "user_id": user_id });
            let prereqs = serde_json::json!([]);
            let task_name = format!("{}", tree_task.task_number);

            // tracing::debug!("inserting: segment {}", task_name);
            taskdb::create_task(
                pool,
                &db_task.job_id,
                &task_name,
                &gpu_stream,
                &task_def,
                &prereqs,
                2,
                60,
            )
            .await
            .context("Failed to create Prove task")?;
        }
        TaskCmd::Join => {
            let task_def = serde_json::json!({
                "Join": {
                    "left": tree_task.depends_on[0],
                    "right": tree_task.depends_on[1],
                    "index": tree_task.task_number
                }, "user_id": user_id
            });
            let prereqs = serde_json::json!([
                format!("{}", tree_task.depends_on[0]),
                format!("{}", tree_task.depends_on[1])
            ]);
            let task_name = format!("{}", tree_task.task_number);

            // tracing::debug!("inserting join {} - {:?}", task_name, prereqs);
            taskdb::create_task(
                pool,
                &db_task.job_id,
                &task_name,
                &gpu_stream,
                &task_def,
                &prereqs,
                2,
                2,
            )
            .await
            .context("Failed to create Join task")?;
        }
        TaskCmd::Union => {
            let task_def = serde_json::json!({
                "Union": {
                    "left": tree_task.depends_on[0],
                    "right": tree_task.depends_on[1],
                    "index": tree_task.task_number
                }, "user_id": user_id
            });
            let prereqs = serde_json::json!([
                format!("{}", tree_task.depends_on[0]),
                format!("{}", tree_task.depends_on[1])
            ]);
            let task_name = format!("{}", tree_task.task_number);

            // tracing::debug!("inserting Union {} - {:?}", task_name, prereqs);
            taskdb::create_task(
                pool,
                &db_task.job_id,
                &task_name,
                &gpu_stream,
                &task_def,
                &prereqs,
                2,
                2,
            )
            .await
            .context("Failed to create Union task")?;
        }
        TaskCmd::Finalize => {
            let task_def = serde_json::json!({
                "Finalize": {
                }, "user_id": user_id
            });
            let prereqs = serde_json::json!([format!("{}", tree_task.depends_on[0])]);

            // tracing::debug!("inserting finalize {} {:?}", tree_task.task_number, prereqs);
            taskdb::create_task(
                pool,
                &db_task.job_id,
                "finalize",
                &cpu_stream,
                &task_def,
                &prereqs,
                0,
                10,
            )
            .await
            .context("Failed to create finalize task")?;
        }
    }
    Ok(())
}

async fn run_exec_task(pool: &PgPool, task: &ReadyTask, args: &Args) -> Result<()> {
    let mut planner = Planner::default();
    let segments = task
        .task_def
        .get("segments")
        .context("task missing segments json elm")?
        .as_u64()
        .context("segments not u64")?;

    tracing::info!("Executor running job: {}", task.job_id);
    for _ in 0..segments {
        planner.enqueue_segment().unwrap();

        while let Some(tree_task) = planner.next_task() {
            process_task(pool, tree_task, task).await.unwrap();
        }
    }

    planner.finish().unwrap();
    while let Some(tree_task) = planner.next_task() {
        process_task(pool, tree_task, task).await.unwrap();
    }
    tracing::info!("Executor completed job: {}", task.job_id);
    sleep(Duration::from_millis(args.exec_delay)).await;

    Ok(())
}

async fn worker(
    shutdown: Arc<AtomicBool>,
    pool: PgPool,
    worker_id: u32,
    worker_type: &str,
    args: Args,
) -> Result<()> {
    tracing::info!("in worker: {worker_type} idx: {worker_id}");
    let mut r = StdRng::seed_from_u64(args.rng_seed + u64::from(worker_id));

    while !shutdown.load(Ordering::Relaxed) {
        match taskdb::request_work(&pool, worker_type).await {
            Ok(task) => {
                let Some(task) = task else {
                    sleep(Duration::from_millis(200)).await;
                    continue;
                };
                // let user_id = task.task_def.get("user_id").unwrap().as_str().unwrap();

                match worker_type {
                    "CPU" => {
                        match task.task_id.as_str() {
                            taskdb::INIT_TASK => run_exec_task(&pool, &task, &args)
                                .await
                                .context("failed to run exec")?,
                            "finalize" => {}
                            _ => bail!("unsupported CPU task"),
                        }

                        let res = update_task_done(
                            &pool,
                            &task.job_id,
                            &task.task_id,
                            JsonValue::default(),
                        )
                        .await
                        .context("Failed to set task to complete")?;
                        if !res {
                            tracing::error!(
                                "Failed to update task to done: {}:{}",
                                task.job_id,
                                task.task_id
                            );
                        }
                    }
                    "GPU" => {
                        // wait random ms in range
                        // let seconds = r.gen_range(1..args.gpu_work_speed);
                        tracing::info!(
                            "[{worker_id}] GPU running for {} ms, job: {}:{}",
                            args.gpu_work_speed,
                            task.job_id,
                            task.task_id
                        );
                        sleep(Duration::from_millis(args.gpu_work_speed)).await;

                        // 1 in N chance to fail a task
                        if r.gen_range(0..args.gpu_fail_rate) == 0 {
                            tracing::error!(
                                "Intentionally failing job: {}:{}",
                                task.job_id,
                                task.task_id
                            );

                            if !update_task_failed(&pool, &task.job_id, &task.task_id, "ERROR")
                                .await
                                .context("Failed to update_task_failed")?
                            {
                                tracing::error!(
                                    "Failed to fail task {}:{}, probably already failing..",
                                    task.job_id,
                                    task.task_id
                                );
                            }
                        } else if r.gen_range(0..args.gpu_retry_rate) == 0 {
                            tracing::warn!("Retrying task {}:{}", task.job_id, task.task_id);

                            if !update_task_retry(&pool, &task.job_id, &task.task_id)
                                .await
                                .context("Failed to task_retry")?
                            {
                                tracing::error!(
                                    "Failed to retry task {}:{}, probably already failing..",
                                    task.job_id,
                                    task.task_id
                                );
                            }
                        } else {
                            let res = update_task_done(
                                &pool,
                                &task.job_id,
                                &task.task_id,
                                JsonValue::default(),
                            )
                            .await
                            .context("Failed to set task to complete")?;

                            tracing::info!(
                                "Completed GPU task: {}:{} - res: {}",
                                task.job_id,
                                task.task_id,
                                res
                            );
                            if !res {
                                tracing::error!(
                                    "Failed to update task to done: {}:{}",
                                    task.job_id,
                                    task.task_id
                                );
                            }
                        }
                    }
                    _ => bail!("Unsupported work type"),
                }
            }
            Err(err) => {
                tracing::error!("Failed to request_work(): {err:?}");
                bail!(err);
            }
        }
    }

    Ok(())
}

/// taskdb Stress testing harness
#[derive(Parser, Clone, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// cpu workers
    #[arg(short, long, default_value_t = 1)]
    cpu_workers: u32,

    /// gpu workers
    #[arg(short, long, default_value_t = 4)]
    gpu_workers: u32,

    /// Customers with work
    #[arg(short = 's', long, default_value_t = 1)]
    customers: u64,

    /// Time between starting new jobs (in ms)
    #[arg(short, long, default_value_t = 5000)]
    job_speed: u64,

    /// Toggles incremental job mode
    ///
    /// This mode waits between new jobs for the last job to complete
    #[arg(short, long, default_value_t = false)]
    incra_mode: bool,

    /// Time between executor tasks (in ms)
    /// Observed ranges: 70ms - 240ms in prod
    #[arg(short, long, default_value_t = 240)]
    exec_delay: u64,

    /// Max size of new jobs, in segments
    #[arg(short, long, default_value_t = 32)]
    max_job_size: u64,

    /// Wait time to use for the GPU work time (in ms)
    #[arg(short = 't', long, default_value_t = 800)]
    gpu_work_speed: u64,

    /// Frequency of GPU task failures (1/N chance)
    #[arg(long, default_value_t = 100)]
    gpu_fail_rate: u64,

    /// Frequency of GPU retries (1/N chance)
    #[arg(long, default_value_t = 200)]
    gpu_retry_rate: u64,

    /// RNG seed
    #[arg(short, long, default_value_t = 41)]
    rng_seed: u64,

    /// Postgresql connection pool size
    #[arg(short, long, default_value_t = 100)]
    pool_size: u32,
}

#[tokio::main]
async fn main() -> Result<()> {
    tracing_subscriber::fmt().with_env_filter(EnvFilter::from_default_env()).init();

    let args = Args::parse();
    let conn_url = std::env::var("DATABASE_URL").expect("Env var DATABASE_URL is required.");
    let db = PgPoolOptions::new().max_connections(args.pool_size).connect(&conn_url).await.unwrap();

    let mut tasks = JoinSet::new();
    let shutdown = Arc::new(AtomicBool::new(false));

    let pool = db.clone();
    let args_copy = args.clone();
    let shutdown_copy = shutdown.clone();
    tasks.spawn(spawner(shutdown_copy, pool, args_copy));

    // Create reaper
    let pool_copy = db.clone();
    let shutdown_copy = shutdown.clone();
    tasks.spawn(async move {
        while !shutdown_copy.load(Ordering::Relaxed) {
            let requeued_tasks =
                taskdb::requeue_tasks(&pool_copy, 100).await.expect("Failed to requeue tasks");
            if requeued_tasks > 0 {
                tracing::warn!("requeued {requeued_tasks} tasks");
            }

            sleep(Duration::from_secs(2)).await;
        }

        Ok(())
    });

    for i in 0..args.cpu_workers {
        let pool_copy = db.clone();
        let args_copy = args.clone();
        let shutdown_copy = shutdown.clone();
        tasks.spawn(worker(shutdown_copy, pool_copy, i, "CPU", args_copy));
    }
    for i in 0..args.gpu_workers {
        let pool_copy = db.clone();
        let args_copy = args.clone();
        let shutdown_copy = shutdown.clone();
        tasks.spawn(worker(shutdown_copy, pool_copy, i, "GPU", args_copy));
    }

    // ctrl-c handler
    let shutdown_copy = shutdown.clone();
    tokio::spawn(async move {
        tokio::signal::ctrl_c().await.expect("Failed to register ctrl+c handler");
        tracing::warn!("Starting Graceful shutdown, cleaning up...");
        shutdown_copy.store(true, Ordering::Relaxed);
    });

    loop {
        while let Some(res) = tasks.try_join_next() {
            res.unwrap().unwrap();
        }

        if shutdown.load(Ordering::Relaxed) {
            tasks.abort_all();
            while let Some(res) = tasks.try_join_next() {
                let _ = res.unwrap();
            }
            test_helpers::cleanup(&db).await;
            break;
        }

        sleep(Duration::from_millis(100)).await;
    }

    tracing::info!("Completed stress test...");

    Ok(())
}
