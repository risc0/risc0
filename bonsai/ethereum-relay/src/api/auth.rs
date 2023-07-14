// Copyright 2023 RISC Zero, Inc.
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

use axum::{http::Request, middleware::Next, response::Response};

use super::{Error, Result};

pub(crate) async fn authorize<B>(mut req: Request<B>, next: Next<B>) -> Result<Response> {
    if let Some(auth_header) = req
        .headers()
        .get("x-api-key")
        .and_then(|header| header.to_str().ok())
    {
        let owned_value = auth_header.to_owned();
        // insert the current user into a request extension so the handler can
        // extract it
        req.extensions_mut().insert(owned_value);
        Ok(next.run(req).await)
    } else {
        Err(Error::Unauthorized)
    }
}
