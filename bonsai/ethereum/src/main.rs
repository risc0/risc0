#[cfg(feature = "control-id")]
use risc0_zkvm::sha::Digest;
#[cfg(feature = "control-id")]
use risc0_zkvm::ALLOWED_IDS_ROOT;

/// Outputs the Control ID hash for the identity_p254 predicate
/// decomposed as implemented by splitDigest.
fn main() {
    #[cfg(feature = "control-id")]
    {
        let root = hex::decode(ALLOWED_IDS_ROOT).unwrap();
        let slice = root.as_slice();
        let mut digest: [u8; 32] = [0; 32];
        digest[..slice.len()].copy_from_slice(slice);
        let (a, b) = split_digest(Digest::from(digest));
        println!("CONTROL_ID_0: 0x{b}");
        println!("CONTROL_ID_1: 0x{a}");
    }
}

#[cfg(feature = "control-id")]
fn split_digest(d: Digest) -> (String, String) {
    let mut big_endian: [u8; 32] = Default::default();
    let bytes = d.as_bytes();
    for i in 0..32 {
        big_endian[i] = bytes[31 - i];
    }
    let middle = big_endian.len() / 2;
    let (a, b) = big_endian.split_at(middle);
    (hex::encode(a), hex::encode(b))
}
