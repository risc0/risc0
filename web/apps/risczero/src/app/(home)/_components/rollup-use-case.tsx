"use client";

import { cn } from "@risc0/ui/cn";
import Image from "next/image";
import { useRef } from "react";
import { AnimatedBeam } from "@/components/animated-beam";

export function RollupUseCase({ className }: { className?: string }) {
  const containerRef = useRef<HTMLDivElement>(null);
  const div1Ref = useRef(null);
  const div2Ref = useRef(null);
  const div3Ref = useRef(null);
  const div4Ref = useRef(null);
  const div5Ref = useRef(null);
  const div6Ref = useRef(null);
  const div7Ref = useRef(null);

  return (
    <div
      className={cn("relative flex h-[324px] w-full items-center justify-center overflow-hidden", className)}
      ref={containerRef}
    >
      <div className="flex size-full max-w-lg flex-row items-stretch justify-between gap-10">
        <div className="flex flex-col justify-center gap-2">
          <Image
            ref={div1Ref}
            src="/companies/arbitrum.svg"
            width={20}
            height={20}
            loading="lazy"
            alt="Arbitrum"
            unoptimized
            draggable={false}
            className="z-10 flex size-12 items-center justify-center rounded-full border border-neutral-300 border-dashed bg-white p-3 shadow-[0_0_20px_-12px_rgba(0,0,0,0.8)] dark:border-neutral-600"
          />

          <Image
            ref={div2Ref}
            src="/companies/base.svg"
            width={20}
            height={20}
            loading="lazy"
            alt="Base"
            unoptimized
            draggable={false}
            className="z-10 flex size-12 items-center justify-center rounded-full border border-neutral-300 border-dashed bg-white p-3 shadow-[0_0_20px_-12px_rgba(0,0,0,0.8)] dark:border-neutral-600"
          />

          <Image
            ref={div3Ref}
            src="/companies/optimism.svg"
            width={20}
            height={20}
            loading="lazy"
            alt="Optimism"
            draggable={false}
            unoptimized
            className="z-10 flex size-12 items-center justify-center rounded-full border border-neutral-300 border-dashed bg-white p-3 shadow-[0_0_20px_-12px_rgba(0,0,0,0.8)] dark:border-neutral-600"
          />

          <Image
            ref={div4Ref}
            src="/companies/mantle.svg"
            width={20}
            height={20}
            loading="lazy"
            alt="Mantle"
            draggable={false}
            unoptimized
            className="z-10 flex size-12 items-center justify-center rounded-full border border-neutral-300 border-dashed bg-white p-3 shadow-[0_0_20px_-12px_rgba(0,0,0,0.8)] dark:border-neutral-600"
          />

          <Image
            ref={div5Ref}
            src="/companies/opbnb.svg"
            width={20}
            height={20}
            loading="lazy"
            alt="opBNB"
            unoptimized
            draggable={false}
            className="z-10 flex size-12 items-center justify-center rounded-full border border-neutral-300 border-dashed bg-white p-3 shadow-[0_0_20px_-12px_rgba(0,0,0,0.8)] dark:border-neutral-600"
          />
        </div>

        <div className="flex flex-col justify-center">
          <div className="z-10 flex size-24 items-center justify-center rounded-full border border-neutral-300 border-solid bg-white p-3 shadow-[0_0_20px_-12px_rgba(0,0,0,0.8)] dark:border-neutral-600 dark:bg-primary">
            <Image
              ref={div6Ref}
              src="/companies/risczero.svg"
              width={42}
              height={30}
              alt="RISC Zero"
              loading="lazy"
              unoptimized
              draggable={false}
            />
          </div>
        </div>

        <div className="flex flex-col justify-center">
          <span
            ref={div7Ref}
            className="z-10 flex size-12 items-center justify-center rounded-full border border-neutral-300 border-solid bg-white p-3 font-black font-mono shadow-[0_0_20px_-12px_rgba(0,0,0,0.8)] dark:border-neutral-600"
          >
            ZK
          </span>
        </div>
      </div>

      <AnimatedBeam containerRef={containerRef} fromRef={div1Ref} toRef={div6Ref} />
      <AnimatedBeam containerRef={containerRef} fromRef={div2Ref} toRef={div6Ref} />
      <AnimatedBeam containerRef={containerRef} fromRef={div3Ref} toRef={div6Ref} />
      <AnimatedBeam containerRef={containerRef} fromRef={div4Ref} toRef={div6Ref} />
      <AnimatedBeam containerRef={containerRef} fromRef={div5Ref} toRef={div6Ref} />
      <AnimatedBeam containerRef={containerRef} fromRef={div6Ref} toRef={div7Ref} />
    </div>
  );
}
