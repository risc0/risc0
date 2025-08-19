import type { Metadata } from "next";
import { NotionRenderer } from "@/components/notion/notion-renderer";
import { getPage } from "@/libs/notion/api";
import { OG_BASE } from "../_constants/og";

const TITLE = "Terms of Service";

export const metadata: Metadata = {
  title: "Terms of Service",
  openGraph: {
    ...OG_BASE,
    title: TITLE,
    url: "https://risczero.com/terms-of-service",
    images: [
      {
        url: `https://risczero.com/api/og?title=${TITLE}`,
      },
    ],
  },
  twitter: {
    card: "summary_large_image",
    title: TITLE,
    images: [
      {
        url: `https://risczero.com/api/og?title=${TITLE}`,
      },
    ],
  },
  alternates: {
    canonical: "/terms-of-service",
  },
};

export default async function TermsOfServicePage() {
  const blockMap = await getPage("b5da674176704f1781fa1a272562269e");

  if (!blockMap) {
    return <div>There was an issue fetching this blog post, please try again later.</div>;
  }

  return <NotionRenderer recordMap={blockMap} fullPage={false} />;
}
