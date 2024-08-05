import { Skeleton } from "@risc0/ui/skeleton";

export function CratesIoValidationSkeleton() {
  return (
    <div className="space-y-8">
      <div className="space-y-2">
        <Skeleton className="h-7 w-72" />

        <Skeleton className="h-[116.88px] w-full" />
      </div>

      <div className="space-y-4">
        <div className="flex flex-row items-center justify-between">
          <Skeleton className="h-7 w-40" />

          <div className="flex items-center justify-end gap-2">
            <Skeleton className="h-8 w-[180px]" />
            <Skeleton className="h-8 w-[105.85px]" />
            <Skeleton className="h-8 w-[119.5px]" />
            <Skeleton className="h-8 w-[154px]" />
          </div>
        </div>

        <Skeleton className="h-[1300px] w-full" />
      </div>
    </div>
  );
}
