import "./src/env";

import withBundleAnalyzer from "@next/bundle-analyzer";
import { nextConfigBase } from "@risc0/ui/config/next.config.base.js";
import deepmerge from "deepmerge";
import type { NextConfig } from "next";
import { fetchBenchmarks } from "~/app/(benchmarks-and-reports)/benchmarks/_actions/fetch-benchmarks";
import { latestVersion } from "./src/versions.js";

let config: NextConfig = deepmerge(nextConfigBase, {
  experimental: {
    ppr: false, // DO NOT USE PPR, breaks everything, don't bother with it
  },

  async redirects() {
    const data = await fetchBenchmarks();
    const benchmarksSlugs = Object.keys(data.entries);

    return [
      {
        source: "/",
        destination: latestVersion ? `/${latestVersion}` : "/",
        permanent: true,
      },
      {
        source: "/:version/applications-benchmarks",
        destination: "/:version/applications-benchmarks/macOS-apple_m2_pro", // TODO: make sure this is the right default
        permanent: true,
      },
      {
        source: "/benchmarks",
        destination: `/benchmarks/${benchmarksSlugs[0]}`,
        permanent: true,
      },
    ];
  },
});

if (process.env.ANALYZE === "true") {
  config = withBundleAnalyzer({
    enabled: true,
  })(config);
}

export default config;
