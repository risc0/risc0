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

use risc0_zkvm::{
    ApiClient, Asset, AssetRequest, ProveKeccakRequest, ProverOpts, ReceiptClaim, SuccinctReceipt,
    Unknown,
};

use crate::task_mgr::{Job, JobKind};

#[derive(Default)]
pub struct Worker;

impl workerpool::Worker for Worker {
    type Input = Job;
    type Output = Job;

    fn execute(&mut self, job: Job) -> Job {
        println!("{:?}", job.task);

        std::panic::catch_unwind(|| match job.kind {
            JobKind::Segment(segment) => Job {
                task: job.task.clone(),
                kind: JobKind::FinalizeJoins(Box::new(Self::prove_and_lift(segment))),
            },
            JobKind::Join(pair) => Job {
                task: job.task.clone(),
                kind: JobKind::FinalizeJoins(Box::new(Self::join(pair.0, pair.1))),
            },
            JobKind::FinalizeJoins(receipt) => Job {
                task: job.task.clone(),
                kind: JobKind::FinalizeJoins(Box::new(*receipt)),
            },
            JobKind::Keccak(proof_request) => Job {
                task: job.task.clone(),
                kind: JobKind::FinalizeUnions(Box::new(Self::keccak(proof_request))),
            },
            JobKind::FinalizeUnions(receipt) => Job {
                task: job.task.clone(),
                kind: JobKind::FinalizeUnions(Box::new(*receipt)),
            },
            JobKind::Union(pair) => Job {
                task: job.task.clone(),
                kind: JobKind::FinalizeUnions(Box::new(Self::union(pair.0, pair.1))),
            },
        })
        .unwrap_or_else(|_| {
            std::process::abort();
        })
    }
}

impl Worker {
    fn prove_and_lift(segment: Asset) -> SuccinctReceipt<ReceiptClaim> {
        let opts = ProverOpts::default();
        let client = ApiClient::from_env().unwrap();

        let segment_receipt = client
            .prove_segment(&opts, segment, AssetRequest::Inline)
            .unwrap();

        let segment_receipt_asset = segment_receipt.try_into().unwrap();
        client
            .lift(&opts, segment_receipt_asset, AssetRequest::Inline)
            .unwrap()
    }

    fn join(
        left: SuccinctReceipt<ReceiptClaim>,
        right: SuccinctReceipt<ReceiptClaim>,
    ) -> SuccinctReceipt<ReceiptClaim> {
        let opts = ProverOpts::default();
        let client = ApiClient::from_env().unwrap();
        let left_asset = left.try_into().unwrap();
        let right_asset = right.try_into().unwrap();
        client
            .join(&opts, left_asset, right_asset, AssetRequest::Inline)
            .unwrap()
    }

    fn keccak(proof_request: ProveKeccakRequest) -> SuccinctReceipt<Unknown> {
        let client = ApiClient::from_env().unwrap();
        client
            .prove_keccak(proof_request, AssetRequest::Inline)
            .unwrap()
    }

    fn union(
        left: SuccinctReceipt<Unknown>,
        right: SuccinctReceipt<Unknown>,
    ) -> SuccinctReceipt<Unknown> {
        let opts = ProverOpts::default();
        let client = ApiClient::from_env().unwrap();
        let left_asset = left.try_into().unwrap();
        let right_asset = right.try_into().unwrap();
        client
            .union(&opts, left_asset, right_asset, AssetRequest::Inline)
            .unwrap()
            .into_unknown()
    }
}
