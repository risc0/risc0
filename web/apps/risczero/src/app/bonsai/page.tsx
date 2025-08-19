import type { Metadata } from "next";
import { PartnerWithUs } from "../_components/partner-with-us";
import { OG_BASE } from "../_constants/og";
import { EffortlessScaling } from "./_components/effortless-scaling";
import { Hero } from "./_components/hero";

const TITLE = "Bonsai";
const DESCRIPTION = "Unlock enterprise-grade performance with Bonsai, the world's fastest proving service.";

export const metadata: Metadata = {
  title: TITLE,
  description: DESCRIPTION,
  openGraph: {
    ...OG_BASE,
    title: TITLE,
    description: DESCRIPTION,
    url: "https://risczero.com/bonsai",
    images: [
      {
        url: `https://risczero.com/api/og?bonsai=1&title=${TITLE}&description=${DESCRIPTION}`,
      },
    ],
  },
  twitter: {
    card: "summary_large_image",
    title: TITLE,
    description: DESCRIPTION,
    images: [
      {
        url: `https://risczero.com/api/ogbonsai=1&title=${TITLE}&description=${DESCRIPTION}`,
      },
    ],
  },
  alternates: {
    canonical: "/bonsai",
  },
};

export default function BonsaiPage() {
  return (
    <main>
      <Hero />

      <EffortlessScaling />

      <PartnerWithUs theme="bonsai" />
    </main>
  );
}
