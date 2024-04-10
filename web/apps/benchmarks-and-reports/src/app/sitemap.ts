export const baseUrl = "https://risczero-reports.vercel.app";

export default async function sitemap() {
  const routes = ["", "/applications-benchmarks", "/benchmarks", "/crates-validation", "/datasheet"].map((route) => ({
    url: `${baseUrl}${route}`,
    lastModified: new Date().toISOString().split("T")[0],
  }));

  return [...routes];
}
