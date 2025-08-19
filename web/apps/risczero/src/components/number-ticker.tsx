"use client";

import { cn } from "@risc0/ui/cn";
import { useInView, useMotionValue, useSpring } from "motion/react";
import { useEffect, useRef } from "react";

type NonEmptyNumberArray = [number, ...number[]];

export default function NumberTicker({
  values,
  direction = "up",
  delay = 0,
  decimals = 0,
  className,
  isCurrency = false,
  damping = 60,
  stiffness = 250,
}: {
  values: NonEmptyNumberArray;
  direction?: "up" | "down";
  className?: string;
  decimals?: number;
  delay?: number; // Delay in seconds
  isCurrency?: boolean;
  damping?: number;
  stiffness?: number;
}) {
  const ref = useRef<HTMLSpanElement>(null);
  const motionValue = useMotionValue(direction === "down" ? values[0] : (values[1] ?? 0));
  const springValue = useSpring(motionValue, {
    damping,
    stiffness,
  });
  const isInView = useInView(ref, { once: true, margin: "0px" });

  useEffect(() => {
    if (isInView) {
      setTimeout(() => {
        motionValue.set(direction === "down" ? (values[1] ?? 0) : values[0]);
      }, delay * 1000);
    }
  }, [motionValue, isInView, delay, values, direction]);

  useEffect(
    () =>
      springValue.on("change", (latest) => {
        if (!ref.current) {
          return;
        }

        /**
         * Ensure 3 decimal places.
         */
        const formattedNumber = latest.toFixed(decimals);

        ref.current.textContent = `${isCurrency ? "$" : ""}${formattedNumber}`;
      }),
    [springValue, decimals, isCurrency],
  );

  return (
    <span className={cn("tabular-nums", className)} ref={ref}>
      {isCurrency ? "$" : ""}
      {direction === "down" ? values[0] : (values[1] ?? 0)}
    </span>
  );
}
