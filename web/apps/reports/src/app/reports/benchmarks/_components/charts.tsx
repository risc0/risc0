"use client";

import Button from "@risc0/ui/button";
import Separator from "@risc0/ui/separator";
import { DownloadIcon } from "lucide-react";
import Script from "next/script";
import { useState } from "react";

export default function Charts() {
  const [lastUpdate, setLastUpdate] = useState<string>();

  return (
    <div>
      <div className="flex items-center justify-between text-muted-foreground">
        <h1 className="title-sm">Benchmarks</h1>
        <div className="flex items-center gap-3">
          {lastUpdate && <p className="text-xs">Last Update: {lastUpdate}</p>}
          <Button id="dl-button" size="sm" variant="ghost" startIcon={<DownloadIcon />}>
            Download Data
          </Button>
        </div>
      </div>

      <Separator />

      <div className="mt-8 max-w-screen-md mx-auto">
        <div id="charts" />
      </div>

      <Script
        src="https://risc0.github.io/ghpages/dev/bench/data.js"
        onReady={() => {
          const toolColors = {
            cargo: "#dea584",
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

          function init() {
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

            // @ts-expect-error -- it exists
            const data = window.BENCHMARK_DATA;

            // Render last update date
            setLastUpdate(new Date(data.lastUpdate).toLocaleString());

            //// Render download button
            document.getElementById("dl-button")!.onclick = () => {
              const dataStr = `data:text/json;charset=utf-8,${encodeURIComponent(JSON.stringify(data))}`;
              const a = document.createElement("a");
              a.href = dataStr;
              a.download = "benchmark_data.json";
              a.click();
            };

            // Prepare data points for charts
            return Object.keys(data.entries).map((name) => ({
              name,
              dataSet: collectBenchesPerTestCase(data.entries[name]),
            }));
          }

          function renderAllChars(dataSets) {
            function renderGraph(parent, name, dataset) {
              const canvas = document.createElement("canvas");
              canvas.className = "benchmark-chart";
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
                  callbacks: {
                    afterTitle: (items) => {
                      const { index } = items[0];
                      const data = dataset[index];
                      return `\n${data.commit.message}\n\n${data.commit.timestamp} committed by @${data.commit.committer.username}\n`;
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

            function renderBenchSet(name, benchSet, main) {
              const setElem = document.createElement("div");
              setElem.className = "benchmark-set";
              main.appendChild(setElem);

              const nameElem = document.createElement("h1");
              nameElem.className = "benchmark-title";
              nameElem.textContent = name;
              setElem.appendChild(nameElem);

              const graphsElem = document.createElement("div");
              graphsElem.className = "benchmark-graphs";
              setElem.appendChild(graphsElem);

              for (const [benchName, benches] of benchSet.entries()) {
                renderGraph(graphsElem, benchName, benches);
              }
            }

            const main = document.getElementById("charts");
            for (const { name, dataSet } of dataSets) {
              renderBenchSet(name, dataSet, main);
            }
          }

          renderAllChars(init()); // Start
        }}
      />
    </div>
  );
}
