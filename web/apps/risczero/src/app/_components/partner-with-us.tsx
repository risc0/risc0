import { Button } from "@risc0/ui/button";
import Link from "next/link";
import { Subtitle } from "@/app/_components/subtitle";
import { Title } from "@/app/_components/title";
import { FlickeringGrid } from "@/components/flickering-grid";

export function PartnerWithUs({
  title,
  subtitle,
  theme,
  ctaLink,
  ctaLabel,
}: {
  title?: string;
  subtitle?: string;
  theme: "bonsai" | "steel" | "blobstream" | "zeth" | "op-kailua";
  ctaLabel?: string;
  ctaLink?: string;
}) {
  return (
    <div
      className={`-mb-48 bg-${theme}-light dark:bg-${theme}-dark relative overflow-hidden text-default-dark dark:text-default-light`}
    >
      <FlickeringGrid
        className="absolute inset-0 z-0 hidden size-full animate-fade-in 2xl:block"
        squareSize={3}
        gridGap={16}
        color="#6B7280"
        maxOpacity={0.7}
        flickerChance={0.1}
        height={1000}
        width={4000}
      />

      <div
        className={`bg-${theme}-light dark:bg-${theme}-dark container relative z-10 flex max-w-screen-md flex-col items-center justify-between rounded-[8rem] py-32`}
      >
        <Title className="mb-2 text-center">{title ?? "Partner with Us"}</Title>
        <Subtitle as="p" className="text-center">
          {subtitle ?? (
            <>
              Learn how to use <span className="capitalize">{theme}</span> as a competitive advantage
            </>
          )}
        </Subtitle>
        <Link
          tabIndex={-1}
          className="mt-8"
          href={ctaLink ?? "https://share.hsforms.com/1y4akhGomTBet6MkD9mcdSgq7xur"}
          target="_blank"
        >
          <Button size="lg" variant="secondary">
            {ctaLabel ?? "Contact Us"}
          </Button>
        </Link>
      </div>
    </div>
  );
}
