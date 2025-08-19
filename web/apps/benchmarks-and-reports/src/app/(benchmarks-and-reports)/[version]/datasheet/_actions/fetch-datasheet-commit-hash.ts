import "server-only";

import { tryit } from "radash";
import type { Version } from "@/types/version";

export async function fetchDatasheetCommitHash({ version }: { version: Version }) {
  const tryFetch = tryit(fetch);
  const [error, response] = await tryFetch(
    `https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/datasheet/COMMIT_HASH.txt`,
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

  return {
    data: await response.text(),
    updatedAt: Date.now(),
  };
}
