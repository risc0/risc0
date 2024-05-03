"use server";

import env from "~/env";
import type { CratesIoValidationTableSchema } from "../_components/crates-io-validation-table-schema";

export async function fetchCratesValidationResults({
  hash,
}: { hash: string }): Promise<CratesIoValidationTableSchema[]> {
  const response = await fetch(
    `https://raw.githubusercontent.com/risc0/ghpages/main/dev/crate-validation/results/${hash}.json`,
    {
      headers: {
        Authorization: `token ${env.GITHUB_PAT}`,
        Accept: "application/vnd.github.v3.raw",
      },
      next: { revalidate: 900 },
    },
  );
  const responseJson = await response.json();

  return responseJson;
}
