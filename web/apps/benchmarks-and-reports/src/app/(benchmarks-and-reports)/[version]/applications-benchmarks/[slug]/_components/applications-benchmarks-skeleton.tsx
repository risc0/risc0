import { Skeleton } from "@risc0/ui/skeleton";

export function ApplicationsBenchmarksSkeleton() {
  return (
    <div className="space-y-4">
      <div className="flex flex-row items-center justify-between">
        <Skeleton className="h-7 w-52" />

        <div className="flex items-center justify-end gap-2">
          <Skeleton className="h-8 w-[180px]" />
          <Skeleton className="h-8 w-[155px]" />
        </div>
      </div>

      <Skeleton className="h-[1400px] w-full" />
    </div>
  );
}
