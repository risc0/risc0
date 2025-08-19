"use client";

import { GlareCard } from "@/components/glare-card";
import { ShineBorder } from "@/components/shine-border";
import { Card } from "@risc0/ui/card";
import Image from "next/image";

export function Bonsai3dCard() {
  return (
    <GlareCard>
      <ShineBorder borderWidth={2} color={["#a2a7d4"]} borderRadius="1.5rem">
        <Card className="flex h-[250px] w-full max-w-[587px] rounded-3xl bg-neutral-800 p-4 md:h-[500px] dark:bg-neutral-900">
          <Image
            src="/solutions/bonsai2.png"
            unoptimized
            priority
            width={587}
            height={500}
            alt="Bonsai ASCII Art"
            draggable={false}
            className="max-h-[250px] rounded-xl object-cover object-center md:max-h-[500px]"
          />
        </Card>
      </ShineBorder>
    </GlareCard>
  );
}
