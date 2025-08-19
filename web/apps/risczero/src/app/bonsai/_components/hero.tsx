import { Title } from "@/app/_components/title";
import { BoxReveal } from "@/components/box-reveal";
import { Button } from "@risc0/ui/button";
import { ArrowUpRightIcon } from "lucide-react";
import Link from "next/link";
import { Bonsai3dCard } from "./bonsai-3d-card";

export function Hero() {
  return (
    <section
      id="hero"
      className="container flex min-h-[56dvh] max-w-screen-2xl flex-col items-center justify-between gap-x-24 gap-y-12 md:flex-row"
    >
      <div className="size-full max-w-[38rem] items-center justify-center overflow-hidden pt-8">
        <BoxReveal duration={0.3} theme="bonsai">
          <Title as="h1" className="mb-0 py-3 text-5xl md:text-7xl">
            Proof Generation at <span className="font-black text-bonsai-light dark:text-bonsai-dark">Scale</span>
          </Title>
        </BoxReveal>

        <BoxReveal duration={0.3} theme="bonsai">
          <p className="text-2xl">
            Unlock enterprise-grade performance with Bonsai, the world's fastest proving service.
          </p>
        </BoxReveal>

        <div className="mt-10">
          <BoxReveal duration={0.3} theme="bonsai">
            <div className="flex flex-col gap-4 md:flex-row">
              <Link
                tabIndex={-1}
                href="https://docs.google.com/forms/d/e/1FAIpQLSf9mu18V65862GS4PLYd7tFTEKrl90J5GTyzw_d14ASxrruFQ/viewform"
                target="_blank"
              >
                <Button
                  size="lg"
                  className="bg-bonsai-light text-default-dark dark:bg-bonsai-dark dark:text-default-light"
                >
                  Request API Key
                </Button>
              </Link>
              <Link tabIndex={-1} href="https://dev.risczero.com/api/generating-proofs/remote-proving" target="_blank">
                <Button size="lg" variant="secondary" endIcon={<ArrowUpRightIcon />}>
                  Learn More
                </Button>
              </Link>
            </div>
          </BoxReveal>
        </div>
      </div>

      <div className="animate-fade-in-left duration-300">
        <Bonsai3dCard />
      </div>
    </section>
  );
}
