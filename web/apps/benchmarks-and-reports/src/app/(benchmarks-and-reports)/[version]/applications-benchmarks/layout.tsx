import { Separator } from "@risc0/ui/separator";
import { Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { ApplicationsBenchmarksCommitHashButton } from "./_components/applications-benchmarks-commit-hash-button";

export default function ApplicationsBenchmarksLayout({ params, children }) {
  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <h1 className="title-sm">Applications Benchmarks</h1>

        <Suspense fallback={<SuspenseLoader />}>
          <ApplicationsBenchmarksCommitHashButton version={params.version} />
        </Suspense>
      </div>

      <Separator className="mt-2" />

      {children}
    </div>
  );
}
