// This file is @generated by prost-build.
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ServerRequest {
    #[prost(
        oneof = "server_request::Kind",
        tags = "1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12"
    )]
    pub kind: ::core::option::Option<server_request::Kind>,
}
/// Nested message and enum types in `ServerRequest`.
pub mod server_request {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Execute(super::ExecuteRequest),
        #[prost(message, tag = "2")]
        Prove(super::ProveRequest),
        #[prost(message, tag = "3")]
        ProveSegment(super::ProveSegmentRequest),
        #[prost(message, tag = "4")]
        Lift(super::LiftRequest),
        #[prost(message, tag = "5")]
        Join(super::JoinRequest),
        #[prost(message, tag = "6")]
        IdentityP254(super::IdentityP254Request),
        #[prost(message, tag = "7")]
        Resolve(super::ResolveRequest),
        #[prost(message, tag = "8")]
        Compress(super::CompressRequest),
        #[prost(message, tag = "9")]
        Verify(super::VerifyRequest),
        #[prost(message, tag = "11")]
        ProveKeccak(super::ProveKeccakRequest),
        #[prost(message, tag = "12")]
        Union(super::UnionRequest),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct HelloRequest {
    #[prost(message, optional, tag = "1")]
    pub version: ::core::option::Option<super::base::SemanticVersion>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct HelloReply {
    #[prost(oneof = "hello_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<hello_reply::Kind>,
}
/// Nested message and enum types in `HelloReply`.
pub mod hello_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(super::HelloResult),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct HelloResult {
    #[prost(message, optional, tag = "1")]
    pub version: ::core::option::Option<super::base::SemanticVersion>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ExecuteRequest {
    #[prost(message, optional, tag = "1")]
    pub env: ::core::option::Option<ExecutorEnv>,
    #[prost(message, optional, tag = "2")]
    pub segments_out: ::core::option::Option<AssetRequest>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ProveRequest {
    #[prost(message, optional, tag = "1")]
    pub env: ::core::option::Option<ExecutorEnv>,
    #[prost(message, optional, tag = "2")]
    pub opts: ::core::option::Option<ProverOpts>,
    #[prost(message, optional, tag = "3")]
    pub receipt_out: ::core::option::Option<AssetRequest>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ProveSegmentRequest {
    #[prost(message, optional, tag = "1")]
    pub opts: ::core::option::Option<ProverOpts>,
    #[prost(message, optional, tag = "2")]
    pub segment: ::core::option::Option<Asset>,
    #[prost(message, optional, tag = "3")]
    pub receipt_out: ::core::option::Option<AssetRequest>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ProveSegmentReply {
    #[prost(oneof = "prove_segment_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<prove_segment_reply::Kind>,
}
/// Nested message and enum types in `ProveSegmentReply`.
pub mod prove_segment_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(super::ProveSegmentResult),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ProveZkrReply {
    #[prost(oneof = "prove_zkr_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<prove_zkr_reply::Kind>,
}
/// Nested message and enum types in `ProveZkrReply`.
pub mod prove_zkr_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(super::ProveZkrResult),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ProveZkrResult {
    #[prost(message, optional, tag = "1")]
    pub receipt: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ProveKeccakRequest {
    #[prost(message, optional, tag = "1")]
    pub claim_digest: ::core::option::Option<super::base::Digest>,
    #[prost(uint32, tag = "2")]
    pub po2: u32,
    #[prost(message, optional, tag = "3")]
    pub control_root: ::core::option::Option<super::base::Digest>,
    #[prost(bytes = "vec", tag = "4")]
    pub input: ::prost::alloc::vec::Vec<u8>,
    /// This is optional in the context of a CoprocessorRequest
    #[prost(message, optional, tag = "5")]
    pub receipt_out: ::core::option::Option<AssetRequest>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ProveKeccakReply {
    #[prost(oneof = "prove_keccak_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<prove_keccak_reply::Kind>,
}
/// Nested message and enum types in `ProveKeccakReply`.
pub mod prove_keccak_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(super::ProveKeccakResult),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ProveKeccakResult {
    #[prost(message, optional, tag = "1")]
    pub receipt: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct LiftRequest {
    #[prost(message, optional, tag = "1")]
    pub opts: ::core::option::Option<ProverOpts>,
    #[prost(message, optional, tag = "2")]
    pub receipt: ::core::option::Option<Asset>,
    #[prost(message, optional, tag = "3")]
    pub receipt_out: ::core::option::Option<AssetRequest>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct LiftReply {
    #[prost(oneof = "lift_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<lift_reply::Kind>,
}
/// Nested message and enum types in `LiftReply`.
pub mod lift_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(super::LiftResult),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct LiftResult {
    #[prost(message, optional, tag = "1")]
    pub receipt: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct JoinRequest {
    #[prost(message, optional, tag = "1")]
    pub opts: ::core::option::Option<ProverOpts>,
    #[prost(message, optional, tag = "2")]
    pub left_receipt: ::core::option::Option<Asset>,
    #[prost(message, optional, tag = "3")]
    pub right_receipt: ::core::option::Option<Asset>,
    #[prost(message, optional, tag = "4")]
    pub receipt_out: ::core::option::Option<AssetRequest>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct JoinReply {
    #[prost(oneof = "join_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<join_reply::Kind>,
}
/// Nested message and enum types in `JoinReply`.
pub mod join_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(super::JoinResult),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct JoinResult {
    #[prost(message, optional, tag = "1")]
    pub receipt: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct UnionRequest {
    #[prost(message, optional, tag = "1")]
    pub opts: ::core::option::Option<ProverOpts>,
    #[prost(message, optional, tag = "2")]
    pub left_receipt: ::core::option::Option<Asset>,
    #[prost(message, optional, tag = "3")]
    pub right_receipt: ::core::option::Option<Asset>,
    #[prost(message, optional, tag = "4")]
    pub receipt_out: ::core::option::Option<AssetRequest>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct UnionReply {
    #[prost(oneof = "union_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<union_reply::Kind>,
}
/// Nested message and enum types in `UnionReply`.
pub mod union_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(super::UnionResult),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct UnionResult {
    #[prost(message, optional, tag = "1")]
    pub receipt: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ResolveRequest {
    #[prost(message, optional, tag = "1")]
    pub opts: ::core::option::Option<ProverOpts>,
    #[prost(message, optional, tag = "2")]
    pub conditional_receipt: ::core::option::Option<Asset>,
    #[prost(message, optional, tag = "3")]
    pub assumption_receipt: ::core::option::Option<Asset>,
    #[prost(message, optional, tag = "4")]
    pub receipt_out: ::core::option::Option<AssetRequest>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ResolveReply {
    #[prost(oneof = "resolve_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<resolve_reply::Kind>,
}
/// Nested message and enum types in `ResolveReply`.
pub mod resolve_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(super::ResolveResult),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ResolveResult {
    #[prost(message, optional, tag = "1")]
    pub receipt: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct IdentityP254Request {
    #[prost(message, optional, tag = "1")]
    pub opts: ::core::option::Option<ProverOpts>,
    #[prost(message, optional, tag = "2")]
    pub receipt: ::core::option::Option<Asset>,
    #[prost(message, optional, tag = "3")]
    pub receipt_out: ::core::option::Option<AssetRequest>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct IdentityP254Reply {
    #[prost(oneof = "identity_p254_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<identity_p254_reply::Kind>,
}
/// Nested message and enum types in `IdentityP254Reply`.
pub mod identity_p254_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(super::IdentityP254Result),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct IdentityP254Result {
    #[prost(message, optional, tag = "1")]
    pub receipt: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct CompressRequest {
    #[prost(message, optional, tag = "1")]
    pub opts: ::core::option::Option<ProverOpts>,
    #[prost(message, optional, tag = "2")]
    pub receipt: ::core::option::Option<Asset>,
    #[prost(message, optional, tag = "3")]
    pub receipt_out: ::core::option::Option<AssetRequest>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct CompressReply {
    #[prost(oneof = "compress_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<compress_reply::Kind>,
}
/// Nested message and enum types in `CompressReply`.
pub mod compress_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(super::CompressResult),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct CompressResult {
    #[prost(message, optional, tag = "1")]
    pub receipt: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct VerifyRequest {
    #[prost(message, optional, tag = "1")]
    pub receipt: ::core::option::Option<Asset>,
    #[prost(message, optional, tag = "2")]
    pub image_id: ::core::option::Option<super::base::Digest>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ExecutorEnv {
    #[prost(message, optional, tag = "1")]
    pub binary: ::core::option::Option<Asset>,
    #[prost(map = "string, string", tag = "2")]
    pub env_vars:
        ::std::collections::HashMap<::prost::alloc::string::String, ::prost::alloc::string::String>,
    #[prost(string, repeated, tag = "3")]
    pub slice_ios: ::prost::alloc::vec::Vec<::prost::alloc::string::String>,
    #[prost(uint32, repeated, tag = "4")]
    pub read_fds: ::prost::alloc::vec::Vec<u32>,
    #[prost(uint32, repeated, tag = "5")]
    pub write_fds: ::prost::alloc::vec::Vec<u32>,
    #[prost(uint32, optional, tag = "6")]
    pub segment_limit_po2: ::core::option::Option<u32>,
    #[prost(uint64, optional, tag = "7")]
    pub session_limit: ::core::option::Option<u64>,
    #[prost(string, repeated, tag = "8")]
    pub args: ::prost::alloc::vec::Vec<::prost::alloc::string::String>,
    /// When present, trace events will be sent back to the client.
    #[prost(message, optional, tag = "9")]
    pub trace_events: ::core::option::Option<()>,
    #[prost(string, tag = "10")]
    pub pprof_out: ::prost::alloc::string::String,
    #[prost(message, repeated, tag = "11")]
    pub assumptions: ::prost::alloc::vec::Vec<AssumptionReceipt>,
    #[prost(string, tag = "12")]
    pub segment_path: ::prost::alloc::string::String,
    #[prost(bool, tag = "13")]
    pub coprocessor: bool,
    #[prost(uint32, optional, tag = "14")]
    pub keccak_max_po2: ::core::option::Option<u32>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct AssumptionReceipt {
    #[prost(oneof = "assumption_receipt::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<assumption_receipt::Kind>,
}
/// Nested message and enum types in `AssumptionReceipt`.
pub mod assumption_receipt {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        /// InnerReceipt
        #[prost(message, tag = "1")]
        Proven(super::Asset),
        /// Assumption
        #[prost(message, tag = "2")]
        Unresolved(super::Asset),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ProverOpts {
    #[prost(string, tag = "1")]
    pub hashfn: ::prost::alloc::string::String,
    #[prost(bool, tag = "2")]
    pub prove_guest_errors: bool,
    #[prost(enumeration = "ReceiptKind", tag = "3")]
    pub receipt_kind: i32,
    #[prost(message, repeated, tag = "4")]
    pub control_ids: ::prost::alloc::vec::Vec<super::base::Digest>,
    #[prost(uint64, tag = "5")]
    pub max_segment_po2: u64,
    #[prost(bool, tag = "6")]
    pub is_dev_mode: bool,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct SessionInfo {
    #[prost(uint32, tag = "1")]
    pub segments: u32,
    #[prost(bytes = "vec", tag = "2")]
    pub journal: ::prost::alloc::vec::Vec<u8>,
    #[prost(message, optional, tag = "3")]
    pub exit_code: ::core::option::Option<super::base::ExitCode>,
    #[prost(message, optional, tag = "4")]
    pub receipt_claim: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct SegmentInfo {
    #[prost(uint32, tag = "1")]
    pub index: u32,
    #[prost(uint32, tag = "2")]
    pub po2: u32,
    #[prost(uint32, tag = "3")]
    pub cycles: u32,
    #[prost(message, optional, tag = "4")]
    pub segment: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ProveSegmentResult {
    #[prost(message, optional, tag = "1")]
    pub receipt: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct RedisParams {
    #[prost(string, tag = "1")]
    pub url: ::prost::alloc::string::String,
    #[prost(string, tag = "2")]
    pub key: ::prost::alloc::string::String,
    #[prost(uint64, tag = "3")]
    pub ttl: u64,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
#[prost(skip_debug)]
pub struct Asset {
    #[prost(oneof = "asset::Kind", tags = "1, 2, 3")]
    pub kind: ::core::option::Option<asset::Kind>,
}
/// Nested message and enum types in `Asset`.
pub mod asset {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    #[prost(skip_debug)]
    pub enum Kind {
        #[prost(bytes, tag = "1")]
        Inline(::prost::alloc::vec::Vec<u8>),
        #[prost(string, tag = "2")]
        Path(::prost::alloc::string::String),
        #[prost(string, tag = "3")]
        Redis(::prost::alloc::string::String),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct AssetRequest {
    #[prost(oneof = "asset_request::Kind", tags = "1, 2, 3")]
    pub kind: ::core::option::Option<asset_request::Kind>,
}
/// Nested message and enum types in `AssetRequest`.
pub mod asset_request {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Inline(()),
        #[prost(string, tag = "2")]
        Path(::prost::alloc::string::String),
        #[prost(message, tag = "3")]
        Redis(super::RedisParams),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ServerReply {
    #[prost(oneof = "server_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<server_reply::Kind>,
}
/// Nested message and enum types in `ServerReply`.
pub mod server_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(super::ClientCallback),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct ClientCallback {
    #[prost(oneof = "client_callback::Kind", tags = "1, 2, 3, 4")]
    pub kind: ::core::option::Option<client_callback::Kind>,
}
/// Nested message and enum types in `ClientCallback`.
pub mod client_callback {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Io(super::OnIoRequest),
        #[prost(message, tag = "2")]
        SegmentDone(super::OnSegmentDone),
        #[prost(message, tag = "3")]
        SessionDone(super::OnSessionDone),
        #[prost(message, tag = "4")]
        ProveDone(super::OnProveDone),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct OnIoRequest {
    #[prost(oneof = "on_io_request::Kind", tags = "1, 2, 3, 4")]
    pub kind: ::core::option::Option<on_io_request::Kind>,
}
/// Nested message and enum types in `OnIoRequest`.
pub mod on_io_request {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Posix(super::PosixIo),
        #[prost(message, tag = "2")]
        Slice(super::SliceIo),
        #[prost(message, tag = "3")]
        Trace(super::TraceEvent),
        #[prost(message, tag = "4")]
        Coprocessor(super::CoprocessorRequest),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
#[prost(skip_debug)]
pub struct SliceIo {
    #[prost(string, tag = "1")]
    pub name: ::prost::alloc::string::String,
    #[prost(bytes = "vec", tag = "2")]
    pub from_guest: ::prost::alloc::vec::Vec<u8>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct PosixIo {
    #[prost(uint32, tag = "1")]
    pub fd: u32,
    #[prost(message, optional, tag = "2")]
    pub cmd: ::core::option::Option<PosixCmd>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
#[prost(skip_debug)]
pub struct PosixCmd {
    #[prost(oneof = "posix_cmd::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<posix_cmd::Kind>,
}
/// Nested message and enum types in `PosixCmd`.
pub mod posix_cmd {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    #[prost(skip_debug)]
    pub enum Kind {
        #[prost(uint32, tag = "1")]
        Read(u32),
        #[prost(bytes, tag = "2")]
        Write(::prost::alloc::vec::Vec<u8>),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct TraceEvent {
    #[prost(oneof = "trace_event::Kind", tags = "1, 2, 3, 4, 5")]
    pub kind: ::core::option::Option<trace_event::Kind>,
}
/// Nested message and enum types in `TraceEvent`.
pub mod trace_event {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Message)]
    pub struct InstructionStart {
        #[prost(uint64, tag = "1")]
        pub cycle: u64,
        #[prost(uint32, tag = "2")]
        pub pc: u32,
        #[prost(uint32, tag = "3")]
        pub insn: u32,
    }
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Message)]
    pub struct RegisterSet {
        #[prost(uint32, tag = "1")]
        pub idx: u32,
        #[prost(uint32, tag = "2")]
        pub value: u32,
    }
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Message)]
    pub struct MemorySet {
        #[prost(uint32, tag = "1")]
        pub addr: u32,
        #[prost(uint32, tag = "2")]
        pub value: u32,
        #[prost(bytes = "vec", tag = "3")]
        pub region: ::prost::alloc::vec::Vec<u8>,
    }
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Message)]
    pub struct PageIn {
        #[prost(uint64, tag = "1")]
        pub cycles: u64,
    }
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Message)]
    pub struct PageOut {
        #[prost(uint64, tag = "1")]
        pub cycles: u64,
    }
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        InsnStart(InstructionStart),
        #[prost(message, tag = "2")]
        RegisterSet(RegisterSet),
        #[prost(message, tag = "3")]
        MemorySet(MemorySet),
        #[prost(message, tag = "4")]
        PageIn(PageIn),
        #[prost(message, tag = "5")]
        PageOut(PageOut),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct CoprocessorRequest {
    #[prost(oneof = "coprocessor_request::Kind", tags = "2")]
    pub kind: ::core::option::Option<coprocessor_request::Kind>,
}
/// Nested message and enum types in `CoprocessorRequest`.
pub mod coprocessor_request {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "2")]
        ProveKeccak(super::ProveKeccakRequest),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
#[prost(skip_debug)]
pub struct OnIoReply {
    #[prost(oneof = "on_io_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<on_io_reply::Kind>,
}
/// Nested message and enum types in `OnIoReply`.
pub mod on_io_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    #[prost(skip_debug)]
    pub enum Kind {
        #[prost(bytes, tag = "1")]
        Ok(::prost::alloc::vec::Vec<u8>),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct OnSegmentDone {
    #[prost(message, optional, tag = "1")]
    pub segment: ::core::option::Option<SegmentInfo>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct OnSessionDone {
    #[prost(message, optional, tag = "1")]
    pub session: ::core::option::Option<SessionInfo>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct OnProveDone {
    #[prost(message, optional, tag = "1")]
    pub prove_info: ::core::option::Option<Asset>,
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct GenericReply {
    #[prost(oneof = "generic_reply::Kind", tags = "1, 2")]
    pub kind: ::core::option::Option<generic_reply::Kind>,
}
/// Nested message and enum types in `GenericReply`.
pub mod generic_reply {
    #[allow(clippy::derive_partial_eq_without_eq)]
    #[derive(Clone, PartialEq, ::prost::Oneof)]
    pub enum Kind {
        #[prost(message, tag = "1")]
        Ok(()),
        #[prost(message, tag = "2")]
        Error(super::GenericError),
    }
}
#[allow(clippy::derive_partial_eq_without_eq)]
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct GenericError {
    #[prost(string, tag = "1")]
    pub reason: ::prost::alloc::string::String,
}
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, ::prost::Enumeration)]
#[repr(i32)]
pub enum ReceiptKind {
    Composite = 0,
    Succinct = 1,
    Groth16 = 2,
}
impl ReceiptKind {
    /// String value of the enum field names used in the ProtoBuf definition.
    ///
    /// The values are not transformed in any way and thus are considered stable
    /// (if the ProtoBuf definition does not change) and safe for programmatic use.
    pub fn as_str_name(&self) -> &'static str {
        match self {
            ReceiptKind::Composite => "COMPOSITE",
            ReceiptKind::Succinct => "SUCCINCT",
            ReceiptKind::Groth16 => "GROTH16",
        }
    }
    /// Creates an enum from field names used in the ProtoBuf definition.
    pub fn from_str_name(value: &str) -> ::core::option::Option<Self> {
        match value {
            "COMPOSITE" => Some(Self::Composite),
            "SUCCINCT" => Some(Self::Succinct),
            "GROTH16" => Some(Self::Groth16),
            _ => None,
        }
    }
}
