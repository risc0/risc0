import { cn } from "@risc0/ui/cn";
import type { HTMLAttributes } from "react";

interface TitleProps extends HTMLAttributes<HTMLHeadingElement | HTMLParagraphElement> {
  as?: "h1" | "h2" | "h3" | "h4" | "h5" | "h6" | "p";
  className?: string;
}

export function Title({ as: Component = "h2", children, className, ...rest }: TitleProps) {
  return (
    <Component className={cn("mb-16 max-w-screen-md text-pretty font-bold text-4xl md:text-6xl", className)} {...rest}>
      {children}
    </Component>
  );
}
