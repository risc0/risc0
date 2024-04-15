import type { Metadata } from "next";
import { Suspense } from "react";
import { BENCHMARKS_DESCRIPTION } from "../_utils/constants";
import { Charts } from "./_components/charts";

export const metadata: Metadata = {
  title: "Benchmarks",
  description: BENCHMARKS_DESCRIPTION,
};

export default function BenchmarksPage() {
  return (
    <div className="container max-w-screen-3xl">
      <Suspense>
        <Charts />
      </Suspense>
    </div>
  );
}
