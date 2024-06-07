import type { Metadata } from "next";
import { Suspense } from "react";
import { CRATES_VALIDATION_DESCRIPTION } from "../[version]/_utils/constants";
import { CratesIoValidationContent } from "./_components/crates-io-validation-content";
import { CratesIoValidationSkeleton } from "./_components/crates-io-validation-skeleton";

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

export default function CratesIoValidationPage() {
  return (
    <div className="mt-6">
      <Suspense fallback={<CratesIoValidationSkeleton />}>
        <CratesIoValidationContent />
      </Suspense>
    </div>
  );
}
