import { Badge } from "@risc0/ui/badge";
import { Button } from "@risc0/ui/button";
import type { Metadata } from "next";
import { AsciiArt } from "@/components/ascii-art";
import { ProgressBarLink } from "@/components/progress-bar-link";
import { Subtitle } from "./_components/subtitle";
import { Title } from "./_components/title";

export const metadata: Metadata = {
  title: "Page Not Found",
};

export default function NotFoundPage() {
  return (
    <div className="-mb-24 container flex min-h-[56dvh] max-w-screen-lg flex-col items-center gap-16 py-12 lg:flex-row lg:items-center lg:justify-between">
      <div className="space-y-10">
        <div className="space-y-1">
          <Badge variant="secondary" className="mb-2 self-start">
            404 Error
          </Badge>
          <Title className="text-2xl md:text-2xl">Page Not Found</Title>
          <Subtitle className="text-muted-foreground md:text-lg">
            Sorry, the page you are looking for doesn't exist.
          </Subtitle>
        </div>
        <ProgressBarLink href="/" className="inline-block" tabIndex={-1}>
          <Button size="lg" autoFocus className="focus-visible:ring-offset-background">
            Take Me Home
          </Button>
        </ProgressBarLink>
      </div>

      <AsciiArt
        className="text-sm opacity-60"
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
