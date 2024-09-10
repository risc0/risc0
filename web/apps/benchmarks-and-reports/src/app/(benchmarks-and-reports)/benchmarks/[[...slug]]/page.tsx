import type { Metadata } from "next";
import { BENCHMARKS_DESCRIPTION } from "../../_utils/constants";
import { Benchmarks } from "../_components/benchmarks";

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

export default function BenchmarksPage({ params }: { params: { slug: string } }) {
  return (
    <div className="container max-w-screen-3xl">
      <Benchmarks selectedBench={params.slug} />
    </div>
  );
}
