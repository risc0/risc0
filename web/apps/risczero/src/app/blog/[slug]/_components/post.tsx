import type { Post as IPost } from "@/app/blog/_types";
import { FormattedDate } from "@/components/formatted-date";
import { NotionRendererFull } from "@/components/notion/notion-render-full";
import { ProgressBarLink } from "@/components/progress-bar-link";
import { Shimmer } from "@/components/shimmer";
import { toBase64 } from "@/utils/to-base-64";
import { Button } from "@risc0/ui/button";
import { ArrowLeftIcon } from "lucide-react";
import Image from "next/image";
import type { ExtendedRecordMap } from "notion-types";

type PostProps = {
  post: IPost;
  authors: any[];
  blockMap: ExtendedRecordMap;
  fromTagSlug?: string;
};

export function Post({ post, blockMap, authors, fromTagSlug }: PostProps) {
  return (
    <article className="flex flex-col items-center">
      <header className="pt-16 text-center">
        <FormattedDate date={post.postDate} showWeekday className="text-sm" />

        <h1 className="my-6 w-full max-w-[860px] text-balance font-bold text-3xl sm:text-4xl md:text-5xl">
          {post.title}
        </h1>

        <div className="mb-2 flex flex-row items-center justify-center gap-10">
          {authors.map(({ value }) => {
            return (
              <div className="flex flex-row items-center gap-2" key={value.id}>
                {value.profile_photo && (
                  <Image
                    alt={value.name}
                    width={28}
                    draggable={false}
                    height={28}
                    src={value.profile_photo}
                    className="rounded-full"
                    quality={75}
                  />
                )}
                <p className="text-sm">{value.name}</p>
              </div>
            );
          })}
        </div>
      </header>

      <ProgressBarLink
        href={`/blog${fromTagSlug ? `/tag/${fromTagSlug}` : ""}`}
        className="mb-2 self-start"
        tabIndex={-1}
      >
        <Button variant="ghost" startIcon={<ArrowLeftIcon />}>
          Back
        </Button>
      </ProgressBarLink>

      {post.pageCover && (
        <Image
          width={1024}
          height={464}
          draggable={false}
          className="mb-8 max-h-[464px] w-full rounded-2xl object-cover object-left"
          placeholder={`data:image/svg+xml;base64,${toBase64(Shimmer(1024, 464))}`}
          src={post.pageCover}
          alt={post.title ?? ""}
          quality={80}
          priority
        />
      )}

      <div className="!font-mono relative w-full flex-none">
        <NotionRendererFull recordMap={blockMap} fullPage={false} />
      </div>
    </article>
  );
}
