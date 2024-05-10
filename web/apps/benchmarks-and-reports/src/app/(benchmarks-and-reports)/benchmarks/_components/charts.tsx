"use client";

import { Button } from "@risc0/ui/button";
import { useMounted } from "@risc0/ui/hooks/use-mounted";
import { Separator } from "@risc0/ui/separator";
import { Skeleton } from "@risc0/ui/skeleton";
import { Tabs, TabsContent, TabsList, TabsOverflowWrapper, TabsTrigger } from "@risc0/ui/tabs";
import { joinWords } from "@risc0/ui/utils/join-words";
import { DownloadIcon } from "lucide-react";
import Script from "next/script";
import { Fragment, useEffect, useState } from "react";
import { type FormattedDataSetEntry, collectBenchesPerTestCase } from "../_utils/collect-benches-per-test-case";
import { renderGraph } from "../_utils/render-graph";
import { ChartsList } from "./charts-list";

export function Charts() {
  const [lastUpdate, setLastUpdate] = useState<string>("");
  const [benchSet, setBenchSet] =
    useState<
      {
        name: string;
        dataSet: Map<string, FormattedDataSetEntry[]>;
      }[]
    >();
  const [selectedPlatform, setSelectedPlatform] = useState<string>();
  const [names, setNames] = useState<string[]>();
  const [ready, setReady] = useState<boolean>(false);
  const mounted = useMounted();

  useEffect(() => {
    const data = window.BENCHMARK_DATA;

    if (!ready || !data) {
      return;
    }

    setLastUpdate(new Date(data.lastUpdate).toLocaleString());
    setNames(Object.keys(data.entries));
    setSelectedPlatform(Object.keys(data.entries)[0]);
  }, [ready]);

  useEffect(() => {
    const data = window.BENCHMARK_DATA;

    if (!names || !data) {
      return;
    }

    //// Render download button
    // biome-ignore lint/style/noNonNullAssertion: ignore -- not my code
    document.getElementById("dl-button")!.onclick = () => {
      const dataStr = `data:text/json;charset=utf-8,${encodeURIComponent(JSON.stringify(data))}`;
      const a = document.createElement("a");
      a.href = dataStr;
      a.download = "benchmark_data.json";
      a.click();
    };

    // Prepare data points for charts
    const dataset = Object.keys(data.entries).map((name) => ({
      name,
      dataSet: collectBenchesPerTestCase(data.entries[name]),
    }));

    setBenchSet(dataset);
  }, [names]);

  if (!mounted) {
    return null;
  }

  return (
    <div>
      <div className="flex items-center justify-between">
        <div>
          <h1 className="title-sm">Benchmarks</h1>
          <div className="text-muted-foreground text-xs">
            <span>Last Update: {lastUpdate || <Skeleton className="inline-block h-2 w-28" />}</span>
          </div>
        </div>
        <div className="flex items-center gap-3">
          <Button id="dl-button" size="sm" variant="ghost" startIcon={<DownloadIcon />}>
            Download All Benchmarks Data
          </Button>
        </div>
      </div>

      <Separator className="mt-2" />

      {names && (
        <Tabs
          onValueChange={(value) => {
            setSelectedPlatform(value);
          }}
          defaultValue={names[0]}
          className="mt-6"
        >
          <TabsOverflowWrapper>
            <TabsList>
              {names.map((name) => (
                <TabsTrigger className="capitalize" key={name} value={name}>
                  {joinWords(name)}
                </TabsTrigger>
              ))}
            </TabsList>
          </TabsOverflowWrapper>

          <div className="mt-4 flex flex-row gap-8">
            <div className="sticky top-6 hidden min-w-[240px] self-start lg:block">
              {benchSet && selectedPlatform && <ChartsList charts={benchSet} selectedPlatform={selectedPlatform} />}
            </div>

            <div className="w-full lg:w-[calc(100%-240px-32px)]">
              {benchSet &&
                names.map((name) => (
                  <TabsContent tabIndex={-1} id={`chart-${name}`} key={name} value={name}>
                    {benchSet.map(({ name: platformName, dataSet }, index) => {
                      return (
                        <Fragment
                          // biome-ignore lint/suspicious/noArrayIndexKey: ignore
                          key={`${platformName}-${index}`}
                        >
                          {platformName === name && (
                            <div className="mt-6 flex flex-col gap-10 dark:invert">
                              {Array.from(dataSet, ([key, value]) =>
                                renderGraph({
                                  platformName,
                                  benchName: key,
                                  dataset: value,
                                }),
                              )}
                            </div>
                          )}
                        </Fragment>
                      );
                    })}
                  </TabsContent>
                ))}
            </div>
          </div>
        </Tabs>
      )}

      <Script
        src="https://risc0.github.io/ghpages/dev/bench/data.js"
        onReady={() => {
          setReady(true);
        }}
      />
    </div>
  );
}
