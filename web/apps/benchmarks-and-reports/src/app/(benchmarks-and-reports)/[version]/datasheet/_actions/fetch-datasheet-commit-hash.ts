import "server-only";

import { tryFetch } from "shared/utils/try-fetch";
import type { Version } from "~/types/version";

export async function fetchDatasheetCommitHash({ version }: { version: Version }) {
  const [error, response] = await tryFetch(
    `https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/datasheet/COMMIT_HASH.txt`,
    {
      next: { revalidate: 180 }, // 3 minutes cache
    },
  );

  // error handling
  if (error || !response.ok) {
    throw error || new Error("Failed to fetch");
  }

  return await response.text();
}
