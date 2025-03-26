"use client";

import { type ColumnDef, createColumnHelper } from "@tanstack/react-table";
import { TableColumnHeader } from "shared/client/table/table-column-header";
import { formatBytes } from "shared/utils/format-bytes";
import { formatDuration } from "shared/utils/format-duration";
import { formatNumber } from "shared/utils/format-number";
import type { ApplicationsBenchmarksTableSchema } from "./applications-benchmarks-table-schema";

const columnHelper = {
  "release-0.21": createColumnHelper<ApplicationsBenchmarksTableSchema<"release-0.21">>(),
  main: createColumnHelper<ApplicationsBenchmarksTableSchema<"main">>(),
};

export const applicationsBenchmarksTableColumns = {
  "release-0.21": [
    columnHelper["release-0.21"].accessor("job_name", {
      header: ({ column }) => <TableColumnHeader column={column} title="Job Name" />,
      cell: (info) => <div className="truncate font-mono">{info.getValue()}</div>,
    }),
    columnHelper["release-0.21"].accessor("job_size", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Job Size" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper["release-0.21"].accessor("exec_duration", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Execution Duration" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
    }),
    columnHelper["release-0.21"].accessor("proof_duration", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Duration" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
    }),
    columnHelper["release-0.21"].accessor("total_duration", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Total Duration" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
    }),
    columnHelper["release-0.21"].accessor("verify_duration", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Verify Duration" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
    }),
    columnHelper["release-0.21"].accessor("insn_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="INSN Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper["release-0.21"].accessor("prove_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Prove Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper["release-0.21"].accessor("proof_bytes", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Bytes" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatBytes(Number(info.getValue()))}</div>,
    }),
  ] as ColumnDef<ApplicationsBenchmarksTableSchema<"release-0.21">, unknown>[],
  main: [
    columnHelper.main.accessor("name", {
      header: ({ column }) => <TableColumnHeader column={column} title="Name" />,
      cell: (info) => <div className="truncate font-mono">{info.getValue()}</div>,
    }),
    columnHelper.main.accessor("size", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Size" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("speed", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Speed" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(Number(info.getValue()))}</div>,
    }),
    columnHelper.main.accessor("total_duration", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Duration" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
    }),
    columnHelper.main.accessor("user_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="User Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("total_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Total Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("proof_bytes", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Bytes" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatBytes(Number(info.getValue()))}</div>,
    }),
  ] as ColumnDef<ApplicationsBenchmarksTableSchema<"main">, unknown>[],
  "release-1.0": [
    columnHelper.main.accessor("name", {
      header: ({ column }) => <TableColumnHeader column={column} title="Name" />,
      cell: (info) => <div className="truncate font-mono">{info.getValue()}</div>,
    }),
    columnHelper.main.accessor("size", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Size" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("speed", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Speed" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(Number(info.getValue()))}</div>,
    }),
    columnHelper.main.accessor("total_duration", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Duration" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
    }),
    columnHelper.main.accessor("user_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="User Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("total_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Total Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("proof_bytes", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Bytes" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatBytes(Number(info.getValue()))}</div>,
    }),
  ] as ColumnDef<ApplicationsBenchmarksTableSchema<"release-1.0">, unknown>[],
  "release-1.1": [
    columnHelper.main.accessor("name", {
      header: ({ column }) => <TableColumnHeader column={column} title="Name" />,
      cell: (info) => <div className="truncate font-mono">{info.getValue()}</div>,
    }),
    columnHelper.main.accessor("size", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Size" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("speed", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Speed" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(Number(info.getValue()))}</div>,
    }),
    columnHelper.main.accessor("total_duration", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Duration" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
    }),
    columnHelper.main.accessor("user_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="User Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("total_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Total Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("proof_bytes", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Bytes" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatBytes(Number(info.getValue()))}</div>,
    }),
  ] as ColumnDef<ApplicationsBenchmarksTableSchema<"release-1.1">, unknown>[],
  "release-1.2": [
    columnHelper.main.accessor("name", {
      header: ({ column }) => <TableColumnHeader column={column} title="Name" />,
      cell: (info) => <div className="truncate font-mono">{info.getValue()}</div>,
    }),
    columnHelper.main.accessor("size", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Size" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("speed", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Speed" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(Number(info.getValue()))}</div>,
    }),
    columnHelper.main.accessor("total_duration", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Duration" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
    }),
    columnHelper.main.accessor("user_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="User Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("total_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Total Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("proof_bytes", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Bytes" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatBytes(Number(info.getValue()))}</div>,
    }),
  ] as ColumnDef<ApplicationsBenchmarksTableSchema<"release-1.2">, unknown>[],
  "release-2.0": [
    columnHelper.main.accessor("name", {
      header: ({ column }) => <TableColumnHeader column={column} title="Name" />,
      cell: (info) => <div className="truncate font-mono">{info.getValue()}</div>,
    }),
    columnHelper.main.accessor("size", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Size" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("speed", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Speed" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(Number(info.getValue()))}</div>,
    }),
    columnHelper.main.accessor("total_duration", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Duration" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatDuration(Number(info.getValue()))}</div>,
    }),
    columnHelper.main.accessor("user_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="User Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("total_cycles", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Total Cycles" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatNumber(info.getValue())}</div>,
    }),
    columnHelper.main.accessor("proof_bytes", {
      header: ({ column }) => <TableColumnHeader align="right" column={column} title="Proof Bytes" />,
      cell: (info) => <div className="truncate text-right font-mono">{formatBytes(Number(info.getValue()))}</div>,
    }),
  ] as ColumnDef<ApplicationsBenchmarksTableSchema<"release-2.0">, unknown>[],
};
