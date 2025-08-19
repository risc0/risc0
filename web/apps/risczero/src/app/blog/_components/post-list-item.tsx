import { TagItem } from "@/app/blog/_components/tag-item";
import type { Post } from "@/app/blog/_types";
import { ProgressBarLink } from "@/components/progress-bar-link";
import { Shimmer } from "@/components/shimmer";
import { toBase64 } from "@/utils/to-base-64";
import { Card, CardContent } from "@risc0/ui/card";
import Image from "next/image";

type PostListItemProps = {
  post: Post;
  fromTagSlug?: string;
  id: number;
};

export function PostListItem({ post, id, fromTagSlug }: PostListItemProps) {
  return (
    <ProgressBarLink
      href={`/blog/${encodeURIComponent(post.slug ?? "")}${fromTagSlug ? `?from=${encodeURIComponent(fromTagSlug)}` : ""}`}
      className="group"
      prefetch={false}
    >
      <Card
        key={post.id}
        className="group-hover:-translate-y-1 flex flex-col items-stretch overflow-hidden rounded-3xl border-none outline-dashed outline-1 outline-neutral-200 outline-offset-8 transition-all group-hover:outline-neutral-500 md:flex-row md:group-[:nth-child(3n)]:flex-row-reverse dark:outline-neutral-700 dark:group-hover:outline-primary"
      >
        <Image
          src={post.pageCover}
          alt={post.title ?? ""}
          placeholder={`data:image/svg+xml;base64,${toBase64(Shimmer(420, 298))}`}
          height="298"
          width="570"
          draggable={false}
          priority={id === 0}
          quality={75}
          className="min-h-[198px] w-full max-w-[570px] rounded-3xl object-cover object-left shadow transition-all group-[:nth-child(3n)]:group-hover:rounded-s-3xl sm:min-w-[380px] md:min-h-[298px] md:rounded-sm md:group-hover:rounded-e-3xl md:group-[:nth-child(3n)]:group-hover:rounded-e-3xl lg:min-w-[570px]"
        />

        <CardContent className="flex flex-row items-stretch gap-8 pt-6 pb-8 md:px-10">
          <div className="flex flex-col justify-between">
            {post.tags.length > 0 && (
              <div className="-ml-2.5 flex flex-row flex-nowrap gap-2 md:hidden lg:flex">
                {post.tags
                  .sort((a, b) => a.tag.localeCompare(b.tag))
                  .map((tag, index) => (
                    <TagItem key={`${post.id}-${index}`} className="opacity-80" {...tag} />
                  ))}
              </div>
            )}

            <div>
              <h2 className="line-clamp-2 font-bold text-2xl leading-tight">{post.title}</h2>

              <p className="mt-3 line-clamp-4 text-muted-foreground text-sm">{post.summary}</p>
            </div>

            <span className="font-bold text-sm">Read More &rarr;</span>
          </div>
        </CardContent>
      </Card>
    </ProgressBarLink>
  );
}
