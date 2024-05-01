import { Separator } from "@risc0/ui/separator";
import { Tabs, TabsList, TabsTrigger } from "@risc0/ui/tabs";
import pick from "lodash-es/pick";
import Link from "next/link";
import { Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { replace } from "string-ts";
import { APPLICATIONS_BENCHMARKS_DESCRIPTION } from "../../_utils/constants";
import { ApplicationsBenchmarksCommitHashButton } from "./_components/applications-benchmarks-commit-hash-button";
import { ApplicationsBenchmarksContent } from "./_components/applications-benchmarks-content";
import { FILENAMES_TO_TITLES } from "./_utils/constants";

export function generateMetadata({ params }) {
  // read route params to generate metadata
  const slug = params.slug ?? "";
  const slugLabel = Object.values(pick(FILENAMES_TO_TITLES, `${slug}.csv`))[0];

  return {
    title: `${slugLabel ? `${slugLabel} | ` : ""}Applications Benchmark`,
    description: APPLICATIONS_BENCHMARKS_DESCRIPTION,
    openGraph: {
      images: [
        {
          url: `https://reports-and-benchmarks-risczero.vercel.app/api/og?title=Applications%20Benchmark&description=${encodeURIComponent(
            APPLICATIONS_BENCHMARKS_DESCRIPTION,
          )}`,
        },
      ],
    },
  };
}

export default function ApplicationsBenchmarksPage({ params }) {
  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <h1 className="title-sm">Applications Benchmarks</h1>

        <Suspense fallback={<SuspenseLoader />}>
          <ApplicationsBenchmarksCommitHashButton version={params.version} />
        </Suspense>
      </div>

      <Separator className="mt-2" />

      <Tabs className="mt-6" defaultValue={params.slug}>
        <div className="flex items-center overflow-auto">
          <TabsList>
            {Object.keys(FILENAMES_TO_TITLES).map((filename, index) => (
              <Link
                tabIndex={-1}
                key={filename}
                href={`/${params.version}/applications-benchmarks/${replace(filename, ".csv", "")}`}
              >
                <TabsTrigger value={replace(filename, ".csv", "")}>
                  {Object.values(FILENAMES_TO_TITLES)[index]}
                </TabsTrigger>
              </Link>
            ))}
          </TabsList>
        </div>

        <div className="mt-4">
          <Suspense fallback={<SuspenseLoader />}>
            <ApplicationsBenchmarksContent version={params.version} currentTab={params.slug} />
          </Suspense>
        </div>
      </Tabs>
    </div>
  );
}
