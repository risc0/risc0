"use client";

import { createColumnHelper } from "@tanstack/react-table";
import { TableColumnHeader } from "shared/client/table/table-column-header";
import { formatBytes } from "shared/utils/format-bytes";
import { formatDuration } from "shared/utils/format-duration";
import { formatHz } from "shared/utils/format-hz";
import type { DatasheetTableSchema } from "./datasheet-table-schema";

const columnHelper = createColumnHelper<DatasheetTableSchema>();

export const datasheetTableColumns = [
  {
    accessorKey: "total_cycles",
    header: ({ column }) => <TableColumnHeader column={column} title="Cycles" />,
    cell: ({ row }) => (
      <div className="font-mono">{`${(row.getValue("total_cycles") ?? row.getValue("cycles")) / 1024}k`}</div>
    ),
  },
  columnHelper.accessor("duration", {
    header: ({ column }) => <TableColumnHeader column={column} title="Duration" />,
    cell: (info) => <div className="font-mono">{formatDuration(info.getValue()) ?? "-"}</div>,
  }),
  columnHelper.accessor("ram", {
    header: ({ column }) => <TableColumnHeader column={column} title="RAM" />,
    cell: (info) => <div className="font-mono">{formatBytes(info.getValue()) ?? "-"}</div>,
  }),
  columnHelper.accessor("seal", {
    header: ({ column }) => <TableColumnHeader column={column} title="Seal" />,
    cell: (info) => <div className="font-mono">{formatBytes(info.getValue()) ?? "-"}</div>,
  }),
  {
    accessorKey: "throughput",
    header: ({ column }) => <TableColumnHeader column={column} title="Speed" />,
    cell: ({ row }) => (
      <div className="font-mono">{formatHz(row.getValue("throughput") ?? row.getValue("speed")) ?? "-"}</div>
    ),
  },
];
