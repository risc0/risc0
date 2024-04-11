import { Link } from "@risc0/ui/link";
import { Separator } from "@risc0/ui/separator";
import { Tabs, TabsContent, TabsList, TabsTrigger } from "@risc0/ui/tabs";
import { truncate } from "@risc0/ui/utils/truncate";
import type { Metadata } from "next";
import { redirect } from "next/navigation";
import { CopyButton } from "shared/client/components/copy-button";
import { convertCsvToJson } from "shared/utils/convert-csv-to-json";
import { replace } from "string-ts";
import { fetchApplicationsBenchmarks } from "./_actions/fetch-applications-benchmarks";
import { fetchApplicationsBenchmarksCommitHash } from "./_actions/fetch-applications-benchmarks-commit-hash";
import { ApplicationsBenchmarksTable } from "./_components/applications-benchmarks-table";
import { applicationsBenchmarksTableColumns } from "./_components/applications-benchmarks-table-columns";
import { FILENAMES_TO_TITLES } from "./_utils/constants";

export const metadata: Metadata = {
  title: "Applications Benchmark",
};

export default async function ApplicationsBenchmarksPage({ params }) {
  const commitHash = await fetchApplicationsBenchmarksCommitHash();
  const urls = Object.keys(FILENAMES_TO_TITLES);
  const dataPromises = urls.map((url) => fetchApplicationsBenchmarks(url));
  const data = await Promise.all(dataPromises);

  if (!params.slug) {
    redirect(`/applications-benchmarks/${replace(Object.keys(FILENAMES_TO_TITLES)[0]!, ".csv", "")}`);
  }

  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <h1 className="title-sm">Applications Benchmarks</h1>
        {commitHash && (
          <CopyButton size="sm" variant="ghost" value={commitHash}>
            Commit Hash<span className="hidden sm:inline">: {truncate(commitHash, 15)}</span>
          </CopyButton>
        )}
      </div>

      <Separator className="mt-2" />

      <Tabs className="mt-6" defaultValue={params.slug?.[0]}>
        <div className="flex items-center overflow-auto">
          <TabsList>
            {Object.keys(FILENAMES_TO_TITLES).map((filename, index) => (
              <Link key={filename} href={`/applications-benchmarks/${replace(filename, ".csv", "")}`}>
                <TabsTrigger value={replace(filename, ".csv", "")}>
                  {Object.values(FILENAMES_TO_TITLES)[index]}
                </TabsTrigger>
              </Link>
            ))}
          </TabsList>
        </div>

        {Object.keys(FILENAMES_TO_TITLES).map((filename, index) => (
          <TabsContent key={filename} value={replace(filename, ".csv", "")} className="mt-4">
            <ApplicationsBenchmarksTable
              title={Object.values(FILENAMES_TO_TITLES)[index] ?? ""}
              columns={applicationsBenchmarksTableColumns}
              data={convertCsvToJson(data[index]).filter((element) => element.job_name)}
            />
          </TabsContent>
        ))}
      </Tabs>
    </div>
  );
}
