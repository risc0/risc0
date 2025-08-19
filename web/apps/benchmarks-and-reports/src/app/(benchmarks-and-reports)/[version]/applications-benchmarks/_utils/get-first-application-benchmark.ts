import type { Version } from "@/types/version";
import { APPLICATIONS_BENCHMARKS_FILENAMES_TO_TITLES } from "../[slug]/_utils/constants";

export function getFirstApplicationBenchmark(version: Version) {
  const firstApplicationBenchmarks = Object.keys(APPLICATIONS_BENCHMARKS_FILENAMES_TO_TITLES[version])[0];

  return firstApplicationBenchmarks?.replace(".csv", "");
}
