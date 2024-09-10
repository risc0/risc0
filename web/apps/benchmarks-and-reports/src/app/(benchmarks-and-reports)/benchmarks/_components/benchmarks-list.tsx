"use client";

import { Command, CommandGroup, CommandItem, CommandList } from "@risc0/ui/command";
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
      <CommandList className="max-h-[calc(100dvh-19.5rem)] overscroll-contain">
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
