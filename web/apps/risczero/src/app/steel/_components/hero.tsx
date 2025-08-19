import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";
import { BoxReveal } from "@/components/box-reveal";
import { Button } from "@risc0/ui/button";
import Link from "next/link";
import { Steel3dCard } from "./steel-3d-card";

export function Hero() {
  return (
    <section
      id="hero"
      className="container flex min-h-[56dvh] max-w-screen-2xl flex-col items-center justify-between gap-x-24 gap-y-12 md:flex-row"
    >
      <div className="size-full max-w-[38rem] items-center justify-center overflow-hidden pt-8">
        <BoxReveal duration={0.3} theme="steel">
          <Title as="h1" className="mb-0 py-3 text-5xl md:text-7xl">
            <span className="font-black text-steel-light dark:text-steel-dark">Supercharge</span> your EVM Development
          </Title>
        </BoxReveal>

        <BoxReveal duration={0.3} theme="steel">
          <Subtitle>Compute over all EVM state in your smart contract. Fast, trustless, and cost-effective.</Subtitle>
        </BoxReveal>

        <div className="mt-10">
          <BoxReveal duration={0.3} theme="steel">
            <Link target="_blank" href="https://github.com/risc0/risc0-ethereum/tree/main/crates/steel" tabIndex={-1}>
              <Button size="lg" className="bg-steel-light text-default-dark dark:bg-steel-dark dark:text-default-light">
                Start Building
              </Button>
            </Link>
          </BoxReveal>
        </div>
      </div>

      <div className="animate-fade-in-left duration-300">
        <Steel3dCard />
      </div>
    </section>
  );
}
