import { isNil } from "./is-nil";

const THRESHOLDS = [1000, 1000, 1000, 60, 60] as const;
const UNITS = ["ns", "µs", "ms", "s", "m", "h"] as const;

export function formatDuration(duration: number): string {
  if (isNil(duration)) {
    return "";
  }

  let unitIndex = 0;

  // @ts-expect-error -- not my code
  while (duration >= THRESHOLDS[unitIndex] && unitIndex < THRESHOLDS.length) {
    // @ts-expect-error -- not my code
    // biome-ignore lint/style/noParameterAssign: not my code
    duration /= THRESHOLDS[unitIndex];
    unitIndex++;
  }

  // Special handling for minutes to include remaining seconds
  if (UNITS[unitIndex] === "m") {
    const minutes = Math.floor(duration);
    const seconds = (duration - minutes) * 60;
    return `${minutes}m ${seconds.toFixed(0)}s`;
  }

  // Special handling for hours to include remaining minutes
  if (UNITS[unitIndex] === "h") {
    const hours = Math.floor(duration);
    const minutes = (duration - hours) * 60;
    return `${hours}h ${minutes.toFixed(0)}m`;
  }

  // Format the result to two decimal places and add the appropriate unit
  return `${duration.toFixed(2)}${UNITS[unitIndex]}`;
}
