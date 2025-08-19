"use client";

import { Table, TableBody, TableCell, TableHead, TableHeader, TableRow } from "@risc0/ui/table";
import {
  type ColumnDef,
  type ColumnFiltersState,
  flexRender,
  getCoreRowModel,
  getFacetedRowModel,
  getFacetedUniqueValues,
  getFilteredRowModel,
  getPaginationRowModel,
  getSortedRowModel,
  type SortingState,
  useReactTable,
  type VisibilityState,
} from "@tanstack/react-table";
import { useState } from "react";
import { TablePagination } from "shared/client/table/table-pagination";
import { TableToolbar } from "shared/client/table/table-toolbar";
import { formatNumber } from "shared/utils/format-number";
import { tableFuzzyFilter } from "shared/utils/table-fuzzy-filter";

type CratesIoValidationTableProps<TData, TValue> = {
  columns: ColumnDef<TData, TValue>[];
  data: TData[];
};

export function CratesIoValidationTable<TData, TValue>({ columns, data }: CratesIoValidationTableProps<TData, TValue>) {
  const [columnVisibility, setColumnVisibility] = useState<VisibilityState>({});
  const [columnFilters, setColumnFilters] = useState<ColumnFiltersState>([]);
  const [sorting, setSorting] = useState<SortingState>([]);
  const [globalFilter, setGlobalFilter] = useState<string>("");

  const table = useReactTable({
    data,
    columns,
    state: {
      sorting,
      columnVisibility,
      columnFilters,
      globalFilter,
    },
    initialState: {
      pagination: {
        pageSize: 100,
      },
    },
    filterFns: {
      fuzzy: tableFuzzyFilter,
    },
    onGlobalFilterChange: setGlobalFilter,
    globalFilterFn: tableFuzzyFilter,
    onSortingChange: setSorting,
    onColumnFiltersChange: setColumnFilters,
    onColumnVisibilityChange: setColumnVisibility,
    getCoreRowModel: getCoreRowModel(),
    getFilteredRowModel: getFilteredRowModel(),
    getSortedRowModel: getSortedRowModel(),
    getPaginationRowModel: getPaginationRowModel(),
    getFacetedRowModel: getFacetedRowModel(),
    getFacetedUniqueValues: getFacetedUniqueValues(),
  });

  return (
    <div className="space-y-4">
      <div className="flex flex-wrap items-center justify-between gap-3">
        <h2 className="text-xl">
          Crates{" "}
          <span className="ml-2 font-normal text-muted-foreground text-sm">
            {formatNumber(table.getRowCount())} results
          </span>
        </h2>
        <TableToolbar
          statuses={[
            {
              value: "Success",
              label: "Success",
            },
            {
              value: "BuildFail",
              label: "BuildFail",
            },
            {
              value: "Skipped",
              label: "Skipped",
            },
            {
              value: "RunFail",
              label: "RunFail",
            },
          ]}
          customProfiles={[
            {
              value: true,
              label: "True",
            },
            {
              value: false,
              label: "False",
            },
          ]}
          globalFilter={globalFilter}
          setGlobalFilter={setGlobalFilter}
          table={table}
        />
      </div>

      <div className="overflow-auto rounded border">
        <Table className="table-auto md:table-fixed">
          <TableHeader>
            {table.getHeaderGroups().map((headerGroup) => (
              <TableRow key={headerGroup.id}>
                {headerGroup.headers.map((header) => (
                  <TableHead key={header.id} colSpan={header.colSpan}>
                    {header.isPlaceholder ? null : flexRender(header.column.columnDef.header, header.getContext())}
                  </TableHead>
                ))}
              </TableRow>
            ))}
          </TableHeader>
          <TableBody className="border-transparent">
            {table.getRowModel().rows?.length ? (
              table.getRowModel().rows.map((row) => (
                <TableRow key={row.id} data-state={row.getIsSelected() && "selected"}>
                  {row.getVisibleCells().map((cell, index, { length }) => (
                    <TableCell colSpan={index === length - 1 ? 4 : 1} key={cell.id}>
                      {flexRender(cell.column.columnDef.cell, cell.getContext())}
                    </TableCell>
                  ))}
                </TableRow>
              ))
            ) : (
              <TableRow>
                <TableCell colSpan={columns.length} className="h-24 text-center text-muted-foreground">
                  No Results
                </TableCell>
              </TableRow>
            )}
          </TableBody>
        </Table>
      </div>
      <TablePagination table={table} />
    </div>
  );
}
