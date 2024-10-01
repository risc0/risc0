await import("./src/env.js");

import withBundleAnalyzer from "@next/bundle-analyzer";
import { nextConfigBase } from "@risc0/ui/config/next.config.base.js";
import deepmerge from "deepmerge";
import { latestVersion } from "./src/versions.js";

/** @type {import("next").NextConfig} */
let config = deepmerge(nextConfigBase, {
  experimental: {
    ppr: false, // DO NOT USE PPR, breaks everything, don't bother with it
  },

  async redirects() {
    // @TODO: use the action instead, this can be achieved in https://github.com/risc0/risc0/pull/1940 gets merged in with typescript support for next config
    const response = await fetch("https://risc0.github.io/ghpages/dev/bench/data.js", {
      cache: "no-store",
    });
    const text = await response.text();
    const data = JSON.parse(text.replace("window.BENCHMARK_DATA = ", "").trim());
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
