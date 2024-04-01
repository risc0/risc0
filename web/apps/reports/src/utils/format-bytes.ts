import { isNil } from "lodash-es";

// Function to format bytes
export default function formatBytes(bytes: number) {
  if (isNil(bytes)) {
    return;
  }

  const units = ["B", "KB", "MB", "GB", "TB"] as const;
  let unitIndex = 0;

  while (bytes >= 1024 && unitIndex < units.length - 1) {
    // biome-ignore lint/style/noParameterAssign: not my code
    bytes /= 1024;
    unitIndex++;
  }

  return `${bytes.toFixed(2)}${units[unitIndex]}`;
}
