import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";
import NumberTicker from "@/components/number-ticker";
import { ShineBorder } from "@/components/shine-border";
import { Button } from "@risc0/ui/button";
import { Card, CardContent, CardFooter } from "@risc0/ui/card";
import { ArrowUpRightIcon } from "lucide-react";
import Image from "next/image";
import Link from "next/link";

const KEY_POINTS = [
  {
    title: "Ethereum Compatible",
    icon: "/icons/ethereum.svg",
    subtitle: "Compatible with Ethereum at the opcode level, meaning everything works right out of the box.",
  },
  {
    title: "Effortless Upgradability",
    icon: "/icons/upgradable.svg",
    subtitle: "Seamlessly syncs with Ethereum updates, simplifying ongoing management.",
  },
  {
    title: "100% Open-Source",
    icon: "/icons/open-source.svg",
    subtitle: "Zeth is fully open-source and flexible for all your needs.",
  },
] as const;

export function CostPerTxn() {
  return (
    <section id="zkevm-perfected" className="container mb-36 max-w-screen-2xl pt-12 md:pt-24">
      <Title>
        zkEVM, <span className="text-zeth-light dark:text-zeth-dark">perfected</span>
      </Title>

      <div className="grid grid-cols-1 items-center gap-32 lg:grid-cols-3">
        <div className="col-span-1 space-y-14">
          {KEY_POINTS.map(({ icon, title, subtitle }) => (
            <div key={title}>
              <Image
                src={icon}
                alt={title}
                draggable={false}
                width={32}
                height={32}
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

        <ShineBorder
          borderRadius="4rem"
          className="col-span-2 animate-fade-in shadow-2xl duration-300"
          borderWidth={6}
          color={["#FF7BFA"]}
        >
          <Card className="flex size-full min-h-[280px] flex-col items-center justify-center rounded-[4rem] bg-neutral-800 py-12 md:min-h-[420px] md:pt-24 md:pb-20 dark:bg-neutral-950">
            <CardContent className="p-0 text-center">
              <NumberTicker
                stiffness={120}
                className="bg-gradient-to-b from-white to-neutral-100/80 bg-clip-text font-bold font-mono text-7xl text-transparent md:text-8xl xl:text-9xl"
                values={[3.982, 0.001]}
                direction="down"
                decimals={3}
                isCurrency
              />
              <h4 className="bg-gradient-to-b from-white to-neutral-100/80 bg-clip-text font-bold text-3xl text-transparent">
                Cost Per Txn
              </h4>
            </CardContent>
            <CardFooter className="p-0 pt-12">
              <Link href="https://github.com/risc0/zeth" tabIndex={-1} target="_blank">
                <Button
                  size="lg"
                  variant="outline"
                  className="border-zeth-light border-dashed bg-transparent text-white dark:border-zeth-dark"
                  endIcon={<ArrowUpRightIcon />}
                >
                  View Documentation
                </Button>
              </Link>
            </CardFooter>
          </Card>
        </ShineBorder>
      </div>
    </section>
  );
}
