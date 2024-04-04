"use client";

// TODO: this whole component was copy pasted from old code
// could probably improve a lot
import { Button } from "@risc0/ui/button";
import { Separator } from "@risc0/ui/separator";
import { Tabs, TabsContent, TabsList, TabsTrigger } from "@risc0/ui/tabs";
import truncate from "lodash-es/truncate";
import { DownloadIcon } from "lucide-react";
import Script from "next/script";
import { useEffect, useState } from "react";

const toolColors = {
  cargo: "#020077",
  go: "#00add8",
  benchmarkjs: "#f1e05a",
  benchmarkluau: "#000080",
  pytest: "#3572a5",
  googlecpp: "#f34b7d",
  catch2: "#f34b7d",
  julia: "#a270ba",
  jmh: "#b07219",
  benchmarkdotnet: "#178600",
  customBiggerIsBetter: "#38ff38",
  customSmallerIsBetter: "#ff3838",
  _: "#333333",
};

function renderGraph(parent, name, dataset) {
  const canvas = document.createElement("canvas");
  canvas.className = "benchmark-chart max-w-screen-sm";
  parent.appendChild(canvas);

  const color = toolColors[dataset.length > 0 ? dataset[0].tool : "_"];

  const data = {
    labels: dataset.map((d) => d.commit.id.slice(0, 7)),
    datasets: [
      {
        label: name,
        data: dataset.map((d) => d.bench.value),
        borderColor: color,
        fill: true,
        backgroundColor: `${color}60`, // Add alpha for #rrggbbaa
      },
    ],
  };

  const options = {
    scales: {
      xAxes: [
        {
          scaleLabel: {
            display: true,
            labelString: "commit",
          },
        },
      ],
      yAxes: [
        {
          scaleLabel: {
            display: true,
            labelString: dataset.length > 0 ? dataset[0].bench.unit : "",
          },
          ticks: {
            beginAtZero: true,
          },
        },
      ],
    },
    tooltips: {
      intersect: false,
      callbacks: {
        afterTitle: (items) => {
          const { index } = items[0];
          const data = dataset[index];
          return `\n${truncate(data.commit.message, {
            length: 180,
            omission: "...",
          })}\n\n${data.commit.timestamp} committed by @${data.commit.committer.username}\n`;
        },
        label: (item) => {
          let label = item.value;
          const { range, unit } = dataset[item.index].bench;
          label += ` ${unit}`;
          if (range) {
            label += ` (${range})`;
          }
          return label;
        },
        afterLabel: (item) => {
          const { extra } = dataset[item.index].bench;
          return extra ? `\n${extra}` : "";
        },
      },
    },
    onClick: (_mouseEvent, activeElems) => {
      if (activeElems.length === 0) {
        return;
      }
      // XXX: Undocumented. How can we know the index?
      const index = activeElems[0]._index;
      const url = dataset[index].commit.url;
      window.open(url, "_blank");
    },
  };

  // @ts-expect-error -- it exists
  // biome-ignore lint/correctness/noUndeclaredVariables: ignore
  new Chart(canvas, {
    type: "line",
    data,
    options,
  });
}

function renderBenchSet(benchSet, main) {
  const graphsElem = document.createElement("div");
  graphsElem.className = "flex flex-row flex-wrap gap-16 dark:invert";
  main.appendChild(graphsElem);

  for (const [benchName, benches] of benchSet.entries()) {
    renderGraph(graphsElem, benchName, benches);
  }
}

export function Charts() {
  const [lastUpdate, setLastUpdate] = useState<string>("");
  const [names, setNames] = useState<string[]>();
  const [ready, setReady] = useState<boolean>(false);

  useEffect(() => {
    // @ts-expect-error -- it exists
    const data = window.BENCHMARK_DATA;

    if (ready && data) {
      // @ts-expect-error -- it exists
      const data = window.BENCHMARK_DATA;

      setLastUpdate(new Date(data.lastUpdate).toLocaleString());
      setNames(Object.keys(data.entries));
    }
  }, [ready]);

  useEffect(() => {
    // @ts-expect-error -- it exists
    const data = window.BENCHMARK_DATA;

    if (names && data) {
      function collectBenchesPerTestCase(entries) {
        const map = new Map();
        for (const entry of entries) {
          const { commit, date, tool, benches } = entry;
          for (const bench of benches) {
            const result = { commit, date, tool, bench };
            const arr = map.get(bench.name);
            if (arr === undefined) {
              map.set(bench.name, [result]);
            } else {
              arr.push(result);
            }
          }
        }
        return map;
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

      for (const { name, dataSet } of dataset) {
        renderBenchSet(dataSet, document.getElementById(`chart-${name}`));
      }
    }
  }, [names]);

  return (
    <div>
      <div className="flex items-center justify-between">
        <div>
          <h1 className="title-sm">Benchmarks</h1>
          {lastUpdate && <p className="text-muted-foreground text-xs">Last Update: {lastUpdate}</p>}
        </div>
        <div className="flex items-center gap-3">
          <Button id="dl-button" size="sm" variant="ghost" startIcon={<DownloadIcon />}>
            Download Data
          </Button>
        </div>
      </div>

      <Separator className="mt-2" />

      {names && (
        <Tabs defaultValue={names[0]} className="mt-6">
          <div className="flex items-center overflow-auto">
            <TabsList>
              {names.map((name) => (
                <TabsTrigger key={name} value={name}>
                  {name}
                </TabsTrigger>
              ))}
            </TabsList>
          </div>

          {names.map((name) => (
            <TabsContent className="mt-4" id={`chart-${name}`} key={name} value={name} />
          ))}
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
