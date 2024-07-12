import { isNil } from "./is-nil";

const UNITS = ["", "K", "M", "G", "T"] as const;

// Function to format cycles
export function formatCycles(cycles: number) {
  if (isNil(cycles)) {
    return;
  }

  if (cycles === 0) {
    return "N/A";
  }

  let unitIndex = 0;

  while (cycles >= 1024 && unitIndex < UNITS.length - 1) {
    // biome-ignore lint/style/noParameterAssign: not my code
    cycles /= 1024;
    unitIndex++;
  }

  return `${cycles.toFixed(2)} ${UNITS[unitIndex]}`;
}
