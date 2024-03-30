"use client";

import { createColumnHelper } from "@tanstack/react-table";
import formatBytes from "../../_utils/formatBytes";
import formatDuration from "../../_utils/formatDuration";
import formatNumber from "../../_utils/formatNumber";
import ApplicationsBenchmarksTableColumnHeader from "./applications-benchmarks-table-column-header";
import type { ApplicationsBenchmarksTable } from "./applications-benchmarks-table-schema";

const columnHelper = createColumnHelper<ApplicationsBenchmarksTable>();

const applicationsBenchmarksTableColumns = [
  columnHelper.accessor("job_name", {
    header: ({ column }) => <ApplicationsBenchmarksTableColumnHeader column={column} title="Job Name" />,
    cell: (info) => <div className="font-mono">{info.getValue()}</div>,
  }),
  columnHelper.accessor("job_size", {
    header: ({ column }) => <ApplicationsBenchmarksTableColumnHeader align="right" column={column} title="Job Size" />,
    cell: (info) => <div className="font-mono text-right">{formatNumber(info.getValue())}</div>,
  }),
  columnHelper.accessor("exec_duration", {
    header: ({ column }) => (
      <ApplicationsBenchmarksTableColumnHeader align="right" column={column} title="Execution Duration" />
    ),
    cell: (info) => <div className="font-mono text-right">{formatDuration(Number(info.getValue()))}</div>,
  }),
  columnHelper.accessor("proof_duration", {
    header: ({ column }) => (
      <ApplicationsBenchmarksTableColumnHeader align="right" column={column} title="Proof Duration" />
    ),
    cell: (info) => <div className="font-mono text-right">{formatDuration(Number(info.getValue()))}</div>,
  }),
  columnHelper.accessor("total_duration", {
    header: ({ column }) => (
      <ApplicationsBenchmarksTableColumnHeader align="right" column={column} title="Total Duration" />
    ),
    cell: (info) => <div className="font-mono text-right">{formatDuration(Number(info.getValue()))}</div>,
  }),
  columnHelper.accessor("verify_duration", {
    header: ({ column }) => (
      <ApplicationsBenchmarksTableColumnHeader align="right" column={column} title="Verify Duration" />
    ),
    cell: (info) => <div className="font-mono text-right">{formatDuration(Number(info.getValue()))}</div>,
  }),
  columnHelper.accessor("insn_cycles", {
    header: ({ column }) => (
      <ApplicationsBenchmarksTableColumnHeader align="right" column={column} title="INSN Cycles" />
    ),
    cell: (info) => <div className="font-mono text-right">{formatNumber(info.getValue())}</div>,
  }),
  columnHelper.accessor("prove_cycles", {
    header: ({ column }) => (
      <ApplicationsBenchmarksTableColumnHeader align="right" column={column} title="Prove Cycles" />
    ),
    cell: (info) => <div className="font-mono text-right">{formatNumber(info.getValue())}</div>,
  }),
  columnHelper.accessor("proof_bytes", {
    header: ({ column }) => (
      <ApplicationsBenchmarksTableColumnHeader align="right" column={column} title="Proof Bytes" />
    ),
    cell: (info) => <div className="font-mono text-right">{formatBytes(Number(info.getValue()))}</div>,
  }),
];

export default applicationsBenchmarksTableColumns;
