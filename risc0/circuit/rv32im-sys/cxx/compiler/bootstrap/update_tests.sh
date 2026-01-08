#!/bin/sh

# fn stable_root
# file risc0/zkvm/src/host/recursion/tests.rs
recursion_control_root=$(sed -n '/ALLOWED_CONTROL_ROOT/,/);/s/.*digest!("\([a-f0-9]*\)").*/\1/p' risc0/circuit/recursion/src/control_id.rs)

echo "New recursion control root: $recursion_control_root"
sed -i '' "/fn stable_root()/,/^    }/s/digest!(\"[a-f0-9]*\")/digest!(\"$recursion_control_root\")/" "risc0/zkvm/src/host/recursion/tests.rs"

# fn composite_receipt_verifier_parameters_is_stable
# file risc0/zkvm/src/receipt/composite.rs
composite_verifier_digest=$(
  cargo test --package risc0-zkvm --lib -- receipt::composite::tests::composite_receipt_verifier_parameters_is_stable --exact \
    | grep "left:" \
    | sed -n 's/.*Digest(\([^)]*\)).*/\1/p')

if [ -n "$composite_verifier_digest" ]; then
  echo "New composite verifier digest: $composite_verifier_digest"
  sed -i '' "/composite_receipt_verifier_parameters_is_stable/,/^    }/s/digest!(\"[a-f0-9]*\")/digest!(\"$composite_verifier_digest\")/" "risc0/zkvm/src/receipt/composite.rs"
else
  echo "Composite verifier test passed, no update needed"
fi

# fn groth16_receipt_verifier_parameters_is_stable
# file risc0/zkvm/src/receipt/groth16.rs
groth16_verifier_digest=$(
  cargo test --package risc0-zkvm --lib -- receipt::groth16::tests::groth16_receipt_verifier_parameters_is_stable --exact \
    | grep "left:" \
    | sed -n 's/.*Digest(\([^)]*\)).*/\1/p')

if [ -n "$groth16_verifier_digest" ]; then
  echo "New Groth16 verifier digest: $groth16_verifier_digest"
  sed -i '' "/groth16_receipt_verifier_parameters_is_stable/,/^    }/s/digest!(\"[a-f0-9]*\")/digest!(\"$groth16_verifier_digest\")/" "risc0/zkvm/src/receipt/groth16.rs"
else
  echo "Groth16 verifier test passed, no update needed"
fi

# fn succinct_receipt_verifier_parameters_is_stable
# file risc0/zkvm/src/receipt/succinct.rs
succinct_verifier_digest=$(
  cargo test --package risc0-zkvm --lib -- receipt::succinct::tests::succinct_receipt_verifier_parameters_is_stable --exact \
    | grep "left:" \
    | sed -n 's/.*Digest(\([^)]*\)).*/\1/p')

if [ -n "$succinct_verifier_digest" ]; then
  echo "New succinct verifier digest: $succinct_verifier_digest"
  sed -i '' "/succinct_receipt_verifier_parameters_is_stable/,/^    }/s/digest!(\"[a-f0-9]*\")/digest!(\"$succinct_verifier_digest\")/" "risc0/zkvm/src/receipt/succinct.rs"
else
  echo "Succinct verifier test passed, no update needed"
fi

# fn test_reproducible_methods_guest
# file risc0/build/src/docker.rs
docker_image_id=$(
  cargo run --bin cargo-risczero -- risczero build --manifest-path risc0/zkvm/methods/guest/Cargo.toml \
    | grep "hello_commit" \
    |  awk '{print $2}')

if [ -n "$docker_image_id" ]; then
  echo "New Docker image ID: $docker_image_id"
  sed -i '' "/test_reproducible_methods_guest/,/^    }/s/\"[a-f0-9]\{64\}\"/\"$docker_image_id\"/" risc0/build/src/docker.rs

else
  echo "Docker image build failed, no update made"
  exit 1
fi

