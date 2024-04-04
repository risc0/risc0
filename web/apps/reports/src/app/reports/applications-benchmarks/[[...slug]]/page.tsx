import { Link } from "@risc0/ui/link";
import { Separator } from "@risc0/ui/separator";
import { Tabs, TabsContent, TabsList, TabsTrigger } from "@risc0/ui/tabs";
import { truncate } from "@risc0/ui/utils/truncate";
import type { Metadata } from "next";
import { CopyButton } from "~/client/copy-button";
import { convertCsvToJson } from "~/utils/convert-csv-to-json";
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
  const dataPromises = urls.map((url) =>
    fetch(`https://risc0.github.io/ghpages/dev/benchmarks/${url}`)
      .then((response) => {
        if (!response.ok) {
          throw new Error(`Error fetching ${url}: ${response.statusText}`);
        }
        return response.text();
      })
      .catch((error) => {
        console.error(`Failed fetching ${url}:`, error.message);
        return null; // Handle individual failures gracefully
      }),
  );
  const dataArrays = await Promise.all(dataPromises);

  return (
    <div className="container max-w-screen-3xl pt-4">
      <div className="flex items-center justify-between">
        <h1 className="title-sm">Applications Benchmarks</h1>
        {commitHash && (
          <CopyButton size="sm" variant="ghost" value={commitHash}>
            Commit Hash: {truncate(commitHash, 15)}
          </CopyButton>
        )}
      </div>

      <Separator className="mt-2" />

      <Tabs className="mt-6" defaultValue={params.slug?.[0] ?? Object.keys(FILENAMES_TO_TITLES)[0]}>
        <div className="flex items-center overflow-auto">
          <TabsList>
            {Object.keys(FILENAMES_TO_TITLES).map((filename, index) => (
              <Link key={filename} href={`/reports/applications-benchmarks/${filename}`}>
                <TabsTrigger value={filename}>{Object.values(FILENAMES_TO_TITLES)[index]}</TabsTrigger>
              </Link>
            ))}
          </TabsList>
        </div>

        {Object.keys(FILENAMES_TO_TITLES).map((filename, index) => (
          <TabsContent key={filename} value={filename} className="mt-4">
            <ApplicationsBenchmarksTable
              title={Object.values(FILENAMES_TO_TITLES)[index] ?? ""}
              columns={applicationsBenchmarksTableColumns}
              data={convertCsvToJson(dataArrays[index]).filter((element) => element.job_name)}
            />
          </TabsContent>
        ))}
      </Tabs>
    </div>
  );
}
