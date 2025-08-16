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

use std::collections::HashMap;
use std::future::Future;
use std::num::NonZeroU32;
use std::sync::{Arc, Mutex};

use anyhow::{anyhow, bail, Context as _, Result};
use opentelemetry::metrics::{Counter, Meter};
use serde::{de::DeserializeOwned, Deserialize, Serialize};
use tokio::io::{AsyncRead, AsyncReadExt as _, AsyncWrite, AsyncWriteExt as _};
use tokio::net::{tcp, unix, TcpStream, UnixStream};
use tokio::sync::Mutex as TokioMutex;

/// Create a pair of RPC sender and receiver. The sender is used to send messages to the remote
/// side, the receiver is used to get responses and remote requests.
pub fn rpc_system<StreamT: RpcStream>(
    stream: StreamT,
    meter: Meter,
) -> (
    RpcSender<StreamT::WriteHalf>,
    RpcReceiver<StreamT::ReadHalf>,
) {
    let (read_half, write_half) = stream.into_split();

    let registry = Arc::new(Mutex::new(RpcRegistry::new()));

    (
        RpcSender::new(write_half, registry.clone(), meter.clone()),
        RpcReceiver::new(read_half, registry, meter),
    )
}

/// A stream fit for use with the RPC system.
pub trait RpcStream: Sized {
    type ReadHalf: AsyncRead + Unpin;
    type WriteHalf: AsyncWrite + Unpin;

    fn into_split(self) -> (Self::ReadHalf, Self::WriteHalf);
}

//  ____                 _
// / ___|  ___ _ __   __| |
// \___ \ / _ \ '_ \ / _` |
//  ___) |  __/ | | | (_| |
// |____/ \___|_| |_|\__,_|
//

/// Represents a unique request and response between a particular local and remote machine.
#[derive(Clone, Copy, PartialEq, Eq, Hash, Serialize, Deserialize)]
pub struct RpcMessageId(NonZeroU32);

impl<StreamT: AsyncWrite + Unpin> RpcSender<StreamT> {
    /// Send a message to the remote machine and expect a response. When the response is received,
    /// the given callback will be called.
    pub async fn ask<ResponseT: DeserializeOwned>(
        &self,
        msg: &impl Serialize,
        callback: impl FnOnce(ResponseT) + Send + 'static,
    ) -> Result<()> {
        let message_id = self.registry.lock().unwrap().add_request(callback);
        self.send(msg, message_id, RpcMessageKind::ExpectsResponse)
            .await
    }

    /// Send a message to the remote machine and expect no response.
    pub async fn tell(&self, msg: &impl Serialize) -> Result<()> {
        let message_id = self.registry.lock().unwrap().next_message_id();
        self.send(msg, message_id, RpcMessageKind::ExpectsNoResponse)
            .await
    }

    /// Reply to a ask given to us.
    pub async fn respond(&self, msg: &impl Serialize, message_id: RpcMessageId) -> Result<()> {
        self.send(msg, message_id, RpcMessageKind::IsResponse).await
    }

    /// Shutdown the write side of the socket.
    pub async fn shutdown(&self) -> Result<()> {
        self.stream.lock().await.shutdown().await?;
        Ok(())
    }
}

//  ____               _
// |  _ \ ___  ___ ___(_)_   _____
// | |_) / _ \/ __/ _ \ \ \ / / _ \
// |  _ <  __/ (_|  __/ |\ V /  __/
// |_| \_\___|\___\___|_| \_/ \___|
//

impl<StreamT: AsyncRead + Unpin> RpcReceiver<StreamT> {
    /// Receive RPC messages until the socket is closed. The given callback is called when we
    /// receive a message which isn't a reply to an ask. That is, its called when the other-side
    /// sends us an asks or tell.
    pub async fn receive_many<RemoteMsgT: DeserializeOwned, FutT: Future<Output = ()>>(
        &mut self,
        mut remote_msg_callback: impl FnMut(RemoteMsgT, Option<RpcMessageId>) -> FutT,
    ) {
        loop {
            match self.receive_one(&mut remote_msg_callback).await {
                Ok(false) => {
                    // The socket was closed, just exit.
                    break;
                }
                Err(error) => {
                    tracing::error!("RPC error: {error}");

                    // Any IO error is fatal, so don't continue.
                    if error.downcast::<std::io::Error>().is_ok() {
                        break;
                    }
                }
                _ => (),
            }
        }
    }
}

//  ____       _            _
// |  _ \ _ __(_)_   ____ _| |_ ___
// | |_) | '__| \ \ / / _` | __/ _ \
// |  __/| |  | |\ V / (_| | ||  __/
// |_|   |_|  |_| \_/ \__,_|\__\___|
//

impl RpcMessageId {
    const INITIAL: Self = Self(NonZeroU32::new(1).unwrap());
    const MAX: Self = Self(NonZeroU32::new(u32::MAX).unwrap());

    fn incr(&mut self) {
        if *self == Self::MAX {
            *self = Self::INITIAL;
        } else {
            self.0 = self.0.saturating_add(1);
        }
    }
}

#[allow(clippy::enum_variant_names)]
#[derive(Serialize, Deserialize)]
enum RpcMessageKind {
    ExpectsResponse,
    ExpectsNoResponse,
    IsResponse,
}

#[derive(Serialize, Deserialize)]
struct RpcHeader {
    body_length: u32,
    message_id: RpcMessageId,
    kind: RpcMessageKind,
}

const GIGABYTE: usize = 1024 * 1024 * 1024;

/// The maximum size of the serialized RpcHeader
const RPC_HEADER_SIZE: usize = 4 + 4 + 4;

/// The maximum size of an RPC body
const RPC_BODY_MAX: usize = 2 * GIGABYTE;

type RpcRegistryCallback = Box<dyn FnOnce(&[u8]) -> Result<()> + Send>;

struct RpcRegistry {
    pending_requests: HashMap<RpcMessageId, RpcRegistryCallback>,
    next_message_id: RpcMessageId,
}

impl RpcRegistry {
    fn new() -> Self {
        Self {
            pending_requests: Default::default(),
            next_message_id: RpcMessageId::INITIAL,
        }
    }

    fn next_message_id(&mut self) -> RpcMessageId {
        let message_id = self.next_message_id;
        self.next_message_id.incr();
        message_id
    }

    fn remove_request(&mut self, message_id: RpcMessageId) -> Result<RpcRegistryCallback> {
        self.pending_requests
            .remove(&message_id)
            .ok_or_else(|| anyhow!("received response RPC which didn't have matching request"))
    }

    fn add_request<ResponseT: DeserializeOwned>(
        &mut self,
        callback: impl FnOnce(ResponseT) + Send + 'static,
    ) -> RpcMessageId {
        let message_id = self.next_message_id();

        let inserted = self
            .pending_requests
            .insert(
                message_id,
                Box::new(move |body_bytes| {
                    let response: ResponseT =
                        bincode::deserialize(body_bytes).with_context(|| {
                            format!("error deserializing {}", std::any::type_name::<ResponseT>())
                        })?;
                    callback(response);
                    Ok(())
                }),
            )
            .is_none();

        assert!(inserted, "RPC message_id reuse");

        message_id
    }
}

pub struct RpcSender<StreamT> {
    stream: Arc<TokioMutex<StreamT>>,
    registry: Arc<Mutex<RpcRegistry>>,
    tx_messages: Counter<u64>,
}

impl<StreamT> Clone for RpcSender<StreamT> {
    fn clone(&self) -> Self {
        Self {
            stream: self.stream.clone(),
            registry: self.registry.clone(),
            tx_messages: self.tx_messages.clone(),
        }
    }
}

impl<StreamT: AsyncWrite + Unpin> RpcSender<StreamT> {
    fn new(stream: StreamT, registry: Arc<Mutex<RpcRegistry>>, meter: Meter) -> Self {
        let tx_messages = meter.u64_counter("tx_messages").build();

        Self {
            stream: Arc::new(TokioMutex::new(stream)),
            tx_messages,
            registry,
        }
    }

    async fn send(
        &self,
        msg: &impl Serialize,
        message_id: RpcMessageId,
        kind: RpcMessageKind,
    ) -> Result<()> {
        // Serialize the body
        let mut buffer = vec![0; RPC_HEADER_SIZE];
        bincode::serialize_into(&mut buffer, msg).unwrap();

        // Craft the header
        let body_length = buffer.len() - RPC_HEADER_SIZE;
        if body_length > RPC_BODY_MAX {
            bail!("sending RPC request with too large of a body");
        }

        let header = RpcHeader {
            body_length: body_length as u32,
            message_id,
            kind,
        };
        bincode::serialize_into(&mut buffer[0..RPC_HEADER_SIZE], &header).unwrap();

        // Send the message
        self.stream
            .lock()
            .await
            .write_all(&buffer)
            .await
            .context("error sending RPC message")?;

        self.tx_messages.add(1, &[]);

        Ok(())
    }
}

async fn read_detecting_clean_eof(
    stream: &mut (impl AsyncRead + Unpin),
    buffer: &mut [u8],
) -> Result<bool> {
    let mut i = 0;
    while i < buffer.len() {
        let read = stream.read(&mut buffer[i..]).await?;

        if read == 0 {
            if i == 0 {
                // if we get no data on the first read, the socket was cleanly closed.
                return Ok(true);
            } else {
                // if we get no data in the middle of reading, this is unexpected.
                return Err(std::io::Error::from(std::io::ErrorKind::UnexpectedEof).into());
            }
        }
        i += read;
    }

    Ok(false)
}

pub struct RpcReceiver<StreamT> {
    stream: StreamT,
    registry: Arc<Mutex<RpcRegistry>>,
    rx_messages: Counter<u64>,
}

impl<StreamT: AsyncRead + Unpin> RpcReceiver<StreamT> {
    fn new(stream: StreamT, registry: Arc<Mutex<RpcRegistry>>, meter: Meter) -> Self {
        let rx_messages = meter.u64_counter("rx_messages").build();

        Self {
            stream,
            registry,
            rx_messages,
        }
    }

    /// Reads and handles one RPC message. Returns true if the socket is still open.
    async fn receive_one<RemoteMsgT: DeserializeOwned, FutT: Future<Output = ()>>(
        &mut self,
        mut remote_msg_callback: impl FnMut(RemoteMsgT, Option<RpcMessageId>) -> FutT,
    ) -> Result<bool> {
        // Read the header
        let mut buffer = [0; RPC_HEADER_SIZE];
        let clean_eof = read_detecting_clean_eof(&mut self.stream, &mut buffer).await?;
        if clean_eof {
            return Ok(false);
        }

        let header: RpcHeader =
            bincode::deserialize(&buffer).context("received invalid RPC header")?;

        if header.body_length as usize > RPC_BODY_MAX {
            bail!(
                "received RPC with message body of length {} which is > {RPC_BODY_MAX}",
                header.body_length
            );
        }

        // Read the body
        let mut body = vec![0; header.body_length as usize];
        self.stream
            .read_exact(&mut body)
            .await
            .context("error reading RPC body")?;

        self.rx_messages.add(1, &[]);

        match header.kind {
            RpcMessageKind::ExpectsResponse => {
                let msg: RemoteMsgT = bincode::deserialize(&body).with_context(|| {
                    format!(
                        "error deserializing {}",
                        std::any::type_name::<RemoteMsgT>()
                    )
                })?;
                remote_msg_callback(msg, Some(header.message_id)).await;
            }
            RpcMessageKind::ExpectsNoResponse => {
                let msg: RemoteMsgT = bincode::deserialize(&body).with_context(|| {
                    format!(
                        "error deserializing {}",
                        std::any::type_name::<RemoteMsgT>()
                    )
                })?;
                remote_msg_callback(msg, None).await;
            }
            RpcMessageKind::IsResponse => {
                let callback = self
                    .registry
                    .lock()
                    .unwrap()
                    .remove_request(header.message_id)?;
                callback(&body)?;
            }
        }

        Ok(true)
    }
}

impl RpcStream for TcpStream {
    type ReadHalf = tcp::OwnedReadHalf;
    type WriteHalf = tcp::OwnedWriteHalf;

    fn into_split(self) -> (Self::ReadHalf, Self::WriteHalf) {
        TcpStream::into_split(self)
    }
}

impl RpcStream for UnixStream {
    type ReadHalf = unix::OwnedReadHalf;
    type WriteHalf = unix::OwnedWriteHalf;

    fn into_split(self) -> (Self::ReadHalf, Self::WriteHalf) {
        UnixStream::into_split(self)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use assert_matches::assert_matches;
    use opentelemetry::metrics::MeterProvider as _;
    use opentelemetry_sdk::metrics::{
        data::{AggregatedMetrics, MetricData, ResourceMetrics},
        in_memory_exporter::InMemoryMetricExporter,
        PeriodicReader, SdkMeterProvider,
    };
    use tokio::sync::mpsc::{unbounded_channel, UnboundedReceiver};

    #[test]
    fn header_serialization() {
        // bincode has variable sized integer encoding.
        let max_header = RpcHeader {
            body_length: u32::MAX,
            message_id: RpcMessageId::MAX,
            kind: RpcMessageKind::IsResponse,
        };
        let serialized = bincode::serialize(&max_header).unwrap();

        assert_eq!(serialized.len(), RPC_HEADER_SIZE);
    }

    #[derive(Serialize, Deserialize, PartialEq, Eq, Debug)]
    enum Request {
        A,
        B,
    }

    #[derive(Serialize, Deserialize, PartialEq, Eq, Debug)]
    struct Response {
        message: String,
    }

    fn get_metric(metrics: &[ResourceMetrics], name: &str) -> u64 {
        let metric = metrics[0]
            .scope_metrics()
            .next()
            .unwrap()
            .metrics()
            .find(|m| m.name() == name)
            .unwrap();
        let sum = assert_matches!(metric.data(), AggregatedMetrics::U64(MetricData::Sum(s)) => s);
        sum.data_points().map(|p| p.value()).sum()
    }

    struct Fixture {
        sender_a: RpcSender<unix::OwnedWriteHalf>,
        sender_b: RpcSender<unix::OwnedWriteHalf>,
        receiver_a: RpcReceiver<unix::OwnedReadHalf>,
        receiver_b: RpcReceiver<unix::OwnedReadHalf>,

        exporter: InMemoryMetricExporter,
        meter_provider: SdkMeterProvider,
    }

    impl Fixture {
        async fn new() -> Self {
            let exporter = InMemoryMetricExporter::default();
            let meter_provider = SdkMeterProvider::builder()
                .with_reader(PeriodicReader::builder(exporter.clone()).build())
                .build();
            let meter = meter_provider.meter("r0vm");

            let (a, b) = UnixStream::pair().unwrap();
            let (sender_a, receiver_a) = rpc_system(a, meter.clone());
            let (sender_b, receiver_b) = rpc_system(b, meter);
            Self {
                sender_a,
                sender_b,
                receiver_a,
                receiver_b,
                exporter,
                meter_provider,
            }
        }

        async fn ask_a<RequestT: Serialize, ResponseT: DeserializeOwned + Send + 'static>(
            &mut self,
            req: &RequestT,
        ) -> UnboundedReceiver<ResponseT> {
            let (send, recv) = unbounded_channel();

            self.sender_a
                .ask(req, move |res: ResponseT| send.send(res).unwrap())
                .await
                .unwrap();

            recv
        }

        async fn receive_b<RequestT: DeserializeOwned + Send>(
            &mut self,
        ) -> Result<(RequestT, Option<RpcMessageId>)> {
            let (send, mut recv) = unbounded_channel();

            let socket_open = self
                .receiver_b
                .receive_one(move |req: RequestT, message_id| {
                    let send = send.clone();
                    async move {
                        send.send((req, message_id)).unwrap();
                    }
                })
                .await?;
            assert!(socket_open);

            Ok(recv.try_recv().unwrap())
        }

        async fn receive_b_response(&mut self) -> Result<()> {
            let socket_open = self
                .receiver_b
                .receive_one(move |_: (), _| async { panic!() })
                .await?;
            assert!(socket_open);

            Ok(())
        }

        async fn receive_a_response(&mut self) -> Result<()> {
            let socket_open = self
                .receiver_a
                .receive_one(move |_: (), _| async { panic!() })
                .await?;
            assert!(socket_open);
            Ok(())
        }

        fn tx_and_rx_messages_metrics(&self) -> (u64, u64) {
            self.meter_provider.force_flush().unwrap();
            let finished_metrics = self.exporter.get_finished_metrics().unwrap();
            (
                get_metric(&finished_metrics, "tx_messages"),
                get_metric(&finished_metrics, "rx_messages"),
            )
        }
    }

    #[tokio::test]
    async fn ask() {
        let mut fix = Fixture::new().await;

        let mut ask_recv: UnboundedReceiver<Response> = fix.ask_a(&Request::A).await;

        let (req, message_id): (Request, _) = fix.receive_b().await.unwrap();
        fix.sender_b
            .respond(
                &Response {
                    message: format!("hello {req:?}"),
                },
                message_id.unwrap(),
            )
            .await
            .unwrap();

        fix.receive_a_response().await.unwrap();
        let res = ask_recv.try_recv().unwrap();
        assert_eq!(
            res,
            Response {
                message: "hello A".into()
            }
        );

        assert_eq!(fix.tx_and_rx_messages_metrics(), (2, 2));
    }

    #[tokio::test]
    async fn tell() {
        let mut fix = Fixture::new().await;

        fix.sender_a.tell(&Request::A).await.unwrap();

        let (req, message_id): (Request, _) = fix.receive_b().await.unwrap();
        assert_eq!(req, Request::A);
        assert!(message_id.is_none());

        assert_eq!(fix.tx_and_rx_messages_metrics(), (1, 1));
    }

    #[tokio::test]
    async fn unsolicited_response() {
        let mut fix = Fixture::new().await;

        fix.sender_a
            .respond(
                &Response {
                    message: "hi".into(),
                },
                RpcMessageId::INITIAL,
            )
            .await
            .unwrap();
        assert_eq!(
            fix.receive_b_response().await.unwrap_err().to_string(),
            "received response RPC which didn't have matching request"
        );

        assert_eq!(fix.tx_and_rx_messages_metrics(), (1, 1));
    }

    #[tokio::test]
    async fn socket_close() {
        let mut fix = Fixture::new().await;

        drop(fix.sender_a);

        let socket_open = fix
            .receiver_b
            .receive_one(move |_: (), _| async { panic!() })
            .await
            .unwrap();
        assert!(!socket_open);
    }
}
