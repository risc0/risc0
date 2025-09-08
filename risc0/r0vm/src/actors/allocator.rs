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

#![allow(dead_code)]

//! This module contains a piece of the actor system known as the "allocator"
//!
//! The allocator exists to provide coordination between different versions of r0vm actor clusters.
//! To support fulfilling proof requests across different r0vm versions, multiple clusters of r0vm
//! must be run on the same hardware. To handle this scenario the allocator takes care of the
//! following responsibilities:
//!
//! - Routing proof requests to the appropriate versioned r0vm cluster.
//! - Ensuring that workers which share hardware resources (such as GPUSs) do not schedule jobs
//!   using said resources simultaneously.
//!
//! To accomplish this, the allocator must communicate with managers and workers.
//!
//! Workers advertise to the allocator what hardware resources they are using. Managers receive
//! proof requests from the allocator, and they also talk to the allocator to reserve workers.
//!

use std::collections::{BTreeMap, HashMap, btree_map, hash_map};
use std::net::SocketAddr;
use std::num::NonZeroU32;
use std::sync::Arc;

use super::protocol::WorkerId;
use anyhow::{Context as _, anyhow, bail};
use http_body_util::BodyExt as _;
use kameo::{Reply, prelude::*};
use tokio::net::TcpListener;
use url::Url;
use uuid::Uuid;

/// This is the URL path where requests are proxied to a manager of a specified version.
const PROXY_URL_PATH: &str = "/r0vm";

/// This value is the globally unique immutable alphanumeric identifier of the GPU. It does not
/// correspond to any physical label on the board.
pub struct GpuUuid(Uuid);

impl std::str::FromStr for GpuUuid {
    type Err = anyhow::Error;

    fn from_str(s: &str) -> anyhow::Result<Self> {
        let rest = s
            .strip_prefix("GPU-")
            .ok_or_else(|| anyhow!("UUID doesn't start with GPU-"))?;
        Ok(Self(Uuid::from_str(rest)?))
    }
}

/// Represents the ability schedule something to run on the GPU.
pub struct GpuTokens(u64);

/// Represents a GPU on some machine.
pub struct Gpu {
    /// The name of the GPU for logging purposes
    name: String,
    /// A globally unique ID representing the GPU.
    uuid: GpuUuid,
    /// Number of GPU tokens
    tokens: GpuTokens,
}

/// Represents a CPU on some machine.
pub struct Cpu {
    /// The name of the CPU for logging purposes
    name: String,
    /// The number of cores this CPU has.
    cores: u32,
    /// The base clock speed of the CPU in Mhz.
    speed_mhz: u32,
}

pub enum HardwareResource {
    Gpu(Gpu),
    Cpu(Cpu),
}

pub struct MachineId {
    ip: std::net::IpAddr,
}

/// Description of a hardware resource to reserve while a worker is allocated.
enum HardwareReservation {
    /// A single GPU is reserved.
    Gpu,
    /// A portion of a CPU is reserved.
    Cpu { reserved_cores: NonZeroU32 },
}

/// The allocator's representation of a worker.
struct Worker {
    machine: MachineId,
    hardware: Vec<HardwareResource>,
}

/// Reply when a worker is successfully allocated.
#[derive(Reply)]
struct AllocateWorkerReply {
    worker_id: WorkerId,
}

struct Manager {
    endpoint: Url,
}

#[derive(Actor)]
pub struct AllocatorActor {
    workers: HashMap<WorkerId, Worker>,
    managers: BTreeMap<semver::Version, Manager>,
    http_client: Arc<reqwest::Client>,
}

impl AllocatorActor {
    pub fn new() -> Self {
        Self {
            workers: HashMap::new(),
            managers: BTreeMap::new(),
            http_client: Arc::new(reqwest::Client::new()),
        }
    }
}

/// Request to register a worker with the allocator.
struct RegisterWorker {
    worker_id: WorkerId,
    machine: MachineId,
    hardware: Vec<HardwareResource>,
}

impl Message<RegisterWorker> for AllocatorActor {
    type Reply = anyhow::Result<()>;

    async fn handle(
        &mut self,
        msg: RegisterWorker,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> anyhow::Result<()> {
        if let hash_map::Entry::Vacant(e) = self.workers.entry(msg.worker_id) {
            e.insert(Worker {
                machine: msg.machine,
                hardware: msg.hardware,
            });
        } else {
            bail!(
                "duplicate registration from worker {} at {}",
                msg.worker_id,
                msg.machine.ip
            );
        }
        Ok(())
    }
}

/// Allocate a worker from the given eligibility pool. While the worker is allocated, another
/// worker using the same hardware represented by `hardware_reservation` won't be allocated.
struct AllocateWorker {
    pool: Vec<WorkerId>,
    hardware_reservations: Vec<HardwareReservation>,
}

impl Message<AllocateWorker> for AllocatorActor {
    type Reply = DelegatedReply<AllocateWorkerReply>;

    async fn handle(
        &mut self,
        _msg: AllocateWorker,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let (delegated_reply, _reply_sender) = ctx.reply_sender();
        // todo
        delegated_reply
    }
}

/// The given worker is now free again to accept other work.
struct DeallocateWorker {
    worker_id: WorkerId,
}

impl Message<DeallocateWorker> for AllocatorActor {
    type Reply = ();

    async fn handle(&mut self, _msg: DeallocateWorker, _ctx: &mut Context<Self, Self::Reply>) {
        // todo
    }
}

struct RegisterManager {
    zkvm_version: semver::Version,
    endpoint: Url,
}

impl Message<RegisterManager> for AllocatorActor {
    type Reply = anyhow::Result<()>;

    async fn handle(
        &mut self,
        msg: RegisterManager,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> anyhow::Result<()> {
        if let btree_map::Entry::Vacant(e) = self.managers.entry(msg.zkvm_version.clone()) {
            e.insert(Manager {
                endpoint: msg.endpoint,
            });
        } else {
            bail!(
                "duplicate registration for manager with version {}",
                msg.zkvm_version
            );
        }
        Ok(())
    }
}

//  _ __  _ __ _____  ___   _
// | '_ \| '__/ _ \ \/ / | | |
// | |_) | | | (_) >  <| |_| |
// | .__/|_|  \___/_/\_\\__, |
// |_|                  |___/

#[derive(Debug)]
struct HttpError {
    status_code: http::StatusCode,
    message: String,
}

impl HttpError {
    fn new(status_code: http::StatusCode, message: impl Into<String>) -> Self {
        Self {
            status_code,
            message: message.into(),
        }
    }
}

impl std::error::Error for HttpError {}

impl std::fmt::Display for HttpError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        self.message.fmt(f)
    }
}

pub struct ApiRequest {
    pub request: http::Request<axum::body::Body>,
}

impl ApiRequest {
    fn risc0_version(&self) -> anyhow::Result<semver::VersionReq> {
        let version_value = self
            .request
            .headers()
            .get("x-risc0-version")
            .ok_or_else(|| anyhow!("request missing `x-risc0-version` header"))?;
        Ok(version_value.to_str()?.parse()?)
    }
}

pub struct ApiResponse {
    pub response: http::Response<axum::body::Body>,
}

async fn proxy_api_request(
    http_client: Arc<reqwest::Client>,
    endpoint: Url,
    req: ApiRequest,
) -> anyhow::Result<ApiResponse> {
    // Convert request into reqwest::Request
    let (parts, body) = req.request.into_parts();
    let request =
        http::Request::from_parts(parts, reqwest::Body::wrap_stream(body.into_data_stream()));
    let mut req: reqwest::Request = request.try_into()?;

    // Join the URLs together
    *req.url_mut() = endpoint.join(
        req.url()
            .path()
            .strip_prefix(PROXY_URL_PATH)
            .ok_or_else(|| anyhow!("url doesn't begin with {PROXY_URL_PATH}"))?,
    )?;

    let response: http::Response<reqwest::Body> = http_client.execute(req).await?.into();
    let (parts, body) = response.into_parts();

    Ok(ApiResponse {
        response: http::Response::from_parts(
            parts,
            axum::body::Body::from_stream(body.into_data_stream()),
        ),
    })
}

impl AllocatorActor {
    fn handle_api_request(
        &mut self,
        request: ApiRequest,
        reply_sender: &mut Option<ReplySender<anyhow::Result<ApiResponse>>>,
    ) -> anyhow::Result<()> {
        let version_req = request.risc0_version()?;

        // Find a registered manager which satisfies the given request version.
        // We prefer versions which are higher.
        for (manager_version, manager) in self.managers.iter().rev() {
            if version_req.matches(manager_version) {
                let http_client = self.http_client.clone();
                let endpoint = manager.endpoint.clone();
                let reply_sender = reply_sender.take();
                tokio::task::spawn(async move {
                    if let Some(reply_sender) = reply_sender {
                        reply_sender.send(proxy_api_request(http_client, endpoint, request).await)
                    }
                });
                return Ok(());
            }
        }

        Err(HttpError::new(
            http::StatusCode::BAD_REQUEST,
            format!("no manager found to satisfy request with requirement {version_req}"),
        )
        .into())
    }
}

impl Message<ApiRequest> for AllocatorActor {
    type Reply = DelegatedReply<anyhow::Result<ApiResponse>>;

    async fn handle(
        &mut self,
        request: ApiRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let (delegated_reply, mut reply_sender) = ctx.reply_sender();
        if let Err(error) = self.handle_api_request(request, &mut reply_sender)
            && let Some(reply_sender) = reply_sender
        {
            reply_sender.send(Err(error));
        }
        delegated_reply
    }
}

fn send_error_err<M, E>(error: &SendError<M, E>) -> Option<&E> {
    if let SendError::HandlerError(e) = error {
        Some(e)
    } else {
        None
    }
}

#[axum::debug_handler]
async fn proxy_handler(
    axum::extract::State(allocator): axum::extract::State<ActorRef<AllocatorActor>>,
    request: http::Request<axum::body::Body>,
) -> http::Response<axum::body::Body> {
    match allocator.ask(ApiRequest { request }).await {
        Ok(resp) => resp.response,
        Err(error) => {
            let status_code = send_error_err(&error)
                .and_then(|e| e.downcast_ref::<HttpError>())
                .map(|e| e.status_code)
                .unwrap_or(http::StatusCode::INTERNAL_SERVER_ERROR);
            http::Response::builder()
                .status(status_code)
                .body(axum::body::Body::new(error.to_string()))
                .unwrap()
        }
    }
}

fn proxy_app(allocator: ActorRef<AllocatorActor>) -> axum::Router {
    use axum::routing::*;

    // This attempts to be a complete list of HTTP methods we would ever support.
    axum::Router::new()
        .route(
            &format!("{PROXY_URL_PATH}/{{*wildcard}}"),
            delete(proxy_handler)
                .get(proxy_handler)
                .head(proxy_handler)
                .options(proxy_handler)
                .patch(proxy_handler)
                .post(proxy_handler)
                .put(proxy_handler)
                .trace(proxy_handler),
        )
        .with_state(allocator)
}

/// Runs HTTP proxy that forwards to all registered managers. The particular manager is selected
/// via the `x-risc0-version` header.
pub async fn run_proxy(
    addr: SocketAddr,
    allocator: ActorRef<AllocatorActor>,
) -> anyhow::Result<()> {
    let listener = TcpListener::bind(addr).await?;
    tracing::info!("Allocator API listening on: {}", listener.local_addr()?);

    axum::serve(listener, proxy_app(allocator))
        .with_graceful_shutdown(crate::api::shutdown_signal())
        .await
        .context("Allocator API service failed")?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use axum_test::TestServer;
    use httpmock::MockServer;
    use rstest::rstest;

    struct TestManager {
        server: MockServer,
    }

    impl TestManager {
        fn new() -> Self {
            let server = MockServer::start();
            Self { server }
        }
    }

    fn method_req_has_body(method: &http::Method) -> bool {
        use http::Method;

        method == Method::PUT || method == Method::PATCH || method == Method::POST
    }

    fn method_resp_has_body(method: &http::Method) -> bool {
        use http::Method;
        method == Method::DELETE
            || method == Method::GET
            || method == Method::PATCH
            || method == Method::POST
            || method == Method::PUT
            || method == Method::TRACE
    }

    async fn manager_proxy_test(
        manager_versions: Vec<semver::Version>,
        expected_replied_manager_version: Option<semver::Version>,
        method: http::Method,
        request_version: &str,
    ) -> axum_test::TestResponse {
        let managers: HashMap<_, _> = manager_versions
            .iter()
            .map(|v| (v.clone(), TestManager::new()))
            .collect();

        let alloc_ref = kameo::spawn(AllocatorActor::new());

        for (version, manager) in &managers {
            alloc_ref
                .ask(RegisterManager {
                    zkvm_version: version.clone(),
                    endpoint: manager.server.url("/").parse().unwrap(),
                })
                .await
                .unwrap();
        }

        let proxy = TestServer::new(proxy_app(alloc_ref)).unwrap();

        let hello_mock = expected_replied_manager_version.map(|v| {
            let method = method.clone();
            managers[&v].server.mock(move |mut when, mut then| {
                when = when.path("/ping").method(method.as_str());
                if method_req_has_body(&method) {
                    when.body("ping");
                }
                then = then.status(200);
                if method_resp_has_body(&method) {
                    then.body("pong");
                }
            })
        });
        let req_url = format!("{PROXY_URL_PATH}/ping");
        let mut test_req = proxy.method(method.clone(), &req_url);

        if method_req_has_body(&method) {
            test_req = test_req.text("ping");
        }
        let response = test_req
            .add_header("x-risc0-version", request_version)
            .await;

        if let Some(hello_mock) = hello_mock {
            hello_mock.assert();
        }

        response
    }

    #[rstest]
    #[case::delete("DELETE")]
    #[case::get("GET")]
    #[case::head("HEAD")]
    #[case::options("OPTIONS")]
    #[case::patch("PATCH")]
    #[case::post("POST")]
    #[case::put("PUT")]
    #[case::trace("TRACE")]
    #[tokio::test]
    async fn proxy_manager_not_found(#[case] method: &str) {
        let method = http::Method::from_bytes(method.as_bytes()).unwrap();
        let response = manager_proxy_test(
            vec![semver::Version::new(1, 2, 3)],
            None,
            method.clone(),
            "1.2.4",
        )
        .await;
        response.assert_status(http::StatusCode::BAD_REQUEST);
        if method_resp_has_body(&method) {
            assert_eq!(
                response.text(),
                "no manager found to satisfy request with requirement ^1.2.4"
            );
        }
    }

    #[rstest]
    #[case::delete("DELETE")]
    #[case::get("GET")]
    #[case::head("HEAD")]
    #[case::options("OPTIONS")]
    #[case::patch("PATCH")]
    #[case::post("POST")]
    #[case::put("PUT")]
    #[case::trace("TRACE")]
    #[tokio::test]
    async fn proxy_manager_exact_match(#[case] method: &str) {
        let method = http::Method::from_bytes(method.as_bytes()).unwrap();
        let response = manager_proxy_test(
            vec![semver::Version::new(1, 2, 3), semver::Version::new(1, 2, 4)],
            Some(semver::Version::new(1, 2, 3)),
            method.clone(),
            "=1.2.3",
        )
        .await;
        response.assert_status_success();
        if method_resp_has_body(&method) {
            response.assert_text("pong");
        }
    }

    #[tokio::test]
    async fn proxy_manager_multiple_match_chooses_latest() {
        let method = http::Method::PUT;
        let response = manager_proxy_test(
            vec![
                semver::Version::new(1, 2, 3),
                semver::Version::new(1, 2, 4),
                semver::Version::new(3, 0, 0),
            ],
            Some(semver::Version::new(1, 2, 4)),
            method,
            "1.2.3",
        )
        .await;
        response.assert_status_success();
        response.assert_text("pong");
    }

    #[tokio::test]
    async fn proxy_manager_multiple_match_doesnt_choose_rc() {
        let method = http::Method::PUT;
        let response = manager_proxy_test(
            vec![
                semver::Version::new(1, 2, 3),
                semver::Version::new(1, 2, 4),
                semver::Version::new(3, 0, 0),
                "3.0.0-rc.1".parse().unwrap(),
            ],
            Some(semver::Version::new(3, 0, 0)),
            method,
            "3.0.0",
        )
        .await;
        response.assert_status_success();
        response.assert_text("pong");
    }

    #[tokio::test]
    async fn multiple_managers_registered_error() {
        let alloc_ref = kameo::spawn(AllocatorActor::new());

        alloc_ref
            .ask(RegisterManager {
                zkvm_version: semver::Version::new(1, 2, 3),
                endpoint: "http://[::]".parse().unwrap(),
            })
            .await
            .unwrap();

        let error = alloc_ref
            .ask(RegisterManager {
                zkvm_version: semver::Version::new(1, 2, 3),
                endpoint: "http://[::]".parse().unwrap(),
            })
            .await
            .unwrap_err();
        assert_eq!(
            error.to_string(),
            "duplicate registration for manager with version 1.2.3"
        );
    }
}
