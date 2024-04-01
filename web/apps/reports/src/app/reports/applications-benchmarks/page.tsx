import Separator from "@web/ui/separator";
import { Tabs, TabsContent, TabsList, TabsTrigger } from "@web/ui/tabs";
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
      <div className="flex items-center justify-between text-muted-foreground">
        <h1 className="title-sm">Applications Benchmarks</h1>
        <p className="text-xs">Commit Hash: {commitHash}</p>
      </div>

      <Separator />

      <div className="mt-6">
        <Tabs defaultValue={Object.keys(FILENAMES_TO_TITLES)[0]}>
          <div className="flex items-center">
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
    </div>
  );
}
