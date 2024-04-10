import type { Metadata } from "next";
import { Charts } from "./_components/charts";

export const metadata: Metadata = {
  title: "Benchmarks",
};

export default function BenchmarksPage() {
  return (
    <div className="container max-w-screen-3xl">
      <Charts />
    </div>
  );
}
