/// Calls that the guest runtime provides.  These function signatures
/// and symbols must match the ones in risc0_zkvm_platform::abi.

// Number of u32 words in a SHA digest.
const DIGEST_WORDS: usize = 8;

#[export_name = "zkvm_sha_raw_digest"]
pub fn sha_raw_digest(data: &[u32]) -> &'static [u32; DIGEST_WORDS] {
    bytemuck::cast_ref(crate::sha::raw_digest(data))
}

#[export_name = "zkvm_sha_digest_u8_slice"]
pub fn sha_digest_u8_slice(data: &[u8]) -> &'static [u32; DIGEST_WORDS] {
    bytemuck::cast_ref(crate::sha::digest_u8_slice(data))
}

#[export_name = "zkvm_host_sendrecv"]
pub fn host_sendrecv(channel: u32, buf: &[u8]) -> (&'static [u32], usize) {
    crate::io::host_sendrecv(channel, buf)
}
