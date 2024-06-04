import type { Metadata } from "next";
import { Suspense } from "react";
import type { Version } from "~/types/version";
import { VERSIONS } from "~/versions";
import { DATASHEET_DESCRIPTION } from "../_utils/constants";
import { DatasheetContent } from "./_components/datasheet-content";
import { DatasheetSkeleton } from "./_components/datasheet-skeleton";

export function generateStaticParams() {
  return VERSIONS.map(({ value }) => ({
    version: value,
  }));
}

export const metadata: Metadata = {
  title: "Datasheet",
  description: DATASHEET_DESCRIPTION,
  openGraph: {
    images: [
      {
        url: `https://benchmarks.risczero.com/api/og?title=Datasheet&description=${encodeURIComponent(
          DATASHEET_DESCRIPTION,
        )}`,
      },
    ],
  },
};

export default function DatasheetPage({
  params,
}: {
  params: {
    version: Version;
  };
}) {
  return (
    <div className="mt-6 grid grid-cols-1 gap-8 xl:grid-cols-2">
      <Suspense fallback={<DatasheetSkeleton />}>
        <DatasheetContent version={params.version} />
      </Suspense>
    </div>
  );
}
