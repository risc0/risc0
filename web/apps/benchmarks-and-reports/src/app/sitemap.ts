export const baseUrl = "https://benchmarks.risczero.com";

export default async function sitemap() {
  const routes = [
    "/benchmarks",
    "/crates-validation",
    "/main",
    "/main/applications-benchmarks",
    "/main/datasheet",
    "/release-0.21",
    "/release-0.21/applications-benchmarks",
    "/release-0.21/datasheet",
  ].map((route) => ({
    url: `${baseUrl}${route}`,
    lastModified: new Date().toISOString().split("T")[0],
  }));

  return [...routes];
}
