"use client";

import Link from "next/link";
import { usePathname } from "next/navigation";
import { useUrlHash } from "shared/client/hooks/use-url-hash";
import type { FormattedDataSetEntry } from "../_utils/collect-benches-per-test-case";

export function BenchmarksList({
  charts,
}: {
  charts: { name: string; dataSet: Map<string, FormattedDataSetEntry[]> }[];
}) {
  const pathname = usePathname();
  const selectedBench = pathname.split("/").pop() ?? "";
  const urlHash = useUrlHash();

  return charts.flatMap((chart) =>
    chart.name === selectedBench
      ? [
          <div className="rounded-md border p-1" key={chart.name}>
            {[...chart.dataSet.keys()].map((benchmark) => {
              return (
                <Link
                  tabIndex={-1}
                  key={`${chart.name}-${benchmark}`}
                  scroll
                  aria-selected={`${chart.name}-${benchmark}` === urlHash}
                  href={`#${chart.name}-${benchmark}`}
                  className="flex select-none items-center rounded-sm px-2 py-1.5 text-sm outline-none hover:bg-accent aria-selected:bg-accent aria-selected:text-accent-foreground"
                >
                  {benchmark}
                </Link>
              );
            })}
          </div>,
        ]
      : [],
  );
}
