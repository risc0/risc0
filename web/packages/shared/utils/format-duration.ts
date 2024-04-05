import { isNil } from "lodash-es";

export function formatDuration(duration: number) {
  if (isNil(duration)) {
    return;
  }

  let unitIndex = 0;
  const thresholds = [1000, 1000, 1000, 60, 60] as const;
  const units = ["ns", "µs", "ms", "s", "min", "h"] as const;

  // @ts-expect-error -- not my code
  while (duration >= thresholds[unitIndex] && unitIndex < thresholds.length) {
    // @ts-expect-error -- not my code
    // biome-ignore lint/style/noParameterAssign: not my code
    duration /= thresholds[unitIndex];
    unitIndex++;
  }

  return `${duration.toFixed(2)}${units[unitIndex]}`;
}
