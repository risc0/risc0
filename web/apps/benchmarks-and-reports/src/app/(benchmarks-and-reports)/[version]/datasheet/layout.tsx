import { Separator } from "@risc0/ui/separator";
import { type PropsWithChildren, Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { useRedirectIfWrongVersion } from "~/hooks/use-redirect-if-wrong-version";
import type { Version } from "~/types/version";
import { FooterAscii } from "../../_components/footer-ascii";
import { DatasheetCommitHashButton } from "./_components/datasheet-commit-hash-button";

export default function DatasheetLayout({
  children,
  params,
}: PropsWithChildren<{
  params: {
    version: Version;
  };
}>) {
  useRedirectIfWrongVersion(params.version);

  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <h1 className="title-sm">Datasheet</h1>

        <Suspense fallback={<SuspenseLoader />}>
          <DatasheetCommitHashButton version={params.version} />
        </Suspense>
      </div>

      <Separator className="mt-2" />

      {children}

      <FooterAscii text="Datasheet" />
    </div>
  );
}
