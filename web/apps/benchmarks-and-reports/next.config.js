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

  // biome-ignore lint/suspicious/useAwait: needs to be async
  async redirects() {
    return [
      {
        source: "/",
        destination: latestVersion ? `/${latestVersion}` : "/",
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
