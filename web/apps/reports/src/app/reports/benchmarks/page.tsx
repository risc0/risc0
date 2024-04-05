"use client";

import type { Metadata } from "next";
import Script from "next/script";
import { useState } from "react";
import { Charts } from "./_components/charts";

export default function BenchmarksPage() {
  const [renderCharts, setRenderCharts] = useState<boolean>(false);

  return (
    <div className="container max-w-screen-3xl pt-4">
      {(renderCharts || window.BENCHMARK_DATA) && <Charts />}

      <Script
        // TODO: replace with newer version
        src="https://cdn.jsdelivr.net/npm/chart.js@2.9.4/dist/Chart.min.js"
        onLoad={() => {
          setRenderCharts(true);
        }}
      />
    </div>
  );
}
