import { Button } from "@risc0/ui/button";
import { Link } from "@risc0/ui/link";
import { GithubIcon } from "lucide-react";
import Image from "next/image";
import { ThemeToggle } from "shared/client/theme/theme-toggle";
import { Breadcrumbs } from "./breadcrumbs";

export function Header() {
  return (
    <div className="container flex max-w-screen-3xl flex-row justify-between py-6">
      <Link href="/" className="flex flex-col gap-2 transition-opacity hover:opacity-70">
        <Image width={59} height={43} src="/risczero.webp" alt="RISC Zero" className="invert dark:invert-0" />

        <h1 className="truncate text-[10px] text-primary">Benchmarks & Reports</h1>
      </Link>

      <div className="ml-8 flex w-full flex-row items-center justify-between gap-12">
        <Breadcrumbs />

        <div className="flex flex-row justify-end gap-2">
          <ThemeToggle />

          <Link tabIndex={-1} target="_blank" href="https://github.com/risc0/risc0/">
            <Button variant="ghost" size="sm" className="hidden sm:flex" startIcon={<GithubIcon />}>
              GitHub
            </Button>
            <Button variant="ghost" className="flex sm:hidden" size="icon-sm" startIcon={<GithubIcon />}>
              <span className="sr-only">GitHub</span>
            </Button>
          </Link>
        </div>
      </div>
    </div>
  );
}
