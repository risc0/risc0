"use client";

import Script from "next/script";
import { useState } from "react";
import { Charts } from "./charts";

export function ChartsWrapper() {
  const [renderCharts, setRenderCharts] = useState<boolean>(false);

  if (typeof window !== "undefined") {
    return (
      <>
        {(renderCharts || window.BENCHMARK_DATA) && <Charts />}

        <Script
          // TODO: replace with newer version
          src="https://cdn.jsdelivr.net/npm/chart.js@2.9.4/dist/Chart.min.js"
          onLoad={() => {
            setRenderCharts(true);
          }}
        />
      </>
    );
  }

  return null;
}
