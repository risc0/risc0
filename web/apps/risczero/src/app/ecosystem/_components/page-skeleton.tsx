import { Skeleton } from "@risc0/ui/skeleton";

export function EcosystemPageSkeleton() {
  const projects = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] as const;

  return projects.map((project) => (
    <Skeleton
      key={project}
      className="h-[256px] w-full rounded-2xl outline-dashed outline-1 outline-neutral-200 outline-offset-8 dark:outline-neutral-700"
    />
  ));
}
