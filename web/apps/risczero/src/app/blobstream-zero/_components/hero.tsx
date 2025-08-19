import { Title } from "@/app/_components/title";
import { BoxReveal } from "@/components/box-reveal";
import { Button } from "@risc0/ui/button";
import { ArrowUpRightIcon } from "lucide-react";
import Image from "next/image";

export function Hero() {
  return (
    <section id="hero" className="container flex min-h-[56dvh] max-w-screen-2xl items-center justify-between">
      <div className="size-full max-w-[38rem] items-center justify-center overflow-hidden pt-8">
        <BoxReveal duration={0.3} theme="blobstream">
          <Title as="h1" className="mb-0 py-3 md:text-7xl">
            The Future of <span className="text-blobstream-light dark:text-blobstream-dark">Cross-chain</span> Data
            Availability
          </Title>
        </BoxReveal>

        <BoxReveal duration={0.3} theme="blobstream">
          <p className="text-2xl">Prove and verify Celestia DA on any chain with Blobstream Zero.</p>
        </BoxReveal>

        <div className="mt-10">
          <BoxReveal duration={0.3} theme="blobstream">
            <Button
              size="lg"
              endIcon={<ArrowUpRightIcon />}
              className="bg-blobstream-light text-default-light dark:bg-blobstream-dark"
            >
              Documentation
            </Button>
          </BoxReveal>
        </div>
      </div>

      <Image
        src="/solutions/blobstream-zero.png"
        unoptimized
        priority
        width={409}
        draggable={false}
        height={555}
        alt="Blobstream Zero ASCII Art"
        className="max-h-[555px] animate-fade-in-left rounded-3xl object-contain object-center duration-300"
      />
    </section>
  );
}
