import "server-only";

import { tryit } from "radash";

export async function findMostRecentHash(): Promise<string> {
  const tryFetch = tryit(fetch);
  const [error, response] = await tryFetch(
    "https://raw.githubusercontent.com/risc0/ghpages/main/dev/crate-validation/results/index.json",
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

  const responseText = await response.text();

  // Find the most recent timestamp
  const mostRecent = (
    JSON.parse(responseText.replace("[,", "[")) as {
      timestamp: number;
      hash: string;
    }[]
  ).reduce((prev, current) => (prev.timestamp > current.timestamp ? prev : current));

  return mostRecent.hash;
}
