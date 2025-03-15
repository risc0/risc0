"use client";

import { Button } from "@risc0/ui/button";
import { Skeleton } from "@risc0/ui/skeleton";
import { DownloadIcon } from "lucide-react";
import Link from "next/link";

export function BenchmarksHeader({ lastUpdate }: { lastUpdate: string }) {
  return (
    <div className="flex items-center justify-between">
      <div>
        <h1 className="text-2xl">Benchmarks</h1>
        <p className="text-muted-foreground text-xs">
          To see the source code or run the benchmarks yourself,{" "}
          <Link className="link" target="_blank" href="https://github.com/risc0/risc0/tree/main/benchmarks">
            see our benchmarks directory
          </Link>
          .
        </p>
        <p className="text-muted-foreground text-xs">
          We recommend reading about our{" "}
          <Link className="link" target="_blank" href="https://dev.risczero.com/api/recursion">
            recursive proving architecture
          </Link>{" "}
          as a companion for this page.
        </p>
        <div className="text-muted-foreground text-xs">
          Last update: {lastUpdate || <Skeleton className="inline-block h-2 w-28" />}
        </div>
      </div>
      <div className="flex items-center gap-3">
        <Button id="dl-button" size="sm" variant="ghost" startIcon={<DownloadIcon />}>
          Download All Benchmarks Data
        </Button>
      </div>
    </div>
  );
}
