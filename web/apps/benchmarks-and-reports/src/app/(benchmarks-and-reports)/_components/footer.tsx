import Link from "next/link";

export function Footer() {
  return (
    <div className="space-x-2 py-6 text-center text-muted-foreground text-xs">
      <span>
        Built by{" "}
        <Link
          rel="noopener noreferrer"
          className="link text-muted-foreground"
          href="https://www.risczero.com"
          target="_blank"
        >
          Risc Zero
        </Link>
      </span>
      <span>•</span>
      <Link
        rel="noopener noreferrer"
        target="_blank"
        className="link text-muted-foreground"
        href="https://dev.risczero.com/api/"
      >
        Docs
      </Link>
      <span>•</span>
      <Link
        rel="noopener noreferrer"
        target="_blank"
        className="link text-muted-foreground"
        href="https://github.com/risc0/risc0/"
      >
        GitHub
      </Link>
    </div>
  );
}
