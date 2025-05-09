RISC0_LIB_HASH=$(git hash-object -- groth16_proof/groth16/risc0.circom | awk '{ print $1 }')
RISC0_LIB_EXPECTED_HASH="87af73e7d1b24bff3df350136ec6637245a2330a"
if [ $RISC0_LIB_HASH != $RISC0_LIB_EXPECTED_HASH ]; then
    echo "Unexpected hash of risc0.circom: $RISC0_LIB_HASH"
    exit 1
fi
    
STARK_VERIFY_HASH=$(git hash-object -- groth16_proof/groth16/stark_verify.circom | awk '{ print $1 }')
STARK_VERIFY_EXPECTED_HASH="81557c4f15ce43f5c7c840c287e76abd3a676cd5"
if [ $STARK_VERIFY_HASH != $STARK_VERIFY_EXPECTED_HASH ]; then
    echo "Unexpected hash of stark_verify.circom: $STARK_VERIFY_HASH"
    exit 1
fi
