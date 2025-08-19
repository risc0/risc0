import { NotionRenderer } from "@/components/notion/notion-renderer";
import { getPage } from "@/libs/notion/api";
import type { Metadata } from "next";
import { OG_BASE } from "../_constants/og";

const TITLE = "Privacy Policy";

export const metadata: Metadata = {
  title: "Terms of Service",
  openGraph: {
    ...OG_BASE,
    title: TITLE,
    url: "https://risczero.com/privacy-policy",
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
    canonical: "/privacy-policy",
  },
};

export default async function PrivacyPolicyPage() {
  const blockMap = await getPage("c2968429ff714774958ff9ee9783def6");

  if (!blockMap) {
    return <div>There was an issue fetching this blog post, please try again later.</div>;
  }

  return <NotionRenderer recordMap={blockMap} fullPage={false} />;
}
