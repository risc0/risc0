import Link from "@web/ui/link";
import Image from "next/image";
import type { PropsWithChildren } from "react";
import ThemeToggle from "~/client/theme-toggle";

export default function ReportsLayout({ children }: PropsWithChildren) {
  return (
    <div className="min-h-screen space-y-4 py-6">
      <div className="container flex max-w-screen-3xl flex-row justify-between">
        <Link href="/" className="transition-opacity hover:opacity-70 flex flex-col gap-2">
          <Image width={59} height={43} src="/risczero.webp" alt="RISC Zero" className="invert dark:invert-0" />

          <h1 className="text-pretty text-[10px] text-muted-foreground">Reports</h1>
        </Link>

        <div className="flex flex-row justify-end gap-2">
          <ThemeToggle />
        </div>
      </div>

      {children}
    </div>
  );
}
