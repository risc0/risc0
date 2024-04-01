STARK_VERIFY_HASH=$(shasum -a 256 compact_proof/groth16/stark_verify.circom | awk '{ print $1 }')
STARK_VERIFY_EXPECTED_HASH="4649d6a6504d6448b8eb0bbf57b5adcb56affee6f28626e6c7432be4a0ad7932"
if [ $STARK_VERIFY_HASH != $STARK_VERIFY_EXPECTED_HASH ]; \
then echo "Unexpected SHA-256 of stark_verify.circom: $STARK_VERIFY_HASH"; \
exit 1; \
fi

RISC0_LIB_HASH=$(shasum -a 256 compact_proof/groth16/risc0.circom | awk '{ print $1 }')
RISC0_LIB_EXPECTED_HASH="38d3937558dae8f9de3d0bdc534c76c9adc6c7ffe37cc43935073324e1e53bf3"
if [ $RISC0_LIB_HASH != $RISC0_LIB_EXPECTED_HASH ]; \
then echo "Unexpected SHA-256 of risc0.circom: $RISC0_LIB_HASH"; \
exit 1; \
fi
