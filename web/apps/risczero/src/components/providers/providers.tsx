"use client";

import { TooltipProvider } from "@risc0/ui/tooltip";
import { ThemeProvider } from "next-themes";
import { ProgressBarProvider } from "./progress-bar-provider";

/**
 * Client-side providers.
 */
export function Providers({ children }) {
  return (
    <ThemeProvider attribute="class" defaultTheme="dark" disableTransitionOnChange enableSystem enableColorScheme>
      <ProgressBarProvider className="fixed top-0 h-[2px] bg-primary">
        <TooltipProvider delayDuration={300}>{children}</TooltipProvider>
      </ProgressBarProvider>
    </ThemeProvider>
  );
}
