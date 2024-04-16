STARK_VERIFY_HASH=$(shasum -a 256 compact_proof/groth16/stark_verify.circom | awk '{ print $1 }')
STARK_VERIFY_EXPECTED_HASH="a3789471909ba1a13cca783dc5269b25b6d41295abe60234a8075f750017518c"
if [ $STARK_VERIFY_HASH != $STARK_VERIFY_EXPECTED_HASH ]; then
    echo "Unexpected SHA-256 of stark_verify.circom: $STARK_VERIFY_HASH"
    exit 1
fi

RISC0_LIB_HASH=$(shasum -a 256 compact_proof/groth16/risc0.circom | awk '{ print $1 }')
RISC0_LIB_EXPECTED_HASH="38d3937558dae8f9de3d0bdc534c76c9adc6c7ffe37cc43935073324e1e53bf3"
if [ $RISC0_LIB_HASH != $RISC0_LIB_EXPECTED_HASH ]; then
    echo "Unexpected SHA-256 of risc0.circom: $RISC0_LIB_HASH"
    exit 1
fi
