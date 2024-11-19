import { joinWords } from "@risc0/ui/utils/join-words";
import upperFirst from "lodash-es/upperFirst";
import { BENCHMARKS_DESCRIPTION } from "../../_utils/constants";
import { fetchBenchmarks } from "../_actions/fetch-benchmarks";
import { Benchmarks } from "../_components/benchmarks";

export async function generateStaticParams() {
  const data = await fetchBenchmarks();
  const slugs = Object.keys(data.entries);

  return slugs.map((slug) => ({ slug: [slug] }));
}

export async function generateMetadata(props: {
  params: Promise<{
    slug: string;
  }>;
}) {
  const params = await props.params;

  if (!params.slug[0]) {
    return;
  }

  const title = joinWords(params.slug[0])
    .split(" ")
    .map((word) => upperFirst(word))
    .join(" ");

  return {
    title: `${title ? `${title} ` : ""}Benchmarks`,
    description: BENCHMARKS_DESCRIPTION,
    openGraph: {
      images: [
        {
          url: `https://reports.risczero.com/api/og?title=Benchmarks&description=${encodeURIComponent(
            BENCHMARKS_DESCRIPTION,
          )}`,
        },
      ],
    },
  };
}

export default function BenchmarksPage() {
  return (
    <div className="container max-w-screen-3xl">
      <Benchmarks />
    </div>
  );
}
