import { cn } from "@risc0/ui/cn";
import type { HTMLAttributes } from "react";

interface SubtitleProps extends HTMLAttributes<HTMLHeadingElement | HTMLParagraphElement> {
  as?: "h1" | "h2" | "h3" | "h4" | "h5" | "h6" | "p";
  className?: string;
}

export function Subtitle({ as: Component = "p", children, className }: SubtitleProps) {
  return <Component className={cn("text-pretty text-lg md:max-w-lg md:text-2xl", className)}>{children}</Component>;
}
