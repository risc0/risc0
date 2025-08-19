import type { MetadataRoute } from "next";
import { getAllPosts } from "@/libs/notion/get-all-posts";

export default async function sitemap(): Promise<MetadataRoute.Sitemap> {
  const posts = await getAllPosts();

  if (!posts) {
    return [];
  }

  const latest = Math.max(...posts.map((post) => post.postDate));

  const blogFields: MetadataRoute.Sitemap = posts.map((post) => ({
    url: `https://risczero.com/blog/${post.slug}`,
    lastModified: new Date(post.postDate).toISOString(),
    changeFrequency: "weekly",
    priority: 0.7,
  }));

  const blogHome: MetadataRoute.Sitemap[number] = {
    url: "https://risczero.com/blog",
    lastModified: new Date(latest).toISOString(),
    changeFrequency: "weekly",
    priority: 1,
  };

  return [
    {
      url: "https://risczero.com/",
      lastModified: new Date(latest).toISOString(),
      changeFrequency: "weekly",
      priority: 1,
    },
    {
      url: "https://risczero.com/bonsai",
      lastModified: new Date(latest).toISOString(),
      changeFrequency: "weekly",
      priority: 1,
    },
    {
      url: "https://risczero.com/steel",
      lastModified: new Date(latest).toISOString(),
      changeFrequency: "weekly",
      priority: 1,
    },
    {
      url: "https://risczero.com/zeth",
      lastModified: new Date(latest).toISOString(),
      changeFrequency: "weekly",
      priority: 1,
    },
    {
      url: "https://risczero.com/our-story",
      lastModified: new Date(latest).toISOString(),
      changeFrequency: "weekly",
      priority: 0.8,
    },
    {
      url: "https://risczero.com/ecosystem",
      lastModified: new Date(latest).toISOString(),
      changeFrequency: "weekly",
      priority: 0.8,
    },
    {
      url: "https://risczero.com/privacy-policy",
      lastModified: new Date(latest).toISOString(),
      changeFrequency: "weekly",
      priority: 0.3,
    },
    {
      url: "https://risczero.com/terms-of-service",
      lastModified: new Date(latest).toISOString(),
      changeFrequency: "weekly",
      priority: 0.3,
    },
    {
      url: "https://risczero.com/blog/tag/Developer",
      lastModified: new Date(latest).toISOString(),
      changeFrequency: "weekly",
      priority: 0.5,
    },
    {
      url: "https://risczero.com/blog/tag/Announcement",
      lastModified: new Date(latest).toISOString(),
      changeFrequency: "weekly",
      priority: 0.5,
    },
    {
      url: "https://risczero.com/blog/tag/General",
      lastModified: new Date(latest).toISOString(),
      changeFrequency: "weekly",
      priority: 0.5,
    },
    blogHome,
    ...blogFields,
  ];
}
