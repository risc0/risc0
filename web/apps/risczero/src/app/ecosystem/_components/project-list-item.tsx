import { Card, CardContent, CardFooter, CardHeader } from "@risc0/ui/card";
import { ArrowUpRight } from "lucide-react";
import Image from "next/image";
import Link from "next/link";
import { TagItem } from "@/app/blog/_components/tag-item";
import type { Project } from "@/app/blog/_types";

type ProjectListItemProps = {
  project: Project;
};

export function ProjectListItem({ project }: ProjectListItemProps) {
  return (
    <Link href={project.slug ?? ""} className="group" target="_blank">
      <Card
        key={project.id}
        className="group-hover:-translate-y-1 flex min-h-64 flex-col items-center justify-between rounded-3xl border-none px-7 py-5 outline-dashed outline-1 outline-neutral-200 outline-offset-8 transition-all group-hover:outline-neutral-500 dark:outline-neutral-700 dark:group-hover:outline-primary"
      >
        <CardHeader className="flex w-full flex-row items-center justify-end gap-2 space-y-0 p-0">
          {project.tags.length > 0 &&
            project.tags
              .sort((a, b) => a.tag.localeCompare(b.tag))
              .map((tag, index) => <TagItem key={`${project.id}-${index}`} {...tag} />)}
        </CardHeader>

        <CardContent className="w-full p-0">
          <Image
            src={project.pageCover}
            alt={project.title ?? ""}
            height="72"
            width="164"
            draggable={false}
            loading="lazy"
            unoptimized
            className="mx-auto max-h-[72px] max-w-[164px] select-none object-contain object-center dark:invert"
          />
        </CardContent>

        <CardFooter className="flex w-full flex-row justify-between gap-2 p-0 opacity-80">
          <p className="font-mono text-xs">{project.slug}</p>

          <ArrowUpRight />
        </CardFooter>
      </Card>
    </Link>
  );
}
