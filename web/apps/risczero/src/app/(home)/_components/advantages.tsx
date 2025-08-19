import { Button } from "@risc0/ui/button";
import { CardContent, CardFooter, CardHeader, CardTitle } from "@risc0/ui/card";
import { ArrowUpRightIcon } from "lucide-react";
import Image from "next/image";
import Link from "next/link";
import { Suspense } from "react";
import { Title } from "@/app/_components/title";
import { MagicCard } from "@/components/magic-card";
import { ProgressBarLink } from "@/components/progress-bar-link";
import { Contributors } from "./contributors";

export function Advantages() {
  return (
    <section id="the-risc-zero-advantage" className="container max-w-screen-2xl py-12 md:py-24">
      <Title>The RISC Zero Advantage</Title>

      <div className="grid grid-cols-1 gap-4 md:grid-cols-3">
        <ProgressBarLink className="group" href="/steel" tabIndex={-1} target="_blank">
          <MagicCard
            gradientColor="#fefefd"
            cardClassName="dark:bg-newspaper"
            className="flex flex-col justify-between text-default-light"
          >
            <CardHeader className="flex h-28 flex-row items-center justify-between space-y-0 p-8 pb-6">
              <CardTitle className="truncate text-3xl underline-offset-[6px] group-hover:underline">
                EVM Aligned
              </CardTitle>

              <Button
                className="-mt-1 size-12"
                variant="ghost"
                startIcon={<ArrowUpRightIcon className="size-16" />}
                size="icon"
              >
                <span className="sr-only">Explore Steel</span>
              </Button>
            </CardHeader>

            <CardContent>
              <div className="animate-fade-in overflow-hidden rounded-lg shadow-md">
                <Image
                  unoptimized
                  src="/misc/code.png"
                  alt="EVM Aligned"
                  loading="lazy"
                  width={387.3}
                  height={190.8}
                  draggable={false}
                  className="w-full object-contain object-center"
                />
              </div>
            </CardContent>

            <CardFooter className="p-8 pt-0 text-xl">
              <p className="line-clamp-4">
                Seamlessly run Solidity contracts in the zkVM, boosting performance and reducing gas costs.
              </p>
            </CardFooter>
          </MagicCard>
        </ProgressBarLink>

        <MagicCard
          gradientColor="#fefefd"
          cardClassName="dark:bg-newspaper"
          className="flex flex-col justify-between text-default-light"
        >
          <CardHeader className="flex h-28 min-h-[104px] flex-row items-center justify-between space-y-0 p-8 pb-6">
            <CardTitle className="truncate text-3xl">Future-Proof Design</CardTitle>
          </CardHeader>

          <CardContent>
            <div className="animate-fade-in">
              <Image
                src="/misc/scaling.svg"
                unoptimized
                alt="Future-Proof Design"
                width={387.3}
                height={190.8}
                draggable={false}
                loading="lazy"
                className="max-h-[190.65px] w-full object-contain object-center"
              />
            </div>
          </CardContent>

          <CardFooter className="p-8 pt-0 text-xl">
            <p className="line-clamp-4">
              Evolve without limits. Upgrade your zkVM apps seamlessly, preserving your development agility.
            </p>
          </CardFooter>
        </MagicCard>

        <MagicCard
          gradientColor="#fefefd"
          cardClassName="dark:bg-newspaper"
          className="flex flex-col justify-between text-default-light"
        >
          <Link href="https://github.com/risc0" tabIndex={-1} target="_blank">
            <CardHeader className="flex h-28 flex-row items-center justify-between space-y-0 p-8">
              <CardTitle className="truncate text-3xl underline-offset-[6px] group-hover:underline">
                100% Open-Source
              </CardTitle>

              <Button
                className="-mt-1 size-12"
                variant="ghost"
                startIcon={<ArrowUpRightIcon className="size-16" />}
                size="icon"
              >
                <span className="sr-only">View on GitHub</span>
              </Button>
            </CardHeader>
          </Link>

          <CardContent className="flex h-[174px] flex-col justify-center p-0">
            <Suspense fallback={<div className="h-[174px]" />}>
              <Contributors />
            </Suspense>
          </CardContent>

          <CardFooter className="p-8 text-xl">
            <p className="line-clamp-4">Leverage an open-source codebase, continuously improved by the community.</p>
          </CardFooter>
        </MagicCard>
      </div>
    </section>
  );
}
