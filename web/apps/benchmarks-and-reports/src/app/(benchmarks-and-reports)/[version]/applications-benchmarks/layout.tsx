import { Separator } from "@risc0/ui/separator";
import { type PropsWithChildren, Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { useRedirectIfWrongVersion } from "~/hooks/use-redirect-if-wrong-version";
import type { Version } from "~/types/version";
import { FooterAscii } from "../../_components/footer-ascii";
import { ApplicationsBenchmarksCommitHashButton } from "./_components/applications-benchmarks-commit-hash-button";

export default function ApplicationsBenchmarksLayout({
  params,
  children,
}: PropsWithChildren<{
  params: {
    version: Version;
  };
}>) {
  useRedirectIfWrongVersion(params.version);

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

      <FooterAscii text="Applications Benchmarks" />
    </div>
  );
}
