import "server-only";

export async function fetchApplicationsBenchmarksCommitHash({ version }: { version: string }) {
  const response = await fetch(
    `https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/benchmarks/COMMIT_HASH.txt`,
    {
      headers: {
        Accept: "application/vnd.github.v3.raw",
      },
      next: { revalidate: 900 },
    },
  );
  const responseText = await response.text();

  return responseText;
}
