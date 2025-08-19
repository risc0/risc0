import "./src/env";

import { nextConfigBase } from "@risc0/ui/config/next.config.base.js";
import deepmerge from "deepmerge";
import type { NextConfig } from "next";
import { latestVersion } from "./src/versions.js";

const config: NextConfig = deepmerge(nextConfigBase, {
	experimental: {
		ppr: false, // DO NOT USE PPR, breaks everything, don't bother with it
	},

	eslint: {
		ignoreDuringBuilds: true,
	},

	typescript: {
		ignoreBuildErrors: true,
	},

	async redirects() {
		const response = await fetch(
			"https://risc0.github.io/ghpages/dev/bench/data.js",
		);
		const text = await response.text();
		const data = JSON.parse(
			text.replace("window.BENCHMARK_DATA = ", "").trim(),
		);
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

export default config;
