import { isNil } from "lodash-es";

const UNITS = ["B", "KB", "MB", "GB", "TB"] as const;

// Function to format bytes
export function formatBytes(bytes: number) {
  if (isNil(bytes)) {
    return;
  }

  let unitIndex = 0;

  while (bytes >= 1024 && unitIndex < UNITS.length - 1) {
    // biome-ignore lint/style/noParameterAssign: not my code
    bytes /= 1024;
    unitIndex++;
  }

  return `${bytes.toFixed(2)} ${UNITS[unitIndex]}`;
}
