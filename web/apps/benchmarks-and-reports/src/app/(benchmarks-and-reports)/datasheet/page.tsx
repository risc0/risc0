import { Separator } from "@risc0/ui/separator";
import { truncate } from "@risc0/ui/utils/truncate";
import type { Metadata } from "next";
import { Suspense } from "react";
import { CopyButton } from "shared/client/components/copy-button";
import { DATASHEET_DESCRIPTION } from "../_utils/constants";
import { fetchDatasheetCommitHash } from "./_actions/fetch-datasheet-commit-hash";
import DatasheetContent from "./_components/datasheet-content";

export const metadata: Metadata = {
  title: "Datasheet",
  description: DATASHEET_DESCRIPTION,
  openGraph: {
    images: {
      url: "http://localhost:3000/og?title=Datasheet",
    },
  },
};

export default async function DatasheetPage() {
  const commitHash = await fetchDatasheetCommitHash();

  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <h1 className="title-sm">Datasheet</h1>
        {commitHash && (
          <CopyButton size="sm" variant="ghost" value={commitHash}>
            Commit Hash<span className="hidden sm:inline">: {truncate(commitHash, 15)}</span>
          </CopyButton>
        )}
      </div>

      <Separator className="mt-2" />

      <div className="mt-6 grid grid-cols-1 gap-8 xl:grid-cols-2">
        <Suspense>
          <DatasheetContent />
        </Suspense>
      </div>
    </div>
  );
}
