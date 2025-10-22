// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{borrow::Cow, collections::HashMap};

use opentelemetry::{
    KeyValue,
    global::BoxedTracer,
    trace::{TraceContextExt as _, Tracer},
};
use serde::{Deserialize, Serialize};

use crate::actors::protocol::{TaskHeader, TaskId};

pub struct JobTracer {
    ctx: opentelemetry::Context,
    tracer: BoxedTracer,
    pending_spans: HashMap<TaskId, opentelemetry::Context>,
}

impl JobTracer {
    pub fn new(name: &'static str, job_id: impl ToString) -> Self {
        let tracer = opentelemetry::global::tracer(name);
        let span = tracer
            .span_builder("job")
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
        self.pending_spans.insert(
            task_id,
            self.ctx
                .with_span(self.tracer.start_with_context(name, &self.ctx)),
        );
    }

    pub fn span_event<T>(&mut self, header: TaskHeader, name: T)
    where
        T: Into<Cow<'static, str>>,
    {
        self.pending_spans
            .get_mut(&header.global_id.task_id)
            .expect("span_start should be called before span_event for given task")
            .span()
            .add_event(name, vec![]);
    }

    pub fn span_end(&mut self, task_id: TaskId) {
        self.pending_spans
            .remove(&task_id)
            .as_mut()
            .expect("span_start should be called before span_start for given task")
            .span()
            .end();
    }

    pub fn end(&mut self) {
        self.ctx.span().end();
    }

    pub fn saved_task_context(&self, task_id: TaskId) -> SavedContext {
        let ctx = self
            .pending_spans
            .get(&task_id)
            .expect("span_start should be called before to_task_saved_context for given task");

        let mut saved = SavedContext {
            context: Default::default(),
        };
        opentelemetry::global::get_text_map_propagator(|prop| {
            prop.inject_context(ctx, &mut saved.context)
        });
        saved
    }
}

#[derive(Clone, Default, Serialize, Deserialize)]
pub struct SavedContext {
    context: HashMap<String, String>,
}

impl SavedContext {
    pub fn to_context(&self) -> opentelemetry::Context {
        opentelemetry::global::get_text_map_propagator(|prop| prop.extract(&self.context))
    }
}
