import cn from "@web/shared/cn";
import type { HTMLAttributes } from "react";

export default function Skeleton({ className, ...rest }: HTMLAttributes<HTMLDivElement>) {
  return <div className={cn("animate-pulse rounded-md bg-primary/10", className)} {...rest} />;
}
