type Option = {
  showWeekday?: boolean;
  locale?: Intl.LocalesArgument;
  timeZone?: string;
};

export function formatDate(date: string | number | Date, options: Option = {}): string {
  options.locale ??= "en-US";
  options.showWeekday ??= false;
  options.timeZone ??= "UTC"; // default to UTC

  const { locale, timeZone, showWeekday } = options;

  return new Date(date).toLocaleDateString(locale, {
    year: "numeric",
    month: "long",
    day: "2-digit",
    weekday: showWeekday ? "long" : undefined,
    timeZone,
  });
}
