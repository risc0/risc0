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

use std::cmp::Ordering;

#[derive(Debug)]
pub enum PlannerErr {
    PlanNotStartedString,
    PlanFinalized,
}

#[derive(Clone, Debug, Eq, PartialEq)]
pub enum Command {
    Finalize,
    Join,
    Segment,
}

#[derive(Clone, Debug)]
pub struct Task {
    pub task_number: usize,
    pub task_height: u32,
    pub command: Command,
    pub depends_on: Vec<usize>,
    pub segment_idx: Option<u32>,
}

impl Task {
    pub fn new_segment(task_number: usize, segment_idx: u32) -> Self {
        Task {
            task_number,
            task_height: 0,
            command: Command::Segment,
            depends_on: Vec::new(),
            segment_idx: Some(segment_idx),
        }
    }

    pub fn new_join(task_number: usize, task_height: u32, left: usize, right: usize) -> Self {
        Task {
            task_number,
            task_height,
            command: Command::Join,
            depends_on: vec![left, right],
            segment_idx: None,
        }
    }

    pub fn new_finalize(task_number: usize, task_height: u32, depends_on: usize) -> Self {
        Task {
            task_number,
            task_height,
            command: Command::Finalize,
            depends_on: vec![depends_on],
            segment_idx: None,
        }
    }
}

#[derive(Clone, Default)]
pub struct Planner {
    /// All of the tasks in this plan
    tasks: Vec<Task>,

    /// List of current "peaks." Sorted in order of decreasing height.
    ///
    /// A task is a "peak" if (1) it is either a Segment or Join command AND (2) no other join tasks depend on it.
    peaks: Vec<usize>,

    /// Iterator position. Used by `self.next_task()`.
    consumer_position: usize,

    /// Last task in the plan. Set by `self.finish()`.
    last_task: Option<usize>,
}

impl Planner {
    pub fn enqueue_segment(&mut self, segment_idx: u32) -> Result<usize, PlannerErr> {
        if self.last_task.is_some() {
            return Err(PlannerErr::PlanFinalized);
        }

        let task_number = self.next_task_number();
        self.tasks.push(Task::new_segment(task_number, segment_idx));

        let mut new_peak = task_number;
        while let Some(smallest_peak) = self.peaks.last().copied() {
            let new_height = self.get_task(new_peak).task_height;
            let smallest_peak_height = self.get_task(smallest_peak).task_height;

            match new_height.cmp(&smallest_peak_height) {
                Ordering::Less => break,
                Ordering::Equal => {
                    self.peaks.pop();
                    new_peak = self.enqueue_join(smallest_peak, new_peak);
                }
                Ordering::Greater => unreachable!(),
            }
        }
        self.peaks.push(new_peak);

        Ok(task_number)
    }

    pub fn finish(&mut self) -> Result<usize, PlannerErr> {
        // Return error if plan has not yet started
        if self.peaks.is_empty() {
            return Err(PlannerErr::PlanNotStartedString);
        }

        // Finish the plan (if it's not yet finished)
        if self.last_task.is_none() {
            // Join remaining peaks
            while 2 <= self.peaks.len() {
                let peak_0 = self.peaks.pop().unwrap();
                let peak_1 = self.peaks.pop().unwrap();

                let peak_3 = self.enqueue_join(peak_1, peak_0);
                self.peaks.push(peak_3);
            }

            // Add the Finalize task
            self.last_task = Some(self.enqueue_finalize(self.peaks[0]));
        }

        Ok(self.last_task.unwrap())
    }

    pub fn task_count(&self) -> usize {
        self.tasks.len()
    }

    pub fn get_task(&self, task_number: usize) -> &Task {
        if task_number < self.tasks.len() {
            &self.tasks[task_number]
        } else {
            panic!("Invalid task number {task_number}");
        }
    }

    pub fn next_task(&mut self) -> Option<&Task> {
        if self.consumer_position < self.task_count() {
            let out = &self.tasks[self.consumer_position];
            self.consumer_position += 1;
            Some(out)
        } else {
            None
        }
    }

    fn enqueue_join(&mut self, left: usize, right: usize) -> usize {
        let task_number = self.next_task_number();
        let task_height = 1 + u32::max(
            self.get_task(left).task_height,
            self.get_task(right).task_height,
        );
        self.tasks
            .push(Task::new_join(task_number, task_height, left, right));
        task_number
    }

    fn enqueue_finalize(&mut self, depends_on: usize) -> usize {
        let task_number = self.next_task_number();
        let task_height = 1 + self.get_task(depends_on).task_height;
        self.tasks
            .push(Task::new_finalize(task_number, task_height, depends_on));
        task_number
    }

    fn next_task_number(&self) -> usize {
        self.task_count()
    }
}

impl std::fmt::Debug for Planner {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        let mut stack = Vec::new();

        if self.last_task.is_none() {
            writeln!(f, "Still in planning phases ...")?;
        } else {
            stack.push((0, self.last_task.unwrap()));
        }

        while let Some((indent, cursor)) = stack.pop() {
            if indent > 0 {
                write!(f, "\n{}", " ".repeat(indent))?;
            }

            let task = self.get_task(cursor);

            match task.command {
                Command::Finalize => {
                    write!(f, "{:?} Finalize", task.task_number)?;
                    stack.push((indent + 2, task.depends_on[0]));
                }
                Command::Join => {
                    write!(f, "{:?} Join", task.task_number)?;
                    stack.push((indent + 2, task.depends_on[0]));
                    stack.push((indent + 2, task.depends_on[1]));
                }
                Command::Segment => {
                    write!(f, "{:?} Segment", task.task_number)?;
                }
            }
        }

        Ok(())
    }
}
