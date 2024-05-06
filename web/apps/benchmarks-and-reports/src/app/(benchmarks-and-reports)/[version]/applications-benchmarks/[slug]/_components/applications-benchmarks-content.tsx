import pick from "lodash-es/pick";
import { convertCsvToJson } from "shared/utils/convert-csv-to-json";
import { fetchApplicationsBenchmarks } from "../_actions/fetch-applications-benchmarks";
import { FILENAMES_TO_TITLES } from "../_utils/constants";
import { ApplicationsBenchmarksTable } from "./applications-benchmarks-table";
import { applicationsBenchmarksTableColumns } from "./applications-benchmarks-table-columns";

export async function ApplicationsBenchmarksContent({ version, currentTab }: { version: string; currentTab: string }) {
  const currentApplication = pick(FILENAMES_TO_TITLES, `${currentTab}.csv`);
  const data = await fetchApplicationsBenchmarks({ url: `${currentTab}.csv`, version });
  const currentApplicationName = Object.values(currentApplication)[0];

  if (!data || !currentApplicationName) {
    return null;
  }

  return (
    <ApplicationsBenchmarksTable
      title={currentApplicationName}
      columns={applicationsBenchmarksTableColumns}
      data={convertCsvToJson(data).filter((element) => element.job_name)}
    />
  );
}
