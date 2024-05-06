import type { Metadata } from "next";
import { Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { DATASHEET_DESCRIPTION } from "../_utils/constants";
import { DatasheetContent } from "./_components/datasheet-content";

export const metadata: Metadata = {
  title: "Datasheet",
  description: DATASHEET_DESCRIPTION,
  openGraph: {
    images: [
      {
        url: `https://reports-and-benchmarks-risczero.vercel.app/api/og?title=Datasheet&description=${encodeURIComponent(
          DATASHEET_DESCRIPTION,
        )}`,
      },
    ],
  },
};

export default function DatasheetPage({ params }) {
  return (
    <div className="mt-6 grid grid-cols-1 gap-8 xl:grid-cols-2">
      <Suspense fallback={<SuspenseLoader />}>
        <DatasheetContent version={params.version} />
      </Suspense>
    </div>
  );
}
