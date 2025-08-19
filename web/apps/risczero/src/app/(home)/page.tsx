import type { Metadata } from "next";
import { Suspense } from "react";
import { Particles } from "@/components/particles";
import { Advantages } from "./_components/advantages";
import { BuiltForEveryUseCase } from "./_components/built-for-every-use-case";
import { Hero } from "./_components/hero";
import { Investors } from "./_components/investors";
import { OurNumbers } from "./_components/our-numbers";
import { Partners } from "./_components/partners";
import { RecentNews } from "./_components/recent-news";
import { ZeroKnowledgeRequired } from "./_components/zero-knowledge-required";

export const metadata: Metadata = {
  title: "Universal Zero Knowledge",
  alternates: {
    canonical: "/",
  },
};

export default function HomePage() {
  return (
    <main className="-mt-28 relative bg-[length:640px_640px] bg-[position:calc(100%_+_284px)_32px] bg-no-repeat pt-28 md:bg-[url('/misc/planet.webp')] lg:bg-[length:900px_900px] lg:bg-[position:calc(100%_+_184px)_-16px] md:dark:bg-[url('/misc/planet-dark.webp')]">
      <div className="relative">
        <Particles className="-z-0 fade-bottom absolute inset-0 opacity-0 dark:opacity-80" quantity={320} ease={100} />

        <Hero />

        <Partners />
      </div>

      <ZeroKnowledgeRequired />

      <Advantages />

      <OurNumbers />

      <Investors />

      <BuiltForEveryUseCase />

      <Suspense>
        <RecentNews />
      </Suspense>
    </main>
  );
}
