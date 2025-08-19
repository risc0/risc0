"use client";

import { cn } from "@risc0/ui/cn";
import { motion, useAnimation, useInView } from "motion/react";
import { type PropsWithChildren, useEffect, useRef } from "react";

type BoxRevealProps = {
  width?: "fit-content" | "100%";
  theme?: "zeth" | "steel" | "bonsai" | "blobstream" | "primary" | "op-kailua";
  duration?: number;
};

export function BoxReveal({ children, width = "fit-content", theme, duration }: PropsWithChildren<BoxRevealProps>) {
  const mainControls = useAnimation();
  const slideControls = useAnimation();
  const ref = useRef(null);
  const isInView = useInView(ref, { once: true });

  useEffect(() => {
    if (isInView) {
      slideControls.start("visible");
      mainControls.start("visible");
    } else {
      slideControls.start("hidden");
      mainControls.start("hidden");
    }
  }, [isInView, mainControls, slideControls]);

  return (
    <div ref={ref} style={{ padding: "4px", position: "relative", width, overflow: "hidden" }}>
      <motion.div
        variants={{
          hidden: { opacity: 0, y: 75 },
          visible: { opacity: 1, y: 0 },
        }}
        initial="hidden"
        animate={mainControls}
        transition={{ duration: duration || 0.5, delay: 0.25 }}
      >
        {children}
      </motion.div>

      <motion.div
        variants={{
          hidden: { left: 0 },
          visible: { left: "100%" },
        }}
        initial="hidden"
        animate={slideControls}
        transition={{ duration: duration || 0.5, ease: "easeIn" }}
        className={cn(
          `bg-${theme}-light dark:bg-${theme}-dark absolute top-1 right-0 bottom-1 left-0 z-20`,
          !theme && "bg-primary",
        )}
      />
    </div>
  );
}
