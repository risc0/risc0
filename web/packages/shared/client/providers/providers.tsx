"use client";

import { TooltipProvider } from "@risc0/ui/tooltip";
import { ThemeProvider } from "next-themes";
import type { PropsWithChildren } from "react";
import { Toaster } from "../components/toaster";
import { ProgressBarProvider } from "./progress-bar-provider";

// Client-side providers
export function Providers({ children }: PropsWithChildren) {
  return (
    <ThemeProvider attribute="class" defaultTheme="dark" disableTransitionOnChange enableSystem enableColorScheme>
      <div vaul-drawer-wrapper="" className="flex flex-1 flex-col bg-background">
        <ProgressBarProvider className="fixed top-0 h-[2px] bg-primary">
          <TooltipProvider>{children}</TooltipProvider>
          <Toaster visibleToasts={3} richColors duration={8000} />
        </ProgressBarProvider>
      </div>
    </ThemeProvider>
  );
}
