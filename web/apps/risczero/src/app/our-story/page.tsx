import { Button } from "@risc0/ui/button";
import { ArrowUpRightIcon } from "lucide-react";
import type { Metadata } from "next";
import Link from "next/link";
import { Suspense } from "react";
import { Subtitle } from "../_components/subtitle";
import { Title } from "../_components/title";
import { OG_BASE } from "../_constants/og";
import { Leadership } from "./_components/leadership";
import { TeamMembersPreviouslyAt } from "./_components/team-members-previously-at";
import { WhatMakesUs } from "./_components/what-makes-us";

const TITLE = "Our Story";
const DESCRIPTION = "Founded in 2021 to revolutionize Web3.";

export const metadata: Metadata = {
  title: TITLE,
  description: DESCRIPTION,
  openGraph: {
    ...OG_BASE,
    title: TITLE,
    description: DESCRIPTION,
    url: "https://risczero.com/our-story",
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
    canonical: "/our-story",
  },
};

export default function OurStoryPage() {
  return (
    <main className="container mx-auto max-w-screen-2xl">
      <div className="flex flex-col items-center justify-between gap-8 pt-12 md:flex-row md:pt-24">
        <div className="flex flex-col gap-6">
          <Title as="h1" className="mb-0 text-center md:text-left">
            Our Story
          </Title>
          <Subtitle className="text-center md:text-left">Founded in 2021 to revolutionize Web3.</Subtitle>
        </div>

        <Link target="_blank" tabIndex={-1} href="https://jobs.ashbyhq.com/RiscZero">
          <Button autoFocus size="lg" endIcon={<ArrowUpRightIcon />}>
            See Open Roles
          </Button>
        </Link>
      </div>

      <WhatMakesUs />

      <TeamMembersPreviouslyAt />

      <Suspense>
        <Leadership />
      </Suspense>
    </main>
  );
}
