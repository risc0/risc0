import { cn } from "@risc0/ui/cn";
import { Loader2Icon } from "lucide-react";

export function SuspenseLoader({ className }: { className?: string }) {
  return <Loader2Icon className={cn("h-4 animate-spin opacity-10", className)} />;
}
