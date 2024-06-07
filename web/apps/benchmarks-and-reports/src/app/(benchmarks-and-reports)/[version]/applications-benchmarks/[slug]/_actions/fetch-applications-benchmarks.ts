import "server-only";

import { tryFetch } from "shared/utils/try-fetch";
import type { Version } from "~/types/version";

export async function fetchApplicationsBenchmarks({ url, version }: { url: string; version: Version }) {
  const [error, response] = await tryFetch(
    `https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/benchmarks/${url}`,
    {
      next: { revalidate: 10, tags: ["fetch-applications-benchmarks"] }, // 1 minute cache
    },
  );

  // error handling
  if (error || !response.ok) {
    throw error || new Error("Failed to fetch");
  }

  return await response.text();
}
