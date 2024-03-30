"use client";

import type { Table } from "@tanstack/react-table";
import Input from "@web/ui/input";
import type { Dispatch, SetStateAction } from "react";
import ApplicationsBenchmarkViewOptions from "./applications-benchmarks-table-view-options";

type ApplicationsBenchmarksTableToolbarProps<TData> = {
  table: Table<TData>;
  globalFilter: string;
  setGlobalFilter: Dispatch<SetStateAction<string>>;
};

export default function ApplicationsBenchmarksTableToolbar<TData>({
  table,
  setGlobalFilter,
  globalFilter,
}: ApplicationsBenchmarksTableToolbarProps<TData>) {
  return (
    <div className="flex items-center justify-end gap-2">
      <Input
        placeholder="Search…"
        value={globalFilter ?? ""}
        onChange={(event) => setGlobalFilter(String(event.target.value))}
        className="h-8 w-[180px]"
      />

      <ApplicationsBenchmarkViewOptions table={table} />
    </div>
  );
}
