-- Install support for UUID generation Note: uuid_generate_v4() generates
-- random UUIDS with system CRNG
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

-- Enumeration for job state
CREATE TYPE job_state AS ENUM (
  'running', -- A job is created and running
  'done',    -- A job is complete
  'failed'   -- A job has failed
);

-- Enumeration for task state
CREATE TYPE task_state AS ENUM (
  'pending', -- A task is waiting on the completion of prerequisites
  'ready',   -- A task is ready to assign to a worker
  'running', -- task is actively running
  'done',    -- A task is complete
  'failed'   -- A task has failed (max retries or explicit failure)
);

/*
A stream represents a set of prioritization rules that apply to set of tasks
*/
CREATE TABLE streams (
  -- Set at stream creation
  id UUID NOT NULL DEFAULT uuid_generate_v4() PRIMARY KEY,
  worker_type TEXT NOT NULL, -- What type of worker is this stream for
  reserved INTEGER NOT NULL, -- How many 'reserved' workers for this stream
  be_mult REAL NOT NULL,     -- Best effort multiplier, 2.0 gets twice as much as 1.0
  user_id TEXT NOT NULL,     -- User identifier that owns this stream

  -- Managed by triggers
  running INTEGER NOT NULL DEFAULT(0),  -- How many running tasks in this stream
  ready INTEGER NOT NULL DEFAULT(0),    -- How many 'ready' tasks in this stream

  -- Computed
  -- The priority of a stream is negative if it's within it's reserved range
  -- and positive if it's in best effort, and infinite if there is no work
  -- to do right now.  So ordering by priority gets the right stream
  priority REAL NOT NULL GENERATED ALWAYS AS (
    CASE WHEN ready=0 THEN 'infinity'
         WHEN running >= reserved THEN (running - reserved) / be_mult
         ELSE (running - reserved) * 1.0 / reserved
    END) STORED
);

-- Make sure we can find streams quickly by priority
CREATE INDEX streams_by_priority ON streams USING btree (worker_type, priority);

/*
A job represent a full workflow created by a user, and consists of a series of
tasks that represent individual discrete items of work.
*/
CREATE TABLE jobs (
  id UUID NOT NULL DEFAULT uuid_generate_v4() PRIMARY KEY,
  state job_state NOT NULL,
  error TEXT,            -- Error message if state = 'failed', NULL otherwise
  user_id TEXT NOT NULL, -- User identifier that owns this job
  reported BOOLEAN NOT NULL DEFAULT(FALSE) -- Optional field for post-processing in batches to report metrics for each done/failed job
);

/*
A task is an item of work, and is local to a job.  Within a job, a task is
identified by string based identifier.  Task should be 'equivalently
idempotent', in that rerunning them should result in 'logically' the same
output.  For example, a ZKP may not be identical due to randomness used in that
protocol, but should prove the same thing.  It is important that if a given
task creates more tasks, the naming should consistent, i.e. 'prove-0' rather
than a UUID so that if tasks that make tasks are rerun, duplicate tasks don't
get added.
 */
CREATE TABLE tasks (
  -- Task definition (do not changes after create)
  job_id UUID NOT NULL,  -- The job this task is part of
  task_id TEXT NOT NULL, -- Name of task within the job
  stream_id UUID NOT NULL,  -- Which stream to run this task on
  task_def jsonb NOT NULL,  -- JSON blob that defines this task
  prerequisites jsonb NOT NULL, -- JSON list of prerequisites
  state task_state NOT NULL,
  created_at TIMESTAMP NOT NULL DEFAULT NOW(), -- When a task was first made

  -- Task running state
  started_at TIMESTAMP, -- When a task most recently began running
  updated_at TIMESTAMP, -- When a task was most recently updates (failed | done)
  waiting_on INTEGER NOT NULL,  -- How many prereqs still remain
  progress REAL NOT NULL DEFAULT 0.0, -- % of task completion (0 - 1.0)
  retries INTEGER NOT NULL DEFAULT 0, -- How many times has the task been retried
  max_retries INTEGER NOT NULL DEFAULT 0, -- Max number of retries before a hard fault
  timeout_secs INTEGER NOT NULL, -- Max number of seconds before failing / retrying the job

  -- Task 'output'
  output jsonb,  -- JSON blob that is the task's output
  error TEXT,    -- An error message if a task failed

  PRIMARY KEY (job_id, task_id),
  FOREIGN KEY (job_id) REFERENCES jobs(id),
  FOREIGN KEY (stream_id) REFERENCES streams(id)
);

-- Tasks within a given stream are 'fifo' order
CREATE INDEX tasks_by_stream ON tasks using btree (state, stream_id, created_at);
-- Look up all states in a jobs to count unresolved
CREATE INDEX tasks_state ON tasks USING btree (job_id, state);
CREATE INDEX tasks_job_task_state_idx ON tasks (job_id, task_id, state);

-- The linking table that manages task dependencies
CREATE TABLE task_deps (
  job_id UUID NOT NULL, -- Job ID both tasks are part of
  pre_task_id TEXT NOT NULL, -- Task ID of task that must run first
  post_task_id TEXT NOT NULL, -- Task ID of task that waits on pre

  FOREIGN KEY (job_id) REFERENCES jobs(id),
  FOREIGN KEY (job_id, pre_task_id) REFERENCES tasks(job_id, task_id),
  FOREIGN KEY (job_id, post_task_id) REFERENCES tasks(job_id, task_id)
);

CREATE INDEX task_deps_idx ON task_deps USING btree (job_id, pre_task_id, post_task_id);

-- Make a trigger that keeps the summary data in streams valid
-- such that the priority can be calculated correctly
CREATE OR REPLACE FUNCTION maint_streams() RETURNS TRIGGER as $$
DECLARE
    delta_ready INTEGER := 0;
    delta_running INTEGER := 0;
    stream_id UUID;
BEGIN
  -- Set stream ID from whichever version is set
  IF OLD.stream_id IS NOT NULL THEN stream_id = OLD.stream_id; END IF;
  IF NEW.stream_id IS NOT NULL THEN stream_id = NEW.stream_id; END IF;

  -- Collect deltas
  IF OLD.state = 'ready' THEN delta_ready = delta_ready - 1; END IF;
  IF OLD.state = 'running' THEN delta_running = delta_running - 1; END IF;
  IF NEW.state = 'ready' THEN delta_ready = delta_ready + 1; END IF;
  IF NEW.state = 'running' THEN delta_running = delta_running + 1; END IF;

  -- Apply deltas
  IF delta_ready != 0 OR delta_running != 0 THEN
    UPDATE streams SET
        ready = GREATEST(ready + delta_ready, 0),
        running = GREATEST(running + delta_running, 0)
    WHERE id = stream_id;
  END IF;

  RETURN NULL;
END;
$$ LANGUAGE plpgsql;
CREATE TRIGGER maint_streams_trigger
AFTER INSERT OR UPDATE ON tasks
FOR EACH ROW EXECUTE FUNCTION maint_streams();

-- Make a new stream, will always have no tasks initially
CREATE OR REPLACE FUNCTION create_stream(
    worker_type TEXT,
    reserved INTEGER,
    be_mult REAL,
    user_id TEXT)
  RETURNS UUID as $$
DECLARE
  new_id UUID;
BEGIN
  INSERT INTO streams (worker_type, reserved, be_mult, user_id)
         VALUES (worker_type, reserved, be_mult, user_id) RETURNING (id)
         INTO new_id;
  RETURN new_id;
END
$$ LANGUAGE plpgsql;

-- Create a new task with an initialization job called 'init' and a definition,
-- max_retries is set for the 'init' task
CREATE OR REPLACE FUNCTION create_job(
    stream_id UUID,
    task_def jsonb,
    max_retries INTEGER,
    timeout_secs INTEGER,
    user_id TEXT)
  RETURNS UUID as $$
DECLARE
  new_id UUID;
BEGIN
  INSERT INTO jobs (state, user_id) VALUES ('running', user_id) RETURNING (id) INTO new_id;
  INSERT INTO tasks (job_id, task_id, stream_id, task_def, prerequisites, max_retries, timeout_secs, state, waiting_on)
         VALUES (new_id, 'init', stream_id, task_def, '[]', max_retries, timeout_secs, 'ready', 0);
  RETURN new_id;
END;
$$ LANGUAGE plpgsql;

-- Create a non-init task in a job, with optional prerequisites
-- The prerequisites are a json list of strings
CREATE OR REPLACE PROCEDURE create_task(
    job_id_var UUID,
    task_id_var TEXT,
    stream_id UUID,
    task_def jsonb,
    prerequisites jsonb,
    max_retries INTEGER,
    timeout_secs INTEGER) as $$
DECLARE
    not_done_count INTEGER;
BEGIN
  -- TODO / QUESTION:
  -- Should we fail on create_task() for a job_id.state = 'done'?

  INSERT INTO tasks (job_id, task_id, stream_id, task_def, prerequisites, max_retries, timeout_secs, state, waiting_on)
         VALUES (job_id_var, task_id_var, stream_id, task_def, prerequisites, max_retries, timeout_secs, 'pending', 0);
  INSERT INTO task_deps
  SELECT job_id_var, value#>>'{}', task_id_var FROM jsonb_array_elements(prerequisites);

  SELECT COUNT(*) INTO not_done_count FROM task_deps, tasks
         WHERE task_deps.job_id = job_id_var and
               task_deps.post_task_id = task_id_var and
               tasks.job_id = job_id_var AND
               tasks.task_id = task_deps.pre_task_id and
               tasks.state != 'done';

  UPDATE tasks SET
      waiting_on = not_done_count,
      state = (CASE not_done_count WHEN 0 THEN 'ready' ELSE 'pending' END)::task_state
  WHERE job_id = job_id_var AND task_id = task_id_var;
END;
$$ LANGUAGE plpgsql;

-- Requests a new task from a given worker type, marking the task as running.
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
  SELECT id INTO stream from streams where streams.worker_type = in_worker_type ORDER BY priority LIMIT 1;
  IF stream IS NOT NULL THEN
    SELECT INTO found_job_id, found_task_id, found_definition, found_max_retries tasks.job_id, tasks.task_id, tasks.task_def, tasks.max_retries
      FROM tasks WHERE tasks.stream_id = stream AND tasks.state = 'ready'
      ORDER BY created_at ASC
      LIMIT 1
      FOR UPDATE SKIP LOCKED;
  END IF;

  IF found_job_id is NOT NULL THEN
    UPDATE tasks SET state = 'running', started_at = now() WHERE tasks.state = 'ready' AND tasks.job_id = found_job_id AND tasks.task_id = found_task_id;
    IF FOUND THEN
      job_id := found_job_id;
      task_id := found_task_id;
      task_def := found_definition;
      max_retries := found_max_retries;
      prereqs := '[]';
      RETURN NEXT;
    END IF;
  END IF;
END;
$$ LANGUAGE plpgsql;

-- Update methods
-- TODO: Notes:
-- retry considerations:
-- - progress: dueling workers, if progress goes backwards, ignore that
--              no worker should ever un-done a task. Work should terminate if their task is getting 'done'd

-- Updates an existing task as successful/done
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
    UPDATE tasks SET
      waiting_on = waiting_on - 1,
      state = (CASE waiting_on WHEN 1 THEN 'ready' ELSE 'pending' END)::task_state
    FROM task_deps WHERE
      tasks.job_id = job_id_var AND
      task_deps.job_id = job_id_var AND
      task_deps.pre_task_id = task_id_var AND
      task_deps.post_task_id = tasks.task_id AND
      tasks.state != 'failed';

    SELECT COUNT(*) INTO unresolved FROM tasks WHERE job_id = job_id_var AND state != 'done';
    IF unresolved = 0 THEN
      UPDATE jobs SET state = 'done' WHERE id = job_id_var;
    END IF;
  END IF;

  RETURN found_done_task;
END;
$$ LANGUAGE plpgsql;

-- Updates an existing task as failed
CREATE OR REPLACE FUNCTION update_task_failed(
  job_id_var UUID,
  task_id_var TEXT,
  error_var TEXT
)
RETURNS BOOLEAN as $$
BEGIN
  -- Set the error on the faulted task itself
  UPDATE tasks SET
    state = 'failed',
    error = error_var,
    progress = 1.0,
    updated_at = now()
  WHERE
    job_id = job_id_var AND
    task_id = task_id_var AND
    state IN ('ready', 'running', 'pending');

  IF FOUND THEN
    UPDATE jobs SET
      state = 'failed',
      error = error_var
    WHERE
      id = job_id_var AND
      state != 'failed';

    RETURN TRUE;
  ELSE
    RETURN FALSE;
  END IF;
END;
$$ LANGUAGE plpgsql;

-- Updates an existing task progress
CREATE OR REPLACE FUNCTION update_task_progress(
  job_id_var UUID,
  task_id_var TEXT,
  progress_var REAL
)
RETURNS BOOLEAN as $$
BEGIN
  UPDATE tasks SET
    updated_at = now(),
    progress = GREATEST(progress, progress_var)
    WHERE
      job_id = job_id_var and
      task_id = task_id_var and
      (state = 'ready' OR state = 'running');
  RETURN FOUND;
END;
$$ LANGUAGE plpgsql;

-- Requeue a task by setting it to ready and bump the retry counter
CREATE OR REPLACE FUNCTION update_task_retry(
  job_id_var UUID,
  task_id_var TEXT
)
RETURNS BOOLEAN as $$
DECLARE
  retry_var INTEGER;
  max_retry_var INTEGER;
BEGIN
  UPDATE tasks SET
    updated_at = now(),
    retries = retries + 1,
    progress = 0.0,
    state = 'ready',
    error = ''
    WHERE
      job_id = job_id_var and
      task_id = task_id_var and
      state = 'running'
  RETURNING retries, max_retries INTO retry_var, max_retry_var;
  IF FOUND THEN
    IF retry_var > max_retry_var THEN
      PERFORM update_task_failed(job_id_var, task_id_var, 'retry max hit');
      RETURN FALSE;
    END IF;
    RETURN TRUE;
  ELSE
    RETURN FALSE;
  END IF;
END;
$$ LANGUAGE plpgsql;
