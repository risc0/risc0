import type { Post } from "@/app/blog/_types";
import { unstable_cache } from "next/cache";
import { fetchNotionData } from "./fetch-notion-data";

const PAGE_ID = "a16a202acb3645f4b0d9a4ec9a0ec95f";

function processPosts(posts: Post[]): Post[] {
  return posts
    .map((notionPost) => {
      const { start_date } = notionPost.date ?? {};
      const postDate = start_date ? new Date(`${start_date}T00:00:00Z`).getTime() : Date.now();

      return { ...notionPost, postDate };
    })
    .sort((a, b) => {
      if (b.postDate !== a.postDate) {
        return b.postDate - a.postDate;
      }

      return (b.title ?? "").localeCompare(a.title ?? "");
    });
}

async function fetchAndProcessPosts(): Promise<Post[] | null> {
  try {
    const posts = await fetchNotionData<Post>(PAGE_ID);

    return posts ? processPosts(posts) : null;
  } catch (error) {
    console.error("Error fetching posts:", error);
    return null;
  }
}

export const getAllPosts = unstable_cache(
  async (): Promise<Post[] | null> => {
    return await fetchAndProcessPosts();
  },
  ["all-posts"],
  { tags: ["all-posts"] },
);
