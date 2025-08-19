# Shrink-Wrapping Proofs

The default proving options will result in the final proof being a composite receipt. This receipt
can be quite large and grows linearly with respect to execution length. So instead a smaller receipt
may be desired for posting on-chain. We call the process of creating this smaller receipt
"shrink-wrapping".

## Groth16

The only currently officially supported shrink-wrapping type is Groth16. To request it, set the
receipt-kind in the `ProverOpts` to be `ReceiptKind::Groth16`. This should cause the prover to do a
final "shrink-wrapping".

The Groth16 shrink-wrapping requires the prover install a certain `rzup` component. This can be
installed by first ensuring you are using `rzup` version >= 0.5.0 and then running `rzup install
risc0-groth16`
