import type { Project } from "@/app/blog/_types";
import { Marquee } from "@/components/marquee";
import { ProgressBarLink } from "@/components/progress-bar-link";
import { getAllProjects } from "@/libs/notion/get-all-projects";
import { cn } from "@risc0/ui/cn";
import Image from "next/image";
import { Suspense } from "react";

function PartnerCard({ title, pageCover }: Project) {
  return (
    <Image
      unoptimized
      height="72"
      width="164"
      alt={title ?? ""}
      src={pageCover}
      draggable={false}
      className={cn("max-h-[72px] max-w-[164px] object-contain object-center px-8 py-2 dark:invert")}
    />
  );
}

async function PartnersContent() {
  const partners = await getAllProjects();

  if (!partners) {
    return null;
  }

  const filteredPartners = partners.filter((partner) => partner.pageCover);
  const firstRow = filteredPartners.slice(0, filteredPartners.length / 2);
  const secondRow = filteredPartners.slice(filteredPartners.length / 2);

  return (
    <ProgressBarLink href="/ecosystem" className="animate-fade-in">
      <Marquee className="[--duration:35s]">
        {firstRow.map((review) => (
          <PartnerCard key={review.pageCover} {...review} />
        ))}
      </Marquee>
      <Marquee reverse className="[--duration:35s]">
        {secondRow.map((review) => (
          <PartnerCard key={review.pageCover} {...review} />
        ))}
      </Marquee>
    </ProgressBarLink>
  );
}

export function Partners() {
  return (
    <section
      id="partners"
      className="relative flex min-h-[368px] w-full flex-col items-center justify-center overflow-hidden py-12 md:py-24"
    >
      <Suspense>
        <PartnersContent />
      </Suspense>
    </section>
  );
}
