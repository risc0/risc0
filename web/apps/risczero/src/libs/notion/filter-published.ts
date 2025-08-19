import type { Investor, Leadership, Post, Project } from "@/app/blog/_types";

export function filterPublished<T extends Post | Project | Leadership | Investor>({ entries }: { entries: T[] }): T[] {
  if (entries.length === 0) {
    return [] as T[];
  }

  return entries.filter((entry) => entry.title && entry.status?.[0] === "Published");
}
