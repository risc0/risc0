import "./src/env";

import { nextConfigBase } from "@risc0/ui/config/next.config.base.js";
import deepmerge from "deepmerge";
import type { NextConfig } from "next";

const config: NextConfig = deepmerge(nextConfigBase, {
  experimental: {
    reactCompiler: true,
    ppr: false, // dont enable ppr, it sucks
  },

  images: {
    remotePatterns: [
      { hostname: "www.notion.so" },
      { hostname: "lh3.googleusercontent.com" },
      { hostname: "s3-us-west-2.amazonaws.com" },
      { hostname: "avatars.githubusercontent.com" },
      { hostname: "avatar.vercel.sh" },
    ],
  },

  async redirects() {
    return [
      {
        source: "/tos",
        destination: "/terms-of-service",
        permanent: true,
      },
      {
        source: "/zkvm",
        destination: "/",
        permanent: true,
      },
      {
        source: "/team",
        destination: "/our-story",
        permanent: true,
      },
      {
        source: "/blog/ethdenver",
        destination: "/blog/ethdenver-2024-recap",
        permanent: true,
      },
      {
        source: "/get-started",
        destination: "/",
        permanent: true,
      },
      {
        source: "/use-cases-demos",
        destination: "/",
        permanent: true,
      },
      {
        source: "/policy",
        destination: "/privacy-policy",
        permanent: true,
      },
      {
        source: "/news/:path*",
        destination: "/blog/:path*",
        permanent: true,
      },

      // CSV-based redirects from old webflow site
      {
        source: "/docs/(.*)",
        destination: "https://dev.risczero.com",
        permanent: true,
      },
      {
        source: "/docs",
        destination: "https://dev.risczero.com",
        permanent: true,
      },
      {
        source: "/mailing",
        destination: "/",
        permanent: true,
      },
      {
        source: "/proof-system-in-detail.pdf",
        destination: "https://dev.risczero.com/proof-system-in-detail.pdf",
        permanent: true,
      },
      {
        source: "/technology---zkvm",
        destination: "/",
        permanent: true,
      },
      {
        source: "/technology---bonsai",
        destination: "/bonsai",
        permanent: true,
      },
      {
        source: "/blog/risc-zero-take-the-rekt-test",
        destination: "/blog/risc-zero-takes-the-rekt-test",
        permanent: true,
      },
      {
        source: "/technology-zkvm",
        destination: "/",
        permanent: true,
      },
      {
        source: "/technology-bonsai",
        destination: "/bonsai",
        permanent: true,
      },
      {
        source: "/install",
        destination: "https://risc0-artifacts.s3.us-west-2.amazonaws.com/rzup/prod/install",
        permanent: true,
      },
    ];
  },
});

export default config;
