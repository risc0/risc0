import formatters from "@poppinss/intl-formatter";

export function formatNumber(input: number | string, options?: Intl.NumberFormatOptions) {
  return formatters.number("en-US", options).format(input);
}
