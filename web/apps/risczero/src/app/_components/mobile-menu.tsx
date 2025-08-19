"use client";

import { Button } from "@risc0/ui/button";
import { Separator } from "@risc0/ui/separator";
import { Sheet, SheetContent, SheetTrigger } from "@risc0/ui/sheet";
import { MenuIcon } from "lucide-react";
import { useState } from "react";
import { HeaderListItem } from "./header";
import { Subtitle } from "./subtitle";

export function MobileMenu({ links: { company, developers, solutions, demos, socials } }) {
  const [open, setOpen] = useState<boolean>(false);

  return (
    <Sheet open={open} onOpenChange={setOpen}>
      <SheetTrigger asChild>
        <Button
          startIcon={<MenuIcon />}
          className="ml-3 flex border-neutral-300 border-dashed md:hidden dark:border-neutral-600"
          variant="outline"
          size="icon"
        >
          <span className="sr-only">Menu</span>
        </Button>
      </SheetTrigger>
      <SheetContent className="z-[80] p-0" sheetOverlayClassName="z-[75]">
        <ul className="h-full overflow-auto px-6 pt-8 pb-4">
          <Subtitle className="mb-2 text-muted-foreground md:text-lg">Solutions</Subtitle>

          {solutions.map(({ title, description, disabled, href }) => (
            <HeaderListItem
              key={title}
              title={title}
              href={href}
              disabled={disabled}
              onClick={() => {
                setOpen(false);
              }}
            >
              {description}
            </HeaderListItem>
          ))}

          <Separator className="-mx-6 mt-3 w-[calc(100%+3rem)]" />

          <Subtitle className="mt-4 mb-2 text-muted-foreground md:text-lg">Developers</Subtitle>

          {developers.map(({ title, description, href }) => (
            <HeaderListItem
              key={title}
              title={title}
              href={href}
              onClick={() => {
                setOpen(false);
              }}
            >
              {description}
            </HeaderListItem>
          ))}

          <Separator className="-mx-6 mt-3 w-[calc(100%+3rem)]" />

          <Subtitle className="mt-4 mb-2 text-muted-foreground md:text-lg">Uses Cases & Demos</Subtitle>

          {demos.map(({ title, description, href }) => (
            <HeaderListItem
              key={title}
              title={title}
              href={href}
              onClick={() => {
                setOpen(false);
              }}
            >
              {description}
            </HeaderListItem>
          ))}

          <Separator className="-mx-6 mt-3 w-[calc(100%+3rem)]" />

          <Subtitle className="mt-4 mb-2 text-muted-foreground md:text-lg">Company</Subtitle>

          {company.map(({ title, description, href }) => (
            <HeaderListItem
              key={title}
              title={title}
              href={href}
              onClick={() => {
                setOpen(false);
              }}
            >
              {description}
            </HeaderListItem>
          ))}

          <HeaderListItem
            title="Blog"
            href="/blog"
            onClick={() => {
              setOpen(false);
            }}
          >
            Learn about RISC Zero's technology
          </HeaderListItem>

          <Separator className="-mx-6 mt-3 w-[calc(100%+3rem)]" />

          <Subtitle className="mt-4 mb-2 text-muted-foreground md:text-lg">Socials</Subtitle>

          {socials.map(({ title, description, href }) => (
            <HeaderListItem
              key={title}
              title={title}
              href={href}
              onClick={() => {
                setOpen(false);
              }}
            >
              {description}
            </HeaderListItem>
          ))}
        </ul>
      </SheetContent>
    </Sheet>
  );
}
