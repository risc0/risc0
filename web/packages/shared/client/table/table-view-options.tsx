"use client";

import { DropdownMenuTrigger } from "@radix-ui/react-dropdown-menu";
import { Button } from "@risc0/ui/button";
import { DropdownMenu, DropdownMenuCheckboxItem, DropdownMenuContent } from "@risc0/ui/dropdown-menu";
import { joinWords } from "@risc0/ui/utils/join-words";
import type { Table } from "@tanstack/react-table";
import { Settings2Icon } from "lucide-react";

type TableViewOptionsProps<TData> = {
  table: Table<TData>;
};

export function TableViewOptions<TData>({ table }: TableViewOptionsProps<TData>) {
  return (
    <DropdownMenu>
      <DropdownMenuTrigger asChild>
        <Button startIcon={<Settings2Icon />} variant="outline" size="sm">
          Show / Hide Columns
        </Button>
      </DropdownMenuTrigger>
      <DropdownMenuContent align="end" className="w-[162px]">
        {table
          .getAllColumns()
          .filter((column) => typeof column.accessorFn !== "undefined" && column.getCanHide())
          .map((column) => (
            <DropdownMenuCheckboxItem
              key={column.id}
              className="cursor-pointer capitalize"
              checked={column.getIsVisible()}
              onCheckedChange={(value) => column.toggleVisibility(!!value)}
            >
              {joinWords(column.id)}
            </DropdownMenuCheckboxItem>
          ))}
      </DropdownMenuContent>
    </DropdownMenu>
  );
}
