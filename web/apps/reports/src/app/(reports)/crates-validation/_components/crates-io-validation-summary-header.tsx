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
      <h3 className="flex flex-row items-center text-muted-foreground text-sm">
        <CheckCircle2Icon className="mr-1 size-3 text-green-400" />
        {successCount}
        <CircleAlertIcon className="mr-1 ml-2 size-3 text-red-400" />
        {buildFailCount}
        <CircleDotIcon className="mr-1 ml-2 size-3 text-neutral-400" />
        {neutralCount}
      </h3>
    </div>
  );
}
