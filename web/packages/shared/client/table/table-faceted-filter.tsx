import { Badge } from "@risc0/ui/badge";
import { Button } from "@risc0/ui/button";
import { cn } from "@risc0/ui/cn";
import {
  Command,
  CommandEmpty,
  CommandGroup,
  CommandInput,
  CommandItem,
  CommandList,
  CommandSeparator,
} from "@risc0/ui/command";
import { Popover, PopoverContent, PopoverTrigger } from "@risc0/ui/popover";
import { Separator } from "@risc0/ui/separator";
import { joinWords } from "@risc0/ui/utils/join-words";
import type { Column } from "@tanstack/react-table";
import { CheckIcon, PlusCircleIcon } from "lucide-react";
import type { ComponentType } from "react";

interface TableFacetedFilterProps<TData, TValue> {
  column?: Column<TData, TValue>;
  title?: string;
  options: {
    label: string;
    value: string | boolean;
    icon?: ComponentType<{ className?: string }>;
  }[];
}

export function TableFacetedFilter<TData, TValue>({ column, title, options }: TableFacetedFilterProps<TData, TValue>) {
  const facets = column?.getFacetedUniqueValues();
  const selectedValues = new Set<string | boolean>(column?.getFilterValue() as (string | boolean)[]);

  return (
    <Popover>
      <PopoverTrigger asChild>
        <Button
          startIcon={selectedValues?.size === 0 ? <PlusCircleIcon /> : undefined}
          variant="outline"
          size="sm"
          className={cn(selectedValues?.size === 0 && "border-dashed")}
        >
          {title}

          {selectedValues?.size > 0 && (
            <>
              <Separator orientation="vertical" className="mx-2 h-4" />
              <Badge variant="secondary" className="px-1 font-normal lg:hidden">
                {selectedValues.size}
              </Badge>
              <div className="hidden space-x-1 lg:flex">
                {selectedValues.size > 4 ? (
                  <Badge variant="secondary" className="px-1 font-normal">
                    {selectedValues.size} selected
                  </Badge>
                ) : (
                  options
                    .filter((option) => selectedValues.has(option.value))
                    .map((option) => (
                      <Badge
                        key={`options-${option.value}`}
                        className={cn(
                          "rounded-full p-2 py-0 text-[10px]",
                          option.label === "Success"
                            ? "border-green-200 bg-green-50 dark:bg-green-950"
                            : option.label === "BuildFail"
                              ? "border-red-200 bg-red-50 dark:bg-red-950"
                              : "text-foreground",
                        )}
                        variant="outline"
                      >
                        {joinWords(option.label)}
                      </Badge>
                    ))
                )}
              </div>
            </>
          )}
        </Button>
      </PopoverTrigger>
      <PopoverContent className="w-[200px] p-0" align="start">
        <Command>
          <CommandInput placeholder={title} />
          <CommandList>
            <CommandEmpty>No Results Found</CommandEmpty>
            <CommandGroup>
              {options.map((option) => {
                const isSelected = selectedValues.has(option.value);

                return (
                  <CommandItem
                    key={`options-${option.value}`}
                    onSelect={() => {
                      if (isSelected) {
                        selectedValues.delete(option.value);
                      } else {
                        selectedValues.add(option.value);
                      }
                      const filterValues = Array.from(selectedValues);
                      column?.setFilterValue(filterValues.length ? filterValues : undefined);
                    }}
                    className="cursor-pointer"
                  >
                    <div
                      className={cn(
                        "mr-2 flex size-4 items-center justify-center rounded-[3px] border border-primary",
                        isSelected ? "bg-primary text-primary-foreground" : "opacity-50 [&_svg]:invisible",
                      )}
                    >
                      <CheckIcon className={cn("size-4")} />
                    </div>

                    {option.icon && <option.icon className="mr-2 size-4 text-muted-foreground" />}

                    <span>{joinWords(option.label)}</span>

                    <span className="ml-auto flex size-4 items-center justify-end font-mono text-xs">
                      {facets?.get(option.value) || 0}
                    </span>
                  </CommandItem>
                );
              })}
            </CommandGroup>

            {selectedValues.size > 0 && (
              <>
                <CommandSeparator />
                <CommandGroup>
                  <CommandItem
                    onSelect={() => column?.setFilterValue(undefined)}
                    className="cursor-pointer justify-center text-center"
                  >
                    Clear Filters
                  </CommandItem>
                </CommandGroup>
              </>
            )}
          </CommandList>
        </Command>
      </PopoverContent>
    </Popover>
  );
}
