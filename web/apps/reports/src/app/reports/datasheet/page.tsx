import Separator from "@web/ui/separator";
import type { Metadata } from "next";
import fetchDatasheetCommitHash from "./_actions/fetch-datasheet-commit-hash";
import DataSheetTable from "./_components/datasheet-table";
import datasheetTableColumns from "./_components/datasheet-table-columns";

const FILENAMES_TO_TITLES = {
  "macOS-apple_m2_pro.json": "Metal on Apple M2 Pro",
  "Linux-nvidia_rtx_a5000.json": "CUDA on NVIDIA RTX A5000",
  "macOS-cpu.json": "CPU only on Apple M2 Pro",
  "Linux-cpu.json": "CPU only on TBD [Linux]",
} as const;

export const metadata: Metadata = {
  title: "Datasheet",
};

export default async function DatasheetPage() {
  const urls = Object.keys(FILENAMES_TO_TITLES);
  const commitHash = await fetchDatasheetCommitHash();
  const dataPromises = urls.map((url) =>
    fetch(`https://risc0.github.io/ghpages/dev/datasheet/${url}`)
      .then((response) => {
        if (!response.ok) {
          throw new Error(`Error fetching ${url}: ${response.statusText}`);
        }
        return response.json();
      })
      .catch((error) => {
        console.warn(`Failed fetching ${url}:`, error.message);
        return null; // Handle individual failures gracefully
      }),
  );
  const dataArrays = await Promise.all(dataPromises);

  return (
    <div className="container max-w-screen-3xl  pt-4">
      <div className="flex items-center justify-between text-muted-foreground">
        <h1 className="title-sm">Applications Benchmarks</h1>
        <p className="text-xs">Commit Hash: {commitHash}</p>
      </div>

      <Separator />

      <div className="mt-8 grid xl:grid-cols-2 gap-8">
        {dataArrays.map((dataArray, index) => (
          <DataSheetTable
            key={Object.values(FILENAMES_TO_TITLES)[index]}
            data={dataArray}
            title={Object.values(FILENAMES_TO_TITLES)[index] ?? ""}
            columns={datasheetTableColumns}
          />
        ))}
      </div>
    </div>
  );
}
