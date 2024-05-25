import { Tabs, TabsList, TabsTrigger } from "@risc0/ui/tabs";
import Link from "next/link";
import { pick } from "radash";
import { Suspense } from "react";
import { replace } from "string-ts";
import { VERSIONS } from "~/versions";
import { APPLICATIONS_BENCHMARKS_DESCRIPTION } from "../../_utils/constants";
import { ApplicationsBenchmarksContent } from "./_components/applications-benchmarks-content";
import { ApplicationsBenchmarksSkeleton } from "./_components/applications-benchmarks-skeleton";
import { FILENAMES_TO_TITLES } from "./_utils/constants";

export function generateStaticParams() {
  return VERSIONS.flatMap(({ value }) => {
    return Object.keys(FILENAMES_TO_TITLES).map((filename) => ({
      slug: replace(filename, ".csv", ""),
      version: value,
    }));
  });
}

export function generateMetadata({ params }) {
  // read route params to generate metadata
  const slug = params.slug ?? "";
  const slugLabel = Object.values(
    pick(FILENAMES_TO_TITLES, [`${slug}.csv`] as (keyof typeof FILENAMES_TO_TITLES)[]),
  )[0];

  return {
    title: `${slugLabel ? `${slugLabel} | ` : ""}Applications Benchmark`,
    description: APPLICATIONS_BENCHMARKS_DESCRIPTION,
    openGraph: {
      images: [
        {
          url: `https://benchmarks.risczero.com/api/og?title=Applications%20Benchmark&description=${encodeURIComponent(
            APPLICATIONS_BENCHMARKS_DESCRIPTION,
          )}`,
        },
      ],
    },
  };
}

export default function ApplicationsBenchmarksPage({ params }) {
  return (
    <Tabs className="mt-6" defaultValue={params.slug}>
      <TabsList>
        {Object.keys(FILENAMES_TO_TITLES).map((filename, index) => (
          <Link
            tabIndex={-1}
            key={filename}
            replace
            prefetch
            href={`/${params.version}/applications-benchmarks/${replace(filename, ".csv", "")}`}
          >
            <TabsTrigger value={replace(filename, ".csv", "")}>{Object.values(FILENAMES_TO_TITLES)[index]}</TabsTrigger>
          </Link>
        ))}
      </TabsList>

      <div className="mt-4">
        <Suspense fallback={<ApplicationsBenchmarksSkeleton />}>
          <ApplicationsBenchmarksContent version={params.version} currentTab={params.slug} />
        </Suspense>
      </div>
    </Tabs>
  );
}
