import { Button } from "@risc0/ui/button";
import { GithubIcon } from "lucide-react";
import Link from "next/link";
import { ThemeToggle } from "shared/client/theme/theme-toggle";
import { Breadcrumbs } from "./breadcrumbs";
import { HeaderLogo } from "./header-logo";
import { VersionSelect } from "./version-select";

export function Header() {
  return (
    <div className="container flex max-w-screen-3xl flex-row justify-between py-6">
      <HeaderLogo />

      <div className="ml-8 flex w-full flex-row items-center justify-between gap-12">
        <Breadcrumbs />

        <div className="flex flex-row justify-end gap-2">
          <VersionSelect />

          <ThemeToggle />

          <Link rel="noopener noreferrer" tabIndex={-1} target="_blank" href="https://github.com/risc0/risc0/">
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
