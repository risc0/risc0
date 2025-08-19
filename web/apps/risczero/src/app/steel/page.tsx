import type { Metadata } from "next";
import { PartnerWithUs } from "../_components/partner-with-us";
import { OG_BASE } from "../_constants/og";
import { Hero } from "./_components/hero";
import { KeyPoints } from "./_components/key-points";
import { Toolkit } from "./_components/toolkit";

const TITLE = "Steel";
const DESCRIPTION = "Compute over all EVM state in your smart contract. Fast, trustless, and cost-effective.";

export const metadata: Metadata = {
  title: TITLE,
  description: DESCRIPTION,
  openGraph: {
    ...OG_BASE,
    title: TITLE,
    description: DESCRIPTION,
    url: "https://risczero.com/steel",
    images: [
      {
        url: `https://risczero.com/api/og?steel=1&title=${TITLE}&description=${DESCRIPTION}`,
      },
    ],
  },
  twitter: {
    card: "summary_large_image",
    title: TITLE,
    description: DESCRIPTION,
    images: [
      {
        url: `https://risczero.com/api/og?steel=1&title=${TITLE}&description=${DESCRIPTION}`,
      },
    ],
  },
  alternates: {
    canonical: "/steel",
  },
};

export default function SteelPage() {
  return (
    <main>
      <Hero />

      <KeyPoints />

      <Toolkit />

      <PartnerWithUs theme="steel" />
    </main>
  );
}
