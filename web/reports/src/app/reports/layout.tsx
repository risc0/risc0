import type { PropsWithChildren } from "react";
import SignInFooter from "./_components/footer";
import Header from "./_components/header";

export default function ReportsLayout({ children }: PropsWithChildren) {
  return (
    <>
      <Header />

      <main className="grow">{children}</main>

      <SignInFooter />
    </>
  );
}
