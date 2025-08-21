// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{cmp::Ordering, collections::VecDeque};

#[derive(Debug)]
pub enum PlannerErr {
    PlanNotStartedString,
    PlanFinalized,
}

#[derive(Clone, Debug, Eq, PartialEq)]
pub enum Command {
    Segment,
    Join,
    FinalizeJoins,
    Keccak,
    Union,
    FinalizeUnions,
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

    pub fn new_keccak(task_number: usize, segment_idx: u32) -> Self {
        Task {
            task_number,
            task_height: 0,
            command: Command::Keccak,
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

    pub fn new_union(task_number: usize, task_height: u32, left: usize, right: usize) -> Self {
        Task {
            task_number,
            task_height,
            command: Command::Union,
            depends_on: vec![left, right],
            segment_idx: None,
        }
    }

    pub fn new_finalize_joins(task_number: usize, task_height: u32, depends_on: usize) -> Self {
        Task {
            task_number,
            task_height,
            command: Command::FinalizeJoins,
            depends_on: vec![depends_on],
            segment_idx: None,
        }
    }

    pub fn new_finalize_unions(task_number: usize, task_height: u32, depends_on: usize) -> Self {
        Task {
            task_number,
            task_height,
            command: Command::FinalizeUnions,
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

    /// List of current "keccak_peaks." Sorted in order of decreasing height.
    ///
    /// A task is a "keccak_peak" if (1) it is either a Keccak Segment or Union command AND (2) no other union tasks depend on it.
    keccak_peaks: VecDeque<usize>,

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

            tracing::debug!(
                "new height: {new_height} smallest peak height: {smallest_peak_height}"
            );
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

    pub fn enqueue_keccak(&mut self, segment_idx: u32) -> Result<usize, PlannerErr> {
        if self.last_task.is_some() {
            return Err(PlannerErr::PlanFinalized);
        }

        let task_number = self.next_task_number();
        self.tasks.push(Task::new_keccak(task_number, segment_idx));

        let mut new_peak = task_number;
        while let Some(smallest_peak) = self.keccak_peaks.back().copied() {
            let new_height = self.get_task(new_peak).task_height;
            let smallest_peak_height = self.get_task(smallest_peak).task_height;

            tracing::debug!(
                "new height: {new_height} smallest peak height: {smallest_peak_height}"
            );
            match new_height.cmp(&smallest_peak_height) {
                Ordering::Less => break,
                Ordering::Equal => {
                    self.keccak_peaks.pop_back();
                    new_peak = self.enqueue_union(smallest_peak, new_peak);
                }
                Ordering::Greater => unreachable!(),
            }
        }
        self.keccak_peaks.push_back(new_peak);

        Ok(task_number)
    }

    pub fn finish(&mut self) -> Result<(), PlannerErr> {
        self.finish_unions()?;
        self.finish_joins()?;
        Ok(())
    }

    fn finish_joins(&mut self) -> Result<usize, PlannerErr> {
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

    fn finish_unions(&mut self) -> Result<usize, PlannerErr> {
        // Return error if plan has not yet started
        if self.keccak_peaks.is_empty() {
            return Err(PlannerErr::PlanNotStartedString);
        }

        // Join remaining peaks
        while 2 <= self.keccak_peaks.len() {
            let peak_0 = self.keccak_peaks.pop_front().unwrap();
            let peak_1 = self.keccak_peaks.pop_front().unwrap();

            let peak_3 = self.enqueue_union(peak_1, peak_0);
            self.keccak_peaks.push_front(peak_3);
        }

        // Add the Finalize task
        Ok(self.enqueue_finalize_keccak(self.keccak_peaks[0]))
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

    fn enqueue_union(&mut self, left: usize, right: usize) -> usize {
        let task_number = self.next_task_number();
        let task_height = 1 + u32::max(
            self.get_task(left).task_height,
            self.get_task(right).task_height,
        );
        self.tasks
            .push(Task::new_union(task_number, task_height, left, right));
        task_number
    }

    fn enqueue_finalize(&mut self, depends_on: usize) -> usize {
        let task_number = self.next_task_number();
        let task_height = 1 + self.get_task(depends_on).task_height;
        self.tasks.push(Task::new_finalize_joins(
            task_number,
            task_height,
            depends_on,
        ));
        task_number
    }

    fn enqueue_finalize_keccak(&mut self, depends_on: usize) -> usize {
        let task_number = self.next_task_number();
        let task_height = 1 + self.get_task(depends_on).task_height;
        self.tasks.push(Task::new_finalize_unions(
            task_number,
            task_height,
            depends_on,
        ));
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
                Command::FinalizeJoins => {
                    write!(f, "{:?} FinalizeJoins", task.task_number)?;
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
                Command::FinalizeUnions => {
                    write!(f, "{:?} FinalizeUnions", task.task_number)?;
                    stack.push((indent + 2, task.depends_on[0]));
                }
                Command::Keccak => {
                    write!(f, "{:?} Keccak", task.task_number)?;
                }
                Command::Union => {
                    write!(f, "{:?} Union", task.task_number)?;
                    stack.push((indent + 2, task.depends_on[0]));
                    stack.push((indent + 2, task.depends_on[1]));
                }
            }
        }

        Ok(())
    }
}
