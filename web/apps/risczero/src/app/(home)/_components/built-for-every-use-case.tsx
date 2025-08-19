import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";
import { MagicCard } from "@/components/magic-card";
import { ProgressBarLink } from "@/components/progress-bar-link";
import { CardContent, CardFooter, CardHeader, CardTitle } from "@risc0/ui/card";
import { ArrowUpRight } from "lucide-react";
import Link from "next/link";
import { RollupUseCase } from "./rollup-use-case";

export function BuiltForEveryUseCase() {
  return (
    <section id="comprehensive-solutions-for-every-need" className="container max-w-screen-2xl py-12 md:py-24">
      <Title className="mb-2 text-2xl text-muted-foreground md:text-2xl">Product Suite</Title>
      <Title>Comprehensive Solutions for Every Need</Title>

      <div className="grid grid-cols-1 gap-3 lg:grid-cols-3">
        <div className="col-span-1 lg:col-span-2">
          <ProgressBarLink href="/op-kailua" className="group">
            <MagicCard
              gradientColor="#fefefd"
              cardClassName="group-hover:-translate-y-1 text-default-light transition-all dark:bg-newspaper"
            >
              <CardHeader className="flex flex-row items-center justify-between gap-2 space-y-0 text-2xl">
                <CardTitle>Rollups</CardTitle>
                <ArrowUpRight className="size-8" />
              </CardHeader>
              <CardContent>
                <RollupUseCase />
              </CardContent>
              <CardFooter>
                <Subtitle className="md:text-xl">Future-proof your OP chain with ZK Fraud or Validity Proofs.</Subtitle>
              </CardFooter>
            </MagicCard>
          </ProgressBarLink>
        </div>

        <div className="col-span-1 flex flex-col gap-3">
          <ProgressBarLink href="/steel" className="group">
            <MagicCard
              gradientColor="#fefefd"
              cardClassName="group-hover:-translate-y-1 text-default-light transition-all dark:bg-newspaper"
            >
              <CardHeader className="flex flex-row items-center justify-between gap-2 space-y-0 text-2xl">
                <CardTitle>EVM Development</CardTitle>
                <ArrowUpRight className="size-8" />
              </CardHeader>
              <CardFooter>
                <Subtitle className="md:text-xl">
                  Compute over Ethereum's entire state in your smart contract. Fast, trustless, and cost-effective.
                </Subtitle>
              </CardFooter>
            </MagicCard>
          </ProgressBarLink>

          <Link href="https://github.com/risc0/blobstream0" target="_blank" className="group">
            <MagicCard
              gradientColor="#fefefd"
              cardClassName="group-hover:-translate-y-1 text-default-light transition-all dark:bg-newspaper"
            >
              <CardHeader className="flex flex-row items-center justify-between gap-2 space-y-0 text-2xl">
                <CardTitle>Scalable Data Availability</CardTitle>
                <ArrowUpRight className="size-8" />
              </CardHeader>
              <CardFooter>
                <Subtitle className="md:text-xl">
                  Integrate Celestia's data availability with any chain using Blobstream Zero.
                </Subtitle>
              </CardFooter>
            </MagicCard>
          </Link>

          <Link href="https://docs.beboundless.xyz/introduction/why-boundless" target="_blank" className="group">
            <MagicCard
              gradientColor="#fefefd"
              cardClassName="group-hover:-translate-y-1 text-default-light transition-all dark:bg-newspaper"
            >
              <CardHeader className="flex flex-row items-center justify-between gap-2 space-y-0 text-2xl">
                <CardTitle>Decentralized Proving</CardTitle>
                <ArrowUpRight className="size-8" />
              </CardHeader>
              <CardFooter>
                <Subtitle className="md:text-xl">
                  Get proofs delivered with a high degree of liveness at extremely low cost.
                </Subtitle>
              </CardFooter>
            </MagicCard>
          </Link>
        </div>
      </div>
    </section>
  );
}
