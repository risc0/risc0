import type { PropsWithChildren } from "react";
import ProgressProvider from "shared/client/providers/progress-provider";
import { Footer } from "./_components/footer";
import { Header } from "./_components/header";

export default function ReportsLayout({ children }: PropsWithChildren) {
  return (
    <>
      <Header />

      <main className="grow">{children}</main>

      <Footer />

      <ProgressProvider />
    </>
  );
}
