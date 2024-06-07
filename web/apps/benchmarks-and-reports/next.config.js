await import("./src/env.js");

import withBundleAnalyzer from "@next/bundle-analyzer";
import { nextConfigBase } from "@risc0/ui/config/next.config.base.js";
import deepmerge from "deepmerge";
import { latestVersion } from "./src/versions.js";

/** @type {import("next").NextConfig} */
let config = deepmerge(nextConfigBase, {
  experimental: {
    staleTimes: {
      dynamic: 0,
      static: 0,
    },
  },
});

if (process.env.ANALYZE === "true") {
  config = withBundleAnalyzer({
    enabled: true,
  })(config);
}

export default config;
