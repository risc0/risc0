import { PostListItem } from "@/app/blog/_components/post-list-item";
import { getAllPosts } from "@/libs/notion/get-all-posts";
import { getTagsAndCountsFromPosts } from "@/libs/notion/get-all-tags-from-post";
import { TagsCloud } from "./tags-cloud";

export async function BlogPageContent({ slug }: { slug?: string }) {
  const posts = await getAllPosts();

  if (!posts) {
    console.error("No posts found, revalidating path & tag");
    return null;
  }

  const currentTag = slug ? decodeURIComponent(slug) : undefined;
  const [tags, tagCounts] = getTagsAndCountsFromPosts(posts);
  const filteredPosts = currentTag ? posts.filter((post) => post.tags.some(({ tag }) => tag === currentTag)) : posts;

  return (
    <>
      <TagsCloud tags={tags} tagCounts={tagCounts} posts={posts} currentTag={currentTag} />

      <div className="mt-12 flex flex-col gap-10 md:gap-20">
        {filteredPosts.map((filteredPost, id) => (
          <PostListItem key={filteredPost.id} id={id} post={filteredPost} fromTagSlug={slug} />
        ))}
      </div>
    </>
  );
}
