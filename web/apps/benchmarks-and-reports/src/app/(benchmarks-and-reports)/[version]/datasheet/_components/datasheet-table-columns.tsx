"use client";

import { type ColumnDef, createColumnHelper } from "@tanstack/react-table";
import { TableColumnHeader } from "shared/client/table/table-column-header";
import { formatBytes } from "shared/utils/format-bytes";
import { formatCycles } from "shared/utils/format-cycles";
import { formatDuration } from "shared/utils/format-duration";
import { formatHz } from "shared/utils/format-hz";
import type { DatasheetTableSchema } from "./datasheet-table-schema";

const columnHelper = createColumnHelper<DatasheetTableSchema>();

export const datasheetTableColumns = [
  columnHelper.accessor("name", {
    header: ({ column }) => <TableColumnHeader column={column} title="Name" />,
    cell: (info) => <div className="truncate font-mono">{info.getValue() ?? "-"}</div>,
  }),
  columnHelper.accessor("hashfn", {
    header: ({ column }) => <TableColumnHeader column={column} title="Hash Function" />,
    cell: (info) => <div className="truncate font-mono">{info.getValue() ?? "-"}</div>,
  }),
  {
    accessorKey: "total_cycles",
    header: ({ column }) => <TableColumnHeader column={column} title="Cycles" />,
    cell: ({ row }) => (
      <div title={String(row.original.total_cycles ?? row.original.cycles)} className="truncate font-mono">
        {formatCycles(row.original.total_cycles ?? row.original.cycles) ?? "-"}
      </div>
    ),
  },
  columnHelper.accessor("duration", {
    header: ({ column }) => <TableColumnHeader column={column} title="Duration" />,
    cell: (info) => <div className="truncate font-mono">{formatDuration(info.getValue()) ?? "-"}</div>,
  }),
  columnHelper.accessor("ram", {
    header: ({ column }) => <TableColumnHeader column={column} title="RAM" />,
    cell: (info) => <div className="truncate font-mono">{formatBytes(info.getValue()) ?? "-"}</div>,
  }),
  columnHelper.accessor("seal", {
    header: ({ column }) => <TableColumnHeader column={column} title="Seal" />,
    cell: (info) => <div className="truncate font-mono">{formatBytes(info.getValue()) ?? "-"}</div>,
  }),
  {
    accessorKey: "throughput",
    header: ({ column }) => <TableColumnHeader column={column} title="Speed" />,
    cell: ({ row }) => (
      <div className="truncate font-mono">{formatHz(row.getValue("throughput") ?? row.getValue("speed")) ?? "-"}</div>
    ),
  },
] as ColumnDef<DatasheetTableSchema, unknown>[];
