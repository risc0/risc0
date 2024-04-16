"use client";

import { Button } from "@risc0/ui/button";
import { cn } from "@risc0/ui/cn";
import { DropdownMenu, DropdownMenuContent, DropdownMenuItem, DropdownMenuTrigger } from "@risc0/ui/dropdown-menu";
import { CheckIcon, SunMoonIcon } from "lucide-react";
import { useTheme } from "next-themes";
import { useEffect, useState } from "react";

function ButtonBase() {
  return (
    <>
      <Button size="sm" className="hidden sm:flex" variant="outline" startIcon={<SunMoonIcon />}>
        Toggle Theme
      </Button>
      <Button size="icon-sm" className="flex sm:hidden" variant="outline" startIcon={<SunMoonIcon />}>
        <span className="sr-only">Toggle Theme</span>
      </Button>
    </>
  );
}

export function ThemeToggle({ className }: { className?: string }) {
  const { theme, setTheme } = useTheme();
  const [isMounted, setIsMounted] = useState<boolean>(false);

  useEffect(() => {
    setIsMounted(true);
  }, []);

  if (!isMounted) {
    return <ButtonBase />;
  }

  return (
    <DropdownMenu>
      <DropdownMenuTrigger asChild className={className}>
        <div>
          <ButtonBase />
        </div>
      </DropdownMenuTrigger>

      <DropdownMenuContent align="end">
        <DropdownMenuItem className="cursor-pointer" onClick={() => setTheme("light")}>
          <CheckIcon
            className={cn("mr-2 size-3 text-muted-foreground opacity-0", theme === "light" && "opacity-100")}
          />
          Light
        </DropdownMenuItem>
        <DropdownMenuItem className="cursor-pointer" onClick={() => setTheme("dark")}>
          <CheckIcon className={cn("mr-2 size-3 text-muted-foreground opacity-0", theme === "dark" && "opacity-100")} />
          Dark
        </DropdownMenuItem>
        <DropdownMenuItem className="cursor-pointer" onClick={() => setTheme("system")}>
          <CheckIcon
            className={cn("mr-2 size-3 text-muted-foreground opacity-0", theme === "system" && "opacity-100")}
          />
          System
        </DropdownMenuItem>
      </DropdownMenuContent>
    </DropdownMenu>
  );
}
