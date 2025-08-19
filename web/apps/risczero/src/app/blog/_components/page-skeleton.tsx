import { rand } from "@/utils/rand";
import { Skeleton } from "@risc0/ui/skeleton";

export function BlogPageSkeleton() {
  const tags = [0, 1, 2, 3] as const;
  const posts = [0, 1, 2, 3, 4, 5, 6] as const;

  return (
    <>
      <ul className="mt-4 flex flex-wrap gap-x-3 gap-y-2">
        {tags.map((tag) => (
          <Skeleton
            key={tag}
            style={{
              width: `${rand(42, 100)}px`,
            }}
            className="h-[26px] rounded-md"
          />
        ))}
      </ul>

      <div className="my-12 flex flex-col gap-20">
        {posts.map((post) => (
          <Skeleton
            key={post}
            className="h-[320.15px] w-full rounded-3xl outline-dashed outline-1 outline-neutral-200 outline-offset-8 dark:outline-neutral-700"
          />
        ))}
      </div>
    </>
  );
}
