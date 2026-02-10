#!/bin/sh

echo "path to zip file: " $1
echo "path in zip file: " $2

clean_up() {
  ARG=$?
  cat picus_output.log
  rm picus_output.log
  exit $ARG
}
trap clean_up EXIT

VID=$(ah create-version-via-local-archive \
    --project-id 2104 \
    --name "$(date)" \
    --archive-path $1)
ah start-picus-v2-task \
    --source $2 \
    --project-id 2104 \
    --version-id $VID \
    --solver multi-solver \
    --solver-timeout 2000 \
    --assume-deterministic FpWrite \
    --wait # > picus_output.log
# grep -q "Verification result for module Top is: verified" picus_output.log
