import Script from "next/script";
import type { PropsWithChildren } from "react";
import ProgressProvider from "~/client/progress-provider";
import { Footer } from "./_components/footer";
import { Header } from "./_components/header";

export default function ReportsLayout({ children }: PropsWithChildren) {
  return (
    <>
      <Header />

      <main className="grow">{children}</main>

      <Footer />

      <ProgressProvider />

      <Script
        // TODO: replace with newer version
        src="https://cdn.jsdelivr.net/npm/chart.js@2.9.4/dist/Chart.min.js"
        strategy="beforeInteractive"
      />
    </>
  );
}
