import "shared/styles/styles.css";

import { cn } from "@risc0/ui/cn";
import { SpeedInsights } from "@vercel/speed-insights/next";
import type { Metadata } from "next";
import { JetBrains_Mono } from "next/font/google";
import Script from "next/script";
import type { PropsWithChildren } from "react";
import { Providers } from "shared/client/providers/providers";

export const metadata: Metadata = {
  title: {
    template: "%s | RISC Zero Benchmarks & Reports",
    default: "RISC Zero Benchmarks & Reports",
  },
  keywords: ["risczero", "zero knowledge proofs", "zkvm", "benchmarks", "zk", "reports", "risc0", "risc0.com"],
  metadataBase: new URL("https://reports.risczero.com"),
  description: "Get to market fast with dramatically lower development costs on the first general purpose zkVM",
  openGraph: {
    images: [
      {
        url: "https://reports.risczero.com/api/og?title=RISC%20Zero%20Benchmarks%20%26%20Reports",
      },
    ],
  },
  icons: [
    {
      rel: "icon",
      url: "/favicon.png",
    },
  ],
};

const fontMono = JetBrains_Mono({
  subsets: ["latin"],
  variable: "--font-jetbrains-mono",
});

export default function RootLayout({ children }: PropsWithChildren) {
  return (
    <html lang="en" suppressHydrationWarning className="h-full">
      <body className={cn("flex min-h-full flex-col font-sans", fontMono.variable)}>
        <Providers>{children}</Providers>
        <SpeedInsights />

        <Script defer data-domain="reports.risczero.com" src="https://plausible.io/js/script.outbound-links.js" />
      </body>
    </html>
  );
}
