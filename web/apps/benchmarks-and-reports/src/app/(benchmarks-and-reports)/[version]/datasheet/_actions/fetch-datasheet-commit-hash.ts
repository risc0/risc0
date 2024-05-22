import "server-only";

import { unstable_noStore as noStore } from "next/cache";

export async function fetchDatasheetCommitHash({ version }: { version: string }) {
  noStore();

  const response = await fetch(
    `https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/datasheet/COMMIT_HASH.txt`,
    {
      headers: {
        Accept: "application/vnd.github.v3.raw",
      },
    },
  );
  const responseText = await response.text();

  return responseText;
}
