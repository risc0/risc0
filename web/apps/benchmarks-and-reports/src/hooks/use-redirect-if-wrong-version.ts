import { redirect } from "next/navigation";
import type { Version } from "~/types/version";
import { VERSIONS } from "~/versions";

export function useRedirectIfWrongVersion(version: Version) {
  if (VERSIONS.findIndex(({ value }) => value === version) === -1) {
    redirect("/");
  }
}
