"use client";

import Link from "next/link";
import { useRouter } from "next/navigation";
import { type ComponentProps, startTransition } from "react";
import { useProgressBar } from "./providers/progress-bar-provider";

// same as next's `Link` component, but adds a nice progress bar at top of the screen
// need to wrap your app in `ProgressBarProvider` for this to work
export function ProgressBarLink({ href, onClick, children, ...rest }: ComponentProps<typeof Link>) {
  const progress = useProgressBar();
  const router = useRouter();
  const isExternal = typeof href === "string" && href.startsWith("http");

  return (
    <Link
      href={href}
      onClick={(e) => {
        if (isExternal) {
          return;
        }

        e.preventDefault();
        onClick?.(e);
        progress.start();

        startTransition(() => {
          router.push(href.toString());
          progress.done();
        });
      }}
      {...rest}
    >
      {children}
    </Link>
  );
}
