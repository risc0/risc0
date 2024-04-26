import { Separator } from "@risc0/ui/separator";
import { Tabs, TabsList, TabsTrigger } from "@risc0/ui/tabs";
import type { Metadata } from "next";
import Link from "next/link";
import { redirect } from "next/navigation";
import { Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { replace } from "string-ts";
import { APPLICATIONS_BENCHMARKS_DESCRIPTION } from "../../_utils/constants";
import ApplicationsBenchmarksCommitHashButton from "./_components/applications-benchmarks-commit-hash-button";
import ApplicationsBenchmarksContent from "./_components/applications-benchmarks-content";
import { FILENAMES_TO_TITLES } from "./_utils/constants";

export const metadata: Metadata = {
  title: "Applications Benchmark",
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

export default function ApplicationsBenchmarksPage({ params }) {
  if (!params.slug) {
    redirect(
      `/${params.version}/applications-benchmarks/${
        // biome-ignore lint/style/noNonNullAssertion: ignore
        replace(Object.keys(FILENAMES_TO_TITLES)[0]!, ".csv", "")
      }`,
    );
  }

  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <h1 className="title-sm">Applications Benchmarks</h1>

        <Suspense fallback={<SuspenseLoader />}>
          <ApplicationsBenchmarksCommitHashButton version={params.version} />
        </Suspense>
      </div>

      <Separator className="mt-2" />

      <Tabs className="mt-6" defaultValue={params.slug?.[0]}>
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
            <ApplicationsBenchmarksContent version={params.version} currentTab={params.slug?.[0]} />
          </Suspense>
        </div>
      </Tabs>
    </div>
  );
}
