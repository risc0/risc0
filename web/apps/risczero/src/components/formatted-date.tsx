import { formatDate } from "@/utils/date";
import { cn } from "@risc0/ui/cn";

type FormattedDateProps = {
  date: number | string | Date;
  showWeekday?: boolean;
  className?: string;
};

export function FormattedDate({ date, showWeekday = false, className }: FormattedDateProps) {
  return (
    <p className={cn("text-muted-foreground text-sm", className)}>
      <time dateTime={new Date(date).toISOString()}>{formatDate(date, { showWeekday })}</time>
    </p>
  );
}
