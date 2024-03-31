await import("./src/env.js");
import withBundleAnalyzer from "@next/bundle-analyzer";

/** @type {import("next").NextConfig} */
const config = {
  eslint: {
    ignoreDuringBuilds: true,
  },
  experimental: {
    ppr: true,
  },

  // biome-ignore lint/suspicious/useAwait: not needed
  async redirects() {
    return [
      {
        source: "/",
        destination: "/reports",
        permanent: true,
      },
    ];
  },
};

export default withBundleAnalyzer({
  enabled: process.env.ANALYZE === "true",
})(config);
