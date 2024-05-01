"use server";

import env from "~/env";

export async function fetchDatasheetCommitHash({ version }: { version: string }) {
  const response = await fetch(
    `https://raw.githubusercontent.com/risc0/ghpages/${version}/dev/datasheet/COMMIT_HASH.txt`,
    {
      headers: {
        Authorization: `token ${env.GITHUB_PAT}`,
        Accept: "application/vnd.github.v3.raw",
      },
      cache: "no-store",
    },
  );
  const responseText = await response.text();

  return responseText;
}
