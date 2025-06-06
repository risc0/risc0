-- Set the below tables to unlogged, which means they are not written to the transaction log
ALTER TABLE task_deps SET UNLOGGED;
ALTER TABLE tasks SET UNLOGGED;
ALTER TABLE streams SET UNLOGGED;

-- Set statistics for the tables, larger statistics means better query planning
ALTER TABLE streams ALTER COLUMN worker_type SET STATISTICS 1000;

ALTER TABLE tasks ALTER COLUMN state SET STATISTICS 1000;

ALTER TABLE task_deps ALTER COLUMN job_id SET STATISTICS 1000;
ALTER TABLE task_deps ALTER COLUMN pre_task_id SET STATISTICS 1000;
ALTER TABLE task_deps ALTER COLUMN post_task_id SET STATISTICS 1000;

-- Set the fillfactor for the tables, which is the percentage of the table that is filled with data
ALTER TABLE task_deps SET (fillfactor = 70);


CREATE OR REPLACE FUNCTION request_work(in_worker_type TEXT)
  RETURNS TABLE (job_id UUID, task_id TEXT, task_def jsonb, prereqs jsonb, max_retries INTEGER) as $$
DECLARE
  stream UUID;
  found_job_id UUID;
  found_task_id TEXT;
  found_definition jsonb;
  found_max_retries INTEGER;
  prereq_outputs jsonb;
BEGIN
  -- Use SKIP LOCKED when selecting the stream to prevent stream-level contention
  SELECT id INTO stream
  FROM streams
  WHERE streams.worker_type = in_worker_type
  ORDER BY priority
  LIMIT 1
  FOR UPDATE SKIP LOCKED;

  IF stream IS NOT NULL THEN
    -- Use a CTE to atomically select and update in one operation
    WITH selected_task AS (
      SELECT tasks.job_id, tasks.task_id, tasks.task_def, tasks.max_retries
      FROM tasks
      WHERE tasks.stream_id = stream
        AND tasks.state = 'ready'
      ORDER BY created_at ASC
      LIMIT 1
      FOR UPDATE SKIP LOCKED
    ),
    update_task AS (
      UPDATE tasks
      SET state = 'running',
          started_at = now()
      FROM selected_task
      WHERE tasks.job_id = selected_task.job_id
        AND tasks.task_id = selected_task.task_id
      RETURNING selected_task.*
    )
    SELECT INTO found_job_id, found_task_id, found_definition, found_max_retries
      update_task.job_id, update_task.task_id, update_task.task_def, update_task.max_retries
    FROM update_task;
  END IF;

  IF found_job_id is NOT NULL THEN
    job_id := found_job_id;
    task_id := found_task_id;
    task_def := found_definition;
    max_retries := found_max_retries;
    prereqs := '[]';
    RETURN NEXT;
  END IF;
END;
$$ LANGUAGE plpgsql;

CREATE INDEX IF NOT EXISTS streams_worker_type_priority_idx ON streams(worker_type, priority);
CREATE INDEX IF NOT EXISTS tasks_stream_state_idx ON tasks(stream_id, state, created_at);
CREATE INDEX IF NOT EXISTS tasks_ready_idx ON tasks(stream_id, created_at) WHERE state = 'ready';

CREATE OR REPLACE FUNCTION update_task_done(
  job_id_var UUID,
  task_id_var TEXT,
  output_var jsonb
)
RETURNS BOOLEAN as $$
DECLARE
  found_done_task BOOLEAN DEFAULT FALSE;
  unresolved INTEGER;
BEGIN
  UPDATE tasks SET
    state = 'done',
    output = output_var,
    updated_at = now(),
    progress = 1.0
    WHERE
      tasks.job_id = job_id_var and
      tasks.task_id = task_id_var and
      (state = 'ready' OR state = 'running');
  found_done_task = FOUND;

  -- Reduce deps if a task is done, and maybe move to ready
  IF found_done_task THEN
    -- 2) In a single updatable CTE, lock and decrement waiting_on for child tasks
    WITH child_tasks AS (
      SELECT tasks.job_id, tasks.task_id, tasks.waiting_on
        FROM tasks
        JOIN task_deps
          ON task_deps.job_id = tasks.job_id
          AND task_deps.post_task_id = tasks.task_id
        WHERE tasks.job_id = job_id_var
          AND task_deps.job_id = job_id_var
          AND task_deps.pre_task_id = task_id_var
          AND tasks.state != 'failed'
        FOR UPDATE            -- <--- row-level lock to prevent concurrency issues
    )
    UPDATE tasks SET
      waiting_on = child_tasks.waiting_on - 1,
      state = (CASE WHEN child_tasks.waiting_on - 1 <= 0
                  THEN 'ready'
                  ELSE 'pending'
              END)::task_state
    FROM child_tasks
    WHERE tasks.job_id = child_tasks.job_id AND
      tasks.task_id = child_tasks.task_id;

    SELECT COUNT(*) INTO unresolved FROM tasks WHERE job_id = job_id_var AND state != 'done';
    IF unresolved = 0 THEN
      UPDATE jobs SET state = 'done' WHERE id = job_id_var;
    END IF;
  END IF;

  RETURN found_done_task;
END;
$$ LANGUAGE plpgsql;
