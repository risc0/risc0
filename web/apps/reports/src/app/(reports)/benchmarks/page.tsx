import type { Metadata } from "next";
import { ChartsWrapper } from "./_components/charts-wrapper";

export const metadata: Metadata = {
  title: "Benchmarks",
};

export default function BenchmarksPage() {
  return (
    <div className="container max-w-screen-3xl pt-4">
      <ChartsWrapper />
    </div>
  );
}
