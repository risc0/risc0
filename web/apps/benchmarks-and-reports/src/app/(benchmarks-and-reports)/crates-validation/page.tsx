import { Separator } from "@risc0/ui/separator";
import type { Metadata } from "next";
import Link from "next/link";
import { Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { CRATES_VALIDATION_DESCRIPTION } from "../[version]/_utils/constants";
import { CratesIoValidationContent } from "./_components/crates-io-validation-content";
import { CratesIoValidationHashButton } from "./_components/creates-io-validation-hash-button";

export const metadata: Metadata = {
  title: "Crates.io Validation",
  description: CRATES_VALIDATION_DESCRIPTION,
  openGraph: {
    images: [
      {
        url: `https://reports-and-benchmarks-risczero.vercel.app/api/og?title=Crates.io%20Validation&description=${encodeURIComponent(
          CRATES_VALIDATION_DESCRIPTION,
        )}`,
      },
    ],
  },
};

export default function CratesIoValidationPage() {
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

        <Suspense fallback={<SuspenseLoader />}>
          <CratesIoValidationHashButton />
        </Suspense>
      </div>

      <Separator className="mt-2" />

      <div className="mt-6">
        <Suspense fallback={<SuspenseLoader />}>
          <CratesIoValidationContent />
        </Suspense>
      </div>
    </div>
  );
}
