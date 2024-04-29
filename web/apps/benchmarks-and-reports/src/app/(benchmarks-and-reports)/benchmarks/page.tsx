import type { Metadata } from "next";
import { Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { BENCHMARKS_DESCRIPTION } from "../[version]/_utils/constants";
import { Charts } from "./_components/charts";

export const metadata: Metadata = {
  title: "Benchmarks",
  description: BENCHMARKS_DESCRIPTION,
  openGraph: {
    images: [
      {
        url: `https://benchmarks.risczero.com/api/og?title=Benchmarks&description=${encodeURIComponent(
          BENCHMARKS_DESCRIPTION,
        )}`,
      },
    ],
  },
};

export default function BenchmarksPage() {
  return (
    <div className="container max-w-screen-3xl">
      <Suspense fallback={<SuspenseLoader />}>
        <Charts />
      </Suspense>
    </div>
  );
}
