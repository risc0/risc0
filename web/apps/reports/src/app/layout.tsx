import "@web/shared/styles/globals.css";

import { TooltipProvider } from "@web/ui/tooltip";
import { GeistMono } from "geist/font/mono";
import { GeistSans } from "geist/font/sans";
import { Next13NProgress } from "nextjs13-progress";
import type { PropsWithChildren } from "react";
import Providers from "~/client/providers";

export const metadata = {
  title: {
    template: "%s | RISC Zero Reports",
    default: "RISC Zero Reports",
  },
  description: "Get to market fast with dramatically lower development costs on the first general purpose zkVM.",
  icons: [
    {
      rel: "icon",
      url: "/favicon.png",
    },
  ],
};

export default function RootLayout({ children }: PropsWithChildren) {
  return (
    <html
      lang="en"
      suppressHydrationWarning
      className={`${
        GeistMono.variable
        // biome-ignore lint/nursery/useSortedClasses: ignore
      } ${GeistSans.variable} h-full`}
    >
      <body className="flex min-h-full flex-col">
        <Providers>
          <TooltipProvider>{children}</TooltipProvider>
        </Providers>
        <Next13NProgress color="#4E46E5" height={1} showOnShallow={false} />
      </body>
    </html>
  );
}
