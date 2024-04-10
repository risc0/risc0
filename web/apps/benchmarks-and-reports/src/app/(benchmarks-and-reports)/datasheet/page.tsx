import { Link } from "@risc0/ui/link";
import { Separator } from "@risc0/ui/separator";
import { truncate } from "@risc0/ui/utils/truncate";
import type { Metadata } from "next";
import { CopyButton } from "shared/client/components/copy-button";
import { DATASHEET_DESCRIPTION } from "../_utils/constants";
import { fetchDatasheet } from "./_actions/fetch-datasheet";
import { fetchDatasheetCommitHash } from "./_actions/fetch-datasheet-commit-hash";
import { DatasheetTable } from "./_components/datasheet-table";
import { datasheetTableColumns } from "./_components/datasheet-table-columns";
import type { DatasheetTableSchema } from "./_components/datasheet-table-schema";

const FILENAMES_TO_TITLES = {
  "macOS-apple_m2_pro.json": "Metal on Apple M2 Pro",
  "Linux-nvidia_rtx_3090_ti.json": "CUDA on NVIDIA RTX 3090 Ti",
  "macOS-cpu.json": "CPU only on Apple M2 Pro",
  "Linux-cpu.json": (
    <>
      CPU only on{" "}
      <Link target="_blank" href="https://instances.vantage.sh/aws/ec2/c6i.8xlarge" className="link">
        c6i.8xlarge
      </Link>
    </>
  ),
} as const;

export const metadata: Metadata = {
  title: "Datasheet",
  description: DATASHEET_DESCRIPTION,
};

export default async function DatasheetPage() {
  const urls = Object.keys(FILENAMES_TO_TITLES);
  const commitHash = await fetchDatasheetCommitHash();
  const dataPromises = urls.map((url) => fetchDatasheet(url));
  const data: DatasheetTableSchema[][] = await Promise.all(dataPromises);

  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <h1 className="title-sm">Datasheet</h1>
        {commitHash && (
          <CopyButton size="sm" variant="ghost" value={commitHash}>
            Commit Hash<span className="hidden sm:inline">: {truncate(commitHash, 15)}</span>
          </CopyButton>
        )}
      </div>

      <Separator className="mt-2" />

      <div className="mt-6 grid grid-cols-1 gap-8 xl:grid-cols-2">
        {data.map((dataArray, index) => (
          <DatasheetTable
            key={Object.keys(FILENAMES_TO_TITLES)[index]}
            data={dataArray}
            title={Object.values(FILENAMES_TO_TITLES)[index] ?? ""}
            columns={datasheetTableColumns}
          />
        ))}
      </div>
    </div>
  );
}
