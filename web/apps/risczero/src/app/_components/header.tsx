"use client";

import { Badge } from "@risc0/ui/badge";
import { buttonVariants } from "@risc0/ui/button";
import { cn } from "@risc0/ui/cn";
import {
  NavigationMenu,
  NavigationMenuContent,
  NavigationMenuItem,
  NavigationMenuLink,
  NavigationMenuList,
  NavigationMenuTrigger,
  navigationMenuTriggerStyle,
} from "@risc0/ui/navigation-menu";
import { ArrowUpRightIcon } from "lucide-react";
import Link from "next/link";
import { type ElementRef, forwardRef, type PropsWithChildren, type ReactNode } from "react";
import { RiDiscordLine, RiGithubLine, RiTwitterXLine, RiYoutubeLine } from "react-icons/ri";
import { ProgressBarLink } from "@/components/progress-bar-link";
import { ThemeToggle } from "@/components/theme-toggle";
import { HeaderLogo } from "./header-logo";
import { MobileMenu } from "./mobile-menu";

const socials: { title: string; href: string; description: string; image: ReactNode }[] = [
  {
    title: "GitHub",
    description: "Contribute to open-source projects",
    href: "https://github.com/risc0",
    image: <RiGithubLine size={16} className="text-muted-foreground" />,
  },
  {
    title: "Discord",
    description: "Join our technical community",
    href: "https://discord.com/invite/risczero",
    image: <RiDiscordLine size={16} className="text-muted-foreground" />,
  },
  {
    title: "X",
    description: "Read our latest announcements",
    href: "https://x.com/RiscZero",
    image: <RiTwitterXLine size={16} className="text-muted-foreground" />,
  },
  {
    title: "YouTube",
    description: "Watch our latest videos",
    href: "https://www.youtube.com/@risczero",
    image: <RiYoutubeLine size={16} className="text-muted-foreground" />,
  },
];

const company: { title: string; href: string; description: string }[] = [
  {
    title: "Ecosystem",
    href: "/ecosystem",
    description: "An overview of apps & integrations",
  },
  {
    title: "Our Story",
    href: "/our-story",
    description: "How we started & our purpose",
  },
  {
    title: "Careers",
    href: "https://jobs.ashbyhq.com/RiscZero",
    description: "See all open roles",
  },
];

const demos: { title: string; href: string }[] = [
  {
    title: "Bonsai Pay",
    href: "/blog/bonsai-pay",
  },
  {
    title: "DAO Governance",
    href: "/blog/governance",
  },
  {
    title: "ZK Coprocessor",
    href: "/blog/a-guide-to-zk-coprocessors-for-scalability",
  },
  {
    title: "ZK Fraud Proofs for Optimistic Rollups",
    href: "/blog/altlayer-zkfraudproofs",
  },
  {
    title: "zkKYC",
    href: "/blog/decentralized-identity-verification-with-zkkyc-and-soulbound-nfts",
  },
  {
    title: "zk Light Client",
    href: "https://github.com/risc0/demos/tree/main/near-zk-light-client",
  },
  {
    title: "zkML",
    href: "https://github.com/risc0/risc0/tree/main/examples/smartcore-ml",
  },
];

const developers: { title: string; href: string; description: string }[] = [
  {
    title: "Documentation",
    href: "https://dev.risczero.com",
    description: "Learn how to get started",
  },
  {
    title: "Benchmarks & Reports",
    href: "https://reports.risczero.com",
    description: "See all the numbers",
  },
  {
    title: "zkvm",
    href: "https://dev.risczero.com/api/zkvm",
    description: "Our zero-knowledge virtual machine",
  },
  {
    title: "Bug Bounties",
    href: "https://hackenproof.com/company/risc-zero/programs",
    description: "Let the bug hunt begin",
  },
];

const solutions: {
  title: string;
  href: string;
  description: string;
  disabled?: boolean;
}[] = [
  {
    title: "OP Kailua",
    href: "/op-kailua",
    description: "Future-proof your OP Chain with ZK",
  },
  {
    title: "Steel",
    href: "/steel",
    description: "Supercharge your EVM Development",
  },
  {
    title: "Boundless",
    href: "https://beboundless.xyz",
    description: "The Universal ZK Protocol",
  },
];

type HeaderListItemProps = {
  className?: string;
  onClick?: () => void;
  title: ReactNode;
  disabled?: boolean;
  href?: string;
};

export const HeaderListItem = forwardRef<ElementRef<"a">, PropsWithChildren<HeaderListItemProps>>(
  ({ className, title, children, href, disabled, onClick, ...props }, ref) => {
    const isExternal = href?.startsWith("http");

    return (
      <li className="relative">
        {disabled && (
          <Badge variant="secondary" className="absolute top-3 right-3 text-[9px]">
            Coming Soon!
          </Badge>
        )}
        <NavigationMenuLink asChild className={cn(disabled && "pointer-events-none opacity-50")}>
          <ProgressBarLink
            tabIndex={disabled ? -1 : 0}
            ref={ref}
            className={cn(
              "flex select-none flex-row items-center justify-between gap-4 rounded-md p-3 no-underline outline-none transition-colors hover:bg-accent hover:text-accent-foreground focus:bg-accent focus:text-accent-foreground",
              className,
            )}
            href={href ?? ""}
            target="_blank"
            onClick={onClick}
            {...props}
          >
            <div className="flex flex-col gap-1">
              <div className="mt-[1px] font-bold text-sm leading-none">{title}</div>
              {children && <p className="line-clamp-2 text-muted-foreground text-sm leading-snug">{children}</p>}
            </div>
            {isExternal && <ArrowUpRightIcon className="size-4 text-muted-foreground" />}
          </ProgressBarLink>
        </NavigationMenuLink>
      </li>
    );
  },
);

export function Header() {
  return (
    <header className="container relative z-[70] flex min-h-28 max-w-screen-2xl flex-row items-center justify-between">
      <HeaderLogo />

      <div className="flex flex-row">
        <NavigationMenu viewPortClassName="border-neutral-200 border-dashed dark:border-neutral-700">
          <NavigationMenuList className="gap-2.5 space-x-0">
            <NavigationMenuItem className="hidden md:flex">
              <NavigationMenuTrigger
                className={cn(
                  buttonVariants({ variant: "outline" }),
                  "border-neutral-300 border-dashed dark:border-neutral-600",
                )}
              >
                Solutions
              </NavigationMenuTrigger>
              <NavigationMenuContent>
                <ul className="grid w-[400px] gap-3 p-4 md:w-[500px] md:grid-cols-2 lg:w-[600px]">
                  {solutions.map(({ title, href, description, disabled }) => (
                    <HeaderListItem
                      key={title}
                      title={title}
                      href={href}
                      disabled={disabled}
                      className="relative flex min-h-[66px] items-center space-y-0 truncate border border-neutral-200 border-dashed px-5 dark:border-neutral-700"
                    >
                      {description}
                    </HeaderListItem>
                  ))}
                </ul>
              </NavigationMenuContent>
            </NavigationMenuItem>

            <NavigationMenuItem className="hidden md:flex">
              <NavigationMenuTrigger
                className={cn(
                  buttonVariants({ variant: "outline" }),
                  "border-neutral-300 border-dashed dark:border-neutral-600",
                )}
              >
                Developers
              </NavigationMenuTrigger>
              <NavigationMenuContent>
                <div className="grid w-[400px] gap-4 p-4 md:w-[500px] md:grid-cols-2 lg:w-[600px]">
                  <div>
                    <p className="mb-2 font-normal text-muted-foreground text-sm">Resources</p>
                    <ul className="space-y-2">
                      {developers.map(({ title, description, href }) => (
                        <HeaderListItem
                          className="relative flex min-h-[66px] items-center space-y-0 border border-neutral-200 border-dashed px-5 dark:border-neutral-700"
                          key={title}
                          title={title}
                          href={href}
                        >
                          {description}
                        </HeaderListItem>
                      ))}
                    </ul>
                  </div>
                  <div>
                    <p className="mb-2 font-normal text-muted-foreground text-sm">Use Cases & Demos</p>
                    <ul className="space-y-2">
                      {demos.map(({ title, href }) => (
                        <HeaderListItem
                          className="flex items-center space-y-0 truncate border border-neutral-200 border-dashed px-5 dark:border-neutral-700"
                          key={title}
                          title={title}
                          href={href}
                        />
                      ))}
                    </ul>
                  </div>
                </div>
              </NavigationMenuContent>
            </NavigationMenuItem>

            <NavigationMenuItem className="hidden md:flex">
              <NavigationMenuTrigger
                className={cn(
                  buttonVariants({ variant: "outline" }),
                  "border-neutral-300 border-dashed dark:border-neutral-600",
                )}
              >
                Company
              </NavigationMenuTrigger>
              <NavigationMenuContent>
                <div className="grid w-[400px] gap-4 p-4 md:w-[500px] md:grid-cols-2 lg:w-[600px]">
                  <div>
                    <p className="mb-2 font-normal text-muted-foreground text-sm">About</p>
                    <ul className="space-y-2">
                      {company.map(({ title, description, href }) => (
                        <HeaderListItem
                          className="relative flex min-h-[66px] items-center space-y-0 border border-neutral-200 border-dashed px-5 dark:border-neutral-700"
                          key={title}
                          title={title}
                          href={href}
                        >
                          {description}
                        </HeaderListItem>
                      ))}
                    </ul>
                  </div>

                  <div>
                    <p className="mb-2 font-normal text-muted-foreground text-sm">Socials</p>
                    <ul className="space-y-2">
                      {socials.map(({ title, description, image, href }) => (
                        <HeaderListItem
                          className="flex min-h-[66px] items-center space-y-0 border border-neutral-200 border-dashed px-5 dark:border-neutral-700"
                          key={title}
                          title={
                            <p className="relative top-0.5 flex flex-row items-center gap-3">
                              {image} {title}
                            </p>
                          }
                          href={href}
                        >
                          {description}
                        </HeaderListItem>
                      ))}
                    </ul>
                  </div>
                </div>
              </NavigationMenuContent>
            </NavigationMenuItem>

            <NavigationMenuItem className="hidden md:flex">
              <NavigationMenuLink
                asChild
                className={cn(
                  navigationMenuTriggerStyle(),
                  buttonVariants({ variant: "outline" }),
                  "border-neutral-300 border-dashed dark:border-neutral-600",
                )}
              >
                <ProgressBarLink href="/blog">Blog</ProgressBarLink>
              </NavigationMenuLink>
            </NavigationMenuItem>

            <li>
              <ul className="flex flex-row-reverse gap-3 md:flex-row md:gap-2.5">
                <li>
                  <ThemeToggle variant="outline" className="border-neutral-300 border-dashed dark:border-neutral-600" />
                </li>

                <NavigationMenuItem>
                  <Link
                    href="https://share.hsforms.com/1y4akhGomTBet6MkD9mcdSgq7xur"
                    legacyBehavior
                    passHref
                    target="_blank"
                  >
                    <NavigationMenuLink className={cn(navigationMenuTriggerStyle(), buttonVariants(), "bg-primary")}>
                      Contact Us
                    </NavigationMenuLink>
                  </Link>
                </NavigationMenuItem>
              </ul>
            </li>
          </NavigationMenuList>

          <MobileMenu
            links={{
              company,
              developers,
              solutions,
              socials,
              demos,
            }}
          />
        </NavigationMenu>
      </div>
    </header>
  );
}

HeaderListItem.displayName = "HeaderListItem";
