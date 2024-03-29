"use client";

import { createColumnHelper } from "@tanstack/react-table";
import DatasheetTableColumnHeader from "./applications-benchmarks-table-column-header";
import type { DatasheetTable } from "./applications-benchmarks-table-schema";

const columnHelper = createColumnHelper<DatasheetTable>();

const datasheetTableColumns = [
  columnHelper.accessor("job_name", {
    header: ({ column }) => <DatasheetTableColumnHeader column={column} title="Duration" />,
    cell: (info) => <div className="font-mono">{info.getValue()}</div>,
  }),
  columnHelper.accessor("job_size", {
    header: ({ column }) => <DatasheetTableColumnHeader column={column} title="Duration" />,
    cell: (info) => <div className="font-mono">{info.getValue()}</div>,
  }),
  columnHelper.accessor("exec_duration", {
    header: ({ column }) => <DatasheetTableColumnHeader column={column} title="RAM" />,
    cell: (info) => <div className="font-mono">{info.getValue()}</div>,
  }),
  columnHelper.accessor("proof_duration", {
    header: ({ column }) => <DatasheetTableColumnHeader column={column} title="Seal" />,
    cell: (info) => <div className="font-mono">{info.getValue()}</div>,
  }),
];

export default datasheetTableColumns;
