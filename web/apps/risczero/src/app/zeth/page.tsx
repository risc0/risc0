import type { Metadata } from "next";
import { PartnerWithUs } from "../_components/partner-with-us";
import { OG_BASE } from "../_constants/og";
import { CostPerTxn } from "./_components/cost-per-txn";
import { Hero } from "./_components/hero";

const TITLE = "Zeth";
const DESCRIPTION = "Meet Zeth, the Ethereum-equivalent, maintainable, fully open-source zkEVM.";

export const metadata: Metadata = {
  title: TITLE,
  description: DESCRIPTION,
  openGraph: {
    ...OG_BASE,
    title: TITLE,
    description: DESCRIPTION,
    url: "https://risczero.com/zeth",
    images: [
      {
        url: `https://risczero.com/api/og?zeth=1&title=${TITLE}&description=${DESCRIPTION}`,
      },
    ],
  },
  twitter: {
    card: "summary_large_image",
    title: TITLE,
    description: DESCRIPTION,
    images: [
      {
        url: `https://risczero.com/api/og?zeth=1&title=${TITLE}&description=${DESCRIPTION}`,
      },
    ],
  },
  alternates: {
    canonical: "/zeth",
  },
};

export default function ZethPage() {
  return (
    <main>
      <Hero />

      <CostPerTxn />

      <PartnerWithUs theme="zeth" />
    </main>
  );
}
