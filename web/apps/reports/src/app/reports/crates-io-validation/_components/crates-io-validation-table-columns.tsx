"use client";

import { Badge } from "@risc0/ui/badge";
import { Button } from "@risc0/ui/button";
import { cn } from "@risc0/ui/cn";
import { Dialog, DialogContent, DialogTitle, DialogTrigger } from "@risc0/ui/dialog";
import { createColumnHelper } from "@tanstack/react-table";
import { EyeIcon } from "lucide-react";
import { TableColumnHeader } from "~/client/table/table-column-header";
import type { CratesIoValidationTable } from "./crates-io-validation-table-schema";

const columnHelper = createColumnHelper<CratesIoValidationTable>();

export const cratesIoValidationTableColumns = [
  columnHelper.accessor("name", {
    header: ({ column }) => <TableColumnHeader column={column} title="Name" />,
    cell: (info) => <div className="font-mono text-xs">{info.getValue()}</div>,
  }),
  columnHelper.accessor("version", {
    header: ({ column }) => <TableColumnHeader column={column} title="Version" />,
    cell: (info) => <div className="font-mono text-xs">{info.getValue()}</div>,
  }),
  columnHelper.accessor("status", {
    filterFn: (row, id, value) => value.includes(row.getValue(id)),
    header: ({ column }) => <TableColumnHeader column={column} title="Status" />,
    cell: (info) => (
      <Badge
        className={cn(
          "p-2 py-0 text-[10px] rounded-full",
          info.getValue() === "Success"
            ? "border-green-200 bg-green-50 dark:bg-green-950"
            : info.getValue() === "BuildFail"
              ? "border-red-200 bg-red-50 dark:bg-red-950"
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
    cell: (info) => <div className="font-mono text-xs capitalize">{String(info.getValue())}</div>,
  }),
  columnHelper.accessor("build_errors", {
    header: ({ column }) => <TableColumnHeader column={column} title="Build Errors" />,
    cell: (info) => {
      return (
        info.getValue() && (
          <Badge title={info.getValue()} variant="secondary" className="max-w-xl line-clamp-6 font-mono text-[10px]">
            <pre>{info.getValue()}</pre>
          </Badge>
        )
      );
    },
  }),
  {
    accessorKey: "actions",
    header: undefined,
    cell: ({ row }) => {
      return (
        row.original.build_errors && (
          <Dialog>
            <DialogTrigger asChild>
              <Button size="sm" variant="outline" startIcon={<EyeIcon />}>
                View Build Errors
              </Button>
            </DialogTrigger>

            <DialogContent className="max-h-full max-w-screen-3xl">
              <DialogTitle>Build Errors for {row.original.name}</DialogTitle>
              <div className="overflow-auto max-h-[calc(100dvh-8rem)]">
                <pre className="text-[10px] ">{row.original.build_errors}</pre>
              </div>
            </DialogContent>
          </Dialog>
        )
      );
    },
  },
];
