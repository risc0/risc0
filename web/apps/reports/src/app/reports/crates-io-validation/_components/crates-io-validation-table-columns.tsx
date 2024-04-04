"use client";

import { Badge } from "@risc0/ui/badge";
import { cn } from "@risc0/ui/cn";
import { createColumnHelper } from "@tanstack/react-table";
import { TableColumnHeader } from "~/client/table/table-column-header";
import type { CratesIoValidationTable } from "./crates-io-validation-table-schema";

const columnHelper = createColumnHelper<CratesIoValidationTable>();

export const cratesIoValidationTableColumns = [
  columnHelper.accessor("name", {
    header: ({ column }) => <TableColumnHeader column={column} title="Name" />,
    cell: (info) => <div className="font-mono">{info.getValue()}</div>,
  }),
  columnHelper.accessor("version", {
    header: ({ column }) => <TableColumnHeader column={column} title="Version" />,
    cell: (info) => <div className="font-mono">{info.getValue()}</div>,
  }),
  columnHelper.accessor("status", {
    filterFn: (row, id, value) => value.includes(row.getValue(id)),
    header: ({ column }) => <TableColumnHeader column={column} title="Status" />,
    cell: (info) => (
      <Badge
        className={cn(
          "p-2 py-0 text-[10px]",
          info.getValue() === "Success"
            ? "border-green-200 bg-green-50 dark:bg-inherit"
            : info.getValue() === "BuildFail"
              ? "border-orange-200 bg-orange-50 dark:bg-inherit"
              : "text-foreground",
        )}
        variant="outline"
      >
        {info.getValue()}
      </Badge>
    ),
  }),
  columnHelper.accessor("custom_profile", {
    header: ({ column }) => <TableColumnHeader column={column} title="Custom Profile" />,
    cell: (info) => <div className="font-mono capitalize">{String(info.getValue())}</div>,
  }),
  columnHelper.accessor("build_errors", {
    header: ({ column }) => <TableColumnHeader column={column} title="Build Errors" />,
    cell: (info) =>
      info.getValue() && (
        <Badge title={info.getValue()} variant="secondary" className="max-w-xl line-clamp-6 font-mono text-xs">
          <pre>{info.getValue()}</pre>
        </Badge>
      ),
  }),
];
