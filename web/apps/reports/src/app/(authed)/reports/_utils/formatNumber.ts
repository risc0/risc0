import formatters from "@poppinss/intl-formatter";

export default function formatNumber(input: number | string, options?: Intl.NumberFormatOptions) {
  return formatters.number("en-US", options).format(input);
}
