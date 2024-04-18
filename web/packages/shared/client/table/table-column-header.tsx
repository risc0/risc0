import { Button } from "@risc0/ui/button";
import { cn } from "@risc0/ui/cn";
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuSeparator,
  DropdownMenuTrigger,
} from "@risc0/ui/dropdown-menu";
import { Tooltip, TooltipContent, TooltipTrigger } from "@risc0/ui/tooltip";
import type { Column } from "@tanstack/react-table";
import { ArrowDownIcon, ArrowUpIcon, ChevronsUpDownIcon, EyeOffIcon, InfoIcon } from "lucide-react";
import type { HTMLAttributes } from "react";

interface TableColumnHeaderProps<TData, TValue> extends HTMLAttributes<HTMLDivElement> {
  column: Column<TData, TValue>;
  title: string;
  align?: "left" | "right";
  description?: string;
}

export function TableColumnHeader<TData, TValue>({
  column,
  title,
  className,
  align = "left",
  description,
}: TableColumnHeaderProps<TData, TValue>) {
  if (!column.getCanSort()) {
    return (
      <Tooltip>
        <TooltipTrigger asChild>
          <div className={cn(className)}>{title}</div>
        </TooltipTrigger>
        {description && <TooltipContent>{description}</TooltipContent>}
      </Tooltip>
    );
  }

  return (
    <Tooltip>
      <div className={cn("flex items-center space-x-2", align === "right" && "justify-end", className)}>
        <DropdownMenu>
          <DropdownMenuTrigger asChild>
            <TooltipTrigger asChild>
              <Button
                variant="ghost"
                size="sm"
                startIcon={description ? <InfoIcon className="hover:cursor-help" /> : undefined}
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
            </TooltipTrigger>
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

        {description && <TooltipContent>{description}</TooltipContent>}
      </div>
    </Tooltip>
  );
}
