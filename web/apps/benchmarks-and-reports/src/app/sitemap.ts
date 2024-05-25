import { VERSIONS } from "~/versions";

export const baseUrl = "https://benchmarks.risczero.com";

// @TODO: add individual tabs for app benchmarks?
export default async function sitemap() {
  const routes = [
    "/benchmarks",
    "/crates-validation",
    ...VERSIONS.flatMap(({ value }) => [`/${value}`, `/${value}/applications-benchmarks`, `/${value}/datasheet`]),
  ].map((route) => ({
    url: `${baseUrl}${route}`,
    lastModified: new Date().toISOString().split("T")[0],
  }));

  return [...routes];
}
