// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use anyhow::Result;
use sqlx::{
    PgPool,
    types::{JsonValue, Uuid},
};
use taskdb::{
    ReadyTask, TaskState,
    planner::{
        Planner,
        task::{Command as TaskCmd, Task},
    },
    test_helpers,
};

#[sqlx::test()]
async fn e2e(pool: PgPool) -> Result<()> {
    let image_id = "41414141";
    let input_id = "42424242";
    let aux_worker_type = "AUX";
    let cpu_worker_type = "CPU";
    let gpu_worker_type = "GPU";
    let segments = 3;
    let user_id = "user1";

    // initial setup, on first workflow from customer
    // or on provisining a new user with reservations.

    // Stream for handling auxiliary tasks note: we could just overload the CPU
    // stream with aux tasks but it would not scale well
    let aux_stream = taskdb::create_stream(&pool, aux_worker_type, 1, 1.0, user_id)
        .await
        .unwrap();

    // CPU intensive tasks (executor)
    let cpu_stream = taskdb::create_stream(&pool, cpu_worker_type, 1, 1.0, user_id)
        .await
        .unwrap();

    // GPU workers for prove/lift/join
    let gpu_stream = taskdb::create_stream(&pool, gpu_worker_type, 1, 1.0, user_id)
        .await
        .unwrap();

    // Create a new workflow for a given customer
    let task_def = serde_json::json!({"image_id": image_id, "input_id": input_id});
    taskdb::create_job(&pool, &aux_stream, &task_def, 0, 100, user_id)
        .await
        .unwrap();

    // Init stage, spawn the executor task, move things into hot storage
    let task = taskdb::request_work(&pool, aux_worker_type)
        .await
        .unwrap()
        .unwrap();
    // DO INIT TASKS HERE...

    // forward the taskdef on to the executor...
    taskdb::create_task(
        &pool,
        &task.job_id,
        "executor",
        &cpu_stream,
        &task.task_def,
        &serde_json::json!([]),
        0,
        10,
    )
    .await
    .unwrap();

    assert!(
        taskdb::update_task_done(&pool, &task.job_id, &task.task_id, JsonValue::default())
            .await
            .unwrap()
    );

    // Executor stage:
    let exec_task = taskdb::request_work(&pool, cpu_worker_type)
        .await
        .unwrap()
        .unwrap();

    // Mock executor
    assert_eq!(
        exec_task
            .task_def
            .get("image_id")
            .unwrap()
            .as_str()
            .unwrap(),
        image_id
    );
    assert_eq!(
        exec_task
            .task_def
            .get("input_id")
            .unwrap()
            .as_str()
            .unwrap(),
        input_id
    );

    async fn process_task(
        pool: &PgPool,
        tree_task: &Task,
        db_task: &ReadyTask,
        gpu_stream: &Uuid,
        aux_stream: &Uuid,
    ) -> Result<()> {
        match tree_task.command {
            TaskCmd::Keccak => {
                let task_def = serde_json::json!({"Keccak": { "segment": tree_task.task_number }});
                let prereqs = serde_json::json!([]);
                let task_name = format!("{}", tree_task.task_number);

                // println!("inserting: segment {}", task_name);
                taskdb::create_task(
                    pool,
                    &db_task.job_id,
                    &task_name,
                    gpu_stream,
                    &task_def,
                    &prereqs,
                    0,
                    10,
                )
                .await
                .unwrap();
            }
            TaskCmd::Segment => {
                let task_def = serde_json::json!({"Prove": { "segment": tree_task.task_number }});
                let prereqs = serde_json::json!([]);
                let task_name = format!("{}", tree_task.task_number);

                // println!("inserting: segment {}", task_name);
                taskdb::create_task(
                    pool,
                    &db_task.job_id,
                    &task_name,
                    gpu_stream,
                    &task_def,
                    &prereqs,
                    0,
                    10,
                )
                .await
                .unwrap();
            }
            TaskCmd::Join => {
                let task_def = serde_json::json!({
                    "Join": {
                        "left": tree_task.depends_on[0],
                        "right": tree_task.depends_on[1],
                        "index": tree_task.task_number
                    }
                });
                let prereqs = serde_json::json!([
                    format!("{}", tree_task.depends_on[0]),
                    format!("{}", tree_task.depends_on[1])
                ]);
                let task_name = format!("{}", tree_task.task_number);

                // println!("inserting join {} - {:?}", task_name, prereqs);
                taskdb::create_task(
                    pool,
                    &db_task.job_id,
                    &task_name,
                    gpu_stream,
                    &task_def,
                    &prereqs,
                    0,
                    10,
                )
                .await
                .unwrap();
            }
            TaskCmd::Union => {
                let task_def = serde_json::json!({
                    "Union": {
                        "left": tree_task.depends_on[0],
                        "right": tree_task.depends_on[1],
                        "index": tree_task.task_number
                    }
                });
                let prereqs = serde_json::json!([
                    format!("{}", tree_task.depends_on[0]),
                    format!("{}", tree_task.depends_on[1])
                ]);
                let task_name = format!("{}", tree_task.task_number);

                // println!("inserting union {} - {:?}", task_name, prereqs);
                taskdb::create_task(
                    pool,
                    &db_task.job_id,
                    &task_name,
                    gpu_stream,
                    &task_def,
                    &prereqs,
                    0,
                    10,
                )
                .await
                .unwrap();
            }
            TaskCmd::Finalize => {
                let task_def = serde_json::json!({
                    "Finalize": {
                    }
                });
                let prereqs = serde_json::json!([format!("{}", tree_task.depends_on[0])]);

                // println!("inserting finalize {} {:?}", tree_task.task_number, prereqs);
                taskdb::create_task(
                    pool,
                    &db_task.job_id,
                    "finalize",
                    aux_stream,
                    &task_def,
                    &prereqs,
                    0,
                    10,
                )
                .await
                .unwrap();
            }
        }
        Ok(())
    }

    // Spawn all the segments, and joins
    let mut planner = Planner::default();
    for _ in 0..segments {
        planner.enqueue_segment().unwrap();

        while let Some(tree_task) = planner.next_task() {
            process_task(&pool, tree_task, &exec_task, &gpu_stream, &aux_stream)
                .await
                .unwrap();
        }
    }

    // Spawn final joins + finalize task
    planner.finish().unwrap();
    while let Some(tree_task) = planner.next_task() {
        process_task(&pool, tree_task, &exec_task, &gpu_stream, &aux_stream)
            .await
            .unwrap();
    }

    assert!(
        taskdb::update_task_done(
            &pool,
            &exec_task.job_id,
            &exec_task.task_id,
            JsonValue::default(),
        )
        .await
        .unwrap()
    );

    // Validate we have a terminal (finalize) node and its stats are correct:
    let finalize = test_helpers::get_task(&pool, &task.job_id, "finalize")
        .await
        .unwrap();
    assert_eq!(finalize.waiting_on, 1);
    assert_eq!(
        finalize
            .prerequisites
            .as_array()
            .unwrap()
            .first()
            .unwrap()
            .as_str()
            .unwrap(),
        "4"
    );

    // Mock GPU workers consuming the work items
    let mut idx = 0;
    while let Some(task) = taskdb::request_work(&pool, gpu_worker_type).await.unwrap() {
        let idx_str = idx.to_string();
        assert_eq!(task.task_id, idx_str);
        match idx {
            // Prove Segments
            0 | 1 | 3 => {
                assert_eq!(
                    task.task_def
                        .get("Prove")
                        .unwrap()
                        .as_object()
                        .unwrap()
                        .get("segment")
                        .unwrap()
                        .as_u64()
                        .unwrap(),
                    idx
                );
            }
            // Joins
            2 => {
                let join_obj = task.task_def.get("Join").unwrap().as_object().unwrap();
                assert_eq!(join_obj.get("left").unwrap().as_u64().unwrap(), 0);
                assert_eq!(join_obj.get("right").unwrap().as_u64().unwrap(), 1);
                assert_eq!(join_obj.get("index").unwrap().as_u64().unwrap(), 2);
            }
            4 => {
                let join_obj = task.task_def.get("Join").unwrap().as_object().unwrap();
                assert_eq!(join_obj.get("left").unwrap().as_u64().unwrap(), 2);
                assert_eq!(join_obj.get("right").unwrap().as_u64().unwrap(), 3);
                assert_eq!(join_obj.get("index").unwrap().as_u64().unwrap(), 4);
            }
            // Finalize
            _ => panic!("idx: {idx}"),
        }
        // Mark the task as done.
        assert!(
            taskdb::update_task_done(&pool, &task.job_id, &task.task_id, JsonValue::default())
                .await
                .unwrap()
        );

        idx += 1;
    }

    // grab the final task to perform finalization work..
    let final_task = taskdb::request_work(&pool, aux_worker_type)
        .await
        .unwrap()
        .unwrap();
    assert_eq!(final_task.task_id, "finalize");
    assert!(
        taskdb::update_task_done(
            &pool,
            &final_task.job_id,
            &final_task.task_id,
            JsonValue::default(),
        )
        .await
        .unwrap()
    );

    for task in test_helpers::get_tasks(&pool).await.unwrap() {
        // println!("{:?}", task);
        assert_eq!(task.state, TaskState::Done);
    }

    Ok(())
}
