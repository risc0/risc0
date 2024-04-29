"use client";

import { Button } from "@risc0/ui/button";
import { useLocalStorage } from "@risc0/ui/hooks/use-local-storage";
import { GithubIcon } from "lucide-react";
import Image from "next/image";
import Link from "next/link";
import { ThemeToggle } from "shared/client/theme/theme-toggle";
import { Breadcrumbs } from "./breadcrumbs";
import { VersionSelect } from "./version-select";

export function Header() {
  const [versionLocalStorage] = useLocalStorage<string | undefined>("version", undefined);

  return (
    <div className="container flex max-w-screen-3xl flex-row justify-between py-6">
      <Link href={`/${versionLocalStorage ?? ""}`} className="flex flex-col gap-2 transition-opacity hover:opacity-70">
        <Image width={59} height={43} src="/risczero.svg" alt="RISC Zero" className="dark:invert dark:invert-1" />

        <h1 className="truncate text-[10px] text-primary">Benchmarks & Reports</h1>
      </Link>

      <div className="ml-8 flex w-full flex-row items-center justify-between gap-12">
        <Breadcrumbs />

        <div className="flex flex-row justify-end gap-2">
          <VersionSelect />

          <ThemeToggle />

          <Link tabIndex={-1} target="_blank" href="https://github.com/risc0/risc0/">
            <Button variant="outline" size="sm" className="hidden sm:flex" startIcon={<GithubIcon />}>
              GitHub
            </Button>
            <Button variant="outline" className="flex sm:hidden" size="icon-sm" startIcon={<GithubIcon />}>
              <span className="sr-only">GitHub</span>
            </Button>
          </Link>
        </div>
      </div>
    </div>
  );
}
