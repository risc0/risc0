export default async function fetchCratesValidationResults(hash) {
  const filename = `https://risc0.github.io/ghpages/dev/crate-validation/results/${hash}.json`;
  return await fetch(filename)
    .then((res) => res.json())
    .then((data) => data)
    .catch((err) => {
      console.error(err);
    });
}
