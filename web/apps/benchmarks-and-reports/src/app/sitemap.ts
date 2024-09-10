import { VERSIONS } from "~/versions";
import { APPLICATIONS_BENCHMARKS_FILENAMES_TO_TITLES } from "./(benchmarks-and-reports)/[version]/applications-benchmarks/[slug]/_utils/constants";

export const baseUrl = "https://reports.risczero.com";

export default async function sitemap() {
  const response = await fetch("https://risc0.github.io/ghpages/dev/bench/data.js", {
    cache: "no-store",
  });
  const text = await response.text();
  const data = JSON.parse(text.replace("window.BENCHMARK_DATA = ", "").trim());
  const benchmarksSlugs = Object.keys(data.entries);

  return [
    // crates validation
    "/crates-validation",

    // datasheet
    ...VERSIONS.flatMap(({ value }) => [`/${value}`, `/${value}/datasheet`]),

    // benchmarks
    ...benchmarksSlugs.map((slug) => `/benchmarks/${slug}`),

    // applications benchmarks
    ...VERSIONS.flatMap(({ value }) =>
      Object.keys(APPLICATIONS_BENCHMARKS_FILENAMES_TO_TITLES[value]).map(
        (filename) => `/${value}/applications-benchmarks/${filename.replace(".csv", "")}`,
      ),
    ),
  ].map((route) => ({
    url: `${baseUrl}${route}`,
    lastModified: new Date().toISOString().split("T")[0],
  }));
}
