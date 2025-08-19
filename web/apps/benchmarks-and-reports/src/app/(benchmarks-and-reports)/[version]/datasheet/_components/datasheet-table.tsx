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
  getSortedRowModel,
  type SortingState,
  useReactTable,
  type VisibilityState,
} from "@tanstack/react-table";
import { Children, isValidElement, type ReactNode, useState } from "react";
import { TableToolbar } from "shared/client/table/table-toolbar";
import { tableFuzzyFilter } from "shared/utils/table-fuzzy-filter";

const MAX_AMOUNT_OF_ROWS = 25;

export function DatasheetTable<TData, TValue>({
  title,
  columns,
  data,
}: {
  columns: ColumnDef<TData, TValue>[];
  data: TData[];
  title: ReactNode;
}) {
  const [rowSelection, setRowSelection] = useState({});
  const [columnVisibility, setColumnVisibility] = useState<VisibilityState>({});
  const [columnFilters, setColumnFilters] = useState<ColumnFiltersState>([]);
  const [sorting, setSorting] = useState<SortingState>([]);

  const table = useReactTable({
    data,
    columns,
    state: {
      sorting,
      columnVisibility,
      rowSelection,
      columnFilters,
    },
    filterFns: {
      fuzzy: tableFuzzyFilter,
    },
    onRowSelectionChange: setRowSelection,
    onSortingChange: setSorting,
    onColumnFiltersChange: setColumnFilters,
    onColumnVisibilityChange: setColumnVisibility,
    getCoreRowModel: getCoreRowModel(),
    getFilteredRowModel: getFilteredRowModel(),
    getSortedRowModel: getSortedRowModel(),
    getFacetedRowModel: getFacetedRowModel(),
    getFacetedUniqueValues: getFacetedUniqueValues(),
  });
  const titleString = Children.toArray(title)
    .map((child) => {
      if (isValidElement(child)) {
        // Type assertion since we know child is a ReactElement when isValidElement is true
        return (child as { props: { children: string } }).props.children;
      }
      return child;
    })
    .join("");

  return (
    <div id={titleString.toLowerCase().split(" ").join("_").replaceAll(".", "")} className="space-y-4">
      <div className="flex flex-wrap items-center justify-between gap-3">
        <h2 className="truncate text-xl">{title}</h2>
        <TableToolbar table={table} />
      </div>

      <div className="overflow-auto rounded border">
        <Table>
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
              table.getRowModel().rows.map(
                (row, index) =>
                  index < MAX_AMOUNT_OF_ROWS && (
                    <TableRow key={row.id} data-state={row.getIsSelected() && "selected"}>
                      {row.getVisibleCells().map((cell) => (
                        <TableCell key={cell.id}>{flexRender(cell.column.columnDef.cell, cell.getContext())}</TableCell>
                      ))}
                    </TableRow>
                  ),
              )
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
    </div>
  );
}
