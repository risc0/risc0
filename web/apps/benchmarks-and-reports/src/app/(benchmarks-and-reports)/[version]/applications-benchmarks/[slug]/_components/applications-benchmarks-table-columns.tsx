"use client";

import { type ColumnDef, createColumnHelper } from "@tanstack/react-table";
import { TableColumnHeader } from "shared/client/table/table-column-header";
import { formatBytes } from "shared/utils/format-bytes";
import { formatDuration } from "shared/utils/format-duration";
import { formatNumber } from "shared/utils/format-number";
import type { ApplicationsBenchmarksTableSchema } from "./applications-benchmarks-table-schema";

const columnHelper = createColumnHelper<ApplicationsBenchmarksTableSchema>();

export const applicationsBenchmarksTableColumns = [
  columnHelper.accessor("name", {
    header: ({ column }) => <TableColumnHeader column={column} title="Name" />,
    cell: (info) => <div className="font-mono">{info.getValue()}</div>,
  }),
  columnHelper.accessor("size", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Size" />,
    cell: (info) => <div className="text-right font-mono">{formatNumber(info.getValue())}</div>,
  }),
  columnHelper.accessor("speed", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Speed" />,
    cell: (info) => <div className="text-right font-mono">{formatNumber(Number(info.getValue()))}</div>,
  }),
  columnHelper.accessor("total_duration", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Duration" />,
    cell: (info) => <div className="text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
  }),
  columnHelper.accessor("user_cycles", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="User Cycles" />,
    cell: (info) => <div className="text-right font-mono">{formatNumber(info.getValue())}</div>,
  }),
  columnHelper.accessor("total_cycles", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Total Cycles" />,
    cell: (info) => <div className="text-right font-mono">{formatNumber(info.getValue())}</div>,
  }),
  columnHelper.accessor("proof_bytes", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Bytes" />,
    cell: (info) => <div className="text-right font-mono">{formatBytes(Number(info.getValue()))}</div>,
  }),
] as ColumnDef<ApplicationsBenchmarksTableSchema, unknown>[];
