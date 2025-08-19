"use client";

import { Card } from "@risc0/ui/card";
import { cn } from "@risc0/ui/cn";
import { motion, useMotionTemplate, useMotionValue } from "motion/react";
import { type HTMLAttributes, type MouseEvent, useCallback, useEffect } from "react";

type MagicCardProps = HTMLAttributes<HTMLDivElement> & {
  gradientSize?: number;
  gradientColor?: string;
  gradientOpacity?: number;
  cardClassName?: string;
};

export function MagicCard({
  children,
  className,
  cardClassName,
  gradientSize = 200,
  gradientColor = "#000",
  gradientOpacity = 0.8,
}: MagicCardProps) {
  const mouseX = useMotionValue(-gradientSize);
  const mouseY = useMotionValue(-gradientSize);

  const handleMouseMove = useCallback(
    (e: MouseEvent<HTMLDivElement>) => {
      const { left, top } = e.currentTarget.getBoundingClientRect();

      mouseX.set(e.clientX - left);
      mouseY.set(e.clientY - top);
    },
    [mouseX, mouseY],
  );

  const handleMouseLeave = useCallback(() => {
    mouseX.set(-gradientSize);
    mouseY.set(-gradientSize);
  }, [mouseX, mouseY, gradientSize]);

  useEffect(() => {
    mouseX.set(-gradientSize);
    mouseY.set(-gradientSize);
  }, [mouseX, mouseY, gradientSize]);

  return (
    <Card
      onMouseMove={handleMouseMove}
      onMouseLeave={handleMouseLeave}
      className={cn("group relative flex size-full overflow-hidden", cardClassName)}
    >
      <div className={cn("relative z-10 w-full", className)}>{children}</div>
      <motion.div
        className="-inset-px pointer-events-none absolute rounded-xl opacity-0 transition-opacity duration-300 group-hover:opacity-100"
        style={{
          background: useMotionTemplate`
            radial-gradient(${gradientSize}px circle at ${mouseX}px ${mouseY}px, ${gradientColor}, transparent 100%)
          `,
          opacity: gradientOpacity,
        }}
      />
    </Card>
  );
}
