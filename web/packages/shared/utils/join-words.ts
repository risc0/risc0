import { join, words } from "string-ts";

export function joinWords(str: string): string {
  if (!str) {
    return "";
  }

  return join(words(str), " ");
}
