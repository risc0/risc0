"use client";

import { useIsMounted } from "@risc0/ui/hooks/use-is-mounted";
import Image from "next/image";
import { ProgressBarLink } from "shared/client/providers/progress-bar-provider";
import { useVersion } from "../_hooks/use-version";

export function HeaderLogo() {
  const { version } = useVersion();
  const isMounted = useIsMounted();

  return (
    <ProgressBarLink
      href={isMounted ? `/${version ?? ""}` : "/"}
      className="flex flex-col gap-2 transition-opacity hover:opacity-70"
    >
      <Image unoptimized width={59} height={43} src="/risczero.svg" alt="RISC Zero" className="dark:invert" />

      <h1 className="truncate text-[10px] text-primary">Benchmarks & Reports</h1>
    </ProgressBarLink>
  );
}
