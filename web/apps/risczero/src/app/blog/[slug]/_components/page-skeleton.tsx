import { Skeleton } from "@risc0/ui/skeleton";

export function PostPageSkeleton() {
  return (
    <article className="flex min-w-full flex-col items-center">
      <header className="w-full pt-16 text-center">
        {/* date */}
        <div className="h-[20px]">
          <Skeleton className="inline-block h-[16.5px] w-[144px]" />
        </div>

        {/* post title */}
        <Skeleton className="my-6 h-[96px] w-full" />

        {/* authors */}
        <div className="mb-2 flex flex-row items-center justify-center gap-2">
          <Skeleton className="size-7 rounded-full" />
          <Skeleton className="inline-block h-[28px] w-[95px]" />
        </div>
      </header>

      {/* back button */}
      <Skeleton className="mb-2 h-[36px] w-[90px] self-start" />

      {/* cover image */}
      <Skeleton className="mb-8 h-[464px] w-full rounded-2xl" />

      {/* post content */}
      <Skeleton className="mb-32 h-[860px] w-full" />
    </article>
  );
}
