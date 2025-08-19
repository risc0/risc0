import { Button } from "@risc0/ui/button";
import Link from "next/link";
import { Title } from "@/app/_components/title";
import { BoxReveal } from "@/components/box-reveal";
import { Zeth3dCard } from "./zeth-3d-card";

export function Hero() {
  return (
    <section
      id="hero"
      className="container flex min-h-[56dvh] max-w-screen-2xl flex-col items-center justify-between gap-x-24 gap-y-12 md:flex-row"
    >
      <div className="size-full max-w-[38rem] items-center justify-center overflow-hidden pt-8">
        <BoxReveal duration={0.3} theme="zeth">
          <Title as="h1" className="mb-0 py-3 text-5xl md:text-7xl">
            The First <span className="font-black text-zeth-light dark:text-zeth-dark">Type Zero</span> zkEVM
          </Title>
        </BoxReveal>

        <BoxReveal duration={0.3} theme="zeth">
          <p className="text-2xl">Meet Zeth, the Ethereum-equivalent, maintainable, fully open-source zkEVM.</p>
        </BoxReveal>

        <div className="mt-10">
          <BoxReveal duration={0.3} theme="zeth">
            <Link href="https://www.risczero.com/blog/zeth-release" tabIndex={-1}>
              <Button size="lg" className="bg-zeth-light text-default-dark dark:bg-zeth-dark dark:text-default-light">
                Learn More
              </Button>
            </Link>
          </BoxReveal>
        </div>
      </div>

      <div className="animate-fade-in-left duration-300">
        <Zeth3dCard />
      </div>
    </section>
  );
}
