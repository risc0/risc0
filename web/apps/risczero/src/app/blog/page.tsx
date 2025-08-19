import type { Metadata } from "next";
import { Suspense } from "react";
import { Subtitle } from "../_components/subtitle";
import { Title } from "../_components/title";
import { OG_BASE } from "../_constants/og";
import { BlogPageContent } from "./_components/page-content";
import { BlogPageSkeleton } from "./_components/page-skeleton";

const TITLE = "Blog";
const BLOG_DESCRIPTION = "Learn about RISC Zero's technology, research, and latest developments.";

export const metadata: Metadata = {
  title: TITLE,
  description: BLOG_DESCRIPTION,
  openGraph: {
    ...OG_BASE,
    title: TITLE,
    description: BLOG_DESCRIPTION,
    url: "https://risczero.com/blog",
    images: [
      {
        url: `https://risczero.com/api/og?title=${TITLE}&description=${BLOG_DESCRIPTION}`,
      },
    ],
  },
  twitter: {
    card: "summary_large_image",
    title: TITLE,
    description: BLOG_DESCRIPTION,
    images: [
      {
        url: `https://risczero.com/api/og?title=${TITLE}&description=${BLOG_DESCRIPTION}`,
      },
    ],
  },
  alternates: {
    canonical: "/blog",
  },
};

export default function BlogPage() {
  return (
    <>
      <div className="flex flex-col gap-6 py-6 md:py-12">
        <Title as="h1" className="mb-0 text-center md:text-left">
          RISC Zero Blog
        </Title>
        <Subtitle className="text-center md:text-left">
          Learn about RISC Zero's technology, research, and latest developments.
        </Subtitle>
      </div>

      <Suspense fallback={<BlogPageSkeleton />}>
        <BlogPageContent />
      </Suspense>
    </>
  );
}

export { BLOG_DESCRIPTION };
