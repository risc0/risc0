"use client";

import type { Table } from "@tanstack/react-table";
import Input from "@web/ui/input";
import type { Dispatch, SetStateAction } from "react";
import TableViewOptions from "~/client/table/table-view-options";

type TableToolbarProps<TData> = {
  table: Table<TData>;
  globalFilter: string;
  setGlobalFilter: Dispatch<SetStateAction<string>>;
};

export default function TableToolbar<TData>({ table, setGlobalFilter, globalFilter }: TableToolbarProps<TData>) {
  return (
    <div className="flex items-center justify-end gap-2">
      <Input
        placeholder="Search…"
        value={globalFilter ?? ""}
        onChange={(event) => setGlobalFilter(String(event.target.value))}
        className="h-8 w-[180px]"
      />

      <TableViewOptions table={table} />
    </div>
  );
}
