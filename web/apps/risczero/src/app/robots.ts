import type { MetadataRoute } from "next";

export default function robots(): MetadataRoute.Robots {
  return {
    rules: {
      userAgent: "*",
      allow: "/",
      disallow: "/api/og",
    },
    host: "https://risczero.com",
    sitemap: "https://risczero.com/sitemap.xml",
  };
}
