import { isNil } from "./is-nil";

const THRESHOLDS = [1000, 1000, 1000, 60, 60] as const;
const UNITS = ["ns", "µs", "ms", "s", "m", "h"] as const;

export function formatDuration(duration: number) {
  if (isNil(duration)) {
    return;
  }

  let unitIndex = 0;

  // @ts-expect-error -- not my code
  while (duration >= THRESHOLDS[unitIndex] && unitIndex < THRESHOLDS.length) {
    // @ts-expect-error -- not my code
    // biome-ignore lint/style/noParameterAssign: not my code
    duration /= THRESHOLDS[unitIndex];
    unitIndex++;
  }

  return `${duration.toFixed(2)}${UNITS[unitIndex]}`;
}
