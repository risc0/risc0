import { Separator } from "@risc0/ui/separator";
import { Tabs } from "@risc0/ui/tabs";
import { truncate } from "@risc0/ui/utils/truncate";
import type { Metadata } from "next";
import { redirect } from "next/navigation";
import { CopyButton } from "shared/client/components/copy-button";
import { replace } from "string-ts";
import { APPLICATIONS_BENCHMARKS_DESCRIPTION } from "../../_utils/constants";
import { fetchApplicationsBenchmarksCommitHash } from "./_actions/fetch-applications-benchmarks-commit-hash";
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

export default async function ApplicationsBenchmarksPage({ params }) {
  const commitHash = await fetchApplicationsBenchmarksCommitHash();

  if (!params.slug) {
    redirect(`/applications-benchmarks/${replace(Object.keys(FILENAMES_TO_TITLES)[0]!, ".csv", "")}`);
  }

  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <h1 className="title-sm">Applications Benchmarks</h1>
        {commitHash && (
          <CopyButton size="sm" variant="ghost" value={commitHash}>
            Commit Hash<span className="hidden sm:inline">: {truncate(commitHash, 15)}</span>
          </CopyButton>
        )}
      </div>

      <Separator className="mt-2" />

      <Tabs className="mt-6" defaultValue={params.slug?.[0]}>
        <ApplicationsBenchmarksContent />
      </Tabs>
    </div>
  );
}
