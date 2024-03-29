"use client";

import type { Table } from "@tanstack/react-table";
import Input from "@web/ui/input";
import type { Dispatch, SetStateAction } from "react";
import DatasheetViewOptions from "./datasheet-table-view-options";

type DatasheetToolbarProps<TData> = {
  table: Table<TData>;
  globalFilter: string;
  setGlobalFilter: Dispatch<SetStateAction<string>>;
};

export default function DatasheetTableToolbar<TData>({
  table,
  setGlobalFilter,
  globalFilter,
}: DatasheetToolbarProps<TData>) {
  return (
    <div className="flex items-center justify-end gap-2">
      <Input
        placeholder="Search…"
        value={globalFilter ?? ""}
        onChange={(event) => setGlobalFilter(String(event.target.value))}
        className="h-8 w-[180px]"
      />

      <DatasheetViewOptions table={table} />
    </div>
  );
}
