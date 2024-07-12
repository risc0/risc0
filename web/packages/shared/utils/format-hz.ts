import { isNil } from "./is-nil";

const UNITS = ["Hz", "KHz", "MHz", "GHz"] as const;

export function formatHz(hertz: number) {
  if (isNil(hertz)) {
    return;
  }

  let unitIndex = 0;

  while (hertz >= 1000 && unitIndex < UNITS.length - 1) {
    // biome-ignore lint/style/noParameterAssign: not my code
    hertz /= 1000;
    unitIndex++;
  }

  return `${hertz.toFixed(2)} ${UNITS[unitIndex]}`;
}
