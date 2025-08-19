import "server-only";

import type { Version } from "@/types/version";
import { tryit } from "radash";

export async function fetchApplicationsBenchmarksCommitHash({ version }: { version: Version }) {
  const tryFetch = tryit(fetch);
  const [error, response] = await tryFetch(
    `https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/benchmarks/COMMIT_HASH.txt`,
    {
      next: {
        revalidate: 60,
      },
    },
  );

  // error handling
  if (error || !response.ok) {
    throw error || new Error("Failed to fetch");
  }

  return await response.text();
}
