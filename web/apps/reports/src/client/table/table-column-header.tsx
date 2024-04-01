import type { Column } from "@tanstack/react-table";
import cn from "@web/shared/cn";
import Button from "@web/ui/button";
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuSeparator,
  DropdownMenuTrigger,
} from "@web/ui/dropdown-menu";
import { ArrowDownIcon, ArrowUpIcon, ChevronsUpDownIcon, EyeOffIcon } from "lucide-react";
import type { HTMLAttributes } from "react";

interface TableColumnHeaderProps<TData, TValue> extends HTMLAttributes<HTMLDivElement> {
  column: Column<TData, TValue>;
  title: string;
  align?: "left" | "right";
}

export default function TableColumnHeader<TData, TValue>({
  column,
  title,
  className,
  align = "left",
}: TableColumnHeaderProps<TData, TValue>) {
  if (!column.getCanSort()) {
    return <div className={cn(className)}>{title}</div>;
  }

  return (
    <div className={cn("flex items-center space-x-2", align === "right" && "justify-end", className)}>
      <DropdownMenu>
        <DropdownMenuTrigger asChild>
          <Button
            variant="ghost"
            size="sm"
            endIcon={
              column.getIsSorted() === "desc" ? (
                <ArrowDownIcon className="ml-2 size-3" />
              ) : column.getIsSorted() === "asc" ? (
                <ArrowUpIcon className="ml-2 size-3" />
              ) : (
                <ChevronsUpDownIcon className="ml-2 size-3" />
              )
            }
            className={cn(align === "left" ? "-ml-3" : "-mr-3", "h-8 data-[state=open]:bg-accent")}
          >
            {title}
          </Button>
        </DropdownMenuTrigger>
        <DropdownMenuContent align="start">
          <DropdownMenuItem onClick={() => column.toggleSorting(false)}>
            <ArrowUpIcon className="mr-2 size-3 text-muted-foreground/70" />
            Asc
          </DropdownMenuItem>
          <DropdownMenuItem onClick={() => column.toggleSorting(true)}>
            <ArrowDownIcon className="mr-2 size-3 text-muted-foreground/70" />
            Desc
          </DropdownMenuItem>
          <DropdownMenuSeparator />
          <DropdownMenuItem onClick={() => column.toggleVisibility(false)}>
            <EyeOffIcon className="mr-2 size-3 text-muted-foreground/70" />
            Hide
          </DropdownMenuItem>
        </DropdownMenuContent>
      </DropdownMenu>
    </div>
  );
}
