import "@web/shared/styles/globals.css";

import { TooltipProvider } from "@web/ui/tooltip";
import { GeistMono } from "geist/font/mono";
import { GeistSans } from "geist/font/sans";
import Script from "next/script";
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
      } ${GeistSans.variable}`}
    >
      <body>
        <Providers>
          <TooltipProvider>{children}</TooltipProvider>
        </Providers>
        <Script strategy="beforeInteractive" src="/google.js" />
      </body>
    </html>
  );
}
