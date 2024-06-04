import { Command, CommandEmpty, CommandGroup, CommandInput, CommandItem, CommandList } from "@risc0/ui/command";
import { joinWords } from "@risc0/ui/utils/join-words";
import Link from "next/link";
import type { FormattedDataSetEntry } from "../_utils/collect-benches-per-test-case";

export function BenchmarksList({
  charts,
  selectedPlatform,
}: {
  charts: { name: string; dataSet: Map<string, FormattedDataSetEntry[]> }[];
  selectedPlatform: string;
}) {
  return (
    <Command className="border">
      <CommandInput className="capitalize" placeholder={`${joinWords(selectedPlatform)} Benchmarks`} />
      <CommandList className="max-h-[calc(100dvh-19.5rem)] overscroll-contain">
        <CommandEmpty>No Results</CommandEmpty>
        {charts.flatMap((chart) =>
          // biome-ignore lint/correctness/useJsxKeyInIterable: ignore jsx key
          chart.name === selectedPlatform
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
