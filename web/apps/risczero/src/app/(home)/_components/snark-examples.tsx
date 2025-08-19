import { buttonVariants } from "@risc0/ui/button";
import { cn } from "@risc0/ui/cn";
import { Tooltip, TooltipContent, TooltipProvider, TooltipTrigger } from "@risc0/ui/tooltip";
import Link from "next/link";
import { Dock, DockIcon } from "@/components/dock";

const ITEMS = [
  { href: "https://github.com/risc0/demos/tree/main/zk-kyc", icon: <span>zkKYC</span>, label: "zkKYC" },
  { href: "https://github.com/risc0/demos/tree/main/bonsai-pay", icon: <span>JWT</span>, label: "JWT" },
  { href: "https://github.com/risc0/blobstream0", icon: <span>TMint</span>, label: "Tendermint" },
] as const;

export function SnarkExamples() {
  return (
    <TooltipProvider delayDuration={0}>
      <Dock direction="middle" label="Examples:" className="hidden md:flex">
        {ITEMS.map(({ label, href, icon }) => (
          <DockIcon key={label}>
            <Tooltip>
              <TooltipTrigger asChild>
                <Link
                  href={href}
                  target="_blank"
                  className={cn(buttonVariants({ variant: "ghost", size: "icon" }), "size-12 rounded-full")}
                >
                  {icon}
                </Link>
              </TooltipTrigger>
              <TooltipContent>See the {label} project on GitHub</TooltipContent>
            </Tooltip>
          </DockIcon>
        ))}
      </Dock>
    </TooltipProvider>
  );
}
