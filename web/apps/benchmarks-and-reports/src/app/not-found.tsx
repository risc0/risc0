import { Badge } from "@risc0/ui/badge";
import { buttonVariants } from "@risc0/ui/button";
import { CardDescription, CardFooter, CardHeader, CardTitle } from "@risc0/ui/card";
import type { Metadata } from "next";
import { ProgressBarLink } from "shared/client/providers/progress-bar-provider";
import { AsciiArt } from "shared/server/components/ascii-art";

export const metadata: Metadata = {
  title: "Page Not Found",
};

export default function NotFoundPage() {
  return (
    <div className="container flex min-h-screen max-w-screen-lg flex-col items-center gap-6 py-12 lg:flex-row lg:items-center lg:pt-0">
      <div className="lg:w-1/2">
        <CardHeader className="space-y-1">
          <Badge variant="secondary" className="mb-2 self-start">
            404 Error
          </Badge>
          <CardTitle className="text-2xl">Page Not Found</CardTitle>
          <CardDescription>Sorry, the page you are looking for doesn't exist</CardDescription>
        </CardHeader>

        <CardFooter>
          <ProgressBarLink href="/" className={buttonVariants({ variant: "default" })}>
            Take Me Home
          </ProgressBarLink>
        </CardFooter>
      </div>

      <AsciiArt
        withWrapper
        className="text-sm"
        code={`// Code
  ___   ___  ________  ___   ___
 |\\  \\ |\\  \\|\\   __  \\|\\  \\ |\\  \\
 \\ \\  \\\\_\\  \\ \\  \\|\\  \\ \\  \\\\_\\  \\
  \\ \\______  \\ \\  \\\\\\  \\ \\______  \\
   \\|_____|\\  \\ \\  \\\\\\  \\|_____|\\  \\
          \\ \\__\\ \\_______\\     \\ \\__\\
           \\|__|\\|_______|      \\|__|`}
      />
    </div>
  );
}
