import { Button } from "@risc0/ui/button";
import { Skeleton } from "@risc0/ui/skeleton";
import { DownloadIcon } from "lucide-react";

export function BenchmarksHeader({ lastUpdate }: { lastUpdate: string }) {
  return (
    <div className="flex items-center justify-between">
      <div>
        <h1 className="title-sm">Benchmarks</h1>
        <div className="text-muted-foreground text-xs">
          <span>Last Update: {lastUpdate || <Skeleton className="inline-block h-2 w-28" />}</span>
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
