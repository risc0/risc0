import { all } from "radash";
import type { Version } from "@/types/version";
import { fetchDatasheet } from "../_actions/fetch-datasheet";
import { DATASHEET_FILENAMES_TO_TITLES } from "../_utils/constants";
import { DatasheetTable } from "./datasheet-table";
import { datasheetTableColumns } from "./datasheet-table-columns";
import type { DatasheetTableSchema } from "./datasheet-table-schema";

export async function DatasheetContent({ version }: { version: Version }) {
  const urls = Object.keys(DATASHEET_FILENAMES_TO_TITLES[version]);
  const dataPromises = urls.map((url) => fetchDatasheet({ version, url }));
  const data = (await all(dataPromises)) as DatasheetTableSchema[][];

  return data.map((dataArray, index) => (
    <DatasheetTable
      key={urls[index]}
      data={dataArray}
      title={Object.values(DATASHEET_FILENAMES_TO_TITLES[version])[index] ?? ""}
      columns={datasheetTableColumns}
    />
  ));
}
