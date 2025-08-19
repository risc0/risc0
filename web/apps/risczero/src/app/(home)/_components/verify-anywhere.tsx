import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";
import { Button } from "@risc0/ui/button";
import { Skeleton } from "@risc0/ui/skeleton";
import { list } from "@vercel/blob";
import { ArrowUpRightIcon } from "lucide-react";
import Link from "next/link";
import { Suspense } from "react";

async function VerifyAnywhereVideo() {
  const { blobs } = await list({
    prefix: "output-rv1ecgDs2adWx8pInlzqtcpN32wvaM.webm",
    limit: 1,
  });

  if (!blobs || blobs.length === 0) {
    return;
  }

  const { url } = blobs[0]!;

  return (
    <video
      autoPlay
      playsInline
      loop
      preload="none"
      muted
      controls={false}
      aria-label="Video player"
      className="rounded-lg invert lg:min-h-[410px] dark:invert-0"
    >
      <source src={url} type="video/webm" />
    </video>
  );
}

export function VerifyAnywhere() {
  return (
    <>
      <div className="relative col-span-2">
        <Suspense fallback={<Skeleton className="h-[410px] w-full" />}>
          <VerifyAnywhereVideo />
        </Suspense>
      </div>

      <div className="col-span-1 flex flex-col items-center md:items-start">
        <Title as="h3" className="mb-8 text-center text-3xl md:text-left md:text-3xl">
          Verify Anywhere
        </Title>
        <Subtitle className="text-center md:text-left md:text-xl">
          RISC Zero's Universal Verifier enables seamless proof verification across major blockchains. Switch chains
          effortlessly, inheriting their native security while expanding your reach.
        </Subtitle>

        <Link
          href="https://dev.risczero.com/api/blockchain-integration/contracts/verifier"
          target="_blank"
          tabIndex={-1}
        >
          <Button
            size="lg"
            endIcon={<ArrowUpRightIcon />}
            className="mt-10 border-primary border-dashed text-primary lg:w-[290px]"
            variant="outline"
          >
            Verifier Contracts
          </Button>
        </Link>
      </div>
    </>
  );
}
