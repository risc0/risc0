import { Button } from "@risc0/ui/button";
import { ArrowUpRightIcon } from "lucide-react";
import Link from "next/link";
import { Subtitle } from "@/app/_components/subtitle";
import { BoxReveal } from "@/components/box-reveal";

export function Hero() {
  return (
    <section id="hero" className="container mb-12 flex min-h-[56dvh] max-w-screen-2xl items-center">
      <div className="mx-auto size-full max-w-[38rem] items-center justify-center overflow-hidden pt-8 md:ml-0">
        <BoxReveal duration={0.3}>
          <h1 className="bg-gradient-to-b from-black to-gray-800/80 bg-clip-text py-6 text-center font-bold text-6xl text-transparent leading-[3.5rem] md:text-left md:text-7xl md:leading-[4rem] lg:text-8xl lg:leading-[5rem] dark:from-white dark:to-neutral-100/80 md:[word-spacing:1rem]">
            Universal Zero Knowledge
          </h1>
        </BoxReveal>

        <BoxReveal duration={0.3}>
          <Subtitle className="text-center text-2xl md:text-left lg:text-3xl">
            Unlock the full potential of ZK on every chain. High-performance, cost-effective, and powered by the leading
            open-source zkVM.
          </Subtitle>
        </BoxReveal>

        <div className="mt-10 flex justify-center md:justify-start">
          <BoxReveal duration={0.3}>
            <div className="flex flex-col items-center gap-4 sm:flex-row">
              <Link
                tabIndex={-1}
                href="https://share.hsforms.com/1y4akhGomTBet6MkD9mcdSgq7xur"
                className="min-w-[300px] sm:min-w-0"
              >
                <Button size="lg" className="w-full">
                  Partner with Us
                </Button>
              </Link>
              <Link tabIndex={-1} href="https://dev.risczero.com" target="_blank" className="min-w-[300px] sm:min-w-0">
                <Button size="lg" variant="secondary" className="w-full" endIcon={<ArrowUpRightIcon />}>
                  Start Building
                </Button>
              </Link>
            </div>
          </BoxReveal>
        </div>
      </div>
    </section>
  );
}
