import Separator from "@web/ui/separator";
import type { Metadata } from "next";
import findMostRecentHash from "./_actions/findMostRecentHash";
import DataSheetTable from "./_components/datasheet-table";
import datasheetTableColumns from "./_components/datasheet-table-columns";

export const metadata: Metadata = {
  title: "Datasheet",
};

export default async function DatasheetPage() {
  const mostRecentHash = await findMostRecentHash();

  console.log("mostRecentHash", mostRecentHash);

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

      <div className="mt-8 grid xl:grid-cols-2 gap-8">
        {/*dataArrays.map((dataArray, index) => (
          <DataSheetTable
            key={Object.values(FILENAMES_TO_TITLES)[index]}
            data={dataArray}
            title={Object.values(FILENAMES_TO_TITLES)[index] ?? ""}
            columns={datasheetTableColumns}
          />
        ))*/}
      </div>
    </div>
  );
}
