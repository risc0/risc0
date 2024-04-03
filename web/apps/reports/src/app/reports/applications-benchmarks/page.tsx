import Separator from "@risc0/ui/separator";
import { Tabs, TabsContent, TabsList, TabsTrigger } from "@risc0/ui/tabs";
import truncate from "@risc0/ui/utils/truncate";
import type { Metadata } from "next";
import convertCsvToJson from "~/utils/convert-csv-to-json";
import fetchApplicationsBenchmarksCommitHash from "./_actions/fetch-applications-benchmarks-commit-hash";
import ApplicationsBenchmarksTable from "./_components/applications-benchmarks-table";
import applicationsBenchmarksTableColumns from "./_components/applications-benchmarks-table-columns";

const FILENAMES_TO_TITLES = {
  "macOS-apple_m2_pro.csv": "Metal on Apple M2 Pro",
  "Linux-nvidia_rtx_a5000.csv": "CUDA on NVIDIA RTX A5000",
  "macOS-cpu.csv": "CPU only on Apple M2 Pro",
  "Linux-cpu.csv": "CPU only on TBD [Linux]",
} as const;

export const metadata: Metadata = {
  title: "Applications Benchmark",
};

export default async function ApplicationsBenchmarksPage() {
  const urls = Object.keys(FILENAMES_TO_TITLES);
  const commitHash = await fetchApplicationsBenchmarksCommitHash();
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
          <p className="text-xs" title={commitHash}>
            Commit Hash: {truncate(commitHash, 15)}
          </p>
        )}
      </div>

      <Separator />

      <Tabs className="mt-6" defaultValue={Object.keys(FILENAMES_TO_TITLES)[0]}>
        <div className="flex items-center overflow-auto">
          <TabsList>
            {Object.keys(FILENAMES_TO_TITLES).map((filename, index) => (
              <TabsTrigger key={filename} value={filename}>
                {Object.values(FILENAMES_TO_TITLES)[index]}
              </TabsTrigger>
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
