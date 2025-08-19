import "../styles/globals.css";

import { Providers } from "@/components/providers/providers";
import { cn } from "@risc0/ui/cn";
import type { Metadata } from "next";
import { JetBrains_Mono } from "next/font/google";
import Script from "next/script";
import type { PropsWithChildren } from "react";
import { Announcement } from "./_components/announcement";
import { Footer } from "./_components/footer";
import { Header } from "./_components/header";
import { OG_BASE } from "./_constants/og";
import { PreloadResources } from "./preload-resources";

const DESCRIPTION =
  "Unlock the full potential of ZK on every chain. High-performance, cost-effective, and powered by the leading open-source zkVM.";

export const metadata: Metadata = {
  metadataBase: new URL("https://risczero.com"),
  title: {
    template: "%s | RISC Zero",
    default: "RISC Zero",
  },
  category: "technology",
  description: DESCRIPTION,
  keywords: ["risczero", "zero knowledge proofs", "zkvm", "benchmarks", "zk", "reports", "risc0", "risc0.com"],
  openGraph: {
    ...OG_BASE,
    title: "RISC Zero",
    description: DESCRIPTION,
  },
  twitter: {
    card: "summary_large_image",
    title: "RISC Zero",
    creator: "@RiscZero",
    description: DESCRIPTION,
    images: [
      {
        url: "https://risczero.com/api/og?title=RISC%20Zero",
      },
    ],
  },
  alternates: {
    canonical: "/",
  },
};

const fontMono = JetBrains_Mono({
  subsets: ["latin"],
  variable: "--font-jetbrains-mono",
});

export default function RootLayout({ children }: PropsWithChildren) {
  return (
    <html suppressHydrationWarning lang="en-US">
      <body className={cn("relative flex min-h-screen flex-col bg-background font-sans", fontMono.variable)}>
        <PreloadResources />

        <Providers>
          <Announcement />

          <Header />

          {children}

          <Footer />
        </Providers>

        <Script defer data-domain="risczero.com" src="https://plausible.io/js/script.outbound-links.js" />
      </body>
    </html>
  );
}
