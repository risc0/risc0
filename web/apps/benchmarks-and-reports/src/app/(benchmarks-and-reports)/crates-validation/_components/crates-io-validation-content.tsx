import { fetchCratesValidationResults } from "../_actions/fetch-crates-validation-results";
import { CratesIoValidationSummary } from "./crates-io-validation-summary";
import { CratesIoValidationSummaryHeader } from "./crates-io-validation-summary-header";
import { CratesIoValidationTable } from "./crates-io-validation-table";
import { cratesIoValidationTableColumns } from "./crates-io-validation-table-columns";
import type { CratesIoValidationTableSchema } from "./crates-io-validation-table-schema";

export default async function CratesIoValidationContent({
  mostRecentHash,
}: {
  mostRecentHash: string;
}) {
  const cratesValidationResults: CratesIoValidationTableSchema[] = await fetchCratesValidationResults({
    hash: mostRecentHash,
  });

  return (
    <>
      <CratesIoValidationSummaryHeader data={cratesValidationResults} />
      <CratesIoValidationSummary data={cratesValidationResults} />
      <CratesIoValidationTable data={cratesValidationResults} columns={cratesIoValidationTableColumns} />
    </>
  );
}
