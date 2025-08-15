// Copyright 2025 RISC Zero, Inc.
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

use std::{borrow::Cow, collections::HashMap};

use opentelemetry::{
    global::{BoxedSpan, BoxedTracer},
    trace::{Span, SpanKind, TraceContextExt as _, Tracer},
    KeyValue,
};

use crate::actors::protocol::{TaskHeader, TaskId};

pub struct JobTracer {
    ctx: opentelemetry::Context,
    tracer: BoxedTracer,
    pending_spans: HashMap<TaskId, BoxedSpan>,
}

impl JobTracer {
    pub fn new(name: &'static str, job_id: impl ToString) -> Self {
        let tracer = opentelemetry::global::tracer(name);
        let span = tracer
            .span_builder("job")
            .with_kind(SpanKind::Client)
            .with_attributes([KeyValue::new("job_id", job_id.to_string())])
            .start(&tracer);
        let ctx = opentelemetry::Context::current_with_span(span);
        Self {
            ctx,
            tracer,
            pending_spans: HashMap::new(),
        }
    }

    pub fn span_start<T>(&mut self, task_id: TaskId, name: T)
    where
        T: Into<Cow<'static, str>>,
    {
        self.pending_spans
            .insert(task_id, self.tracer.start_with_context(name, &self.ctx));
    }

    pub fn span_event<T>(&mut self, header: TaskHeader, name: T)
    where
        T: Into<Cow<'static, str>>,
    {
        self.pending_spans
            .get_mut(&header.global_id.task_id)
            .unwrap()
            .add_event(name, vec![]);
    }

    pub fn span_end(&mut self, task_id: TaskId) {
        self.pending_spans.remove(&task_id).as_mut().unwrap().end();
    }

    pub fn record_error(&mut self, error: &dyn std::error::Error) {
        self.ctx.span().record_error(error);
    }

    pub fn end(&mut self) {
        self.ctx.span().end();
    }
}
