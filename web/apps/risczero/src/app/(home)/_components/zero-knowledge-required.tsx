import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";
import { DotPattern } from "@/components/dot-pattern";
import { Button } from "@risc0/ui/button";
import { ArrowUpRightIcon, SquircleIcon } from "lucide-react";
import Link from "next/link";
import { RecursionScaling } from "./recursion-scaling";
import { RecursionSpeed } from "./recursion-speed";
import { SnarkBenchmark } from "./snark-benchmark";
import { VerifyAnywhere } from "./verify-anywhere";
import { WriteRustNotCircuits } from "./write-rust-not-circuits";

export function ZeroKnowledgeRequired() {
  return (
    <section id="zero-knowledge-required" className="container max-w-screen-2xl py-12 md:py-24">
      <Title className="mb-8 text-center md:text-left">Zero-Knowledge Required</Title>

      <Subtitle className="text-center md:text-left">
        RISC Zero is democratizing zero-knowledge technology, making it accessible and scalable for developers
        everywhere.
      </Subtitle>

      <div className="md:-mb-10 mt-8 grid grid-cols-1 items-center md:mt-16 md:grid-cols-5 md:gap-12 xl:gap-48">
        <WriteRustNotCircuits />
      </div>

      <div
        id="unmatched-performance"
        className="grid grid-cols-1 items-start gap-0 pt-24 md:grid-cols-3 md:gap-48 md:pt-0"
      >
        <div className="sticky top-0 order-last col-span-1 mt-20 flex flex-col items-center justify-center md:order-first md:mt-0 md:min-h-[75dvh] md:items-start md:justify-end">
          <div className="md:-top-[25dvh] relative flex flex-col items-center justify-center md:translate-y-1/2 md:items-start md:justify-end">
            <Title as="h3" className="mb-8 text-center text-3xl md:text-left md:text-3xl">
              Unmatched Performance
            </Title>
            <Subtitle className="text-center md:text-left md:text-xl">
              Experience blazing fast proofs and reduced costs. Our zkVM makes zero-knowledge applications viable at
              scale, accelerating your development.
            </Subtitle>

            <Link
              tabIndex={-1}
              href="https://reports.risczero.com/"
              aria-label="Read more about RISC Zero's performance"
              target="_blank"
            >
              <Button
                size="lg"
                endIcon={<ArrowUpRightIcon />}
                className="mt-10 border-primary border-dashed text-primary lg:w-[290px]"
                variant="outline"
              >
                Performance Benchmarks
              </Button>
            </Link>
          </div>
        </div>

        <div className="relative col-span-2 flex flex-col gap-24 md:gap-0">
          <div id="graph-snark" className="-mx-6 top-0 flex items-end bg-background sm:mx-0 md:sticky md:min-h-[75dvh]">
            <div className="-left-10 xl:-left-24 absolute top-[42.5dvh] hidden w-full items-start gap-1 pt-12 lg:flex lg:flex-col">
              <SquircleIcon className="size-4 bg-background fill-primary text-transparent" />
              <SquircleIcon className="size-4 bg-background fill-muted-foreground text-transparent" />
              <SquircleIcon className="size-4 bg-background fill-muted-foreground text-transparent" />
            </div>
            <div className="md:-top-[25dvh] relative w-full md:translate-y-1/2">
              <SnarkBenchmark />
            </div>
          </div>

          <div
            id="graph-recursion-speed"
            className="-mx-6 top-0 flex items-end bg-background transition-opacity duration-200 sm:mx-0 md:pointer-events-none md:sticky md:min-h-[75dvh] md:opacity-0"
          >
            <div className="absolute inset-0 z-0 hidden size-full flex-col items-center justify-center dark:block">
              <DotPattern className="opacity-20 [mask-image:radial-gradient(416px_circle_at_center,white,transparent)] md:opacity-40" />
            </div>

            <div className="-left-10 xl:-left-24 absolute top-[42.5dvh] hidden w-full items-start gap-1 pt-12 lg:flex lg:flex-col">
              <SquircleIcon className="size-4 bg-background fill-muted-foreground text-transparent" />
              <SquircleIcon className="size-4 bg-background fill-primary text-transparent" />
              <SquircleIcon className="size-4 bg-background fill-muted-foreground text-transparent" />
            </div>

            <div className="md:-top-[25dvh] relative w-full md:translate-y-1/2">
              <RecursionSpeed />
            </div>
          </div>

          <div
            id="graph-recursion-scaling"
            className="-mx-6 top-0 flex items-end bg-background transition-opacity duration-200 sm:mx-0 md:pointer-events-none md:sticky md:min-h-[75dvh] md:opacity-0"
          >
            <div className="absolute inset-0 z-0 hidden size-full flex-col items-center justify-center dark:block">
              <DotPattern className="opacity-20 [mask-image:radial-gradient(416px_circle_at_center,white,transparent)] md:opacity-40" />
            </div>

            <div className="-left-10 xl:-left-24 absolute top-[42.5dvh] hidden w-full items-start gap-1 pt-12 lg:flex lg:flex-col">
              <SquircleIcon className="size-4 bg-background fill-muted-foreground text-transparent" />
              <SquircleIcon className="size-4 bg-background fill-muted-foreground text-transparent" />
              <SquircleIcon className="size-4 bg-background fill-primary text-transparent" />
            </div>

            <div className="md:-top-[25dvh] relative w-full md:translate-y-1/2">
              <RecursionScaling />
            </div>
          </div>
          <div className="sticky top-0 hidden opacity-0 md:block md:min-h-[75dvh]" />
        </div>
      </div>
      <div className="hidden first:opacity-0 md:block md:min-h-[25dvh]" />

      <div
        id="verify-anywhere"
        className="mt-24 grid grid-cols-1 items-center gap-y-12 md:mt-0 md:grid-cols-3 md:gap-x-12 xl:gap-48"
      >
        <VerifyAnywhere />
      </div>
    </section>
  );
}
