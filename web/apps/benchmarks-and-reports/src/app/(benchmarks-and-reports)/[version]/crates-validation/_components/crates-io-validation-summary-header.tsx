import { Tooltip, TooltipArrow, TooltipContent, TooltipTrigger } from "@risc0/ui/tooltip";
import { CheckCircle2Icon, CircleAlertIcon, CircleDotIcon } from "lucide-react";
import type { CratesIoValidationTableSchema } from "./crates-io-validation-table-schema";

type CratesIoValidationSummaryHeaderProps = {
  data: CratesIoValidationTableSchema[];
};

export function CratesIoValidationSummaryHeader({ data }: CratesIoValidationSummaryHeaderProps) {
  const successCount = data.filter((item) => item.status === "Success").length;
  const buildFailCount = data.filter((item) => item.status === "BuildFail").length;
  const neutralCount = data.length - successCount - buildFailCount;

  return (
    <div className="flex items-center gap-4">
      <h2 className="subtitle">Crates Build Status Summary</h2>
      <h3 className="flex flex-row items-center gap-3 text-muted-foreground text-sm">
        <Tooltip delayDuration={0}>
          <TooltipTrigger asChild>
            <div className="flex cursor-help flex-row items-center">
              <CheckCircle2Icon className="mr-1 size-3 text-green-600 dark:text-green-400" />
              {successCount}
            </div>
          </TooltipTrigger>
          <TooltipContent disableAnimation>
            Success
            <TooltipArrow />
          </TooltipContent>
        </Tooltip>

        <Tooltip delayDuration={0}>
          <TooltipTrigger asChild>
            <div className="flex cursor-help flex-row items-center">
              <CircleAlertIcon className="mr-1 size-3 text-red-600 dark:text-red-400" />
              {buildFailCount}
            </div>
          </TooltipTrigger>
          <TooltipContent disableAnimation>
            Build Fail
            <TooltipArrow />
          </TooltipContent>
        </Tooltip>

        <Tooltip delayDuration={0}>
          <TooltipTrigger asChild>
            <div className="flex cursor-help flex-row items-center">
              <CircleDotIcon className="mr-1 size-3 text-neutral-600 dark:text-neutral-400" />
              {neutralCount}
            </div>
          </TooltipTrigger>
          <TooltipContent disableAnimation>
            Skipped
            <TooltipArrow />
          </TooltipContent>
        </Tooltip>
      </h3>
    </div>
  );
}
