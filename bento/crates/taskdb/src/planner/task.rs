// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use std::collections::VecDeque;

#[derive(Clone, Debug, Eq, PartialEq)]
pub enum Command {
    Keccak,
    Finalize,
    Join,
    Segment,
    Union,
}

#[derive(Clone, Debug, Eq, PartialEq)]
pub struct Task {
    pub task_number: usize,
    pub task_height: u32,
    pub command: Command,
    pub depends_on: Vec<usize>,
    pub keccak_depends_on: VecDeque<usize>,
}

impl Task {
    pub fn new_keccak(task_number: usize) -> Self {
        Task {
            task_number,
            task_height: 0,
            command: Command::Keccak,
            depends_on: Vec::new(),
            keccak_depends_on: VecDeque::new(),
        }
    }

    pub fn new_segment(task_number: usize) -> Self {
        Task {
            task_number,
            task_height: 0,
            command: Command::Segment,
            depends_on: Vec::new(),
            keccak_depends_on: VecDeque::new(),
        }
    }

    pub fn new_join(task_number: usize, task_height: u32, left: usize, right: usize) -> Self {
        Task {
            task_number,
            task_height,
            command: Command::Join,
            depends_on: vec![left, right],
            keccak_depends_on: VecDeque::new(),
        }
    }

    pub fn new_union(task_number: usize, task_height: u32, left: usize, right: usize) -> Self {
        Task {
            task_number,
            task_height,
            command: Command::Union,
            depends_on: vec![],
            keccak_depends_on: vec![left, right].into(),
        }
    }

    pub fn new_finalize(
        task_number: usize,
        task_height: u32,
        depends_on: usize,
        keccak_depends_on: Option<VecDeque<usize>>,
    ) -> Self {
        Task {
            task_number,
            task_height,
            command: Command::Finalize,
            depends_on: vec![depends_on],
            keccak_depends_on: keccak_depends_on.unwrap_or_default(),
        }
    }
}
