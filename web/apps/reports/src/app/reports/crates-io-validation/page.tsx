import Separator from "@web/ui/separator";
import type { Metadata } from "next";
import fetchCratesValidationResults from "./_actions/fetch-crates-validation-results";
import findMostRecentHash from "./_actions/find-most-recent-hash";
import DatasheetTable from "./_components/crates-io-validation-table";
import datasheetTableColumns from "./_components/crates-io-validation-table-columns";

export const metadata: Metadata = {
  title: "Crates.io Validation",
};

export default async function CratesIoValidationPage() {
  const mostRecentHash = await findMostRecentHash();
  const cratesValidationResults = await fetchCratesValidationResults(mostRecentHash);

  return (
    <div className="container max-w-screen-3xl  pt-4">
      <div className="flex items-center justify-between text-muted-foreground">
        <h1 className="title-sm">Crates.io Validation</h1>
        <p className="text-xs">Commit Hash: {mostRecentHash}</p>
      </div>
      <p className="text-sm">
        Each night, we test compatibility between each of the top 1000 Rust crates and the RISC Zero zkVM. This page
        shows the results of those tests.
      </p>

      <Separator className="mt-2" />

      <div className="mt-8">
        <DatasheetTable data={cratesValidationResults} columns={datasheetTableColumns} />
      </div>
    </div>
  );
}
