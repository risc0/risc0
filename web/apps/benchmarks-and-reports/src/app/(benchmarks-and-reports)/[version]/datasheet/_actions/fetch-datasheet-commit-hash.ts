import "server-only";

import { tryit } from "radash";
import type { Version } from "~/types/version";

export async function fetchDatasheetCommitHash({ version }: { version: Version }) {
  const tryFetch = tryit(fetch);
  const [error, response] = await tryFetch(
    `https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/datasheet/COMMIT_HASH.txt`,
    {
      next: { revalidate: 10, tags: ["fetch-datasheet-commit-hash"] }, // 1 minute cache
    },
  );

  // error handling
  if (error || !response.ok) {
    throw error || new Error("Failed to fetch");
  }

  return await response.text();
}
