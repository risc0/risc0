RISC0_LIB_HASH=$(git hash-object -- groth16_proof/groth16/risc0.circom | awk '{ print $1 }')
RISC0_LIB_EXPECTED_HASH="a83e5b894f4b6fcc3d04aa82b95f3c1d52bfc827"
if [ $RISC0_LIB_HASH != $RISC0_LIB_EXPECTED_HASH ]; then
    echo "Unexpected hash of risc0.circom: $RISC0_LIB_HASH"
    exit 1
fi
    
STARK_VERIFY_HASH=$(git hash-object -- groth16_proof/groth16/stark_verify.circom | awk '{ print $1 }')
STARK_VERIFY_EXPECTED_HASH="5ea750bb57bec9ce0f6c9750ac1c66705657bb66"
if [ $STARK_VERIFY_HASH != $STARK_VERIFY_EXPECTED_HASH ]; then
    echo "Unexpected hash of stark_verify.circom: $STARK_VERIFY_HASH"
    exit 1
fi
