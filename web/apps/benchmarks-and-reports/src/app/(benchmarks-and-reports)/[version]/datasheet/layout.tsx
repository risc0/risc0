import { Separator } from "@risc0/ui/separator";
import { Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { FooterAscii } from "../../_components/footer-ascii";
import { DatasheetCommitHashButton } from "./_components/datasheet-commit-hash-button";

export default function DatasheetLayout({ children, params }) {
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
