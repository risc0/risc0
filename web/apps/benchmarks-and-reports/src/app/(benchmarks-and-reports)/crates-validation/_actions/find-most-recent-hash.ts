import "server-only";

import { tryFetch } from "shared/utils/try-fetch";

export async function findMostRecentHash(): Promise<string> {
  const [error, response] = await tryFetch(
    "https://raw.githubusercontent.com/risc0/ghpages/main/dev/crate-validation/results/index.json",
    {
      next: { revalidate: 180 }, // 3 minutes cache
    },
  );

  // error handling
  if (error || !response.ok) {
    throw error || new Error("Failed to fetch");
  }

  const responseText = await response.text();

  // Find the most recent timestamp
  const mostRecent = JSON.parse(responseText.replace("[,", "[")).reduce((prev, current) =>
    prev.timestamp > current.timestamp ? prev : current,
  );

  return mostRecent.hash;
}
