import type { Version } from "@/types/version";
import { pick } from "radash";
import { convertCsvToJson } from "shared/utils/convert-csv-to-json";
import { fetchApplicationsBenchmarks } from "../_actions/fetch-applications-benchmarks";
import { APPLICATIONS_BENCHMARKS_FILENAMES_TO_TITLES } from "../_utils/constants";
import { ApplicationsBenchmarksTable } from "./applications-benchmarks-table";
import { applicationsBenchmarksTableColumns } from "./applications-benchmarks-table-columns";

export async function ApplicationsBenchmarksContent({ version, currentTab }: { version: Version; currentTab: string }) {
  const applicationsBenchmarks = APPLICATIONS_BENCHMARKS_FILENAMES_TO_TITLES[version];
  const currentApplication = pick(applicationsBenchmarks, [`${currentTab}.csv` as keyof typeof applicationsBenchmarks]);
  const data = await fetchApplicationsBenchmarks({
    url: `${currentTab}.csv`,
    version,
  });
  const currentApplicationName = Object.values(currentApplication)[0];

  if (!data || !currentApplicationName) {
    return null;
  }

  return (
    <ApplicationsBenchmarksTable
      title={currentApplicationName}
      columns={applicationsBenchmarksTableColumns}
      version={version}
      data={convertCsvToJson(data).filter((element) => element.name ?? element.job_name)}
    />
  );
}
