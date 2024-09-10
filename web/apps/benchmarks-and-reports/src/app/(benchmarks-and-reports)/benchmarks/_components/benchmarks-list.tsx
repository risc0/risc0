"use client";

import { Command, CommandEmpty, CommandGroup, CommandInput, CommandItem, CommandList } from "@risc0/ui/command";
import { joinWords } from "@risc0/ui/utils/join-words";
import Link from "next/link";
import { usePathname } from "next/navigation";
import type { FormattedDataSetEntry } from "../_utils/collect-benches-per-test-case";

export function BenchmarksList({
  charts,
}: {
  charts: { name: string; dataSet: Map<string, FormattedDataSetEntry[]> }[];
}) {
  const pathname = usePathname();
  const selectedBench = pathname.split("/").pop() ?? "";

  return (
    <Command className="border">
      <CommandInput className="capitalize" placeholder={`${joinWords(selectedBench)} Benchmarks`} />
      <CommandList className="max-h-[calc(100dvh-19.5rem)] overscroll-contain">
        <CommandEmpty>No Results</CommandEmpty>
        {charts.flatMap((chart) =>
          chart.name === selectedBench
            ? [
                <CommandGroup key={chart.name}>
                  {[...chart.dataSet.keys()].map((benchmark) => (
                    <Link tabIndex={-1} key={`${chart.name}-${benchmark}`} scroll href={`#${chart.name}-${benchmark}`}>
                      <CommandItem className="cursor-pointer">{benchmark}</CommandItem>
                    </Link>
                  ))}
                </CommandGroup>,
              ]
            : [],
        )}
      </CommandList>
    </Command>
  );
}
