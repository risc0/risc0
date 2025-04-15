// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use std::time::Instant;

use criterion::{black_box, criterion_group, criterion_main, Criterion};
use serde_json::Value;
use sqlx::postgres::PgPoolOptions;
use taskdb::INIT_TASK;
use tokio::runtime::Runtime;

fn taskdb(c: &mut Criterion) {
    let runtime = Runtime::new().unwrap();
    let worker_type = "CPU";
    let user_id = "user1";
    let database_url = std::env::var("DATABASE_URL").expect("DATABASE_URL must be set");
    let db_url = database_url.as_str();

    c.bench_function("create_stream", |b| {
        b.to_async(&runtime).iter_custom(|iters| async move {
            let db = PgPoolOptions::new()
                .max_connections(4)
                .connect(db_url)
                .await
                .expect("failed to connect to DATABASE_URL");

            let start = Instant::now();
            for _i in 0..iters {
                black_box(
                    taskdb::create_stream(&db, worker_type, 1, 1.0, user_id)
                        .await
                        .unwrap(),
                );
            }
            let elapsed = start.elapsed();
            taskdb::test_helpers::cleanup(&db).await;
            elapsed
        });
    });

    c.bench_function("create_job", |b| {
        b.to_async(&runtime).iter_custom(|iters| async move {
            let db = PgPoolOptions::new()
                .max_connections(4)
                .connect(db_url)
                .await
                .expect("failed to connect to DATABASE_URL");

            let stream_id = taskdb::create_stream(&db, worker_type, 1, 1.0, user_id)
                .await
                .unwrap();
            let task_def = Value::default();

            let start = Instant::now();
            for _i in 0..iters {
                black_box(
                    taskdb::create_job(&db, &stream_id, &task_def, 1, 1, user_id)
                        .await
                        .unwrap(),
                );
            }

            let elapsed = start.elapsed();
            taskdb::test_helpers::cleanup(&db).await;
            elapsed
        });
    });

    #[allow(clippy::unit_arg)]
    c.bench_function("create_task", |b| {
        b.to_async(&runtime).iter_custom(|iters| async move {
            let db = PgPoolOptions::new()
                .max_connections(4)
                .connect(db_url)
                .await
                .expect("failed to connect to DATABASE_URL");

            let stream_id = taskdb::create_stream(&db, worker_type, 0, 1.0, user_id)
                .await
                .unwrap();
            let task_def = Value::default();
            let job_id = taskdb::create_job(&db, &stream_id, &task_def, 0, 1, user_id)
                .await
                .unwrap();

            let start = Instant::now();
            for i in 0..iters {
                // creates a linear task dep tree:
                let pre_reqs = if i == 0 {
                    serde_json::json!([taskdb::INIT_TASK])
                } else {
                    serde_json::json!([format!("{}", i - 1)])
                };
                let task_id = format!("{i}");
                black_box(
                    taskdb::create_task(
                        &db, &job_id, &task_id, &stream_id, &task_def, &pre_reqs, 0, 1,
                    )
                    .await
                    .unwrap(),
                );
            }

            let elapsed = start.elapsed();
            taskdb::test_helpers::cleanup(&db).await;
            elapsed
        });
    });

    c.bench_function("request_work", |b| {
        b.to_async(&runtime).iter_custom(|iters| async move {
            let db = PgPoolOptions::new()
                .max_connections(4)
                .connect(db_url)
                .await
                .expect("failed to connect to DATABASE_URL");

            let stream_id = taskdb::create_stream(&db, worker_type, 0, 1.0, user_id)
                .await
                .unwrap();
            let task_def = Value::default();
            let job_id = taskdb::create_job(&db, &stream_id, &task_def, 0, 1, user_id)
                .await
                .unwrap();

            // Pre populate the tasks:
            for i in 0..iters {
                // creates a linear task dep tree:
                let pre_reqs = if i == 0 {
                    serde_json::json!([taskdb::INIT_TASK])
                } else {
                    serde_json::json!([format!("{}", i - 1)])
                };
                taskdb::create_task(
                    &db,
                    &job_id,
                    &format!("{i}"),
                    &stream_id,
                    &task_def,
                    &pre_reqs,
                    0,
                    1,
                )
                .await
                .unwrap();
            }

            let start = Instant::now();
            for _i in 0..iters {
                // creates a linear task dep tree:
                black_box(taskdb::request_work(&db, worker_type).await.unwrap());
            }

            let elapsed = start.elapsed();
            taskdb::test_helpers::cleanup(&db).await;
            elapsed
        });
    });

    c.bench_function("update_task_done", |b| {
        b.to_async(&runtime).iter_custom(|iters| async move {
            let db = PgPoolOptions::new()
                .max_connections(4)
                .connect(db_url)
                .await
                .expect("failed to connect to DATABASE_URL");

            let stream_id = taskdb::create_stream(&db, worker_type, 0, 1.0, user_id)
                .await
                .unwrap();
            let task_def = Value::default();
            let job_id = taskdb::create_job(&db, &stream_id, &task_def, 0, 1, user_id)
                .await
                .unwrap();

            // Pre populate the tasks:
            for i in 0..iters {
                // creates a linear task dep tree:
                let pre_reqs = if i == 0 {
                    serde_json::json!([taskdb::INIT_TASK])
                } else {
                    serde_json::json!([format!("{}", i - 1)])
                };
                taskdb::create_task(
                    &db,
                    &job_id,
                    &format!("{i}"),
                    &stream_id,
                    &task_def,
                    &pre_reqs,
                    0,
                    1,
                )
                .await
                .unwrap();
                // Complete the first task so the last task triggers a job complete
                taskdb::update_task_done(&db, &job_id, INIT_TASK, Value::default())
                    .await
                    .unwrap();
            }
            let start = Instant::now();
            for i in 0..iters {
                black_box(
                    taskdb::update_task_done(&db, &job_id, &format!("{i}"), Value::default())
                        .await
                        .unwrap(),
                );
            }
            let elapsed = start.elapsed();
            taskdb::test_helpers::cleanup(&db).await;
            elapsed
        });
    });
}

criterion_group!(benches, taskdb);
criterion_main!(benches);
