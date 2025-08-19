"use client";

import { Button, type ButtonProps } from "@risc0/ui/button";
import { useIsMounted } from "@risc0/ui/hooks/use-is-mounted";
import { MoonIcon, SunIcon } from "lucide-react";
import { useTheme } from "next-themes";

export function ThemeToggle({ ...rest }: ButtonProps) {
  const isMounted = useIsMounted();
  const { setTheme, resolvedTheme } = useTheme();

  if (!isMounted) {
    return <div className="size-[36px]" />;
  }

  return (
    <Button
      variant="ghost"
      size="icon"
      onClick={() => {
        setTheme(resolvedTheme === "dark" ? "light" : "dark");
      }}
      startIcon={resolvedTheme === "dark" ? <SunIcon /> : <MoonIcon />}
      {...rest}
    >
      <span className="sr-only">Toggle Theme</span>
    </Button>
  );
}
