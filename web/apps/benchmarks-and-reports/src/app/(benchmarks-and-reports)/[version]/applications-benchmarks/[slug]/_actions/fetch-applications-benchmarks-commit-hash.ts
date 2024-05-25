import "server-only";
import type { Version } from "~/types/version";

export async function fetchApplicationsBenchmarksCommitHash({ version }: { version: Version }) {
  const response = await fetch(
    `https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/benchmarks/COMMIT_HASH.txt`,
    {
      next: { revalidate: 180 }, // 3 minutes cache
    },
  );
  const responseText = await response.text();

  return responseText;
}
