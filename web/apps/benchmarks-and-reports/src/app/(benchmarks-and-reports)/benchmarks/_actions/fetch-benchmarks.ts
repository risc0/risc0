import "server-only";

import { tryit } from "radash";

export async function fetchBenchmarks() {
  const tryFetch = tryit(fetch);
  const [error, response] = await tryFetch("https://risc0.github.io/ghpages/dev/bench/data.js", {
    next: {
      revalidate: 60,
    },
  });

  // error handling
  if (error || !response.ok) {
    throw error || new Error("Failed to fetch");
  }

  const text = await response.text();
  const data = JSON.parse(text.replace("window.BENCHMARK_DATA = ", "").trim());

  return data;
}
