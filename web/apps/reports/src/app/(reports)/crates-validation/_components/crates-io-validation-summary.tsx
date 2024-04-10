import { Badge } from "@risc0/ui/badge";
import { cn } from "@risc0/ui/cn";
import { Tooltip, TooltipArrow, TooltipContent, TooltipTrigger } from "@risc0/ui/tooltip";
import type { CratesIoValidationTableSchema } from "./crates-io-validation-table-schema";

type CratesIoValidationSummaryProps = {
  data: CratesIoValidationTableSchema[];
};

export function CratesIoValidationSummary({ data }: CratesIoValidationSummaryProps) {
  return (
    <div className="mt-2 mb-8 flex flex-row flex-wrap">
      {data.map((item) => (
        <Tooltip key={item.name} disableHoverableContent delayDuration={0}>
          <TooltipTrigger asChild>
            <div
              className={cn(
                item.status === "Success"
                  ? "border-green-400 bg-green-200 dark:border-green-500 dark:bg-green-300"
                  : item.status === "BuildFail"
                    ? "border-red-300 bg-red-200 dark:border-red-500 dark:bg-red-300"
                    : "border-neutral-400 bg-neutral-300 dark:border-neutral-500",
                "hover:!border-neutral-500 dark:hover:!border-white size-3 rounded-[3px] border hover:border-2",
              )}
            />
          </TooltipTrigger>
          <TooltipContent disableAnimation className="flex items-center gap-4">
            <p>{item.name}</p>
            {item.version && <p>v{item.version}</p>}
            <Badge variant="outline" className="rounded-full text-[10px] text-white dark:text-black">
              {item.status}
            </Badge>
            <TooltipArrow />
          </TooltipContent>
        </Tooltip>
      ))}
    </div>
  );
}
