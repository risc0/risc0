import { cn } from "@risc0/ui/cn";

export function AsciiArt({
  withWrapper = false,
  code,
  className,
}: {
  withWrapper?: boolean;
  code: string;
  className?: string;
}) {
  return (
    <div className={cn(withWrapper && "flex justify-center rounded border bg-neutral-50 p-4 dark:bg-neutral-900")}>
      <pre
        className={cn("whitespace-pre font-bold font-mono-raw leading-none", className)}
        // biome-ignore lint/security/noDangerouslySetInnerHtml: ignore for ascii art, need to keep newline chars
        dangerouslySetInnerHTML={{ __html: code }}
      />
    </div>
  );
}
