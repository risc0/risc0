import { Separator } from "@risc0/ui/separator";
import { truncate } from "@risc0/ui/utils/truncate";
import type { Metadata } from "next";
import { CopyButton } from "~/client/copy-button";
import { fetchDatasheetCommitHash } from "./_actions/fetch-datasheet-commit-hash";
import { DatasheetTable } from "./_components/datasheet-table";
import { datasheetTableColumns } from "./_components/datasheet-table-columns";

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
    <div className="container max-w-screen-3xl pt-4">
      <div className="flex items-center justify-between">
        <h1 className="title-sm">Datasheet</h1>
        {commitHash && (
          <CopyButton size="sm" variant="ghost" value={commitHash}>
            Commit Hash: {truncate(commitHash, 15)}
          </CopyButton>
        )}
      </div>

      <Separator className="mt-2" />

      <div className="mt-6 grid gap-8 xl:grid-cols-2">
        {dataArrays.map((dataArray, index) => (
          <DatasheetTable
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
