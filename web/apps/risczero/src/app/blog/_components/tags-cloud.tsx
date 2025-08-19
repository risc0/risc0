import { Badge } from "@risc0/ui/badge";
import { cn } from "@risc0/ui/cn";
import Link from "next/link";
import type { Post } from "@/app/blog/_types";

type TagsCloudItemProps = {
  tag?: string;
  selected: boolean;
  tagCounts?: number;
};

function TagsCloudItem({ selected, tag, tagCounts }: TagsCloudItemProps) {
  return (
    <Link
      href={selected || !tag ? "/blog" : `/blog/tag/${encodeURIComponent(tag)}`}
      className="flex h-full items-center"
    >
      <Badge
        variant={selected ? "default" : "outline"}
        className={cn("text-sm", !selected && "border-neutral-300 border-dashed dark:border-neutral-600")}
      >
        {tag && tagCounts ? (
          <span className="flex flex-row gap-3">
            {tag}{" "}
            <span
              className={cn(
                "font-normal text-muted-foreground",
                selected && "text-default-dark dark:text-default-light",
              )}
            >
              {tagCounts}
            </span>
          </span>
        ) : (
          "All"
        )}
      </Badge>
    </Link>
  );
}

type TagsCloudProps = {
  tags: string[];
  tagCounts: Record<string, number>;
  posts: Post[];
  currentTag?: string;
};

export function TagsCloud({ tags, tagCounts, currentTag }: TagsCloudProps) {
  return (
    <div className="mt-4 flex flex-wrap justify-center gap-x-3 gap-y-2 md:justify-start">
      <TagsCloudItem selected={!currentTag} />

      {tags.map((tag) => (
        <TagsCloudItem key={tag} tag={tag} selected={tag === currentTag} tagCounts={tagCounts[tag]} />
      ))}
    </div>
  );
}
