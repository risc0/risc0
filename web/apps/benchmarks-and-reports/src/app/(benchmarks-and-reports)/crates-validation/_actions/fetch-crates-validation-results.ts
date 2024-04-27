"use server";

import env from "~/env";

export async function fetchCratesValidationResults({ hash }: { hash: string }) {
  const response = await fetch(
    `https://raw.githubusercontent.com/risc0/ghpages/main/dev/crate-validation/results/${hash}.json`,
    {
      headers: {
        Authorization: `token ${env.GITHUB_PAT}`,
        Accept: "application/vnd.github.v3.raw",
      },
      next: { revalidate: 3600 },
    },
  );
  const responseJson = await response.json();

  return responseJson;
}
