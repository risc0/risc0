set -e

cd ${TEMP_DIR}/benchmarks/

RESULTS_DIR="./dev/crate-validation/results"
INDEX_FILE="${RESULTS_DIR}/index.json"
mkdir -p ${RESULTS_DIR}

cp ${TEMP_DIR}/crate-validation/profile-results.json "${RESULTS_DIR}/${GITHUB_SHA}.json"

touch ${INDEX_FILE}

echo "Filtering out old results"
CRATE_VALIDATOR_PAST_VALUES=$(grep -ohE '{\s*"timestamp":\s*\d+\s*,\s*"hash":\s*"[a-zA-Z0-9]+"\s*}' ${INDEX_FILE} || true)
echo $CRATE_VALIDATOR_PAST_VALUES

echo "Processing results"
CRATE_VALIDATOR_PROCESSED_VALUES=$(echo $CRATE_VALIDATOR_PAST_VALUES | awk -v timestamp="$(date +%s)" -v hash="${GITHUB_SHA}" 'BEGIN{print "["} {print $0","} END{print "{\"timestamp\":"timestamp", \"hash\":\""hash"\"}" "\n]"}')
echo $CRATE_VALIDATOR_PROCESSED_VALUES

echo "Removing whitespace"
CRATE_VALIDATOR_FINAL_VALUES=$(echo $CRATE_VALIDATOR_PROCESSED_VALUES | tr -d '[:space:]')
echo $CRATE_VALIDATOR_FINAL_VALUES

echo "Checking old index"
cat ${INDEX_FILE}

echo "Updating index"
echo $CRATE_VALIDATOR_FINAL_VALUES | tee ${INDEX_FILE}

echo "Committing results"
git add .
git  -c "user.name=nightly-action" -c "user.email=github@users.noreply.github.com" commit -m "Added update at '$(date)'"
git push origin main
