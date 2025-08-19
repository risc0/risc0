import "server-only";

import { tryit } from "radash";
import type { CratesIoValidationTableSchema } from "../_components/crates-io-validation-table-schema";

export async function fetchCratesValidationResults({
  hash,
}: {
  hash: string;
}): Promise<CratesIoValidationTableSchema[]> {
  const tryFetch = tryit(fetch);
  const [error, response] = await tryFetch(
    `https://raw.githubusercontent.com/risc0/ghpages/main/dev/crate-validation/results/${hash}.json`,
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

  return (await response.json()) as CratesIoValidationTableSchema[];
}
