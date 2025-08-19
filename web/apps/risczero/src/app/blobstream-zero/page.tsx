import type { Metadata } from "next";
import { Hero } from "./_components/hero";
import { KeyPoints } from "./_components/key-points";

export const metadata: Metadata = {
  title: "Blobstream Zero",
  description: "Prove and verify Celestia DA on any chain with Blobstream Zero.",
  alternates: {
    canonical: "/blobstream-zero",
  },
};

export default function BlobstreamZeroPage() {
  return (
    <main>
      <Hero />

      <KeyPoints />
    </main>
  );
}
