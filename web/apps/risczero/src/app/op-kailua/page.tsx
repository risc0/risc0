import type { Metadata } from "next";
import { PartnerWithUs } from "../_components/partner-with-us";
import { OG_BASE } from "../_constants/og";
import { Hero } from "./_components/hero";
import { SecurityMode } from "./_components/security-mode";
import { UpgradeAtYourOwnPace } from "./_components/upgrade-at-your-own-pace";

const TITLE = "OP Kailua";
const DESCRIPTION =
  "Future-proof your OP Chain with ZK. Choose between ZK Fraud or Validity Proofs for faster finality and stronger security.";

export const metadata: Metadata = {
  title: TITLE,
  description: DESCRIPTION,
  openGraph: {
    ...OG_BASE,
    title: TITLE,
    description: DESCRIPTION,
    url: "https://risczero.com/op-kailua",
    images: [
      {
        url: `https://risczero.com/api/og?kailua=1&title=${TITLE}&description=${DESCRIPTION}`,
      },
    ],
  },
  twitter: {
    card: "summary_large_image",
    title: TITLE,
    description: DESCRIPTION,
    images: [
      {
        url: `https://risczero.com/api/og?kailua=1&title=${TITLE}&description=${DESCRIPTION}`,
      },
    ],
  },
  alternates: {
    canonical: "/op-kailua",
  },
};

export default function OPKailuaPage() {
  return (
    <main>
      <Hero />

      <SecurityMode />

      <div className="mt-36 mb-80">
        <PartnerWithUs
          ctaLabel="Get in Touch"
          subtitle=""
          ctaLink="https://docs.google.com/forms/d/e/1FAIpQLScH3mRdi8pCeaunup7vtX7Ack9AaMUKY54TD3y8aj131WgK1g/viewform"
          title="Let Us Help You Pick the Right Option"
          theme="op-kailua"
        />
      </div>

      <UpgradeAtYourOwnPace />
    </main>
  );
}
