// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use crate::Agent;
use anyhow::{bail, Result};
use workflow_common::{SnarkReq, SnarkResp};

/// Converts a stark, stored in s3 to a snark
pub async fn stark2snark(_agent: &Agent, _job_id: &str, _req: &SnarkReq) -> Result<SnarkResp> {
    bail!("stark2snark bento is todo")
}
