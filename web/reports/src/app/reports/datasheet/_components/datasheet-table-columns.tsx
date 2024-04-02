"use client";

import { createColumnHelper } from "@tanstack/react-table";
import TableColumnHeader from "~/client/table/table-column-header";
import formatBytes from "~/utils/format-bytes";
import formatDuration from "~/utils/format-duration";
import formatHz from "~/utils/format-hz";
import type { DatasheetTable } from "./datasheet-table-schema";

const columnHelper = createColumnHelper<DatasheetTable>();

const datasheetTableColumns = [
  {
    accessorKey: "total_cycles",
    header: ({ column }) => <TableColumnHeader column={column} title="Cycles" />,
    cell: ({ row }) => {
      return row.getValue("total_cycles") ? (
        <div className="font-mono">{`${row.original.total_cycles / 1024}k`}</div>
      ) : (
        <div className="font-mono">{`${row.original.cycles / 1024}k`}</div>
      );
    },
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
    cell: ({ row }) => {
      return row.getValue("throughput") ? (
        <div className="font-mono">{formatHz(row.original.throughput)}</div>
      ) : (
        <div className="font-mono">{formatHz(row.original.speed)}</div>
      );
    },
  },
];

export default datasheetTableColumns;
