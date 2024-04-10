"use client";

import { Badge } from "@risc0/ui/badge";
import { Button } from "@risc0/ui/button";
import { cn } from "@risc0/ui/cn";
import { Dialog, DialogContent, DialogTitle, DialogTrigger } from "@risc0/ui/dialog";
import { createColumnHelper } from "@tanstack/react-table";
import { EyeIcon } from "lucide-react";
import { Highlight, themes } from "prism-react-renderer";
import { TableColumnHeader } from "shared/client/table/table-column-header";
import { joinWords } from "shared/utils/join-words";
import type { CratesIoValidationTableSchema } from "./crates-io-validation-table-schema";

const columnHelper = createColumnHelper<CratesIoValidationTableSchema>();

export const cratesIoValidationTableColumns = [
  columnHelper.accessor("name", {
    header: ({ column }) => <TableColumnHeader column={column} title="Crate" />,
    cell: (info) => <div className="font-mono text-xs">{info.getValue()}</div>,
  }),
  columnHelper.accessor("version", {
    header: ({ column }) => <TableColumnHeader column={column} title="Crate Version" />,
    cell: (info) => <div className="font-mono text-xs">{info.getValue()}</div>,
  }),
  columnHelper.accessor("status", {
    filterFn: (row, id, value) => value.includes(row.getValue(id)),
    header: ({ column }) => <TableColumnHeader column={column} title="Build Status" />,
    cell: (info) => (
      <Badge
        className={cn(
          "rounded-full p-2 py-0 text-[10px]",
          info.getValue() === "Success"
            ? "border-green-200 bg-green-50 dark:bg-green-950"
            : info.getValue() === "BuildFail"
              ? "border-red-200 bg-red-50 dark:bg-red-950"
              : "text-foreground",
        )}
        variant="outline"
      >
        {joinWords(info.getValue())}
      </Badge>
    ),
  }),
  columnHelper.accessor("custom_profile", {
    filterFn: (row, id, value) => value.includes(row.getValue(id)), // converting this to string for comparison, since raw value is a boolean
    header: ({ column }) => (
      <TableColumnHeader
        description="The zkVM can be configured with a custom profile to fix the build errors of a crate"
        column={column}
        title="Custom Profile"
      />
    ),
    cell: (info) => <div className="font-mono text-xs capitalize">{String(info.getValue())}</div>,
  }),
  columnHelper.accessor("build_errors", {
    header: ({ column }) => (
      <TableColumnHeader
        column={column}
        title="Build Errors"
        description="Error logs produced while building the crate in the zkVM"
      />
    ),
    cell: (info) => {
      const originalString = info.getValue();

      if (!info.row.original.build_errors || !originalString) {
        return;
      }

      const errorIndex: number = originalString.indexOf("error");
      const methodNameIndex: number = originalString.lastIndexOf("\n", errorIndex);
      const resultString: string = originalString.substring(methodNameIndex + 1);

      return (
        <Dialog>
          <DialogTrigger asChild>
            <Badge
              title={info.getValue()}
              variant="secondary"
              className="relative line-clamp-5 max-w-lg cursor-pointer font-mono text-[10px] md:max-w-max"
            >
              <pre>{resultString}</pre>

              <Button
                size="sm"
                variant="outline"
                className="absolute bottom-1 left-1 text-destructive"
                startIcon={<EyeIcon />}
              >
                View Build Errors
              </Button>
            </Badge>
          </DialogTrigger>

          <DialogContent className="max-h-full max-w-screen-3xl">
            <DialogTitle>Build Errors for {info.row.original.name}</DialogTitle>
            <div className="max-h-[calc(100dvh-8rem)] overflow-auto bg-slate-950 dark:bg-inherit">
              <Highlight theme={themes.shadesOfPurple} code={info.row.original.build_errors} language="rust">
                {({ className, tokens, getLineProps, getTokenProps }) => (
                  <pre className={cn(className, "text-xs")}>
                    {tokens.map((line, index) => (
                      <div key={`row-${index}`} {...getLineProps({ line })}>
                        {line.map((token, index) => (
                          <span key={`token-${index}`} {...getTokenProps({ token })} />
                        ))}
                      </div>
                    ))}
                  </pre>
                )}
              </Highlight>
            </div>
          </DialogContent>
        </Dialog>
      );
    },
  }),
];
