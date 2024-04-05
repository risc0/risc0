import { isNil } from "lodash-es";

export function formatHz(hertz: number) {
  if (isNil(hertz)) {
    return;
  }

  let unitIndex = 0;
  const units = ["Hz", "KHz", "MHz", "GHz"] as const;

  while (hertz >= 1000 && unitIndex < units.length - 1) {
    // biome-ignore lint/style/noParameterAssign: not my code
    hertz /= 1000;
    unitIndex++;
  }

  return `${hertz.toFixed(2)}${units[unitIndex]}`;
}
