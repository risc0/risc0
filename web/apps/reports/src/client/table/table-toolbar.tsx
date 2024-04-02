"use client";

import type { Table } from "@tanstack/react-table";
import Button from "@risc0/ui/button";
import Input from "@risc0/ui/input";
import { XIcon } from "lucide-react";
import type { ComponentType, Dispatch, ReactNode, SetStateAction } from "react";
import TableViewOptions from "~/client/table/table-view-options";
import { TableFacetedFilter } from "./table-faceted-filter";

type TableToolbarProps<TData> = {
  table: Table<TData>;
  globalFilter: string;
  statuses?: {
    label: string;
    value: string;
    icon?: ComponentType<{ className?: string }>;
  }[];
  setGlobalFilter: Dispatch<SetStateAction<string>>;
};

export default function TableToolbar<TData>({
  table,
  statuses,
  setGlobalFilter,
  globalFilter,
}: TableToolbarProps<TData>) {
  const isFiltered = table.getState().columnFilters.length > 0;

  return (
    <div className="flex items-center justify-end gap-2">
      <Input
        placeholder="Search…"
        value={globalFilter ?? ""}
        onChange={(event) => setGlobalFilter(String(event.target.value))}
        className="h-8 w-[180px]"
      />
      {statuses && table.getColumn("status") && (
        <TableFacetedFilter column={table.getColumn("status")} title="Status" options={statuses} />
      )}
      {isFiltered && (
        <Button
          startIcon={<XIcon />}
          variant="ghost"
          onClick={() => table.resetColumnFilters()}
          className="h-8 px-2 lg:px-3"
        >
          Reset
        </Button>
      )}

      <TableViewOptions table={table} />
    </div>
  );
}
