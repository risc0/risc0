import { ProgressBarLink } from "@/components/progress-bar-link";
import { cn } from "@risc0/ui/cn";
import Image, { type ImageProps } from "next/image";

export function HeaderLogo({ className, ...rest }: Omit<ImageProps, "src" | "alt">) {
  return (
    <ProgressBarLink href="/" className="flex min-w-[59px] flex-col gap-2 transition-opacity hover:opacity-80">
      <Image
        unoptimized
        priority
        width={59}
        height={43}
        className={cn("w-[59px] dark:invert", className)}
        {...rest}
        src="/companies/risczero.svg"
        alt="RISC Zero Company Logo"
        draggable={false}
      />
    </ProgressBarLink>
  );
}
