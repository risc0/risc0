"use client";

import { Tabs, TabsContent, TabsList, TabsTrigger } from "@risc0/ui/tabs";
import { joinWords } from "@risc0/ui/utils/join-words";
import { Fragment } from "react";
import { renderGraph } from "../_utils/render-graph";
import { BenchmarksList } from "./benchmarks-list";

export function BenchmarksContent({ names, setSelectedPlatform, selectedPlatform, benchSet }) {
  return (
    names && (
      <Tabs
        onValueChange={(value) => {
          setSelectedPlatform(value);
        }}
        defaultValue={names[0]}
        className="mt-6"
      >
        <TabsList>
          {names.map((name) => (
            <TabsTrigger className="capitalize" key={name} value={name}>
              {joinWords(name)}
            </TabsTrigger>
          ))}
        </TabsList>

        <div className="mt-4 flex flex-row gap-8">
          <div className="sticky top-6 hidden min-w-[240px] self-start lg:block">
            {benchSet && selectedPlatform && <BenchmarksList charts={benchSet} selectedPlatform={selectedPlatform} />}
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
    )
  );
}
