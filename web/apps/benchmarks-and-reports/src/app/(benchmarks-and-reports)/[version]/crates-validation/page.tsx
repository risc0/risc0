import { Separator } from "@risc0/ui/separator";
import { truncate } from "@risc0/ui/utils/truncate";
import type { Metadata } from "next";
import Link from "next/link";
import { Suspense } from "react";
import { CopyButton } from "shared/client/components/copy-button";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { CRATES_VALIDATION_DESCRIPTION } from "../_utils/constants";
import { findMostRecentHash } from "./_actions/find-most-recent-hash";
import CratesIoValidationContent from "./_components/crates-io-validation-content";

export const metadata: Metadata = {
  title: "Crates.io Validation",
  description: CRATES_VALIDATION_DESCRIPTION,
  openGraph: {
    images: [
      {
        url: `https://benchmarks.risczero.com/api/og?title=Crates.io%20Validation&description=${encodeURIComponent(
          CRATES_VALIDATION_DESCRIPTION,
        )}`,
      },
    ],
  },
};

export default async function CratesIoValidationPage() {
  const mostRecentHash = await findMostRecentHash();

  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <div>
          <h1 className="title-sm">Crates.io Validation</h1>
          <p className="text-muted-foreground text-sm">
            Each night, we test compatibility between each of the{" "}
            <Link href="https://crates.io/crates?sort=downloads" target="_blank" className="link">
              top 1000 Rust crates
            </Link>{" "}
            and the RISC Zero zkVM
          </p>
        </div>
        {mostRecentHash && (
          <CopyButton size="sm" variant="ghost" value={mostRecentHash}>
            Commit Hash<span className="hidden sm:inline">: {truncate(mostRecentHash, 15)}</span>
          </CopyButton>
        )}
      </div>

      <Separator className="mt-2" />

      <div className="mt-6">
        <Suspense fallback={<SuspenseLoader />}>
          <CratesIoValidationContent mostRecentHash={mostRecentHash} />
        </Suspense>
      </div>
    </div>
  );
}
