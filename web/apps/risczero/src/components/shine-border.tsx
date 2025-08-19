"use client";

import { cn } from "@risc0/ui/cn";
import type { CSSProperties, PropsWithChildren } from "react";

type TColorProp = string | string[];

type ShineBorderProps = {
  borderWidth?: number;
  borderRadius?: string;
  duration?: number;
  color?: TColorProp;
  className?: string;
};

export function ShineBorder({
  borderWidth = 1,
  borderRadius = "0.75rem",
  duration = 14,
  color = "#000000",
  className,
  children,
}: PropsWithChildren<ShineBorderProps>) {
  return (
    <div
      style={
        {
          "--border-radius": borderRadius,
        } as CSSProperties
      }
      className={cn("relative rounded-[--border-radius]", className)}
    >
      <div
        style={
          {
            "--border-width": `${String(borderWidth)}px`,
            "--border-radius": borderRadius,
            "--shine-pulse-duration": `${String(duration)}s`,
            "--mask-linear-gradient": "linear-gradient(#fff 0 0) content-box, linear-gradient(#fff 0 0)",
            "--background-radial-gradient": `radial-gradient(transparent,transparent, ${Array.isArray(color) ? color.join(",") : color},transparent,transparent)`,
          } as CSSProperties
        }
        className='before:![-webkit-mask-composite:xor] before:![mask-composite:exclude] pointer-events-none before:absolute before:inset-0 before:aspect-square before:size-full before:rounded-[--border-radius] before:bg-shine-size before:p-[--border-width] before:will-change-[background-position] before:content-[""] motion-safe:before:animate-[shine-pulse_var(--shine-pulse-duration)_infinite_linear] before:[background-image:--background-radial-gradient] before:[background-size:300%_300%] before:[mask:--mask-linear-gradient]'
      />
      {children}
    </div>
  );
}
