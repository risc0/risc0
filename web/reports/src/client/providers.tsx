"use client";

import { ThemeProvider } from "next-themes";
import type { PropsWithChildren } from "react";

// Client-side providers
export default function Providers({ children }: PropsWithChildren) {
  return (
    <ThemeProvider attribute="class" defaultTheme="dark" disableTransitionOnChange enableSystem enableColorScheme>
      {children}
    </ThemeProvider>
  );
}
