/// Calls that the zkvm runtime provides.  These function signatures
/// and symbols must match the ones in risc0_zkvm_guest::abi.

// Number of u32 wors in a SHA digest.
const DIGEST_WORDS: usize = 8;

extern "Rust" {
    #[link_name = "zkvm_sha_raw_digest"]
    fn _sha_raw_digest(data: &[u32]) -> &'static [u32; DIGEST_WORDS];

    #[link_name = "zkvm_sha_digest_u8_slice"]
    fn _sha_digest_u8_slice(data: &[u8]) -> &'static [u32; DIGEST_WORDS];

    #[link_name = "zkvm_host_sendrecv"]
    fn _host_sendrecv(channel: u32, buf: &[u8]) -> (&'static [u32], usize);
}

// SAFETY: These functnion signatures defined above should exactly
// match the ones defined in risc0_zkvm_guest::abi.

/// Computes a raw digest of the given slice without adding a SHA end
/// marker or trailer.
pub fn sha_raw_digest(data: &[u32]) -> &'static [u32; DIGEST_WORDS] {
    unsafe { _sha_raw_digest(data) }
}

/// Makes a digest for a slice of bytes, padding to SHA block length
/// and adding the SHA end marker and trailer.
pub fn sha_digest_u8_slice(data: &[u8]) -> &'static [u32; DIGEST_WORDS] {
    unsafe { _sha_digest_u8_slice(data) }
}

/// Interacts with the host.  'channel' specifies the ZKVM channel to
/// use, and 'buf' provides the data to tsend to the host.
///
/// The returned tuple contains a slice of 32-bit words from the host,
/// and a size in bytes of the returned data.  The size in bytes might
/// not match the length of the returned slice * WORD_SIZE in the case
/// that the returned buffer does not fall on a word boundry.
pub fn host_sendrecv(channel: u32, buf: &[u8]) -> (&'static [u32], usize) {
    unsafe { _host_sendrecv(channel, buf) }
}
