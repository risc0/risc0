import Link from "next/link";

export function ApplicationsBenchmarksHeader() {
  return (
    <div>
      <h1 className="text-2xl">Applications Benchmarks</h1>
      <p className="text-muted-foreground text-xs">
        To see the source code or run the applications benchmarks yourself,{" "}
        <Link className="link" target="_blank" href="https://github.com/risc0/risc0/tree/main/benchmarks">
          see our benchmarks directory
        </Link>
        .
      </p>
    </div>
  );
}
