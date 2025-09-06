// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{
    io,
    pin::{Pin, pin},
    task::{Context, Poll},
};

use opentelemetry::metrics::{Counter, Meter};
use tokio::io::{AsyncRead, AsyncWrite, ReadBuf};

use super::rpc;

pub struct StreamWithMetrics<StreamT: rpc::RpcStream> {
    read_half: OwnedReadHalfWithMetrics<StreamT::ReadHalf>,
    write_half: OwnedWriteHalfWithMetrics<StreamT::WriteHalf>,
}

impl<StreamT: rpc::RpcStream> StreamWithMetrics<StreamT> {
    pub fn new(stream: StreamT, meter: Meter) -> Self {
        let tx_bytes = meter.u64_counter("tx_bytes").with_unit("bytes").build();
        let rx_bytes = meter.u64_counter("rx_bytes").with_unit("bytes").build();
        let (read_half, write_half) = stream.into_split();

        Self {
            read_half: OwnedReadHalfWithMetrics {
                stream: read_half,
                rx_bytes,
            },
            write_half: OwnedWriteHalfWithMetrics {
                stream: write_half,
                tx_bytes,
            },
        }
    }
}

impl<StreamT: rpc::RpcStream> rpc::RpcStream for StreamWithMetrics<StreamT> {
    type ReadHalf = OwnedReadHalfWithMetrics<StreamT::ReadHalf>;
    type WriteHalf = OwnedWriteHalfWithMetrics<StreamT::WriteHalf>;

    fn into_split(self) -> (Self::ReadHalf, Self::WriteHalf) {
        (self.read_half, self.write_half)
    }
}

pub struct OwnedReadHalfWithMetrics<StreamT> {
    stream: StreamT,
    rx_bytes: Counter<u64>,
}

pub struct OwnedWriteHalfWithMetrics<StreamT> {
    stream: StreamT,
    tx_bytes: Counter<u64>,
}

impl<StreamT: AsyncRead + Unpin> AsyncRead for OwnedReadHalfWithMetrics<StreamT> {
    fn poll_read(
        self: Pin<&mut Self>,
        cx: &mut Context<'_>,
        dst: &mut ReadBuf<'_>,
    ) -> Poll<io::Result<()>> {
        let start_len = dst.filled().len();
        let me = self.get_mut();
        let res = AsyncRead::poll_read(pin!(&mut me.stream), cx, dst);
        if matches!(res, Poll::Ready(Ok(_))) {
            let len = dst.filled().len() - start_len;
            me.rx_bytes.add(len as u64, &[]);
        }
        res
    }
}

impl<StreamT: AsyncWrite + Unpin> AsyncWrite for OwnedWriteHalfWithMetrics<StreamT> {
    fn poll_write(
        self: Pin<&mut Self>,
        cx: &mut Context<'_>,
        src: &[u8],
    ) -> Poll<io::Result<usize>> {
        let me = self.get_mut();
        let res = AsyncWrite::poll_write(pin!(&mut me.stream), cx, src);
        if let Poll::Ready(Ok(len)) = &res {
            me.tx_bytes.add(*len as u64, &[]);
        }
        res
    }

    fn poll_flush(self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Result<(), io::Error>> {
        let me = self.get_mut();
        AsyncWrite::poll_flush(pin!(&mut me.stream), cx)
    }

    fn poll_shutdown(self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Result<(), io::Error>> {
        let me = self.get_mut();
        AsyncWrite::poll_shutdown(pin!(&mut me.stream), cx)
    }
}

impl<StreamT: rpc::RpcStream> AsyncRead for StreamWithMetrics<StreamT> {
    fn poll_read(
        self: Pin<&mut Self>,
        cx: &mut Context<'_>,
        dst: &mut ReadBuf<'_>,
    ) -> Poll<io::Result<()>> {
        let me = self.get_mut();
        AsyncRead::poll_read(pin!(&mut me.read_half), cx, dst)
    }
}

impl<StreamT: rpc::RpcStream> AsyncWrite for StreamWithMetrics<StreamT> {
    fn poll_write(
        self: Pin<&mut Self>,
        cx: &mut Context<'_>,
        src: &[u8],
    ) -> Poll<io::Result<usize>> {
        let me = self.get_mut();
        AsyncWrite::poll_write(pin!(&mut me.write_half), cx, src)
    }

    fn poll_flush(self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Result<(), io::Error>> {
        let me = self.get_mut();
        AsyncWrite::poll_flush(pin!(&mut me.write_half), cx)
    }

    fn poll_shutdown(self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Result<(), io::Error>> {
        let me = self.get_mut();
        AsyncWrite::poll_shutdown(pin!(&mut me.write_half), cx)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use assert_matches::assert_matches;
    use opentelemetry::metrics::MeterProvider as _;
    use opentelemetry_sdk::metrics::{
        PeriodicReader, SdkMeterProvider,
        data::{AggregatedMetrics, MetricData, ResourceMetrics},
        in_memory_exporter::InMemoryMetricExporter,
    };
    use tokio::io::{AsyncReadExt as _, AsyncWriteExt as _};
    use tokio::net::UnixStream;

    fn get_metric(metrics: &[ResourceMetrics], name: &str) -> u64 {
        assert_eq!(metrics.len(), 1);

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

    #[tokio::test]
    async fn tx_bytes() {
        let exporter = InMemoryMetricExporter::default();
        let meter_provider = SdkMeterProvider::builder()
            .with_reader(PeriodicReader::builder(exporter.clone()).build())
            .build();
        let meter = meter_provider.meter("r0vm");

        let (a, _b) = UnixStream::pair().unwrap();
        let mut stream_a = StreamWithMetrics::new(a, meter);
        stream_a.write_all(&[1, 2, 3, 4]).await.unwrap();

        meter_provider.force_flush().unwrap();

        let finished_metrics = exporter.get_finished_metrics().unwrap();

        let tx_bytes = get_metric(&finished_metrics, "tx_bytes");
        assert_eq!(tx_bytes, 4);
    }

    #[tokio::test]
    async fn rx_bytes() {
        let exporter = InMemoryMetricExporter::default();
        let meter_provider = SdkMeterProvider::builder()
            .with_reader(PeriodicReader::builder(exporter.clone()).build())
            .build();
        let meter = meter_provider.meter("r0vm");

        let (a, b) = UnixStream::pair().unwrap();
        let mut stream_a = StreamWithMetrics::new(a, meter.clone());
        stream_a.write_all(&[1, 2, 3, 4]).await.unwrap();

        let mut stream_b = StreamWithMetrics::new(b, meter);
        let mut buffer = [0; 4];
        stream_b.read_exact(&mut buffer).await.unwrap();

        meter_provider.force_flush().unwrap();

        let finished_metrics = exporter.get_finished_metrics().unwrap();

        let rx_bytes = get_metric(&finished_metrics, "rx_bytes");
        assert_eq!(rx_bytes, 4);
    }
}
