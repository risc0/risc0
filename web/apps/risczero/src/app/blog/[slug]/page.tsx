import { OG_BASE } from "@/app/_constants/og";
import { getUsers } from "@/libs/notion/api";
import { getAllPosts } from "@/libs/notion/get-all-posts";
import type { Metadata } from "next";
import { Suspense } from "react";
import { PostPageContent } from "./_components/page-content";
import { PostPageSkeleton } from "./_components/page-skeleton";

type Params = {
  params: Promise<{
    slug: string;
  }>;
  searchParams?: Promise<{
    from: string;
  }>;
};

export async function generateStaticParams() {
  const posts = await getAllPosts();

  if (!posts) {
    return [];
  }

  return posts.map((post) => ({ slug: post.slug ?? "" }));
}

export async function generateMetadata(props: Params): Promise<Metadata> {
  const params = await props.params;
  const posts = await getAllPosts();
  const slug = decodeURIComponent(params.slug);

  if (!posts) {
    return {};
  }

  const post = posts.find((p) => p.slug === slug);

  if (!post || !post.id) {
    return {};
  }

  const { results: authors } = await getUsers(post.author ?? []);
  const path = `/blog/${slug}`;
  const tags = post.tags.slice(0, 10).map(({ tag }) => tag);
  const joinedAuthors = (authors as any[]).map(({ value }) => value.name).join(" & ");

  return {
    title: post.title,
    description: post.summary,
    alternates: {
      canonical: path,
    },
    openGraph: {
      ...OG_BASE,
      title: post.title,
      description: post.summary,
      url: `https://risczero.com${path}`,
      type: "article",
      publishedTime: new Date(post.postDate).toISOString(),
      modifiedTime: new Date(post.postDate).toISOString(),
      authors: joinedAuthors,
      images: [
        {
          url: post.pageCover,
        },
      ],
    },
    twitter: {
      card: "summary_large_image",
      title: post.title,
      description: post.summary,
      images: [
        {
          url: post.pageCover,
        },
      ],
    },
    keywords: tags,
    authors: { name: joinedAuthors },
  };
}

export default async function PostPage(props: Params) {
  const searchParams = await props.searchParams;
  const params = await props.params;

  return (
    <Suspense fallback={<PostPageSkeleton />}>
      <PostPageContent params={params} fromTagSlug={searchParams?.from} />
    </Suspense>
  );
}
