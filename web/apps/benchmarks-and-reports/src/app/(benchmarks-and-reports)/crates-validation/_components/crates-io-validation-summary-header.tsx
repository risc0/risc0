import { Tooltip, TooltipArrow, TooltipContent, TooltipTrigger } from "@risc0/ui/tooltip";
import { CheckCircle2Icon, CircleAlertIcon, CircleDotIcon } from "lucide-react";
import type { CratesIoValidationTableSchema } from "./crates-io-validation-table-schema";

export function CratesIoValidationSummaryHeader({ data }: { data: CratesIoValidationTableSchema[] }) {
  const successCount = data.filter((item) => item.status === "Success").length;
  const buildFailCount = data.filter((item) => item.status === "BuildFail").length;
  const neutralCount = data.length - successCount - buildFailCount;
  const successPercentage = (successCount / data.length) * 100;
  const buildFailPercentage = (buildFailCount / data.length) * 100;
  const neutralPercentage = (neutralCount / data.length) * 100;

  return (
    <div className="flex items-center gap-6">
      <h2 className="subtitle">Crates Build Status Summary</h2>
      <h3 className="flex flex-row items-center gap-6 text-muted-foreground text-sm">
        <Tooltip delayDuration={0}>
          <TooltipTrigger asChild>
            <div className="flex cursor-help flex-row items-center">
              <CheckCircle2Icon className="mr-1 size-3 text-green-600 dark:text-green-400" />
              <div>
                <span className="text-green-600 dark:text-green-400">{successCount}</span>{" "}
                <span className="ml-1 text-xs">({Math.floor(successPercentage)}%)</span>
              </div>
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
              <div>
                <span className="text-red-600 dark:text-red-400">{buildFailCount}</span>{" "}
                <span className="ml-1 text-xs">({Math.floor(buildFailPercentage)}%)</span>
              </div>
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
              <div>
                <span className="text-neutral-600 dark:text-neutral-400">{neutralCount}</span>{" "}
                <span className="ml-1 text-xs">({Math.floor(neutralPercentage)}%)</span>
              </div>
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
