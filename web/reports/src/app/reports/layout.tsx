import Script from "next/script";
import type { PropsWithChildren } from "react";
import SignInFooter from "./_components/footer";
import Header from "./_components/header";

export default function ReportsLayout({ children }: PropsWithChildren) {
  return (
    <>
      <Header />

      <main className="grow">{children}</main>

      <SignInFooter />
      <Script src="https://cdn.jsdelivr.net/npm/chart.js@4.4.2/dist/chart.umd.min.js" strategy="beforeInteractive" />
    </>
  );
}
