import "server-only";

import { unstable_noStore as noStore } from "next/cache";
import env from "~/env";

export async function fetchDatasheet({ version, url }: { version: string; url: string }) {
  noStore();

  return fetch(`https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/datasheet/${url}`, {
    headers: {
      Authorization: `token ${env.GITHUB_PAT}`,
      Accept: "application/vnd.github.v3.raw",
    },
  })
    .then((response) => {
      if (!response.ok) {
        throw new Error(`Error fetching ${url}: ${response.statusText}`);
      }

      return response.json();
    })
    .catch((error) => {
      console.error(`Failed fetching ${url}:`, error.message);

      return null; // Handle individual failures gracefully
    });
}
