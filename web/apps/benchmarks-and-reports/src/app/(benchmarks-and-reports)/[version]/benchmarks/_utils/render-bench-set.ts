import type { FormattedDataSetEntry } from "./collect-benches-per-test-case";
import { renderGraph } from "./render-graph";

export function renderBenchSet({
  platformName,
  benchSet,
  main,
}: { platformName: string; benchSet: Map<string, FormattedDataSetEntry[]>; main: HTMLElement }) {
  const graphsElem = document.createElement("div");
  graphsElem.className = "mt-6 flex flex-row flex-wrap gap-10 dark:invert [&>*]:tracking-normal";
  main.appendChild(graphsElem);

  for (const [benchName, benches] of benchSet.entries()) {
    renderGraph({ parent: graphsElem, benchName, dataset: benches, platformName });
  }
}
