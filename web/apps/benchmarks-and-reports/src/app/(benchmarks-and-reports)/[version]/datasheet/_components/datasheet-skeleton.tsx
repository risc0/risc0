import { Skeleton } from "@risc0/ui/skeleton";

export function DatasheetSkeleton() {
  return [0, 1, 2, 3].map((element) => (
    <div className="space-y-4" key={element}>
      <div className="flex flex-row items-center justify-between">
        <Skeleton className="h-7 w-52" />
        <Skeleton className="h-8 w-[155px]" />
      </div>

      <Skeleton className="h-[224.5px] w-full" />
    </div>
  ));
}
