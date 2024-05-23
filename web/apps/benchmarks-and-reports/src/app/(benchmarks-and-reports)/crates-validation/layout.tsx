import { Separator } from "@risc0/ui/separator";
import Link from "next/link";
import { Suspense } from "react";
import { SuspenseLoader } from "shared/client/components/suspense-loader";
import { FooterAscii } from "../_components/footer-ascii";
import { CratesIoValidationHashButton } from "./_components/creates-io-validation-hash-button";

export default function CratesIoValidationLayout({ children }) {
  return (
    <div className="container max-w-screen-3xl">
      <div className="flex items-center justify-between gap-8">
        <div>
          <h1 className="title-sm">Crates.io Validation</h1>
          <p className="text-muted-foreground text-sm">
            Each night, we test compatibility between each of the{" "}
            <Link
              rel="noopener noreferrer"
              href="https://crates.io/crates?sort=downloads"
              target="_blank"
              className="link"
            >
              top 1000 Rust crates
            </Link>{" "}
            and the RISC Zero zkVM
          </p>
        </div>

        <Suspense fallback={<SuspenseLoader />}>
          <CratesIoValidationHashButton />
        </Suspense>
      </div>

      <Separator className="mt-2" />

      {children}

      <FooterAscii text="Crates.io Validation" />
    </div>
  );
}
