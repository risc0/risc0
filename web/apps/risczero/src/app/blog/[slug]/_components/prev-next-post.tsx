import type { Post } from "@/app/blog/_types";
import { ProgressBarLink } from "@/components/progress-bar-link";
import { Shimmer } from "@/components/shimmer";
import { toBase64 } from "@/utils/to-base-64";
import Image from "next/image";

type PrevNextPostProps = {
  posts: Post[];
  slug: string;
};

export function PrevNextPost({ posts, slug }: PrevNextPostProps) {
  const postIndex = posts.findIndex((post) => post.slug === slug);
  const prevPost = posts[postIndex + 1];
  const nextPost = posts[postIndex - 1];

  if (!prevPost && !nextPost) {
    return null;
  }

  return (
    <div className="my-14 grid grid-cols-2 flex-row flex-nowrap justify-between gap-8 border-border border-t pt-14">
      {prevPost?.slug && (
        <ProgressBarLink
          href={`/blog/${prevPost.slug}`}
          className="flex flex-col gap-2 transition-opacity hover:opacity-80"
        >
          <Image
            src={prevPost.pageCover}
            alt={prevPost.title ?? ""}
            width={200}
            height={104}
            loading="lazy"
            draggable={false}
            quality={75}
            placeholder={`data:image/svg+xml;base64,${toBase64(Shimmer(200, 104))}`}
            className="rounded object-cover object-left"
          />
          <p className="text-muted-foreground text-xs uppercase">Prev</p>
          <h2 className="line-clamp-2 max-w-96 font-bold leading-tight">{prevPost.title}</h2>
        </ProgressBarLink>
      )}
      {nextPost?.slug && (
        <ProgressBarLink
          href={`/blog/${nextPost.slug}`}
          className="flex flex-col items-end gap-2 text-right transition-opacity hover:opacity-80"
        >
          <Image
            src={nextPost.pageCover}
            alt={nextPost.title ?? ""}
            width={200}
            height={104}
            loading="lazy"
            draggable={false}
            quality={75}
            placeholder={`data:image/svg+xml;base64,${toBase64(Shimmer(200, 104))}`}
            className="rounded object-cover object-left"
          />
          <p className="text-muted-foreground text-xs uppercase">Next</p>
          <h2 className="line-clamp-2 max-w-96 font-bold leading-tight">{nextPost.title}</h2>
        </ProgressBarLink>
      )}
    </div>
  );
}
