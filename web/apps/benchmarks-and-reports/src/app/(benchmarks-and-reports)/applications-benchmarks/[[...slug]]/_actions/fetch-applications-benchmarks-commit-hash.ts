"use server";

export async function fetchApplicationsBenchmarksCommitHash() {
  const response = await fetch("https://risc0.github.io/ghpages/dev/benchmarks/COMMIT_HASH.txt", {
    next: { revalidate: 3600 },
  });
  const responseText = await response.text();

  return responseText;
}
