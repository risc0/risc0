"use client";

import { Input } from "@risc0/ui/input";
import type { Table } from "@tanstack/react-table";
import type { ComponentType, Dispatch, SetStateAction } from "react";
import { TableFacetedFilter } from "./table-faceted-filter";
import { TableViewOptions } from "./table-view-options";

type TableToolbarProps<TData> = {
  table: Table<TData>;
  globalFilter: string;
  statuses?: {
    label: string;
    value: string;
    icon?: ComponentType<{ className?: string }>;
  }[];
  customProfiles?: {
    label: string;
    value: boolean;
    icon?: ComponentType<{ className?: string }>;
  }[];
  setGlobalFilter: Dispatch<SetStateAction<string>>;
};

export function TableToolbar<TData>({
  table,
  statuses,
  customProfiles,
  setGlobalFilter,
  globalFilter,
}: TableToolbarProps<TData>) {
  return (
    <div className="flex items-center flex-wrap justify-start md:justify-end gap-2">
      <Input
        placeholder="Search…"
        value={globalFilter ?? ""}
        onChange={(event) => setGlobalFilter(String(event.target.value))}
        className="h-8 w-[180px]"
      />

      {statuses && table.getColumn("status") && (
        <TableFacetedFilter column={table.getColumn("status")} title="Build Status" options={statuses} />
      )}

      {customProfiles && table.getColumn("custom_profile") && (
        <TableFacetedFilter
          column={table.getColumn("custom_profile")}
          title="Custom Profile"
          options={customProfiles}
        />
      )}

      <TableViewOptions table={table} />
    </div>
  );
}
