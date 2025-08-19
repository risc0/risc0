import { Title } from "@/app/_components/title";
import { FlickeringGrid } from "@/components/flickering-grid";
import { getAllInvestors } from "@/libs/notion/get-all-investors";
import { shuffle } from "es-toolkit";
import { ExternalLinkIcon } from "lucide-react";
import Image from "next/image";
import Link from "next/link";
import { Suspense } from "react";

async function InvestorsContent() {
  const investors = await getAllInvestors();

  if (!investors) {
    return null;
  }

  return shuffle(investors).map(({ title, pageCover, id, slug }) => (
    <Link
      className="group relative flex items-center justify-center rounded-lg border border-transparent border-dashed px-3 py-6 opacity-90 transition-all hover:border-border"
      key={id}
      href={slug ?? ""}
      target="_blank"
    >
      <Image
        alt={title ?? ""}
        src={pageCover}
        width={200}
        height={52}
        unoptimized
        draggable={false}
        loading="lazy"
        className="max-h-[52px] max-w-[120px] select-none object-contain object-center xl:max-w-[200px]"
      />

      <ExternalLinkIcon
        size={14}
        className="absolute top-3.5 right-3.5 opacity-0 transition-opacity group-hover:opacity-70"
      />
    </Link>
  ));
}

export function Investors() {
  return (
    <section id="investors" className="relative overflow-hidden bg-[#E5E3D5] text-default-light">
      <FlickeringGrid
        className="absolute inset-0 z-0 hidden size-full animate-fade-in 2xl:block"
        squareSize={3}
        gridGap={16}
        color="#6B7280"
        maxOpacity={0.7}
        flickerChance={0.1}
        height={600}
        width={4000}
      />

      <div className="container relative z-10 max-w-screen-2xl rounded-[6rem] bg-[#E5E3D5] pt-24 pb-20">
        <Title className="mb-12">Investors</Title>

        <div className="grid min-h-[152px] grid-cols-2 md:grid-cols-5">
          <Suspense>
            <InvestorsContent />
          </Suspense>
        </div>
      </div>
    </section>
  );
}
