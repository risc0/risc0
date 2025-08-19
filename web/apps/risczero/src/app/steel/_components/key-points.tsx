import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";
import { Button } from "@risc0/ui/button";
import { ArrowUpRightIcon } from "lucide-react";
import Image from "next/image";
import Link from "next/link";

const KEY_POINTS = [
  {
    title: "Solidity Integration",
    icon: "/icons/link.svg",
    subtitle: "Execute Solidity contracts directly within the zkVM. No new languages or architectures to learn.",
  },
  {
    title: "Unlimited Compute",
    icon: "/icons/infinity.svg",
    subtitle:
      "Bypass EVM transaction size and block limits. Implement advanced on-chain logic previously impossible on Ethereum.",
  },
  {
    title: "Reduced Gas",
    icon: "/icons/reduced-gas.svg",
    subtitle: "Cut gas costs by up to 99%. Make resource-intensive dApps economically viable.",
  },
  {
    title: "Open-Source",
    icon: "/icons/open-source.svg",
    subtitle: "Build with confidence using 100% open-source code. Full transparency, no vendor lock-in.",
  },
] as const;

export function KeyPoints() {
  return (
    <section id="key-points" className="container max-w-screen-2xl py-12 md:py-24">
      <div className="grid grid-cols-1 gap-32 lg:grid-cols-3">
        <div className="col-span-2">
          <Title className="mb-8">Unlock the Full Potential of All EVM Chains</Title>
          <Subtitle>
            Break free from EVM constraints. Execute complex logic off-chain, verify on-chain. Build dApps that were
            previously impossible.
          </Subtitle>

          <Link tabIndex={-1} href="https://github.com/risc0/risc0-ethereum/tree/main/crates/steel" target="_blank">
            <Button
              variant="outline"
              size="lg"
              endIcon={<ArrowUpRightIcon />}
              className="mt-10 border-steel-light border-dashed text-primary dark:border-steel-dark dark:text-steel-dark"
            >
              View Documentation
            </Button>
          </Link>

          <Image
            src="/misc/code-lg.webp"
            alt="Code example"
            unoptimized
            width={792}
            draggable={false}
            height={390}
            loading="lazy"
            className="mt-24 aspect-[2797/1377] animate-fade-in-up object-contain shadow-2xl"
          />
        </div>
        <div className="col-span-1 space-y-14">
          {KEY_POINTS.map(({ title, icon, subtitle }) => (
            <div key={title}>
              <Image
                src={icon}
                alt={title}
                width={32}
                height={32}
                draggable={false}
                unoptimized
                loading="lazy"
                className="mb-4 size-[32px] object-contain object-center dark:invert"
              />

              <Title as="h3" className="mb-3 text-2xl md:text-2xl">
                {title}
              </Title>
              <Subtitle className="md:text-lg">{subtitle}</Subtitle>
            </div>
          ))}
        </div>
      </div>
    </section>
  );
}
