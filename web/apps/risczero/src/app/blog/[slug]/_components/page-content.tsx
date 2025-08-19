import { notFound, redirect } from "next/navigation";
import { getPage, getUsers } from "@/libs/notion/api";
import { getAllPosts } from "@/libs/notion/get-all-posts";
import { Post } from "./post";
import { PrevNextPost } from "./prev-next-post";

type Params = {
  params: {
    slug: string;
  };
  fromTagSlug?: string;
};

export async function PostPageContent({ params, fromTagSlug }: Params) {
  const posts = await getAllPosts();
  const slug = decodeURIComponent(params.slug);

  if (!posts) {
    notFound();
  }

  const post = posts.find((post) => post.slug === slug);

  if (!post || !post.id) {
    redirect(`/blog${fromTagSlug ? `/tag/${fromTagSlug}` : ""}`);
  }

  const { results: authors } = await getUsers(post.author ?? []);
  const blockMap = await getPage(post.id);

  if (!blockMap) {
    return <div>There was an issue fetching this blog post, please try again later.</div>;
  }

  return (
    <div>
      <Post post={post} blockMap={blockMap} authors={authors} fromTagSlug={fromTagSlug} />

      <PrevNextPost posts={posts} slug={slug} />
    </div>
  );
}
