import Separator from "@risc0/ui/separator";
import truncate from "@risc0/ui/utils/truncate";
import type { Metadata } from "next";
import fetchCratesValidationResults from "./_actions/fetch-crates-validation-results";
import findMostRecentHash from "./_actions/find-most-recent-hash";
import CratesIoValidationTable from "./_components/crates-io-validation-table";
import cratesIoValidationTableColumns from "./_components/crates-io-validation-table-columns";

export const metadata: Metadata = {
  title: "Crates.io Validation",
};

export default async function CratesIoValidationPage() {
  const mostRecentHash = await findMostRecentHash();
  const cratesValidationResults = await fetchCratesValidationResults(mostRecentHash);

  return (
    <div className="container max-w-screen-3xl pt-4">
      <div className="flex items-center justify-between">
        <h1 className="title-sm">Crates.io Validation</h1>
        {mostRecentHash && (
          <p className="text-xs" title={mostRecentHash}>
            Commit Hash: {truncate(mostRecentHash, 15)}
          </p>
        )}
      </div>
      <p className="text-muted-foreground text-sm">
        Each night, we test compatibility between each of the top 1000 Rust crates and the RISC Zero zkVM. This page
        shows the results of those tests.
      </p>

      <Separator className="mt-2" />

      <div className="mt-8">
        <CratesIoValidationTable data={cratesValidationResults} columns={cratesIoValidationTableColumns} />
      </div>
    </div>
  );
}
