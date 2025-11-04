"use client";

import { Separator } from "@risc0/ui/separator";
import Script from "next/script";
import { useEffect, useState } from "react";
import { FooterAscii } from "../../_components/footer-ascii";
import { type FormattedDataSetEntry, collectBenchesPerTestCase } from "../_utils/collect-benches-per-test-case";
import { BenchmarksContent } from "./benchmarks-content";
import { BenchmarksHeader } from "./benchmarks-header";

export function Benchmarks() {
  const [lastUpdate, setLastUpdate] = useState<string>("");
  const [benchSet, setBenchSet] =
    useState<
      {
        name: string;
        dataSet: Map<string, FormattedDataSetEntry[]>;
      }[]
    >();
  const [names, setNames] = useState<string[]>();
  const [ready, setReady] = useState<boolean>(false);

  useEffect(() => {
    const data = window.BENCHMARK_DATA;

    if (!ready || !data) {
      return;
    }

    setLastUpdate(new Date(data.lastUpdate).toUTCString());
    setNames(Object.keys(data.entries));
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
    const dataset = names.map((name) => ({
      name,
      dataSet: collectBenchesPerTestCase(data.entries[name]),
    }));

    setBenchSet(dataset);
  }, [names]);

  return (
    <>
      <BenchmarksHeader lastUpdate={lastUpdate} />

      <Separator className="mt-2" />

      <BenchmarksContent benchSet={benchSet} names={names} />

      <FooterAscii text="Benchmarks" />

      <Script
        src="https://risc0.github.io/ghpages/dev/bench/data.js"
        onReady={() => {
          setReady(true);
        }}
      />
    </>
  );
}
