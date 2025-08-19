import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";
import { OG_BASE } from "@/app/_constants/og";
import { getAllPosts } from "@/libs/notion/get-all-posts";
import { getTagsAndCountsFromPosts } from "@/libs/notion/get-all-tags-from-post";
import type { Metadata } from "next";
import { Suspense } from "react";
import { BlogPageContent } from "../../_components/page-content";
import { BlogPageSkeleton } from "../../_components/page-skeleton";
import { BLOG_DESCRIPTION } from "../../page";

export async function generateMetadata(props: { params: Promise<{ slug: string }> }): Promise<Metadata> {
  const params = await props.params;
  const slug = decodeURIComponent(params.slug);
  const path = `/blog/tag/${slug}`;
  const title = `${slug} Blog Articles`;

  return {
    title,
    description: BLOG_DESCRIPTION,
    alternates: {
      canonical: path,
    },
    openGraph: {
      ...OG_BASE,
      title,
      description: BLOG_DESCRIPTION,
      url: `https://risczero.com${path}`,
      images: [
        {
          url: `https://risczero.com/api/og?title=${title}&description=${BLOG_DESCRIPTION}`,
        },
      ],
    },
    twitter: {
      card: "summary_large_image",
      title,
      description: BLOG_DESCRIPTION,
      images: [
        {
          url: `https://risczero.com/api/og?title=${title}&description=${BLOG_DESCRIPTION}`,
        },
      ],
    },
  };
}

export async function generateStaticParams(): Promise<{ slug: string }[]> {
  const posts = await getAllPosts();

  if (!posts) {
    return [];
  }

  const [tags] = getTagsAndCountsFromPosts(posts);

  return tags.map((tag) => ({ slug: encodeURIComponent(tag) }));
}

export default async function BlogPage(props: { params: Promise<{ slug: string }> }) {
  const params = await props.params;
  return (
    <>
      <div className="flex flex-col gap-6 py-6 md:py-12">
        <Title as="h1" className="mb-0 text-center md:text-left">
          RISC Zero Blog{" "}
          {params.slug ? (
            <span className="inline-block animate-fade-in-left font-normal text-2xl text-muted-foreground">
              &nbsp;&nbsp;{params.slug}
            </span>
          ) : (
            ""
          )}
        </Title>
        <Subtitle className="text-center md:text-left">
          Learn about RISC Zero's technology, research, and latest developments.
        </Subtitle>
      </div>

      <Suspense fallback={<BlogPageSkeleton />}>
        <BlogPageContent slug={params.slug} />
      </Suspense>
    </>
  );
}
