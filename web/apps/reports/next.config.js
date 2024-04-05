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
  reactStrictMode: true,
  swcMinify: true,
  transpilePackages: ["@risc0/ui"],
};

export default withBundleAnalyzer({
  enabled: process.env.ANALYZE === "true",
})(config);
