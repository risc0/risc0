"use server";

export async function fetchCratesValidationResults(hash: string) {
  const response = await fetch(`https://risc0.github.io/ghpages/dev/crate-validation/results/${hash}.json`, {
    next: { revalidate: 3600 },
  });
  const responseJson = await response.json();

  return responseJson;
}
