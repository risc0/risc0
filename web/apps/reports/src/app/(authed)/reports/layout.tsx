import { cookies } from "next/headers";
import { redirect } from "next/navigation";
import type { PropsWithChildren } from "react";
import ThemeToggle from "~/client/theme-toggle";

export default function ReportsLayout({ children }: PropsWithChildren) {
  const cookieStore = cookies();
  const token = cookieStore.get("auth_token");

  if (!token) {
    redirect("/sign-in");
  }

  return (
    <div className="min-h-screen space-y-4 py-6">
      <div className="container flex max-w-screen-3xl flex-row items-center justify-between">
        <h1 className="title">RISC Zero Reports</h1>

        <div className="flex flex-row justify-end gap-2">
          <ThemeToggle />
        </div>
      </div>

      {children}
    </div>
  );
}
