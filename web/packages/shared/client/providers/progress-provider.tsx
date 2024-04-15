"use client";

import { useTheme } from "next-themes";
import { Next13NProgress } from "nextjs13-progress";
import { useEffect, useState } from "react";

export default function ProgressProvider() {
  const { resolvedTheme } = useTheme();
  const [isMounted, setIsMounted] = useState<boolean>(false);

  useEffect(() => {
    setIsMounted(true);
  }, []);

  if (!isMounted) {
    return null;
  }

  return <Next13NProgress color={resolvedTheme === "dark" ? "#fdff9d" : "#2e2e2e"} height={1} showOnShallow={false} />;
}
