import { redirect } from "next/navigation";
import { replace } from "string-ts";
import type { Version } from "~/types/version";
import { APPLICATIONS_BENCHMARKS_FILENAMES_TO_TITLES } from "./[slug]/_utils/constants";

export const dynamic = "error";

export default function ApplicationsBenchmarksPage({
  params,
}: {
  params: {
    version: Version;
    slug: string;
  };
}) {
  const firstElement = Object.keys(APPLICATIONS_BENCHMARKS_FILENAMES_TO_TITLES[params.version])[0];

  if (!params.slug && firstElement) {
    redirect(`/${params.version}/applications-benchmarks/${replace(firstElement, ".csv", "")}`);
  }

  return null;
}
