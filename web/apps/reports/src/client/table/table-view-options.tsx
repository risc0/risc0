"use client";

import { DropdownMenuTrigger } from "@radix-ui/react-dropdown-menu";
import type { Table } from "@tanstack/react-table";
import Button from "@web/ui/button";
import { DropdownMenu, DropdownMenuCheckboxItem, DropdownMenuContent } from "@web/ui/dropdown-menu";
import { Settings2Icon } from "lucide-react";

type TableViewOptionsProps<TData> = {
  table: Table<TData>;
};

export default function TableViewOptions<TData>({ table }: TableViewOptionsProps<TData>) {
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
              className="cursor-pointer"
              checked={column.getIsVisible()}
              onCheckedChange={(value) => column.toggleVisibility(!!value)}
            >
              {column.id}
            </DropdownMenuCheckboxItem>
          ))}
      </DropdownMenuContent>
    </DropdownMenu>
  );
}
