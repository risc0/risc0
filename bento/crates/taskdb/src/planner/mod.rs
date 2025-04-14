// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

pub mod task;

use crate::planner::task::Task;
use std::{cmp::Ordering, collections::VecDeque};
use thiserror::Error;

#[derive(Error, Debug)]
pub enum PlannerErr {
    #[error("Planning not yet started")]
    PlanNotStartedString,
    #[error("Cannot add segment to finished plan")]
    PlanFinalized,
}

#[derive(Clone, Eq, PartialEq, Default)]
pub struct Planner {
    /// All of the tasks in this plan
    tasks: Vec<Task>,

    /// List of current "peaks." Sorted in order of decreasing height.
    ///
    /// A task is a "peak" if (1) it is either a Segment or Join command AND (2) no other join
    /// tasks depend on it.
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

impl core::fmt::Debug for Planner {
    fn fmt(&self, f: &mut core::fmt::Formatter) -> core::fmt::Result {
        use crate::planner::task::Command;

        let mut stack = Vec::new();

        if self.last_task.is_none() {
            writeln!(f, "Still in planning phases ...")?;
        } else {
            stack.push((0, self.last_task.unwrap()));
        }

        while let Some((indent, cursor)) = stack.pop() {
            if indent > 0 {
                write!(f, "\n{}", " ".repeat(indent))?
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

impl Planner {
    pub fn enqueue_segment(&mut self) -> Result<usize, PlannerErr> {
        if self.last_task.is_some() {
            return Err(PlannerErr::PlanFinalized);
        }

        let task_number = self.next_task_number();
        self.tasks.push(Task::new_segment(task_number));

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

    pub fn enqueue_keccak(&mut self) -> Result<usize, PlannerErr> {
        if self.last_task.is_some() {
            return Err(PlannerErr::PlanFinalized);
        }

        let task_number = self.next_task_number();
        self.tasks.push(Task::new_keccak(task_number));

        let mut new_peak = task_number;
        while let Some(smallest_peak) = self.keccak_peaks.back().copied() {
            let new_height = self.get_task(new_peak).task_height;
            let smallest_peak_height = self.get_task(smallest_peak).task_height;
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

    fn finish_unions(&mut self) -> Option<VecDeque<usize>> {
        // this assumes that there's always a minimum of 1 segment
        if self.keccak_peaks.is_empty() {
            return None;
        }

        // Join remaining peaks if using union
        while 2 <= self.keccak_peaks.len() {
            let peak_0 = self.keccak_peaks.pop_front().unwrap();
            let peak_1 = self.keccak_peaks.pop_front().unwrap();

            let peak_3 = self.enqueue_union(peak_1, peak_0);
            self.keccak_peaks.push_front(peak_3);
        }

        // return only highest peak
        Some(VecDeque::from([self.keccak_peaks[0]]))
    }

    pub fn finish(&mut self) -> Result<usize, PlannerErr> {
        // Return error if plan has not yet started
        if self.peaks.is_empty() {
            return Err(PlannerErr::PlanNotStartedString);
        }

        // finish unions
        let keccak_depends_on = self.finish_unions();

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
            self.last_task = Some(self.enqueue_finalize(self.peaks[0], keccak_depends_on));
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
            panic!("Invalid task number {}", task_number);
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
        let task_height =
            1 + u32::max(self.get_task(left).task_height, self.get_task(right).task_height);
        self.tasks.push(Task::new_join(task_number, task_height, left, right));
        task_number
    }

    fn enqueue_union(&mut self, left: usize, right: usize) -> usize {
        let task_number = self.next_task_number();
        let task_height =
            1 + u32::max(self.get_task(left).task_height, self.get_task(right).task_height);
        self.tasks.push(Task::new_union(task_number, task_height, left, right));
        task_number
    }

    fn enqueue_finalize(
        &mut self,
        depends_on: usize,
        keccak_depends_on: Option<VecDeque<usize>>,
    ) -> usize {
        let task_number = self.next_task_number();
        let mut task_height = 1 + self.get_task(depends_on).task_height;
        if let Some(val) = &keccak_depends_on {
            if let Some(highest_peak) = val.iter().max().copied() {
                task_height = task_height.max(1 + self.get_task(highest_peak).task_height);
            }
        }
        self.tasks.push(Task::new_finalize(
            task_number,
            task_height,
            depends_on,
            keccak_depends_on,
        ));
        task_number
    }

    fn next_task_number(&self) -> usize {
        self.task_count()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_simple_plan() {
        let mut planner = Planner::default();
        let numb = planner.enqueue_segment().unwrap();
        assert_eq!(numb, 0);
        let task = planner.next_task().unwrap();
        assert_eq!(task.keccak_depends_on.len(), 0);
        assert_eq!(task.depends_on.len(), 0);
        assert_eq!(task.command, task::Command::Segment);
        assert_eq!(task.task_number, 0);
        assert!(planner.next_task().is_none());

        let numb = planner.enqueue_keccak().unwrap();
        let task = planner.next_task().unwrap();
        assert_eq!(numb, 1);
        assert_eq!(task.keccak_depends_on.len(), 0);
        assert_eq!(task.depends_on.len(), 0);
        assert_eq!(task.command, task::Command::Keccak);
        assert_eq!(task.task_number, 1);
        assert!(planner.next_task().is_none());

        planner.finish().unwrap();
        let task = planner.next_task().unwrap();
        assert_eq!(task.command, task::Command::Finalize);
        assert_eq!(task.keccak_depends_on.len(), 1);
        assert_eq!(task.task_number, 2);
        assert_eq!(task.depends_on.len(), 1);
        assert_eq!(task.task_height, 1);

        assert_eq!(planner.task_count(), 3);
        assert_eq!(planner.get_task(0).task_number, 0);
    }

    #[test]
    fn test_balanced() {
        let mut planner = Planner::default();
        planner.enqueue_segment().unwrap();
        {
            let task = planner.next_task().unwrap();
            assert_eq!(task.command, task::Command::Segment);
            assert_eq!(task.task_number, 0);
            assert_eq!(task.task_height, 0);
            assert!(planner.next_task().is_none());
        }

        planner.enqueue_keccak().unwrap();
        {
            let task = planner.next_task().unwrap();
            assert_eq!(task.command, task::Command::Keccak);
            assert_eq!(task.task_number, 1);
            assert_eq!(task.task_height, 0);
        }

        planner.enqueue_segment().unwrap();
        {
            let task = planner.next_task().unwrap();
            assert_eq!(task.command, task::Command::Segment);
            assert_eq!(task.task_number, 2);
            assert_eq!(task.task_height, 0);
            assert_eq!(task.depends_on.len(), 0);
        }
        {
            let join = planner.next_task().unwrap();
            assert_eq!(join.command, task::Command::Join);
            assert_eq!(join.task_number, 3);
            assert_eq!(join.task_height, 1);
            assert_eq!(join.depends_on.len(), 2);
        }

        planner.enqueue_keccak().unwrap();
        {
            let task = planner.next_task().unwrap();
            assert_eq!(task.command, task::Command::Keccak);
            assert_eq!(task.task_number, 4);
            assert_eq!(task.task_height, 0);
        }
        {
            let union = planner.next_task().unwrap();
            assert_eq!(union.command, task::Command::Union);
            assert_eq!(union.task_number, 5);
            assert_eq!(union.task_height, 1);
            assert_eq!(union.keccak_depends_on.len(), 2);
        }

        planner.finish().unwrap();
        let keccak_last_task = planner.next_task().unwrap();
        assert_eq!(keccak_last_task.command, task::Command::Finalize);
        assert_eq!(keccak_last_task.task_number, 6);
        assert_eq!(keccak_last_task.task_height, 2);
        assert_eq!(keccak_last_task.depends_on.len(), 1);
        assert_eq!(keccak_last_task.keccak_depends_on.len(), 1);
    }

    #[test]
    fn test_unbalanced_keccak() {
        let mut planner = Planner::default();
        planner.enqueue_keccak().unwrap();
        planner.enqueue_keccak().unwrap();
        planner.enqueue_keccak().unwrap();
        planner.enqueue_segment().unwrap();
        planner.finish().unwrap();

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 0);
        assert_eq!(task.command, task::Command::Keccak);
        assert_eq!(task.task_height, 0);

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 1);
        assert_eq!(task.command, task::Command::Keccak);
        assert_eq!(task.task_height, 0);

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 2);
        assert_eq!(task.command, task::Command::Union);
        assert_eq!(task.task_height, 1);

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 3);
        assert_eq!(task.command, task::Command::Keccak);
        assert_eq!(task.task_height, 0);

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 4);
        assert_eq!(task.command, task::Command::Segment);
        assert_eq!(task.task_height, 0);

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 5);
        assert_eq!(task.command, task::Command::Union);
        assert_eq!(task.task_height, 2);

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 6);
        assert_eq!(task.command, task::Command::Finalize);
        assert_eq!(task.task_height, 3);
    }

    #[test]
    fn test_unbalanced() {
        let mut planner = Planner::default();
        planner.enqueue_segment().unwrap();
        planner.enqueue_segment().unwrap();
        planner.enqueue_segment().unwrap();

        planner.finish().unwrap();

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 0);
        assert_eq!(task.command, task::Command::Segment);

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 1);
        assert_eq!(task.command, task::Command::Segment);

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 2);
        assert_eq!(task.command, task::Command::Join);

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 3);
        assert_eq!(task.command, task::Command::Segment);

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 4);
        assert_eq!(task.command, task::Command::Join);

        let task = planner.next_task().unwrap();
        assert_eq!(task.task_number, 5);
        assert_eq!(task.command, task::Command::Finalize);
        assert_eq!(task.task_height, 3);
    }

    #[test]
    #[should_panic(expected = "PlanNotStartedString")]
    fn err_not_started() {
        let mut planner = Planner::default();
        planner.finish().unwrap();
    }

    #[test]
    #[should_panic(expected = "PlanFinalized")]
    fn err_finalized() {
        let mut planner = Planner::default();
        planner.enqueue_segment().unwrap();
        planner.finish().unwrap();
        planner.enqueue_segment().unwrap();
    }

    #[test]
    #[should_panic(expected = "Invalid task number 100")]
    fn err_bad_task_numb() {
        let planner = Planner::default();
        let _ = planner.get_task(100);
    }
}
