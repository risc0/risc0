"use client";

import { createColumnHelper } from "@tanstack/react-table";
import TableColumnHeader from "~/client/table/table-column-header";
import formatBytes from "~/utils/format-bytes";
import formatDuration from "~/utils/format-duration";
import formatNumber from "~/utils/format-number";
import type { ApplicationsBenchmarksTable } from "./applications-benchmarks-table-schema";

const columnHelper = createColumnHelper<ApplicationsBenchmarksTable>();

const applicationsBenchmarksTableColumns = [
  columnHelper.accessor("job_name", {
    header: ({ column }) => <TableColumnHeader column={column} title="Job Name" />,
    cell: (info) => <div className="font-mono">{info.getValue()}</div>,
  }),
  columnHelper.accessor("job_size", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Job Size" />,
    cell: (info) => <div className="text-right font-mono">{formatNumber(info.getValue())}</div>,
  }),
  columnHelper.accessor("exec_duration", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Execution Duration" />,
    cell: (info) => <div className="text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
  }),
  columnHelper.accessor("proof_duration", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Duration" />,
    cell: (info) => <div className="text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
  }),
  columnHelper.accessor("total_duration", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Total Duration" />,
    cell: (info) => <div className="text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
  }),
  columnHelper.accessor("verify_duration", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Verify Duration" />,
    cell: (info) => <div className="text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
  }),
  columnHelper.accessor("insn_cycles", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="INSN Cycles" />,
    cell: (info) => <div className="text-right font-mono">{formatNumber(info.getValue())}</div>,
  }),
  columnHelper.accessor("prove_cycles", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Prove Cycles" />,
    cell: (info) => <div className="text-right font-mono">{formatNumber(info.getValue())}</div>,
  }),
  columnHelper.accessor("proof_bytes", {
    header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Bytes" />,
    cell: (info) => <div className="text-right font-mono">{formatBytes(Number(info.getValue()))}</div>,
  }),
];

export default applicationsBenchmarksTableColumns;
