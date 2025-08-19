import type { Post } from "@/app/blog/_types";

export function getTagsAndCountsFromPosts(posts: Post[]): [string[], Record<string, number>] {
  const allTags = posts
    .filter((post) => post.tags)
    .map(({ tags: postTags }) => postTags)
    .filter(Boolean)
    .flat();

  const tagCounts = allTags.reduce<Record<string, number>>((tagObj, { tag }) => {
    if (tag in tagObj) {
      tagObj[tag]!++;
    } else {
      tagObj[tag] = 1;
    }

    return tagObj;
  }, {});

  const tags = Object.keys(tagCounts || {}).sort((a, b) => tagCounts[b]! - tagCounts[a]!);

  return [tags, tagCounts] as const;
}
