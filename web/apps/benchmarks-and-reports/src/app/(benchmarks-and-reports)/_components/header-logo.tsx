"use client";

import { useLocalStorage } from "@risc0/ui/hooks/use-local-storage";
import { useMounted } from "@risc0/ui/hooks/use-mounted";
import Image from "next/image";
import Link from "next/link";

export function HeaderLogo() {
  const [versionLocalStorage] = useLocalStorage<string | undefined>("version", undefined);
  const mounted = useMounted();

  return (
    <Link
      href={mounted ? `/${versionLocalStorage ?? ""}` : "/"}
      className="flex flex-col gap-2 transition-opacity hover:opacity-70"
    >
      <Image width={59} height={43} src="/risczero.svg" alt="RISC Zero" className="dark:invert dark:invert-1" />

      <h1 className="truncate text-[10px] text-primary">Benchmarks & Reports</h1>
    </Link>
  );
}
