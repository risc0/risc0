import { Button } from "@risc0/ui/button";
import { ArrowUpRightIcon } from "lucide-react";
import type { Metadata } from "next";
import Link from "next/link";
import { Suspense } from "react";
import { Subtitle } from "../_components/subtitle";
import { Title } from "../_components/title";
import { OG_BASE } from "../_constants/og";
import { EcosystemPageContent } from "./_components/page-content";
import { EcosystemPageSkeleton } from "./_components/page-skeleton";

const TITLE = "Ecosystem";
const DESCRIPTION = "An overview of apps and integrations in the RISC Zero ecosystem.";

export const metadata: Metadata = {
  title: TITLE,
  description: DESCRIPTION,
  openGraph: {
    ...OG_BASE,
    title: TITLE,
    description: DESCRIPTION,
    url: "https://risczero.com/ecosystem",
    images: [
      {
        url: `https://risczero.com/api/og?title=${TITLE}&description=${DESCRIPTION}`,
      },
    ],
  },
  twitter: {
    card: "summary_large_image",
    title: TITLE,
    description: DESCRIPTION,
    images: [
      {
        url: `https://risczero.com/api/og?title=${TITLE}&description=${DESCRIPTION}`,
      },
    ],
  },
  alternates: {
    canonical: "/ecosystem",
  },
};

export default function EcosystemPage() {
  return (
    <>
      <div className="flex flex-col items-center justify-between gap-8 py-12 md:flex-row md:py-24">
        <div className="flex flex-col gap-6">
          <Title as="h1" className="mb-0 text-center md:text-left">
            RISC Zero Ecosystem
          </Title>
          <Subtitle className="text-center md:text-left">
            An overview of apps and integrations in the RISC Zero ecosystem.
          </Subtitle>
        </div>

        <Link target="_blank" tabIndex={-1} href="https://share.hsforms.com/1xU1SltHoTXOQFtyPrAIbAAq7xur">
          <Button autoFocus size="lg" endIcon={<ArrowUpRightIcon />}>
            Join the Ecosystem
          </Button>
        </Link>
      </div>

      <div className="my-12 grid grid-cols-1 gap-8 sm:grid-cols-2 md:grid-cols-3 xl:grid-cols-4">
        <Suspense fallback={<EcosystemPageSkeleton />}>
          <EcosystemPageContent />
        </Suspense>
      </div>
    </>
  );
}
