"use server";

import { unstable_noStore as noStore } from "next/cache";
import env from "~/env";

export async function fetchDatasheetCommitHash({ version }: { version: string }) {
  noStore();

  const response = await fetch(
    `https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/datasheet/COMMIT_HASH.txt`,
    {
      headers: {
        Authorization: `token ${env.GITHUB_PAT}`,
        Accept: "application/vnd.github.v3.raw",
      },
    },
  );
  const responseText = await response.text();

  return responseText;
}
