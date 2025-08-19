"use client";

import { usePathname } from "next/navigation";
import { Marquee } from "@/components/marquee";
import { ProgressBarLink } from "@/components/progress-bar-link";

export function Announcement() {
  const pathname = usePathname();

  if (pathname !== "/") {
    return null;
  }

  return (
    <ProgressBarLink href="/blog/introducing-R0VM-2.0">
      <Marquee
        repeat={60}
        className="flex h-8 animate-fade-in-down items-center bg-primary p-0 font-mono text-white uppercase [--duration:14s] dark:text-black"
      >
        Introducing R0VM 2.0 — The zkVM Built for the Real-Time Era {"//"}
      </Marquee>
    </ProgressBarLink>
  );
}
