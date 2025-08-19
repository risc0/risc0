"use client";

import { AnimatePresence, motion, useMotionTemplate } from "motion/react";
import { createContext, type PropsWithChildren, use } from "react";
import { useProgress } from "@/app/_hooks/use-progress";

const ProgressBarContext = createContext<ReturnType<typeof useProgress> | null>(null);

export function useProgressBar() {
  const progress = use(ProgressBarContext);

  if (progress === null) {
    throw new Error("Need to be inside provider");
  }

  return progress;
}

export function ProgressBarProvider({ className, children }: PropsWithChildren<{ className: string }>) {
  const progress = useProgress();
  const width = useMotionTemplate`${progress.value}%`;

  return (
    <ProgressBarContext.Provider value={progress}>
      <AnimatePresence onExitComplete={progress.reset}>
        {progress.state !== "complete" && (
          <motion.div
            style={{
              width,
              height: "3px",
              borderRadius: "999px",
              opacity: 1,
              zIndex: 999,
            }}
            exit={{ opacity: 0 }}
            className={className}
          />
        )}
      </AnimatePresence>

      {children}
    </ProgressBarContext.Provider>
  );
}
