"use server";

import env from "~/env";

export async function fetchApplicationsBenchmarks({ url, version }: { url: string; version: string }) {
  return fetch(`https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/benchmarks/${url}`, {
    headers: {
      Authorization: `token ${env.GITHUB_PAT}`,
      Accept: "application/vnd.github.v3.raw",
    },
    next: { revalidate: 3600 },
  })
    .then((response) => {
      if (!response.ok) {
        throw new Error(`Error fetching ${url}: ${response.statusText}`);
      }

      return response.text();
    })
    .catch((error) => {
      console.error(`Failed fetching ${url}:`, error.message);

      return undefined; // Handle individual failures gracefully
    });
}
