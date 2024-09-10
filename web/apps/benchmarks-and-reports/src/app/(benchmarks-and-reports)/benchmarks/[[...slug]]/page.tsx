import type { Metadata } from "next";
import { BENCHMARKS_DESCRIPTION } from "../../_utils/constants";
import { Benchmarks } from "../_components/benchmarks";

export async function generateStaticParams() {
  const response = await fetch("https://risc0.github.io/ghpages/dev/bench/data.js", {
    cache: "no-store",
  });
  const text = await response.text();
  const data = JSON.parse(text.replace("window.BENCHMARK_DATA = ", "").trim());
  const slugs = Object.keys(data.entries);

  return slugs.map((slug) => ({ slug: [slug] }));
}

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
      <Benchmarks />
    </div>
  );
}
