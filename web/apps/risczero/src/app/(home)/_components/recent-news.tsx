import { Title } from "@/app/_components/title";
import { ProgressBarLink } from "@/components/progress-bar-link";
import { getAllPosts } from "@/libs/notion/get-all-posts";
import Image from "next/image";

export async function RecentNews() {
  const posts = await getAllPosts();
  const last3Posts = posts?.slice(0, 3);

  return (
    <section id="recent-news" className="container max-w-screen-2xl py-12 md:py-24">
      <Title>Recent News</Title>

      <div className="grid grid-cols-1 gap-16 lg:grid-cols-3">
        {last3Posts?.map((post) => {
          return (
            <ProgressBarLink
              href={`/blog/${post.slug ?? ""}`}
              key={post.id}
              className="flex flex-col transition-opacity hover:opacity-80"
            >
              <div className="flex-1">
                <Image
                  draggable={false}
                  src={post.pageCover}
                  alt={post.title ?? ""}
                  width={448}
                  height={234}
                  loading="lazy"
                  quality={75}
                  className="mb-8 max-h-[212px] rounded-lg object-cover"
                />

                <h3 className="mb-4 line-clamp-2 font-bold text-2xl text-primary">{post.title}</h3>

                <p className="mb-6 line-clamp-6 leading-tight">{post.summary}</p>
              </div>

              <span className="font-bold text-sm">Read More &rarr;</span>
            </ProgressBarLink>
          );
        })}
      </div>
    </section>
  );
}
