import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";
import { Card, CardContent, CardFooter, CardHeader, CardTitle } from "@risc0/ui/card";
import { ArrowUpRightIcon } from "lucide-react";
import Link from "next/link";

const TOOLKIT = [
  {
    title: "Foundry Template",
    subtitle:
      "Seamlessly integrate ZK proofs into EVM dApps. Our Foundry template accelerates development with familiar tools, enabling powerful off-chain computations for on-chain use.",
    url: "https://github.com/risc0/risc0-foundry-template",
  },
  {
    title: "Steel",
    subtitle:
      "Simplify Ethereum interactions with our view call proof library. Execute and prove complex computations over Ethereum's state, bypassing EVM limitations and reducing gas.",
    url: "https://github.com/risc0/risc0-ethereum/tree/main/crates/steel",
  },
  {
    title: "Universal Verifier",
    subtitle:
      "Deploy effortlessly across all EVM chains. RISC Zero's Universal Verifier simplifies multi-chain deployment, ensuring consistent behavior and reducing development overhead.",
    url: "https://dev.risczero.com/api/blockchain-integration/contracts/verifier",
  },
] as const;

function ToolkitItem({ title, subtitle, url }: { title: string; subtitle: string; url: string }) {
  return (
    <Link href={url} target="_blank" className="group">
      <Card className="group-hover:-translate-y-1 flex h-full min-h-72 flex-col border-2 border-steel-light bg-background transition-all hover:shadow-lg dark:border-steel-dark">
        <CardHeader className="flex w-full flex-row items-center justify-between gap-4 space-y-0 p-8">
          <CardTitle className="text-3xl text-steel-light dark:text-steel-dark">{title}</CardTitle>

          <ArrowUpRightIcon className="!-mt-1 size-16 text-steel-light dark:text-steel-dark" />
        </CardHeader>

        <CardContent className="p-8 pb-0" />

        <CardFooter className="p-8">
          <Subtitle>{subtitle}</Subtitle>
        </CardFooter>
      </Card>
    </Link>
  );
}

export function Toolkit() {
  return (
    <section id="toolkit" className="container mb-36 max-w-screen-2xl pt-12 md:pt-24">
      <Title>Comprehensive Toolkit for EVM Developers</Title>

      <div className="grid grid-cols-1 gap-12 lg:grid-cols-3">
        {TOOLKIT.map(({ title, subtitle, url }) => (
          <ToolkitItem key={title} title={title} subtitle={subtitle} url={url} />
        ))}
      </div>
    </section>
  );
}
