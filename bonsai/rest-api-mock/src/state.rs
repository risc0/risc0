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

use std::{
    collections::HashMap,
    sync::{Arc, RwLock},
};

pub(crate) type AppState = Arc<RwLock<BonsaiState>>;

#[derive(Clone, Default)]
pub(crate) struct BonsaiState {
    pub(crate) local_url: String,
    // ImageID - MemoryImage
    pub(crate) images: HashMap<String, Vec<u8>>,
    // InputID - input
    pub(crate) inputs: HashMap<String, Vec<u8>>,
    // SessionID - Status
    pub(crate) sessions: HashMap<String, String>,
    // SessionID - Receipts
    pub(crate) receipts: HashMap<String, Vec<u8>>,
}

impl BonsaiState {
    pub(crate) fn new(local_url: String) -> Self {
        Self {
            local_url,
            images: HashMap::new(),
            inputs: HashMap::new(),
            sessions: HashMap::new(),
            receipts: HashMap::new(),
        }
    }
    pub(crate) fn put_image(&mut self, image_id: String, image: Vec<u8>) -> Option<Vec<u8>> {
        self.images.insert(image_id, image)
    }
    pub(crate) fn get_image(&self, image_id: impl AsRef<str>) -> Option<Vec<u8>> {
        self.images.get(image_id.as_ref()).cloned()
    }
    pub(crate) fn put_input(&mut self, input_id: String, input: Vec<u8>) -> Option<Vec<u8>> {
        self.inputs.insert(input_id, input)
    }
    pub(crate) fn get_input(&self, input_id: impl AsRef<str>) -> Option<Vec<u8>> {
        self.inputs.get(input_id.as_ref()).cloned()
    }
    pub(crate) fn put_session(&mut self, session_id: String, status: String) -> Option<String> {
        self.sessions.insert(session_id, status)
    }
    pub(crate) fn get_session(&self, session_id: impl AsRef<str>) -> Option<String> {
        self.sessions.get(session_id.as_ref()).cloned()
    }
    pub(crate) fn put_receipt(&mut self, session_id: String, receipt: Vec<u8>) -> Option<Vec<u8>> {
        self.receipts.insert(session_id, receipt)
    }
    pub(crate) fn get_receipt(&self, session_id: impl AsRef<str>) -> Option<Vec<u8>> {
        self.receipts.get(session_id.as_ref()).cloned()
    }
}
