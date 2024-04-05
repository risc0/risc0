import { Button } from "@risc0/ui/button";
import { Link } from "@risc0/ui/link";
import { GithubIcon } from "lucide-react";
import Image from "next/image";
import { ThemeToggle } from "shared/client/theme/theme-toggle";

export function Header() {
  return (
    <div className="container flex max-w-screen-3xl flex-row justify-between pt-6">
      <Link href="/reports" className="flex flex-col gap-2 transition-opacity hover:opacity-70">
        <Image width={59} height={43} src="/risczero.webp" alt="RISC Zero" className="invert dark:invert-0" />

        <h1 className="text-pretty text-[10px] text-primary">Reports</h1>
      </Link>

      <div className="flex flex-row justify-end gap-2">
        <ThemeToggle />

        <Link tabIndex={-1} target="_blank" href="https://github.com/risc0/risc0/">
          <Button variant="ghost" size="sm" startIcon={<GithubIcon />}>
            GitHub
          </Button>
        </Link>
      </div>
    </div>
  );
}
