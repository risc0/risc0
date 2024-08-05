import { Badge } from "@risc0/ui/badge";
import { cn } from "@risc0/ui/cn";
import { Tooltip, TooltipArrow, TooltipContent, TooltipTrigger } from "@risc0/ui/tooltip";
import { joinWords } from "@risc0/ui/utils/join-words";
import type { CratesIoValidationTableSchema } from "./crates-io-validation-table-schema";

export function CratesIoValidationSummary({ data }: { data: CratesIoValidationTableSchema[] }) {
  return (
    <div className="mt-2 mb-8 flex flex-row flex-wrap">
      {data.map((item) => (
        <Tooltip key={item.name} disableHoverableContent delayDuration={0}>
          <TooltipTrigger asChild>
            <a
              className="group p-[0.5px]"
              href={`https://crates.io/crates/${item.name}${item.version ? `/${item.version}` : ""}`}
              target="_blank"
              rel="noopener noreferrer"
            >
              <span className="sr-only">{`https://crates.io/crates/${item.name}${
                item.version ? `/${item.version}` : ""
              }`}</span>
              <div
                className={cn(
                  item.status === "Success"
                    ? "border-green-400 bg-green-200 dark:border-green-500 dark:bg-green-300"
                    : item.status === "BuildFail"
                      ? "border-red-400 bg-red-200 dark:border-red-500 dark:bg-red-300"
                      : "border-neutral-400 bg-neutral-200 dark:border-neutral-500 dark:bg-neutral-300",
                  "block size-3 rounded-[2.5px] border group-hover:border-2 group-hover:border-black dark:group-hover:border-white",
                )}
              />
            </a>
          </TooltipTrigger>
          <TooltipContent disableAnimation className="flex min-w-[240px] items-center justify-between gap-4 shadow-lg">
            <p>{item.name}</p>
            {item.version && <p>v{item.version}</p>}
            <Badge
              className={cn(
                "rounded-full p-2 py-0 text-[10px]",
                item.status === "Success"
                  ? "border-green-200 bg-green-50 dark:bg-green-950"
                  : item.status === "BuildFail"
                    ? "border-red-200 bg-red-50 dark:bg-red-950"
                    : "text-white dark:text-black",
              )}
              variant="outline"
            >
              {joinWords(item.status)}
            </Badge>
            <TooltipArrow />
          </TooltipContent>
        </Tooltip>
      ))}
    </div>
  );
}
