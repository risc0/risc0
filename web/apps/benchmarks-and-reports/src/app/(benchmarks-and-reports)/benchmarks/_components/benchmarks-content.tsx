"use client";

import { Tabs, TabsContent, TabsList, TabsTrigger } from "@risc0/ui/tabs";
import { joinWords } from "@risc0/ui/utils/join-words";
import Link from "next/link";
import { usePathname } from "next/navigation";
import { useEffect, useMemo } from "react";
import type { FormattedDataSetEntry } from "../_utils/collect-benches-per-test-case";
import { renderGraph } from "../_utils/render-graph";
import { BenchmarksList } from "./benchmarks-list";

// benchmarks you don't want to show up in the page
const HIDDEN_BENCHMARKS: string[] = [];

export function BenchmarksContent({
  names,
  benchSet,
}: {
  names?: string[];
  benchSet?: {
    name: string;
    dataSet: Map<string, FormattedDataSetEntry[]>;
  }[];
}) {
  const pathname = usePathname();
  const selectedBench = pathname.split("/").pop() ?? "";
  const getCurrentUrlHash = useMemo(
    () => () => (typeof window !== "undefined" ? window.location.hash.replace(/^#!?/, "") : ""),
    [],
  );

  useEffect(() => {
    const urlHash = getCurrentUrlHash();

    if (!names || !benchSet || !urlHash) {
      return;
    }

    document.getElementById(urlHash)?.scrollIntoView({ behavior: "instant" });
  }, [getCurrentUrlHash, names, benchSet]);

  if (!names) {
    return null;
  }

  return (
    <Tabs className="mt-6" value={selectedBench}>
      <TabsList className="flex flex-wrap justify-start">
        {names
          .filter((name) => !HIDDEN_BENCHMARKS.includes(name))
          .map((name) => {
            return (
              <Link href={`/benchmarks/${name}`} key={name}>
                <TabsTrigger className="capitalize" value={name}>
                  {joinWords(name)}
                </TabsTrigger>
              </Link>
            );
          })}
      </TabsList>

      <div className="mt-4 flex flex-row gap-8">
        <div className="sticky top-6 hidden min-w-[240px] self-start lg:block">
          {benchSet && <BenchmarksList charts={benchSet} />}
        </div>

        <div className="w-full lg:w-[calc(100%-240px-32px)]">
          {benchSet &&
            names.map((name) => (
              <TabsContent tabIndex={-1} id={`chart-${name}`} key={name} value={name}>
                {benchSet
                  .filter(({ name: platformName }) => platformName === name)
                  .map(({ name: platformName, dataSet }) => (
                    <div
                      className="-mt-8 flex flex-col"
                      key={`${platformName}-${name}-${Array.from(dataSet.keys()).join("-")}`}
                    >
                      {Array.from(dataSet, ([key, value]) =>
                        renderGraph({
                          platformName,
                          benchName: key,
                          dataset: value,
                        }),
                      )}
                    </div>
                  ))}
              </TabsContent>
            ))}
        </div>
      </div>
    </Tabs>
  );
}
