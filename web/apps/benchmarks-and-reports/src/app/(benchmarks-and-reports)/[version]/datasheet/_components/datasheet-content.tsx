import { all } from "radash";
import type { Version } from "~/types/version";
import { fetchDatasheet } from "../_actions/fetch-datasheet";
import { DATASHEET_FILENAMES_TO_TITLES } from "../_utils/constants";
import { DatasheetTable } from "./datasheet-table";
import { datasheetTableColumns } from "./datasheet-table-columns";
import type { DatasheetTableSchema } from "./datasheet-table-schema";

export async function DatasheetContent({ version }: { version: Version }) {
  const urls = Object.keys(FILENAMES_TO_TITLES);
  const dataPromises = urls.map((url) => fetchDatasheet({ version, url }));
  const data: DatasheetTableSchema[][] = await all(dataPromises);

  return data.map((dataArray, index) => (
    <DatasheetTable
      key={Object.keys(FILENAMES_TO_TITLES)[index]}
      data={dataArray}
      title={Object.values(FILENAMES_TO_TITLES)[index] ?? ""}
      columns={datasheetTableColumns}
    />
  ));
}
