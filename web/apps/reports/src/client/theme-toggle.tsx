"use client";

import { Button } from "@risc0/ui/button";
import { cn } from "@risc0/ui/cn";
import { DropdownMenu, DropdownMenuContent, DropdownMenuItem, DropdownMenuTrigger } from "@risc0/ui/dropdown-menu";
import { CheckIcon, SunMoonIcon } from "lucide-react";
import { useTheme } from "next-themes";
import { useEffect, useState } from "react";

export function ThemeToggle({ className }: { className?: string }) {
  const { theme, setTheme } = useTheme();
  const [isMounted, setIsMounted] = useState<boolean>(false);

  useEffect(() => {
    setIsMounted(true);
  }, []);

  if (!isMounted) {
    return <div className="h-8" />;
  }

  return (
    <DropdownMenu>
      <DropdownMenuTrigger asChild className={className}>
        <Button size="sm" variant="ghost" startIcon={<SunMoonIcon />}>
          Toggle Theme
        </Button>
      </DropdownMenuTrigger>

      <DropdownMenuContent align="end">
        <DropdownMenuItem onClick={() => setTheme("light")}>
          <CheckIcon
            className={cn("mr-2 size-3 text-muted-foreground opacity-0", theme === "light" && "opacity-100")}
          />
          Light
        </DropdownMenuItem>
        <DropdownMenuItem onClick={() => setTheme("dark")}>
          <CheckIcon className={cn("mr-2 size-3 text-muted-foreground opacity-0", theme === "dark" && "opacity-100")} />
          Dark
        </DropdownMenuItem>
        <DropdownMenuItem onClick={() => setTheme("system")}>
          <CheckIcon
            className={cn("mr-2 size-3 text-muted-foreground opacity-0", theme === "system" && "opacity-100")}
          />
          System
        </DropdownMenuItem>
      </DropdownMenuContent>
    </DropdownMenu>
  );
}
