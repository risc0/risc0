await import("./src/env.js");

/** @type {import("next").NextConfig} */
const config = {
  eslint: {
    ignoreDuringBuilds: true,
  },
  experimental: {
    ppr: true,
  },
  transpilePackages: ["@risc0/ui"],

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

export default config;
