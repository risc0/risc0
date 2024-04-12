import type { Metadata } from "next";
import { BENCHMARKS_DESCRIPTION } from "../_utils/constants";
import { Charts } from "./_components/charts";

export const metadata: Metadata = {
  title: "Benchmarks",
  description: BENCHMARKS_DESCRIPTION,
};

export default function BenchmarksPage() {
  return (
    <div className="container max-w-screen-3xl">
      <Charts />
    </div>
  );
}
