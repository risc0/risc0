import { Link } from "@risc0/ui/link";
import { TabsContent, TabsList, TabsTrigger } from "@risc0/ui/tabs";
import { convertCsvToJson } from "shared/utils/convert-csv-to-json";
import { replace } from "string-ts";
import { fetchApplicationsBenchmarks } from "../_actions/fetch-applications-benchmarks";
import { FILENAMES_TO_TITLES } from "../_utils/constants";
import { ApplicationsBenchmarksTable } from "./applications-benchmarks-table";
import { applicationsBenchmarksTableColumns } from "./applications-benchmarks-table-columns";

export default async function ApplicationsBenchmarksContent() {
  const urls = Object.keys(FILENAMES_TO_TITLES);
  const dataPromises = urls.map((url) => fetchApplicationsBenchmarks(url));
  const data = await Promise.all(dataPromises);

  return (
    <>
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
    </>
  );
}
