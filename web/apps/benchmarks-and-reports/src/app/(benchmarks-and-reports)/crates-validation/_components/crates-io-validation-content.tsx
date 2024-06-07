import { fetchCratesValidationResults } from "../_actions/fetch-crates-validation-results";
import { findMostRecentHash } from "../_actions/find-most-recent-hash";
import { CratesIoValidationSummary } from "./crates-io-validation-summary";
import { CratesIoValidationSummaryHeader } from "./crates-io-validation-summary-header";
import { CratesIoValidationTable } from "./crates-io-validation-table";
import { cratesIoValidationTableColumns } from "./crates-io-validation-table-columns";

export async function CratesIoValidationContent() {
  const hash = await findMostRecentHash();
  const cratesValidationResults = await fetchCratesValidationResults({
    hash,
  });

  return (
    <>
      <CratesIoValidationSummaryHeader data={cratesValidationResults} />
      <CratesIoValidationSummary data={cratesValidationResults} />
      <CratesIoValidationTable data={cratesValidationResults} columns={cratesIoValidationTableColumns} />
    </>
  );
}
