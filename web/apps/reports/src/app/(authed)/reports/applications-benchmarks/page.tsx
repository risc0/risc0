import Separator from "@web/ui/separator";
import { Tabs, TabsContent, TabsList, TabsTrigger } from "@web/ui/tabs";
import type { Metadata } from "next";
import DatasheetTable from "./_components/applications-benchmarks-table";
import datasheetTableColumns from "./_components/applications-benchmarks-table-columns";

const convertCSVToJson = (csvData) => {
  const lines = csvData.split("\n");
  const headers = lines[0].split(",");
  const result: any[] = [];

  for (let i = 1; i < lines.length; i++) {
    const obj = {};
    const currentLine = lines[i].split(",");

    for (let j = 0; j < headers.length; j++) {
      obj[headers[j]?.trim()] = currentLine[j]?.trim();
    }

    result.push(obj);
  }

  return result;
};

const FILENAMES_TO_TITLES = {
  "macOS-apple_m2_pro.csv": "Metal on Apple M2 Pro",
  "Linux-nvidia_rtx_a5000.csv": "CUDA on NVIDIA RTX A5000",
  "macOS-cpu.csv": "CPU only on Apple M2 Pro",
  "Linux-cpu.csv": "CPU only on TBD [Linux]",
} as const;

export const metadata: Metadata = {
  title: "Applications Benchmark",
};

export default async function DatasheetPage() {
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
        console.warn(`Failed fetching ${url}:`, error.message);
        return null; // Handle individual failures gracefully
      }),
  );

  const dataArrays = await Promise.all(dataPromises);

  console.log("dataArrays", dataArrays);

  return (
    <div className="container max-w-screen-3xl">
      <h1 className="title">Applications Benchmarks</h1>
      <Separator />

      <div className="mt-6 grid grid-cols-2 gap-8">
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
            <TabsContent value={filename} className="mt-4">
              <h2 className="title">{Object.values(FILENAMES_TO_TITLES)[index]}</h2>
              <p className="whitespace-warp">{JSON.stringify(convertCSVToJson(dataArrays[index]))}</p>
              <DatasheetTable columns={datasheetTableColumns} data={convertCSVToJson(dataArrays[index])} />
            </TabsContent>
          ))}
        </Tabs>
      </div>
    </div>
  );
}
