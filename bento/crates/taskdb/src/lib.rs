// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use serde::{de::DeserializeOwned, Deserialize, Serialize};
pub use sqlx::Error as SqlxError;
use sqlx::{
    types::{JsonValue, Uuid},
    FromRow, PgPool,
};
use thiserror::Error;

pub mod planner;

#[derive(Error, Debug)]
pub enum TaskDbErr {
    #[error("sqlx failure")]
    SqlError(#[from] sqlx::Error),
    #[error("taskdb internal error: {0}")]
    InternalErr(String),
    #[error("migration failure")]
    MigrateErr(#[from] sqlx::migrate::MigrateError),
    #[error("jsonb serialization error, invalid json in DB")]
    JsonErr(#[from] serde_json::Error),
    #[error("Stream be_mult cannot be 0.0")]
    InvalidBeMult,
}

#[derive(sqlx::Type, Deserialize, Serialize, Debug, PartialEq)]
#[sqlx(type_name = "job_state", rename_all = "snake_case")]
pub enum JobState {
    Running,
    Done,
    Failed,
}

impl std::fmt::Display for JobState {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            JobState::Running => write!(f, "RUNNING"),
            JobState::Done => write!(f, "SUCCEEDED"),
            JobState::Failed => write!(f, "FAILED"),
        }
    }
}

#[derive(FromRow)]
pub struct ReadyTaskRaw {
    pub job_id: Option<Uuid>,
    pub task_id: Option<String>,
    pub task_def: Option<JsonValue>,
    pub prereqs: Option<JsonValue>,
    pub max_retries: Option<i32>,
}

pub struct ReadyTask {
    pub job_id: Uuid,
    pub task_id: String,
    pub task_def: JsonValue,
    pub prereqs: JsonValue,
    pub max_retries: i32,
}

/// Initial taskid in a job, defined in the SQL schema from create_job()
pub const INIT_TASK: &str = "init";

impl ReadyTaskRaw {
    // TODO: this function is pretty hacky, is there a better way?
    pub fn get(self) -> Option<ReadyTask> {
        Some(ReadyTask {
            job_id: self.job_id?,
            task_id: self.task_id?,
            task_def: self.task_def?,
            prereqs: self.prereqs?,
            max_retries: self.max_retries?,
        })
    }
}

pub async fn init_db(pool: &PgPool) -> Result<(), TaskDbErr> {
    Ok(sqlx::migrate!("./migrations").run(pool).await?)
}

#[derive(sqlx::Type, Debug, PartialEq)]
#[sqlx(type_name = "task_state", rename_all = "snake_case")]
pub enum TaskState {
    Pending,
    Ready,
    Running,
    Done,
    Failed,
}

impl std::fmt::Display for TaskState {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            TaskState::Pending => write!(f, "Pending"),
            TaskState::Ready => write!(f, "Ready"),
            TaskState::Running => write!(f, "Running"),
            TaskState::Done => write!(f, "Done"),
            TaskState::Failed => write!(f, "Failed"),
        }
    }
}

impl TaskState {}

pub async fn create_stream(
    pool: &PgPool,
    worker_type: &str,
    reserved: i32,
    be_mult: f32,
    user_id: &str,
) -> Result<Uuid, TaskDbErr> {
    if be_mult == 0.0 {
        return Err(TaskDbErr::InvalidBeMult);
    }

    sqlx::query!(
        "SELECT create_stream($1, $2, $3, $4) as id",
        worker_type,
        reserved,
        be_mult,
        user_id,
    )
    .fetch_one(pool)
    .await?
    .id
    .ok_or(TaskDbErr::InternalErr("create_stream result missing id field".into()))
}

pub async fn create_job(
    pool: &PgPool,
    stream_id: &Uuid,
    task_def: &JsonValue,
    max_retries: i32,
    timeout_secs: i32,
    user_id: &str,
) -> Result<Uuid, TaskDbErr> {
    sqlx::query!(
        "SELECT create_job($1, $2, $3, $4, $5) as id",
        stream_id,
        task_def,
        max_retries,
        timeout_secs,
        user_id,
    )
    .fetch_one(pool)
    .await?
    .id
    .ok_or(TaskDbErr::InternalErr("create_job result missing id field".into()))
}

// TODO: fix this clippy allow
#[allow(clippy::too_many_arguments)]
pub async fn create_task(
    pool: &PgPool,
    job_id: &Uuid,
    task_id: &str,
    stream_id: &Uuid,
    task_def: &JsonValue,
    prereqs: &JsonValue,
    max_retries: i32,
    timeout_secs: i32,
) -> Result<(), TaskDbErr> {
    sqlx::query!(
        "CALL create_task($1, $2, $3, $4, $5, $6, $7)",
        job_id,
        task_id,
        stream_id,
        task_def,
        prereqs,
        max_retries,
        timeout_secs,
    )
    .execute(pool)
    .await?;

    Ok(())
}

pub async fn request_work(
    pool: &PgPool,
    worker_type: &str,
) -> Result<Option<ReadyTask>, TaskDbErr> {
    let res = sqlx::query_as!(ReadyTaskRaw, "SELECT * FROM request_work($1)", worker_type)
        .fetch_optional(pool)
        .await?;

    if let Some(task) = res {
        Ok(task.get())
    } else {
        Ok(None)
    }
}

pub async fn update_task_done(
    pool: &PgPool,
    job_id: &Uuid,
    task_id: &str,
    output: JsonValue,
) -> Result<bool, TaskDbErr> {
    sqlx::query!("SELECT * FROM update_task_done($1, $2, $3) as updated", job_id, task_id, output)
        .fetch_one(pool)
        .await?
        .updated
        .ok_or(TaskDbErr::InternalErr("update_task_done failed to return FOUND result".into()))
}

pub async fn update_task_failed(
    pool: &PgPool,
    job_id: &Uuid,
    task_id: &str,
    error: &str,
) -> Result<bool, TaskDbErr> {
    sqlx::query!("SELECT * FROM update_task_failed($1, $2, $3) as updated", job_id, task_id, error)
        .fetch_one(pool)
        .await?
        .updated
        .ok_or(TaskDbErr::InternalErr("update_task_failed failed to return FOUND result".into()))
}

pub async fn update_task_progress(
    pool: &PgPool,
    job_id: &Uuid,
    task_id: &str,
    progress: f32,
) -> Result<bool, TaskDbErr> {
    sqlx::query!(
        "SELECT * FROM update_task_progress($1, $2, $3) as updated",
        job_id,
        task_id,
        progress
    )
    .fetch_one(pool)
    .await?
    .updated
    .ok_or(TaskDbErr::InternalErr("update_task_progress failed to return FOUND result".into()))
}

pub async fn update_task_retry(
    pool: &PgPool,
    job_id: &Uuid,
    task_id: &str,
) -> Result<bool, TaskDbErr> {
    sqlx::query!("SELECT * FROM update_task_retry($1, $2) as updated", job_id, task_id,)
        .fetch_one(pool)
        .await?
        .updated
        .ok_or(TaskDbErr::InternalErr("update_task_retry failed to return FOUND result".into()))
}

// TODO: would be nice to have limit come with a sane default?
pub async fn requeue_tasks(pool: &PgPool, limit: i64) -> Result<usize, TaskDbErr> {
    let mut txn = pool.begin().await?;
    let timed_out = sqlx::query!(
        "SELECT job_id, task_id
        FROM tasks
        WHERE
            state = 'running' AND timeout_secs < EXTRACT(EPOCH FROM (now() - GREATEST(started_at, updated_at)))
        LIMIT $1",
        limit
    )
    .fetch_all(&mut *txn)
    .await?;

    for elm in timed_out.iter() {
        sqlx::query!(
            "SELECT * FROM update_task_retry($1, $2) as updated",
            elm.job_id,
            elm.task_id,
        )
        .fetch_one(&mut *txn)
        .await?
        .updated
        .ok_or(TaskDbErr::InternalErr(
            "update_task_retry failed to return FOUND result".into(),
        ))?;
    }

    txn.commit().await?;

    Ok(timed_out.len())
}

pub async fn get_job_state(
    pool: &PgPool,
    job_id: &Uuid,
    user_id: &str,
) -> Result<JobState, TaskDbErr> {
    let row: JobState = sqlx::query_scalar("SELECT state FROM jobs WHERE id = $1 AND user_id = $2")
        .bind(job_id)
        .bind(user_id)
        .fetch_one(pool)
        .await?;

    Ok(row)
}

pub async fn get_job_unresolved(pool: &PgPool, job_id: &Uuid) -> Result<i64, TaskDbErr> {
    let unresolved: i64 =
        sqlx::query_scalar("SELECT COUNT(*) FROM tasks WHERE job_id = $1 AND state != $2")
            .bind(job_id)
            .bind(TaskState::Done)
            .fetch_one(pool)
            .await?;
    Ok(unresolved)
}

pub async fn get_concurrent_jobs(pool: &PgPool, user_id: &str) -> Result<i64, TaskDbErr> {
    let job_count: i64 =
        sqlx::query_scalar("SELECT COUNT(*) FROM jobs WHERE user_id = $1 AND state = 'running'")
            .bind(user_id)
            .fetch_one(pool)
            .await?;
    Ok(job_count)
}

pub async fn get_stream(
    pool: &PgPool,
    user_id: &str,
    worker_type: &str,
) -> Result<Option<Uuid>, TaskDbErr> {
    let stream_id: Option<Uuid> =
        sqlx::query_scalar("SELECT id FROM streams WHERE user_id = $1 and worker_type = $2")
            .bind(user_id)
            .bind(worker_type)
            .fetch_optional(pool)
            .await?;

    Ok(stream_id)
}

pub async fn get_job_time(pool: &PgPool, job_id: &Uuid) -> Result<f64, TaskDbErr> {
    let elapsed: f64 = sqlx::query_scalar(
        "
        SELECT
            EXTRACT(EPOCH FROM (MAX(updated_at) - MIN(started_at)))::float8 AS elapsed_sec
        FROM tasks WHERE
            job_id = $1",
    )
    .bind(job_id)
    .fetch_one(pool)
    .await?;

    Ok(elapsed)
}

pub async fn get_job_failure(pool: &PgPool, job_id: &Uuid) -> Result<String, TaskDbErr> {
    let error: String = sqlx::query_scalar(
        "SELECT error FROM tasks WHERE job_id = $1 AND state = 'failed' AND error <> ''",
    )
    .bind(job_id)
    .fetch_one(pool)
    .await?;
    Ok(error)
}

pub async fn get_task_output<T>(pool: &PgPool, job_id: &Uuid, task_id: &str) -> Result<T, TaskDbErr>
where
    T: DeserializeOwned,
{
    let output: serde_json::Value = sqlx::query_scalar(
        "SELECT output FROM tasks WHERE job_id = $1 AND task_id = $2 AND state = 'done'",
    )
    .bind(job_id)
    .bind(task_id)
    .fetch_one(pool)
    .await?;

    Ok(serde_json::from_value(output)?)
}

/// Deletes a job and all its dependant table entries (tasks / task_deps)
pub async fn delete_job(pool: &PgPool, job_id: &Uuid) -> Result<(), TaskDbErr> {
    let mut txn = pool.begin().await?;

    sqlx::query("DELETE FROM task_deps WHERE job_id = $1").bind(job_id).execute(&mut *txn).await?;

    sqlx::query("DELETE FROM tasks WHERE job_id = $1").bind(job_id).execute(&mut *txn).await?;

    sqlx::query("DELETE FROM jobs WHERE id = $1").bind(job_id).execute(&mut *txn).await?;

    txn.commit().await?;

    Ok(())
}

/// Helpers for unit / integration tests
///
/// Not indented to be used outside of internal testing framework.
// TODO: Remove from the public API but allow usage in integration tests like e2e.rs?
pub mod test_helpers {
    use super::*;
    use sqlx::types::chrono::NaiveDateTime;

    // Testing types for manual SELECT's to inspect post-creation results

    // TODO: Explore using a ORM to generate our types
    #[derive(Debug)]
    pub struct Job {
        pub id: Option<Uuid>,
        pub state: Option<JobState>,
        pub error: Option<String>,
        pub user_id: String,
    }

    #[derive(Debug)]
    pub struct Task {
        pub job_id: Uuid,
        pub task_id: String,
        pub stream_id: Uuid,
        pub task_def: JsonValue,
        pub prerequisites: JsonValue,
        pub state: TaskState,
        pub created_at: NaiveDateTime,
        pub started_at: Option<NaiveDateTime>,
        pub updated_at: Option<NaiveDateTime>,
        pub waiting_on: i32,
        pub progress: f32,
        pub retries: i32,
        pub max_retries: i32,
        pub timeout_secs: i32,
        pub output: Option<JsonValue>,
        pub error: Option<String>,
    }

    pub async fn get_task(pool: &PgPool, job_id: &Uuid, task_id: &str) -> Result<Task, TaskDbErr> {
        Ok(sqlx::query_as!(
            Task,
            r#"
            SELECT
                job_id,
                task_id,
                stream_id,
                task_def,
                prerequisites,
                state as "state: _",
                created_at,
                started_at,
                updated_at,
                waiting_on,
                progress,
                retries,
                max_retries,
                timeout_secs,
                output,
                error
            FROM tasks WHERE job_id = $1 AND task_id = $2"#,
            job_id,
            task_id,
        )
        .fetch_one(pool)
        .await?)
    }

    pub async fn get_tasks(pool: &PgPool) -> Result<Vec<Task>, TaskDbErr> {
        // NOTE: we have to select out all the rows due to:
        // https://github.com/launchbadge/sqlx/issues/1004#issuecomment-764921020
        // TODO: work around enums not correctly working?
        Ok(sqlx::query_as!(
            Task,
            r#"
            SELECT
                job_id,
                task_id,
                stream_id,
                task_def,
                prerequisites,
                state as "state: _",
                created_at,
                started_at,
                updated_at,
                waiting_on,
                progress,
                retries,
                max_retries,
                timeout_secs,
                output,
                error
            FROM tasks"#
        )
        .fetch_all(pool)
        .await?)
    }

    pub async fn get_job(pool: &PgPool, job_id: &Uuid) -> Result<Job, TaskDbErr> {
        Ok(sqlx::query_as!(
            Job,
            r#"SELECT id, state as "state: _", error, user_id FROM jobs WHERE id = $1"#,
            job_id
        )
        .fetch_one(pool)
        .await?)
    }

    pub async fn cleanup(pool: &PgPool) {
        let mut tx = pool.begin().await.unwrap();
        sqlx::query("DELETE FROM task_deps").execute(&mut *tx).await.unwrap();
        sqlx::query("DELETE FROM tasks").execute(&mut *tx).await.unwrap();
        sqlx::query("DELETE FROM jobs").execute(&mut *tx).await.unwrap();
        sqlx::query("DELETE FROM streams").execute(&mut *tx).await.unwrap();

        tx.commit().await.unwrap();
    }
}

#[cfg(test)]
mod tests {
    use super::{
        test_helpers::{get_job, get_task, get_tasks, Task},
        *,
    };

    #[sqlx::test()]
    async fn create_stream_test(pool: PgPool) -> sqlx::Result<()> {
        let worker_type = "executor";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, "user1").await.unwrap();
        let stream = sqlx::query!("SELECT * FROM streams WHERE id = $1", stream_id)
            .fetch_one(&pool)
            .await
            .unwrap();

        assert_eq!(stream.id, stream_id);
        assert_eq!(stream.reserved, 1);
        assert_eq!(stream.be_mult, 1.0);
        assert_eq!(stream.running, 0);
        assert_eq!(stream.ready, 0);
        assert_eq!(stream.priority, f32::INFINITY);

        Ok(())
    }

    #[sqlx::test()]
    async fn create_stream_invalid(pool: PgPool) -> sqlx::Result<()> {
        let worker_type = "executor";
        let res = create_stream(&pool, worker_type, 1, 0.0, "user1").await;
        assert!(matches!(res, Err(TaskDbErr::InvalidBeMult)));

        Ok(())
    }

    #[sqlx::test()]
    async fn create_job_test(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let task_def = serde_json::json!({"member": "data"});
        let stream_id = create_stream(&pool, "CPU", 1, 1.0, user_id).await.unwrap();
        let job_id = create_job(&pool, &stream_id, &task_def, 0, 100, user_id).await.unwrap();

        let job = get_job(&pool, &job_id).await.unwrap();

        assert_eq!(job.state.unwrap(), JobState::Running);
        assert_eq!(job.error, None);
        assert_eq!(get_job_unresolved(&pool, &job_id).await.unwrap(), 1);
        assert_eq!(job.user_id, user_id);

        Ok(())
    }

    #[sqlx::test()]
    async fn create_job_invalid(pool: PgPool) -> sqlx::Result<()> {
        let task_def = serde_json::json!({"member": "data"});
        let stream_id = Uuid::parse_str("a1a2a3a4b1b2c1c2d1d2d3d4d5d6d7d8").unwrap();
        let res = create_job(&pool, &stream_id, &task_def, 0, 100, "user1").await;

        assert!(res.is_err());
        let err = res.err().unwrap();

        assert!(format!("{:?}", err).contains("violates foreign key constraint"));
        Ok(())
    }

    #[sqlx::test()]
    async fn create_task_test(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let stream_id = create_stream(&pool, "CPU", 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let init_timeout = 100;
        let job_id =
            create_job(&pool, &stream_id, &task_def, 0, init_timeout, user_id).await.unwrap();

        let tasks = get_tasks(&pool).await.unwrap();
        assert_eq!(tasks.len(), 1);

        let init: &Task = &tasks[0];
        assert_eq!(init.task_id, INIT_TASK);
        assert_eq!(init.state, TaskState::Ready);

        let task_name = "test_task";
        let task_def = serde_json::json!({"member": "data"});
        let prereqs = serde_json::json!([]);

        let task_timeout = 10;
        create_task(&pool, &job_id, task_name, &stream_id, &task_def, &prereqs, 0, task_timeout)
            .await
            .unwrap();

        // Technically we should call update_task here to complete the init task after emitting
        // the new sub-task, but in order to only test 1 new method per unit test I left it out.

        let tasks = get_tasks(&pool).await.unwrap();

        // 1 for the task and 1 for the init
        assert_eq!(tasks.len(), 2);
        let init: &Task = &tasks[0];
        assert_eq!(init.timeout_secs, init_timeout);

        let task: &Task = &tasks[1];
        assert_eq!(task.task_id, task_name);
        assert_eq!(task.state, TaskState::Ready);
        assert_eq!(task.timeout_secs, task_timeout);

        let _job = get_job(&pool, &task.job_id).await.unwrap();
        assert_eq!(get_job_unresolved(&pool, &job_id).await.unwrap(), 2);

        Ok(())
    }

    #[sqlx::test()]
    async fn request_work_test(pool: PgPool) -> sqlx::Result<()> {
        let worker_type = "CPU";
        let user_id = "user1";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let _job_id = create_job(&pool, &stream_id, &task_def, 0, 100, user_id).await.unwrap();

        let work_item = request_work(&pool, worker_type).await.unwrap();
        let work_item = work_item.unwrap();

        assert_eq!(work_item.task_id, INIT_TASK);
        assert!(work_item.prereqs.as_array().unwrap().is_empty());
        assert_eq!(work_item.task_def.get("init").unwrap().as_str().unwrap(), "test");

        Ok(())
    }

    #[sqlx::test()]
    async fn update_task(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let job_id = create_job(&pool, &stream_id, &task_def, 0, 100, user_id).await.unwrap();

        let init = request_work(&pool, worker_type).await.unwrap().unwrap();

        let output_res_value = "SUCCESS";
        let output_res = serde_json::json!({"result": output_res_value});
        assert!(update_task_done(&pool, &job_id, &init.task_id, output_res).await.unwrap());

        let tasks = get_tasks(&pool).await.unwrap();

        assert_eq!(tasks.len(), 1);
        let init = &tasks[0];

        assert!(init.error.is_none());
        assert_eq!(
            init.output.as_ref().unwrap().get("result").unwrap().as_str().unwrap(),
            output_res_value
        );
        assert_eq!(init.state, TaskState::Done);
        assert_eq!(init.progress, 1.0);
        assert_eq!(init.retries, 0);
        assert_eq!(init.waiting_on, 0);

        let job = get_job(&pool, &init.job_id).await.unwrap();
        assert_eq!(job.state.unwrap(), JobState::Done);
        assert_eq!(get_job_unresolved(&pool, &job_id).await.unwrap(), 0);

        let res = request_work(&pool, worker_type).await.unwrap();
        assert!(res.is_none());

        Ok(())
    }

    #[sqlx::test()]
    async fn update_task_retry_test(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});

        let retry_max = 1;
        let _job_id =
            create_job(&pool, &stream_id, &task_def, retry_max, 100, user_id).await.unwrap();
        let task = request_work(&pool, worker_type).await.unwrap().unwrap();

        let retry_task_id = task.task_id.clone();

        // Requeue the work
        assert!(update_task_retry(&pool, &task.job_id, &task.task_id).await.unwrap());

        let task = request_work(&pool, worker_type).await.unwrap().unwrap();
        let task_raw = get_task(&pool, &task.job_id, &task.task_id).await.unwrap();
        assert_eq!(task_raw.error.unwrap(), "");
        assert_eq!(task_raw.retries, 1);
        assert_eq!(task_raw.max_retries, 1);
        assert_eq!(task_raw.progress, 0.0);
        assert_eq!(task_raw.state, TaskState::Running);
        assert_eq!(task_raw.task_id, retry_task_id);

        assert_eq!(get_job_unresolved(&pool, &task_raw.job_id).await.unwrap(), 1);
        let job = get_job(&pool, &task_raw.job_id).await.unwrap();
        assert_eq!(job.state.unwrap(), JobState::Running);

        // Attempt to retry over max_retries and fail the job
        assert!(!update_task_retry(&pool, &task.job_id, &task.task_id).await.unwrap());

        assert!(request_work(&pool, worker_type).await.unwrap().is_none());
        let task_raw = get_task(&pool, &task.job_id, &task.task_id).await.unwrap();
        assert_eq!(task_raw.state, TaskState::Failed);

        let job = get_job(&pool, &task_raw.job_id).await.unwrap();
        assert_eq!(get_job_unresolved(&pool, &task_raw.job_id).await.unwrap(), 1);
        assert_eq!(job.error.unwrap(), "retry max hit");
        assert_eq!(job.state.unwrap(), JobState::Failed);

        Ok(())
    }

    #[sqlx::test()]
    async fn update_task_invalid(pool: PgPool) -> sqlx::Result<()> {
        // Setup
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let _job_id = create_job(&pool, &stream_id, &task_def, 0, 100, user_id).await.unwrap();
        let task = request_work(&pool, worker_type).await.unwrap().unwrap();

        // Test that you can't update a task to done when its already done
        assert!(update_task_done(&pool, &task.job_id, &task.task_id, JsonValue::default())
            .await
            .unwrap());
        assert!(!update_task_done(&pool, &task.job_id, &task.task_id, JsonValue::default())
            .await
            .unwrap());

        // Validate you can't fail a 'done' task
        assert!(!update_task_failed(&pool, &task.job_id, &task.task_id, "").await.unwrap());
        // Validate you can't update progress on a 'done' task
        assert!(!update_task_progress(&pool, &task.job_id, &task.task_id, 0.5).await.unwrap());

        Ok(())
    }

    #[sqlx::test()]
    async fn update_task_prog_failed(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let job_id = create_job(&pool, &stream_id, &task_def, 0, 100, user_id).await.unwrap();

        let init = request_work(&pool, worker_type).await.unwrap().unwrap();

        let task_name = "test_task";
        let task_def = serde_json::json!({"member": "data"});
        let prereqs = serde_json::json!([]);
        create_task(&pool, &job_id, task_name, &stream_id, &task_def, &prereqs, 0, 10)
            .await
            .unwrap();

        assert!(update_task_done(&pool, &job_id, &init.task_id, JsonValue::default())
            .await
            .unwrap());

        let task = request_work(&pool, worker_type).await.unwrap().unwrap();

        assert_eq!(task.task_id, task_name);
        assert_eq!(task.job_id, job_id);

        let progress = 0.5;
        assert!(update_task_progress(&pool, &task.job_id, &task.task_id, progress).await.unwrap());

        let task_info = get_task(&pool, &task.job_id, &task.task_id).await.unwrap();
        assert_eq!(task_info.state, TaskState::Running);
        assert_eq!(task_info.progress, 0.5);

        let error_msg = "it_broke";
        assert!(update_task_failed(&pool, &task.job_id, &task.task_id, error_msg).await.unwrap());

        // Check the main task failed correctly
        let task_info = get_task(&pool, &task.job_id, &task.task_id).await.unwrap();
        assert_eq!(task_info.progress, 1.0);
        assert_eq!(task_info.state, TaskState::Failed);
        assert_eq!(task_info.error.unwrap(), error_msg);

        // Check the job failed as expected
        let job = get_job(&pool, &task_info.job_id).await.unwrap();
        assert_eq!(get_job_unresolved(&pool, &job_id).await.unwrap(), 1);
        assert_eq!(job.state.unwrap(), JobState::Failed);
        assert_eq!(job.error.unwrap(), error_msg);

        // Check the 'init' task that is done is still marked as 'done'
        let init_task = get_task(&pool, &init.job_id, &init.task_id).await.unwrap();
        assert_eq!(init_task.state, TaskState::Done);

        Ok(())
    }

    #[sqlx::test()]
    async fn prereqs(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});

        // Start and grab init task
        let job_id = create_job(&pool, &stream_id, &task_def, 0, 100, user_id).await.unwrap();
        let init = request_work(&pool, worker_type).await.unwrap().unwrap();

        // Place two segments and a join task into the task queue
        let task_1_name = "segment_1";
        let task_def = JsonValue::default();
        let prereqs = serde_json::json!([]);
        create_task(&pool, &job_id, task_1_name, &stream_id, &task_def, &prereqs, 0, 10)
            .await
            .unwrap();

        let task_2_name = "segment_2";
        let task_def = JsonValue::default();
        let prereqs = serde_json::json!([]);
        create_task(&pool, &job_id, task_2_name, &stream_id, &task_def, &prereqs, 0, 10)
            .await
            .unwrap();

        let join_name = "join_3";
        let task_def = JsonValue::default();
        let prereqs = serde_json::json!([task_1_name, task_2_name]);
        create_task(&pool, &job_id, join_name, &stream_id, &task_def, &prereqs, 0, 10)
            .await
            .unwrap();

        // Close the init task
        assert!(update_task_done(&pool, &job_id, &init.task_id, JsonValue::default())
            .await
            .unwrap());

        // Validate the pending / waiting on fields of the join
        let join_task = get_task(&pool, &job_id, join_name).await.unwrap();
        assert_eq!(join_task.waiting_on, 2);
        assert_eq!(join_task.state, TaskState::Pending);

        // Close the segment tasks
        assert!(update_task_done(&pool, &job_id, task_1_name, JsonValue::default()).await.unwrap());
        let join_task = get_task(&pool, &job_id, join_name).await.unwrap();
        assert_eq!(join_task.waiting_on, 1);
        assert_eq!(join_task.state, TaskState::Pending);

        assert!(update_task_done(&pool, &job_id, task_2_name, JsonValue::default()).await.unwrap());

        // Validate that the task is now ready
        let join_task = get_task(&pool, &job_id, join_name).await.unwrap();
        assert_eq!(join_task.waiting_on, 0);
        assert_eq!(join_task.state, TaskState::Ready);

        Ok(())
    }

    #[sqlx::test()]
    async fn prereq_waiting_on(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});

        // Start and grab init task
        let job_id = create_job(&pool, &stream_id, &task_def, 0, 100, user_id).await.unwrap();

        let task_def = JsonValue::default();
        let prereqs = serde_json::json!(["init"]);
        create_task(&pool, &job_id, "task_1", &stream_id, &task_def, &prereqs, 0, 10)
            .await
            .unwrap();

        let task_def = serde_json::json!({"init": "test"});
        let job_id = create_job(&pool, &stream_id, &task_def, 0, 100, user_id).await.unwrap();

        let final_task_id = "task_2";
        let task_def = JsonValue::default();
        let prereqs = serde_json::json!(["init"]);
        create_task(&pool, &job_id, final_task_id, &stream_id, &task_def, &prereqs, 0, 10)
            .await
            .unwrap();
        let init_task = get_task(&pool, &job_id, final_task_id).await.unwrap();
        assert_eq!(init_task.waiting_on, 1);

        Ok(())
    }

    #[sqlx::test()]
    async fn stream_reservations(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id_0 = create_stream(&pool, worker_type, 0, 1.0, user_id).await.unwrap();
        let job_id_0 =
            create_job(&pool, &stream_id_0, &JsonValue::default(), 0, 100, user_id).await.unwrap();

        let stream_id_1 = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let job_id_1 =
            create_job(&pool, &stream_id_1, &JsonValue::default(), 0, 100, user_id).await.unwrap();

        let task = request_work(&pool, worker_type).await.unwrap().unwrap();
        assert_eq!(task.job_id, job_id_1);
        let task = request_work(&pool, worker_type).await.unwrap().unwrap();
        assert_eq!(task.job_id, job_id_0);

        Ok(())
    }

    #[sqlx::test()]
    async fn stream_multiplier(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        // Creates two streams.
        let worker_type = "CPU";
        let stream_id_0 = create_stream(&pool, worker_type, 0, 1.0, user_id).await.unwrap();
        let job_id_0 =
            create_job(&pool, &stream_id_0, &JsonValue::default(), 0, 100, user_id).await.unwrap();

        // populates both streams with two tasks.
        create_task(
            &pool,
            &job_id_0,
            "task2",
            &stream_id_0,
            &JsonValue::default(),
            &serde_json::json!([]),
            0,
            10,
        )
        .await
        .unwrap();
        // starts 'running' a task from each to get the system out of round robin stream selection
        // and into best effort.
        let _task = request_work(&pool, worker_type).await.unwrap().unwrap();

        let stream_id_1 = create_stream(&pool, worker_type, 0, 1.1, user_id).await.unwrap();
        let job_id_1 =
            create_job(&pool, &stream_id_1, &JsonValue::default(), 0, 100, user_id).await.unwrap();
        create_task(
            &pool,
            &job_id_1,
            "task2",
            &stream_id_1,
            &JsonValue::default(),
            &serde_json::json!([]),
            0,
            10,
        )
        .await
        .unwrap();
        let _task = request_work(&pool, worker_type).await.unwrap().unwrap();

        // validate that the higher be_mult stream is emitted first.
        let task = request_work(&pool, worker_type).await.unwrap().unwrap();
        assert_eq!(task.job_id, job_id_1);
        let task = request_work(&pool, worker_type).await.unwrap().unwrap();
        assert_eq!(task.job_id, job_id_0);

        Ok(())
    }

    #[sqlx::test()]
    async fn stream_peak_resv(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        // Create a best effort stream
        let stream_id_0 = create_stream(&pool, worker_type, 0, 1.0, user_id).await.unwrap();
        let job_id_0 =
            create_job(&pool, &stream_id_0, &JsonValue::default(), 0, 100, user_id).await.unwrap();

        // Create a 2 reservation stream
        let worker_type = "CPU";
        let stream_id_2 = create_stream(&pool, worker_type, 2, 1.0, user_id).await.unwrap();
        let job_id_2 =
            create_job(&pool, &stream_id_2, &JsonValue::default(), 0, 100, user_id).await.unwrap();

        // Populate the reservation with 2 tasks
        let task_name = "task2";
        create_task(
            &pool,
            &job_id_2,
            task_name,
            &stream_id_2,
            &JsonValue::default(),
            &serde_json::json!([]),
            0,
            10,
        )
        .await
        .unwrap();

        let tasks = get_tasks(&pool).await.unwrap();
        for task in tasks {
            println!("{task:?}");
        }

        // Validate that the order of work coming from the queue is:
        // - stream_2, init
        // - stream_2, task
        // - HIT PEAK of stream2 reservations
        // - stream_0, init
        let task = request_work(&pool, worker_type).await.unwrap().unwrap();
        assert_eq!(task.job_id, job_id_2);
        assert_eq!(task.task_id, INIT_TASK);
        assert!(update_task_done(&pool, &task.job_id, &task.task_id, JsonValue::default())
            .await
            .unwrap());

        let task = request_work(&pool, worker_type).await.unwrap().unwrap();
        assert_eq!(task.job_id, job_id_2);
        assert_eq!(task.task_id, task_name);
        assert!(update_task_done(&pool, &task.job_id, &task.task_id, JsonValue::default())
            .await
            .unwrap());

        let task = request_work(&pool, worker_type).await.unwrap().unwrap();
        assert_eq!(task.job_id, job_id_0);
        assert_eq!(task.task_id, INIT_TASK);
        assert!(update_task_done(&pool, &task.job_id, &task.task_id, JsonValue::default())
            .await
            .unwrap());

        assert!(request_work(&pool, worker_type).await.unwrap().is_none());

        Ok(())
    }

    #[sqlx::test()]
    async fn async_req_work(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let job_id = create_job(&pool, &stream_id, &task_def, 0, 100, user_id).await.unwrap();

        // Create two workers pooling for work
        let mut tasks = tokio::task::JoinSet::new();
        for _ in 0..2 {
            let pool_cpy = pool.clone();
            tasks.spawn(async move {
                loop {
                    match request_work(&pool_cpy, worker_type).await.unwrap() {
                        Some(task) => break task.task_id,
                        None => tokio::time::sleep(tokio::time::Duration::from_secs(1)).await,
                    }
                }
            });
        }

        for i in 0..2 {
            create_task(
                &pool,
                &job_id,
                &format!("{}", i),
                &stream_id,
                &task_def,
                &serde_json::json!([]),
                0,
                10,
            )
            .await
            .unwrap();
        }

        let mut results = vec![];
        while let Some(res) = tasks.join_next().await {
            let task_id = res.unwrap();
            results.push(task_id);
        }

        // Validate that we have two results and they are different task id's
        assert_eq!(results.len(), 2);
        assert!(results[0] != results[1]);

        Ok(())
    }

    #[sqlx::test()]
    async fn requeue_timeout_test(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let init_timeout = 1;
        let job_id =
            create_job(&pool, &stream_id, &task_def, 1, init_timeout, user_id).await.unwrap();

        // Start the task
        let _task = request_work(&pool, worker_type).await.unwrap().unwrap();

        // wait out the timeout
        std::thread::sleep(std::time::Duration::from_millis((init_timeout * 1000 + 100) as u64));

        // requeue it
        let timed_out_count = requeue_tasks(&pool, 100).await.unwrap();
        assert_eq!(timed_out_count, 1);

        let task = request_work(&pool, worker_type).await.unwrap().unwrap();
        assert_eq!(task.task_def.get("init").unwrap().as_str().unwrap(), "test");
        let init_task = get_task(&pool, &job_id, &task.task_id).await.unwrap();
        assert_eq!(init_task.retries, 1);

        Ok(())
    }

    #[sqlx::test()]
    async fn get_job_state_test(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let init_timeout = 1;
        let job_id =
            create_job(&pool, &stream_id, &task_def, 1, init_timeout, user_id).await.unwrap();

        let state = get_job_state(&pool, &job_id, user_id).await.unwrap();
        assert_eq!(state, JobState::Running);

        Ok(())
    }

    #[sqlx::test()]
    async fn job_count_test(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let init_timeout = 1;
        create_job(&pool, &stream_id, &task_def, 1, init_timeout, user_id).await.unwrap();

        let job_count = get_concurrent_jobs(&pool, user_id).await.unwrap();
        assert_eq!(job_count, 1);

        create_job(&pool, &stream_id, &task_def, 1, init_timeout, "user2").await.unwrap();
        let job_count = get_concurrent_jobs(&pool, user_id).await.unwrap();
        assert_eq!(job_count, 1);

        create_job(&pool, &stream_id, &task_def, 1, init_timeout, user_id).await.unwrap();
        let job_count = get_concurrent_jobs(&pool, user_id).await.unwrap();
        assert_eq!(job_count, 2);

        Ok(())
    }

    #[sqlx::test()]
    async fn get_invalid_job_state(pool: PgPool) -> sqlx::Result<()> {
        let job_id = Uuid::max();
        let res = get_job_state(&pool, &job_id, "test").await;

        assert!(matches!(res, Err(TaskDbErr::SqlError(sqlx::Error::RowNotFound))));

        Ok(())
    }

    #[sqlx::test()]
    async fn get_stream_id_test(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();

        let id = get_stream(&pool, user_id, worker_type).await.unwrap().unwrap();
        assert_eq!(stream_id, id);

        Ok(())
    }

    #[sqlx::test()]
    async fn get_job_time_test(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let init_timeout = 1;
        let job_id =
            create_job(&pool, &stream_id, &task_def, 1, init_timeout, user_id).await.unwrap();

        let task = request_work(&pool, worker_type).await.unwrap().unwrap();
        let res =
            update_task_done(&pool, &job_id, &task.task_id, serde_json::Value::Null).await.unwrap();

        assert!(res);

        let task_time = get_job_time(&pool, &job_id).await.unwrap();
        // TODO better way to just checking the time value?
        assert!(task_time < 1.0);

        Ok(())
    }

    #[sqlx::test()]
    async fn get_job_failure_test(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let init_timeout = 1;
        let job_id =
            create_job(&pool, &stream_id, &task_def, 1, init_timeout, user_id).await.unwrap();

        let test_err = "TEST";
        update_task_failed(&pool, &job_id, INIT_TASK, test_err).await.unwrap();

        let error = get_job_failure(&pool, &job_id).await.unwrap();
        assert_eq!(error, test_err);

        let job_id =
            create_job(&pool, &stream_id, &task_def, 1, init_timeout, user_id).await.unwrap();

        let res = get_job_failure(&pool, &job_id).await;
        assert!(matches!(res, Err(TaskDbErr::SqlError(sqlx::Error::RowNotFound))));

        Ok(())
    }

    #[sqlx::test()]
    async fn get_task_output_test(pool: PgPool) -> sqlx::Result<()> {
        let user_id = "user1";
        let worker_type = "CPU";
        let stream_id = create_stream(&pool, worker_type, 1, 1.0, user_id).await.unwrap();
        let task_def = serde_json::json!({"init": "test"});
        let init_timeout = 1;
        let job_id =
            create_job(&pool, &stream_id, &task_def, 1, init_timeout, user_id).await.unwrap();

        let output = serde_json::json!({"result": "done"});
        update_task_done(&pool, &job_id, INIT_TASK, output).await.unwrap();

        let task_output: serde_json::Value =
            get_task_output(&pool, &job_id, INIT_TASK).await.unwrap();

        assert_eq!(task_output.get("result").unwrap().as_str().unwrap(), "done");

        Ok(())
    }
}

#[sqlx::test()]
async fn delete_job_test(pool: PgPool) -> sqlx::Result<()> {
    let stream_id = create_stream(&pool, "CPU", 1, 1.0, "user1").await.unwrap();
    let job_id =
        create_job(&pool, &stream_id, &serde_json::json!({"init": "test"}), 0, 100, "user1")
            .await
            .unwrap();

    create_task(
        &pool,
        &job_id,
        "test",
        &stream_id,
        &serde_json::json!({"blah": "test"}),
        &serde_json::json!(["init"]),
        0,
        5,
    )
    .await
    .unwrap();

    let count_task_deps: i64 =
        sqlx::query_scalar("SELECT COUNT(*) FROM task_deps WHERE job_id = $1")
            .bind(job_id)
            .fetch_one(&pool)
            .await
            .unwrap();

    assert_eq!(count_task_deps, 1);

    delete_job(&pool, &job_id).await.unwrap();

    let count_task_deps: i64 =
        sqlx::query_scalar("SELECT COUNT(*) FROM task_deps WHERE job_id = $1")
            .bind(job_id)
            .fetch_one(&pool)
            .await
            .unwrap();
    assert_eq!(count_task_deps, 0);

    let count_tasks: i64 = sqlx::query_scalar("SELECT COUNT(*) FROM tasks WHERE job_id = $1")
        .bind(job_id)
        .fetch_one(&pool)
        .await
        .unwrap();
    assert_eq!(count_tasks, 0);

    let count_jobs: i64 = sqlx::query_scalar("SELECT COUNT(*) FROM jobs WHERE id = $1")
        .bind(job_id)
        .fetch_one(&pool)
        .await
        .unwrap();
    assert_eq!(count_jobs, 0);

    Ok(())
}
