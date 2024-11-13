import { Separator } from "@risc0/ui/separator";
import { type PropsWithChildren, Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import type { Version } from "~/types/version";
import { FooterAscii } from "../../_components/footer-ascii";
import { redirectIfWrongVersion } from "../../_utils/redirect-if-wrong-version";
import { ApplicationsBenchmarksCommitHashButton } from "./_components/applications-benchmarks-commit-hash-button";
import { ApplicationsBenchmarksHeader } from "./_components/applications-benchmarks-header";

export default function ApplicationsBenchmarksLayout({
  params,
  children,
}: PropsWithChildren<{
  params: {
    version: Version;
  };
}>) {
  redirectIfWrongVersion(params.version);

  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <ApplicationsBenchmarksHeader />

        <Suspense fallback={<SuspenseLoader />}>
          <ApplicationsBenchmarksCommitHashButton version={params.version} />
        </Suspense>
      </div>

      <Separator className="mt-2" />

      {children}

      <FooterAscii text="Applications Benchmarks" />
    </div>
  );
}
