import Image from "next/image";
import Link from "next/link";
import ThemeToggle from "~/client/theme-toggle";

export default function SignInHeader() {
  return (
    <div className="flex flex-row justify-between">
      <div>
        <Link tabIndex={-1} href="/" className="transition-opacity hover:opacity-70">
          <Image width={118} height={85} src="/risczero.webp" alt="RISC Zero" className="invert dark:invert-0" />
        </Link>
        <h1 className="mt-2 text-pretty text-[10px] text-muted-foreground">Reports</h1>
      </div>

      <ThemeToggle />
    </div>
  );
}
